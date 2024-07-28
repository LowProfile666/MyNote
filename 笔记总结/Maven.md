# maven是什么

maven是一个依赖管理工具，就是一个软件。

# maven的作用

## 1、依赖管理

使用maven前，当一个项目中需要某些依赖时，通常是引入对应的jar包，然后讲这个jar包右键单击添加到类路径，比如要连接数据库，需要引入jar包mysql-connector-j-8.1.0.jar。

使用maven，就可以不用手动导入这些依赖对应的jar包，只需要在pom.xml文件中配置对应依赖的信息即可。

maven仓库：https://mvnrepository.com/

## 2、构建管理

主要应用场景：使用maven，可以快速将一个Java项目打包成war包或jar包。

# maven的使用

下载maven：https://maven.apache.org/docs/history.html

配置maven环境：

+ 配置MAVEN_HOME
+ 配置path中%MAVEN_HOME%\bin
+ 命令行中测试：mvn -v

# maven配置文件

maven的配置文件在maven主目录下的conf中，名为settings.xml。

主要修改配置三个：

+ 依赖本地缓存位置（本地仓库位置）：`<localRepository>`
+ maven下载镜像：`<mirror>`
+ maven选用编译项目的jdk版本：`<profile>`

# IDEA中用maven

## 1、配置

在设置中搜索maven，选择Maven home path为自己的maven主目录，选择User settings file为自己maven目录下的settings.xml文件，选择Local repository为自己的本地仓库文件夹。

## 2、GAVP

Maven 中的 GAVP 是指 GroupId、ArtifactId、Version、Packaging 等四个属性的缩写，其中前三个是必要的，而 Packaging 属性为可选项（默认为jar包方式）。

+ groupId：组id
+ artifactId：工件id
+ version：版本号
+ packaging：打包方式

## 3、创建一个maven项目

