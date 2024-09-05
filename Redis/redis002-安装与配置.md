这里是要将 Redis 安装到 Linux 系统中。

# 2.1 Redis 的安装

## 2.1.1 克隆并配置主机

右键单击虚拟机，可以选择克隆虚拟机：

![image-20240719160335593](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191603639.png)

然后选择克隆的类型和位置即可，克隆完成后，是一台新的和之前一样的虚拟机，所以可以修改一下这个新虚拟机的一些配置：

+ 修改主机名：/etc/hostname

然后使用xshell连接虚拟机，如果想要使用主机名连接虚拟机，可以在本机的hosts文件中添加地址映射。

## 2.1.2 安装前的准备工作

（1） 安装 gcc

```bash
yum -y install gcc gcc-c++
```

由于 Redis 是由 C/C++语言编写的，而从官网下载的 Redis 安装包是需要编译后才可安装的，所以对其进行编译就必须要使用相关编译器。对于 C/C++语言的编译器，使用最多的是gcc 与 gcc-c++，而这两款编译器在 CentOS7 中是没有安装的，所以首先要安装这两款编译器。

GCC：GNU Compiler Collection，GNU 编译器集合。

（2） 下载 Redis

redis 的官网为： http://redis.io。点击下面的链接可以直接进行下载。

https://download.redis.io/redis-stable.tar.gz

（3） 上传到 Linux

将下载好的压缩包上传到 Linux 的/opt/tools 目录中。

## 2.1.3 安装 Redis

（1） 解压 Redis

将 Redis 解压到/opt/apps 目录中。 

将 Redis 解压包目录更名为 redis（不更名也无所谓）。

（2） 编译

编译过程是根据 Makefile 文件进行的，而 Redis 解压包中已经存在该文件了。所以可以直接进行编译了。

进入到解压目录中，然后执行编译命令 make。

```bash
make
```

当看到如下提示时，表示编译成功。

![image-20240719170520075](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191705145.png)

（3） 安装

在 Linux 中对于编译过的安装包执行 make install 进行安装

```bash
make install
```

![image-20240719170556431](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191705463.png)

可以看到，共安装了三个组件：redis 服务器、客户端与一个性能测试工具 benchmark。

（4） 查看 bin 目录

安装完成后，打开/usr/local/bin 目录，可以看到出现了很多的文件。

```bash
ls -l /usr/local/bin
```

![image-20240719170717568](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191707606.png)

通过 echo $PATH 可以看到，/usr/local/bin 目录是存在于该系统变量中的，这样这些命令就可以在任意目录中执行了。

```bash
echo $PATH
```

![image-20240719170828973](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191708007.png)

## 2.1.4 Redis 启动与停止

（1） 前台启动

在任意目录执行 redis-server 命令即可启动 Redis。这种启动方式会占用当前命令行窗口。

```bash
redis-server
```

![image-20240719172429774](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191724864.png)

再开启一个会话窗口，可以查看到当前的 Redis 进程，默认端口号为 6379。

> 6379在是手机按键上MERZ对应的号码，而MERZ取自意大利歌女Alessia Merz的名字。MERZ长期以来被Redis作者antirez及其朋友当作愚蠢的代名词。后来Redis作者在开发Redis时就选用了这个端口。
>
> ——Alessia Merz 是一位意大利舞女、女演员。 Redis 作者 Antirez 早年看电视节目，觉得 Merz 在节目中的一些话愚蠢可笑，Antirez 喜欢造“梗”用于平时和朋友们交流，于是造了一个词 “MERZ”，形容愚蠢，与 “stupid” 含义相同。
> ——后来 Antirez 重新定义了 “MERZ” ，形容”具有很高的技术价值，包含技艺、耐心和劳动，但仍然保持简单本质“。
> ——到了给 Redis 选择一个数字作为默认端口号时，Antirez 没有多想，把 “MERZ” 在手机键盘上对应的数字 6379 拿来用了。

```bash
ps aux | grep redis
```

![image-20240719172610577](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191726615.png)

通过 Ctrl + C 命令可以停止 Redis。

（2） 命令式后台启动

使用 nohub 命令，最后再添加一个&符，可以使要启动的程序在后台以守护进程方式运行。这样的好处是，进程启动后不会占用一个会话窗口，且其还会在当前目录，即运行启动命令的当前目录中创建一个 nohup.out 文件用于记录 Redis 的操作日志。

```bash
nohup redis-server &
```

![image-20240719173703696](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191737739.png)

（3） Redis 的停止

通过 redis-cli shutdown 命令可以停止 Redis。

（4） 配置式后台启动

使用 nohup 命令可以使 Redis 后台启动，但每次都要键入 nohup 与&符，比较麻烦。可以通过修改 Linux 中 Redis 的核心配置文件 redis.conf 达到后台启动的目的。redis.conf 文件在Redis 的安装目录根下。

![image-20240719173934061](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191739143.png)

将 daemonize 属性值由 no 改为 yes，使 Redis 进程以守护进程方式运行。

```bash
vi redis.conf
```

![image-20240719174134907](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191741949.png)

修改后再启动 Redis，就无需再键入 nohup 与&符了，但必须要指定启动所使用的 Redis配置文件。

```bash
redis-server /root/redis/redis/redis.conf
```

这是为什么呢？

使用 nohup redis-server &命令启动 Redis 时，启动项中已经设置好了 Redis 各个参数的默认值，Redis 会按照这些设置的参数进行启动。但这些参数是可以在配置文件中进行修改的，修改后，需要在启动命令中指定要加载的配置文件，这样，配置文件中的参数值将覆盖
原默认值。

Redis 已经给我们提供好了配置文件模板，是 Redis 安装目录的根目录下的 redis.conf 文件。由于刚刚对 redis.conf 配置文件做了修改，所以在开启 Redis 时需要显示指出要加载的配置文件。配置文件应紧跟在 redis-server 的后面。

## 2.1.5 在windows上以服务的形式运行

需要专门下载redis的windows版本，然后以服务的形式启动，在redis的安装目录下：

```
redis-server --service-install redis.windows.conf --loglevel verbose
```

取消以服务的形式：

```
redis-server --service-uninstall
```



# 2.2 连接前的配置

Redis 是一个内存数据库服务器，就像 MySQL 一样，对其操作也需要通过客户端进行。若要使远程主机上的客户端能够连接并访问到服务端的 Redis，则服务端首先要做如下配置。

## 2.2.1 绑定客户端 IP

Redis 可以通过修改配置文件redis.conf来限定可以访问自己的客户端 IP。

![image-20240719174935015](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191749058.png)

+ 127.0.0.1是ipv4的本机
+ -::1是ipv6的本机

以上是默认设置，只允许当前主机访问当前的 Redis，其它主机均不可访问。所以，如果不想限定访问的客户端，只需要将该行注释掉即可。

![image-20240719175012882](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191750924.png)

## 2.2.2 关闭保护模式

默认保护模式是开启的，其只允许本机的客户端访问，即只允许自己访问自己。但生产中应该关闭，以确保其它客户端可以连接 Redis，将redis.conf中的protected-mode的值改为no：

![image-20240719175126316](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407191751361.png)

## 2.2.3 设置访问密码

为 Redis 设置访问密码，可以对要读/写 Redis 的用户进行身份验证。没有密码的用户可以登录 Redis，但无法访问。

（1） 密码设置

访问密码的设置位置在 redis.conf 配置文件中。默认是被注释掉的，没有密码。

![image-20240719224516391](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192246668.png)

设置一个密码：

![image-20240719225018600](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192250643.png)

没有通过密码登录的用户，无法读/写 Redis。比如，在注释了requirepass的情况下，使用redis-cli连接，可以操作redis：

![image-20240719225532870](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192255913.png)

在没有注释requirepass的情况下，设置了密码，没有密码登录的话，不能操作redis：

![image-20240719225840769](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192258813.png)

需要使用密码登录：`auth 密码`

![image-20240719225941716](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192259763.png)

使用密码登录过后，可以在客户端里关闭redis，直接输入shutdown：

![image-20240719230147879](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192301918.png)

（2） 使用密码

对于密码的使用，有两种方式：登录时未使用密码，则访问时先输入密码；登录时直接使用密码登录，访问时无需再输入密码。

A、 登录时未使用密码，登录后使用密码：

![image-20240719230409295](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192304335.png)

B、 登录时使用密码：

![image-20240719230511904](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192305944.png)

C、 退出时使用密码，不使用密码退出不了：

![image-20240719230633934](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192306980.png)

## 2.2.4 禁止/重命名命令

后面要学习两个非常危险的命令：flushal 与 flushdb。它们都是用于直接删除整个 Redis数据库的。若让用户可以随便使用它们，可能会危及数据安全。Redis 可以通过修改配置文件来禁止使用这些命令，或重命名这些命令。以下配置，禁用了 flushall 与 flushdb 命令。

```
rename-command flushall ""
rename-command flushdb ""
```

+ 将flushall和flushdb这两个命令重命名为空字符串，导致两个命令失效

当然，在学习过程中暂时不禁用它们，注释掉：

![image-20240719231012248](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407192310291.png)

##  2.2.5 启动 Redis

当然，若要使客户端能够连接 Redis，则必须开启服务端的 Redis。

```bash
redis-server /root/redis/redis/redis.conf
```

# 2.3 Redis 客户端分类

Redis 客户端也像 MySQL 客户端一样有多种类型：命令行客户端、图形界面客户端、Java代码客户端。

## 2.3.1 命令行客户端

Redis 提供了基本的命令行客户端。打开命令行客户端的命令为 redis-cli。

```bash
redis-cli -h 192.168.231.130 -p 6279
```

+ -h：指定要连接的 Redis 服务器的 IP。
+ -p：指定要连接的 Redis 的端口号。
+ -a：指定密码
+ 若连接的是本机 Redis，且端口号没有改变，保持默认的 6379，则-h 与-p 选项可以省略不写。

## 2.3.2 图形界面客户端

（1） Redis Desktop Manager

Redis 的图形界面客户端很多，其中较出名的是 Redis Desktop Manager 的客户端。不过，该软件原来是免费软件，从 0.8.8 版本后变为了商业化收费软件。

官网为：https://resp.app/（原来是 http://redisdesktop.com）。

使用软件连接redis时，需要打开服务器的6379端口：

```bash
# 开放端口
firewall-cmd --add-port=6379/tcp --permanent
# 重启配置
firewall-cmd --reload
# 查看是否开启
redifirewall-cmd --list-ports
```

![image-20240720092329898](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407200923073.png)

（2） RedisPlus

RedisPlus 是为 Redis 可视化管理开发的一款开源免费的桌面客户端软件，支持 Windows 、Linux、Mac 三大系统平台，RedisPlus 提供更加高效、方便、快捷的使用体验，有着更加现代化的用户界面风格。

RedisPlus 的官网地址为 https://gitee.com/MaxBill/RedisPlus。

## 2.3.3 Java 代码客户端

所谓 Java 代码客户端就是一套操作 Redis 的 API，其作用就像 JDBC 一样，所以 Java 代码客户端其实就是一个或多个 Jar 包，提供了对 Redis 的操作接口。

对 Redis 操作的 API 很多，例如 jdbc-redis、jredis 等，但最常用也是最有名的是 Jedis。

# 2.4 Redis 配置文件详解

Redis 的核心配置文件 redis.conf 在安装根目录下，默认包含 2000 多行。这些内容根据功能被划分为了很多部分。下面将一些重要部分进行介绍。

首先，该配置文件是分了很多模块的：

![image-20240720093706674](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407200937773.png)

## 2.4.1 基础说明

![image-20240720094003014](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407200940082.png)

这部分主要是给出一些说明，包含三部分意思：

+ 第 1-6 行用于说明，如果要启动 Redis，需要指出配置文件的路径。
+ 第 8-16 行用于说明当前配置文件中可以使用的的容量单位及意义。
+ 第 18 行用于说明这些容量单位没有大小写之分。

## 2.4.2 includes

![image-20240720094123686](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407200941784.png)

指定要在当前配置文件中包含的配置文件。

这样做的目的主要是便于配置信息管理：可以将不同场景的配置都进行单独定义，然后在当前核心配置文件中根据不同场景选择包含进不同的配置文件。

如果想要导入的配置文件的属性覆盖原配置文件的属性，最好是在该配置文件中的最后一行使用include导入。

比如在和redis.conf同级目录下有一个test.conf：

```
port 6666
daemonize no
```

只指定了一个端口号的属性和以前台方式的运行，然后在redis.conf中的最后一行，通过include将这个test配置文件导入：

```
include test.conf
```

现在重启redis服务：

```bash
redis-server redis.conf
```

![image-20240720095926664](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407200959766.png)

可以看到redis服务启动变成了前台启动，且端口号为6666，这都是test配置文件中的。

## 2.4.3 modules

![image-20240720100201673](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201002742.png)

Redis 配置文件中可以通过加载不同的第三方模块，来增强、扩展 Redis 的功能。

so 是linux里面的一个函数库，类似于windows上的dll。

## 2.4.4 network

![image-20240720100525134](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201005236.png)

Network 配置模块是比较重要的部分，主要进行网络相关的配置。其中较重要的有：

### （1） bind

指定可以访问当前 Redis 服务的客户端 IP，默认只允许本地访问，即当前 Redis 自己访问自己。为了使所有其它客户端都可访问，一般要将其注释掉。

![image-20240720100559339](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201005399.png)

### （2） protected-mode

默认保护模式是开启的。其只允许本机的客户端访问，即只允许自己访问自己。但生产中应该关闭，以确保其它客户端可以连接 Redis。

![image-20240720100614586](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201006646.png)

### （3） port

Redis 监听的连接端口号，默认 6379。

![image-20240720100628881](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201006940.png)

### （4） tcp-backlog

![image-20240720100646251](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201006312.png)

tcp-backlog 是一个 TCP 连接的队列，其主要用于解决高并发场景下客户端**慢连接**问题。这里设置的值就是这个队列的长度。该队列与 TCP 连接的三次握手有关。不同的 Linux 内核，backlog 队列中存放的元素（客户端连接）类型是不同的。

+ Linux 内核 2.2 版本之前，该队列中存放的是已完成了第一次握手的所有客户端连接，其中就包含已完成三次握手的客户端连接。当然，此时的 backlog 队列中的连接也具有两种状态：未完成三次握手的连接状态为 SYN_RECEIVED，已完成三次握手的连接状态为 ESTABLISHED。只有 ESTABLISHED 状态的连接才会被 Redis 处理。

+ Linux 内核 2.2 版本之后 TCP 系统中维护了两个队列：SYN_RECEIVED 队列与 ESTABLISHED队列。SYN_RECEIVED 队列中存放的是未完成三次握手的连接，ESTABLISHED 队列中存放的是已完成三次握手的连接。此时的 backlog 就是 ESTABLISHED 队列。

+ 查看 Linux 内核版本：

  ```bash
  uname -a
  cat /proc/version
  ```

TCP 中的 backlog 队列的长度在 Linux 中由内核参数 somaxconn 来决定。所以，在 Redis中该队列的长度由 Redis 配置文件设置与 somaxconn 来共同决定：取它们中的最小值。

查看当前 Linux 内核中 somaxconn 的值：

```bash
cat /proc/sys/net/core/somaxconn
```

生产环境下（特别是高并发场景下），backlog 的值最好要大一些，否则可能会影响系统性能。
修改/etc/sysctl.conf 文件，在文件最后添加如下内容：

```bash
net.core.somaxconn=4096
```

修改过后可以重启虚拟机，也可以通过执行如下命令来使新的修改生效：

```bash
sysctl -p
```

#### 关于三次握手、四次挥手

一个TCP连接是双工（双方可以互相发送消息）的，这个双工实际上是通过两个channel实现的：

![image-20240720105226873](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201052943.png)

一次TCP连接的三次握手（建立TCP连接）：

![image-20240720105240023](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201052094.png)

1. 客户端会向服务端发送连接请求，会将请求报文中的SYN置为1，并创建一个通信Channel
2. 服务端收到客户端的请求后，会给与响应，确认已经收到，会将报文中的ACK置为1，同时，服务端也要向客户端发送连接请求，将SYN置为1，并创建一个通信Channel
3. 客户端收到服务端的连接请求，也要确认收到，响应给服务端，将报文中的ACK置为1

这样两端已经建立好了连接，可以开始通信。

TCP的四次挥手（关闭TCP连接）：双方都可以主动关闭TCP连接，这里以客户端主动为例：

![image-20240720105250902](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201052976.png)

### （5） timeout

![image-20240720101121514](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201011576.png)

空闲超时。当客户端与 Redis 间的空闲时间超过该时长后，连接自动断开。单位秒。默认值为 0，表示永远不超时。

### （6） tcp-keepalive

![image-20240720101146119](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201011184.png)

该配置主要用于设置 Redis 检测与其连接的所有客户端的存活性时间间隔，单位秒。一般是在空闲超时 timeout 设置为 0 时进行配置。

## 2.4.5 general

### （1） daemonize

![image-20240720105633948](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201056010.png)

该配置可以控制 Redis 启动是否采用守护进程方式，即是否是后台启动。yes 是采用后台启动。

### （2） pidfile

![image-20240720105711813](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201057873.png)

该配置用于指定 Redis 运行时 pid 写入的文件，无论 Redis 是否采用守护进程方式启动，pid 都会写入到该配置的文件。

使用后台方式启动，然后查看这个 /var/run/redis_6379.pid 文件的内容，里面放的就是redis进程的id号：

![image-20240720110253827](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201102890.png)

注意，如果没有配置 pid 文件，不同的启动方式，pid 文件的产生效果是不同的：

+ 采用守护进程方式启动（后台启动，daemonize 为 yes）：pid 文件为/var/run/redis.pid。
+ 采用前台启动（daemonize 为 no）：不生产 pid 文件

### （3） loglevel

![image-20240720105811766](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201058831.png)

配置日志的级别。Redis 中共有四个级别，由低到高依次是：

+ debug：可以获取到很多的信息，一般在开发和测试时使用。
+ verbose：可以获取到很多不太有用的信息，但不像 debug 级别那么多。
+ notice：可以获取到在生产中想获取到的适当多的信息，默认级别。
+ warning：只记录非常重要/关键的信息。

### （4） logfile

![image-20240720105828033](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201058092.png)

指定日志文件。如果设置为空串，则强制将日志记录到标准输出设备（显示器）。

如果使用的是守护进程启动方式，设置为空串，则意味着会将日志发送到设备/dev/null（空设备）。也就是不显示。

### （5） databases

![image-20240720105854811](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201058872.png)

设置数据库的数量。默认数据库是 0 号数据库。可以使用 select <dbid>在每个连接的基础上选择一个不同的数据库，其中 dbid 是介于 0 和'databases'-1'之间的数字。

## 2.4.6 security

用户设置 ACL 权限、Redis 访问密码相关配置。

![image-20240720110758592](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201107660.png)

该模块中最常用的就是 requirepass 属性：

![image-20240720110843800](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201108864.png)

设置客户端访问密码。注释掉后则没有密码。

## 2.4.7 clients

![image-20240720111016944](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201110025.png)

该模块用于设置与客户端相关的属性，其中仅包含一个属性 maxclients。maxclients 用于设置 Redis 可并发处理的客户端连接数量，默认值为 10000。如果达到了该最大连接数，则会拒绝再来的新连接，并返回一个异常信息：已达到最大连接数。

注意，该值不能超过 Linux 系统支持的可打开的文件描述符最大数量阈值。查看该阈值的方式如下：

```bash
ulimit -n
```

修改该值，可以通过修改/etc/secutiry/limits.conf 文件（自己查）。

## 2.4.8 memory management

![image-20240720111914688](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201119755.png)

该配置可以控制最大可用内存及相关内容移除问题。

### （1） maxmemory

![image-20240720111931992](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201119057.png)

将内存使用限制设置为指定的字节数。当达到内存限制时，Redis 将根据选择的逐出策略 maxmemory-policy 尝试删除符合条件的 key。

如果不能按照逐出策略移除 key，则会给写操作命令返回 error，但对于只读的命令是没有影响的。

### （2） maxmamory-policy

![image-20240720111947510](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201119581.png)

该属性用于设置，当达到 maxmemory 时，Redis 将如何选择要移除的内容。当然，如果没有符合相应策略的内容要删除，则在执行写入命令时会给出 errors 的响应。Redis 中共支持 8 种移除策略：

+ volatile-lru：使用近似 LRU 算法移除，仅适用于设置了过期时间的 key。
+ allkeys-lru：使用近似 LRU 算法移除，可适用于所有类型的 key。
+ volatile-lfu：使用近似 LFU 算法移除，仅适用于设置了过期时间的 key。
+ allkeys-lfu：使用近似 LFU 算法移除，可适用于所有类型的 key。
+ volatile-random：随机移除一个 key，仅适用于设置了过期时间的 key。
+ allkeys-random：随机移除一个 key，可适用于所有类型的 key。
+ volatile-ttl：移除距离过期时间最近的 key。
+ noeviction：不移除任何内容，只是在写操作时返回一个错误，默认值。

### （3） maxmemory-samples

![image-20240720111959353](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201119417.png)

该属性用于指定挑选要删除的 key 的样本数量。样本的选择采用的是 LRU 算法，其不能修改。但从样本中再选择要移除的 key，则采用的是 maxmamory-policy 指定的策略。

### （4） maxmemory-eviction-tenacity

![image-20240720112012914](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201120982.png)

设置移除容忍度。数值越小表示容忍度越低，需要移除的数据移除延迟越小；数值越大表示容忍度越高，需要移除的数据移除延迟越大。

## 2.4.9 threaded I/O

![image-20240720123743321](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201237391.png)

该配置模块用于配置 Redis 对多线程 IO 模型的支持。

### （1） io-threads

![image-20240720123759216](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201237284.png)

该属性用于指定要启用多线程 IO 模型时，要使用的线程数量。查看当前系统中包含的 CPU 数量：

```bash
lscpu
```

### （2） io-threads-do-reads

![image-20240720124135513](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407201241584.png)

该属性用于启用多线程 IO 模型中的多线程处理读请求的能力。