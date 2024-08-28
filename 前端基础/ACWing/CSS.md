# 	0、概述

一般项目会用一个 `static` 文件夹来存放一些静态的资源，比如：html页面、css文件、视频图片等等，这样比较方便好管理。

CSS 全名叫做 层叠样式表。作用是 修饰html中各种标签。

# 1、样式定义j

## 行内样式表（inline style sheet）
直接定义在标签的`style`属性中。

+ 作用范围：仅对当前标签产生影响。

例如：

```html
<img src="/images/mountain.jpg" alt="" style="width: 300px; height: 200px;">
```

在以后我们自己实现的时候，其实这个属性名 `style` 可以任意写，因为可以通过 JavaScript 代码来实现样式的设置，只不过内置的就是 style 写法。

行内样式表由于定义在某一个具体的标签上的，所以这个样式只对这一个标签起作用，对其他的相同的标签不会有作用。

```html
<div style="width:300px; height: 300px; background-color:blue"></div>
<div>上面的div样式不会影响到我</div>
```

+ px：像素单位，分辨率

## 内部样式表（internal style sheet）

定义在`style`标签中，通过选择器影响对应的标签。

+ 作用范围：可以对同一个页面中的多个元素产生影响。

```html
<style type="text/css">
    img {
        width: 300px;
    }
</style>
```

`style` 标签一般放在 `head` 标签中，所以会对该 html 文档中的所有指定元素产生影响。

+ `type="text/css"` 写不写都可以。

## 外部样式表（external style sheet）

定义在css样式文件中（文件扩展名是`.css`），通过选择器影响对应的标签。可以用link标签引入某些页面。

+ 作用范围：可以对多个页面产生影响。

将样式写在 css 文件中：

```css
img {
    width: 300px;
}
.blue-p {
    width: 200px;
    height: 200px;
    background-color: blue;
}
```

不需要再写 `style` 标签，直接写样式即可。

将 css 文件加入到需要的 html 文档中：

```html
<link rel="stylesheet" href="/static/CSS/style.css">
```

这一句一般也写在 `head` 标签中。

## 注释

注意不能使用//。

只有：`/* 注释 */ `

# 2、选择器

方便地选择出来想要修改样式的标签。

## 标签选择器

语法：

```css
标签名 {
	样式
}
```

选择所有`div`标签：

```css
div {
    width: 200px;
    height: 200px;
    background-color: gray;
}
```

## ID选择器

这个 id 是 html 标签的 id 属性：

```html
<div id="mydiv"></div>
```

语法：

```css
#ID {
    样式
}
```

选择ID为`mydiv`的标签：

```css
#mydiv {
    width: 200px;
    height: 200px;
    background-color: gray;
}
```

id 属性应该是整个页面中唯一的，但是你如果写多个相同的 id 的标签也可以。

## 类选择器

选择所有`blue-p`类的标签：

```css
.blue-p {
    width: 200px;
    height: 200px;
    background-color: blue;
}
```

指定标签的类：

```html
<p class="blue-p big">1</p>
<p class="blue-p">2</p>
<p class="big">3</p>
```

一个标签可以属于多个类，类名之间使用空格隔开即可。

类是可以跨标签的：

```html
<div class="big"></div>
<img class="blue-p" />
```

如果两个类样式中都有同种操作，比如改变颜色：

```css
.big-tag {
    background-color: blue;
}
.red-tag {
    background-color: red;
}
```

有一个 p 标签属于以上两个类：

```html
<p class="red-tag big-tag">111</p>
```

最终这个 p 标签的背景颜色取决于 red-tag、big-tag 的定义的先后顺序，red-tag 样式定义在 big-tag 之后，所以最终的结果是 red-tag。与 `class="red-tag big-tag"` 中的顺序无关。

## 伪类选择器

伪类用于定义元素的特殊状态。比如一张图片，鼠标放上去后图片会变大，此时鼠标放图片上面就是一种状态。

**链接伪类选择器：**

+ `:link`：链接访问前的样式

+ `:visited`：链接访问后的样式

+ `:hover`：鼠标悬停时的样式

+ `:active`：鼠标点击后长按时的样式

+ `:focus`：聚焦后的样式

+ 比如：一个 p，当鼠标放上去后，变大且改变颜色：

  ```html
  <style type="text/css">
      .effect {
          width: 80px;
          height: 80px;
          background-color: lightgreen;
      }
      .effect:hover {
          transform: scale(1.2);  /* 变大1.2倍 */
          transition: 200ms;  /* 变大的时间，用于设置渐变的过程 */
          background-color: lightpink;
      }
  
  </style>
  <p class="effect">111</p>
  ```

**位置伪类选择器：**

+ `:nth-child(n)`：选择是其父标签第n个子元素的所有元素。

  + `:nth-child(3n)`
  + `:nth-child(odd)`
  + `:nth-child(even)`
  + `:nth-child(2n+1)`

+ **注意：**例如，`p:nth-child(2)` 不是选择父元素中第 2 个 `p` 标签，而是判断父元素中的第 2 个元素是不是 `p` 标签这个状态，是的话则选中。这个 p 是处于它父元素的第 2 个标签的位置。

  ```html
  <style>
      p:nth-child(3) {
          background-color: lightpink;
      }
  </style>
  <p>1</p>
  <p>2</p>
  <p>3</p>
  <p>4</p>
  <p>5</p>
  ```

  以上代码会选中 `<p>2</p>` 这一行，背景变为粉色。

  ```html
  <style>
      p:nth-child(3) {
          background-color: lightpink;
      }
  </style>
  <div></div>
  <div></div>
  <p>1</p>
  <p>2</p>
  <p>3</p>
  <p>4</p>
  <p>5</p>
  ```

  以上代码不会选中任何元素，因为此时父元素 `<body>` 中的第二个元素是 `div` ，不是 `p` ，所以没有选中。

要把 `nth-child()` 当成一种状态，就是一个 `boolean` 函数，会判断这个标签是不是满足某个条件，比如：`p:nth-child(2n + 1)` ，这会遍历所有的 p 标签，判断 p 标签是不是它父节点的第 `2n+1` 个子节点。

**目标伪类选择器：**

+ `:target`：当`url`指向该元素时生效。

可以通过超链接跳转到页面中某一个元素的位置：

```html
<a href="#myp">点击</a>
<p>1</p>
<p>2</p>
<p id="myp">3</p>
<p>4</p>
<p>5</p>
<p>6</p>
<p>7</p>
<p>8</p>
<p>9</p>
<p>10</p>
```

如上代码，点击后，观察浏览器的地址栏：

+ 点击之前：http://127.0.0.1:5501/index.html
+ 点击之后：http://127.0.0.1:5501/index.html#myp，此时就是 url 指向 id 为 myp 的元素的情况。

那么就可以使用 `:target` 选择器来对此时的状态进行样式修饰：

```css
p:target {
    transform: scale(1.2);
    background-color: burlywood;
    transition: 2s;
}
```

当一个元素是处于被 url 指向的状态时，浏览器会把页面定位到被指向的元素位置，且该元素会被显示到浏览器页面的最顶端，如果底下页面不够的话，则不会显示。

## 复合选择器

由两个及以上基础选择器组合而成的选择器。

+ `element1, element2`：同时选择元素`element1`和元素`element2`。CSS中所有并列的情况都用逗号

  ```html
  <style type="text/css">
      div, p {
          width: 100px;
          height: 30px;
      }
      /* 可以和伪类选择器一起使用 */
      div:hover, p:hover {
          transform: scale(1.2);
          background-color: brown;
      }
  </style>
  
  <body>
      <div>1</div>
      <div>2</div>
      <div>3</div>
      <p>1</p>
      <p>2</p>
      <p>3</p>
      <p>4</p>
  </body>
  ```

+ `element.class`：选则包含某类的`element`元素。

  ```html
  <style type="text/css">
      div.red {
          background-color: red;
      }
      div.big {
          transform: scale(1.2);
      }
      /* 可以串联 */
      div.red.big{  /* 这个就只会针对第二个div */
          transform: scale(1.2);
          background-color: red;
      }
  </style>
  
  <div class="big">1</div>
  <div class="red big">2</div>
  <div class="red">3</div>
  ```

+ `element1 + element2`：选择紧跟`element1`的`element2`元素。

  ```html
  <style type="text/css">
      div, p {
          width: 100px;
          height: 100px;
      }
      div + p {
          background-color: blueviolet;
      }
      p + p {
          background-color: lightblue;
      }
      #myp + p {
          background-color: lightblue;
      }
      p + #myp {
          background-color: lightblue;
      }
  </style>
  
  <body>
      <div>1</div>
      <div>2</div>
      <div>3</div>
      <p>1</p>
      <p id="#myp">2</p>
      <p>3</p>
      <p>4</p>
  </body>
  ```

+ `element1 element2`：选择`element1`内的所有`element2`元素。

  这里不一定要求 element1 是父节点，祖先节点也可以。

  ```html
  <style type="text/css">
      ul ul {
          color: red;
      }
  </style>
  
  <body>
      <ul id="ul1">
          <li>1
              <ul id="ul2">
                  <li>1.1</li>
                  <li>1.2</li>
                  <li>1.3</li>
              </ul>
          </li>
          <li>2</li>
          <li>3</li>
      </ul>
  </body>
  ```

  ul1 的父节点及其祖先节点都不是 `ul`，ul2 的祖先节点是 `ul` ，所以 ul2 的颜色会变红，同时会发现，ul2 的颜色变红了，其子节点 `li` 的颜色也都变红了。

+ `element1 > element2`：选择父标签是`element1`的所有`element2`元素。

复合选择器可以随意串联。

## 通配符选择器

+ `*`：选择所有标签

  ```css
  * {
  	margin: 0px;
  	padding: 0px;
  }
  ```

+ `[attribute]`：选择具有某个属性的所有标签

+ `[attribute=value]`：选择attribute值为value的所有标签

  ```css
  <style type="text/css">
  /* 选择具有id属性的所有input标签 */
  input[id] {
      background-color: gray;
  }
  /* 选择type值为number的所有标签 */
  input[type=number] {
      background-color: yellow;
  }
  </style>
  
  <body>
      <input type="text">
      <input type="text" id="">
      <input type="number" id="">
  </body>
  ```

## 伪元素选择器

将特定内容当做一个元素，选择这些元素的选择器被称为伪元素选择器。

+ `::first-letter`：选择第一个字母

  ```html
  <style type="text/css">
      /* 每段的第一个字变红 */
      p::first-letter {
          color: red;
          font-size: 110%;
      }
  </style>
  
  <body>
      <p>锄禾日当午，</p>
      <p>汗滴禾下土。</p>
      <p>谁知盘中餐，</p>
      <p>粒粒皆辛苦。</p>
  </body>
  ```

+ `::first-line`：选择第一行

  ```html
  <style type="text/css">
      /* 每段的第一行字变红 */
      p::first-line {
          color: red;
          font-size: 110%;
      }
  </style>
  <body>
      <p>
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
      </p>
  </body>
  ```

  并且这个一行的内容是由浏览器的窗口大小来决定的。

+ `::selection`：选择已被选中的内容

  ```html
   <style type="text/css">
       /* 每段的选中字变黄，背景变黑 */
       p::selection {
           color: yellow;
           background-color: black;
       }
  </style>
  
  <body>
      <p>
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
          锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。
      </p>
  </body>
  ```

+ `::after`：可以在元素后插入内容

+ `::before`：可以在元素前插入内容

  ```html
  <style type="text/css">
      h1::before {
          content: "《";
      }
      h1::after {
          content: "》";
      }
  </style>
  
  <body>
      <h1>悯农</h1>
      <h1>咏柳</h1>
      <h1>鹅鹅鹅</h1>
  </body>
  ```

通过这两个属性渲染的内容在页面上是无法通过鼠标选中的。

## 样式渲染优先级

+ 权重大小，越具体的选择器权重越大：`!important > 行内样式 > ID选择器 > 类与伪类选择器 > 标签选择器 > 通用选择器`
+ 权重相同时，后面的样式会覆盖前面的样式（后来居上）
+ 继承自父元素的权重最低

# 3、颜色

## 预定义的颜色值

black、white、red、green、blue、lightblue等。

## 16进制表示法

红绿蓝三种颜色，每个颜色可以取值 0-255，可以组合出所有的颜色。

使用6位16进制数表示颜色，例如：#ADD8E6。

其中第1-2位表示红色，第3-4位表示绿色，第5-6位表示蓝色。

简写方式：`#ABC`，等价于`#AABBCC`。

## RGB表示法

`rgb(173, 216, 230)`。

其中第一个数表示红色，第二个数表示绿色，第三个数表示蓝色。

## RGBA表示法

`rgba(173, 216, 230, 0.5)`。

前三个数同上，第四个数表示透明度。

## 取色方式

网页里的颜色，可以在chrome的调试模式下获取。Ctrl+Shift+C，可以快速选择元素。

其他颜色可以使用QQ或其他的截图软件：

+ 直接按c键，可以复制rgb颜色值
+ 按住shift再按c键，可以复制16进制颜色值

---

# 4、文本

## **`text-align`**

`text-align` CSS属性定义行内内容（例如文字）如何相对它的块父元素对齐。`text-align` 并不控制块元素自己的对齐，只控制它的行内内容的对齐。

```html
<h1>悯农</h1>
<div class="mydiv">
    锄禾日当午，<br>
    汗滴禾下土。<br>
    谁知盘中餐，<br>
    粒粒皆辛苦。
</div>
```

文字对齐是可以继承的：如果父标签有文字对齐的属性的话，子标签会继承这个属性。

```html
<div class="mydiv">
    <p>锄禾日当午，</p>
    <p>汗滴禾下土。</p>
    <p>谁知盘中餐，</p>
    <p>粒粒皆辛苦。</p>
</div>
```

此时我们只给 div 标签设置 text-align 属性的话，div 标签中的 p 标签也会有同样的效果。

## **`line-height`**

`line-height` CSS 属性用于设置多行元素的空间量，如多行文本的间距。对于块级元素，它指定元素行盒（line boxes）的最小高度。对于非替代的 inline 元素，它用于计算行盒（line box）的高度。

补充知识点：长度单位

| 单位 | 描述                                                         |
| ---- | ------------------------------------------------------------ |
| px   | 设备上的像素点（绝对单位）                                   |
| %    | 相对于父元素的百分比                                         |
| em   | 相对于当前元素的字体大小（相对于当前元素默认的字体大小的几倍） |
| rem  | 相对于根元素的字体大小                                       |
| vw   | 相对于视窗宽度的百分比                                       |
| vh   | 相对于视窗高度的百分比                                       |

`em` 一般用于等比例控制放大缩小， `em` 例子：

```html
<div style="font-size: 2em;">
    第一层
    <div style="font-size: 2em;">
        第二层
        <div style="font-size: 2em;">
            第三层
        </div>
    </div>
</div>
```

+ 第一层的字体大小是 32px，因为第一层最开始默认的字体大小是 16 px
+ 第二层的字体大小是 64 px，因为第二层开始的字体大小是继承自它的父级 div 元素是 32px
+ 第三层的字体大小是 128px，因为第三层开始的字体大小是 64 px

`rem` 一般用于处理使用 `em` 不方便的地方，比如要删除以上代码中的中间 div，那么第三层的 div 字体就会收到影响， `rem` 例子：

```html
<div style="font-size: 2rem;">
    第一层
    <div style="font-size: 2rem;">
        第二层
        <div style="font-size: 2rem;">
            第三层
        </div>
    </div>
</div>
```

+ 此时三层 div 的字体大小都是 32px，因为根元素的字体大小为 16px，这里的根元素是 `<html></html>` 标签

`vw` ：将整个浏览器窗口平均分为 100 份，1vw 就是表示一份，浏览器窗口的宽度的百分之一。

`vh` 同理。设置一个高度占浏览器窗口百分之 30，宽度占屏幕百分之 50 的矩形：

```html
.mydiv {
    height: 30vh;
    width: 50vw;
    background-color: aqua;
}
```

+ 注意：`height: 30%` 这种写法是指父元素的百分比，vh 的写法是指整个浏览器窗口

设置一倍行高：

```html
.mydiv {
    text-align: center;
    line-height: 1em;
}
```

+ `1em` 表示一倍的当前字体大小

![image-20240129110756078](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291108315.png)

行高有个很重要的作用，就是==让文字竖直居中==。可以通过 `text-align:center` 实现水平居中，竖直居中就可以使用行高 `line-height` 来实现。

```html
<div class="mydiv">
    锄禾日当午。
</div>

.mydiv {
    text-align: center;
    height: 200px;
    line-height: 200px;
    background-color: aqua;
}
```

## **`letter-spacing`**

CSS 的 `letter-spacing` 属性用于设置文本字符的间距。

每个字之间隔一个字的间距：

```css
.mydiv {
    text-align: center;
    letter-spacing: 1em;
}
```

## **`text-indent`**

`text-indent`属性能定义一个块元素首行文本内容之前的缩进量。

## **`text-decoration`**

`text-decoration` 这个 CSS 属性是用于设置文本的修饰线外观的（下划线、上划线、贯穿线/删除线 或 闪烁）它是 `text-decoration-line, text-decoration-color, text-decoration-style`, 和新出现的 `text-decoration-thickness` 属性的缩写。

去掉超链接的下划线：

```css
a {
    text-decoration: none;
}
```

## **`text-shadow`**

`text-shadow`为文字添加阴影。可以为文字与 `text-decorations` 添加多个阴影，阴影值之间用逗号隔开。每个阴影值由元素在X和Y方向的偏移量、模糊半径和颜色值组成。

`text-shadow` 有四个参数（x, y, r, color），前两个参数是坐标，指定阴影往哪个方向偏，第三个参数是阴影模糊的半径，第四个参数是阴影的颜色。

这个坐标的所在坐标系是这样的：

![image-20230219112727803](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291120084.png)

将文字的左上、右下两个方向设置阴影：

```css
.mydiv {
    text-shadow: -3px -3px red, 3px 3px 5px yellow;
}
```

+ 模糊度没有可以不用写
+ 颜色不写的话默认是黑色

# 5、字体

## **`font-size`**

`font-size` CSS 属性指定字体的大小。因为该属性的值会被用于计算em和ex长度单位，定义该值可能改变其他元素的大小。

## **`font-style`**

`font-style` CSS 属性允许你选择 `font-family` 字体下的 `italic `或 `oblique `样式。

## **`font-weight`**

`font-weight` CSS 属性指定了字体的粗细程度。 一些字体只提供 `normal` 和 `bold` 两种值。

## **`font-family`**

CSS 属性 `font-family` 允许您通过给定一个有先后顺序的，由字体名或者字体族名组成的列表来为选定的元素设置字体。
属性值用逗号隔开。浏览器会选择列表中第一个该计算机上有安装的字体，或者是通过 `@font-face` 指定的可以直接下载的字体。

# 6、背景

## **`background-color`**

CSS属性中的`background-color`会设置元素的背景色, 属性的值为颜色值或关键字”`transparent`”二者选其一。

## **`background-image`**

CSS `background-image` 属性用于为一个元素设置一个或者多个背景图像。

+ 渐变色：`linear-gradient(rgba(0, 0, 255, 0.5), rgba(255, 255, 0, 0.5))`

```css
.mydiv {
    background-image: url("/static/imags/logo.png");
}
```

`background-image` 的优先级比 `background-color` 要高，图片会显示在颜色的上方。

设置多个图片的时候，用逗号隔开。

## **`background-size`**

`background-size` 设置背景图片大小。图片可以保有其原有的尺寸，或者拉伸到新的尺寸，或者在保持其原有比例的同时缩放到元素的可用空间的尺寸。

```css
.mydiv {
    background-size: 50px;
}
```

+ background-size 可以指定宽高的大小，只写一个参数的话，会另一个参数会等比例变化。

如果设置了多个图片，也可以对应着设置多个图片的 size，也是通过逗号隔开。

## **`background-repeat`**

`background-repeat` CSS 属性定义背景图像的重复方式。背景图像可以沿着水平轴，垂直轴，两个轴重复，或者根本不重复。

## **`background-position`**

`background-position` 为背景图片设置初始位置。

使用两张图片做背景图片，左右各一半：

```css
.mydiv {
    height: 200px;
    width: 200px;
    background-color: limegreen;
    background-image: url("/static/images/img1.jpg"),
    url("/static/images/logo.jpg");
    background-size: 100px 200px, 100px 200px;
    background-repeat: no-repeat;
    background-position: left top, 100px top;
}
```

## **`background-attachment`**

`background-attachment` CSS 属性决定背景图像的位置是在视口内固定，或者随着包含它的区块滚动。

先在图片所在的 div 上下多加一点 div ，这样这个页面就变长了：

```html
<div></div>
<div></div>
<div></div>
<div></div>
<div></div>
<div class="mydiv">
  
</div>
<div></div>
<div></div>
<div></div>
<div></div>
<div></div>
```

然后设置样式：

```css
div {
    height: 200px;
}
.mydiv {
    height: 200px;
    width: 200px;
    background-color: limegreen;
    background-image: url("/static/images/img1.jpg"),
    url("/static/images/logo.jpg");
    background-size: 100px 200px, 100px 200px;
    background-repeat: no-repeat;
    background-position: left top, 100px top;
    background-attachment: scroll;  
}
```

+ `background-attachment: scroll; ` 表示图片会随着页面滚动而动
+ `background-attachment: fixed; ` 表示图片不会随着页面滚动而动，可以使用 `background-position` 来控制显示的位置。

## opacity

`opacity` 属性指定了一个元素的**不透明度**。换言之，`opacity` 属性指定了一个元素后面的背景的被覆盖程度。

设置背景图片的半透明：
```css
<div class="mydiv">
	<div></div>
</div>

.mydiv {
    height: 200px;
    width: 200px;
    background-color: limegreen;
    background-image: url("/static/images/img1.jpg");
    background-size: 100%;
    background-repeat: no-repeat;
}
.mydiv > div {
    height: 100px;
    width: 100px;
    background-size: 100%;
    background-image: url("/static/images/logo.jpg");
    opacity: 0.5;
}
```

# 7、边框

## **`border-style`**

`border-style` 是一个 CSS 简写属性，用来设定元素所有边框的样式。

这个属性有四个参数，按顺序来是：上右下左，顺时针方向上的每个边框。

如果我们只写一个参数的话，表示所有的边的边框都是这一个值：

```css
.div {
    border-style: solid;
}
```

如果写两个参数的话，其实表示的是上、右这样按顺序来的，然后下、左两边就会取各自的对边的值：

```css
.div {
    border-style: dotted solid;
}
```

如果写多个参数，就是按顺时针顺序来赋值，没有写的位置会取对边的样式。

## **`border-width`**

`border-width` 属性可以设置盒子模型的边框宽度。

`border-width` 同样可以设置四个参数，分别对应上右下左，多个参数的效果和 `border-style` 的规则一样。

## **`border-color`**

CSS属性`border-color` 是一个用于设置元素四个边框颜色的快捷属性： `border-top-color`, `border-right-color`, `border-bottom-color`, `border-left-color`

同样可以设置四个参数，，规则同上。

## **`border-radius`**

CSS 属性 `border-radius` 允许你设置元素的外边框圆角。当使用一个半径时确定一个圆形，当使用两个半径时确定一个椭圆。这个(椭)圆与边框的交集形成圆角效果。

![image-20240129161938016](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291619097.png)

角的顺序也是顺时针顺序。

将一个矩形变成圆形，只需要将 `border-radius` 设置为 50% 即可：

```css
.div {
    border-radius: 50%;
}
```

## **`border-collapse`**

`border-collapse` CSS 属性是用来决定表格的边框是分开的还是合并的。在分隔模式下，相邻的单元格都拥有独立的边框。在合并模式下，相邻单元格共享边框。

表格的边框是分开的：

```css
td {
    width: 20px;
    height: 20px;
    border-style: solid;
}

table {
    border: solid;
}
```

![image-20240129162849601](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291628657.png)

表格的边框是合并的：

```css
td {
    width: 20px;
    height: 20px;
    border-style: solid;
}

table {
    border: solid;
    border-collapse: collapse;
}
```

![image-20240129162946043](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291629096.png)

# 8、展示格式

## **`display`**

+ `block`：
  + 独占一行
  + width、height、margin、padding均可控制
  + width默认100%。
+ `inline`：
  + 可以共占一行
  + width与height无效，水平方向的margin与padding有效，竖直方向的margin与padding无效
  + width默认为本身内容宽度
+ `inline-block`:
  + 可以共占一行
  + width、height、margin、padding均可控制
  + width默认为本身内容宽度

## **`white-space`**

`white-space` CSS 属性是用来设置如何处理元素中的 空白 (en-US)。

```html
<div>锄禾日当午，汗滴禾下土。谁知盘中餐，粒粒皆辛苦。</div>
div {
    width: 100px;
    height: 100px;
    background-color: lightblue;
}
```

以上代码的效果是每句诗占一行，因为 div 的宽度不够。

添加以下样式可以设置不换行：

```css
white-space: nowrap;
```

添加以下样式可以达到 `<pre></pre>` 的 效果：

```css
white-space: pre;
```

在上面这个不换行的例子中，效果是这样的：

![image-20240129173501156](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291735220.png)

现在要设置超出矩形的部分显示为省略号：

```css
div {
    width: 100px;
    height: 50px;
    background-color: lightblue;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;  /*不加上面这一句没用*/
}
```

效果：

![image-20240129174030786](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291740830.png)

## **`text-overflow`**

`text-overflow` CSS 属性确定如何向用户发出未显示的溢出内容信号。它可以被剪切，显示一个省略号或显示一个自定义字符串。

只对横向超出范围有效。

## **`overflow`**

CSS属性 `overflow` 定义当一个元素的内容太大而无法适应 块级格式化上下文 时候该做什么。它是 `overflow-x` 和 `overflow-y` 的简写属性 。

隐藏多余的部分：

```css
overflow: hidden;
```

![image-20240129174132800](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291741859.png)

自动判断哪个方向超出，设置滚轮：

```css
overflow: auto;
```

![image-20240129174225940](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291742011.png)

两个方向都设置滚轮：

```css
overflow: scroll;
```

![image-20240129174252979](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401291742035.png)

如果只设置横向或者纵向的滚轮：

```css
overflow-x: scroll;
```

```css
overflow-y: scroll;
```

# 9、内边距与外边距

先定义一个 div，并给他设置样式，观察页面：

```html
<div class="div-outer">
    <div class="div-inner"></div>
</div>
<style>
    .div-outer {
        width: 300px;
        height: 300px;
        background-color: lightblue;
    }
</style>
```

观察页面会发现，div 展示出来的矩形并没有紧靠着窗口的边缘，而是留有一定的空隙。使用开发者工具，用箭头选择点击这个 div，在控制台的 body 区域就能看到一个盒子样式的模型，就可以看到 div 外面的外边距、边框、内边距、内容：

![image-20240130101936553](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301025924.png)

## **`margin`**

`margin` 属性为给定元素设置所有四个（上下左右）方向的外边距属性。

+ 可以接受1~4个值（上、右、下、左的顺序），多个参数的赋值规则同边框`border`。

+ 可以分别指明四个方向：`margin-top`、`margin-right`、`margin-bottom`、`margin-left`

+ 可取值

  + `length`：固定值

  + `percentage`：相对于包含块的宽度，以百分比值为外边距。

  + `auto`：让浏览器自己选择一个合适的外边距。有时，在一些特殊情况下，该值可以使元素居中。

    水平居中：只设置上下边距，左右边距使用 `auto`，这种方法只对块级元素有效。

    ```css
    margin: 0 auto;
    ```

+ 外边距重叠

  + 块的上外边距(`margin-top`)和下外边距(`margin-bottom`)有时合并(折叠)为单个边距，其大小为单个边距的最大值(或如果它们相

    等，则仅为其中一个)，这种行为称为边距折叠。

  + 父元素与后代元素：父元素没有上边框和`padding`时，后代元素的`margin-top`会溢出，溢出后父元素的`margin-top`会与后代元素取最大值。

去除外边距就是将外边距赋值为 0px。

```html
<div class="div-outer" style="margin:0px;">
    <div class="div-inner"></div>
</div>
```

但是有时候浏览器可能会有一些默认的外边距样式，比如 `body` 区域会有个 8px 的默认外边距，那么以上代码就可能不起作用，所以一般会这样写来清除所有默认的外边距样式：

```css
* {
    margin: 0px;
}
```

### 外边距重叠1：

当我们给里面的div设置一个外边距后：

```css
* {
    margin: 0px;
}
.div-outer {
    width: 300px;
    height: 300px;
    background-color: lightblue;
}
.div-inner {
    width: 100px;
    height: 100px;
    background-color: darkred;
    margin: 20px;
}
```

会发现页面上出现这种效果：

![image-20240130104258345](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301042456.png)此时就是上外边距发生了重叠。红色的div的外边距影响到了蓝色div的外边距，导致蓝色div也多了一个外边距。这是因为==蓝色div作为父元素没有上边框和`padding`时，后代元素的`margin-top`会溢出，溢出后父元素的`margin-top`会与后代元素取最大值。== 所以只要给蓝色div设置一个上边框就可以解决，注意，上边框不能设为 0px：

```css
.div-outer {
    border-top: 1px solid;
}
```

![image-20240130104742471](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301047572.png)

但是不管是设置父级元素的边框或者内边距时，都会影响到原来的元素高度，会让元素高度增加，所以还可以使用 `overflow` 来抵消这种外边距重叠的效果。

可以把子元素溢出的外边距当成是子元素的一部分，超出了父元素的顶部范围，所以就使用 `overflow:hidden;` 将它溢出部分给隐藏了，这样就可以了。

但是万一我们这个父元素需要将超出的部分显示出来，这时候就不能使用 `overflow:hidden` 了，还有一个方法，就是在父元素的前面再加一个元素即可。

```css
.div-outer::before {
    content: "";
    display: table;
}
```

注意，直接在HTML文档中添加一个元素是不行的：

```html
<div style="display: table;"></div>
<div class="div-outer">
    <div class="div-inner"></div>
</div>
```

### 外边距重叠2：

有两个元素 A、B，当 A 元素有一个对于 B 的下外边距时，且 B 元素有一个对于 A 的上外边距时，这时他们的外边距会发生重叠，会取最大值。

比如，再定义一个 div：

```html
<div class="div-outer">
    <div class="div-inner"></div>
    <div class="div-inner2"></div>
</div>
```

设置样式：

```css
.div-inner {
    width: 100px;
    height: 100px;
    background-color: darkred;
    margin-bottom: 20px;
}
.div-inner2 {
    width: 100px;
    height: 100px;
    background-color: darkcyan;
    margin-top: 30px;
}
```

此时页面上两个 div 的间距就是 30px，因为它取了最大值。

所以说外边距其实就是在某一个方向上，与其他元素相隔的最小距离。

另外，重叠只会出现在上下外边距上，左右外边距是不会有的。

```css
.div-inner {
    width: 100px;
    height: 100px;
    background-color: darkred;
    float: left;
    margin-right: 20PX;
}
.div-inner2 {
    width: 100px;
    height: 100px;
    background-color: darkcyan;
    float: left;
    margin-left: 20PX;
}
```

此时 A、B 元素之间的间距是 40px。

## **`padding`**

内边距是定义元素中的内容离某个方向上元素的边界的最小距离。

注意：**内边距会影响到元素的大小，元素大小（宽高）会加上内边距。**

+ 默认的，一个矩形的宽度为：内边距的宽度 + 内容的宽度 + 边框的宽度

`padding` CSS 简写属性控制元素所有四条边的内边距区域。

+ 可以接受1~4个值（上、右、下、左的顺序）
+ 可以分别指明四个方向：`padding-top`、`padding-right`、`padding-bottom`、`padding-left`
+ 可取值
  + `length`：固定值
  + `percentage`：相对于包含块的宽度，以百分比值为内边距。

# 10、盒子模型

## **`box-sizing`**

元素的总宽度 = 内边距的宽度 + 内容的宽度 + 边框的宽度

CSS 中的 `box-sizing` 属性定义了 user agent 应该如何计算一个元素的总宽度和总高度。

+ `content-box`：是默认值，设置`border`和`padding`均会增加元素的宽高。
+ `border-box`：设置`border`和`padding`不会改变元素的宽高，而是挤占内容区域。

# 11、位置

## **`position`**

CSS `position`属性用于指定一个元素在文档中的定位方式。

**流式渲染：**就是页面上的元素一个挨着一个的被渲染，是 `static` 的效果。

**定位类型：**

+ 定位元素（positioned element）是其计算后位置属性为 `relative`, `absolute`, `fixed `或 `sticky `的一个元素（换句话说，除`static`以外的任何东西）。
+ 相对定位元素（relatively positioned element）是计算后位置属性为 `relative` 的元素。
+ 绝对定位元素（absolutely positioned element）是计算后位置属性为 `absolute` 或 `fixed` 的元素。
+ 粘性定位元素（stickily positioned element）是计算后位置属性为 `sticky` 的元素。

**取值：**

+ `static`：该关键字指定元素使用正常的布局行为，即元素在文档常规流中当前的布局位置。此时 `top`, `right`, `bottom`, `left `和 `z-index` 属性无效。
  + `z-index`：是指向屏幕外的坐标轴，可以用来控制元素的层次显示
+ `relative`：该关键字下，元素先放置在未添加定位时的位置，再在不改变页面布局的前提下调整元素位置（因此会在此元素未添加定位时所在位置留下空白）。`top`, `right`, `bottom`, `left`等调整元素相对于初始位置的偏移量。
+ `absolute`：元素会被移出正常文档流，并不为元素预留空间，通过指定元素相对于最近的非 `static` 定位祖先元素的偏移，来确定元素位置。绝对定位的元素可以设置外边距（`margins`），且不会与其他边距合并。
+ `fixed`：元素会被移出正常文档流，并不为元素预留空间，而是通过指定元素相对于屏幕视口（`viewport`）的位置来指定元素位置。元素的位置在屏幕滚动时不会改变。
+ `sticky`：元素根据正常文档流进行定位，然后相对它的最近滚动祖先（nearest scrolling ancestor）和 containing block (最近块级祖先 nearest block-level ancestor)，包括`table-related`元素，基于`top`, `right`, `bottom`, 和 `left`的值进行偏移。偏移值不会影响任何其他元素的位置。

元素：

```html
<div class="div-outer">
    <div class="div-inner1">1</div>
    <div class="div-inner2">2</div>
    <div class="div-inner3">3</div>
</div>
```

## **static**

流式渲染，一个挨着一个渲染，就是默认的情况

```html
.div-inner1 {
    width: 50px;
    height: 50px;
    background-color: darkred;
    color: white;
    margin: 10px;
    display: inline-block;
}

.div-inner2 {
    width: 50px;
    height: 50px;
    background-color: darkred;
    color: white;
    display: inline-block;
    margin: 10px;
}

.div-inner3 {
    width: 50px;
    height: 50px;
    background-color: darkred;
    color: white;
    display: inline-block;
    margin: 10px;
}
```

## **relative**

元素有一个最初始所在的位置，然后在 `realative` 下，使用 `top`、`right`、`bottom`、`left` 可以控制元素上下左右地相对于原来地位置进行一个偏移，偏移的距离是以初始的位置为起点计算的，所以“相对”是相对于元素的初始位置。

```html
.div-inner2 {
    width: 50px;
    height: 50px;
    background-color: darkgreen;
    color: white;
    display: inline-block;
    margin: 10px;
    position: relative;
    top: 100px;
    right: 40px;
}
```

并且，该元素原来的位置不会被其他元素占据，依旧保持在那里。

![image-20240130113217725](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301132802.png)

使用 `z-index` 实现层次感：

```css
.div-inner1 {
    width: 50px;
    height: 50px;
    background-color: darkred;
    color: white;
    margin: 10px;
    display: inline-block;
}

.div-inner2 {
    width: 50px;
    height: 50px;
    background-color: darkgreen;
    color: white;
    display: inline-block;
    margin: 10px;
    position: relative;
    right: 60px;
}

.div-inner3 {
    width: 50px;
    height: 50px;
    background-color: darkblue;
    color: white;
    display: inline-block;
    margin: 10px;
    position: relative;
    right: 120px;
}
```

此时效果，此时的 1 被 2、3 盖住了：

![image-20240130114212243](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301142318.png)

使用 `z-index` 将 div1 盖住 div2、div3：

```css
position: relative;
z-index: 1;
```

此时因为默认的 `z-index` 都是 0，所以给 div1 的 `z-index` 设为 1 就可以盖住其他两个div，如果 div2 的 `z-index` 是 1 的话，那么 div1 的 `z-index` 就要设为 2 才能盖住 div2。

## **absolute**

`absolute` 是对应整个文档绝对定位，就是说，元素会随着文档的滚动而滚动。

`absolute` 定位时是从父节点开始向上找，会找到第一个非 `static` 的祖宗节点来定位。

在最开始的样子，我们给 div2 添加绝对定位：

```css
.div-inner2 {
    width: 50px;
    height: 50px;
    background-color: darkgreen;
    color: white;
    display: inline-block;
    position: absolute;
    top: 0px;
    left: 0px;
}
```

效果：

![image-20240130120045073](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301200149.png)

发现 div2 在指定 `top` 和 `left` 偏移为 0 的时候，是对齐窗口的左上顶点的，说明当前 `absolute` 是相对文档来定位的。因为它的父级 div 默认是 `static`.

如果我们把 div2 的父级元素的定位设为非 `static`，同时为了方便看效果，将最外层的 div 设置一个上外边距，此时效果：

![image-20240130115848261](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301158323.png)

这就能说明，`absolute` 是相对第一个非 `static` 祖宗节点来定位的。同时，也能发现， div2 这个元素已经被文档流中踢出来了，div3 会占掉 div2 在流中应该占据的位置。

## **fixed**

固定定位，也是从父节点开始向上找，找到第一个非 `static` 的元素来定位。

固定定位的元素不会随着文档的滚动而滚动。

```css
.div-inner2 {
    width: 50px;
    height: 50px;
    background-color: darkgreen;
    color: white;
    display: inline-block;
    position: fixed;
    top: 200px;
    right: 0px;
}
```

可以实现这样的效果：

![image-20240130120604316](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301206408.png)

## **sticky**

粘性定位，效果类似Excel中的冻结窗口。

```html
<div class="div-outer">
    <div class="div-inner2">2</div>
    <div class="div-inner1">1</div>
    <div class="div-inner2">2</div>
    <div class="div-inner3">3</div>
    <div class="div-inner2">2</div>
</div>
```

设置 div1 为粘性定位

```css
.div-inner1 {
    width: 50px;
    height: 50px;
    background-color: darkred;
    color: white;
    margin: 10px;
    position: sticky;
    top: 20px;
}
```

以上样式能实现的效果：当页面向下滚动时，当 div1 区域滚动到距离窗口顶部还剩 20px 距离时，就会停止滚动，div1 就会一直处于当前距离顶部 20px 的位置，但是页面的其他元素不会停止滚动。

设置 div3 为粘性定位

```css
.div-inner3 {
    width: 50px;
    height: 50px;
    background-color: darkblue;
    color: white;
    margin: 10px;
    position: sticky;
    bottom: 20px;
}
```

以上样式能实现的效果：当页面向上滚动时，当 div3 区域滚动到距离窗口底部还剩 20px 距离时，就会停止滚动，div3 就会一直处于当前距离底部 20px 的位置，但是页面的其他元素不会停止滚动。

# 12、浮动

现在有很多 div 块：
```html
<div class="div-outer">
    <div class="div-inner2">2</div>
    <div class="div-inner1">1</div>
    <div class="div-inner2">2</div>
    <div class="div-inner3">3</div>
    <div class="div-inner2">2</div>
    <div class="div-inner3">3</div>
    <div class="div-inner3">3</div>
    <div class="div-inner3">3</div>
    <div class="div-inner3">3</div>
    <div class="div-inner3">3</div>
    <div class="div-inner3">3</div>
    <div class="div-inner3">3</div>
</div>
```

要想这些 div 块实现一种效果就是当一行能放下这些块的时候九放在一行，放不下的话就换行放，可以实现 `inline-block` 实现：

```css
.div-inner1 {
    width: 50px;
    height: 50px;
    background-color: darkred;
    color: white;
    display: inline-block;
}

.div-inner2 { 
    width: 50px;
    height: 50px;
    background-color: darkgreen;
    color: white;
    display: inline-block;
}

.div-inner3 {
    width: 50px;
    height: 50px;
    background-color: darkblue;
    color: white;
    display: inline-block;
}
```

效果：

![image-20240130131434998](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301314093.png)

可以看到，我们并没有设置外边距属性，但是使用 `inline-block` 属性的话，一行中自带了一个空隙，如果想不要这个空隙，就要使用浮动来实现。将 `display:inline-block` 换成以下代码：

```css
float: left;
```

效果：

![image-20240130131723204](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301317289.png)

## **`float`**

`float` CSS属性指定一个元素应沿其容器的左侧或右侧放置，允许文本和内联元素环绕它。该元素从网页的正常流动(文档流)中移除，尽管仍然保持部分的流动性（与绝对定位相反）。

由于float意味着使用块布局，它在某些情况下修改 `display` 值的计算值：

+ `display`为`inline`或`inline-block`时，使用`float`后会统一变成`block`。

**取值：**

+ `left`：表明元素必须浮动在其所在的块容器左侧的关键字。
+ `right`：表明元素必须浮动在其所在的块容器右侧的关键字。

使用浮动后，该元素在页面上的位置就会被其他元素占据，使用浮动就相当于这个元素浮在了原来位置的上方，所以其他元素是可以占据它下方的原来的位置。

在上面代码的基础中，在添加一个新的div块,，设置样式：

```css
.div-inner4 {
    width: 100px;
    height: 100px;
    background-color: yellow;
}
```

然后看页面效果：

![image-20240130132419700](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301324789.png)

并没有看到我们的黄色div块，这是因为div4被放在了左上角四个格子的下面，因为这四个格子是浮动的，所以他们下方的位置可以被占据，如果把浏览器窗口拉大一点，就能看见下面的div4：

![image-20240130132603864](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301326963.png)

或者使用 `z-index` 也可以看见div4：

```css
.div-inner4 {
    width: 100px;
    height: 100px;
    background-color: yellow;
    position: relative;
    z-index: 1;
}
```

![image-20240130132702369](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301327453.png)

如果我们要将新的元素放在浮动元素的后面而不是下面的话，就需要使用 `clear`。

## **`clear`**

有时，你可能想要强制元素移至任何浮动元素下方。比如说，你可能希望某个段落与浮动元素保持相邻的位置，但又希望这个段落从头开始强制独占一行。此时可以使用`clear`。

**取值：**

+ `left`：清除左侧浮动。
+ `right`：清除右侧浮动。
+ `both`：清除左右两侧浮动

```css
.div-inner4 {
    width: 100px;
    height: 100px;
    background-color: yellow;
    clear: left;
}
```

![image-20240130132819222](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301328305.png)

# 实战一下

模拟实现 [StackOverflow](https://stackoverflow.com/?newreg=a61301344a764feca23593c0fa4025ec) 网站上的小名片：

![image-20240130134518892](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301345971.png)

利用浏览器的开发者工具，先搞清楚这个名片的结构布局，然后模仿着写代码。

```html
<div class="card">
    <div class="card-head">
        asked 3 hours ago
    </div>
    <div class="card-body">
        <div class="card-body-photo">
            <img src="/static/images/logo.jpg" alt="">
        </div>
        <div class="card-body-info">
            <div class="card-body-info-name">
                <a href="#" style="text-decoration: none;">zsm</a>
            </div>
            <div class="card-body-info-reputation">
                <span style="font-weight: bold;">679</span>
                <div class="card-body-info-reputation-circle" style="background-color: #b4b8bc;"></div>
                6
                <div class="card-body-info-reputation-circle" style="background-color: #ddc9b9;"></div>
                12
            </div>
        </div>
    </div>
</div>
```

```css
* {
    margin: 0px;
    padding: 0px;
}

.card {
    width: 200px;
    height: 67.49px;
    background-color: #edf5fd;
    padding: 5px 6px 7px 7px;
    box-sizing: border-box;
    margin: 50px auto;
}

.card-head {
    margin: 1px 0 4px 0;
    font-size: 12px;
}

.card-body-photo {
    float: left;
}

.card-body-photo>img {
    width: 32px;
    height: 32px;
}

.card-body-info {
    float: left;
    height: 32px;
    margin: 0 0 0 8px;
}

.card-body-info-name {
    font-size: 13px;
    height: 16px;
    line-height: 16px;
}

.card-body-info-reputation {
    font-size: 12px;
    height: 16px;
    line-height: 16px;
}

.card-body-info-reputation-circle {
    width: 6px;
    height: 6px;
    display: inline-block;
    border-radius: 50%;
    margin: 0 3px 0 2px;
}
```

效果：

![image-20240130150224262](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301502342.png)

实现B站的名片：

![image-20240130150822074](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301508167.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>bilibili</title>
    <link rel="stylesheet" href="/static/CSS/bilibili.css">
</head>
<body>
    <div class="card">
        <div class="bg"></div>
        <div class="content">
            <div class="left">
                <img src="/static/images/logo.jpg" alt="">
            </div>
            <div class="right">
                <div class="username">
                    <span>多低调</span>
                    <span>♂</span>
                    <span>LV4</span>
                </div>
                <div class="info">
                    <span>
                        22
                        <span>关注</span>
                    </span>
                    <span>
                        9
                        <span>粉丝</span>
                    </span>
                    <span>
                        0
                        <span>获赞</span>
                    </span>
                </div>
                <div class="btns">
                    <button>+关注</button>
                    <button>发消息</button>
                </div>
                <div></div>
            </div>
        </div>
    </div>
</body>
</html>
```

```css
* {
    margin: 0px;
    padding: 0px;
}

.card {
    width: 366px;
    margin: 0 auto;
    box-shadow: 0px 0px 2px grey;
    border-radius: 10px;
}

.bg {
    width: 366px;
    height: 85px;
    background-image: url("/static/images/img1.jpg");
    background-size: cover;
    border-radius: 10px 10px 0 0;
}

.content {
    width: 366px;
    height: 120px;
    border-radius: 0 0 10px 10px;
    padding: 10px 0 0 0;
    box-sizing: border-box;
}

.left {
    width: 110px;
    height: 100%;
    float: left;
}

.right {
    width: calc(100% - 110px);
    height: 100%;
    float: left;
}

.left>img {
    width: 48px;
    height: 48px;
    border-radius: 50%;
    margin: 0 auto;
    display: block;
}

.right>div {
    margin-top: 10px;
}

.username>span:nth-child(1) {
    font-size: 16px;
    margin: 0 5px 0 0;
    font-weight: bold;
}

.username>span:nth-child(2) {
    color: blue;
    font-weight: bold;
}

.username>span:nth-child(3) {
    color: #febb8b;
}

.info {
    font-size: 12px;
    margin-bottom: 16px;
}

.info>span {
    margin-right: 18px;
}

.info>span span {
    color: #adb3b5;
}

.btns button {
    width: 100px;
    height: 30px;
    margin-right: 8px;
    border-style: none;
    border-radius: 5px;
}

.btns button:nth-child(1) {
    background-color: #00aeec;
    color: white;
}

.btns button:nth-child(2) {
    background-color: white;
    border: 1px solid;
    color: #7a7174;
}
```

效果：

![image-20240130163109370](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301631483.png)

---

# 13、flex布局

`flex` CSS简写属性设置了弹性项目如何增大或缩小以适应其弹性容器中可用的空间。	

`flex` 用来更好地布局页面中地各个模块的。

一般默认的布局是有两个轴，默认是从往右为主轴，从上往下为交叉轴，这两个轴可以通过某些属性来改变。在页面上放模块的时候，默认就是先按主轴放，主轴放不下就按交叉轴放，也就是一行一行的放，一行放不下就放下一行。

![image-20240131114422787](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311144858.png)

首先有这样个页面：

```html
<div class="div-flex">
    <div class="item">1</div>
    <div class="item">2</div>
    <div class="item">3</div>
    <div class="item">4</div>
    <div class="item">5</div>
    <div class="item">6</div>
    <div class="item">7</div>
    <div class="item">8</div>
    <div class="item">9</div>
    <div class="item">10</div>
</div>
```

```css
.div-flex {
    width: 50%;
    height: 200px;
    background-color: lightblue;
}
.item {
    width: 100px;
    height: 100px;
}
.item:nth-child(even) {
    background-color: lightgray;
}
.item:nth-child(odd) {
    background-color: lightpink;
}
```

![](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301928662.png)

然后在最外层的样式中添加这样一句：

```css
display: flex;
```

页面就变成了这样：

![image-20240130192903797](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301929862.png)

并且，样式会随着页面大小的变化而进行压缩。而如果在每个 item div 上使用 `display:inline-block` 的话是这样的效果：

![image-20240131114236574](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311142664.png)

随着窗口变化的只有外层div的大小，item div并没有改变大小。

## **`flex-direction`**

CSS `flex-direction` 属性指定了内部元素是如何在 `flex` 容器中布局的，定义了主轴的方向(正方向或反方向)。

**取值：**

+ `row`：flex容器的主轴被定义为与文本方向相同。 主轴起点和主轴终点与内容方向相同。

+ `row-reverse`：表现和`row`相同，但是置换了主轴起点和主轴终点。

  ```css
  flex-direction: row-reverse;
  ```

  ![image-20240130193017141](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301930210.png)

+ `column`：`flex`容器的主轴和块轴相同。主轴起点与主轴终点和书写模式的前后点相同

  ```css
  flex-direction: column;
  ```

  ![image-20240130193239182](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301932258.png)

+ `column-reverse`：表现和`column`相同，但是置换了主轴起点和主轴终点

  ```css
  flex-direction: column-reverse;
  ```

  ![image-20240130193317565](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301933635.png)

## **`flex-wrap`**

CSS 的 `flex-wrap` 属性指定 `flex` 元素单行显示还是多行显示。如果允许换行，这个属性允许你控制行的堆叠方向。

**取值：**

+ `nowrap`：默认值。不换行。

+ `wrap`：换行，第一行在上方。

  ```css
  flex-wrap: wrap;
  ```

  ![image-20240130193946924](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301939001.png)

+ `wrap-reverse`：换行，第一行在下方。

  ```css
  flex-wrap: wrap-reverse;
  ```

  ![image-20240130194016671](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401301940745.png)

## **`flex-flow`**

CSS `flex-flow` 属性是 `flex-direction` 和 `flex-wrap` 的简写。默认值为：`row nowrap`。

```css
flex-flow: row-reverse nowrap;
```

## **`justify-content`**

CSS `justify-content` 属性定义了浏览器之间，如何分配顺着弹性容器主轴(或者网格行轴) 的元素之间及其周围的空间。

**取值：**

+ `flex-start`：默认值。左对齐。

+ `flex-end`：右对齐。

+ `space-between`：左右两段对齐。

+ `space-around`：在每行上均匀分配弹性元素。相邻元素间距离相同。每行第一个元素到行首的距离和每行最后一个元素到行尾的距离将会是相邻元素之间距离的一半。

  ![image-20240131124025622](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311240691.png)

  左右两边的距离是中间距离的一半。

+ `space-evenly`：flex项都沿着主轴均匀分布在指定的对齐容器中。相邻`flex`项之间的间距，主轴起始位置到第一个`flex`项的间距，主轴结束位置到最后一个`flex`项的间距，都完全一样。

  ![image-20240131124121253](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311241319.png)

  左右两边和中间的距离都一样。

## **`align-items`**

CSS `align-items` 属性将所有直接子节点上的`align-self`值设置为一个组。 `align-self`属性设置项目在其包含块中在交叉轴方向上的对齐方式。

**取值：**

+ `flex-start`：元素向主轴起点对齐。
+ `flex-end`：元素向主轴终点对齐。
+ `center`：元素在侧轴居中。
+ `stretch`：弹性元素被在侧轴方向被拉伸到与容器相同的高度或宽度。
  + 当没有定义高度的时候


## **`align-content`**

CSS 的 `align-content` 属性设置了浏览器如何沿着弹性盒子布局的纵轴和网格布局的主轴在内容项之间和周围分配空间。

和 `align-items` 类似，但是有点区别：

+ `align-items`：行之间会有间隔，`align-content`： 没有。
+ 当只有一行元素的时候，`align-items` 会有竖直居中效果，`align-content` 没有

**取值：**

+ `flex-start`：所有行从垂直轴起点开始填充。第一行的垂直轴起点边和容器的垂直轴起点边对齐。接下来的每一行紧跟前一行。
+ `flex-end`：所有行从垂直轴末尾开始填充。最后一行的垂直轴终点和容器的垂直轴终点对齐。同时所有后续行与前一个对齐。
+ `center`：所有行朝向容器的中心填充。每行互相紧挨，相对于容器居中对齐。容器的垂直轴起点边和第一行的距离相等于容器的垂直轴终点边和最后一行的距离。
+ `stretch`：拉伸所有行来填满剩余空间。剩余空间平均地分配给每一行。

现在就可以很简单通过 `flex` 布局的来实现 div 的居中：

```css
display: flex;
justify-content: center;
align-content: cneter;
```

## **`order`**

定义`flex`项目的顺序，值越小越靠前。

## **`flex-grow`**

CSS 属性 `flex-grow` CSS 设置 `flex` 项主尺寸 的 `flex` 增长系数。

负值无效，默认为 0。

在默认情况下，当flex容器的大小大于其中的div块时，div块不会变大；当felx容器的大小小于其中的div块时，div块会被压缩变小。

现在要实现当容器变大，div块也一起变大： 

```css
.item:nth-child(even) {
    background-color: lightgreen;
    flex-grow: 2;
}

.item:nth-child(odd) {
    background-color: lightpink;
    flex-grow: 1;
}
```

`flow-grow` 跟比例有关系，上面的代码中，偶数块会变大为奇数块的2倍。

## **`flex-shrink`**

CSS `flex-shrink` 属性指定了 `flex` 元素的收缩规则。`flex` 元素仅在默认宽度之和大于容器的时候才会发生收缩，其收缩的大小是依据 `flex-shrink` 的值。

负值无效，默认为1。

## **`flex-basis`**

CSS 属性 `flex-basis` 指定了 `flex` 元素在主轴方向上的初始大小。

**取值：**

+ `width` 值可以是 `<length>`; 该值也可以是一个相对于其父弹性盒容器主轴尺寸的百分数 。负值是不被允许的。默认为 `auto`。

## **`flex`**

`flex-grow`、`flex-shrink`、`flex-basis`的缩写。

**常用取值：**

+ `auto`：`flex: 1 1 auto`
+ `none`：`flex: 0 0 auto`

# 14、响应式布局

当网站跑在手机上时，会自动调整页面的布局来适应手机。

## media查询

当屏幕宽度满足特定条件时应用css。通过media可以得到当前屏幕的逻辑宽度是多少，可以在不同的宽度下选用不同的样式设置，不只是能查询宽度。

例如：

```css
@media(min-width: 768px) {
    .container {
        width: 960px;
        background-color: lightblue;
    }
}
```

例子：

```html
<div class="container">
    <div class="block"></div>
</div>
```

样式：

```css
.container {
    width: 80%;
    background-color: lightblue;
    margin: 0 auto;
    padding: 10px;
}

.block {
    width: 80%;
    height: 100vh;
    background-color: lightgreen;
    margin: 0 auto;
}
```

按F12打开控制台，并选择左上角的电脑手机按钮，这样可以在页面上面看到页面的大小，此时效果：

![image-20240131132618899](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311326021.png)

设置当页面的宽度大于768px的时候，将block的颜色改为红色：

```css
@media (min-width: 768px) {
    .block {
        background-color: red;
    }
}
```

这样，当页面的宽度被拉到768px及以上时，页面会变红：

![image-20240131132903939](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311329044.png)

## 栅格系统

现在有这样个页面：

![image-20240131134057006](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311340087.png)

```html
<div class="container">
    <div class="block">
        <div class="row">
            <div class="col">1</div>
            <div class="col">2</div>
            <div class="col">3</div>
        </div>
    </div>
</div>
```

```css
.container {
    width: 80%;
    height: 100vh;
    background-color: lightblue;
    margin: 0 auto;
    padding: 10px;
}

.col {
    width: 33.33333%;
    height: 100px;
    background-color: lightgray;
    line-height: 100px;
    color: white;
    float: left ;
    text-align: center;
    border: 1px solid black;
    box-sizing: border-box;
    font-size: 30px;
}
```

我们如果要把这三个col给设置为宽度比例为 1：2：3 的形式，需要这样写：

```html
<div class="row">
    <div class="col" style="width: 16.66667%">1</div>
    <div class="col" style="width: 33.33333%;">2</div>
    <div class="col" style="width: 50%;">3</div>
</div>
```

此时效果：

![image-20240131134336936](https://gitee.com/LowProfile666/image-bed/raw/master/img/202401311343998.png)

但是每次都这样写就会很麻烦。所以可以就屏幕分为固定的数量，然后预定义一些类，来表示占屏幕宽度的几分之一。

一般会把设备的屏幕宽度分为：xs、sm、md、lg、xl……

一般将整个屏幕分为 12 份（因为 12 的因子可以覆盖到大部分情况），然后给每一种情况预定义，对应着占据整个屏幕宽度的 1-12 份，比如对于中型设备：

```css
.col-md-1 {
    width: 8.3333333%;
}
.col-md-2 {
    width: 16.666667%;
}
.col-md-3 {
    width: 25%;
}

.col-md-4 {
    width: 33.333333%;
}
.col-md-5 {
    width: 41.666667%;
}

.col-md-6 {
    width: 50%;
}

.col-md-7 {
    width: 58.3333333%;
}

.col-md-8 {
    width: 66.6666667%;
}

.col-md-9 {
    width: 75%;
}
.col-md-10 {
    width: 8.33333333%;
}

.col-md-11 {
    width: 91.6666667%;
}

.col-md-12 {
    width: 100%;
}
```

也可以使用 `width` 的 `clac()` 函数：

```css
.col-md-1 {
    width: calc(100% * 1 / 12);
}
.col-md-2 {
    width: calc(100% * 2 / 12);
}
.col-md-3 {
    width: calc(100% * 3 / 12);
}

.col-md-4 {
    width: calc(100% * 4 / 12);
}
```

然后要将每个 col 定义成占屏幕的三分之一，就可以这样写：

```html
<div class="col col-md-4" >1</div>
<div class="col col-md-4" >2</div>
<div class="col col-md-4" >3</div>
```

而且一行放不下的话，会自动换行，并且还会随着窗口的变化而变化。

然后利用`@media`可以实现响应式布局。当屏幕宽度大于等于 768px 时，就应用这个中等的样式：

```css
@media (min-width: 768px) {
    .col-md-1 {
        width: calc(100% / 12);
    }
    .col-md-2 {
        width: calc(200% / 12);
    }
    .col-md-3 {
        width: calc(300% / 12);
    }
    .col-md-4 {
        width: calc(400% / 12);
    }
    .col-md-5 {
        width: 41.666667%;
    }
    .col-md-6 {
        width: 50%;
    }
    .col-md-7 {
        width: 58.3333333%;
    }
    .col-md-8 {
        width: 66.6666667%;
    }
    .col-md-9 {
        width: 75%;
    }
    .col-md-10 {
        width: 8.33333333%;
    }
    .col-md-11 {
        width: 91.6666667%;
    }
    .col-md-12 {
        width: 100%;
    }
}
```

当屏幕宽度小于等于767px的时候，就应用这个小型的样式：

```css
@media(max-width: 767px) {
    .col-sm-1 {
        width: calc(100% / 12);
    }
    .col-sm-2 {
        width: calc(200% / 12);
    }
    .col-sm-3 {
        width: calc(300% / 12);
    }
    .col-sm-4 {
        width: calc(400% / 12);
    }
    .col-sm-5 {
        width: 41.666667%;
    }
    .col-sm-6 {
        width: 50%;
    }
    .col-sm-7 {
        width: 58.3333333%;
    }
    .col-sm-8 {
        width: 66.6666667%;
    }
    .col-sm-9 {
        width: 75%;
    }
    .col-sm-10 {
        width: 8.33333333%;
    }
    .col-sm-11 {
        width: 91.6666667%;
    }
    .col-sm-12 {
        width: 100%;
    }
}
```

应用实例：一个登录页面，有用户名、密码输入框和一个个人简介文本域，在电脑的屏幕上，用户名和密码框显示在一行，个人简介在一行；在手机的屏幕上，用户名、密码、个人简介都独自在一行：

```html
<div class="row">
    <div class="col col-md-6 col-sm-12" >用户名</div>
    <div class="col col-md-6 col-sm-12" >密码</div>
    <div class="col col-md-12 col-sm-12" >个人简介</div>
</div>
```

## Bootstrap

[bootstrap地址](https://v5.bootcss.com/)

下载 boostrap 的包，然后引用要使用的 css 和 js 文件。

+ bootstrap.css：开发环境的css文件，有格式
+ bootstrap.min.css：生产环境的css文件，上面的压缩版，方便传输
+ bootstrap.js：开发环境
+ bootstrap.min.js：生产环境

然后将要用的文件复制到项目目录中，再在要使用的页面文件中引用对应的文件即可：

```html
<link rel="stylesheet" href="/static/bootstrap/bootstrap.css">
<script src="/static/bootstrap/bootstrap.js"></script>
```

然后就可以直接复制 bootstrap 官网上的各种样式到自己的页面中，即可使用。

