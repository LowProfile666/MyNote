分布式锁是控制分布式系统间同步访问共享资源的一种方式，其可以保证共享资源在并发场景下的数据一致性。

# 9.1 分布式锁的工作原理

当有多个线程要访问某一个共享资源（DBMS 中的数据或Redis 中的数据，或共享文件等）时，为了达到协调多个线程的同步访问，此时就需要使用分布式锁了。

为了达到同步访问的目的，规定，让这些线程在访问共享资源之前先要获取到一个令牌 token，只有具有令牌的线程才可以访问共享资源。这个令牌就是通过各种技术实现的分布式锁。而这个分布锁是一种“互斥资源”，即只有一个。只要有线程抢到了锁，那么其它线程只能等待，直到锁被释放或等待超时。

# 9.2 问题引入

## 9.2.1    场景

某电商平台要对某商品（例如商品 sk:0008）进行秒杀销售。假设参与秒杀的商品数量 amount 为 1000 台，每个账户只允许抢购一台，即每个请求只会减少一台库存。

## 9.2.2    实现

创建一个 Spring Boot 工程。

### （1）pom.xml

```xml
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter</artifactId>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-test</artifactId>
        <scope>test</scope>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-data-redis</artifactId>
    </dependency>
    <dependency>
        <groupId>org.projectlombok</groupId>
        <artifactId>lombok</artifactId>
    </dependency>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>
```

### （2）application.yaml

配置redis：

```yaml
spring:
  data:
    redis:
      host: 47.109.78.124
      port: 6379
```

### （3）创建controller

创建一个秒杀的方法，先从缓存中查找是否有数据，如果有说明抢到了，如果没有说明没有抢到。

```java
@RestController
public class MSController {
    @Autowired
    private StringRedisTemplate stringRedisTemplate;

    @RequestMapping("/ms")
    public String ms() {
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }

        return "没有库存了";
    }
}
```

上述代码是有问题的。既然是秒杀，那么一定是高并发场景，且生产环境下，该应用一定是部署在一个集群中的。如果参与秒杀的用户数量特别巨大，那么一定会存在很多用户同时读取 Redis 缓存中的 sk:0008 这个 key，那么大家读取到的 value 很可能是相同的，均大于零，均可购买。此时就会出现“超卖”。即，以上代码存在并发问题。

# 9.3 setnx 实现方式

## 9.3.1    原理 

为了解决上述代码中的并发问题，可以使用 Redis 实现的分布式锁。

该实现方式主要是通过 setnx 命令完成的。其基本原理是，setnx 只有在指定 key 不存在时才能执行成功，分布式系统中的哪个节点抢先成功执行了 setnx，谁就抢到了锁，谁就拥有了对共享资源的操作权限。当然，其它节点只能等待锁的释放。一旦拥有锁的节点对共享资源操作完毕，其就可以主动删除该 key，即释放锁。然后其它节点就可重新使用 setnx 命令抢注该 key，即抢注锁。

## 9.3.2 实现

首先在 Controller 类中添加一个String 常量，作为 Redis 锁的 key。然后修改代码。

```java
public static final String REDIS_LOCK = "redis_lock";
@Autowired
private StringRedisTemplate stringRedisTemplate;

@RequestMapping("/ms")
public String ms() {
    try {
        // 添加锁
        Boolean ok = stringRedisTemplate.opsForValue().setIfAbsent(REDIS_LOCK, "redis");
        if (!ok)
            return "没有抢到锁";
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }
    } finally {
        // 释放锁
        stringRedisTemplate.delete(REDIS_LOCK);
    }

    return "没有库存了";
}
```

若处理当前请求的 APP 节点主机在执行完“添加锁”语句后突然宕机，其 finally 中的释放锁代码根本就没有执行，那么，其它客户端通过其它 APP 节点主机申请资源时，将会由于无法获得到锁而永久性阻塞。

# 9.4 为锁添加过期时间

## 9.4.1    原理

为了解决前述方式中存在的问题，可以为锁添加过期时间，这样就不会出现锁被某节点主机永久性占用的情况，即不会出现节点被永久性阻塞的情况。

不过，为 key 添加过期时间的方式有两种：一种是通过 expire 命令为key 指定过期时间，还有一种是在setnx 命令中直接给出该 key 的过期时间。第一种方式中 setnx 与 expire 命令是分别执行的，不具备原子性，仍然可能会出现问题。而第二种方式则是直接在 setnx 中完成了两步操作，具有原子性。故，应采用第二种方式。

## 9.4.2    实现 

```java
public static final String REDIS_LOCK = "redis_lock";

@Autowired
private StringRedisTemplate stringRedisTemplate;

@RequestMapping("/ms")
public String ms() {
    try {
        // 添加锁
        // Boolean ok = stringRedisTemplate.opsForValue().setIfAbsent(REDIS_LOCK, "redis");
        // 为锁添加过期时间
        // stringRedisTemplate.expire(REDIS_LOCK, 5, TimeUnit.SECONDS);

        // 添加锁并设置过期时间，该操作具有原子性
        Boolean ok = stringRedisTemplate.opsForValue().setIfAbsent(REDIS_LOCK, "redis", 5, TimeUnit.SECONDS);
        if (!ok)
            return "没有抢到锁";
        
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }
    } finally {
        // 释放锁
        stringRedisTemplate.delete(REDIS_LOCK);
    }

    return "没有库存了";
}
```

上述代码中为锁指定的过期时间为 5 秒，如果 ms 方法的业务逻辑比较复杂，需要调用其它微服务处理。如果请求 a 的处理时间超过了 5 秒(假设 6 秒)，而当 5 秒钟过去 后，这个锁自动过期了。由于锁已过期，另一个请求 b 通过 setnx 申请到了锁。此时如果耗 时 6 秒的请求a 处理完了，回来继续执行程序，请求 a 就会把请求b 设置的锁给删除了。此 时其它请求就可申请到锁，并与请求 b 同时访问共享资源，很可能会引发数据的不一致。这是个很严重的问题。

# 9.5 为锁添加标识

## 9.5.1    原理 

上述代码只所以会出现那种锁被误删的情况，主要是因为所有客户端添加的锁的value值完全相同，而我们想要的效果是“谁添加的锁，该锁只能由谁来删”。

为了实现这个效果，为每个申请锁的客户端随机生成一个 UUID，使用这个 UUID 作为该客户端标识，然后将该 UUID 作为该客户端申请到的锁的value。在删除锁时，只有在发起当前删除操作的客户端的 UUID 与锁的value 相同时才可以。

## 9.5.2    实现

```java
public static final String REDIS_LOCK = "redis_lock";

@Autowired
private StringRedisTemplate stringRedisTemplate;

@RequestMapping("/ms")
public String ms() {
    // 为每一个访问的客户端生成一个随机的客户端标识
    String clientId = UUID.randomUUID().toString();
    try {
        // 添加锁并设置过期时间，该操作具有原子性
        // 将value设为uuid
        Boolean ok = stringRedisTemplate.opsForValue().setIfAbsent(REDIS_LOCK, clientId, 5, TimeUnit.SECONDS);
        if (!ok)
            return "没有抢到锁";
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }
    } finally {
        // 只有添加锁的客户端才能释放锁
        if (clientId.equals(stringRedisTemplate.opsForValue().get(REDIS_LOCK)))
            // 释放锁
            stringRedisTemplate.delete(REDIS_LOCK);
    }

    return "没有库存了";
}
```

## 9.5.3    问题

在 finally{}中对于删除锁的客户端身份的判断与删除锁操作是两个语句，不具有原子性，在并发场景下可能会出问题。

例如，客户端 a 在节点主机 A 中添加了锁后，执行业务逻辑用时 6 秒，此时锁已过期，然后执行到了 finally{}中的判断，并判断结果为真，然后时间片到了，暂停执行。

由于节点主机A 中的锁已经过期，客户端 b 在节点主机B 中添加锁成功，然后很快执行到了业务逻辑（未超过锁的过期时间），此时客户端 b 的处理进程时间片到了。

此时主机A 中的代码又获得了处理机，继续执行。此时就会执行对锁的删除语句，删除成功。也就是说主机A 删除了由主机B 添加的锁。这就是很严重的问题。 

# 9.6 添加 Lua 脚本

## 9.6.1    原理 

对客户端身份的判断与删除锁操作的合并，是没有专门的原子性命令的。此时可以通过Lua 脚本来实现它们的原子性。而对 Lua 脚本的执行，可以通过 eval 命令来完成。

不过，eval 命令在 RedisTemplate 中没有对应的方法，而 Jedis 中具有该同名方法。所以，需要在代码中首先获取到 Jedis 客户端，然后才能调用 jedis.eval()。

## 9.6.2 实现

导入jedis依赖：

```xml
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
</dependency>
```

修改代码：

```java
public static final String REDIS_LOCK = "redis_lock";

@Autowired
private StringRedisTemplate stringRedisTemplate;

@Value("${spring.redis.host}")
private String host;
@Value("${spring.redis.port}")
private Integer port;

@RequestMapping("/ms")
public String ms() {
    // 为每一个访问的客户端生成一个随机的客户端标识
    String clientId = UUID.randomUUID().toString();
    try {
        // 添加锁并设置过期时间，该操作具有原子性
        // 将value设为uuid
        Boolean ok = stringRedisTemplate.opsForValue().setIfAbsent(REDIS_LOCK, clientId, 5, TimeUnit.SECONDS);
        if (!ok)
            return "没有抢到锁";
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }
    } finally {
        JedisPool jedisPool = new JedisPool(host, port);
        try(Jedis jedis = jedisPool.getResource()) {
            // 定义lua脚本
            // redis.call()是lua中对redis命令的调用函数
            String script = """
                                if redis.call('get', KEYS[1]) == ARGV[1] then 
                                    return redis.call('del', KEYS[1])
                                    end
                                    return 0;
                            """;
                // eval的返回值为脚本script的返回值
                Object eval = jedis.eval(script, Collections.singletonList(REDIS_LOCK), Collections.singletonList(clientId));

            if ("1".equals(eval.toString())) System.out.println("释放锁成功");
            else System.out.println("释放锁失败");
        }
    }

    return "没有库存了";
}
```

以上代码仍然是存在问题的：请求 a 的锁过期，但其业务还未执行完毕；请求 b 申请到了锁，其也正在处理业务。如果此时两个请求都同时修改了共享的库存数据，那么就又会出现数据不一致的问题，即仍然存在并发问题。在高并发场景下，问题会被无限放大。

对于该问题，可以采用“锁续约”方式解决。即，在当前业务进程开始执行时，fork 出一个子进程，用于启动一个定时任务。该定时任务的定时时间小于锁的过期时间，其会定时查看处理当前请求的业务进程的锁是否已被删除。如果已被删除，则子进程结束；如果未被删除，说明当前请求的业务还未处理完毕，则将锁的时间重新设置为“原过期时间”。这种方式称为锁续约，也称为锁续命。

# 9.7 Redisson 可重入锁

## 9.7.1    原理

使用 Redisson 的可重入锁可以解决上述问题。

Redisson 内部使用 Lua 脚本实现了对可重入锁的添加、重入、续约（续命）、释放。Redisson需要用户为锁指定一个 key，但无需为锁指定过期时间，因为它有默认过期时间(当然，也可指定)。由于该锁具有“可重入”功能，所以 Redisson 会为该锁生成一个计数器，记录一个线程重入锁的次数。 

## 9.7.2 实现

导入redisson依赖：
```xml
<!-- https://mvnrepository.com/artifact/org.redisson/redisson -->
<dependency>
    <groupId>org.redisson</groupId>
    <artifactId>redisson</artifactId>
    <version>3.34.1</version>
</dependency>
```

Redisson对象需要注入到容器中，所以可以在启动类中注入：

```java
@SpringBootApplication
public class Application {
    @Value("${spring.redis.host}")
    private String host;
    @Value("${spring.redis.port}")
    private Integer port;

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    public Redisson redisson() {
        // redisson需要从一个config对象中获取redis的信息
        Config config = new Config();
        config.useSingleServer()
                .setAddress(host + ":" + port)  // 这是redis链接
                .setDatabase(0);  // 使用0号数据库
         
        return ((Redisson) Redisson.create(config));
    }
}
```

然后可以使用redisson：

```java
@Autowired
private Redisson redisson;

@RequestMapping("/ms")
public String ms() {
    RLock lock = redisson.getLock(REDIS_LOCK);
    try {
        // 添加分布式锁
        // Boolean ok = lock.tryLock();
        // 指定锁的过期时间为5秒，如果申请失败，则最长等待20秒
        boolean ok = lock.tryLock(20, 5, TimeUnit.SECONDS);
        if (!ok)
            return "没有抢到锁";
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }
    } finally {
        // 释放锁
        lock.unlock();
    }

    return "没有库存了";
}
```

在 Redis 单机情况下，以上代码是没有问题的。但如果是在 Redis 主从集群中，那么其还存在锁丢失问题。

在 Redis 主从集群中，假设节点A 为 master，节点 B、C 为 slave。如果一个请求 a 在处理时申请锁，即向节点 A 添加一个 key。当节点A 收到请求后写入key 成功，然后会立即向处理 a 请求的应用服务器 Sa 响应，然后会向slave 同步该 key。不过，在同步还未开始时，节点A 宕机，节点B 晋升为 master。此时正好有一个请求 b 申请锁，由于节点 B 中并没有该 key，所以该 key 写入成功，然后会立即向处理 b 请求的应用服务器 Sb 响应。由于 Sa 与 Sb 都收到了 key 写入成功的响应，所以它们都可同时对共享数据进行处理。这就又出现了并发问题。

只所以新的 master 节点B 同意请求 b 的锁申请，是因为主从集群丢失了请求a 的锁申请，即对于节点 B 来说，其根本就不知道有过请求 a 的锁申请。所以，该问题称为主从集群的锁丢失问题。

# 9.8 Redisson 红锁

## 9.8.1    原理

Redisson 红锁可以防止主从集群锁丢失问题。Redisson 红锁要求，必须要构建出至少三个 Redis 主从集群。若一个请求要申请锁，必须向所有主从集群中提交key 写入请求，只有当大多数集群锁写入成功后，该锁才算申请成功。

## 9.8.2 实现

我们这里要使用三个高可用的 Redis 主从集群，所以需要在启动类中添加三个Sentinel集群构建的Redisson 的Bean。由于这三个 Bean 将来要使用 byName 注入方式，所以这里为每个Bean 指定了一个名称。

```java
@Bean("redisson1")
public Redisson redisson1() {
    Config config = new Config();
    config.useSentinelServers()
        .setMasterName("mymaster")
        .addSentinelAddress("47.109.78.124:16380", "47.109.78.124:16381", "47.109.78.124:16382");
    return ((Redisson) Redisson.create(config));
}
@Bean("redisson2")
public Redisson redisson2() {
    Config config = new Config();
    config.useSentinelServers()
        .setMasterName("mymaster")
        .addSentinelAddress("47.109.78.124:26380", "47.109.78.124:26381", "47.109.78.124:26382");
    return ((Redisson) Redisson.create(config));
}
@Bean("redisson3")
public Redisson redisson3() {
    Config config = new Config();
    config.useSentinelServers()
        .setMasterName("mymaster")
        .addSentinelAddress("47.109.78.124:36380", "47.109.78.124:36381", "47.109.78.124:36382");
    return ((Redisson) Redisson.create(config));
}
```

然后修改controller中的代码，注入三个redisson：

```java
@Resource(name = "redisson1")
private Redisson redisson1;
@Resource(name = "redisson2")
private Redisson redisson2;
@Resource(name = "redisson3")
private Redisson redisson3;
```

创建三个锁：
```java
@RequestMapping("/ms")
public String ms() {
    // 定义三个可重入锁
    RLock lock1 = redisson1.getLock(REDIS_LOCK);
    RLock lock2 = redisson2.getLock(REDIS_LOCK);
    RLock lock3 = redisson3.getLock(REDIS_LOCK);

    // 定义红锁
    RedissonRedLock lock = new RedissonRedLock(lock1, lock2, lock3);
    try {
        boolean ok = lock.tryLock();
        if (!ok)
            return "没有抢到锁";
        String name = "sk:0008";
        // 查询内存，获取库存
        String val = stringRedisTemplate.opsForValue().get(name);
        int stock = val == null ? 0 : Integer.parseInt(val);
        if (stock > 0) {
            // 修改内存
            stringRedisTemplate.opsForValue().set(name, String.valueOf(--stock));
            return "库存剩余" + stock + "台";
        }
    } finally {
        // 释放锁
        lock.unlock();
    }

    return "没有库存了";
}
```

无论前面使用的是哪种锁，它们解决并发问题的思路都是相同的，那就将所有请求通过锁实现串行化。而串行化在高并发场景下势必会引发性能问题。

# 9.9 分段锁

解决锁的串行化引发的性能问题的方案就是，使访问并行化。将要共享访问的一个资源，拆分为多个共享访问资源，这样就会将一把锁的需求转变为多把锁，实现并行化。

例如，对于秒杀商品 sk:0008，其有 1000 件。现在将其拆分为 10 份，每份 100 件。即将秒杀商品变为了 10 件，分别为 sk:0008:01，sk:0008:02，sk:0008:03，„„，sk:0008:10。这样的话，就需要 10 把锁来控制所有请求的并发。由原来的因为只有一把锁而导致的每个时刻只能处理 1 个请求，变为了现在有了 10 把锁，每个时刻可以同时处理 10 个请求。并发提高了 10 倍。

# 9.10       Redisson 详解 

## 9.10.1    Redisson 简介

Redisson 是一个在 Redis 的基础上实现的Java 驻内存数据网格（In-Memory Data Grid）。它不仅提供了一系列的分布式的 Java 常用对象，还提供了许多分布式服务。其中包括 (BitSet, Set, Multimap, SortedSet, Map, List, Queue, BlockingQueue, Deque, BlockingDeque, Sem aphore, Lock, AtomicLong, CountDownLatch, Publish / Subscribe, Bloom filter, Remote service, Spring cache, Executor service, Live Object service, Scheduler service) Redisson 提供了使用 Redis 的最简单和最便捷的方法。Redisson 的宗旨是促进使用者对 Redis 的关注分离（Separation of Concern），从而让使用者能够将精力更集中地放在处理业务逻辑上。 Redisson 底层采用的是Netty 框架。支持 Redis2.8 以上版本，支持Java1.6+以上版本。

Redisson 官网：[https://redisson.org](https://redisson.org/)，github 上的官网：[https://github.com/redisson/redisson](https://github.com/redisson/redisson/wiki/目录)。

在生产中，对于Redisson 使用最多的场景就是其分布式锁 RLock。当然，RLock 仅仅是 Redisson 的线程同步方案之一。Redisson 提供了 8 种线程同步方案，用户可针对不同场景选用不同方案。

需要注意的是，为了避免锁到期但业务逻辑没有执行完毕而引发的多个线程同时访问共享资源的情况发生，Redisson 内部为锁提供了一个监控锁的看门狗 watch dog，其会在锁到期前不断延长锁的到期时间，直到锁被主动释放。即会自动完成“锁续命”。

## 9.10.2    可重入锁 

Redisson 的分布式锁 RLock 是一种可重入锁。当一个线程获取到锁之后，这个线程可以再次获取本对象上的锁，而其他的线程是不可以的。

+ JDK 中的 ReentrantLock 是可重入锁，其是通过 AQS(抽象队列同步器)实现的锁机制

+ synchronized 也是可重入锁，其是通过监视器模式(本质是 OS 的互斥锁)实现的锁机制

## 9.10.3    公平锁

Redisson 的可重入锁 RLock 默认是一种非公平锁，但也支持可重入公平锁 FailLock。当有多个线程同时申请锁时，这些线程会进入到一个 FIFO 队列，只有队首元素才会获取到锁，其它元素等待。只有当锁被释放后，才会再将锁分配给当前的队首元素。

## 9.10.4    联锁

Redisson 分布式锁可以实现联锁MultiLock。当一个线程需要同时处理多个共享资源时，可使用联锁。即一次性申请多个锁，同时锁定多个共享资源。联锁可预防死锁。相当于对共享资源的申请实现了原子性：要么都申请到，只要缺少一个资源，则将申请到的所有资源全部释放。其是 OS 底层原理中 AND 型信号量机制的典型应用。

## 9.10.5    红锁

Redisson 分布式锁可以实现红锁 RedLock。红锁由多个锁构成，只有当这些锁中的大部分锁申请成功时，红锁才申请成功。红锁一般用于解决 Redis 主从集群锁丢失问题。

红锁与联锁的区别是，红锁实现的是对一个共享资源的同步访问控制，而联锁实现的是多个共享资源的同步访问控制。

## 9.10.6    读写锁

通过 Redisson 可以获取到读写锁 RReadWriteLock。通过RReadWriteLock 实例可分别获取到读锁 RedissonReadLock 与写锁 RedissonWriteLock。读锁与写锁分别是实现了 RLock 的可重入锁。

一个共享资源，在没有写锁的情况下，允许同时添加多个读锁。只要添加了写锁，任何读锁与写锁都不能再次添加。即读锁是共享锁，写锁为排他锁。 

## 9.10.7    信号量 

通过Redisson 可以获取到信号量RSemaphore。RSemaphore 的常用场景有两种：一种是，无论谁添加的锁，任何其它线程都可以解锁，就可以使用 RSemaphore。另外，当一个线程需要一次申请多个资源时，可使用RSemaphore。RSemaphore 是信号量机制的典型应用。

## 9.10.8    可过期信号量

通过 Redisson 可以获取到可过期信号量 PermitExpirableSemaphore。该信号量是在 RSemaphore 基础上，为每个信号增加了一个过期时间，且每个信号都可以通过独立的 ID 来辨识。释放时也只能通过提交该 ID 才能释放。

不过，一个线程每次只能申请一个信号量，当然每次了只会释放一个信号量。这是与RSemaphore 不同的地方。

该信号量为互斥信号量时，其就等同于可重入锁。或者说，可重入锁就相当于信号量为 1 的可过期信号量。

注意，可过期信号量与可重入锁的区别：

+ 可重入锁：相当于用户每次只能申请 1 个信号量，且只有一个用户可以申请成功

+ 可过期信号量：用户每次只能申请 1 个信号量，但可以有多个用户申请成功

## 9.10.9    分布式闭锁

通过 Redisson 可以获取到分布式闭锁 RCountDownLatch，其与 JDK 的 JUC 中的闭锁 CountDownLatch 原理相同，用法类似。其常用于一个或者多个线程的执行必须在其它某些任务执行完毕的场景。例如，大规模分布式并行计算中，最终的合并计算必须基于很多并行计算的运行完毕。

闭锁中定义了一个计数器和一个阻塞队列。阻塞队列中存放着待执行的线程。每当一个并行任务执行完毕，计数器就减 1。当计数器递减到 0 时就会唤醒阻塞队列的所有线程。

通常使用 Barrier 队列解决该问题，而 Barrier 队列通常使用Zookeeper 实现。







