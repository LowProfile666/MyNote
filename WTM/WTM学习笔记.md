# WTM学习笔记

>  Walking Tec MVVM。

## 一、初始

### 1、项目结构

![image-20231111100304791](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111003856.png)

+ ReviewSystem：Web的主项目
+ DataAccess：数据层
+ Model：模型层
+ Test：测试
+ ViewModel：视图层

在调试模式下，界面的左侧菜单都是 Controller 反射生成的，实际页面需要在菜单管理中配置。

### 2、模型

数据库中的每个表就是一个模型，就是代码中的一个类，一个`.cs`文件。就是创建类，框架会自动生成数据库的表。

![image-20231111100820692](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111008715.png)

每个模型都需要继承框架提供的基类，可以不继承，但是不继承就代表着不用框架的功能。

+ TopBasePoco：有Guid等字段
+ BasePoco：继承 TopBasePoco，多了一些创建人、创建时间的字段，对于这些字段，框架会自动更改。
+ PersistPoco：可以假删除，继承 BasePoco，不能物理删除，多了一个 IsVaild 字段。

类中的属性就是表中的字段，可以通过DataAnnotation的方法来对字段进行一定程度上的限制。

```c#
public class IndicatorInfo : TopBasePoco
{
    [Display(Name = "内容")] 
    [Required(ErrorMeesage = "这个是必填项")]
    [StringLength(10)]    
    public string Name { get; set; }
}
```

+ Display：  给这个字段起个名，后期在表单中可以绑定一个Textbox，这个Textbox的label就会默认显示这个名字
+ Required()：设置必填项
  + Required(ErrorMeesage = "这个是必填项")：定义如果没有填的话输出自定义的错误信息，默认是ASP .Net Core 的自定义错误信息。
+ StringLength：限制字符串的最大长度

如果想要一个枚举属性不是必填的话，可以在属性名后加上一个`?`；也可以在属性名后加上了`?`后，再给一个`[Required()]`限制，这样可以实现：在代码上可以达到“已选择”、“未选择”的效果，但在数据库中是必填的。

枚举类型默认就是必填。

在枚举的字段上也可以加 Display，在页面上显示的就是自定义的名字，但是在数据库中还是整型 0 1 2 3 ……

定义完模型后，要在`DataContext`类中定义一个`DbSet<>`的属性，表示要在数据库中生成这个表。

```c#
 public partial class DataContext : FrameworkContext
{
    public DbSet<IndicatorInfo> IndicatorInfos { get; set; }
}
```

想要一个字段不在数据库中声明，只在页面显示，可以使用 `[NotMapped]` 。

想要添加正则表达式的验证可以使用 `[RegularExpression("", ErrorMessage="")]`，第一参数是正则表达式，第二个参数是不满足正则表达式后的错误信息。

想要给一个数值的字段设置范围，可以使用 `[Range(1,2,ErrorMessage="")]`，比如 `[Range(10, 20, ErrorMessage="错")]` 表示10 到 20。

Areas：只是给模型分个组，便于管理。

### 3、appsettings.json

全局配置文件。

```json
"Connections": [
    {
      "Key": "default",
      "Value": "Server=(localdb)\\mssqllocaldb;Database=ReviewSystem_db;Trusted_Connection=True;",
      "DbContext": "DataContext",
      "DBType": "SqlServer" //DataBase, you can choose mysql,sqlserver,pgsql,sqlite,oracle
    }
  ],
  "CookiePre": "ReviewSystem", //cookie prefix
  "IsQuickDebug": true, //is debug mode
   "EnableTenant":  true, //是否启动多租户
   "CorsOptions": {
    "EnableAll": true
  },
```

## 二、CodeFirst

先写代码，用代码生成数据库。

### 1、一对多关联

一个城市有多个医院：

```c#
public class City : TopBasePoco
{
    public string Name {get; set;}
}

public class Hospital : TopBasePoco 
{
    public string Name {get; set;}
    public City Location {get; set;}
    public Guid LocationId {get; set;}
}
```

Location 和 LocationId 成对出现说明 Hospital 这个表需要和 City 这张表有主外键关系，并且外键的名字叫做 LocationId ，这就是一对多，每个 Hospital 都有一个 City，表示一个 City 对应着多个 Hospital。

如果想要加照片或文件等，添加 `FileAttachMent File` 属性可以生成附件的上传和下载，FileAttachment 是框架自带的附件表，所以这是一个一对多的关联关系，所以还要配套使用 `FileId`：

```c#
public FileAttacment Photo {get; set;}
public Guid? PhotoId {get; set;}
```



### 2、树形结构

一个类和自己有主外键关系。

框架提供了一个树形结构的接口 `TreePoco<>` ，`<>`中的泛型还是写自己的类。

它自带三个字段

+ List<T> Children
+ T Parent
+ Guid? ParentId

```c#
public class City : TopBasePoco, TreePoco<City>
{
    public string Name {get; set;}
    public List<T> Children {get; set;}
    public T Parent {get; set;}
    public Guid? ParentId {get; set;}
}
```



### 3、自定义主键

直接定义一个 ID 属性覆盖：

```c#
[DatabaseGenerated(DatabaseGenerateOption.Identity)]
public new int ID {get; set;}
```

+ [DatabaseGenerated(DatabaseGenerateOption.Identity)]：设置自增



### 4、自定义表名

在类名上面加一个 `[Table("")]`，这类表名用于自己手写SQL语句时。



### 5、多对多

多对多就是两个一对多，需要一个中间表。

比如一个人可以得多种病，一种病也可以被多个人得：

```c#
[MiddelTable]
public class PatientVirus : TopBasePoco
{
    public Patient Patient {get; set;}
    public Guid PatientId {get; set;}
    public Virus Virus {get; set;}
    public Guid VirusId {get; set;}
}
```

+ [MiddelTable]：框架提供的一个属性，和具体功能没有关系，是为了代码生成器生成多对多的代码

有了中间表之后，还需要在 Patient 和 Virus 中各定义一个 List<Virus> 和 List<Patient> 属性。



如果自定义索引，在 `DataContext` 中的 `OnModelCreating` 方法中通过流函数来定义索引：

```c#
modelBulider.Entity<Patient>().HasIndex(x => x.IdNumber);
```



## 三、MVVM

### 1、没有模式

一个空的Web项目。可以直接在 Program.cs 中实现一个简单的系统。

### 2、MVC 模式

模型视图控制器。

通过路由找到要访问的控制器里的某个方法，这个方法再返回一个页面。

路由：

```c#
// program.cs

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");
```

+ {controller=Home}：这里是 Controller 的名称
+ {action=Index}：这里是 Controller 里方法的名称
+ {id?}：这里是方法的参数，如果有就会去找 Controller 里带 id 参数的 Action

Controller 里的方法会把数据返回到 View 上，展现出页面：

路由支持覆盖，比如在 HomeController 里的 Index 方法上这样写：

```c#
// HomeController.cs

[HttpGet("/abc")]
public IActionResult Index()
{
    return View();
}
```

表示访问这个方法的路径是 abc，而不是原来的 Home/Index。

### 3、MVVM模式

通过路由找到 Controller，Controller 会创建自己的 ViewModel，最后把 ViewModel 返回给页面。ViewModel 中会封装一些跟 Model 相关的数据库操作，也就是，Model 只会有 ViewModel 会使用。

多加了一个 View Model 层，为什么多加？

+ 因为 Model 是和数据库对应的，很多时候就不适合展示在页面上
+ 可以在 VM 里面写一些通用的代码，实现代码复用

ViewModel 可能关联一个实体 Model，有可能不关联，和数据库没有关系。

MVVM 还是有 Controller 存在的，因为 Controller 是和 路由 配套的，如果没有 Controller 我们还是需要有 路由，那么路由就只能写在 ViewModel 中，还不如直接写在 Controller 中。

### 4、DDD

DDD 和 MVVM 没有关系。

DDD 是一种业务思考的方法。

### 5、生命周期

![image-20231111135842920](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111358013.png)



## 四、View和TagHelper

### 1、Layout、View、PartialView

View 会返回一个完整的目录 HTML 页面；PartialView 会返回一部分 HTML，在局部显示。

在 Views 目录下的 Shared 目录下有一个 \_Layout.cshtml 文件，就是一个完整的 HTML 的外壳，它里面有一个 `  @RenderBody()`，是用来替换当前输出的内容，

比如，在 LoginController 中：

```C#
public IActionResult Login()
{
    LoginVM vm = Wtm.CreateVM<LoginVM>();
    vm.Redirect = HttpContext.Request.Query["ReturnUrl"];
    if (Wtm.ConfigInfo.IsQuickDebug == true)
    {
        vm.ITCode = "admin";
        vm.Password = "000000";
    }
    return View(vm);
}
```

这个 Login 方法会去  Views 目录下找 Login 这个方法名对应的页面：

![image-20231111140910388](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111409484.png)

在这个 Login.cshtml 页面中，如果有以下这一句，说明不需要返回 Layout，本身就返回一个页面；否则呢，默认会使用 Shared 目录下的 \_Layout.cshtml 文件，将当前输出内容拼成一个页面：

```c#
Layout = null;
```

### 3、默认流程

当我们直接访问这个网站时，首先走的是 Controllers/HomeController.cs 中的 Index 方法：

```c#
// HomoController.cs

[AllRights]
public IActionResult Index()
{
    ViewData["title"] = "评测系统v1.0";
    return View();
}
```

这个页面框架背后会有权限验证的操作，如果发现你没有登录，就会跳转到 Controllers/LoginController.cs 中的 Login 方法，这个方法返回的就是 Views/Login.cshtml，这个页面背后的 LoginVM。

![image-20231111141752135](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111417174.png)



首页的右半部分就是：Views/Home/FrontPage.cshtml，左侧的菜单是在这个目录下的一个 Layout.cshtml 文件：

![image-20231111142523390](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111425426.png)

当前网站的标题和左侧顶部显示的标题是在 wwwroot/layuiadmin/config.js 文件中，它的 logo 文件是放在 layuiadmin/style/res 下的。

![image-20231111142554022](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111425055.png)

如果改变了左侧菜单顶部的文字和logo，如果没有显示，则按 F12，选择 network 下的 Disable Cache，清除缓存

### 4、TagHelper

在 .cshtml 文件中，所有带 `wt:` 的标签，都是框架提供的 TagHelper，本质的作用就是生成 HTML，原理还是反射。

```html
@model ReviewSystem.ViewModel.Front.RaterGroupVM
@using WalkingTec.Mvvm.Core.Extensions;
@inject IStringLocalizer<Program> Localizer;

<wt:searchpanel vm="@Model.IndicatorInfoListVM3" reset-btn="true"  grid-id="g1311699583634726" id="g5047877369">
  <wt:combobox field="IndicatorInfoListVM3.Searcher.FirstId"  item-url="/Data/Indicator/GetIndicators?istree=true&istop=true" empty-text="@Localizer["Sys.All"]" id="g5882126248" link-id="g5830755896"  trigger-url="/Data/Indicator/Select_GetIndicatorByIndicator"/>
  <wt:combobox field="IndicatorInfoListVM3.Searcher.SecndId"  empty-text="@Localizer["Sys.All"]" id="g5830755896"/>
  <wt:textbox field="IndicatorInfoListVM3.Searcher.Name" id="g8586028423"/>
  <wt:textbox field="IndicatorInfoListVM3.Searcher.DepartmentNumber" id="g3972781151"/>
</wt:searchpanel>

<wt:form vm="@Model.IndicatorInfoVM" url="/Data/IndicatorInfo/Create"  id="g1295547033">
  <wt:grid vm="@Model.IndicatorInfoListVM3" url="/Front/_Default/SearchIndicatorInfo3"  id="g1311699583634726" search-panel-id="g5047877369" Height="500"/>

  <wt:container align="AlignEnum.Right">
    <wt:submitbutton  text="@Localizer["Sys.Submit"].Value"/>
    <wt:closebutton  text="@Localizer["Sys.Close"].Value"/>
  </wt:container>

</wt:form>
```

`@model ReviewSystem.ViewModel.Front.RaterGroupVM` ：这是页面传过来的 ViewModel

`<wt:textbox field="IndicatorInfoListVM3.Searcher.Name"/>` ：field 绑定的是页面传过来的 VM 的某一个字段，框架会反射这个字段，会找到这个字段的 [Display()] 当作 label，如果这个字段有值的话，也会拿到这个值并显示在 textbox 中。

`combobox` 是下拉框，如果绑定的是一个枚举字段，它会自动去反射枚举字段里的每个值上的 [Display()] 中的信息，然后列成下拉框中的选项。

`checkbox` 是多选，使用在多对多关系上，也可以用 `cmobobox` 实现多选的功能，只需添加一个属性：`mulit-select="true"`。

更多参考官网文档Layui部分。

TagHelper 能起作用全靠 Areas 目录下的 \_ViewImports.cshtml 文件：

```c#
@using WalkingTec.Mvvm.TagHelpers.LayUI
@using Microsoft.Extensions.Localization;
@using ReviewSystem;
@addTagHelper *, WalkingTec.Mvvm.TagHelpers.LayUI
```

### 5、ViewModel 的桥梁作用

ViewModel 除了提供很多方法，还定义了字段让前台可以双向绑定。

### 6、前后台交互

**三级联动**：省市区的关系

```c#
<wt:combobox field="Sheng" items="AllSheng">
<wt:combobox field="Shi" items="AllShi">
<wt:combobox field="Entity.LocationId" items="AllQu">
```

+ `items` ：就是绑定的数据源
+ Sheng、Shi、Qu：都是自定义的属性，数据库中没有的，在 InitVM 中初始化的，所以前面也不用加 `Entity.`

用于联动的两个属性：

+ `trigger-url` ：后台的数据位置，联动后的数据来源
+ `link-field` ：绑定的是影响目标，当我动的时候，谁应该跟着动。

```c#
<wt:combobox field="Sheng" items="AllSheng" trigger-url="/City/GetChildrenCity" link-field="Shi">
<wt:combobox field="Shi" items="AllShi" trigger-url="/City/GetChildrenCity" link-field="Entity.LocationId">
<wt:combobox field="Entity.LocationId" items="AllQu">
```

`trigger-url` 会带着当前所选的 ID 去访问 url：

```c#
public IActionResult GetChilrenCity(string id)
{
    var res = DC.Set<City>().Where(x => x.ParentId == id).GetSelectListItems(LoginUserInfo.DataPrivileges, null, x => x.Name);
    return Json(res);
}
```

+ `GetSelectListItems()` ：框架提供的函数：快速生成 List<ComboSelectListItem>
+ 第一个参数：数据权限
+ 第二个参数：
+ 第三个参数：指定显示的字段

### 7、SearchPanel和Grid

SearchPanel 和 Grid 出现在列表页。

SearchPanel 本质上也会被渲染成一个 form，里面的控件绑定的字段都是搜索的条件。

Grid 只需要绑定一个 Model，指定一下搜索的 url 就可以了。

因为所有的逻辑都写在了对应的 ListVM 中。

## 五、WebAPI

## 六、权限和认证

权限分为

+ 页面权限：和某个功能相关，有没有资格访问某些页面、某个WebApi、某个按钮。
+ 数据权限：看到的页面是一样的，但是数据不一样

要使用权限，先关闭代码的debug模式。

### 1、角色和用户组

角色控制页面权限。

用户组控制数据权限。

在角色管理里面配置每个角色可以访问哪些页面。

### 2、页面权限

页面权限可以用框架直接配置，首先需要创建菜单，否则在非debug模式下，看不到左侧的菜单。

在菜单管理里新建菜单：

+ 目录：不用选模块，设置名称和顺序、图标等，没有父级，开启菜单显示、目录
  ![image-20231111152902745](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111529828.png)
+ 具体页面：要选某个模块，设置名称、顺序等，选父级表示这个页面在哪个目录下，
  ![image-20231111152932331](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111529394.png)

动作是这个模块的Controller中的方法，Index 方法是 主页面，如果没有

菜单显示表示在不在左侧菜单里显示；

角色如果不选，默认是系统管理员，可以选多个角色。

建完菜单后，要在右上角点击“刷新菜单”，然后在刷新页面，就能看到左侧的新配的菜单。

可以通过外部地址，来将一个功能直接添加成页面。

### 3、数据权限

在 Program.cs 中添加代码：

```csharp
var pris = new List<IDataPrivilege>
{
    new DataPrivilegeInfo<City>("地点", y => y.Name);
}
x.AddFrameworkService(dataPrivilegeSettings:pris);
```

![image-20231111155029544](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111550593.png)

然后在 ListVM.cs 中的 GetSearchQuery 方法里，使用 `DPWhere` 句是设置数据权限的。

在新建数据权限时，需要选择权限名称，这是在代码中指定的，或者是WTMPLUS创建页面时开启的，然后可以选择是否开启全部权限，否的话就可以选择具体的字段。

![image-20231111154503063](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111545116.png)

DataPrivilegeInfo<City>("地点", y => y.Name); 这一句中的 “地点” 就是在不是全部权限时，供选择的名字。

+ y.Name 是有数据权限的字段
+ “地点” 是这个数据权限的名字



### 4、自定义用户

新建一个新类，定义字段，在 DataContext 中添加对应的属性。

LoginUserInfo 中保存的是当前登录用户的信息，在 LoginController 中，当我们登录的时候，是会给 LoginUserInfo 赋值的，有个 DoLogin 方法，它会从数据库中取出信息，然后赋值给 LoginUserInfo ，可以通过 Attributes 属性来新添属性

![image-20231111160919386](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111609458.png)



## 七、ListVM

### 1、生命周期

```c#
public partial class IndicatorInfoListVM1 : BasePagedListVM<IndicatorInfo_View1, IndicatorInfoSearcher1>
{
}
```

ListVM 继承于 BasePagedListVM，有两个泛型，第一个泛型是最后输出的类型，第二个是 Searcher 的类

主要有三个函数：

**InitGridAction**：初始化列表上面的那一排按钮

**InitGridHeader**：列表的列
`MakeGridHeaderAction`：是上面函数里定义的在行内显示的按钮显示的列

**GetSearchQuery**：上面传的 Searcher 就是为了在这写查询语句

工作流程：Contronller 中的 Index 方法，返回一个 Index.cshtml 页面，这时还没有进行搜索，而是调用 ListVM 里面的 InitGridAction 和 InitGridHeader 两个方法，当前端渲染完后，才会执行 \<wt:grid url=""\>  中的 url 中指定的方法，去进行搜索。

### 2、自定义按钮

所有的按钮都在 `InitGridAction` 方法中定义，常用的按钮使用 `MakeStandardAction` 来定义，

```c#
this.MakeStandardAction("Stu_Situation", GridActionStandardTypesEnum.SimpleDelete, @Localizer["Sys.Delete"].Value, "Data", dialogWidth: 800).SetIconCls("fa fa-trash").SetButtonClass("layui-btn-danger"),
```

+ "Stu_Situation"：指定 controller 的方法
+ GridActionStandardTypesEnum.SimpleDelete ：通过枚举指定按钮的类型
+ "Data"：Area 的名字

自定义按钮使用 `MakeAction` 来定义。

```c#
this.MakeAction("Stu_Situation","Create",@Localizer["Sys.Create"].Value,@Localizer["Sys.Create"].Value,GridActionParameterTypesEnum.SingleIdWithNull,"Data",800).SetShowInRow(false).SetHideOnToolBar(false).SetIconCls("fa fa-plus"),
```

+ "Stu_Situation"：controller 的名字
+ "Create"：调用方法的名字
+ @Localizer["Sys.Create"].Value：按钮上显示的内容
+ @Localizer["Sys.Create"].Value：如果有弹出窗口，弹出窗口的名称
+ GridActionParameterTypesEnum.SingleIdWithNull：只传一个id，但id可能为空
+ "Data"：Areas 的名称
+ 800：弹出窗口的宽度
  + SetIconCls：设置图标，这个图标的名字是在 wwwroot/font 下的 ifconfig.svg 文件或者 wwwroot/layui/font 下的 ifconfig.svg 文件里定义的，前者是框架自带的，后者是 layui 的。

+ ……

**`MakeAction` 方法的最后一个参数是一个 whereStr，表示除了 Id 之外，还需要带这条数据的哪些字段到后台去。**

 给数据列表添加一个按钮，在每行上显示，在顶部不显示：

```c#
this.MakeAction("Review_Materials","Generate","生成单子","生成",GridActionParameterTypesEnum.NoId,
				"Review_Materials",600).SetShowInRow(true).SetHideOnToolBar(true),
```

默认会在顶部显示：

```c#
this.MakeAction("Review_Materials", "Test","测试一下","测试",
                GridActionParameterTypesEnum.NoId,"Review_Materials",600),
```

![image-20231028191904552](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111626651.png)

想一个按钮出现在每一行，使用 `SetShowInRow(true)`；

想一个按钮不出现在顶部，使用 `SetHideOnToolBar(true)`。

### 3、分页、排序和汇总

**分页**

在 ListVM 中加上一个构造函数，给 NeedPage 属性赋值，true 表示分页，false 表示不分页。

在前台页面，就是 \<wt:grid> 中直接添加 limit="" 限制每页多少行数据。

**排序**

在 InitGridHeader 中，在每一个 MakeGridHeader 后面都可以使用 `.SetSort()` 方法，这样前台就会在这一列头生成排序的按钮，如果该列数据是中文的话，排序取决于数据库的排序规则。

**汇总**

在前台页面中，\<wt:grid> 上添加 need-show-total="true" 就可以实现前台页面的简单汇总，这是 layui 提供的，只能汇总当前这一页的数据，且数据必须是数字的，相当于在列表下面添加了一行。

要在页面上显示一个新的汇总：

在 ListVM 中添加字段，这样前台的页面才有绑定的数据源，在 PatientListVM 中添加一个小类：

![image-20231111165222627](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111652673.png)

要把这些数据的个数取出来，要自己在 ListVM 中添加个方法：

![image-20231111170739907](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111707969.png)

还要在 ListVM 中添加一个属性，这个属性就是用来给前台绑定的属性：

![image-20231111165347022](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111653068.png)

然后在 PatientController 中，Index 方法里调用上面这个方法，这样就有值了：

![image-20231111165515523](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111655567.png)

然后在前台，添加一个 quote，这是 layui 提供的：

![image-20231111165810143](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111658191.png)

这就是效果：

![image-20231111165920875](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111659921.png)

但实际上，在使用搜索的时候，列表中的数据会被刷新，但是这个汇总却不会刷新，也就是说这个数据是第一次调用时的数据，会一直不变，所以要让页面在列表刷新的时候也刷新，就能实现搜索不一样，数据也不一样。

在前台中，\<wt:searchpanel\> 上添加一句 `old-post="true"`，就像传统表单一样，每次提交都会把页面也刷新，当然，框架会控制它不会刷新整个页面，只会刷新右边的这一块，左边的菜单不会刷新。

但是就这样的话，页面刷新了，数据还是没有改变，因为点击搜索的时候这是一个 post 请求，但是后台只有一个 get 的 Index 方法，没有相对应的 post，所以要新建一个 post 的 Index 方法。因为 post 回来就是当前的 vm，所以也不需要再新建一个 vm：

![image-20231111170551946](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111705997.png)

### 4、背景色

在 InitGridHeader 中，可以使用两个函数

+ `SetBackGroundFunc(Func<Patient_View, string> backGroundFunc)`：设置背景色
+ `SetForeGroundFunc()`：设置前景色

`Func<Patient_View, string> ` 这种标签的意思是，需要一个参数：Patient_View，返回值的类型是：string

比如：治愈返回绿色，其他为白色：

![image-20231111171240240](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111712289.png)

但这种只是改当前单元格的背景色，如果想将一行的背景色都改了，可以重写 SetFullRowBgColor 或者 SetFullRowColor 方法

![image-20231111171441116](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111714165.png)

如果不想要前台页面中数据列表上的每一行开头的勾选框，可以在 \<wt:grid> 上添加 `hidden-checkbox="true"`，添加 `hidden-grid-index="true"` 就可以隐藏每一行前面的数字。

### 5、列表的全局配置

在 appsetting.json 中可以有一些关系列表的全局的配置。

```json
"UIOptions": {
    "DataTable": {
      "RPP": 20, // 默认列表每页显示的条数
      "ShowPrint": true,  // 默认显示打印
      "ShowFilter": true  // 默认显示列筛选
    },
    "ComboBox": {
      "DefaultEnableSearch": true // 默认允许checkbox搜索
    },
    "DateTime": {
      "DefaultReadonly": true  // 默认开启Datetime只读
    },
    "SearchPanel": {
      "DefaultExpand": true   // 默认展开搜索框的内容
    }
  },
```



### 6、自定义输出

`SetFormat(ColumnFormatCallBack<> format)`：里面的参数会返回一个 ColumnFormatInfo 类的对象，是一大串 HTML 代码，可以直接写匿名方法，也可以在里面调用方法。

可以通过这个方法，不绑定真实的数据也可以创建一列：

```c#
this.MakeGridHeader(x => "test").SetFormat((a,b) => "aaaaa"),
```

这里的 x 就是想绑定的那一列。

给图片生成下载和预览的按钮：

```c#
this.MakeGridHeader(x => x.PhotoId).SetFormat(PhotoIdFormat),
```

要实现这个方法：

```c#
private List<ColumnFormatInfo> PhotoIdFormat(Patient_View entity, object val)
{
    return new List<ColumnFormatInfo>
    {
        ColumnFormatInfo.MakeDownloadButton(ButtonTypeEnum.Button, entity.PhotoId);
        ColumnFormatInfo.MakeViewButton(ButtonTypeEnum.Button, entity.PhotoId, 640, 480);
    };
}
```

+ MakeDownloadButton：生成下载按钮
+ MakeViewButton：生成预览按钮

复杂点的操作：想要在 PatientVM 的详情页显示 ReportListVM 的数据列表。

先在 PatientVM 中定义一个 ReportListVM 的属性

```c#
public ReportListVM Reports {get; set; } = new ReportListVM();
```

然后在 InitVM 中使用 `CopyContext()` 方法初始化 ReportListVM,，将当前的 VM 的 DC 等信息传过去，这样这个 ListVM 才知道用哪个 DC 去搜索：

```c#
Reports.CopyContext(this);
```

然后就在 Patient 的详情页面 Details.cshtml 中添加一个 \<wt:grid> 就可以了：

```c#
<wt:grid vm="@Model.Reports" url="/Patients/Report/Search" height="300">
```

使用一些属性隐藏一些不必要的地方：

```c#
<wt:grid vm="@Model.Reports" url="/Patients/Report/Search" height="300" hidden-checkbox="true" hidden-grid-index="true" use-local-data="true">
```

+ use-local-data="true"：使用这个属性就不用在后台配置 NeedPage 了，肯定不会分页，也不用指定 url 了，他不会再走 url 的方法，它的原理是在 Index 的时候就直接搜索，然后将结果显示出来。

再通过判断 SearcherMode 来取消列表上的按钮的显示，SearcherMode 默认是走的 Search：

![image-20231111192852837](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111928920.png)

因为这个列表是从其他 VM 的详情页拿过来的，所以不能直接更改它的按钮，这回影响原来位置的列表显示。

设置好了后，还要将 VM 中的相对属性进行设置，在初始化的时候赋值就可以：

```c#
Reports.CopyContext(this);
Reports.SearcherMode = ListVMSearchModeEnum.MasterDetail;
```

同时，想要通过当前病人的 ID 显示对应的病例追踪，还要将这个 ID 传过去给 Reports：

```c#
Reports.CopyContext(this);
Reports.SearcherMode = ListVMSearchModeEnum.MasterDetail;
Reports.Searcher.PatientID = Entity.ID;
```

### 7、更改每一行的数据

先新增一个每一行都显示的按钮：

```c#
this.MakeAction("Patient","ChangeStatus","更改状态","更改状态",GridActionParameterTypesEnum.SingleId,"Patient",800).SetShowInRow(true).SetIconCls("fa fa-plus"),
```

+ GridActionParameterTypesEnum：这里如果是 单个ID，则会访问 get 方法；多个 ID 则会访问 post 的方法，因为选多行数据的话，get 访问的 url 会有长度限制，post 访问没有。

然后实现 PatientController 中的 ChangeStatus 方法，一个 get 方法选择页面，然后 post 回来：

![image-20231111195151809](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311111951868.png)

它的 url 会自动带着 id 过来，所以在方法上设个参数 id ，就会直接拿到传过来的 id。这个 id 如果不知道是 int 还是 Guid，可以都是用 string。然后在 CreateVM 的时候，也可以传入一个 id，CreateVM 就会根据这个 id 去访问一次数据库，将这个 id 的值，读入到 vm 的 Entity 中。

然后添加一个视图，将这个页面显示出来。

### 8、根据条件显示行内按钮

```c#
this.MakeAction("Patient","ChangeStatus","更改状态","更改状态",
                GridActionParameterTypesEnum.SingleId,"Patient",800)
    .SetShowInRow(true)
    .SetIconCls("fa fa-plus")
    .SetBindVisibleColName("aaa"),
```

+ SetBindVisibleColName() ：设置这个按钮显不显示。将他绑定到另外一列，显示与否取决于那一列的返回值，true则显示，否则不显示。

创建一个名为 aaa 的列，根据病人状态来返回值：

```c#
this.MakeGridHeader(x => "aaa").SetFormat((a,b) => {
    if (a.Status != PatientStatusEnum.SiWang)
        return "true";
    return "false";
}),
```

### 9、弹出确认信息

```c#
this.MakeAction("Patient","ChangeStatus","更改状态","更改状态",
                GridActionParameterTypesEnum.SingleId,"Patient",800)
    .SetShowInRow(true)
    .SetIconCls("fa fa-plus")
    .SetBindVisibleColName("aaa")
    .SetPromptMessage("你真的要更改吗？"),
```

### 10、更改打开方式

将弹窗的打开方式改为打开一个新的 Tab 页，同时设置以下两个函数：

+ SetShowDialog(false)：取消弹窗
+ SetIsRedirect(true)

或者使用 SetMax() 函数，这不是打开一个 Tab 页，而是直接全屏显示原本的弹窗窗口，可以缩小。

在点击删除的时候，默认会弹出一个对话框，点击提交后才会进入 Controller 里的 get 的 Delete 方法。如果取消删除按钮的弹窗，使用 SetPromptMessage 显示一个确认框，然后点击确认就可以删除，就需要改一下 Controller 里的 get 的 Delete 方法，就直接将 post 的方法里的代码复制到 get 方法里就行：

![image-20231111201107950](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311112011025.png)

### 11、点击某一列出现详情

在某一列里，使用 SetFormat 函数：

![image-20231111201246325](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311112012383.png)

以上写法是打开一个新的页面来显示详情，默认的是一个弹窗窗口显示详情，那是 layui 默认的，以下写法是封装了 layui 的：

![image-20231111201447673](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311112014738.png)

框架将 layui 的写法给封装了，在 Program.cs 中，以下语句就是将 layui 服务注入了：

```c#
a.AddLayui()
```

MakeDialogButton()

+ 第一个参数：Link 或 Button，Link 和上一种写法一样，Button 就是在右边的操作列里加一个 Button。
+ 第二个参数：就是点开的地址
+ 第三个参数：文本的名字
+ 第四个参数：宽度
+ 第五个参数：高度，可以不指定，不指定就是根据内容自动变化。
+ 第六个参数：对话框标题

### 12、可编辑的列表

第一步：使用 SetEditType() 来设置当前单元格的编辑类型，

第二步：点了提交后，应该往后台提交，那么要在后台写对应的逻辑，要让它提交的数据和哪个部分对上。在 PatientListVM 的构造方法中加上一句：

```c#
DetailGridPrix = "EntityList";	
```

因为 ListVM 本身就有 EntityList 字段，就是搜索出来的那些东西，如果是主子表添加的话，那上面代码的值就应该是子表的 List 属性的名称了。这里是自己改自己，就使用 EntityLIst。

第三步：点了提交后，需要 post 回去，所以要在 Controller 中加一个 post 的方法：

![img](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121401232.png)

![img](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121401404.png)

ProcessListError：当出现错误的时候，框架会自动帮你找到错误的那一行位置

UpdateEntityList：循环批量更新

最后，要将前台的那个数据列表放入一个 form 中，指定好 url：

![1](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121403353.png)

这个 class 是为了让这个 grid 能充满表单空间。

### 13、树型菜单

左边是一个城市的树型菜单，右边是一个病人的列表。

在 PatientListVM 中新加一个树属性：

```c#
public List<TreeSelectListItem> AllCity {get; set;}
```

这是用来绑定到左边的树型菜单上的。

然后在 InitVM 初始化的时候给这个属性赋值：

```c#
AllCity = DC.Set<City>().GetTreeSelectListItem(LoginUserInfo.DataPrivileges, null, x => x.Name);
```

第一个参数：过滤数据权限

第二个参数：条件，如果你不想取所有数据的话

第三个参数：指定要显示的字段

如果 PatientSearcher 中没有按照地区搜索的条件的话，则需要添加一个属性：

```c#
public Guid? LocationId {get; set;}
```

同时，也要在 PatientListVM 中的 GetSearchQuery 查询语句中添加上对应的语句：

```c#
.CheckWhere(Searcher.LocationId, x => x.LocationId == Searcher.LocationId 
            || x.Location.ParentId == Searcher.LocationId 
            || x.Location.ParentId == Searcher.LocationId)
```

最后需要在前台绑定一下：

在 index.cshtml 中，在搜索框中添加了一个隐藏的字段：

```c#
<wt:hidden field = "Searcher.LocationId"/>
```

并且给整个前台内容套了一个 \<wt:treecontainer>：

```c#
<wt:treecontainer items="AllCity" id-field="Searcher.LocationId" height="500">
    <wt:searchpanel>
        ......
	</wt:searchpanel>
    <wt:quote>
        ......
	</wt:quote>
</wt:treecontainer>
```

这个 treecontainer 就会在左侧显示一个树，右侧它里面的这些东西。

+ id-field：当我点击某一项时，这一项的 id 应该给谁，以上代码就是赋给 Searcher.LocationId ，

### 14、调用前台的 js 方法

比如用一个按钮，点击运行一段前台的 Javascript 代码：

```c#
this.MakeAction("Login","Login","test",GridActionStandardTypeEnum.NoId,null,500).SetOnClickScript("test()"),
```

将这个按钮的 url 设置到 Login/Login 下，表示所有人有权限访问。

然后要在对应的前台页面中实现这个 test() 方法：

```html
<script>
    function test() {
        alert("test");
    }
</script>
```

### 15、同时显示多个列表

效果如图：上面的列表是 PatientListVM2，下面的列表是 ReportListVM2

![image-20231112084112074](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311120841210.png)

首先在上面的列表中添加一个跟踪的按钮：

```c#
this.MakeAction("Patient2", "Reports", "跟踪", GridActionParamentTypeEnum.SingleId, null, 500).SetOnClickScript("Report2").SetShowInRow().SetHideOnToolBar(),
```

或者改变列：

```c#
this.MakeGridHeader(x => "report").SetFormat((a,b) => {
    string rv = UIService.MakeScriptButton(ButtonTypeEnum.Link, "跟踪", $"report'{a.ID}'");
    return rv;
}),
```

还要在 PatientListVM2 中添加一个 ReportListVM2 的属性：

```c#
public ReportListVM2 Reports {get; set;} = new ReportListVM2();
```

在 ReportListVM2 中，将“新建按钮”的 url 指向了一个新的方法 Create2，同时也设置了 Javascript 方法：
```c#
this.MakeAction("Report","Create2","新建","新建",GridActionParameterTypeEnum.NoId,"Patiens").SetOnClickScript("CreateReport"),
```

这个 js 方法就是将上面列表选中的人的 id 取出来，然后拿去调用 Report/Create2 的方法：

![image-20231112091451050](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311120914132.png)

Create2 的页面是这样的：

![image-20231112093916137](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311120939202.png)

然后在 PatientListVM2 的 index.cshtml 页面中，添加一个 \<wt:grid\>，绑定到 ReportListVM2 ：

```c#
<wt:grid vm="@Model" id="grid1" url="/Patients/Patient2/Search2" hidden-grid-index="true" height=300/>
<wt:grid vm="@Model.Reports" id="grid2" url="/Patients/Report/Search2" hidden-grid-index="true" height=300/>
```

下面的列表如果不设置高度的话，上下两个就会平均分。且，设置 id 是为了 js 代码可以拿到对应列表的数据，设置了 id 后，需要将搜索框的 `grid-id` 设置为主列表的 id `grid1`。

然后就是页面上的 js 代码：

![image-20231112092546597](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311120925694.png)

上图中的 report(id) 方法就是对应的 PatientListVM2 中的“跟踪”列调用的方法；

如果框架没有提供一些自动的东西，可以使用 layui 提供的一些方法，比如 `layui.table.cache["grid1"]` 就是列表 grid1 所有的数据。

`layui.table.reload()`：刷新某一个列表，第一个参数是：要刷新的列表的 id；第二个参数是：带着搜索条件去刷新，也就是带着这个搜索条件去调用指定列表的 url 。

report2() 方法是对应 PatientListVM2 中的自定义“跟踪”按钮调用的方法。

CreateReport() 方法就是对应 PatientListVM2 中的“新建”按钮调用的方法。

### 16、改按钮颜色

`.SetButtonClass()`，参数可以写自己定义的样式（该样式需要定义在 wwwroot/sitecss/wtm.css 里）；没有自定义样式，就可以用 layui 自带的。

## 八、CRUDVM

CRUD：Create、Read、Update、Delete，增删改查。

框架的增删改查操作都放在了 BaseCRUDVM 中，使用时，用一个具体 VM 继承自 BaseCRUDVM 就可以了。

### 1、生命周期

继承：

```C#
public class HospitalVM : BaseCRUDVM<Hospital>
{
    
}
```

`BaseCRUDVM<Hospital>` 表示这是关于 Hospital 这个 Model 的增删改查。

可以重写一些方法。

在 Controller 里，都会调用 CreateVM<>() 方法，这个方法中的泛型就是增删改查的 VM 的类型。当我们在创建 VM 的时候，框架首先会 new 一个 ViewModel，然后把 Controller 里面的 DC、LogUerInfo 等信息都传递给这个 VM，在此之后，就会执行 `InitVM()` 方法，只有在这个方法的时候，DC 才会有值。

`ReInitVM()` ：是在 post 回来时如果发生了错误，就会被调用，如果不写的话就会调用 `InitVM()` 。如果重写了 ReInitVM() 方法，框架就不会走 InitVM 方法。	

`SetDuplicatedCheck()`：框架提供的对数据唯一性的验证，在 Validate 里面自动调用

`Validate()`：做一些自定义的验证。

`DoAdd()`、`DoEdit()`、`DoDelete()`、`DoRealDelete()`：DoRealDelete 用于物理删除，因为框架中有一个类实现了假删除。

`GetById(Id)`：返回的是一个 VM，根据 Id 返回。如果不重写的话默认也会调用这个方法。

CreateVM 创建一个 VM 的流程：先 new，然后初始化，然后 InitVM，然后就是调用 DoAdd 等方法；

当 post 回来，参数是 HospitalVM 时的流程：先 new，然后 Validate，然后 InitVM 或者 ReInitVM，然后就是调用 DoAdd 等方法；

### 2、唯一性验证

**验证单一字段不能重复**：要让医院的名字不能重复：

![image-20231112100933236](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121009304.png)

当出现重复时，会提示错误信息，且会把重复的字段标红。

**验证组合字段不能重复**：医院名称和医院级别一起不能重复：

![image-20231112101128960](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121011021.png)

**验证多个字段都不能重复**：医院名称和医院级别都不能重复：

![image-20231112101335849](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121013917.png)

### 3、自定义验证

在 Vaildate 中，`base.Validate()` 是必须要有的，如果没有，它都不会走 SetDuplicatedCheck() 方法。

比如：如果医院所选地区的病人数量小于10，就不能新建医院：

![image-20231112102502758](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121025834.png)

这个的函数没有返回 true 或 false，如果 MSD 中有错误信息，就说明失败了。在 Controller 里面的 post 方法一般首先就是判断 ModelState 的有效性，这个 ModelState 就是 MSD，ModelState 无效就会直接返回页面，不会执行实际操作。

`AsNoTracking()`：不需要 EF 记录追踪。

`AddModelError("Entity.LocationId", "错误")`：第一个参数可以随便打，如果和前台绑定的控件的字段一样的话，就会将那个字段标红，否则就不标红。

### 4、数据初始化

当前台有一些 combobox、transfer、checkbox 这些数据源需要从数据库中读到的，那么就可以在 InitVM 中给这些数据进行初始化。

### 5、selector

用一个按钮，点击后会弹出一个列表，可供选择。

在新建医院的时候，选择地点的原始的下拉框会带出所有的地区，现在改成一个按钮，点击会弹出地区的列表，然后选择。

现在 HosptialVM 中添加一个属性：

```c#
public CityListVM Cities {get; set;}
```

然后在 InitVM 中给它初始化：

```c#
Cities = new CityListVM();
Cities.CopyContext(this);
```

然后在前台，Hospital 的 Create.cshtml 页面中加一个 selector：

![image-20231112103532713](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121035797.png)

他需要指定一个 list-vm，因为他会弹出一个列表；还要绑定最后返回的字段，text-bind 绑定的字段就是选择后返回的数据的字段。

如果后台绑定的是一个数组，框架会自动将 selector 改为多选。

### 6、主子表添加

在新建病人的时候，同时新建病例追踪。

要先在主表的 VM 中添加一个子表的 VM 属性。

再在主表 Patient 中添加一个 List<Report> 属性 Reports。

修改 ReportListVM 的构造函数中的 DetailGridPrix 为 Entity.Reports。

最后在 Patient 的 Create.cshtml 页面下新添一个 grid。 

要在修改的时候也完成主子表的显示，要在 PatientController 的 Edit 方法中指定 vm.Reports.Serarcher.PatientId= id。

### 7、修改部分字段

不想修改某些字段可以在前台页面中删除对应字段，但是这样的话，如果在 Controller 里的 DoEdit 方法中指定的给这个字段赋值的话也不会起作用，因为框架会觉得你没有传过来这个值，就不会去变化这个值。

解决办法1：不删除字段，使用 \<wt:hidden> 将字段隐藏，这样提交的时候依旧会被提交，且可以在 Controller 中手动赋值。

解决办法2：删除字段，在后台使用 FC （form collection）的 Add(p1, p2) 方法指定字段，第一个参数是指定的字段名，第二个参数随便写什么值都行，这个方法的意思就是告诉框架，前台传过来的字段里也有 p1 这个字段，那框架就会对这个字段进行修改，修改的值还是 Entity 里面的值决定的。

![image-20231112110517002](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121105072.png)

注意：要在 Controller 上添加：`[ValidateFormItemOnly]`，告诉 Controller 只验证前台传过来的字段。

### 8、级联删除

默认规则：在一张表中有一个外键指向了另一张表，如果这个外键是必填的，那么这个级联删除的关系在建库的时候就已经建好了，这种情况下假如删除了外键指向的这条数据，那么外键所在的这条数据也会被删除。如果这个外键不是必填的，当删除了外键指向的数据时，外键所在的这条数据不会被删除。

所以级联删除一般就把外键设为必填就可以了。

也可以在 DataContext 中使用流函数来设置级联删除：

![image-20231112111137878](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121111954.png)

手动处理

![image-20231112112103034](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121121112.png)

### 9、使用事务

在添加城市的时候，自动添加一个医院。

![image-20231112112426063](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121124131.png)

以上代码， 在实际中操作 DC 的时候可能会报错，报错了的话，新增的地点也应该不成功，所以这就要使用事务。

使用事务：

![image-20231112112707314](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121127395.png)

## 九、ImportVM

导入时，点击上传会进入对应 Controller 中的 Import 方法，然后上传的文件数据会在 BatchSaveData() 中完成数据库的存储。

ImportVM 实际上依赖于 TemplateVM，这就是个模板。

可以重写两个方法：

+ `SetEntityList()`：打开上传的文件，读取里面的内容，将他转为 EntityList

+ `BatchSaveData()`：会利用转成的实体，去把它写到数据库里。

在导入时，model 上的属性限制（比如[Required()]）都会生效，如果有对应的 CRUDVM，框架也会去调用其中的 Validate 方法来验证数据。

如果没有设置唯一性的话，导入相同数据的话会再插入一条数据；如果有唯一性的话，在导入相同的数据就会更新原来的数据。

### 1、导入树形

想用系统默认生成的导入来导入一个树形结构是很难的，需要我们自己做点改变。

第一步：先把 excel 表的数据取到内存中，让他是个强类型

第二步：再把数据转成数据结构，存到数据库中

首先，在模型 City 中，添加几个字段：

```c#
[NotMapped]
public string Sheng {get; set;}
[NotMapped]
public string Shi {get; set;}
[NotMapped]
public string Qu {get; set;}
```

这三字段都不需要存到数据库中，只是用它们来干点其他事。

然后在 CityImportVM 中修改模板：

![image-20231112132240489](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121322571.png)

然后重写了 BatchSaveData() 方法：

![image-20231112132453834](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121324952.png)

### 2、主子表导入

在主表的 ImportVM 中的模板类 TemplateVM 中添加子表的字段：

![image-20231112133759527](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121337635.png)

因为两张表已经有了主子表的关系，所以不用在做其他事情。

在准备导入数据的时候，第一行写了主表数据和子表数据，后面几行就可以只用写子表数据，不写主表数据，这样就会生成主对子一对多的情况：

![image-20231112134031965](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121340056.png)

以上表示这三行体温和备注数据都是测试1的。

### 3、输出错误信息

ImportVM 有一个 ErrorListVM，它是在 BaseImportVM 中定义的，本身是一个 VM，所以他也有 EntityList。

要输出错误信息，向 ErrorListVM 里加入错误信息就行：

```c#
ErrorListVM.EntityList.Add(new ErrorMessage{Message="", Index=0});
```

## 十、BatchVM

批量操作VM。

BactchVM 需要指定是哪一个 model，还需要指定一个批量更新的类：

![image-20231112134912667](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121349760.png)

批量修改的字段会在 BatchEdit 中出现：

![image-20231112135148032](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121351121.png)

然后前台也要进行修改：

![image-20231112135233961](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311121352049.png)

## 十一、数据库

# 审批工作流（Layui）

> WTMPlus目前没有工作流。（2023/11/21）
>
> WTM从6.4开始支持工作流，使用Elsa开源工作流作为底层。
>
> Elsa工作流是一种自动化工作流程的技术，旨在简化和优化业务流程的执行。以下是关于Elsa工作流的一些详细介绍：
>
> - Elsa工作流是一个用户界面，用于设计、创建和管理工作流程。它提供了可视化的方式来定义工作流程，使得定义工作流程变得更加直观和易于理解。
> - 通过Elsa工作流，您可以规定工作流程的执行顺序、条件和动作，以实现特定的业务逻辑。这意味着您可以根据实际需求来设定工作流的各个环节，以满足您的业务需求。
> - 工作流程定义（Workflow Definitions）是指在Elsa Workflow面板中创建的工作流程的定义。这包括工作流程的结构、步骤和逻辑等信息，为实际的工作流程提供基础。
> - 工作流实例（Workflow Instances）则是根据工作流定义创建的具体工作流程实例。每个实例都代表一个独立的执行过程，包含工作流程的当前状态、已完成的步骤、待处理的任务等信息。
> - Elsa工作流还包含一个工作流注册表（Workflow Registry），用于存储和管理工作流程的定义。它作为工作流定义的中央存储库，方便您查看和管理已注册的工作流程定义。
>
> 在实际运行中，工作流引擎会从工作流注册表中获取相应的工作流定义，并创建对应的工作流实例。这使得工作流程的执行更加自动化和高效。同时，持久化存储机制确保了工作流状态的保存，使得在失败或暂停后能够恢复工作流的执行。

在创建项目时，选择 .netcore 版本为 6.0 以上的就会自带工作流了。

下载代码后可以直接运行，就能看到有一个流程管理，里面有两个页面，一个流程定义，一个流程实例，这其实就是 Elsa 的页面了。

+ 流程实例：定义流程后，每个启动的流程

## 注册审批

> 用户提交注册，管理员审批是否通过注册。

在“流程定义”点击“创建工作流程”，在右上角的齿轮中可以配置一些基本的信息。

`workflow context`：指定后台的哪个表单、哪个模型的类在使用这个工作流。这个名称的规则是：带命名空间的模型全称+逗号+所在项目的名称：

![image-20231121201356944](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212013048.png)

![image-20231121201431613](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212014692.png)

然后可以点击 start，里面会有很多的 activity 节点，先选择“工作流”类然后点一个“审批”，然后再“审批人”里添加 admin，点击保存，他就会出现以下界面：

![image-20231121201757788](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212017873.png)

这个审批节点会出现同意和拒绝的两个分支，如果我们同意的话需要把表单里面的值改为 true，这时候就可以使用脚本，点击同意分支下的加号，选择脚本，点击运行 JavaScript，在这里面可以直接使用刚刚设置的 WorkflowContext ，可以直接点出来这个 frameworkUser 的各种属性，在这里只需要将 isValid 值改为 true 即可，然后点击保存。

![image-20231121202907710](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212029797.png)

现在的工作流就是这样：

![image-20231121202945320](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212029392.png)

最后加上一个工作流里的“结束”的节点，什么都用就是单纯的结束。最后将上面的拒绝的分支也连到结束节点上：按住 shift，点击拒绝的加号，再点击结束的节点即可：

![image-20231121203235141](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212032211.png)

然后点击右下角的 publish 就发布了，就可以在流程定义里看到这一条流程。

## 代码触发流程

这个审批流程应该是在用户点击注册的时候被触发，在 Controllers 下的 LoginController 中，有个 Reg 方法，当用户点击注册的时候，会执行 doReg 方法，在这个 doReg 方法中，isVaild 属性模型是 true，将它改为 false，然后在方法的返回语句前添加触发流程的代码：

```c#
/**
FrameworkUser user = new FrameworkUser
{
    ITCode = ITCode,
    Name = Name,
    Password = Utils.GetMD5String(Password),
    IsValid = false,
    CellPhone = CellPhone,
    Email = Email
};

DC.Set<FrameworkUser>().Add(user);
DC.SaveChanges();
*/

var vm = Wtm.CreateVM<FrameworkUserVM>(user.ID);
var r = vm.StartWorkflowAsync().Result;
```

使用刚刚新建的用户ID创建一个 FrameworkUserVM，这个 vm 中会有一个 StartWorkflowAsync 方法，用来启动工作流的，他有一个参数，可以指定工作流的名称（如果一个表单只有一个流程，不填也可以）。

还要让指定的类支持工作流，需要继承 IWorkFlow 接口 ：

```c#
public class FrameworkUser : FrameworkUserBase, IWorkflow
```

这个接口不需要实现任何方法，只是告诉框架这个表单是需要流程的。这是启动项目，注册一个用户，就可以在流程实例中看到一条数据：

![image-20231121210836666](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212108778.png)

可以点击ID处，进入流程查看状态。画绿的地方就是现在流程停到哪个地方了，可以点击右边的箭头展开详情，这个 Journal 就是每一步流程：

![image-20231121211358764](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311212113865.png)

现在是正在等待审批的状态，所以还需要加一个审批的操作：在用户列表上添加一个审批按钮。

```c#
this.MakeStandardAction("FrameworkUser",GridActionStandardTypesEnum.Approve,"","_Admin",dialogWidth:800).SetBindVisiableColName("CanApprove"),
```

`Approve`：是固定的审批按钮，会去调用Controller里的叫 approve 的方法，

`SetBindVisiableColName`：控制每一行的按钮到底显不显示，它绑定一个叫 CanApprove 的列。

现在这个列中加一个布尔值，也叫 CanApprove：

```c#
public class FrameworkUser_View : FrameworkUser
{
    [Display(Name = "_Admin.Role")]
    public string RoleName_view { get; set; }

    [Display(Name = "_Admin.Group")]
    public string GroupName_view { get; set; }

    public bool CanApprove { get; set; }
}
```

然后可以重载一个函数 `AfterDoSearch` ，这个函数是在查询完了后，EntityList 里有值了后，执行的操作，这里是决定哪些数据可以被审批：

```c#
public override void AfterDoSearcher()
{
    var ids = DC.Set<FrameworkWorkflow>().Where(x => x.WorkflowName == "注册审批" && x.UserCode == Wtm.LoginUserInfo.ITCode).Select(x => x.ModelID).ToList();
    foreach (var item in EntityList)
    {
        if (ids.Contains(item.GetID().ToString()))
            item.CanApprove = true;
    }
}
```

去 `FrameworkWorkflow` 这个表中取到 “注册审批” 流程的审批人是当前登录人的所有可以审批的模型 ID ，然后找这些 查出来的 ID 有没有在 EntityList 中，在的话就将他们的状态改为 true。`FrameworkWorkflow` 这个表是框架自己加的，里面存的每一个流程的当前的步骤。

还要在输出列的地方加一个列，因为审批按钮绑定了一个列：

```c#
this.MakeGridHeader(x => "CanApprove").SetHide().SetFormat((a,b) =>
                                                           {
                                                               if (a.CanApprove)   return "true";
                                                               return "false";
                                                           }),
```

最后在 FrameworkUserController 中添加一个 Approve 方法以及页面，

```c#
[ActionDescription("Sys.Approve")]
public ActionResult Approve(string id)
{
    var vm = Wtm.CreateVM<FrameworkUserVM>(id);
    vm.Entity.Password = null;
    return PartialView(vm);
}

[ActionDescription("Sys.Approve")]
[HttpPost]
[ValidateFormItemOnly]
public async Task<ActionResult> Approve(FrameworkUserVM vm)
{
    if (ModelState.Any(x => x.Key != "Entity.Password" && x.Value.ValidationState == Microsoft.AspNetCore.Mvc.ModelBinding.ModelValidationState.Invalid))
    {
        return PartialView(vm);
    }
    else
    {
        ModelState.Clear();
        await vm.DoEditAsync();
        await vm.ContinueWorkflowAsync(vm.ActionName, vm.Remark);
        if (!ModelState.IsValid)
        {
            vm.DoReInit();
            return PartialView(vm);
        }
        else
        {
            return FFResult().CloseDialog().RefreshGridRow(vm.Entity.ID);
        }
    }
}
```

两个 Approve 方法，一个是 get 的返回页面，一个是点完了之后提交的。post 的 Approve 方法和自带的 Edit 方法差不多，因为这也是一种修改操作，只不过是不是修改的表单。

`ContinueWorkflowAsync(vm.ActionName, vm.Remark)`：第一个参数代表你点的是同意还是拒绝，第二个参数是你加的备注。

然后将 Edit.cshtml 文件复制一份，改名为 Approve ，其他部分都可以和 Edit 页面一样，只不过需要将提交和关闭按钮改成同意和拒绝：

```c#
<wt:form vm="@Model" url="/_Admin/FrameworkUser/Approve" >
    

<wt:hidden field="ActionName"/> 
    
<wt:row>
	<wt:textarea field="Remark"></wt:textarea>
</wt:row>
    
<wt:row align="AlignEnum.Right">
    <wt:submitbutton text="同意" click="$('#FrameworkUserVM_ActionName').val('同意')"/>
    <wt:submitbutton text="拒绝" click="$('#FrameworkUserVM_ActionName').val('拒绝')" />
    <wt:closebutton />
  </wt:row>
```

还在表单中加了一个隐藏的字段 ActionName，这个字段是在 BaseVM 里的一个字段，方便处理工作流的。

这样过后，就可以在用户管理中看到 需要审批的用户，点击同意后，该用户账号就可以使用：

![image-20231122143034697](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221430784.png)

然后再看流程实例，现在已经是 Filished 状态了：

![image-20231122143128877](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221431934.png)

## 详情页里看审批进度

```c#
<wt:tab>
      <wt:wt:tabheaders>
            <wt:tabheader title="用户信息" />
            <wt:tabheader title="审批记录" />
      </wt:wt:tabheaders>
      <wt:wt:tabcontents>
          <wt:tabcontent>
                <wt:row items-per-row=" ItemsPerRowEnum.Two">
                    <wt:image field="Entity.PhotoId" width="128" />
                    <wt:display field="Entity.ITCode" />
                    <wt:display field="Entity.Name" />
                    <wt:display field="Entity.Gender" />
                    <wt:display field="Entity.Email" />
                    <wt:display field="Entity.CellPhone" />
                    <wt:display field="Entity.HomePhone" />
                    <wt:display field="Entity.Address" />
                    <wt:display field="Entity.ZipCode" />
                </wt:row>
          </wt:tabcontent>
          <wt:wt:tabcontent>
              <wt:wt:flowinfo vm="@Model" />
          </wt:wt:tabcontent>
      </wt:wt:tabcontents>
  </wt:tab>
```

显示审批记录的时候，框架提供了一个控件，只需要绑定当前这个模型就可以，它可以显示当前这个模型的历史审批和当前状态：

![image-20231122144451664](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221444728.png)

如果是前后端分离的项目，可以直接使用这些关于工作流的操作，只是没有流程控制这个页面，但是也可以通过地址访问：_workflow/inner。

# 审批工作流（VUE3）

> 模拟大学生报道流程。
>
> WTMPlus 生成的项目里面已经有了工作流（2023.11.22）

用 WTMPlus 维护一个 Student 模型，创建一些字段，然后直接下载 VUE3 的代码。

整个项目是后台，前台的代码放在了主项目的 ClientApp 下面，这个目录可以单独打开，也可以单独运行起来：

![image-20231122150328543](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221503606.png)

启动项目后，不会把前后台同时启动，因为实践当中，前后台分开启动比较好：

![image-20231122150536016](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221505082.png)

可以使用命令行的方式启动前台页面，在 ClientApp 目录下使用命令行：

```bash
npm install
npm run dev
```

第一次启动需要先使用 `npm install` 安装一下依赖的 JavaScript 包，之后就不用安装了；安装好了之后，就使用 `npm run dev` 可以启动前台了。启动成功的页面：

![image-20231122151233795](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221512852.png)

可以按住 ctrl 单击这些链接即可访问前台页面。

如果默认没有生成流程管理的页面，需要在 Startup.cs 文件中添加：

```c#
services.AddWtmWorkflow(ConfigRoot);
```

然后那个流程的可视化界面依赖于一个 Elsa 的 nugut 包，需要将这个包装一下：

![image-20231122151720748](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221517808.png)

最后在前台加一个流程管理的页面，实际上只需要一个 frame 去指向框架已经打包在 dll 中的一个页面：

![image-20231122151912189](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221519287.png)

## 入学报道流程

接下来新建一个入学流程：

![image-20231122152426365](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221524432.png)

将一个流程分叉，使用控制流里的分叉：

![image-20231122152739745](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221527813.png)

然后在每个分叉下都加一个审批，由 user1 审批基础信息，user2 审批背景调查，可以修改审批流程的标签，这个标签的主要目的是，当你的两个审批的表单是有细微差别的，需要填的不一样，那就可以指定不一样的标签，前台就会获取到这个信息来判断审批到底是啥样的。

在基础信息审批通过后，使用控制流的合并，因为这两个分支会合成一个，模式选择等候全部，因为需要都通过了才能走下一步：

![image-20231122191522140](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221915213.png)

然后将背景调查审批的同意节点连接到这个合并节点上来（按住shift点击）。现在的流程是这样的：

![image-20231122191805764](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221918828.png)

## 添加条件

在两个审核都通过后，可以加一个控制流中的 if 条件，condition 可以选成 JavaScript，用来判断学生的性别男女：

![image-20231122192050408](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221920475.png)

这样的话会创建三个分支出来，一个是 true、一个是 false、一个是没有指明的情况，如图：

![image-20231122192214948](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221922002.png)

那对于这里的需求来说，只需要两个分支就够了，因为只需要判断是男是女。

可以使用 switch，switch 可以判断多种分支：

![image-20231122192424521](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221924593.png)

![image-20231122192512540](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221925593.png)

然后在男的分支上建一个审批，且标签填一个分配宿舍，因为需要填写一个宿舍：

![image-20231122192704046](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221927112.png)

女生的分支也是一样，只不过审批人是 user4，这样给男女生分宿舍的界面是一样的，但是审批的人不一样。

等宿舍也审批通过了后，就认为审批结束了，就在分支上加一个运行 JavaScript 脚本，并且将男女两分支都连过来：

```javascript
workflowContext.IsValid = true
```

最后添加一个结束的节点。

## 添加收费

当用微信付款时，其实是向微信发起一个收款的信息，然后付完款后微信会回调你的系统的一个 API，告诉你这笔钱已经付了。所以我们可以在调用 API 的时候触发工作流上的一个信号，让工作流走。这和审批流没有关系。

修改第一个分支，添加一个分支：收费。在这个分支上连一个工作流里的接受信号，起个名字：

![image-20231122193732366](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221937431.png)

最后将这个分支也合并到合并的节点上：

![image-20231122193843890](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311221938957.png)

意思是，当基础信息、背景调查这个两个都审批过了，且交了费，才能继续向下走，根据男女分配宿舍。最后点击 publish。

## 实现代码

首先要给 Student 这个模型实现 IWorkflow 接口，给 isValid 字段设个默认值 false，当流程走完后这个字段就会是 true。

在 \_StudentController 里面，在 Create 方法中，添加一句：

```c#
[ActionDescription("Sys.Create")]
[HttpPost("[action]")]
public async Task<IActionResult> Create(StudentVM vm)
{
    if (!ModelState.IsValid)
    {
        return BadRequest(ModelState.GetErrorJson());
    }
    else
    {
        await vm.DoAddAsync();
        await vm.StartWorkflowAsync();  // 启动流程
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState.GetErrorJson());
        }
        else
        {
            return Ok(vm.Entity);
        }
    }

}
```

意思是，当我们在后台添加一个学生的时候，就启动这个流程。

这时运行项目，添加一个学生，然后就可以在流程管理里面看到流程实例。下一步就是需要审批了。

现在学生列表 StudentListVM 里面重写一个 AfterDoSearcher 方法，用来找搜索条件返回的数据中有没有我能审批的数据，如果有就给 ApproveName 赋上值，ApproveName 是在 StudentListVM 中的 Student_View 类中新建的一个字段，这样前台可以根据这个字段来判断需不需要显示审批按钮。

```c#
public override void AfterDoSearcher()
{
    var approveInfo = DC.Set<FrameworkWorkflow>().Where(x => x.ModelType == typeof(Student).FullName && x.UserCode == Wtm.LoginUserInfo.ITCode)
        .Select(x => new { id = x.ModelID, tag = x.Tag }).ToList();
    foreach (var item in EntityList)
    {
        var approve = approveInfo.Find(x => x.id == item.GetID().ToString());
        if (approve != null)
        {
            item.ApproveName = approve.tag ?? "审批";
        }
    }
}
```

approve.tag 为空值，就是没有设置标签的审批，直接显示 “审批” 即可；否则就是分配宿舍审批，显示“分配宿舍”。

然后看前台，前台页面在 ClientApp 下的 src 中的 views 下的 data 下的 student 中的 index.vue。

在 WtmTable 中添加了一个按钮：

```c#
<WtmButton v-if="scope.row.ApproveName" :is-text="true" type='warning' :button-text="scope.row.ApproveName" @click="OnApproveClick(scope.row)"/>
```

`scope.row` 表示当前一行的数据，`scope.row.ApproveName` 就是刚才后台 AfterDoSearcher 返回的字段，v-if 就是说，如果这个字段有值，就显示这个按钮，按钮的文字就是这个 ApproveName。当点击这个按钮的时候，执行 `OnApproveClick(scope.row)` 这个方法。`OnApproveClick` 这个方法就是在下面写的一个方法：

```vue
const OnApproveClick = (row:any) => {
// 打开一个对话框去显示审批表单
	other.openDialog(row.ApproveName, ApproveDialog, row, getTableDataStudent)
}
```

这个 `ApproveDialog` 是上面定义的一个常量：

```vue
const ApproveDialog = defineAsyncComponent(() => import('./approve.vue'));
```

这个审批表单也是从 Edit 页面改过来的。需要注意这块：

```vue
<el-row v-if="ci.attrs['wtmdata'].ApproveName=='分配宿舍'">
    <el-col :xs="24" :lg="12" class="mb20">
        <el-form-item ref="Entity_Dormitory_FormItem" prop="Entity.Dormitory" :label="$t('message.autotrans._Model_Student_Dormitory')">
            <el-input v-model="stateStudent.vmModel.Entity.Dormitory" clearable></el-input>
        </el-form-item>
    </el-col>
</el-row>
```

`ci.attrs['wtmdata']` ：指弹出表单的时候，传给这个表单的列表的行数据。以上代码的意思是，如果是 分配宿舍 的流程，就显示这些，否则不显示。这就是根据流程的 TagName 来控制前台页面的不同变化。

同意按钮的事件：

```vue
const onAgree = () => {
	const loadingInstance = ElLoading.service({
		lock: true,
		text: '正在审批中',
		background: 'rgba(0, 0, 0, 0.7)',
	});
	stateStudent.vmModel.ActionName = '同意';
	studentApi()
		.approve(stateStudent.vmModel,ci.attrs['wtmdata'].ApproveName)
		.then(() => {
			ElMessage.success('审批成功');
			emit('refresh');
			closeDialog();
		})
		.catch((error) => {
			other.setFormError(ci, error);
		})
		.finally(() => {
			loadingInstance.close();
		});
};
```

会调用 \_StudentController 中的 Approve 方法：

```c#
[ActionDescription("审批")]
[AllRights]
[HttpPost("[action]")]
public async Task<IActionResult> Approve(StudentVM vm, [FromQuery] string tag)
{
    if (!ModelState.IsValid)
    {
        return BadRequest(ModelState.GetErrorJson());
    }
    else
    {
        await vm.ContinueWorkflowAsync(vm.ActionName,vm.Remark,tag:tag=="审批"?null:tag);
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState.GetErrorJson());
        }
        else
        {
            if (vm.ActionName == "同意")
            {
                await vm.DoEditAsync(false);
            }
            return Ok(vm.Entity);
        }
    }
}
```

拒绝按钮的事件：

```vue
const onRefuse = () => {
	const loadingInstance = ElLoading.service({
		lock: true,
		text: '正在审批中',
		background: 'rgba(0, 0, 0, 0.7)',
	});
	stateStudent.vmModel.ActionName = '拒绝';
	studentApi()
		.approve(stateStudent.vmModel,ci.attrs['wtmdata'].ApproveName)
		.then(() => {
			ElMessage.success('审批成功');
			emit('refresh');
			closeDialog();
		})
		.catch((error) => {
			other.setFormError(ci, error);
		})
		.finally(() => {
			loadingInstance.close();
		});
};
```

也会调用 studentApi 这个接口，这个接口定义在 ClientApp/src/data/student 下的 index.ts 中：

```ts
approve: (data: object, tag: string) => {
    return request({
        url: '/api/Data/Student/approve?tag=' + tag,
        method: 'post',
        data
    });
},
```

还需要在 StudentListVM 中添加行：

```c#
this.MakeGridHeader(x => x.ApproveName),
```

然后运行项目，要添加几个用户，就是审批流程中指定的那几个：user1、user2、user3、user4、user5，然后使用 admin 添加一个学生，登录 user1 的账户就可以看到这个学生的信息上会有一个审批按钮。

## 收费代码

正常情况是，微信付完款后，微信会调用你自己系统的一个接口，然后这个接口就会处理一些自己的业务。

在 \_StudentController 里模拟了这样一个接口：

```c#
[Public]
[HttpPost("[action]")]
public async Task<IActionResult> WxPay([FromServices] ISignaler _singler,string studentid)
{
    //进行验证，更新订单
    var wid = DC.Set<Elsa_WorkflowInstance>().Where(x => x.ContextType == typeof(Student).FullName && x.ContextId == studentid && x.WorkflowStatus == 3).Select(x => x.ID).FirstOrDefault();
    await _singler.TriggerSignalAsync("WechatPay", workflowInstanceId:wid);
    return Ok();
}
```

然后通过 Swagger 文档，传一个 StudentID 调用这个接口，再看流程管理，发现流程已经走到了分配宿舍的位置，现在登录 user3 查看，会看到在学生数据的行内会有一个叫 分配宿舍 的按钮。当点击这个按钮的时候，就会看到表单内有一个宿舍文本框：

![image-20231123085741691](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311230857846.png)

当点击同意之后，这个流程就走完了，这个学生的 isValid 属性就会被赋值为 true。

## 详情中显示审批流程

VUE 不想 Layui 默认带了一个控件，但是可以自己添加，在 components 里添加了一个 workflowTimeLine 目录，在下面新建一个 index.vue ：

```vue
<template>

                        <el-timeline>
                            <el-timeline-item v-for="(activity, index) in localdata.approveRecords"
                                              :key="index" placement="top"
                                              :color="getColor(activity)"
                                              :timestamp="activity.Time">
                                {{ activity.Message }}
                                <p v-if="activity.Remark">审批意见：{{activity.Remark}}</p>
                            </el-timeline-item>
                        </el-timeline>
</template>


<script setup lang="ts">
import { watch, reactive, ref, getCurrentInstance, onMounted, nextTick } from 'vue';
import other from '/@/utils/other';
import workflowApi from '/@/api/workflow';
const ci = getCurrentInstance() as any;

    const props = defineProps({
        flowname: String,
        entitytype: String,
        entityid: null,
    });
// 定义变量内容
const localdata = reactive({
    approveRecords: [] as any[]
});
  

    watch(()=>props.entityid, () => {
        if (props.entityid) {
            workflowApi().getTimeLine(props.flowname ?? "", props.entitytype ?? "", props.entityid ?? "")
                .then((data: any) => {
                    localdata.approveRecords = data;
                })
        }
    })

    const getColor = (data : any)=>{
        if (data.Action == '同意') {
            return "#0bbd87";
        }
        if (data.Action == '拒绝') {
            return "#ff0000";
        }
        return "";
    }
// 暴露变量
defineExpose({

});
</script>

<style scoped lang="scss">

</style>
```

还要在 ClientApp 下的 Api 下新建一个 workflow 目录，在里面新建一个 index.ts：

```ts
import request from '/@/utils/request';

/**
 * （不建议写成 request.post(xxx)，因为这样 post 时，无法 params 与 data 同时传参）
 *
 * 登录api接口集合
 * @method signIn 用户登录
 * @method signOut 用户退出登录
 */
export default function WorkflowApi() {
	return {		
		getTimeLine: (flowname: string, entitytype: string, entityid:string) => {
			return request({
				url: '/_workflowapi/gettimeline',
				method: 'get',
				params: { flowname, entitytype, entityid }
			});
		}
	};
}
```

还需要在 components 目录下的 index.ts 中引用：

```ts
import WtmWorkflowTimeLine from '/@/components/workflowTimeLine/index.vue'

app.component('WtmWorkflowTimeLine', WtmWorkflowTimeLine);
```

然后在详情页面里，加了一个 tab 页，用来显示流程步骤：

```cs
<el-tabs type="border-card">
    <el-tab-pane label="基础信息"></el-tab-pane>

    <el-tab-pane label="审批记录">
    <WtmWorkflowTimeLine entitytype="WorkFlow2.Model.Data.Student" :entityid="stateStudent.vmModel.Entity.ID" />
    </el-tab-pane>
</el-tabs>
```

![image-20231123092018207](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311230920312.png)

# 自定义工作流节点

