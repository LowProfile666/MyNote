使用 XShell 连接上远程服务器。

## CentOS8 安装 MySQL8

下载 mysql 安装包：

```bash
wget https://dev.mysql.com/get/mysql80-community-release-el8-1.noarch.rpm
yum install mysql80-community-release-el8-1.noarch.rpm
```

安装 mysql 命令

```bash
yum module disable mysql
```

如果出现 No match for argument: mysql-community-server 报错，需要先禁用CentOS8自带mysql模块

```bash
yum module disable mysql
```

如果以上报错 Error: GPG check FAILED 的话，使用：

```bash
yum install mysql-community-server --nogpgcheck
```

安装成功。

启动 mysql 服务：

```bash
service mysqld start
```

会提示：

```bash
Redirecting to /bin/systemctl start mysqld.service
```

所以正确启动命令：

```bash
/bin/systemctl start mysqld.service
```

可以使用以下命令查看状态：

```bash
service mysqld status
```

显示 mysql 的随机密码：

```bash
grep 'temporary password' /var/log/mysqld.log
```

输出，密码就是 ：j6:?8vyriieK

```bash
[root@zsm ~]# grep 'temporary password' /var/log/mysqld.log
2023-12-11T03:58:34.714530Z 6 [Note] [MY-010454] [Server] A temporary password is generated for root@localhost: j6:?8vyriieK
```

登录：

```bash
mysql -uroot -pj6:?8vyriieK
```

修改密码：

如果密码随便设置的话可能会报错，不满足它的密码策略：

```bash
mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY '123456';
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
```

所以要先修改成一个满足要求的密码，然后修改它的密码策略，最后修改成自己想要的密码：

```bash
# 先将密码修改为满足它密码策略的密码
ALTER USER 'root'@'localhost' IDENTIFIED BY 'Root_21root';

# 查看它的密码策略
SHOW VARIABLES LIKE 'validate_password%';
+-------------------------------------------------+--------+
| Variable_name                                   | Value  |
+-------------------------------------------------+--------+
| validate_password.changed_characters_percentage | 0      |
| validate_password.check_user_name               | ON     |
| validate_password.dictionary_file               |        |
| validate_password.length                        | 8      |
| validate_password.mixed_case_count              | 1      |
| validate_password.number_count                  | 1      |
| validate_password.policy                        | MEDIUM |
| validate_password.special_char_count            | 1      |
+-------------------------------------------------+--------+
# 修改密码长度：
set global validate_password.length=1; 
# 修改密码等级：
set global validate_password.policy=0; 
# 查看修改后的密码策略
SHOW VARIABLES LIKE 'validate_password%';
+-------------------------------------------------+-------+
| Variable_name                                   | Value |
+-------------------------------------------------+-------+
| validate_password.changed_characters_percentage | 0     |
| validate_password.check_user_name               | ON    |
| validate_password.dictionary_file               |       |
| validate_password.length                        | 4     |
| validate_password.mixed_case_count              | 1     |
| validate_password.number_count                  | 1     |
| validate_password.policy                        | LOW   |
| validate_password.special_char_count            | 1     |
+-------------------------------------------------+-------+
# 设置成自己想要的密码:
ALTER USER 'root'@'localhost' IDENTIFIED BY '1234';
```

开放远程访问：

```bash
create user 'root'@'%' identified by 'root123'; //1、先创建权限记录
grant all privileges on *.* to 'root'@'%' with grant option; //2、授权
```

开放防火墙端口：直接在安全组开放mysql端口号。

## 安装 .NET 6 SDK

1. **添加 Microsoft 存储库：**

   ```bash
   sudo rpm -Uvh https://packages.microsoft.com/config/centos/8/packages-microsoft-prod.rpm
   ```

2. **安装 .NET SDK：**

   ```bash
   sudo dnf install dotnet-sdk-6.0
   ```

3. **验证安装：**

   ```bash
   dotnet --version
   ```

   确保输出显示 .NET 6 的版本号，以确保 SDK 安装成功。

在本地发布项目，将项目发布成文件夹的形式，点击发布后，会有一个文件夹：

![image-20231211152440364](https://gitee.com/LowProfile666/image-bed/raw/master/img/202312111527305.png)

登录 mysql，创建一个数据库，然后将本地的数据库文件通过 source 命令将数据导入服务器本地数据库。

在服务器上新建一个文件夹，用来保存上面这个文件夹中的所有文件，将上面文件夹中的文件全部复制到服务器上，然后使用命令启动：

```bash
dotnet NurseExaminationSystem.dll
```

## 在CentOS 8上安装Nginx

从CentOS 8开始，Nginx软件包在默认的CentOS存储库中可用。在CentOS 8上安装Nginx只需输入以下命令：

```bash
sudo yum install nginx -y  (-y 作用是安装过程中 y/n 选择时自动选择y)
```

安装完成后，使用以下命令设置开机启动nginx和启动Nginx服务：

```bash
sudo systemctl enable nginx
sudo systemctl start nginx
```

查看Nginx服务运行状态：

```bash
sudo systemctl status nginx
```

此时如果一切正常，应该会看到如下界面：

![image-20231211154736256](https://gitee.com/LowProfile666/image-bed/raw/master/img/202312111547291.png)

到目前为止，在未启用防火墙的情况下，我们访问http://你的ip，应该能看到如下界面。这说明Nginx安装成功且服务正常启动了。
**注：如果是阿里云服务器，请确保服务器安全组里内网入方向规则里添加了允许80/443端口的规则*

![image-20231211154758267](https://gitee.com/LowProfile666/image-bed/raw/master/img/202312111547322.png)

#### 调整服务器防火墙

  一般情况下，为了安全我们会在服务器上启用防火墙。所以我们需要调整防火墙以开发我们需要运行公开访问的端口。FirewallD是Centos 8上的默认防火墙解决方案。(Centos 7以前可查找iptables相关资料)

  为了使外部用户能够访问您的Web服务器，需要启用到主机的HTTP和HTTPS通信。
修改防火墙规则并添加以下条目：

```bash
sudo firewall-cmd --permanent --zone=public --add-service=http
sudo firewall-cmd --permanent --zone=public --add-service=https
sudo firewall-cmd --reload
```

如果没有启动防火墙，先启动防火墙：

```bash
sudo systemctl start firewalld
```

在项目的 program.cs 文件中的 CreateWebHostBuilder 方法中添加一句：

```cs
webBuilder.UseUrls("http://*:5000");
```

`*`代表任何地址。这样，我们就可以通过ip地址远程访问我们的应用程序啦。

还要将防火墙的 5000 端口打开，

```bash
sudo firewall-cmd --zone=public --add-port=5000/tcp --permanent
sudo firewall-cmd --reload
```

第一条命令添加了永久规则，需要使用 `--reload` 选项重新加载防火墙配置。

还要在阿里云的安全组中添加入方向的策略，放开 5000 端口。

## 启动项目

新建一个数据库，数据库名跟 appsetting.json 中的数据库名一样，mysql8 区分数据库和表名的大小写，所以默认生成的数据库中的表都会变成以下样子：

```bash
+-----------------------------+
| ActionLogs                  |
| Bookmarks                   |
| Chapters                    |
| DataPrivileges              |
| DicDefs                     |
| DicFields                   |
| FileAttachments             |
| FrameworkGroups             |
| FrameworkMenus              |
| FrameworkRoles              |
| FrameworkTenants            |
| FrameworkUserGroups         |
| FrameworkUserRoles          |
| FrameworkUsers              |
| FrameworkWorkflows          |
| FunctionPrivileges          |
| Questions                   |
| Sections                    |
| Triggers                    |
| WorkflowDefinitions         |
| WorkflowExecutionLogRecords |
| WorkflowInstances           |
+-----------------------------+
```

所以我本地使用的数据库的表名都是小写的，如果直接通过 source 命令导进去，会出现找不到表的错误，所以先将数据导进去，然后通过命令修改每个表的名字，就可以了：

```sql
rename table questions to Questions;
```

在项目启动后，登录页面的验证码出现了问题，报错提示找不到 Arial 字体，所以需要先下载这个字体：

## 使用 Systemd 管理应用程序

Systemd 是一个在现代 Linux 系统上管理系统和服务的系统和服务管理器。它可以用于启动、停止、重启和监视应用程序。下面是使用 Systemd 管理 ASP.NET Core 应用程序的基本步骤：

1. **创建 Systemd 服务文件：**

   在 `/etc/systemd/system/` 目录下创建一个新的服务文件，文件名通常以 `.service` 结尾，例如 `your-app.service`。

   ```
   [Unit]
   Description=NurseExaminationSystem
   After=network.target
   
   [Service]
   WorkingDirectory=/root/web
   ExecStart=/usr/bin/dotnet NurseExaminationSystem.dll
   Restart=always
   RestartSec=10
   KillSignal=SIGINT
   SyslogIdentifier=NurseExaminationSystem
   User=root
   Environment=ASPNETCORE_ENVIRONMENT=Production
   
   [Install]
   WantedBy=multi-user.target
   ```

   - `Description`: 服务的描述信息。
   - `After`: 声明服务在 `network.target` 启动后启动。
   - `WorkingDirectory` ：明确设置工作目录
   - `ExecStart`: 指定应用程序启动的命令，这里是启动 ASP.NET Core 应用程序的命令。
   - `Restart`: 设置服务在发生故障时自动重启。
   - `RestartSec`: 两次重启之间的延迟时间（秒）。
   - `KillSignal`: 指定关闭服务的信号。
   - `SyslogIdentifier`: 用于在系统日志中标识服务的标识符。
   - `User`: 指定运行服务的用户。
   - `Environment`: 设置 ASP.NET Core 应用程序的环境变量，例如 `Production`。

2. **重新加载 Systemd 配置：**

   保存服务文件后，使用以下命令重新加载 Systemd 配置：

   ```bash
   sudo systemctl daemon-reload
   ```

3. **启动服务：**

   启动服务使用以下命令：

   ```bash
   sudo systemctl start NurseExaminationSystem
   ```

4. **启用自启动：**

   若要使服务在系统启动时自动启动，使用以下命令启用服务：

   ```bash
   sudo systemctl enable NurseExaminationSystem
   ```

   这将在系统启动时启动你的应用程序服务。

5. **查看服务状态：**

   可以使用以下命令查看服务的状态：

   ```bash
   sudo systemctl status NurseExaminationSystem
   ```

   这将显示服务的详细状态信息，包括是否正在运行、最后一次启动时间等。

6. **查看服务日志：**

   使用 `journalctl` 命令可以查看服务的日志：

   ```bash
   journalctl -u NurseExaminationSystem
   ```

   这将显示与服务相关的日志。

7. **停止和重启服务：**

   使用以下命令停止和重启服务：

   ```bash
   sudo systemctl stop NurseExaminationSystem
   sudo systemctl restart NurseExaminationSystem
   ```

通过以上步骤，你的 ASP.NET Core 应用程序就会通过 Systemd 进行管理，能够在系统启动时自动启动，并能够在发生故障时自动重启。



## 安装Docker

1. 安装必要的依赖：

   ```
   sudo yum install -y yum-utils device-mapper-persistent-data lvm2
   ```

2. 添加 Docker 存储库：

   ```
   sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
   ```

3. 安装 Docker：

   ```
   sudo yum install -y docker-ce docker-ce-cli containerd.io
   ```

4. 启动 Docker 服务：

   ```
   sudo systemctl start docker
   ```

5. 设置 Docker 开机启动：

   ```
   sudo systemctl enable docker
   ```

6. 验证安装是否成功：

   ```
   sudo docker run hello-world
   ```

由于 CentOS8 防火墙使用了 `nftables`，但 Docker 尚未支持 `nftables`，我们可以行如下命令：

```bash
$ firewall-cmd --permanent --zone=trusted --add-interface=docker0
$ firewall-cmd --reload
```

如果您需要获取Docker官方提供的CentOS 8镜像，可以通过以下命令从Docker Hub下载它：

```
复制代码docker pull centos:8
```

这将会下载一个最新版本的CentOS 8 Docker镜像，您可以使用它来创建并运行容器。

运行 Docker 容器：

```bash
docker run -d -p 8080:80 --name your_container_name your_image_name
```

- `docker run`: 这个部分指示 Docker 启动一个新的容器。
- `-d`: 这个选项让容器在后台（detached mode）运行，也就是说，容器会在后台执行，并且不会阻塞终端。
- `-p 8080:80`: 这个选项定义了端口映射。它将容器内的端口 80 映射到主机机器上的端口 8080。这意味着，当你在主机上访问 `localhost:8080` 时，实际上是访问了容器内运行在端口 80 上的应用程序。
- `--name your_container_name`: 这个选项为容器指定了一个名称，可以使用这个名称来引用容器，而不必依赖于自动生成的容器 ID。
- `your_image_name`: 这是你要运行的 Docker 镜像的名称。这应该是你之前使用 `docker build` 命令创建的镜像的名称。

综合起来，整个命令告诉 Docker 在后台运行一个容器，使用端口映射将容器内的端口 80 映射到主机机器的端口 8080，容器的名称是 `your_container_name` ，名称可以随意，使用的镜像是 `your_image_name`。这样，你可以通过访问 `http://localhost:8080` 来访问在容器内运行的应用程序。

卸载docker：

```bash
sudo yum remove docker-ce docker-ce-cli containerd.io
sudo yum erase docker-ce docker-ce-cli containerd.io
sudo rm -rf /var/lib/docker
```

