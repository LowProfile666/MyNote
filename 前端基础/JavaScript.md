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

