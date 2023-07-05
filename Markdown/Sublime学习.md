## Windows配置Sublime Text

如图 1 所示，是笔者本机已经安装好的 Sublime Text。如果读者尚未安装，先前往[ Sublime Text官网](https://www.sublimetext.com/3)下载并安装（安装过程非常简单，这里不做过多赘述）。
![安装好的Sublime Text](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H03NA.gif)
图 1 安装好的 Sublime Text

要知道，刚刚安装的 Sublime Text 无法自行具备运行 C、C++ 代码的能力，需要我们手动对其进行设置。不过在开始设置之前，读者需保证当前系统中已经初始化好了 GCC 编译环境。打开命令行窗口，并执行 gcc -v 指令，如果输出 GCC 编译器的具体版本等信息，表明当前系统以成功配置了 GCC 编译环境（如图 2 所示)。![配置GCC编译环境](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H10J24.gif)
图 2 配置 GCC 编译环境

> 如果读者所用环境中尚未配置 GCC 编译环境，可阅读《[MinGW下载和安装教程](#target)》一节进行安装。

在已安装好 GCC 编译器的基础上，接下来开始正式配置 Sublime Text 编辑器。
\1) 要想使 Sublime Text 具备运行 C 语言程序的能力，需在菜单栏中依次点击“Tools -> Build System -> New Build System”,由此即可在 Sublime Text 打开一个临时文件，如下所示：
![运行C语言程序的配置文件](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H1235P.gif)
图 3 运行 C 语言程序的配置文件


删除其所有内容，并将如下内容完整地复制到该文件中：

```
{
  "cmd": ["gcc","${file}","-o", "${file_path}/${file_base_name}"],
  "file_regex":"^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir":"${file_path}",
  "selector": "source.c",
  "encoding":"cp936",
  "variants":
  [
    {
      "name": "C_Run",
      "cmd": ["cmd","/c", "gcc", "${file}", "-o", "${file_path}/${file_base_name}","&&", "cmd", "/c","${file_path}/${file_base_name}"]
    },
    {
      "name":"C_RunInCommand",
      "cmd": ["cmd","/c", "gcc", "${file}","-o","${file_path}/${file_base_name}", "&&","start", "cmd", "/c","${file_path}/${file_base_name} & pause"]
     }
  ]
}
```

> 此文件中的内容，实则是运行 C 语言程序时需要执行的 gcc 指令，只不过在 Sublime Text 文件中，需写成以上形式。

按 Ctrl+S 组合键，将此文件保存起来，其中文件名默认为 untitled.sublime-build（untitile 可以自定义，例如 gcc_sublime-build），保存路径即为按 Ctrl+S 弹出的路径（切忌手动修改此路径）。

\2) 重新打开 Sublime Text，并依次在菜单栏中选择“Tools -> Build System”， 在该选项中就可以看到上一步创建好的 gcc_sublime-build 的文件名 gcc，如图 4 所示：
![查看创建好的gcc编译选项](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H141461.gif)
图 4 查看创建好的 gcc 编译选项

通过勾选 gcc 编译选项（直接在图 4 中点击即可），我们就可以直接在 Sublime Text 运行写好的 C 语言程序。比如，在 Sublime Text 编写如下程序：
![SublimeText中编写C语言程序](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H15N37.gif)
图 5 SublimeText 中编写 C 语言程序


在此基础上，选择“Tools -> Build With...”选项，此时 Sublime Text 会弹出如下对话框：
![可选择的编译选项](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H210953.gif)
图 6 可选择的编译选项

可以看到，这里有 gcc、gcc-C_Run 和 gcc-RunInCommand 3 个选项，其中 gcc 用于编译程序（读者可自行查看执行结果），gcc-C_Run 用于在 Sublime Text 内部调用 GCC 编译器并显示程序的执行结果（如图 7 a) 所示），gcc_RunInCommand 用于在命令行窗口中借助 gcc 指令运行该程序并输出执行结果（如图 7 b) ）。![Windows配置Sublime Text](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G31H229508.gif)
图 7 各个选项的功能


同样，如果想使 Sublime Text 具备执行 C++ 程序的能力，则只需再建立一个 g++_sublime-build 配置文件，并将如下内容拷贝到该文件中：

```c
{
  "cmd": ["g++","-Wall", "${file}", "-o", "${file_path}/${file_base_name}"],
  "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c, source.c++",
  "encoding":"cp936",
  "variants":
  [
    {
      "name": "C++_Run",
      "cmd": ["cmd", "/c", "g++", "-Wall","${file}", "-o", "${file_path}/${file_base_name}", "&&", "cmd", "/c", "${file_path}/${file_base_name}"]
    },  
    {
      "name": "C++_RunInCommand",
      "cmd": ["cmd", "/c", "g++", "-Wall","${file}", "-o", "${file_path}/${file_base_name}", "&&", "start", "cmd", "/c", "${file_path}/${file_base_name} & echo.&pause"]
    }
  ]
}
```

其它操作步骤，和上面是完全一样的。由此，即可使 Sublime_Text 具备执行 C++ 程序的能力。

---

---

要知道，GCC 官网提供的 GCC 编译器是无法直接安装到 Windows 平台上的，如果我们想在 Windows 平台使用 GCC 编译器，可以安装 GCC 的移植版本。

目前适用于 Windows 平台、受欢迎的 GCC 移植版主要有 2 种，分别为 MinGW 和 Cygwin。其中，MinGW 侧重于服务 Windows 用户可以使用 GCC 编译环境，直接生成可运行 Windows 平台上的可执行程序，相比后者体积更小，使用更方便；而 Cygwin 则可以提供一个完整的 Linux 环境，借助它不仅可以在 Windows 平台上使用 GCC 编译器，理论上可以运行 Linux 平台上所有的程序。

> 如果读者仅需要在 Windows 平台上使用 GCC，可以使用 MinGW 或者 Cygwin；除此之外，如果读者还有更高的需求（例如运行 POSIX 应用程序），就只能选择安装 Cygwin。

本节要重点给大家介绍的是 MinGw 的安装和使用。MinGw 全称 Minimalist GNU for Windows，应用于 Windows 平台，可以为我们提供一个功能有限的 Linux 系统环境以使用一些 GNU 工具，比如 GCC 编译器、gawk、bison 等等。

## <span id="target">MinGW的安装</span>

相比在 Linux 平台上安装 GCC 编译环境，在 Windows 平台上安装 MinGW 是比较简单的，只需经历以下几个过程。

\1) 打开 [MinGW 官网](https://osdn.net/projects/mingw/)（点击即可进入官网），下载 MinGW 安装包。![官网下载MinGW](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G0155032123.gif)
图 1 官网下载MinGW


\2) 下载完成后，会得到一个名为 mingw-get-setup.exe 的安装包，双击打开它，可以看到如下的对话框：

![开始安装MinGW](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G0155312N8.gif)
图 2 开始安装 MinGW

\3) 直接点击“Install”，进入下面的对话框：
![自定义MinGW的安装位置](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G0155430540.gif)
图 3 自定义 MinGW 的安装位置

\4) 读者可根据自己操作系统的实际情况，自定义 MinGW 的安装位置（例如我选择将其安装到 E 盘），然后点击“continue”，进入下面的对话框：
![下载并安装MinGW配置器](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G0155521960.gif)
图 4 下载并安装 MinGW 配置器

\5) 进入安装 MinGW 配置器的界面，读者耐心等待安装完成（显示 100%）即可。安装完成之后，我们会得到一个名为 "MinGW Installer Manager" 的软件，借助它，我们可以随时根据需要修改 GCC 编译器的配置。点击“continue”,会自动弹出配置界面，如下所示：
![配置GCC编译器](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G016005D11.gif)
图 5 配置 GCC 编译器


为使 GCC 同时支持编译 C 语言和 C++，需勾选图中标注的 2 项。我们知道，GCC 还支持其它编程语言，读者可借助此配置器，随时实际需要安装自己需要的编译环境。勾选完成后，在菜单栏中选择`Installation -> Apply Changes`，弹出如下对话框：
![开始安装选中的编译环境](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G0160220954.gif)
图 6 开始安装选中的编译环境


选择“Apply”。然后耐心等待，直至安装成功，即可关闭此界面。注意，整个安装过程中可能会提示某些组件下载失败，但没关系，后续需要时，可以通过 MinGw Installer（图 4 所示）安装界面中的 “All Packages”选项中，手动选择指定的安装包进行安装。

\6) 在安装完成的基础上，我们需要手动配置 PATH 环境变量。依次`右击计算机（我的电脑） -> 属性 -> 高级系统设置 -> 环境变量`，建议读者在当前用户的 PATH 环境变量中增加 MinGW 的安装路径，例如我将其安装到了`E:\MinGW`文件夹中，因此 PATH 环境变量的设置如下：
![配置PATH环境变量](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G016041W06.gif)
图 7 配置 PATH 环境变量


\7) 由此，打开命令行窗口（通过在搜索栏中执行 cmd 指令即可），输入`gcc -v`指令，如果输出 GCC 编译器的具体信息，则表示安装成功，例如：
![成功安装GCC编译环境](https://gitee.com/zsm666/image-bed/raw/master/img/2-200G0160522164.gif)
图 8 成功安装 GCC 编译环境

## MinGW的使用

通过上面的安装，我们就可以在当前 Windows 平台上编译、运行 C 或者 C++ 程序了。

这里以运行一个 C 语言程序为例（存储路径为：D:\demo.c）：

```c
#include <stdio.h>
#include <stdlib.h>
int main(){    
    printf("Hello, World!");    
    system("pause");    
    return 0;
}
```

在此基础上，在命令行窗口中执行如下指令：

`C:\Users\mengma>gcc D:\demo.c -o D:\demo.exe`

其会在 D 盘生成一个 demo.exe 可执行文件，找到该文件并双击，即可看到程序的执行结果：

`Hello, World!`

## 配置运行Java

sublime自己有一个JavaC的构建系统，但是只能编译不能运行，所以需要配置一下：

在 Tools 菜单栏中 Build System 里选择 New Build System，然后将以下代码复制进去：

```json
{
    "cmd": ["javac", "$file_name", "&&", "java", "$file_base_name"],
    "selector": "source.java",
    "shell": true,
    "working_dir": "$file_path"
}
```

并保存，可以取名为 Java.sublime-build。

同时在 Tools 中 Build System 中可以选定 Automatic ，这样sublime就可以根据文件类型自动选择 Builid System。

因为sublime编码的问题，一般在DOS窗口中运行Java是使用的ASNI编码保存的，但是在sublime中，ASNI对应的Western（Window1252）不能使用中文，所以只能使用UTF-8的格式，但是使用UTF-8的话，DOS中就不能正常运行，会出现乱码，所以要在系统环境变量里面新建一个变量：

```
名为：JAVA_TOOL_OPTIONS
值为：-Dfile.encoding=UTF-8
```

这样在DOS中和在sublime中都可以使用UTF-8的格式来运行Java，而不会出现乱码。

还可以使用 chcp 命令来更改当前DOS窗口的格式

1. 查看当前代码页：在DOS命令行窗口中，输入以下命令并按Enter键：

```
chcp
```

该命令将显示当前的代码页信息。

1. 更改为ANSI格式：根据您所需的ANSI格式值，使用以下命令更改当前的代码页。例如，要将代码页更改为ANSI标准的代码页437，输入以下命令并按Enter键：

```
chcp 437
```

1. 确认更改：输入`chcp`命令再次检查当前的代码页，确保已成功更改为所需的ANSI格式。

请注意，不同的ANSI格式对应不同的代码页值。常见的ANSI标准代码页包括437、850、1252等，具体取决于您所处的地区和语言环境。

通过使用`chcp`命令切换到ANSI格式，您可以在DOS命令行中正确显示和处理相应的ANSI编码字符。

