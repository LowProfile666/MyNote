# SpringSecurity从入门到精通

## 1.简介

[Spring Security 中文文档 ](https://springdoc.cn/spring-security/)

Spring Security是一个Java框架，用于保护应用程序的安全性。它提供了一套全面的安全解决方案，包括身份验证、授权、防止攻击等功能。Spring Security基于过滤器链的概念，可以轻松地集成到任何基于Spring的应用程序中。它支持多种身份验证选项和授权策略，开发人员可以根据需要选择适合的方式。此外，Spring Security还提供了一些附加功能，如集成第三方身份验证提供商和单点登录，以及会话管理和密码编码等。总之，Spring Security是一个强大且易于使用的框架，可以帮助开发人员提高应用程序的安全性和可靠性。

一般Web应用的需要进行**认证**和**授权**。

**认证：验证当前访问系统的是不是本系统的用户，并且要确认具体是哪个用户**

**授权：经过认证后判断当前用户是否有权限进行某个操作**

而认证和授权也是SpringSecurity作为安全框架的核心功能

## 2.快速入门

### 2.1准备工作

创建一个空项目，在空项目里创建一个普通maven模块，设置好maven，手动构建成springboot项目。

在pom.xml文件中设置父工程和添加依赖：

```xml
<parent>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-parent</artifactId>
    <version>3.3.1</version>
</parent>
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
        <optional>true</optional>
    </dependency>
</dependencies>
```

+ 原教程中用的springboot 2.5.0

创建启动类，创建com.zsm.Application类，使用@SpringBootApplication注解，创建主方法，主方法中调用run方法：

```java
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
}
```

+ run方法中传的是当前启动类的字节码对象，和args参数

创建一个com.zsm.controller.HelloController类：

```java
@RestController
public class HelloController {
    @RequestMapping("/hello")
    public String hello() {
        return "hello";
    }
}
```

此时启动项目，访问http://localhost:8080/hello：

![image-20240711171102742](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111711858.png)

### 2.2引入SpringSecurity

你可以通过添加 `spring-boot-starter-security` 来为你的Spring Boot项目添加Spring Security：

```xml
<!--security依赖项目(重点)-->
 <dependency>
     <groupId>org.springframework.boot</groupId>
     <artifactId>spring-boot-starter-security</artifactId>
 </dependency>       
```

引入依赖后，尝试访问之前的接口http://localhost:8080/hello时，就会跳转到一个SpringSecurity的默认的登录页面，默认的用户名是user，密码会输出在控制台：

![image-20240711171531038](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111715122.png)

![image-20240711171455817](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111714915.png)

输入用户名和密码后，成功登录会继续跳转hello地址：

![image-20240711171625679](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111716758.png)

如果要退出登录，可以访问 `localhost:8080/logout`，这是SpringSecurity默认的退出登录接口，然后确认你想注销：

![image-20240711171928449](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111719550.png)

退出登录后，再访问hello接口，就又需要登录。

所以这个SpringSecurity就是对我们的资源进行一个保护，要求用户必须进行一些认证和授权的流程。

## 3.认证

### 3.1登录校验流程

认证其实就是登录校验。

前后端分离的情况下，认证的核心就是token，token可以就理解成一个加密之后的字符串。服务器可以通过你是否携带了这个token或者解析token后获取到加密前的信息，来判断你是否是受信任用户。

![image-20240711172314869](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111723997.png)

### 3.2原理初探

`SpringSecurity`的原理其实就是一个过滤器链，内部包含了提供各种功能的过滤器。这里我们可以看看入门案例中的过滤器。

![image-20240510123927556](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111728349.png)

图中只展示了核心过滤器，其它的非核心过滤器并没有在图中展示。

+ **UsernamePasswordAuthenticationFilter**:负责处理我们在登陆页面填写了用户名密码后的登陆请求。入门案例的认证工作主要有它负责。

+ **ExceptionTranslationFilter**：处理过滤器链中抛出的任何AccessDeniedException和AuthenticationException 。

+ **FilterSecurityInterceptor**：负责权限校验的过滤器。

我们可以通过Debug查看当前系统中SpringSecurity过滤器链中有哪些过滤器及它们的顺序，在启动类中，run方法最终会返回一个容器类对象：

![image-20240711173749755](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111737831.png)

让程序停在这里，右键单击鼠标，选择Evaluate Expression，通过context这个容器对象来获取过滤器链，查看里面所有的过滤器 ：

![image-20240711173919014](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111739103.png)

输入 `context.getBean(DefaultSecurityFilterChain.class)` 求值

![image-20240711174034816](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111740924.png)

黄色框框住的两个过滤器就是显示登录页面和登出页面的。

### 3.3认证详流程详解

![image-20240711175039848](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407111750984.png)

概念速查:

`Authentication`接口: 它的实现类，表示当前访问系统的用户，封装了用户相关信息。

`AuthenticationManager`接口：定义了认证Authentication的方法

`UserDetailsService`接口：加载用户特定数据的核心接口。里面定义了一个根据用户名查询用户信息的方法。

`UserDetails`接口：提供核心用户信息。通过UserDetailsService根据用户名获取处理的用户信息要封装成UserDetails对象返回。然后将这些信息封装到Authentication对象中

### 3.4自定义

知道了大体流程，就知道可以修改哪里来实现自定义的流程。比如，要从数据库中去验证用户，就只需要自己实现UserDetailsService接口即可，因为是这个接口的实现类在进行验证用户的操作。

这是登录流程：

![image-20240712085805912](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407120858037.png)

登录后，每次请求还要校验，这是校验流程：
![image-20240712090119650](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407120901770.png)

那么解析token获取到了userid，但是其他的用户信息呢？可以通过数据库查询得到，但是每一次请求都会进行一次校验，如果每一次都要访问数据库的话，那么会很浪费事件，所以可以把用户信息存在redis中，来减少数据库的压力。

那么在redis中查询，就需要在redis中有用户的信息，这个用户的信息可以在登录成功后，写入redis中。在生成jwt后，用userid作为key，用户信息作为value存入redis中。

![image-20240712090641281](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407120906402.png)

## 4.案例实战

### 4.1 思路分析

登录：

1. 自定义登录接口：调用ProviderManager的方法进行认证，认证成功后生成jwt，并把用户信息存入redis中
2. 自定义UserDetailsService：在这个实现类中去查询数据库

校验：

1. 定义jwt认证过滤器：获取token、解析token、从redis中获取用户信息、存入SecurityContextHolder

**自定义登录接口**

调用`ProviderManager`的方法进行认证 如果认证通过生成jwt

把用户信息存入redis中

> `SpringSecurity`在默认的认证过程中如果账号密码校验成功会返回Authentication对象，之后`UsernamePasswordAuthenticationFilter`会将用户信息`Authentication`存入`SecurityContextHolder`中
>
> 但是我们在实际运用场景中认证通过后还需要向前端返回一个JSON格式的数据里面包括了JWT
>
> 所以此时我们需要写一个自定义登录接口

**自定义UserDetailsService接口**

在这个实现类中去查询数据库

校验：

+ 定义Jwt认证过滤器

+ 获取token

+ 解析token获取其中的userid

+ 从redis中获取用户信息

+ 存入SecurityContextHolder

> `SpringSecurity` 默认是在内存中查找对应的用户名密码然后封装成`UserDetai`l对象交给`DaoAuthenticationProcider`校验
>
> 但是我们在实际运用场景中是从数据库中查找用户信息	
>
> 所以此时我们需要写一个`UserDetailsService`的实现类用来在数据库中查询用户信息并且封装到`UserDetai`l对象中

### 4.2准备工作

新建一个项目，手动改为SpingBoot项目。

#### **添加依赖**(pom.xml)

要引入redis依赖、jwt依赖、fastjson依赖等

```xml
<!-- Spring Boot 安全功能的starter包，用于web应用的安全控制 -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-security</artifactId>
</dependency>
<!-- Spring Boot Web功能的starter包，提供web应用的基本功能 -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
<!-- Lombok，提供简单的代码生成工具，减少样板代码，设置为可选依赖 -->
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <optional>true</optional>
</dependency>
<!-- Spring Boot的测试starter包，用于单元测试和集成测试 -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
<!-- Spring Security的测试包，用于安全测试 -->
<dependency>
    <groupId>org.springframework.security</groupId>
    <artifactId>spring-security-test</artifactId>
    <scope>test</scope>
</dependency>
<!-- Redis的starter包，用于集成Redis作为缓存或持久化方案 -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
<!-- FastJSON，一个Java语言编写的高性能功能完备的JSON库 -->
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>fastjson</artifactId>
    <version>1.2.33</version>
</dependency>
<!-- JWT（JSON Web Token）的库，用于生成和解析JWT -->
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt</artifactId>
    <version>0.9.0</version>
</dependency>
<!-- JAXB API，用于XML和Java对象之间的绑定 -->
<dependency>
    <groupId>javax.xml.bind</groupId>
    <artifactId>jaxb-api</artifactId>
    <version>2.3.1</version>
</dependency>
<!-- MyBatis Plus的Spring Boot starter，用于简化MyBatis的使用 -->
<dependency>
    <groupId>com.baomidou</groupId>
    <artifactId>mybatis-plus-spring-boot3-starter</artifactId>
    <version>3.5.5</version>
</dependency>
<!-- MySQL连接器，用于连接和操作MySQL数据库 -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.29</version>
</dependency>
<!-- Spring Boot的测试starter包，重复项，可能用于不同目的 -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
</dependency>
```

#### **添加Redis相关配置**

定义一个utils包，直接复制代码会自动创建一个名为FastJsonRedisSerializer的java文件，这是用来将Redis使用Fastjson序列化的：

```java
public class FastJsonRedisSerializer<T> implements RedisSerializer<T> {
    public static final Charset DEFAULT_CHARSET = Charset.forName("UTF-8");
    private Class<T> clazz;

    static {
        ParserConfig.getGlobalInstance().setAutoTypeSupport(true);
    }

    public FastJsonRedisSerializer(Class<T> clazz) {
        super();
        this.clazz = clazz;
    }

    @Override
    public byte[] serialize(T t) throws SerializationException {
        if (t == null) {
            return new byte[0];
        }
        return JSON.toJSONString(t,
                SerializerFeature.WriteClassName).getBytes(DEFAULT_CHARSET);
    }

    @Override
    public T deserialize(byte[] bytes) throws SerializationException {
        if (bytes == null || bytes.length <= 0) {
            return null;
        }
        String str = new String(bytes, DEFAULT_CHARSET);
        return JSON.parseObject(str, clazz);
    }

    protected JavaType getJavaType(Class<?> clazz) {
        return TypeFactory.defaultInstance().constructType(clazz);
    }
}
```

然后还需要定义一个配置类，写一些redis的配置，创建一个config包，直接复制：

```java
@Configuration
public class RedisConfig {
    @Bean
    @SuppressWarnings(value = {"unchecked", "rawtypes"})
    public RedisTemplate<Object, Object> redisTemplate(RedisConnectionFactory
                                                               connectionFactory) {
        RedisTemplate<Object, Object> template = new RedisTemplate<>();
        template.setConnectionFactory(connectionFactory);
        FastJsonRedisSerializer serializer = new FastJsonRedisSerializer(Object.class);
        // 使用StringRedisSerializer来序列化和反序列化redis的key值
        template.setKeySerializer(new StringRedisSerializer());
        template.setValueSerializer(serializer);
        // Hash的key也采用StringRedisSerializer的序列化方式
        template.setHashKeySerializer(new StringRedisSerializer());
        template.setHashValueSerializer(serializer);
        template.afterPropertiesSet();
        return template;
    }
}
```

#### **响应类**

前后端分离项目一般都会统一一个响应格式，所以定义一个响应类，新建一个包domain，复制代码：

```java
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ResponseResult<T> {
    /**
     * 状态码
     */
    private Integer code;
    /**
     * 提示信息，如果有错误时，前端可以获取该字段进行提示
     */
    private String msg;
    /**
     * 查询到的结果数据，
     */
    private T data;

    public ResponseResult(Integer code, String msg) {
        this.code = code;
        this.msg = msg;
    }

    public ResponseResult(Integer code, T data) {
        this.code = code;
        this.data = data;
    }

    public Integer getCode() {
        return code;
    }

    public void setCode(Integer code) {
        this.code = code;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public ResponseResult(Integer code, String msg, T data) {
        this.code = code;
        this.msg = msg;
        this.data = data;
    }
}

```

#### **工具类**

生成jwt和解析jwt的工具：

```java
/**
 * JWT工具类
 */
public class JwtUtil {
    //有效期为
    public static final Long JWT_TTL = 60 * 60 * 1000L;// 60 * 60 *1000 一个小时
    //设置秘钥明文
    public static final String JWT_KEY = "sangeng";

    public static String getUUID() {
        String token = UUID.randomUUID().toString().replaceAll("-", "");
        return token;
    }

    /**
     * 生成jtw
     *
     * @param subject token中要存放的数据（json格式）
     * @return
     */
    public static String createJWT(String subject) {
        JwtBuilder builder = getJwtBuilder(subject, null, getUUID());// 设置过期时间
        return builder.compact();
    }

    /**
     * 生成jtw
     *
     * @param subject   token中要存放的数据（json格式）
     * @param ttlMillis token超时时间
     * @return
     */
    public static String createJWT(String subject, Long ttlMillis) {
        JwtBuilder builder = getJwtBuilder(subject, ttlMillis, getUUID());// 设置过期时间
        return builder.compact();
    }

    private static JwtBuilder getJwtBuilder(String subject, Long ttlMillis,
                                            String uuid) {
        SignatureAlgorithm signatureAlgorithm = SignatureAlgorithm.HS256;
        SecretKey secretKey = generalKey();
        long nowMillis = System.currentTimeMillis();
        Date now = new Date(nowMillis);
        if (ttlMillis == null) {
            ttlMillis = JwtUtil.JWT_TTL;
        }
        long expMillis = nowMillis + ttlMillis;
        Date expDate = new Date(expMillis);
        return Jwts.builder()
                .setId(uuid) //唯一的ID
                .setSubject(subject) // 主题 可以是JSON数据
                .setIssuer("sg") // 签发者
                .setIssuedAt(now) // 签发时间
                .signWith(signatureAlgorithm, secretKey) //使用HS256对称加密算法签名, 第二个参数为秘钥
                .setExpiration(expDate);
    }

    /**
     * 创建token
     *
     * @param id
     * @param subject
     * @param ttlMillis
     * @return
     */
    public static String createJWT(String id, String subject, Long ttlMillis) {
        JwtBuilder builder = getJwtBuilder(subject, ttlMillis, id);// 设置过期时间
        return builder.compact();
    }

    public static void main(String[] args) throws Exception {
        String token ="eyJhbGciOiJIUzI1NiJ9.eyJqdGkiOiJjYWM2ZDVhZi1mNjVlLTQ0MDAtYjcxMi0zYWEwOGIyOTIwYjQiLCJzdWIiOiJzZyIsImlzcyI6InNnIiwiaWF0IjoxNjM4MTA2NzEyLCJleHAiOjE2MzgxMTAzMTJ9.JVsSbkP94wuczb4QryQbAke3ysBDIL5ou8fWsbt_ebg ";
        Claims claims = parseJWT(token);
        System.out.println(claims);
    }

    /**
     * 生成加密后的秘钥 secretKey
     *
     * @return
     */
    public static SecretKey generalKey() {
        byte[] encodedKey = Base64.getDecoder().decode(JwtUtil.JWT_KEY);
        SecretKey key = new SecretKeySpec(encodedKey, 0, encodedKey.length,
                "AES");
        return key;
    }

    /**
     * 解析
     *
     * @param jwt
     * @return
     * @throws Exception
     */
    public static Claims parseJWT(String jwt) throws Exception {
        SecretKey secretKey = generalKey();
        return Jwts.parser()
                .setSigningKey(secretKey)
                .parseClaimsJws(jwt)
                .getBody();
    }
}
```

redis的工具类，对redis的方法进行了进一步的封装：

```java
@SuppressWarnings(value = {"unchecked", "rawtypes"})
@Component
public class RedisCache {
    @Autowired
    public RedisTemplate redisTemplate;

    /**
     * 缓存基本的对象，Integer、String、实体类等
     *
     * @param key   缓存的键值
     * @param value 缓存的值
     */
    public <T> void setCacheObject(final String key, final T value) {
        redisTemplate.opsForValue().set(key, value);
    }

    /**
     * 缓存基本的对象，Integer、String、实体类等
     *
     * @param key      缓存的键值
     * @param value    缓存的值
     * @param timeout  时间
     * @param timeUnit 时间颗粒度
     */
    public <T> void setCacheObject(final String key, final T value, final
    Integer timeout, final TimeUnit timeUnit) {
        redisTemplate.opsForValue().set(key, value, timeout, timeUnit);
    }

    /**
     * 设置有效时间
     *
     * @param key     Redis键
     * @param timeout 超时时间
     * @return true=设置成功；false=设置失败
     */
    public boolean expire(final String key, final long timeout) {
        return expire(key, timeout, TimeUnit.SECONDS);
    }

    /**
     * 设置有效时间
     *
     * @param key     Redis键
     * @param timeout 超时时间
     * @param unit    时间单位
     * @return true=设置成功；false=设置失败
     */
    public boolean expire(final String key, final long timeout, final TimeUnit unit) {
        return redisTemplate.expire(key, timeout, unit);
    }

    /**
     * 获得缓存的基本对象。
     *
     * @param key 缓存键值
     * @return 缓存键值对应的数据
     */
    public <T> T getCacheObject(final String key) {
        ValueOperations<String, T> operation = redisTemplate.opsForValue();
        return operation.get(key);
    }

    /**
     * 删除单个对象
     *
     * @param key
     */
    public boolean deleteObject(final String key) {
        return redisTemplate.delete(key);
    }

    /**
     * 删除集合对象
     *
     * @param collection 多个对象
     * @return
     */
    public long deleteObject(final Collection collection) {
        return redisTemplate.delete(collection);
    }

    /**
     * 缓存List数据
     *
     * @param key      缓存的键值
     * @param dataList 待缓存的List数据
     * @return 缓存的对象
     */
    public <T> long setCacheList(final String key, final List<T> dataList) {
        Long count = redisTemplate.opsForList().rightPushAll(key, dataList);
        return count == null ? 0 : count;
    }

    /**
     * 获得缓存的list对象
     *
     * @param key 缓存的键值
     * @return 缓存键值对应的数据
     */
    public <T> List<T> getCacheList(final String key) {
        return redisTemplate.opsForList().range(key, 0, -1);
    }

    /**
     * 缓存Set
     *
     * @param key     缓存键值
     * @param dataSet 缓存的数据
     * @return 缓存数据的对象
     */
    public <T> BoundSetOperations<String, T> setCacheSet(final String key, final
    Set<T> dataSet) {
        BoundSetOperations<String, T> setOperation =
                redisTemplate.boundSetOps(key);
        Iterator<T> it = dataSet.iterator();
        while (it.hasNext()) {
            setOperation.add(it.next());
        }
        return setOperation;
    }

    /**
     * 获得缓存的set
     *
     * @param key
     * @return
     */
    public <T> Set<T> getCacheSet(final String key) {
        return redisTemplate.opsForSet().members(key);
    }

    /**
     * 缓存Map
     *
     * @param key
     * @param dataMap
     */
    public <T> void setCacheMap(final String key, final Map<String, T> dataMap) {
        if (dataMap != null) {
            redisTemplate.opsForHash().putAll(key, dataMap);
        }
    }

    /**
     * 获得缓存的Map
     *
     * @param key
     * @return
     */
    public <T> Map<String, T> getCacheMap(final String key) {
        return redisTemplate.opsForHash().entries(key);
    }

    /**
     * 往Hash中存入数据
     *
     * @param key   Redis键
     * @param hKey  Hash键
     * @param value 值
     */
    public <T> void setCacheMapValue(final String key, final String hKey, final
    T value) {
        redisTemplate.opsForHash().put(key, hKey, value);
    }

    /**
     * 获取Hash中的数据
     *
     * @param key  Redis键
     * @param hKey Hash键
     * @return Hash中的对象
     */
    public <T> T getCacheMapValue(final String key, final String hKey) {
        HashOperations<String, String, T> opsForHash =
                redisTemplate.opsForHash();
        return opsForHash.get(key, hKey);
    }

    /**
     * 删除Hash中的数据
     *
     * @param key
     * @param hkey
     */
    public void delCacheMapValue(final String key, final String hkey) {
        HashOperations hashOperations = redisTemplate.opsForHash();
        hashOperations.delete(key, hkey);
    }

    /**
     * 获取多个Hash中的数据
     *
     * @param key   Redis键
     * @param hKeys Hash键集合
     * @return Hash对象集合
     */
    public <T> List<T> getMultiCacheMapValue(final String key, final
    Collection<Object> hKeys) {
        return redisTemplate.opsForHash().multiGet(key, hKeys);
    }

    /**
     * 获得缓存的基本对象列表
     *
     * @param pattern 字符串前缀
     * @return 对象列表
     */
    public Collection<String> keys(final String pattern) {

        return redisTemplate.keys(pattern);
    }
}
```

web工具，向响应里写数据：

```java
public class WebUtils {
    /**
     * 将字符串渲染到客户端
     *
     * @param response 渲染对象
     * @param string   待渲染的字符串
     * @return null
     */
    public static String renderString(HttpServletResponse response, String
            string) {
        try {
            response.setStatus(200);
            response.setContentType("application/json");
            response.setCharacterEncoding("utf-8");
            response.getWriter().print(string);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
```

```java
public class RedisUtils {
    // 启动Redis服务器
    public static void startRedisServer() {
        try {
            Process process = Runtime.getRuntime().exec("C:\\develop1\\Redis-x64-3.2.100\\redis-server.exe C:\\develop1\\Redis-x64-3.2.100\\redis.windows.conf");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    // 登录到Redis服务器
    public static void loginRedisCli(String host, int port, String password) {
        try {
            String command = "redis-cli.exe -h " + host + " -p " + port + " -a " + password;
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // 启动Redis服务器
        startRedisServer();

        // 登录到Redis服务器
        loginRedisCli("localhost", 6379, "123456");
    }
}
```

#### **实体类**

用户的实体类

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class User implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 主键
     */

    private Long id;

    /**
     * 用户名
     */
    private String userName;

    /**
     * 昵称
     */
    private String nickName;

    /**
     * 密码
     */
    private String password;

    /**
     * 用户类型：0代表普通用户，1代表管理员
     */
    private String type;

    /**
     * 账号状态（0正常 1停用）
     */
    private String status;

    /**
     * 邮箱
     */
    private String email;

    /**
     * 手机号
     */
    private String phonenumber;

    /**
     * 用户性别（0男，1女，2未知）
     */
    private String sex;

    /**
     * 头像
     */
    private String avatar;

    /**
     * 创建人的用户id
     */
    private Long createBy;

    /**
     * 创建时间
     */
    private LocalDateTime createTime;

    /**
     * 更新人
     */
    private Long updateBy;

    /**
     * 更新时间
     */
    private LocalDateTime updateTime;

    /**
     * 删除标志（0代表未删除，1代表已删除）
     */
    private Integer delFlag;
}
```

#### **项目结构**

![image-20240712093532144](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407120935280.png)



### 4.3实战

#### 1.数据库校验用户

从之前的分析我们可以知道，我们可以自定义一个UserDetailsService,让SpringSecurity使用我们的UserDetailsService。我们自己的UserDetailsService可以从数据库中查询用户名和密码。

##### **准备工作**

数据库表, 建表语句如下

```sql
CREATE TABLE `sys_user` (
  `id` bigint NOT NULL AUTO_INCREMENT COMMENT '主键',
  `user_name` varchar(64) NOT NULL DEFAULT 'NULL' COMMENT '用户名',
  `nick_name` varchar(64) NOT NULL DEFAULT 'NULL' COMMENT '昵称',
  `password` varchar(64) NOT NULL DEFAULT 'NULL' COMMENT '密码',
  `type` char(1) DEFAULT '0' COMMENT '用户类型：0代表普通用户，1代表管理员',
  `status` char(1) DEFAULT '0' COMMENT '账号状态（0正常 1停用）',
  `email` varchar(64) DEFAULT NULL COMMENT '邮箱',
  `phonenumber` varchar(32) DEFAULT NULL COMMENT '手机号',
  `sex` char(1) DEFAULT NULL COMMENT '用户性别（0男，1女，2未知）',
  `avatar` varchar(128) DEFAULT NULL COMMENT '头像',
  `create_by` bigint DEFAULT NULL COMMENT '创建人的用户id',
  `create_time` datetime DEFAULT NULL COMMENT '创建时间',
  `update_by` bigint DEFAULT NULL COMMENT '更新人',
  `update_time` datetime DEFAULT NULL COMMENT '更新时间',
  `del_flag` int DEFAULT '0' COMMENT '删除标志（0代表未删除，1代表已删除）',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=14787164048663 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='用户表'
```

##### **引入Mybatis和mysql驱动的依赖**

需要连接数据库

```xml
<!-- MyBatis Plus的Spring Boot starter，用于简化MyBatis的使用 -->
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>3.0.3</version>
</dependency>
<!-- MySQL连接器，用于连接和操作MySQL数据库 -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.29</version>
</dependency>
```

##### **配置数据库信息**

在resources下创建一个application.yml文件，配置数据库信息和开启mtbatis的驼峰命名转换：

```yml
spring:
  datasource:
    driver-class-name: com.mysql.cj.jdbc.Driver
    url: jdbc:mysql://localhost:3306/security
    username: root
    password: 1234
   
mybatis:
  configuration:
    map-underscore-to-camel-case: true
```

##### **定义Mapper接口**

创建一个mapper包，包下创建UserMapper接口，实现查询用户的方法：

```java
public interface UserMapper {
    @Select("""
                select * from sys_user
            """)
    List<User> selectUserList();

    @Select("""
                select * from sys_user where user_name = #{name}
            """)
    User selectOne(String name);
}
```

##### **配置Mapper扫描**

在启动类上开启mapper扫描：

```java
@SpringBootApplication
@MapperScan("com.zsm.token.mapper")
public class TokenApplication {
    public static void main(String[] args) {
        SpringApplication.run(TokenApplication.class, args);
    }
}
```

##### **测试mybatis是否能正常使用**

使用单元测试，需要先引入junit依赖：

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
</dependency>
```

然后创建测试类：

```java
@SpringBootTest
public class MapperTest {
    @Autowired
    private UserMapper userMapper;
    
    @Test
    public void testUerMapper() {
        List<User> users = userMapper.selectUserList();
        System.out.println(users);
    }
}
```

输出结果：

```java
[User(id=14787164048663, userName=zhangsan, nickName= 张三, password=1234, type=0, status=0, email=null, phonenumber=null, sex=null, avatar=null, createBy=null, createTime=null, updateBy=null, updateTime=null, delFlag=0)]
```

#### 2.核心代码

**分析:**

> `SpringSecurity` 默认是在内存中查找对应的用户名密码然后`UserDetailsService`的默认实现类使用封装成`UserDetai`l对象交给`DaoAuthenticationProcider`校验
>
> 但是我们在实际运用场景中是从数据库中查找用户信息	
>
> 所以此时我们需要写一个`UserDetailsService`的实现类用来在数据库中查询用户信息并且封装到`UserDetai`l对象中
>
> 并且需要写一个`UserDetai`的实现类因为用户信息不仅仅只有用户名和密码还有其他信息

##### 1.创建UserDetailsService实现类 

创建一个service.ipml包，在包下创建一个UserDetailsServiceImpl类实现UserDetailsService接口：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    @Autowired
    private UserMapper userMapper;
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        // 查询用户信息
        User user = userMapper.selectOne(username);
        if (user == null) throw new RuntimeException("用户名或密码错误");

        // todo 查询用户的权限信息

        // 把数据封装成UserDetails返回
        return new LoginUser(user);
    }
}
```

这个方法的返回值类型是一个UserDetails，这是一个接口，所以要自己实现这个接口，LoginUser就是自己写的一个实现类。

##### 2.创建UserDetail实现类

创建一个LoginUser类，实现UserDetails接口，添加一个User属性，重写接口的三个方法：

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class LoginUser implements UserDetails {
    //封装用户信息
    private User user;
    
    //获取权限
    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return null;
    }

    //获取密码
    @Override
    public String getPassword() {
        return user.getPassword();
    }

    //获取用户名
    @Override
    public String getUsername() {
        return user.getUserName();
    }
}
```

这个接口还有其他方法有了默认实现，不需要重写：

+ 账户是否未过期
+ 账户是否未锁定
+ 密码是否未过期
+ 账户是否可用

![image-20240712102652936](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121026106.png)

这个时候可以测试一下，我们只是修改了验证登录的部分，所以登录页面等操作都没有改变，启动项目，输入数据库中的用户名zhangsna和密码1234，但是没有登录成功，控制台报错：

![image-20240712103106323](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121031496.png)

> 这条信息是在提醒您，在Spring Security的上下文中，您输入了一个密码但没有使用密码编码器（PasswordEncoder）。在Spring Security中，出于安全考虑，密码在存储到数据库之前通常会被加密或编码。这是为了防止密码以明文形式存储，从而在数据库泄露时保护用户信息。
>
> 当Spring Security检测到密码没有经过编码处理时，它会发出这个警告，提示您如果确实想要以明文形式存储密码，应该使用`{noop}`前缀。`{noop}`是一个密码编码器的名称，它代表“不执行任何操作”，即密码将不会被加密或修改，直接以原样存储。

所以在数据库中这样存储密码：

![image-20240712103544949](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121035084.png)

然后重新登录访问输入1234就没问题了。

当前就实现了从数据库中查询用户。当然这种方式只用于测试，后面会被替换掉。

##### 3.密码加密存储模式更改

>实际项目中我们不会把密码明文存储在数据库中。
>
>默认使用的PasswordEncoder要求数据库中的密码格式为：{id}password 。它会根据id去判断密码的加密方式。
>
>但是我们一般不会采用这种方式。所以就需要替换PasswordEncoder。
>
>我们一般使用SpringSecurity为我们提供的BCryptPasswordEncoder。
>
>我们只需要使用把BCryptPasswordEncoder对象注入Spring容器中，SpringSecurity就会使用该PasswordEncoder来进行密码验。
>
>我们可以定义一个SpringSecurity的配置类，SpringSecurity要求这个配置类要继承WebSecurityConfigurerAdapter。
>

**创建SpringSecurity配置类**

SpringBoot3中，WebSecurityConfigurerAdapter已没有了，所以不用实现：

```JAVA
@Configuration //配置类
@EnableWebSecurity // 开启Spring Security的功能 代替了 implements WebSecurityConfigurerAdapter
public class SecurityConfig {

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
}
```

可以测试一下BCryptPasswordEncoder对象的用法：

```java
@Autowired
private PasswordEncoder passwordEncoder;

@Test
void testPasswordEncoder() {
    BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
    String encoded = passwordEncoder.encode("1234");
    System.out.println(encoded);
    boolean matches = passwordEncoder.matches("1234", encoded);
    System.out.println(matches);
}
```

+ encode("")：加密，得到加密后的密文
+ matches("", "")：校验，第一个参数是明文，第二个参数是密文，校验明文加密后时候和密文一样、

输出结果：

```java
$2a$10$0NQTWzfO6VNGWiY4NYM8POUKl5RtAf23hjK/EHWF48KfJkPMHiSiW
true
```

注意：同一个明文使用encode方法得到密文是不一样：

```java
@Autowired
private PasswordEncoder passwordEncoder;
@Test
void testPasswordEncoder() {
    BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
    String encoded = passwordEncoder.encode("1234");
    String encoded2 = passwordEncoder.encode("1234");
    System.out.println(encoded);
    System.out.println(encoded2);
}
```

结果：

```java
$2a$10$DqJJbFf909IRL6YCr0CbR.Bdhqo9x1TPkdipoEM/pEXKsT3qTAt5m
$2a$10$/oMykwei4Sij/fMKP3g7aOxqpL7zdZLDGP2fq6OP/cAgqJKde4knC
```

因为每次加密都会生成一个随机的盐（salt）值，然后根据这个盐值去加密。

加密后字符串的长度为固定的60位。其中：$是分割符，无意义；2a是bcrypt加密版本号；10是cost的值；而后的前22位是salt值；再然后的字符串就是密码的密文了。

将以上输出的密文随便复制一个放到数据库中，然后重新使用zhangsan、1234登录，可以登录成功。

##### 使用jwtUtil

在复制的jwtUtil工具类中，有一个createJWT方法，用这个方法来创建token；有一个parseJWT方法，用这个方法来解析token，解析了token就可以通过getSubject获取到原文：

```java
public static void main(String[] args) throws Exception {
    String jwt = createJWT("1234");
    Claims claims = parseJWT(jwt);
    String subject = claims.getSubject();
    System.out.println(claims);
    System.out.println(subject);
}
```

这里执行时可能会报错：

![image-20240712111121744](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121111905.png)

需要添加依赖：

```xml
<!-- JAXB API，用于XML和Java对象之间的绑定 -->
<dependency>
    <groupId>javax.xml.bind</groupId>
    <artifactId>jaxb-api</artifactId>
    <version>2.3.1</version>
</dependency>
```

输出结果：

```xml
{jti=c5adc74e90284a9aa08d3c29ce6fa437, sub=1234, iss=sg, iat=1720754021, exp=1720757621}
1234
```

##### 4.登陆接口

> 接下我们需要自定义登陆接口，然后让SpringSecurity对这个接口放行,让用户访问这个接口的时候不用登录也能访问。
>
> 在接口中我们通过AuthenticationManager的authenticate方法来进行用户认证,所以需要在SecurityConfig中配置把AuthenticationManager注入容器。
>
> 认证成功的话要生成一个jwt，放入响应中返回。并且为了让用户下回请求时能通过jwt识别出具体的是哪个用户，我们需要把用户信息存入redis，可以把用户id作为key	
>

创建登录接口，使用之前定义的统一返回格式实体类ResponseResult做返回值：

```java
@RestController
public class LoginController {

    @Autowired
    private LoginService loginService;

    @PostMapping("/login")
    public ResponseResult login(@RequestBody User user) {
        return loginService.login(user);
    }
}
```

登录service接口：

```java
public interface LoginServcie {
    ResponseResult login(User user);
}
```

接口实现类，主要要做的事：

+ 通过AuthenticationManager调用authenticate方法进行用户认证
+ 如果认证没有通过，给出提示
+ 如果认证通过，使用userid生成一个jwt，jwt存入ResponseResult中返回
+ 把完整的用户信息存入redis，userid作为key

```java
@Service
public class LoginServiceImpl implements LoginService {

    @Autowired
    AuthenticationManager authenticationManager;
    @Autowired
    RedisCache redisCache;

    @Override
    public ResponseResult login(User user) {
        // 通过AuthenticationManager调用authenticate方法进行用户认证
        // authenticate方法的参数是一个Authentication对象
        // Authentication是一个接口，需要使用他的实现类
        // 在认证验证一块，是默认将用户名和密码封装成一个Authentication对象的
        // 所以这里也将用户名和密码封装成一个Authentication的实现了UsernamePasswordAuthenticationToken对象
        Authentication token = new UsernamePasswordAuthenticationToken(user.getUserName(), user.getPassword());
        Authentication authentication = authenticationManager.authenticate(token);

        // 如果认证没有通过，给出提示
        // 如果authenticate方法返回的是null，说明认证没有通过
        if (authentication == null) throw new RuntimeException("登录失败！");

        // 如果认证通过，使用userid生成一个jwt，jwt存入ResponseResult中返回
        LoginUser loginUser = (LoginUser) authentication.getPrincipal();
        Long id = loginUser.getUser().getId();
        String jwt = JwtUtil.createJWT(id.toString());

        // 把完整的用户信息存入redis，userid作为key
        redisCache.setCacheObject("login:" + id, loginUser);

        // 把token返回给前端
        Map<String, String> map = new HashMap<>();
        map.put("token", jwt);
        return new ResponseResult(200, "登录成功", map);
    }
}
```

![image-20240712144548329](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121445548.png)

那么如何获取这个AuthenticationManager，需要注入一个对象AuthenticationConfiguration，使用该对象的getAuthenticationManager方法，返回一个AuthenticationManager对象，可以写在SecurityConfig配置类中：

```java
@Configuration //配置类
@EnableWebSecurity // 开启Spring Security的功能 代替了 implements WebSecurityConfigurerAdapter
public class SecurityConfig {
    @Autowired
    AuthenticationConfiguration authenticationConfiguration;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    public AuthenticationManager authenticationManagerBean() throws Exception {
        return authenticationConfiguration.getAuthenticationManager();
    }
}
```

然后此时想要测试的话，需要在配置类中开启放行，让用户不需要登录就能访问login这个接口：

```java
/**
     * 配置Spring Security的过滤链。
     *
     * @param http 用于构建安全配置的HttpSecurity对象。
     * @return 返回配置好的SecurityFilterChain对象。
     * @throws Exception 如果配置过程中发生错误，则抛出异常。
     */
@Bean
SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    http
        // 禁用CSRF保护
        .csrf(csrf -> csrf.disable())
        // 设置会话创建策略为无状态
        .sessionManagement(session -> session.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
        // 配置授权规则                 指定user/login路径.允许匿名访问(未登录可访问已登陆不能访问). 其他路径需要身份认证
        .authorizeHttpRequests(auth -> auth.requestMatchers("/user/login").anonymous().anyRequest().authenticated());
    // 构建并返回安全过滤链
    return http.build();
}
```

**测试**

使用apifox发送请求：

![image-20240712153325367](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121533600.png)

此时会报错：

![image-20240712154534603](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121545788.png)

观察报错上面的信息：

![image-20240712154617547](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121546731.png)

是没有启动redis，连接不到redis，所以启动redis：

![image-20240712154739834](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121547060.png)

重新发送请求，查看返回的结果：

![image-20240712154811149](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121548337.png)

说明此时登录接口已经完成了。

可以在程序中使用断点，查看用户id放在哪的：

![image-20240712153540396](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121535620.png)

##### 5.认证过滤器

> 我们需要自定义一个过滤器，这个过滤器会去获取请求头中的token，对token进行解析取出其中的userid。(主要作用于除登录外的请求)
>
> 使用userid去redis中获取对应的LoginUser对象。
>
> 然后封装Authentication对象存入SecurityContextHolder

创建一个filter包，包下创建一个JwtAuthenticationTokenFilter类，继承自OncePerRequestFilter，因为默认的Filter接口可能会导致一个请求调用多次过滤器，继承OncePerRequestFilter可以保证过滤器一次请求只会被执行一次。

OncePerRequestFilter特点是在处理单个HTTP请求时确保过滤器的 doFilterInternal 方法只被调用一次：

```java
@Component
public class JwtAuthenticationTokenFilter extends OncePerRequestFilter {
    @Autowired
    private RedisCache redisCache;
    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws ServletException, IOException {
        // 获取token（要求前端必须在请求头中携带啊token）
        String token = request.getHeader("token");

        // 如果没有token
        if (!StringUtils.hasText(token)) {
            // 放行，因为接下来的操作是解析token，没有token就不需要解析了，直接放行，让后面的过滤器去拦截
            filterChain.doFilter(request, response);
            // 后面响应给前端时会走到这里，所以这里可以直接返回
            return;
        }

        // 解析token
        Claims claims = null;
        String userid = null;  // 获取用于生成token的userid
        try {
            claims = JwtUtil.parseJWT(token);
            userid = claims.getSubject();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        // 从redis中获取用户信息，注意：redis中的key是login：+userId
        String key = "login:" + userid;
        LoginUser loginUser = (LoginUser) redisCache.getCacheObject(key);
        if (loginUser == null) throw new RuntimeException("用户未登录");

        // 存入SecurityContextHolder
        // todo 获取权限信息封装到Authentication中
        // 参数（用户信息，？，权限信息）
        Authentication authentication = new UsernamePasswordAuthenticationToken(loginUser, null, null);
        SecurityContextHolder.getContext().setAuthentication(authentication);

        // 放行
        filterChain.doFilter(request, response);
    }
}
```

**把token校验过滤器添加到过滤器链中**

在SecurityConfig配置类中，在securityFilterChain方法中的http对象上添加过滤器，将jwtAuthenticationTokenFilter过滤器添加到UsernamePasswordAuthenticationFilter之前，需要注入JwtAuthenticationTokenFilter对象：

```java
@Autowired
JwtAuthenticationTokenFilter jwtAuthenticationTokenFilter;
@Bean
SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    http
        // 禁用CSRF保护
        .csrf(csrf -> csrf.disable())
        // 设置会话创建策略为无状态
        .sessionManagement(session -> session.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
        // 配置授权规则                 指定user/login路径.允许匿名访问(未登录可访问已登陆不能访问). 其他路径需要身份认证
        .authorizeHttpRequests(auth -> auth.requestMatchers("/user/login").anonymous().anyRequest().authenticated());

    // 将jwtAuthenticationTokenFilter过滤器添加到UsernamePasswordAuthenticationFilter之前
    http.addFilterBefore(jwtAuthenticationTokenFilter, UsernamePasswordAuthenticationFilter.class);

    // 构建并返回安全过滤链
    return http.build();
}
```

此时可以测试一下，重新发送一遍/user/login的请求，获取到token，然后向/hello发送请求，在请求头上带上token，可以正常访问：

![image-20240712162613570](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121626762.png)

如果不带token访问，会是403：

![image-20240712162817694](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121628886.png)

##### 6.退出登录

我们只需要定义一个退出登陆接口，然后获取SecurityContextHolder中的认证信息，删除redis中对应的数据即可。

在LoginController中添加一个控制器方法：

```java
@RequestMapping("/user/logout")
public ResponseResult logout() {
    return loginService.logout();
}
```

定义接口：

```java
ResponseResult logout();
```

实现接口：

```java
@Override
public ResponseResult logout() {
    // 获取用户id
    Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
    LoginUser loginUser = (LoginUser) authentication.getPrincipal();
    Long id = loginUser.getUser().getId();

    // 删除redis中的数据
    redisCache.deleteObject("login:" + id);

    return new ResponseResult(200, "注销成功");
}
```

测试：

带着token访问logout的接口：

![image-20240712165459892](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407121655141.png)

然后再去访问hello接口就会报错403。

有个问题：注销成功后，该token没有失效，如果此时重新登录了，再用这个原先的token去访问登出接口，依旧会将当前登录状态注销。

##### 7.自定义失败处理器

> 我们还希望在认证失败或者是授权失败的情况下也能和我们的接口一样返回相同结构的json，这样可以让前端能对响应进行统一的处理。要实现这个功能我们需要知道SpringSecurity的异常处理机制。
>
> 在SpringSecurity中，如果我们在认证或者授权的过程中出现了异常会被ExceptionTranslationFilter捕获到。在ExceptionTranslationFilter中会去判断是认证失败还是授权失败出现的异常。
>
> 如果是认证过程中出现的异常会被封装成AuthenticationException然后调用**AuthenticationEntryPoint**对象的方法去进行异常处理。
>
> 如果是授权过程中出现的异常会被封装成AccessDeniedException然后调用**AccessDeniedHandler**对象的方法去进行异常处理。
>
> 所以如果我们需要自定义异常处理，我们只需要自定义AuthenticationEntryPoint和AccessDeniedHandler然后配置SpringSecurity即可。

创建一个handler包，包下创建一个AuthenticationEntryPoint的实现类：

```java
@Component
public class AuthenticationEntryPointImpl implements AuthenticationEntryPoint {
    @Override
    public void commence(HttpServletRequest request, HttpServletResponse response, AuthenticationException authException) throws IOException, ServletException {
        // 设置需要响应回去的数据
        ResponseResult responseResult = new ResponseResult(HttpStatus.UNAUTHORIZED.value(), "认证失败请重新登录");
        // 转为json
        String json = JSON.toJSONString(responseResult);
        // 设置响应
        WebUtils.renderString(response, json);
    }
}
```

+ WebUtils是一个自定义的工具类，renderString方法：

  ```java
  public static String renderString(HttpServletResponse response, String
                                    string) {
      try {
          response.setStatus(200);
          response.setContentType("application/json");
          response.setCharacterEncoding("utf-8");
          response.getWriter().print(string);
      } catch (IOException e) {
          e.printStackTrace();
      }
      return null;
  }
  ```

再创建一个AccessDeniedHandlerImpl类：

```java
@Component
public class AccessDeniedHandlerImpl implements AccessDeniedHandler {
    @Override
    public void handle(HttpServletRequest request, HttpServletResponse response, AccessDeniedException accessDeniedException) throws IOException, ServletException {
        // 设置需要响应回去的数据
        ResponseResult responseResult = new ResponseResult(HttpStatus.FORBIDDEN.value(), "权限不足");
        // 转为json
        String json = JSON.toJSONString(responseResult);
        // 设置响应
        WebUtils.renderString(response, json);
    }
}
```

**修改配置类**

然后需要将以上两个类配置给SpringSecurity：

```java
@Configuration //配置类
@EnableWebSecurity // 开启Spring Security的功能 代替了 implements WebSecurityConfigurerAdapter
@EnableMethodSecurity
public class SecurityConfig {

    @Autowired
    AuthenticationConfiguration authenticationConfiguration;
    @Autowired
    JwtAuthenticationTokenFilter jwtAuthenticationTokenFilter;
    @Autowired
    AuthenticationEntryPointImpl authenticationEntryPoint;
    @Autowired
    AccessDeniedHandlerImpl accessDeniedHandler;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    public AuthenticationManager authenticationManagerBean() throws Exception {
        return authenticationConfiguration.getAuthenticationManager();
    }

    /**
     * 配置Spring Security的过滤链。
     *
     * @param http 用于构建安全配置的HttpSecurity对象。
     * @return 返回配置好的SecurityFilterChain对象。
     * @throws Exception 如果配置过程中发生错误，则抛出异常。
     */
    @Bean
    SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
                // 禁用CSRF保护
                .csrf(csrf -> csrf.disable())
                // 设置会话创建策略为无状态
                .sessionManagement(session -> session.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
                // 配置授权规则                 指定user/login路径.允许匿名访问(未登录可访问已登陆不能访问). 其他路径需要身份认证
                .authorizeHttpRequests(auth -> auth.requestMatchers("/user/login").anonymous().anyRequest().authenticated());

        // 将jwtAuthenticationTokenFilter过滤器添加到UsernamePasswordAuthenticationFilter之前
        http.addFilterBefore(jwtAuthenticationTokenFilter, UsernamePasswordAuthenticationFilter.class);

        // 配置异常处理器
        http.exceptionHandling(exception -> exception
                               .accessDeniedHandler(accessDeniedHandler)
                               .authenticationEntryPoint(authenticationEntryPoint));

        // 构建并返回安全过滤链
        return http.build();
    }
}
```

**测试**

认证失败：只需要用户名或密码错误：

![image-20240713125236551](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131252742.png)

鉴权失败：将hello接口上的权限字符串改掉：

![image-20240713125339999](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131253151.png)

## 5.授权

#### 5.1 权限系统的作用

> 例如一个学校图书馆的管理系统，如果是普通学生登录就能看到借书还书相关的功能，不可能让他看到并且去使用添加书籍信息，删除书籍信息等功能。但是如果是一个图书馆管理员的账号登录了，应该就能看到并使用添加书籍信息，删除书籍信息等功能。
>
> 总结起来就是**不同的用户可以使用不同的功能**。这就是权限系统要去实现的效果。
>
> 我们不能只依赖前端去判断用户的权限来选择显示哪些菜单哪些按钮。因为如果只是这样，如果有人知道了对应功能的接口地址就可以不通过前端，直接去发送请求来实现相关功能操作。
>
> 所以我们还需要在后台进行用户权限的判断，判断当前用户是否有相应的权限，必须具有所需权限才能进行相应的操作。
>

#### 5.2授权基本流程

> 在SpringSecurity中，会使用默认的FilterSecurityInterceptor来进行权限校验。在FilterSecurityInterceptor中会从SecurityContextHolder获取其中的Authentication，然后获取其中的权限信息。当前用户是否拥有访问当前资源所需的权限。
>
> 所以我们在项目中只需要把当前登录用户的权限信息也存入Authentication。
>
> 然后设置我们的资源所需要的权限即可。

#### 5.3 授权基本实现

##### 1.限制访问资源所需权限

SpringSecurity为我们提供了基于注解的权限控制方案，这也是我们项目中主要采用的方式。我们可以使用注解去指定访问对应的资源所需的权限。

但是要使用它我们需要先开启相关配置。在SpringSecurity的配置类SecurityConfig上添加注解：

```java
@EnableMethodSecurity
```

然后就可以使用对应的注解：@PreAuthorize。

比如在hello接口上使用：

```java
@RequestMapping("hello")
@PreAuthorize("hasAuthority('user')")
public String hello(){
    return "hello world";
}
```

在@PreAuthorize()中写的表达式其实是一个方法调用，hasAuthority的返回值是一个boolean，如果是true，则可以访问，如果是false，则不能访问：

```java
public final boolean hasAuthority(String authority) {
    return this.hasAnyAuthority(authority);
}
```

hasAuthority这个方法回去判断用户是否有“user”这个权限，如果有则返回true，没有则返回false。

所以其实权限就是一个字符串。

##### 2.封装权限信息

我们前面在写UserDetailsServiceImpl的时候说过，在查询出用户后还要获取对应的权限信息，封装到UserDetails中返回:

```java
@Override
public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
    // 查询用户信息
    User user = userMapper.selectOne(username);
    if (user == null) throw new RuntimeException("用户名或密码错误");

    // todo 查询用户的权限信息

    // 把数据封装成UserDetails返回
    return new LoginUser(user);
}
```

我们先直接把权限信息写死封装到UserDetails中进行测试：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    @Autowired
    private UserMapper userMapper;
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        // 查询用户信息
        User user = userMapper.selectOne(username);
        if (user == null) throw new RuntimeException("用户名或密码错误");

        // todo 查询用户的权限信息
        // 两个权限：user和test
        List<String> list = Arrays.asList("user", "test");
        // 把数据封装成UserDetails返回
        return new LoginUser(user, list);
    }
}
```

我们之前定义了UserDetails的实现类LoginUser，想要让其能封装权限信息就要对其进行修改，添加一个List<String>属性，同时，还要重写getAuthorities这个方法，这个方法是框架会调用来获取权限的。

那这个方法的返回值是一个集合，集合中的类型是GrantedAuthority，这是一个，他有三个实现类：

![image-20240712222218085](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407122222878.png)

我们可以选择创建这个SimpleGrantedAuthority对象，他有一个简单的构造方法：

![image-20240712222419076](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407122224160.png)

所以在LoginUser类中，可以将List<String>中的String封装成一个SimpleGrantedAuthority：

```java
@Data
@AllArgsConstructor
@NoArgsConstructor
public class LoginUser implements UserDetails {
    private User user;
    private List<String> permissions;

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        // 普通写法
//        List<GrantedAuthority> authorities = new ArrayList<>();
//        SimpleGrantedAuthority simpleGrantedAuthority = null;
//        for (String s : permissions) {
//            simpleGrantedAuthority = new SimpleGrantedAuthority(s);
//            authorities.add(simpleGrantedAuthority);
//        }

        // 流写法
        List<SimpleGrantedAuthority> authorities = permissions.stream()
            .map(SimpleGrantedAuthority::new)
            .collect(Collectors.toList());

        return authorities;
    }

    @Override
    public String getPassword() {
        return user.getPassword();
    }

    @Override
    public String getUsername() {
        return user.getUserName();
    }
}
```

以上代码还可以优化下，不需要每次都将权限转为List集合，将authorities变量定义为成员变量，且每次判断当前authorities是否为空，不是则直接返回，是则执行操作：

```java
private List<SimpleGrantedAuthority> authorities;

@Override
public Collection<? extends GrantedAuthority> getAuthorities() {
    if (authorities != null) return authorities;

    // 普通写法
    //        List<GrantedAuthority> authorities = new ArrayList<>();
    //        SimpleGrantedAuthority simpleGrantedAuthority = null;
    //        for (String s : permissions) {
    //            simpleGrantedAuthority = new SimpleGrantedAuthority(s);
    //            authorities.add(simpleGrantedAuthority);
    //        }

    // 流写法
    authorities = permissions.stream().map(SimpleGrantedAuthority::new).collect(Collectors.toList());

    return authorities;
}
```

还有一个问题是，到时会把LoginUser存到redis中，但是redis默认不会把SimpleGrantedAuthority类型就行序列化，会出现异常，所以我们不需要将authorities这个集合序列化，只将permissions序列化就可，到时将permissions反序列化后，还可以得到authorities，所以给authorities添加一个注解，表示他不被序列化到redis中：

```java
@JSONField(serialize = false)
private List<SimpleGrantedAuthority> authorities;
```

LoginUser修改完后，在JwtAuthenticationTokenFilter中的doFilterInternal方法中，就要获取权限信息封装到Authentication中：

```java
@Component
public class JwtAuthenticationTokenFilter extends OncePerRequestFilter {
    @Autowired
    private RedisCache redisCache;
    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain) throws ServletException, IOException {
        // 获取token（要求前端必须在请求头中携带啊token）
        String token = request.getHeader("token");

        // 如果没有token
        if (!StringUtils.hasText(token)) {
            // 放行，因为接下来的操作是解析token，没有token就不需要解析了，直接放行，让后面的过滤器去拦截
            filterChain.doFilter(request, response);
            // 后面响应给前端时会走到这里，所以这里可以直接返回
            return;
        }

        // 解析token
        Claims claims = null;
        String userid = null;  // 获取用于生成token的userid
        try {
            claims = JwtUtil.parseJWT(token);
            userid = claims.getSubject();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        // 从redis中获取用户信息，注意：redis中的key是login：+userId
        String key = "login:" + userid;
        LoginUser loginUser = (LoginUser) redisCache.getCacheObject(key);
        if (loginUser == null) throw new RuntimeException("用户未登录");

        // 存入SecurityContextHolder
        // todo 获取权限信息封装到Authentication中
        // 参数（用户信息，？，权限信息）
        Authentication authentication = 
            new UsernamePasswordAuthenticationToken(loginUser, null, loginUser.getAuthorities());
        SecurityContextHolder.getContext().setAuthentication(authentication);

        // 放行
        filterChain.doFilter(request, response);
    }
}
```

**测试**

重新登录，获取到这个token，访问hello接口，在JwtAuthenticationTokenFilter类中可以打断点查看当前登录用户的权限：

![image-20240712225540778](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407122255938.png)

hello接口的权限字符串是user，所以鉴权可以成功，能够正常访问。

如果将hello接口上的权限改为admin：

```java
@RestController
public class HelloController {
    @RequestMapping("/hello")
    @PreAuthorize("hasAuthority('admin')")
    public String hello() {
        return "hello";
    }
}
```

那么此时再用user和test的权限去访问hello接口，就会访问失败：

![image-20240712230110038](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407122301175.png)

#### 5.4从数据库查询权限信息

##### 1.RBAC权限模型

RBAC权限模型（Role-Based Access Control）即：基于角色的权限控制。这是目前最常被开发者使用也是相对易用、通用权限模型。

![image-20240713091845800](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130918954.png)

在一个系统中，用户和权限都可能有很多个，一个用户可以对应多个权限，但是就这样写的话，给每个用户设置权限的时候就很麻烦，所以需要在用户注册的时候一次性就给他配置一组权限，所以有了角色的概念：

![image-20240713092104129](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130921242.png)

可以理解一个角色就是一个权限组。一个角色可以对应多个权限，一个权限也可以被多个角色所有，所以他们是多对多的关系，需要一张中间表来关联：

![image-20240713092349004](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130923101.png)

而用户和角色之间也是多对多的关系，需要一张中间表：

![image-20240713092520050](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130925144.png)

#####  2.准备工作

建表：

```sql
CREATE TABLE `sys_menu` (
  `id` bigint NOT NULL AUTO_INCREMENT COMMENT '菜单ID',
  `menu_name` varchar(50) NOT NULL COMMENT '菜单名称',
  `parent_id` bigint DEFAULT '0' COMMENT '父菜单ID',
  `order_num` int DEFAULT '0' COMMENT '显示顺序',
  `path` varchar(200) DEFAULT '' COMMENT '路由地址',
  `component` varchar(255) DEFAULT NULL COMMENT '组件路径',
  `is_frame` int DEFAULT '1' COMMENT '是否为外链（0是 1否）',
  `menu_type` char(1) DEFAULT '' COMMENT '菜单类型（M目录 C菜单 F按钮）',
  `visible` char(1) DEFAULT '0' COMMENT '菜单状态（0显示 1隐藏）',
  `status` char(1) DEFAULT '0' COMMENT '菜单状态（0正常 1停用）',
  `perms` varchar(100) DEFAULT NULL COMMENT '权限标识',
  `icon` varchar(100) DEFAULT '#' COMMENT '菜单图标',
  `create_by` bigint DEFAULT NULL COMMENT '创建者',
  `create_time` datetime DEFAULT NULL COMMENT '创建时间',
  `update_by` bigint DEFAULT NULL COMMENT '更新者',
  `update_time` datetime DEFAULT NULL COMMENT '更新时间',
  `remark` varchar(500) DEFAULT '' COMMENT '备注',
  `del_flag` char(1) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2034 DEFAULT CHARSET=utf8mb3 COMMENT='菜单权限表'

CREATE TABLE `sys_role` (
  `id` bigint NOT NULL AUTO_INCREMENT COMMENT '角色ID',
  `role_name` varchar(30) NOT NULL COMMENT '角色名称',
  `role_key` varchar(100) NOT NULL COMMENT '角色权限字符串',
  `role_sort` int NOT NULL COMMENT '显示顺序',
  `status` char(1) NOT NULL COMMENT '角色状态（0正常 1停用）',
  `del_flag` char(1) DEFAULT '0' COMMENT '删除标志（0代表存在 1代表删除）',
  `create_by` bigint DEFAULT NULL COMMENT '创建者',
  `create_time` datetime DEFAULT NULL COMMENT '创建时间',
  `update_by` bigint DEFAULT NULL COMMENT '更新者',
  `update_time` datetime DEFAULT NULL COMMENT '更新时间',
  `remark` varchar(500) DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb3 COMMENT='角色信息表'

CREATE TABLE `sys_role_menu` (
  `role_id` bigint NOT NULL COMMENT '角色ID',
  `menu_id` bigint NOT NULL COMMENT '菜单ID',
  PRIMARY KEY (`role_id`,`menu_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COMMENT='角色和菜单关联表'

CREATE TABLE `sys_user_role` (
  `user_id` bigint NOT NULL COMMENT '用户ID',
  `role_id` bigint NOT NULL COMMENT '角色ID',
  PRIMARY KEY (`user_id`,`role_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COMMENT='用户和角色关联表'
```

表的数据：

sys_menu：

![image-20240713093705403](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130937501.png)

sys_role：

![image-20240713093729303](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130937400.png)

sys_user_role：

![image-20240713093749902](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130937996.png)

sys_role_menu：

![image-20240713093807638](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130938732.png)

先测试以下sql语句：

```sql
select distinct sm.perms
from sys_user_role sur
         left join sys_role sr on sur.role_id = sr.id
         left join sys_role_menu srm on sur.role_id = srm.role_id
         left join sys_menu sm on srm.menu_id = sm.id
where sur.user_id = 1
  and sr.status = 0
  and sm.status = 0
```

![image-20240713095652606](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407130956738.png)

创建一个跟menu表对应的实体类：

```java
@Data
@EqualsAndHashCode(callSuper = false)
@Accessors(chain = true)
public class Menu implements Serializable {

    private static final long serialVersionUID = 1L;

    /**
     * 菜单ID
     */
    private Long id;

    /**
     * 菜单名称
     */
    private String menuName;

    /**
     * 父菜单ID
     */
    private Long parentId;

    /**
     * 显示顺序
     */
    private Integer orderNum;

    /**
     * 路由地址
     */
    private String path;

    /**
     * 组件路径
     */
    private String component;

    /**
     * 是否为外链（0是 1否）
     */
    private Integer isFrame;

    /**
     * 菜单类型（M目录 C菜单 F按钮）
     */
    private String menuType;

    /**
     * 菜单状态（0显示 1隐藏）
     */
    private String visible;

    /**
     * 菜单状态（0正常 1停用）
     */
    private String status;

    /**
     * 权限标识
     */
    private String perms;

    /**
     * 菜单图标
     */
    private String icon;

    /**
     * 创建者
     */
    private Long createBy;

    /**
     * 创建时间
     */
    private LocalDateTime createTime;

    /**
     * 更新者
     */
    private Long updateBy;

    /**
     * 更新时间
     */
    private LocalDateTime updateTime;

    /**
     * 备注
     */
    private String remark;

    private String delFlag;
}
```

+ `@EqualsAndHashCode(callSuper = false)`：是Lombok的注解，用于生成`equals`和`hashCode`方法。`callSuper = false`表示不调用父类的`equals`和`hashCode`方法。
+ `@Accessors(chain = true)`：这是Lombok的注解，允许你使用链式调用设置属性。例如，可以用`menu.setId(1).setName("menuName")`这样的方式来设置属性。

##### 3.代码实现

主要要实现的就是从数据库中查询权限信息，封装到LoginUser当中，所以要新建一个mapper接口：

com.zsm.token.mapper下的MenuMapper：

```java
public interface MenuMapper {
    @Select("""
            select distinct sm.perms
            from sys_user_role sur
                     left join sys_role sr on sur.role_id = sr.id
                     left join sys_role_menu srm on sur.role_id = srm.role_id
                     left join sys_menu sm on srm.menu_id = sm.id
            where sur.user_id = #{id}
              and sr.status = 0
              and sm.status = 0
            """)
    List<String> selectPermsByUserId (Long userId);
}
```

然后我们可以在UserDetailsServiceImpl中去调用该mapper的方法查询权限信息封装到LoginUser对象中即可：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    @Autowired
    private UserMapper userMapper;
    
    @Autowired
    private MenuMapper menuMapper;
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        // 查询用户信息
        User user = userMapper.selectOne(username);
        if (user == null) throw new RuntimeException("用户名或密码错误");

        // todo 查询用户的权限信息
        // 两个权限：user和test
//        List<String> list = Arrays.asList("user", "test");
        List<String> list = menuMapper.selectPermsByUserId(user.getId());
        // 把数据封装成UserDetails返回
        return new LoginUser(user, list, null);
    }
}
```

**注意**:cookie:此处需要注意修改HelloController中的权限 之前写的是@PreAuthorize("hasAuthority('user')") 要改为数据库中对应有的权限

```java
@RestController
public class HelloController {
    @RequestMapping("/hello")
    @PreAuthorize("hasAuthority('system:dept:list')")
    public String hello() {
        return "hello";
    }
}
```

然后重启项目，重新登录，重新访问。

## 6.跨域

浏览器出于安全的考虑，使用 XMLHttpRequest对象发起 HTTP请求时必须遵守同源策略，否则就是跨域的HTTP请求，

默认情况下是被禁止的。 同源策略要求源相同才能正常进行通信，即协议、域名、端口号都完全一致。

前后端分离项目，前端项目和后端项目一般都不是同源的，所以肯定会存在跨域请求的问题。比如用ajax访问登录接口：

```html
<script>
    var raw = JSON.stringify({
        userName: "zhangsan",
        password: "1234",
    });
    $.ajax({
        url: "http://localhost:8080/user/login",
        type: "post",
        contentType: "application/json",
        data: raw,
        success(resp) {
            console.log(resp);
        },
        error(resp) {
            console.log(resp);
        },
    });
</script>
```

+ 用表单直接访问好像不会跨域

  ```html
  <form action="http://localhost:8080/user/login" method="post">
      用户名：<input type="text" name="userName" />
      <br />
      密码：<input type="text" name="password" />
      <br />
      <input type="submit" name="" value="登录" />
  </form> 
  ```

![image-20240713131520601](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131315795.png)

所以我们就要处理一下，让前端能进行跨域请求。

先对SpringBoot配置，允许跨域请求：

创建一个配置类：

```java
@Configuration
public class CorsConfig implements WebMvcConfigurer {
    @Override
    public void addCorsMappings(CorsRegistry registry) {

        registry.addMapping("/**")
                // 设置允许跨域请求的域名
                .allowedOriginPatterns("*")
                // 是否允许cookie
                .allowCredentials(true)
                // 设置允许的请求方式
                .allowedMethods("GET", "POST", "DELETE", "PUT")
                // 设置允许的header属性
                .allowedHeaders("*")
                // 跨域允许时间
                .maxAge(3600);
    }
}
```

开启SpringSecurity的跨域访问

由于我们的资源都会收到SpringSecurity的保护，所以想要跨域访问还要让SpringSecurity运行跨域访问。

```java
@Bean
SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    http
        // 禁用CSRF保护
        .csrf(csrf -> csrf.disable())
        // 设置会话创建策略为无状态
        .sessionManagement(session -> session.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
        // 配置授权规则                 指定user/login路径.允许匿名访问(未登录可访问已登陆不能访问). 其他路径需要身份认证
        .authorizeHttpRequests(auth -> auth
                               .requestMatchers("/user/login")
                               .anonymous()
                               .anyRequest()
                               .authenticated());

    // 将jwtAuthenticationTokenFilter过滤器添加到UsernamePasswordAuthenticationFilter之前
    http.addFilterBefore(jwtAuthenticationTokenFilter, UsernamePasswordAuthenticationFilter.class);

    // 配置异常处理器
    http.exceptionHandling(exception -> exception
                           .accessDeniedHandler(accessDeniedHandler)
                           .authenticationEntryPoint(authenticationEntryPoint));

    // 允许跨域
    http.cors();

    // 构建并返回安全过滤链
    return http.build();
}
```

![image-20240713132402213](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131324391.png)

目前测试出，如果SpringSecurity没有设置跨域的话，也可以访问。

## 7.遗留小问题
### 其它权限校验方法

> 我们前面都是使用@PreAuthorize注解，然后在在其中使用的是hasAuthority方法进行校验。
>
> SpringSecurity还为我们提供了其它方法例如：hasAnyAuthority，hasRole，hasAnyRole等。
>
> 这里我们先不急着去介绍这些方法，我们先去理解hasAuthority的原理，然后再去学习其他方法你就更容易理解，而不是死记硬背区别。并且我们也可以选择定义校验方法，实现我们自己的校验逻辑。
>
> hasAuthority方法实际是执行到了SecurityExpressionRoot的hasAuthority，大家只要断点调试既可知道它内部的校验原理。
>
> 它内部其实是调用authentication的getAuthorities方法获取用户的权限列表。然后判断我们存入的方法参数数据在权限列表中。
>

进入hasAuthority方法中：

```java
public final boolean hasAuthority(String authority) {
    return this.hasAnyAuthority(authority);
}
```

再进入其中的hasAnyAuthority方法中：

```java
public final boolean hasAnyAuthority(String... authorities) {
    return this.hasAnyAuthorityName((String)null, authorities);
}
```

再进入其中的hasAnyAuthorityName方法中：

```java
private boolean hasAnyAuthorityName(String prefix, String... roles) {
    Set<String> roleSet = this.getAuthoritySet();
    String[] var4 = roles;
    int var5 = roles.length;

    for(int var6 = 0; var6 < var5; ++var6) {
        String role = var4[var6];
        String defaultedRole = getRoleWithDefaultPrefix(prefix, role);
        if (roleSet.contains(defaultedRole)) {
            return true;
        }
    }

    return false;
}
```

这三个方法都在一个类中。那么在上面这个方法中，有getAuthoritySet方法，顾名思义是获取权限列表的，进去：

```java
private Set<String> getAuthoritySet() {
    if (this.roles == null) {
        Collection<? extends GrantedAuthority> userAuthorities = this.getAuthentication().getAuthorities();
        if (this.roleHierarchy != null) {
            userAuthorities = this.roleHierarchy.getReachableGrantedAuthorities(userAuthorities);
        }

        this.roles = AuthorityUtils.authorityListToSet(userAuthorities);
    }

    return this.roles;
}
```

这个getAuthentication方法返回的就是我们在JwtAuthenticationTokenFilter中存入的authentication：

![image-20240713133859589](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131338736.png)

![image-20240713133804489](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131338663.png)

最终返回的是一个字符串集合，里面放的就是权限字符串。然后返回到hasAnyAuthorityName方法中，开始进行集合的遍历，遍历用户有的权限列表是否和接口上定义的权限有相同的：

![image-20240713134255085](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131342235.png)

其中这个getRoleWithDefaultPrefix方法，进行了字符串拼接，将前缀和权限拼接。

除了hasAuthority方法，还有其他的方法。 

hasAnyAuthority方法可以传入多个权限，只要用户有其中任意一个权限都可以访问对应资源。

```java
@PreAuthorize("hasAnyAuthority('admin','test','system:dept:list')")
public String hello(){
      return "hello";
}
```

hasRole要求有对应的角色才可以访问，但是它内部会把我们传入的参数拼接上 **ROLE_** 后再去比较。所以这种情况下要用用户对应的权限也要有 **ROLE_** 这个前缀才可以。

```java
@PreAuthorize("hasRole('system:dept:list')")
public String hello(){
    return "hello";
}
```

hasAnyRole 有任意的角色就可以访问。它内部也会把我们传入的参数拼接上 **ROLE_** 后再去比较。所以这种情况下要用用户对应的权限也要有 **ROLE_** 这个前缀才可以。

```java
@PreAuthorize("hasAnyRole('admin','system:dept:list')")
public String hello(){
    return "hello";
}
```

### 自定义权限校验方法

我们也可以定义自己的权限校验方法，在@PreAuthorize注解中使用我们的方法。

先定义一个自己的类和方法，写法参照源码：

```java
@Component("ex")
public class ZSMExpressionRoot {
    public boolean hasAuthority(String authority) {
        // 获取当前用的权限
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        LoginUser loginUser = (LoginUser) authentication.getPrincipal();
        List<String> permissions = loginUser.getPermissions();
        // 判断用户权限中是否包含authority
        return permissions.contains(authority);
    }
}
```

+ 给bean取一个名字叫ex

那么接下来就是如何让框架能够调用我自己写的hasAuthority方法，可以在SPEL表达式中使用 @ex相当于获取容器中bean的名字为ex的对象。然后再调用这个对象的hasAuthority方法

```java
@RequestMapping("/hello")
@PreAuthorize("@ex.hasAuthority('system:dept:list')")
public String hello(){
    return "hello";
}
```

### 基于配置的权限控制

我们也可以在配置类中使用使用配置的方式对资源进行权限控制。

```java
@Bean
SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    http
        // 禁用CSRF保护
        .csrf(csrf -> csrf.disable())
        // 设置会话创建策略为无状态
        .sessionManagement(session -> session.sessionCreationPolicy(SessionCreationPolicy.STATELESS))
        // 配置授权规则                 指定user/login路径.允许匿名访问(未登录可访问已登陆不能访问). 其他路径需要身份认证
        .authorizeHttpRequests(auth -> auth
                               // 登录接口允许匿名访问
                               .requestMatchers("/user/login").anonymous()
                               // hello接口需要system:dept:list权限
                               .requestMatchers("/hello").hasAuthority("system:dept:list")
                               // 除上面外的所有请求全部需要鉴权认证
                               .anyRequest()
                               .authenticated()
                              );

    // 将jwtAuthenticationTokenFilter过滤器添加到UsernamePasswordAuthenticationFilter之前
    http.addFilterBefore(jwtAuthenticationTokenFilter, UsernamePasswordAuthenticationFilter.class);

    // 配置异常处理器
    http.exceptionHandling(exception -> exception
                           .accessDeniedHandler(accessDeniedHandler)
                           .authenticationEntryPoint(authenticationEntryPoint));

    // 允许跨域
    http.cors();

    // 构建并返回安全过滤链
    return http.build();
}
```

### CSRF

CSRF是指跨站请求伪造（Cross-site request forgery），是web常见的攻击之一。

https://blog.csdn.net/freeking101/article/details/86537087

SpringSecurity去防止CSRF攻击的方式就是通过csrf_token。后端会生成一个csrf_token，前端发起请求的时候需要携带这个csrf_token,后端会有过滤器进行校验，如果没有携带或者是伪造的就不允许访问。

我们可以发现CSRF攻击依靠的是cookie中所携带的认证信息。但是在前后端分离的项目中我们的认证信息其实是token，而token并不是存储中cookie中，并且需要前端代码去把token设置到请求头中才可以，所以CSRF攻击也就不用担心了。

### 认证成功处理器

实际上在UsernamePasswordAuthenticationFilter进行登录认证的时候,如果登录成功了是会调用AuthenticationSuccessHandler的方法进行认证成功后的处理的。AuthenticationSuccessHandler就是 登录成功处理器。

我们也可以自己去自定义成功处理器进行成功后的相应处理。

使用第一次创建的start项目，先创建一个类实现AuthenticationSuccessHandler接口：

```java
@Component
public class ZSMAuthenticationSuccessHandler implements AuthenticationSuccessHandler {
    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        System.out.println("认证成了！");
    }
}
```

然后配置SpringSecurity，让登录成功后调用这个类：

```java
@EnableWebSecurity
@Configuration
public class SecurityConfig {

    @Autowired
    private ZSMAuthenticationSuccessHandler zsmAuthenticationSuccessHandler;

    @Bean
    SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        // 启用登录成功后操作
        http.formLogin().successHandler(zsmAuthenticationSuccessHandler);
        // 设置所有接口需要验证
        http.authorizeHttpRequests().anyRequest().authenticated();
        return http.build();
    }
}
```

启动项目，访问hello接口，登录成功后查看控制台：

![image-20240713145303986](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131453166.png)

### 认证失败处理器

实际上在UsernamePasswordAuthenticationfiter进行登录认证的时候，如果认证失败了是会调用AuthenticationFailureHandler的方法进行认证失败后的处理的。AuthenticationFailureHandler就是登录失败处理器。

我们也可以自己去自定义失败处理器进行失败后的相应处理。和认证成功处理器的使用一样。

```java
@Component
public class ZSMAuthenticationFailureHandler implements AuthenticationFailureHandler {
    @Override
    public void onAuthenticationFailure(HttpServletRequest request, HttpServletResponse response, AuthenticationException exception) throws IOException, ServletException {
        System.out.println("认证失败了！");
    }
}
```

```java
@EnableWebSecurity
@Configuration
public class SecurityConfig {

    @Autowired
    private ZSMAuthenticationSuccessHandler zsmAuthenticationSuccessHandler;
    @Autowired
    private ZSMAuthenticationFailureHandler zsmAuthenticationFailureHandler;

    @Bean
    SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        // 启用认证成功后处理器
        http.formLogin().successHandler(zsmAuthenticationSuccessHandler);
        // 启用认证失败后处理器
        http.formLogin().failureHandler(zsmAuthenticationFailureHandler);
        // 设置所有接口需要验证
        http.authorizeHttpRequests().anyRequest().authenticated();
        return http.build();
    }
}
```

![image-20240713150121607](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131501764.png)

### 登出成功处理器

和上面两个类似。

```java
@Component
public class ZSMLogoutSuccessHandler implements LogoutSuccessHandler {
    @Override
    public void onLogoutSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication) throws IOException, ServletException {
        System.out.println("登出成功");
    }
}
```

```java
@EnableWebSecurity
@Configuration
public class SecurityConfig {

    @Autowired
    private ZSMAuthenticationSuccessHandler zsmAuthenticationSuccessHandler;
    @Autowired
    private ZSMAuthenticationFailureHandler zsmAuthenticationFailureHandler;
    @Autowired
    private ZSMLogoutSuccessHandler zsmLogoutSuccessHandler;
    
    @Bean
    SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http.formLogin()
                // 启用认证成功后处理器
                .successHandler(zsmAuthenticationSuccessHandler)
                // 启用认证失败后处理器
                .failureHandler(zsmAuthenticationFailureHandler);

        http.logout().logoutSuccessHandler(zsmLogoutSuccessHandler);
        // 设置所有接口需要验证
        http.authorizeHttpRequests().anyRequest().authenticated();
        return http.build();
    }
}
```

![image-20240713150831781](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407131508948.png)