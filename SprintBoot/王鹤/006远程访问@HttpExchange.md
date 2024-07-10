远程访问是开发的常用技术，一个应用能够访问其他应用的功能。Spring Boot 提供了多种远程访问的技术。基于 HTTP 协议的远程访问是支付最广泛的。Spring Boot3 提供了新的 HTTP 的访问能力，通过接口简化 HTTP远程访问，类似 Feign 功能。Spring 包装了底层 HTTP 客户的访问细节。

SpringBoot 中定义接口提供 HTTP 服务，生成的代理对象实现此接口，代理对象实现 HTTP 的远程访问。需要理解：

+ @HttpExchange
+ WebClient

WebClient 特性：

我们想要调用其他系统提供的 HTTP 服务，通常可以使用 Spring 提供的 RestTemplate 来访问，RestTemplate 是 Spring 3 中引入的同步阻塞式 HTTP 客户端，因此存在一定性能瓶颈。Spring 官方在 Spring 5中引入了 WebClient 作为非阻塞式 HTTP 客户端。

+ 非阻塞，异步请求
+ 它的响应式编程的基于 Reactor
+ 高并发，硬件资源少。
+ 支持 Java 8 lambdas 函数式编程

什么是异步非阻塞？

理解：异步和同步，非阻塞和阻塞

+ 上面都是针对对象不一样
+ 异步和同步针对调度者,调用者发送请求,如果等待对方回应之后才去做其他事情,就是同步,如果发送请求之后不等着对方回应就去做其他事情就是异步
+ 阻塞和非阻塞针对被调度者,被调度者收到请求后,做完请求任务之后才给出反馈就是阻塞,收到请求之后马上给出反馈然后去做事情,就是非阻塞

# 准备工作

安装 GsonFormat 插件，方便在写代码时， json 和 Bean 的转换

![image-20240709163347576](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091633689.png)

介绍一个免费的、24h 在线的 Rest Http 服务，每月提供近 20 亿的请求，关键还是免费的、可公开访问的。https://jsonplaceholder.typicode.com/

创建一个新项目。需要加入依赖：Spring Web, Spring Reactive Web（有webclient对象） ,Lombok 。

# 声明式 HTTP 远程服务

访问 https://jsonplaceholder.typicode.com/ 提供的 todos 服务，基于 RESTful 风格，添加新的 todo，修改 todo，修改 todo 中的 title，查询某个 todo。声明接口提供对象 https://jsonplaceholder.typicode.com/todos 服务的访问。

访问https://jsonplaceholder.typicode.com/todos/1可以获得id为1的todo信息：

![image-20240709164003621](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091640659.png)

在代码中新定义一个todo实体类来保存数据，将以上图中的json信息复制下来，然后回到IDEA，创建一个Todo类，右键单击选择Generate或者使用快捷键Alt+Insert弹出以下页面：

![image-20240709164237260](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091642300.png)

选择Gsonformat，这是刚刚下载的插件提供的功能，将复制的json信息复制进去：

![image-20240709164400984](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091644037.png)

点击ok：

![image-20240709164425751](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091644798.png)

再点击ok就生成好了代码：

![image-20240709164537374](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091645425.png)

最后修改成自己要的模式：

```java
@NoArgsConstructor
@AllArgsConstructor
@Data
public class Todo {
    private Integer userId;
    private Integer id;
    private String title;
    private boolean completed;
}
```

+ 使用GsonFormatPlus插件生成的代码更好

创建服务接口，写服务方法，一个服务方法就是一个远程调用。

定义一个根据id获取todo的服务：

```java
public interface TodoService {
    @GetExchange("/todos/{id}")
    Todo getTodoById(@PathVariable("id") Integer id);
}
```

+ GetExchange是HttpExchange的衍生，指定了远程调用的接口，这是源码：

  ```java
  @Target({ElementType.METHOD})
  @Retention(RetentionPolicy.RUNTIME)
  @Documented
  @HttpExchange(
      method = "GET"
  )
  public @interface GetExchange {
      @AliasFor(
          annotation = HttpExchange.class
      )
      String value() default "";
  
      @AliasFor(
          annotation = HttpExchange.class
      )
      String url() default "";
  
      @AliasFor(
          annotation = HttpExchange.class
      )
      String[] accept() default {};
  }
  ```

  类似的还有@PostExchange、@PutExchange等，限制了请求的类型

接下来要创建代理的配置类：
```java
@Configuration(proxyBeanMethods = false)
public class HttpConfiguration {
    @Bean
    public TodoService requestService() {
        // 先创建WebClient
        WebClient webClient = WebClient.builder().baseUrl("https://jsonplaceholder.typicode.com/").build();

        // 再创建代理工厂
        HttpServiceProxyFactory proxyFactory =
                HttpServiceProxyFactory.builder(WebClientAdapter.forClient(webClient)).build();

        // 再通过工厂创建接口的代理服务，返回
        return proxyFactory.createClient(TodoService.class);
    }
}
```

接下来就可以使用代理对象了，测试：

```java
@Autowired
private TodoService service;

@Test
void testGetTodoById() {
    Todo todo = service.getTodoById(1);
    System.out.println(todo);
}
```

输出结果：

```java
Todo(userId=1, id=1, title=delectus aut autem, completed=false)
```

如果要创建一个todo，先声明方法：

```java
@PostExchange("/todos/")
Todo addTodo(@RequestBody Todo todo);
```

+ 这个路径要去官方查看具体用法

然后测试：

```java
@Test
void testAddTodo() {
    Todo todo = new Todo(111, 222, "新加的一个todo", true);
    Todo newTodo = service.addTodo(todo);
    System.out.println(newTodo);
}
```

输出结果：

```java
Todo(userId=111, id=201, title=新加的一个todo, completed=true)
```

删除和修改用法都差不多。

# Http 服务接口的方法定义

@HttpExchange 注解用于声明接口作为 HTTP 远程服务。在方法、类级别使用。通过注解属性以及方法的参数设置 HTTP 请求的细节。

快捷注解简化不同的请求方式

+ GetExchange
+ PostExchange
+ PutExchange
+ PatchExchange
+ DeleteExchange

@GetExchange 就是@HttpExchange 表示的 GET 请求方式：

```java
@HttpExchange(method = "GET")
```

作为 HTTP 服务接口中的方法允许使用的参数列表：

![image-20240709171757964](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091717029.png)

比如：

```java
@HttpExchange("/todos/{id}")
Todo getTodoById(URI uri, HttpMethod method, @PathVariable("id") Integer id);
```

+ uri会覆盖掉"/todos/{id}"
+ method会指定该HttpExchange是GET还是其他

接口中方法返回值:

![image-20240709171816635](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091718705.png)

反应式的相关的返回值包含 Mono<Void>,Mono<HttpHeaders>,Mono<T>,Flux<T>Mono<ResponseEntity<Void>>,Mono<ResponseEntity<T>>,Mono<ResponseEntity<Flux<T>>。

# 组合使用注解

@HttpExchange ， @GetExchange 等可以组合使用。

这次使用 Albums 远程服务接口，查询 Albums 信息。

![image-20240709172522057](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407091725102.png)

创建实体类Album：

```java
@NoArgsConstructor
@AllArgsConstructor
@Data
public class Album {
    private Integer userId;
    private Integer id;
    private String title;
}
```

创建 AlbumsService 接口，接口声明方法，提供 HTTP 远程服务。在类级别应用@HttpExchange 接口，在方法级别使@HttpExchange ,@GetExchange 等：

```java
@HttpExchange(url = "https://jsonplaceholder.typicode.com/")
public interface AlbumService {
    @GetExchange(url = "albums/{id}")
    Album getAlbumById(@PathVariable Integer id);

    @PostExchange("albums/")
    Album createAlbum(@RequestBody Album album);

    @DeleteMapping("albums/{id}")
    void deleteAlbum(@PathVariable Integer id);

    @PutExchange("albums/{id}")
    Album updateAlbum(@PathVariable Integer id);
}
```

接着还是要创建代理对象：

```java
@Bean
public AlbumService albumService() {
    WebClient webClient = WebClient.create();
    HttpServiceProxyFactory factory = HttpServiceProxyFactory
        .builder(WebClientAdapter.forClient(webClient)).build();
    return factory.createClient(AlbumService.class);
}
```

测试：

```java
@Autowired
AlbumService albumService;
@Test
void testGetAlbum() {
    Album album = albumService.getAlbumById(1);
    System.out.println(album);
}
```

输出结果：

```java
Album(userId=1, id=1, title=quidem molestiae enim)
```

# Java Record

测试 Java Record 作为返回类型，由框架的 HTTP 代理转换应该内容为 Record 对象.

创建record：

```java
public record AlbumRecord(Integer id, Integer userId, String title) {
}
```

创建服务方法：

```java
@GetExchange(url = "albums/{id}")
AlbumRecord getAlbumRecord(@PathVariable Integer id);
```

测试：

```java
@Autowired
AlbumService albumService;
@Test
void testGetAlbum() {
    AlbumRecord album = albumService.getAlbumRecord(1);
    System.out.println(album);
}
```

输出结果：

```java
AlbumRecord[id=1, userId=1, title=quidem molestiae enim]
```

# 定制 HTTP 请求服务

设置 HTTP 远程的超时时间， 异常处理.

在创建接口代理对象前，先设置 WebClient 的有关配置。

定制http服务，就是定制代理对象：

```java
@Bean
public AlbumsService albumsService(){
    HttpClient httpClient = HttpClient.create()
        .option(ChannelOption.CONNECT_TIMEOUT_MILLIS, 30000)
        //连接超时
        .doOnConnected(conn -> {
            conn.addHandlerLast(new ReadTimeoutHandler(10)); //读超时
            conn.addHandlerLast(new WriteTimeoutHandler(10)); //写超时
        });
    WebClient webClient = WebClient.builder()
        .clientConnector(new ReactorClientHttpConnector(httpClient))
        //定制 4XX,5XX 的回调函数
        .defaultStatusHandler(HttpStatusCode::isError,clientResponse -> {
            System.out.println("******WebClient 请求异常********");
            return
                Mono.error(new RuntimeException(
                    "请求异常"+ clientResponse.statusCode().value()));
        }).build();
    HttpServiceProxyFactory proxyFactory
        = HttpServiceProxyFactory.builder(
        WebClientAdapter.forClient(webClient)).build();
    return proxyFactory.createClient(AlbumsService.class);
}
```

