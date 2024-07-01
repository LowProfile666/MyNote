# 目录

## 常用目录

`/` ：根目录

`/bin`：包含一些常用的二进制可执行文件。如cat、ls、mkdir、rm等。这些二进制文件在系统运行时始终可用，可以被任何用户运行。 

`/etc`：包含了系统的大多数配置文件。大多数应用程序在安装后都会在这个目录下创建自己的子目录，以便存储自己的配置文件。 

`/home`：包含Linux系统用户的家目录。每个用户的数据和个人文件都存放在这里。 

`/lib`：包含一些共享库文件。应用程序可以通过这些共享库文件调用系统的功。

`/root`：是系统管理者（超级用户）的家目录。

`/tmp`：是系统中的一个临时目录。所有用户都可以在这里创建临时文件，文件系统会定期清空该目录，以防止文件滞留。 

`/usr`：包含系统启动后，所有用户能访问的应用程序和数据文件。 

`/var`：包含可变数据的文件。它是一个经常被修改的目录，如果在其他目录有可变数据的话，它们都应当被链接到 /var 中。如日志等。

## 家目录

每个用户登录后，默认是在用户的家目录下，使用 `pwd` 命令可以看到当前所在的目录。

root 用户的家目录是 /root：

![image-20240624135637877](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241356927.png)

其他用户的家目录是 /home/用户名：

![image-20240624135839557](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241358589.png)

`~` 表示家目录。

# 基础命令

## --help参数

所有命令都可以使用 --help 参数，来查看命令的大概用法。

查看 pwd 命令的用法：

```shell
pwd --help
```

![image-20240624140353905](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241403975.png)

## man

`man` 命令可以查看某个命令的具体用法。

查看 pwd 命令的用法：

```shell
man pwd
```

![image-20240624140210008](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241402080.png)

+ 使用空格翻页
+ 按 q 退出

## ls

`ls` 命令可以查看目录下子目录和子文件。

ls 命令是 list 的意思，列出、列表等。

### 查看当前目录

查看当前目录下的文件和目录：
```shell
ls
```

![image-20240624140601340](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241406380.png)

### 查看指定目录

查看指定目录下的文件和目录：

```
ls 路径
```

路径名如果是从 / 开始，就是绝对路径；否则就是相对路径，相对路径都是从当前所在的位置开始。

```
ls java21
ls /usr
ls /usr/local
```

![image-20240624141131993](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241411035.png)

也可以同时查看多个目录：

```shell
ls -l java21/ tomcat/
```

![image-20240624150056732](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241500786.png)

### 查看所有

使用 `-a` 参数，a 是 all 所有的意思。

`ls -a` 会列出所有的文件和目录，包括隐藏文件和目录（在Linux操作系统中隐藏文件的文件名通常以"."开始）。

![image-20240624141406409](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241414453.png)

### 长格式查看

使用 `-l` 参数，l 是 long format。

`ls -l` 会以长格式的形式列出所有的文件和目录。

![image-20240624141938224](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241419267.png)

每一行具体表现的信息：

![image.png](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241423582.png)

第二到十列表示文件的权限部分：

+ 前三位：文件拥有者的权限
+ 中三位：跟文件拥有者在同一组的用户的权限
+ 后三位：其他组的用户的权限

`ls -l` 命令可以简写为 `ll` 命令。

也可以用该命令来查看某个文件的信息：

```shell
ls -l dump.rdb 
```

![image-20240624150211177](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241502215.png)

### 模糊匹配

可以通过模糊匹配来查看某些指定的文件信息：

```shell
ls -l *.txt
```

![image-20240624151323705](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241513107.png)

### 参数可以合并

可以同时使用多个参数。

`ls -al` 或者 `ls -la` 都等同于 `ls -a` 加 `ls -l` 的功能，以长格式的样式列出所有的文件和目录。

也可以写 `ll -a`

### 查看inode号

每一个文件都有一个inode号，index node：索引节点号。并且不会重复，在Linux操作系统中通过inode来区分两个文件。

使用 `-i` 参数查看inode号。

```shell
ls -i
```

![image-20240624154326286](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241543362.png)



## cd

`cd` 命令用来切换目录，change directory。

```shell
cd 路径
```

回到上级目录：

```shell
cd ..
```

回到用户的家目录：

```shell
cd ~
或
cd
```

![image-20240624145541123](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241455159.png)

## clear

清屏

# 文件管理命令

文件和目录的操作方法几乎都一样。几个命令之间的规则也差不多。

## 新建目录

使用 `mkdir` 命令，make directory。

```shell
mkdir 目录路径名
```

mkdir 后面可以跟多个目录路径名，同时创建多个目录。

```shell
mkdir a b c
```

![image-20240624150300713](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241503755.png)

使用 `-p` 参数可以创建多重目录。

```shell
mkdir -p level1/level2/level3
```

![image-20240624150414204](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241504250.png)

不能创建已经存在的目录，但是如果是多重目录的创建，已存在的目录也不会报错。

![image-20240624150640555](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241506600.png)

## 新建文件

使用 `touch` 命令。

```shell
touch 文件路径名
```

可以同时创建多个文件。

```shell
touch 1.txt 2.txt level1/3.txt
```

![image-20240624150816893](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241508941.png)

## 删除文件

使用 `rm` 命令，remove。

```shell
rm 文件路径名
```

可以同时删除多个文件。

```shell
rm 1.txt 2.txt
```

![image-20240624150938257](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241509301.png)

使用 `-f` 参数可以直接删除文件，不需要确认。f 是 force 强制的意思。

```shell
rm -f 1.txt 2.txt
```

可以通过模糊匹配删除多个文件。

```shell
rm -f *.txt
```

## 删除目录

删除目录必须使用 `-r` 参数，r 表示递归 recursion。

```shell
rm -rf 目录路径名
```

加上 -f 参数无需确认直接删除，删除该目录以及目录下所有的东西。

## 拷贝文件

使用 `cp` 命令，copy。

```shell
cp 源文件路径名 目标文件路径名
```

将 1.txt 文件拷贝到 a 目录下：

```shell
cp 1.txt a/
```

![image-20240624151942319](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241519367.png)

将 1.txt 文件拷贝到 a 目录下，并重命名为 a.txt：

```shell
cp 1.txt a/a.txt
```

![image-20240624152051400](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241520465.png)

## 拷贝目录

和拷贝文件一样，但是需要使用 -r 参数。

```shell
cp -r 源目录路径名 目标目录路径名
```

将 a 目录拷贝到 b 目录下：

```shell
cp -r a b
```

![image-20240624152245463](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241522515.png)

将 a 目录拷贝到 b 目录下，并重命名为 aa：

```shell
cp -r a b/aa
```

![image-20240624152554503](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241525554.png)

注意：目标目录路径名要注意末尾是否跟 `/` 符号。加了 `/` 表示目录下。

比如：将 a 目录复制到 b 目录**下**

```shell
cp -r a b/
```

+ 这会在 b 目录下多出一个 a 目录

如果不加 `/` 会有两种情况

```shell
cp -r a b
```

+ 如果 b 目录存在的话，那么等同于 `cp -r a b/`
+ 如果 b 目录不存在的话，那么新建 b 目录，这个 b 目录就是 a 目录的拷贝

## 移动

也就是剪切，使用 `mv` 命令，move。

移动文件和目录的操作是一样的。

```shell
mv 源路径名 目标路径名
```

可以同时移动多个文件和目录。

将 1.txt、Main.java 和目录 a 移动到目录 b 中：

```shell
mv 1.txt Main.java a b
```

![image-20240624153336626](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241533686.png)

## 搜索

### find

使用 `find `命令可以在指定目录下搜索文件。

常用的是通过文件名字查找，使用 `-namw` 参数：

```shell
find 路径名 -name 表达式
```

可以使用模糊匹配。

查找b目录下所有的java文件：

```shell
find b -name *.java
```

![image-20240624153949046](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241539110.png)

### whereis

使用 `whereis` 命令搜索命令的位置。

查找 ls 命令的位置：

```shell
whereis ls
```

![image-20240624154053559](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241540619.png)

# 链接

链接也是一个文件。

使用 `ln` 命令创建链接（硬链接）

+ `-s`：创建软连接

## 软链接

软链接类似于windows操作系统中的快捷方式。

软链接和目标文件是两个不同的文件，只是软链接这个文件中存储的是目标文件的物理路径。

创建软链接：
```shell
ln -s 目标路径名 链接路径名
```

给 a/b/c/target 目录下的 1.java 文件创建一个软链接叫 link.java：

```shell
ln -s a/b/c/target/1.java link.java
```

![image-20240624155054978](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241550064.png)

+ 软链接的类型标识是 l。

通过inode号证明软链接和目标文件是两个不同的文件：

```shell
ls -il link.java a/b/c/target/1.java
```

![image-20240624161023775](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241610845.png)

对软链接进行修改，相当于直接修改目标文件。

如果删除了对应的目标文件，那么软链接会失效：
![image-20240624155254689](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241552772.png)

软链接也可以指向目录，进入软链接就相当于进入了目标目录。

## 硬链接

创建硬链接不需要带参数，直接使用 `ln`。

硬链接其实就是目标文件。

```shell
ln 目标路径名 链接路径名
```

给 a/b/c/target 目录下的 1.java 文件创建一个硬链接叫 link_hard.java：

```shell
ln a/b/c/target/1.java link_hard.java
```

![image-20240624162908628](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241629708.png)

+ 硬链接的标识是 -。

通过inode号证明硬链接和目标文件是同一个文件：

```shell
ls -il a/b/c/target/1.java link_hard.java 
```

![image-20240624163057934](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241631407.png)

对硬链接进行修改，相当于直接修改目标文件。操作了目标文件，硬链接也会改变（比如改变权限等）。

删除文件时，硬链接和目标文件只要有一个存在，文件就不算删除。

硬链接不能指向目录。

# 压缩和解压缩

`tar` 是在linux系统当中完成压缩和解压缩的命令。压缩后的文件又被称为**归档文件**。

tar 命令常用的参数：

+ z：指定是否使用gzip压缩方式压缩。（扩展名通常为：tar.gz。特点：速度最快）
+ j：是否需要用 bzip2 压缩方式压缩。（扩展名通常为：tar.bz2。特点：体积最小）
+ c：创建压缩（create）
+ x：解压缩
+ v：是否在压缩的过程中显示文件
+ f：指定归档文件名（file）。f参数后面必须紧跟文件名，不能在f参数后面再加其他参数。
+ t：查看 tarfile 里面的文件
+ C：指定解压到的具体目录。注意是大写C。

注意：f 参数必须是参数中的最后一个，因为 f 后面必须紧跟文件名。

注意：c、x、t，这三个参数不能共存，只能出现一个。

## 压缩

```shell
tar -zcvf 压缩包路径名 被压缩的路径名
```

将 1.txt 和 2.txt 和 目录 a压缩到 txts.tar.gz 中：

```shell
tar -zcvf txts.tar.gz 1.txt 2.txt a
```

![image-20240624163849053](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241638137.png)

## 解压

解压到当前路径下：

```shell
tar -zxvf 压缩包路径名
```

解压到指定路径下：

```shell
x tar -zxvf 压缩包路径名 -C 解压路径名
```

+ -C 后的目录必须存在

将 txts.tar.gz 解压到 jieya 目录中：

```shell
tar -zxvf txts.tar.gz -C jieya
```

![image-20240624164155903](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241641985.png)

# vi编辑

使用 `vi` 命令或 `vim` 命令来打开 vim 编辑器。

## vi和vim

vim 是 vi 编辑器的升级版，包含vi编辑器所有的功能。

在 CentOS 中，默认的是 vim 编辑器，使用 `vi` 或 `vim` 命令打开的编辑器都是 vim。

## 编辑文件

通过这两个命令

```shell
vi 文件路径名
```

或 

```shell
vim 文件路径名
```

进入文件的编辑界面。如果指定的文件不存在，则会新建。

vi 编辑器有两个模式：命令行模式，编辑模式。刚进入vi编辑器时是命令模式，此时输入的都是命令；命令模式下键入i命令进入编辑模式，此时就可以编辑文件内容，按下esc键又回到命令模式。

## 常用命令

`:w`：保存文件

`:q`：退出文件

`:wq`：保存并退出

`:q!`：不保存文件，强制退出

`dd`：删除光标所在行

`yy`：复制光标所在行

`p`：粘贴

`gg`：光标回到文件第一行

`GG`：光标回到文件最后一行

`^` ：光标移动至当前行的行首

`$` ：光标移动至当前行的行尾

`/关键字`：按斜杠/键，可以输入想搜索的字符，然后确定进行搜索，如果第一次查找的关键字不是想要的，可以一直按 n 键往后查找到想要的关键字为止

`o`命令：在下一行插入。
`x`命令：命令行模式下，x命令会删除单个字符。
`a`命令：在光标后面插入。
`i`命令：在光标位置插入。

# 系统命令

## 当前时间

输出当前时间：

```shell
date
```

按指定格式初始当前时间：

```shell
date +格式
```

可以使用 --help 参数查看具体用法。

## 切换用户

```shell
su 用户名
```

root 用户可以随意切换其他用户，不需要输入用户密码。

其他用户想要切换到 root 用户，需要输入 root 密码。

## 以root身份执行

```shell
sudo 命令
```

普通用户可以使用sudo来以root身份执行某个命令，需要输入root密码。

## 变量

定义变量：

```shell
变量名=值
```

比如定义一个name变量，值为zsm：

```shell
name=zsm
```

注意：等号两边不能有空格，否则会被识别为命令。

使用变量：

```shell
$变量名
```

或

```shell
${变量名}
```

有没有 {} 都可以，使用 {} 可以清楚的展现出变量名的范围。

##  echo

`echo` 命令用于输出。输出后，会换行。

```shell
echo 字符串或变量
```

字符串可以使用 `""` 、`''` 和不使用引号。

+ 单引号中的内容会被原样输出
+ 双引号中的内容可以引用变量

```shell
name=zsm
echo "I am $name " 'I am $name ' I am $name
```

![image-20240624165906240](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241659328.png)

使用双信号可以输出多行：

```shell
echo "line1
> line2
> line3"
```

![image-20240624170427322](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241704418.png)

可以输出特殊字符，需要使用双引号和 `-e` 参数： 

```shell
echo -e "a\tb\nc\td"
```

![image-20240624170609772](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241706869.png)

## sort

sort命令可以对文件中的内容以“行”为单位进行升序和降序排列。以字典序排序。排序后的文件没有被改变。

升序排序

```shell
sort 文件路径名
```

降序排序

```shell
sort -r 文件路径名
```

将文件中的内容当作数字排序，而不是字符串：

```shell
sort -b 文件路径名
```

## diff

diff命令可以用来比较两个文件的不同之处。

```shell
diff 文件1路径名 文件2路径名
```

比如，比较1.tx和2.txt文件的差别：

```shell
diff 1.txt 2.txt
```

![image-20240624171227122](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241712225.png)

1c1表示：第一个文件的第1行 和 第二个文件的第1行 发生了改变。

## 重定向

### 输出重定向

使用 `>` 或 `>>` 可以指定输出结果的位置。

+ `>` ：以覆盖的形式
+ `>>`：以追加的形式

将 `ls` 命令的结果输出到 1.txt 文件中，1.txt 文件中原有一行数据：

I am 1.txt。

以覆盖的形式：

```shell
ls > 1.txt
```

![image-20240624171806612](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241718718.png)

+ I am 1.txt 被覆盖掉了

以追加的方式：

```shell
ls >> 1.txt
```

![image-20240624171911644](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241719755.png)

### 输入重定向

使用 `<` 和 `<<` 将内容输入到某个命令中。

+ `<`：默认的，可以省略
+ `<<`：可以接收键盘的输入

比如sort命令排序1.txt文件（将1.txt文件的内容输入给sort命令）：

```shell
sort 1.txt
```

其实是省略了 `<` 的：

```shell
sort < 1.txt
```

将键盘输入的数据输入给sort命令：

```shell
sort << 结束符
```

![image-20240624172311619](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241723735.png)

+ 当输入结束符时就会停止输入，结束符可以随意定义

## grep

使用 `grep` 命令进行在某段内容中搜索。

```shell
grep pattern 目标文件路径名
```

+ pattern：表示要匹配的字符串或模式。

搜索多个文件：

```shell
grep 'pattern' file1 file2
grep 'pattern' *.txt
```

- `file1` 和 `file2` 表示要搜索的多个文件名。也可以使用通配符 `*.txt` 搜索所有扩展名为 `.txt` 的文件。

递归搜索目录：

```shell
grep -r 'pattern' dir
```

- `-r` 表示递归搜索目录。
- `dir` 表示要搜索的目录。

显示匹配行前的几行或后的几行：

```shell
grep -A 2 'pattern' file    # 显示匹配行后2行
grep -B 2 'pattern' file    # 显示匹配行前2行
grep -C 2 'pattern' file    # 显示匹配行前后各2行
```

- `-A` 表示显示匹配行后的几行。
- `-B` 表示显示匹配行前的几行。
- `-C` 表示同时显示匹配行前后的几行。这三个选项后面必须跟一个数字，表示要显示的行数。

同时输出匹配结果的行号：

```shell
grep -n 'pattern' file
```

- `-n` 表示只输出匹配结果所在的行号。

忽略大小写：

```shell
grep -i 'pattern' file
```

- `-i` 表示忽略大小写。

找出不匹配的行：

```shell
grep -v 'pattern' file
```

- `-v` 输出不匹配模式的行。

使用正则表达式匹配：

```shell
grep -E 'pattern' file
```

- `-E` 表示使用正则表达式匹配。

## 管道

管道符号 `|`，将 `|` 前面命令的输出作为后面命令的输入，可以叠加：

![image-20240622171715268](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406221717360.png)

## 查看系统进程

使用 `ps` 命令。

显示所有进程的详细信息：

```shell
ps -ef
```

![image-20240624173235059](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241732184.png)

+ UID：该进程的所属用户
+ PID：进程id
+ PPID：父进程id
+ C：CPU使用百分比
+ STIME：启动时间
+ TTY：启动该进程的终端设备是哪个
+ TIME：耗费的CPU时间
+ CMD：该进程对应的命令

## sleep

使用 `sleep` 命令暂停程序的执行。

```shell
sleep NUMBER[SUFFIX]
```

其中，`NUMBER` 为需要暂停的时间，单位是秒；`SUFFIX` 则可以是以下之一：

- `s` ：秒（默认）；
- `m` ：分；
- `h` ：小时；
- `d` ：日。

```shell
# 暂停 3 秒
sleep 3

# 暂停 1 分钟
sleep 1m

# 暂停 2 小时
sleep 2h

# 暂停 1 天
sleep 1d
```

## kill

使用 `kill` 命令杀死进程。

根据进程号杀死进程：

```shell
kill 进程号
```

强制杀死进程：
```she
kill -9 进程号
```

根据进程名杀死进程：

```shell
killall 进程名
```

## top

`top` 命令是用于查看正在运行的系统进程信息的命令。它会**实时**动态地显示系统资源的使用情况。

![image.png](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241735572.png)

## free、uptime

free命令和uptime命令展示的内容在top的内容中都有。

`free`命令可以用于查看物理内存和交换分区的使用情况。

`uptime`命令用于显示系统运行时间。

![image-20240624173707698](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241737834.png)

## df、du

`df` 命令是 Linux 系统中的一个磁盘空间使用情况查询命令，用于显示当前文件系统的磁盘空间使用状况，以及文件系统的挂载点、磁盘大小、已用空间、可用空间、使用占比等信息。`df`命令是 "disk free" 的缩写。

`du`命令是 Linux 系统中的一个磁盘空间占用查询命令，用于显示文件或目录占用的磁盘空间大小。`du`命令是 "disk usage" 的缩写。

## 重启

```shell
reboot
```

## 关机

```shell
poweroff
```

或

```shell
shutdown -h now
```

1.  `shutdown -h now` 命令会向系统发送信号，通知所有正在运行的进程停止运行，并保存当前的状态，然后关闭系统。通常会在关机前向所有用户发送通知消息。 
2.  `poweroff` 命令相较于 `shutdown -h now` 更为强制，它会立即关闭系统电源，不会等待正在运行的进程结束。使用 `poweroff` 命令时需要特别小心，因为它可能会丢失尚未保存的数据。 

## ifconfig

查看网卡的ip地址。在windows当中是：ipconfig。在linux当中是ifconfig。

## ping

查看计算机之间是否可以正常通信

```shell
ping IP地址或域名
```

## curl

模拟用户访问，模拟浏览器行为。可以用来测试我们编写的web服务接口。

`curl` 命令的基本语法如下：

```shell
curl [options] <URL>
```

其中，`URL` 表示要请求的目标地址。

`curl` 命令的常用选项如下：

- `-i` ：显示响应头信息。
- `-I` ：只显示响应头信息，不显示响应体。
- `-X` ：设置请求方法，包括 GET、POST、PUT、DELETE 等。
- `-d` ：设置请求体数据（POST 请求）。
- `-H` ：设置请求头信息。
- `-o/-O` ：下载文件，并保存到本地。
- `-u` ：设置认证信息。
- `-A` ：设置 User-Agent。
- `-s` ：静默模式，不输出进度信息。

以下是 `curl` 命令的一些使用示例：

1. 请求一个 URL 并输出响应信息：

```shell
curl www.example.com
```

2. 发送 POST 请求：

```shell
curl -X POST -d "name=john&age=30" www.example.com/submit
```

3. 下载一个文件：

```shell
curl -O www.example.com/test.zip
```

4. 设置请求头信息：

```shell
curl -H "User-Agent: Mozilla/5.0" www.example.com
```

## wget

下载资源。

```shell
wget 下载链接
```

## netstat

查看网络连接状态及端口。

以下是netstat命令的常用参数和用法：

1. 查看所有的网络连接状态：

```
netstat -a
```

![image-20240622182114034](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406221821151.png)

可以看到连接的地址和端口号，但是端口号是以文字的形式显示的，使用这个命令可以直接显示数字格式的IP地址和端口号：

```
netstat -an 
```

添加-n参数的目的是：不将端口和IP地址转换为名称，而是直接显示数字格式的IP地址和端口号

![image-20240622182242727](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406221822813.png)

2. 查看**所有处于监听状态**的连接：

```
netstat -l
```

3. 查看指定端口的网络连接状态：

```
netstat -an | grep 端口号
```

例如，查看80端口的网络连接状态：

```
netstat -an | grep :80
```

# 查看文件内容

## cat

```shell
用法：cat [选项]... [文件]...

常用选项：
  -n, 对输出的所有行编号
  -b, 对输出的所有行编号（不含空白行）
  -t, 将制表符(tab)显示为^I
  -e, 在每行结束处显示"$"
  -s, 当连续空白行数量大于1时，合并为1个空白行
```

## more

```shell
用法：
 more [选项] <文件>...

常用选项：
 -<number>  每个屏幕的行数
 +<number>  从行号开始显示文件
 +/<pattern>  从匹配的位置前两行开始显示内容
 -p  以清除原内容的方式进行翻页。
 
常用操作：
  回车键        【显示下一行】
  空格键        【显示下一页】
  ctrl + b     【显示上一页】
  =            【显示行号】
  :f           【显示文件名的同时显示行号】
  q            【退出more命令】
```

## less

```shell
用法：less [选项] 文件

常用选项：
-g  只标志当前搜索到的关键词所在行
-I  忽略搜索时的大小写（注意：是大写I）
-m  显示类似more命令的百分比
-N  显示每行的行号
+num 从第num行开始显示

常用操作：
/字符串：向下搜索“字符串”的功能
?字符串：向上搜索“字符串”的功能

n：重复前一个搜索（与 / 或 ? 有关）
N：反向重复前一个搜索（与 / 或 ? 有关）

y  向前滚动一行
回车键 向后滚动一行

u  向前滚动半页
d  向后滚动半页

b  向前翻一页
空格键 向后翻一页

g  移动到第一行
G  移动到最后一行

= 显示详细信息（第几行，共多少行，内容的字节数量等）

v  使用vim编辑器进行编辑

q  退出less 命令

[pagedown] 向下翻动一页
[pageup] 向上翻动一页
```

### 标记兴趣点

在感兴趣的位置添加标记： 

- 先按m键 (set mark)
- 输入标记名称，例如标记名字为：x

需要回到感兴趣的位置时： 

- 先按 ' 键 (goto mark)
- 输入标记名称 x

### 实时监控

```shell
less +F 文件路径名
```

这样可以实时更新指定文件的内容。使用vi编辑文件内容不会被监控。

## head

```shell
用法：head [选项]... [文件]...
将每个指定文件的前 10 行输出到标准输出。
如果指定了多于一个文件，在每块输出之前附加文件名称作为头部。

参数：
  -c 输出前几个字符
  -n 指定行数
  -q 不显示包含给定文件名的文件头
```

## tail

```shell
用法：tail [选项]... [文件]...
显示每个指定文件的最后 10 行并输出至标准输出。
若指定了多于一个文件，程序会在每段输出的开始添加相应文件名作为头。

参数：
  -c  输出最后几个字符
  -f  随文件增长即时输出新增数据
  -n  指定行数
  -q  不输出文件名的头
```

## nl

nl命令是比较专业的显示行号的命令。
用法如下：

- nl -b a 所有行添加行号，包括空白行；
- nl -b t 给行添加行号，不包括空白行（默认行为，和直接使用 nl 一样效果）；
- nl -n ln 行号在自己栏位左侧显示；
- nl -n rn 行号在自己栏位的右侧显示 ；
- nl -n rz 显示行号，行号栏位不满时，自动补0 ；
- nl -w 行号栏位的占用的位数。

# 用户和用户组

## 用户组查看

**查看有哪些用户组**

```shell
cat /etc/group
```

每一个用户组四部分组成：组名：密码标识：组的ID（GID)：该用户组中的用户列表。

**查看当前用户属于哪一组：**

```shell
groups
```

**查看某个用户属于哪一组:**

```shell
groups 用户名
```

## 用户组添加

```shell
groupadd 用户组名
```

使用 `-g` 参数可以指定用户组的标识号

```shell
groupadd -g 标识号 用户组名
```

创建组时，一般是从 1000 开始分配用户和组 ID。这是为了避免与系统保留的用户和组 ID 冲突。

## 用户组的修改

修改用户组的名字：

```shell
groupmod -n 新用户组名 原用户组名
```

## 用户组的删除

```shell
groupdel 用户组名
```

## 用户添加

```shell
useradd 用户名
```

参数：

- -d    指定新用户的主目录
- -g    指定新用户属于哪个组（主组）
- -G    可以给新用户添加附加组

注意：当新建用户时，没有指定组，也没有指定工作目录时：

- 默认的组名：和自己用户名一样
- 默认的主目录：/home/用户名

## 设置用户密码

```shell
passwd 用户名
```

## 切换用户

```shell
su 用户名
```

## 修改用户

```shell
usermod 用户名
```

参数：

- -d    指定新用户的主目录
- -g    指定新用户属于哪个组（主组）
- -G    可以给新用户添加附加组
- -l     指定新的用户名（小写的艾路）

## 删除用户

```shell
userdel -r 用户名
```

-r 选项的作用是连同该用户主目录一块删除。

## 给用户主目录之外的目录授权

第一步：创建目录

```shell
mkdir /java
```

第二步：给目录授权

```shell
# -R表示递归设置权限，该目录下所有的子目录以及子文件
chmod -R 775 /java
```

第三步：创建组

```shell
groupadd dev
```

第四步：把目录赋予组

```shell
chgrp -R dev /java
```

第五步：创建用户

```shell
useradd xiaoming
```

第六步：设置密码

```shell
passwd xiaoming
```

第七步：给用户添加附加组

```shell
usermod -G dev xiaoming
```

# 文件权限

三个权限：

- 读的权利（Read，简称r）
- 写的权利（Write，简称w）
- 执行的权利（eXecute，简称x）

不同的用户：

- 文件拥有者（User，简称U）：该文件的创建人
- 同组用户（Group，简称G）：和创建人在同一组的用户
- 其他组用户（Other，简称O）：和创建人不在同一组的用户

UGO模型。也就是说一个文件的权限包括三组：

- 第一组U：我们可以给文件的创建者设置rwx权限。
- 第二组G：我们可以给文件创建者的同组人员设置rwx权限。
- 第三组O：我们可以给和文件创建者不在同一组的人员设置rwx权限。

## 查看权限

使用 ls -l 命令可以查看文件的权限。

每一个文件或目录采用ls -l查看之后，第一个字段描述了文件类型+文件的权限。第一个字段共10个字符：

- 第1个字符：代表文件的类型，- 代表文件，d代表目录
  - 其实Linux中文件的类型有7种：
    - `-` 代表普通文件
    - d 代表目录
    - l 代表链接（软链接：快捷方式）
    - b 块设备（硬盘，软盘等存储设备）
    - c 字符设备（通常以字节流的方式访问）
    - p 管道文件（主要用于进程间通讯）
    - s 套接字文件（主要用于网络通讯）
- 第2,3,4个字符：代表文件创建者对该文件的权限。
- 第5,6,7个字符：代表与文件创建者在同一组的用户对该文件的权限。
- 第8,9,10 个字符：代表其他组人员对该文件的权限。

关于文件权限的9个字符中包含四种字符，分别是：r、w、x、-，他们代表什么含义：

- r：读权限
- w：写权限
- x：执行权限
- -：无权限

## 设置权限

使用 `chmod` 命令。

使用 UGO 方式修改权限：

```shell
chmod g+w Hello.java  # 给组用户添加写的权限
chmod g+w, o+w Hello.java  # 给组用户和其他用户添加写的权限
chmod g-w, o-w Hello.java  # 给组用户和其他用户减去写的权限
```

使用421设置权限：

```shell
chmod 三个数字 文件路径名
```

421采用数字来表示不同的权限。

- 4代表读
- 2代表写
- 1代表执行

```shell
chmod 755 HelloWorld.java  
```

第一个数字7是文件拥有者的权限：rwx

第二个数字5是同组人员的权限：r-x

第三个数字5是其他组人员的权限：r-x

## 修改文件拥有者

使用 `chown` 命令来修改指定文件或目录的拥有者和所属组。

# 安装软件

CentOS安装软件的方式主要包括：

- 源码安装
- rpm安装（二进制安装）
- **yum安装**（在线安装）

安装命令：yum -y  install  软件名
升级命令：yum -y  install  软件名
升级所有软件：yum -y  install
卸载命令：yum  remove  软件名
列出可安装的软件包：yum list
列出已安装的软件包：yum list installed
查询某个软件包：yum  list  软件名
根据关键字搜索软件包：yum search  Keyword
清除缓存：yum clean all

# shell编程

shell是Linux操作系统内置的一种编程语言。像 ls，cat……这些用过的命令都是shell命令。

shell编程本质上其实就是编写具有一定业务逻辑的shell命令，将一堆的shell命令写到xxx.sh文件中，这个xxx.sh文件被称为shell脚本，shell脚本就是可执行文件。

## 切换shell

在CentOS中，可以使用`chsh`命令切换默认Shell。`chsh`命令允许您更改用户的登录Shell。以下是切换Shell的步骤：

1. 查看已安装的Shell。

```shell
cat /etc/shells
```

2. 使用以下命令更改Shell。更改后需要重启才能使用输出语句看到

```shell
chsh -s /bin/sh
```

3.  重新登录后：检查Shell是否已更改： 

```shell
echo $SHELL
```

## 注释

单行注释：

```shell
# 单行注释以#开头
```

多行注释：

```shell
: '
这里是注释内容。
可以是多行，直到下面一行的单独引号为止。
'
```

+ 注意：冒号 `:` 和单引号 `'` 之间必须要有一个空格

## 变量

### 环境变量

环境变量是Linux操作系统中最常用的变量类型之一。它们是在Shell会话外设置的（一个shell脚本就是一个会话），可以由多个脚本和进程共享。在Linux中，环境变量没有固定的值，而是在需要时通过脚本或命令进行设置或更新。（**系统环境变量一般在/etc/profile文件中设置。**）
要查看当前所有环境变量，可以运行以下命令：

```shell
printenv
```

或

```shell
env
```

要设置一个新的环境变量，请使用“export”命令，例如：

```shell
export MY_VAR="Hello World"
```

要使用环境变量，在变量名称前必须加上$符号，例如：

```shell
echo $MY_VAR
```

### 本地变量

在Shell脚本中，变量的命名遵循以下规则：

1. 变量名由字母、数字和下划线组成。
2. 不能以数字开头。
3. 区分大小写。
4. 等号两侧不能有空格。
5. 不能使用特殊字符作为变量名，如$, &, !, (, ), *等。

创建本地变量：

```shell
变量名=值
```

在使用本地变量时，变量名称前必须加上$符号。

### 特殊变量

或叫内置变量。

以下是常见的一些特殊变量：

- `$0`: 当前脚本的文件名
- `$1, $2...`: 脚本参数列表中的第1个、第2个参数等等  (例如：./first.sh abc def，在执行这个脚本时，第一个参数abc，第二个参数def。)
- `$#`: 脚本参数的数量
- `$*`: 所有脚本参数的列表（将所有的参数作为一个字符串："zhangsan lisi wangwu"）
- `$@`: 所有脚本参数的列表（将每一个参数作为一个独立的字符串："zhangsan" "lisi" "wangwu"）
- `$$`: 当前脚本的进程ID号
- `$?`: 上一个命令的退出状态，一个数值。

## 中括号[]

中括号有两种使用方法：

1. 用于比较操作符：用于比较两个值的大小或者判断两个值是否相等。例如：

- `-eq`: 判断两个值是否相等（equal to），例如`[ $a -eq $b ]` 
- `-ne`: 判断两个值是否不相等（not equal to），例如`[ $a -ne $b ]`
- `-lt`: 判断左边的值是否小于右边的值（less than），例如`[ $a -lt $b ]`
- `-gt`: 判断左边的值是否大于右边的值（greater than），例如`[ $a -gt $b ]`
- `-le`: 判断左边的值是否小于等于右边的值（less than or equal to），例如`[ $a -le $b ]`
- `-ge`: 判断左边的值是否大于等于右边的值（greater than or equal to），例如`[ $a -ge $b ]`
- 一定要有空格隔开

在Shell中，比较操作符可以用于中括号[]中，例如:`[ $a -eq $b ]`。在比较时，要注意两个值之间必须有空格分隔，否则会出现语法错误。

2. 用于测试表达式：用于测试某个表达式是否成立。例如：

- `-f`: 判断某个文件是否存在并且是一个常规文件（regular file），例如`[ -f file.txt ]`
- `-d`: 判断某个文件是否存在并且是一个目录（directory），例如`[ -d dir ]`
- `-z`: 判断某个字符串是否为空（zero length），例如`[ -z "$str" ]`
- `-n`: 判断某个字符串是否非空（not zero length），例如`[ -n "$str" ]`
- `-e`: 判断某个文件或目录是否存在（exist），例如`[ -e file.txt ]`

需要注意的是，中括号中的空格很重要，空格缺少会导致语法错误。另外，在使用中括号[]时，要注意变量用双引号括起来，避免空值引起的语法错误。

## \$(())和$()

在shell编程中 `$((...))` 被称为算术扩展运算符，做数学运算的，并且将运算结果返回。`$(...)`运算符会将结果直接返回。

```shell
#!/bin/bash

i=1

while [ $i -le 10 ]
do
        echo "i = $i"
        i=$((i+1))
        echo $(echo "hello $i  world")
done
```

![image-20240624112149021](https://gitee.com/LowProfile666/image-bed/raw/master/img/202406241121217.png)

## if

if语句用于检查指定条件是否成立，并根据条件判断的结果执行不同的语句块。if语法格式如下：

```shell
if condition 
then
  command1
  command2
  ...
elif condition2 
then
  command3
  command4
  ...
else
  command5
  command6
  ...
fi
```

+ then 必须要换行写
+ else 后面不能写then
+ if 开始，fi 结束

比如：

```shell
#!/bin/bash

score=80

if [ $score -lt 60 ]
then
        echo "不及格"   
elif [ $score -lt 80 ]
then
        echo "合格"
elif [ $score -lt 90 ]
then
        echo "良好"
else
        echo "优秀"
fi
```

## for

for循环用于遍历指定列表或值的集合，并执行相应的语句块。for循环语法格式如下：

```shell
for var in list
do
  command1
  command2
  ...
done
```

其中，`var`是一个临时的变量名，用于存储当前循环的值，`list`是一个值或者多个带有空格或换行符分隔的值组成的列表。在每一次循环迭代时，`var`会被`list`列表中的一个值所替换，直到`list`中的所有值都被处理完为止。

比如：

```shell
#!/bin/bash

for item in "zsm" "hlt" 1 2 4 5 6 "zzzzz" zsdfsdf
do 
	if [ -f for.log ]
	then
		echo value = $item >> for.log
	else
		echo "没有该文件，创建……"
		touch for.txt
		echo value = $item >> for.log
	fi
done

cat -n for.log
```

## while

while循环用于不断执行语句块，直到满足指定条件为止。while循环语法格式如下：

```shell
while condition
do
  command1
  command2
  ...
done
```

其中，`condition`是要检查的条件，如果条件为真，则执行`do`语句块中的命令，执行完后再回到`while`语句中检查条件是否依然为真，如果条件仍为真，则继续执行命令块，否则跳出循环。

比如：

```shell
#!/bin/bash

i=1

while [ $i -le 10 ]
do
        echo "i = $i"
        i=$((i+1))
        echo $(echo "hello $i  world")
done
```

## until

until循环用于不断执行语句块，直到满足指定条件为止。和while循环不同的是，直到指定条件为假时才会停止循环。until循环语法格式如下：

```shell
until condition
do
  command1
  command2
  ...
done
```

其中，`condition`是要检查的条件，如果条件为假，则执行`do`语句块中的命令，执行完后再回到`until`语句中检查条件是否依然为假，如果条件仍为假，则继续执行命令块，否则跳出循环。

比如：

```shell
#!/bin/bash

i=0

until [ $i -eq 10 ]
do
        echo "i = $i"
        i=$((i+2))
done
```

## break和continue

break语句用于跳出当前循环块；continue语句用于跳过本次循环迭代。

比如：

```shell
#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9 10
do      
        if [ $i -eq 5 ]
        then    
                continue
        fi      
        echo "i = $i"
        if [ $i -gt 8 ]
        then    
                break
        fi      
done
```

## 函数

定义函数

```shell
function 函数名() {

}
```

调用函数

```shell
函数名 参数列表
```

在函数中使用参数：通过占位符

```shell
#!/bin/sh

# 定义函数say_hello
say_hello() {
  echo "Hello, world!"
}

# 调用函数say_hello
say_hello

# 定义函数greet
greet() {
  echo "Hello, $1 $2"
}

# 调用函数greet
greet "John" "Doe"
```

调用函数时，如果传入多余的参数不会有影响。