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

## 5.1.2 分级管理

若 Redis 主从集群中的 Slave 较多时，它们的数据同步过程会对 Master 形成较大的性能压力。此时可以对这些 Slave 进行分级管理

![image-20240730134131375](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301341470.png)

设置方式很简单，只需要让低级别 Slave 指定其 slaveof 的主机为其上一级 Slave 即可。不过，上一级Slave 的状态仍为 Slave，只不过，其是更上一级的 Slave。

例如，指定 6382 主机为 6381 主机的 Slave，而 6381 主机仍为真正的 Master 的 Slave。

![image-20240730134718446](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301347509.png)

此时会发现，Master 的 Slave 只有 6381 一个主机。

如果此时master坏了，但是不影响其他两台slave主机，但是6381的主机还是无法向redis中写入数据：

![image-20240730135101084](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301351130.png)

## 5.1.3 容灾冷处理

在 Master/Slave 的 Redis 集群中，若 Master 出现宕机怎么办呢？有两种处理方式，一种是通过手工角色调整，使Slave 晋升为 Master 的冷处理；一种是使用哨兵模式，实现 Redis集群的高可用HA，即热处理。

无论 Master 是否宕机，Slave 都可通过 slaveof no one 将自己由 Slave 晋升为 Master。如果其原本就有下一级的 Slave，那么，其就直接变为了这些 Slave 的真正的 Master 了。而原来的 Master 也会失去这个原来的 Slave。

![image-20240730135351243](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301353298.png)

# 5.2 主从复制原理

## 5.2.1    主从复制过程

![主从复制过程.drawio](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301434350.png)

当一个 Redis 节点（slave 节点）接收到类似 slaveof 127.0.0.1 6380 的指令后直至其可以从 master 持续复制数据，大体经历了如下几个过程：

### （1）  保存 master 地址

当 slave 接收到 slaveof 指令后，slave 会立即将新的master 的地址保存下来。

### （2）  建立连接

slave 中维护着一个定时任务，该定时任务会尝试着与该 master 建立 socket 连接。如果连接无法建立，则其会不断定时重试，直到连接成功或接收到 slaveof no one 指令。

### （3）  slave 发送 ping 命令

连接建立成功后，slave 会发送 ping 命令进行首次通信。如果 slave 没有收到 master 的回复，则 slave 会主动断开连接，下次的定时任务会重新尝试连接。

### （4）  对 slave 身份验证

如果 master 收到了 slave 的 ping 命令，并不会立即对其进行回复，而是会先进行身份验证。如果验证失败，则会发送消息拒绝连接；如果验证成功，则向 slave 发送连接成功响应。

### （5）  master 持久化

首次通信成功后，slave 会向 master 发送数据同步请求。当 master 接收到请求后，会 fork出一个子进程，让子进程以异步方式立即进行持久化。

### （6）  数据发送

持久化完毕后 master 会再 fork 出一个子进程，让该子进程以异步方式将数据发送给slave。slave 会将接收到的数据不断写入到本地的持久化文件中。

在 slave 数据同步过程中，master 的主进程仍在不断地接受着客户端的写操作，且不仅将新的数据写入到了master 内存，同时也写入到了同步缓存。当 master 的持久化文件中的数据发送完毕后，master 会再将同步缓存中新的数据发送给 slave，由 slave 将其写入到本地持久化文件中。数据同步完成。

### （7）  slave 恢复内存数据

当 slave 与 master 的数据同步完成后，slave 就会读取本地的持久化文件，将其恢复到本地内存，然后就可以对外提供读服务了。

### （8）  持续增量复制

在slave 对外提供服务过程中，master 会持续不断的将新的数据以增量方式发送给slave，以保证主从数据的一致性。

## 5.2.2    数据同步演变过程

### （1）  sync 同步 

Redis 2.8 版本之前，首次通信成功后，slave 会向 master 发送 sync 数据同步请求。然后 master 就会将其所有数据全部发送给 slave，由 slave 保存到其本地的持久化文件中。这个过程称为全量复制。

但这里存在一个问题：在全量复制过程中可能会出现由于网络抖动而导致复制过程中断。当网络恢复后，slave 与 master 重新连接成功，此时slave 会重新发送 sync 请求，然后会从头开始全量复制。

由于全量复制过程非常耗时，所以期间出现网络抖动的概率很高。而中断后的从头开始不仅需要消耗大量的系统资源、网络带宽，而且可能会出现长时间无法完成全量复制的情况。

### （2）  psync 同步

Redis 2.8 版本之后，全量复制采用了 psync（Partial Sync，不完全同步）同步策略。当全量复制过程出现由于网络抖动而导致复制过程中断时，当重新连接成功后，复制过程可以 “断点续传”。即从断开位置开始继续复制，而不用从头再来。这就大大提升了性能。

为了实现 psync，整个系统做了三个大的变化：

#### A、复制偏移量

系统为每个要传送数据进行了编号，该编号从 0 开始，每个字节一个编号。该编号称为复制偏移量。参与复制的主从节点都会维护该复制偏移量。

![image-20240730161443384](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301616021.png)

master 每发送过一个字节数据后就会进行累计。统计信息通过 info replication 的 master_repl_offset 可查看到。同时，slave 会定时向master 上报其自身已完成的复制偏移量给 master，所以 master 也会保存 slave 的复制偏移量 offset。

slave 在接收到master 的数据后，也会累计接收到的偏移量。统计信息通过info replication 的 slave_repl_offset 可查看到。

#### B、主节点复制 ID

当master 启动后就会动态生成一个长度为 40 位的 16 进制字符串作为当前master 的复制 ID，该 ID 是在进行数据同步时 slave 识别 master 使用的。通过 info replication 的 master_replid 属性可查看到该 ID。

#### C、 复制积压缓冲区

当 master 有连接的 slave 时，在 master 中就会创建并维护一个队列 backlog，默认大小为 1MB，该队列称为复制积压缓冲区。master 接收到了写操作数据不仅会写入到 master 主存，写入到master 中为每个 slave 配置的发送缓存，而且还会写入到复制积压缓冲区。其作用就是用于保存最近操作的数据，以备“断点续传”时做数据补偿，防止数据丢失。

#### D、psync 同步过程

![image-20240730170614728](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407301706814.png)

psync 是一个由 slave 提交的命令，其格式为 psync <master_replid> <repl_offset>，表示当前 slave 要从指定的 master 中的 repl_offset+1 处开始复制。repl_offset 表示当前 slave 已经完成复制的数据的offset。该命令保证了“断点续传”的实现。

在第一次开始复制时，slave 并不知道 master 的动态 ID，并且一定是从头开始复制，所以其提交的 psync 命令为 PSYNC ? -1。即 master_replid 为问号(?)，repl_offset 为-1。

如果复制过程中断后slave 与master 成功连接，则 slave 再次提交 psyn 命令。此时的 psyn 命令的 repl_offset 参数为其前面已经完成复制的数据的偏移量。

其实，并不是slave 提交了psyn 命令后就可以立即从master 处开始复制，而是需要master给出响应结果后，根据响应结果来执行。master 根据 slave 提交的请求及master 自身情况会给出不同的响应结果。响应结果有三种可能：

+ FULLRESYNC <master_replid> <repl_offset>：告知 slave 当前 master 的动态 ID 及可以开始全量复制了，这里的 repl_offset 一般为 0

+ CONTINUE：告知 slave 可以按照你提交的repl_offset 后面位置开始“续传”了

+ ERR：告知 slave，当前master 的版本低于 Redis 2.8，不支持 psyn，你可以开始全量复制了

#### E、 psync 存在的问题

+ 在 psync 数据同步过程中，若 slave 重启，在 slave 内存中保存的 master 的动态 ID 与续传 offset 都会消失，“断点续传”将无法进行，从而只能进行全量复制，导致资源浪费。
+ 在 psync 数据同步过程中，master 宕机后 slave 会发生“易主”，从而导致 slave 需要从新 master 进行全量复制，形成资源浪费。

### （3）  psync 同步的改进

Redis 4.0 对 psync 进行了改进，提出了“同源增量同步”策略。

#### A、解决 slave 重启问题

针对“slave 重启时 master 动态 ID 丢失问题”，改进后的 psync 将 master 的动态 ID 直接写入到了 slave 的持久化文件中。

slave 重启后直接从本地持久化文件中读取 master 的动态 ID，然后向 master 提交获取复制偏移量的请求。master 会根据提交请求的slave 地址，查找到保存在 master 中的复制偏移量，然后向 slave 回复 FULLRESYNC <master_replid> <repl_offset>，以告知 slave 其马上要开始发送的位置。然后master 开始“断点续传”。

#### B、 解决 slave 易主问题

slave 易主后需要和新 master 进行全量复制，本质原因是新 master 不认识 slave 提交的 psync 请求中“原 master 的动态 ID”。如果 slave 发送 PSYNC <原 master_replid> <repl_offset>命令，新master 能够识别出该slave 要从原master 复制数据，而自己的数据也都是从该master

复制来的。那么新master 就会明白，其与该slave“师出同门”，应该接收其“断点续传”同步请求。

而新 master 中恰好保存的有“原 master 的动态 ID”。由于改进后的 psync 中每个 slave都在本地保存了当前master 的动态 ID，所以当 slave 晋升为新的 master 后，其本地仍保存有之前 master 的动态 ID。而这一点也恰恰为解决“slave 易主”问题提供了条件。通过 master的 info replicaton 中的 master_replid2 可查看到。如果尚未发生过易主，则该值为 40 个 0。

### （4）  无盘操作

Redis 6.0 对同步过程又进行了改进，提出了“无盘全量同步”与“无盘加载”策略，避免了耗时的 IO 操作。

+ 无盘全量同步：master 的主进程 fork 出的子进程直接将内存中的数据发送给 slave，无需经过磁盘。

+ 无盘加载：slave 在接收到master 发送来的数据后不需要将其写入到磁盘文件，而是直接写入到内存，这样 slave 就可快速完成数据恢复。

### （5）  共享复制积压缓冲区

Redis 7.0 版本对复制积压缓冲区进行了改进，让各个 slave 的发送缓冲区共享复制积压缓冲区。这使得复制积压缓冲区的作用，除了可以保障数据的安全性外，还作为所有 slave的发送缓冲区，充分利用了复制积压缓冲区。

# 5.3 哨兵机制实现

## 5.3.1    简介

对于 Master 宕机后的冷处理方式是无法实现高可用的。Redis 从 2.6 版本开始提供了高可用的解决方案—— Sentinel 哨兵机制。在集群中再引入一个节点，该节点充当 Sentinel 哨兵，用于监视 Master 的运行状态，并在 Master 宕机后自动指定一个 Slave 作为新的Master。整个过程无需人工参与，完全由哨兵自动完成。

不过，此时的 Sentinel 哨兵又成为了一个单点故障点：若哨兵发生宕机，整个集群将瘫痪。所以为了解决Sentinel 的单点问题，又要为Sentinel 创建一个集群，即Sentinel 哨兵集群。一个哨兵的宕机，将不会影响到 Redis 集群的运行。

那么这些Sentinel 哨兵是如何工作的呢？Sentinel 是如何知道其监视的Master 状态的呢？每个 Sentinel 都会定时会向 Master 发送心跳，如果 Master 在有效时间内向它们都进行了响 应，则说明 Master 是“活着的”。如果 Sentinel 中有 quorum 个哨兵没有收到响应，那么就 认为 Master 已经宕机，然后会有一个 Sentinel 做Failover 故障转移。即将原来的某一个 Slave 晋升为 Master。

## 5.3.2    Redis 高可用集群搭建

在“不差钱”的情况下，可以让 Sentinel 占用独立的主机，即在 Redis 主机上只启动 Redis进程，在 Sentinel 主机上只启动 Sentinel 进程。下面要搭建一个“一主二从三哨兵”的高可用伪集群，即这些角色全部安装运行在一台主机上。“一主二从”使用前面的主从集群，下面仅搭建一个Sentinel 伪集群。

Sentinel 的默认端口是26379。

| **角色**   | **端口号** | **角色** | **端口号** |
| ---------- | ---------- | -------- | ---------- |
| **master** | 6380       | sentinel | 26380      |
| **slave**  | 6381       | sentinel | 26381      |
| **slave**  | 6382       | sentinel | 26382      |

### （1）  复制sentinel.conf

将 Redis 安装目录中的 sentinel.conf 文件复制到 cluster 目录中。该配置文件中用于存放一些 sentinel 集群中的一些公共配置。

### （2）  修改sentinel.conf

修改 cluster/sentinel.conf 配置文件。

#### A、sentinel monitor

![image-20240731141703917](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311417809.png)

该配置用于指定Sentinel 要监控的 master 是谁<ip><redis-port>，并为 master 起了一个名字<master-name>。该名字在后面很多配置中都会使用。同时指定 Sentinel 集群中决定该master“客观下线状态”判断的法定 sentinel 数量<quorum>。<quorum>的另一个用途与 sentinel 的 Leader 选举有关。要求中至少要有 max(quorum, sentinelNum/2+1)个sentinel 参与，选举才能进行。

这里将该配置注释掉，因为要在后面的其它配置文件中设置，如果不注释就会出现配置冲突。

#### B、 sentinel auth-pass

![image-20240731142601403](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311426471.png)

如果 Redis 主从集群中的主机设置了访问密码，那么该属性就需要指定 master 的主机名与访问密码。以方便sentinel 监控 master。

### （3）  新建sentinel26380.conf

在Redis 安装目录下的cluster 目录中新建sentinel26380.conf 文件作为Sentinel 的配置文件，并在其中键入如下内容

```
include sentinel.conf
pidfile /var/run/sentinel26380.pid
port 26380
sentinel monitor mymaster 172.27.45.196 6380 2
```

+ 172.27.45.196 是本机使用ifconfig查看的地址

sentinel monitor 属性用于指定当前监控的 master 的 IP 与 Port，同时为集群中 master 指定一个名称mymaster，以方便其它属性使用。

最后的 2 是参数 quorum 的值，quorum 有两个用途。一个是只有当 quorum 个 sentinel都认为当前master 宕机了才能开启故障转移。另一个用途与 sentinel 的 Leader 选举有关。要求中至少要有max(quorum, sentinelNum/2+1)个 sentinel 参与，选举才能进行。

### （4）  再复制两个 conf 文件

再使用sentinel26380.conf 复制出两个conf 文件：sentinel26381.conf 与sentinel26382.conf。然后修改其中的内容。

## 5.3.3    Redis 高可用集群的启动

### （1）  启动并关联 Redis 集群

首先要启动三台Redis，然后再通过slaveof 关联它们.

### （2）  启动Sentinel 集群

#### A、启动命令

在/usr/local/bin 目录下有一个命令 redis-sentinel 用于启动 Sentinel。不过，我们发现一个奇怪的现象：/usr/local/bin 目录中的redis-sentinel 命令是 redis-server 命令的软链接，这是为什么呢？

![image-20240731145046659](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311450712.png)

查看 Redis 安装目录中的 src 目录中的redis-server 与redis-sentinel 命令，我们发现这两个命令的大小一模一样。其实，这两个命令本质上是同一个命令。

![image-20240731145150657](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311451704.png)

之所以可以启动不同的进程，主要是因为在启动时所加载的配置文件的不同。所以在启动 Sentinel 时，需要指定 sentinel.conf 配置文件。

#### B、两种启动方式

由于redis-server 与redis-sentinel 命令本质上是同一个命令，所以使用这两个命令均可启动 Sentinel。

+ 方式一，使用redis-sentinel 命令：redis-sentinel sentinel26380.conf

+ 方式二，使用redis-server 命令：redis-server sentinel26380.conf --sentinel

#### C、 启动三台 Sentinel

```bash
redis-sentinel sentinel26380.conf
redis-sentinel sentinel26381.conf
redis-sentinel sentinel26382.conf
```

![image-20240731161108791](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311611885.png)

### （3）  查看Sentinel 信息

运行中的 Sentinel 就是一个特殊Redis，其也可以通过客户端连接，然后通过 info sentinel 来查看当前连接的Sentinel 的信息。

```bash
redis-cli -p 26380 info sentinel
```

![image-20240731162358179](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311623239.png)

此时如果将master关闭，sentinel中会有：

![image-20240731173017009](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311730107.png)

master会变成6382的redis，因为redis配置文件中指定了优先级，值越低的优先级越高。

### （4）  查看sentinel 配置文件

打开任意 sentinel 的配置文件，发现其配置内容中新增加了很多配置

![image-20240731162502499](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407311625589.png)

## 5.3.4    Sentinel 优化配置

在公共的 sentinel.conf 文件中，还可以通过修改一些其它属性的值来达到对 Sentinel 的配置优化。

### （1）sentinel down-after-milliseconds

![image-20240731211917789](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407312119855.png)

每个Sentinel 会通过定期发送 ping 命令来判断master、slave 及其它Sentinel 是否存活。如果 Sentinel 在该属性指定的时间内没有收到它们的响应，那么该 Sentinel 就会主观认为该主机宕机。默认为 30 秒。

### （2）  sentinel parallel-syncs

![image-20240731211942348](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407312119407.png)

该属性用于指定，在故障转移期间，即老的 master 出现问题，新的 master 刚晋升后，允许多少个slave 同时从新master 进行数据同步。默认值为 1 表示所有slave 逐个从新master进行数据同步。

### （3）sentinel failover-timeout

![image-20240731212014551](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407312120633.png)

指定故障转移的超时时间，默认时间为 3 分钟。该超时时间的用途很多：

+ 由于第一次故障转移失败，在同一个 master 上进行第二次故障转移尝试的时间为该failover-timeout 的两倍

+ 新 master 晋升完毕，slave 从老 master 强制转到新 master 进行数据同步的时间阈值。

+ 取消正在进行的故障转换所需的时间阈值。

+ 新 master 晋升完毕，所有replicas 的配置文件更新为新 master 的时间阈值。

### （4）sentinel deny-scripts-reconfig

![image-20240731212105316](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407312121378.png)

指定是否可以通过命令sentinel set 动态修改 notification-script 与client-reconfig-script 两个脚本。默认是不能的。这两个脚本如果允许动态修改，可能会引发安全问题。

### （5）  动态修改配置

通过redis-cli 连接上 Sentinel 后，通过 sentinel set 命令可动态修改配置信息。例如，下面的命令动态修改了sentinel monitor 中的 quorum 的值。

下表是 sentinel set 命令支持的参数：

| **参数**                    | **示例**                                                     |
| --------------------------- | ------------------------------------------------------------ |
| **quorum**                  | sentinel set  mymaster quorum 2                              |
| **down-after-milliseconds** | sentinel set mymaster down-after-milliseconds 50000          |
| **failover-timeout**        | sentinel set mymaster failover-timeout 300000                |
| **parallel-syncs**          | sentinel set mymaster parallel-syncs 3                       |
| **notification-script**     | sentinel set mymaster notification-script /var/redis/notify.sh |
| **client-reconfig-script**  | sentinel set mymaster client-reconfig-script /var/redis/reconfig.sh |
| **auth-pass**               | sentinel set mymaster auth-pass 111                          |

# 5.4 哨兵机制原理

## 5.4.1    三个定时任务

Sentinel 维护着三个定时任务以监测 Redis 节点及其它 Sentinel 节点的状态。

### （1）  info 任务

每个 Sentinel 节点每 10 秒就会向 Redis 集群中的每个节点发送 info 命令，以获得最新的Redis 拓扑结构。

### （2）  心跳任务

每个Sentinel 节点每1 秒就会向所有Redis 节点及其它Sentinel 节点发送一条ping 命令，以检测这些节点的存活状态。该任务是判断节点在线状态的重要依据。

### （3）  发布/订阅任务

每个 Sentinel 节点在启动时都会向所有 Redis 节点订阅_ _sentinel_ _:hello 主题的信息，当 Redis 节点中该主题的信息发生了变化，就会立即通知到所有订阅者。

启动后，每个 Sentinel 节点每 2 秒就会向每个 Redis 节点发布一条_ _sentinel_ _:hello 主题的信息，该信息是当前Sentinel 对每个 Redis 节点在线状态的判断结果及当前 Sentinel 节点信息。

当 Sentinel 节点接收到_ _sentinel_ _:hello 主题信息后，就会读取并解析这些信息，然后主要完成以下三项工作：

+ 如果发现有新的Sentinel 节点加入，则记录下新加入 Sentinel 节点信息，并与其建立连接。

+ 如果发现有 Sentinel Leader 选举的选票信息，则执行 Leader 选举过程。

+ 汇总其它 Sentinel 节点对当前 Redis 节点在线状态的判断结果，作为 Redis 节点客观下线的判断依据。

## 5.4.2    Redis 节点下线判断

对于每个 Redis 节点在线状态的监控是由 Sentinel 完成的。

### （1）  主观下线

每个 Sentinel 节点每秒就会向每个 Redis 节点发送 ping 心跳检测，如果Sentinel 在 down-after-milliseconds 时间内没有收到某Redis 节点的回复，则 Sentinel 节点就会对该 Redis节点做出“下线状态”的判断。这个判断仅仅是当前 Sentinel 节点的“一家之言”，所以称为主观下线。

### （2）  客观下线

当 Sentinel 主观下线的节点是 master 时，该 Sentinel 节点会向每个其它Sentinel 节点发送 sentinel is-master-down-by-addr 命令，以询问其对master 在线状态的判断结果。这些 Sentinel 节点在收到命令后会向这个发问 Sentinel 节点响应 0（在线）或 1（下线）。当 Sentinel收到超过 quorum 个下线判断后，就会对 master 做出客观下线判断。

## 5.4.3    Sentinel Leader 选举

当Sentinel 节点对master 做出客观下线判断后会由Sentinel Leader 来完成后续的故障转移，即 Sentinel 集群中的节点也并非是对等节点，是存在 Leader 与 Follower 的。

Sentinel 集群的 Leader 选举是通过Raft 算法实现的。Raft 算法比较复杂，后面会详细学习。这里仅简单介绍一下大致思路。

每个选举参与者都具有当选 Leader 的资格，当其完成了“客观下线”判断后，就会立即“毛遂自荐”推选自己做 Leader，然后将自己的提案发送给所有参与者。其它参与者在收到提案后，只要自己手中的选票没有投出去，其就会立即通过该提案并将同意结果反馈给提案者，后续再过来的提案会由于该参与者没有了选票而被拒绝。当提案者收到了同意反馈数量大于等于max(quorum，sentinelNum/2+1)时，该提案者当选 Leader。

说明：

+ 在网络没有问题的前提下，基本就是谁先做出了“客观下线”判断，谁就会首先发起Sentinel Leader 的选举，谁就会得到大多数参与者的支持，谁就会当选 Leader。

+ Sentinel Leader 选举会在次故障转移发生之前进行。

+ 故障转移结束后Sentinel 不再维护这种 Leader-Follower 关系，即 Leader 不再存在。

## 5.4.4    master 选择算法

![image-20240801111533843](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011115990.png)

在进行故障转移时，Sentinel Leader 需要从所有Redis 的Slave 节点中选择出新的Master。其选择算法为：

1) 过滤掉所有主观下线的，或心跳没有响应 Sentinel 的，或replica-priority 值为 0 的 Redis节点

2) 在剩余 Redis 节点中选择出 replica-priority 最小的的节点列表。如果只有一个节点，则直接返回，否则，继续
3) 从优先级相同的节点列表中选择复制偏移量最大的节点。如果只有一个节点，则直接返回，否则，继续
4) 从复制偏移值量相同的节点列表中选择动态 ID 最小的节点返回

## 5.4.5    故障转移过程

Sentinel Leader 负责整个故障转移过程，经历了如上步骤：

1) Sentinel Leader 根据 master 选择算法选择出一个 slave 节点作为新的master
2) Sentinel Leader 向新 master 节点发送 slaveof no one 指令，使其晋升为master
3) Sentinel Leader 向新 master 发送 info replication 指令，获取到 master 的动态 ID
4) Sentinel Leader 向其余 Redis 节点发送消息，以告知它们新 master 的动态 ID
5) Sentinel Leader 向其余 Redis 节点发送 slaveof <mastIp> <masterPort>指令，使它们成为新 master 的 slave
6) Sentinel Leader 从所有slave 节点中每次选择出parallel-syncs 个slave 从新 master 同步数据，直至所有 slave 全部同步完毕
7) 故障转移完毕

## 5.4.6    节点上线

不同的节点类型，其上线的方式也是不同的。

### （1）  原 Redis 节点上线

无论是原下线的master 节点还是原下线的slave 节点，只要是原Redis 集群中的节点上线，只需启动 Redis 即可。因为每个 Sentinel 中都保存有原来其监控的所有 Redis 节点列表， Sentinel 会定时查看这些 Redis 节点是否恢复。如果查看到其已经恢复，则会命其从当前 master 进行数据同步。

不过，如果是原master 上线，在新 master 晋升后 Sentinel Leader 会立即先将原 master节点更新为slave，然后才会定时查看其是否恢复。

### （2）  新 Redis 节点上线

如果需要在 Redis 集群中添加一个新的节点，其未曾出现在Redis 集群中，则上线操作只能手工完成。即添加者在添加之前必须知道当前master 是谁，然后在新节点启动后运行 slaveof 命令加入集群。

### （3）  Sentinel 节点上线

如果要添加的是Sentinel 节点，无论其是否曾经出现在 Sentinel 集群中，都需要手工完成。即添加者在添加之前必须知道当前 master 是谁，然后在配置文件中修改 sentinel monitor属性，指定要监控的master。然后启动 Sentinel 即可。

# 5.5 CAP 定理

## 5.5.1    概念

CAP 定理指的是在一个分布式系统中，一致性 Consistency、可用性 Availability、分区容错性 Partition tolerance，三者不可兼得。

+ 一致性（C）：分布式系统中多个主机之间是否能够保持数据一致的特性。即，当系统数据发生更新操作后，各个主机中的数据仍然处于一致的状态。

+ 可用性（A）：系统提供的服务必须一直处于可用的状态，即对于用户的每一个请求，系统总是可以在有限的时间内对用户做出响应。

+ 分区容错性（P）：分布式系统在遇到任何网络分区故障时，仍能够保证对外提供满足一致性和可用性的服务。

## 5.5.2    定理

CAP 定理的内容是：对于分布式系统，网络环境相对是不可控的，出现网络分区是不可避免的，因此系统必须具备分区容错性。但系统不能同时保证一致性与可用性。即要么 CP，要么 AP。

## 5.5.3    BASE 理论

BASE 是Basically Available（基本可用）、Soft state（软状态）和 Eventually consistent（最终一致性）三个短语的简写，BASE 是对 CAP 中一致性和可用性权衡的结果，其来源于对大规模互联网系统分布式实践的结论，是基于 CAP 定理逐步演化而来的。

BASE 理论的核心思想是：即使无法做到强一致性，但每个系统都可以根据自身的业务特点，采用适当的方式来使系统达到最终一致性。

### （1）  基本可用

基本可用是指分布式系统在出现不可预知故障的时候，允许损失部分可用性。

### （2）  软状态

软状态，是指允许系统数据存在的中间状态，并认为该中间状态的存在不会影响系统的整体可用性，即允许系统主机间进行数据同步的过程存在一定延时。软状态，其实就是一种灰度状态，过渡状态。

### （3）  最终一致性

最终一致性强调的是系统中所有的数据副本，在经过一段时间的同步后，最终能够达到一个一致的状态。因此，最终一致性的本质是需要系统保证最终数据能够达到一致，而不需要保证系统数据的实时一致性。

+ 实时一致性：要求数据内容一旦发生更新，客户端立刻可以访问到最新的数据。所以，在集群环境下该特性是无法实现的，只存在于单机环境中。
+ 最终一致性：数据内容发生更新后，经过一小段时间后，客户端可以访问到最新的数据。

实时一致性与最终一致性两个概念是从客户端访问到一致性内容的时间角度来说的，单从客户端访问到的内容角度来说(不说时间问题)，还有两个概念：

+ 强一致性：也称为严格一致性。要求客户端访问到的一定是更新过的新数据。
+ 弱一致性：允许客户端从集群不同的节点访问到的数据是不一致的。

## 5.5.4    CAP 的应用

下面将生产中常见到的一些中间件与服务器集群的CAP 特性进行分析。

### （1）  Zookeeper 与 CAP

Zookeeper 遵循的是 CP 模式，即保证了一致性，但牺牲了可用性。

当Leader 节点中的数据发生了变化后，在 Follower 还没有同步完成之前，整个 Zookeeper集群是不对外提供服务的。如果此时有客户端来访问数据，则客户端会因访问超时而发生重试。不过，由于 Leader 的选举非常快，所以这种重试对于用户来说几乎是感知不到的。所以说，Zookeeper 保证了一致性，但牺牲了可用性。

### （2）  Consul 与 CAP

Consul 遵循的是 CP 模式，即保证了一致性，但牺牲了可用性。

### （3）  Redis 与 CAP

Redis 遵循的是AP 模式，即保证了可用性，但牺牲了一致性。

### （4）  Eureka 与 CAP

Eureka 遵循的是AP 模式，即保证了可用性，但牺牲了一致性。

### （5）  Nacos 与 CAP

Nacos 在做注册中心时，默认是 AP 的。但其也支持 CP 模式，但需要用户提交请求进行转换。

# 5.6 Raft 算法

## 5.6.1    基础

Raft 算法是一种通过对日志复制管理来达到集群节点一致性的算法。这个日志复制管理发生在集群节点中的 Leader 与 Followers 之间。Raft 通过选举出的 Leader 节点负责管理日志复制过程，以实现各个节点间数据的一致性。

## 5.6.2 角色、任期及角色转变

![image-20240801141818779](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011418884.png)

在 Raft 中，节点有三种角色：

+ Leader：唯一负责处理客户端写请求的节点；也可以处理客户端读请求；同时负责日志复制工作

+ Candidate：Leader 选举的候选人，其可能会成为 Leader。是一个选举中的过程角色

+ Follower：可以处理客户端读请求；负责同步来自于 Leader 的日志；当接收到其它 Cadidate 的投票请求后可以进行投票；当发现 Leader 挂了，其会转变为 Candidate 发起 Leader 选举

## 5.6.3    leader 选举

通过Raft 算法首先要实现集群中 Leader 的选举。

### （1）  我要选举

若 follower 在心跳超时范围内没有接收到来自于 leader 的心跳，则认为 leader 挂了。此时其首先会使其本地term 增一。然后 follower 会完成以下步骤：

+ 此时若接收到了其它 candidate 的投票请求，则会将选票投给这个 candidate

+ 由 follower 转变为 candidate

+ 若之前尚未投票，则向自己投一票

+ 向其它节点发出投票请求，然后等待响应

### （2）  我要投票

follower 在接收到投票请求后，其会根据以下情况来判断是否投票：

+ 发来投票请求的 candidate 的 term 不能小于我的 term

+ 在我当前 term 内，我的选票还没有投出去

+ 若接收到多个 candidate 的请求，我将采取 first-come-first-served 方式投票

### （3）  等待响应

当一个 Candidate 发出投票请求后会等待其它节点的响应结果。这个响应结果可能有三种情况：

+ 收到过半选票，成为新的 leader。然后会将消息广播给所有其它节点，以告诉大家我是新的 Leader 了

+ 接收到别的candidate 发来的新leader 通知，比较了新 leader 的term 并不比自己的term小，则自己转变为 follower

+ 经过一段时间后，没有收到过半选票，也没有收到新 leader 通知，则重新发出选举

### （4）  选举时机

在很多时候，当 Leader 真的挂了，Follower 几乎同时会感知到，所以它们几乎同时会变为 candidate 发起新的选举。此时就可能会出现较多 candidate 票数相同的情况，即无法选举出 Leader。

为了防止这种情况的发生，Raft 算法其采用了 randomized election timeouts 策略来解决这个问题。其会为这些 Follower 随机分配一个选举发起时间 election timeout，这个 timeout在 150-300ms 范围内。只有到达了election timeout 时间的 Follower 才能转变为 candidate，否则等待。那么election timeout 较小的 Follower 则会转变为 candidate 然后先发起选举，一般情况下其会优先获取到过半选票成为新的 leader。

## 5.6.4    数据同步

在 Leader 选举出来的情况下，通过日志复制管理实现集群中各节点数据的同步。

### （1）  状态机

Raft 算法一致性的实现，是基于日志复制状态机的。状态机的最大特征是，不同 Server中的状态机若当前状态相同，然后接受了相同的输入，则一定会得到相同的输出。

![image-20240801141833327](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011418400.png)

### （2）  处理流程

![image-20240801141901285](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011419375.png)

当 leader 接收到 client 的写操作请求后，大体会经历以下流程

+ leader 在接收到 client 的写操作请求后，leader 会将数据与term 封装为一个 box，并随着下一次心跳发送给所有 followers，以征求大家对该 box 的意见。同时在本地将数据封装为日志

+ follower 在接收到来自leader 的 box 后首先会比较该box 的term 与本地记录的曾接受过的 box 的最大 term，只要不比自己的小就接受该 box，并向 leader 回复同意。同时会将该 box 中的数据封装为日志。

+ 当 leader 接收到过半同意响应后，会将日志 commit 到自己的状态机，状态机会输出一个结果，同时日志状态变为了 committed

+ 同时 leader 还会通知所有 follower 将日志 commit 到它们本地的状态机，日志状态变为了 committed

+ 在 commit 通知发出的同时，leader 也会向 client 发出成功处理的响应

### （3）  AP 支持

![image-20240801141945082](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011419157.png)

Log 由 term index、log index 及 command 构成。为了保证可用性，各个节点中的日志可以不完全相同，但leader 会不断给 follower 发送 box，以使各个节点的 log 最终达到相同。即 raft 算法不是强一致性的，而是最终一致的。

## 5.6.5    脑裂

Raft 集群存在脑裂问题。在多机房部署中，由于网络连接问题，很容易形成多个分区。

而多分区的形成，很容易产生脑裂，从而导致数据不一致。

由于三机房部署的容灾能力最强，所以生产环境下，三机房部署是最为常见的。下面以三机房部署为例进行分析，根据机房断网情况，可以分为五种情况：

### （1）情况一：不确定

![image-20240801142055944](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011420014.png)

这种情况下，B 机房中的主机是感知不到 Leader 的存在的，所以B 机房中的主机会发起新一轮的 Leader 选举。由于B 机房与C 机房是相连的，虽然 C 机房中的 Follower 能够感知到A 机房中的 Leader，但由于其接收到了更大 term 的投票请求，所以C 机房的 Follower也就放弃了A 机房中的 Leader，参与了新 Leader 的选举。

若新 Leader 出现在 B 机房，A 机房是感知不到新 Leader 的诞生的，其不会自动下课，所以会形成脑裂。但由于A 机房 Leader 处理的写操作请求无法获取到过半响应，所以无法完成写操作。但B 机房 Leader 的写操作处理是可以获取到过半响应的，所以可以完成写操作。故，A 机房与 B、C 机房中出现脑裂，且形成了数据的不一致。

若新 Leader 出现在 C 机房，A 机房中的 Leader 则会自动下课，所以不会形成脑裂。

### （2）情况二：形成脑裂

![image-20240801142136856](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011421929.png)

这种情况与情况一基本是一样的。不同的是，一定会形成脑裂，无论新 Leader 在B 还是 C 机房。

### （3） 情况三：无脑裂

![image-20240801142208226](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011422301.png)

A、C 可以正常对外提供服务，但 B 无法选举出新的 Leader。由于 B 中的主机全部变为了选举状态，所以无法提供任何服务，没有形成脑裂。

### （4） 情况四：无脑裂

![image-20240801142236114](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011422188.png)

A、B、C 均可以对外提供服务，不受影响。

### （5） 情况五：无脑裂

![image-20240801142317182](https://gitee.com/LowProfile666/image-bed/raw/master/img/202408011423254.png)

A 机房无法处理写操作请求，但可以对外提供读服务。

B、C 机房由于失去了 Leader，均会发起选举，但由于均无法获取过半支持，所以均无法选举出新的Leader。

## 5.6.6   Leader 宕机处理

### （1）  请求到达前 Leader 挂了

client 发送写操作请求到达 Leader 之前 Leader 就挂了，因为请求还没有到达集群，所以这个请求对于集群来说就没有存在过，对集群数据的一致性没有任何影响。Leader 挂了之后，会选举产生新的 Leader。

由于Stale Leader 并未向 client 发送成功处理响应，所以 client 会重新发送该写操作请求。

### （2）  未开始同步数据前 Leader 挂了

client 发送写操作请求给 Leader，请求到达 Leader 后，Leader 还没有开始向 Followers发出数据 Leader 就挂了。这时集群会选举产生新的 Leader。Stale Leader 重启后会作为 Follower 重新加入集群，并同步新 Leader 中的数据以保证数据一致性。之前接收到 client 的数据被丢弃。

由于Stale Leader 并未向 client 发送成功处理响应，所以 client 会重新发送该写操作请求。

### （3）  同步完部分后 Leader 挂了

client 发送写操作请求给 Leader，Leader 接收完数据后向所有 Follower 发送数据。在部分 Follower 接收到数据后 Leader 挂了。由于 Leader 挂了，就会发起新的 Leader 选举。

+ 若 Leader 产生于已完成数据接收的 Follower，其会继续将前面接收到的写操作请求转换为日志，并写入到本地状态机，并向所有 Flollower 发出询问。在获取过半同意响应后会向所有 Followers 发送 commit 指令，同时向 client 进行响应。

+ 若 Leader 产生于尚未完成数据接收的 Follower，那么原来已完成接收的 Follower 则会放弃曾接收到的数据。由于 client 没有接收到响应，所以 client 会重新发送该写操作请求。

### （4）  commit 通知发出后 Leader 挂了

client 发送写操作请求给 Leader，Leader 也成功向所有 Followers 发出的 commit 指令，并向 client 发出响应后，Leader 挂了。

由于 Stale Leader 已经向 client 发送成功接收响应，且 commit 通知已经发出，说明这个写操作请求已经被server 成功处理。

## 5.6.7    Raft 算法动画演示

在网络上有一个关于Raft 算法的动画，其非常清晰全面地演示了 Raft 算法的工作原理。该动画的地址为：http://thesecretlivesofdata.com/raft/