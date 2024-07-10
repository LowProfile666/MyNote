Thymeleaf 是一个表现层的模板引擎， 一般被使用在 Web 环境中，它可以处理 HTML, XML、 JS 等文档，简单来说，它可以将 JSP 作为 Java Web 应用的表现层，有能力展示与处理数据。Thyme leaf 可以让表现层的界面节点与程序逻辑被共享，这样的设计， 可以让界面设计人员、业务人员与技术人员都参与到项目开发中。

这样，同一个模板文件，既可以使用浏览器直接打开，也可以放到服务器中用来显示数据，并且样式之间基本上不会存在差异，因此界面设计人员与程序设计人员可以使用同一个模板文件，来查看静态与动态数据的效果。

Thymeleaf 作为视图展示模型数据，用于和用户交互操作。JSP 的代替技术。比较适合做管理系统，是一种易于学习，掌握的。

# 表达式

表达式用于在页面展示数据的，有多种表达式语法，最常用的是变量表达式、链接表达式。

![image-20240709175248296](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091752328.png)

## 变量表达式

创建一个首页index.html，是一个静态页面，所以创建在resources/static下：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<div style="margin-left: 200px">
    1.<a href="exp">表达式</a> <br/>
</div>
</body>
</html>
```

定义一个控制器：

```java
@Controller
public class ExpController {
    @GetMapping("/exp")
    public String exp(Model model) {
        model.addAttribute("username", "张三");
        model.addAttribute("address", "中国湖北荆门");
        return "exp";
    }
}
```

需要在resources/templates下创建一个exp.html文件，使用Thymeleaf的语法：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h1 th:text="${username}"></h1>
<h1 th:text="${address}"></h1>
</body>
</html>
```

+ 更规范的写法是要在<html lang="en">这个标签中添加：

  ```html
  <html lang="en" xmlns:th="www.thymeleaf.org">
  ```

然后启动项目，会默认显示index页面：

![image-20240709200114279](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092001338.png)

点击后，会显示exp页面：

![image-20240709200129126](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092001154.png)

## 链接表达式

`@{}`中的路径是从应用程序的上下文路径（context path）开始。

上下文路径是你的应用程序在服务器上的根路径。例如，如果你的应用程序部署在 `http://localhost:8080/myapp`，那么 `myapp` 就是上下文路径。

`@{}` 也支持相对路径和绝对路径：

- **相对路径**：`@{/path}` 会自动包含上下文路径。
- **绝对路径**：`@{http://example.com/path}` 会生成一个完整的 URL。

在主页新加一个超链接：

```html
2.<a href="link">链接表达式</a> <br/>
```

新建一个控制器：

```java
@GetMapping("/link")
public String link(Integer id, String name, Model model) {
    model.addAttribute("id", id);
    model.addAttribute("name", name);
    return "link";
}
```

创建link页面：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h1>Link页面</h1>
<h1 th:text="${id}"></h1>
<h1 th:text="${name}"></h1>
</body>
</html>
```

在exp页面中使用链接表达式：

```html
<a th:href="@{http://www.baidu.com}">去百度</a>
<a th:href="@{/link}">去link，无参数</a>
```

从以上这个链接跳到link页面：

![image-20240709201518645](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092015681.png)

然后使用链接表达式传参：

```html
<a th:href="@{/link(id=111, name=zs)}">去link，带参数</a>
```

+ 格式是：`@{链接(参数名=值, 参数名=值...)}`

从上面这个链接点过去：

![image-20240709201943480](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092019519.png)

# if-for

Thymeaf 同样支持 if，for 语句的使用。

![image-20240709202252524](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092022583.png)

+ 没有else，只有if

在主页添加一个链接：

```html
3.<a href="if-for">if-for</a> <br/>
```

添加一个控制器：

```java
@GetMapping("/if-for")
public String ifFor(Model model) {
    model.addAttribute("login", true);
    model.addAttribute("user", new User("Tom", "1233433"));
    List<User> users = Arrays.asList(
        new User("Jimi", "123"),
        new User("Fiona", "wewe"),
        new User("lip", "23hjhjd")
    );
    model.addAttribute("users", users);
    return "ifFor";
}
```

实现这个User类：

```java
@Data
@NoArgsConstructor
@AllArgsConstructor
public class User {
    private String username;
    private String password;
}
```

然后创建ifFor视图页面：

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h3>if-for</h3>
<h5 th:if="10 > 2">10 > 2</h5>
<h5 th:if="10 > 20">10 > 20</h5>
<h5 th:if="${login}">已登录</h5>
</body>
</html>
```

现在查看if的效果：

![image-20240709203443164](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092034206.png)



可以查看网页的源代码，发现第二个h5标签不是被隐藏，而是根本就没有：

![image-20240709203609702](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092036745.png)

使用th:each来循环一个表格，谁被循环谁就加th:each：

```html
<table border="1">
    <tr>
        <td>username</td>
        <td>password</td>
    </tr>
    <tr th:each="user : ${users}}">
        <td th:text="${user.username}}"></td>
        <td th:text="${user.password}}"></td>
    </tr>
</table>
```

+ user 就是被循环的集合 users 中的每一个元素

效果：

![image-20240709203944158](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092039204.png)

`th:each` 还提供了一个状态变量，可以用来获取迭代过程中的各种信息，如当前索引、是否是第一个元素、是否是最后一个元素等。

```html
<div th:each="item, iterStat : ${items}">
    <p th:text="${item} + ' - Index: ' + ${iterStat.index}"></p>
</div>
```

iterStat是状态变量，它包含以下属性：

- `index`: 当前元素的从0开始的索引。
- `count`: 当前元素的从1开始的索引。
- `size`: 集合的总大小。
- `even/odd`: 布尔值，表示当前元素是偶数还是奇数。
- `first`: 布尔值，表示当前元素是否是第一个。
- `last`: 布尔值，表示当前元素是否是最后一个。

# 默认配置

在application配置文件中，有很多集成好的关于Thymeleaf的配置。

![image-20240709204217571](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407092042643.png)

