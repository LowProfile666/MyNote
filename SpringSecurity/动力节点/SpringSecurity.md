# 1、不使用SpringSecurity

新建一个普通项目，手动改造成SpringBoot项目，引入以下依赖：

```xml
<parent>
    <artifactId>spring-boot-starter-parent</artifactId>
    <groupId>org.springframework.boot</groupId>
    <version>2.6.13</version>
    <relativePath/> <!-- lookup parent from repository -->
</parent>

<properties>
    <java.version>21</java.version>
</properties>

<dependencies>
    <!--springboot web 程序 -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <!--springboot 单元测试-->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>
    <!--自动生成get、set和日志对象的lombok-->
    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <optional>true</optional>
    </dependency>
</dependencies>
<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>
```

创建启动类com.zsm.Application：

```java
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```

接着创建三个controller，对应着三种身份：

学生：

```java
@RestController
@RequestMapping("/student")
public class StudentController {
    @GetMapping("/query")
    public String queryInfo(){
        return "I am a student,My name is Eric!";
    }
}
```

老师：

```java
@RestController
@RequestMapping("/teacher")
public class TeacherController {
    @GetMapping("/query")
    public String queryInfo(){
        return "I am a teacher,My name is Thomas!";
    }
}
```

管理员：

```java
@RestController
@RequestMapping("/admin")
public class AdminController {
    @GetMapping("/query")
    public String queryInfo(){
        return "I am a administrator, My name is Obama!";
    }
}
```

然后启动项目，可以随意访问这三个路径：

```
http://localhost:8080/admin/query
http://localhost:8080/teacher/query
http://localhost:8080/student/query
```

也可以通过在gitbash中使用curl命令来访问：

```bash
curl -X GET localhost:8080/admin/query
```

![image-20240713210621765](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132106443.png)

+ curl 后加 `-X 请求方式`  可以发送对应的请求，不加 -X 默认就是发get请求

+ curl 加 -v 可以查看具体的请求过程

  ![image-20240713211139034](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132111077.png)

+ curl 的学习地址：

  https://catonmat.net/cookbooks/curl

  https://www.ruanyifeng.com/blog/2019/09/curl-reference.html

  https://www.ruanyifeng.com/blog/2011/09/curl.html

  https://blog.csdn.net/angle_chen123/article/details/120675472

此示例说明：**没有加入安全框架的springboot web程序，默认所有资源均不受保护。**

我们的项目很多资源必须被保护起来，如何保护？**引入安全框架**

# 2、认证授权等基本概念

## 2.1 认证（authentication）

系统为什么要认证？认证是为了保护系统的隐私数据与资源，用户的身份合法方可访问该系统的资源。

什么是认证（登录）？认证 ：**用户认证就是判断一个用户的身份是否合法的过程。**

常见的用户身份认证方式

+ 用户名密码登录
+ 二维码登录
+ 手机短信登录
+ 指纹认证
+ 人脸识别
+ 等等...

## 2.2 会话（session）

### 2.2.1 什么是会话

用户认证通过后，为了避免用户的每次操作都进行认证可将用户的信息保存在会话中。会话就是系统为了保持当前用户的登录状态所提供的机制，**常见的有基于****session****方式、基于token****方式**等。

### 2.2.2 基于session的认证方式

它的交互流程是，用户认证成功后，在服务端生成用户相关的数据保存在session(当前会话)中，发给客户端的sesssion_id 存放到 cookie 中，这样用户客户端请求时带上 session_id 就可以验证服务器端是否存在 session 数据，以此完成用户的合法校验，当用户退出系统或session过期销毁时,客户端的session_id也就无效了，但是服务器端的session未必被删除了，只不过是客户端的session_id丢失了，就拿不到服务器端之前的会话数据了。

cookie可以在请求体中看到：

![image-20240713213034456](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132130523.png)

### 2.2.3 基于token的认证方式

token叫做令牌，一般就是一个字符串。

它的交互流程是，用户认证成功后，服务端生成一个token发给客户端，客户端可以放到 cookie 或 localStorage等存储中，每次请求时带上 token，服务端收到token通过验证后即可确认用户身份。可以使用Redis 存储用户信息（分布式中**共享session**）。

+ cookie在每次请求对应网站时会被自动携带
+ localStorage中的数据不会被自动携带，需要程序员写代码

基于session的认证方式由Servlet规范定制，服务端要存储session信息需要占用内存资源，客户端需要支持cookie；基于token的方式则一般不需要服务端存储token，并且不限制客户端的存储方式。**如今移动互联网时代更多类型的客户端需要接入系统，系统多是采用前后端分离的架构进行实现，所以基于token的方式更适合**。

## 2.3 授权(authorization)

**authe**ntication是认证，**autho**rization是授权。

### 2.3.1 为什么要授权（控制资源被访问）？

因为不同的用户可以访问的资源是不一样的。

### 2.3.2 什么是授权（给用户颁发权限）

授权： **授权是用户认证通过后，根据用户的权限来控制用户访问资源的过程。**

**拥有资源的访问权限则正常访问，没有权限则拒绝访问。**

## 2.4 RBAC（Role-Based Access Control） 基于角色的访问控制

![img](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132118089.jpg)

用户，角色，权限 本质：就是把权限打包给角色（角色拥有一组权限），分配给用户（用户拥有多个角色）。

最少包括五张表 （用户表、角色表、用户角色表、权限表、角色权限表）

# 3 java的安全框架实现

主要有三种方式：

+ Shiro：轻量级的安全框架，提供认证、授权、会话管理、密码管理、缓存管理等功能 
+ Spring Security：功能比Shiro强大，更复杂，权限控制细粒度更高，对OAuth2 支持更好，与Spring 框架无缝集合，使Spring Boot 集成很快捷。
+ 自己写：基于过滤器（filter）和AOP来实现，难度大，没必要。  

# 4 Spring Security

## 4.1 什么是Spring Security

Spring Security是一个能够为基于Spring的企业应用系统提供**声明式（注解）的安全访问控制解决方案的安全框架**。它提供了一组可以在Spring应用上下文中配置的Bean，充分利用了Spring IoC，DI（控制反转Inversion of Control ,DI:Dependency Injection 依赖注入）和AOP（面向切面编程）功能，为应用系统提供声明式的安全访问控制功能，减少了为企业系统安全控制编写大量重复代码的工作。 

以上解释来源于百度百科。可以一句话来概括：

  **SpringSecurity** **是一个安全框架**。  

## 4.2 官方网址

  https://spring.io/projects/spring-security  

![image-20240713220907912](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132209012.png) 

# 5 认证入门

## 5.1 安全入门项目

新建一个项目，手动构建SpringBoot项目，创建启动类。

引入依赖：

```xml
<parent>
    <artifactId>spring-boot-starter-parent</artifactId>
    <groupId>org.springframework.boot</groupId>
    <version>2.6.13</version>
    <relativePath/> <!-- lookup parent from repository -->
</parent>

<properties>
    <java.version>21</java.version>
</properties>

<dependencies>
    <!--springboot web 程序 -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <!--springboot 单元测试-->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>
    <!--自动生成get、set和日志对象的lombok-->
    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <optional>true</optional>
    </dependency>
</dependencies>
<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>
```

还要引入SpringSecurity启动器：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-security</artifactId>
</dependency>
```

将第一个项目中的三个controller复制到该项目中，启动项目，访问任意一个controller。

### 5.1.1 登录

比如访问http://localhost:8080/admin/query，现在需要登录：

![image-20240713222229955](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132222025.png)

用户名是user，密码会输出在控制台中：

![image-20240713222401122](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132224178.png)

+ 这个密码就是一个UUID，用四个横线隔开的36位字符。

登录成功后，就会跳转到http://localhost:8080/admin/query页面，并且现在访问其他的两个controller也都可以正常访问。

使用curl访问：

![image-20240713223027725](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132230777.png)

+ -u 参数指定用户名和密码

### 5.1.2 登出

访问http://localhost:8080/logout可以退出登录：

![image-20240713223321948](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132233012.png)

退出登录之后，再访问项目中的资源就会又需要登录。

### 5.1.3 结论

引入spring-boot-starter-security依赖后，项目中除登录退出外所有资源都会被保护起来。

**认证（登录）用户可以访问所有资源，不经过认证用户任何资源也访问不了。**

### 5.1.4 问题

所有资源均已保护，但是用户只用一个，密码是随机的，只能在开发环境使用；

## 5.2 使用配置文件配置用户名和密码

### 5.2.1 新建配置文件application.yml

在resources下创建application.xml文件，添加spring security 配置信息

```yaml
spring:
  security:
    user:
      name: admin
      password: 123456
```

可以看到默认的用户名就是user：

![image-20240713223849038](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132238093.png)

+ 也可以从配置文件中点过去看源码：

  ![image-20240713224216432](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132242492.png)

这时候启动项目，再访问某一个控制器，会要求登录，就可以使用配置的用户名admin和密码123456登录了，控制台中也不会有随机密码输出了。

### 5.2.2 下载源码

再查看默认的name时，跳到的代码是IDEA反编译后的代码，是经过优化后的代码，而且上面会提示下载源代码：

![image-20240713224604511](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132246560.png)

可以点击下载，下载后的位置是当前的maven仓库中，包名的路径下：

### 5.2.3 问题

Spring Security配置文件中默认配置用户是单一的用户，大部分系统都有多个用户，多个用户如何配置？

## 5.3 基于内存的多用户管理

### 5.3.1 新建配置类

一个请求经过SpringSecurity的流程：

![image-20240713231013107](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132310187.png)

重点关注用户详情服务和密码编码器两类。

创建一个配置类，config.MySecurityUserConfig，配置一个获取用户详情服务接口UserDetailsService对象的方法：

```java
@Configuration
public class MySecurityUserConfig {
    @Bean
    public UserDetailsService userDetailService() {
        // 使用org.springframework.security.core.userdetails.User类来定义用户
        // 定义两个用户
        UserDetails user1 = User.builder().username("eric").password("123456").roles("student").build();
        UserDetails user2 = User.builder().username("thomas").password("123456").roles("teacher").build();
        // 创建两个用户
        InMemoryUserDetailsManager userDetailsManager = new InMemoryUserDetailsManager();
        userDetailsManager.createUser(user1);
        userDetailsManager.createUser(user2);
        return userDetailsManager;
    }
}
```

+ username是用户名，password是密码，roles是角色列表，这里要写角色列表，不然启动会报错
+ InMemoryUserDetailsManager实现了UserDetailsManager接口，该接口继承自UserDetailsService接口

SpringSecurity默认会提供一个UserDetailsService类对象，将自定义的对象注入到容器中，就会覆盖掉默认提供的对象。该类返回一个用户，用户名为user，密码为随机生成的。UserDetailsService主要是根据用户名来找到用户信息，这是源码：

```java
public interface UserDetailsService {
    UserDetails loadUserByUsername(String username) throws UsernameNotFoundException;
}
```

那用户信息UserDetails包括哪些东西？包括用户名、密码、权限列表等：

```java
public interface UserDetails extends Serializable {
    Collection<? extends GrantedAuthority> getAuthorities();  // 权限列表
    String getPassword();  // 密码
    String getUsername();  // 用户名
    boolean isAccountNonExpired();  // 账户是否未过期
    boolean isAccountNonLocked();  // 账户是否未锁定
    boolean isCredentialsNonExpired();  // 凭据是否未过期
    boolean isEnabled();  // 是否能用
}
```

拿到这个用户信息后，就会去验证用户的密码是否正确，如果正确，就会将用户的认证信息存到上下文中。

接下来启动项目，会报错：

![image-20240713233443096](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407132334166.png)

报错的原因：**这个是因为spring Sercurity强制要使用密码加密，当然我们也可以不加密，但是官方要求是不管你是否加密，都必须配置一个密码编码（加密）器。**

所以还要在该配置类中配置一个加密器，可以配置一个不加密的加密器：

```java
@Bean
public PasswordEncoder passwordEncoder(){
    //不对密码进行加密，使用明文
    return NoOpPasswordEncoder.getInstance();
}
```

+ 从 Spring5 开始，强制要求密码要加密，如果非不想加密，可以使用一个过期的 PasswordEncoder 的实例 NoOpPasswordEncoder。但是不建议这么做，毕竟不安全。

+ 查看NoOpPasswordEncoder源码：

  ```java
  @Deprecated
  public final class NoOpPasswordEncoder implements PasswordEncoder {
      private static final PasswordEncoder INSTANCE = new NoOpPasswordEncoder();
  
      private NoOpPasswordEncoder() {
      }
  
      public String encode(CharSequence rawPassword) {
          return rawPassword.toString();
      }
  
      public boolean matches(CharSequence rawPassword, String encodedPassword) {
          return rawPassword.toString().equals(encodedPassword);
      }
  
      public static PasswordEncoder getInstance() {
          return INSTANCE;
      }
  }
  ```

  它的加密方法encode是直接将源字符串返回，所以没有加密。且这是单例模式。

再重启程序，成功运行，输入配置的用户名eric和密码123456，或者用户名tomas和密码123456，都可以正常登录，但是原先在applicatio.yml文件中配置的用户名admin和密码123456就无法使用了。说明：**我们只要添加了安全配置类，那么我们在yml里面的配置就失效了**

### 5.3.2 问题

此时还有问题，

+ 密码没有加密
+ 以学生身份登录，发现不但可以访问学生的页面，还可以访问教师的页面和管理员的页面
+ 如果要动态的创建用户，或者修改密码等(不是把用户名和密码写死到代码中)，怎么办

# 6 密码处理

明文：plaintext

密文：ciphertext

## 6.1 为什么要加密？

csdn 密码泄露事件

泄露事件经过：https://www.williamlong.info/archives/2933.html

泄露数据分析：https://blog.csdn.net/crazyhacking/article/details/10443849

## 6.2加密方案

密码加密一般使用散列函数，又称散列算法，哈希函数，这些函数都是单向函数（从明文到密文，反之不行）

常用的散列算法有MD5和SHA

Spring Security提供多种密码加密方案，基本上都实现了PasswordEncoder接口，官方推荐使用BCryptPasswordEncoder类。

PasswordEncoder中的方法：

```java
public interface PasswordEncoder {
    String encode(CharSequence rawPassword);

    boolean matches(CharSequence rawPassword, String encodedPassword);

    default boolean upgradeEncoding(String encodedPassword) {
        return false;
    }
}
```

+ encode：加密
+ matches：匹配，匹配原始密码和加密后的密码是否一致

## 6.3 BCryptPasswordEncoder类初体验

创建一个测试类：

```java
public class PasswordTest {
    @Test
    public void testPassword() {
        PasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
        String encoded1 = passwordEncoder.encode("1234");
        String encoded2 = passwordEncoder.encode("1234");
        String encoded3 = passwordEncoder.encode("1234");
        System.out.println(encoded1);
        System.out.println(encoded2);
        System.out.println(encoded3);

        boolean res1 = passwordEncoder.matches("1234", encoded1);
        boolean res2 = passwordEncoder.matches("1234", encoded2);
        boolean res3 = passwordEncoder.matches("1234", encoded3);
        System.out.println(res1 + " " + res2 + " " + res3);
    }
}
```

输出结果：

```
$2a$10$cQ2V/rOJCWIpaCQ9.6F0oeQAMXO4xhcfyPP/FXoj0M5NjB.lkQFiC
$2a$10$j9dOdG2UC76ZZiBWgyAjfuOwNfJkArgQGmgss6JXXfPF5.UzrHgLK
$2a$10$4vv8raxqLOCmTNl0uECKreCJa.nhvj5fJz2TLCEiF0BjYHJtQXnta
true true true
```

查看控制台发现特点是：**相同的字符串加密之后的结果都不一样，但是比较的时候是一样的，因为加了盐（salt）了。**

小提示：

> **代码中一般不允许使用System.out.println直接输出，而是使用日志输出**
>
> **单元测试尽量使用断言，而不是使用System.out.println输出**

所以修改测试代码：

```java
@Slf4j
public class PasswordTest {
    @Test
    public void testPassword() {
        PasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
        String encoded1 = passwordEncoder.encode("1234");
        String encoded2 = passwordEncoder.encode("1234");
        String encoded3 = passwordEncoder.encode("1234");
        log.info(encoded1);
        log.info(encoded2);
        log.info(encoded3);

        boolean res1 = passwordEncoder.matches("1234", encoded1);
        boolean res2 = passwordEncoder.matches("1234", encoded2);
        boolean res3 = passwordEncoder.matches("1234", encoded3);
        assertTrue(res1);
        assertTrue(res2);
        assertTrue(res3);
    }
}
```

assertTrue期待的值是true，如果是一个false的值话，会出现报错信息。

## 6.4 使用加密器并且加密

修改MySecurityUserConfig类中的加密器bean：

```java
@Bean
public PasswordEncoder passwordEncoder(){
    // 使用加密算法对密码进行加密
    return new BCryptPasswordEncoder();
}
```

启动程序测试，发现不能正常登录

原因是输入的密码是进行加密了，但是系统中定义的用户密码没有加密。将用户密码修改成密文，如下：

```java
@Configuration
public class MySecurityUserConfig {
    @Bean
    public UserDetailsService userDetailService() {
		// 使用org.springframework.security.core.userdetails.User类来定义用户
        // 定义两个用户
        UserDetails user1 = User.builder()
                .username("eric")
                .password(passwordEncoder().encode("123456"))
                .roles("student")
                .build();
        UserDetails user2 = User.builder()
                .username("thomas")
                .password(passwordEncoder().encode("123456"))
                .roles("teacher")
                .build();
        // 创建两个用户
        InMemoryUserDetailsManager userDetailsManager = new InMemoryUserDetailsManager();
        userDetailsManager.createUser(user1);
        userDetailsManager.createUser(user2);
        return userDetailsManager;
    }

    /*
     * 从 Spring5 开始，强制要求密码要加密
     * @return
     */
    @Bean
    public PasswordEncoder passwordEncoder(){
        // 使用加密算法对密码进行加密
        return new BCryptPasswordEncoder();
    }
}
```

# 7 查看当前登录用户信息及配置用户权限

一旦用户登录成功后，用户信息就会被存在安全上下文（SecurityContext）中。

## 7.1 获取当前登录用户信息

创建一个controller，用来返回用户的登录信息：

```java
@RestController
public class LoginUserController {
    @RequestMapping("/loginUser")
    public Authentication loginUser(Authentication authentication) {
        System.out.println(authentication);
        return authentication;
    }

    @RequestMapping("/loginUser2")
    public Principal loginUser2(Principal principal) {
        System.out.println(principal);
        return principal;
    }
    
    @RequestMapping("/loginUser3")
    public Authentication loginUser3() {
        // 通过安全上下文持有器，获取安全上下文，再获取到登录信息
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        System.out.println(authentication);
        return authentication;
    }
}
```

+ 只要登录成功后，登录信息就会被放到Authentication类中，在请求的时候，控制器方法中可以直接获取这个对象
+ Authentication是一个接口，继承了Principal接口

然后启动项目，登录，测试一下这三个接口：

第一个：http://localhost:8080/loginUser

![image-20240714091826035](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407140918193.png)

+ authority：是权限，SpringSecurity将角色变成了权限，在角色的前面加了一个前缀ROLE_。
+ authenticated：认证
+ principal：principal里面的东西，就是UserDetail里面的东西
+ credentials：登录凭证，一般就是指密码。当用户登录成功之后，登录凭证会被自动擦除，防止泄露。

这三个接口的返回值都是一样的，说明这三种方法都可以获取到用户的登录信息。

所以整个登录流程是这样的：登录成功后，将认证信息放到Authentication类对象中，然后将该对象放到安全上下文SecurityContext中。

## 7.2 配置用户权限

配置用户权限有两种方式:

+ 配置roles

+ 配置authorities

注意事项：

+ 如果给一个用户同时配置roles和authorities，哪个写在后面哪个起作用

+ 配置roles时，权限名会加上ROLE_。

修改MySecurityUserConfig代码，使用roles和authorities来配置权限：

```java
@Bean
public UserDetailsService userDetailService() {
    //定义两个用户
    UserDetails user1 = User.builder()
        .username("eric")
        .password(passwordEncoder().encode("123456"))
        .roles("student", "test1")  // 配置两个角色
        .authorities("student:list", "student:query")  // 配置两个权限
        .build();
    UserDetails user2 = User.builder()
        .username("thomas")
        .password(passwordEncoder().encode("123456"))
        .authorities("teacher:list", "teacher:query")  // 配置两个权限
        .roles("teacher", "test2")  // 配置两个角色
        .build();
    //创建两个用户
    InMemoryUserDetailsManager userDetailsManager = new InMemoryUserDetailsManager();
    userDetailsManager.createUser(user1);
    userDetailsManager.createUser(user2);
    return userDetailsManager;
}
```

给两个用户分别配置了两个权限和两个角色，其中thomas是先调用authorities来设置权限，再通过roles设置角色；eric是先通过roles设置角色，再用authorities设置权限。

现在登录eric，查看认证信息中的权限列表：

![image-20240714093312719](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407140933845.png)

只有通过authorities方法配置的权限在，没有了由角色变过来的权限。

再登录thomas的账户，查看：

![image-20240714093644626](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407140936753.png)

只有由角色变过来的权限，没有通过authorities方法设置的权限。

所以使用roles和authorities进行权限设置时，哪个写在后面哪个起作用。可以看下roles方法的源码：

![image-20240714095446052](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407140954140.png)

+ 它会将每个角色前面加一个字符串ROLE_，然后生成权限列表

再看authorities方法的源码：

![image-20240714095604346](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407140956425.png)

+ 他是直接将指定的权限用来生成权限列表

这两个方法在同一个类中，操作的权限列表this.authorities是同一个集合，所以写在后面的方法就会将前面的结果覆盖掉。

现在用户有了权限，但是没有起到权限的作用，任意用户还是可以访问任意接口。

# 8 授权（对URL进行授权）

上面讲的实现了认证功能，但是受保护的资源是默认的，默认所有认证（登录）用户均可以访问所有资源，不能根据实际情况进行角色管理，要实现授权功能，需重写WebSecurityConfigureAdapter 中的一个configure方法。

新建一个配置类WebSecurityConfig，继承自WebSecurityConfigureAdapter抽象类：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests()  // 授权请求
                .anyRequest()  // 任何请求
                .denyAll();  // 拒绝访问
    }
}
```

以上代码配置了拒绝所有的请求访问，所以现在访问任何接口都是这样：

![image-20240714101905813](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141019937.png)

但是登录接口不应该被拦截，所以要加一句允许表单登录：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests()  // 授权请求
                .anyRequest()  // 任何请求
                .denyAll();  // 拒绝访问

        http.formLogin().permitAll();  // 允许表单登录
    }
}
```

现在可以正常登录，但是登录后，访问不了任何接口。

如果将代码中的denyAll()改成permitAll()，那就是允许所有的请求，都不需要登录就可以直接访问所有接口。

接下来将接口对应上用户的权限：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests()  // 授权请求
                // 以/student/开头的所有请求
                .mvcMatchers("/student/**")
                // 要有student:list权限才能访问
                .hasAnyAuthority("student:list")
                // 以/teacher/开头的所有请求
                .mvcMatchers("/teacher/**")
                // 要有teacher:list权限才能访问
                .hasAnyAuthority("teacher:list")
                // 除了以上指定的请求外的所有请求
                .anyRequest()
                // 需要认证了才能访问
                .authenticated();

        http.formLogin().permitAll();  // 允许表单登录
    }
}
```

+ 匹配路径的方法还有：antMatchers()、regxMatchers()等

+ 限制权限的方法还有：hasAuthority(单个权限)、access()、hasRoles()等

  ```java
  @Configuration
  public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
      @Override
      protected void configure(HttpSecurity http) throws Exception {
          http.authorizeRequests()
                  //角色student或者teacher都可以访问/student/** 这样的url
                  .mvcMatchers("/student/*").hasAnyRole("student", "teacher")
                  // 角色teacher 可以访问teacher/**
                  .mvcMatchers("/teacher/**").hasRole("teacher")
                  //权限admin:query 可以访问/admin**
  //                .mvcMatchers("/admin/**").hasAuthority("admin:query")
                  //角色teacher 或者权限admin:query 觉可以访问admin/**
                  .mvcMatchers("/admin/**").access("hasRole('teacher') or hasAuthority('admin:query')")
                  //任何请求均需要认证
                  .anyRequest().authenticated();
          //使用表单登录
          http.formLogin();
      }
  }
  ```

以上代码只限制了以/student/开头的路径只能用student:list权限访问，以/teacher/开头的路径只能用teacher:list权限访问，其他的路径只要登录了就都能访问。所以现在以eric用户的身份登录，eric的权限是"student:list"和"student:query"，所以他可以访问除了/teacher/开头外的任意路径：

http://localhost:8080/student/query

![image-20240714104213466](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141042564.png)

http://localhost:8080/admin/query

![image-20240714104230505](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141042598.png)

http://localhost:8080/teacher/query

![image-20240714104258735](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141042832.png)

# 9 授权（方法级别的权限控制）

上面学习的认证与授权都是基于URL的，我们也可以通过注解灵活的配置方法安全，我们先通过@EnableGlobalMethodSecurity开启基于注解的安全配置。

新建一个项目springsecurity003。复制上一个项目的获取用户信息的LoginUserController.java 。

创建一个service和其实现类：

TeacherService：

```java
public interface TeacherService {
    String add();
    String update();
    String delete();
    String query();
}
```

TeacherServiceImpl：

```java
@Service
public class TeacherServiceImpl implements TeacherService {
    @Override
    public String add() {
       System.out.println("添加教师成功");
        return "添加教师成功";
    }

    @Override
    public String update() {
       System.out.println("修改教师成功");
        return "修改教师成功";
    }

    @Override
    public String delete() {
       System.out.println("删除教师成功");
        return "删除教师成功";
    }

    @Override
    public String query() {
       System.out.println("查询教师成功");
        return "查询教师成功";
    }
}
```

然后创建TeacherController：

```java
@RestController
@RequestMapping("/teacher")
public class TeacherController {
    @Resource
    private TeacherService teacherService;

    @GetMapping("/query")
    public String queryInfo() {
        return teacherService.query();
    }

    @GetMapping("/add")
    public String addInfo() {
        return teacherService.add();
    }

    @GetMapping("/update")
    public String updateInfo() {
        return teacherService.update();
    }

    @GetMapping("/delete")
    public String deleteInfo() {
        return teacherService.delete();
    }
}
```

接下来要配置用户信息，创建一个用户信息配置类：

```java
@Configuration
public class MySecurityUserConfig {
    @Bean
    public UserDetailsService userDetailService() {
        // 定义用户
        UserDetails user1 = User.builder()
                .username("eric")
                .password(passwordEncoder().encode("123456"))
                .roles("student")  
                .build();
        UserDetails user2 = User.builder()
                .username("thomas")
                .password(passwordEncoder().encode("123456"))
                .authorities("teacher:query")  
                .build();
        UserDetails user3 = User.builder()
                .username("admin")
                .password(passwordEncoder().encode("123456"))
                .authorities("teacher:query","teacher:add", "teacher:delete", "teacher:update")
                .build();
        //创建用户
        InMemoryUserDetailsManager userDetailsManager = new InMemoryUserDetailsManager();
        userDetailsManager.createUser(user1);
        userDetailsManager.createUser(user2);
        userDetailsManager.createUser(user3);
        return userDetailsManager;
    }
    
    @Bean
    public PasswordEncoder passwordEncoder(){
        return new BCryptPasswordEncoder();
    }
}
```

定义了三个用户，三个用户拥有不同的权限。

接下来对安全进行配置，创建一个WebSecurityConfig配置类继承WebSecurityConfigurerAdapter：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();  // 所有接口都需要认证

        http.formLogin().permitAll();  // 允许表单登录
    }
}
```

现在启动程序，结果是只要登录了用户，就可以访问到任意一个接口。

那么接下来就要针对方法进行授权，让eric用户不能访问teacher的任何接口，让thomas只能访问teacher的query接口，让admin可以访问teacher的任意接口。

在安全配置类WebSecurityConfig类上使用一个注解，启动全局方法安全：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
```

+ prePostEnabled = true：表示可以使用预授权注解和后授权注解

+ 查看@EnableGlobalMethodSecurity注解的源码

  ![image-20240714112425205](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141124309.png)

  这个注解已经包含了@Configuration注解，所以安全配置类上原先使用的@Configuration注解就可以不用了。

```java
@EnableGlobalMethodSecurity
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();  // 所有接口都需要认证

        http.formLogin().permitAll();  // 允许表单登录
    }
}
```

预授权：在访问方法之前判断有没有权限

后授权：访问完方法之后判断有没有权限

那么可以方法上面添加预授权注解：

```java
@Service
public class TeacherServiceImpl implements TeacherService {
    @Override
    @PreAuthorize("hasAuthority('teacher:add')")
    public String add() {
       System.out.println("添加教师成功");
        return "添加教师成功";
    }

    @Override
    @PreAuthorize("hasAuthority('teacher:update')")
    public String update() {
       System.out.println("修改教师成功");
        return "修改教师成功";
    }

    @Override
    @PreAuthorize("hasAuthority('teacher:delete')")
    public String delete() {
       System.out.println("删除教师成功");
        return "删除教师成功";
    }

    @Override
    @PreAuthorize("hasAuthority('teacher:query')")
    public String query() {
       System.out.println("查询教师成功");
        return "查询教师成功";
    }
}
```

以上是控制的具体业务方法的权限，没有控制controller的权限，所以可以在controller中添加以下代码，看下区别：

```java
@RestController
@RequestMapping("/teacher")
public class TeacherController {
    @Resource
    private TeacherService teacherService;

    @GetMapping("/query")
    public String queryInfo() {
        System.out.println("进入teacher/query方法");
        return teacherService.query();
    }

    @GetMapping("/add")
    public String addInfo() {
        System.out.println("进入teacher/add方法");
        return teacherService.add();
    }

    @GetMapping("/update")
    public String updateInfo() {
        System.out.println("进入teacher/update方法");
        return teacherService.update();
    }

    @GetMapping("/delete")
    public String deleteInfo() {
        System.out.println("进入teacher/delete方法");
        return teacherService.delete();
    }
}
```

启动项目，使用eric账户登录，访问teacher的接口：

![image-20240714123706063](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141237216.png)

但是控制台中会输出：

![image-20240714123731021](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141237126.png)

就说明，该请求进入了controller，有权限执行controller，但是没有权限执行具体的方法。

也可以将@PreAuthorize注解使用在controller方法上。

# 10 SpringSecurity 返回json

前后端分离成为企业应用开发中的主流，前后端分离通过json进行交互，登录成功和失败后不用页面跳转，而是一段json提示

新建一个项目springsecurit004-json，将上一个项目的controller、service和用户配置拷贝过来。

要想登录成功或失败后都返回一个json字符串给前端，那么需要自定义处理器。

## 10.1 创建统一响应类HttpResult

创建一个vo包，包下创建一个类HttpResult：

```java
public class HttpResult {
    private Integer code;  // 返回给前端的自定义响应码
    private String message;  // 返回给前端的信息
    private Object data;  // 返回给前端的数据
    // getter setter toString
}
```

## 10.2 创建登录成功处理器

在hanler包下创建一个LoginSuccessHandler，实现AuthenticationSuccessHandler接口：

```java
@Component
public class LoginSuccessHandler implements AuthenticationSuccessHandler {
    @Resource
    private ObjectMapper objectMapper;  // 可以序列化（转为json）和反序列化
    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        // 定义一个响应对象
        HttpResult httpResult = new HttpResult(1, "登录成功", null);
        // 将对象转为json
        String json = objectMapper.writeValueAsString(httpResult);
        // 返回给前端
        response.setContentType("application/json;charset=UTF-8");
        PrintWriter out = response.getWriter();
        out.print(json);
        out.flush();
    }
}
```

只要认证成功，就会调用该类中的方法。

写完之后需要使用，需要创建一个security的配置类，在里面配置登录成功从处理器：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Resource
    private LoginSuccessHandler loginSuccessHandler;
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
            .successHandler(loginSuccessHandler)  // 注册登录成功处理器
            .permitAll();
    }
}
```

然后启动项目，可以测试登录成功：

![image-20240714132444221](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141324357.png)

## 10.3 创建登录失败处理器

在hanler包下创建一个LoginFailureHandler，实现AuthenticationFailureHandler接口：

```java
@Component
public class LoginFailureHandler implements AuthenticationFailureHandler {
    @Resource
    private ObjectMapper objectMapper;  // 可以序列化（转为json）和反序列化
    @Override
    public void onAuthenticationFailure(HttpServletRequest request, HttpServletResponse response, AuthenticationException exception) throws IOException, ServletException {
        // 定义一个响应对象
        HttpResult httpResult = new HttpResult(0, "登录失败", null);
        // 将对象转为json
        String json = objectMapper.writeValueAsString(httpResult);
        // 返回给前端
        response.setContentType("application/json;charset=UTF-8");
        PrintWriter out = response.getWriter();
        out.print(json);
        out.flush();
    }
}
```

然后再security的配置类中注册这个登录失败处理器：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Resource
    private LoginSuccessHandler loginSuccessHandler;
    @Resource
    private LoginFailureHandler loginFailureHandler;
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
            // 添加登录失败处理器
                .failureHandler(loginFailureHandler)
            // 添加登录成功处理器
                .successHandler(loginSuccessHandler)
                .permitAll();
    }
}
```

测试：

![image-20240714133909814](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141339941.png)

## 10.4 创键无权限处理器

```java
/**
 * 无权限的处理器
 */
@Component
public class AppAccessDeniedHandler implements AccessDeniedHandler {

    //声明一个把对象转成JSON的对象
    @Resource
    private ObjectMapper objectMapper;

    @Override
    public void handle(HttpServletRequest request, HttpServletResponse response, AccessDeniedException accessDeniedException) throws IOException, ServletException {
        //设置响应编码
        response.setCharacterEncoding("UTF-8");
        response.setContentType("application/json;charset=utf-8");
        //返回JSON出去
        HttpResult result=new HttpResult(-1,"您没有权限访问");
        //把result转成JSON
        String json = objectMapper.writeValueAsString(result);
        //响应出去
        PrintWriter out = response.getWriter();
        out.write(json);
        out.flush();
    }
}
```

在配置类中配置：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Resource
    private LoginSuccessHandler loginSuccessHandler;
    @Resource
    private LoginFailureHandler loginFailureHandler;
    @Resource
    private AppAccessDeniedHandler accessDeniedHandler;
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests()
                .mvcMatchers("/student/**")
                .hasAuthority("student")
                .anyRequest().authenticated();
        http.formLogin()
                // 添加登录失败处理器
                .failureHandler(loginFailureHandler)
                // 添加登录成功处理器
                .successHandler(loginSuccessHandler)
                .permitAll();

        // 配置访问拒绝处理器
        http.exceptionHandling().accessDeniedHandler(accessDeniedHandler);
    }
}
```

测试，用老师的角色去访问限制了学生角色的接口：

![image-20240714135515977](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141355101.png)

## 10.5 创建登出（退出）处理器

```java
/**
 * 退出成功的处理器
 */
@Component
public class AppLogoutSuccessHandler implements LogoutSuccessHandler {

    //声明一个把对象转成JSON的对象
    @Resource
    private ObjectMapper objectMapper;

    /**
     *
     * @param request
     * @param response
     * @param authentication 当前退出的用户对象
     * @throws IOException
     * @throws ServletException
     */
    @Override
    public void onLogoutSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        System.out.println("退出成功");
        //设置响应编码
        response.setCharacterEncoding("UTF-8");
        response.setContentType("application/json;charset=utf-8");
        //返回JSON出去
        HttpResult result=new HttpResult(200,"退出成功");
        //把result转成JSON
        String json = objectMapper.writeValueAsString(result);
        //响应出去
        PrintWriter out = response.getWriter();
        out.write(json);
        out.flush();
    }
}
```

配置：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Resource
    private LoginSuccessHandler loginSuccessHandler;
    @Resource
    private LoginFailureHandler loginFailureHandler;
    @Resource
    private AppLogoutSuccessHandler logoutSuccessHandler;
    @Resource
    private AppAccessDeniedHandler accessDeniedHandler;
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
                // 添加登录失败处理器
                .failureHandler(loginFailureHandler)
                // 添加登录成功处理器
                .successHandler(loginSuccessHandler)
                .permitAll();

        // 配置访问拒绝处理器
        http.exceptionHandling().accessDeniedHandler(accessDeniedHandler);
        
        // 配置登出成功处理器
        http.logout().logoutSuccessHandler(logoutSuccessHandler);
    }
}
```

测试：

![image-20240714135616074](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141356196.png)

# 11 使用UserDetailsService获取用户认证信息

复制一个项目为 springsecurity005-userdertialservice。

之前的程序的用户都是用MySecurityUserConfig这个类中的UserDetailsService方法来生成的，在方法里创建了UserDetails对象，然后用InMemoryUserDetailsManager来生成用户，是保存在内存中的，现在不需要使用这个类了，删除。可以自定义一个UserDetails的实现类来创建用户。

那么删除MySecurityUserConfig类之后，原先定义在该类中的密码编码器要写在WebSecurityConfig配置类中去：

```java
@Bean
public PasswordEncoder passwordEncoder() {
    return new BCryptPasswordEncoder();
}
```

## 11.1 新建用户信息类

 在vo包下创建一个MyUser类来实现UserDetails接口：

```java
public class MyUser implements UserDetails {
    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        // 用户的权限
        return null;
    }

    @Override
    public String getPassword() {
        // 用户的密码
        return new BCryptPasswordEncoder().encode("1234");
    }

    @Override
    public String getUsername() {
        // 用户名
        return "eric";
    }

    @Override
    public boolean isAccountNonExpired() {
        // 是否未过期，默认为false
        return true;
    }

    @Override
    public boolean isAccountNonLocked() {
        // 是否账户未锁定，默认false
        return true;
    }

    @Override
    public boolean isCredentialsNonExpired() {
        // 凭据是否未过期，默认false
        return true;
    }

    @Override
    public boolean isEnabled() {
        // 账户是否能用，默认false
        return true;
    }
}
```

## 11.6 新建类实现UserDetailService接口

在service.impl下创建一个类实现UserDetailService接口：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        if (username == null || username.isEmpty()) throw new UsernameNotFoundException("用户名不存在");
        
        if (!"eric".equals(username)) throw new UsernameNotFoundException("用户名错误！");
        
        return new MyUser();
    }
}
```

现在这样就相当于直接向Spring容器中放了一个UserDetailsService类的对象。

+ 之前的写法是在配置类中写：

  ```java
  @Configuration
  public class MySecurityUserConfig {
      @Bean
      public UserDetailsService userDetailService() {
          // 定义用户
          UserDetails user1 = User.builder()
                  .username("eric")
                  .password(passwordEncoder().encode("123456"))
                  .roles("student")
                  .build();
          UserDetails user2 = User.builder()
                  .username("thomas")
                  .password(passwordEncoder().encode("123456"))
                  .authorities("teacher:query")
                  .build();
          UserDetails user3 = User.builder()
                  .username("admin")
                  .password(passwordEncoder().encode("123456"))
                  .authorities("teacher:query","teacher:add", "teacher:delete", "teacher:update")
                  .build();
          //创建用户
          InMemoryUserDetailsManager userDetailsManager = new InMemoryUserDetailsManager();
          userDetailsManager.createUser(user1);
          userDetailsManager.createUser(user2);
          userDetailsManager.createUser(user3);
          return userDetailsManager;
      }
  }
  ```

UserDetailsService接口中只有一个方法，根据用户名获取用户的详情。判断登录用户是否能够登录，能够登录的话就返回该登录用户的详情信息，那么当前指定的可登录用户是在MyUser类中写死的，是eric。

然后启动项目，查看用户的登录信息：

![image-20240714144451716](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141444891.png)

可以看到这些信息都是MyUser类中实现的方法返回的信息。

那么以后从数据库中取用户信息的时候，就可以将其封装成实现了UserDetails接口的类。

# 12 基于数据库的认证

真正的项目用户数据不是写死在代码中的，是放在数据库中的，从数据库中获取，然后封装到UserDetails实现类中。

## 12.1 准备

编码顺序：实体类entity-->dao-->dao的单元测试-->service接口-->service实现-->service的单元测试-->controller-->controller的测试

### 12.1.1 数据库

创建数据库security_study

导入数据库脚本security_study.sql

```sql
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for sys_menu
-- ----------------------------
DROP TABLE IF EXISTS `sys_menu`;
CREATE TABLE `sys_menu`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '编号',
  `pid` int NULL DEFAULT NULL COMMENT '父级编号',
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '名称',
  `code` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '权限编码',
  `type` int NULL DEFAULT NULL COMMENT '0代表菜单1权限2 url',
  `delete_flag` tinyint NULL DEFAULT 0 COMMENT '0代表未删除，1 代表已删除',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 10 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of sys_menu
-- ----------------------------
INSERT INTO `sys_menu` VALUES (1, 0, '学生管理', '/student/**', 0, 0);
INSERT INTO `sys_menu` VALUES (2, 1, '学生查询', 'student:query', 1, 0);
INSERT INTO `sys_menu` VALUES (3, 1, '学生添加', 'student:add', 1, 0);
INSERT INTO `sys_menu` VALUES (4, 1, '学生修改', 'student:update', 1, 0);
INSERT INTO `sys_menu` VALUES (5, 1, '学生删除', 'student:delete', 1, 0);
INSERT INTO `sys_menu` VALUES (6, 1, '导出学生信息', 'student:export', 1, 0);
INSERT INTO `sys_menu` VALUES (7, 0, '教师管理', '/teacher/**', 0, 0);
INSERT INTO `sys_menu` VALUES (9, 7, '教师查询', 'teacher:query', 1, 0);

-- ----------------------------
-- Table structure for sys_role
-- ----------------------------
DROP TABLE IF EXISTS `sys_role`;
CREATE TABLE `sys_role`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '角色ID',
  `rolename` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '角色名称，英文名称',
  `remark` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of sys_role
-- ----------------------------
INSERT INTO `sys_role` VALUES (1, 'ROLE_ADMIN', '管理员');
INSERT INTO `sys_role` VALUES (2, 'ROLE_TEACHER', '老师');
INSERT INTO `sys_role` VALUES (3, 'ROLE_STUDENT', '学生');

-- ----------------------------
-- Table structure for sys_role_menu
-- ----------------------------
DROP TABLE IF EXISTS `sys_role_menu`;
CREATE TABLE `sys_role_menu`  (
  `rid` int NOT NULL COMMENT '角色表的编号',
  `mid` int NOT NULL COMMENT '菜单表的编号',
  PRIMARY KEY (`mid`, `rid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of sys_role_menu
-- ----------------------------
INSERT INTO `sys_role_menu` VALUES (1, 1);
INSERT INTO `sys_role_menu` VALUES (3, 1);
INSERT INTO `sys_role_menu` VALUES (2, 2);
INSERT INTO `sys_role_menu` VALUES (3, 2);
INSERT INTO `sys_role_menu` VALUES (1, 3);
INSERT INTO `sys_role_menu` VALUES (2, 3);
INSERT INTO `sys_role_menu` VALUES (1, 4);
INSERT INTO `sys_role_menu` VALUES (2, 4);
INSERT INTO `sys_role_menu` VALUES (1, 5);
INSERT INTO `sys_role_menu` VALUES (2, 5);
INSERT INTO `sys_role_menu` VALUES (3, 6);
INSERT INTO `sys_role_menu` VALUES (1, 9);
INSERT INTO `sys_role_menu` VALUES (2, 9);
INSERT INTO `sys_role_menu` VALUES (3, 9);
INSERT INTO `sys_role_menu` VALUES (1, 10);
INSERT INTO `sys_role_menu` VALUES (1, 17);

-- ----------------------------
-- Table structure for sys_role_user
-- ----------------------------
DROP TABLE IF EXISTS `sys_role_user`;
CREATE TABLE `sys_role_user`  (
  `uid` int NOT NULL COMMENT '用户编号',
  `rid` int NOT NULL COMMENT '角色编号',
  PRIMARY KEY (`uid`, `rid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of sys_role_user
-- ----------------------------
INSERT INTO `sys_role_user` VALUES (1, 1);
INSERT INTO `sys_role_user` VALUES (2, 2);
INSERT INTO `sys_role_user` VALUES (3, 3);

-- ----------------------------
-- Table structure for sys_user
-- ----------------------------
DROP TABLE IF EXISTS `sys_user`;
CREATE TABLE `sys_user`  (
  `user_id` int NOT NULL AUTO_INCREMENT COMMENT '编号',
  `username` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '登陆名',
  `password` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '密码',
  `sex` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '性别',
  `address` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL COMMENT '地址',
  `enabled` int NULL DEFAULT 1 COMMENT '是否启动账户0禁用 1启用',
  `account_no_expired` int NULL DEFAULT 1 COMMENT '账户是否没有过期0已过期 1 正常',
  `credentials_no_expired` int NULL DEFAULT 1 COMMENT '密码是否没有过期0已过期 1 正常',
  `account_no_locked` int NULL DEFAULT 1 COMMENT '账户是否没有锁定0已锁定 1 正常',
  PRIMARY KEY (`user_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of sys_user
-- ----------------------------
INSERT INTO `sys_user` VALUES (1, 'obama', '$2a$10$KyXAnVcsrLaHMWpd3e2xhe6JmzBi.3AgMhteFq8t8kjxmwL8olEDq', '男', '武汉', 1, 1, 1, 1);
INSERT INTO `sys_user` VALUES (2, 'thomas', '$2a$10$KyXAnVcsrLaHMWpd3e2xhe6JmzBi.3AgMhteFq8t8kjxmwL8olEDq', '男', '北京', 1, 1, 1, 1);
INSERT INTO `sys_user` VALUES (3, 'eric', '$2a$10$KyXAnVcsrLaHMWpd3e2xhe6JmzBi.3AgMhteFq8t8kjxmwL8olEDq', '男', '成都', 1, 1, 1, 1);

SET FOREIGN_KEY_CHECKS = 1;
```

sys_user表：

![image-20240714145732286](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141457427.png)

sys_menu表：

![image-20240714145833146](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141458281.png)

sys_role表：

![image-20240714145903415](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141459546.png)

sys_role_menu表：

![image-20240714145923741](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141459870.png)

sys_role_user表：

![image-20240714145946319](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141459448.png)

### 12.1.2 依赖

创建一个新模块，引入mybatis依赖、mysql依赖：

```xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>2.6.13</version>
    <relativePath/> <!-- lookup parent from repository -->
</parent>
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-security</artifactId>
    </dependency>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <dependency>
        <groupId>org.mybatis.spring.boot</groupId>
        <artifactId>mybatis-spring-boot-starter</artifactId>
        <version>3.0.3</version>
    </dependency>

    <dependency>
        <groupId>com.mysql</groupId>
        <artifactId>mysql-connector-j</artifactId>
        <scope>runtime</scope>
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
    <dependency>
        <groupId>org.mybatis.spring.boot</groupId>
        <artifactId>mybatis-spring-boot-starter-test</artifactId>
        <version>3.0.3</version>
        <scope>test</scope>
    </dependency>
    <dependency>
        <groupId>org.springframework.security</groupId>
        <artifactId>spring-security-test</artifactId>
        <scope>test</scope>
    </dependency>
</dependencies>
```

### 12.1.3 创建包

+ service
  + impl
+ dao
+ controller
+ entity
+ vo
+ config

![image-20240714175642363](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407141757369.png)

### 12.1.4 配置数据源和mybatis

在application.properties文件中配置数据库数据源：

```properties
spring.datasource.url=jdbc:mysql://localhost:3306?security_study
spring.datasource.username=root
spring.datasource.password=1234
```

开启mybatis的驼峰命名转换和开启日志：

```properties
mybatis.configuration.map-underscore-to-camel-case=true
mybatis.configuration.log-impl=org.apache.ibatis.logging.stdout.StdOutImpl
```



## 12.2 查询用户

### 12.2.1 实体类

在entity包下创建用户对应的实体类：
```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class SysUser implements Serializable {
    private Integer userId;
    private String username;
    private String password;
    private String sex;
    private String address;
    private Integer enabled;
    private Integer accountNoExpired;
    private Integer credentialsNoExpired;
    private Integer accountNoLocked;
}
```

### 12.2.2 dao（mapper）

在dao包中创建接口，写一个根据用户名从数据库中查找用户信息的方法：

```java
public interface SysUserDao {
    @Select("""
                select * from sys_user where username = #{username}
            """)
    SysUser getByUserName(String username);
}
```

要在启动类上添加包扫描注解：

```java
@SpringBootApplication
@MapperScan(basePackages = "com.zsm.dao")
public class Application {
	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}
}
```

+ 或者在SysUserDao接口上使用@Mapper注解：

  ```java
  @Mapper
  public interface SysUserDao {
      @Select("""
                  select * from sys_user where username = #{username}
              """)
      SysUser getByUserName(String username);
  }
  ```

然后测试：

```java
@SpringBootTest
class DaoTest {
	@Autowired
	private SysUserDao sysUserDao;
	@Test
	void testGetByUserName() {
		SysUser obama = sysUserDao.getByUserName("obama");
		System.out.println(obama);
	}
}
```

输出结果：

```java
SysUser(userId=1, username=obama, password=$2a$10$KyXAnVcsrLaHMWpd3e2xhe6JmzBi.3AgMhteFq8t8kjxmwL8olEDq, sex=男, address=武汉, enabled=1, accountNoExpired=1, credentialsNoExpired=1, accountNoLocked=1)
```

> 如果是使用mapper.xml文件来写sql语句的话，需要在resources目录下创建一个dao目录，dao目录下写对应的mapper.xml文件，同时要配置mybatis的xml文件路径和开启别名，在application.properties中：
>
> ```properties
> mybatis.mapper-locations=classpath:/dao/*.xml
> mybatis.type-aliases-package=com.zsm.entity
> ```
>
> SysUserDao.xml：
>
> ```xml
> <mapper namespace="com.zsm.dao.SysUserDao">
>     <select id="getByUserName" resultType="sysUser">
>         select * from sys_user where username = #{username}
>     </select>
> </mapper>
> ```

### 12.2.3 service

创建SysUserService以及实现类：

SysUserService：

```java
public interface SysUserService {
    SysUser getByUserName(String username);
}
```

SysUserServiceImpl：

```java
@Service
public class SysUserServiceImpl implements SysUserService {

    @Autowired
    private SysUserDao sysUserDao;
    @Override
    public SysUser getByUserName(String username) {
        return sysUserDao.getByUserName(username);
    }
}
```

+ 按快捷键ctrl+shift+t可以快速创建测试方法

测试：

```java
@SpringBootTest
class SysUserServiceImplTest {
    @Autowired
    private SysUserService sysUserService;

    @Test
    void getByUserName() {
        SysUser obama = sysUserService.getByUserName("obama");
        assertNotNull(obama);
    }
}
```

+ 使用assert断言来代替输出，assertNotNull要求参数一定不为空，为空就会报错

## 12.3 新建安全用户类

可以从数据库查出数据了，就可以结合SpringSecurity使用了。要将用户封装到UserDetails的实现类中。

在vo下创建一个类SecurityUser，实现UserDetails接口：

```java
public class SecurityUser implements UserDetails {
    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return null;
    }

    @Override
    public String getPassword() {
        return null;
    }

    @Override
    public String getUsername() {
        return null;
    }

    @Override
    public boolean isAccountNonExpired() {
        return false;
    }

    @Override
    public boolean isAccountNonLocked() {
        return false;
    }

    @Override
    public boolean isCredentialsNonExpired() {
        return false;
    }

    @Override
    public boolean isEnabled() {
        return false;
    }
}
```

然后就是要这些方法返回的是用户信息即可，所以可以将用户当作一个属性在这个类中存在：

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class SecurityUser implements UserDetails {
    private SysUser sysUser;
    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        // 没有配置权限
        return null;
    }

    @Override
    public String getPassword() {
        return sysUser.getPassword();
    }

    @Override
    public String getUsername() {
        return sysUser.getUsername();
    }

    @Override
    public boolean isAccountNonExpired() {
        return sysUser.getAccountNoExpired().equals(1);
    }

    @Override
    public boolean isAccountNonLocked() {
        return sysUser.getAccountNoLocked().equals(1);
    }

    @Override
    public boolean isCredentialsNonExpired() {
        return sysUser.getCredentialsNoExpired().equals(1);
    }

    @Override
    public boolean isEnabled() {
        return sysUser.getEnabled().equals(1);
    }
}
```

## 12.4 新建UserServiceImpl 实现UserDetailService接口

UserDetailsService接口只有一个方法，就是根据用户名获取用户信息，那么就调用之前写的SysUserService的方法，从数据库中获取用户信息，封装到SecurityUser对象中，返回：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    @Autowired
    private SysUserService sysUserService;
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        SysUser user = sysUserService.getByUserName(username);
        if (user == null) throw new UsernameNotFoundException("用户不存在");

        SecurityUser securityUser = new SecurityUser(user);
        return securityUser;
    }
}
```

## 12.5 新建web安全配置类

在config包下创建Security的配置类，配置密码加密器，配置所有请求需要认证：

```java
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin().permitAll();
    }
}
```

## 12.6 新建两个控制器

StudentController：

```java
@RestController
@RequestMapping("/student")
public class StudentController {
    @GetMapping("/query")
    public String queryInfo(){
        return "query student";
    }
    @GetMapping("/add")
    public String addInfo(){
        return "add  student!";
    }
    @GetMapping("/update")
    public String updateInfo(){
        return "update student";
    }
    @GetMapping("/delete")
    public String deleteInfo(){
        return "delete  student!";
    }
    @GetMapping("/export")
    public String exportInfo(){
        return "export  student!";
    }
}
```

TeacherController，有一个预授权：

```java
@RestController
@RequestMapping("/teacher")
public class TeacherController {
    @GetMapping("/query")
    @PreAuthorize("hasAuthority('teacher:query')")
    public String queryInfo(){
        return "I am a teacher!";
    }
}
```

使用了预授权注解，那么Security的配置类中就要启动预授权注解：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
```

然后可以启动项目，登录thomas账户，可以访问student/query，但是访问不了teacher/query，因为teacher/query设置了权限。

# 13 基于数据库的方法授权

## 13.1 测试sql语句

现在已经可以基于数据库认证了，就是从数据库中用户登录用户的信息。现在要从数据库中获取用户的权限信息。数据库中用户的权限是sys_menu表中的code字段：

![image-20240715090722676](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407150907814.png)

先测试一下从数据库中获取权限的sql语句：

```sql
select distinct m.code from sys_menu m
    left join sys_role_menu rm on m.id = rm.mid
    left join sys_role_user ru on ru.rid = rm.rid
where ru.uid = 1
```

![image-20240715091928962](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407150919066.png)

## 13.2 定义实体类

定义数据库中sys_menu对应的实体类：

SysMenu类：

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class SysMenu implements Serializable {
    private Integer id;
    private Integer pid;
    private Integer type;
    private String name;
    private String code;
}
```

## 13.3 操作数据库

然后创建对应的mapper接口和mapper.xml文件：

SysMenuDao.java：

```java
@Mapper
public interface SysMenuDao {
   List<String> queryPermissionByUserId(Integer userId);
}
```

+ 如果启动类上不配mapper包扫描，就要加上@Mapper注解

SysMenuDao.xml：

```xml
<mapper namespace="com.zsm.dao.SysMenuDao">
    <select id="queryPermissionByUserId" resultType="String">
        select distinct m.code from sys_menu m
        left join sys_role_menu rm on m.id = rm.mid
        left join sys_role_user ru on ru.rid = rm.rid
        where ru.uid = #{id}
    </select>
</mapper>
```

测试：

```java
@SpringBootTest
class SysMenuDaoTest {

    @Autowired
    private SysMenuDao sysMenuDao;
    @Test
    void queryPermissionByUserId() {
        List<String> strings = sysMenuDao.queryPermissionByUserId(1);
        System.out.println(strings);
    }
}
```

输出结果：

```
[/student/**, student:add, student:update, student:delete, teacher:query]
```

## 13.4 service

然后写对应的service：

SysMenuService：

```java
public interface SysMenuService {
    List<String> queryPermissionByUserId(Integer userId);
}
```

SysMenuServiceImpl：

```java
@Service
public class SysMenuServiceImpl implements SysMenuService {
    @Autowired
    private SysMenuDao sysMenuDao;
    @Override
    public List<String> queryPermissionByUserId(Integer userId) {
        return sysMenuDao.queryPermissionByUserId(userId);
    }
}
```

那么现在可以获取到数据库中的权限了，那么要如何设置给UserDetails对象呢，就要在UserDetailsServiceImpl类中，通过用户名查询出用户信息的时候。

那么需要注意一下，在UserDetails中，权限集合的类型：

```java
public Collection<? extends GrantedAuthority> getAuthorities() {
    return null;
}
```

返回值类型是一个Collection集合，那么就可以使用ArrayList，但是其中的泛型是必须要继承GrantedAuthority这个接口的，我们SysMenuDao查出来的集合是List<String>类型的，所以要将String类型封装到GrantedAuthority类型中。

查看GrantedAuthority这个接口的源码：

```java
public interface GrantedAuthority extends Serializable {
    String getAuthority();
}
```

只有一个方法，那么可以使用匿名内部类的方式来实现这个接口：

```java
public Collection<? extends GrantedAuthority> getAuthorities() {
    GrantedAuthority grantedAuthority = new GrantedAuthority() {
        @Override
        public String getAuthority() {
            return "student:query";
        }
    };
    List<GrantedAuthority> list = new ArrayList<>();
    list.add(grantedAuthority);
    return list;
}
```

那么这样写的话，所有的用户的权限都会是student:query这一个了，所以可以在UserDetails类中添加一个用来存储权限的List集合，并且泛型使用SimpleGrantedAuthority：

```java
private List<SimpleGrantedAuthority> grantedAuthorities;

@Override
public Collection<? extends GrantedAuthority> getAuthorities() {
    return grantedAuthorities;
}
```

然后在UserDetailsServiceImpl中，通过这个grantedAuthorities属性的set方法给他赋值，问题就是如何将List<String>转为List<SimpleGrantedAuthority>，遍历获取到的权限字符串集合，将每个字符串转为SimpleGrantedAuthority对象，加到List<SimpleGrantedAuthority>集合中，最后将集合赋给UserDetails对象并返回：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    @Autowired
    private SysUserService sysUserService;
    @Autowired
    private SysMenuService sysMenuService;
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        SysUser user = sysUserService.getByUserName(username);
        if (user == null) throw new UsernameNotFoundException("用户不存在");

        List<String> permissions = sysMenuService.queryPermissionByUserId(user.getUserId());
        List<SimpleGrantedAuthority> grantedAuthorities = new ArrayList<>();
        for (String permission : permissions) {
            grantedAuthorities.add(new SimpleGrantedAuthority(permission));
        }

        SecurityUser securityUser = new SecurityUser(user, grantedAuthorities);
        return securityUser;
    }
}
```

+ 循环遍历的操作可以使用stream流的方法来写：

  ```java
  @Service
  public class UserDetailsServiceImpl implements UserDetailsService {
      @Autowired
      private SysUserService sysUserService;
      @Autowired
      private SysMenuService sysMenuService;
      @Override
      public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
          SysUser user = sysUserService.getByUserName(username);
          if (user == null) throw new UsernameNotFoundException("用户不存在");
  
          List<String> permissions = sysMenuService.queryPermissionByUserId(user.getUserId());
  
          List<SimpleGrantedAuthority> grantedAuthorities = permissions.stream()
              .map(SimpleGrantedAuthority::new)
              .collect(Collectors.toList());
  
          SecurityUser securityUser = new SecurityUser(user, grantedAuthorities);
          return securityUser;
      }
  }
  ```

现在启动项目，登录用户，访问/loginUser接口，查看是否拥有权限：

![image-20240715101110564](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151011694.png)

擦除密码：

当前是可以在前端页面看到密码：

![image-20240715102900473](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151029614.png)

可以设置擦除密码，让前端这个接口看不到密码，在SecurityUser类中：

```java
@Override
public String getPassword() {
    String password = sysUser.getPassword();
    sysUser.setPassword(null);
    return password;
}
```

先获取到密码赋值给password吗，然后将密码置为null，返回password，这样登录时验证密码时可以拿到正常的密码，然后访问/loginUser接口时，重新获取密码，就会是null，就不会显示在页面上：

![image-20240715103420737](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151034859.png)

# 14 SpringSecurity 集成thymeleaf

## 14.1 准备

将上一个项目复制一份。

引入thymeleaf依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

在application.properties中配置thymeleaf：

```properties
# 关闭缓存，方便修改前端代码，热重载
spring.thymeleaf.cache=false
# 检查模板，检查前端页面，默认就是true
spring.thymeleaf.check-template=true
```

创建thymeleaf模板：

![image-20240715144606697](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151447043.png)

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="www.thymeleaf.org">
<head>
  <meta charset="UTF-8">
  <title>#[[$Title$]]#</title>
</head>
<body>
#[[$END$]]#
</body>
</html>
```

这样在创建文件时，可以选择创建thymeleaf文件，会创建一个指定模板的html文件。

也可以安装html转thymeleaf的插件：

![image-20240715150835703](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151508822.png)

## 14.2 做一个自定义的登录页面

做一个自定义的登录页面，替换SpringSecurity默认的登录页面。

### 14.2.1 创建controller

定义一个LoginController，访问接口/toLogin，会跳转到登录页面login.html：

```java
@Controller
public class LoginController {
    @RequestMapping("/toLogin")
    public String toLogin() {
        return "login";
    }
}
```

这个返回的字符串login就是逻辑视图的名称，它会和thymeleaf中规定的前缀和后缀拼接起来形成物理视图名称。

可以在application.properties文件中，ctrl+鼠标单击thymeleaf可以跳转到ThymeleafProperties类中，这里面规定了前缀和后缀：

![image-20240715151542214](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151515314.png)

### 14.2.2 创建视图文件

在resources下的templates下创建一个html文件：

```html
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>用户登陆</title>
</head>
<body>
<h2>登录页面</h2>
<form action="/login/doLogin" method="post">
    <table>
        <tr>
            <td>用户名:</td>
            <td><input type="text" name="uname" value="thomas"></td>
        </tr>
        <tr>
            <td>密码:</td>
            <td><input type="password" name="pwd"></td>
            <span th:if="${param.error}">用户名或者密码错误</span>
        </tr>
        <tr>
            <td colspan="2">
                <button type="submit">登录</button>
            </td>
        </tr>
    </table>
</form>
</body>
```

### 14.2.3 替换SpringSecurity默认登录页

找到Security的配置文件WebSecurityConfig，在configure方法中，配置登录：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
                .loginPage("/toLogin")  // 配置登录页面
                .permitAll();
    }
}
```

+ "/toLogin"是controller的路径 

这样配置之后，还有问题。默认的登录页面的用户名密码输入的name是username和password，这有可能和自定义的登录页面的name不一样，就可能导致不能正常获得用户的输入，所以还需要配置：

```java
@Override
protected void configure(HttpSecurity http) throws Exception {
    http.authorizeRequests().anyRequest().authenticated();
    http.formLogin()
        .loginPage("/toLogin")  // 配置登录页面
        .usernameParameter("uname")  // 用户名参数名
        .passwordParameter("pwd")  // 密码参数名
        .loginProcessingUrl("/login/doLogin")  // 登录提交的地址
        .failureForwardUrl("/toLogin")  // 登录失败后跳转地址
        .successForwardUrl("/index/toIndex")  // 登录成功后跳转地址
        .permitAll();
    http.logout().logoutSuccessUrl("/toLogin");  // 退出成功后跳转登录页面
}
```

顺便创建一个IndexController：

```java
@Controller
@RequestMapping("/index")
public class IndexController {
    @RequestMapping("/toIndex")
    public String index() {
        return "index";
    }
}
```

创建一个index.html：

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
    <head>
        <meta charset="UTF-8">
        <title>系统首页</title>
    </head>
    <body>
        <h1 align="center">系统首页</h1>
        <a href="/student/query">查询学生</a>
        <br>
        <a href="/student/add">添加学生</a>
        <br>
        <a href="/student/update">更新学生</a>
        <br>
        <a href="/student/delete">删除学生</a>
        <br>
        <a href="/student/export">导出学生</a>
        <br>
        <br><br><br>
        <h2><a href="/logout">退出</a></h2>
        <br>
    </body>
</html>
```

以上链接都在StudentController中，都是跳转页面，所以要改一下StudentController，让所有方法都跳转页面：

```java
@Controller
@RequestMapping("/student")
public class StudentController {
    @GetMapping("/query")
    @PreAuthorize("hasAuthority('student:query')")
    public String queryInfo(){
        return "student/query";
    }
    @GetMapping("/add")
    @PreAuthorize("hasAuthority('student:add')")
    public String addInfo(){
        return "student/add";
    }
    @GetMapping("/update")
    @PreAuthorize("hasAuthority('student:update')")
    public String updateInfo(){
        return "student/update";
    }
    @GetMapping("/delete")
    @PreAuthorize("hasAuthority('student:delete')")
    public String deleteInfo(){
        return "student/delete";
    }
    @GetMapping("/export")
    @PreAuthorize("hasAuthority('student:export')")
    public String exportInfo(){
        return "student/export";
    }
}
```

同时在templates下面创建一个student目录，将student有关的页面都放在下面：

![image-20240715163143452](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151631590.png)

### 14.2.4 创建一个403页面

在static/error下面创建403.html：

```html
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>403</title>
    </head>
    <body>
        <h2>403:你没有权限访问此页面</h2>
        <a href="/index/toIndex">去首页</a>
    </body>
</html>
```

只要是在这个目录下，只要是这个名字，该403页面就会自动替换默认得403页面。

### 14.2.5 测试

启动项目访问http://localhost:8080/student/qeury：

![image-20240715164906802](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151649903.png)

为了防止前端被黑客攻击，访问的时候需要带过来一个token，由于自定义的登录页面没有写token，所以关闭SpringSecurity框架的跨域保护，这样就不会验证token，不关的话需要验证token，登录就会一直跳转登录页面，所以在WebSecurityConfig的configure方法中：

```html
http.csrf().disable();
```

登录成功后：

![image-20240715170829789](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151708914.png)

正常页面：

![image-20240715171044004](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151710123.png)

403：

![image-20240715171023441](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151710563.png)

## 14.3 当用户没有某权限时，页面不展示该按钮

上面我们创建的项目里面是当用户点击页面上的链接请求到后台之后没有权限会跳转到403，那么如果用户没有权限，对应的按钮就不显示出来，这样岂不是更好吗？

引入下面的依赖

```xml
<dependency>
    <groupId>org.thymeleaf.extras</groupId>
    <artifactId>thymeleaf-extras-springsecurity5</artifactId>
</dependency>
```

修改index.html即可

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org"
      xmlns:sec="http://www.thymeleaf.org/extras/spring-security">
    <head>
        <meta charset="UTF-8">
        <title>系统首页</title>
    </head>
    <body>
        <h1 align="center">系统首页</h1>
        <a href="/student/query" sec:authorize="hasAuthority('student:query')" >查询用户</a>
        <br>
        <a href="/student/add" sec:authorize="hasAuthority('student:save')" >添加用户</a>
        <br>
        <a href="/student/update" sec:authorize="hasAuthority('student:update')" >更新用户</a>
        <br>
        <a href="/student/delete" sec:authorize="hasAuthority('student:delete')" >删除用户</a>
        <br>
        <a href="/student/export" sec:authorize="hasAuthority('student:export')" >导出用户</a>
        <br>
        <br><br><br>
        <h2><a href="/logout">退出</a></h2>
        <br>
    </body>
</html>
```

重启启动登录后查看效果.

# 15 springsecurity 集成图片验证码

以前因为我们自己写登陆的方法可以在自己的登陆方法里面去接收页面传过来的code再和session里面正确的code进行比较 

## 15.1 概述

上一讲里面我们集成了Thymeleaf实现在页面链接的动态判断是否显示，那么在实际开发中，我们会遇到有验证码的功能，那么如何处理呢？

复制上一个工程，修改名字等

## 15.2 原理、存在问题、解决思路

**我们知道Spring Security是通过过滤器链来完成了，所以它的解决方案是创建一个过滤器放到Security的过滤器链中，在自定义的过滤器中比较验证码**

## 15.3 添加依赖（用于生成验证码）

hutool的依赖：

```xml
<!--引入hutool-->
<dependency>
    <groupId>cn.hutool</groupId>
    <artifactId>hutool-all</artifactId>
    <version>5.3.9</version>
</dependency>
```

## 15.4 添加一个获取验证码的接口

写一个controller来创建验证码：

```java
@Controller
public class CaptchaController {
    // request和response对象可以使用注入，也可以在方法参数上声明
    @Autowired
    private HttpServletRequest request;
    @Autowired
    private HttpServletResponse response;

    @GetMapping("/code/image")
    public void getCaptcha() throws IOException {
        // 创建一个长200，宽100，字符个数3，圆圈个数20的验证码
        CircleCaptcha circleCaptcha = CaptchaUtil.createCircleCaptcha(200, 100, 3, 20);
        // 获取到生成的验证码
        String code = circleCaptcha.getCode();
        System.out.println("验证码：" + code);
        // 要将验证码存入到session中，这样前端输入的验证码可以和session中的验证码进行比较
        request.getSession().setAttribute("CAPTCHA_CODE", code);
        // 把图片返回给前端
        // 使用ImageIO类，将图片写到响应流中
        // 参数1：图片；参数2：图片格式；参数3：响应流
        ImageIO.write(circleCaptcha.getImage(), "jpeg", response.getOutputStream());
    }
}
```

这个方法应该是未登录就有权限访问的，所以要在Security配置类WebSecurityConfig里的configure方法中放行：

```java
http.authorizeRequests()
    .mvcMatchers("/code/image")
    .anonymous()  // 放开验证码的请求
    .anyRequest().authenticated();
```

然后要在前端登录页面中，添加一个验证码元素：

```html
<tr>
    <td>验证码:</td>
    <td><input type="text" name="code"> <img src="/code/image" style="height:33px;cursor:pointer;" onclick="this.src=this.src">
        <span th:text="${session.captchaCodeErrorMsg}" style="color: #FF0000;" >username</span>
    </td>
</tr>
```

+ 这个图片一加载，就会访问/code/image，就会得到一个图片
+ onclick="this.src=this.src"：点击之后，会重新访问/code/image，重新得到一个图片

测试：

报错：

![image-20240715175000040](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151750163.png)

观察报错可以看到，验证码是已经生成了，问题出在响应流的位置。因为Spring注入的是单例模式，这里应该是一个请求一个response，所以将request和response都放在方法的参数上，而不使用spring注入：

```java
@Controller
public class CaptchaController {
    @GetMapping("/code/image")
    public void getCaptcha(HttpServletRequest request, ttpServletResponse response) throws IOException {
        // 创建一个长200，宽100，字符个数3，圆圈个数20的验证码
        CircleCaptcha circleCaptcha = CaptchaUtil.createCircleCaptcha(200, 100, 3, 20);
        // 获取到生成的验证码
        String code = circleCaptcha.getCode();
        System.out.println("验证码：" + code);
        // 要将验证码存入到session中，这样前端输入的验证码可以和session中的验证码进行比较
        request.getSession().setAttribute("CAPTCHA_CODE", code);
        // 把图片返回给前端
        // 使用ImageIO类，将图片写到响应流中
        // 参数1：图片；参数2：图片格式；参数3：响应流
        ImageIO.write(circleCaptcha.getImage(), "jpeg", response.getOutputStream());
    }
}
```

![image-20240715175231086](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151752207.png)

控制台输出：

```java
验证码：gii
```

## 15.5 创建验证码过滤器

验证码的校验应该在用户名密码校验之前，先判断验证码，在判断用户名和密码。

SpringSecurity的核心原理就是过滤器链，我们需要自定义一个过滤器，放到过滤器链中，放到用户名密码认证过滤器之前。

创建ValidateCodeFilter类继承自OncePerRequestFilter，OncePerRequestFilter这个过滤器只会执行一次，OncePerRequestFilter类是一个抽象类，间接实现了Fileter接口，里面有很多方法，这是它的继承图：

![image-20240715193903314](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407151939226.png)

```java
@Component
public class ValidateCodeFilter extends OncePerRequestFilter {
    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws ServletException, IOException {
        // 当前所有的路径都会走这个过滤器
        // 需要判断一下，只过滤/login/doLogin路径
        // 如果不是这个路径，就直接放行
        String uri = request.getRequestURI();
        if (!"/login/doLogin".equals(uri)) {
            filterChain.doFilter(request, response);
            return;
        }
        // 是则校验验证码
        validateCode(request, response, filterChain);
    }

    private void validateCode(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws IOException, ServletException {
        // 清除提示信息
        HttpSession session = request.getSession();
        session.removeAttribute("captchaCodeErrorMsg");

        // 获取用户输入的验证码
        String code = request.getParameter("code");
        if (code == null || code.isEmpty()) {
            session.setAttribute("captchaCodeErrorMsg", "验证码不能为空");
            response.sendRedirect("/toLogin");
            return;
        }

        // 获取session中的验证码
        String captchaCode = (String) session.getAttribute("CAPTCHA_CODE");
        if (captchaCode == null || captchaCode.isEmpty()) {
            session.setAttribute("captchaCodeErrorMsg", "验证码错误");
            response.sendRedirect("/toLogin");
            return;
        }

        // 判断是否相等
        if (!code.equalsIgnoreCase(captchaCode)) {
            session.setAttribute("captchaCodeErrorMsg", "验证码不正确");
            response.sendRedirect("/toLogin");
            return;
        }

        // 验证码只能使用一次，删除session中的验证码
        session.removeAttribute("CAPTCHA_CODE");

        filterChain.doFilter(request, response);
    }
}
```

定义好filter后，需要放到过滤器链中，在Security配置类中，注入这个过滤器，然后在configure方法中添加：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private ValidateCodeFilter validateCodeFilter;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // 在用户名密码认证过滤器前添加土拍你验证码过滤器
        http.addFilterBefore(validateCodeFilter, UsernamePasswordAuthenticationFilter.class);

        http.authorizeRequests()
                .mvcMatchers("/code/image")
                .anonymous()  // 放开验证码的请求
                .anyRequest().authenticated();

        http.formLogin()
                .loginPage("/toLogin")  // 配置登录页面
                .usernameParameter("uname")  // 用户名参数名
                .passwordParameter("pwd")  // 密码参数名
                .loginProcessingUrl("/login/doLogin")  // 登录提交的地址
                .failureForwardUrl("/toLogin")  // 登录失败后跳转地址
                .successForwardUrl("/index/toIndex")  // 登录成功后跳转地址
                .permitAll();
        
        http.logout().logoutSuccessUrl("/toLogin");  // 退出成功后跳转登录页面

        http.csrf().disable();  // 关闭跨域保护
    }
}
```

测试：

验证码不能为空：

![image-20240715200554369](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152005470.png)

验证码不正确：

![image-20240715200617445](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152006541.png)

# 16 JWT+Spring Security+redis+mysql 实现认证

## 16.1 准备

将之前的 springsecurity006-database 项目复制一份为springsecurity009-jwt，该项目以实现认证功能和基于方法授权的功能。

还要添加jwt的依赖：

```xml
<dependency>
    <groupId>com.auth0</groupId>
    <artifactId>java-jwt</artifactId>
    <version>4.4.0</version>
</dependency>
```

理清流程：

+ 在用户输入用户名密码之后，如果认证成功，有一个认证成功处理器，在这个处理器里面创建并返回一个token；
+ 用户的请求头带着token访问服务器，使用一个过滤器来判断token是否正确

## 16.2 密钥

在application.propertise中配置密钥：

```properties
jwt.secret=zsm666777
```

## 16.3 jwt工具类

在com.zsm下创建一个utils.JwtUtil类：

```java
@Component
public class JwtUtil {
    // 设置密钥
    @Value("${jwt.secret}")
    public String secret;

    // 创建token
    public String createJwt(String userInfo, List<String> userAuth) {
        // 设置jwt的头部
        Map<String, Object> headerClaims = new HashMap<>();
        headerClaims.put("alg", "HS256");
        headerClaims.put("typ", "jwt");

        return JWT.create()  // 创建要给jwt
                .withHeader(headerClaims)  // 设置头部，头部需要的是一个map
                .withIssuer("zsm")  // 设置payload中的声明：签发人
                .withIssuedAt(new Date())  // 设置payload中的声明：签发时间
                .withExpiresAt(new Date(new Date().getTime() + 1000 * 60 * 60 * 2))  // 设置过期时间为2小时后
                .withClaim("userInfo", userInfo)  // 自定义数据：用户信息
                .withClaim("userAuth", userAuth)  // 自定义数据：用户权限
                .sign(Algorithm.HMAC256(secret));  // 签名，使用HS256进行签名，使用secret作为密钥
    }

    // 校验token
    public boolean verifyToken(String rawJwt) {
        try {
            // 创建校验器
            JWTVerifier verifier = JWT.require(Algorithm.HMAC256(secret)).build();
            // 校验
            DecodedJWT decodedJWT = verifier.verify(rawJwt);
            System.out.println("token验证正确");
            return true;
        } catch (Exception e) {
            // 如果校验不成功就会抛出异常
            System.out.println("token验证不正确");
            return false;
        }
    }

    // 获取用户信息
    public String getUserInfoFromToken(String jwt) {
        try {
            JWTVerifier verifier = JWT.require(Algorithm.HMAC256(secret)).build();
            DecodedJWT decodedJWT = verifier.verify(jwt);
            return decodedJWT.getClaim("userInfo").asString();
        } catch (Exception e) {
            System.out.println("token验证不正确");
            return "";
        }
    }

    // 获取用户权限
    public List<String> getUserAuthFromToken(String jwt) {
        try {
            JWTVerifier verifier = JWT.require(Algorithm.HMAC256(secret)).build();
            DecodedJWT decodedJWT = verifier.verify(jwt);
            return decodedJWT.getClaim("userAuth").asList(String.class);
        } catch (Exception e) {
            System.out.println("token验证不正确");
            return null;
        }
    }
}
```

## 16.4 响应类

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class HttpResult implements Serializable {
    private Integer code; //响应码
    private String msg; //响应消息
    private Object data; //响应对象
} 
```

## 16.5 认证成功处理器

创建一个handler.LoginSuccessHandler类：

```java
@Component
public class LoginSuccessHandler implements AuthenticationSuccessHandler {
    // 注入jwt工具类
    @Autowired
    private JwtUtil jwtUtil;
    // 注入将对象序列化为json的类
    @Autowired
    private ObjectMapper objectMapper;
    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        // 认证成功后就会执行这里的代码
        // 从authentication里获取用户信息
        SecurityUser loginUser = (SecurityUser) authentication.getPrincipal();
        SysUser sysUser = loginUser.getSysUser();
        String userInfo = objectMapper.writeValueAsString(sysUser);
        // 获取权限列表
        List<SimpleGrantedAuthority> authorities = (List<SimpleGrantedAuthority>) loginUser.getAuthorities();
        // 将权限列表中的数据一个一个的调用getAuthority方法，得到一个字符串，最终收集到一个列表中
        List<String> authList = authorities.stream().map(SimpleGrantedAuthority::getAuthority).collect(Collectors.toList());
        // 生成token
        String jwt = jwtUtil.createJwt(userInfo, authList);
        // 封装响应结果
        HttpResult httpResult = new HttpResult(1, "jwt生成成功", jwt);
        // 响应给前端token
        printToken(request, response, httpResult);
    }

    private void printToken(HttpServletRequest request, HttpServletResponse response, HttpResult httpResult) throws IOException {
        // 将响应结果转为json
        String respJson = objectMapper.writeValueAsString(httpResult);
        // 设置响应内容类型
        response.setContentType("application/json;charset=utf-8");
        // 响应
        PrintWriter out = response.getWriter();
        out.write(respJson);
        out.flush();
    }
}
```

定义完后，需要配置到Security的配置类中：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private LoginSuccessHandler loginSuccessHandler;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
                .successHandler(loginSuccessHandler)  // 配置认证成功处理
                .permitAll();
    }
}
```

+ 其实也可以在这里使用匿名内部类

测试：

登录成功后：

![image-20240716092252803](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407160923003.png)

现在已经可以成功给用户生成并返回token了，接下来就是用户访问服务器时携带token，服务器解析token。

## 16.6 jwt过滤器

新建一个filter.JwtCheckFilter用于检查token：

```java
@Component
public class JwtCheckFilter extends OncePerRequestFilter {
    @Autowired
    private JwtUtil jwtUtil;
    @Autowired
    private ObjectMapper objectMapper;
    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws ServletException, IOException {
        HttpResult httpResult = new HttpResult();

        // 登录请求时，不需要判断
        String uri = request.getRequestURI();
        if ("/login".equals(uri)) {
            filterChain.doFilter(request, response);
            return;
        }

        // jwt存在请求头里面，所以从头里获取
        String authorization = request.getHeader("Authorization");
        // 如果没有token
        if (authorization == null || authorization.isEmpty()) {
            httpResult = new HttpResult(0, "jwt 为空", null);
            printToken(request, response, httpResult);
            return;
        }
        // 有token的话，将jwt开头的bearer 去掉，获取到真正的token
        String token = authorization.replace("bearer ", "");
        // 如果实际token为空
        if (token.isEmpty()) {
            httpResult = new HttpResult(0, "jwt 为空", null);
            printToken(request, response, httpResult);
            return;
        }
        // 否则就要校验实际token
        boolean verifyResult = jwtUtil.verifyToken(token);
        if (!verifyResult) {
            httpResult = new HttpResult(-1, "jwt 非法", null);
            printToken(request, response, httpResult);
            return;
        }
        // 校验成功后，获取用户信息和权限信息
        String userInfo = jwtUtil.getUserInfoFromToken(token);
        List<String> userAuthList = jwtUtil.getUserAuthFromToken(token);

        // 反序列化得到SysUser对象，因为创建token是就是用的SysUser对象
        SysUser sysUser = objectMapper.readValue(userInfo, SysUser.class);
        List<SimpleGrantedAuthority> authList = userAuthList.stream().map(SimpleGrantedAuthority::new).collect(Collectors.toList());
        // 创建用户名密码认证token
        UsernamePasswordAuthenticationToken authenticationToken = new UsernamePasswordAuthenticationToken(sysUser, null, authList);
        // 将这个token放到安全上下文中，才代表认证成功
        // 之前都是框架会自动生成一个这样的token
        SecurityContextHolder.getContext().setAuthentication(authenticationToken);
        
        filterChain.doFilter(request, response);
    }

    private void printToken(HttpServletRequest request, HttpServletResponse response, HttpResult httpResult) throws IOException {
        // 将响应结果转为json
        String respJson = objectMapper.writeValueAsString(httpResult);
        // 设置响应内容类型
        response.setContentType("application/json;charset=utf-8");
        // 响应
        PrintWriter out = response.getWriter();
        out.write(respJson);
        out.flush();
    }
}
```

接着配置这个filter到filter链中，在用户名密码认证过滤器之前：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private LoginSuccessHandler loginSuccessHandler;
    @Autowired
    private JwtCheckFilter jwtCheckFilter;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // 添加过滤器
        http.addFilterBefore(jwtCheckFilter, UsernamePasswordAuthenticationFilter.class);
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
                .successHandler(loginSuccessHandler)  // 配置认证成功处理
                .permitAll();
    }
}
```

关于用户名密码认证token：之前都是只要输入用户名和密码正确就可以正常登录，是因为框架自动创建了一个UsernamePasswordAuthenticationToken放在了安全上下文中，现在是没有登录，通过token来访问，所以要手动创建UsernamePasswordAuthenticationToken并存到安全上下文中，达到登录的状态。

测试：重新登录获取一个token，使用api工具，发送请求到/student/query，请求头中携带token：

![image-20240716101730311](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161017485.png)

+ token一般放在请求头中的Authorization里
+ 一般要在token前面加上 `bearer `，要注意bearer后面有个空格，所以服务器端要将这个前缀去掉才能获取到真正的token

现在停止服务，然后重启，测试当前这个token是否还可以用：依旧可以使用。

## 16.7 禁用session

在Security的配置类中，配置不创建session，这样交互都只依靠jwt：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private LoginSuccessHandler loginSuccessHandler;
    @Autowired
    private JwtCheckFilter jwtCheckFilter;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // 添加检查jwt的过滤器
        http.addFilterBefore(jwtCheckFilter, UsernamePasswordAuthenticationFilter.class);
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
                .successHandler(loginSuccessHandler)  // 配置认证成功处理
                .permitAll();
        // 不创建session
        http.sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS);
    }
}
```

## 16.8 问题

jwt一旦生成后，就只能等待他自己过期作废，所以无法在退出时作废一个用户的jwt，用户退出登录后，还是可以那这个jwt访问服务器。

但是正常来说，用户退出后，就不能在访问系统了，应该要重新登录。

怎么解决：使用redis

+ 登陆成功之后把生成JWT存到redis中：

  | key            | value                               |
  | -------------- | ----------------------------------- |
  | logintoken:jwt | UsernamePasswordAuthenticationToken |

+ 用户退出时，从redis中删除该token

用户每次访问时，先校验jwt是否合法，如果合法再从redis里面取出logintoken:jwt判断这个jwt还存不存在，如果不存在就说是用户已经退出来，就返回未登陆。

## 16.9 使用redis解决问题

### 16.9.1 准备

将以上项目复制一份为：springsecurity010-jwt-redis.

添加redis依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
```

启动redis服务器：

> 如果有远程服务器的redis：
>
> 使用xshell连接上服务器，进入redis目录，找到redis的配置文件 redis.conf或者sentinel.conf：
>
> 修改为后台启动：
>
> ```conf
> daemonize yes
> ```
>
> 放开绑定，否则本机连不上服务器上的redis：
>
> ```conf
> bind 0.0.0.0
> ```
>
> 设置密码：
>
> ```conf
> requirepass 123456
> ```
>
> 设置日志文件目录：
>
> ```conf
> logfile "/root/redis.log"
> ```

直接在windows上启动：

![image-20240716104859712](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161048873.png)

在application.properties中配置redis的地址：

```properties
spring.redis.host=localhost
spring.redis.port=6379
```

+ 这是默认的信息，可以自己修改
+ 如果在本机上直接启动redis的话，不用什么配置

分析：

1. 在用户认证成功后，生成jwt，并将jwt存入redis，设置过期时间和jwt的过期时间一致；
2. 在用户点击退出后，删除redis中的jwt；
3. 用户拿着token访问服务器时，校验token，校验成功的话就去redis中查看token是否存在，不存在不让访问。

### 16.9.2 将jwt存入redis

在登录成功处理器中：

```java
// 注入redis
@Autowired
private StringRedisTemplate stringRedisTemplate;
@Override
public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
    // 认证成功后就会执行这里的代码
    // 从authentication里获取用户信息
    SecurityUser loginUser = (SecurityUser) authentication.getPrincipal();
    SysUser sysUser = loginUser.getSysUser();
    String userInfo = objectMapper.writeValueAsString(sysUser);
    // 获取权限列表
    List<SimpleGrantedAuthority> authorities = (List<SimpleGrantedAuthority>) loginUser.getAuthorities();
    // 将权限列表中的数据一个一个的调用getAuthority方法，得到一个字符串，最终收集到一个列表中
    List<String> authList = authorities.stream()
        .map(SimpleGrantedAuthority::getAuthority)
        .collect(Collectors.toList());
    // 生成token
    String jwt = jwtUtil.createJwt(userInfo, authList);
    // 封装响应结果
    HttpResult httpResult = new HttpResult(1, "jwt生成成功", jwt);
    
    // 将jwt放到redis中
    // 参数：键、值、过期时间、时间单位
    stringRedisTemplate.opsForValue().set("loginkey:" + jwt,
                                          objectMapper.writeValueAsString(authentication), 
                                          2, 
                                          TimeUnit.HOURS);
    
    // 响应给前端token
    printToken(request, response, httpResult);
}
```

### 16.9.3 退出删除redis中的jwt

新建一个退出成功处理器，在这里面删除redis中的jwt：

```java
@Component
public class MyLogoutSuccessHandler implements LogoutSuccessHandler {
    @Autowired
    private StringRedisTemplate stringRedisTemplate;
    @Autowired
    private JwtUtil jwtUtil;
    @Autowired
    private ObjectMapper objectMapper;
    @Override
    public void onLogoutSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        HttpResult httpResult = new HttpResult();

        // 需要判断当前用户存不存在，一定是登录成功后的用户，带着jwt来退出
        String authorization = request.getHeader("Authorization");
        if (authorization == null || authorization.isEmpty()) {
            httpResult = new HttpResult(0, "jwt 不存在", null);
            printToken(request, response, httpResult);
            return;
        }
        // 删除bearer
        String jwt = authorization.replace("bearer ", "");
        // 校验
        boolean res = jwtUtil.verifyToken(jwt);
        if (!res) {
            httpResult = new HttpResult(0, "jwt 非法", null);
            printToken(request, response, httpResult);
            return;
        }
        // 退出，从redis中删除
        stringRedisTemplate.delete("loginkey:" + jwt);
        
        // 响应退出成功
        httpResult = new HttpResult(1, "退出成功", null);
        printToken(request, response, httpResult);
    }

    private void printToken(HttpServletRequest request, HttpServletResponse response, HttpResult httpResult) throws IOException {
        // 将响应结果转为json
        String respJson = objectMapper.writeValueAsString(httpResult);
        // 设置响应内容类型
        response.setContentType("application/json;charset=utf-8");
        // 响应
        PrintWriter out = response.getWriter();
        out.write(respJson);
        out.flush();
    }
}
```

然后要在Security配置类中配置这个处理器：

```java
@EnableGlobalMethodSecurity(prePostEnabled = true)
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private LoginSuccessHandler loginSuccessHandler;
    @Autowired
    private JwtCheckFilter jwtCheckFilter;
    @Autowired
    private MyLogoutSuccessHandler logoutSuccessHandler;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        // 添加检查jwt的过滤器
        http.addFilterBefore(jwtCheckFilter, UsernamePasswordAuthenticationFilter.class);
        http.authorizeRequests().anyRequest().authenticated();
        http.formLogin()
                .successHandler(loginSuccessHandler)  // 配置认证成功处理
                .permitAll();
        // 不创建session
        http.sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS);
        // 配置退出成功处理器
        http.logout().logoutSuccessHandler(logoutSuccessHandler);
    }
}
```

### 16.9.4 访问时判断redis中是否有jwt

在用户进行访问时，需要判断redis中是否当前用户的jwt，以此来判断用户的状态，要在JwtCheckFilter中，校验jwt后，此时判断redis中是否有jwt，有的话说明用户没有退出，可以访问；否则说明退出了，不能访问：

```java
@Autowired
private StringRedisTemplate stringRedisTemplate;

@Override
protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws ServletException, IOException {
    HttpResult httpResult = new HttpResult();

    // 登录请求时，不需要判断
    String uri = request.getRequestURI();
    if ("/login".equals(uri)) {
        filterChain.doFilter(request, response);
        return;
    }

    // jwt存在请求头里面，所以从头里获取
    String authorization = request.getHeader("Authorization");
    // 如果没有token
    if (authorization == null || authorization.isEmpty()) {
        httpResult = new HttpResult(0, "jwt 为空", null);
        printToken(request, response, httpResult);
        return;
    }
    // 有token的话，将jwt开头的bearer 去掉，获取到真正的token
    String token = authorization.replace("bearer ", "");
    // 如果实际token为空
    if (token.isEmpty()) {
        httpResult = new HttpResult(0, "jwt 为空", null);
        printToken(request, response, httpResult);
        return;
    }
    // 否则就要校验实际token
    boolean verifyResult = jwtUtil.verifyToken(token);
    if (!verifyResult) {
        httpResult = new HttpResult(-1, "jwt 非法", null);
        printToken(request, response, httpResult);
        return;
    }

    // 判断用户的登录状态，redis中有就是登录，否则就是退出了登录
    String redisToken = stringRedisTemplate.opsForValue().get("loginkey:" + token);
    if (redisToken == null || redisToken.isEmpty()) {
        httpResult = new HttpResult(-1, "用户已退出，请重新登录", null);
        printToken(request, response, httpResult);
        return;
    }

    // 校验成功后，获取用户信息和权限信息
    String userInfo = jwtUtil.getUserInfoFromToken(token);
    List<String> userAuthList = jwtUtil.getUserAuthFromToken(token);

    // 反序列化得到SysUser对象，因为创建token是就是用的SysUser对象
    SysUser sysUser = objectMapper.readValue(userInfo, SysUser.class);
    List<SimpleGrantedAuthority> authList = userAuthList.stream().map(SimpleGrantedAuthority::new).collect(Collectors.toList());
    // 创建用户名密码认证token
    UsernamePasswordAuthenticationToken authenticationToken = new UsernamePasswordAuthenticationToken(sysUser, null, authList);
    // 将这个token放到安全上下文中，才代表认证成功
    // 之前都是框架会自动生成一个这样的token
    SecurityContextHolder.getContext().setAuthentication(authenticationToken);

    filterChain.doFilter(request, response);
}
```

测试：

首先登录成功后是会在认证成功处理器LoginSuccessHandler中将jwt加入redis：

![image-20240716112818011](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161128186.png)

然后关闭项目，重启项目，拿到上面生成的token，使用api工具进行访问，会在JwtCheckFilter中进行判断redis中是否有token：

![image-20240716124054143](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161240331.png)

![image-20240716124119820](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161241972.png)

最后是访问退出接口，会在退出成功处理器MyLogoutSuccessHandler中，删除redis中的jwt：

![image-20240716130229098](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161302258.png)

![](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161311053.png)

退出后，再访问：

![image-20240716130326135](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161303291.png)

注意：访问登录或退出接口时，如果是get请求，会跳转到登录或登出页面，post请求才是实际的接口，比如用get访问退出接口：

![image-20240716130817411](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161308575.png)

用post请求访问，会发现实际上跳到了登录页面：
![image-20240716130905161](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161309329.png)

可以查看get请求下logout接口返回的页面代码，表单中有一个隐藏的元素，`_crsf`，在post请求中的请求体里加上这个参数，就可以正常登出：

![image-20240716131106896](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161311053.png)

登录接口也是这样。

或者在Security的配置类中，关闭跨域保护，这样生成的登录、登出页面就没有哪个crsf的隐藏元素，访问post的登录登出接口也就不需要添加该参数，可以直接访问：
```
http.csrf().disable();
```

![image-20240716131455541](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407161314699.png)
