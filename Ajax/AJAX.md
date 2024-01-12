# AJAX（Asynchronous Javascript And Xml）

## 传统请求及缺点

- 传统的请求都有哪些？
  - 直接在浏览器地址栏上输入URL。
  - 点击超链接
  - 提交form表单
  - 使用JS代码发送请求
    - window.open(url)
    - document.location.href = url
    - window.location.href = url
    - ....
- 传统请求存在的问题
  - 页面全部刷新导致了用户的体验较差。
  - 传统的请求导致用户的体验有空白期。（用户的体验是不连贯的）
  - ![AJAX同步请求](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111547651.png)

## AJAX概述

- AJAX不能称为一种技术，它是多种技术的综合产物。
- AJAX可以让浏览器发送一种特殊的请求，这种请求可以是：异步的。
- 什么是异步，什么是同步？
  - 假设有t1和t2线程，t1和t2线程并发，就是异步。
  - 假设有t1和t2线程，t2在执行的时候，必须等待t1线程执行到某个位置之后t2才能执行，那么t2在等t1，显然他们是排队的，排队的就是同步。
  - AJAX是可以发送异步请求的。也就是说，在同一个浏览器页面当中，可以发送多个ajax请求，这些ajax请求之间不需要等待，是并发的。
- AJAX代码属于WEB前端的JS代码。和后端的java没有关系，后端也可以是php语言，也可以是C语言。
- AJAX 应用程序可能使用 XML 来传输数据，但将数据作为纯文本或 JSON 文本传输也同样常见。
- AJAX可以更新网页的部分，而不需要重新加载整个页面。（页面局部刷新）
- AJAX可以做到在同一个网页中同时启动多个请求，类似于在同一个网页中启动“多线程”，一个“线程”一个“请求”。

![AJAX异步请求](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111552692.png)

![对AJAX异步请求的理解](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401111552764.png)

## XMLHttpRequest对象

- XMLHttpRequest对象是AJAX的核心对象，发送请求以及接收服务器数据的返回，全靠它了。

- XMLHttpRequest对象，现代浏览器都是支持的，都内置了该对象。直接用即可。

- 创建XMLHttpRequest对象

  - ```javascript
    var xhr = new XMLHttpRequest();
    ```

- XMLHttpRequest对象的方法

| 方法                                          | 描述                                                         |
| :-------------------------------------------- | :----------------------------------------------------------- |
| abort()                                       | 取消当前请求                                                 |
| getAllResponseHeaders()                       | 返回头部信息                                                 |
| getResponseHeader()                           | 返回特定的头部信息                                           |
| open(*method*, *url*, *async*, *user*, *psw*) | 规定请求method：请求类型 GET 或 POSTurl：文件位置async：true（异步）或 false（同步）user：可选的用户名称psw：可选的密码 |
| send()                                        | 将请求发送到服务器，用于 GET 请求                            |
| send(*string*)                                | 将请求发送到服务器，用于 POST 请求                           |
| setRequestHeader()                            | 向要发送的报头添加标签/值对                                  |

- XMLHttpRequest对象的属性

| 属性               | 描述                                                         |
| :----------------- | :----------------------------------------------------------- |
| onreadystatechange | 定义当 readyState 属性发生变化时被调用的函数                 |
| readyState         | 保存 XMLHttpRequest 的状态。0：请求未初始化     1：服务器连接已建立     2：请求已收到    3：正在处理请求    4：请求已完成且响应已就绪 |
| responseText       | 以字符串返回响应数据                                         |
| responseXML        | 以 XML 数据返回响应数据                                      |
| status             | 返回请求的状态号200: "OK"403: "Forbidden"404: "Not Found"    |
| statusText         | 返回状态文本（比如 "OK" 或 "Not Found"）                     |

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>ajax get请求</title>
</head>
<body>

<script type="text/javascript">
    window.onload = function(){
        document.getElementById("helloBtn").onclick = function (){
            // 发送ajax get请求
            //console.log("发送ajax get请求")
            // 1.第一步：创建AJAX核心对象XMLHttpRequest
            var xhr = new XMLHttpRequest();
            // 2.第二步：注册回调函数
            // 这是一个回调函数，这个函数在XMLHttpRequest对象的readyState状态值发生改变的时候被调用。
            xhr.onreadystatechange = function (){
                // 这里的回调函数会被调用多次。
                // 0 -> 1 被调用一次
                // 1 -> 2 被调用一次
                // 2 -> 3 被调用一次
                // 3 -> 4 被调用一次
                //console.log(xhr.readyState)

                // 当XMLHttpRequest对象的readyState的状态是4的时候，表示响应结束了。
                /*if (xhr.readyState == 4) {

                }*/

                if (this.readyState == 4) {
                    // 响应结束了。
                    //console.log("响应结束了")
                    // 响应结束之后，一般会有一个HTTP的状态码。
                    // HTTP状态码常见的包括：200表示成功了，404表示资源找不到，500表示服务器内部错误。
                    // HTTP状态码是HTTP协议的一部分，HTTP协议中规定的。服务器响应之后都会有一个状态码。
                    // 获取HTTP状态码
                    //console.log("HTTP响应状态码：" + this.status)
                    if (this.status == 404) {
                        alert("对不起，您访问的资源不存在，请检查请求路径")
                    } else if(this.status == 500){
                        alert("对不起，服务器发生了严重的内部错误，请联系管理员")
                    } else if(this.status == 200){
                        //alert("响应成功，完美")
                        // 200表示完全响应完毕，成功结束了。
                        // 通过XMLHttpRequest对象获取响应的信息。
                        // 通过XMLHttpRequest对象的responseText属性来获取响应的信息。
                        //alert(this.responseText)

                        // 把响应信息放到div图层当中，渲染
                        document.getElementById("mydiv").innerHTML = this.responseText
                    }

                }
            }
            // 3.第三步：开启通道（open只是浏览器和服务器建立连接，通道打开，并不会发送请求）
            // XMLHttpRequest对象的open方法
            // open(method, url, async, user, psw)
            // method: 请求的方式，可以是GET，也可以是POST，也可以是其它请求方式。
            // url：请求的路径
            // async: 只能是true或者false，true表示此ajax请求是一个异步请求，false表示此ajax请求是一个同步请求。（大部分请求都是true，要求异步。极少数情况需要同步，以后再说。）
            // user：用户名 pwd: 密码，用户名和密码是进行身份认证的，说明要想访问这个服务器上的资源，可能需要提供一些口令才能访问。需不需要用户名和密码，主要看服务器的态度。
            xhr.open("GET", "/ajax1/ajaxrequest1", true)
            // 4.第四步：发送请求
            xhr.send()
        }
    }
</script>

<!--给一个按钮，用户点击这个按钮的时候发送ajax请求-->
<input type="button" value="hello ajax" id="helloBtn">

<!--给一个div图层，ajax接收了响应的数据之后，在div中进行渲染。-->
<div id="mydiv"></div>

</body>
</html>
```

## AJAX GET请求

- 发送AJAX get请求，前端代码：

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <title>发送ajax get请求</title>
  </head>
  <body>
  <script type="text/javascript">
      window.onload = function () {
          document.getElementById("btn").onclick = function () {
              //1. 创建AJAX核心对象
              var xhr = new XMLHttpRequest();
              //2. 注册回调函数
              xhr.onreadystatechange = function(){
                  if (this.readyState == 4) {
                      if (this.status == 200) {
                          // 通过XMLHttpRequest对象的responseText属性可以获取到服务器响应回来的内容。
                          // 并且不管服务器响应回来的是什么，都以普通文本的形势获取。（服务器可能响应回来：普通文本、XML、JSON、HTML...）
                          // innerHTML属性是javascript中的语法，和ajax的XMLHttpRequest对象无关。
                          // innerHTML可以设置元素内部的HTML代码。（innerHTML可以将后面的内容当做一段HTML代码解释并执行）
                          //document.getElementById("myspan").innerHTML = this.responseText
                          document.getElementById("mydiv").innerHTML = this.responseText
                          // innerText也不是AJAX中的，是javascript中的元素属性，和XMLHttpRequest无关。
                          // innerText也是设置元素中的内容，但是即使后面是一段HTML代码，也是将其看做一个普通字符串设置进去。
                          //document.getElementById("myspan").innerText = this.responseText
                      }else{
                          alert(this.status)
                      }
                  }
              }
              //3. 开启通道
              xhr.open("GET", "/ajax/ajaxrequest2", true)
              //4. 发送请求
              xhr.send()
          }
      }
  </script>
  <button id="btn">发送ajax get请求</button>
  <span id="myspan"></span>
  <div id="mydiv"></div>
  </body>
  </html>
  ```

- 发送AJAX get请求，后端代码：

  ```java
  @WebServlet("/ajaxrequest2")
  public class AjaxRequest2Servlet extends HttpServlet {
      @Override
      protected void doGet(HttpServletRequest request, HttpServletResponse response)
              throws ServletException, IOException {
          // 设置响应的内容类型以及字符集
          response.setContentType("text/html;charset=UTF-8");
          // 获取响应流
          PrintWriter out = response.getWriter();
          // 响应
          out.print("<font color='red'>用户名已存在！！！</font>");
      }
  }
  
  ```
  
- AJAX get请求如何提交数据呢？

  - get请求提交数据是在“请求行”上提交，格式是：url?name=value&name=value&name=value....
  - 其实这个get请求提交数据的格式是HTTP协议中规定的，遵循协议即可。

## AJAX GET请求的缓存问题

- 对于低版本的IE浏览器来说，AJAX的get请求可能会走缓存。存在缓存问题。对于现代的浏览器来说，大部分浏览器都已经不存在AJAX get缓存问题了。
- 什么是AJAX GET请求缓存问题呢？
  - 在HTTP协议中是这样规定get请求的：get请求会被缓存起来。
  - 发送AJAX GET请求时，在同一个浏览器上，前后发送的AJAX请求路径一样的话，对于低版本的IE来说，第二次的AJAX GET请求会走缓存，不走服务器。
- POST请求在HTTP协议中规定的是：POST请求不会被浏览器缓存。
- GET请求缓存的优缺点：
  - 优点：直接从浏览器缓存中获取资源，不需要从服务器上重新加载资源，速度较快，用户体验好。
  - 缺点：无法实时获取最新的服务器资源。
- 浏览器什么时候会走缓存？
  - 第一：是一个GET请求
  - 第二：请求路径已经被浏览器缓存过了。第二次发送请求的时候，这个路径没有变化，会走浏览器缓存。
- 如果是低版本的IE浏览器，怎么解决AJAX GET请求的缓存问题呢？
  - 可以在请求路径url后面添加一个时间戳，这个时间戳是随时变化的。所以每一次发送的请求路径都是不一样的，这样就不会走浏览器的缓存问题了。
  - 可以采用时间戳："url?t=" + new Date().getTime()
  - 或者可以通过随机数："url?t=" + Math.random()
  - 也可以随机数+时间戳....

## AJAX POST请求

- AJAX POST请求和GET请求的代码区别在哪里？就是前端代码有区别。后端代码没有区别。

  ```javascript
  // 4. 发送AJAX POST请求
  // 设置请求头的内容类型。模拟form表单提交数据。不设置的话后端拿不到数据
  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded") 
  // 获取表单中的数据
  var username = document.getElementById("username").value;
  var password = document.getElementById("password").value;
  // send函数中的参数就是发送的数据，这个数据在“请求体”当中发送。
  xhr.send("username="+username+"&password="+password)
  ```

  `application/x-www-form-urlencoded` 这一串记不住没关系，可以在 IDEA 中的 form 中，输入 enctype 属性，会有提示。

  注意：`xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded") ` 这一句代码必须放在 `open()` 之后，`send()` 之前。

- 实现一个案例：使用AJAX POST请求实现用户注册的时候，用户名是否可用。（验证用户名是否可以注册）实现步骤如下：

  - 在前端，用户输入用户名之后，失去焦点事件blur发生，然后发送AJAX POST请求，提交用户名

    ```html
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>ajax post 验证用户名</title>
    </head>
    <body>
    <script type="text/javascript">
        window.onload = function () {
            document.getElementById("username").onfocus = function () {
                document.getElementById("mySpan").innerHTML = "";
            }
    
            document.getElementById("username").onblur = function () {
                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function () {
                    if (this.readyState == 4) {
                        if (this.status == 200)
                            document.getElementById("mySpan").innerHTML = this.responseText;
                        else
                            alert(this.status)
                    }
                }
                xhr.open("POST", "/ajax1/ajaxrequestTest2", true);
                xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
                var username = document.getElementById("username").value;
                xhr.send("username=" + username);
            }
        }
    </script>
    用户名：<input type="text" id="username"><span id="mySpan"></span>
    </body>
    </html>
    ```

  - 在后端，接收到用户名，连接数据库，根据用户名去表中搜索

    ```java
    @WebServlet("/ajaxrequestTest2")
    public class AjaxRequest2Servlet extends HttpServlet {
        @Override
        protected void doPost(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
    
            String username = request.getParameter("username");
            Connection conn = null;
            PreparedStatement ps = null;
            ResultSet res = null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
    //            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/kob?user=root&password=1234");
                conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/kob", "root", "1234");
                String sql = "select * from user where username = ?";
                ps = conn.prepareStatement(sql);
                ps.setString(1, username);
                res = ps.executeQuery();
                if (res.next()) {
                    out.print("<font color=red>用户已存在</font>");
                } else {
                    out.print("<font color=green>可以</font>");
                }
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
    }
    ```

  - 如果用户名已存在
    - 后端响应消息：对不起，用户名已存在（在前端页面以红色字体展示）
    
  - 如果用户名不存在
    - 后端响应消息：用户名可以使用（在前端页面以绿色字体展示）

- 实现一个案例：用户点击按钮之后，发送AJAX请求，显示学生列表。

  - 在后端java程序中拼接HTML代码，然后将HTML代码直接响应到浏览器客户端。这种方式不好，不应该在java代码中编写HTML代码，能否在java程序中直接向前端响应数据？可以，可以在后端拼接JSON格式的字符串，或者XML格式的字符串，将这个字符串发送给前端，前端解析即可。

## 基于JSON的数据交换

+ 在 JavaScript 中怎么创建一个 json 对象

  ```js
  var jsonObj = {
      "name1" : value,
      "name2" : value,
      "name3" : value,
      ...
  }
  ```

  属性值的数据类型随意。

+ 怎么访问一个 json 对象

  ```js
  var user = {
      "id" : 111,
      "name" : "zhangsan",
      "sex" : true,
      "age" : 18
  }
  // 第一种方式
  console.log(user.id);
  console.log(user.name);
  console.log(user.sex ? "男" : "女");
  console.log(user.age);
  
  // 第二种方式
  console.log(user["id"]);
  ```

- 在WEB前端中，如何将一个json格式的字符串转换成json对象

  - 第一种：使用 eval 函数

  ```js
  var jsonStr = "{\"username\" : \"zhangsan\", \"password\" : \"1233344\"}"
  window.eval("var jsonObj = " + formJava);
  alert(jsonObj.name+","+jsonObj.password)
  ```

  - 第二种：使用内置对象 JSON 的 parse 方法

  ```javascript
  var jsonStr = "{\"username\" : \"zhangsan\", \"password\" : \"1233344\"}"
  var jsonObj = JSON.parse(jsonStr)
  console.log(jsonObj.username)
  console.log(jsonObj.password)
  ```

- 在后端拼接JSON格式的字符串，响应给前端的浏览器

  ```java
  json.append("[");
  while (rs.next()) {
      // 获取每个学生的信息
      String name = rs.getString("name");
      String age = rs.getString("age");
      String addr = rs.getString("addr");
      // 拼接json格式的字符串
      // {"name":"   王五    ","age":    20      ,"addr":"      北京大兴区     "},
      json.append("{\"name\":\"");
      json.append(name);
      json.append("\",\"age\":");
      json.append(age);
      json.append(",\"addr\":\"");
      json.append(addr);
      json.append("\"},");
  }
  jsonStr = json.substring(0, json.length() - 1) + "]";
  ```

- 拼接JSON格式的字符串太痛苦，可以使用阿里巴巴的fastjson组件，它可以将java对象转换成json格式的字符串

  ```java
  List<Student> studentList = new ArrayList<>();
  while (rs.next()) {
      // 取出数据
      String name = rs.getString("name");
      int age = rs.getInt("age");
      String addr = rs.getString("addr");
      // 将以上数据封装成Student对象
      Student s = new Student(name, age, addr);
      // 将Student对象放到List集合
      studentList.add(s);
  }
  // 将List集合转换成json字符串
  jsonStr = JSON.toJSONString(studentList);
  ```

  注意：使用fastjson需要引入fastjson-1.2.2.jar

## 基于XML的数据交换

- 注意：如果服务器端响应XML的话，响应的内容类型需要写成：

  ```java
  response.setContentType("text/xml;charset=UTF-8");
  ```

  响应的内容应该是这种：

  ```xml
  <students>
      <student>
          <name>zhangsan</name>
          <age>45</age>
      </student>
      <student>
          <name>zhangsan</name>
          <age>45</age>
      </student>
  </students>
  ```

  且前端接收数据的时候要用 `responseXML`，接收返回值后，可以自动封装成 document  对象

  ```js
  var xmlDoc = this.responseXML;
  ```

- xml和JSON都是常用的数据交换格式

  - XML体积大，解析麻烦。较少用。
  - JSON体积小，解析简单，较常用。

- 基于XML的数据交换，前端代码

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <title>使用XML完成数据交换</title>
  </head>
  <body>
  <script type="text/javascript">
      window.onload = function(){
          document.getElementById("btn").onclick = function(){
              // 1.创建XMLHTTPRequest对象
              var xhr = new XMLHttpRequest();
              // 2.注册回调函数
              xhr.onreadystatechange = function () {
                  if (this.readyState == 4) {
                      if (this.status == 200) {
                          // 服务器端响应了一个XML字符串，这里怎么接收呢？
                          // 使用XMLHTTPRequest对象的responseXML属性，接收返回之后，可以自动封装成document对象（文档对象）
                          var xmlDoc = this.responseXML
                          //console.log(xmlDoc)
                          // 获取所有的<student>元素，返回了多个对象，应该是数组。
                          var students = xmlDoc.getElementsByTagName("student")
                          //console.log(students[0].nodeName)
                          var html = "";
                          for (var i = 0; i < students.length; i++) {
                              var student = students[i]
                              // 获取<student>元素下的所有子元素
                              html += "<tr>"
                              html += "<td>"+(i+1)+"</td>"
                              var nameOrAge = student.childNodes
                              for (var j = 0; j < nameOrAge.length; j++) {
                                  var node = nameOrAge[j]
                                  if (node.nodeName == "name") {
                                      //console.log("name = " + node.textContent)
                                      html += "<td>"+node.textContent+"</td>"
                                  }
                                  if (node.nodeName == "age") {
                                      //console.log("age = " + node.textContent)
                                      html += "<td>"+node.textContent+"</td>"
                                  }
                              }
                              html += "</tr>"
                          }
                          document.getElementById("stutbody").innerHTML = html
                      }else{
                          alert(this.status)
                      }
                  }
              }
              // 3.开启通道
              xhr.open("GET", "/ajax/ajaxrequest6?t=" + new Date().getTime(), true)
              // 4.发送请求
              xhr.send()
          }
      }
  </script>
  <button id="btn">显示学生列表</button>
  <table width="500px" border="1px">
      <thead>
      <tr>
          <th>序号</th>
          <th>姓名</th>
          <th>年龄</th>
      </tr>
      </thead>
      <tbody id="stutbody">
      <!--<tr>
          <td>1</td>
          <td>zhangsan</td>
          <td>20</td>
      </tr>
      <tr>
          <td>2</td>
          <td>lisi</td>
          <td>22</td>
      </tr>-->
      </tbody>
  </table>
  </body>
  </html>
  ```

- 基于XML的数据交换，后端java程序：

  ```java
  @WebServlet("/ajaxrequest6")
  public class AjaxRequest6Servlet extends HttpServlet {
      @Override
      protected void doGet(HttpServletRequest request, HttpServletResponse response)
              throws ServletException, IOException {
          // 注意：响应的内容类型是XML。
          response.setContentType("text/xml;charset=UTF-8");
          PrintWriter out = response.getWriter();
  
          /*
          <students>
              <student>
                  <name>zhangsan</name>
                  <age>20</age>
              </student>
              <student>
                  <name>lisi</name>
                  <age>22</age>
              </student>
          </students>
           */
  
          StringBuilder xml = new StringBuilder();
          xml.append("<students>");
          xml.append("<student>");
          xml.append("<name>zhangsan</name>");
          xml.append("<age>20</age>");
          xml.append("</student>");
          xml.append("<student>");
          xml.append("<name>lisi</name>");
          xml.append("<age>22</age>");
          xml.append("</student>");
          xml.append("</students>");
  
          out.print(xml);
      }
  }
  
  ```
  

## AJAX乱码问题

- 测试内容：

  - 发送ajax get请求
    - 发送数据到服务器，服务器获取的数据是否乱码？
    - 服务器响应给前端的中文，会不会乱码？
  - 发送ajax post请求
    - 发送数据到服务器，服务器获取的数据是否乱码？
    - 服务器响应给前端的中文，会不会乱码？

- 包括还要测试tomcat服务器的版本：

  - tomcat10和tomcat9都要进行测试。

- 测试结果：

  - 对于tomcat10来说，关于字符集，我们程序员不需要干涉，不会出现乱码。

  - 对于tomcat9来说呢？

    - 响应中文的时候，会出现乱码，怎么解决？

      ```java
      response.setContentType("text/html;charset=UTF-8");
      ```

    - 发送ajax post请求的时候，发送给服务器的数据，服务器接收之后乱码，怎么解决？

      ```java
      request.setCharacterEncoding("UTF-8");
      ```


## AJAX的异步与同步

- 什么是异步？什么是同步？

  - ajax请求1和ajax请求2，同时并发，谁也不用等谁，这就是异步。（a不等b，b也不等a）
  - 如果ajax请求1在发送的时候需要等待ajax请求2结束之后才能发送，那么这就是同步。（a等待b，或者b等待a，只要发生等待，就是同步。）

- 异步和同步在代码上如何实现？

  ```javascript
  // 假设这个是ajax请求1
  // 如果第三个参数是false：这个就表示“ajax请求1”不支持异步，也就是说ajax请求1发送之后，会影响其他ajax请求的发送，只有当我这个请求结束之后，你们其他的ajax请求才能发送。
  // false表示，不支持异步。我这个请求发了之后，你们其他的请求都要靠边站。都等着。你们别动呢，等我结束了你们再说。
  xhr1.open("请求方式", "URL", false)
  xhr1.send()
  
  // 假设这个是ajax请求2
  // 如果第三个参数是true：这个就表示“ajax请求2”支持异步请求，也就是说ajax请求2发送之后，不影响其他ajax请求的发送。
  xhr2.open("请求方式", "URL", true) 
  xhr2.send()
  ```

  例子，前端代码：

  ```html
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <title>ajax异步同步</title>
  </head>
  <body>
  <script type="text/javascript">
      window.onload = function () {
          document.getElementById("btn1").onclick = function () {
              var xhr = new XMLHttpRequest();
              xhr.onreadystatechange = function () {
                  if (this.readyState == 4) {
                      if (this.status == 200) {
                          document.getElementById("div1").innerHTML = this.responseText;
                      }
                      else
                          alert(this.status)
                  }
              }
              xhr.open("GET","/ajax1/ajaxrequest3?t=" + new Date().getTime(), false);
              xhr.send();
          }
  
          document.getElementById("btn2").onclick = function () {
              var xhr = new XMLHttpRequest();
              xhr.onreadystatechange = function () {
                  if (this.readyState == 4) {
                      if (this.status == 200) {
                          document.getElementById("div2").innerHTML = this.responseText;
                      }
                      else
                          alert(this.status)
                  }
              }
              xhr.open("GET","/ajax1/ajaxrequest4?t=" + new Date().getTime(), true);
              xhr.send();
          }
      }
  
  </script>
      <button id="btn1">ajax 1</button>
      <div id="div1"></div>
  
      <button id="btn2">ajax 2</button>
      <div id="div2"></div>
  </body>
  </html>
  ```

  后端代码：

  ```java
  @WebServlet("/ajaxrequest4")
  public class AjaxRequest4Servlet extends HttpServlet {
  
      @Override
      protected void doGet(HttpServletRequest request, HttpServletResponse response)
              throws ServletException, IOException {
          response.setContentType("text/html;charset=UTF-8");
          PrintWriter out = response.getWriter();
          out.print("<font>ajax 2</font>");
      }
  }
  -----------------------------------------------------------------------------------------------------
  @WebServlet("/ajaxrequest3")
  public class AjaxRequest3Servlet extends HttpServlet {
  
      @Override
      protected void doGet(HttpServletRequest request, HttpServletResponse response)
              throws ServletException, IOException {
          response.setContentType("text/html;charset=UTF-8");
          PrintWriter out = response.getWriter();
          out.print("<font>ajax 1</font>");
          try {
              Thread.sleep(10 * 1000);
          } catch (InterruptedException e) {
              throw new RuntimeException(e);
          }
      }
  }
  ```

- 什么情况下用同步？（大部分情况下我们都是使用ajax异步方式，同步很少用。）

  - 举一个例子
    - 用户注册
      - 用户名需要发送ajax请求进行校验
      - 邮箱地址也需要发送ajax请求校验
      - 其他的也可能需要发送ajax请求。。。
      - 并且最终注册按钮的时候，也是发送ajax请求进行注册。
      - 那么显然，注册的Ajax请求和校验的ajax请求不能异步，必须等待所有的校验ajax请求结束之后，注册的ajax请求才能发。

## AJAX代码封装

- AJAX请求相关的代码都是类似的，有很多重复的代码，这些重复的代码能不能不写，能不能封装一个工具类。要发送ajax请求的话，就直接调用这个工具类中的相关函数即可。
- 接下来，手动封装一个工具类，这个工具类我们可以把它看做是一个JS的库。我们把这个JS库起一个名字，叫做jQuery。（我这里封装的jQuery只是一个前端的库，和后端的java没有关系，只是为了方便web前端代码的编写，提高WEB前端的开发效率）

### 封装getElementById

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>手动封装jQuery</title>
</head>
<body>

<script type="text/javascript">
    /*封装一个函数，通过这个函数可以获取到html页面中的节点，这个函数我给他起一个名字，叫做：jQuery*/
    /*要封装的代码是：根据id来获取元素。document.getElementById("btn")*/
    /*设计思路来自于CSS的语法。 #id 可以获取到这个元素 */
    function jQuery(selector) {  // selector可能是#id，也可以能是其他的选择器，例如类选择器：.class
        if (selector.charAt(0) == '#') {
            var obj = document.getElementById(selector.substring(1));
            return obj;
        }
    }
    window.onload = function () {
        jQuery("#btn").onclick = function () {
            jQuery("#div1").innerHTML = "<font color=red>用户名--</font>";
        }
    }
</script>

<button id="btn">显示用户名</button>
<div id="div1"></div>
</body>
</html>
```

这样实现了通过 id 获取元素的函数封装。但是这个 jQuery 的函数名还是太长了，可以更加简化，使用一个美元符号 `$` 来作函数名：

```js
$ = jQuery;
window.onload = function () {
	$("#btn").onclick = function () {
		$("#div1").innerHTML = "<font color=red>用户名--</font>";
	}
}
```

还要封装 `window.onload = function (){}` 这个代码，也可以在上面的 jQuery 方法中封装，js 中变量可以是任意类型，所以可以使用 `typeof` 来根据 `selector` 的类型执行不同的操作：

### 封装window.onload=function(){}

```js
function jQuery(selector) {
    // 根据id获取元素
    if (typeof selector == "string") {
        if (selector.charAt(0) == '#') {
            var obj = document.getElementById(selector.substring(1));
            return obj;
        }
    }
    // 页面加载完后，注册回调函数
    if (typeof selector == "function") {
        window.onload = selector;
    }
}
$ = jQuery;
```

然后在开始的 `window.onload = function(){}` 就可以改成：

```js
// $(function(){}) 作用是什么？
// 只要你写上以上的代码，就表示在页面加载完毕之后，执行里面的回调函数。
$(function () {
    $("#btn").onclick = function () {
        $("#div1").innerHTML = "<font color=red>##用户名--</font>";
    }
})
```

### 回顾js中的类

```js
<script type="text/javascript">
    // 定义类
    function User(username, usercode) {
        // 属性
        this.username = username;
        this.usercode = usercode;
        // 实例方法（通过对象调用）
        this.doSome = function () {
            console.log(username + " doSome");
        }
        // 静态方法（通过类名调用）
        User.doOther = function () {
            console.log("User doOther");
        }
    }
	// 定义类的第二种方法
    /*User = function(username, usercode) {
        // 属性
        this.username = username;
        this.usercode = usercode;
        // 实例方法（通过对象调用）
        this.doSome = function () {
            console.log(username + " doSome");
        }
        // 静态方法（通过类名调用）
        User.doOther = function () {
            console.log("User doOther");
        }
    }*/
    // 创建对象，访问对象的属性，访问对象的方法，访问静态方法
    // User(); 直接这样调用，你只是把它当做一个普通的函数去执行，不会创建对象，在堆中没有这个对象。
    // new User(); 这样调用的话，其实就是调用该类的构造方法，创建对象，并且在堆中分配空间。
    var user = new User("111", "zhangsan");
    // 访问属性
    alert(user.usercode + "," + user.username)
    // 调用方法（实例方法）
    user.doSome()
    // 调用静态方法
    User.doOther()

    // 后期如果想给某个类型扩展方法，还可以使用prototype属性
    User.prototype.扩展的 = function(){
        console.log("打印。。。。。")
    }

    user.扩展的()
</script>
```

注意：静态方法虽然是用类名来调用，但是一定要先 new 对象，才能用类名调用，否则不会生效。

### 封装innerHTML方法

要实现这样的效果：

```js
$("#div1").html("<font color=red>##用户名--</font>");
```

这个 `$("#div1")` 在上面的代码中，返回的是一个元素，但是这个元素中没有 `html` 函数，所以要将以上代码改为返回一个 jQuery 对象，因为 html 函数是写在 jQuery 对象中的：

```js
// 根据id获取元素
if (typeof selector == "string") {
    if (selector.charAt(0) == '#') {
        obj = document.getElementById(selector.substring(1));
        return new jQuery();
    }
}
```

并且 `obj` 变量也不加 `var` 了，这样他就是个全局变量。可以在任何地方使用

然后在 jQuery 函数中写：

```js
// 定义一个html()函数，代替：obj.innerHTML = ""
this.html = function (htmlStr) {
    obj.innerHTML = htmlStr;
}
```

然后使用：

```js
$(function () {
    $("#btn").onclick = function () {
        $("#div1").html("<font color=red>##用户名##</font>");
    }
})
```

但是以上代码还有问题，因为 `$("#div1")` 现在是一个 jQuery 对象了，并不是 dom 元素，所以它的 `onclick` 就没了，所以还要封装 `onclick`。

### 封装onclick

```js
// 定义一个click()函数，代替：obj.onclick = function(){}
this.click = function (fun) {
    obj.onclick = fun;
}
```

再使用：

```js
$(function () {
    $("#btn").click(function () {
        $("#div1").html("<font color=red>##用户名##</font>");
    });
})
```

### 封装获取value值

要想获取一个文本框的值或修改值，因为 `$("#username")` 返回的对象是一个 jQuery 对象，没有 value 这个属性，所以只能封装一个 val 函数：

```js
this.val = function(v){
    if (v == undefined) {  // 获取值
        return domObj.value
    }else{
        domObj.value = v  // 修改值
    }
}
```

使用：

```js
// 获取到文本框中的用户名
var username = $("#username").val()
alert(username)

// 修改文本框的value
$("#username").val("呵呵了！！！")
```

### 写入js文件

现在可以将以上的代码写入一个专门的 js 文件中，这样可以方便调用

### 封装AJAX

```js
// 静态的方法，发送ajax请求
/**
     * 分析：使用ajax函数发送ajax请求的时候，需要程序员给我们传过来什么？
     *      请求的方式(type)：GET/POST
     *      请求的URL(url)：url
     *      请求时提交的数据(data)：data
     *      请求时发送异步请求还是同步请求(async)：true表示异步，false表示同步。
     */
jQuery.ajax = function(jsonArgs){
    // 1.
    var xhr = new XMLHttpRequest();
    // 2.
    xhr.onreadystatechange = function(){
        if (this.readyState == 4) {
            if (this.status == 200) {
                // 我们这个工具类在封装的时候，先不考虑那么多，假设服务器返回的都是json格式的字符串。
                var jsonObj = JSON.parse(this.responseText)
                // 调用函数
                jsonArgs.success(jsonObj)
            }
        }
    }
    if (jsonArgs.type.toUpperCase() == "POST") {
        // 3.
        xhr.open("POST", jsonArgs.url, jsonArgs.async)
        // 4.
        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
        xhr.send(jsonArgs.data)
    }
    if (jsonArgs.type.toUpperCase() == "GET") {
        xhr.open("GET", jsonArgs.url + "?" + jsonArgs.data, jsonArgs.async)
        xhr.send()
    }
}
```

手动开发的 jQuery，源代码

```javascript
function jQuery(selector){
    if (typeof selector == "string") {
        if (selector.charAt(0) == "#") {
            domObj = document.getElementById(selector.substring(1))
            return new jQuery()
        }
    }
    if (typeof selector == "function") {
        window.onload = selector
    }
    this.html = function(htmlStr){
        domObj.innerHTML = htmlStr
    }
    this.click = function(fun){
        domObj.onclick = fun
    }
    this.focus = function (fun){
        domObj.onfocus = fun
    }
    this.blur = function(fun) {
        domObj.onblur = fun
    }
    this.change = function (fun){
        domObj.onchange = fun
    }
    this.val = function(v){
        if (v == undefined) {
            return domObj.value
        }else{
            domObj.value = v
        }
    }

    // 静态的方法，发送ajax请求
    /**
     * 分析：使用ajax函数发送ajax请求的时候，需要程序员给我们传过来什么？
     *      请求的方式(type)：GET/POST
     *      请求的URL(url)：url
     *      请求时提交的数据(data)：data
     *      请求时发送异步请求还是同步请求(async)：true表示异步，false表示同步。
     */
    jQuery.ajax = function(jsonArgs){
        // 1.
        var xhr = new XMLHttpRequest();
        // 2.
        xhr.onreadystatechange = function(){
            if (this.readyState == 4) {
                if (this.status == 200) {
                    // 我们这个工具类在封装的时候，先不考虑那么多，假设服务器返回的都是json格式的字符串。
                    var jsonObj = JSON.parse(this.responseText)
                    // 调用函数
                    jsonArgs.success(jsonObj)
                }
            }
        }

        if (jsonArgs.type.toUpperCase() == "POST") {
            // 3.
            xhr.open("POST", jsonArgs.url, jsonArgs.async)
            // 4.
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
            xhr.send(jsonArgs.data)
        }

        if (jsonArgs.type.toUpperCase() == "GET") {
            xhr.open("GET", jsonArgs.url + "?" + jsonArgs.data, jsonArgs.async)
            xhr.send()
        }

    }
}
$ = jQuery

// 这里有个细节，执行这个目的是为了让静态方法ajax生效。
new jQuery()
```

使用以上库，怎么用？

```html
<script type="text/javascript" src="/ajax/js/jQuery-1.0.0.js"></script>
<script type="text/javascript">
    $(function(){
        $("#btn1").click(function(){
            $.ajax({
                type : "POST",
                url : "/ajax/ajaxrequest11",
                data : "username=" + $("#username").val(),
                async : true,
                success : function(json){
                    $("#div1").html(json.uname)
                }
            })
        })
    })
</script>
```

## AJAX实现省市联动

- 什么是省市联动？

  - 在网页上，选择对应的省份之后，动态的关联出该省份对应的市。选择对应的市之后，动态的关联出该市对应的区。（首先要清楚需求）

- 进行数据库表的设计

  - ```
    t_area （区域表）
    id(PK-自增)	  code		name		pcode
    ---------------------------------------------
    1				001		 河北省		null
    2				002		 河南省		null
    3				003		 石家庄	    001
    4				004		 邯郸			 001
    5				005		 郑州			 002
    6				006		 洛阳			 002
    7				007		 丛台区	    004  
    
    将全国所有的省、市、区、县等信息都存储到一张表当中。
    采用的存储方式实际上是code pcode形式。
    ```

- 建表t_area，模拟好数据。

- 首先实现第一个功能：

  - 页面加载完毕之后，先把省份全部展现出来。

前端代码：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>省市联动</title>
    <script type="text/javascript" src="/ajax1/js/jQuery1.0.js"></script>
    <script>
        $(function() {
            $.ajax({
                type: "GET",
                url: "/ajax1/listArea",
                data: "t=" + new Date().getTime(),
                async: true,
                success: function(resp) {
                    var html = "<option value='000'>--请选择省份--</option>";
                    for (var i = 0; i < resp.length; i++) {
                        html += "<option value='" + resp[i].code + "'>" + resp[i].name + "</option>";
                    }
                    $("#province").html(html);
                }
            })

            $("#province").change(function(){
                $.ajax({
                    type: "GET",
                    url: "/ajax1/listArea",
                    data: "pcode=" + $("#province").val(),
                    async: true,
                    success: function (resp) {
                        var html = "";
                        for (var i = 0; i < resp.length; i++) {
                            html += "<option value='" + resp[i].code + "'>" + resp[i].name + "</option>";
                        }
                        $("#city").html(html);
                    }
                })
            })
        })
    </script>
</head>
<body>

省：<select id="province"></select>
市：<select id="city"></select>
</body>
</html>
```

后端代码：

```java
@WebServlet("/listArea")
public class ListAreaServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("html/text;charset=UTF-8");
        String pcode = request.getParameter("pcode");
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/dljdtest?user=root&password=1234");
            String sql = "";
            PreparedStatement ps = null;
            if (pcode == null) {
                sql = "select * from t_area where pcode is null";
                ps = conn.prepareStatement(sql);
            } else {
                sql = "select * from t_area where pcode = ?";
                ps = conn.prepareStatement(sql);
                ps.setString(1, pcode);
            }
            ResultSet res = ps.executeQuery();
            List<Area> list = new ArrayList<>();
            while (res.next()) {
                String name = res.getString("name");
                String code = res.getString("code");
                Area a = new Area(name, code, pcode);
                list.add(a);
            }
            response.getWriter().print(JSON.toJSONString(list));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```

## AJAX跨域问题

![对跨域的理解](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401121343893.png)

### 跨域

- 跨域是指从一个域名的网页去请求另一个域名的资源。比如从百度(https://baidu.com)页面去请求京东(https://www.jd.com)的资源。
- 通过超链接或者form表单提交或者window.location.href的方式进行跨域是不存在问题的（**大家可以编写程序测试一下**）。但在一个域名的网页中的一段js代码发送ajax请求去访问另一个域名中的资源，由于同源策略的存在导致无法跨域访问，那么ajax就存在这种跨域问题。
- 同源策略是指一段脚本只能读取来自同一来源的窗口和文档的属性，同源就是协议、域名和端口都相同。
- 同源策略有什么用？如果你刚刚在网银输入账号密码，查看了自己还有1万块钱，紧接着访问一些不规矩的网站，这个网站可以访问刚刚的网银站点，并且获取账号密码，那后果可想而知。所以，从安全的角度来讲，同源策略是有利于保护网站信息的。
- 有一些情况下，我们是需要使用ajax进行跨域访问的。比如某公司的A页面(a.bjpowernode.com)有可能需要获取B页面(b.bjpowernode.com)。

默认情况下，ajax 进行跨域访问会出现以下报错：

```
Access to XMLHttpRequest at 'http://localhost:8080/ajax1/ajaxrequest4' from origin 'null' has been blocked by CORS policy: No 'Access-Control-Allow-Origin' header is present on the requested resource.
```

+ 重点提示：CORS策略阻止（这个ajax跨域请求被：同源策略阻止。）

出现这个错误的根本原因是：跨域的时候，不允许共享同一个XMLHttpRequest对象。因为共享同一个XMLHttpRequest对象是不安全的。

什么是同源策略？？？？？同源策略是浏览器的一种安全策略。

* 什么是同源？什么是不同源？
     * 协议一致、域名一致、端口号一致。才是同源。
* 只要上面的任一元素不一致，就是不同源。
     *      同源：XMLHttpRequest对象可以共享。
     *      不同源：XMLHttpRequest对象不可以共享。

### 同源还是不同源

- 区分同源和不同源的三要素

- - 协议
  - 域名
  - 端口

- 协议一致，域名一致，端口号一致，三个要素都一致，才是同源，其它一律都是不同源

| **URL1**                           | **URL2**                        | **是否同源** | 描述               |
| ---------------------------------- | ------------------------------- | ------------ | ------------------ |
| http://localhost:8080/a/index.html | http://localhost:8080/a/first   | 同源         | 协议 域名 端口一致 |
| http://localhost:8080/a/index.html | http://localhost:8080/b/first   | 同源         | 协议 域名 端口一致 |
| http://www.myweb.com:8080/a.js     | https://www.myweb.com:8080/b.js | 不同源       | 协议不同           |
| http://www.myweb.com:8080/a.js     | http://www.myweb.com:8081/b.js  | 不同源       | 端口不同           |
| http://www.myweb.com/a.js          | http://www.myweb2.com/b.js      | 不同源       | 域名不同           |
| http://www.myweb.com/a.js          | http://crm.myweb.com/b.js       | 不同源       | 子域名不同         |

### 复现AJAX跨域问题

可以在 IDEA 中创建两个模块 a，b，两个模块分别部署一个 Tomcat 服务器，将两 Tomcat 服务器的端口号改成不一样的，这样就实现了不同域。

然后 a 的页面向 b 中的资源发送 ajax 请求，即可看到跨域问题。

### AJAX跨域解决方案

#### 方案1：设置响应头

- 核心原理：跨域访问的资源允许你跨域访问。

- 实现：

  - ```java
    response.setHeader("Access-Control-Allow-Origin", "http://localhost:8080"); // 允许某个
    response.setHeader("Access-Control-Allow-Origin", "*"); // 允许所有
    ```

#### 方案2：jsonp

- jsonp：json with padding（带填充的json【学完之后再理解这个什么意思！！！】）
- jsonp不是一个真正的ajax请求。只不过可以完成ajax的局部刷新效果。可以说jsonp是一种类ajax请求的机制。
- jsonp不是ajax请求，但是可以完成局部刷新的效果，并且可以解决跨域问题。
- 注意：jsonp解决跨域的时候，只支持GET请求。不支持post请求。

```js
<script type="text/javascript">
    /**
     * 这是我自定义的函数
     */
    function sayHello(data){
        //alert("hello world!")
        alert("hello," + data.name)
    }

    function sum(){
        alert("求和。。。")
    }
</script>

<!--超链接也可以跨域呀？为什么不用呢？因为超链接点击之后会跳转页面，无法做到页面局部刷新效果。-->
<!--script标签是可以跨域的。src属性可以是xxx.js文件，那这个路径可以是一个servlet路径吗？可以-->
<script type="text/javascript" src="http://localhost:8081/b/jsonp1?fun=sum"></script>
```

以上方式可以跨域 ，但是没有局部刷新的效果。

以下代码可以跨域，也可以局部刷新：

```js
<!--<script type="text/javascript" src="http://localhost:8081/b/jsonp2?fun=sayHello"></script>-->

<script type="text/javascript">
  // 自定义的函数
  function sayHello(data){ // data是一个json：{"username" : "lucy"}
    document.getElementById("mydiv").innerHTML = data.username
  }

  window.onload = () => {
    document.getElementById("btn").onclick = () => {
      // 加载script元素
      // 创建script元素对象
      const htmlScriptElement = document.createElement("script");
      // 设置script的type属性
      htmlScriptElement.type = "text/javascript"
      // 设置script的src属性
      htmlScriptElement.src = "http://localhost:8081/b/jsonp2?fun=sayHello"
      // 将script对象添加到body标签中（这一步就是加载script）
      document.getElementsByTagName("body")[0].appendChild(htmlScriptElement)
    }
  }
</script>

<button id="btn">jsonp解决跨域问题，达到ajax局部刷新的效果</button>

<div id="mydiv"></div>
```



#### 方案3：jQuery封装的jsonp

- 牛人们写的jQuery库，已经对jsonp进行了封装。大家可以直接拿来用。

- 用之前需要引入jQuery库的js文件。（这里的jQuery库咱们就不再封装了，咱们直接用jQuery写好的jsonp方式。）

- jQuery中的jsonp其实就是我们方案2的高度封装，底层原理完全相同。

- 核心代码

  - ```javascript
    $.ajax({
        type : "GET",
        url : "跨域的url",
        dataType : "jsonp", // 指定数据类型
        jsonp : "fun", // 指定参数名（不设置的时候，默认是："callback"）
        jsonpCallback : "sayHello" // 指定回调函数的名字
    							   // （不设置的时候，jQuery会自动生成一个随机的回调函数，
        						   //并且这个回调函数还会自动调用success的回调函数。）
    })
    ```

  
  这个的后端程序，需要拿到传过去的方法名字，然后再拼接 js 代码：
  
  ```java
  String fun = request.getParameter("fun");
  out.print(fun + "({\"username\":\"lisi\"})");
  ```
  
  前端代码：
  
  ```html
  <!--引入jQuery库：这个jQuery库是官网的，不是咱们手写封装的山寨版。-->
  <!-- <script type="text/javascript" src="/a/js/jquery-3.6.0.min.js"></script> -->
  <script src="https://lf3-cdn-tos.bytecdntp.com/cdn/expire-1-M/jquery/2.1.3/jquery.min.js"></script>
  
  <script type="text/javascript">
  
      // 这个函数不需要你写，jQuery可以自动帮助你生成
      //function jQuery3600508253314856699_1655528968612(json){ // 系统自动生成的这个函数默认情况，会自动调用success的回调函数。 }
  
      // 自定义的函数
      function sayHello(data) {
          $("#mydiv").html("欢迎你：" + data.username)
      }
  
      $(function () {
          $("#btn").click(function () {
              // 发送所谓的ajax请求（其实本质上并不是一个ajax请求。只是披着ajax的皮。乔装打扮的ajax。）
              $.ajax({
                  type: "GET", // jsonp请求只支持get请求。
                  // 虽然这里的url是这样写的，但实际上发送的请求是：/b/jsonp3?callback=jQuery3600508253314856699_1655528968612&_=1655528968613
                  // callback=jQuery3600508253314856699_1655528968612
                  // callback就是我们之前的fun
                  // jQuery3600508253314856699_1655528968612就是我们之前的sayHello，而这个名字是jQuery自动为我们生成的。
                  url: "http://localhost:8080/ajax1/ajaxrequest4",
                  dataType: "jsonp", // 指定数据类型是jsonp形式。【最关键的是它】
                  jsonp: "fun", // 不采用默认的参数名callback，用这个属性来指定具体的参数名。
                  jsonpCallback: "sayHello" // 不采用默认的回调函数，用这个属性来指定具体的回调函数。
                  /*success : function(data){ // data变量用来接收服务器端的响应(data是一个json：{"username":"lisi"})
                          $("#mydiv").html("欢迎你：" + data.username)
                      }*/
              })
          })
      })
  </script>
  
  <button id="btn">jQuery库封装的jsonp</button>
  
  <div id="mydiv"></div>
  ```
  
  如果没有 jsonp 参数的话，发送的请求是这样的：
  
  ![image-20240112151649960](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401121516062.png)
  
  有 jsonp 参数，没有指定 jsonpCallback 回调函数参数的话，请求是这样的：
  
  ![image-20240112151747519](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401121517591.png)
  
  这两个参数都指定了的话，请求才会是这样：
  
  ![image-20240112151843712](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401121518782.png)

#### 方案4：代理机制（httpclient）

![AJAX跨域解决方案之代理机制](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401121524212.png)

- 使用Java程序怎么去发送get/post请求呢？【GET和POST请求就是HTTP请求。】
  - 第一种方案：使用JDK内置的API（java.net.URL.....），这些API是可以发送HTTP请求的。
  - 第二种方案：使用第三方的开源组件，比如：apache的httpclient组件。（httpclient组件是开源免费的，可以直接用）
- 在java程序中，使用httpclient组件可以发送http请求。
  - 对于httpclient组件的代码，大家目前可以不进行深入的研究，可以从网上直接搜。然后粘贴过来，改一改，看看能不能完成发送get和post请求。
  - 使用httpclient组件，需要先将这个组件相关的jar包引入到项目当中。

使用 httpclient 组件，实现用 Java 发送 http get 请求：（要先引入 httpclient 的 jar 包）

```java
public class HttpClientSendGet {
    public static void main(String[] args) throws Exception {
        // 目标地址
		// String url = "https://www.baidu.com";
        String url = "http://localhost:8081/b/hello";
        HttpGet httpGet = new HttpGet(url);

        // 设置类型 "application/x-www-form-urlencoded" "application/json"
        httpGet.setHeader("Content-Type", "application/x-www-form-urlencoded");
        System.out.println("调用URL: " + httpGet.getURI());

         // httpClient实例化
        CloseableHttpClient httpClient = HttpClients.createDefault();
        // 执行请求并获取返回
        HttpResponse response = httpClient.execute(httpGet);
        System.out.println("Response toString()" + response.toString());
        HttpEntity entity = response.getEntity();
        System.out.println("返回状态码：" + response.getStatusLine());

        //得到返回数据的长度；没有该参数返回-1
          if (entity != null) {
              System.out.println("返回消息内容长度: " + entity.getContentLength());
          }

        // 显示结果
        BufferedReader reader = new BufferedReader(new InputStreamReader(entity.getContent(), "UTF-8"));
        String line = null;
        StringBuffer responseSB = new StringBuffer();
        while ((line = reader.readLine()) != null) {
                responseSB.append(line);
            }
        System.out.println("返回消息：" + responseSB);
        reader.close();

        httpClient.close();
    }
}
```

完整代码：前端代码：

```html
<script type="text/javascript">
    // ES6当中的有一个新语法：箭头函数。
    window.onload = () => {
        document.getElementById("btn").onclick = () => {
            // 发送ajax请求
            // 1.创建核心对象
            const xmlHttpRequest = new XMLHttpRequest(); // const可以声明变量。(可以自己研究一下：var let const声明变量时有什么区别)
            // 2.注册回调函数
            xmlHttpRequest.onreadystatechange = () => {
                if (xmlHttpRequest.readyState == 4) {
                    // 这里也可以使用区间的方式，因为状态码是200~299都是正常响应结束。
                    if (xmlHttpRequest.status >= 200 && xmlHttpRequest.status < 300) {
                        document.getElementById("mydiv").innerHTML = xmlHttpRequest.responseText
                    }
                }
            }
            // 3.开启通道
            xmlHttpRequest.open("GET", "/a/proxy", true)
            // 4.发送请求
            xmlHttpRequest.send()
        }
    }
</script>
<button id="btn">使用代理机制解决ajax跨域访问</button>
<div id="mydiv"></div>
```

代理 servlet ：

```java
@WebServlet("/proxy")
public class ProxyServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 通过 httpclient ，发送 http get 请求，访问 targetServlet

        HttpGet httpGet = new HttpGet("http://localhost:8081/b/target");
        httpGet.setHeader("Content-Type", "application/x-www-form-urlencoded");
        CloseableHttpClient httpClient = HttpClients.createDefault();
        HttpResponse resp = httpClient.execute(httpGet);
        HttpEntity entity = resp.getEntity();
        BufferedReader reader = new BufferedReader(new InputStreamReader(entity.getContent(), "UTF-8"));
        String line = null;
        StringBuffer responseSB = new StringBuffer();
        while ((line = reader.readLine()) != null) {
            responseSB.append(line);
        }
        reader.close();
        httpClient.close();

        response.getWriter().print(responseSB);
    }
}
```

目标 servlet：

```java
@WebServlet("/target")
public class TargetServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.getWriter().print("{\"name\":\"zhangsan\"}");
    }
}
```

#### 方案5：nginx反向代理

- nginx反向代理中也是使用了这种代理机制来完成AJAX的跨域，实现起来非常简单，只要修改一个nginx的配置即可。以后大家学习nginx之后再说吧。！！！！

## AJAX实现搜索联想 自动补全

- 什么是搜索联想？自动补全？
  - 百度是一个很典型的代表。在百度的搜索框中输入相关信息的时候，会有搜索联想以及自动补全。
  - 搜索联想和自动补全：实际上是为了方便用户的使用。让用户的体验更好。
  - 搜索联想：当用户输入一些单词之后，自动联想出用户要搜索的信息，给一个提示。
  - 自动补全：当联想出一些内容之后，用户点击某个联想的单词，然后将这个单词自动补全到搜索框当中。
  - 搜索联想和自动补全功能，因为是页面局部刷新效果，所以需要使用ajax请求来完成。
- 搜索联想，自动补全功能的核心实现原理？
  - 当键盘事件发生之后，比如：keyup：键弹起事件。
  - 发送ajax请求，请求中提交用户输入的搜索内容，例如：北京（发送ajax请求，携带“北京”两个字）
  - 后端接收到ajax请求，接收到“北京”两个字，执行select语句进行模糊查询。返回查询结果。
  - 将查询结果封装成json格式的字符串，将json格式的字符串响应到前端。
  - 前端接收到json格式的字符串之后，解析这个json字符串，动态展示页面。

前端代码：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>ajax实现搜索联想和自动补全功能</title>
    <style>
        .userInput {
            width: 300px;
            height: 25px;
            font-size: 20px;
            padding-left: 5px;
        }

        .showDataDiv {
            width: 310px;
            border: 1px solid lightgray;
            background-color: antiquewhite;
            display: none;
        }

        .showDataDiv p {
            padding-left: 5px;
            margin-top: 2px;
            margin-bottom: 2px;
        }

        .showDataDiv p:hover{
            cursor: pointer;
            border: 1px blue solid;
            background-color: aliceblue;
        }
    </style>
</head>
<body>

<script type="text/javascript">
    /*不使用jQuery，也不使用我们自己写的jQuery库。使用原生的ajax实现搜索联想和自动补全。*/
    window.onload = () => {
        document.getElementById("keywords").onkeyup = function(){
            if (this.value == "") {
                document.getElementById("datadiv").style.display = "none"
            }else{
                // 发送ajax请求
                // 1. 创建AJAX核心对象
                const xmlHttpRequest = new XMLHttpRequest();
                // 2. 注册回调函数
                xmlHttpRequest.onreadystatechange = () => {
                    if (xmlHttpRequest.readyState == 4) {
                        if (xmlHttpRequest.status >= 200 && xmlHttpRequest.status < 300) {
                            // [{"content":"javascript"},{"content":"javaweb"},{"content":"java..."}]
                            const json = JSON.parse(xmlHttpRequest.responseText);
                            // 遍历数组
                            let html = ""
                            for (let i = 0; i < json.length; i++) {
                                html += "<p onclick='setInput(\""+json[i].content+"\")'>"+json[i].content+"</p>"
                            }
                            document.getElementById("datadiv").innerHTML = html
                            // 显示出来
                            document.getElementById("datadiv").style.display = "block"
                        }
                    }
                }
                // 3. 开启通道
                xmlHttpRequest.open("GET", "/project/query?_="+new Date().getTime()+"&keywords=" + this.value, true)
                // 4. 发送请求
                xmlHttpRequest.send()
            }
        }
    }

    function setInput(content){
        document.getElementById("keywords").value = content
        document.getElementById("datadiv").style.display = "none"
    }
</script>

<input type="text" class="userInput" id="keywords">

<div id="datadiv" class="showDataDiv">
    <!--<p>北京疫情最新情况</p>
    <p>北京天气</p>
    <p>北京时间</p>
    <p>北京人</p>-->
</div>
</body>
</html>
```

后端代码：

```java
@WebServlet("/query")
public class QueryServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 获取用户输入的关键字
        String keywords = request.getParameter("keywords");
        // jdbc代码连接数据库，根据关键字查询数据库，返回数据，拼接json格式的字符串
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        try {
            // 注册驱动
            Class.forName("com.mysql.cj.jdbc.Driver");
            // 获取连接
            String url = "jdbc:mysql://localhost:3306/dljdtest?useUnicode=true&characterEncoding=UTF-8";
            String user = "root";
            String password = "1234";
            conn = DriverManager.getConnection(url, user, password);

            String sql = "select content from t_ajax where content like ?"; // 模糊查询的时候，条件不建议使用%开始，因为会让字段上的索引失效，查询效率降低。
            ps = conn.prepareStatement(sql);
            ps.setString(1, keywords + "%");
            rs = ps.executeQuery();
            // [{"content":"javascript"},{"content":"javaweb"},{"content":"java..."}]
            while (rs.next()) {
                String content = rs.getString("content");
                sb.append("{\"content\":\""+content+"\"},");
            }
        }catch(Exception e){
            e.printStackTrace();
        } finally {
            if (conn != null) {
                try {
                    conn.close();
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
            if (rs != null) {
                try {
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }

        response.setContentType("text/html;charset=UTF-8");
        response.getWriter().print(sb.subSequence(0, sb.length() - 1) + "]");
    }
}
```

## 附录：HTTP状态信息

### 1xx: 信息

| 消息:                   | 描述:                                                        |
| :---------------------- | :----------------------------------------------------------- |
| 100 Continue            | 服务器仅接收到部分请求，但是一旦服务器并没有拒绝该请求，客户端应该继续发送其余的请求。 |
| 101 Switching Protocols | 服务器转换协议：服务器将遵从客户的请求转换到另外一种协议。   |

### 2xx: 成功

| 消息:                             | 描述:                                                        |
| :-------------------------------- | :----------------------------------------------------------- |
| 200 OK                            | 请求成功（其后是对GET和POST请求的应答文档。）                |
| 201 Created                       | 请求被创建完成，同时新的资源被创建。                         |
| 202 Accepted                      | 供处理的请求已被接受，但是处理未完成。                       |
| 203 Non-authoritative Information | 文档已经正常地返回，但一些应答头可能不正确，因为使用的是文档的拷贝。 |
| 204 No Content                    | 没有新文档。浏览器应该继续显示原来的文档。如果用户定期地刷新页面，而Servlet可以确定用户文档足够新，这个状态代码是很有用的。 |
| 205 Reset Content                 | 没有新文档。但浏览器应该重置它所显示的内容。用来强制浏览器清除表单输入内容。 |
| 206 Partial Content               | 客户发送了一个带有Range头的GET请求，服务器完成了它。         |

### 3xx: 重定向

| 消息:                  | 描述:                                                        |
| :--------------------- | :----------------------------------------------------------- |
| 300 Multiple Choices   | 多重选择。链接列表。用户可以选择某链接到达目的地。最多允许五个地址。 |
| 301 Moved Permanently  | 所请求的页面已经转移至新的url。                              |
| 302 Found              | 所请求的页面已经临时转移至新的url。                          |
| 303 See Other          | 所请求的页面可在别的url下被找到。                            |
| 304 Not Modified       | 未按预期修改文档。客户端有缓冲的文档并发出了一个条件性的请求（一般是提供If-Modified-Since头表示客户只想比指定日期更新的文档）。服务器告诉客户，原来缓冲的文档还可以继续使用。 |
| 305 Use Proxy          | 客户请求的文档应该通过Location头所指明的代理服务器提取。     |
| 306 *Unused*           | 此代码被用于前一版本。目前已不再使用，但是代码依然被保留。   |
| 307 Temporary Redirect | 被请求的页面已经临时移至新的url。                            |

### 4xx: 客户端错误

| 消息:                             | 描述:                                                        |
| :-------------------------------- | :----------------------------------------------------------- |
| 400 Bad Request                   | 服务器未能理解请求。                                         |
| 401 Unauthorized                  | 被请求的页面需要用户名和密码。                               |
| 402 Payment Required              | 此代码尚无法使用。                                           |
| 403 Forbidden                     | 对被请求页面的访问被禁止。                                   |
| 404 Not Found                     | 服务器无法找到被请求的页面。                                 |
| 405 Method Not Allowed            | 请求中指定的方法不被允许。                                   |
| 406 Not Acceptable                | 服务器生成的响应无法被客户端所接受。                         |
| 407 Proxy Authentication Required | 用户必须首先使用代理服务器进行验证，这样请求才会被处理。     |
| 408 Request Timeout               | 请求超出了服务器的等待时间。                                 |
| 409 Conflict                      | 由于冲突，请求无法被完成。                                   |
| 410 Gone                          | 被请求的页面不可用。                                         |
| 411 Length Required               | "Content-Length" 未被定义。如果无此内容，服务器不会接受请求。 |
| 412 Precondition Failed           | 请求中的前提条件被服务器评估为失败。                         |
| 413 Request Entity Too Large      | 由于所请求的实体的太大，服务器不会接受请求。                 |
| 414 Request-url Too Long          | 由于url太长，服务器不会接受请求。当post请求被转换为带有很长的查询信息的get请求时，就会发生这种情况。 |
| 415 Unsupported Media Type        | 由于媒介类型不被支持，服务器不会接受请求。                   |
| 416                               | 服务器不能满足客户在请求中指定的Range头。                    |
| 417 Expectation Failed            |                                                              |

### 5xx: 服务器错误

| 消息:                          | 描述:                                              |
| :----------------------------- | :------------------------------------------------- |
| 500 Internal Server Error      | 请求未完成。服务器遇到不可预知的情况。             |
| 501 Not Implemented            | 请求未完成。服务器不支持所请求的功能。             |
| 502 Bad Gateway                | 请求未完成。服务器从上游服务器收到一个无效的响应。 |
| 503 Service Unavailable        | 请求未完成。服务器临时过载或当机。                 |
| 504 Gateway Timeout            | 网关超时。                                         |
| 505 HTTP Version Not Supported | 服务器不支持请求中指明的HTTP协议版本。             |
