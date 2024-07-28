为了避免 Redis 的单点故障问题，我们可以搭建一个Redis 集群，将数据备份到集群中的其它节点上。若一个 Redis 节点宕机，则由集群中的其它节点顶上。

# 5.1 主从集群搭建

Redis 的主从集群是一个“一主多从”的读写分离集群。集群中的 Master 节点负责处理客户端的读写请求，而 Slave 节点仅能处理客户端的读请求。只所以要将集群搭建为读写分离模式，主要原因是，对于数据库集群，写操作压力一般都较小，压力大多数来自于读操作请求。所以，只有一个节点负责处理写操作请求即可。

## 5.1.1    伪集群搭建与配置

在采用单线程IO 模型时，为了提高处理器的利用率，一般会在一个主机中安装多台Redis，构建一个 Redis 主从伪集群。当然，搭建伪集群的另一个场景是，在学习 Redis，而学习用 主机内存不足以创建多个虚拟机。

下面要搭建的读写分离伪集群包含一个Master 与两个 Slave。它们的端口号分别是：6380、 6381、6382。

### （1）  复制 redis.conf

```bash
mkdir cluster
cp redis.conf cluster/
cd cluster/
```

在 redis 安装目录中 mkdir 一个目录，名称随意。这里命名为 cluster。然后将 redis.conf文件复制到cluster 目录中。该文件后面会被其它配置文件包含，所以该文件中需要设置每个 Redis 节点相同的公共的属性。

### （2）  修改 redis.conf

在 redis.conf 中做如下几项修改：

#### A、masterauth

![image-20240728164317977](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281643020.png)

因为我们要搭建主从集群，且每个主机都有可能会是 Master，所以最好不要设置密码验证属性requirepass。如果真需要设置，一定要每个主机的密码都设置为相同的。此时每个配置文件中都要设置两个完全相同的属性：requirepass 与 masterauth。其中 requirepass 用于指定当前主机的访问密码，而 masterauth 用于指定当前 slave 访问 master 时向 master 提交的访问密码，用于让 master 验证自己身份是否合法。

比如，现在有一个一主三从的集群：

![image-20240728165011605](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281650648.png)

现在BCD三台redis都可以使用密码111去访问A redis，如果A坏了，现在要从BCD中选出一个主redis，假设选D，但是会因为BC的masterauth配置的密码和D的requirepass密码不一致，导致从redis不能访问主redis。所以如果要设置密码，就所有redis主机密码一致。

#### B、 repl-disable-tcp-nodelay

![image-20240728165420029](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281654079.png)

该属性用于设置是否禁用TCP 特性 tcp-nodelay。设置为 yes 则禁用 tcp-nodelay，此时 master 与slave 间的通信会产生延迟，但使用的 TCP 包数量会较少，占用的网络带宽会较小。相反，如果设置为 no，则网络延迟会变小，但使用的 TCP 包数量会较多，相应占用的网络带宽会大。

> tcp-nodelay：为了充分复用网络带宽，TCP 总是希望发送尽可能大的数据块。为了达到该目的，TCP 中使用了一个名为 Nagle 的算法。
>
> Nagle 算法的工作原理是，网络在接收到要发送的数据后，并不直接发送，而是等待着数据量足够大（由 TCP 网络特性决定）时再一次性发送出去。这样，网络上传输的有效数据比例就得到了大大提升，无效数据传递量极大减少，于是就节省了网络带宽，缓解了网络压力。
>
> tcp-nodelay 则是 TCP 协议中 Nagle 算法的开头。

### （3）  新建 redis6380.conf

新建一个redis 配置文件，该配置文件中的 Redis 端口号为 6380：

```
include redis.conf
pidfile /var/run/redis_6380.pid
port 6380
dbfilename dump6380.rdb
appendfilename appendonly6380.aof
relica-priority 90

logfile logs/access6380.log
```

+ relica-priority是用来设置优先级的，当主redis挂了之后，会从从redis中选举出一个redis做主，就是根据这个值来判断，值越小，优先级越高，默认值是100

### （4）  再复制出两个 conf 文件

再使用 redis6380.conf 复制出两个 conf 文件：redis6381.conf 与redis6382.conf。然后修改其中的内容。

使用替换：

![image-20240728182947085](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281829156.png)

redis6381.conf：

```
include redis.conf
pidfile /var/run/redis_6381.pid
port 6381
dbfilename dump6381.rdb
appendfilename appendonly6381.aof
relica-priority 90

logfile logs/access6381.log
```

redis6382.conf：

```
include redis.conf
pidfile /var/run/redis_6382.pid
port 6382
dbfilename dump6382.rdb
appendfilename appendonly6382.aof
relica-priority 90

logfile logs/access6382.log
```

### （5）  启动三台 Redis

分别使用redis6380.conf、redis6381.conf 与redis6382.conf 三个配置文件启动三台Redis。

```bash
redis-server redis6380.conf
redis-server redis6381.conf
redis-server redis6382.conf
```

![image-20240728183809974](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281838019.png)

### （6）  设置主从关系

再打开三个会话框，分别使用客户端连接三台 Redis。然后通过 slaveof 命令，指定 6380的 Redis 为 Master。

使用redis-cli连接redis时使用-p参数指定端口号：

```bash
redis-cli -p 6380
```

使用info replication命令查看主机信息：

![image-20240728184113097](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281841149.png)

表示现在的主机是master，没有slave。现在三台主机是独立的。

现在在6381和6382的连接中，使用slaveof命令，将这两个redis设为6380的从：

```bash
slaveof 127.0.0.1 6380
```

![image-20240728184351010](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281843078.png)

### （7）  查看状态信息

通过 info replication 命令可查看当前连接的Redis 的状态信息。

查看6380的：

![image-20240728184459443](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281844502.png)

现在在主redis中设置一些数据，从redis中可以直接获取到这些数据：

![image-20240728184817409](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281848463.png)

如果在从redis中进行写操作：

![image-20240728184909945](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281849986.png)

如果挂掉一个slave，查看master的状态：

![image-20240728185003285](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281850346.png)

如果再将挂了的slave重启，这个slave就不再是之前的slave了，而是一个新的master：

![image-20240728185226365](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407281852485.png)

仍然需要使用slaveof重新设置主从关系。