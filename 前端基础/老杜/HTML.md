# HTML

[TOC]

## 1. 系统结构

**B/S架构**：Browser / Server （浏览器 / 服务器的交互形式）（主要）

- 优点：升级方便，只升级服务器端代码，维护成本低

- 缺点：速度慢、体验不好、界面不炫酷

**C/S架构**：Client / Sever （客户端 / 服务器端的交互形式）

- 优点：速度快、体验好、界面炫酷（娱乐型的系统多数是c/s结构的）

- 缺点：升级麻烦、维护成本较高

## 2. HTML 概述

HTML：Hyper Text Markup Language（超文本标记语言）

+ 由大量的标签组成，每一个标签都有开始标签和结束标签。。

- HTML开发的时候使用普通的文本编辑器就行，创建的文件扩展名是`.html`或者`.htm`。
- 直接用浏览器打开HTML文件就是运行。

HTML是W3C（世界万维网联盟）制定的。W3C制定了HTML的规范，每个浏览器生产厂家都会遵守规范。

HTML规范目前最高的版本是：HTML5.0，简称H5。

以下这句代码加上就是HTML5的语法，不加就是HTML4。

```html
<!doctype html> 
```

## 3. 基本标签

- 段落标签：`<p></p>`
- 标题字：`<hi></hi>（1 <= i <= 6）`
- 换行：`<br>`
- 水平线：`<hr>`
- 预留格式：`<pre></pre>`
- 粗体字：`<b></b>`
- 斜体字：`<i></i>`
- 插入字：`<ins></ins>`
- 删除字：`<del></del>`
- 右上角加字：`<sup></sup>`：10的平方表示：`10<sup>2</sup>`
- 右下角加字：`<sub><sub>`
- font标签：`<font></font>`
- 注释：`<!--  -->`

## 4. 实体符号

特点：以`&` 开头，以 `;` 结尾。

- 空格：`&nbsp;`

- 大于号：`&lt;`

- 小于号：`&gt;`

## 5.  背景颜色与图片

- `<meta charset="utf-8">`：这行代码的作用是告诉浏览器采用哪一种字符集打开当前页面，注意：并不是设置当前页面的字符编码方式。
- `bgcolor `设置背景色
- `background `设置背景图片
  ![img](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309081847144.jpeg)

## 6. 表格

表格的标签：

+ `table `表示一个表格，
+ `tr` 表示一行，
+ `td` 表示一格
+ `th` 也表示一格，比 `td` 多的是居中、加粗
+ `thead` 表格的头部
+ `tbody` 表格的身体
+ `tfood` 表格的脚部

常用属性

- `border=1px` ：设置表格的边框为1像素宽度

- `width=60%`：用比例设置宽，可以随着窗口的变化而变化

- `height=150px` ：设置表格的高度

- `width=300px` ：设置表格的宽

- `align=center`：对齐方式：居中对齐
  居中也可以使用居中标签：`<center>这样也可以居中对齐</center>`

### **单元格合并**

**行合并**：`rowspan = “ 需要合并的行数”` ，注意：需要删除下面的那个单元格。

比如：有这么一个表格：![image-20230908185322398](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309081853411.png)

```html
<table border="1px" width="20%">
    <tr align="center">
        <td>1</td>
        <td>2</td>
        <td>3</td>
    </tr>
    <tr align="center">
        <td>4</td>
        <td>5</td>
        <td>6</td>
    </tr>
    <tr align="center">
        <td>7</td>
        <td>8</td>
        <td>9</td>
    </tr>
</table>
```

想要合并第 2 行的 6 和第 3 行的 9，就需要在第 2 行的 6 上写 `rowspan = 2` ，且删除掉第 3 行的 9：

```html
<table border="1px" width="20%">
    <tr align="center">
        <td>1</td>
        <td>2</td>
        <td>3</td>
    </tr>
    <tr align="center">
        <td>4</td>
        <td>5</td>
        <td rowspan="2">6</td>
    </tr>
    <tr align="center">
        <td>7</td>
        <td>8</td>
        <!-- <td>9</td> -->
    </tr>
</table>
```

结果：![image-20230908185702643](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309081857667.png)

**列合并**：`colspan = “ 需要合并的列数 ”`，删除需要合并的那一列即可。

就以上面合并行后的表格为例，想要将第 3 行的 7 和 8 两列进行合并，就需要在第 7 的格子上写：`colspan = "2"`，然后第 8 格删除；也可以在第 8 格上写 `colspan = "2"`，再将第 7 格删掉：

```html
<table border="1px" width="20%">
    <tr align="center">
        <td>1</td>
        <td>2</td>
        <td>3</td>
    </tr>
    <tr align="center">
        <td>4</td>
        <td>5</td>
        <td rowspan="2">6</td>
    </tr>
    <tr align="center">
        <!-- <td>7</td> -->
        <td  colspan="2">8</td>
        <!-- <td>9</td> -->
    </tr>
</table>
```

结果是：![image-20230908190318570](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309081903597.png)

## 7. 表单

表单的作用：收集用户信息，表单展现之后，用户填写，点击提交数据给服务器。

### 标签

表单的标签：`form` 标签：`<form action="服务器地址"></form>` 。一个网页中可以有多个表单`form`。

```html
<form action="">
    <!-- ... -->
</form>
```

- `action`属性用来指定数据提交给哪个服务器
- `action`属性和超链接的`href`属性一样，都可以向服务器发送请求（request）

### 提交数据

表单最终是需要提交数据给服务器的，提交方法：在表单内部画一个类型为 `submit` 的按钮

```html
<form action="https://www.baidu.com/" >
    <input type="submit" value="百度"/>
   <!--  对于按钮来说，按钮的value属性用来指定按钮上的显示的文本信息  --> 
</form>
```

表单提交按钮与普通按钮的区别就是 `type` 属性不一样，这是普通的按钮：

```html
<input type="button" name="" id="" value="设置按钮上显示的文本" />
```

表单和超链接的区别：超链接和表单都可以向服务器发送请求，只不过**表单发送请求的同时可以携带数据**。

表单给服务器提交数据的格式：

```
action?name=value&name=value&name=value....
```

这是http协议规定的，必须以这种格式提交给服务器，比如：`http://localhost:88/?username=12&usrpwd=12`。

表单会提交哪些数据？

只要表单里的项写了`name`属性的，一律会提交值给服务器，如果不想提交这一项，就不要写`name`属性

注意：

- 文本框和密码框的`value`不需要程序员指定，用户输入什么`value`就是什么

- 当`value`没有写的时候，`value`的默认值是空字符串`""`,会将空字符串提交给服务器，Java代码得到的是`String username = ""`;

- 当`name`没有写的时候，该项不会提交给服务器

<form action="http://localhost:88/">
    <table>
        <tr>
            <th align="center">用户名</th>
            <td><input type="text" name="username"/></td>
        </tr>
        <tr>
            <th align="center">密码</th>
            <td><input type="password" name="usrpwd"/></td>
        </tr>
        <tr align="center">
            <td colspan="2" >
                <input type="submit" value="登录"/>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="reset" value="清空"/>
            </td>
        </tr>
    </table>
</form>

以上就是一个表单，里面有一个表格，代码如下：

```html
<form action="http://localhost:88/">
    <table>
        <tr>
            <th align="center">用户名</th>
            <td><input type="text" name="username"/></td>
        </tr>
        <tr>
            <th align="center">密码</th>
            <td><input type="password" name="usrpwd"/></td>
        </tr>
        <tr align="center">
            <td colspan="2" >
                <input type="submit" value="登录"/>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="reset" value="清空"/>
            </td>
        </tr>
    </table>
</form>
```

当点击登录后，这个表单会向 `http://localhost:88/` 这个服务器发送数据，数据包含 `username` 文本框的值和 `usrpwd` 密码框的值。

注意：

+ `submit` 必须放在 `<form></form>` 的内部
+ `reset` 是清空表单内部所有文本框和密码框的值，也必须放在 `<form></form>` 的内部

### 常用控件

#### `input`

定义输入字段，用户可在其中输入数据。

注意：`input `元素是空的，仅包含属性。

+ `maxlength`：设置文本框中可输入的字符数量：

  ```html
  <input type="text" maxlength="3" />
  ```

  只能输入三个字符。

#### `file`

该控件为文件上传专用：

```html
<input type="file" />
```

#### `hidden`

隐藏域，网页上看不到，但是提交表单的时候数据会自动提交给服务器 ：

```html
<input type="hidden" />
```

### 常用属性

#### 只读

有两个属性都是限制**只读**不能修改，区别在于

+ `readonly` ：可以把数据提交给服务器
+ `disabled` ：不会把数据提交给服务器（即使有 `name` 属性也不行）

#### 提交

表单的`method`属性是决定表单采用什么方式提交数据的。

+ `get`：采用`get`方式提交的时候，用户提交的信息会显示在浏览器的地址栏上（默认）
+ `post`：采用`post`方式提交的时候，用户提交的信息不会显示在浏览器地址栏上

当用户提交的信息中含有敏感信息，例如密码，建议使用`post`方式提交

### 下拉列表

标签为 `select`，创建下拉列表：

```html
<select></select>
```

+ `multiple`属性：当该属性为 `true `时，规定可一次选定多个项目。
+ `size`属性：设置显示条目的数量

使用 `option` 创建下拉列表中的每一个选项：

```html
<option></option>
```

+ `selected` 默认选中。

比如：

<select size=2>
    <option>小学</option>
    <option>初中</option>
    <option>高中</option>
    <option selected>大学</option>
</select>

### 文本域

文本域没有`value`属性，用户填写的内容就是`value`，标签为 `textarea` ，

```html
<textarea rows="10" cols="0" name="introduce"></textarea>
```

+ `rows `是行数
+ `cols `是列数

### 单选按钮

使用 `input` 标签，设定 `type` 为 `radio`：

```html
<input type="radio" />
```

单选按钮的`value`必须手动指定， `checked`表示默认选择：

```html
<input type="radio" value="1" checked/> 男
<input type="radio" value="0"/> 女
```

比如：

<form>
    <input type="radio" value="1" checked/> 男
    <input type="radio" value="0"/> 女    
</form>

## 8. id 属性

在HTML文档中，任何元素（节点）都有`id`属性，`id`属性是该节点的**唯一标识**，所以在同一个HTML文档中`id`值**不能重复**。

注意：表单提交的时候，只和`name`有关系，和`id`无关。

### 作用

JavaScript 语言可以通过对HTML文档当中的任意节点进行增删改操作，那么增删改之前需要先拿到这个节点，通常我们通过`id`来拿节点对象，`id `的存在让我们获取元素（节点）更方便。

HtMl文档是一棵树，树上有很多节点，每一个节点都有唯一的`id`，JavaScript主要就是对这颗DOM（Document）树上的节点进行增删改。

## 9. 超链接

`<a></a>` 标签定义超链接，它用于从一个页面连接到另一个页面。

```html
<a herf=""></a>
```

+ `herf` ：hot references 引用，它的值一定是一个资源的地址，是该超链接跳转的目的地。该地址可以是绝对路径也可以是相对路径，可以是网络中某个资源的路径也可以是本地资源的路径。

作用：通过超链接可以从浏览器向服务器发送请求。

超链接特点

- 有下划线

- 鼠标停留在超链接上会显示小手形状

- 点击超链接之后能跳转页面

超链接有一个`target` 属性，表示打开超链接的窗口位置，可取值：

- `_blank`: 新窗口
- `_self`: 当前窗口
- `_top`: 顶级窗口
- `_parent`: 父窗口

可以在超链接中放上一张图片，实现图片超链接，点击图片即可跳转页面：

```html
<a herf="">
    <img src="">
</a>
```

## 10. div 和 span

`div`和`span`都可以称为“图层”，图层就是一个一个的盒子，`div`嵌套就是盒子套盒子。图层的作用是为了保证页面可以灵活的布局。

`div`和`span`是可以定位的，只要定下`div`的左上角的`x`轴和`y`轴即可。

区别：

- `div`独自占用一行（默认情况下）
- `span`不会独自占用一行

## 11. 列表

列表分为有序列表 `<ol></ol>`，无序列表 `<ul></ul>`，在这两种列表在标签中都使用 `<li>` 标签来定义每个列表项：

```html
有序列表：
<ol>
    <li>no.1</li>
    <li>no.2</li>
</ol>
无序列表：
<ul>
    <li>hh</li>
    <li>uu</li>
</ul>
```

效果如下：

有序列表：
<ol>
    <li>no.1</li>
    <li>no.2</li>
</ol>
无序列表：
<ul>
    <li>hh</li>
    <li>uu</li>
</ul>

## 12. 图片

`<img>` 标签定义图像：

```html
<img src="">
```

+ `src`属性是图片的路径
+ `width`设置宽度
+ `height`设置高度
+ `title`设置鼠标悬停时显示的信息
+ `alt`设置图片加载失败时显示的提示信息

设置图片宽度和高度的时候，只需要设宽度，高度会进行等比例缩放。