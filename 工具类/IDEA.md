# IDEA 

## 1. 安装目录介绍

![image-20230912120122476](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121201533.png)

核心目录 `bin` 介绍：

![image-20230912120312638](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121203651.png)

VM 默认配置（双斜线注释内容是自己添上的）：

```
-Xms128m  // 占用最小内存
-Xmx750m  // 占用最大内存
-XX:ReservedCodeCacheSize=512m  // 代码占用的缓存大小
-XX:+UseG1GC
-XX:SoftRefLRUPolicyMSPerMB=50
-XX:CICompilerCount=2
-XX:+HeapDumpOnOutOfMemoryError
-XX:-OmitStackTraceInFastThrow
-XX:+IgnoreUnrecognizedVMOptions
-XX:CompileCommand=exclude,com/intellij/openapi/vfs/impl/FilePartNodeRoot,trieDescend
-ea
-Dsun.io.useCanonCaches=false
-Dsun.java2d.metal=true
-Djbr.catch.SIGABRT=true
-Djdk.http.auth.tunneling.disabledSchemes=""
-Djdk.attach.allowAttachSelf=true
-Djdk.module.illegalAccess.silent=true
-Dkotlinx.coroutines.debug=off
```

可以添加：

```
Dfile.enconding=UTF-8  // 设置文件编码格式
Dconsole.enconding=UTF-8  // 设置控制台编码格式
```

## 2. 创建项目

一个 project 并不是一个存粹的 Java 工程或者 Java Web 工程。

+ IDEA 中的 project 类似于 eclipse 中的 workspace ，类似于一个文件夹
+ IDEA 中的 Moudle 则类似于 eclipse 中的 project，一个具体的代码项目
+ 一般，可以创建一个 empty 的 project，然后再在 project 中创建各种 Moudle。

项目界面：

![image-20230912123519673](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121235752.png)

## 3. 常用配置

设置位置在：File - Setting，或者右上角的小齿轮 - Setting

### 3.1 设置打开时界面

Settings - System Settings - Project ：

![image-20230912124127536](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121241596.png)

### 3.2 设置字体

外观字体大小：

![image-20230912124645682](C:/Users/20620/AppData/Roaming/Typora/typora-user-images/image-20230912124645682.png)

编辑器字体大小：

![image-20230912124609677](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121246706.png)

### 3.3 设置自动导包

![image-20230912124938383](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121249411.png)

### 3.4 设置行号和方法分隔符

![image-20230912125121654](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121251693.png)

### 3.5 设置代码提示规则

![image-20230912125318027](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121253055.png)

这个设置用于IDEA的代码提示，比如要输入一个` File` ，

+ 勾选了 `Match case` ，你只有输入 `F` 时才能提示 `File`
+ 不勾选，输入 `f` 时就会提示 `File`

### 3.6 取消单行显示

IDEA默认将打开的文件的代码进行收缩单行显示，但是有时候无法看清代码，需要手动将代码展开，此时可以取消单行显示。

![image-20230912125729375](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121257407.png)

### 3.7 设置编辑区的字体

![image-20230912125839380](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121258404.png)

 ### 3.8 设置编辑区的主题

![image-20230912125941786](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121259812.png)

更多主题下载：http://www.riaway.com/

导入方式：

![image-20230912130100413](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121301440.png)

### 3.9 修改控制台输出的字体

![image-20230912130155334](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121301367.png)

 ### 3.10 修改代码中注释的颜色

![image-20230912130313554](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121303584.png)

### 3.11 修改类头的注释文档

![image-20230912130542200](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121305250.png)

### 3.12 设置项目文件的编码

![](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121309697.png)

上图的勾选项一般都需要勾选，主要用于转换 ASCII，不然 Properties 文件中的注释显示的都不会是中文。

### 3.13 设置自动编译

IDEA默认是不会进行自动编译的。

![image-20230912131157751](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121311786.png)

## 4. 创建空项目和 Module 及相关操作

创建完 empty project 后什么也没有，可以在里面创建 Moudle ，想把 Moudle 变成一个 Web ，可以右键单击这个 Moudle，选择 Add FrameWork Support：

![image-20230912132123476](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309121321499.png)

在 IEDA 中，为了防止开发者误删除，是无法直接删除 Module 的相关代码。只能从项目中移出 Module，但是物理磁盘上的文件是不会删除的。

如果要删除物理文件，需要在物理磁盘上删除

+ 右键单击 Moudle，选择 Remove（只移出了代码），再右键单击 Moudle，选择 Delete（完全删除）
+ 右上角设置图标，Project Structure，Modules，减号（只移出了代码），再右键单击 Moudle，选择 Delete（完全删除）

以后一般创建项目是直接创建 Java project，然后删除原先的 src 文件夹，新建 Moudle ，Moudle 里面自带 src 文件夹。

## 5. 快捷键

### 5.1 修改快捷键风格

![image-20230912224629565](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309122246608.png)

### 5.2 修改快捷键

![image-20230912224856194](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309122248242.png)

### 5.3 常用快捷键

| 快捷键                   | 说明                         |
| ------------------------ | ---------------------------- |
| `ctrl + /`               | 单行注释                     |
| `ctrl + shift + /`       | 多行注释                     |
| `ctrl + d`               | 向下复制一行                 |
| `alt + shift + down`     | 向下移动行                   |
| `alt + shift + up`       | 向上移动行                   |
| `ctrl + 选中指定结构`    | 如何查看源码                 |
| `alt + enter`            | 万能解错/生成返回值变量      |
| `alt + left`             | 退回前一个编辑的页面         |
| `alt + right`            | 进入下一个编辑的页面         |
| `ctrl + alt + l`         | 格式化代码                   |
| `ctrl + p`               | 提示方法参数类型             |
| `ctrl + c`               | 复制                         |
| `ctrl + z`               | 撤销                         |
| `ctrl + shift + z`       | 反撤销                       |
| `ctrl + x`               | 剪切                         |
| `ctrl + v`               | 粘贴                         |
| `ctrl + a`               | 全选                         |
| `alt + 7` / `ctrl + f12` | 查看类的结构                 |
| `shift + f6`             | 重构：修改变量名与方法名     |
| `ctrl + shift + u`       | 大小写转换                   |
| `alt + insert`           | 生成构造器/新建              |
| `ctrl + shift + "+/-"`   | 折叠/展开全部方法            |
| `ctrl + "+/-"`           | 折叠/展开当前方法            |
| `ctrl + alt + f12`       | 打开代码所在硬盘文件夹选择器 |
| `ctrl + shift + f12`     | 最大化代码编辑器             |
| `ctrl + alt + t`         | 生成 try-catch / if-else 等  |
| `alt + shift + f`        | 添加收藏                     |
| `ctrl + f`               | 查找（当前）                 |
| `ctrl + r`               | 查找/替换（当前）            |
| `ctrl + h`               | 查看类的继承结构             |
| `double shift`           | 查找文件                     |

## 6. IDEA 模板 - Templates

#### 6.1 Live Templates - 代码模板

代码模板是指，配置一些常用的代码字母缩写后，当输入缩写字母时，IDEA 会根据输入的字母缩写，帮助自动完成预设的代码。从而提高编码效率，同时也可以进行个性化设置。

#### 6.2 内置模板

![image-20230913192014239](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131920352.png)

鉴于 Postfix Completion 模板无法改变，IDEA 提供了 Live Templates 模板，用户可以自定义。

#### 6.3 常用模板说明

| 模板       | 说明                      | 效果                                                         |
| ---------- | ------------------------- | ------------------------------------------------------------ |
| `psvm`     | 生成 main 方法            | `public static void main(String[] args) {}`                  |
| `sout`     | 生成打印语句              | `System.out.println();`                                      |
| `soutv`    | 生成打印语句并输出变量    | `System.out.println("a = " + a);`                            |
| `fori`     | 生成 for 循环             | `for (int i = 0; i < ; i++) {}`                              |
| `iter`     | 增强型 for 循环           | `for (String arg : args) {}`                                 |
| `itar`     | 普通 for 循环             | `for (int i = 0; i < args.length; i++) {String arg = args[i];}` |
| `list.for` | 生成集合 list 的 for 循环 | `for (Integer i : list) {}`                                  |
| `ifn`      | 生成 if xx 为 null        | `if (a == null) {}`                                          |
| `psf`      | 在类体中使用              | `public static final `                                       |
| `prsf`     | 在类体中使用              | `private static final     `                                  |
| `psfs`     |                           | `public static final String     `                            |
| `psfi`     |                           | `public static final int `                                   |

#### 6.4 自定义模板

**创建模板组**

![image-20230913193419952](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131934008.png)

**创建模板**

选中创建的模板组，点击 `+` ，选择 Live Template。

![image-20230913193608874](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131936920.png)

**自定义模板**

通过 `$名称$` 的形式声明变量，然后使用内置的函数为变量动态的赋值。

![image-20230913194020238](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131940280.png)

![image-20230913194107764](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131941803.png)

## 7. 配置 Tomcat

在 IDEA 中配置 Tomcat，推荐使用 Maven 插件中的 Tomcat 插件启动项目。

需要自己下载一个 Tomcat。

### 7.1 配置 Tomcat 容器

![image-20230913194407238](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131944280.png)

![image-20230913194447878](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131944913.png)选择自己下载的 Tomcat 的路径即可。

或者在新 UI 下的这里

![image-20230913194842440](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131948483.png)

![image-20230913194924522](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131949560.png)

![image-20230913195049003](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131950067.png)



### 7.2 发布项目

![image-20230913195113130](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131951167.png)

###	7.3 配置第三方 jar 包

![image-20230913195313550](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131953583.png)

![image-20230913195338447](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309131953481.png)

还可以直接在项目下新建一个目录 `lib`，将目标文件拖入这个目录，然后选中，右键，选择 Add as Library。

## 8. Maven 的安装和配置

Maven 是一个免安装的程序，解压即可使用，但是 Maven 管理项目需要使用插件管理生命周期。而需要使用 Maven 的命令，所以需要配置 Maven 的环境变量。Maven 本身使用 Java 开发，也依赖 JDK 的环境变量。

### 8.1 Maven 的目录结构

`bin` ：Maven 中的命令脚本，配置 Maven 在 path 中也是为了能全局使用 Maven 命令。

`conf` ：maven 服务器配置信息：编译环境、镜像等。

### 8.2 配置 Maven 环境变量

在系统的环境变量中配置 `MAVEN-HOME` ，值为 Maven-bin 的路径，然后将这个变量添加到 path 中。

### 8.3 IDEA 集成 Maven

![image-20230913200411998](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132004064.png)

这样只是为当前项目配好了，新建项目时可能还需要配置。

![image-20230913200519513](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132005568.png)

选择这个后，接下来的配置操作同上即可。

### 8.4 创建 Maven 的 Java 项目

![image-20230913200814414](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132008473.png)

### 8.5 创建 Maven 的 Web 项目

![image-20230913201000892](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132010951.png)

### 8.6 创建 Maven 的 SpringBoot 项目

![image-20230913201221333](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132012392.png)

## 9. IDEA 连接数据库

![image-20230913201414685](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132014785.png)

连接数据库需要驱动包，如果没有可以直接点击页面下方的连接下载。

![image-20230913201548027](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132015093.png)

## 10. 特殊功能

### 10.1 代码分栏

![image-20230913201807294](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132018395.png)

### 10.2 命令行终端分栏

![image-20230913202016613](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132020672.png)

### 10.3 禅模式

![image-20230913202137522](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132021556.png)

### 10.4 HttpClient

![image-20230913202258084](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132022133.png)

使用效果：

![image-20230913202349788](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132023869.png)

## 11. 断点调试

单击行号即可打断点。

### 11.1 Debug 设置

### 11.2 常用调试快捷键

| 图标                                                         | DEBUG            | 快捷键            | 说明                                                     |
| ------------------------------------------------------------ | ---------------- | ----------------- | -------------------------------------------------------- |
| ![image-20230913203531355](C:/Users/20620/AppData/Roaming/Typora/typora-user-images/image-20230913203531355.png) | step over        | F8                | 进入下一步，如果当前行断点是一个方法，则不进入方法体内。 |
| ![image-20230913203632307](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132036347.png) | step into        | F7                | 进入下一步，如果当前行断点是一个方法，则进入方法体内。   |
| ![image-20230913203818106](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132040968.png) | force step into  | alt + shift  + F7 | 进入下一步，如果当前行断点是一个方法，则进入方法体内。   |
| ![image-20230913203921279](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132039313.png) | step out         | Shift  + F8       | 跳出                                                     |
| ![image-20230913204144076](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132041102.png) | stop             | Ctrl + F2         | 停止                                                     |
| ![image-20230913204227815](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132042841.png) | mute breakpoints |                   | 所有断点失效                                             |
| ![image-20230913204301419](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132043447.png) | view breakpoints | Ctrl + Shift + F8 | 查看所有断点                                             |
| ![image-20230913204352363](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132043393.png) | resume program   | F9                | 直接去下一个断点                                         |

## 12. IDEA中使用 GIT 协同开发

### 12.1 配置 GIT

![image-20230913204945801](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132049873.png)

### 12.2 使用 git 提交代码

#### 创建本地仓库

![image-20230913205233858](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132054673.png)

成功后有些文件就会变红，表示本地有，但是暂存区以及版本库中都没有

![image-20230913205353956](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132053983.png)

#### 提交到本地

![image-20230913205616490](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132056549.png)

忽略的文件

![image-20230913205144250](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132051304.png)

#### 提交到远程

![image-20230913205846962](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132058019.png)

![image-20230913210055072](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132100128.png)

#### 从远程拉取整个项目

![image-20230913210252554](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132102590.png)

或者

![image-20230913210320446](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132103477.png)

#### 从远程合并代码

![image-20230913210730466](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132107514.png)

使用 fetch 后，点击右小角的 master，会看到本地仓库有个紫色的小箭头，点击，再点击 update 即可。

#### 创建新分支

![image-20230913211005987](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132110041.png)

再使用 push 的时候会自动推送新的分支。

#### 获取远程分支

还是使用 fetch，然后点击右下角的 master，点击新的分支，点击 check out，即可。

#### 把分支合并

要把新分支合并到主分支，要先切换到主分支，然后![image-20230913211336259](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132113312.png)

合并后，记得 push 到远程仓库。

#### 发版，打 tag

![image-20230913211513117](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132115170.png)

然后 push

![image-20230913211552861](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132115888.png)

## 13. 常用插件

### 13.1 Translation

![image-20230913211927314](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309132119367.png)

安装后，可以选词右键翻译，在工具栏上也会有翻译的快捷图标。

### 13.2 CodeGlance

可以查看缩略图一样，快速切换自己想去的地方。

在代码的右边会有一个缩略图。

### 13.3 Alibaba Java Coding Guidlines

阿里巴巴公司试行的开发设计规范。

### 13.4 Maven Helper

主要功能：查找和排除冲突依赖项的简便方法，为包含当前文件或根模块的模块运行/调试 maven 目标的操作，运行/调试当前测试文件的操作。

### 13.5 MyBatisCodeHelperPro

+ 提供 Mapper 接口与配置文件中对应的 SQL 导航
+ 编辑 XML 文件时自动补全
+ 根据 Mapper 接口，使用快捷键生成 xml 文件及 SQL 标签
+ ResultMap 中的 property 支持自动补全，支持级联
+ 快捷键生成 @Param 注解
+ XML 中编辑 SQL 时，括号自动补全，支持参数自动补全
+ 自动检查 Mapper XML 文件中 ID 冲突和错误的属性值
+ 支持 Find Usage
+ 支持重构重命名
+ 支持别名

### 13.6 Lombok

能以简单的注解形式来简化 Java 代码。

默认已安装。

