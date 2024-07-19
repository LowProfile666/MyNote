# 创建SpringBoot项目

## 手动创建

步骤：

1. 引入SpringBoot的父工程
2. 创建启动类

创建一个Maven项目，在pom.xml文件中引入父项目：

```xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>3.3.1</version>
    <relativePath/> <!-- lookup parent from repository -->
</parent>
```

+ 引入的父项目是几，就是SpringBoot几的项目。

然后在根包下创建启动类，类名随意：

```java
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```

+ 启动类上要有注解@SpingBootApplication
+ 启动类中要有主方法
+ 主方法里要有SpringApplication.run方法，参数是启动类的字节码对象，和命令行参数
+ 主方法里可以写其他代码

## 通过脚手架创建

步骤：

1. 配置
2. 下载代码

访问官网https://start.spring.io/，或者阿里云的https://start.aliyun.com/，在页面中进行配置，配置项目的类型、语言、SpringBoot版本、依赖等：

![image-20240716231818397](https://cdn.jsdelivr.net/gh/LowProfile666/imageBed@main/img/202407162318519.png)

## 通过IDEA创建

步骤：

1. 创建项目时选择SpringInitializr

IDEA内置了脚手架，可以选择脚手架的地址，然后创建方法和在web上的差不多。

# 启动类

+ 启动类是一个配置类，可以结合@Bean注入对象【@SpringBootApplication注解包括了@Configure注解】
+ 启动类开启了自动配置【@SpringBootApplication包含了@EnableAutoConfiguration注解】
+ 启动类开启了组件扫描【@SpringBootApplication包含了@ComponentScan注解】
+ 启动类默认放在根包之下，因为组件扫描是从启动类的位置开始

```java
@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

}
```

从这个主方法开始，启动整个项目。

# 配置文件

+ 默认配置文件是application.properties，位于resources目录下
+ 有`.yml`和`.properties`两种格式，本质上是一样的。
+ properties文件的优先级比yml文件更高

## properties

格式：

```properties
# 默认的配置文件
user.name=zsm
user.age=10
user.sex=男
user.email=123456@com
```

## yml

+ 用缩进表示层级
+ 缩进的空格数量不重要，只要同级是左端对齐
+ 冒号的右边必须要有一个空格
+ 只是写法格式和properties不一样

格式：
```yaml
# 编写配置 key: value
user:
  username: zsssm
  age: 20
  emial: 111111@qq.com
  ses: 男
```

配置List集合和数组：

```yaml
names:
  - zhangsn
  - lisi
  - wnagwu
```

+ `-` 后面要有空格，没有空格的话会把 -zhangsan 当作一个值

如果List中放的是一个对象，一个 `-` 表示一个元素：

```yaml
servers:
  - title: 服务器1
    ip: 1.1.1.1
  - title: 服务器2
    ip: 2.2.2.2
```

配置Map<String, User>集合数据： 

```yaml
users:
  user1:
    name: 张三
    sex: 男
    age: 23
  user2: 
    name: 李四
    age: 21
    sex: 女
```

+ 在map集合中，会有两个key，分别是user1和user2，对应着张三和李四两个User对象

## 用法

### @Value

+ 使用`@Value(${key})`来使用配置文件中的值
+ 如果没有指定的key的话，可以使用默认值`@Value(${key:default})`

```java
@Service
public class UserService {
    @Value("${user.name:1231}")
    private String name;

    @Value("${user.sex}")
    private String sex;

    @Value("${user.email}")
    private String email;

    @Value("${user.age}")
    private Integer age;

    @Value("${user.address:JCUT}")
    private String address;

    public void printInfo() {
        System.out.println(name + " " + sex + " " + email + " " + age + " " +address);
    }
}
```

### Environment

+ Environment对象就代表着配置文件
+ 直接注入获得对象，就可使用
+ `getProperty(key)`：用来获取指定key的值
+ `getProperty(key, class, defaultVlaue)`：用来获取指定key的值，并且将结果转为指定的class类型，同时如果没有该key没有值会赋值默认值defaultValue
+ `containsProperty(key)`：用来判断是否有某个key

```java
@Service
public class Config {
    // 注入环境对象
    @Autowired
    private Environment environment;

    public void print() {
        // 读取环境对象值
        String username = environment.getProperty("user.username");

        // 判断某个key是否存在
        if (environment.containsProperty("user.address")) {
            System.out.println("存在：" + environment.getProperty("user.address"));
        } else {
            System.out.println("不存在");
        }

        // 读取某个key的值，转为期望的类型，同时提供默认值
        String address = environment.getProperty("user.address", String.class, "JJJJJCUT");

        String format = String.format("读取的值：username=%s, address=%s", username, address);
        System.out.println(format);
    }
}
```

## 导入其他配置文件

+ 加载application配置文件时，就会一起将导入的配置文件加载
+ 使用spring.config.import=文件名,文件名
+ 导入多个文件时，使用逗号分割

```yaml
# 导入其他配置
spring:
  config:
    import: config/mysql.yml, config/redis.yml
```

## 多环境

+ 使用spring.config.activate.on-profile指定当前配置文件属于的环境名称
+ 环境配置文件的名称一般为：application-{环境名}.properties(yml)
  + dev 表示开发 ，test 表示测试。prod 表示生产，feature 表示特性
+ 需要在application配置文件中使用spring.profiles.active激活指定的环境

常说开发环境，测试环境，生产环境等等。一个环境就是一组相关的配置数据， 支撑我们的应用在这些配置下运行。

指定环境名称：

```yaml
spring:
  config:
    activate:
      on-profile: dev
```

激活环境：

```yaml
spring:
  # 激活某个配置文件（环境）
  profiles:
    active: dev
```

## 绑定bean

+ 使用@ConfigurationProperties注解
+ 如果配置文件中的key有前缀，需要在@ConfigurationProperties中指定前缀
+ 保持bean的属性名和配置文件的key一致
+ static属性不支持绑定属性
+ 通过set方法进行绑定，set方法的名字是关键
+ @ConfigurationProperties不能单独使用（因为它只绑定属性，不创建对象），需要配合@EnableConfigurationProperties 或@ConfigurationPropertiesScan。
  + `@EnableConfigurationProperties({类})`：启动指定类的@ConfigurationProperties注解
  + `@ConfigurationPropertiesScan(basePackages = { "包名" })`：扫描指定包下的@ConfigurationProperties注解

配置文件是：

```yaml
user:
  username: zsssm
  age: 20
  email: 111111@qq.com
  sex: 男
# 以上等价于 
# user.username=zsssm
# user.age=20
# user.email=111111@qq.com
# user.sex=男
# 这个user就是前缀
```

将以上数据绑定到bean的属性上：

```java
@ConfigurationProperties(prefix = "user")
public class UserBean {
    private String username;
    private String email;
    private Integer age;
    private String sex;
    // getter setter
}
```

如果bean中还有一个bean：

```java
@ConfigurationProperties(prefix = "user")
public class UserBean {
    private String username;
    private String email;
    private Integer age;
    private String sex;
    private Address address;
    // getter setter
}
```

这个address：

```java
public class Address {
    private String city;
    private String address;
    // getter setter
}
```

那么配置文件中的key还是要和bean的属性一一对应：

```yaml
user:
  username: zsssm
  age: 20
  email: 111111@qq.com
  sex: 男
  address:
    city: 湖北荆门
    address: 象山大道33号
```

## @ConfigurationProperties结合@Bean

+ @Bean指定一个方法返回的对象被加入容器中
+ @ConfigurationProperties指定该对象的数据来自配置文件

```java
@Configuration
public class ApplicationConfig {
    @Bean
    @ConfigurationProperties(prefix = "security")
    public Security createSecurity() {
        return new Security();
    }
}
```

## 指定数据源

+ 使用@PropertySource注解指定配置文件
+ @PropertySource 与@Configuration 一同使用

```java
@ConfigurationProperties(prefix = "user")
@Configuration
@PropertySource("classpath:/user-info.properties")
public class UserBean {
    private String username;
    private String email;
    private Integer age;
    private String sex;
    private Address address;
    // getter setter toString()
}
```

# AOP

+ 切面（Aspect）：一个类，类中写功能方法代码，使用@Aspect表示一个类是切面类
+ 连接点：可以插入切面的地方
+ 切入点：实际上插入切面的地方
+ 增强（advice）：主要包括 5 个注解：@Before，@After，@AfterReturning，@AfterThrowing，@Around。注解来自 aspectj 框架。
  + @Before：在切点方法之前执行。

  + @After：在切点方法之后执行

  + @AfterReturning：切点方法返回后执行

  + @AfterThrowing：切点方法抛异常执行

  + @Around：属于环绕增强，能控制切点执行前，执行后。功能最强的注解。

使用aop，需要加入依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-aop</artifactId>
</dependency>
```

现在有一个业务类：

```java
@Service
public class AServiceImpl implements AService {
    @Override
    public void query(Integer id) {
        System.out.println("AService 业务方法 query 执行了");
    }

    @Override
    public void save(String name, String code) {
        System.out.println("AService 业务方法 save 执行了");
    }
}
```

现在要在这个service的两个方法调用时输出日志，使用aop最合适。接下来创建切面类，是一个普通类，在这个类中写功能增强的方法：

```java
@Component
@Aspect
public class LogAspect {
    @Before("execution(* com.zsm.aop.service..*.*(..))")
    public void sysLog(JoinPoint jp) {
        // 使用一个StringJoiner来做日志
        StringJoiner log = new StringJoiner("|", "{", "}");

        // 加入时间信息
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        log.add(formatter.format(LocalDateTime.now()));

        // 加入当前执行的业务方法的名字
        String name = jp.getSignature().getName();
        log.add(name);

        // 加入方法的参数
        Object[] args = jp.getArgs();
        for (var arg : args) {
            log.add(arg == null ? "-" : arg.toString());
        }

        System.out.println("日志：" + log);
    }
}
```

+ @Component 将切面类对象注入到 spring 容器。spring 会根据目标类和切面类创建代理对象，织入切面功能。
+ @Aspect表示是一个切面类
+ @Before("execution(* com.zsm.aop.service..*.*(..))")这个注解的意思是：在 `com.zsm.aop.service` 包及其子包中的任意类的任意方法执行之前，执行前置通知中的代码。

# 自动配置

框架中有很多自动配置文件，文件中包含了需要自动配置的类名，框架会根据文件中指定的类名去创建对应的对象并注入容器。

# 访问数据库

## 数据源

+ 在配置文件中以spring.datasource.为数据库数据源的前缀

```properties
spring.datasource.url=jdbc:mysql://localhost/mydb
spring.datasource.username=dbuser
spring.datasource.password=dbpass
```

## Mybatis

+ 添加依赖
+ 配置数据源
+ 配置Mybatis，
+ 创建mapper接口文件
+ 开启mapper扫描或使用@Mapper注解
+ 使用@Results作结果映射，使用@ResultMap指定使用哪个结果映射

依赖：

```xml
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>3.0.3</version>
</dependency>
```

配置数据源：

```properties
spring.datasource.url=jdbc:mysql://localhost:3306/springboot009-blog
spring.datasource.username=root
spring.datasource.password=1234
```

配置mybatis：

```properties
# 开启驼峰命名转换
mybatis.configuration.map-underscore-to-camel-case=true
# 配置mapper.xml文件的路径
mybatis.mapper-locations=classpath:mapper/**/*.xml
```

启动类上开启mapper包扫描：

```java
@MapperScan(basePackages = "com.zsm.mapper")
```

使用结果映射，如果类名和属性名不对应的话：

```java
public interface ArticleMapper {
    @Select("""
                select * from article where id = #{id}
            """)
    @Results(id = "ArticleResult", value = {
            @Result(id = true, column = "id", property = "id"),
            @Result(column = "title", property = "title"),
            @Result(column = "summary", property = "summary"),
            @Result(column = "read_count", property = "readCount"),
            @Result(column = "user_id", property = "userId"),
            @Result(column = "create_time", property = "createTime"),
            @Result(column = "update_time", property = "updateTime")
    })
    Article selectById(@Param("id") Integer id);

    @Select("""
                select * from article where id = #{id}
            """)
    @ResultMap("ArticleResult")
    Article selectById2(@Param("id") Integer id);

}
```

## 声明式事务

+ 在具体方法上使用@Transactional 注解
+ 使用@Transactional(rollbackFor = {异常类})设置发生了指定异常后回滚事务
+ A方法调用带有事务的 B 方法时，运行 A 方法的时候事务无效
+ 方法在线程中运行的，在同一线程中方法具有事务功能， 新的线程中的代码事务无效。

# web

## 验证参数

+ 使用Bean Validation，加入依赖
+ 在属性上使用对应注解
+ 在controller方法参数上进行验证

引入依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-validation</artifactId>
</dependency>
```

在属性上使用对应注解：

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Article {
    private Integer id;

    @NotNull(message = "作者不能为空")
    private Integer userId;

    @NotBlank(message = "标题不能为空")
    @Size(min = 3, max = 10, message = "标题最少3个字，最多10个字")
    private String title;

    @NotBlank(message = "摘要不能为空")
    @Size(min = 20, max = 200, message = "摘要字数必须在20到200之间")
    private String summary;

    @DecimalMin(value = "0", message = "阅读量最少为0")
    private Integer readCount;

    @Email(message = "邮箱格式不对")
    private String email;
}
```

在controller方法中使用@Validated注解开启验证：

```java
@RestController
public class ArticleController {
    @PostMapping("/add")
    public Map<String, Object> addArticle(@Validated @RequestBody Article article, BindingResult br) {

        Map<String, Object> map = new HashMap<>();
        if (br.hasErrors()) {  // 有一项或多项bean的属性验证没通过
            List<FieldError> fieldErrors = br.getFieldErrors();  // 获取没有通过的属性，FieldError封装了属性验证出错的信息
            for (int i = 0; i < fieldErrors.size(); i++) {
                // 将出错信息存到map，getField()拿到字段，getDefaultMessage()拿到属性上注解中的message
                FieldError fieldError = fieldErrors.get(i);
                map.put(fieldError.getField() + "-" + i, fieldError.getDefaultMessage());
            }
        }
        return map;
    }
}
```

+ @Validated：Spring中的一个注解，表示要验证bean
+ 验证bean错误后的结果在BindingResult里面

## 分组验证

+ 定义组
+ 给属性指定组
+ 如果验证参数时指定了组，那么没有组和不是指定组的属性不会被验证

给所有属性分好组：

```java
public class Article {

    public static interface EditArticleGroup{};
    public static interface AddArticleGroup{};

    @NotNull(message = "主键不能为空", groups = {EditArticleGroup.class})
    @Min(value = 1, message = "ID必须大于0", groups = {EditArticleGroup.class})
    private Integer id;

    @NotNull(message = "作者不能为空", 
             groups = {EditArticleGroup.class, AddArticleGroup.class})
    private Integer userId;

    @NotBlank(message = "标题不能为空", 
              groups = {EditArticleGroup.class, AddArticleGroup.class})
    @Size(min = 3, max = 10, message = "标题最少3个字，最多10个字", 
          groups = {EditArticleGroup.class, AddArticleGroup.class})
    private String title;

    @NotBlank(message = "摘要不能为空", 
              groups = {EditArticleGroup.class, AddArticleGroup.class})
    @Size(min = 20, max = 200, message = "摘要字数必须在20到200之间", 
          groups = {EditArticleGroup.class, AddArticleGroup.class})
    private String summary;

    @DecimalMin(value = "0", message = "阅读量最少为0", 
                groups = {EditArticleGroup.class, AddArticleGroup.class})
    private Integer readCount;

    @Email(message = "邮箱格式不对", groups = {EditArticleGroup.class, AddArticleGroup.class})
    private String email;
}
```

验证时指定组：

```java
@PostMapping("/edit")
public Map<String, Object> editArticle(@Validated(Article.EditArticleGroup.class) @RequestBody Article article, BindingResult br) {

    Map<String, Object> map = new HashMap<>();
    if (br.hasErrors()) {  // 有一项或多项bean的属性验证没通过
        List<FieldError> fieldErrors = br.getFieldErrors();  // 获取没有通过的属性，FieldError封装了属性验证出错的信息
        for (int i = 0; i < fieldErrors.size(); i++) {
            // 将出错信息存到map，getField()拿到字段，getDefaultMessage()拿到属性上注解中的message
            FieldError fieldError = fieldErrors.get(i);
            map.put(fieldError.getField() + "-" + i, fieldError.getDefaultMessage());
        }
    }
    return map;
}
```

## 配置服务器

```properties
#服务器端口号
server.port=8001
#上下文访问路径
server.servlet.context-path=/api
#request，response 字符编码
server.servlet.encoding.charset=utf-8
#强制 request，response 设置 charset 字符编码
server.servlet.encoding.force=true
```

## 配置tomcat日志

```properties
#日志路径
server.tomcat.accesslog.directory=D:/TomcatLogs
#启用访问日志
server.tomcat.accesslog.enabled=true
#日志文件名前缀
server.tomcat.accesslog.prefix=tomcat
#日志文件日期时间
server.tomcat.accesslog.file-date-format=.yyyy-MM-dd
#日志文件名称后缀
server.tomcat.accesslog.suffix=.log
#post 请求内容最大值，默认 2M
server.tomcat.max-http-form-post-size=2000000
#服务器最大连接数
server.tomcat.max-connections=8192
```

## 配置SpringMVC

```properties
#访问中央调度器的路径
spring.mvc.servlet.path=/course
#Servlet 的加载顺序，越小创建时间越早
spring.mvc.servlet.load-on-startup=0
#时间格式，可以在接受请求参数使用
spring.mvc.format.date-time=yyyy-MM-dd HH:mm:ss
```

使用配置类来配置SpringMVC，需要实现WebMvcConfigurer接口：

```java
public interface WebMvcConfigurer {
    //帮助配置 HandlerMapping
    default void configurePathMatch(PathMatchConfigurer configurer) {
    }
    //处理内容协商
    default void configureContentNegotiation(ContentNegotiationConfigurer configurer) {
    }//异步请求
    default void configureAsyncSupport(AsyncSupportConfigurer configurer) {
    }
    //配置默认 servlet
    default void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
    }
    //配置内容转换器
    default void addFormatters(FormatterRegistry registry) {
    }
    //配置拦截器
    default void addInterceptors(InterceptorRegistry registry) {
    }
    //处理静态资源
    default void addResourceHandlers(ResourceHandlerRegistry registry) {
    }
    //配置全局跨域
    default void addCorsMappings(CorsRegistry registry) {
    }
    //配置视图页面跳转
    default void addViewControllers(ViewControllerRegistry registry) {
    }
    //配置视图解析器
    default void configureViewResolvers(ViewResolverRegistry registry) {
    }
    //自定义参数解析器，处理请求参数
    default void addArgumentResolvers(List<HandlerMethodArgumentResolver> resolvers) {
    }
    //自定义控制器方法返回值处理器
    default void addReturnValueHandlers(List<HandlerMethodReturnValueHandler> handlers) {}
    //配置 HttpMessageConverters
    default void configureMessageConverters(List<HttpMessageConverter<?>> converters) {
    }
    //配置 HttpMessageConverters
    default void extendMessageConverters(List<HttpMessageConverter<?>> converters) {
    }
    //配置异常处理器
    default void configureHandlerExceptionResolvers(List<HandlerExceptionResolver> resolvers) {
    }
    //扩展异常处理器
    default void extendHandlerExceptionResolvers(List<HandlerExceptionResolver> resolvers) {
    }
    //JSR303 的自定义验证器
    default Validator getValidator() {
        return null;
    }
    //消息处理对象
    default MessageCodesResolver getMessageCodesResolver() {
        return null;
    }
}
```

