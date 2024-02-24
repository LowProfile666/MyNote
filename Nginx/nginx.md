[笔记原文](https://www.nginx.org.cn/article/detail/545)

# Nginx 介绍

传统的 Web 服务器，每个客户端连接作为一个单独的进程或线程处理，需在切换任务时将 CPU 切换到新的任务并创建一个新的运行时上下文，消耗额外的内存和 CPU 时间，当并发请求增加时，服务器响应变慢，从而对性能产生负面影响。

Nginx 是开源、高性能、高可靠的 Web 和反向代理服务器，而且支持热部署，几乎可以做到 7 * 24 小时不间断运行，即使运行几个月也不需要重新启动，还能在不间断服务的情况下对软件版本进行热更新。性能是 Nginx 最重要的考量，其占用内存少、并发能力强、能支持高达 5w 个并发连接数，最重要的是，Nginx 是免费的并可以商业化，配置使用也比较简单。

## 正向代理和反向代理

反向代理（Reverse Proxy）对应的是正向代理（Forward Proxy），他们的区别：

**正向代理**： 一般的访问流程是客户端直接向目标服务器发送请求并获取内容，使用正向代理后，客户端改为向代理服务器发送请求，并指定目标服务器（原始服务器），然后由代理服务器和原始服务器通信，转交请求并获得的内容，再返回给客户端。正向代理隐藏了真实的客户端，为客户端收发请求，使真实客户端对服务器不可见；

举个具体的例子 🌰，你的浏览器无法直接访问谷哥，这时候可以通过一个代理服务器来帮助你访问谷哥，那么这个服务器就叫正向代理。

**反向代理**： 与一般访问流程相比，使用反向代理后，直接收到请求的服务器是代理服务器，然后将请求转发给内部网络上真正进行处理的服务器，得到的结果返回给客户端。反向代理隐藏了真实的服务器，为服务器收发请求，使真实服务器对客户端不可见。一般在处理跨域请求的时候比较常用。现在基本上所有的大型网站都设置了反向代理。

举个具体的例子 🌰，去饭店吃饭，可以点川菜、粤菜、江浙菜，饭店也分别有三个菜系的厨师 👨‍🍳，但是你作为顾客不用管哪个厨师给你做的菜，只用点菜即可，小二将你菜单中的菜分配给不同的厨师来具体处理，那么这个小二就是反向代理服务器。

简单的说，一般给客户端做代理的都是正向代理，给服务器做代理的就是反向代理。

# Nginx 安装

先看看 yum 库中有哪些版本：

```bash
yum list | grep nginx
```

![image-20240221220224595](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402212202656.png)

然后安装：

```bash
yum install nginx -y
```

安装过后，可以查看 nginx 的版本：

```bash
nginx -v
```

![image-20240221220343564](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402212203595.png)

# Nginx 相关文件夹

使用以下命令，查看 Nginx 被安装到了什么地方，有哪些目录：

```bash
rpm -ql nginx
```

![Xnip2020-03-07_21-46-11](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402212207971.jpeg)

主要关注文件夹有两个：

+ `/etc/nginx/conf.d`：是我们进行子配置的配置项存放处，`/etc/nginx/nginx.conf `主配置文件会默认把这个文件夹中所有子配置项都引入；
+ `/usr/share/nginx/html/`：通常静态文件都放在这个文件夹，也可以根据你自己的习惯放其他地方；

# Nginx 运行

安装之后开启 Nginx，如果系统开启了防火墙，那么需要设置一下在防火墙中加入需要开放的端口，下面列举几个常用的防火墙操作（没开启的话不用管这个）：

```bash
systemctl start firewalld  # 开启防火墙
systemctl stop firewalld   # 关闭防火墙
systemctl status firewalld # 查看防火墙开启状态，显示running则是正在运行
firewall-cmd --reload      # 重启防火墙，永久打开端口需要reload一下

# 添加开启端口，--permanent表示永久打开，不加是临时打开重启之后失效
firewall-cmd --permanent --zone=public --add-port=8888/tcp

# 查看防火墙，添加的端口也可以看到
firewall-cmd --list-all
```

设置 Nginx 开机启动：

```bash
systemctl enable nginx
```

启动 nginx：

```bash
systemctl start nginx
```

这时候访问自己的 IP 就可以访问到 Nginx 的欢迎页面：
![image-20240221220924632](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402212209693.png)

# 安装 nvm & node & git

## 安装 nvm

`nvm` 是 Node.js 的版本管理工具，全称是 Node Version Manager。它允许你在同一台计算机上同时安装多个不同版本的 Node.js，并且能够轻松地在这些版本之间切换。

`nvm` 在操作系统中创建一个隐藏的目录（通常是 `~/.nvm`），并在其中管理不同版本的 Node.js 及其相关的 npm 包管理器。

下载 nvm，或者看官网的[步骤](https://github.com/nvm-sh/nvm#install--update-script) 

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
```

安装完毕后，更新配置文件，然后就可使用 nvm 命令：

```bash
source ~/.bashrc  # 更新配置文件
```

运行 `source ~/.bashrc` 命令会重新加载 `~/.bashrc` 文件，从而使其中的任何更改立即生效。这样，就可以在当前会话中使用 `nvm` 命令了，而不需要关闭并重新打开终端。

## 安装 node

查看 node 版本：

```bash
nvm ls-remote
```

选择自己需要的版本安装：

```bash
nvm install v20.11.1
```

安装完后查看安装的版本：

```bash
node list
```

查看是否安装成功：

```bash
node -v
```

## 安装 git

```bash
yum install git
```

# Nginx 常用操作命令

Nginx 的命令在控制台中输入 `nginx -h` 就可以看到完整的命令，这里列举几个常用的命令：

```bash
nginx -s reload  # 向主进程发送信号，重新加载配置文件，热重启
nginx -s reopen	 # 重启 Nginx
nginx -s stop    # 快速关闭
nginx -s quit    # 等待工作进程处理完成后关闭
nginx -T         # 查看当前 Nginx 最终的配置
nginx -t -c     # 检查配置是否有问题，如果已经在配置目录，则不需要-c
```

`systemctl` 是 Linux 系统应用管理工具 `systemd` 的主命令，用于管理系统，我们也可以用它来对 Nginx 进行管理，相关命令如下：

```bash
systemctl start nginx    # 启动 Nginx
systemctl stop nginx     # 停止 Nginx
systemctl restart nginx  # 重启 Nginx
systemctl reload nginx   # 重新加载 Nginx，用于修改配置后
systemctl enable nginx   # 设置开机启动 Nginx
systemctl disable nginx  # 关闭开机启动 Nginx
systemctl status nginx   # 查看 Nginx 运行状态
```

# Nginx 配置语法

Nginx 的主配置文件是 `/etc/nginx/nginx.conf`，你可以使用 `cat -n /etc/nginx/nginx.conf` 来查看配置。

`nginx.conf` 结构图可以这样概括：

```bash
main        # 全局配置，对全局生效
├── events  # 配置影响 Nginx 服务器或与用户的网络连接
├── http    # 配置代理，缓存，日志定义等绝大多数功能和第三方模块的配置
│   ├── upstream # 配置后端服务器具体地址，负载均衡配置不可或缺的部分
│   ├── server   # 配置虚拟主机的相关参数，一个 http 块中可以有多个 server 块
│   ├── server
│   │   ├── location  # server 块可以包含多个 location 块，location 指令用于匹配 uri
│   │   ├── location
│   │   └── ...
│   └── ...
└── ...
```

一个 Nginx 配置文件的结构就像 nginx.conf 显示的那样，配置文件的语法规则：

1. 配置文件由指令与指令块构成；
2. 每条指令以 ; 分号结尾，指令与参数间以空格符号分隔；
3. 指令块以 {} 大括号将多条指令组织在一起；
4. include 语句允许组合多个配置文件以提升可维护性；
5. 使用 # 符号添加注释，提高可读性；
6. 使用 $ 符号使用变量；
7. 部分指令的参数支持正则表达式；

## 典型配置

Nginx 的典型配置：

```bash
user  nginx;                        # 运行用户，默认即是nginx，可以不进行设置
worker_processes  1;                # Nginx 进程数，一般设置为和 CPU 核数一样
error_log  /var/log/nginx/error.log warn;   # Nginx 的错误日志存放目录
pid        /var/run/nginx.pid;      # Nginx 服务启动时的 pid 存放位置

events {
    use epoll;     # 使用epoll的I/O模型(如果你不知道Nginx该使用哪种轮询方法，会自动选择一个最适合你操作系统的)
    worker_connections 1024;   # 每个进程允许最大并发数
}

http {   # 配置使用最频繁的部分，代理、缓存、日志定义等绝大多数功能和第三方模块的配置都在这里设置
    # 设置日志模式
    log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';

    access_log  /var/log/nginx/access.log  main;   # Nginx访问日志存放位置

    sendfile            on;   # 开启高效传输模式
    tcp_nopush          on;   # 减少网络报文段的数量
    tcp_nodelay         on;
    keepalive_timeout   65;   # 保持连接的时间，也叫超时时间，单位秒
    types_hash_max_size 2048;

    include             /etc/nginx/mime.types;      # 文件扩展名与类型映射表
    default_type        application/octet-stream;   # 默认文件类型

    include /etc/nginx/conf.d/*.conf;   # 加载子配置项
    
    server {
    	listen       80;       # 配置监听的端口
    	server_name  localhost;    # 配置的域名
    	
    	location / {
    		root   /usr/share/nginx/html;  # 网站根目录
    		index  index.html index.htm;   # 默认首页文件
    		deny 172.168.22.11;   # 禁止访问的ip地址，可以为all
    		allow 172.168.33.44； # 允许访问的ip地址，可以为all
    	}
    	
    	error_page 500 502 503 504 /50x.html;  # 默认50x对应的访问页面
    	error_page 400 404 error.html;   # 同上
    }
}
```

server 块可以包含多个 location 块，location 指令用于匹配 uri，语法：

```bash
location [ = | ~ | ~* | ^~] uri {
	...
}
```

指令后面：

+ `=` 精确匹配路径，用于不含正则表达式的 uri 前，如果匹配成功，不再进行后续的查找；
+ `^~` 用于不含正则表达式的 uri 前，表示如果该符号后面的字符是最佳匹配，采用该规则，不再进行后续的查找；
+ `~` 表示用该符号后面的正则去匹配路径，区分大小写；
+ `~*` 表示用该符号后面的正则去匹配路径，不区分大小写。跟 ~ 优先级都比较低，如有多个location的正则能匹配的话，则使用正则表达式最长的那个；
+ 如果 uri 包含正则表达式，则必须要有 ~ 或 ~* 标志。

# 设置二级域名虚拟主机

有一个域名，就可以配置虚拟主机了。一般配置的路径在 `域名管理 -> 解析 -> 添加记录` 中添加二级域名，[我的阿里云地址](https://dns.console.aliyun.com/#/dns/setting/zsm666.cn)，配置后某某云会把二级域名也解析到我们配置的服务器 IP 上，然后我们在 Nginx 上配置一下虚拟主机的访问监听，就可以拿到从这个二级域名过来的请求了。

配置结果：

![image-20240221234725228](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402212347272.png)

+ 主机记录：配置的二级域名
+ 记录值：服务器IP

二级域名配置好了后，就可以在浏览器中访问 fe.zsm666.cn 的时候，访问到我的服务器。

然后在 nginx 中配置，由于默认配置文件 `/etc/nginx/nginx.conf` 的 http 模块中有一句 `include /etc/nginx/conf.d/*.conf` 也就是说 `/etc/nginx/conf.d` 文件夹下的所有 `*.conf` 文件都会作为子配置项被引入配置文件中。为了维护方便，我在 `/etc/nginx/conf.d` 文件夹中新建一个 `fe.zsm666.cn.conf` ：

```conf
server {
	listen 80;
	server_name fe.zsm666.cn;

	location / {
		root  /usr/share/nginx/html/fe;
		index index.html;
	}
}
```

然后在 `/usr/share/nginx/html` 文件夹下新建 fe 文件夹，新建文件 `index.html`，内容随便写点，改完 `nginx -s reload` 重新加载，浏览器中输入 fe.zsm666.cn，发现从二级域名就可以访问到我们刚刚新建的 fe 文件夹。

# 配置反向代理

反向代理是工作中最常用的服务器功能，经常被用来解决跨域问题，下面简单介绍一下如何实现反向代理。

首先进入 Nginx 的主配置文件：

```bash
vim /etc/nginx/nginx.conf
```

 然后我们去 `http` 模块的 `server` 块中的 `location /`，增加一行将默认网址重定向到最大学习网站 Bilibili 的 `proxy_pass` 配置 🤓 ：

![image-20200311153131642](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402220002908.jpeg)

改完保存退出，`nginx -s reload` 重新加载，进入默认网址，那么现在就直接跳转到 B 站了，实现了一个简单的代理。

实际使用中，可以将请求转发到本机另一个服务器上，也可以根据访问的路径跳转到不同端口的服务中。

比如我们监听 9001 端口，然后把访问不同路径的请求进行反向代理：

+ 把访问 `http://127.0.0.1:9001/edu` 的请求转发到 `http://127.0.0.1:8080`
+ 把访问 `http://127.0.0.1:9001/vod` 的请求转发到 `http://127.0.0.1:8081` 

这种要怎么配置呢，首先同样打开主配置文件，然后在 http 模块下增加一个 server 块：

```bash
server {
  listen 9001;
  server_name *.zsm666.cn;

  location ~ /edu/ {
    proxy_pass http://127.0.0.1:8080;
  }
  
  location ~ /vod/ {
    proxy_pass http://127.0.0.1:8081;
  }
}
```

反向代理还有一些其他的指令，可以了解一下：

+ `proxy_set_header`：在将客户端请求发送给后端服务器之前，更改来自客户端的请求头信息；
+ `proxy_connect_timeout`：配置 Nginx 与后端代理服务器尝试建立连接的超时时间；
+ `proxy_read_timeout`：配置 Nginx 向后端服务器组发出 read 请求后，等待相应的超时时间；
+ `proxy_send_timeout`：配置 Nginx 向后端服务器组发出 write 请求后，等待相应的超时时间；
+ `proxy_redirect`：用于修改后端服务器返回的响应头中的 Location 和 Refresh。

# 跨域问题

