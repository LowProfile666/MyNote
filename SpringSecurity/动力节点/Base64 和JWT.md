# 1 base64编码

## 1.1 什么是Base64

所谓Base64，就是说选出64个字符：小写字母a-z、大写字母A-Z、数字0-9、符号"+"、"/"（再加上作为垫字的"="，实际上是使用65个字符），作为一个基本字符集。然后，其他所有符号都转换成这个字符集中的字符。

base64的编码规则是，从左到右，每三个字节变成四个字节（这四个字节就是base64编码的内容），1个g的内容经过base64编码后会变成1.33g。

## 1.2 linux base64命令

在git bash中测试。

```bash
echo "hello"
```

这会输出hello，且会有一个换行：

![image-20240715202258936](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152022964.png)

如果不想要有换行，可以使用-n参数：

```bash
echo -n "hello"
```

![image-20240715202330466](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152023492.png)

### 1.2.1 Linux下用base64命令编解码字符串

编码：使用管道符号进行base64编码：

```bash
echo -n "hello" | base64
```

输出：

```bash
aGVsbG8=

```

![image-20240715202439360](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152024387.png)

如果没有-n参数，那么就会对”hello“和一个换行符进行编码：

![image-20240715202534183](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152025210.png)

`=` 等号可能会出现在base64编码的末尾，只能出现在末尾。

+ 没有等号：文件的大小除以3后，余数为0
+ 二个等号：文件的大小除以3后，余数为1，多出了一个字节，还差两个字节
+ 一个等号：文件的大小除以3后，余数为2，多出了两个字节，还差一个字节

解码：使用 -d 参数

```bash
echo -n "aGVsbG8=" | base64 -d
```

结果：

```bash
hello
```

![image-20240715203115281](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152031320.png)

备注：

+ echo 命令是带换行符的

+ echo -n 不换行输出

### 1.2.2 base64 编解码文件

将一个图片base64编码为一个txt文本：

```bash
$ base64 avatar14.jpg > 1.txt
```

![image-20240715203537262](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152035303.png)

将这个1.txt解码回一个图片：

```bash
base64 -d 1.txt > abc.jpg
base64 -d 1.txt > abc.png
```

![image-20240715203843305](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152038391.png)

## 1.3 Base64和Base64Url 的区别

Base64Url是一种在Base64的基础上编码形成新的编码方式，为了编码能在网络中安全顺畅传输，需要对Base64进行的编码，特别是互联网中。

Base64Url 编码的流程：

1、明文使用BASE64进行编码   

2、在Base64编码的基础上进行以下的处理：    

+ 去除尾部的"="    
+ 把"+"替换成"-"    
+ 斜线"/"替换成下划线"_"  

# 2 跨域认证问题和JWT 实现登录原理图

## 2.1 跨域认证问题

互联网服务离不开用户认证。一般流程是下面这样。

+ 用户向服务器发送用户名和密码。

+ 服务器验证通过后，在当前对话（session）里面保存相关数据，比如用户角色、登录时间等等。

+ 服务器向用户返回一个 jsession_id，写入用户的 Cookie。

+ 用户随后的每一次请求，都会通过 Cookie，将 session_id 传回服务器。

+ 服务器收到 session_id，找到前期保存的数据，由此得知用户的身份。

这种模式的问题在于，扩展性（scaling）不好。单机当然没有问题，如果是服务器集群，或者是跨域的服务导向架构，就要求 session 数据共享，每台服务器都能够读取 session。

举例来说，A 网站和 B 网站是同一家公司的关联服务。现在要求，用户只要在其中一个网站登录，再访问另一个网站就会自动登录，请问怎么实现？

**一种解决方案是 session** **数据持久化**，写入数据库或别的持久层。各种服务收到请求后，都向持久层请求数据。这种方案的优点是架构清晰，缺点是工程量比较大。另外，持久层万一挂了，就会单点失败。

**另一种方案是服务器索性不保存 session** **数据了，所有数据都保存在客户端，每次请求都发回服务器**。JWT 就是这种方案的一个代表。 服务器不存数据，客户端存，服务器解析就行了

## 2.2 JWT 实现登录原理图

![img](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152042249.jpg)

说明：

JWT只通过算法实现对Token合法性的验证，不依赖数据库，Memcached的等存储系统，因此可以做到跨服务器验证，只要密钥和算法相同，不同服务器程序生成的Token可以互相验证。

# 3 JWT学习

## 3.1 简介

JSON Web Token（JWT）是一个开放标准（RFC 7519），它定义了一种紧凑且独立的方式，用于在各方之间作为JSON对象安全地传输信息。 此信息可以通过数字签名进行验证和信任。 JWT可以使用密钥（使用HMAC算法）或使用RSA或ECDSA的公钥/私钥对进行签名。

+ 官方网址：https://jwt.io/

+ 调试页面：https://jwt.io/

+ 学习文档：https://jwt.io/introduction/

在官网上有一个案例：

![image-20240715205508283](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152055355.png)

左边的就是jwt字符串，他的内容就是右边的三个json字符串，通过两个 `.` 来分割成三个部分，比如第一部分解码后就是右边第一个json字符串：

```bash
echo -n "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9" | base64 -d
```

输出：

```bash
{"alg":"HS256","typ":"JWT"}
```

![image-20240715205645550](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152056585.png)

## 3.2 用途

+ 授权：这是我们使用JWT最广泛的应用场景。一次用户登录，后续请求将会包含JWT，对于那些合法的token，允许用户连接路由，服务和资源。目前JWT广泛应用在SSO（Single Sign On）(单点登录)上。因为他们开销很小并且可以在不同领域轻松使用。

+ 信息交换：JSON Web Token是一种在各方面之间安全信息传输的好的方式 因为JWT可以签名 - 例如，使用公钥/私钥对 - 您可以确定发件人是他们所说的人。 此外，由于使用标头和有效负载计算签名，您还可以验证内容是否未被篡改。

## 3.3 JWT组成

一个JWT由三部分组成，各部分以点分隔：

+ Header(头部）-----base64Url编码的Json字符串

+ Payload(载荷）---base64url编码的Json字符串

+ Signature(签名)---使用指定算法，通过Header和Playload加盐计算的字符串

一个JWT看起来像下面这样：

```bash
xxxxx.yyyyy.zzzzz
```

```bash
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c
```

### 3.3.1 Header

此部分有两部分组成：

+ 一部分是token的类型，目前只能是JWT

+ 另一部分是签名算法，比如HMAC 、 SHA256 、 RSA

### 3.3.2 Payload

token的第二部分是payload（有效负载），其中包含claims（声明）。Claims是关于一个实体（通常是用户）和其他数据类型的声明。

claims有三种类型：registered,public,and private claims。

+ Registered（已注册的声明）：这些是一组预定义声明，不是强制性的，但建议使用，以提供一组有用的，可互操作的声明。 其中一些是：iss（发行人），exp（到期时间），sub（主题），aud（观众）and others。（请注意，声明名称只有三个字符，因为JWT意味着紧凑。）

  > JWT 规定了7个官方字段，供选用。
  >
  > + iss (issuer)：签发人
  >
  > + **exp (expiration time)：过期时间**
  >
  > + sub (subject)：主题
  >
  > + aud (audience)：受众
  >
  > + nbf (Not Before)：生效时间
  >
  > + **iat (Issued At)：签发时间**
  >
  > + jti (JWT ID)：编号
  >
  > 除了官方字段，你还可以在这个部分定义私有字段，下面就是一个例子。
  >
  > ```json
  > {
  >  "sub": "1234567890",
  >  "name": "John Doe",
  >  "admin": true
  > }
  > ```
  >
  > 注意，JWT 默认是不加密的，任何人都可以读到，所以不要把**秘密信息（密码，手机号等）**放在这个部分。
  >
  > 这个 JSON 对象也要使用 Base64URL 算法转成字符串。

+ Public(公开声明)：这些可以由使用JWT的人随意定义。 但为避免冲突，应在IANA JSON Web Token Registry中定义它们，或者将其定义为包含防冲突命名空间的URI。

+ private (私人声明)：这些声明是为了在同意使用它们的各方之间共享信息而创建的，并且既不是注册声明也不是公开声明。

### 3.3.3 Signature（保证数据安全性的）

Signature 部分是对前两部分的签名，**防止数据篡改**。

首先，需要指定一个**密钥（secret）**。这个密钥只有服务器才知道，不能泄露给用户。然后，使用 Header 里面指定的签名算法（默认是 HMAC SHA256），按照下面的公式产生签名。

```
HMACSHA256(
  base64UrlEncode(header) + "." +
  base64UrlEncode(payload),
  secret)
```

算出签名以后，把 Header、Payload、Signature 三个部分拼成一个字符串，每个部分之间用"点"（.）分隔，就可以返回给用户。

## 3.4 JWT 的使用方式【重点】

客户端收到服务器返回的 JWT，可以储存在 Cookie 里面，也可以储存在 localStorage。

此后，客户端每次与服务器通信，都要带上这个 JWT。你可以把它放在 Cookie 里面自动发送，但是这样不能跨域，所以更好的做法是放在 HTTP 请求的头信息Authorization字段里面。

Authorization: Bearer jwt

另一种做法是，跨域的时候，JWT 就放在 POST 请求的数据体里面。

## 3.5 JWT 的几个特点

1. **JWT的加密性**：
   - JWT默认不加密，但可以加密。生成原始Token后，可以使用密钥对其进行加密。
2. **JWT的数据安全性**：
   - 由于JWT不加密，不应将敏感数据直接写入JWT。
   - 一旦JWT泄露，任何人都可以获得令牌的所有权限，因此应设置较短的有效期。
3. **JWT的用途**：
   - JWT可用于认证和信息交换，有效使用JWT可以减少服务器查询数据库的次数。
4. **JWT的缺点**：
   - 由于服务器不保存session状态，JWT无法在运行时废止或更改权限，除非部署额外的逻辑来处理登出问题。
5. **JWT与密码修改**：
   - 修改密码后，通常需要清空浏览器保存的Token，因为服务端不保留Token信息。
6. **JWT的无状态特性**：
   - 服务端不保存Token信息，使得JWT具有无状态特性。如果需要废止Token或更改权限，需要将无状态转变为有状态，即后端需要保存Token信息。
7. **JWT的有效期**：
   - 通常设置为较短时间，例如2小时，以减少盗用风险。
8. **JWT的传输安全**：
   - 应使用HTTPS协议（443端口）而非HTTP（80端口）来传输JWT，以保证传输过程的安全。
9. **JWT的认证信息**：
   - JWT包含了用户名称和权限信息，一旦解析，即认为用户是可认证的。
10. **JWT的登出问题**：
    - 由于后端无状态，JWT一旦签发，在到期之前始终有效，除非有额外的登出逻辑。

# 4 Java类库

使用其他人写好的类库，在用户认证通过后，调用某个方法，创建一个jwt，返回给客户端；客户拿到jwt后，访问服务器，那么服务器就要调用某个方法拿到用户的jwt并进行校验，校验成功后就可以从jwt的payload部分中获取信息。

所以要做的事就三个

+ 创建jwt
+ 校验jwt
+ 从jwt的payload中获取数据

在官网中可以看到其他人编写的类库：

![image-20240715213014873](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152130974.png)

选择的时候要看它的星数和支持的功能：

![image-20240715213155397](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152131451.png)



# 5 java中使用jwt

## 5.1 准备

创建一个新项目，就需要引入jwt的依赖：

```xml
<!-- 添加jwt的依赖 -->
<!-- https://mvnrepository.com/artifact/com.auth0/java-jwt -->
<dependency>
    <groupId>com.auth0</groupId>
    <artifactId>java-jwt</artifactId>
    <version>4.4.0</version>
</dependency>
```

## 5.2 创建jwt工具类

创建com.zsm.utils.JwtUtil。

### 5.2.1 创建jwt

```java
public class JwtUtil {
    // 设置密钥
    public static final String secret = "zsm666";
    
    public String createJwt(String userId, String userName, List<String> userAuth) {
        // 设置jwt的头部
        Map<String, Object> headerClaims = new HashMap<>();
        headerClaims.put("alg", "HS256");
        headerClaims.put("typ", "jwt");

        return JWT.create()  // 创建要给jwt
                .withHeader(headerClaims)  // 设置头部，头部需要的是一个map
                .withIssuer("zsm")  // 设置payload中的声明：签发人
                .withIssuedAt(new Date())  // 设置payload中的声明：签发时间
                .withExpiresAt(new Date(new Date().getTime() + 1000 * 60 * 60 * 2))  // 设置过期时间为2小时后
                .withClaim("userId", userId)  // 自定义数据：用户id
                .withClaim("userName", userName)  // 自定义数据：用户名
                .withClaim("userAuth", userAuth)  // 自定义数据：用户权限
                .sign(Algorithm.HMAC256(secret));  // 签名，使用HS256进行签名，使用secret作为密钥
    }
}
```

+ 像withIssuer是官方已规定的字段：

  ![image-20240715215915905](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407152159956.png)

然后可以直接在当前类中创建一个主方法用来测试：

```java
public static void main(String[] args) {
    JwtUtil util = new JwtUtil();
    List<String> list = Arrays.asList("student:query", "student:add");
    String jwt = util.createJwt("1", "obama", list);
    System.out.println(jwt);
}
```

输出结果：

```java
eyJ0eXAiOiJqd3QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJ6c20iLCJpYXQiOjE3MjEwNTIxMTgsImV4cCI6MTcyMTA1OTMxOCwidXNlcklkIjoiMSIsInVzZXJOYW1lIjoib2JhbWEiLCJ1c2VyQXV0aCI6WyJzdHVkZW50OnF1ZXJ5Iiwic3R1ZGVudDphZGQiXX0.rCmQHQhlgDiqGX_iMaNpcSwtodO6IsyCG_GHAXMxYuU
```

### 5.2.2 校验jwt

签名时用的什么算法，校验时就用什么算法。

```java
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
```

用主方法测试：将上一次测试生成的jwt拿来校验，该jwt的过期时间是2两小时所以还没有过期，应该校验正确

```java
public static void main(String[] args) { 	System.out.println(util.verifyToken("eyJ0eXAiOiJqd3QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJ6c20iLCJpYXQiOjE3MjEwNTIxMTgsImV4cCI6MTcyMTA1OTMxOCwidXNlcklkIjoiMSIsInVzZXJOYW1lIjoib2JhbWEiLCJ1c2VyQXV0aCI6WyJzdHVkZW50OnF1ZXJ5Iiwic3R1ZGVudDphZGQiXX0.rCmQHQhlgDiqGX_iMaNpcSwtodO6IsyCG_GHAXMxYuU"));
}
```

输出结果：

```java
token验证正确
true
```

现在重新创建一个token，设置过期时间为3秒，然后校验：

```java
public static void main(String[] args) throws InterruptedException {
    JwtUtil util = new JwtUtil();
    List<String> list = Arrays.asList("student:query", "student:add");
    String jwt = util.createJwt("1", "obama", list);
    System.out.println(jwt);

    Thread.sleep(3000);

    System.out.println(util.verifyToken(jwt));
}
```

输出结果：

```java
eyJ0eXAiOiJqd3QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJ6c20iLCJpYXQiOjE3MjEwNTM1NjAsImV4cCI6MTcyMTA1MzU2MiwidXNlcklkIjoiMSIsInVzZXJOYW1lIjoib2JhbWEiLCJ1c2VyQXV0aCI6WyJzdHVkZW50OnF1ZXJ5Iiwic3R1ZGVudDphZGQiXX0.m-T85PuBrvRED7VqpupXT8bKBOSPUejwgANAez9O6Kk
token验证不正确
false
```

### 5.2.3 获取jwt中的数据

还是要先校验jwt，校验成功后会返回一个对象，通过该对象可以获取jwt中的数据：

```java
// 创建校验器
JWTVerifier verifier = JWT.require(Algorithm.HMAC256(secret)).build();
// 校验
DecodedJWT decodedJWT = verifier.verify(rawJwt);
// 可以获取jwt中的信息
String userId = decodedJWT.getClaim("userId").asString();
String userName = decodedJWT.getClaim("userName").asString();
List<String> userAuth = decodedJWT.getClaim("userAuth").asList(String.class);
System.out.println(userId);
System.out.println(userName);
System.out.println(userAuth);
```

输出结果：

```java
obama
[student:query, student:add]
true
```

# 6 JWT的总结

**JWT就是一个加密的带用户信息的字符串**，没学习JWT之前，我们在项目中都是返回一个基本的字符串，然后请求时带上这个字符串，再从session或者redis中（共享session）获取当前用户，学过JWT以后我们可以把用户信息直接放在字符串返回给前端，然后用户请求时带过来，我们是在服务器进行解析拿到当前用户，这就是两种登录方式，这两种方式有各自的优缺点。























