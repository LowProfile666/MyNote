# 1.什么是SpringMVC

它是基于MVC开发模式的框架,用来优化控制器.它是Spring家族的一员.它也具备IOC和AOP.

##   什么是MVC?

  它是一种开发模式,它是模型视图控制器的简称.所有的web应用都是基于MVC开发.

+ M:模型层,包含实体类,业务逻辑层,数据访问层
+ V:视图层,html,javaScript,vue等都是视图层,用来显现数据
+ C:控制器,它是用来接收客户端的请求,并返回响应到客户端的组件,Servlet就是组件

# 2.SpringMVC框架的优点

+ 1)轻量级,基于MVC的框架
+ 2)易于上手,容易理解,功能强大
+ 3)它具备IOC和AOP
+ 4)完全基于注解开发

## SSM优化的方向

![image-20240227125630221](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402271256287.png)

![image-20240227130257857](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402271302916.png)

## SpringMVC 的执行流程

![image-20240227130358039](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402271303126.png)

# 3.基于注解的SpringMVC框架开发的步骤

1)新建一个空的项目,设置项目的 maven 配置，在项目中新建模块，选择 maven 的 webapp模板.

![image-20240227201606497](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402272017615.png)

2)修改目录,此时 src/main 下只有 resources 和 webapp 的目录，所以需要添加缺失的 test,java 目录,并修改目录属性

+ 修改目录属性：

  ![image-20240227202102579](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402272021674.png)

3)修改pom.xml文件,添加SpringMVC的依赖,添加Servlet的依赖

```xml
<!--springMVC依赖 -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-webmvc</artifactId>
    <version>6.1.3</version>
</dependency>
<!-- servlet依赖 -->
<dependency>
    <groupId>jakarta.servlet</groupId>
    <artifactId>jakarta.servlet-api</artifactId>
    <version>6.0.0</version>
    <scope>provided</scope>
</dependency>
```

4)在 src/resources 下添加 springmvc.xml 配置文（也是一个Spring Config文件）,指定包扫描,添加视图解析器.

```xml  
<!--添加包扫描-->
<context:component-scan base-package="servlet" />
<!--添加视图解析器-->
<bean class="org.springframework.web.servlet.view.InternalResourceViewResolver">
    <!--配置前缀-->
    <property name="prefix" value="/admin/" />
    <!--配置后缀-->
    <property name="suffix" value=".jsp" />
</bean>
```

+ 视图解析器用于跳转页面，会跳转到 webapp 下的 admin 下的 jsp 文件。

5)删除web.xml文件,新建web.xml，因为自动生成的文件版本太低

+ 新建 web.xml 文件

![image-20240227205328677](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402272053784.png)

6)在web.xml文件中注册springMVC框架(所有的web请求都是基于servlet的)

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <!--注册SpringMVC框架-->
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:springmvc.xml</param-value>
        </init-param>
    </servlet>
    <servlet-mapping>
        <servlet-name>springmvc</servlet-name>
        <!--
              指定拦截什么样的请求
              http://localhost:8080/one  ×
              http://localhost:8080/index.jsp   ×
              http://localhost:8080/demo.action   √
              <a href="${pageContext.request.contextPath}/demo.action">访问服务器</a>
            -->
        <url-pattern>*.action</url-pattern>
    </servlet-mapping>

</web-app>
```

7)在webapp目录下新建admin目录,在admin目录下新建main.jsp页面,删除index.jsp页面,并新建,发送请求给服务器

```jsp
<body>
<a href="${pageContext.request.contextPath}/demo.action">访问服务器</a>
</body>
```

8)开发控制器(Servlet),它是一个普通的类.在 java 目录下新建一个包 servlet，在包下新建一个类：

```java
@Controller  //交给Spring去创建对象
public class DemoAction {
    /*** 以前的Servlet的规范
     * protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {}
     * action中所有的功能实现都是由方法来完成的
	* action方法的规范
	* 1)访问权限是public
	* 2)方法的返回值任意
	* 3)方法名称任意
	* 4)方法可以没有参数,如果有可是任意类型
	* 5)要使用@RequestMapping注解来声明一个访问的路径(名称)
*/
	@RequestMapping("/demo")
	public String demo(){
        System.out.println("服务器被访问到了.......");
        return "main";  //可以直接跳到/admin/main.jsp页面上
    }
}
```

+ 使用 `@RequestMapping("/demo")` 不行的话，使用 `@RequestMapping("/demo.action")` 

 9)添加tomcat进行测试功能            

![image-20240227210758648](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402272107740.png)

访问 http://localhost:8080/springmvc001/ ，点击页面上的超链接 http://localhost:8080/springmvc001/demo.action，会请求到 demo 方法，然后返回一个名为 “main” 的视图，这个视图文件的名字会被拼接成 /admin/main.jsp ，然后会找到 webapp/admin/main.jsp 文件，将该文件显示在页面上。

# 4.分析web请求

  web请求执行的流程

```
							  核心处理器
index.jsp<--------------->DispatcherServlet<------------------->SpringMVC的处理器是一个普通的方法
one.jsp  <--------------->DispatcherServlet<------------------->SpringMVC的处理器是一个普通的方法
```

+ DispatcherServlet要在web.xml文件中注册才可用.

# 5.@RequestMapping注解详解

  此注解就是来映射服务器访问的路径.

+ 1)此注解可加在方法上,是为此方法注册一个可以访问的名称(路径)

  ```java
  @RequestMapping("/demo")
  public String demo(){
      System.out.println("服务器被访问到了.......");
      return "main";  //可以直接跳到/admin/main.jsp页面上
  }
  ```

  ```jsp
  <a href="${pageContext.request.contextPath}/demo.action">访问服务器</a>
  ```

+ 2)此注解可以加在类上,相当于是包名(虚拟路径),区分不同类中相同的action的名称

  ```java
  @RequestMapping("/user")
  public class DemoAction1 {..}
  ```

  ```jsp
  <a href="${pageContext.request.contextPath}/user/demo.action">访问服务器</a>
  ```

+ 3)此注解可区分get请求和post请求

  ```java
  @Controller
  public class ReqAction {
      @RequestMapping(value = "/req",method = RequestMethod.GET)
      public String req(){
          System.out.println("我是处理get请求的........");
          return "main";
      }
      @RequestMapping(value = "/req" ,method = RequestMethod.POST)
      public String req1(){
          System.out.println("我是处理post请求的........");
          return "main";
      }
  }
  ```

被 `@RequestMapping` 标注的方法的返回值：

+ **字符串（String）**：方法可以返回一个字符串，表示视图的逻辑名称。这个逻辑名称将由视图解析器解析为实际的视图资源（如JSP文件），然后返回给客户端。
+ **ModelAndView对象**：方法可以返回一个 `ModelAndView` 对象，该对象包含了模型数据以及视图的逻辑名称。通过 `ModelAndView`，您可以设置模型数据并指定要返回的视图。这种方式可以更加灵活地处理模型数据和视图的渲染。
+ **void**：方法也可以返回 `void`，此时表示该方法负责生成响应并渲染视图。通常，这种情况下，控制器方法会直接向HTTP响应中写入内容，而不需要返回任何特定的视图逻辑名称。
+ **其他类型**：方法可以返回任何其他类型的对象，Spring MVC会尝试将其转换为视图。如果返回的对象是字符串，它将被解释为视图的逻辑名称。如果返回的对象是JSON、XML等数据格式，Spring MVC将会将其写入到HTTP响应中，而不需要渲染视图。

# 6.五种数据提交方式的优化

可以优化的内容：

![image-20240227215457399](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402272154523.png)

## 1)单个提交数据

页面:  

```jsp
<form action="${pageContext.request.contextPath}/one.action">
    姓名:<input name="myname"><br>
    年龄:<input name="age"><br>
    <input type="submit" value="提交">
</form>
```

action:

```java
@RequestMapping("/one")
public String one(String myname,int age){ //  ===>自动注入,并且类型转换
    System.out.println("myname="+myname+",age="+(age+100));
    return "main";
}
```

+ 参数列表只需要保证名字和前端的 name 一致即可，会自动类型转换

## 2)对象封装提交数据

在提交请求中,保证请求参数的名称与实体类中成员变量的名称一致,则可以自动创建对象,则可以自动提交数据,自动类型转换,自动封装数据到对象中.

实体类:
```java    
public class Users {
    private String name;
    private int age;
}
```

页面:

```jsp
<form action="${pageContext.request.contextPath}/two.action" method="post">
    姓名:<input name="name"><br>
    年龄:<input name="age"><br>
    <input type="submit" value="提交">
</form>
```

action:
```java
@RequestMapping("/two")
public String two(Users u){
    System.out.println(u);
    return "main";
}
```

## 3)动态占位符提交

仅限于超链接或地址拦提交数据.它是一杠一值,一杠一大括号,使用注解@PathVariable来解析.      
```jsp    
<a href="${pageContext.request.contextPath}/three/张三/22.action">动态提交</a>
```

```java
@RequestMapping("/three/{uname}/{uage}")
public String three(
    @PathVariable("uname")  ===>用来解析路径中的请求参数
    String name,
    @PathVariable("uage")
    int age){
    System.out.println("name="+name+",age="+(age+100));
    return "main";
}
```

## 4)映射名称不一致

提交请求参数与action方法的形参的名称不一致,使用注解@RequestParam来解析
    /**

     *  姓名:<input name="name"><br>
          *  年龄:<input name="age"><br>
          */
        @RequestMapping("/four")
        public String four(
            @RequestParam("name")  ===>专门用来解决名称不一致的问题
            String uname,
            @RequestParam("age")
            int uage){
        System.out.println("uname="+uname+",uage="+(uage+100));
        return "main";
        }
    5)手工提取数据
    /**
          *  姓名:<input name="name"><br>
               *  年龄:<input name="age"><br>
               */
      @RequestMapping("/five")
            public String five(HttpServletRequest request){
            String name = request.getParameter("name");
            int age = Integer.parseInt(request.getParameter("age"));
            System.out.println("name="+name+",age="+(age+100));
            return "main";
            }   
        7.中文乱码解决方案
      配置过滤器.
      <filter>
            <filter-name>encode</filter-name>
            <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
            <!--
            配置参数
                private String encoding;
                private boolean forceRequestEncoding;
                private boolean forceResponseEncoding;
            -->
            <init-param>
                <param-name>encoding</param-name>
                <param-value>UTF-8</param-value>
            </init-param>
            <init-param>
                <param-name>forceRequestEncoding</param-name>
                <param-value>true</param-value>
            </init-param>
            <init-param>
                <param-name>forceResponseEncoding</param-name>
                <param-value>true</param-value>
            </init-param>
            </filter>
            <filter-mapping>
            <filter-name>encode</filter-name>
            <url-pattern>/*</url-pattern>
            </filter-mapping> 

8.action方法的返回值
  1)String:客户端资源的地址,自动拼接前缀和后缀.还可以屏蔽自动拼接字符串,可以指定返回的路径.
  2)Object:返回json格式的对象.自动将对象或集合转为json.使用的jackson工具进行转换,必须要添加jackson依赖.一般用于ajax请求.
  3)void:无返回值,一般用于ajax请求.
  4)基本数据类型,用于ajax请求.
  5)ModelAndView:返回数据和视图对象,现在用的很少.

9.完成ajax请求访问服务器,返回学生集合.
  1)添加jackson依赖
     <dependency>
      <groupId>com.fasterxml.jackson.core</groupId>
      <artifactId>jackson-databind</artifactId>
      <version>2.9.8</version>
    </dependency>
  2)在webapp目录下新建js目录,添加jQuery函数库
  3)在index.jsp页面上导入函数库
  function show() {
        $.ajax({
            url:"${pageContext.request.contextPath}/ajax.action",
            dataType:"json",
            type:"get",
            success:function (list) {
              //  alert(list);
                var s="";
                $.each(list,function (i,stu) {
                  //  alert(stu);
                    s+=stu.name+"----"+stu.age+"<br>";
                });
                $("#mydiv").html(s);

            }
        });
    }
  4)在action上添加注解@ResponseBody,用来处理ajax请求
	@Controller
	public class AjaxAction {
	    //处理ajax请求,一定要加@ResponseBody
	    @ResponseBody
	    @RequestMapping("/ajax")
	    public List<Student> ajax(){
	        Student stu1 = new Student("张三",22);
	        Student stu2 = new Student("李四",24);
	        Student stu3 = new Student("王五",23);
	       List<Student> list = new ArrayList<>();
	       list.add(stu1);
	       list.add(stu2);
	       list.add(stu3);
	        //调用json转换工具ObjectMapper进行转换
	        return list;  //===>springmvc负责转换成json
	    }
	}
  5)在springmvc.xml文件中添加注解驱动<mvc:annotationdriven/>,它用来解析@ResponseBody注解
  <mvc:annotation-driven></mvc:annotation-driven>

10.四种跳转方式
  本质还是两种跳转:请求转发和重定向,衍生出四种是请求转发页面,转发action,重定向页面,重定向action
  @RequestMapping("/one")
    public String one(){
        System.out.println("这是请求转发页面跳转.........");
        return "main";  //默认是请求转发,使用视图解析器拼接前缀后缀进行页面跳转
    }

    @RequestMapping("/two")
    public String two(){
        System.out.println("这是请求转发action跳转.........");
        //  /admin/  /other.action  .jsp
        //forward: 这组字符串可以屏蔽前缀和后缀的拼接.实现请求转发跳转
        return "forward:/other.action";  //默认是请求转发,使用视图解析器拼接前缀后缀进行页面跳转
    }
    
    @RequestMapping("/three")
    public String three(){
        System.out.println("这是重定向页面.......");
        //redirect:  这组字符串可以屏蔽前缀和后缀的拼接.实现重定向跳转
        return "redirect:/admin/main.jsp";
    }
    
    @RequestMapping("/four")
    public String four(){
        System.out.println("这是重定向action.......");
        //redirect:  这组字符串可以屏蔽前缀和后缀的拼接.实现重定向跳转
        return "redirect:/other.action";
    }
    
    @RequestMapping("/five")
    public String five(){
        System.out.println("这是随便跳.......");
    
        return "forward:/fore/login.jsp";
    }

11.SpringMVC默认的参数类型
  不需要去创建,直接拿来使用即可.
  1)HttpServletRequest
  2)HttpServletResponse
  3)HttpSession
  4)Model
  5)Map
  6)ModelMap
   		//做一个数据,传到main.jsp页面上
        Users u = new Users("张三",22);

        //传递数据
        request.setAttribute("requestUsers",u);
        session.setAttribute("sessionUsers",u);
        model.addAttribute("modelUsers",u);
        map.put("mapUsers",u);
        modelMap.addAttribute("modelMapUsers",u);

  注意:Map,Model,ModelMap和request一样,都使用请求作用域进行数据传递.所以服务器端的跳转必须是请求转发.

12.日期处理
  1)日期的提交处理
    A.单个日期处理
    要使用注解@DateTimeFormat,此注解必须搭配springmvc.xml文件中的<mvc:annotationdriven标签>

    B.类中全局日期处理
    注册一个注解,用来解析本类中所有的日期类型,自动转换.
     @InitBinder
    public void initBinder(WebDataBinder dataBinder){
        dataBinder.registerCustomEditor(Date.class,new CustomDateEditor(sf,true));
    }

  2)日期的显示处理
    在页面上显示好看的日期,必须使用JSTL.
    步骤:
    A)添加依赖jstl
      <dependency>
      <groupId>jstl</groupId>
      <artifactId>jstl</artifactId>
      <version>1.2</version>
    </dependency>

    B)在页面上导入标签库 
    如果是单个日期对象,直接转为好看的格式化的字符串进行显示.
    如果是list中的实体类对象的成员变量是日期类型,则必须使用jstl进行显示.
    <%--导入jstl核心标签库--%>
    <%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
    <%--导入jstl格式化标签库--%>
    <%@taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
    
    C)使用标签显示数据    
   <table width="800px" border="1">
    <tr>
        <th>姓名</th>
        <th>生日</th>
    </tr>
    	<c:forEach items="${list}" var="stu">
    <tr>
            <td>${stu.name}</td>
            <td>${stu.birthday}------ <fmt:formatDate value="${stu.birthday}" pattern="yyyy-MM-dd"></fmt:formatDate></td>
    </tr>
    	</c:forEach>
	</table>

13.资源在WEB-INF目录下
  此目录下的动态资源,不可直接访问,只能通过请求转发的方式进行访问 .
  @Controller
	public class WebInfAction {
	    @RequestMapping("/showIndex")
	    public String showIndex(){
	        System.out.println("访问index.jsp");
	        return "index";
	    }
	    @RequestMapping("/showMain")
	    public String showMain(){
	        System.out.println("访问main.jsp");
	        return "main";
	    }
	    @RequestMapping("/showLogin")
	    public String showLogin(){
	        System.out.println("访问login.jsp");
	        return "login";
	    }
	    //登录的业务判断
	    @RequestMapping("/login")
	    public String login(String name, String pwd, HttpServletRequest request){
	        if("zar".equalsIgnoreCase(name) && "123".equalsIgnoreCase(pwd)){
	            return "main";
	        }else{
	            request.setAttribute("msg","用户名或密码不正确!");
	            return "login";
	        }
	    }
	}
14.SpringMVC的拦截器
  针对请求和响应进行的额外的处理.在请求和响应的过程中添加预处理,后处理和最终处理.

15.拦截器执行的时机
  1)preHandle():在请求被处理之前进行操作,预处理
  2)postHandle():在请求被处理之后,但结果还没有渲染前进行操作,可以改变响应结果,后处理
  3)afterCompletion:所有的请求响应结束后执行善后工作,清理对象,关闭资源 ,最终处理.

16.拦截器实现的两种方式
  1)继承HandlerInterceptorAdapter的父类
  2)实现HandlerInterceptor接口,实现的接口,推荐使用实现接口的方式

17.拦截器实现的步骤
  1)改造登录方法,在session中存储用户信息,用于进行权限验证
  @RequestMapping("/login")
    public String login(String name, String pwd, HttpServletRequest request){
        if("zar".equalsIgnoreCase(name) && "123".equalsIgnoreCase(pwd)){
            //在session中存储用户信息,用于进行权限验证
            request.getSession().setAttribute("users",name);
            return "main";
        }else{
            request.setAttribute("msg","用户名或密码不正确!");
            return "login";
        }
    }
  2)开发拦截器的功能.实现HandlerInterceptor接口,重写preHandle()方法
    if(request.getSession().getAttribute("users") == null){
            //此时就是没有登录,打回到登录页面,并给出提示
            request.setAttribute("msg","您还没有登录,请先去登录!");
            request.getRequestDispatcher("/WEB-INF/jsp/login.jsp").forward(request,response);
            return false;
        }
        return true;//放行请求
  2)在springmvc.xml文件中注册拦截器
  	<mvc:interceptors>
        <mvc:interceptor>
            <!--映射要拦截的请求-->
            <mvc:mapping path="/**"/>
            <!--设置放行的请求-->
            <mvc:exclude-mapping path="/showLogin"></mvc:exclude-mapping>
            <mvc:exclude-mapping path="/login"></mvc:exclude-mapping>
            <!--配置具体的拦截器实现功能的类-->
            <bean class="com.bjpowernode.interceptor.LoginInterceptor"></bean>
        </mvc:interceptor>
    </mvc:interceptors>

18.SSM整合的步骤
  0)建库,建表
  1)新建Maven项目,选择webapp模板
  2)修改目录
  3)修改pom.xml文件(使用老师提供)
  4)添加jdbc.properties属性文件
  5)添加SqlMapConfig.xml文件(使用模板)
  6)添加applicationContext_mapper.xml文件(数据访问层的核心配置文件)
  7)添加applicationContext_service.xml文件(业务逻辑层的核心配置文件)
  8)添加spirngmvc.xml文件
  9)删除web.xml文件,新建,改名,设置中文编码,并注册spirngmvc框架,并注册Spring框架
  10)新建实体类user
  11)新建UserMapper.java接口
  12)新建UserMapper.xml实现增删查所有功能,没有更新
  13)新建service接口和实现类
  14)新建测试类,完成所有功能的测试
  15)新建控制器,完成所有功能
  16)浏览器测试功能