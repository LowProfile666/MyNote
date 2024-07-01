# 引入依赖

+ Spring：spring-jdbc
+ Mybatis：mybatis、mybtais-spring、mysql-connector-java、druid
+ SpringMVC：spring-web-mvc（包含了Spring的spring-context）、jakarta.servlet-api、thymeleaf-spring6、jackson-databind
+ 日志依赖：logback-classic

# 配置web.xml

在src\main下创建目录webapp，打开模块设置，添加web.xml文件，sping容器是在服务器启动的时候创建的，所以应该在web.xml中配置spring的配置文件：

```xml
<!--    配置Spring-->
<listener>
    <listener-class>org.springframework.web.context.ContextLoaderListener</listener-class>
</listener>
<context-param>
    <param-name>contextConfigLocation</param-name>
    <param-value>classpath:spring.xml</param-value>
</context-param>
<!--    配置SpringMVC-->
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

# 配置spring.xml

配置包扫描、mybatis：

```xml
<!--包扫描-->
<context:component-scan base-package="com.zsm" />
<!--    引入外部资源文件-->
<context:property-placeholder location="jdbc.properties" />
<!--数据源-->
<bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource">
    <property name="driverClassName" value="${jdbc.driver}" />
    <property name="url" value="${jdbc.url}" />
    <property name="username" value="${jdbc.username}" />
    <property name="password" value="${jdbc.password}" />
</bean>
<!--配置mybatis-->
<bean class="org.mybatis.spring.SqlSessionFactoryBean" >
    <property name="typeAliasesPackage" value="com.zsm.bean" />
    <property name="dataSource" ref="dataSource" />
</bean>
<!--配置mapper扫描器-->
<bean class="org.mybatis.spring.mapper.MapperScannerConfigurer" >
    <property name="basePackage" value="com.zsm.mapper" />
</bean>
```

# 配置springmvc.xml

配置包扫描、视图解析器、注解驱动：

```xml
<!--包扫描-->
<context:component-scan base-package="com.zsm" />
<!--    配置视图解析器-->
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
<!--    开启注解驱动-->
<mvc:annotation-driven />
<!--    处理静态资源默认servlet-->
<mvc:default-servlet-handler/>
```

+ 访问根目录时跳转页面，所以配置视图解析器（也可以不用视图解析器）
+ 开启注解驱动
+ 需要使用到一些静态资源如js、css等，需要开启默认处理静态资源的servlet

# 编写

## 项目结构

![image-20240628094333460](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406280943559.png)

## controller

```java
@Controller
public class UserController {
    @Autowired
    private UserService userService;
    @GetMapping("/")
    public String index() {
        return "index";
    }

    @GetMapping("list")
    @ResponseBody
    public List<User> list() {
        return userService.list();
    }
}
```

## mapper

UserMapper.java:

```java
public interface UserMapper {
    List<User> list();
}
```

UserMapper.xml:

```xml
<mapper namespace="com.zsm.mapper.UserMapper">

    <select id="list" resultType="User">
        select * from user;
    </select>
</mapper>
```

## service

UserService.java

```java
public interface UserService {
    List<User> list();
}
```

UserServiceImpl.java:

```java
@Service("userService")
public class UserServiceImpl implements UserService {
    @Autowired
    private UserMapper userMapper;
    @Override
    public List<User> list() {
        return userMapper.list();
    }
}
```

## index.html

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>首页</title>
    <link rel="stylesheet" th:href="@{/static/css/bootstrap.min.css}">
    <script th:src="@{/static/js/jquery-3.7.1.min.js}" ></script>
    <script th:src="@{/static/js/bootstrap.min.js}"></script>
</head>
<body>

<div class="container">
    <script>
        let url = [[@{/}]] + "list";
        $.ajax({
            url: url,
            type: "get",
            success(resp) {
                console.log(resp);
                resp.forEach(obj => {
                    let html = `
                        <div class="card">
                            <div class="card-body">
                                <div class="row">
                                    <div class="col" id="username">${obj.username}</div>
                                    <div class="col" id="password">${obj.password}</div>
                                </div>
                            </div>
                        </div>
                    `;
                    $(".container").append(html);
                })
            }
        });
    </script>
</div>
</body>
</html>
```

+ 引用了Thymeleaf，
+ [[@{/}]]：获取项目的根路径

![image-20240628094653229](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406280946282.png)
