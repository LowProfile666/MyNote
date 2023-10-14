# CSS

[TOC]

## 1. 概述

**CSS**（Cascadinig　Style　Sheet）：层叠样式表语言。它的作用是修饰HTML页面，设置HTML页面中的某些元素的样式，让HTML页面更好看，就是HTML的化妆品一样。

## 2. HTML 中嵌入 CSS 的方式

有三种方式：内联定义方式、样式块方式、链入外部样式表文件（最常用）。

### 内联定义

在标签内部使用`style`属性来设置元素的CSS样式，这种方式称为内联定义方式。

语法：`<标签 style=“样式名：样式值；样式名：样式值；……”></标签>`

比如，将一段文字的颜色设为红色：

```html
<p style="color:red">
    哈哈哈
</p>
```

效果如下：

<p style="color:red">
    哈哈哈
</p>

### 样式块

在`head`标签中使用`style`块，这种方式称为样式块方式。

语法：

```html
<head>
    <style type="text/css">
        选择器{
             样式名：样式值；
             样式名：样式值；
              ……
         }
    </style>
<head>
```

选择器有很多种，常用有：

+ 类选择器：通过类别名称选择具有特定类别的HTML元素。类选择器以 `.`开头，后面跟着类别名称。
  ```html
  <style type="text/css">
      .highlight {
        background-color: yellow;
      }
  </style>
  ```

  这将选择所有具有类别为 **"highlight"** 的元素，将其背景色设为黄色。

+ 标签（元素）选择器：通过标签名选择HTML元素
  ```html
  <style type="text/css">
      p {
          color: red;
      }
  </style>
  ```

  这将选择所有 `<p>` 元素，将其内容改为红色。

+ id 选择器：通过元素的唯一标识符（ID）选择 HTML 元素。ID 选择器以 `#` 开头，后面跟着 ID 名称。
  ```html
  #runoob {
    width: 200px;
  }
  ```

  这将选择具有 ID 为 **"runoob"** 的元素，将其宽度设为 200px。

### 链入外部样式表

将样式写到一个独立的`.css`文件中，在需要的网页上直接引入css文件，样式就引入了，这种方式称为链入外部样式表文件（最常用）。

语法：`<link type="text/css' rel="stylesheet" href="css文件的路径" />`

这种方式易维护，维护成本较低。

## 3. 列表样式

`list-style-type:none;`  去除列表自带的小圆点