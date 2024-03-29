学习网站：[MDN官方文档](https://developer.mozilla.org/zh-CN/)

学习方法：主要模仿，边写边查，不求甚解

HTML CSS JavaScript

# 0、概述

HTML：Hyper Text Markup Language（超文本标记语言）。

HTML规范目前最高的版本是：HTML5.0，简称H5。

以下这句代码加上就是HTML5的语法，不加就是HTML4。

```html
<!doctype html> 
```



# 1、文档结构

html的所有标签为树形结构，每一个标签就是一个节点。

一般来讲，大多标签都有两个部分，开始标签和结束标签。在一个标签的开始和结束之间的节点就是子节点。

例如：

```html
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>前端基础</title>
</head>
<body>
    <h1>第一天</h1>
</body>
</html>
```

+ `<html>` 标签
  HTML `<html>` 元素表示一个 HTML 文档的根（顶级元素），所以它也被称为根元素。所有其他元素必须是此元素的后代。

+ `<head>` 标签
  HTML `<head>` 元素规定文档相关的配置信息（元数据），包括文档的标题，引用的文档样式和脚本等。
+ `<body>` 标签
  HTML `<body>` 元素表示文档的内容。document.body 属性提供了可以轻松访问文档的 body 元素的脚本。
+ `<title>` 标签
  HTML `<title>` 元素定义文档的标题，显示在浏览器的标题栏或标签页上。它只应该包含文本，若是包含有标签，则它包含的任何标签都将被忽略。
+ `<meta>` 标签
  HTML `<meta>` 元素表示那些不能由其它 HTML 元相关（meta-related）元素（`<base>`、`<link>`, `<script>`、`<style>` 或 `<title>`）之一表示的任何元数据信息。
  + `charset`：这个属性声明了文档的字符编码。如果使用了这个属性，其值必须是与 ASCII 大小写无关（ASCII case-insensitive）的”utf-8”。
  + `name`：`name `和 `content` 属性可以一起使用，以名 - 值对的方式给文档提供元数据，其中 `name` 作为元数据的名称，`content` 作为元数据的值。

设置网站 logo：

```html
<link rel="icon" href="imgs/logo.jpg">
```

这里需要注意的是路径写法，推荐写绝对路径：`/imgs/logo.jpg`，绝对路径就是以 `/` 开头，这个 `/` 表示当前的项目根目录。否则就是相对路径，相对路径的话要注意你当前的文档的位置，要从你当前文档的位置开始写。

# 2、基础标签

块级标签：会换行

行内标签：不会换行

## 2.1、注释

`<!-- 多行注释 -->`
示例：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <!--   
        这里的内容均为注释
        <h1>第一讲</h1>
        <p>
            段落。
        </p>
    -->
</body>
</html>
```



## 2.2、文本标签

文本标签虽然很多，但大部分可看成是预定好样式的 `<div>` 和 `<span>`。

**`<div>`标签**

+ `<div>`元素 (或 HTML 文档分区元素) 是一个通用型的流内容容器，在不使用CSS的情况下，其对内容或布局没有任何影响。
  其他块级标签例如：`<h1>, <p>, <pre>, <ul>, <ol>, <table>`。

**`<span>`标签**

+ `<span>` 元素是短语内容的通用行内容器，并没有任何特殊语义。可以使用它来编组元素以达到某种样式意图（通过使用类或者 Id 属性），或者这些元素有着共同的属性，比如lang。应该在没有其他合适的语义元素时才使用它。**`<span>` 与 `<div>` 元素很相似，但 `<div>` 是一个 块元素 而 `<span>` 则是 行内元素**
  其他内联标签例如：`<i>, <b>, <del>, <ins>, <td>, <a>`。

**`<h1> - <h6>`标签**

+ HTML `<h1>–<h6>` 标题 (Heading) 元素呈现了六个不同的级别的标题，`<h1>` 级别最高，而 `<h6>` 级别最低。

**`<p>`标签**

+ HTML `<p>`元素（或者说 HTML 段落元素）表示文本的一个段落。该元素通常表现为一整块与相邻文本分离的文本，或以垂直的空白隔离或以首行缩进。另外，`<p>` 是块级元素。

**`<pre>`标签**

+ HTML `<pre>` 元素表示预定义格式文本。在该元素中的文本通常按照原文件中的编排，以等宽字体的形式展现出来，文本中的空白符（比如空格和换行符）都会显示出来。(紧跟在 `<pre>` 开始标签后的换行符也会被省略)

**`<br>`标签**

+ HTML `<br>` 元素在文本中生成一个换行（回车）符号。此元素在写诗和地址时很有用，这些地方的换行都非常重要。

**`<hr>`标签**

+ HTML `<hr>` 元素表示段落级元素之间的主题转换（例如，一个故事中的场景的改变，或一个章节的主题的改变）。

+ 在 HTML 的早期版本中，它是一个水平线。现在它仍能在可视化浏览器中表现为水平线，但目前被定义为语义上的，而不是表现层面上。所以如果想画一条横线，请使用适当的 css 样式来修饰。

**`<i>`标签**

+ HTML 元素 `<i>` 用于表现因某些原因需要区分普通文本的一系列文本。例如技术术语、外文短语或是小说中人物的思想活动等，它的内容通常以斜体显示。

**`<b>`标签**

+ HTML 提醒注意（Bring Attention To）元素（`<b>`）用于吸引读者的注意到该元素的内容上（如果没有另加特别强调）。这个元素过去被认为是粗体（Boldface）元素，并且大多数浏览器仍然将文字显示为粗体。尽管如此，你不应将 `<b>` 元素用于显示粗体文字；替代方案是使用 CSS font-weight 属性来创建粗体文字。

**`<del>`标签**

+ HTML 的`<del>`标签表示一些被从文档中删除的文字内容。比如可以在需要显示修改记录或者源代码差异的情况使用这个标签。`<ins>`标签的作用恰恰于此相反：表示文档中添加的内容。

**`<ins>`标签**

+ HTML `<ins>` 元素定义已经被插入文档中的文本。

**`<sub>`与`<sup>`标签**

+ 右上角加字：`<sup></sup>`
+ 右下角加字：`<sub><sub>`

## 2.3、图片

HTML `<img>` 元素将一份图像嵌入文档。默认为行内元素，即 `display: inline`。

**`src` 属性**

+ 该属性是**必须的**，它包含了你想嵌入的图片的文件路径。

**`alt` 属性**

+ 该属性包含一条对图像的文本描述，这不是强制性的，但对可访问性而言，它难以置信地有用——屏幕阅读器会将这些描述读给需要使用阅读器的使用者听，让他们知道图像的含义。如果由于某种原因无法加载图像，普通浏览器也会在页面上显示alt 属性中的备用文本：例如，网络错误、内容被屏蔽或链接过期时。

**`height` 属性**

+ 图像的高度，在 HTML5 中的单位是 CSS 像素，在 HTML 4 中既可以是像素，也可以是百分比。*可以只指定 width 和 height 中的一个值，浏览器会根据原始图像进行缩放。*

**`width` 属性**

+ 图像的宽度，在 HTML5 中单位是 CSS 像素， 在 HTML 4 中可以是像素也可以是百分比。

## 2.4、音视频

**`<audio>`标签**

+ HTML `<audio>` 元素用于在文档中嵌入音频内容。 `<audio>` 元素可以包含一个或多个音频资源， 这些音频资源可以使用 `src` 属性或者`<source>` 元素来进行描述：浏览器将会选择最合适的一个来使用。也可以使用 MediaStream 将这个元素用于流式媒体。

+ 使用`src`属性播放

  ```html
  <audio controls src="/audios/bgm.mp3">
      Your browser does not support the audio element.
  </audio>
  ```

  如果浏览器不支持播放的话，则会显示标签内的字体。

+ `<audio>` 与多个 `<source>` 元素

  ```html
  <audio controls>
      <source src="/audios/sound1" type="audio/mpeg" />
      <source src="/audios/sound2.mp3" type="audio/mpeg" />
  </audio>
  ```

  这个例子包含了多个 `<source>` 元素。如果能够播放的话，浏览器就会试图去加载第一个 `source` 元素；如果不行，那就退而求其次去加载第二个。以上例子只能播放第二个。

  **注意：如果不写 `controls` 的话没有效果。**

**`<video>`标签**

+ HTML `<video>` 元素 用于在 HTML 或者 XHTML 文档中嵌入媒体播放器，用于支持文档内的视频播放。你也可以将 `<video>` 标签用于音频内容，但是 `<audio>` 元素可能在用户体验上更合适。

  ```html
  <video controls width="800">
      <source src="/videos/video1.mp4" type="video/mp4">
      <source src="/videos/video2.mp4" type="video/mp4">
      Sorry, your browser doesn't support embedded videos.
  </video>
  ```

## 2.5、超链接

HTML `<a>` 元素（或称锚元素）可以通过它的 `href` 属性创建通向其他网页、文件、同一页面内的位置、电子邮件地址或任何其他 URL 的超链接。`<a>` 中的内容应该指明链接的意图。如果存在 `href` 属性，当 `<a>` 元素聚焦时按下回车键就会激活它。

常用选项

+ 点击链接打开新标签页面时加入属性：`target="_blank"`

注意：`href` 属性一定要写上协议，比如：`https://www.baidu.com`

超链接也可以在站内跳转，也就是跳转到本项目下的其他 `html` 文件。

超链接 `<a></a>` 中可以写任何东西。

## 2.6、表单

**`<form>`标签**

+ HTML `<form>` 元素表示文档中的一个区域，此区域包含交互控件，用于向 Web 服务器提交信息。

**`<input>`标签**

+ HTML `<input>`用来填写内容，常见类型有：
  + `<input type="text">`：创建基础的单行文本框。
  + `<input type="number">`：用于让用户输入一个数字。其包括内置验证以拒绝非数字输入。浏览器可能会选择提供步进箭头，让用户可以使用鼠标增加和减少输入的值，或者只需用指尖敲击即可。
  + `<input type="email">`：带有 “email” (电子邮箱) 类型标记的输入框元素 (`<input>`) 能够让用户输入或编辑一个电子邮箱地址，此外，如果指定了`multiple`属性，用户还可以输入多个电子邮箱地址。在表单提交前，输入框会自动验证输入值是否是一个或多个合法的电子邮箱地址 (非空值且符合电子邮箱地址格式). CSS 伪标签 :`valid `和 :`invalid `能够在校验后自动应用。
  + `<input type="password">`：`<input>` 元素 里有一种叫做 “password” 的值，给我们一个方法让用户更加安全的输入密码。这个元素是作为一行纯文本编辑器控件呈现的，其中文本被遮蔽以致于无法读取，通常通过用诸如星号（“*”）或点（“•”）等符号替换每个字符来实现。这个符号会根据用户的浏览器和操作系统来具体显示哪个。
  + `<input type="radio">`：`<input>` 的 `radio` 类型元素默认渲染为小型圆圈图表，填充即为激活，类似于之前描述额复选框（`checkbox`）类型。单选按钮允许你选择单一的值来提交表单。

常用属性有：

+ `action`：处理表单提交的 URL。

+ `name`: 名称，表单中只有写了 `name` 属性的控件的内容才会被提交
+ `id`: 唯一ID
+ `maxlength`：最大长度
+ `minlength`：最小长度
+ `required`：是否必填
+ `placeholder`：当表单控件为空时，控件中显示的内容

**`<textarea>`标签**

+ HTML `<textarea>` 元素表示一个多行纯文本编辑控件，当你希望用户输入一段相当长的、不限格式的文本，例如评论或反馈表单中的一段意见时，这很有用。
+ 属性：`rows`表行数，`cols`表列数

**`<select>`与`<option>`标签**

+ HTML `<select>` 元素表示一个提供选项菜单的控件。
+ `selected` 属性设置默认选择

**`<button>`标签**

+ HTML `<button>` 元素表示一个可点击的按钮，可以用在表单或文档其它需要使用简单标准按钮的地方。 默认情况下，HTML 按钮的显示样式接近于 user agent 所在的宿主系统平台（用户操作系统）的按钮， 但你可以使用 CSS 来改变按钮的样貌。

**`<label>`标签**

+ HTML `<label>` 元素（标签）表示用户界面中某个元素的说明。
+ 将一个 `<label>` 和一个 `<input>` 元素匹配在一起，你需要给 `<input>` 一个 `id` 属性。而 `<label>` 需要一个 `for` 属性，其值和 `<input>` 的 `id` 一样。
+ 也可以将 `<input>` 直接放在 `<label>` 里，此时则不需要 `for` 和 `id` 属性，因为关联已隐含存在。

## 2.7、列表

**`<ul>`与`<li>`标签**

+ HTML `<ul>` 元素（unordered list，或称 HTML 无序列表元素）表示一个内可含多个元素的无序列表或项目符号列表。

**`<ol>`与`<li>`标签**

+ HTML `<ol>` 元素表示有序列表（ordered list），通常渲染为一个带编号的列表。

**`<dl>、<dt>`与`<dd>`标签**

+ HTML `<dl>` 元素 （或 HTML 描述列表元素）是一个包含术语定义以及描述的列表，通常用于展示词汇表或者元数据 (键 - 值对列表)。
+ t 是 title，d 是 description

## 2.8、表格

**`<table>`标签**

+ HTML的 `table` 元素表示表格数据 — 即通过二维数据表表示的信息。

**`<thead>`标签**

+ HTML的`<thead>`元素定义了一组定义表格的列头的行。

**`<tbody>`标签**

+ HTML的`<tbody>`元素定义一组数据行。

**`<tr>`标签**

+ HTML` <tr>` 元素定义表格中的行。 同一行可同时出现`<td>` 和`<th>` 元素。

**`<th>`标签**

+ HTML `<th>`元素定义表格内的表头单元格。

**`<td>`标签**

+ HTML `<td>` 元素 定义了一个包含数据的表格单元格。

**`<caption>`标签**

+ HTML `<caption>` 元素 (or HTML 表格标题元素) 展示一个表格的标题， 它常常作为 `<table>` 的第一个子元素出现，同时显示在表格内容的最前面，但是，它同样可以被 CSS 样式化，所以，它同样可以出现在相对于表格的任意位置。

## 2.9、语义标签

参考链接：[参考](https://www.jcut.edu.cn/)

![img_sem_elements.gif](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401051956559.gif)

实际上就是简化了以下写法，更加的一目了然：

```html
<div class="head"></div>
<div class="nav"></div>
<div class="content"></div>
<div class="footer"></div>
```

**`<header>`**

+ HTML `<header>` 元素用于展示介绍性内容，通常包含一组介绍性的或是辅助导航的实用元素。它可能包含一些标题元素，但也可能包含其他元素，比如 Logo、搜索框、作者名称，等等。

**`<nav>`**

+ HTML `<nav>`元素表示页面的一部分，其目的是在当前文档或其他文档中提供导航链接。导航部分的常见示例是菜单，目录和索引。

**`<section>`**

+ HTML `<section>`元素表示一个包含在 HTML 文档中的独立部分，它没有更具体的语义元素来表示，一般来说会有包含一个标题。

**`<figure>`**

+ HTML `<figure>` 元素代表一段独立的内容，经常与说明（caption）`<figcaption>` 配合使用，并且作为一个独立的引用单元。当它属于主内容流（main flow）时，它的位置独立于主体。这个标签经常是在主文中引用的图片，插图，表格，代码段等等，当这部分转移到附录中或者其他页面时不会影响到主体。

**`<figcaption>`**

+ HTML `<figcaption>` 元素 是与其相关联的图片的说明/标题，用于描述其父节点` <figure>` 元素里的其他数据。这意味着 `<figcaption>` 在`<figure>` 块里是第一个或最后一个。同时 HTML Figcaption 元素是可选的；如果没有该元素，这个父节点的图片只是会没有说明/标题。

**`<article>`**

+ HTML `<article>`元素表示文档、页面、应用或网站中的独立结构，其意在成为可独立分配的或可复用的结构，如在发布中，它可能是论坛帖子、杂志或新闻文章、博客、用户提交的评论、交互式组件，或者其他独立的内容项目。

**`<aside>`**

+ HTML `<aside>` 元素表示一个和其余页面内容几乎无关的部分，被认为是独立于该内容的一部分并且可以被单独的拆分出来而不会使整体受影响。其通常表现为侧边栏或者标注框（call-out boxes）。

**`<footer>`**

+ HTML `<footer>` 元素表示最近一个章节内容或者根节点（sectioning root ）元素的页脚。一个页脚通常包含该章节作者、版权数据或者与文档相关的链接等信息。

## 2.10、特殊符号

| HTML源代码 | 显示结果 | 描述                   |
| ---------- | -------- | ---------------------- |
| `&lt;`     | <        | 小于号或显示标记       |
| `&gt;`     | >        | 大于号或显示标记       |
| `&amp;`    | &        | 可用于显示其它特殊字符 |
| `&quot;`   | "        | 引号                   |
| `&reg;`    | &reg;    | 已注册                 |
| `&copy;`   | &copy;   | 版权                   |
| `&trade;`  | &trade;  | 商标                   |
| `&nbsp;`   | &nbsp;   | 不断行的空白           |

# 3、习题

