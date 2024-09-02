

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

安装目录可以自定义

```python
mkdir /usr/java21  # 创建一个文件夹
cd /usr/java21  # 进入文件夹
wget https://download.oracle.com/java/21/latest/jdk-21_linux-x64_bin.tar.gz  # 下载jdk21安装包
tar zxvf jdk-21_linux-x64_bin.tar.gz  # 解压
vim /etc/profile  # 修改文件，在文件的末尾添加以下代码，相当于配置环境变量：

export JAVA_HOME=/usr/java21/jdk-21.0.3
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
make install # 将已编译的程序安装到系统中，

redis-server redis.conf  # 通过指定配置文件路径来启动 Redis 服务器
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

ps -aux|grep nginx  # 查看nginx的安装目录，在进程的后面
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

# 安装MySQL

先删除服务器上有的mysql。

```shell
# 下载 mysql 安装包
wget https://dev.mysql.com/get/mysql80-community-release-el8-1.noarch.rpm
yum install mysql80-community-release-el8-1.noarch.rpm

# 安装 mysql 
yum install mysql-server

# 如果出现 No match for argument: mysql-community-server 报错，需要先禁用CentOS8自带mysql模块
yum module disable mysql

# 如果以上报错 Error: GPG check FAILED 的话，使用：
yum install mysql-community-server --nogpgcheck

# 安装成功。启动 mysql 服务：
service mysqld start
# 显示 mysql 的随机密码：
cat /var/log/mysql/mysqld.log | grep password
# 如果 root@localhost is created with an empty password ! 的话，当前登录时不需要密码
# 登录mysql，空密码按两次回车
mysql -uroot -p

# 修改密码
ALTER USER 'root'@'localhost' IDENTIFIED BY '1234'
```

在本地使用 navicat 连接 ssh 再连接 mysql 时，如果报错：

![image-20240427104924285](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271049360.png)

这是因为之前连过，本地的保存的密码和现在服务器上的匹对不了，所以打开本地的 .ssh/known_hosts 文件，将服务器对应的那个记录删除就行。

![image-20240427105134404](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271051467.png)

重新连接，又会重新生成。

开放远程连接：

1. 登录mysql，使用mysql数据库

2. 创建一个允许从任何主机连接的用户并授权：

   ```
   CREATE USER 'root'@'%' IDENTIFIED BY '1234';
   GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
   ```

3. 刷新权限：

   ```
   FLUSH PRIVILEGES;
   ```

4. 检查用户和主机权限：

   ```
   SELECT User, Host FROM mysql.user;
   ```

5. 重启mysql服务：

   ```
   systemctl restart mysqld
   ```

6. 开启云服务器的安全组，放过3306端口

7. 测试连接：

   ```
   mysql -u root -h 47.109.78.124 -p
   ```

# 安装.NET

```shell
# 添加 Microsoft 存储库：
sudo rpm -Uvh https://packages.microsoft.com/config/centos/8/packages-microsoft-prod.rpm
# 安装.NET SDK
sudo dnf install dotnet-sdk-6.0
# 验证安装
dotnet --version
```

# 开放防火墙

```shell
# 启动防火墙
systemctl start firewalld.service

# 为了使外部用户能够访问您的Web服务器，需要启用到主机的HTTP和HTTPS通信
# 修改防火墙规则并添加以下条目：
sudo firewall-cmd --permanent --zone=public --add-service=http
sudo firewall-cmd --permanent --zone=public --add-service=https

# 更新防火墙规则
sudo firewall-cmd --reload

# 查看所有打开的端口
firewall-cmd --list-ports

# 开放端口
firewall-cmd --add-port=8080/tcp --permanent
firewall-cmd --add-port=22/tcp --permanent
firewall-cmd --add-port=3306/tcp --permanent

# 更新防火墙规则
sudo firewall-cmd --reload
```

# 持久运行

要想某个命令或程序以服务的方式一直运行在服务器上，可以使用 systemctl 管理。

```shell
systemctl list-units --type=service --all  # 查看systemctl管理所有服务
```

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

# 各安装目录

jdk21：/root/java21/jdk-21.0.3 

redis：/root/redis、/usr/local/redis

nginx：/usr/sbin/nginx

+ 配置文件：/etc/nginx/nginx.conf

node：/root/.nvm/versions/node/v20.11.1/bin/node

tomcat11：/root/tomcat/apache-tomcat-11.0.0-M13

mysql8：/usr/libexec/mysqld
