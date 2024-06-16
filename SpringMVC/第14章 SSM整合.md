# 引入相关依赖

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.powernode</groupId>
    <artifactId>ssmtest</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>war</packaging>

    <dependencies>
        <!--springmvc-->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-webmvc</artifactId>
            <version>6.1.4</version>
        </dependency>
        <!--spring jdbc-->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-jdbc</artifactId>
            <version>6.1.4</version>
        </dependency>
        <!--mybatis-->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.15</version>
        </dependency>
        <!--mybatis spring-->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis-spring</artifactId>
            <version>3.0.3</version>
        </dependency>
        <!--mysql驱动-->
        <dependency>
            <groupId>com.mysql</groupId>
            <artifactId>mysql-connector-j</artifactId>
            <version>8.3.0</version>
        </dependency>
        <!--德鲁伊连接池-->
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid</artifactId>
            <version>1.2.22</version>
        </dependency>
        <!--jackson-->
        <dependency>
            <groupId>com.fasterxml.jackson.core</groupId>
            <artifactId>jackson-databind</artifactId>
            <version>2.17.0</version>
        </dependency>
        <!--servlet api-->
        <dependency>
            <groupId>jakarta.servlet</groupId>
            <artifactId>jakarta.servlet-api</artifactId>
            <version>6.0.0</version>
            <scope>provided</scope>
        </dependency>
        <!--logback-->
        <dependency>
            <groupId>ch.qos.logback</groupId>
            <artifactId>logback-classic</artifactId>
            <version>1.5.3</version>
        </dependency>
        <!--thymeleaf和spring6的整合依赖-->
        <dependency>
            <groupId>org.thymeleaf</groupId>
            <artifactId>thymeleaf-spring6</artifactId>
            <version>3.1.2.RELEASE</version>
        </dependency>
    </dependencies>

    <properties>
        <maven.compiler.source>21</maven.compiler.source>
        <maven.compiler.target>21</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

</project>
```

# SSM整合

## 创建包结构
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1711952550136-9bf37050-0666-41ea-8bd0-4e77c9f4c4e5.png#averageHue=%233f4345&clientId=ucab011ae-0d3f-4&from=paste&height=124&id=uebdf7be6&originHeight=124&originWidth=201&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3201&status=done&style=none&taskId=u1c8f6ce2-bd07-4c39-980e-95f3ceab9cc&title=&width=201)
## 创建webapp目录
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1711957803441-365c51d0-e046-4230-b02d-a1c192c599ae.png#averageHue=%2345536a&clientId=ua0f2ffef-430b-4&from=paste&height=60&id=ue83dc241&originHeight=60&originWidth=196&originalType=binary&ratio=1&rotation=0&showTitle=false&size=2552&status=done&style=none&taskId=u7b485e34-b1a4-4df6-beb7-18813cb3765&title=&width=196)

## Spring整合MyBatis

### 编写jdbc.properties
在类根路径（resources/）下创建属性配置文件，配置连接数据库的信息：jdbc.properties
```properties
jdbc.driver=com.mysql.cj.jdbc.Driver
jdbc.url=jdbc:mysql://localhost:3306/powernode?useUnicode=true&serverTimezone=Asia/Shanghai&useSSL=true&characterEncoding=utf-8
jdbc.username=root
jdbc.password=1234
```

### 编写DataSourceConfig

Spring 和 MyBatis 整合的时候，如果是基于XML配置文件的话，需要在spring配置文件中配置数据源dataSource，在config包下新建一个配置类DataSourceConfig：

```java
public class DataSourceConfig {
    @Value("${jdbc.driver}")
    private String driver;
    
    @Value("${jdbc.url}")
    private String url;
    
    @Value("${jdbc.username}")
    private String username;
    
    @Value("${jdbc.password}")
    private String password;

    @Bean
    public DataSource dataSource() {
        // 使用德鲁伊连接池
        DruidDataSource dataSource = new DruidDataSource();
        dataSource.setDriverClassName(driver);
        dataSource.setUrl(url);
        dataSource.setUsername(username);
        dataSource.setPassword(password);
        return dataSource;
    }
}
```

### 编写MyBatisConfig

在config包下新建一个MybatisConfig类：

```java
public class MybatisConfig {
    @Bean
    public SqlSessionFactoryBean sqlSessionFactoryBean(DataSource dataSource) {
        SqlSessionFactoryBean sqlSessionFactoryBean = new SqlSessionFactoryBean();
        sqlSessionFactoryBean.setDataSource(dataSource);
        sqlSessionFactoryBean.setTypeAliasesPackage("com.zsm.bean");
        return sqlSessionFactoryBean;
    }

    public MapperScannerConfigurer mapperScannerConfigurer() {
        MapperScannerConfigurer mapperScannerConfigurer = new MapperScannerConfigurer();
        mapperScannerConfigurer.setBasePackage("com.zsm.dao");
        return mapperScannerConfigurer;
    }
}
```

### 编写SpringConfig

在config包下新建一个SpringConfig类：

```java
// 标注该类是一个配置文件类
@Configuration
// 组件扫描
@ComponentScan("com.zsm.service")
// 属性配置文件位置
@PropertySource("classpath:jdbc.properties")
// 导入其他配置到spring配置
@Import({MybatisConfig.class, DataSourceConfig.calss})
public class SpringConfig {
}
```

## Spring整合Spring MVC
### 编写WebAppInitializer（web.xml）

在config包下新建一个WebAppInitializer类：

```java
public class WebAppInitializer extends AbstractAnnotationConfigDispatcherServletInitializer {
    // Spring的配置
    @Override
    protected Class<?>[] getRootConfigClasses() {
        return new Class[]{SpringConfig.class};
    }

    // SpringMVC的配置
    @Override
    protected Class<?>[] getServletConfigClasses() {
        return new Class[]{SpringMVCConfig.class};
    }

    // DispatcherServlet的<url-pattern>配置
    @Override
    protected String[] getServletMappings() {
        return new String[]{"/"};
    }
    // 配置过滤器
    @Override
    protected Filter[] getServletFilters() {
        // 配置字符编码过滤器
        CharacterEncodingFilter characterEncodingFilter = new CharacterEncodingFilter();
        characterEncodingFilter.setEncoding("UTF-8");
        characterEncodingFilter.setForceResponseEncoding(true);
        characterEncodingFilter.setForceRequestEncoding(true);
        // 配置HiddenHttpMethodFilter
        HiddenHttpMethodFilter hiddenHttpMethodFilter = new HiddenHttpMethodFilter();
        return new Filter[]{characterEncodingFilter, hiddenHttpMethodFilter};
    }
}
```


### 编写SpringMvcConfig

在config包下创建一个SpringMvcConfig类：

```java
@Configuration
@ComponentScan("com.zsm.handler")
@EnableWebMvc
public class SpringMvcConfig implements WebMvcConfigurer {

    // 以下三个方法合并起来就是开启视图解析器
    @Bean
    public ThymeleafViewResolver getViewResolver(SpringTemplateEngine springTemplateEngine) {
        ThymeleafViewResolver resolver = new ThymeleafViewResolver();
        resolver.setTemplateEngine(springTemplateEngine);
        resolver.setCharacterEncoding("UTF-8");
        resolver.setOrder(1);
        return resolver;
    }

    @Bean
    public SpringTemplateEngine templateEngine(ITemplateResolver iTemplateResolver) {
        SpringTemplateEngine templateEngine = new SpringTemplateEngine();
        templateEngine.setTemplateResolver(iTemplateResolver);
        return templateEngine;
    }

    @Bean
    public ITemplateResolver templateResolver(ApplicationContext applicationContext) {
        SpringResourceTemplateResolver resolver = new SpringResourceTemplateResolver();
        resolver.setApplicationContext(applicationContext);
        resolver.setPrefix("/WEB-INF/thymeleaf/");
        resolver.setSuffix(".html");
        resolver.setTemplateMode(TemplateMode.HTML);
        resolver.setCharacterEncoding("UTF-8");
        resolver.setCacheable(false);//开发时关闭缓存，改动即可生效
        return resolver;
    }

    // 开启静态资源处理，开启默认的Servlet处理
    @Override
    public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
        configurer.enable();
    }

    // 视图控制器
    @Override
    public void addViewControllers(ViewControllerRegistry registry) {}
    // 配置异常处理器
    @Override
    public void configureHandlerExceptionResolvers(List<HandlerExceptionResolver> resolvers) {}

    // 配置拦截器
    @Override
    public void addInterceptors(InterceptorRegistry registry) {}
}
```


## 添加事务控制
第一步：在SpringConfig中开启事务管理器
```java
@EnableTransactionManagement
public class SpringConfig {
}
```
第二步：在DataSourceConfig中添加事务管理器对象
```java
@Bean
public PlatformTransactionManager platformTransactionManager(DataSource dataSource){
    DataSourceTransactionManager dataSourceTransactionManager = new DataSourceTransactionManager();
    dataSourceTransactionManager.setDataSource(dataSource);
    return dataSourceTransactionManager;
}
```
第三步：在service类上添加如下注解：
```java
@Transactional
public class UserService {}
```


# 实现功能测试ssm整合
## 数据库表
![image-20240616092040941](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406160920054.png)

查看表的结构，封装成对象：

![image-20240616092139375](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406160921453.png)

## pojo类编写

在bean包下创建一个User类：

```java
public class User {
    private Long id;
    private String name;
    private String tel;
    private String address;

    public User() {
    }

    public User(Long id, String name, String tel, String address) {
        this.id = id;
        this.name = name;
        this.tel = tel;
        this.address = address;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", tel='" + tel + '\'' +
                ", address='" + address + '\'' +
                '}';
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getTel() {
        return tel;
    }

    public void setTel(String tel) {
        this.tel = tel;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
```


## dao编写

在dao包下添加一个UserDao接口，这个包下的类会自动扫描，所以不需要添加注解标注。

```java
public interface UserDao {
    @Select("select * from t_user wehere id = #{id}")
    User selectById(Long id);
}
```


## service编写

在service包下创建一个UserService接口：

```java
public interface UserService {
    /**
     * 根据id获取用户信息
     * @param id
     * @return
     */
    User getById(Long id);

}
```
然后在service/impl包下创建UserService的实现类UserServiceImpl：

```java
@Service
public class UserServiceImpl implements UserService {
    @Autowired
    public UserDao userDao;
    @Override
    public User getById(Long id) {
        return userDao.selectById(id);
    }
}
```


## handler编写

在handler包下创建一个UserHandler类，也就是一个controller：

```java
@RestController
@RequestMapping("/users")
public class UserHandler {
    @Autowired
    public UserService userService;

    @RequestMapping("/{id}")
    public User detail(@PathVariable("id") Long id) {
        User user = userService.getById(id);
        return user;
    }
}
```

使用的是@RestController注解，那么每个方法返回的就不是视图名称了，而是字符串数据。
## 前端发送ajax
### 引入js文件
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1711957985712-688287fe-084c-41ed-9938-79374005a147.png#averageHue=%233e4245&clientId=ua0f2ffef-430b-4&from=paste&height=102&id=uc272a66d&originHeight=102&originWidth=198&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3313&status=done&style=none&taskId=u8e02853c-864f-4add-b7fd-8a9b2628c6c&title=&width=198)
### 开启静态资源处理

在SpringMvcConfig类中：

```java
@Override
public void configureDefaultServletHandling(DefaultServletHandlerConfigurer configurer) {
    configurer.enable();
}
```

### 视图控制器

在SpringMvcConfig类中：

```java
public void addViewControllers(ViewControllerRegistry registry) {
    registry.addViewController("/").setViewName("index");
}
```
### 编写ajax
![image.png](https://cdn.nlark.com/yuque/0/2024/png/21376908/1711958191850-52d254f8-950b-4491-881f-3881f148d778.png#averageHue=%23435166&clientId=ua0f2ffef-430b-4&from=paste&height=65&id=uc2c9401a&originHeight=65&originWidth=203&originalType=binary&ratio=1&rotation=0&showTitle=false&size=2599&status=done&style=none&taskId=u64824efb-415e-48fd-a030-f34e5f0f920&title=&width=203)
```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>ssm整合</title>
    <!--引入vue-->
    <script th:src="@{/static/js/vue3.4.21.js}"></script>
    <!--引入axios-->
    <script th:src="@{/static/js/axios.min.js}"></script>
</head>
<body>
<div id="app">
    <button @click="getMessage">查看id=1的用户信息</button>
    <h1>{{message}}</h1>
</div>
<script th:inline="javascript">
    Vue.createApp({
        data(){
            return {
                message : ''
            }
        },
        methods : {
            async getMessage(){
                let response = await axios.get([[@{/}]] + 'users/1')
                this.message = response.data
            }
        }
    }).mount("#app")
</script>
</body>
</html>
```
测试结果：
![image-20240616095127795](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406160951724.png)



