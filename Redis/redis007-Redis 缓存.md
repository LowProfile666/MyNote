# 7.1 Jedis 客户端

## 7.1.1    Jedis 简介

Jedis 是一个基于 java 的 Redis 客户端连接工具，旨在提升性能与易用性。其 github 上的官网地址为：https://github.com/redis/jedis。

## 7.1.2    创建工程

首先创建一个普通的Maven 工程 redis001-jedis，然后在 POM 文件中添加Jedis 与Junit 依赖。

Jedis依赖：

```xml
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
    <version>5.0.0</version>
</dependency>
```

## 7.1.3    使用 Jedis 实例

Jedis 基本使用十分简单，其提供了非常丰富的操作 Redis 的方法，而这些方法名几乎与 Redis 命令相同。在每次使用时直接创建 Jedis 实例即可。在 Jedis 实例创建好之后，Jedis 底层实际会创建一个到指定Redis 服务器的Socket 连接。所以，为了节省系统资源与网络带宽，在每次使用完 Jedis 实例之后，需要立即调用 close()方法将连接关闭。

首先，需要在工程的 src/test/java 下创建测试类 JedisTest。

### （1）  value 为 String 的测试

```java
@Test
public void test01() {
    // 创建jedis对象，指定redis的IP地址和端口，建立起一个长连接
    Jedis jedis = new Jedis("47.109.78.124", 6379);
    
    // 存数据
    jedis.set("name", "zsm");
    jedis.mset("age", "23", "gender", "male");

    // 取数据
    System.out.println(jedis.get("name"));
    System.out.println(jedis.get("age"));
    System.out.println(jedis.get("gender"));
    
    // 关闭
    jedis.close();
}
```

在redis客户端中也可以查看：

![image-20240802223119018](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408022231056.png)

### （2）  value 为 Hash 的测试

```java
@Test
public void test02() {
    Jedis jedis = new Jedis("47.109.78.124", 6379);

    // 存放hash类型的值
    jedis.hset("user", "name", "zhangsan");
    // 也可以直接使用map
    Map<String, String> map = new HashMap<>();
    map.put("age", "66");
    map.put("gender", "male");
    jedis.hset("user", map);

    // 取值
    System.out.println(jedis.hget("user", "name"));
    List<String> user = jedis.hmget("user", "name", "age", "gender");
    System.out.println(user);

    jedis.close();
}
```

输出结果：

```java
zhangsan
[zhangsan, 66, male]
```

redis中查看：

![image-20240802223731525](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408022237564.png)

### （3）  value 为 List 的测试

```java
@Test
public void test03() {
    Jedis jedis = new Jedis("47.109.78.124", 6379);
    jedis.rpush("cities", "beijing", "shanghai", "guangzhou");
    List<String> cities = jedis.lrange("cities", 0, -1);
    System.out.println(cities);
}
```

输出：

```java
[beijing, shanghai, guangzhou]
```

### （4）  value 为 Set 的测试

```java
@Test
public void test04() {
    Jedis jedis = new Jedis("47.109.78.124", 6379);
    jedis.sadd("names", "zhangsan", "lisi", "wangwu");
    Set<String> names = jedis.smembers("names");
    System.out.println(names);
}
```

输出结果：

```java
[lisi, zhangsan, wangwu]
```

### （5）  value 为 ZSet 的测试

```java
@Test
public void test05() {
    Jedis jedis = new Jedis("47.109.78.124", 6379);
    jedis.zadd("score", 60, "zhangsan");
    jedis.zadd("score", 40, "lisi");
    jedis.zadd("score", 70, "wangwu");
    jedis.zadd("score", 30, "zhaoliu");

    List<String> score = jedis.zrevrange("score", 0, 2);
    System.out.println(score);

    List<Tuple> score1 = jedis.zrevrangeWithScores("score", 0, -1);
    for (Tuple tuple : score1) {
        System.out.println(tuple.getScore() + " : " + tuple.getElement());
    }
}
```

输出结果：

```java
[wangwu, zhangsan, lisi]
70.0 : wangwu
60.0 : zhangsan
40.0 : lisi
30.0 : zhaoliu
```

## 7.1.4    使用 JedisPool

如果应用非常频繁地创建和销毁 Jedis 实例，虽然节省了系统资源与网络带宽，但会大大降低系统性能。因为创建和销毁 Socket 连接是比较耗时的。此时可以使用 Jedis 连接池来解决该问题。

```java
private JedisPool jedisPool = new JedisPool("47.109.78.124", 6379);

@Test
public void test01() {
    try(Jedis jedis = jedisPool.getResource()) {
        jedis.set("name", "zsm");
        jedis.mset("age", "23", "gender", "male");

        System.out.println(jedis.get("name"));
        System.out.println(jedis.get("age"));
        System.out.println(jedis.get("gender"));
    }
}
```

使用 JedisPool 与使用 Jedis 实例的区别是，JedisPool 是全局性的，整个类只需创建一次即可，然后每次需要操作Redis 时，只需从 JedisPool 中拿出一个 Jedis 实例直接使用即可。使用完毕后，无需释放 Jedis 实例，只需返回 JedisPool 即可。

## 7.1.5    使用 JedisPooled

对于每次对 Redis 的操作都需要使用try-with-resource 块是比较麻烦的，而使用 JedisPooled 则无需再使用该结构来自动释放资源了。

```java
private JedisPooled jedis = new JedisPooled("47.109.78.124", 6379);

@Test
public void test01() {
    jedis.set("name", "zsm");
    jedis.mset("age", "23", "gender", "male");

    System.out.println(jedis.get("name"));
    System.out.println(jedis.get("age"));
    System.out.println(jedis.get("gender"));
}
```

## 7.1.6    连接 Sentinel 高可用集群

对于 Sentinel 高可用集群的连接，直接使用 JedisSentinelPool 即可。在该客户端只需注册所有Sentinel 节点及其监控的Master 的名称即可，无需出现 master-slave 的任何地址信息。其采用的也是JedisPool，使用完毕的 Jedis 也需要通过 close()方法将其返回给连接池。

```java
private JedisSentinelPool jedisSentinelPool;

{
    Set<String> sentinels = new HashSet<>();
    sentinels.add("47.109.78.124:26380");
    sentinels.add("47.109.78.124:26381");
    sentinels.add("47.109.78.124:26382");
    jedisSentinelPool = new JedisSentinelPool("mymaster", sentinels);
}

@Test
public void test01() {
    Jedis jedis = jedisSentinelPool.getResource();
    jedis.set("name", "zsm");
    jedis.mset("age", "23", "gender", "male");

    System.out.println(jedis.get("name"));
    System.out.println(jedis.get("age"));
    System.out.println(jedis.get("gender"));
}
```

+ 这里连不上可能要考虑是不是防火墙没有开放对应端口

## 7.1.7    连接分布式系统

对于 Redis 的分布式系统的连接，直接使用 JedisCluster 即可。其底层采用的也是 Jedis连接池技术。每次使用完毕后，无需显式关闭，其会自动关闭。

对于 JedisCluster 常用的构造器有两个。一个是只需一个集群节点的构造器，这个节点可以是集群中的任意节点，只要连接上了该节点，就连接上了整个集群。但该构造器存在一个风险：其指定的这个节点在连接之前恰好宕机，那么该客户端将无法连接上集群。所以，推荐使用第二个构造器，即将集群中所有节点全部罗列出来。这样就会避免这种风险了。

```java
private JedisCluster jedisCluster;

{
    Set<HostAndPort> nodes = new HashSet<>();
    nodes.add(new HostAndPort("47.109.78.124", 6380));
    nodes.add(new HostAndPort("47.109.78.124", 6381));
    nodes.add(new HostAndPort("47.109.78.124", 6382));
    nodes.add(new HostAndPort("47.109.78.124", 6383));
    nodes.add(new HostAndPort("47.109.78.124", 6384));
    nodes.add(new HostAndPort("47.109.78.124", 6385));
    jedisCluster = new JedisCluster(nodes);
}

@Test
public void test01() {
    jedisCluster.set("name", "zsm");
    jedisCluster.mset("age{user}", "23", "gender{user}", "male");

    System.out.println(jedisCluster.get("name"));
    System.out.println(jedisCluster.get("age{user}"));
    System.out.println(jedisCluster.get("gender{user}"));
}
```

## 7.1.8   操作事务

对于 Redis 事务的操作，Jedis 提供了multi()、watch()、unwatch()方法来对应 Redis 中的 multi、watch、unwatch 命令。Jedis 的multi()方法返回一个Transaction 对象，其exec()与 discard()方法用于执行和取消事务的执行。

### （1）  抛出Java 异常

```java
private JedisPool jedisPool= new JedisPool("47.109.78.124", 6379);

@Test
public void test01() {
    try (Jedis jedis = jedisPool.getResource()) {
        jedis.set("name", "zsm");
        jedis.mset("age", "23", "gender", "male");

        Transaction transaction = jedis.multi();
        try {
            transaction.set("name", "张三");
            int a = 1 / 0;
            transaction.set("age", "213");
            transaction.exec();
        } catch (Exception e) {
            // 发生异常，全部回滚
            transaction.discard();
        } finally {
            System.out.println(jedis.get("name"));
            System.out.println(jedis.get("age"));
            System.out.println(jedis.get("gender"));
        }
    }
}
```

输出结果：

```java
zsm
23
male
```

其输出结果为全部回滚的结果。

### （2）  让 Redis 异常

```java
@Test
public void test02() {
    try (Jedis jedis = jedisPool.getResource()) {
        jedis.set("name", "zsm");
        jedis.mset("age", "23", "gender", "male");

        Transaction transaction = jedis.multi();
        try {
            transaction.set("name", "张三");
            // redis异常
            transaction.incr("name");
            transaction.set("age", "213");
            transaction.exec();
        } catch (Exception e) {
            // 发生异常，全部回滚
            transaction.discard();
        } finally {
            System.out.println(jedis.get("name"));
            System.out.println(jedis.get("age"));
            System.out.println(jedis.get("gender"));
        }
    }
}
```

其输出结果为修改过的值。说明 Redis 运行时抛出的异常不会被 Java 代码捕获到，其不会影响 Java 代码的执行。

```java
张三
213
male
```

### （3）  watch()

```java
@Test
public void test03() {
    try (Jedis jedis = jedisPool.getResource()) {
        jedis.set("age", "1");
        System.out.println("age = " + jedis.get("age"));

        jedis.watch("age");
        Transaction transaction = jedis.multi();
        try {
            transaction.incr("age");
            transaction.exec();
        } catch (Exception e) 
            transaction.discard();
        } finally {
            System.out.println("age = " + jedis.get("age"));
        }
    }
}
```

打断点，调试：

![image-20240805151458913](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408051515089.png)

然后在redis中，将age加了5，现在age是6：

![image-20240805151704013](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408051517073.png)

此时回到idea，继续向下执行，会将age加1变成7，但是因为使用了watch，所以age不会被修改 成功，age还是6：

```java
age = 1
age = 6
```

# 7.2    Spring Boot 整合 Redis

## 7.2.1    Redis 操作模板

Spring Boot 中可以直接使用 Jedis 实现对 Redis 的操作，但一般不这样用，而是使用 Redis操作模板 RedisTemplate 类的实例来操作Redis。

RedisTemplate 类是一个对Redis 进行操作的模板类。该模板类中具有很多方法，这些方法很多与 Redis 操作命令同名或类似。例如，delete()、keys()、scan()，还有事务相关的 multi()、 exec()、discard()、watch()等。当然还有获取对各种 Value 类型进行操作的操作实例的两类方法 boundXxxOps(k)与 opsForXxx()。

## 7.2.2    需求

下面通过一个例子来说明Spring Boot 是如何与 Redis 进行整合的。

金融产品交易平台：

对于一个资深成熟的金融产品交易平台，其用户端首页一般会展示其最新金融产品列表，同时还为用户提供了产品查询功能。另外，为了显示平台的实力与信誉，在平台首页非常显 眼的位置还会展示平台已完成的总交易额与注册用户数量。对于管理端，管理员可通过管理 页面修改产品、上架新产品、下架老产品。

为了方便了解 Redis 与 Spring Boot 的整合流程，这里对系统进行了简化：用户端首页仅提供根据金融产品名称的查询，显眼位置仅展示交易总额。管理端仅实现上架新产品功能。

## 7.2.3    创建 SSM 工程

### （1）  创建工程

定义一个 Spring Boot 工程，并命名为 redis002-springboot。

### （2）  定义 pom 文件

在 pom 文件中需要导入 MySQL 驱动、Druid 等大量依赖。POM 文件中的重要依赖如下

```xml
<dependencies>
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
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.33</version>
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
        <groupId>com.alibaba</groupId>
        <artifactId>druid</artifactId>
        <version>1.2.22</version>
    </dependency>
    <dependency>
        <groupId>org.thymeleaf</groupId>
        <artifactId>thymeleaf-spring6</artifactId>
        <version>3.1.2.RELEASE</version>
    </dependency>
</dependencies>
```

### （3）  修改主配置文件

在主配置文件中配置 MyBatis、Spring、日志等配置：

```yaml
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/redis-springboot
    username: root
    password: 1234
    type: com.alibaba.druid.pool.DruidDataSource
    
mybatis:
  type-aliases-package: com.zsm.bean
  configuration:
    map-underscore-to-camel-case: true
    
logging:
  pattern:
    console: level-%-5level - %msg%n

  level:
    root: warn
    com.zsm: debug
```

### （4）  实体类 Product

```java
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Product {
    private Integer id;
    // 产品名称
    private String name;
    //年化利率
    private Double rate;
    // 募集总额
    private Double amount;
    // 已募集金额
    private Double raised;
    // 产品周期
    private Integer cycle;
    // 产品募集结束时间
    private String endTime;
}
```

### （5）  创建数据库表

在 redis-springboot 数据库中创建一个名称为 product 的表。创建的 sql 文件如下，直接运行该文件即可：

```sql
DROP TABLE IF EXISTS `product`;
CREATE TABLE `product` (
`id` int(11) NOT NULL AUTO_INCREMENT,
`name` varchar(20) DEFAULT NULL,
`rate` double DEFAULT NULL,
`amount` double DEFAULT NULL,
`raised` double DEFAULT NULL,
`cycle` int(11) DEFAULT NULL,
`endTime` char(10) DEFAULT '0', PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

INSERT INTO `product` VALUES (1,'天鑫添益 2',2.76,50000,20000,30,'2022-07-10'),(2,'国泰添益',2.86,30000,30000,60,'2022-07-12'),(3,'国泰高鑫
',2.55,60000,50000,90,'2022-07-09'),(4,'国福民安
',2.96,30000,20000,7,'2022-05-10'),(5,'天益鑫多
',2.65,80000,60000,20,'2022-07-05'),(6,'惠农收益
',3.05,30000,20000,10,'2022-06-10'),(7,'惠农三鑫
',2.76,50000,30000,30,'2022-07-02'),(8,'励学收益',2.86,30000,20000,20,'2022-07-11');
```

### （6） 创建mapper文件

ProductMapper.java：

```java
@Mapper
public interface ProductMapper {
    List<Product> selectAllProducts();
    List<Product> selectProductsByName(String name);
    Double selectTurnover(String endTime);
    void insertProduct(Product product);   
}
```

ProductMapper.xml：

```xml
<mapper namespace="com.zsm.mapper.ProductMapper">
    <select id="selectAllProducts" resultType="Product">
        select * from product;
    </select>
    <select id="selectTurnover" resultType="double">
        select sum(raised) from product where endTime is not null and endTime &lt; #{endTime}
    </select>
    <select id="selectProductsByName" resultType="product">
        select * from product where name like '%' #{name} '%'
    </select>
    <insert id="insertProduct" >
        insert into product values(null, #{name}, #{rate}, #{amount}, #{raised}, #{cycle}, #{endTime});
    </insert>
</mapper>
```

### （7）创建service接口和实现类

ProductService：

```java
public interface ProductService {
    List<Product> selectAllProducts();
    List<Product> selectProductsByName(String name);
    Double selectTurnover(String endTime);
    void insertProduct(Product product);
}
```

ProductServiceImpl：

```java
@Service
public class ProductServiceImpl implements ProductService {
    @Autowired
    private ProductMapper productMapper;
    @Override
    public List<Product> selectAllProducts() {
        return productMapper.selectAllProducts();
    }

    @Override
    public List<Product> selectProductsByName(String name) {
        return productMapper.selectProductsByName(name);
    }

    @Override
    public Double selectTurnover(String endTime) {
        return productMapper.selectTurnover(endTime);
    }

    @Override
    public void insertProduct(Product product) {
        productMapper.insertProduct(product);
    }
}
```

### （8）创建controller

```java
@Controller
public class ProductController {
    @Autowired
    private ProductService productService;

    @GetMapping("/")
    public String index(Model model) {
        // 查询平台总交易额
        Double turnover = productService.selectTurnover();
        model.addAttribute("turnover", turnover);

        // 查询所有产品
        List<Product> products = productService.selectAllProducts();
        model.addAttribute("products", products);

        return "index";
    }

    @GetMapping("/product/name")
    public String list(String name, Model model) {
        List<Product> products = productService.selectProductsByName(name);
        model.addAttribute("products", products);
        model.addAttribute("name", name);
        return "result";
    }

    @GetMapping("/manager")
    public String manager(Model model) {
        List<Product> products = productService.selectAllProducts();
        model.addAttribute("products", products);
        return "manager";
    }

    @PostMapping("/add")
    public String add(Product product) {
        productService.insertProduct(product);
        return "redirect:/manager";
    }
}
```

### （9）创建页面

idnex：

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>首页</title>
</head>
<body>
平台总交易额：<h3 th:text="${turnover}"></h3>
<div th:each="product : ${products}" th:text="${product}">

</div>
<hr>
<h3>根据产品名称查询</h3>
<form action="/product/name">
    <input type="text" name="name">
    <input type="submit" value="查询">
</form>
<hr>
<a th:href="@{/manager}">管理</a>
</body>
</html>
```

manager：

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>管理</title>
</head>
<body>
<h3>产品列表</h3>
<div th:each="product : ${products}" th:text="${product}">

</div>
<hr>
<h3>新增产品</h3>
<form action="/add" method="post">
    产品名字：<input type="text" name="name"><br>
    产品年化利率：<input type="text" name="rate"><br>
    募集总额：<input type="text" name="amount"><br>
    已募集金额：<input type="text" name="raised"><br>
    产品周期：<input type="text" name="cycle"><br>
    产品募集结束时间：<input type="text" name="endTime"><br>
    <input type="submit" value="添加">
</form>
<hr>
<a th:href="@{/}">返回首页</a>
</body>
</html>
```

result：

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>查询结果页</title>
</head>
<body>
对产品<h3 th:text="${name}"></h3>的查询结果
<hr>
<div th:each="product : ${products}" th:text="${product}">

</div>
<hr>
<a th:href="@{/}">返回首页</a>
</body>
</html>
```

### （10）使用Redis

#### 配置redis和缓存

在主配置文件中配置redis服务器的信息：

单机redis：

```yaml
spring:
  data:
    redis:
      host: 47.109.78.124
      port: 6379
      # password: 111
```

sentinel高可用集群：

```yaml
spring:
  data:
    redis:
      host: 47.109.78.124
      port: 6379
      # password: 111

      sentinel:
        master: mymaster
        nodes: 47.109.78.124:26380,47.109.78.124:26381,47.109.78.124:26382
```

cluster分布式系统：

```yaml
spring:
  data:
    redis:
      host: 47.109.78.124
      port: 6379
      # password: 111

      sentinel:
        master: mymaster
        nodes: 47.109.78.124:26380,47.109.78.124:26381,47.109.78.124:26382

      cluster:
        nodes: 47.109.78.124:6380,47.109.78.124:6381,47.109.78.124:6382,47.109.78.124:6383,47.109.78.124:6384,47.109.78.124:6385
```

还要配置缓存：

```yaml
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/redis-springboot
    username: root
    password: 1234
    type: com.alibaba.druid.pool.DruidDataSource
  data:
    redis:
      host: 47.109.78.124
      port: 6379
      # password: 111
  cache:
    # 缓存类型
    type: redis
    # 缓存的名字，这个后面会用在代码中
    cache-names: pc
```

#### 开启缓存功能

在启动类上加上注解@EnableCaching：

```java
@EnableCaching
@SpringBootApplication
public class Application {

	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}

}
```

#### Product类实现Serializable接口

需要序列化，因为redis中需要序列化。

```java
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Product implements Serializable {
    private Integer id;
    // 产品名称
    private String name;
    //年化利率
    private Double rate;
    // 募集总额
    private Double amount;
    // 已募集金额
    private Double raised;
    // 产品周期
    private Integer cycle;
    // 产品募集结束时间
    private String endTime;
}
```

#### 修改ProductServiceImpl

将全部产品列表和总交易额放在缓存中，产品列表需要立即更新，比如在先添加了产品后；总交易额不需要立即更新。所以这两种不同的数据使用的缓存策略是不一样的。

使用RedisTemplate类。

首先要添加依赖：

```xml
<!-- https://mvnrepository.com/artifact/org.springframework.boot/spring-boot-starter-data-redis -->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
    <version>3.3.2</version>
</dependency>
```

然后注入RedisTemplate类：

```java
@Autowired
private RedisTemplate<Object, Object> redisTemplate;
```

##### 添加产品

当保存一个新产品的时候，就需要将缓存中的数据清空，可以在保存的方法上使用一个注解@CacheEvict：

```java
@Override
@Transactional(rollbackFor = Exception.class)
@CacheEvict(value = "pc", allEntries = true)
public void insertProduct(Product product) {
    productMapper.insertProduct(product);
}
```

+ @CacheEvict 用于实现清空指定名称的缓存区域，value就是名称。allEntries 为 true 指定清空该缓存空间所有数据。如果不想清空所有，则需通过 key 属性指定要清理的 key 数据。
+ 只要这个方法一执行，就会清除pc缓存区域内的所有数据

##### 查询产品

查询产品时，要将查询结果放到缓存中，使用注解@Cacheable：

```java
@Override
@Cacheable(value = "pc", key = "'product_all'")
public List<Product> selectAllProducts() {
    return productMapper.selectAllProducts();
}

@Override
@Cacheable(value = "pc", key = "'product_' + #name")
public List<Product> selectProductsByName(String name) {
    return productMapper.selectProductsByName(name);
}
```

+ @Cacheable 用于指定将查询结果使用指定的 key 缓存到指定缓存空间。如果再有对该查询数据的访问，则会先从缓存中查看。

##### 查询总交易额

先看缓存中是否有数据，有则返回缓存中的数据，否则从数据库中查询数据，并写入缓存中：

```java
@Override
public Double selectTurnover() {
    // 获取Redis操作指定key的对象
    BoundValueOperations<Object, Object> ops = redisTemplate.boundValueOps("turnover");
    // 从缓存中获取指定key的值
    Object turnover = ops.get();
    // 如果缓存中没有
    if (turnover == null) {
        // 获取当前时间并格式化
        Date date = new Date();
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");

        // 从数据库中获取值
        turnover = productMapper.selectTurnover(simpleDateFormat.format(date));

        // 将值写入缓存，设置10秒的过期时间
        ops.set(turnover, 10, TimeUnit.SECONDS);
    }

    return (Double) turnover;
}
```

##### 运行

现在运行项目。

查看redis中的数据：

![image-20240806100713950](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061007105.png)

十秒过后，再次查看redis：

![image-20240806100752990](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061007110.png)

此时观察控制台可以看到执行了sql查询：

![image-20240806100859131](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061008255.png)

清空控制台的消息，重新刷新页面，再观察：

![image-20240806100935196](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061009320.png)

只执行了查交易总额的sql，查询从产品列表的sql没有执行，因为缓存中有。

## 7.2.4 总结

如何将 Spring Boot 与 Redis 整合？

+ 在 POM 中导入依赖

+ 在配置文件中注册 Redis 连接信息与缓存信息   

+ 需要缓存到 Redis 中的实体类必须要序列化

+ Spring Boot 启动类中要添加@EnableCaching 注解

+ 查询方法上要添加@Cacheable 注解

+ 对数据进行写操作的方法上添加@CacheEvict 注解

+ 对于需要手工操作 Redis 的方法，需通过RedisTemplate 来获取操作对象

# 7.3 高并发问题

Redis 做缓存虽减轻了 DBMS 的压力，减小了 RT，但在高并发情况下也是可能会出现各种问题的。

## 7.3.1    缓存穿透

当用户访问的数据既不在缓存也不在数据库中时，就会导致每个用户查询都会“穿透”缓存“直抵”数据库。这种情况就称为缓存穿透。当高度发的访问请求到达时，缓存穿透不仅增加了响应时间，而且还会引发对 DBMS 的高并发查询，这种高并发查询很可能会导致 DBMS 的崩溃。

缓存穿透产生的主要原因有两个：一是在数据库中没有相应的查询结果，二是查询结果为空时，不对查询结果进行缓存。所以，针对以上两点，解决方案也有两个：

+ 对非法请求进行限制

+ 对结果为空的查询给出默认值

## 7.3.2    缓存击穿

对于某一个缓存，在高并发情况下若其访问量特别巨大，当该缓存的有效时限到达时，可能会出现大量的访问都要重建该缓存，即这些访问请求发现缓存中没有该数据，则立即到 DBMS 中进行查询，那么这就有可能会引发对 DBMS 的高并发查询，从而接导致 DBMS 的崩溃。这种情况称为缓存击穿，而该缓存数据称为热点数据。

对于缓存击穿的解决方案，较典型的是使用“双重检测锁”机制。比如，上面代码中的获取总交易额的操作，使用双重检测锁：

```java
public Double selectTurnover() {
    // 获取Redis操作指定key的对象
    BoundValueOperations<Object, Object> ops = redisTemplate.boundValueOps("turnover");
    // 从缓存中获取指定key的值
    Object turnover = ops.get();
    // 如果缓存中没有
    if (turnover == null) {  // 第一重
        synchronized (this) {
            turnover = ops.get();
            if (turnover == null) {  // 第二重
                // 获取当前时间并格式化
                Date date = new Date();
                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");

                // 从数据库中获取值
                turnover = productMapper.selectTurnover(simpleDateFormat.format(date));

                // 将值写入缓存，设置10秒的过期时间
                ops.set(turnover, 10, TimeUnit.SECONDS);
            }
        }
    }

    return (Double) turnover;
}
```

当第一个请求 走到第二重时，这段代码被锁住了，其他请求只能走进第一重，然后等着，当第一个请求在缓存中写入数据后，其他再来的请求就不会走进第一重，可以直接返回；而之前走进第一重的请求，也会因为从缓存中获取  到了数据而不会进入到第二重中。

## 7.3.3    缓存雪崩

对于缓存中的数据，很多都是有过期时间的。若大量缓存的过期时间在同一很短的时间段内几乎同时到达，那么在高并发访问场景下就可能会引发对 DBMS 的高并发查询，而这将可能直接导致DBMS 的崩溃。这种情况称为缓存雪崩。

对于缓存雪崩没有很直接的解决方案，最好的解决方案就是预防，即提前规划好缓存的过期时间。要么就是让缓存永久有效，当 DB 中数据发生变化时清除相应的缓存。如果 DBMS采用的是分布式部署，则将热点数据均匀分布在不同数据库节点中，将可能到来的访问负载均衡开来。

## 7.1.4    数据库缓存双写不一致

以上三种情况都是针对高并发读场景中可能会出现的问题，而数据库缓存双写不一致问题，则是在高并发写场景下可能会出现的问题。

对于数据库缓存双写不一致问题，以下两种场景下均有可能会发生：

### （1）  “修改 DB 更新缓存”场景

对于具有缓存 warmup 功能的系统，DBMS 中常用数据的变更，都会引发缓存中相关数据的更新。在高并发写请求场景下，若多个请求要对 DBMS 中同一个数据进行修改，修改后还需要更新缓存中相关数据，那么就有可能会出现缓存与数据库中数据不一致的情况。

![image-20240806133531185](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061335347.png)

### （2）  “修改 DB 删除缓存”场景

在很多系统中是没有缓存warmup 功能的，为了保持缓存与数据库数据的一致性，一般都是在对数据库执行了写操作后，就会删除相应缓存。

在高并发读写请求场景下，若这些请求对 DBMS 中同一个数据的操作既包含写也包含读，且修改后还要删除缓存中相关数据，那么就有可能会出现缓存与数据库中数据不一致的情况。

![image-20240806133539944](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061335085.png)

###  （3）  解决方案：延迟双删

延迟双删方案是专门针对于“修改 DB 删除缓存”场景的解决方案。但该方案并不能彻底解决数据不一致的状况，其只可能降低发生数据不一致的概率。

延迟双删方案是指，在写操作完毕后会立即执行一次缓存的删除操作，然后再停上一段时间（一般为几秒）后再进行一次删除。而两次删除中间的间隔时长，要大于一次缓存写操作的时长。

![image-20240806133550921](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408061335052.png)

### （4）  解决方案：队列

 

以上两种场景中，只所以会出现数据库与缓存中数据不一致，主要是因为对请求的处理出现了并行。只要将请求写入到一个统一的队列，只有处理完一个请求后才可处理下一个请求，即使系统对用户请求的处理串行化，就可以完全解决数据不一致的问题。

### （5）  解决方案：分布式锁

使用队列的串行化虽然可以解决数据库与缓存中数据不一致，但系统失去了并发性，降低了性能。使用分布式锁可以在不影响并发性的前提下，协调各处理线程间的关系，使数据库与缓存中的数据达成一致性。

只需要对数据库中的这个共享数据的访问通过分布式锁来协调对其的操作访问即可。

