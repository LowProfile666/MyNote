

# 命令

查看

# 安装 JDK

[参考链接](https://timberkito.com/?p=12)

## 方法1

```python
yum search java|grep jdk  # 查看云端yum库中目前支持安装的jdk软件包
yum install -y java-1.8.0-openjdk*  # 选择版本安装jdk
java -version  # 验证是否安装成功
find / -name 'java'  # 查找 jdk 安装位置
```

## 方法2

```python
mkdir /usr/java21  # 创建一个文件夹
cd /usr/java21  # 进入文件夹
wget https://download.oracle.com/java/21/latest/jdk-21_linux-x64_bin.tar.gz  # 下载jdk21安装包
tar zxvf jdk-21_linux-x64_bin.tar.gz  # 解压
vim /etc/profile  # 修改文件，在文件的末尾添加以下代码，相当于配置环境变量：

export JAVA_HOME=/usr/java21/jdk-21.0.2
export PATH=$JAVA_HOME/bin:$PATH
export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar

source /etc/profile  # 使配置文件生效
java -version  # 查看版本
```

# 安装 Redis

[参考链接](https://juejin.cn/post/7012898467643621412)

```python
wget https://github.com/redis/redis/archive/7.2.4.tar.gz  # 获取redis安装包
tar xzvf 7.2.4.tar.gz  # 解压
cd redis-7.2.4/  # 进入解压后的文件夹中

make  # 生成 Redis 可执行文件
cd src  # 进入src目录，该目录通常包含生成的可执行文件。
make install PREFIX=/usr/local/redis  # 将已编译的程序安装到系统中，安装目录为/usr/local/redis

cd ../  # 退回上一级
mkdir /usr/local/redis/etc  # 新建目录
mv redis.conf /usr/local/redis/etc  # 将配置文件移动到etc目录，这个配置文件包含了 Redis 服务器的各种配置选项，例如端口号、数据持久化选项等
/usr/local/redis/bin/redis-server /usr/local/redis/etc/redis.conf  # 通过指定配置文件来启动 Redis 服务器

# 将redis-cli,redis-server拷贝到bin下，让redis-cli指令可以在任意目录下直接使用
cp /usr/local/redis/bin/redis-server /usr/local/bin/  
cp /usr/local/redis/bin/redis-cli /usr/local/bin/
```

如果启动遇到异常：

![image-20240222003439481](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402231716077.png)

+ 这个警告是关于内存过度提交（Memory overcommit）的问题。Redis 在启动时发现内存过度提交被禁用，因此发出了警告。

有两个解决方法：

+ 将 `vm.overcommit_memory` 设置为 1：你可以编辑 `/etc/sysctl.conf` 文件，在文件末尾添加一行 `vm.overcommit_memory = 1`，然后保存并退出。然后，运行 `sysctl -p` 命令来重新加载配置文件，使更改生效。这个方法会在系统重新启动后永久生效。
+ 直接运行命令：你也可以直接运行命令 `sysctl vm.overcommit_memory=1`，这将立即生效，但不会在系统重启后保留设置。

# 安装 nginx

[nginx学习链接](https://www.nginx.org.cn/article/detail/545)

```python
yum install nginx -y  # 安装Nginx
systemctl enable nginx  # 设置nginx开启启动
systemctl start nginx  # 启动nginx
```

# 安装 node

```python
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash  # 安装node管理工具nvm
source ~/.bashrc  # 更新配置文件
nvm install v20.11.1  # 安装node
node -v  # 验证是否安装成功
```

安装路径为 ：`/root/.nvm/versions/node/v20.11.1/bin/node` 

# 安装 Tomcat

在 /root 下新建了一个 tomcat 文件夹，我的 tomcat 都放在里面

```python
wget https://archive.apache.org/dist/tomcat/tomcat-11/v11.0.0-M13/bin/apache-tomcat-11.0.0-M13.tar.gz  # 获取tomcat
tar -zxvf apache-tomcat-11.0.0-M17.tar.gz  # 解压tomcat
```

如果有多个 tomcat 运行，需要修改 tomcat 的端口，因为默认 tomcat 的端口都是 8080，目前我的 tomcat9 端口是 8081，tomcat11 端口是 8082。

# 持久运行

要想某个命令或程序以服务的方式一直运行在服务器上，可以使用 systemctl 管理。

比如要一直运行 redis 服务器：在 systemd 服务目录中 `/etc/systemd/system/`，创建服务单元文件 `redis.service`，文件内容：

```python
[Unit]  # 这个部分用于描述系统单元的基本信息
Description=Redis Server  # 描述了这个单元的作用，即 Redis 服务器
After=network.target  # 指定了这个单元在网络服务之后启动，确保网络服务已经准备就绪后再启动 Redis 服务器

[Service]  # 这个部分定义了如何启动和管理服务
User=root  # 指定了服务运行的用户，这里将服务设置为以 root 用户的身份运行
Type=simple  # 指定了服务的类型，这里是简单类型，表示 systemd 会认为服务启动完毕的标志是当执行的命令退出时即可
ExecStart=/usr/local/redis/bin/redis-server /usr/local/redis/etc/redis.conf  # 定义了服务启动时执行的命令，即启动 Redis 服务器并使用指定的配置文件
Restart=always  # 指定了当服务退出时应该进行重启
RestartSec=3  # 指定了重启之间的延迟时间，这里设置为 3 秒

[Install]  # 这个部分定义了在什么情况下这个单元应该被安装
WantedBy=multi-user.target  # 指定了在 multi-user.target（多用户模式）中启用这个单元，这通常是系统正常运行时的默认目标
```

修改过服务单元文件后：

```python
systemctl daemon-reload  # 重新加载 systemd 守护程序配置
systemctl start redis  # 开启服务
systemctl enable redis  # 设置开机自启
```

