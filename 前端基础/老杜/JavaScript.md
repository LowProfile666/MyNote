# JavaScript

[TOC]

## 1. 概述

JavaScript 是运行在浏览器上的脚本语言，简称 JS。

### 1.1 发展

JavaScript 是网景公司（NetScape）的 布兰登艾奇（JavaScript 之父）开发的，最初叫 LiveScript。

LiveScript 的出现让浏览器更加的生动了，不再是单纯的静态页面了，页面更具有交互性。

在历史的某个阶段，sun 公司和网景公司有合作关系，sun 公司把 LiveScript 的名字修改为 JavaScript。 

网景公司最著名的就是领航者浏览器：Navigator 浏览器。LiveScript 的出现，最初的时候是为了 Navigator 浏览器量身定制一门语言，不支持其他浏览器。

当 Navigator 浏览器使用非常广泛的时候，微软害怕了，于是微软在最短的时间内组件了一个团队，开始研发只支持 IE 浏览器的脚本语言，叫做 Jscript。JavaScript 和 Jscript 并存的年代程序员是很痛苦的，因为要写两套程序。

在这种情况下，有一个非营利性的组织站出来了，叫 ECMA 组织（欧洲计算机协会）。ECMA 根据 JavaScript 制定了 ECMA-262 号标准，叫做 ECMA-Script，现代的 JavaScript 和 Jscript 都实现了 ECMA-Script 规范（JavaScript 和 Jscript 统一了）。

### 1.2 JavaScript 和 Java

**JavaScript 和 Java 没有任何关系，只是语法上有点相似。**

区别：

+ 他们运行的位置不同，Java 运行在 JVM 中，JavaScript 运行在浏览器的内存当中；

+ JavaScript 不需要程序员手动编译，编写完源代码之后，浏览器直接打开解释执行；
+ JavaScript 的“目标程序”以普通文本形式保存，这种语言都叫做“脚本语言”；

+ Java 的目标程序以 `.class` 形式存在，不能使用文本编辑器打开，不是脚本语言。

### 三大块

JavaScript 包括三大块

- **ECMAScript**：JS的核心语法（ES规范 / ECMA-262标准）

- **DOM**：Document Object Model（文档对象模型。对网页当中的节点进行增删改的过程）

  - HTML文档被当成一颗DOM树来看待
    ```js
    var domObj = document.getElementById("id");
    ```

- **BOM**：Browser Object Model（浏览器对象模型）

  - 关闭浏览器窗口、打开一个新的浏览器窗口、后退、前进、浏览器地址栏上的地址等，都是BOM编程

DOM 和 BOM 的区别和联系

- BOM 的顶级对象是：window
- DOM 的顶级对象是：document
- 实际上 BOM 是包括 DOM 的！

## 2. ECMAScript

### 2.1 注释

JS 中代码的注释和 Java 的注释一样

- `//` 这是单行注释 

- `/* */` 这是多行注释 

### 2.2 字符串

可以使用双引号表示字符串，也可以使用单引号。

在 js 中比较字符串是否相等使用 `==` 完成。

### 2.3 语句

JS 中的一条语句结束之后，可以使用分号 `;` 也可以不用。

### 2.4 HTML 中嵌入 JS 代码

有三种方式。

#### 2.4.1 onclick 方式

具体用法为：

```html
onclick = "JS代码"
```

JS 是一门事件驱动型的编程语言，依靠事件去驱动，然后执行对应的程。

在 JS 中有很多事件，其中有一个事件叫做：鼠标单击，单词：click，并且任何事件都会对应一个事件句柄叫做：onclick。【注意：事件和事件句柄的区别：事件句柄是在事件单词前添加一个 on】，而事件句柄是以HTML标签的属性存在的。

比如在一个按钮上注册点击事件，当点击这个按钮后，会出现一个弹窗：

```html
<input type="button" onclick="alert('你好')" value="点击" />	
```

+ 在 js 中有一个内置的对象叫做 `window`，全部小写，可以直接拿来使用，`window` 代表的是浏览器对象，`window` 对象有一个函数叫做：`alert`，用法是：`window.alert("消息")`，这样就可以实现弹窗了。
+ `window.alert("消息") ` 的 `window.` 可以省略不写。
+ `alert` 函数会阻塞整个HTMl页面的加载，直到用户点击确定。

执行原理：页面打开的时候，js 代码并不会执行，只是这段代码注册到按钮的 click 事件上了，等这个按钮发生 click 事件之后，注册在onclick 后面的 js 代码就会被浏览器自动调用。

效果如图：![image-20230908222803745](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309082228793.png)

#### 2.4.2 脚本块的方式

语法：

```html
<script type="text/javascript">
	中间是js代码
</script>
```

- JavaScript 的脚本块在一个页面当中可以出现多次，没有要求。
-  JavaScript 的脚本块出现的位置也没有要求，可以出现在文件中任意位置。
- 暴露在脚本块当中的程序，在页面打开的时候执行，并且遵守自上而下的顺序一次逐行执行（这个代码执行不需要事件）。

#### 2.4.3  引入外部的独立 JS 文件

语法：

```html
<script type="text/javascript" src="js文件路径"></script>
```

- 在需要的位置引入 js 脚本文件（同一个 js 文件可以被引入多次，但没必要 ）。
- 引入外部独立的 js 文件的时候，js 文件中的代码会遵循自上而下的顺序依次逐行执行 。
- 引入 js 文件后，可以继续写 js 脚本块。

### 2.5 变量

声明：

```javascript
var 变量名
```

赋值：

```javascript
变量名 = 值
```

JavaScript 是一种弱类型语言，没有编译阶段，一个变量可以随意赋值，什么类型都行。在 JS 中，当一个变量没有手动赋值的时候，系统默认赋值 `undefined`，`undefined` 在 js 当中是一个具体存在值。

#### 2.5.1 全局变量

在函数体之外声明的变量属于全局变量。

全局变量的生命周期：浏览器打开时声明，浏览器关闭时销毁。尽量少用，因为全局变量会一直在浏览器的内存当中，耗费内存空间，能使用局部变量就使用局部变量。

当一个变量声明的时候没有使用 `var` 关键字，那么不管这个变量是在哪里声明的，都是全局变量。

```javascript
var i = 100;
function access(){
    //访问的是全局变量
    alert("i = " + i);
}

//调用函数
access();
var name="jack";	//全局变量
function accessname(){
    var name = "Tom";	//局部变量
    alert("name = " + name);	//就近原则，访问局部变量，name=Tom
}

//调用函数
accessname();
alert("name = " + name);	//访问的全局变量，name=jack

//以下语法很奇怪
function myfunction(){
    //当一个变量声明的时候没有使用var关键字，那么不管这个变量是在哪里声明的，都是全局变量
    myname = "zhangshimao";
}

myfunction();
alert("myname = " + myname);
```

#### 2.5.2 局部变量

在函数体当中声明的变量，包括一个函数的形参都属于局部变量。

局部变量的生命周期是：函数开始执行时局部变量的内存空间开辟，函数执行结束之后，局部变量的内存空间释放。局部变量的生命周期较短。

### 2.6 函数

等同于 Java 中的方法，函数也是一段可以被重复利用的代码片段，一般都是可以完成某个特定功能的。函数必须调用才能执行。

定义格式：

第一种

```javascript
function 函数名 (形参列表) {
    函数体
}
```

第二种

```javascript
函数名 = function (形参列表) {
    函数体
}
```

js 函数在调用的时候，参数的类型没有限制，并且参数的个数也没有限制，很随意（弱类型）。

在 JS 中，函数的名字不能重名，当函数重名的时候，后声明的函数会将之前声明的同名函数**覆盖**。

### 2.7 数据类型

虽然 js 中的变量在声明的时候不需要指定数据类型，但是在赋值的时候，每一个数据还是有类型的。

原始类型：

+ Undefined
+ Number
+ String
+ Boolean
+ Null：只有一个值 null

引用数据类型：

+ Object 以及 Object子类

ES规范（ECMAScript规范），在ES6之后，又基于以上的 6 种类型之外添加了一种新的类型：Symbol。

#### 2.7.1 typeof

js 中有一个运算符叫做 `typeof`，这个运算符可以在程序的运行阶段动态的获取变量的数据类型。

语法：

```javascript
typeof 变量名
```

`typeof` 结果是以下 6 个字符串之一：注意全部是小写

- "undefined"

- "number"

- "string"

- "boolean"

- "object"

- "function"

#### 2.7.2 Undefined 类型

`Undefined` 类型只有一个值，这个值就是 `undefined`。

当一个变量没有手动赋值，系统默认赋值 `undefined`，或者也可以给一个变量手动赋值 `undefined`。

#### 2.7.3 Number 类型

整数、小数、正数、负数、NaN（不是数字）、Infinity（无穷大）都属于 `Number` 类型。

关于 NaN

- 表示 Not a Number,不是一个数字，但属于 `Number`。

- 什么情况下结果是 NaN

  - 运算结果本来应该是一个数字，最后算完不是一个数字的时候，结果是 NaN，如：`100 / china = NaN`

  - `+` 号两边有一个是字符串的话，会做字符串拼接，而不是加法，如：`100 + china = 100china`

关于Infinity

- 当除数为 0 的时候，结果为无穷大。

一些函数：

+ `isNaN()`：结果是 `true` 表示不是一个数字，结果是 `false` 表示是一个数字 。
+ `parseInt()`：可以将字符串自动转换成数字，并且取整数位。
+ `parseFloat()`：可以将字符串自动转换为数字。
+ `Math.ceil()`：(Math 是数学类，数学类当中有一个函数叫做 ceil()，作用是向上取整)。

#### 2.7.4 Boolean 类型

JS 中的 `Boolean` 类型永远都是只有两个值：`true` 和 `false`。

在 `bolean` 类型中有一个函数叫做：`Boolean()`，作用是将非布尔类型的转换成布尔类型。语法：

```javascript
Boolean(数据)
```

规律：“有”就转换成 `true`，“没有”就转换成 `false`。

```javascript
//规律：“有”就转换成true，“没有”就转换成false
alert(Boolean(1));			//true
alert(Boolean(0));			//false
alert(Boolean(""));		//false
alert(Boolean("abc"));		//true
alert(Boolean(null));		//false
alert(Boolean(NaN));		//false
alert(Boolean(undefined));	//false
alert(Boolean(Infinity));	//true
```

#### 2.7.5 String 类型

在 JS 当中，字符串可以使用单引号，也可以使用双引号。

```javascript
var s = "hello";
var t = "world";
```

创建字符串对象：

方法一

```javascript
var s = "abc";  // 小string（属于原始类型String）
alert(typeof s);	// "String"
```

方法二，使用 JS 内置的支持类 String

```javascript
var s = new String("abc");  // 大string（属于Object类型）
alert(typeof s);	// "Object"
```

需要注意的是：`String` 是一个内置的类，可以直接用，`String` 的父类是 `Object`。无论小 `string` 或者大 `String`，他们的属性和函数都是通用的。

关于 `string` 的常用属性和函数

常用属性

+ `length` 获取字符串长度

常用函数

- `indexOf`：获取指定字符串在当前字符串中第一次出现处的索引
- `lastIndexOf`：获取指定字符串在当前字符串中最后一次出现处的索引
- `replace`：替换
- `toUpperCase`：转换大写
- `toLowerCase`：转换小写
- `substring`：截取子字符串
- `substr`：截取子字符串
- `split`：拆分字符串

```javascript
//常用函数演示
alert("http://www.baidu.com".indexOf("http"));	//0
alert("http://www.baidu.com".indexOf("https"));//负数，-1

//判断一个字符串中是否包含某个子字符串
alert("http://www.baidu.com.".indexOf("https") >= 0 ? "包含" : "不包含");	//不包含

//替换,replace只替换了第一个
alert("name=value%name=value%name=value".replace("%","&"));	//name=value&name=value%name=value
//想全部替换掉需要使用正则表达式

//substr(startIndex,length)
alert("abcdefg".substr(2,4));	//cdef
//substring(startIndex,endIndex),注意：不包含endIndex
alert("abcdefg".substring(2,4));//cd
```

#### 2.7.6 Object 类型

`Object` 类型是所有类型的超类，自定义的任何类型，默认继承 `Object`。在 JS 中定义的类默认继承 `Object`，会继承 `Object` 类中所有的属性以及函数。换句话说，自定定义的类中也有以下属性和函数。

属性：

- `prototype`属性（常用）:作用是给类动态的扩展属性和函数
- `constructor`属性

函数：

- `toString()`
- `valueOf()`
- `toLocaleString()`

#### 2.7.7 null 和 NaN 和 undefined 的区别

先了解一下两个特殊的运算符：

+ `==`  ：等同运算符，只判断值是否相等。
+ `===` ：全等运算符：既判断值是否相等，又判断数据类型是否相等。

可以先使用 `typeof` 看一下这三个值的类型：

```javascript
alert(typeof null);	 // "object"
alert(typeof NaN);	 // "number"
alert(typeof undefined);  // "undefined"
```

再使用 `==` 等同运算符判断三者之间值的关系：

```javascript
alert(null == NaN);			// false
alert(null == undefined);	// true
alert(undefined == NaN);	// false
```

这说明：`null` 和 `undefined` 是可以等同的。

再使用 `===` 全等运算符：

```javascript
alert(null === NaN);		// false
alert(null === undefined);	// false
alert(undefined === NaN);	// false
```

### 2.8 定义类和创建对象

定义类的语法和定义函数一样。JS 中的类的定义，同时又是一个构造函数的定义，在 JS 中类的定义和构造函数的定义是放在一起完成的。

方法一

```javascript
function 类名 (形参) {
    
}
```

方法二

```javascript
类名 = function (形参) {
    
}
```

创建对象：

```javascript
new 构造方法(实参)  // 构造方法名和类名一致
```

比如：

```javascript
function sayHello(){

}

//把sayHello当作普通函数来调用
sayHello();

//这种方式就表示把sayHello当作一个类来创建对象
var obj = new sayHello();	//obj 是一个引用，保存内存地址指向堆中的对象

//定义一个学生类
function Student(){
    alert("Student……");
}

//当作普通函数调用
Student();

//当作类来创建对象
var stu = new Student();
alert(stu);		//[object Object]

//JS 中的类的定义，同时又是一个构造函数的定义
//在JS中类的定义和构造函数的定义是放在一起完成的
function User(a,b,c){
    //声明属性
    //User类中有三个属性：sno，sname，sage
    this.sno = a;
    this.sname = b
    this.sage = c;
}
```

#### 2.8.1 访问类的属性

两种方法：

方法一，通过 `.` 来访问，一个节点对象中只要有的属性都可以 "`.`"

```javascript
//创建对象
var u1 = new User(111,"zhangshan",30);
//访问对象属性
alert(u1.sno);
alert(u1.sname);
alert(u1.sage);
```

方法二，通过 `[]` 来访问

```javascript
//访问一个对象的属性还可以使用以下语法：
var u2 = new User(222,"lisi",25);
alert(u2["sno"]);
alert(u2["sname"]);
alert(u2["sage"]);
```

#### 2.8.2 prototype

可以通过`prototype`这个属性来给类动态扩展属性以及函数。

比如：

```javascript
// 先创建一个类
Product = function(pno,pname,price){
    //属性
    this.pname = pname;
    this.pno = pno;
    this.price = price;
    //函数
    this.getPrice = function(){
        return this.price;
    }
}

// 通过prototype这个属性来给类动态扩展属性以及函数
Product.prototype.getPname = function(){
    return this.pname;
}

// 调用后期扩展的getPname函数
var pname = xigua.getPname();
alert(pname);	//西瓜

// 给String扩展一个函数
String.prototype.suiyi = function(){
    alert("这是给String扩展的一个函数");
}
"abc".suiyi();	//这是可以的
```

### 2.9 JS 中的常用事件

常用事件

- `blur` 失去焦点

- `focus` 获得焦点

- `click` 鼠标单击

- `dbclick` 鼠标双击

- `keydown` 键盘按下

- `keyup` 键盘弹起

- `mousedown` 鼠标按下

- `mouseup` 鼠标弹起

- `mousemove` 鼠标移动

- `mouseout` 鼠标离开

- `mouseover` 鼠标经过

- `reset` 表单重置

- `submit` 表单提交

- `change`下拉列表选中项改变，或文本框内容改变

- `select` 文本被选定

- `load` 页面加载完毕(整个HTML页面中所有的元素全部加载完毕之后发生)
  以下代码表示当前页面加载完毕后就执行 statements：

  ```javascript
  window.onload = function(){
      statements;
  }
  ```

任何一个事件都会对应一个事件句柄，事件句柄就是在事件前面添加 `on` ，如 `onclick`。`onXXX` 这个事件句柄出现在一个标签的属性位置上（事件句柄以属性的形式存在）。

#### 2.9.1 注册事件的方式

有两种方式：

方法一，直接在标签中使用事件句柄。

```javascript
<script type="text/javascript">
	function sayHello(){
        alert("hello");
    }    
</script>
<body>
	<input type="button" value="hello" onclick="sayHello()" />    
</body>
```

以上代码的含义是：将 `sayHello` 函数注册到按钮上，等待 `click` 事件发生之后，该函数被浏览器调用，我们成这个函数为**回调函数。**

回调函数的特点：自己把这个函数代码写出来了，但是这个函数不是自己负责调用，由其他程序员负责调用该函数。



方法二，使用纯 js 代码完成事件的注册。

```javascript
<script type="text/javascript">
    function doSome(){
        alert("doSome>……");
    }

    var btnObj = document.getElementById("mybtn");
    btnObj.onclick = doSome; 
</script>
```

第一步：先获取这个按钮对象（`document`是全部小写，内置对象，可以直接使用，`document`就代表整个HTML页面）： 

```javascript
var btnObj = document.getElementById("mybtn");
```

第二步：给按钮对象的 `onclick` 属性赋值：

```javascript
btnObj.onclick = doSome;
```

 注意：这里千万不要加小括号，以下这是错误的写法：

```javascript
btnObj.onclick = doSome();
```

还可以使用匿名函数的方式进行注册事件：

```javascript
var btnObj1 = document.getElementById("mybtn1");
btnObj1.onclick = function(){	
    alert("这是一个匿名函数")		
};
```

这个函数没有名字，叫做 **匿名函数**，这个匿名函数也是一个回调函数。这个函数在页面打开的时候只是注册上，不会被调用，在 `click` 事件发生后才会调用。

#### 2.9.2 设置节点的属性

先获取节点对象，然后通过 `对象.属性名 = 属性值` 的语法就可以修改属性。一个节点对象中只要有的属性都可以 `.` 它。

```javascript
<script type="text/javascript">
    window.onload = function(){
        document.getElementById("btn").onclick = function(){
            document.getElementById("mytext").type = "checkbox";
        }
    }
</script>
<input type="text" id="mytext"/>
<input type="button" value="修改文本框为复选框" id="btn" />
```

#### 2.9.3 捕捉回车键

通过文本框的键盘事件，来获取键值：对于“键盘事件对象”来说，都有 `keyCode` 属性用来获取键值。

```javascript
<script type="text/javascript">
    window.onload = function(){
        document.getElementById("mytext").onkeydown = function(e){
            alert(e.keyCode);	
            alert(e)  // [object KeyboardEvent]
            if(e.keyCode == 13){  // 如果是回车键
                alert("登陆验证中....");
            }
        }
    }
</script>
<input type="text" id="mytext" />
```

常用键的键值：

+ 回车：13
+ ESC：27
+ 空格：32

### 2.10 void 运算符

`void` 运算符语法：

```javascript
void（表达式）
```

运算原理：执行表达式，但不返回任何结果。

假如要实现一个效果：用户点击一个超链接，会执行一段 JS 代码，但页面不会跳转。可以这样写：

```javascript
<a href = "" onclick="alert('test code')">
    既保留住超链接的样式，同时用户点击超链接的时候执行一段js代码，但页面不能跳转
</a> 
```

以上代码会将当前的页面刷新，其实是跳转到一个新的当前页面，因为 `href=""` 代表着本身这个页面。

如果这个页面很长，这个超链接在页面的底部，点击它的话就会刷新页面，页面就会回到顶部重新显示。为了不重新显示该页面，只执行一段 JS 代码，可以这样写：

```javascript
<a href = "javascript:void(0)" onclick="alert('test code2')">
    既保留住超链接的样式，同时用户点击超链接的时候执行一段js代码，但页面不能跳转
</a>
```

注意：不能直接 `void(0)` 写在 `href` 后面，因为系统会认为他是一个路径。

要这样写：`javascript:void(0)` ，这句代码中的 `javascript` 就是为了告诉浏览器，后面的是一段 js 代码。

### 2.11 控制语句

有 9 个控制语句，前 7 个都和 Java 的语法一样

- `if`
- `switch`
- `while`
- `do while`
- `for`
- `break`
- `continue`
- `for in`
- `with`

`for in` 用法和 Java 中增强 `for` 循环（`for each`）类似，`for in` 不仅可以遍历数组，还可以遍历对象的属性：

```javascript
// 创建JS数组
var arr = [false, true, 12, 3.14, "acd"];	// JS数组中的元素类型随意，元素的个数随意

// for in 遍历数组
for(var i in arr){	// i是数组元素的下标
    alert(arr[i]);	
}

// 创建类
User = function(username,password){
    this.username = username;
    this.password = password;
}
// 创建对象
var u = new User("张三","123");

// for in 遍历对象的属性
for(var i in u){	// i是属性名，是一个字符串
    alert(u[i]);  
}
```

使用 `for in` 遍历对象的属性时，取出的是对象的每个属性名，是一个字符串，以上的 `u[i]` 就相当于 `u["username"]` 和 `u["password"]`。

`with` 是为语句设定默认对象。 

语法格式：

```javascript
with (object) {
    statements;
}
```

`with`  后面小括号中的 `object` 是 `{}` 中的所有语句的默认对象。

比如，输出一个对象的属性平常这样写：

```javascript
var u = new User("张三","123");
alert(u.username);  // 张三
alert(u.password);  // 123
```

使用 `with` 语句就可以这样写：

```javascript
var u = new User("张三","123");
with (u) {
    alert(username);  // 对象默认是 u
    alert(password);
}
```

在有些时候，`with` 语句可以缩短代码量，比如以下代码的 `Math` 的重复使用：

```javascript
x = Math.cos(3 * Math.PI) + Math.sin(Math.LN10) 
y = Math.tan(14 * Math.E)
```

使用 `with` 后：

```javascript
with (Math) {   
    x = cos(3 * PI) + sin (LN10);    
    y = tan(14 * E);
}
```

## 3. DOM

DOM：Document Object Model（文档对象模型。对网页当中的节点进行增删改的过程）。就是将HTML文档当成一颗 DOM 树来看待。

DOM的顶级对象是：document。

### 3.1 获取节点对象

通过节点对象的 ID 来获取到该对象，使用 `getElementById` 函数：

```javascript
var domObj = document.getElementById("id值");
```

比如要实现这样一个功能，有两个文本框，一个按钮，在第一个文本框输入内容后，点击按钮，会将第二个文本框的内容也改为第一个文本框的内容，如图：![image-20230909191252033](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309091912106.png)

```javascript
<!DOCTYPE HTML>
<html>
	<head></head>
	<body>
		文本框 1<input type = "text" id = "text1"/>	
		<br />
		<br />
		<input type = "button" onclick = "m()" value="点击获取文本框的值"/>
		<br />
		<br />
		文本框 2<input type = "text" id = "text2"/>
	</body>
</html>
<script type="text/javascript">
	m = function(){
    	// 获取两个文本框的对象
		var text1 = document.getElementById("text1");
		var text2 = document.getElementById("text2");
    	// 修改第二个文本框的值
		text2.value = text1.value;
	}
</script>
```

### 3.2 innerHTML 和 innerText

`innerHTML` 和 `innerText` 都是属性。

- 相同点：都是设置元素内部的内容。

- 不同点：

  - `innerHTML`：会把后面的“字符串”当作一段HTML代码解释并执行。

  - `innerText`：即使后面是一段HTML代码，也只是将其当作普通的字符串来看待。

比如要实现这样一个功能，这有一个文本框，一个按钮，当没有在文本框中输入任何信息时，点击按钮会出现一段红色提示："当前内容为空！"，如图：![image-20230909192504308](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309091925356.png)![image-20230909192515251](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309091925312.png)

实现：在文本框和按钮之间我们可以使用一个 `div` 标签，为按钮注册一个点击事件，在这个事件中，要获取到文本框和 `div` 这两个节点对象，然后判断文本框的值是不是为 `""` ，是的话就使用 `innerHTML` 属性将 `div` 内部的值设为一段HTML代码，这段代码可以显示指定内容：

```javascript
<!DOCTYPE HTML>
<html>
	<head></head>
	<body>
		用户名：<input type = "text" id = "text1"/>	
		<div id="warn"></div>
		<input type = "button" onclick = "submit()" value="提交"/>
	</body>
</html>
<script type="text/javascript">
	submit = function(){
		var text1 = document.getElementById("text1")
		var warn = document.getElementById("warn")
		if (text1.value == "")
			warn.innerHTML = "<font color='red'>当前内容为空！</font>"
	}
</script>
```

如果使用 `innerTEXT` 属性的话，效果就是这样：

![image-20230909193037303](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309091930342.png)

### 3.3 正则表达式

正则表达式：Regular Expression，主要用在字符串格式匹配方面。

正则表达式实际上是一门独立的学科，在Java语言中支持，在C语言中也支持。大部分编程语言都支持正则表达式，正则表达式最初使用在医学方面，用来表示神经符号，目前使用最多的是计算机编程领域，用做字符串格式匹配，包括搜索方面等。

#### 3.3.1 常见的正则表达式符号

常见的正则表达式符号

- `.` ：匹配除换行符以外的任意字符 

- `\w` ： 匹配字母或数字或下划线或汉字

- `\s`  ：匹配任意的空白符

- `\d` ：匹配数字

- `\b` ：匹配单词的开始或结束

- `^` ：匹配字符串的开始

- `$` ：匹配字符串的结束

- `*` ：重复零次或更多次

- `+` ：重复一次或更多次

- `?` ：重复零次或一次

- `{n}` ：重复n次

- `{n,}` ：重复n次或更多次

- `{n,m}` ：重复n到m次

- `\W` ：匹配任意不是字母，数字，下划线，汉字的字符

- `\S` ：匹配任意不是空白符的字符

- `\D` ：匹配任意非数字的字符

- `\B` ：匹配不是单词开头或结束的位置

- `[^x]` ：匹配除了x以外的任意字符

- `[^aeiou]` ：匹配除了`aeiou` 这几个字母以外的任意字符

- 正则表达式当中的小括号 `()` 优先级比较高

- `[1-9]` ：表示1到9的任意一个数字（次数是1）

- `[A-Za-z0-9-]` ：表示`A-Z、a-z、0-9`，以上所有字符中的任意一个字符

- `[A-Za-z0-9-]` ：表示`A-Z、a-z、0-9、-`，以上所有字符中的任意一个字符

#### 3.3.2 常见的正则表达式

+ QQ号：`^[1-9]\d{4,10}$`，一般为5-11位数字，而且开头不为0。

+ 电话号：`^(\d{4}-\d{7,8}|\d{3}-\d{8})$`，一般为前3/4位数字，一个"-"，后面为8位数字。或者前4位数字，一个"-",后面为7位数字。

  ```
  /*0349-3089000 
  \d{4}-\d{7}
  
  010-34678903
  \d{3}-\d{8}
  
  0349-23456789
  \d{4}-\d{8}*/
  ```

+ 手机号：`^1[34578]\d{9}$`，般为11位数字，开头为1，第二位一般是3/4/5/7/8。

+ 邮箱号：`^\w+@[a-z0-9A-Z]+\.[a-z]+$`，一般开始为数字、字母、下划线(w),然后为@，接下来是数字或字母，然后是".",最后为字母。

+ 身份证：`^[1-9]\d{5}\d{4}\d{2}\d{2}\d{3}[0-9X]$`，一般为第一位数字不为0，然后是5位数字，接下来是出生年月日，然后是4位数字，最后一位数可能为X。

#### 3.3.3 创建正则表达式对象

两种方式：

方法一

```javascript
var regExp = /正则表达式/[flags];
```

方法二，使用内置支持类 `RegExp`

```javascript
var regExp = new RegExp("正则表达式","[flags]");
```

关于 `flags`：

- `g` （全文查找出现的所有 `pattern`） 

- `i`（忽略大小写）

- `m` （多行查找） ，当前面是正则表达式的时候，`m` 不能用，只有前面是普通字符串的时候，`m` 才可以用

正则表达式对象的 `test()` 方法，返回 `true` 或 `false`，调用格式：

```javascript
true / false = 正则表达式对象.test(用户填写的字符串)
```

+ `true`：字符串格式匹配成功
+ `false`：字符串格式匹配失败

比如，要实现这样一个功能，有一个文本框，一个按钮，在文本框中输入邮箱地址，点击按钮后判断邮箱地址是否合法，若不合法则在文本框后输出红色字体“邮箱地址不合法！”提醒，同时，重新点击文本框输入时，红色提示会消失。

```javascript
<script type="text/javascript">
    window.onload = function(){
        //给按钮绑定click事件
        document.getElementById("btn").onclick = function(){
            //这个是用户填写的字符串
            var email = document.getElementById("email").value;
            //这个是正则表达式对象
            var emailRegExp = /^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/;
            //这个是调用方法
            var ok = emailRegExp.test(email);
            if(!ok){
                document.getElementById("eamilError").innerText = "邮箱地址不合法！"
            }
        }
        //这是给文本框绑定focus事件，获得焦点
        document.getElementById("email").onfocus = function(){
            document.getElementById("eamilError").innerText = ""
        }
	}
</script>

<input type="text" id="email" />
<span id="eamilError" style="color:red;font-size:12px"></span>
<br>
<input type="button" value="验证邮箱" id="btn" />
```

#### 3.3.4 去除字符串前后空白

`trim()` 函数的功能是去除字符串前后的空白。使用方法：`字符串.trim()`。只能去除前后的空白，如果字符串中间有空白的话不受影响。

比如，在一个文本框中输入含有前后空格的字符串，点击按钮后，弹出去除前后空白的字符串，如图：![image-20230910182444005](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309101824073.png)

```javascript
<script type="text/javascript">
	submit = function(){
		var text1 = document.getElementById("text1");
		var value = text1.value.trim();
		alert("-->" + value + "<--");
	}
</script>
<input type = "text" id = "text1"/>	
<input type = "button" onclick = "submit()" value="提交"/>
```

而低版本的 IE 浏览器不支持字符串的 `trim` 函数，我们可以自己对 `String` 类扩展一个全新的 `trim` 函数，使用正则表达式和 `replace` 函数。

```javascript
String.prototype.trim = function(){
    // 在当前的函数中的this代表的当前字符串
    // return this.replace("前空白","").replace("后空白","");
    // return this.replace(/^\s+/,"").replace(/\s+$/,"");
    return this.replace(/^\s+|\s+$/g,"");
}
```

### 3.4 复选框的全选和取消全选

复选框使用 `input` 控件，将 `input` 的 `type` 属性设为 `checkbox` 就是复选框（`radio` 是单选）。

```html
<input type="checkbox" />
```

一般复选框会有很多个，想要一键全选，可以将每个复选框都拿到并且更改他们的状态为选中即可。这就需要使用到数组和循环。

单独使用一个主复选框表示是否全选，再通过其他复选框们的 `name` 属性拿到所有的复选框，用一个数组保存；如果是全选，则使用循环将数组中所有的复选框的状态改为选中，否则改为不选。

```javascript
<script type="text/javascript">
    window.onload = function(){
        // 获取主复选框对象
        var main = document.getElementById("main");
        main.onclick = function(){
            // 获取当前复选框的状态(复选框对象.checked)
            // 根据name属性获取对象集合
            var hobbies = document.getElementsByName("aihao");
            if(main.checked){
                //全选
                for(var i = 0;i < hobbies.length;i++){
                    hobbies[i].checked = true;
                }
            }else{
                //取消全选
                for(var i = 0;i < hobbies.length;i++){
                    hobbies[i].checked = false;
                }
            }
        }
    }
</script>
<input type="checkbox" id="main"/>全选
<input type="checkbox" name="hobby" id="smoke"/>抽烟
<input type="checkbox" name="hobby" id="drink"/>喝酒
<input type="checkbox" name="hobby" id="perm"/>烫头
```

优化：让其他复选框的状态变成主复选框的状态就可以了。

```javascript
<script type="text/javascript">
    window.onload = function(){
        // 获取对象
        var main = document.getElementById("main");
        var hobbies = document.getElementsByName("aihao");
        main.onclick = function(){
            for(var i = 0;i < hobbies.length;i++){
                hobbies[i].checked = main.checked;
            }
        }
        // 让主复选框跟着其他复选框的状态进行改变
        var all = hobbies.length;
        for(var i = 0;i < hobbies.length;i++){
            // 给每一个复选框设置单击事件
            hobbies[i].onclick = function(){
                var count = 0;
                // 遍历检查每一个复选的状态
                for(var j = 0;j < hobbies.length;j++){
                    if(hobbies[j].checked)
                        count++;
                }
                main.checked = (all == count);
            }
        }
    }
</script>
<input type="checkbox" id="main"/>全选
<input type="checkbox" name="hobby" id="smoke"/>抽烟
<input type="checkbox" name="hobby" id="drink"/>喝酒
<input type="checkbox" name="hobby" id="perm"/>烫头
```

### 3.5 下拉列表的值

下拉列表标签为 `select`，其中每个选项是 `option` 标签。

```html
<select>
    <option>--请选择省份--</option>
    <option>四川</option>
    <option>湖北</option>
    <option>河北</option>
    <option>河南</option>
</select>
```

以上代码效果如图：![image-20230910184759572](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309101847636.png)

这个下拉列表的值就是选中的选项的值。要想获取选中的选项的值，首先需要给每个选项的 `value` 赋值，然后可以使用 `onchange` 属性，这个属性表示当元素改变时运行脚本：

```html
<select onchange="alert(this.value)">
    <option>--请选择省份--</option>
    <option value="1">四川</option>	
    <option value="2">湖北</option>
    <option value="3">河北</option>
    <option value="4">河南</option>
</select>
```

这样当选中一个选项后，窗口会弹出这个选项的值。

也可以给下拉列表设个 ID，通过 ID 获得对象，通过对象的 `onchange` 属性来获取值：

```html
<script type="text/javascript">
    window.onload = function(){
        var list = document.getElementById("provinceList");
        list.onchange = function(){
            // 获取选中项的value
            alert(list.value);
        }
    }
</script>
<select id="provinceList">
    <option>--请选择省份--</option>
    <option value="1">四川</option>
    <option value="2">湖北</option>
    <option value="3">河北</option>
    <option value="4">河南</option>
</select>
```

### 3.6 显示网页时钟

#### 3.6.1 Date

JS 中有一个内置的支持类：`Date`，可以用来获取时间/日期。

获取系统当前时间：

```javascript
var nowTime = new Date();
```

转换成具有本地语言环境的日期格式：

```javascript
nowTime = nowTime.toLocaleString();
```

可以输出一下看看格式：

```javascript
alert(nowTime);  // 2023/9/10 19:02:17
```

我们还可以通过日期获取年月日等信息，自定制日期格式：

```javascript
var t = new Date();
var year = t.getFullYear();	// 返回年信息，以全格式返回
var month = t.getMonth();	// 月份是：0-11
var day = t.getDate();		//获取日信息
// var dayOfWeek = t.getDay();		//获取的一周的第几天：0-6

document.write(year+"年"+(month+1)+"月"+day+"日");  // 2023年9月10日
```

#### 3.6.2 获取毫秒

获取从`1970年1月1日 00：00：00 000`到当前系统时间的总毫秒数：

```javascript
var t = new Date();
var times = t.getTime();
```

一般会使用这个毫秒数当作时间戳（timestamp），可以用在一些特殊情况中。

#### 3.6.3 网页时钟

效果如下：![image-20230910191052328](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309101910390.png)

当点击显示当前时间时，下面出现当前时间，并且每一秒都会变一次；当点击时间停止时，时间就会停止不变：

```html
<script type="text/javascript">
    function displayTime(){
        var time = new Date();
        time = time.toLocaleString();
        document.getElementById("timeDiv").innerHTML = time;
    }
    // 每隔一秒调用displayTime函数
    function start(){
        // 从这行代码执行结束开始，则会不间断的，每隔1000毫秒调用一次displayTime函数
        v = window.setInterval("displayTime()",1000);
    }
    function stop(){
        window.clearInterval(v);
    }
</script>
<input type="button" onclick="start()" value="显示当前时间" />
<input type="button" onclick="stop()" value="时间停止"/>
<div id="timeDiv"></div>
```

### 3.7 内置类 Array

创建长度为 0 的数组：

```javascript
var arr = [];
```

另一种创建数组的对象的方式：

```javascript
var a = new Array();
var a2 = new Array(3);	// 3表示长度
var a3 = new Array(3,2);  // 3，2表示元素
```

#### 3.7.1 join 方法

返回字符串值，其中包含了连接到一起的数组的所有元素，元素由指定的分隔符分隔开来。

```javascript
arrayObj.join(separator);
```

比如：

```javascript
var b = [1,2,3,4];
var str = b.join("-");
alert(str);	//1-2-3-4
```

#### 3.7.2 模拟栈

JS 中的数组可以自动模拟 栈 数据结构：先进后出。

+ `push`压栈，在数组的末尾添加一个元素（数组长度+1）：

  ```javascript
  a.push(10);
  ```

+ `pop`出栈，将数组末尾的元素弹出（数组长度-1）：

  ```javascript
  var endElt = a.pop();
  ```

## 4. BOM

### 4.1 open和close

BOM编程中，`window`对象是顶级对象，代表浏览器窗口，`window`有`open`和`close`方法，可以开启窗口和关闭窗口。

注意：脚本只能关闭它们打开的窗口。

```html
<input type="button" value="开启百度(新窗口)" onclick="window.open('http://www.baidu.com');"/>
<input type="button" value="开启百度(当前窗口)" onclick="window.open('http://www.baidu.com','_self');"/>
<input type="button" value="开启百度(新窗口)" onclick="window.open('http://www.baidu.com','_blank');"/>
<input type="button" value="开启百度(父窗口)" onclick="window.open('http://www.baidu.com','_parent');"/>
<input type="button" value="开启百度(顶级窗口)" onclick="window.open('http://www.baidu.com','_top');"/>

<input type="button" value="打开表单验证" onclick="window.open('../DOM/005-表单验证.html')" />

<input type="button" value="关闭当前窗口" onclick="window.close()" />	
```

### 4.2 消息框和确认框

使用 `alert` 弹出消息框，`confirm` 弹出确认框。

```html
<script type="text/javascript">
    function del(){
        // var ok = window.confirm("亲，确认删除数据吗？")
        // alert(ok)
        if(window.confirm("亲，确认删除数据吗？"))
            alert("delete data ....")
    }
</script>
<input type="button" value="弹出消息框" onclick="alert('消息框！')" />
<input type="button" value="弹出确认框（删除）" onclick="del()" />
```

### 4.3 将当前窗口设置为顶级窗口

`window` 是当前浏览器窗口，`window.top` 就是当前窗口对相应的顶级窗口，`window.self` 是当前自己这个窗口。

```javascript
if(window.top != window.self){
    // 将当前窗口设置为顶级窗口
    window.top.location = window.self.location;
}
```

### 4.4 history对象

有两个函数：

+ `go()`：前进，`go(1)` 表示前进 1 个页面，注意：`go()` 必须要跟前进的页数。
+ `back()`：后退，`back(1)` 表示后退 1 个页面，注意：`back()` 不跟后退的页数时默认后退 1 页。

比如我在页面 a 中打开了页面 b，再在页面 b 中打开了页面 c，这时在 c 中调用 `back(1)` 函数，我会回到页面 b，再在 b 中调用 `back(1)` 会回到页面 a，这时在 a 中调用 `go(2)` 会回到页面 c。

还可以使用 `go(-1)` 来代替 `back()` 。

### 4.5 设置浏览器地址的URL

改变地址栏里的网站链接地址。

方法一：通过 `window` 对象的 `location` 属性和 `loaction` 的 `herf`  属性

```javascript
var locationObj = window.location;
locationObj.href = "http://www.baidu.com";

window.location.href = "http://www.baidu.com"

window.location= "http://www.baidu.com"
```

方法二：通过 `document` 对象的 `location` 属性和 `loaction` 的 `herf`  属性

```javascript
document.location.href = "http://www.baidu.com"

document.location = "http://www.baidu.com"
```

总结有哪些方法可以通过浏览器往服务器发送请求

+ 表单form 的提交
+ 超链接
+ document.location
+ window.location
+ window.open("url")

以上所有的请求方式均可以携带数据给服务器，只有通过表单提交的数据才是动态的。

## 5. JSON

JavaScript Object Notation（JavaScript对象标记，简称 JSON（数据交换格式））。

JSON主要的作用是：一种标准的数据交换格式（目前非常流行，90%以上的系统，系统A与系统B交换数据的话，都是采用JSON）。

JSON是一种标准的轻量级的数据交换格式，特点是体积小、易解析。

在实际的开发中有两种数据交换格式，使用最多，其一是JSON，另一个是XML

+ XML体积较大，解析麻烦，但是有其优点：语法严谨（通常银行相关的系统之间进行数据交换的话会使用XML）

**JSON 在 JS 中以 JS对象的形式存在。**

### 5.1 创建JSON对象

JSON也可以称为无类型对象

```javascript
var stu ={
    "sno" : "001",
    "sname" : "张三",
    "sex" : "男"
};
```

访问 JSON 对象的属性：

```javascript
alert(stu.sno+","+stu.sname+","+stu.sex)
```

之前没有JSON的时候，定义类、创建对象、访问对象的属性：

```javascript
student = function(sno,sname,sex){
    this.sno = sno;
    this.sname = sname;
    this.sex = sex;
}
var stu1 = new student("111","里斯",'男')
alert(stu1.sno+","+stu1.sname+","+stu1.sex)
```

复杂一点的 JSON 对象：就是JSON对象里面包含着其他多种类型的数据

```javascript
var user = {
    "usercode" : 10,
    "username" : "张三",
    "sex" : true,
    "address" : {
        "city" : "北京",
        "street" : "大兴区",
    },
    "aihao" : ["smoke","drink","tt"]
};
```

访问复杂的对象的属性：

```javascript
alert(user.username+"居住在"+user.address.city)
```

设计JSON格式的代码，这个JSON格式的数据可以描述整个班级中每一个学生的信息，以及总人数信息：

```javascript
var Students = {
    "total" : 3,
    "students" : [
        {"name":"", "sex":"", "age":""},
        {"name":"", "sex":"", "age":""},
        {"name":"", "sex":"", "age":""}
    ]
};
```



### 5.2 JSON 数组

定义：

```javascript
var students =[
    {"sno":"110","sname":"张三","sex":"男"},
    {"sno":"112","sname":"李四","sex":"男"},
    {"sno":"113","sname":"王五","sex":"男"}
];
```

遍历：

```javascript
for(var i = 0;i < students.length;i++){
    var temp = students[i];
    alert(temp.sno+","+temp.sname+","+temp.sex)
}
```

### 5.3 eval 函数

`eval` 函数的作用是：将字符串当作一段JS代码解释并执行，比如：	

```javascript
window.eval("var i = 100");
alert("i = " + i)	// i = 100
```

Java 连接数据库，查询数据之后，将数据在 Java 程序中拼接成 JSON 格式的 '字符串'，将 JSON 格式的字符串响应到浏览器。

也就是说，Java 响应到浏览器上的仅仅是一个 JSON 格式的字符串 ，还不是一个 json 对象，可以使用 `eval` 函数，将 json 格式的字符串转换成 json 对象。

比如，这是 Java 程序发过来的 JSON 格式的字符串：

```javascript
var formJava = "{\"name\":\"zhangsan\",\"password\":\"123\"}";
```

将以上的 json 格式的字符串转换成 json 对象：

```javascript
window.eval("var jsonObj = " + formJava);
```

然后就可以访问该 json 对象：

```javascript
alert(jsonObj.name+","+jsonObj.password)
```

### 5.4 [] 和 {} 的区别

在 JS 中

+ `[]` 是数组

  ```javascript
  var arr = [1,2,3];
  ```

+ `{}` 是JSON

  ```javascript
  var jsonObj = {"name":"zs", "age":20};
  ```

### 5.5 table 的 tbody

现在有这些 json 数据：

```javascript
var data = {
    "total" : 0,  
    "emps" : [
        {"empno" : 1, "empname" : "Jack"},
        {"empno" : 2, "empname" : "John"},
        {"empno" : 3, "empname" : "Alice"},
        {"empno" : 4, "empname" : "Bob"},
        {"empno" : 5, "empname" : "Tom"}
    ]
}
```

希望把数据展示到一个 table 中 ：

```javascript
window.onload = function(){
    var displayElt = document.getElementById("display");
    displayElt.onclick = function(){
        var emps = data.emps;
        var html = "";
        for(var i = 0;i < emps.length;i++){
            var emp = emps[i];
            html += "<tr>";
            html += "<td>"+emp.empno+"</td>";
            html +=	"<td>"+emp.empname+"</td>";
            html += "</tr>";
            data.total++;
        }
        document.getElementById("tbodyId").innerHTML = html;
        document.getElementById("count").innerHTML = data.total;
    }
}
```

这个 table 是这样的：

```html
<h1>员工信息表</h1>
<input type="button" value="显示员工信息" id="display"/>
<hr >
<table border="1px" width="50%">
    <tr>
        <th>员工编号</th>
        <th>员工姓名</th>
    </tr>
    <tbody id="tbodyId"></tbody>
    总共<span id="count">0</span>条数
</table>
```

最终结果如下：![image-20230911154243341](https://gitee.com/LowProfile666/image-bed/raw/master/img/202309111542450.png)
