前后端综合项目：通讯录管理系统

# 准备数据库

准备一个数据库，准备一张表，有以下字段：

+ id：主键
+ name：姓名
+ tel：电话
+ address：住址

再随便插入一点数据。

# 准备web项目

## 创建项目

在 IDEA 中新建一个空的项目，在项目中新建一个普通模块，然后右键单击这个模块。选择 Open Module Settings 进入以下页面：

![image-20240222151711239](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221517273.png)

选中自己的模块，右键单击或点击上方的加号，选择下面的 web，这是给模块添加框架依赖，选择了 web 后，会在你的模块中创建一个 web 文件夹，就是放前端的代码的地方。

然后：

![image-20240222151838166](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221518257.png)

将模块作为一个 Artifact，这是为了能够部署到 Tomacat 服务器上。

接着点击上方这里：

![image-20240222151931568](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221519611.png)

然后在左上角加号打开，选择 Tomacat->local：

![image-20240222152020557](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221520637.png)

然后点击 Deployment，将我们的模块部署在 Tomcat 上：

![image-20240222152344522](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221523600.png)

![image-20240222152418027](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221524264.png)

然后就是配置 Tomcat：

![image-20240222152306603](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221523684.png)

现在，一个 web 项目已经准备好了。

## 引入第三方jar包

我们需要连接数据库，所以需要连接数据库的驱动。

在 web 目录下的 WEB-INF 目录下新建一个目录 lib，这个目录名一定叫 lib，因为这是规定，tomcat 服务器会从这个 lib 文件夹下加载我们需要的第三方库，如果不是叫 lib，就会找不到。

然后将 mysql 驱动器的 jar 包复制到这个 lib 下，并且右键单击这个 jar 包，选择 add as library 将这个包添加到类路径中，这样我们就可以使用这个包里的类：

![image-20240222153652046](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221536087.png)

还有我们会用到 fastjson 这个 jar 包，以同样的方式将这个 jar 包加载到项目中。

## 创建工具类

我们需要用到的连接数据库的的代码大部分都是重复性的，不同的只有执行具体的sql语句以及处理结果，所以我们可以将 JDBC 的重复性代码封装在一个工具类里面，供我们使用。

在 src 下建一个 utils 包，这个包放我们用到的工具类，在这个包下新建一个类，叫 DBUtil：

```java
import java.sql.*;

public class DBUtil {
    private static String url = "jdbc:mysql://localhost:3306/abms";
    private static String username = "root";
    private static String password = "1234";

    // 注册驱动
    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    // 获取连接
    public static Connection getConnection() {
        Connection res = null;
        try {
            res = DriverManager.getConnection(url, username, password);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return res;
    }
    // 释放资源
    public static void close(Connection conn, PreparedStatement ps, ResultSet res) {
        if (res != null) {
            try {
                res.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        if (ps != null) {
            try {
                ps.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
```

这样我们想获取一个数据库连接的话，直接使用 DBUtil.getConnection() 方法即可。

# 准备前端

可以直接在生成的 web 文件夹下写前端代码，这是不会出现跨域问题的；也可以自己在该项目外新建一个前端项目，将该 web 项目只是作为后端程序，但是需要解决跨域问题。本次使用前后端不分离的情况，直接在 web 项目中写前端。

在项目的 web 目录下，新建三个文件夹，

+ js：用来放需要用到的 js 文件
+ css：用来放需要用到的 css 文件
+ components：用来存放组件文件，组件就是单个的一些 html 代码

将 bootstrap 的 css 文件放入 css 文件夹，bootstrap 的 js 文件和 jQuery 文件放入 js 文件夹。

然后在 web 目录下新建一个主页 index.html，引入 bootstrap 和 jQuery 文件：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>ABMS</title>
    <script src="js/bootstrap.min.js"></script>
    <script src="js/jquery-3.7.1.min.js"></script>
    <link rel="stylesheet" href="css/bootstrap.min.css" />
</head>
<body>

</body>
</html>
```

## navbar

navbar 是导航栏，导航栏应该在每个页面都显示，所以将这个导航栏当作一个组件使用。

先在 bootstrap 中复制一个 navbar 的样式，然后在 components 下新建一个 html 文件，里面就写导航栏的样式，然后保存即可

```html
<nav class="navbar navbar-expand-lg bg-body-tertiary">
  <div class="container-fluid">
    <a class="navbar-brand" href="#">通讯录管理系统</a>
    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarNav">
      <ul class="navbar-nav">
        <li class="nav-item">
          <a class="nav-link" href="#">添加</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">修改</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">删除</a>
        </li>
      </ul>
    </div>
  </div>
</nav>
```

在主页中使用这个导航栏：有两种方法

+ 通过 ajax 获取组件的内容，显示到页面上
+ 通过 load 方法加载

使用 ajax：

```html
<body>
<div class="container">
    <div id="navbar"></div>
</div>

<script type="module">
$.ajax({
    url: "components/navbar.html",
    type: "get",
    success(resp) {
        console.log(resp)
        $("#navbar").html(resp);
    }
})
</script>
</body>
```

+ 这个方法会去获取 components/navbar.html 这个资源中的数据，会返回这个资源中的所有代码，然后通过 html 方法将所有的代码渲染到 `div` 中

使用 load：

```html
<div class="container">
    <div id="navbar"></div>
</div>

<script type="module">
    $("#navbar").load("components/navbar.html")
</script>
```

+ load 函数用来加载另一个HTML文件的内容并插入到当前页面中

使用 container 是因为 bootstrap 中的 container 样式有自适应宽度的功能。

此时效果：

![image-20240222120516323](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221205388.png)

# 首页

首页就是显示联系人列表的。

那么就需要连接数据库拿到所有的联系人信息，然后返回给前端显示出来。先准备后端获取联系人的接口。

## 获取联系人

在 src 下，新建一个包 service，这个包用来放所有的业务代码，本次实验就按最简单的方法来实现业务，不再写接口文件。

在 service 包下新建一个类，名字可以叫 GetListServlet，表明这是一个获取列表的 servlet 类：

```java
@WebServlet("/getList")  // 这个注解的作用就是指定路径，接口的路径
public class GetListServlet extends HttpServlet {  // 需要继承 HttpServlet
    @Override
    // 重写 doGet 方法，说明前端会发送一个 get 请求，如果前端发送 post 请求，就重写 post 方法
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 连接数据库
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet res = null;
        // 将获取到的所有的联系人放在一个集合里
        List<ContactPerson> list = new ArrayList<>();

        try {
            conn = DBUtil.getConnection();  // 获取连接
            String sql = "select * from t_user;";
            ps = conn.prepareStatement(sql);  // 获取数据库操作对象
            res = ps.executeQuery();  // 执行sql
            while (res.next()) {  // 处理结果集
                String name = res.getString("name");
                String tel = res.getString("tel");
                String address = res.getString("address");
                ContactPerson p = new ContactPerson(name, tel, address);
                list.add(p);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        PrintWriter out = response.getWriter();  // 获取向前端响应的对象
        response.setContentType("application/json");  // 这是响应的内容格式，要设置正确，不然前端可能解析不到
        out.print(JSON.toJSONString(list));  // 将集合转化为json格式返回，这个JSON就是第三方jar包fastjson中的
    }
}
```

这样一个获取联系人的接口就写好了，然后要在前端调用这个接口，获取到返回的数据：

```html
<script type="module">
    let list = [];
    $.ajax({
        url: "/ABMS_WEB/getList",  // 接口的地址
        type: 'get',  // 请求方式
        success: resp => {  // 如果请求成功，会返回数据，resp就是返回来的
            let html = `<div class="card"><div class="card-body">
                                            <div class="row header">
                                                <div class="col-2">姓名</div>
                                                <div class="col-4">电话</div>
                                                <div class="col-6">家庭住址</div>
    </div></div></div>`;
            // 使用循环，拼接字符串
            resp.forEach(item => {
                html += `<div class="card item"><div class="card-body">
                                        <div class="row">
                                            <div class="col-2">${item.name}</div>
                                            <div class="col-4">${item.tel}</div>
                                            <div class="col-6">${item.address}</div>
    </div></div></div>`;
            })
            // 将字符串渲染到前端的元素中
            $("#list").html(html);
        },
        error(resp) {
            console.log(2,resp)
        }
    })
</script>
```

此时效果：

![image-20240222164258978](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402221642080.png)

# 添加联系人页面

在 web 目录下新建一个 html 文件，叫 insert。

先配置一下导航栏上的跳转，在 navbar.html 文件中，顺便修改其他的跳转链接：

```html
<ul class="navbar-nav">
    <li class="nav-item">
        <a class="nav-link" href="insert.html">添加</a>
    </li>
    <li class="nav-item">
        <a class="nav-link" href="update.html">修改</a>
    </li>
    <li class="nav-item">
        <a class="nav-link" href="delete.html">删除</a>
    </li>
</ul>
```

在这里，注意一下地址栏上的地址变化，此时主页的地址是 http://localhost:8080/ABMS_WEB/，如果向上面这样写路径，点击后会跳转：http://localhost:8080/ABMS_WEB/insert.html，这是可以的；也可以这样写路径，从跟路径写起，根路径就是 `/` ，就是 localhost:8080，所以如果从根路径写起的话得把项目名加上：

```html
<li class="nav-item">
    <a class="nav-link" href="/ABMS_WEB/insert.html">添加</a>
</li>
```

两种都行。

然后从 boostrap 中复制一个表单控件的样式，使用栅格系统的布局方式：

```html
<div class="card">
    <div  class="card-body">
        <div class="row">
            <div class="col">
                <h3>添加联系人</h3>
            </div>
        </div>
        <form action="">
            <div class="row justify-content-md-center">
                <div class="col-3">
                    <div class="mb-3">
                        <input type="text" class="form-control" id="username" placeholder="输入姓名">
                    </div>
                </div>
            </div>
            <div class="row justify-content-md-center">
                <div class="col-3">
                    <div class="mb-3">
                        <input type="text" class="form-control" id="tel" placeholder="输入电话">
                    </div>
                </div>
            </div>
            <div class="row justify-content-md-center">
                <div class="col-3">
                    <div class="mb-3">
                        <input type="text" class="form-control" id="address" placeholder="输入家庭住址">
                    </div>
                </div>
            </div>
            <div class="row justify-content-md-center">
                <div class="col-3">
                    <button type="button" class="btn btn-secondary">添加</button>
                </div>
            </div>
        </form>
    </div>
</div>
```

目前样式：

![image-20240222205504340](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402222055461.png)

然后给添加按钮绑定事件，向后端发送数据。

## 添加联系人

```java
@WebServlet("/insert")
public class InsertServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 获取前端传来的数据，数据是以参数的形式传的
        String username = request.getParameter("username");
        String tel = request.getParameter("tel");
        String address = request.getParameter("address");
        
        Connection conn = null;
        PreparedStatement ps = null;
        int count = 0;

        try {
            conn = DBUtil.getConnection();  // 获取链接
            String sql = "insert into t_user values(null,?,?,?);";
            ps = conn.prepareStatement(sql);  // 获取数据库操作对象
            ps.setString(1,username);  // 设置参数
            ps.setString(2,tel);
            ps.setString(3,address);
            count = ps.executeUpdate();  // 执行sql
        } catch (SQLException e) {
            e.printStackTrace();
        }

        response.setContentType("application/json");
        PrintWriter out = response.getWriter();
        Map<String, String> map = new HashMap<>();  // map可以代替json格式使用
        if (count == 1) map.put("message", "添加成功");
        else map.put("message", "添加失败");
        out.write(JSON.toJSONString(map));
    }
}
```

```html
 <script type="module">
     $("button").on('click', () => {
         let username = $("#username").val();
         let tel = $("#tel").val();
         let address = $("#address").val();
         $.ajax({
             url: "/ABMS_WEB/insert",
             type: 'post',
             data: {
                 username: username,
                 tel: tel,
                 address: address,
             },
             success(resp) {
                 alert(resp.message);
             }
         })
     })
</script>
```

# 打包部署

## 打包

由于这个项目不是 maven 构建的，所以需要手动打包。

右击这个module，open module settings 打开设置，点击 artifacts ，点击加号，选择 web application：archive，选择 for ‘ABMS-WEB：war exploded’，然后点击 ok。

![image-20240222210938019](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402222109133.png)

![image-20240222211006111](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402222110232.png)

接着关掉当前设置面板，在菜单栏上选择 Build，选择 Build Artifacts，选择 ABMS-WEB：war，在选择 Build，会生成一个 war 文件。

![image-20240222211035672](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402222110757.png)

![image-20240222211050950](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402222110032.png)

![image-20240222211107649](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402222111733.png)

## 部署

[参考链接](https://blog.csdn.net/leaf_dai/article/details/84067906)

现在服务器上下载 tomcat，然后解压 tomcat，

```bash
wget https://archive.apache.org/dist/tomcat/tomcat-11/v11.0.0-M13/bin/apache-tomcat-11.0.0-M13.tar.gz
tar -zxvf apache-tomcat-11.0.0-M17.tar.gz
```

+ 不要安装太高版本的tomcat
+ 尽量和开发的环境保持一致(jdk21，tomcat11)
+ tomcat9及以下是使用javax，10开始是使用Jakarta

安装好了后，修改一下 conf 目录下的 server.xml 文件，将端口改为 8082，因为我的服务器上之前部署了若依项目，若依的 tomcat 占用了 8080 的端口。

然后将打包生成的 war 文件放到 tomcat 的 webapps 目录下，重启 tomcat 服务器，会自动加载该 war 文件，然后会生成对应的文件夹，再将这个目录配置在 nginx 上面，直接在默认的 server 块中写一个 location 就行：

```bash
location /ABMS/ {
    proxy_pass http://localhost:8082/ABMS/;
    proxy_set_header Host $host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
}
```

这样，输入http://47.109.78.124/ABMS/ 就可以访问到这个项目。

注意，生成的ABMS文件夹一定要对应代码中写的路径，也就是说，代码中的路径是 ABMS，那么服务器中的文件夹名也是这个，不一样的话就会报 404。
