[TOC]

# **Tpora常用快捷键**

- 加粗： `Ctrl + B`
- 撤销： `Ctrl + Z`
- 字体倾斜 ：`Ctrl+I`
- 下划线：`Ctrl+U`
- 多级标题： `Ctrl + 1~6`
- 有序列表：`Ctrl + Shift + [`
- 无序列表：`Ctrl + Shift + ]`
- 降级快捷键 ：`Tab`
- 升级快捷键：`Shift + Tab`
- 插入链接： `Ctrl + K`
- 插入公式： `Ctrl + Shift + M`
- 行内代码： `Ctrl + Shift + K`
- 插入图片： `Ctrl + Shift + I`
- 返回Typora顶部：`Ctrl+Home`
- 返回Typora底部 ：`Ctrl+End`
- 创建表格 ：`Ctrl+T`
- 选中某句话 ：`Ctrl+L`
- 选中某个单词 ：`Ctrl+D`
- 选中相同格式的文字 ：`Ctrl+E`
- 搜索: `Ctrl+F`
- 搜索并替换 ：`Ctrl+H`
- 删除线 ：`Alt+Shift+5`
- 引用 ：`Ctrl+Shift+Q`
- 生成目录：`[TOC]+Enter`

# markdown语法

## **菜单**

* 输入[TOC]即可产生菜单，菜单会自动更新

## **区域元素**

+ 在文章的最上方输入---，按换行键产生，然后在里面输入内容即可。

## **段落**

+ 按换行键[Enter]建立新的一行,按`Shift`+`Enter`可以创建一个比段落间距更小的行间距。可在行尾插入打断线，禁止向后插入
  打断线<br/>后面的内容自动换行

## **标题**

+ 开头#的个数表示，空格+文字。标题有1~6个级别，#表示开始，按换行键结束

  ```
  # 一级标题 快捷键为 Ctrl + 1
  ## 二级标题 快捷键为 Ctrl + 2
  ......
  ###### 六级标题 快捷键为 Ctrl + 6
  ```

## **字体**

+ 斜体以**或__括住
  `*斜体1* _斜体2_`
  *斜体1* _斜体2_
+ 开头`**`，结尾`**`。或者开头`__`,结尾`__`(两个短横线)。
  `**粗体1** __粗体2__`
  **粗体1** __粗体2__

+ 删除线,开头`~~`，结尾`~~`
  `~~这是错误的字~~`
  ~~这是错误的字~~
+ 下划线使用HTML标签`<u>`下划线`</u>`
  `<u>下划线</u>`
  <u>下划线</u>
+ 高亮,`==内容==`，需要自己在偏好设置里面打开这项功能
  `==内容==`
  ==内容==

## **代码**

+ 行内输入代码块快捷键： `Ctrl + Shift + K`

+ 开头```+语言名，开启代码块，换行键换行，光标下移键跳出

  ```java
  ```java的效果
  ```

* 用两个`在正常段落中表示代码

  > `代码`

## **数学式**

+ 打开Typora选择数学模块

  - 点击“段落”—>“公式块”
  - 快捷键Ctrl+Shift+m
  - `“$$”+回车`

  以上三种方式都能打开数学公式的编辑栏。
  $\lim_{x\to\infty}\exp(-x)=0$

* 下标使用`~~`括住内容。需要自己在偏好设置里面打开这项功能：`H~2~o`
  H~2~o
* 上标使用`^`括住内容。需要自己在偏好设置里面打开这项功能：`y^2^=x`
  y^2^=x

## **表情**

+ Typora语法支持添加emoji表情，输入不同的符号码（两个冒号包围的字符）可以显示出不同的表情。

  > ```text
  > 以:开始，然后输入表情的英文单词,以：结尾，将直接输入该表情.例如：
  > :smile
  > :cry
  > :happy
  > ```
  >
  > :smile:

## **表格**

* 开头|+列名+|+列名+|+换行键，创建一个2*2表格，`Ctrl+Enter`可建立新行。

## **分割线**

+ 输入 `***` 或者 `---`,按换行键换行，即可绘制一条水平线。

## **引用**

+ 开头>表示，空格+文字，按换行键换行，双按换行跳出

+ 普通引用
  空格 + 引用文字：在引用的文字前加>+空格即可，引用可以嵌套。

  > ```text
  > > 引用文本前使用 [大于号+空格]
  > > 这行可以不加，新起一行都要加上哦
  > >这是引用的内容
  > >>这是引用的内容
  > ```

+ 列表中使用

  > ```text
  > * 第一项   
  > > 引用1    
  > > 引用2
  > * 第二项
  > ```

+ 引用里嵌套引用

  > ```text
  > > 最外层引用
  > > > 多一个 
  > > 嵌套一层引用
  > > > > 可以嵌套很多层
  > ```

+ 引用里嵌套列表

  >```text
  >> - 这是引用里嵌套的一个列表
  >> - 还可以有子列表
  >>     * 子列表需要从 - 之后延后四个空格开始
  >```

+ 引用里嵌套代码块

  > ```text
  > >     同样的，在前面加四个空格形成代码块
  > > ```
  > > 或者使用 ``` 形成代码块
  > > ```
  > ```

## **脚注**

+ 在需要添加脚注的文字后面+[+^+序列+]，注释的产生可以鼠标放置其上单击自动产生，添加信息
  `[^1]`

  > ```text
  > 脚注产生的方法[^footnote].
  > [^footnote]:这个就是"脚注"
  > ```

## **链接**

* 输入网址，单击链接，展开后可编辑，ctr+单击，打开链接

* 常用链接方法 `文字链接 [链接名称](http://链接网址)网址链接 <http://链接网址>`
  文字链接 [链接名称](http://链接网址)网址链接 <http://链接网址>

* 超链接

  * 格式1：用[ ]括住要超链接的内容，紧接着用( )括住超链接源+名字，超链接源后面+超链接命名
    同样ctrl+单击，打开链接例如：`这是[百度](https://www.baidu.com)官网`
    这是[百度](https://www.baidu.com)官网

  * 格式2：超链接 title可加可不加

    > ```text
    > This is [an example](http://example.com/ "Title") inline link.
    > [This link](http://example.net/) has no title attribute.
    > ```

* 高级链接技巧

  * 使用[+超链接文字+]+[+标签+]，创建可定义链接
    ctrl+单击，打开链接。:`这是[百度][id][id]:https://www.baidu.com`
    这是[百度][id][id]:https://www.baidu.com

  + 格式二：

    > ```text
    > 这个链接用 1 作为网址变量 [Google][1].
    > 这个链接用 yahoo 作为网址变量 [Yahoo!][yahoo].
    > 然后在文档的结尾为变量赋值（网址）  
    > [1]: http://www.google.com/  
    > [yahoo]: http://www.yahoo.com/
    > ```

## **URL**

+ 用<>括住url，可手动设置url对于标准URLs，可自动识别:`<www.baidu.com>`
  <www.baidu.com>

## **序列**

+ 开头`*` / `+` / `-` 加`空格`+文字，可以创建无序序列，换行键换行，删除键和shift+tab跳出
+ 开头1.加空格+后接文字，可以创建有序序列
+ 可选序列，开头序列+空格+[ ]+空格+文字，换行键换行，删除键+shift+tab跳出
  `+  [ ] 文字`
  + [ ] 文字

* 总结：先输入减号，然后输入空格，之后就变成了黑色圆点，在输入[]，在中间加个空格，回车就可以

## **图片**

> Typora文本文档中有使用图片内容，如果需要发布在各个兼容Markdown的软件平台，需要预先上传文档中的图片至图床，再通过对图床的图片链接调用，才能正常显示，否则各个平台将无法看到该文档图片。
> 免费图床网址：[https://sm.ms/](https://link.zhihu.com/?target=https%3A//sm.ms/)图床设置：[Typora图床自动上传图片设置篇]

+ 手动添加：跟链接的方法区别在于前面加了个感叹号 `!`：`![图片名称](http://图片网址)`

+ 当然，你也可以像网址那样对图片网址使用变量

  > ```text
  > 这个链接用 1 作为网址变量 [Google][1].
  > 然后在文档的结尾位变量赋值（网址） 
  > 
  > [1]: http://www.google.com/logo.png
  > ```

+ 除了以上2种方式之外，还可以直接将图片拖拽进来，自动生成链接。

# 图床设置

Typora文本文档中有使用图片内容，如果需要发布在各个兼容Markdown的软件平台，需要预先上传文档中的图片至图床，再通过对图床的图片链接调用，才能正常显示，否则各个平台将无法看到该文档图片。

> 图床意义：就是专门用来存放图片，同时允许你把图片对外连接的网上空间，不少图床都是免费的。

参考文章：https://zhuanlan.zhihu.com/p/412422531

## 安装node.js

安装nodejs：[https://nodejs.org/en/](https://link.zhihu.com/?target=https%3A//nodejs.org/en/)

运行成功的大概效果如下：

```text
C:\>node -v
v14.16.0

C:\>npm -v
6.14.11
```

## 配置gitee仓库

Gitee账户：[https://gitee.com/](https://link.zhihu.com/?target=https%3A//gitee.com/)

### 新建仓库

![新建仓库](https://gitee.com/zsm666/image-bed/raw/master/img/%E6%96%B0%E5%BB%BA%E4%BB%93%E5%BA%93.png)

### 私人令牌token配置获取

找到`设置`->`安全设置`->`私人令牌`，点击生成新令牌，选择下面的选项即可！

![img](https://pic4.zhimg.com/80/v2-06263bbbc624e2b9d5d3782cad1f68b3_720w.webp)

保存后面生成的私人令牌：

gitee仓库私人令牌：8678e6291b9f777d6067adf964bb5997

## 配置Github仓库

新建一个仓库，然后获取：https://github.com/settings/tokens：

![image-20240704194709505](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041947582.png)

然后选择没有过期时间，勾选repo：

![image-20240704194415650](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041947767.png)

然后拉到页面最下方，点击生成，复制，然后配置picgo中的图床设置：

![image-20240704194832892](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407041948964.png)

## PicGo配置

PicGo:[https://molunerfinn.com/PicGo/](https://link.zhihu.com/?target=https%3A//molunerfinn.com/PicGo/)

![PicGo配置1](https://gitee.com/zsm666/image-bed/raw/master/img/PicGo%E9%85%8D%E7%BD%AE1.png)

![PicGo配置2](https://gitee.com/zsm666/image-bed/raw/master/img/PicGo%E9%85%8D%E7%BD%AE2.png)

## Typora配置

![Typora配置](https://gitee.com/zsm666/image-bed/raw/master/img/Typora%E9%85%8D%E7%BD%AE.png)
