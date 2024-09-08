# 概述

Nginx （engine x） 是一个高性能的Web服务器和反向代理服务器，也可以作为邮件代理服务器。

Nginx 特点是占有内存少，并发处理能力强，以高性能、低系统资源消耗而闻名，Nginx官方测试为5万并发请求。与Nginx同类型的Web服务器还有Apache、Lighttpd（音同lighty）、Tengine（阿里巴巴的） 等。Nginx 的并发处理能力在同类型的Web服务器中表现极好（Apache、Lighttpd），在全世界范围内大量的网站使用了Nginx，国内互联网中也大量使用了Nginx，比如：淘宝、新浪、搜狐、网易、美团等。

Nginx是免费开源的，同时Nginx也有收费的商业版本，商业版本提供了性能优化、宕机等紧急问题处理等技术支持和服务。

## 正向代理和反向代理

反向代理（Reverse Proxy）方式是指以代理服务器来接受internet上的连接请求，然后将请求转发给内部网络上的服务器，并将从服务器上得到的结果返回给internet上请求连接的客户端，此时代理服务器对外就表现为一个反向代理服务器；

正向代理类似一个跳板机，代理访问外部资源。比如：我是一个用户，我访问不了某网站，但是我能访问一个代理服务器，这个代理服务器，它能访问那个我不能访问的网站，于是我先连上代理服务器，告诉它我需要那个无法访问网站的内容，代理服务器去取回来,然后返回给我。

**正向代理代理对象是客户端，反向代理代理对象是服务端。**

软件层面一般常用Nginx来做反向代理服务器，它的性能非常好，用来做负载均衡。

### 正向代理举例

比如你现在缺钱，想找马云爸爸去借钱，可想而知人家可能鸟都不鸟你，到最后碰一鼻子灰借不到钱。不过你认识你家隔壁老王，而老王认识马云同志，而且关系还很好。这时候你托老王去找马云借钱，当然这事最后成了，你从马云那里借到了500万！这时候马云并不知道钱是你借的，只知道这钱是老王借的。最后由老王把钱转交给你。在这里，老王就充当了一个重要的角色：代理。

此时的代理，就是我们常说的正向代理。代理客户端去请求服务器，隐藏了真实客户端，服务器并不知道真实的客户端是谁。正向代理应用最广泛的莫过于现在的某些“科学上网工具”，你访问不了谷歌、Facebook的时候，你可以在国外搭建一台代理服务器，代理你访问，代理服务器再把请求到的数据转交给你，你就可以看到内容了。

### 反向代理举例

比如你现在很无聊，想找人聊天，这时候你拨通了联通客服10010电话，联通的总机可能随机给你分配一个闲置的客服给你接通。这时候你如愿以偿的和客服聊了起来，问了问她目前有没有结婚、有没有对象、家住哪里、她的微信号、她的手机号。。。

此时联通总机充当的角色就是反向代理，你只知道和客服接通并聊了起来，具体为什么会接通这个客服MM，怎么接通的，你并不知道。

反向代理隐藏了真正的服务端，就像你每天使用百度的时候，只知道敲打www.baidu.com就可以打开百度搜索页面，但背后成千上万台百度服务器具体是哪一台为我们服务的，我们并不知道。我们只知道这个代理服务器，它会把我们的请求转发到真实为我们服务的那台服务器那里去。

# 环境

免费开源版的官方网站：http://nginx.org 

下载nginx的tar.gz包，然后传到服务器上去。

也可以使用wget下载，但是不推荐，wget不会断点续传，如果在下载过程中断开，那么就需要全部重新下载。

## 安装前的准备

Nginx的安装需要确定Linux安装相关的几个库，否则配置和编译会出现错误， 具体的检查安装过程为：

#### （1） gcc编译器是否安装

​	检查是否安装：yum list installed | grep gcc

​	执行安装：yum install gcc -y

#### （2） openssl库是否安装

​	检查是否安装：yum list installed | grep openssl

​	执行安装：yum install openssl openssl-devel -y

#### （3） pcre库是否安装

​	检查是否安装：yum list installed | grep pcre

​	执行安装：yum install pcre pcre-devel -y

#### （4） zlib库是否安装

​	检查是否安装：yum list installed | grep zlib

​	执行安装：yum install zlib zlib-devel -y

#### **（5）**一次性安装，执行如下命令

```bash
yum install gcc openssl openssl-devel pcre pcre-devel zlib zlib-devel -y
```

如果有些库没有安装，则会自动安装，安装过的则会跳过。

## 安装

1. 解压下载下来的nginx文件，执行命令：

   ```bash
   tar -zxvf nginx-1.14.2.tar.gz
   ```

2. 切换至解压后的nginx主目录，执行命令：

   ```bash
   cd nginx-1.14.2
   ```

3. 在nginx主目录nginx-1.14.2下执行命令：

   ```bash
   ./configure --prefix=/usr/local/nginx 
   ```

   1. 配置nginx的安装，（其中--prefix是指定nginx安装路径）  注意:等号左右不要有空格

4. 执行命令进行编译：

   ```bash
   make
   ```

5. 执行命令进行安装：

   ```bash
   make install
   ```

安装成功后，可以切换到/usr/local/nginx目录下，查看内容

![image-20240908112725157](https://gitee.com/LowProfile666/image-bed/raw/master/img/202409081127241.png)

如果使用的yum命令安装的nginx，而不是手动安装的话，这四个文件对应的位置：

+ conf ---> /etc/nginx/
+ html ---> /usr/share/nginx/html/
+ logs ---> /var/log/nginx/
+ sbin(里面只有一个nginx启动文件) ---> /usr/sbin

## 启动

切换到nginx安装目录的sbin目录下，执行：

```bash
./nginx
```

通过配置文件启动：

```bash
./nginx -c /usr/local/nginx/conf/nginx.conf
或者
/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf
```

+ **其中-c是指定配置文件,而且配置文件路径必须指定绝对路径**

通过查看进程检查nginx是否启动：

```bash
[root@zsm ~]# ps -ef | grep nginx
root        1458       1  0 8月16 ?       00:00:00 nginx: master process /usr/sbin/nginx
nginx     676163    1458  0 9月07 ?       00:00:00 nginx: worker process
nginx     676164    1458  0 9月07 ?       00:00:00 nginx: worker process
```

nginx 体系结构由 master 进程和其 worker 进程组成

+ master 进程读取配置文件，并维护 worker 进程，
+ 而 worker 进程则对请求进行实际处理

Nginx启动后，安装目录下会出现一些_tmp结尾的文件，这些是临时文件，不用管。

## 关闭

还是用 ps -ef | grep nginx 找出 nginx 的进程号，使用 kill 命令杀掉该进程：

```bash
kill 主pid
kill -QUIT 主pid
kill -TERM 主pid
```

其中pid是主进程号的pid（master process），其他为子进程pid（worker process）。

使用 kill 和 kill -term 的效果是一样的，会直接关闭进程；使用 kill -quit 会优雅的关闭进程，就是会等当前nginx处理掉所有的已接受的请求后关闭。

如果使用 kill -9 强制杀死进程的话，子进程不会被杀掉。

## 重启

重启只能在nginx运行的状态下重启：

```bash
./nginx -s reload
```

该命令包含两个操作，杀掉进程，启动服务。

## 其他

当修改Nginx配置文件后，可以使用Nginx命令进行配置文件语法检查，用于检查Nginx配置文件是否正确：

```bash
/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf –t
```

Linux上查看nginx版本：

```bash
/usr/local/nginx/sbin/nginx -V
```

+ -v （小写的v）显示 nginx 的版本
+ -V （大写的V）显示 nginx 的版本、编译器版本和配置参数

# 核心配置文件

学习Nginx首先需要对它的核心配置文件有一定的认识，这个文件位于Nginx的安装目录/usr/local/nginx/conf目录下，名字为nginx.conf：

```
#配置worker进程运行用户 nobody也是一个linux用户，一般用于启动程序，没有密码
user  nobody;  
#配置工作进程数目，根据硬件调整，通常等于CPU数量或者2倍于CPU数量
worker_processes  1;  

#配置全局错误日志及类型，[debug | info | notice | warn | error | crit]，默认是error
error_log  logs/error.log;  
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

pid        logs/nginx.pid;  #配置进程pid文件 


###====================================================


#配置工作模式和连接数
events {
    worker_connections  1024;  #配置每个worker进程连接数上限，nginx支持的总连接数就等于worker_processes * worker_connections
}

###===================================================


#配置http服务器,利用它的反向代理功能提供负载均衡支持
http {
    #配置nginx支持哪些多媒体类型，可以在conf/mime.types查看支持哪些多媒体类型
    include       mime.types;  
    #默认文件类型 流类型，可以理解为支持任意类型
    default_type  application/octet-stream;  
    #配置日志格式 
    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #配置access.log日志及存放路径，并使用上面定义的main日志格式
    #access_log  logs/access.log  main;

    sendfile        on;  #开启高效文件传输模式
    #tcp_nopush     on;  #防止网络阻塞

    #keepalive_timeout  0;
    keepalive_timeout  65;  #长连接超时时间，单位是秒

    #gzip  on;  #开启gzip压缩输出
	
	###-----------------------------------------------
	

    #配置虚拟主机
    server {
        listen       80;  #配置监听端口
        server_name  localhost;  #配置服务名

        #charset koi8-r;  #配置字符集

        #access_log  logs/host.access.log  main;  #配置本虚拟主机的访问日志

	#默认的匹配斜杠/的请求，当访问路径中有斜杠/，会被该location匹配到并进行处理
        location / {
	    #root是配置服务器的默认网站根目录位置，默认为nginx安装主目录下的html目录
            root   html;  
	    #配置首页文件的名称
            index  index.html index.htm;  
        }		

        #error_page  404              /404.html;  #配置404页面
        # redirect server error pages to the static page /50x.html
        #error_page   500 502 503 504  /50x.html;  #配置50x错误页面
        
	#精确匹配
	location = /50x.html {
            root   html;
        }

		#PHP 脚本请求全部转发到Apache处理
        # proxy the PHP scripts to Apache listening on 127.0.0.1:80
        #
        #location ~ \.php$ {
        #    proxy_pass   http://127.0.0.1;
        #}

		#PHP 脚本请求全部转发到FastCGI处理
        # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
        #
        #location ~ \.php$ {
        #    root           html;
        #    fastcgi_pass   127.0.0.1:9000;
        #    fastcgi_index  index.php;
        #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
        #    include        fastcgi_params;
        #}

		#禁止访问 .htaccess 文件
        # deny access to .htaccess files, if Apache's document root
        # concurs with nginx's one
        #
        #location ~ /\.ht {
        #    deny  all;
        #}
    }

	
	#配置另一个虚拟主机
    # another virtual host using mix of IP-, name-, and port-based configuration
    #
    #server {
    #    listen       8000;
    #    listen       somename:8080;
    #    server_name  somename  alias  another.alias;

    #    location / {
    #        root   html;
    #        index  index.html index.htm;
    #    }
    #}

	
	#配置https服务，安全的网络传输协议，加密传输，端口443，运维来配置
	#
    # HTTPS server
    #
    #server {
    #    listen       443 ssl;
    #    server_name  localhost;

    #    ssl_certificate      cert.pem;
    #    ssl_certificate_key  cert.key;

    #    ssl_session_cache    shared:SSL:1m;
    #    ssl_session_timeout  5m;

    #    ssl_ciphers  HIGH:!aNULL:!MD5;
    #    ssl_prefer_server_ciphers  on;

    #    location / {
    #        root   html;
    #        index  index.html index.htm;
    #    }
    #}
}
```

**Nginx的核心配置文件主要由三个部分构成**

+ 基本配置
+ events配置
+ http配置

## 基本配置

```
#配置worker进程运行用户 nobody也是一个linux用户，一般用于启动程序，没有密码
user  nobody;  
#配置工作进程数目，根据硬件调整，通常等于CPU数量或者2倍于CPU数量
worker_processes  1;  

#配置全局错误日志及类型，[debug | info | notice | warn | error | crit]，默认是error
error_log  logs/error.log;  
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

pid        logs/nginx.pid;  #配置进程pid文件 
```

查看worker进程的运行用户：

![image-20240908134322028](https://gitee.com/LowProfile666/image-bed/raw/master/img/202409081343097.png)

日志级别从左往右、由高到低，高的兼容低的：debug | info | notice | warn | error | crit

进程pid文件只存放nginx进程的pid号。

## events配置

```
#配置工作模式和连接数
events {
    worker_connections  1024;  
    #配置每个worker进程连接数上限，nginx支持的总连接数就等于worker_processes * worker_connections
}
```

worker_connections 的上限是65535，也就是说，一个woker进程最大连接数就是65535。

## http配置

### 基础配置

```python
#配置http服务器,利用它的反向代理功能提供负载均衡支持
http {
    #配置nginx支持哪些多媒体类型，可以在conf/mime.types查看支持哪些多媒体类型
    include       mime.types;  
    #默认文件类型 流类型，可以理解为支持任意类型
    default_type  application/octet-stream;  
    #配置日志格式 
    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #配置access.log日志及存放路径，并使用上面定义的main日志格式
    #access_log  logs/access.log  main;

    sendfile        on;  #开启高效文件传输模式
    #tcp_nopush     on;  #防止网络阻塞

    #keepalive_timeout  0;
    keepalive_timeout  65;  #长连接超时时间，单位是秒

    #gzip  on;  #开启gzip压缩输出
```

如果你的多媒体类型不在types中，那么会使用默认的文件类型打开，也就是default_type配置的类型。

log_format 后面是一个变量名，用于下面指定写入日志的格式。

http的日志会记录该http块中所有的server块的访问记录。

gzip 压缩会将IO流中的数据进行压缩，比如删掉一些无用的空格等，提高IO流的传输效率。

### server配置

```python
#配置虚拟主机
server {
    listen       80;  #配置监听端口
    server_name  localhost;  #配置服务名

    #charset koi8-r;  #配置字符集

    #access_log  logs/host.access.log  main;  #配置本虚拟主机的访问日志

    #默认的匹配斜杠/的请求，当访问路径中有斜杠/，会被该location匹配到并进行处理
    location / {
        #root是配置服务器的默认网站根目录位置，默认为nginx安装主目录下的html目录
        root   html;  
        #配置首页文件的名称
        index  index.html index.htm;  
    }		

    #error_page  404              /404.html;  #配置404页面
    # redirect server error pages to the static page /50x.html
    #error_page   500 502 503 504  /50x.html;  #配置50x错误页面

    #精确匹配
    location = /50x.html {
        root   html;
    }

    #PHP 脚本请求全部转发到Apache处理
    # proxy the PHP scripts to Apache listening on 127.0.0.1:80
    #
    #location ~ \.php$ {
    #    proxy_pass   http://127.0.0.1;
    #}

    #PHP 脚本请求全部转发到FastCGI处理
    # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
    #
    #location ~ \.php$ {
    #    root           html;
    #    fastcgi_pass   127.0.0.1:9000;
    #    fastcgi_index  index.php;
    #    fastcgi_param  SCRIPT_FILENAME  /scripts$fastcgi_script_name;
    #    include        fastcgi_params;
    #}

    #禁止访问 .htaccess 文件
    # deny access to .htaccess files, if Apache's document root
    # concurs with nginx's one
    #
    #location ~ /\.ht {
    #    deny  all;
    #}
}
```

一个http配置中可以有多个server配置。但是多个server之间的端口号 listen 和域名 server_name 不能完全相同。

+ 如果两个server的listen都是 80，没有问题，但是server_name不能一样
+ 如果两个server的server_name一样，没有问题，但是 listen 不能一样

server总的access_log只记录访问当前server的日志。

`location /` 用来拦截根路径，域名加端口就是根路径。nginx会拦截该请求，将请求转发到root指定的路径去，该root指定的路径就是服务器本地磁盘上的根路径。index 是指定主页。

注意：location / 这个 / 表示请求的根路径，这个根路径会对应到 root 指定的服务器磁盘上的根路径，所以如果是 location /ace，root是 html，那么其实访问的是服务器上的 html/ace 路径，所以如果 html 下没有这个 ace 目录，就会报 404。

# 静态网站部署

Nginx是一个HTTP的web服务器，可以将服务器上的静态文件（如HTML、图片等）通过HTTP协议返回给浏览器客户端。

在nginx.conf中写一个sever块配置：

```python
server {
    listen 81;
    server_name 47.109.78.124;

    location /ace {
        root /usr/share/nginx/html;
        index login.html;
    }
}
```

要在 /usr/share/nginx/html 目录下新建一个文件夹 ace，然后将静态资源放到该文件夹中，然后重启nginx，访问 47.109.78.124:81/ace。

这个 47.109.78.124:81/ 就等价于 /usr/share/nginx/html，所以要在 /usr/share/nginx/html 下创建一个 ace 目录，才能访问到目标地址 47.109.78.124:81/ace。

> **location匹配顺序**：
>
> 在没有标识符的请求下，匹配规则如下：
>
> 1、nginx服务器首先在server块的多个location块中搜索是否有标准的uri和请求字符串匹配。如果有多个标准uri可以匹配，就匹配其中匹配度最高的一个location。
>
> 2、然后，nginx在使用location块中，正则uri和请求字符串，进行匹配。如果正则匹配成功，则结束匹配，并使用这个location处理请求；如果正则匹配失败，则使用标准uri中，匹配度最高的location。备注：
>
> + 1、如果有精确匹配，会先进行精确匹配，匹配成功，立刻返回结果。
>
> + 2、普通匹配与顺序无关，因为按照匹配的长短来取匹配结果。
>
> + 3、正则匹配与顺序有关，因为是从上往下匹配。(首先匹配，就结束解析过程)
>
> + 4、在location中，有一种统配的location，所有的请求，都可以匹配，如下：
>
>   ```python
>   location / { 
>       # 因为所有的地址都以 / 开头，所以这条规则将匹配到所有请求 
>       # 但是正则和最长字符串会优先匹配
>   } 
>   ```
>
> 结合标识符，匹配顺序如下：(location =) > (location 完整路径) > (location ^~ 路径) > (location ~,~* 正则顺序) > (location 部分起始路径) > (location /)即（精确匹配）> (最长字符串匹配，但完全匹配) >（非正则匹配）>（正则匹配）>（最长字符串匹配，不完全匹配）>（location通配）

# 负载均衡

在网站创立初期，我们一般都使用单台机器对外提供集中式服务。随着业务量的增大，我们一台服务器不够用，此时就会把多台机器组成一个集群对外提供服务，但是，我们网站对外提供的访问入口通常只有一个，比如 www.web.com。那么当用户在浏览器输入www.web.com进行访问的时候，如何将用户的请求分发到集群中不同的机器上呢，这就是负载均衡要做的事情。

负载均衡通常是指将请求"均匀"分摊到集群中多个服务器节点上执行，这里的均匀是指在一个比较大的统计范围内是基本均匀的，并不是完全均匀。

负载均衡实现有：

+ 硬件负载均衡：比如 F5、深信服、Array 等。优点是有厂商专业的技术服务团队提供支持，性能稳定；缺点是费用昂贵，对于规模较小的网络应用成本太高
+ 软件负载均衡：比如 Nginx、LVS、HAProxy 等。优点是免费开源，成本低廉

## nginx负载均衡

Nginx通过在nginx.conf文件进行配置即可实现负载均衡。

原理：

![image-20240908144909518](https://gitee.com/LowProfile666/image-bed/raw/master/img/202409081449613.png)

配置：

### 1. upstream配置

**upstream是配置nginx与后端服务器负载均衡非常重要的一个模块**，并且它还能对后端的服务器的健康状态进行检查，若后端服务器中的一台发生故障，则前端的请求不会转发到该故障的机器

```python
upstream www.myweb.com { 
     	server  127.0.0.1:9100 weight=3; 
      	server  127.0.0.1:9200 weight=1;  
} 
```

其中weight=1表示权重，用于后端服务器性能不均的情况，访问比率约等于权重之比，权重越大访问机会越多。

如果没有指定weight，会采用默认的轮询机制，就是第一次请求发送到第一个server，第二次请求发送到第二个server，第三次请求再发送到第一个server，upstream里的server轮流来。

```python
upstream www.myweb.com { 
     	server  127.0.0.1:9100;
      	server  127.0.0.1:9200;  
} 
```

upstream 后面的字符串是一个变量名，可以随便写，但是要在下面的proxy_pass的配置中保持一致。

### 2. 配置proxy_pass

```python
location /myweb {
	proxy_pass http://www.myweb.com;
}
```

其中 www.myweb.com 字符串要和 upstream 后面的字符串相等。

proxy_pass 和 http:// 这两部分都是固定写的，后面的部分是上面upstream的名字，当访问 /myweb 这个路径时，会被转发到 http://www.myweb.com 上。

### 3. 示例

现在服务器上有两个tomcat服务器，一个端口是8080，一个端口是8081，有一个myweb.war包，放到tomcat的webapps下，然后启动两个tomcat，正常访问：http://47.109.78.124:8081/myweb/，http://47.109.78.124:8080/myweb/。

现在要使用nginx来实现负载均衡。先修改nginx的配置文件：

```python
upstream myweb {
    server localhost:8080;
    server localhost:8081;
}

server {
    listen 80;
    server_name 47.109.78.124;

    location /myweb {
        proxy_pass http://myweb;
    }
}
```

现在访问http://47.109.78.124/myweb/，它会轮流去访问 localhost:8080 和 localhost:8081。

## nginx常用负责均衡策略

### 轮询（默认）

**注意：这里的轮询并不是每个请求轮流分配到不同的后端服务器，**与ip_hash类似，但是按照访问url的hash结果来分配请求，使得每个url定向到同一个后端服务器，主要应用于后端服务器为缓存时的场景下。**如果后端服务器down掉，将自动剔除**

```python
upstream backserver { 
    server 127.0.0.1:8080; 
    server 127.0.0.1:9090; 
} 
```

### 权重

每个请求按一定比例分发到不同的后端服务器，weight值越大访问的比例越大，用于后端服务器性能不均的情况

```python
upstream backserver { 
    server 192.168.0.14 weight=5; 
    server 192.168.0.15 weight=2; 
} 
```

### ip_hash

ip_hash也叫IP绑定，每个请求按访问ip的hash值分配，这样每个访问客户端会固定访问一个后端服务器，可以解决会话Session丢失的问题。算法：hash("124.207.55.82") % 2 = 0, 1

```python
upstream backserver { 
    ip_hash; 
    server 127.0.0.1:8080; 
    server 127.0.0.1:9090; 
}
```

### 最少连接

web请求会被转发到连接数最少的服务器上

```python
upstream backserver { 
    least_conn;
    server 127.0.0.1:8080; 
    server 127.0.0.1:9090; 
}	
```

## 其他配置

备份服务器：

```python
upstream backserver { 
    server 127.0.0.1:9100;
    # 其它所有的非backup机器down的时候，才请求backup机器
    server 127.0.0.1:9200 backup; 
} 
```

假设有多态服务器部署着项目，现在项目要更新，就可以先更新backup这一台服务器，然后关闭其他服务器来更新，这样用户随时访问都是新的项目，等其他服务器跟新完毕后才重新运行起来。

不参与的服务器：

```python
upstream backserver { 
    server 127.0.0.1:9100;
    # down表示当前的server是down状态，不参与负载均衡
    server 127.0.0.1:9200 down; 
} 
```

一般在项目上线的时候，可以分配部署不同的服务器上，然后对Nginx重新reload。reload不会影响用户的访问，或者可以给一个提示页面,系统正在升级...

# 静态代理

把所有静态资源的访问改为访问nginx，而不是访问tomcat，这种方式叫静态代理。因为nginx更擅长于静态资源的处理，性能更好，效率更高。

所以在实际应用中，我们将静态资源比如图片、css、html、js等交给nginx处理，而不是由tomcat处理。

![image-20240908164215997](https://gitee.com/LowProfile666/image-bed/raw/master/img/202409081642100.png)

静态代理的实现也是通过location拦截路径实现的，一般会使用正则表达式，比如根据资源的后缀名来拦截：

```python
location ~ .*\.(js|css|htm|html|gif|jpg|jpeg|png|bmp|swf|ioc|rar|zip|txt|flv|mid
                |doc|ppt|pdf|xls|mp3|wma)$ {
    root /opt/static;
}
```

这个location表示，当访问静态资源（比如 xxx.js），则从linux服务器/opt/static目录下获取。

+ ~ 表示正则匹配，也就是说后面的内容可以是正则表达式匹配
+ 第一个点 `.` 表示任意字符
+ `*`表示一个或多个字符
+ `\.` 是转义字符，是后面这个点的转义字符
+ `|` 表示或者
+ `$` 表示结尾

放置静态资源的目录（这里是/opt/static），要注意一下目录权限问题，如果权限不足，给目录赋予权限； 否则会出现403错误

还可以使用拦截静态资源所在的目录：

```python
location ~ .*/(css|js|img|images) {
    root   /opt/static;
}
```

这个location不匹配具体的资源类型，只匹配资源所在的目录。

# 动静分离

Nginx的负载均衡和静态代理结合在一起，我们可以实现动静分离，这是实际应用中常见的一种场景。

动态资源，如jsp由tomcat或其他web服务器完成

静态资源，如图片、css、js等由nginx服务器完成

它们各司其职，专注于做自己擅长的事情

动静分离充分利用了它们各自的优势，从而达到更高效合理的架构。

![image-20240908165832877](https://gitee.com/LowProfile666/image-bed/raw/master/img/202409081658966.png)

整个架构中，一个nginx负责负载均衡，两个nginx负责静态代理。Nginx在一台Linux上安装一份，可以启动多个Nginx，每个Nginx的配置文件不一样即可。

动态资源的负载均衡：

```python
upstream www.myweb.com { 
    ip_hash;
    server  127.0.0.1:8080 weight=5; 
    server  127.0.0.1:8081 weight=2;  
}
location /myweb {
    proxy_pass http://www.myweb.com;
}
```

静态资源的负载均衡：

```python
upstream static.myweb.com { 
    server  127.0.0.1:81 weight=1; 
    server  127.0.0.1:82 weight=1;  
}

location ~ .*/(css|js|img|images) {
    proxy_pass http://static.myweb.com;
}
```

再启动两台nginx服务器，配置文件中端口分别写 81 和 82，使用配置文件的方式启动即可。

# 虚拟主机

虚拟主机，就是把一台物理服务器划分成多个“虚拟”的服务器，这样我们的一台物理服务器就可以当做多个服务器来使用，从而可以配置多个网站。

Nginx提供虚拟主机的功能，就是为了让我们不需要安装多个Nginx，就可以运行多个域名不同的网站。

Nginx下，一个server标签就是一个虚拟主机。nginx的虚拟主机就是通过nginx.conf中server节点指定的，想要设置多个虚拟主机，配置多个server节点即可；

例如：[www.meituan.com](http://www.meituan.com) 切换城市，可以看到不同的城市地址不一样（二级域名）

比如一个公司有多个二级域名，没有必要为每个二级域名都提供一台Nginx服务器，就可以使用虚拟主机技术，在一台nginx服务器上，模拟多个虚拟服务器。

## 基于端口的虚拟主机

基于端口的虚拟主机配置，使用端口来区分。浏览器使用 同一个域名+端口 或 同一个ip地址+端口访问；

```python
server {
    listen 8080;
    server_name www.myweb.com;
    location /myweb {
        proxy_pass http://www.myweb.com;
    }
}
server {
    listen 9090;
    server_name www.myweb.com;
    location /p2p {
        proxy_pass http://www.p2p.com;
    }
}
```

## 基于域名的虚拟主机

基于域名的虚拟主机是最常见的一种虚拟主机：

```python
server {
    listen       80;
    server_name  www.myweb.com;
    location /myweb {
        proxy_pass http://www. myweb.com;
    }
}
server {
    listen       80;
    server_name  www.p2p.com;
    location /myweb {
        proxy_pass http://www.p2p.com;
    }
}
```

需要修改一下本地的hosts文件，文件位置：C:\Windows\System32\drivers\etc\hosts，在hosts文件配置：

```python
192.168.208.128 www.myweb.com
192.168.208.128 www.p2p.com
```

前面是Linux的IP，后面是你自定义的域名。这是为了在主机上访问 www.myweb.com 和 www.p2p.com 这两个地址的时候，会被映射到 192.168.208.128。

