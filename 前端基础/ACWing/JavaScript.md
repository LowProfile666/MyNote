# 1、JS的调用方式与执行顺序

## **使用方式**

HTML页面中的任意位置加上`<script type="module"></script>`标签即可。

+ 一般将 `<script></script>` 块放在页面的最下方，因为页面的渲染是从上往下渲染的，脚本块如果放在页面代码前面的话，就有在页面元素还没有渲染出来的情况下引用页面元素，就会出现一些错误。

常见使用方式有以下几种：

+ 直接在`<script type="module"></script>`标签内写JS代码。

  + 声明模块化脚本，在模块中，可以使用 `import` 和 `export` 语法进行模块的导入和导出。
  + 这个写法是符合ES6语法的
  + 使用` <script></script>` 声明的js代码是全局的，可能会在不同区域的js代码中产生冲突，加上 `type=module` 后，会限制该脚本快中的js代码，不会影响其他区域也不会被影响。

+ 直接引入文件：`<script type="module" src="/static/js/index.js"></script>`。

+ 将所需的代码通过`import`关键字引入到当前作用域。

  例如：

  `/static/js/index.js`文件中的内容为：

  ```js
  let name = "acwing";
  
  function print() {
      console.log("Hello World!");
  }
  
  export {  // 里面写想要让其他文件引用到的变量
      name,
      print
  }
  ```

  + 如果文件中有很多的变量的话，想让其他文件只能引用一部分的话，就将这部分写在 `export` 中

  `<script type="module"></script>` 中的内容为：
  
  ```js
  <script type="module">
      import { name, print } from "/static/js/index.js";
  
      console.log(name);
      print();
  </script>
  ```

## **执行顺序**

+ 类似与HTML与CSS，按从上到下的顺序执行；
+ 事件驱动执行；

## **HTML, CSS, JavaScript三者之间的关系**

+ CSS控制HTML
+ JavaScript控制HTML与CSS
+ 为了方便开发与维护，尽量按照上述顺序写代码。例如：不要在HTML中调用JavaScript中的函数。

## js的调试输出语句

```js
console.log();
```

在 `log()` 小括号中写入输出的东西，输出的东西在浏览器的控制台里看。

**输出字符串**

```js
console,log("hello");
console.log("hello" + "world");
```

**输出多个变量**

```js
let name = "zsm";
console.log("hello",name,12);
```

# 2、变量与运算符

## let和const

用来声明变量，作用范围为当前作用域。

+ `let`用来定义变量；
+ `const`用来定义常量；

例如：

```js
let s = "hello", x = 5;

let d = {
    name: "zsm",
    age: 18,
}

const n = 100;
```

定义变量时，是不需要声明类型的，变量的类型是动态的。

### 解构赋值

定义多个变量时，还可以这样写：

```js
let [a, b] = [1, 2];
console.log(a, b)  // 1 2
```

### let与var

let 和 var 都可以声明变量，但是 let 更加严格。

+ var 声明的变量是函数作用域（在整个函数中都有效），let 声明的变量是块级作用域（只在声明的代码块中有效）

以下代码通过 var 创建变量，在整个函数 `fun` 中都可以访问到：

```js
function fun () {
    if (true) {
        var a = 10;
    }
    console.log(a)  // 10
}
```

以下代码通过 let 创建变量，只能在那个大括号域中访问：

```js
function fun () {
    if (true) {
        let a = 10;
    }
    console.log(a)  // Uncaught ReferenceError: a is not defined
}
```

+ `var` 声明的变量可以先使用后定义（值是`undefined`），`let` 声明的变量先使用后定义会报错

```js
console.log(b);  // undefined
var b = 10;
```

```js
console.log(b);  // Uncaught ReferenceError: Cannot access 'b' before initialization
let b = 10;
```

## 变量类型

可以使用 `typeof` 运算符来查看一个变量的类型：

```js
let x = 1;
console.log(typeof x);
```

+ `number`：数值变量，例如1, 2.5

  + 不区分小数和整数，都是 `number` 类型

+ `string`：字符串，例如"hello", 'zsm'，**单引号与双引号均可**。字符串中的每个字符为只读类型。

  ```js
  let s = "zsm";
  console.log(s[0]);  // z
  s[0] = 'h';  // Uncaught TypeError: Cannot assign to read only property '0' of string 'zsm'
  ```

+ `boolean`：布尔值，例如`true`, `false`

+ `object`：对象，键值对

  ```js
  let obj = {
      name: 'zsm',
      age: 18,
      "tel": "10086"
  }
  ```

  属性名（键名）可以使用引号括起来也可以不用，值的类型可以是任意类型。

  **调用对象中的属性**

  Java数组的方式：

  ```js
  console.log(obj["name"]);  // zsm
  ```

  这里 `name` 必须要用引号。

  Java对象的方式：

  ```js
  console.log(obj.age);  // 18
  ```

  **动态添加属性**

  ```js
  obj["school"] = "JCUT";
  obj.major = "computer";
  ```

  **空对象**

  `null` 也是 `object` 类型。

  **删除对象的属性**

  ```js
  delete obj.school;
  ```

+ `undefined`：未定义的变量

  变量的数据类型都是由值来决定的，如果定义了一个变量没有赋值，那这个变量就是 `undefined` 类型的。

  `undefined` 也可以直接被用来赋值。

类似于Python，JavaScript中的变量类型可以动态变化。

## 运算符

与C++、Python、Java类似，不同点：

+ `**`表示乘方

+ 等于与不等于用`===`和`!==`

  `===` 会判断类型，`==` 只会判断值

  ```js
  console.log(1 == "1");  // true
  console.log(1 === "1");  // false
  ```

使用除法的时候，不会向 Java 那样整除：

```js
console.log(5 / 3);  // 1.6666666666666667
```

整除：

```js
console.log(parseInt(5 / 3));  // 1
```

# 3、输入与输出

## 输入

从HTML与用户的交互中输入信息，例如通过`input`、`textarea`等标签获取用户的键盘输入，通过`click`、`hover`等事件获取用户的鼠标输入。

比如现在有个页面：

```html
<body>
    输入：<br>
    <textarea class="input"></textarea>
    <br>
    <button>run</button>
    <pre></pre>
</body>
<style>
    textarea {
        width: 200px;
        height: 200px;
        background-color: lightblue;
    }

    pre {
        width: 200px;
        height: 200px;
        background-color: lightgrey;
    }
</style>
```

![image-20240201235538780](C:/Users/20620/AppData/Roaming/Typora/typora-user-images/image-20240201235538780.png)

如果想要用户输入内容到第一个文本域中，点击 run 按钮后，用户输入的内容会显示到下面的 `pre` 标签中，就需要先获取到页面元素，然后拿到用户输入的值，在赋给 `pre` 标签。

如果要获取页面元素中用户的输入，可以使用 `document.querySelector()` 来先获取到页面的标签，这个函数的选择规则和 CSS 的选择器规则一样，它会返回第一个人满足要求的标签元素。`document.querySelectorAll()` 就可以获取所有满足条件的标签元素。

```js
let input = document.querySelector(".input");  // 获取第一个input类的元素
let run = document.querySelector("button");  // 获取第一个button标签元素
let output = document.querySelector("pre");  // 获取第一个pre标签元素
```

当我们点击按钮的时候，就获取到用户的输入，

```js
run.addEventListener("click", function () {
	let val = input.value;  // 获取到用户输入的值
    output.innerHtml = val;  // 将用户输入的值显示到pre标签中
})
```

+ `addEventListener()` ：给某个标签绑定一个事件函数。第一个参数是一个字符串，指绑定哪个事件；第二个参数是绑定的函数，当触发了这个事件之后，就会执行的函数
+ `.value`：是一个属性，这个属性表示了标签元素的值，`textarea` 和 `input` 标签的 `value` 就是用户输入的内容
+ `innerHtml`：是一个属性，这个属性可以设置标签元素的显示内容，可以渲染 HTML 语句

然后把这些代码封装到一个 js 文件中：

```js
let input = document.querySelector(".input");
let run = document.querySelector("button");
let output = document.querySelector("pre");

function main() {
    run.addEventListener("click", function () {
        let val = input.value;
        output.innerHTML = val;
    })
}

export {
    main
}
```

通过`Ajax`与`WebSocket`从服务器端获取输入。

标准输入，参考

```js
let fs = require('fs');
let buf = '';

// 输入开始时的执行函数
process.stdin.on('readable', function() {
    let chunk = process.stdin.read();
    if (chunk) buf += chunk.toString();
});

// 输入结束时的执行函数
process.stdin.on('end', function() {
    buf.split('\n').forEach(function(line) {
        let tokens = line.split(' ').map(function(x) { return parseInt(x); });
        if (tokens.length != 2) return;
        console.log(tokens.reduce(function(a, b) { return a + b; }));
    });
});
```

## 输出

调试用`console.log`，会将信息输出到浏览器控制台

改变当前页面的HTML与CSS

通过`Ajax`与`WebSocket`将结果返回到服务器。

## 格式化字符串

字符串中填入数值：

```js
let name = 'zsm', age = 18;
let s = `My name is ${name}, I'm ${age} years old.`;
```

定义多行字符串：

```js
let s = 
`<div>
    <h2>标题</h2>
    <p>段落</p>
/div>`
```

保留两位小数如何输出：

```js
let x = 1.234567;
let s = `${x.toFixed(2)}`;
```

取整：

```js
let x = 1.23456;
console.log(Math.ceil(x));  // 向上取整
console.log(Math.round(x));  // 取整
console.log(Math.floor(x));  // 向下取整
```

## 练习

+ 输出Hello World。

  ```js
  console.log("Hello World");
  ```

+ 输入两个数，计算两个数的和。

  ```js
  function main() {
      run.addEventListener("click", function () {
          let [a, b] = input.value.split(" ");
          a = parseInt(a), b = parseInt(b);
          output.innerHTML = a + b;
      })
  }
  ```

+ 输入一个小数，返回向零取整之后的结果。

  ```js
  function main() {
      run.addEventListener("click", function () {
          let num = input.value;
          output.innerHTML = parseInt(num);
      })
  }
  ```

  `parseInt()` 就是向 0 取整。

+ 输入a, b, c，输出 (a + b) * c 的值。

  ```js
  function main() {
      run.addEventListener("click", function () {
          let [a, b, c] = input.value.split(" ");
          a = parseInt(a);
          b = parseInt(b);
          c = parseInt(c);
          output.innerHTML = (a + b) * c;
      })
  }
  ```

+ 求反三位数。

  ```js
  function main() {
      run.addEventListener("click", function () {
          let num = input.value;
          let a = num % 10;
          let b = parseInt(num / 10 % 10);
          let c = parseInt(num / 100);
          let s = `${a}${b}${c}`;
          output.innerHTML = s;
      })
  }
  ```

+ 输出如下的菱形。

  ```js
        *
       ***
      *****
       ***
        *
  ```

  ```js
  function main() {
      run.addEventListener("click", function () {
          output.innerHTML = `  *
   ***
  *****
   ***
    *`;
      })
  }
  ```

# 4、判断语句

JavaScript中的`if-else`语句与C++、Python、Java中类似。

例如：

```js
let score = 90;
if (score >= 85) {
    console.log("A");
} else if (score >= 70) {
    console.log("B");
} else if (score >= 60) {
    console.log("C");
} else {
    console.log("D");
}
```

JavaScript中的逻辑运算符也与C++、Java中类似：

+ `&&`表示与
+ `||`表示或
+ `!`表示非

## **练习**

+ 输入一个年份，如果是闰年输出yes，否则输出no。

  闰年判断：**能被4整除，但不能被100整除，或者能被400整除**

  + 整百年：能被 400 整除，`year % 100 === 0 && year % 400 === 0`
  + 非整百年：能被 4 整除，`year % 100 !== 0 && year % 4 === 0`

  ```js
  function main() {
      run.addEventListener("click", function () {
          let year = parseInt(input.value);    
          let res;
          if (year % 4 === 0 && year % 100 !== 0 || year % 400 === 0)
              res = "yes";
          else
              res = "no";
          output.innerHTML = res;
      })
  }
  ```

+ 输入三个数，输出三个数中的最大值。

  ```js
  function main() {
      run.addEventListener("click", function () {
          let [a, b, c] = input.value.split(" ");
          let max;
          if (a > b && a > c) max = a;
          else if (b > c && b > c) max = b;
          else max = c;
          output.innerHTML = max;
      })
  }
  ```

# 5、循环语句

JavaScript中的循环语句与C++中类似，也包含`for`、`while`、`do while`循环。

## for

```js
for (let i = 0; i < 10; i++) {
    console.log(i);
}
```

枚举对象或数组时可以使用：

+ `for-in`循环，可以枚举数组中的下标，以及对象中的`key`
+ `for-of`循环，可以枚举数组中的值，以及对象中的`value`

## while

```js
let i = 0;
while (i < 10) {
    console.log(i);
    i++;
}
```

## do while

`do while`语句与`while`语句非常相似。唯一的区别是，`do while`语句限制性循环体后检查条件。不管条件的值如何，我们都要至少执行一次循环。

```js
let i = 0;
do {
    console.log(i);
    i++;
} while (i < 10);
```

**练习**

+ 求1~100中所有数的立方和。

  ```js
  let sum = 0;
  for (let i = 1; i <= 100; i++) {
      sum += i ** 3;
  }
  console.log(sum)
  ```

+ 求斐波那契数列的第n项。`f(1) = 1`,` f(2) = 1`, `f(3) = 2`, `f(n) = f(n-1) + f(n-2)`。

  ```js
  function main() {
      run.addEventListener("click", function () {
          let n = parseInt(input.value);
          let a = 1, b = 1, c;
          for (let i = 3; i <= n; i++) {
              c = a + b;
              a = b;
              b = c;
          }
          output.innerHTML = c;
      })
  }
  ```

+ 打印1~100中的所有质数。

  ```js
  for (let i = 1; i <= 100; i++) {
      let f = true;
      for (let j = 2; j * j <= i; j++)
          if (i % j == 0) {
              f = false;
              break;
          }
      if (f) console.log(i);
  }
  ```


---

# 6、对象

英文名称：`Object`。

类似于 Java 中的`map`，由`key:value`对构成。

+ `value`可以是变量、数组、对象、函数等。
+ 函数定义中的`this`用来引用该函数的“拥有者”。

例如：

```js
let person = {
    name: "zsm",
    age: 18,
    money: 0,
    add_money: function (x) {
        this.money += x;
    }
}
```

对象属性与函数的调用方式：

+ `person.name`、`person.add_money()`
+ `person["name"]`、`person["add_money"]()`

这两种访问的效果是一样的，但是第一种是写死的，第二种可以动态变化

```js
let key = "name";
console.log(person[key]);
key = "age";
console.log(person[key]);
```



# 7、数组

数组是一种特殊的对象。

类似于Java中的数组，但是JS的数组中的元素类型可以不同。

+ 数组中的元素可以是变量、数组、对象、函数。

例如：

```js
let a = [1, 2, "a", "zsm"];

let b = [
    1,  // 变量
    "zsm",  // 变量
    ['a', 'b', 3],  // 数组
    function () {  // 函数
        console.log("Hello World");
    },
    { name: "zsm", age: 18 }  // 对象
];
```

## 访问数组中的元素

通过下标访问。

例如：

```js
a[0] = 1; // 访问数组a[]的第0个元素
console.log(a[0]);
```

如果数组元素是一个数组的话，还可以继续使用 `[]` 访问：

```js
console.log(b[2][0])  // a
```

如果数组元素是一个函数的话，输出这个元素的话会直接输出函数的定义

```js
console.log(b[2]);  // 会直接输出函数的定义
```

如果想调用这个函数，就使用 `()`：

```js
b[2]();
```

如果数组元素是一个对象的话，还可以继续通过 `[]` 或 `.` 来访问对象的属性。

```js
console.log(b[3].name, b[3]["age"]);
```

## 数组的下标

js 中的数组没有下标越界，可以随意定义在数组的任意下标。

```js
b[10] = 10;
console.log(b);
```

此时可以看到输出的 b 数组，长度为 11，其中的值只有下标为 0、1、2、3、4、10 的位置有值，

![image-20240202101324633](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021013697.png)

数组的长度就是最大的下标 + 1。

使用负数作下标：

```js
b[-10] = 10;
console.log(b);
```

![image-20240202101516540](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021015594.png)

这是因为 JS 中的数组也是一个对象，所以他的下标可以看作一个字符串 key，当下标为负数的时候，它就被当成了一个 key。

## 数组的常用属性和函数

+ 属性`length`：返回数组长度。注意`length`是属性，不是函数，因此调用的时候不要加`()`
+ 函数`push()`：向数组末尾添加元素
+ 函数`pop()`：删除数组末尾的元素
+ 函数`splice(a, b`)：删除从a开始的b个元素
+ 函数`sort()`：将整个数组从小到大排序
+ 自定义比较函数：`array.sort(cmp)`，函数`cmp`输入两个需要比较的元素，返回一个实数，负数表示第一个参数小于第二个参数，0表示相等，正数表示大于。

# 8、函数

函数是用对象来实现的。

函数也和Java中的函数类似。

## 定义方式

```js
function add(a, b) {
    return a + b;
}

let add = function (a, b) {
    return a + b;
}

let add = (a, b) => {
    return a + b;
}
```

箭头函数 `=>` 的形式是一种简写的形式，省略了 `function` 关键字，如果参数只有一个的话，也可以省略 `()` ：

```js
let add = a => { return a; }
```

当函数的参数列表为空的时候，不能省略掉 `()`：

```js
let add = () => console.log("hello");
```

当函数的函数体中只有一句返回值语句的话，可以省略 `return` 和 函数体的 `{}`：

```js
let add = a => a;
```

箭头函数主要的特点是它没有自己的 `this`。它继承了外围作用域的 `this` 值。

## 参数

调用 JS 的函数时，参数可以随意传多少个都行，不传也行。

+ 不传或少传：没有赋值的参数就是 `undefined`
+ 多传：多的参数没有用，其余参数一一对应赋值

## 返回值

可以返回任意值。如果未定义返回值，则返回`undefined`。

# 9、类

与Java中的`class`类似。但是不存在私有成员。

+ `this`指向类的实例。

## 定义

```js
class Point {
    constructor(x, y) {  // 构造函数
        this.x = x;  // 成员变量
        this.y = y;

        this.init();
    }

    init() {  // 成员函数，不需要写function
        this.sum = this.x + this.y;  // 成员变量可以在任意的成员函数中定义
    }

    toString() {  // 成员函数
        return '(' + this.x + ', ' + this.y + ')';
    }
}

let p = new Point(3, 4);
console.log(p.toString());
```

+ 构造函数（Constructor），使用 `constructor` 关键字定义，没有定义的话默认有个无参构造方法，自定义了就会覆盖无参的

+ 成员方法，是类中定义的函数，不需要使用关键字 `function`。

+ 成员变量，不需要在类体中定义，直接写在构造器中即可，一定要用上 `this.` 才行。

  将上面的构造函数添加几个属性：

  ```js
  constructor(x, y) {  
      this.x = x;  
      this.y = y;
      this.z = [];
      this.i = 0;
  }
  ```

  查看：

  ![image-20240202104842172](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021048211.png)

创建一个对象的写和Java类似：

```js
let p = new Point(3, 4);
```



## 继承

```js
class ColorPoint extends Point {
    constructor(x, y, color) {
        super(x, y); // 这里的super表示父类的构造函数
        this.color = color;
    }

    toString() {
        return this.color + ' ' + super.toString(); // 调用父类的toString()
    }
}
```

**注意：**

+ `super`这个关键字，既可以当作函数使用，也可以当作对象使用。
  + 作为函数调用时，代表父类的构造函数，且只能用在子类的构造函数之中。
  + `super`作为对象时，指向父类的原型对象。
+ 在子类的构造函数中，只有调用`super`之后，才可以使用`this`关键字。
+ 成员重名时，子类的成员会覆盖父类的成员。

## 静态方法

在成员函数前添加`static`关键字即可。静态方法不会被类的实例继承，只能通过类来调用。例如：

```js
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    toString() {
        return '(' + this.x + ', ' + this.y + ')';
    }

    static print_class_name() {
        console.log("Point");
    }
}

let p = new Point(1, 2);
Point.print_class_name();
p.print_class_name();  // 会报错
```

静态成员方法是可以被继承的。

## 静态变量

在ES6中，只能通过`class.propname`定义和访问。例如：

```js
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;

        Point.cnt++;
    }

    toString() {
        return '(' + this.x + ', ' + this.y + ')';
    }
}

Point.cnt = 0;

let p = new Point(1, 2);
let q = new Point(3, 4);

console.log(Point.cnt);
```

静态成员变量是可以被继承的。

# 10、事件

JavaScript的代码一般通过事件触发。

可以通过`addEventListener`函数为元素绑定事件的触发函数。

+ 在定义触发函数时，可接收一个参数 `event`，因为触发事件的时候，会将这个事件当作参数传过来：

  ```js
  let div = document.querySelector('div');
  
  div.addEventListener("click", function (event) {
      console.log(event.type)
  })
  ```

  `event.type` 可以看到当前的事件的类型。

常见的触发函数有：

**鼠标**

+ `click`：鼠标左键点击
+ `dblclick`：鼠标左键双击
+ `contextmenu`：鼠标右键点击
+ `mousedown`：鼠标按下，包括左键、滚轮、右键
  + `event.button`：0表示左键，1表示中键，2表示右键
+ `mouseup`：鼠标弹起，包括左键、滚轮、右键
  + `event.button`：0表示左键，1表示中键，2表示右键

**键盘**

+ `keydown`：某个键是否被按住，事件会连续触发
  + `event.code`：返回按的是哪个键
  + `event.altKey`、`event.ctrlKey`、`event.shiftKey`分别表示是否同时按下了alt、ctrl、shift键。
+ `keyup`：某个按键是否被释放
  + `event`常用属性同上
+ `keypress`：紧跟在`keydown`事件后触发，只有按下字符键时触发，功能键如ESC键不会触发。适用于判定用户输入的字符。
  + `event`常用属性同上
+ `keydown`、`keyup`、`keypress`的关系类似于鼠标的`mousedown`、`mouseup`、`click`

**表单**

+ `focus`：聚焦某个元素
+ `blur`：取消聚焦某个元素
+ `change`：某个元素的内容发生了改变

**窗口**

需要作用到`window`元素上。

+ `resize`：当窗口大小放生变化

  ```js
  window.addEventListener("resize", function (event) {
      console.log(event.type)
  })
  ```

+ `scroll`：滚动指定的元素

+ `load`：当元素被加载完成

---

# 11、常用库

## jQuery

是用来让我们更容易方便的控制页面上的标签元素的。 

### **使用方式**

+ 按[jQuery官网](https://jquery.com/download/)提示下载

+ 在`<head>`元素中添加 `jQuery` 库的引用，可以是本地文件路径，也可以是网络链接：

```html
<script src="/static/jQuery/jquery-3.7.1.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>
```

### **选择器**

用来选择页面中的元素，语法：`$(selector)`，例如：

```js
$('div');  // 返回所有的div
$('#mydiv');
$('.big-div');
$('div > p')
```

`selector`类似于CSS选择器。

一般通过 `$()` 语法获得的对象的命名以 `$` 开头：

```js
let $A = $("#A");
```

方便一下就能看出来是一个 jQuery 对象。

### **事件**

给页面元素绑定事件，语法：`$(selector).on(event, func)`，例如：

```js
$('div').on('click', function (e) {
    console.log("click div");
})
```

还有种方式，比如是点击事件：

```js
$("div").click(function(e){
    console.log("click div");
})
```

`$(selector).off(event, func)` 删除事件，例如：

```js
$('div').on('click', function (e) {
    console.log("click div");

    $('div').off('click');
});
```

当存在多个相同类型的事件触发函数时，可以通过`click.name`来区分，（`.` 后面跟的是名字，这种用法也适用于其他的事件），例如：

```js
$('div').on('click.name1', function (e) {
    console.log("click div1");

    $('div').off('click.name2');
});
$('div').on('click.name2', function (e) {
    console.log("click div2");
});
```

以上代码在点击第一次的时候会输出 `click div1` 和 `click div2` ，后面再点击的时候就只会输出 `click div1` 。

在事件触发的函数中的`return false`等价于同时执行：

+ `e.stopPropagation()`：阻止事件向上传递

  每个子节点的事件，都会向父节点传递，比如，子节点的点击事件触发后，也会向上触发它父节点的点击事件。

  ```html
  <div>
      <a href="https://www.baidu.com" target="_blank">百度</a>
  </div>
  ```

  ```js
  $("div").click(function (e) {
      console.log("div clicked");
  })
  $("a").click(function (e) {
      e.stopPropagation();  // 不写这一句，当超链接被点击时，div的点击事件也会被执行一次
  })
  ```

+ `e.preventDefault()`：阻止事件的默认行为

  但是不会阻止向上传递。如果在超链接的点击事件中使用了这个函数，那么点击超链接就不会跳转页面，但是会执行div的点击事件。

+ 这两个函数太长不好记，所以可以直接使用 `return false` 来代替这两句话同时写上的效果：既不向上传递，也组织了默认行为。

### 元素的隐藏、展现

定义两个按钮用来控制隐藏、显示效果：

```html
<div></div>
<button id="hide-btn">隐藏</button>
<button id="show-btn">显示</button>
```

+ `$A.hide()`：隐藏，可以添加参数，表示消失时间

+ `$A.show()`：展现，可以添出现时间

  ```js
  let div = $("div");
  let hideBtn = $("#hide-btn");
  let showBtn = $("#show-btn");
  
  hideBtn.click(function (e) {
      div.hide(2000);
  })
  showBtn.click(function (e) {
      div.show(1000);
  })
  ```

+ `$A.fadeOut()`：淡出，慢慢消失，可以添加参数，表示消失时间

+ `$A.fadeIn()`：淡入，慢慢出现，可以添加参数，表示出现时间

  ```js
  hideBtn.click(function (e) {
      div.fadeOut(2000);
  })
  showBtn.click(function (e) {
      div.fadeIn(1000);
  })
  ```

### 元素的添加、删除

+ `S()` 不仅可以用来作选择器，还可以用来构造一个元素，这种方式可以嵌套标签

  +  `$('<div class="mydiv"><span>Hello World</span></div>')`：构造一个jQuery对象

+ `$A.append($B)`：将`$B`添加到`$A`的末尾

  在 div 中添加一个 a 标签

  ```js
  let $div = $("div");
  let $a = $('<a href="https://www.baidu.com">百度</a>');
  $div.append($a);
  ```

+ `$A.prepend($B)`：将`$B`添加到`$A`的开头

+ `$A.remove()`：删除元素`$A`

  双击删除 a 标签：

  ```js
  let $a = $('<a href="https://www.baidu.com">百度</a>');
  div.click(function () {
      div.append($a);
  })
  div.dblclick(function () {
      $a.remove();
  })
  ```

  注意：`$a` 被定义在 `div.click()` 外面的话，就只能被添加一次。

+ `$A.empty()`：清空元素`$A`的所有儿子

### 对类的操作

+ `$A.addClass(class_name)`：添加某个类

+ `$A.removeClass(class_name)`：删除某个类

  ```js
  div.click(function () {
      div.addClass("mydiv");  // div会有mydiv类标签的样式
  })
  div.dblclick(function () {
      div.removeClass("mydiv");  // 移除mydiv的样式
  })
  ```

+ `$A.hasClass(class_name)`：判断某个类是否存在

### 对CSS的操作

+ `$("div").css("background-color")`：获取某个CSS的属性
+ `$("div").css("background-color","yellow")`：设置某个CSS的属性

同时设置多个CSS的属性：

```js
$('div').css({
    width: "200px",
    height: "200px",
    "background-color": "orange",  // background-color有短横线，所以要加个引号括起来
});
```

### 对标签属性的操作

+ `$('div').attr('id')`：获取属性
+ `$('div').attr('id', 'ID')`：设置属性

### 对HTML内容、文本的操作

不需要背每个标签该用哪种，用到的时候Google或者百度即可。

+ `$A.html()`：获取、修改HTML内容，没参数就是获取，有参数就是修改，将内容修改成传过去的参数
+ `$A.text()`：获取、修改文本信息，同上
+ `$A.val()`：获取、修改文本的值，同上

有这样一个页面：

```html
<div><span>span-1</span></div>
```

+ 使用 `$div.html()` 的结果：`<span>span-1</span>`

+ 使用 `$div.text()` 的结果：`span-1`

### 查找

现在有三个div：

```html
<div class="div1">
    <div class="div2">
        <div class="div3"></div>
    </div>
</div>
```

+ `$(selector).parent(filter)`：查找父元素

  ```js
  let div3 = $(".div3");
  console.log(div3.parent());
  console.log(div3.parent('.div2'));  // 查找满足要求的父元素
  ```

  上面的两个输出结果是一样的，都是输出它的父元素 div2：

  ![image-20240202141621948](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021416055.png)

  如果是 `console.log(".div1")` 的话，会找不到这个父节点：

  ![image-20240202141712702](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021417783.png)

+ `$(selector).parents(filter)`：查找所有祖先元素

+ `$(selector).children(filter)`：在所有子元素中查找

+ `$(selector).find(filter)`：在所有后代元素中查找

### ajax

用来跟后端通信的。可以在不刷新页面的情况下，从服务器端获取数据，或者说实现局部刷新。

GET 方法：一般用来从服务器获取数据

```js
$.ajax({
    url: url,
    type: "GET",
    data: {
    },
    dataType: "json",
    success: function (resp) {

    },
});
```

POST 方法：

```js
$.ajax({
    url: url,
    type: "POST",
    data: {
    },
    dataType: "json",
    success: function (resp) {

    },
});
```

## setTimeout与setInterval

两个常用的函数。这两个函数都会返回一个 `number` 类型的数值。

### `setTimeout(func, delay)`

`delay`毫秒后，执行函数`func()`。

比如，单击div 2 秒后，输出一句 hello：

```js
$("div").click(function () {
    setTimeout(function () {
        console.log("hello");
    }, 2000);
})
```

### `clearTimeout()`

关闭定时器，例如：

```js
let timeout_id = setTimeout(() => {
    console.log("Hello World!")
}, 2000);  // 2秒后在控制台输出"Hello World"

clearTimeout(timeout_id);  // 清除定时器
```

### `setInterval(func, delay)`

每隔`delay`毫秒，执行一次函数`func()`。
第一次在第`delay`毫秒后执行。

### `clearInterval()`

关闭周期执行的函数，例如：

```js
let interval_id = setInterval(() => {
    console.log("Hello World!")
}, 2000);  // 每隔2秒，输出一次"Hello World"

clearInterval(interval_id);  // 清除周期执行的函数
```

## requestAnimationFrame

### `requestAnimationFrame(func)`

该函数会在下次浏览器刷新页面之前执行一次，通常会用递归写法使其每秒执行60次`func`函数。

例如：每次屏幕刷新让div的宽度增加1

```js
let step = () => {
    $("div").width($("div").width() + 1);
    requestAnimationFrame(step);
}
requestAnimationFrame(step);
```

+ `width()`：获取元素的宽度，有参数的话就是修改

调用时会传入一个参数，表示函数执行的时间戳，单位为毫秒。

```js
let step = (timestamp) => {  // 每帧将div的宽度增加1像素
    let div = document.querySelector('div');
    div.style.width = div.clientWidth + 1 + 'px';
    requestAnimationFrame(step);
};
requestAnimationFrame(step);
```

也可以利用两个时间戳来计算出页面刷新一次的时间间隔：

```js
let lasttime = 0;
let step = (timestamp) => {
    console.log(timestamp - lasttime);
    lasttime = timestamp;
    $("div").width($("div").width() + 1);
    requestAnimationFrame(step);
}
requestAnimationFrame(step);
```

可以发现几乎都是 16.7 ms 左右刷新一次，这就说明浏览器刷新是 1 秒 60 帧，因为 1 / 60 = 0.0166666666666667。

这种效果，在浏览器切换了页面之后就会停下来，知道页面切回来继续。

与`setTimeout`和`setInterval`的区别：

+ `requestAnimationFrame`渲染动画的效果更好，性能更加。该函数可以保证每两次调用之间的时间间隔相同，

+ 但`setTimeout`与`setInterval`不能保证这点。`setTmeout`两次调用之间的间隔包含回调函数的执行时间；

  `setInterval`只能保证按固定时间间隔将回调函数压入栈中，但具体的执行时间间隔仍然受回调函数的执行时间影响。

  ![image-20240202145000755](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021450701.png)

+ 当页面在后台时，因为页面不再渲染，因此`requestAnimationFrame`不再执行。但`setTimeout`与`setInterval`函数会继续执行。

### `cancelAnimationFrame(func_id)`

用于停止 `requestAnimationFrame` 的效果：

```js
let lasttime = 0;
let func_id;  
let step = (timestamp) => {
    console.log(timestamp - lasttime);
    lasttime = timestamp;
    $("div").width($("div").width() + 1);
    func_id = requestAnimationFrame(step); 
}
func_id = requestAnimationFrame(step);

$("div").click(function () {
    cancelAnimationFrame(func_id)
})
```

还可以通过时间控制。比如，十秒后就停止：

```js
let lasttime = 0;
let step = (timestamp) => {
    console.log(timestamp - lasttime);
    lasttime = timestamp;
    $("div").width($("div").width() + 1);
    if (timestamp / 1000 <= 10)
        requestAnimationFrame(step);
}
requestAnimationFrame(step);
```

但是一般不用这个停止函数，因为 `requestAnimationFrame` 一般用于游戏中，需要一直刷新。

## Map与Set

### `Map`

Map 对象保存键值对。

+ 用`for...of`或者`forEach`可以按插入顺序遍历。

  ```js
  let map = new Map();
  
  for (let [key, value] of map) 
      console.log(key, value);
  
  map.forEach(function(value, key) {
  	console.log(key,vlaue);
  })
  ```

+ 键值可以为任意值，包括函数、对象或任意基本类型。

常用API：

+ `set(key, value)`：插入键值对，如果`key`已存在，则会覆盖原有的`value`
+ `get(key)`：查找关键字，如果不存在，返回`undefined`
+ `size`：返回键值对数量
+ `has(key)`：返回是否包含关键字`key`
+ `delete(key)`：删除关键字`key`
+ `clear()`：删除所有元素

### `Set`

Set 对象允许你存储任何类型的唯一值，无论是原始值或者是对象引用。

用`for...of`或者`forEach`可以按插入顺序遍历。
常用API：

+ `add()`：添加元素
+ `has()`：返回是否包含某个元素
+ `size`：返回元素数量
+ `delete()`：删除某个元素
+ `clear()`：删除所有元素

## localStorage

可以在用户的浏览器上存储键值对。

在浏览器的调试工具中，Application 中，可以看到 localStorage 中存在的值：

![image-20240202150923968](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402021509073.png)

常用API：

+ `setItem(key, value)`：插入
+ `getItem(key)`：查找
+ `removeItem(key)`：删除
+ `clear()`：清空

## JSON

JSON对象用于序列化对象、数组、数值、字符串、布尔值和null。

常用API：

+ `JSON.parse()`：将字符串解析成对象
+ `JSON.stringify()`：将对象转化为字符串

```js
let obj = {
    name: "zsm",
    age: 18,
}
let str = JSON.stringify(obj);
console.log(str);

let obj2 = JSON.parse(str);
console.log(obj2);
```

## 日期

返回值为整数的API，数值为1970-1-1 00:00:00 UTC（世界标准时间）到某个时刻所经过的毫秒数：

+ `Date.now()`：返回现在时刻。
+ `Date.parse("2022-04-15T15:30:00.000+08:00")`：返回北京时间2022年4月15日 15:30:00的时刻。

与Date对象的实例相关的API：

+ `new Date()`：返回现在时刻。
+ `new Date("2022-04-15T15:30:00.000+08:00")`：返回北京时间2022年4月15日 15:30:00的时刻。
+ 两个Date对象实例的差值为毫秒数
+ `getDay()`：返回星期，0表示星期日，1-6表示星期一至星期六
+ `getDate()`：返回日，数值为1-31
+ `getMonth()`：返回月，数值为0-11
+ `getFullYear()`：返回年份
+ `getHours()`：返回小时
+ `getMinutes()`：返回分钟
+ `getSeconds()`：返回秒
+ `getMilliseconds()`：返回毫秒

## WebSocket

与服务器建立全双工连接。

+ 全双工：两边都可以发送信息

HTTP 请求（ajax也是HTTP请求）是用户端向服务器端发送请求，然后服务器端向用户端响应这个请求，服务器端是无法主动联系用户端的，而有些时候需要服务器端主动向用户端发送请求，因此 HTTP 不能实现（但是也可以通过一直向服务器端发送请求来实现），就有了 WebSocket 。

常用API：

+ `new WebSocket('ws://localhost:8080');`：建立ws连接。
+ `send()`：向服务器端发送一个字符串。一般用JSON将传入的对象序列化为字符串。
+ `onopen`：类似于`onclick`，当连接建立时触发。
+ `onmessage`：当从服务器端接收到消息时触发。
+ `close()`：关闭连接。
+ `onclose`：当连接关闭后触发。

## Window

+ `window.open("https://www.baidu.com")`在新标签栏中打开页面。
+ `window.location.reload()`刷新页面。
+ `window.location.href = "https://www.baidu.com"`：在当前标签栏中打开页面。

`window` 可以省略不写。

## Canvas

[教程](https://developer.mozilla.org/zh-CN/docs/Web/API/Canvas_API/Tutorial)