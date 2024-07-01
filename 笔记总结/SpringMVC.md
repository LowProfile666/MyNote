发送请求到DispatcherServlet，根据请求路径将请求分发到某个控制器方法上，控制器方法返回一个页面或数据。

# 需要的依赖

+ spring-webmvc
+ jakarta.servlet-api
+ thymeleaf-spring6

# RequesMapping

将指定 URL 的请求绑定到一个特定的方法或类上，从而实现对请求的处理和响应。

使用位置：

+ 类

+ 方法

  ```java
  @Controller
  @RequestMapping("/user")
  public class UserController {
      @RequestMapping("/detail")
      public String toDetail(){
          return "/user/detail";
      }
  }
  ```

表示路径的属性：这两个属性都是一样的，都是数组，随便写哪个都可以

+ value
+ path

可以支持路径模糊匹配：

+ ?，代表任意一个字符：不能匹配 / 和 ？
+ *，代表0到N个任意字符：不能匹配 /
+ **，代表0到N个任意字符，并且路径中可以出现路径分隔符 /：spring6中，只能出现在路径末尾

表示请求方式的属性：该属性也是一个数组

+ method

  ```java
  @RequestMapping(value="/login", method = RequestMethod.POST)
  ```

表示指定参数的属性：该属性也是一个数组，要求请求参数必须和该数组中要求的所有参数完全一致后，才能映射成功

+ params

  表示：请求参数中必须包含 username 和 password，才能与当前标注的方法进行映射。

  ```java
  @RequestMapping(value="/login", params={"username", "password"})
  ```

  表示：请求参数中不能包含username参数，但必须包含password参数，才能与当前标注的方法进行映射。

  ```java
  @RequestMapping(value="/login", params={"!username", "password"}) 
  ```

   表示：请求参数中必须包含username参数，并且参数的值必须是admin，另外也必须包含password参数，才能与当前标注的方法进行映射。

  ```java
  @RequestMapping(value="/login", params={"username=admin", "password"}) 
  ```

  表示：请求参数中必须包含username参数，但参数的值不能是admin，另外也必须包含password参数，才能与当前标注的方法进行映射。

  ```java
  @RequestMapping(value="/login", params={"username!=admin", "password"}) 
  ```

  注意：如果前端提交的参数，和后端要求的请求参数不一致，则出现400错误！！！

表示指定请求头信息的属性：该属性也是一个数组，用法和params一样

+ headers

## 参数

使用RESTFul风格的请求路径时，可以使用占位符 `{}` 来表示参数。

```java
@RequestMapping(value="/testRESTful/{id}/{username}")
```

使用了占位符，就要使用@PathVariable注解标注参数，要在该注解中指定参数的名字（占位符中的名字），它会将数据传到对应的方法参数上：

```java
@RequestMapping(value="/testRESTful/{id}/{username}")
public String testRESTful(@PathVariable("id") int id, @PathVariable("username") String username){
    System.out.println(id + "," + username);
    return "testRESTful";
}
```

## 衍生RerquetMapping

+ **PostMaping**：要求前端必须发送post请求

+ **GetMapping**：要求前端必须发送get请求
+ **PutMapping**：要求前端必须发送put请求
+ **DeleteMapping**：要求前端必须发送delete请求
+ **PatchMapping**：要求前端必须发送patch请求

# 接收参数

## RequestParam

@RequestParam注解作用：将`请求参数`与方法上的`形参`映射。

```java
public String register(@RequestParam("username") String username,
                           @RequestParam("password") String password,
                           @RequestParam("sex") Integer sex,
                           @RequestParam("hobby") String[] hobbies,
                           @RequestParam("intro") String intro){}
```

该注解使用在形参上。该注解会自动做类型转换（将前端传过来的“1”转为1）。

该注解表示值的属性：这两个属性是一样的，属性值一定是前端传过来的参数名

+ name
+ value

表示参数的必要性的属性：没有写时默认为ture，表示必要

+ required

  ```java
  @RequestParam(value = "intro", required = false)
  ```

设置默认值的属性：当`没有提供对应的请求参数`或者`请求参数的值是空字符串""`的时候，方法的形参会采用默认值

+ defaultValue

  ```java
  @RequestParam(value = "intro", required = false, defaultValue = "hello")
  ```

类似的注解：用法都和@RequestParam一样

+ @RequestHeader：将`请求头信息`映射到`方法的形参`上
+ @CookieValue：将`请求提交的Cookie数据`映射到`方法形参`上

## 形参

@RequestParam这个注解可以省略，形参就直接是前端传过来的参数，前提是形参名和传过来的参数名一致。但是在Spring6+中，需要在pom.xml中配置：

```xml
<build>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <version>3.12.1</version>
            <configuration>
                <source>21</source>
                <target>21</target>
                <compilerArgs>
                    <arg>-parameters</arg>
                </compilerArgs>
            </configuration>
        </plugin>
    </plugins>
</build>
```

## pojo

前提：`POJO类的属性名`必须和`请求参数的参数名`保持一致，本质上是：POJO类的属性的set方法名去除set后首字母小写

```java
@PostMapping("/register")
public String register(User user){
    System.out.println(user);
    return "success";
}
```

SpringMVC看到方法的参数上是一个User对象，就会先通过反射机制拿到User类，创建一个User类对象， 通过前端传过来的参数名推出User类的set方法名，再调用这个set方法给user对象赋值。

# 三个域对象

请求域：request

+ 接口名：HttpServletRequest
+ request对象代表了一次请求。一次请求一个request。

会话域：session

+ 接口名：HttpSession
+ session对象代表了一次会话。从打开浏览器开始访问，到最终浏览器关闭，这是一次完整的会话。每个会话session对象都对应一个JSESSIONID，而JSESSIONID生成后以cookie的方式存储在浏览器客户端。浏览器关闭，JSESSIONID失效，会话结束。

应用域：application

+ 接口名：ServletContext
+ application对象代表了整个web应用，服务器启动时创建，服务器关闭时销毁。对于一个web应用来说，application对象只有一个。

都有以下方法：

```java
// 向域中存储数据
void setAttribute(String name, Object obj);

// 从域中读取数据
Object getAttribute(String name);

// 删除域中的数据
void removeAttribute(String name);
```

# 转发和重定向

在Spring MVC中将请求转发到另一个Controller上：

```java
return "forward:下一个资源的路径";
```

重定向：

```java
return "redirect:下一个资源的路径";
```

# RESTFul

RESTful 的英文全称是 Representational State Transfer（表述性状态转移）。简称REST。

REST对请求方式的约束是这样的：

- 查询必须发送GET请求
- 新增必须发送POST请求
- 修改必须发送PUT请求
- 删除必须发送DELETE请求

REST对URL的约束是这样的：

- 传统的URL：get请求，/springmvc/getUserById?id=1
- REST风格的URL：get请求，/springmvc/user/1

- 传统的URL：get请求，/springmvc/deleteUserById?id=1
- REST风格的URL：delete请求, /springmvc/user/1

# @ResponseBody

使用 @ResponseBody 注解来启用对应的消息转换器。而这种消息转换器只负责将Controller返回的信息以响应体的形式写入响应协议。

```java
@Controller
public class HelloController {

    @RequestMapping(value = "/hello")
    @ResponseBody
    public String hello(){
        // 由于你使用了 @ResponseBody 注解
        // 以下的return语句返回的字符串则不再是“逻辑视图名”了
        // 而是作为响应协议的响应体进行响应。
        return "hello";
    }
}
```

使用@ResponseBody注解可以将返回内容直接响应给浏览器，而不用返回一个页面名字。

如果想要直接返回一个Java对象，除了使用该注解，还要引入一些依赖，将对象转为json字符串。

+ 可以使用一些工具类如fastjson将对象转为json字符串返回，返回类型还是字符串：

  ```java
  @RequestMapping("/")
  @ResponseBody
  public String index() {
      User user = new User("zsm", "1222");
      return JSON.toJSONString(user);
  }
  ```

+ 使用jackson将返回的对象转为json字符串，返回类型还是对象：

  ```java
  @RequestMapping("/")
  @ResponseBody
  public User index() {
      User user = new User("zsm", "1222");
      return user;
  }
  ```

  需要引入jackson的依赖：

  ```xml
  <dependency>
      <groupId>com.fasterxml.jackson.core</groupId>
      <artifactId>jackson-databind</artifactId>
      <version>2.17.0</version>
  </dependency>
  ```

  需要开启注解驱动，在springmvc.xml中：

  ```xml
  <mvc:annotation-driven />
  ```

如果不引入jackson依赖的话，直接返回一个Java对象回去会报错406。

# @RestController

这一个注解代表了：@Controller + @ResponseBody。

@RestController 标注在类上即可。被它标注的Controller中所有的方法上都会自动标注 @ResponseBody

# @RequestBody

这个注解的作用是直接将请求体传递给Java程序，在Java程序中可以直接使用一个String类型的变量接收这个请求体的内容，获取到的是原生的请求体，如：username=admin&password=admin。

这个注解只能出现在方法的参数上。

而如果前端提交的是一个json格式字符串，而不是原生的格式，想要将该json字符串转成一个Java对象，还是需要使用jackson依赖和开启注解驱动：

```java
@RequestMapping("/a")
@ResponseBody
public String index(@RequestBody User user) {
    System.out.println(user);
    return "ok";
}
```

前端提交数据：

```json
{
    "username" : "zsm",
    "password" : "123"
}
```

如果不使用@RequestBody注解，程序没有问题，只是user对象的属性为null；写了@RequestBody注解，可以正确拿到值。

# RequestEntity

这个类的实例封装了整个请求协议：包括请求行、请求头、请求体所有信息。

出现在控制器方法的参数上，SpringMVC自动创建好，传递给处理器方法的参数上：

```java
@RequestMapping("/send")
@ResponseBody
public String send(RequestEntity<User> requestEntity){
    System.out.println("请求方式：" + requestEntity.getMethod());
    System.out.println("请求URL：" + requestEntity.getUrl());
    HttpHeaders headers = requestEntity.getHeaders();
    System.out.println("请求的内容类型：" + headers.getContentType());
    System.out.println("请求头：" + headers);

    User user = requestEntity.getBody();
    System.out.println(user);
    System.out.println(user.getUsername());
    System.out.println(user.getPassword());
    return "success";
}
```

# ResponseEntity

用该类的实例可以封装响应协议，包括：状态行、响应头、响应体。也就是说：如果你想定制属于自己的响应协议，可以使用该类。

```java
@Controller
public class UserController {
    @GetMapping("/users/{id}")
    // 响应体中的内容是User，所以泛型使用User
    public ResponseEntity<User> getUserById(@PathVariable Long id) {
        User user = userService.getUserById(id);
        if (user == null) {
            return ResponseEntity.status(HttpStatus.NOT_FOUND).body(null);
        } else {
            return ResponseEntity.ok(user);
        }
    }
}
```

# SpringMVC配置文件

配置包扫描：

```xml
<context:component-scan base-package="com.zsm.controller" />
```

配置视图解析器：

```xml
<bean id="thymeleafViewResolver" class="org.thymeleaf.spring6.view.ThymeleafViewResolver">
    <property name="characterEncoding" value="UTF-8"/>
    <property name="order" value="1"/>
    <property name="templateEngine">
        <bean class="org.thymeleaf.spring6.SpringTemplateEngine">
            <property name="templateResolver">
                <bean class="org.thymeleaf.spring6.templateresolver.SpringResourceTemplateResolver">
                    <property name="prefix" value="/WEB-INF/templates/"/>
                    <property name="suffix" value=".html"/>
                    <property name="templateMode" value="HTML"/>
                    <property name="characterEncoding" value="UTF-8"/>
                </bean>
            </property>
        </bean>
    </property>
</bean>
```

配置注解驱动：

```xml
<mvc:annotation-driven />
```

+ 用于使用jackson依赖将对象转为json字符串或将json字符串转为对象
+ 用于配置视图解析器
+ 用于配置静态资源

配置视图解析器：

```xml
<mvc:view-controller path="/如何访问该页面" view-name="对应的逻辑视图名称" />
```

+ 需要开启注解驱动

配置静态资源默认处理Servlet：

```xml
<mvc:default-servlet-handler>
```

+ 需要开启注解驱动器

配置静态资源：

```xml
<mvc:resources mapping="/static/**" location="/static/" />
```

+ 凡是请求路径是"/static/"开始的，都会去"/static/"目录下找该资源。
+ 需要开启注解驱动

配置自定义异常处理器：

```xml
<bean class="org.springframework.web.servlet.handler.SimpleMappingExceptionResolver">
    <property name="exceptionMappings">
        <props>
            <!--用来指定出现异常后，跳转的视图：出现Exception异常后，跳转到tip视图-->
            <prop key="java.lang.Exception">tip</prop>
        </props>
    </property>
    <!--将异常信息存储到request域，value属性用来指定存储时的key。-->
    <!--底层会执行这样的代码：request.setAttribute("e", 异常对象)，这个异常对象SpringMVC会自己设置-->
    <property name="exceptionAttribute" value="e"/>
</bean>
```

配置拦截器：

```xml
<mvc:interceptors>
    <bean class="com.powernode.springmvc.interceptors.Interceptor1"/>
</mvc:interceptors>
```

或：

```xml
<mvc:interceptors>
    <ref bean="interceptor1"/>
</mvc:interceptors>
```

+ 需要添加包扫描
+ 将拦截器使用@Component标注

高级配置：

```xml
<mvc:interceptors>
    <mvc:interceptor>
        <!--拦截所有路径-->
        <mvc:mapping path="/**"/>
        <!--除 /test 路径之外，/test路径不拦截-->
        <mvc:exclude-mapping path="/test"/>
        <!--设置拦截器-->
        <ref bean="interceptor1"/>
    </mvc:interceptor>
</mvc:interceptors>
```

# web.xml配置文件

配置前端控制器：

```xml
<servlet>
    <servlet-name>dispatcherServlet</servlet-name>
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
    <init-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>classpath:springmvc.xml</param-value>
    </init-param>
    <load-on-startup>1</load-on-startup>
</servlet>
<servlet-mapping>
    <servlet-name>dispatcherServlet</servlet-name>
    <url-pattern>/</url-pattern>
</servlet-mapping>
```

+ 表示当请求不是xx.jsp的时候，DispatcherServlet来负责处理本次请求

配置静态资源默认Servlet：

```xml
<servlet>
    <servlet-name>default</servlet-name>
    <servlet-class>org.apache.catalina.servlets.DefaultServlet</servlet-class>
    <init-param>
        <param-name>debug</param-name>
        <param-value>0</param-value>
    </init-param>
    <init-param>
        <param-name>listings</param-name>
        <param-value>false</param-value>
    </init-param>
    <load-on-startup>1</load-on-startup>
</servlet>
<servlet-mapping>
    <servlet-name>default</servlet-name>
    <url-pattern>/</url-pattern>
</servlet-mapping>
```

+ Tomcat自带的web.xml（CATALINA_HOME/conf/web.xml）有一个DefaultServlet可以用来处理静态资源，如果Tomcat没有自带，将一下代码手动写到自己的web.xml文件中也可以
+ 或者使用springmvc.xml配置文件中的`<mvc:default-servlet-handler>` 或 `<mvc:resources>`

配置字符编码过滤器：

```xml
<filter>
    <filter-name>characterEncodingFilter</filter-name>
    <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
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
    <filter-name>characterEncodingFilter</filter-name>
    <url-pattern>/*</url-pattern>
</filter-mapping>
```

配置文件下载：在DispatcherServlet的配置中添加一个属性

```xml
<servlet>
    <servlet-name>dispatcherServlet</servlet-name>
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
    <init-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>classpath:springmvc.xml</param-value>
    </init-param>
    <load-on-startup>1</load-on-startup>
    <multipart-config>
        <!--设置单个支持最大文件的大小-->
        <max-file-size>102400</max-file-size>
        <!--设置整个表单所有文件上传的最大值-->
        <max-request-size>102400</max-request-size>
        <!--设置最小上传文件大小-->
        <file-size-threshold>0</file-size-threshold>
    </multipart-config>
</servlet>
<servlet-mapping>
    <servlet-name>dispatcherServlet</servlet-name>
    <url-pattern>/</url-pattern>
</servlet-mapping>
```

