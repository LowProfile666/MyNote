# 整个完整系统的参与者

对于一个完整的web项目参与者包括：

- Servlet规范的制定者（已有）
- 实现Servlet规范的Tomcat服务器（已有）
- Spring MVC框架的开发者（手写Spring MVC框架）
- 编写webapp的开发者（用Spring MVC框架的人）

# 基本结构搭建

## 创建Maven模块

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712020799342-9ee1720f-5a83-4a2f-b5da-7fccca5b7fca.png#averageHue=%233d4145&clientId=uae70fab4-1447-4&from=paste&height=656&id=u4d017e69&originHeight=656&originWidth=775&originalType=binary&ratio=1&rotation=0&showTitle=false&size=46398&status=done&style=none&taskId=u6d15b9d4-b8a5-4625-8988-b39b6a8c0b4&title=&width=775)

## 引入Servlet依赖

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>org.springmvc</groupId>
    <artifactId>myspringmvc</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>war</packaging>

    <dependencies>
        <!--servlet api-->
        <dependency>
            <groupId>jakarta.servlet</groupId>
            <artifactId>jakarta.servlet-api</artifactId>
            <version>6.0.0</version>
            <scope>provided</scope>
        </dependency>
    </dependencies>

    <properties>
        <maven.compiler.source>21</maven.compiler.source>
        <maven.compiler.target>21</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

</project>
```

## 配置Tomcat服务器

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712020903992-0aae56a0-5652-464c-9b43-bb784f75daf2.png#averageHue=%233e4143&clientId=uae70fab4-1447-4&from=paste&height=62&id=u0581fcfc&originHeight=62&originWidth=257&originalType=binary&ratio=1&rotation=0&showTitle=false&size=2845&status=done&style=shadow&taskId=u12a01a2e-098f-4071-acb2-6820980160b&title=&width=257)
## 添加web支持
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712020961226-61820425-2590-4efe-bad2-6220d08a36ea.png#averageHue=%23404852&clientId=uae70fab4-1447-4&from=paste&height=164&id=u2ff19a4d&originHeight=164&originWidth=234&originalType=binary&ratio=1&rotation=0&showTitle=false&size=5850&status=done&style=shadow&taskId=uce4273cf-4649-429e-857d-a7d213ccfd6&title=&width=234)
```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="https://jakarta.ee/xml/ns/jakartaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="https://jakarta.ee/xml/ns/jakartaee https://jakarta.ee/xml/ns/jakartaee/web-app_6_0.xsd"
         version="6.0">
</web-app>
```

## 创建基本类和接口

先分析一下SpringMVC中有哪些重要的类和接口：

+ DispatcherServlet 类（所有servlet都要实现Servlet接口，或者直接继承HttpServlet，javaWeb规范中的）

+ HandlerExecutionChain 类

+ HandlerMapping 处理器映射器接口

+ RequestMappingHandlerMapping 类（是HandlerMapping接口的实现类，专门为@RequestMapping注解使用的）

+ HandlerMethod 类（处理器方法）

  请求路径通过HandlerMapping映射到这个方法上，这个方法就是HandlerMethod，然后给HandlerExecutionChain处理器执行链中的Object handler 属性

  ![image-20240612151512443](https://gitee.com/LowProfile666/image-bed/raw/master/img/image-20240612151512443.png)、

+ HandlerInterceptor 接口（拦截器接口）

+ HandlerAdapter 接口（处理器适配器接口）

+ RequestMappingHandlerAdapter 类（是HandlerAdapter接口的实现类，专门给@RequestMapping注解使用的）

+ ModelAndView 类

+ ViewResolver 接口

+ InternalResourceViewReslover 类（使用JSP模板引擎）

+ View 接口

+ InternalResourceView 类

+ @Controller 注解

+ @RequestMapping 注解

根据Spring MVC执行流程，目前先创建出以下的类和接口，后期如果需要其他的再添加：

![image-20240612161510460](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406121615582.png)

# 部分类和接口的代码完善

## @Controller注解

用来标注类的，只能出现在类上，可以被反射机制读取。

```java
package org.myspringmvc.stereotype;
/**
 * 用来标注控制器，被标志的控制器纳入Ioc容器管理
 */

@Target(ElementType.TYPE)  // 只能标注类
@Retention(RetentionPolicy.RUNTIME)  // 可以被发射机制读取
public @interface Controller {
}
```

## @RequestMapping注解

能出现在类上，也能出现在方法上，可以被反射机制读取

```java
package org.myspringmvc.web.bind.annotation;
/**
 * 请求映射的注解
 */
@Target({ElementType.TYPE, ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
public @interface RequestMapping {
    String[] value();  // 支持多个请求路径
    RequestMethod method();  // 指定请求方式
}
```

这个RequestMethod是一个枚举类型，需要重新创建。

## RequestMethod枚举（新建）

在package org.myspringmvc.web.bind.annotation包下创建一个枚举类型

```java
package org.myspringmvc.web.bind.annotation;
/**
 * 请求方式枚举
 */
public enum RequestMethod {
    GET, POST
}
```

## HandlerMethod

什么是处理器方法？以下就是一个处理器方法：

```java
@Controller
public class UserController {
    @RequestMapping(value="/",method=RequestMthod.GET)
    public String index() {
        return "index";
    }
}
```

那么一个HandlerMthod应该包括一个处理器（UserController对象），一个方法（Method对象），在SpringMVC源码中，HandlerMethod 中：

![image-20240612165346342](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406121653455.png)

+ 源码中的很复杂

```java
package org.myspringmvc.web.method;

import java.lang.reflect.Method;

/**
 * 处理器方法
 */
public class HandlerMethod {
    /**
     * 处理器对象
     */
    private Object handler;
    /**
     * 要执行的方法
     */
    private Method method;
    public Object getHandler() {
        return handler;
    }

    public void setHandler(Object handler) {
        this.handler = handler;
    }

    public Method getMethod() {
        return method;
    }

    public void setMethod(Method method) {
        this.method = method;
    }

    public HandlerMethod() {
    }

    public HandlerMethod(Object handler, Method method) {
        this.handler = handler;
        this.method = method;
    }
}
```

## HandlerMapping接口

HandlerMapping就是根据请求路径找到要执行的处理方法（HandlerMethod），参考源代码的代码：

```java
HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception;
```

直接复制：

```java
package org.myspringmvc.web.servlet;

/**
 * 处理器映射器，根据请求路径映射到HandlerMethod
 */
public interface HandlerMapping {
    /**
     * 根据请求返回处理器执行链对象
     * @param request 请求对象
     * @return 处理器执行链对象
     * @throws Exception
     */
    HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception;
}
```

## RequestMappingHandlerMapping

这个类实现了HandlerMapping接口，所以要实现方法：

```java
package org.myspringmvc.web.servlet.mvc.method.annotation;
/**
 * 处理器映射器，专门为@RequestMapping注解服务的处理器映射器
 */
public class RequestMappingHandlerMapping implements HandlerMapping {
    @Override
    public HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception {
        return null;
    }
}
```

## HandlerAdapter接口
```java
package org.myspringmvc.web.servlet;
/**
 * 处理器适配器接口
 */
public interface HandlerAdapter {
    /**
     * 调用处理器方法（底层会真正调用处理器方法，执行核心业务）
     * @param request
     * @param response
     * @param handler
     * @return 返回模型和视图对象
     * @throws Exception
     */
    ModelAndView handle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception;
}
```

## RequestMappingHandlerAdapter

这个类是HandlerAdapter接口的实现类，需要实现方法：

```java
package org.myspringmvc.web.servlet.mvc.method.annotation;
/**
 * 处理器适配器，专门为@RequestMapping注解服务的
 */
public class RequestMappingHandlerAdapter implements HandlerAdapter {
    @Override
    public ModelAndView handle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        return null;
    }
}
```

## View接口

```java
package org.myspringmvc.web.servlet;

/**
 * 视图接口
 */
public interface View {
    /**
     * 渲染
     * @param model
     * @param request
     * @param response
     * @throws Exception
     */
    void render(Map<String, ?> model, HttpServletRequest request, HttpServletResponse response)
            throws Exception;
}
```

## InternalResourceView

该类实现了View接口，需要实现方法：

```java
package org.myspringmvc.web.servlet.view;

/**
 * 视图接口的实现类
 */
public class InternalResourceVIew implements View {
    @Override
    public void render(Map<String, ?> model, HttpServletRequest request, HttpServletResponse response) throws Exception {
        
    }
}
```

## ViewResolver接口
```java
package org.myspringmvc.web.servlet;
/**
 * 视图解析器接口
 */
public interface ViewResolver {
    /**
     * 视图解析，将逻辑视图名称转化为物理视图名称，并返回视图对象。
     * @param viewName
     * @param locale
     * @return
     * @throws Exception
     */
    View resolveViewName(String viewName, Locale locale) throws Exception;
}
```

## InternalResourceViewResolver

实现了ViewResolver接口，实现方法：

```java
package org.myspringmvc.web.servlet.view;
/**
 * 内部资源的视图解析器,可以解析JSP
 */
public class InternalResourceViewResolver implements ViewResolver {
    @Override
    public View resolveViewName(String viewName, Locale locale) throws Exception {
        return null;
    }
}
```

## DispatcherServlet

这个是配置在web.xml文件中的，DispatcherServlet对象不需要我们去new，它的方法也不需要我们去调用，创建和调用都是由Tomcat来执行的。Tomcat服务器new了DispactherServlet对象之后，立即调用init(ServletConfig)方法，且这个方法只会被调用一次，之后用户每一次发送请求的时候，只调用DispatcherServlet中的service方法。

init方法只需要重写init()方法，因为会自动调用父类的init(ServletConfig)方法，且这个方法最终还是会调用init()方法。

```java
package org.myspringmvc.web.servlet;
/**
 * 前端控制器
 */
public class DispatcherServlet extends HttpServlet {
    @Override
    public void init() throws ServletException {
        // 初始化Spring web容器
    }

    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doDispatch(req, resp);
    }

    /**
     * DispatcherServlet前端控制器最核心的方法
     * @param request
     * @param response
     * @throws ServletException
     * @throws IOException
     */
    private void doDispatch(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // 处理用户的请求
    }
}
```

## HandlerExecutionChain
```java
package org.myspringmvc.web.servlet;
/**
 * 处理器执行链
 */
public class HandlerExecutionChain {
    /**
     * 处理器方法，实际上底层对象是 HandlerMethod 对象
     */
    private Object handler;

    /**
     * 本次请求需要执行的拦截器
     */
    private List<HandlerInterceptor> interceptors;
	/**
     * 当前拦截器列表执行到了哪个拦截器的下标
     */
    private int interceptorIndex = -1;
    public Object getHandler() {
        return handler;
    }

    public void setHandler(Object handler) {
        this.handler = handler;
    }

    public List<HandlerInterceptor> getInterceptors() {
        return interceptors;
    }

    public void setInterceptors(List<HandlerInterceptor> interceptors) {
        this.interceptors = interceptors;
    }

    public int getInterceptorIndex() {
        return interceptorIndex;
    }

    public void setInterceptorIndex(int interceptorIndex) {
        this.interceptorIndex = interceptorIndex;
    }

    public HandlerExecutionChain() {
    }

    public HandlerExecutionChain(Object handler, List<HandlerInterceptor> interceptors, int interceptorIndex) {
        this.handler = handler;
        this.interceptors = interceptors;
        this.interceptorIndex = interceptorIndex;
    }
}
```

## HandlerInterceptor拦截器接口

```java
package org.myspringmvc.web.servlet;
/**
 * 拦截器接口
 */
public interface HandlerInterceptor {
    default boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        return true;
    }

    default void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, odelAndView modelAndView) throws Exception {
    }

    default void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
    }
}
```

## ModelAndView

ModelAndView 中有两个属性：View和ModelMap

```java
package org.myspringmvc.web.servlet;

/**
 * 模型和视图
 */
public class ModelAndView {
    private Object View;
    private ModelMap modelMap;

    public Object getView() {
        return View;
    }

    public void setView(Object view) {
        View = view;
    }

    public ModelMap getModelMap() {
        return modelMap;
    }

    public void setModelMap(ModelMap modelMap) {
        this.modelMap = modelMap;
    }

    public ModelAndView() {
    }

    public ModelAndView(Object view, ModelMap modelMap) {
        View = view;
        this.modelMap = modelMap;
    }
}
```

## ModelMap类（新建）

查看源码中的ModelMap，就是一个Map集合的应用，很简单：

![image-20240612173430302](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406121734437.png)

新建一个包org.myspringmvc.ui：

```java
package org.myspringmvc.ui;

public class ModelMap extends LinkedHashMap<String, Object> {
    public ModelMap() {
    }

    /**
     * 向域中绑定数据
     * @param name
     * @param value
     * @return
     */
    public ModelMap addAttribute(String name, String value){
        this.put(name, value);
        return this;
    }
}
```

# webapp开发者写应用

在webapp开发者的角度，去使用myspringmvc框架。

## web.xml文件
```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="https://jakarta.ee/xml/ns/jakartaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="https://jakarta.ee/xml/ns/jakartaee https://jakarta.ee/xml/ns/jakartaee/web-app_6_0.xsd"
         version="6.0">
    
    <!--配置前端控制器-->
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.myspringmvc.web.servlet.DispatcherServlet</servlet-class>
        <!--这个init-param的数据在ServletConfig对象中-->
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <!--表示springmvc.xml是从类路径开始查找，表示类的根路径下有个springmvc.xml文件-->
            <param-value>classpath:springmvc.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
    <servlet-mapping>
        <servlet-name>springmvc</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
    
</web-app>
```

## 编写springmvc.xml

```xml
<?xml version="1.0" encoding="UTF-8" ?>

<beans>
<!--    组件扫描-->
    <component-scan base-package="com.zsm.controller"/>
<!--    视图解析器-->
    <bean class="org.myspringmvc.web.servlet.view.InternalResourceViewResolver">
        <property name="prefix" value="/WEB-INF/jsp/"/>
        <property name="suffix" value=".jsp"/>
    </bean>
<!--    拦截器-->
    <interceptors>
        <bean class="com.zsm.interceptors.Interceptor1"/>
        <bean class="com.zsm.interceptors.Interceptor2"/>
    </interceptors>
</beans>
```

视图解析器中有两个属性，要在InternalResourceViewResolver类中添加属性：suffix和prefix

```java
package org.myspringmvc.web.servlet.view;
/**
 * 内部资源的视图解析器,可以解析JSP
 */
public class InternalResourceViewResolver implements ViewResolver {
    private String prefix;
    private String suffix;

    public String getPrefix() {
        return prefix;
    }

    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }

    public String getSuffix() {
        return suffix;
    }

    public void setSuffix(String suffix) {
        this.suffix = suffix;
    }

    public InternalResourceViewResolver() {
    }

    public InternalResourceViewResolver(String prefix, String suffix) {
        this.prefix = prefix;
        this.suffix = suffix;
    }

    @Override
    public View resolveViewName(String viewName, Locale locale) throws Exception {
        return null;
    }
}
```

## 编写拦截器

需要新建一个com.zsm.controller包和一个com.zsm.interceptors包，并且在interceptors下创建几个拦截器：

```java
package com.zsm.interceptors;

public class Interceptor1 implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        System.out.println("Interceptor1's preHandle");
        return true;
    }

    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        System.out.println("Interceptor1's postHandle");
    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        System.out.println("Interceptor1's afterCompletion");
    }
}
```

## 编写处理器Controller

```java
package com.zsm.controller;
@Controller
public class UserController {
    @RequestMapping(value = "/index", method = RequestMethod.GET)
    public String index() {
        return "index";
    }
}
```

## 提供视图

在WEB-INF下新加一个jsp文件夹，创建一个index.jsp文件：

```jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>zsm手写SpringMVC</title>
</head>
<body>
<h1>哈哈哈哈</h1>
</body>
```

# 服务器启动阶段的处理

## 如何找到配置文件

首先要让DispatcherServlet能找到springmvc.xml文件，只能通过web.xml中的配置来找：

```xml
<init-param>
    <param-name>contextConfigLocation</param-name>
    <param-value>classpath:springmvc.xml</param-value>
</init-param>
```

以上信息会被封装到ServletConfig对象里面，这个ServletConfig对象不需要自己创建，Tomcat服务器已经创建好了，并且Tomcat调用init方法的时候会自动将创建好的ServletConfig对象传递给init方法。要在DispatcherServlet类中的init方法中编写代码：

```java
@Override
public void init() throws ServletException {
    // 获取ServletConfig对象（Servlet配置信息对象，该对象由web容器自动创建，并且将其传递给init方法）
    ServletConfig servletConfig = this.getServletConfig();
    // 获取配置springmvc.xml文件路径的值
    String contextConfigLocation = servletConfig.getInitParameter("contextConfigLocation"); 
}
```

这里的这个名字contextConfigLocation是写死的，一般用一个常量来代替，所以可以创建一个常量类，用来表示系统中的所有的常量。在org.myspringmvc.web下新建一个包constant，包中新建一个类Const：

```java
public class Const {
    /**
     * web.xml文件中配置DispatcherServlet的初始化参数的contextConfigLocation的名字
     */
    public static final String CONTEXT_CONFIG_LOCATION = "contextConfigLocation";
}
```

然后接着写init方法：

```java
public void init() throws ServletException {
    // 获取ServletConfig对象（Servlet配置信息对象，该对象由web容器自动创建，并且将其传递给init方法）
    ServletConfig servletConfig = this.getServletConfig();
    // 获取配置springmvc.xml文件路径的值
    String contextConfigLocation = servletConfig.getInitParameter(Const.CONTEXT_CONFIG_LOCATION);
    System.out.println("spirngmvc: " + contextConfigLocation);
}
```

这时候启动服务器就可以看到输出：

![image-20240612200034675](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406122002644.png)

接着判断这个路径是不是以classpath:开始，以这个开始表示从类的根路径开始查找，同时在Const类中将这个“classpath:”字符串也定义成一个常量：

```java
/**
     * contextConfigLocation的前缀
     */
public static final String PREFIX_CLASSPATH = "classpath:";v
```

在DispatcherServlet类中查找：

```java
if (contextConfigLocation.trim().startsWith(Const.PREFIX_CLASSPATH)) {
    // 表示这个配置文件要从类的路径当中查找
    // 从类路径中找：
    String springMvcConfigPath = Thread.currentThread().getContextClassLoader().getResource("springmvc.xml").getPath();
    System.out.println("springMvcConfigPath--->" + springMvcConfigPath);
}
```

![image-20240613101728389](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406131017581.png)

那么这个“springmvc.xml”名字不应该写死，而是从contextConfigLocation中截取出来：

```java
String springMvcConfigPath = Thread.currentThread().getContextClassLoader().getResource(contextConfigLocation.substring(Const.PREFIX_CLASSPATH.length())).getPath();
```

这样就是通用的了，可以在web.xml中随便配置名字。

如果路径中有空格或中文的话，会出现编码的问题，解决编码的问题：

```java
springMvcConfigPath = URLDecoder.decode(springMvcConfigPath, Charset.defaultCharset());
```

+ URLDecoder是解码，第一个参数要解码的字符串，第二个参数是指定字符集，Charset.defaultCharset()是当前JDK的字符集，默认是UTF-8

## 分析服务器启动阶段都需要初始化什么

1. 初始化Spring容器
   1. 组件扫描包下的类纳入IoC容器的管理。
   2. 创建视图解析器对象
   3. 创建所有的拦截器对象
   4. 扫描这个包下所有的类：org.myspringmvc.web.servlet.mvc.method.annotation，全部实例化，纳入IoC容器管理
2. 初始化HandlerMapping
3. 初始化HandlerAdapter
4. 初始化ViewResolver

## 初始化Spring容器

接着要初始化Spring Web容器：

+ Spring容器：ApplicationContext（普通的Java项目使用Spring的话就会创建ApplicationContext对象）
+ Spring Web容器：WebApplicationContext（继承自ApplicationContext，多了个ServletContext属性，web项目专属的）

也就是要将所有的要创建的bean都创建出来，然后放在容器中，容器是以map集合的方式存储，key是bean的id或名字，value是bean对象。

接下来就是将springmvc.xml中配置的组件扫描、视图解析器和拦截器初始化到容器中，还要初始化处理器适应器和处理器映射器。

创建一个包org.myspringmvc.context，在包下创建出ApplicationContext类，里面有个map集合用来存储所有的bean，还有一个通过map集合的key来获取bean的方法：

```java
package org.myspringmvc.context;
/**
 * Spring的IoC容器，Spring上下文，适合于普通的java项目
 */
public class ApplicationContext {
    private Map<String, Object> beanMap = new HashMap<>();

    public ApplicationContext(String xmlPath) {
        // 解析xml文件
        // 组件扫描
        // 创建视图解析器
        // 创建拦截器
        // 创建org.myspringmvc.web.servlet.mvc.method.annotation下的所有HandlerAdapter
        // 创建org.myspringmvc.web.servlet.mvc.method.annotation下的所有HandlerMapping
    }

    /**
     * 通过beanName获取对应的bean
     * @param beanName
     * @return
     */
    public Object getBean(String beanName) {
        return beanMap.get(beanName);
    }
}
```

创建一个包org.myspringmvc.web.context，在包下创建出WebApplicationContext类，继承自ApplicationContext类，且有一个自己的ServletContext，以及用来指定springmvc配置文件的属性：

```java
package org.myspringmvc.web.context;
public class WebApplicationContext extends ApplicationContext {
    private ServletContext servletContext;
    private String springMvcConfigPath;

    public WebApplicationContext(ServletContext servletContext, String springMvcConfigPath) {
        super(springMvcConfigPath);
        this.servletContext = servletContext;
    }

    public ServletContext getServletContext() {
        return servletContext;
    }

    public void setServletContext(ServletContext servletContext) {
        this.servletContext = servletContext;
    }

    public String getSpringMvcConfigPath() {
        return springMvcConfigPath;
    }

    public void setSpringMvcConfigPath(String springMvcConfigPath) {
        this.springMvcConfigPath = springMvcConfigPath;
    }
}
```

然后在DispatcherServlet中继续初始化容器，创建WebApplicationContext对象：

```java
WebApplicationContext webApplicationContext = new WebApplicationContext(this.getServletContext(), contextConfigLocation);
```

webApplicationContext代表的就是Spring Web容器，我们最好将其存储到Servlet上下文中，以便后期的使用：

```java
this.getServletContext().setAttribute("webApplicationContext", webApplicationContext);
```

这里有个常量，将这个常量定义在Const类中：

```java
public static final String WEB_APPLICATION_CONTEXT = "webApplicationContext";
```

然后使用：

```java
this.getServletContext().setAttribute(Const.WEB_APPLICATION_CONTEXT, webApplicationContext);
```

### 解析xml文件

先添加解析xml文件的依赖

```xml
<!--dom4j-->
<dependency>
    <groupId>dom4j</groupId>
    <artifactId>dom4j</artifactId>
    <version>1.6.1</version>
</dependency>
<!--jaxen-->
<dependency>
    <groupId>jaxen</groupId>
    <artifactId>jaxen</artifactId>
    <version>1.1.6</version>
</dependency>
```

然后实现ApplicationContext中的代码：

```java
public class ApplicationContext {
    private Map<String, Object> beanMap = new HashMap<>();

    public ApplicationContext(String xmlPath) {
        try {
            // 解析xml文件
            SAXReader reader = new SAXReader();
            Document document = reader.read(new File(xmlPath));  // 这个document就是spingmvc.xml文件
            // 组件扫描
            Element componentScanElement = (Element) document.selectSingleNode("/beans/component-scan");
            componentScan(componentScanElement);

            // 创建视图解析器
            Element viewResloverElement = (Element) document.selectSingleNode("/beans/bean");
            createViewResolver(viewResloverElement);

            // 创建拦截器
            Element interceptorsElement = (Element) document.selectSingleNode("/beans/interceptors");
            createInterceptors(interceptorsElement);

            // 创建org.myspringmvc.web.servlet.mvc.method.annotation下的所有HandlerAdapter
            // 将包名传过去，包名定为了常量
            createHandlerAdapter(Const.DEFAULT_PACKAGE);

            // 创建org.myspringmvc.web.servlet.mvc.method.annotation下的所有HandlerMapping
            createHandlerMapping(Const.DEFAULT_PACKAGE);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void createHandlerAdapter(String defaultPackage) {
    }

    private void createHandlerMapping(String defaultPackage) {
        
    }

    private void createViewResolver(Element viewResloverElement) {
        
    }

    private void createInterceptors(Element interceptorsElement) {
        
    }

    private void componentScan(Element componentScanElement) {
        
    }

    /**
     * 通过beanName获取对应的bean
     * @param beanName
     * @return
     */
    public Object getBean(String beanName) {
        return beanMap.get(beanName);
    }
}
```

### 组件扫描

获取到springmvc.xml文件中<component-scan>标签中的包名，拿到包中所有的类，再看每个类上是否有@Controller注解，如果有则创建出对象，放到spring容器（beanMap）中。

```java
private void componentScan(Element componentScanElement) throws Exception {
    // 获取包名，将属性“base-package”变成常量
    String basePackage = componentScanElement.attributeValue(Const.BASE_PACKAGE);
    System.out.println("组件扫描的包：" + basePackage);
    // 获取包的路径，将包名中的.换成/
    String basePath = basePackage.replace(".", "/");
    System.out.println("包对应的路径：" + basePath);
    // 获取包的绝对路径
    String absolutePath = Thread.currentThread().getContextClassLoader().getResource(basePath).getPath();
    System.out.println("包的绝对路径：" + absolutePath);
    // 封装成File对象
    File file = new File(absolutePath);
    // 获取该目录下所有的子文件
    File[] files = file.listFiles();
    for (File f : files) {
        String className = f.getName();
        System.out.println("类的名字：" + className);
        // 判断文件的名字是不是以.class结尾的，将".class"字符串写为一个常量
        if (f.getName().endsWith(Const.SUFFIX_CLASS)) {
            // 是的话，只需要拿到文件名，不需要后缀名
            String simpleClassName = className.substring(0,className.lastIndexOf('.'));
            System.out.println("简单类名：" + simpleClassName);
            // 完整类名
            className = basePackage + "." + simpleClassName;
            System.out.println("完整类名：" + className);

            // 如果类上有@Controller注解，则创建Controller对象，加入IoC容器
            Class<?> clazz = Class.forName(className);
            if (clazz.isAnnotationPresent(Controller.class)) {
                // 创建controller对象
                Object bean = clazz.newInstance();
                // 将其存储到IoC容器中，
                // 这个key取决于@Controller注解中指定的名字，如果没有，则是将类名首字母小写作为key
                beanMap.put(toFirstLower(simpleClassName), bean);
            }
        }
    }
}
```
测试结果：

![image-20240613154658453](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406131619092.png)

### 创建视图解析器对象

springmvc.xml文件中配置的视图解析器：

```xml
<bean class="org.myspringmvc.web.servlet.view.InternalResourceViewResolver">
    <property name="prefix" value="/WEB-INF/jsp/"/>
    <property name="suffix" value=".jsp"/>
</bean>
```

需要创建出InternalResourceViewResolver对象，并且给对象的prefix和suffix属性赋值：

```java
private void createViewResolver(Element viewResloverElement) throws Exception {
    // 获取viewResloverElement的class属性，也就是类名，将这个“class”字符串写为常量
    String className = viewResloverElement.attributeValue(Const.BEAN_TAG_CLASS_ATTRIBUTE);
    System.out.println("视图解析器的名字：" + className);
    // 创建对象
    Class<?> clazz = Class.forName(className);
    // 视图解析器对象
    Object bean = clazz.newInstance();
    // 需要给对象的suffix和prefix属性赋值，调用set方法
    // 先获取当前bean节点下的子节点property,"property"也定位常量
    List<Element> propertyElements = viewResloverElement.elements(Const.PROPERTY_TAG_NAME);
    // 获取每个property的name和value属性值，"name"、"value"都定位常量
    for (Element propertyElement : propertyElements) {
        String fieldName = propertyElement.attributeValue(Const.PROPERTY_NAME);
        String fieldValue = propertyElement.attributeValue(Const.PROPERTY_VALUE);
        System.out.println("属性名：" + fieldName);
        System.out.println("属性值：" + fieldValue);

        // 将属性名转为set方法名
        String setMethodName = fieldNameToSetMethodName(fieldName);
        System.out.println("set方法名：" + setMethodName);

        // 通过方法名获取方法
        Method setMethod = clazz.getDeclaredMethod(setMethodName, String.class);
        // 通过反射机制调用方法
        setMethod.invoke(bean, fieldValue);
    }
    // 添加到IoC容器
    // 为了更方便的访问，将key设为一个常量“viewSolver”
    beanMap.put(Const.VIEW_RESOLVER, bean);
}
```

测试结果：

![image-20240613160726390](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406131620251.png)

### 创建所有的拦截器对象

在springmvc.xml文件中配置的拦截器对象：

```xml
<interceptors>
    <bean class="com.zsm.interceptors.Interceptor1"/>
    <bean class="com.zsm.interceptors.Interceptor2"/>
</interceptors>
```

要将配置的拦截器对象都创建出来，放到一个List集合中，然后将这个List集合放到beanMap中：

```java
private void createInterceptors(Element interceptorsElement) throws Exception {
    // 准备一个List集合存储拦截器对象
    List<HandlerInterceptor> interceptors = new ArrayList<>();

    // 获取该标签下的所有的bean标签
    List<Element> beans = interceptorsElement.elements("bean");
    // 遍历bean标签
    for  (Element beanElement : beans) {
        // 获取bean标签中的class属性，获取到类名
        String className = beanElement.attributeValue(Const.BEAN_TAG_CLASS_ATTRIBUTE);
        // 通过反射机制创建对象
        Class<?> clazz = Class.forName(className);
        Object interceptor = clazz.newInstance();
        interceptors.add((HandlerInterceptor) interceptor);
    }
    // 存储到IoC容器中
    // 方便取，给key定义个常量
    beanMap.put(Const.INTERCEPTORS, interceptors);
}
```

测试效果：

![image-20240613163322768](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406131633939.png)

### 初始化annotation包下所有类的实例

createHandlerAdapter：

```java
private void createHandlerAdapter(String defaultPackage) throws Exception {
    // 将包名中的.换成/，变成路径
    String defaultPath = defaultPackage.replace(".", "/");
    System.out.println("defaultPath ：" + defaultPath);
    // 获取绝对路径
    String absolutePath = Thread.currentThread().getContextClassLoader().getResource(defaultPath).getPath();
    absolutePath = URLDecoder.decode(absolutePath, Charset.defaultCharset());
    System.out.println("绝对路径：" + absolutePath);
    // 封装成一个File对象
    File file = new File(absolutePath);
    // 获取包下所有文件
    File[] files = file.listFiles();
    for (File f : files) {
        // 获取文件名字
        String classFileName = f.getName();
        System.out.println("classFileName ：" + classFileName);
        // 获取简单类名
        String simpleClassName = classFileName.substring(0, classFileName.lastIndexOf('.'));
        System.out.println("simpleClassName : " + simpleClassName);
        // 获取完整类名
        String className = defaultPackage + "." + simpleClassName;
        System.out.println("className ： " + className);
        // 获取class
        Class<?> clazz = Class.forName(className);
        // 只有实现了HandlerAdapter接口的，再创建对象
        if (HandlerAdapter.class.isAssignableFrom(clazz)) {
            Object bean = clazz.newInstance();
            // 放入容器
            beanMap.put(Const.HANDLER_ADAPTER, bean);
            return;
        }
    }
}
```

createHandlerMapping：

```java
private void createHandlerMapping(String defaultPackage) throws Exception {
    // 将包名中的.换成/，变成路径
    String defaultPath = defaultPackage.replace(".", "/");
    System.out.println("defaultPath ：" + defaultPath);
    // 获取绝对路径
    String absolutePath = Thread.currentThread().getContextClassLoader().getResource(defaultPath).getPath();
    absolutePath = URLDecoder.decode(absolutePath, Charset.defaultCharset());
    System.out.println("绝对路径：" + absolutePath);
    // 封装成一个File对象
    File file = new File(absolutePath);
    // 获取包下所有文件
    File[] files = file.listFiles();
    for (File f : files) {
        // 获取文件名字
        String classFileName = f.getName();
        System.out.println("classFileName ：" + classFileName);
        // 获取简单类名
        String simpleClassName = classFileName.substring(0, classFileName.lastIndexOf('.'));
        System.out.println("simpleClassName : " + simpleClassName);
        // 获取完整类名
        String className = defaultPackage + "." + simpleClassName;
        System.out.println("className ： " + className);
        // 获取class
        Class<?> clazz = Class.forName(className);
        // 只有实现了HandlerMapping接口的，再创建对象
        if (HandlerMapping.class.isAssignableFrom(clazz)) {
            Object bean = clazz.newInstance();
            // 放入容器
            beanMap.put(Const.HANDLER_MAPPING, bean);
            return;
        }
    }
}
```

结果：

![image-20240613165103966](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406131651254.png)

## 初始化ViewResolver、HandlerMapping、HandlerAdapter

在DispatcherServlet中的doDispatch方法里，需要用到视图解析器等，所以要先定义属性：

```java
/**
     * 视图解析器，做页面解析的
     */
private ViewResolver viewResolver;
/**
     * 处理器映射器，通过请求路径找处理器的
     */
private HandlerMapping handlerMapping;
/**
     * 处理器适配器，调用处理器方法的
     */
private HandlerAdapter handlerAdapter;
```

属性定义好后，要初始化，在初始化Spring容器之后：

```java
// 初始化视图解析器
this.viewResolver = (ViewResolver) webApplicationContext.getBean(Const.VIEW_RESOLVER);
// 初始化处理器适配器
this.handlerAdapter = (HandlerAdapter) webApplicationContext.getBean(Const.HANDLER_ADAPTER);
// 初始化处理器映射器
this.handlerMapping = (HandlerMapping) webApplicationContext.getBean(Const.HANDLER_MAPPING);
```

# 根据请求流程补充代码

七个流程：

1. 根据请求对象获取对应的处理器执行链对象
2. 根据”处理器方法“获取对应的处理器适配器对象
3. 执行拦截器中的preHandle方法
4. 执行处理器方法，并返回ModelAndView
5. 执行拦截器中的postHandle方法
6. 响应
7. 执行拦截器中的afterCompletion方法

## 根据请求获取处理器执行链

处理器映射器通过前端提交的”请求“，来映射底层要执行的HandlerMethod。前端提交的信息包括：请求路径、请求方式。所以可以将请求路径和方式包装成一个对象RequestMappingInfo，然后将底层要执行的HandleMethod合在一起，看成一个map集合Map<RequestMappingInfo, HandleMethod>，这个map集合可以作为RequestMappingHandlerMaping的属性。

重新创建一个类，在org.myspringmvc.web.servlet.mvc包下：

```java
package org.myspringmvc.web.servlet.mvc;
/**
 * 请求映射信息，包含请求路径、请求方式……
 */
public class RequestMappingInfo {
    private String requestURI;
    private String method;

    public String getRequestURI() {
        return requestURI;
    }

    public void setRequestURI(String requestURI) {
        this.requestURI = requestURI;
    }

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }

    public RequestMappingInfo(String requestURI, String method) {
        this.requestURI = requestURI;
        this.method = method;
    }

    public RequestMappingInfo() {
    }
}
```
然后在RequestMappingHandlerMapping类中创建一个Map属性，并在初始化的时候初始化：

```java
public class RequestMappingHandlerMapping implements HandlerMapping {
    /**
     * 处理器映射器，主要就是通过以下的map集合进行映射
     * key：请求信息
     * vlaue：该请求信息要执行的处理器方法
     */
    private Map<RequestMappingInfo, HandlerMethod> map;

    /**
     * 创建HandlerMapping对象时，给map赋值
     * @param map
     */
    public RequestMappingHandlerMapping(Map<RequestMappingInfo, HandlerMethod> map) {
        this.map = map;
    }

    @Override
    public HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception {
        return null;
    }
}
```

但是在这前的代码中，使用的是该类的无参构造方法来创建对象，但是使用无参构造方法创建对象时又没有办法给map属性赋值，所以，在服务器启动的时候创建所有的HandlerMethod，将其存储在map集合中。

而HandlerMethod在controller类中，所以可以在进行包扫描的时候就创建所有的HandlerMthod类，让componentScan方法返回一个map集合，再将这个map集合传到createHandlerMapping中，在ApplicationContext类中的构造方法中：

![image-20240613211437041](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406132114262.png)

```java
Map<RequestMappingInfo, HandlerMethod> map = componentScan(componentScanElement);
createHandlerMapping(Const.DEFAULT_PACKAGE, map);
```

在createHandlerMapping方法中，使用有参构造方法创建实例：

![image-20240613211536412](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406132115606.png)

```java
Constructor<?> con = clazz.getDeclaredConstructor(Map.class);
Object bean = con.newInstance(map);
```

然后修改componentScan方法：

```java
private Map<RequestMappingInfo, HandlerMethod> componentScan(Element componentScanElement) throws ClassNotFoundException, InstantiationException, IllegalAccessException {
    // 创建处理器映射器大Map
    Map<RequestMappingInfo, HandlerMethod> map = new HashMap<>();
    // 获取包名，将属性“base-package”变成常量
    String basePackage = componentScanElement.attributeValue(Const.BASE_PACKAGE);
    System.out.println("组件扫描的包：" + basePackage);
    // 获取包的路径，将包名中的.换成/
    String basePath = basePackage.replace(".", "/");
    System.out.println("包对应的路径：" + basePath);
    // 获取包的绝对路径
    String absolutePath = Thread.currentThread().getContextClassLoader().getResource(basePath).getPath();
    System.out.println("包的绝对路径：" + absolutePath);
    // 封装成File对象
    File file = new File(absolutePath);
    // 获取该目录下所有的子文件
    File[] files = file.listFiles();
    for (File f : files) {
        String className = f.getName();
        System.out.println("类的名字：" + className);
        // 判断文件的名字是不是以.class结尾的，将".class"字符串写为一个常量
        if (f.getName().endsWith(Const.SUFFIX_CLASS)) {
            // 是的话，只需要拿到文件名，不需要后缀名
            String simpleClassName = className.substring(0,className.lastIndexOf('.'));
            System.out.println("简单类名：" + simpleClassName);
            // 完整类名
            className = basePackage + "." + simpleClassName;
            System.out.println("完整类名：" + className);

            // 如果类上有@Controller注解，则创建Controller对象，加入IoC容器
            Class<?> clazz = Class.forName(className);
            if (clazz.isAnnotationPresent(Controller.class)) {
                // 创建controller对象
                Object bean = clazz.newInstance();
                // 将其存储到IoC容器中，
                // 这个key取决于@Controller注解中指定的名字，如果没有，则是将类名首字母小写作为key
                beanMap.put(toFirstLower(simpleClassName), bean);
                // 创建这个bean中的所有HandlerMethod对象，将其放到map集合中
                // 获取类中所有的方法
                Method[] methods = clazz.getMethods();
                for (Method method : methods) {
                    if (method.isAnnotationPresent(RequestMapping.class)) {
                        // 如果被@RequestMapping注解标注了
                        // 获取注解
                        RequestMapping requestMapping = method.getAnnotation(RequestMapping.class);
                        // 创建RequestMappingIngo对象
                        RequestMappingInfo requestMappingInfo = new RequestMappingInfo();
                        requestMappingInfo.setRequestURI(requestMapping.value()[0]);
                        requestMappingInfo.setMethod(requestMapping.method().toString());
                        // 创建HandlerMethod对象
                        HandlerMethod handlerMethod = new HandlerMethod();
                        handlerMethod.setHandler(bean);
                        handlerMethod.setMethod(method);
                        // 放到map集合
                        map.put(requestMappingInfo, handlerMethod);
                    }
                }
            }
        }
    }
    return map;
}
```

接着要实现这个getHandler方法：

```java
public HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception {
    // 通过request对象，获取请求路径、方式，封装成RequestMappingInfo对象
    RequestMappingInfo requestMappingInfo = new RequestMappingInfo(request.getServletPath(), request.getMethod());

    // 创建处理器执行对象
    HandlerExecutionChain handlerExecutionChain = new HandlerExecutionChain();

    // 给执行链设置HandleMethod
    handlerExecutionChain.setHandler(map.get(requestMappingInfo));

    // 获取所有拦截器
    WebApplicationContext webApplicationContext = (WebApplicationContext) request.getServletContext().getAttribute(Const.WEB_APPLICATION_CONTEXT);
    List<HandlerInterceptor> interceptors = (List<HandlerInterceptor>) webApplicationContext.getBean(Const.INTERCEPTORS);
    // 给执行链设置拦截器
    handlerExecutionChain.setInterceptors(interceptors);

    return handlerExecutionChain;
}
```

在这里有个细节，同一个请求new两次RequestMappingInfo的话，如果不重写hashCode和equals方法，那么就会new出两个对象，但是同一个请求应该只有一个对象，所以在RequestMappingInfo类中，应该重写hashCode和equals方法：

```java
@Override
public int hashCode() {
    return Objects.hash(requestURI, method);
}

@Override
public boolean equals(Object obj) {
    if (this == obj) return true;
    if (obj == null || getClass() != obj.getClass()) return false;
    RequestMappingInfo that = (RequestMappingInfo) obj;
    return Objects.equals(requestURI, that.requestURI) && Objects.equals(method, that.method);
}
```

## 执行拦截器的preHandle

添加以下代码：

```java
if (!mappedHandler.applyPreHandle(request, response)) return;
```

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712056664132-90f25f97-bc21-4aff-851b-63d222974148.png#averageHue=%232e2b2b&clientId=uae70fab4-1447-4&from=paste&height=310&id=u1b97258b&originHeight=310&originWidth=1330&originalType=binary&ratio=1&rotation=0&showTitle=false&size=38297&status=done&style=shadow&taskId=u608791fc-8147-4e21-a40d-f9ee94bf3a9&title=&width=1330)

HandlerExecutionChain添加以下代码：
```java
/**
     * 执行所有拦截器的preHandler放啊
     * @param request
     * @param response
     * @return
     */
public boolean applyPreHandle(HttpServletRequest request, HttpServletResponse response) throws Exception {
    // 遍历拦截器
    for (int i = 0; i < interceptors.size(); i++) {
        // 取出每一个拦截器对象
        HandlerInterceptor handlerInterceptor = interceptors.get(i);
        // 调用preHandle方法
        boolean res = handlerInterceptor.preHandle(request, response, handler);
        // 根据执行结果，如果false，表示不再执行
        if (!res) return false;
    }
    return true;
}
```

## 执行处理器方法

DispatcherServlet中的doDispatch方法：

```java
ModelAndView mv = ha.handle(request, response, mappedHandler.getHandler());
```

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068532880-a22a29f7-6acf-44da-9c2e-016aa01f3756.png#averageHue=%232d2c2b&clientId=uae70fab4-1447-4&from=paste&height=111&id=ued28d3e9&originHeight=111&originWidth=1395&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23777&status=done&style=shadow&taskId=u39d0417d-154d-4f5b-b690-a75fc10f3ee&title=&width=1395)

先让handle方法返回一个固定的ModelAndView，后期在详细编写 handle 方法：

```java
public class RequestMappingHandlerAdapter implements HandlerAdapter {
    @Override
    public ModelAndView handle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setView("index");
        modelAndView.setModelMap(null);
        return modelAndView;
    }
}
```

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712066826429-45d064ef-6649-4b7d-a504-b485143f87b6.png#averageHue=%232d2c2c&clientId=uae70fab4-1447-4&from=paste&height=307&id=u32db08a6&originHeight=307&originWidth=1285&originalType=binary&ratio=1&rotation=0&showTitle=false&size=41136&status=done&style=shadow&taskId=u4fc49120-5b20-4ddc-a4a3-07c0f698a17&title=&width=1285)


## 执行拦截器的postHandle
DispatcherServlet的doDispatch方法中：

```java
mappedHandler.applyPostHandle(request, response, mv);
```

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712067006139-fe7993eb-1745-4653-92c1-173b31254417.png#averageHue=%232c2c2b&clientId=uae70fab4-1447-4&from=paste&height=102&id=u3184c834&originHeight=102&originWidth=899&originalType=binary&ratio=1&rotation=0&showTitle=false&size=8558&status=done&style=shadow&taskId=udf523c3b-d13b-4215-a019-869c84d9bf1&title=&width=899)

HandlerExecutionChain的方法：

```java
/**
     * 按照逆序的方式执行拦截器中的postHandle方法
     * @param request
     * @param response
     * @param mv
     */
public void applyPostHandle(HttpServletRequest request, HttpServletResponse response, ModelAndView mv) throws Exception {
    for (int i = interceptors.size() - 1; i >= 0; i--) {
        HandlerInterceptor handlerInterceptor = interceptors.get(i);
        handlerInterceptor.postHandle(request, response, handler, mv);
    }
}
```

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068684534-c19e8af2-4a17-4997-8e5a-3c478fa95854.png#averageHue=%232c2c2b&clientId=uae70fab4-1447-4&from=paste&height=200&id=uc5a62c6f&originHeight=200&originWidth=1421&originalType=binary&ratio=1&rotation=0&showTitle=false&size=33486&status=done&style=shadow&taskId=ud5c81bf5-682b-47b4-9204-33cd11509f6&title=&width=1421)


## 处理响应
在DispatcherServlet的 doDispatch方法中：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712067254904-79ff05f1-b27e-457a-8c43-a5999d8c47d7.png#averageHue=%232d2c2b&clientId=uae70fab4-1447-4&from=paste&height=102&id=uf2356e65&originHeight=102&originWidth=843&originalType=binary&ratio=1&rotation=0&showTitle=false&size=14239&status=done&style=shadow&taskId=u3f815fbf-e0dc-46b7-a010-e320d5862bb&title=&width=843)

```java
package org.myspringmvc.web.servlet.view;

import org.myspringmvc.web.servlet.View;
import org.myspringmvc.web.servlet.ViewResolver;

import java.util.Locale;

/**
 * ClassName: InternalResourceViewResolver
 * Description:
 * Datetime: 2024/4/2 9:45
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class InternalResourceViewResolver implements ViewResolver {
    private String suffix;
    private String prefix;

    public String getSuffix() {
        return suffix;
    }

    public void setSuffix(String suffix) {
        this.suffix = suffix;
    }

    public String getPrefix() {
        return prefix;
    }

    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }

    @Override
    public View resolveViewName(String viewName, Locale locale) throws Exception {
        return new InternalResourceView("text/html;charset=UTF-8", prefix + viewName + suffix);
    }
}

```
![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=zFXk0&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
```java
package org.myspringmvc.web.servlet.view;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.myspringmvc.web.servlet.View;

import java.util.Map;

/**
 * ClassName: InternalResourceView
 * Description:
 * Datetime: 2024/4/2 10:17
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class InternalResourceView implements View {

    private String contentType;
    private String path;

    public InternalResourceView(String contentType, String path) {
        this.contentType = contentType;
        this.path = path;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public void setContentType(String contentType) {
        this.contentType = contentType;
    }

    @Override
    public String getContentType() {
        return contentType;
    }

    @Override
    public void render(Map<String, ?> model, HttpServletRequest request, HttpServletResponse response) throws Exception {
        // 设置响应内容类型
        response.setContentType(getContentType());
        // 向request域中绑定数据
        if(model != null){
            model.forEach(request::setAttribute);    
        }
        // 转发
        request.getRequestDispatcher(path).forward(request, response);
    }
}

```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=x9G5Q&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 执行拦截器的afterCompletion
在DispatcherServlet类的doDispatch方法中：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068193170-1b47284d-c42d-45a5-ae1b-a729794a105c.png#averageHue=%232e2d2c&clientId=uae70fab4-1447-4&from=paste&height=66&id=uac12270b&originHeight=66&originWidth=965&originalType=binary&ratio=1&rotation=0&showTitle=false&size=9628&status=done&style=shadow&taskId=u6555a2d4-220e-4fcf-a729-b613b001899&title=&width=965)

在HandlerExecutionChain中：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068259935-ea02fdbe-ff19-4662-ad8c-eb349c269bf1.png#averageHue=%232d2c2c&clientId=uae70fab4-1447-4&from=paste&height=206&id=u04e5515e&originHeight=206&originWidth=1450&originalType=binary&ratio=1&rotation=0&showTitle=false&size=30726&status=done&style=shadow&taskId=u98cb9e46-ed3e-4ded-b726-d1e67451a4a&title=&width=1450)

![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068277775-336dda1a-e26c-4d37-84af-545bb818f0c9.png#averageHue=%232d2b2b&clientId=uae70fab4-1447-4&from=paste&height=362&id=u3d9d44a7&originHeight=362&originWidth=1287&originalType=binary&ratio=1&rotation=0&showTitle=false&size=45702&status=done&style=shadow&taskId=ube190ada-2fdc-44d3-89b5-5f3db202ef6&title=&width=1287)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=hMtBB&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 初步测试
启动服务器，浏览器地址栏：http://localhost:8080/myspringmvc
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068892689-b37a04ee-3e89-44a2-b018-1f3644812b71.png#averageHue=%23d7b27a&clientId=uae70fab4-1447-4&from=paste&height=120&id=u19c54095&originHeight=120&originWidth=586&originalType=binary&ratio=1&rotation=0&showTitle=false&size=15020&status=done&style=shadow&taskId=ud8061808-24ef-40ef-bbea-4d778d3d999&title=&width=586)
后台效果：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068880417-1a0839a3-84b3-459e-ab4b-77ccec5cff76.png#averageHue=%23312f2e&clientId=uae70fab4-1447-4&from=paste&height=162&id=u24007468&originHeight=162&originWidth=403&originalType=binary&ratio=1&rotation=0&showTitle=false&size=18495&status=done&style=shadow&taskId=ua727f346-8bc2-49ab-aaea-fabfb435ab5&title=&width=403)

如果让第二个拦截器返回false尝试一下：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068979607-248d52d3-17fd-402b-a859-26884ed27e98.png#averageHue=%23fcfbfb&clientId=uae70fab4-1447-4&from=paste&height=109&id=ub7c7d97d&originHeight=109&originWidth=459&originalType=binary&ratio=1&rotation=0&showTitle=false&size=5380&status=done&style=shadow&taskId=u14287d22-f0f0-49f5-9d25-d8c11af3645&title=&width=459)
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068971047-6774611e-9d91-482d-88b5-8e08478de7cb.png#averageHue=%2332302e&clientId=uae70fab4-1447-4&from=paste&height=83&id=ub336e206&originHeight=83&originWidth=349&originalType=binary&ratio=1&rotation=0&showTitle=false&size=9231&status=done&style=shadow&taskId=u59f97293-e4e0-4744-b6f7-9633a086d88&title=&width=349)
初步测试通过！！！

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=SeliC&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
# 调用处理器方法

