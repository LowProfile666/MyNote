# SpringBoot

Spring Boot 是目前流行的微服务框架 倡导 约定优先于配置” 其设 目的是 用来简化新 Spring 应用的初
始化搭建以及开发过程。 Spring Boot 提供了很多核心的功 能，比如自动化配置 starter（启动器） 简化 Maven
配置、内嵌 Servlet 容器、应用监控等功能， 让我们可以快速构建企业级应用程序。
特性：

+ 创建独立的 Spring 应用程序。
+ 嵌入式 Tomcat、 Jetty、 Undertow 容器（jar）
+ 提供的 starters 简化构建配置（简化依赖管理和版本控制）
+ 尽可能自动配置 spring 应用和第三方库
+ 提供生产指标,例如指标、健壮检查和外部化配置
+ 没有代码生成，无需 XML 配置

SpringBoot 同时提供 “开箱即用”，“约定优于配置”的特性。

开箱即用：Spring Boot 应用无需从 0 开始，使用脚手架创建项目。基础配置已经完成。 集成大部分第三方库对象，无需配置就能使用。例如在 Spring Boot 项目中使用 MyBatis。可以直接使用 XXXMapper 对象， 调用方法执行 sql 语句。

约定优于配置：Spring Boot 定义了常用类，包的位置和结构，默认的设置。代码不需要做调整，项目能够按照预期运行。比如启动类在根包的路径下，使用了@SpringBooApplication 注解。创建了默认的测试类。controller，service，dao 应该放在根包的子包中。application 为默认的配置文件。

脚手架（spring 提供的一个 web 应用，帮助开发人员，创建 springboot 项目）

SpringBoot3 最小 jdk17， 支持 17-20.

Spring Boot 理念“约定优于配置”，也可称为按约定编程

## 与Spring的关系

Spring Boot 创建的是 Spring 应用，也就是使用 Spring 框架创建的应用程序。这里的 Spring是指 Spring Framework。 我们常说的 Spring，一般指 Spring 家族，包括 Spring Boot、Spring Framework 、SpringData ，Spring Security,Spring Batch , Spring Shell, Spring for Apache Kafka ....。

Spring Boot 是一个新的框架，看做是 Spring 框架的扩展，它消除了设置 Spring 应用程序所需的 XML 配置，为更快，更高效的创建 Spring应用提供了基础平台。Spring Boot 能够快速创建基于 Spring ，SpringMVC 的普通应用以及 Web 项目。

SpringBoot 是包含了 Spring 、SpringMVC 的高级的框架，提供了自动功能，短平快。能够更快的创建 Spring应用。消除了 Spring 的 XML 配置文件，提供了开发效率，消除 Spring 应用的臃肿。避免了大量的样板代码。

![image-20240704161158227](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041611280.png)

## 与SpringCloud的关系

微服务：微服务(Microservices Architecture)是一种架构和组织方法，微服务是指单个小型的但有业务功能的服务，每个服务都有自己的处理和轻量通讯机制，可以部署在单个或多个服务器上。

将一个大型应用的功能，依据业务功能类型，抽象出相对独立的功能，称为服务。每个服务就上一个应用程序，有自己的业务功能，通过轻量级的通信机制与其他服务通信（通常是基于 HTTP 的 RESTful API），协调其他服务完成业务请求的处理。 这样的服务是独立的，与其他服务是隔离的， 可以独立部署，运行。与其他服务解耦合。

微服务看做是模块化的应用，将一个大型应用，分成多个独立的服务，通过 http 或 rpc 将多个部分联系起来。请求沿着一定的请求路径，完成服务处理。

![image-20240704161507593](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041615628.png)

项目规模大，服务多。要构建大型的分布式应用，保证应用的稳定，高效，不间断的提供服务。Spring Cloud是对分布式项目提供了，有力的支持。

Spring Cloud 是一系列框架的有序的组合，为开发人员提供了快速构建分布式系统中常用工具(例如，配置管理、服务发现、断路器、智能路由、微代理、控制总线、一次性令牌、全局锁、领导选举、分布式会话、集群状态)。开发人员使用使用 Spring Cloud 这套框架和工具的集合可以快速建立实现分布式服务。这些框架需要使用Spring Boot 作为基础开发平台。

Spring Cloud 包含的这些框架和工具各负其职，例如 Spring Cloud Config 提供配置中心的能力，给分布式多个服务提供动态的数据配置，像数据库的 url，用户名和密码等，第三方接口数据等。 Spring Cloud Gateway 网关，提供服务统一入口，鉴权，路由等功能。

## SpringBoot3新特性

SpringBoot3 中的重大变化：
1）JDK 最小 Java 17,能够支持 17-20.
2）Spring Boot 3.0 已将所有底层依赖项从 Java EE 迁移到了 Jakarta EE API。原来 javax 开头的包名，修改为 jakarta。 例如 jakarta.servlet.http.HttpServlet 原来 javax.servlet.http.HttpServlet
3）支持 GraalVM 原生镜像。将 Java 应用编译为本机代码，提供显著的内存和启动性能改进。
4）对第三方库，更新了版本支持。
5）自动配置文件的修改。
6）提供新的声明式 Http 服务，在接口方法上声明@HttpExchange 获取 http 远程访问的能力。代替 OpenFeign
7）Spring HTTP 客户端提供基于 Micrometer 的可观察性. 跟踪服务，记录服务运行状态等
8）AOT（预先编译） 支持 Ahead Of Time，指运行前编译
9）Servlet6.0 规范
10）支持 Jackson 2.14。
11）Spring MVC :默认情况下使用的 PathPatternParser。删除过时的文件和 FreeMarker 、JSP 支持。

# 脚手架

脚手架是一种用在建筑领域的辅助工具，是为了保证建筑施工过程顺利进行而搭设的工作平台。软件工程中的脚手架是用来快速搭建一个小的可用的应用程序的骨架，将开发过程中要用到的工具、环境都配置好，同时生成必要的模板代码。

脚手架辅助创建程序的工具，Spring Initializr 是创建 Spring Boot 项目的脚手架。快速建立 Spring Boot 项目的最好方式。他是一个 web 应用，能够在浏览器中使用。IDEA 中继承了此工具，用来快速创建 Spring Boot 项目以及 Spring Cloud 项目。

Spring Initializr 脚手架的 web 地址： https://start.spring.io/

阿里云脚手架：https://start.aliyun.com/

## 使用脚手架创建项目

直接使用浏览器访问Spring Initializr 脚手架地址：

![image-20240704163803822](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041638901.png)

这会生成一个zip包，里面的内容是：

![image-20240704163845557](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041638635.png)

其中这个.mvn和mvnw等东西是为了在没有maven的环境中自动配置maven，如果已经配置好了maven的话，可以删除。

将这个下载下来，导入IDEA中，删除掉多余的东西后，项目结构：

![image-20240704164237468](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041642524.png)

+ Springboot3Application类是项目的启动类（入口类），该类中有主方法。
+ 有@SpringBootApplication注解标注的类就是启动类
+  [application.properties](..\..\..\MyCode\SpringBoot\springboot3\springboot3\src\main\resources\application.properties) 文件是默认的配置文件

## 使用IDEA中的脚手架创建项目

在IDEA中新建一个Moudle：

![image-20240704164919496](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041649550.png)

+ 创建Moudle时选择Spring Initializr
+ Server url 表示脚手架的访问地址

然后点击next开始配置依赖项：

![image-20240704165150752](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041651808.png)

+ 左上角是SpringBoot版本，这个版本可以在pom文件中手动修改

然后点击Create创建，创建出的项目的结构和使用网站下载的项目结构一样。

这是该项目的pom文件：

```xml
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter</artifactId>
    </dependency>

    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <optional>true</optional>
    </dependency>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>
</dependencies>
```

+ lombok依赖是创建项目时选的

spring-boot-starter这个依赖是Spring的依赖，SpringBoot项目必须直接或间接包含这个依赖。这个依赖是用来加载Spring框架相关的依赖。

# 代码结构

## 单一模块

项目只做某一个方面、某一个模块的功能。

一般的代码结构：

```java
com.zsm.模块名称
    +----Application.java 启动类
    +----controller 控制器包
        ---StudentController.java
        ---ScoreController.java
    +----service 业务层包
        ---inter 业务层接口
        ---impl 接口实现包
    +----repository 持久层包
    +----model 模型包
        ---entity 实体类包
	    ---dto 数据传输包
		---vo 视图数据包
```

比如，创建一个web项目，创建好后的初始结构：

![image-20240704171108066](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041711110.png)

这个Springboot004Application类中有@SpringBootApplication注解标注的，所以这是项目的启动类，启动类推荐放在根包之下。

然后在根包下创建controller包、service包（service包下又有inter包、impl包）、repository包（repository包中是访问数据库的）、model包（model包又有entity包、dto包等）：

![image-20240704171929696](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041719742.png)

## 多个模块

一个 Spring Boot 中多个模块。在根包下创建每个模块的子包， 子包中可以按“单一模块”包结构定义。

先创建一个项目：

![image-20240704172245567](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041722630.png)

启动类在根包下，在根包下创建独立的每个模块的子包，在每个子包的下面，根据功能分类，按照单一模块的结构建包：

![image-20240704172703099](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041727140.png)

# 运行项目

创建一个web项目：

![image-20240704173805768](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041738818.png)

在根包下创建controller包，包下定义一个controller：

```java
@RestController
public class HelloController {
    
    @RequestMapping("/hello")
    public String hello() {
        return "hello SpringBoot3 !";
    }
}
```

然后回到启动类中，点击启动类左边的运行符号即可启动项目：

![image-20240704174112585](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041741629.png)

启动后，控制台会有日志信息：

![image-20240704174344370](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041743439.png)

那么就可以访问localhost:8080/hello来访问到HelloController中的控制方法：

![image-20240704174457710](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041744749.png)

那么这个项目是如何运行的，如何将这个请求给到HelloController的？

## pom文件

从pom文件开始，有一个parent节点，是表示父项目的坐标：

```xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>3.3.1</version>
    <relativePath/> <!-- lookup parent from repository -->
</parent>
```

+ 表示当前SpringBoot项目的父是spring-boot-starter-parent，版本是3.3.1

接下来是当前项目的坐标：

```xml
<groupId>com.zsm</groupId>
<artifactId>springboot006</artifactId>
<version>0.0.1-SNAPSHOT</version>
<packaging>war</packaging>
```

然后是对项目的解释说明，这两个可以没有：

```xml
<name>springboot006</name>
<description>springboot006</description>
```

然后是jdk的版本：

```xml
<properties>
    <java.version>21</java.version>
</properties>
```

接着是依赖：

```xml
<dependencies>
    <!--Spring Web的启动依赖-->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>

    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <optional>true</optional>
    </dependency>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-tomcat</artifactId>
        <scope>provided</scope>
    </dependency>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>
</dependencies>
```

+ 依赖中有一个spring-boot-starter-tomcat，像这种带着starter的都叫做启动器
+ 以spring-boot-starter-开头的是Spring官方推出的启动器
+ 像xxx-starter的是非Spring官方的启动器，由其他组织推出

接着是插件：

```xml
<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
            <configuration>
                <excludes>
                    <exclude>
                        <groupId>org.projectlombok</groupId>
                        <artifactId>lombok</artifactId>
                    </exclude>
                </excludes>
            </configuration>
        </plugin>
    </plugins>
</build>
```

+ 这是SpringBoot的插件，用来、编译打包等

## starter

starter 是一组依赖描述（包含了相关技术所需要的其他的依赖），应用中包含 starter，可以获取 spring 相关技术的一站式的依赖和版本。不必复制、粘粘代码。通过 starter 能够快速启动并运行项目。
starter 包含：

+ 依赖坐标、版本
+ 传递依赖的坐标、版本
+ 配置类，配置项

## spring-boot-starter-parent

在当前的pom文件中，每个依赖都没有指定版本号，但是在maven管理器中又可以看到依赖的版本，这个版本信息就是来自父项目中的：

![image-20240704203506847](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407042035900.png)

pom.xml 中的<parent>指定 spring-boot-starter-parent 作为坐标，表示继承 Spring Boot 提供的父项目。从spring-boot-starter-parent 继承以获得合理的默认值和完整的依赖树，以便快速建立一个 Spring Boot 项目。 父项目提供以下功能：

+ JDK 的基准版本，比如<java.version>17</java.version>
+ 源码使用 UTF-8 格式编码
+ 公共依赖的版本
+ 自动化的资源过滤：默认把 src/main/resources 目录下的文件进行资源打包
+ maven 的占位符为‘@’
+ 对多个 Maven 插件做了默认配置，如 maven-compile-plugin，maven-jar-plugin

在当前项目的pom文件中，按住鼠标单击父项目的id，跳转到父项目的pom文件中，可以看到父项目中还有父项目，以及一些配置：

![image-20240704203845888](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407042038975.png)

在这个pom文件中，再点击过去它的父项目，可以看到大量的版本号：

![image-20240704204010241](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407042040353.png)

也可以不继承父项目来创建SpringBoot项目：

+ pom.xml 不继承 spring-boot-starter-parent，单独加入 spring-boot-dependencies 依赖，需要声明依赖管理的标签：

  ```xml
  <dependencyManagement>
      <dependencies>
          <dependency>
              <groupId>org.springframework.boot</groupId>
              <artifactId>spring-boot-dependencies</artifactId>
              <version>3.0.1</version>
              <type>pom</type>
              <scope>import</scope>
          </dependency>
      </dependencies>
  </dependencyManagement>
  ```

# 核心注解

在启动类上有一个注解@SpringBootApplication，这是一个复合注解：

![image-20240704204800868](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407042048927.png)

这三个注解具有什么作用，那么@SpringBootApplication就具有什么作用：

```
@SpringBootConfiguration
@EnableAutoConfiguration
@ComponentScan
```

## @SpringBootConfiguration

这个注解的源码：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Configuration
@Indexed
public @interface SpringBootConfiguration {
    @AliasFor(
        annotation = Configuration.class
    )
    boolean proxyBeanMethods() default true;
}
```

可以看到这个注解包含@Configuration注解的功能，而@Configuration注解的功能是配置类，结合@Bean注解能够将对象注入到Spring的Ioc容器中。那说明有@SpringBootConfiguration标注的类就是一个配置类。

而项目的启动类上的注解@SpringBootApplication包含了@SpringBootConfiguration，说明启动类也是一个配置类。那说明可以在启动类中声明对象：

```java
@SpringBootApplication
public class Springboot006Application {
	@Bean
	public Date myDate() {
		return new Date();
	}

	public static void main(String[] args) {
		SpringApplication.run(Springboot006Application.class, args);
	}

}
```

同时，那说明主方法中的run方法的第一个参数是配置类，这个配置类也被称为源，从这个源开始，加载当前项目需要的各种对象，从这个源开始，将需要的对象都创建好，注入容器之中。也就是说需要通过run方法来指明程序从哪个类开始运行。

## @EnableAutoConfiguration

这个注解的源码：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@AutoConfigurationPackage
@Import({AutoConfigurationImportSelector.class})
public @interface EnableAutoConfiguration {
    String ENABLED_OVERRIDE_PROPERTY = "spring.boot.enableautoconfiguration";

    Class<?>[] exclude() default {};

    String[] excludeName() default {};
}
```

该注解用来开启自动配置，将Spring和其他第三方库中对象创建好，注入到Spring的容器。避免了写xml，去掉样例代码。

## @ComponentScan

组件扫描器，主要用来扫描@Controller、@Service、@Repository、@Component注解，创建他们的对象注入到容器。

同时，SpringBoot约定：启动类作为扫描包的根（起点），也就是说，@ComponentScan会以当前启动类所在的包为起点，扫描该包下以及子包下所有的类，当前启动类在om.zsm.blog包下，就会扫描该包下所有类。

所以按照约定，就应该将启动类放在根包的下面，和其他子包同级。

所以，启动类中的run方法会通过这个启动类，将整个项目运行起来，准备整个项目的环境，并且返回创建好的容器对象，可以使用这个容器对象：

```java
@SpringBootApplication
public class Springboot006Application {
	@Bean
	public Date myDate() {
		return new Date();
	}

	public static void main(String[] args) {
		ApplicationContext applicationContext = SpringApplication.run(Springboot006Application.class, args);
		Date bean = applicationContext.getBean(Date.class);
	}
}
```

# 运行 Spring Boot 项目方式

三种方式：

+ 开发工具，例如 IDEA 执行 main 方法
+ Maven 插件 mvn spring-boot:run
+ java -jar jar 文件的路径

Spring Boot 项目可以打包为 jar 或者 war 文件。 因为 Spring Boot 内嵌了 web 服务器，例如 tomcat。能够以jar 方式运行 web 应用。 无需安装 tomcat 程序。

打包的时候，在pom文件中的build节点中，添加一个节点finalName，用来指定打包后生成的文件名。

## SpringBoot的jar包和普通jar包的区别

![image-20240704213217422](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407042132515.png)

在powershell中使用tree命令查看SpringBoot jar包结构：

![image-20240704213310044](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407042133224.png)

# 外部化配置

应用程序 = 代码 + 数据（数据库，文件，url）

应用程序的配置文件：Spring Boot 允许在代码之外，提供应用程序运行的数据，以便在不同的环境中使用相同的应用程序代码。避免硬编码，提供系统的灵活性。可使用各种外部配置源，包括 Java 属性文件、YAML（yml） 文件、环境变量和命令行参数。

项目中经常使用 properties 与 yaml 文件，其次是命令行参数。

## 配置文件基础

配置文件有两种格式分别：properies 和 yaml（yml）。properties 是 Java 中的常用的一种配置文件格式，`key=value`。key 是唯一的，文件扩展名为 properties。

yaml（YAML Ain't Markup Language）也看做是 yml，是一种做配置文件的数据格式，基本的语法 `key:[空格]值`。yml 文件文件扩展名是 yaml 或 yml（常用）。

yml基本语法规则：

+ 大小写敏感
+ 使用缩进表示层级关系
+ 缩进只可以使用空格，不允许使用 Tab 键
+ 缩进的空格数目不重要，相同层级的元素左侧对齐即可
+ #字符表示注释，只支持单行注释。#放在注释行的第一个字符

YAML 缩进必须使用空格，而且区分大小写，建议编写 YAML 文件只用小写和空格。

yml支持三种数据结构：

+ 对象：键值对的集合，又称为映射（mapping）/ 哈希（hashes） / 字典（dictionary）
+ 数组：一组按次序排列的值，又称为序列（sequence） / 列表（list）
+ 标量（scalars）：单个的、不可再分的值，例如数字、字符串、true|false 等

### application 文件

Spring Boot 同时支持 properties 和 yml 格式的配置文件。 配置文件名称默认是 application。我们可以使用application.properties , application.yml。

读取配置文件的 key 值，注入到 Bean 的属性可用@Value，@Value 一次注入一个 key 的值。将多个 key 值绑定到 Bean 的多个属性要用到@ConfigurationProperties 注解。在代码中访问属性除了注解，Spring 提供了外部化配置的抽象对象 Environment。Environment 包含了几乎所有外部配置文件，环境变量，命令行参数等的所有 key和 value。需要使用 Environment 的注入此对象，调用它的 getProperty(String key)方法即可。

Spring Boot 建议使用一种格式的配置文件，如果 properties 和 yml 都存在。properties 文件优先。推荐使用 yml文件。

application 配置文件的名称和位置都可以修改。约定名称为 application，位置为 resources 目录。

#### application.properties

创建一个新项目，默认的配置文件就是application.properties，在application.properties中编写：

```properties
# 默认的配置文件
user.name=zsm
user.age=10
user.sex=男
user.email=123456@com
```

然后在根包下创建一个包，包下创建一个service类，来通过@Value注解使用这些配置好的数据：

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

@Value用来读取单个值，参数是属性的key，如果指定的key没有对应的属性值，那么可以使用@Value(key:default)的格式来指定一个默认值。

然后使用测试方法：

```java
@SpringBootTest
class Springboot007ConfigApplicationTests {
	@Autowired
	UserService userService;

	@Test
	void testPrint() {
		userService.printInfo();
	}
}
```

+ 这个userService对象不要自己创建，自己创建的话，不受Spring的控制，不会给你自动注入属性，所以会输出null

会输出：

```java
20620 男 123456@com 10 JCUT
```

可以看到address在application.properties文件中没有指定，但是他有一个默认值JCUT；同时看到name属性输出的并不是属性文件中的值，而是本机系统的名字，所以这个user.name最好是换一个名字，否则会和本机的环境变量冲突。

如果没有指定的key，又没有指定的默认值，那么程序就会报错。

#### application.yml

将上面的application.properties改为application.yml格式。

在resources目录下，新建一个application.yml文件：

```yaml
# 编写配置 key: value
user:
  username: zsssm
  age: 20
  emial: 111111@qq.com
  ses: 男
```

像在properties文件中的user.username这样的是有层级关系的，user是第一层，username是第二层，在yaml中就要像以上这种写法来区分层级。

这种格式叫做扁平化处理。Spring Boot 对 yml 文件的内容进行扁平化处理。将 yml 中的内容看做和 properties 中的格式一样处理。也就是user:username 看做是 user.username。 所以在程序中 Spring Boot 认为 properties 和 yml 是一样的。

然后先将application.properties文件删除或改名，因为当这两个配置文件同时出现时，application.properties的优先级更高，然后重新测试输出结果：

```java
zsssm 男 111111@qq.com 20 JCUT
```

这两种文件只有编写格式不一样。

注意：yaml的格式是 `key: value`，冒号后面必须要有空格，如果没有会报错：

![image-20240705090432499](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407050904650.png)

### Environment

Environment 是外部化的抽象，是多种数据来源的集合。从中可以读取 application 配置文件，环境变量，系统属性。使用方式在 Bean 中注入 Environment。调用它的 getProperty(key)方法。

新建一个类，使用Environment对象：

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

+ `getProperty(key)`：用来获取指定key的值
+ `getProperty(key, class, defaultVlaue)`：用来获取指定key的值，并且将结果转为指定的class类型，同时如果没有该key没有值会赋值默认值defaultValue
+ `containsProperty(key)`：用来判断是否有某个key

然后测试：

```java
@SpringBootTest
class Springboot007ConfigApplicationTests {
	@Autowired
	Config config;

	@Test
	void testPrint() {
		config.print();
	}
}
```

输出结果是：

```java
不存在
读取的值：username=zsm, address=JJJJJCUT
```

同样，当application.properties和application.yml文件同时存在时，优先级更高的是application.properties。

### 组织多文件

大型集成的第三方框架，中间件比较多。每个框架的配置细节相对复杂。如果都将配置集中到一个 application 文件，导致文件内容多，不易于阅读。我们将每个框架独立一个配置文件，最后将多个文件集中到 application。我们使用导入文件的功能。

在resources目录下创建一个文件夹config，在下面创建两个配置文件redis.yml和mysql.yml：

redis.yml：

```yaml
spring:
  redis:
    host: 192.168.1.1
    port: 3333
    password: 123456
```

mysql.yml：

```yaml
spring:
  mysql:
    url: jdbc:mysql://localhost:3306/db
    username: root
    password: 1234
```

这两个配置文件里的key名字和层级都可以自己随便写。

然后在application.yml文件中进行导入：

```yaml
# 编写配置 key: value
user:
  username: zsssm
  age: 20
  email: 111111@qq.com
  sex: 男

# 导入其他配置
spring:
  config:
    import: config/mysql.yml, config/redis.yml
```

+ 这个导入的格式必须这么写：spring.config.import，少一个都会报错。

导入多个文件时，使用逗号分割。现在加载了application.yml文件后，就会一起加载导入进来的配置文件。

然后新建一个类来测试：

```java
@Service
public class MultiConfigService {
    @Value("${spring.redis.host}")
    private String redisHost;
    @Value("${spring.redis.port}")
    private String redisPort;
    @Value("${spring.mysql.url}")
    private String mysqlUrl;
    @Value("${spring.mysql.username}")
    private String mysqlUsername;

    public void print() {
        System.out.println(redisHost + " " + redisPort);
        System.out.println(mysqlUrl + " " + mysqlUsername);
    }
}
```

测试：

```java
@SpringBootTest
class Springboot007ConfigApplicationTests {
	@Autowired
	MultiConfigService multiConfigService;

	@Test
	void testPrint() {
		multiConfigService.print();
	}
}
```

输出结果：

```yaml
192.168.1.1 3333
jdbc:mysql://localhost:3306/db root
```

### 多环境配置

软件开发中经常提到环境这个概念，与日常生活中的环境概念一样。环境影响居住体验。影响软件运行的也叫做环境，例如应用中访问数据库的 ip，用户名和密码，Redis 的端口，配置文件的路径，windows，linux 系统，tomcat 服务器等等。围绕着程序周围的都是环境。环境影响软件的运行。

Spring Profiles 表示环境，Profiles 有助于隔离应用程序配置，并使它们仅在某些环境中可用。常说开发环境，测试环境，生产环境等等。一个环境就是一组相关的配置数据， 支撑我们的应用在这些配置下运行。应用启动时指定适合的环境。开发环境下每个开发人员使用自己的数据库 ip，用户，redis 端口。 同一个程序现在要测试了。需要把数据库 ip，redis 的改变为测试服务器上的信息。 此时使用多环境能够方便解决这个问题。

Spring Boot 规定环境文件的名称 application-{profile}.properties(yml)。其中 profile 为自定义的环境名称，推荐使用 dev 表示开发 ，test 表示测试。prod 表示生产，feature 表示特性。总是 profile 名称是自定义的。Spring Boot会加载 application 以及 application-{profile}两类文件，不是只单独加载 application-{profile}。

准备两个环境，开发环境（application-dev.yml）和测试环境（application-test.yml），在resources目录下直接创建配置环境文件。

application-dev.yml：

```yaml
myapp:
  desc: 这是开发环境的配置文件

# 指定环境名称
spring:
  config:
    activate:
      on-profile: dev
```

指定环境名称的写法是固定的，必须是：spring.config.activate.on-profile，名称推荐和application-dev中的名字相同。当项目激活的环境是dev时，这个环境起作用。

application-test.yml：

```yaml
myapp:
  desc: 这是测试环境的配置文件

spring:
  config:
    activate:
      on-profile: test
```

配置文件创建好后，需要去applicaton.yml中激活某个环境。

```yaml
spring:
  config:
    # 导入其他配置
    import: config/mysql.yml, config/redis.yml
  # 激活某个配置文件（环境）
  profiles:
    active: dev
```

这个激活的写法也是固定的：spring.profiles.active

默认是激活的是default环境，可以在项目启动的日志看到以下信息：

![image-20240705100045357](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407051000478.png)

然后创建一个类来测试：

```java
@Service
public class MultiEnvironmentService {
    @Value("${myapp.desc}")
    private String desc;

    public void print() {
        System.out.println(desc);
    }
}
```

测试：

```java
@SpringBootTest
class Springboot007ConfigApplicationTests {
	@Autowired
	MultiEnvironmentService multiEnvironmentService;

	@Test
	void testPrint() {
		multiEnvironmentService.print();
	}
}
```

输出结果：

```java
这是开发环境的配置文件
```

可以看到启动时的环境：

![image-20240705100644076](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407051006171.png)

## 绑定bean

@Value 绑定单个属性，当属性较多时不方便，Spring Boot 提供了另一种属性的方法。将多个配置项绑定到 Bean 的属性，提供强类型的 Bean。Bean 能够访问到配置数据。

基本原则：标准的 Java Bean 有无参数构造方法，包含属性的访问器。配合@ConfigurationProperties 注解一起使用。Bean 的 static 属性不支持。

Spring Boot 自动配置中大量使用了绑定 Bean 与@ConfigurationProperties，提供对框架的定制参数。项目中要使用的数据如果是可变的，推荐在 yml 或 properties 中提供。项目代码具有较大的灵活性。

@ConfigurationProperties 能够配置多个简单类型属性，同时支持 Map，List，数组类型。对属性还能验证基本格式。

### 简单的属性绑定

还是用之前的application.yml文件：

```yaml
# 编写配置 key: value
user:
  username: zsssm
  age: 20
  email: 111111@qq.com
  sex: 男
```

然后编写一个Bean，属性名都和上面的key相同：

```java
@Component
@ConfigurationProperties(prefix = "user")
public class UserBean {
    private String username;
    private String email;
    private Integer age;
    private String sex;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }
    @Override
    public String toString() {
        return "UserBean{" +
                "username='" + username + '\'' +
                ", email='" + email + '\'' +
                ", age=" + age +
                ", sex='" + sex + '\'' +
                '}';
    }
}
```

+ @ConfigurationProperties 声明在类上，表示绑定属性到此类。prefix 表示前缀，是配置文件中多个 key 的公共前
  缀。这些 key 以“.”作为分隔符。比如user.username，这里的前缀就是user。
+ prefix=”user”, 将文件中 user 开始的 key 都找到，调用与 key 相同名称的 setXxx 方法。如果有给属性赋值成功。没有的忽略。
+ 属性的名称和key的名称相同，框架会调用setXxx方法给属性赋值
+ @ConfigurationProperties不能单独使用，会报错，因为这个注解只负责绑定属性，不负责创建对象，所以可以使用@Component注解消除这个错误（一种解决方法），也可以使用@Configuration注解

测试：

```java
@SpringBootTest
class Springboot007ConfigApplicationTests {
	@Autowired
	UserBean userBean;

	@Test
	void testPrint() {
		System.out.println(userBean);
	}
}
```

输出结果：

```java
UserBean{username='zsssm', email='111111@qq.com', age=20, sex='男'}
```

注意：对static属性无效。

如果UserBean这个类使用的是@Configuration注解来标注他是一个配置类的话，此时的userBean其实是一个代理对象，可以输出他的反射类查看：

```java
System.out.println(userBean.getClass());  // class com.zsm.bean.UserBean$$SpringCGLIB$$0
```

如果UserBean这个类使用的是@Conponent注解来标注的话，那他就是一个普通的bean，结果是：

```java
System.out.println(userBean.getClass());  // class com.zsm.bean.UserBean
```

使用@Configuration注解也可以将他当成一个普通的bean，需要使用一个参数：

```java
@Configuration(proxyBeanMethods = false)
```

这样就会只是一个普通bean，而不是代理对象：

```java
System.out.println(userBean.getClass());  // class com.zsm.bean.UserBean
```

这样创建的UserBean速度更快。

### 嵌套Bean

Bean 中包含其他 Bean 作为属性，将配置文件中的配置项绑定到 Bean 以及引用类型的成员。Bean 的定义无特殊要求。

在UserBean中加一个属性address，这个address也是一个单独的类，创建这个Address：

```java
public class Address {
    private String city;
    private String address;

    @Override
    public String toString() {
        return "AddressBean{" +
                "city='" + city + '\'' +
                ", address='" + address + '\'' +
                '}';
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
```

修改UserBean，给他添加一个属性：

```java
@Configuration(proxyBeanMethods = false)
@ConfigurationProperties(prefix = "user")
public class UserBean {
    private String username;
    private String email;
    private Integer age;
    private String sex;
    private Address address;

    @Override
    public String toString() {
        return "UserBean{" +
                "username='" + username + '\'' +
                ", email='" + email + '\'' +
                ", age=" + age +
                ", sex='" + sex + '\'' +
                ", address=" + address +
                '}';
    }

    public AddressBean getAddress() {
        return address;
    }

    public void setAddress(AddressBean address) {
        this.address = address;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }
}
```

然后在application.yml文件中添加address：

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

+ 这个address还是和UserBean中的属性名一样
+ address下的key和Address类中的属性名一样

测试：

```java
@SpringBootTest
class Springboot007ConfigApplicationTests {
	@Autowired
	UserBean userBean;

	@Test
	void testPrint() {
		System.out.println(userBean);
	}
}
```

输出结果：

```yaml
UserBean{username='zsssm', email='111111@qq.com', age=20, sex='男', address=Address{city='湖北荆门', address='象山大道33号'}}
```

### 扫描注解

在上面的Bean类中，@ConfigurationProperties 注解起作用需要和@Configuration或@Component注解一起使用，还可以使用其他的注解来配合使用，@EnableConfigurationProperties 或@ConfigurationPropertiesScan。

这两个注解是专门用来扫描寻找@ConfigurationProperties 注解的，将他的对象注入到 Spring 容器，在启动类上使用扫描注解。

删除UserBean上的@Configuration注解，观察报错 ：

![image-20240705105453684](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407051054833.png)

报错中提示到了@EnableConfigurationProperties和@ConfigurationPropertiesScan这两个注解，接着在启动类上使用这两个注解。

@EnableConfigurationProperties：

这是源码：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Import({EnableConfigurationPropertiesRegistrar.class})
public @interface EnableConfigurationProperties {
    String VALIDATOR_BEAN_NAME = "configurationPropertiesValidator";

    Class<?>[] value() default {};
}
```

有一个value属性，是一个数组，用来指定类的Class，使用：

```java
@EnableConfigurationProperties(UserBean.class)
@SpringBootApplication
public class Springboot007ConfigApplication {
	public static void main(String[] args) {
		SpringApplication.run(Springboot007ConfigApplication.class, args);
	}
}
```

+ @EnableConfigurationProperties：启用ConfigurationProperties，参数是类，是一个数组，可以写多个类名。

@ConfigurationPropertiesScan：

这是源码：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Import({ConfigurationPropertiesScanRegistrar.class})
@EnableConfigurationProperties
public @interface ConfigurationPropertiesScan {
    @AliasFor("basePackages")
    String[] value() default {};

    @AliasFor("value")
    String[] basePackages() default {};

    Class<?>[] basePackageClasses() default {};
}
```

有两个属性都是数组可以指定多个包名，使用：

```java
// @ConfigurationPropertiesScan("com.zsm.bean")
@ConfigurationPropertiesScan(basePackages = { "com.zsm.bean" })
@SpringBootApplication
public class Springboot007ConfigApplication {
	public static void main(String[] args) {
		SpringApplication.run(Springboot007ConfigApplication.class, args);
	}
}
```

### 处理第三方库对象

上面的例子都是在源代码中使用@ConfigurationProperties 注解，如果某个类需要在配置文件中提供数据，但是没有源代码。此时@ConfigurationProperties 结合@Bean 一起在方法上面使用。

假如现在有一个第三方库的类Security：

```java
public class Security {
    private String username;
    private String password;

    @Override
    public String toString() {
        return "Security{" +
                "username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
```

现在要提供它的 username，password 属性值，在application.yml中配置：

```yaml
security:
  username: root
  password: 1234
```

然后假设创建一个配置类，在这个配置类中需要创建Security对象：

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

+ 使用@Bean创建bean对象，使用@ConfigurationProperties指定属性值来自配置文件
+ 他会将配置文件中以security开头的key的值赋给对象的属性。

测试：

```java
@Autowired
Security security;

@Test
void testPrint() {
    System.out.println(security);
}
```

输出结果：

```java
Security{username='root', password='1234'}
```

### 集合 Map，List 以及 Array

Map，List 以及 Array 都能提供配置数据。

创建一个User类：

```java
public class User {
    private String name;
    private String sex;
    private Integer age;
    // getter setter toString()
}
```

创建一个MyServer类：

```java
public class MyServer {
    private String title;
    private String ip;
    // getter setter toString()
}
```

配置数组数据，使用 `-` 表示一个成员，在application.yml中：

```yaml
names:
  - zhangsn
  - lisi
  - wnagwu
```

+ 注意：`-` 后面要有空格，没有空格的话会把 -zhangsan 当作一个值

+ 如果不写 `-` 的话也可以，但是必须所有的元素都不能写 `-`：

  ```yaml
  names:
    zhangsn
    list
    wnagwu
  ```

创建一个CollectuinConfig类：

```java
@ConfigurationProperties
public class CollectionConfig {
    private List<MyServer> servers;
    private Map<String, User> users;
    private String[] names;

    // getter setter toString()
}
```

+ 这里的@ConfigurationProperties注解不需要指定前缀，因为没有前缀

然后测试：

```java
@Autowired
CollectionConfig config;

@Test
void testPrint() {
	System.out.println(config);
}
```

输出结果：

```yaml
CollectionConfig{servers=null, users=null, names=[zhangsn list wnagwu]}
```

然后配置List<MyServer>的数据，这个集合中每个元素都是MySever类，MySever类有两个属性，所以要都配置：

```yaml
servers:
  - title: 服务器1
    ip: 1.1.1.1
  - title: 服务器2
    ip: 2.2.2.2
```

+ 一个 `-` 表示一个元素

输出结果：

```yaml
CollectionConfig{servers=[MyServer{title='服务器1', ip='1.1.1.1'}, MyServer{title='服务器2', ip='2.2.2.2'}], users=null, names=[zhangsn list wnagwu]}
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

+ 这配置了两个User对象
+ 在map集合中，会有两个key，分别是user1和user2，对应着张三和李四两个User对象

输出结果：

```yaml
CollectionConfig{servers=[MyServer{title='服务器1', ip='1.1.1.1'}, MyServer{title='服务器2', ip='2.2.2.2'}], users={user1=User{name='张三', sex='男', age=23}, user2=User{name='李四', sex='女', age=21}}, names=[zhangsn list wnagwu]}
```

### 指定数据源文件

application 做配置是经常使用的，除此以外我们能够指定某个文件作为数据来源。@PropertySource 注解，用以加载指定的 properties 文件。也可以是 XML 文件（无需了解）。@PropertySource 与@Configuration 一同使用，其他注解还有@Value、@ConfigurationProperties。

在resources下新建一个user-info.properties文件：

```properties
user.username=zsm
user.age=10
user.sex=男
user.email=123456@com
```

然后在UserBean类上使用：

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

+ @PropertySource("classpath:/user-info.properties")表示数据源文件的位置，在类路径下

测试：

```java
@Autowired
UserBean userBean;

@Test
void testPrint() {
    System.out.println(userBean);
}
```

输出结果：

```java
UserBean{username='zsm', email='123456@com', age=10, sex='男', address=null}
```

+ 注意，如果application.yml或application.properties中有user.username等数据的话，还是会优先使用application中的数据

总结：

+ @ConfigurationProperties 绑定 Bean 对于使用配置文件的数据是十分方便，灵活的。也支持对数据的校验，校验是 JSR303 规范中的注解
+ Bean 定义结合 Lombok 会更加方便。

## 创建对象三种方式

将对象注入到 Spring 容器，可以通过如下方式：

+ 传统的 XML 配置文件
+ Java Config 技术， @Configuration 与@Bean
+ 创建对象的注解，@Controller ，@Service ， @Repository ，@Component

Spring Boot 不建议使用 xml 文件的方式， 自动配置已经解决了大部分 xml 中的工作了。如果需要 xml 提供 bean的声明，@ImportResource 加载 xml 注册 Bean。

在resources下创建一个xml文件，applicationContex.xml：

```java
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean class="com.zsm.bean.User" id="user">
        <property name="name" value="ZhangSan" />
        <property name="age" value="20" />
        <property name="sex" value="男" />
    </bean>
</beans>
```

这个User类是之前写过的：

```java
public class User {
    private String name;
    private String sex;
    private Integer age;
    // getter setter toString()
}
```

然后如何引入这个配置文件，在启动类中加入注解@ImportResource，这个注解用来加载一个或多个配置文件，它的源代码：

```java
@Retention(RetentionPolicy.RUNTIME)
@Target({ElementType.TYPE})
@Documented
public @interface ImportResource {
    @AliasFor("locations")
    String[] value() default {};

    @AliasFor("value")
    String[] locations() default {};

    Class<? extends BeanDefinitionReader> reader() default BeanDefinitionReader.class;
}
```

locations和value都用来指定配置文件的路径。

在启动类中导入配置，并且在主方法中可以通过容器拿到这个Bean测试：

```java
@ImportResource("classpath:/applicationContext.xml")
@ConfigurationPropertiesScan(basePackages = { "com.zsm.config" })
@SpringBootApplication
public class Springboot007ConfigApplication {

	public static void main(String[] args) {
		ApplicationContext applicationContext = SpringApplication.run(Springboot007ConfigApplication.class, args);
		Object user = applicationContext.getBean("user");
		System.out.println(user);
	}

}
```

输出结果：

```java
User{name='ZhangSan', sex='男', age=20}
```

## AOP

AOP(Aspect Oriented Programming):面向切面编程，保持原有代码不变，能够给原有的业务逻辑增加二维的功能。AOP 增加的功能是开发人员自己编写的，底层是动态代理实现功能的增强。对于扩展功能十分有利。Spring的事务功能就是在 AOP 基础上实现的， 业务方法在执行前【开启事务】，在执行业务方法，最后【提交或回滚失败】。

+ Aspect：表示切面，开发自己编写功能增强代码的地方，这些代码会通过动态代理加入到原有的业务方法中。

  @Aspect 注解表示当前类是切面类。 切面类是一个普通类。

+ Joinpoint：表示连接点，连接切面和目标对象。或是一个方法名称，一个包名，类名。在这个特定的位置执行切面中的功能代码。

+ 切入点（Pointcut）：其实就是筛选出的连接点。一个类中的所有方法都可以是 JoinPoint, 具体的那个方法要增加功能，这个方法就是 Pointcut。

+ Advice：翻译是通知，也叫做增强。表示增强的功能执行时间。 Java 代码执行的单位是方法，方法是业务逻辑代码，在方法之前增加新的功能，还是方法之后增加功能。 表示在方法前，后等的就是通知。

  主要包括 5 个注解：@Before，@After，@AfterReturning，@AfterThrowing，@Around。注解来自 aspectj 框架。

  + @Before：在切点方法之前执行。

  + @After：在切点方法之后执行

  + @AfterReturning：切点方法返回后执行

  + @AfterThrowing：切点方法抛异常执行

  + @Around：属于环绕增强，能控制切点执行前，执行后。功能最强的注解。

+ Target Object: 目标对象。 在 A 类的 print()方法执行前， 输出方法的执行时间。 也就是给 A 这个对象增加了“输出执行时间的功能”

AOP 技术主要的实现一个是 Spring 框架，Spring Boot 当然支持 AOP；另一个是功能全面的 AspectJ 框架。SpringBoot 执行 AspectJ 框架。使用@Before，@After，@AfterReturning，@AfterThrowing，@Around 注解的方式就来自 AspectJ 框架的功能。

需要使用AOP，先要加入依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-aop</artifactId>
</dependency>
```

+ 包含了 aop 和 aspectj 依赖

目前有一个Service：

```java
public interface AService {
    void query(Integer id);
    void save(String name, String code);
}
```

和他的实现类：

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

现在要在这个service的两个方法调用时输出日志，使用aop最合适。

接下来创建切面类，是一个普通类，在这个类中写功能增强的方法：

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
+ `DateTimeFormatter` 类是 Java 中用于格式化和解析日期时间对象的重要类之一。它允许你定义日期时间的输出格式，以便将日期时间对象转换为字符串，或者将字符串解析为日期时间对象。
+ `LocalDateTime` 类是 Java 8 中引入的一部分，用于表示日期和时间但不包含时区信息。它结合了 `LocalDate` 和 `LocalTime` 类的功能，提供了一种方便的方法来处理日期和时间。
+  @Before("execution(* com.zsm.aop.service..*.*(..))")这个注解的意思是：在 `com.zsm.aop.service` 包及其子包中的任意类的任意方法执行之前，执行前置通知中的代码。

然后测试：

```java
@SpringBootTest
class Spring008AopApplicationTests {

	@Autowired
	AService aService;
	@Test
	void test01() {
		aService.save("aaa", "123");
		aService.query(1);
	}
}
```

输出结果：

```java
日志：{2024-07-05 15:11:26|save|aaa|123}
AService 业务方法 save 执行了
日志：{2024-07-05 15:11:26|query|1}
AService 业务方法 query 执行了
```

