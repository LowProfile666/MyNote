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

DispatcherServlet的<init-param>的contextConfigLocation可以编写代码了：

```java
@Override
public void init() throws ServletException {
    ServletConfig servletConfig = this.getServletConfig();
    String contextConfigLocation = servletConfig.getInitParameter(Constant.CONTEXT_CONFIG_LOCATION);
    String springMvcXmlPath = getSpringMvcXmlPath(contextConfigLocation);
    System.out.println("Spring MVC配置文件路径解析完成：" + springMvcXmlPath);
}

private String getSpringMvcXmlPath(String contextConfigLocation) throws UnsupportedEncodingException {
    if(contextConfigLocation.startsWith(Constant.CLASSPATH)){
        String path = contextConfigLocation.substring(Constant.CLASSPATH.length()).trim();
        String springMvcXmlPath = Thread.currentThread().getContextClassLoader().getResource(path).getPath();
        // 对路径解码，防止路径中有 % 等字符。
        return URLDecoder.decode(springMvcXmlPath, Charset.defaultCharset());
    }
    return null;
}
```
定义系统常量类：Constant
```java
package org.myspringmvc.web.constant;

/**
 * ClassName: Constant
 * Description:SpringMVC系统常量类
 * Datetime: 2024/4/2 11:28
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class Constant {
    public static final String CONTEXT_CONFIG_LOCATION = "contextConfigLocation";
    public static final String CLASSPATH = "classpath:";
}

```

## 编写springmvc.xml

```xml
<?xml version="1.0" encoding="UTF-8">

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



InternalResourceViewResolver类中添加属性：suffix和prefix

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
        return null;
    }
}

```

# 服务器启动阶段的处理

## 分析服务器启动阶段都需要初始化什么

1. 初始化Spring容器
   1. 组件扫描包下的类纳入IoC容器的管理。
   2. 创建视图解析器对象
   3. 创建所有的拦截器对象
   4. 扫描这个包下所有的类：org.myspringmvc.web.servlet.mvc.method.annotation，全部实例化，纳入IoC容器管理
2. 初始化HandlerMapping
3. 初始化HandlerAdapter
4. 初始化ViewResolver

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=N1l3f&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 初始化Spring容器
Spring容器：ApplicationContext
Spring Web容器：WebApplicationContext
### 组件扫描
添加解析xml文件的依赖
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
```java
package org.myspringmvc.context;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.lang.reflect.Constructor;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Map;

/**
 * ClassName: ApplicationContext
 * Description: Spring容器，启动服务器时，初始化
 * Datetime: 2024/4/2 13:52
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class ApplicationContext {
    private Map<String, Object> beanMap = new HashMap<>();

    public ApplicationContext(String xmlPath) throws Exception {
        // 组件扫描
        SAXReader saxReader = new SAXReader();
        Document document = saxReader.read(new File(xmlPath));
        Element componentScanElement = (Element)document.selectSingleNode("/beans/context:component-scan");
        String basePackage = componentScanElement.attributeValue("base-package");
        System.out.println("组件扫描：" + basePackage);
        componentScan(basePackage);
        System.out.println("Spring Web容器当下状态：" + beanMap);
    }

    private void componentScan(String basePackage) throws Exception{
        String dirPath = Thread.currentThread().getContextClassLoader().getResource(basePackage.replace(".", "/")).getPath();
        File file = new File(URLDecoder.decode(dirPath));
        if(file.isDirectory()){
            File[] files = file.listFiles();
            for (File classFile : files){
                if(classFile.getName().endsWith(".class")){
                    String className = basePackage + "." + classFile.getName().substring(0, classFile.getName().lastIndexOf("."));
                    Class<?> clazz = Class.forName(className);
                    Constructor<?> defaultCon = clazz.getDeclaredConstructor();
                    Object bean = defaultCon.newInstance();
                    beanMap.put(firstCharLowerCase(clazz.getSimpleName()), bean);
                }
            }
        }
    }

    private String firstCharLowerCase(String simpleName) {
        return simpleName.substring(0, 1).toLowerCase() + simpleName.substring(1);
    }

    public Object getBean(String beanName){
        return beanMap.get(beanName);
    }
}

```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=lRrYR&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
```java
package org.myspringmvc.context;

import jakarta.servlet.ServletContext;

/**
 * ClassName: WebApplicationContext
 * Description:
 * Datetime: 2024/4/2 14:24
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class WebApplicationContext extends ApplicationContext{

    private ServletContext servletContext;

    public WebApplicationContext(String xmlPath, ServletContext servletContext) throws Exception {
        super(xmlPath);
        this.servletContext = servletContext;
    }

    public ServletContext getServletContext() {
        return servletContext;
    }
}

```
在DispatcherServlet中添加如下代码：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712041922023-4a1c3828-06cf-4443-a02a-e873e16993e1.png#averageHue=%232e2b2b&clientId=uae70fab4-1447-4&from=paste&height=457&id=u19a612c8&originHeight=457&originWidth=1367&originalType=binary&ratio=1&rotation=0&showTitle=false&size=80860&status=done&style=shadow&taskId=uc2d2171d-a841-4e76-acc5-456330636b2&title=&width=1367)
添加常量值：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712041948893-c2315381-d5a0-4ba6-b97e-ecb53436073e.png#averageHue=%23302b2b&clientId=uae70fab4-1447-4&from=paste&height=289&id=u966d7c5a&originHeight=289&originWidth=962&originalType=binary&ratio=1&rotation=0&showTitle=false&size=34450&status=done&style=shadow&taskId=u2f340b9b-afc4-4ec2-aacc-c2f7addf677&title=&width=962)

启动服务器测试：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712042124851-e6e6cb3c-0701-4e37-bcec-0a3fdd4d79c0.png#averageHue=%233a302f&clientId=uae70fab4-1447-4&from=paste&height=143&id=uc81ebad9&originHeight=143&originWidth=986&originalType=binary&ratio=1&rotation=0&showTitle=false&size=35638&status=done&style=shadow&taskId=u24621a8b-919d-4c01-afb9-b753b73c2aa&title=&width=986)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=cYNFp&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
### 创建视图解析器对象
InternalResourceViewResolver类代码改动，添加prefix和suffix属性：
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
        return null;
    }
}

```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=NWtZm&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712050149246-9884a89f-d261-49b1-8a99-6a9768ca69cc.png#averageHue=%232f2c2b&clientId=uae70fab4-1447-4&from=paste&height=711&id=u706ae1ca&originHeight=711&originWidth=1243&originalType=binary&ratio=1&rotation=0&showTitle=false&size=146866&status=done&style=shadow&taskId=ud73960b1-6428-4dd6-a43c-f19f75bfa42&title=&width=1243)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=bKpf0&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
```java
// 创建视图解析器对象
Element viewResolverBean = (Element) document.selectSingleNode("/beans/bean");
String viewResolverClassName = viewResolverBean.attributeValue("class");
Class viewResolverClass = Class.forName(viewResolverClassName);
Object viewResolverObj = viewResolverClass.newInstance();
if(viewResolverObj instanceof InternalResourceViewResolver internalResourceViewResolver){
    // 前缀
    Element prefixProperty = (Element)viewResolverBean.selectSingleNode("property[@name='prefix']");
    internalResourceViewResolver.setPrefix(prefixProperty.attributeValue("value"));
    // 后缀
    Element suffixProperty = (Element)viewResolverBean.selectSingleNode("property[@name='suffix']");
    internalResourceViewResolver.setSuffix(suffixProperty.attributeValue("value"));
}
beanMap.put(Constant.VIEW_RESOLVER, viewResolverObj);
System.out.println("Spring Web容器当下状态：" + beanMap);
```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=qwP75&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
### 创建所有的拦截器对象
在ApplicationContext构造方法中继续添加如下代码：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712045626658-02f8ddf3-e2a4-46e7-bbc2-5c154000c7c5.png#averageHue=%232e2d2c&clientId=uae70fab4-1447-4&from=paste&height=300&id=u99830af4&originHeight=300&originWidth=1000&originalType=binary&ratio=1&rotation=0&showTitle=false&size=59672&status=done&style=shadow&taskId=u8e5decaf-a146-4740-83bc-8c98f3a784a&title=&width=1000)
```java
// 创建所有拦截器对象
Element interceptorsElement = (Element) document.selectSingleNode("/beans/interceptors");
List<Element> interceptorBeans = interceptorsElement.elements("bean");
List<HandlerInterceptor> interceptors = new ArrayList<>();
for(Element interceptorBean : interceptorBeans){
    String className = interceptorBean.attributeValue("class");
    Class<?> clazz = Class.forName(className);
    interceptors.add((HandlerInterceptor) clazz.newInstance());
}
beanMap.put(Constant.INTERCEPTORS, interceptors);
System.out.println("Spring Web容器当下状态：" + beanMap);
```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=ibmZO&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
### 初始化annotation包下所有类的实例
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712048048630-7038a487-0f3d-4518-9d9f-49e320e58cdd.png#averageHue=%232c2b2b&clientId=uae70fab4-1447-4&from=paste&height=569&id=u510034ac&originHeight=569&originWidth=1636&originalType=binary&ratio=1&rotation=0&showTitle=false&size=105235&status=done&style=shadow&taskId=u1eb68c84-3791-49ca-93a3-69a1ddb62b3&title=&width=1636)
```java
// 将这个包下所有的类实例化：org.myspringmvc.web.servlet.mvc.method.annotation
String dirPath = Thread.currentThread().getContextClassLoader().getResource(Constant.PACKAGE_AUTO_CREATE.replace(".", "/")).getPath();
File file = new File(URLDecoder.decode(dirPath));
if(file.isDirectory()){
    File[] files = file.listFiles();
    for (File classFile : files){
        if(classFile.getName().endsWith(".class")){
            String className = Constant.PACKAGE_AUTO_CREATE + "." + classFile.getName().substring(0, classFile.getName().lastIndexOf("."));
            Class<?> clazz = Class.forName(className);
            Constructor<?> defaultCon = clazz.getDeclaredConstructor();
            Object bean = defaultCon.newInstance();
            if(bean instanceof HandlerMapping){
                beanMap.put(Constant.HANDLER_MAPPING, bean);
            }
            if(bean instanceof HandlerAdapter){
                beanMap.put(Constant.HANDLER_ADAPTER, bean);
            }
        }
    }
}
System.out.println("Spring Web容器当下状态：" + beanMap);
```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=zOGSi&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 初始化HandlerMapping
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712050860912-9b46aa11-9b17-43df-9f38-74802dba5d59.png#averageHue=%232e2b2b&clientId=uae70fab4-1447-4&from=paste&height=783&id=u666aa25c&originHeight=783&originWidth=1325&originalType=binary&ratio=1&rotation=0&showTitle=false&size=144195&status=done&style=shadow&taskId=uce12b2d5-0cbc-408c-84f2-669275d0280&title=&width=1325)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=ogZJm&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 初始化HandlerAdapter
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712050860912-9b46aa11-9b17-43df-9f38-74802dba5d59.png#averageHue=%232e2b2b&clientId=uae70fab4-1447-4&from=paste&height=783&id=osYOB&originHeight=783&originWidth=1325&originalType=binary&ratio=1&rotation=0&showTitle=false&size=144195&status=done&style=shadow&taskId=uce12b2d5-0cbc-408c-84f2-669275d0280&title=&width=1325)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=tkRZU&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 初始化ViewResolver
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712050860912-9b46aa11-9b17-43df-9f38-74802dba5d59.png#averageHue=%232e2b2b&clientId=uae70fab4-1447-4&from=paste&height=783&id=nOiWp&originHeight=783&originWidth=1325&originalType=binary&ratio=1&rotation=0&showTitle=false&size=144195&status=done&style=shadow&taskId=uce12b2d5-0cbc-408c-84f2-669275d0280&title=&width=1325)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=ssl3B&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
# 根据请求流程补充代码
## 根据请求获取处理器执行链
```java
private void doDispatch(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    try {
        // 根据请求获取处理器执行链
        HandlerExecutionChain mappedHandler = handlerMapping.getHandler(request);
        System.out.println(mappedHandler);
    } catch (Exception e) {
        e.printStackTrace();
    }
}
```
```java
package org.myspringmvc.web.servlet.mvc.method.annotation;

import jakarta.servlet.http.HttpServletRequest;
import org.myspringmvc.context.WebApplicationContext;
import org.myspringmvc.web.constant.Constant;
import org.myspringmvc.web.method.HandlerMethod;
import org.myspringmvc.web.servlet.HandlerExecutionChain;
import org.myspringmvc.web.servlet.HandlerInterceptor;
import org.myspringmvc.web.servlet.HandlerMapping;
import org.myspringmvc.web.servlet.mvc.RequestMappingInfo;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * ClassName: RequestMappingHandlerMapping
 * Description:
 * Datetime: 2024/4/2 9:44
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class RequestMappingHandlerMapping implements HandlerMapping {

    private Map<RequestMappingInfo, HandlerMethod> map;

    public RequestMappingHandlerMapping(Map<RequestMappingInfo, HandlerMethod> map) {
        this.map = map;
    }

    @Override
    public HandlerExecutionChain getHandler(HttpServletRequest request) throws Exception {
        RequestMappingInfo requestMappingInfo = new RequestMappingInfo(request.getServletPath(), request.getMethod());
        HandlerExecutionChain handlerExecutionChain = new HandlerExecutionChain();
        handlerExecutionChain.setHandler(map.get(requestMappingInfo));
        WebApplicationContext wac = (WebApplicationContext) request.getServletContext().getAttribute(Constant.WEB_APPLICATION_CONTEXT);
        handlerExecutionChain.setInterceptorList((List<HandlerInterceptor>)wac.getBean(Constant.INTERCEPTORS));
        return handlerExecutionChain;
    }
}

```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=V9Lap&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
```java
private Map<RequestMappingInfo, HandlerMethod> componentScan(String basePackage) throws Exception{
    // 初始化HandlerMethod
    Map<RequestMappingInfo, HandlerMethod> handlerMethodMap = new HashMap<>();

    String dirPath = Thread.currentThread().getContextClassLoader().getResource(basePackage.replace(".", "/")).getPath();
    File file = new File(URLDecoder.decode(dirPath));
    if(file.isDirectory()){
        File[] files = file.listFiles();
        for (File classFile : files){
            if(classFile.getName().endsWith(".class")){
                String className = basePackage + "." + classFile.getName().substring(0, classFile.getName().lastIndexOf("."));
                Class<?> clazz = Class.forName(className);
                Constructor<?> defaultCon = clazz.getDeclaredConstructor();
                Object bean = defaultCon.newInstance();
                beanMap.put(firstCharLowerCase(clazz.getSimpleName()), bean);
                // 如果clazz被@Controller注解标注
                if(clazz.isAnnotationPresent(Controller.class)){
                    // 获取该类中所有的方法
                    Method[] methods = clazz.getDeclaredMethods();
                    for(Method method : methods){
                        if(method.isAnnotationPresent(RequestMapping.class)){
                            RequestMapping requestMapping = method.getAnnotation(RequestMapping.class);
                            // 创建RequestMappingInfo对象
                            RequestMappingInfo requestMappingInfo = new RequestMappingInfo();
                            requestMappingInfo.setRequestURI(requestMapping.value()[0]);
                            requestMappingInfo.setRequestMethod(requestMapping.method().toString());
                            // 创建HandlerMethod对象
                            HandlerMethod handlerMethod = new HandlerMethod();
                            handlerMethod.setMethod(method);
                            handlerMethod.setHandler(bean);

                            handlerMethodMap.put(requestMappingInfo, handlerMethod);
                        }
                    }
                }
            }
        }
    }
    return handlerMethodMap;
}
```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=jp4ib&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
ApplicationContext代码还有以下改造：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712055939500-e4301f42-0486-43b6-b3fa-bc9780fd91c4.png#averageHue=%23302c2b&clientId=uae70fab4-1447-4&from=paste&height=311&id=uf747f873&originHeight=311&originWidth=1037&originalType=binary&ratio=1&rotation=0&showTitle=false&size=57663&status=done&style=shadow&taskId=u6c597b6a-2e25-448d-a843-cfbadc876e5&title=&width=1037)
添加一个新的类：RequestMappingInfo
```java
package org.myspringmvc.web.servlet.mvc;

import java.util.Objects;

/**
 * ClassName: RequestMappingInfo
 * Description:
 * Datetime: 2024/4/2 17:58
 * Author: 老杜@动力节点
 * Version: 1.0
 */
public class RequestMappingInfo {
    private String requestURI;
    private String requestMethod;

    public RequestMappingInfo() {
    }

    public RequestMappingInfo(String requestURI, String requestMethod) {
        this.requestURI = requestURI;
        this.requestMethod = requestMethod;
    }

    public String getRequestURI() {
        return requestURI;
    }

    public void setRequestURI(String requestURI) {
        this.requestURI = requestURI;
    }

    public String getRequestMethod() {
        return requestMethod;
    }

    public void setRequestMethod(String requestMethod) {
        this.requestMethod = requestMethod;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RequestMappingInfo that = (RequestMappingInfo) o;
        return Objects.equals(requestURI, that.requestURI) && Objects.equals(requestMethod, that.requestMethod);
    }

    @Override
    public int hashCode() {
        return Objects.hash(requestURI, requestMethod);
    }

    @Override
    public String toString() {
        return "RequestMappingInfo{" +
                "requestURI='" + requestURI + '\'' +
                ", requestMethod='" + requestMethod + '\'' +
                '}';
    }
}

```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=ZxO2a&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 执行拦截器的preHandle
添加以下代码：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712056664132-90f25f97-bc21-4aff-851b-63d222974148.png#averageHue=%232e2b2b&clientId=uae70fab4-1447-4&from=paste&height=310&id=u1b97258b&originHeight=310&originWidth=1330&originalType=binary&ratio=1&rotation=0&showTitle=false&size=38297&status=done&style=shadow&taskId=u608791fc-8147-4e21-a40d-f9ee94bf3a9&title=&width=1330)

HandlerExecutionChain添加以下代码：
```java
public boolean applyPreHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
    for (int i = 0; i < interceptorList.size(); i++) {
        HandlerInterceptor handlerInterceptor = interceptorList.get(i);
        boolean result = handlerInterceptor.preHandle(request, response, handler);
        if(!result){
            return false;
        }
        interceptorIndex = i;
    }
    return true;
}
```

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=tN3h4&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 执行处理器方法
DispatcherServlet中的doDispatch方法：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068532880-a22a29f7-6acf-44da-9c2e-016aa01f3756.png#averageHue=%232d2c2b&clientId=uae70fab4-1447-4&from=paste&height=111&id=ued28d3e9&originHeight=111&originWidth=1395&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23777&status=done&style=shadow&taskId=u39d0417d-154d-4f5b-b690-a75fc10f3ee&title=&width=1395)
先让handle方法返回一个固定的ModelAndView，后期在详细编写 handle 方法：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712066826429-45d064ef-6649-4b7d-a504-b485143f87b6.png#averageHue=%232d2c2c&clientId=uae70fab4-1447-4&from=paste&height=307&id=u32db08a6&originHeight=307&originWidth=1285&originalType=binary&ratio=1&rotation=0&showTitle=false&size=41136&status=done&style=shadow&taskId=u4fc49120-5b20-4ddc-a4a3-07c0f698a17&title=&width=1285)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=taS9u&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
## 执行拦截器的postHandle
DispatcherServlet的doDispatch方法中：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712067006139-fe7993eb-1745-4653-92c1-173b31254417.png#averageHue=%232c2c2b&clientId=uae70fab4-1447-4&from=paste&height=102&id=u3184c834&originHeight=102&originWidth=899&originalType=binary&ratio=1&rotation=0&showTitle=false&size=8558&status=done&style=shadow&taskId=udf523c3b-d13b-4215-a019-869c84d9bf1&title=&width=899)

HandlerExecutionChain的方法：
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1712068684534-c19e8af2-4a17-4997-8e5a-3c478fa95854.png#averageHue=%232c2c2b&clientId=uae70fab4-1447-4&from=paste&height=200&id=uc5a62c6f&originHeight=200&originWidth=1421&originalType=binary&ratio=1&rotation=0&showTitle=false&size=33486&status=done&style=shadow&taskId=ud5c81bf5-682b-47b4-9204-33cd11509f6&title=&width=1421)

![标头.jpg](https://cdn.nlark.com/yuque/0/2023/jpeg/21376908/1692002570088-3338946f-42b3-4174-8910-7e749c31e950.jpeg#averageHue=%23f9f8f8&clientId=uc5a67c34-8a0d-4&from=paste&height=78&id=s9c8K&originHeight=78&originWidth=1400&originalType=binary&ratio=1&rotation=0&showTitle=false&size=23158&status=done&style=shadow&taskId=u98709943-fd0b-4e51-821c-a3fc0aef219&title=&width=1400)
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

