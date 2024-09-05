# Vue2

## 1、使用

### 1.1、原始使用

1. 引入vue.js文件

2. 创建vue实例
   + **必须使用 new Vue()** 
3. 挂载vue实例
   + 使用$mount()方法
   + 使用el配置项

使用$mount()方法挂载：

```js
var myVue = new Vue({
    template: '<h1>hello world</h1>'
});
myVue.$mount('#app');
```

使用el配置项挂载：

```js
var myVue = new Vue({
    template: '<h1>hello world</h1>'，
    el: '#app'
});
```

### 1.2、组件化使用

单文件组件的使用方式

+ 创建组件：创建一个 vue 文件，并使用 export 导出

  ```vue
  <template>
  	<div>
      	<h3>Y1组件</h3>
      </div>
  </template>
  
  <script>
      // 默认导出
      export default {
          
      }
  </script>
  
  <style></style>
  ```

+ 注册组件：引入 vue 文件，并在 export 中使用 components 注册组件

  ```vue
  <script>
      import Y1 from './Y1.vue'
      export default {
          // 注册组件
          components : {Y1}
      }
  </script>
  ```

+ 使用组件：直接在 template 中的使用

  ```vue
  <template>
      <div>
          <h2>Y组件</h2>
          <!-- 使用组件 -->
          <Y1></Y1>
      </div>
  </template>
  ```

### 1.3、vue2工程

使用vue-cli脚手架创建：

```cmd
vue create project_name
```

运行项目：

```cmd
npm run serve
```

vue2工程中的项目结构，主要关注 src 目录，以后写代码就是在该目录下：

+ node_modules：脚手架的依赖包，不要动
+ public：不会被打包，也就是说现在是什么样，将来发布后放在 dist 文件夹中还是什么样

+ src 下的 assets 也是存放静态资源，和 public 目录不一样的地方是，assets 下的资源会被打包
+ main.js 的名字可以修改，但是修改后要在 vue.config.js 文件中配置，一般不要修改

+ package.json：包的说明书（包的名字，包的版本，依赖哪些库）。该文件里有 webpack 的短命令：

  + serve（启动内置服务器）

  + build 命令是最后一次的编译，生成 html css js，给后端人员

  + lint 做语法检查的。

在主页index.html里，没有手动引入vue和main.js，Vue脚手架会自动引入，所以不要动main.js文件的名字和位置：

```html
<!DOCTYPE html>
<html lang="">
  <head>
    <meta charset="utf-8">
    <!-- 让IE浏览器启用最高渲染标准。IE8是不支持Vue的。 -->
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <!-- 开启移动端虚拟窗口（理想视口） -->
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <!-- 设置页签图标，从根路径开始获取，就是从public开始 -->
    <link rel="icon" href="<%= BASE_URL %>favicon.ico">
    <!-- 设置标题，通过插件从package.json中获取项目的name-->
    <title><%= htmlWebpackPlugin.options.title %></title>
  </head>
  <body>
    <!-- 当浏览器不支持JS语言的时候，显示如下的提示信息。 -->
    <noscript>
      <strong>We're sorry but <%= htmlWebpackPlugin.options.title %> doesn't work properly without JavaScript enabled. Please enable it to continue.</strong>
    </noscript>
    <!-- 容器 -->
    <div id="app"></div>
    <!-- built files will be auto injected -->
  </body>
</html>
```

在main.js文件中，渲染了根组件，render对象的值就是一个渲染组件的函数：

```js
// 这句代码等同于引入vue.js文件
import Vue from 'vue'
// 导入App组件（根组件）
import App from './App.vue'

// 关闭生产提示信息
Vue.config.productionTip = false

// 创建Vue实例
new Vue({
  render: h => h(App),
}).$mount('#app')  // 挂载实例
```

脚手架的配置文件vue.config.js，在 [VueCLI的配置参考](https://cli.vuejs.org/zh/config/) 中可以看到可以配置的东西有哪些：

```js
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
})
```

如果想修改程序的入口文件，可以使用pages配置，想关闭语法检查可以使用lintOnSave配置：

```js
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  // 保存时是否进行语法检查。true表示检查，false表示不检查。默认值是true。
  lintOnSave : false,
  // 配置入口
  pages: {
    index: {
      entry: 'src/main.js',
    }
  },
})
```



## 2、基础语法

### 2.0、模板

创建Vue实例时，使用的template配置项就是一个模板语句。

+ template中只能有一个根节点
+ template中的数据来自data配置项
+ template中的数据源（data）发生改变的话，模板语句一定会被重新编译
+ template会替换掉挂载位置的元素
+ template可以直接写在html中，不使用template配置项

直接写在html中的模板语句：

```html
<div id="app">
    <div>
        <h1>{{msg}}</h1>
        <h1>{{name}}</h1>
    </div>
</div>
```

### 2.1、data

在创建Vue实例时，一般会有一个data配置项，这是Vue实例模板的数据来源。

```js
new Vue({
    el: "#app",
    data: {
        msg: "Hello World",
        name: "lisi"
    }
})
```

在创建 Vue 实例时，一般给 data 配置项设置的是一个对象，如上代码。但是也可以是函数，此时这个函数必须返回一个对象：

```js
const vm = new Vue({
    el: '#app',
    // data : function(){
    //     return {
    //         msg : 'Hello Vue!',
    // 		   name: "lisi"
    //     }
    // }

    // 在对象当中，函数的 :function 可以省略
    data() {
        return {
            msg: 'Hello Zhangsan!',
            name: "lisi"
        }
    }
})
```

### 2.2、插值语法

使用 `{{ }}` 就是插值语法，在 `{{ }}` 中可以写四种东西。

+ 在data中声明的变量、函数等

+ 常量（由const定义的常量不算）

+ 合法的javascript表达式（在 `{{ }}` 中写 js 语句是不会生效的）

+ 白名单变量

  ```html
  'Infinity,undefined,NaN,isFinite,isNaN,'
  'parseFloat,parseInt,decodeURI,decodeURIComponent,encodeURI,encodeURIComponent,'
  'Math,Number,Date,Array,Object,Boolean,String,RegExp,Map,Set,JSON,Intl,'
  'require'
  ```

在使用插值语法时，Vue.js 会自动将组件实例的数据绑定到模板上下文中，所以随便写不写this都行，一般不写：

```vue
<h1>{{ msg }}</h1>
<h1>{{ this.msg }}</h1>
```

+ 这个 this 还是表示的该模板绑定的实例

示例代码：

```html
<div id="app">
    <!-- 插值语法：使用在data中声明的 -->
    <h1>{{msg}}</h1>
    <h1>{{sayHello()}}</h1>

    <!-- 插值语法：使用常量 -->
    <h1>{{100}}</h1>
    <h1>{{'hello vue!'}}</h1>
    <h1>{{3.14}}</h1>

    <!-- 插值语法：使用合法javascript表达式 -->
    <h1>{{1 + 1}}</h1>
    <h1>{{'hello' + 'vue'}}</h1>
    <h1>{{msg + 1}}</h1>
    <h1>{{'msg' + 1}}</h1>
    <h1>{{gender ? '男' : '女'}}</h1>

    <!-- 插值语法：使用白名单中的内容 -->
    <h1>{{Date}}</h1>
    <h1>{{Date.now()}}</h1>
    <h1>{{Math}}</h1>
    <h1>{{Math.ceil(3.14)}}</h1>
</div>

<script>
    new Vue({
        el : '#app',
        data : {
            number : 1,
            gender : true,
            msg : 'abcdef',  // 把msg叫做变量。（这行代码就可以看做是变量的声明。）
            sayHello : function(){
                console.log('hello vue!');
            }
        }
    })
</script>
```

### 2.3、指令语法

指令的职责是：当表达式的值改变时，将其产生的连带影响，响应式地作用于 DOM。

指令是写在标签上的，以属性的形式存在，Vue 框架中的所有指令的名字都以 “v-” 开始：

```html
<HTML标签 v-指令名:参数="javascript表达式"></HTML标签>
```

+ `v-指令名:参数="javascript表达式"` 这一串就是一个完整的指令写法
+ 参数是属于指令的参数，参数不是必须的，有的指令不需要参数
+ 表达式：这里与插值语法能写的规则一样的，但是需要注意的是：**在指令中的表达式位置不能外层再添加一个 `{{ }}`**

虽然指令是写在标签的属性位置上，但是这个指令浏览器是无法直接看懂的。是需要先让 Vue 框架进行编译的，编译之后的内容浏览器是可以看懂的。

#### 2.3.1、v-once

作用：只渲染元素一次。随后的重新渲染，元素及其所有的子节点将被视为静态内容并跳过。这可以用于优化更新性能。

```html
<h1>{{msg}}</h1>
<h1 v-once>{{msg}}</h1>
```

当 data 中的 msg 发生了改变后，以上两个 `h1` 标签只会更新第一个，因为第二个使用了 `v-once` 指令，只会熏染一次，相当于变成了一个静态的元素，只有重新刷新页面才会重新渲染。

#### 2.3.2、v-if

表达式的执行结果需要是一个布尔类型的数据：true 或者 false

+ true：这个指令所在的标签，会被渲染到浏览器当中。
+ false：这个指令所在的标签，不会被渲染到浏览器当中。

```html
<div id="app">
    <h1 v-if="a > b">v-if测试：{{msg}}</h1>
</div>
<script>
    new Vue({
        el : '#app',
        data : {
            msg : 'Hello Vue!qqqq',
            a : 10,
            b : 11
        }
    })
</script>
```

注意：v-if=false 时，并不是将元素隐藏了，而是根本没有渲染，在开发者工具中找不到该元素。

#### 2.3.3、v-bind

负责动态绑定的指令，它可以让HTML标签的某个属性的值产生动态的效果。它的原理是：

编译前：

```html
<HTML标签 v-bind:参数="表达式"></HTML标签>
```

编译后：

```html
<HTML标签 参数="表达式的执行结果"></HTML标签>
```

表达式会关联 data，当 data 发生改变之后，表达式的执行结果就会发生变化。所以，连带的就会产生动态效果。

v-bind有一个简写方式：`:参数="表达式"`

```html
<img v-bind:src="path" >
<img :src="path">
```

注意：v-bind指令是单向绑定的，数据可以影响视图，但是视图无法影响到数据。

#### 2.3.4、v-model

v-model基本用法和v-bind一样，也是用来完成数据的绑定的。是双向数据绑定，数据可以影响到视图，视图也可以影响数据。

+ 单向数据绑定：修改了 data 后，视图中的显示会变化。
+ 双向数据绑定：修改了 data 后，视图中的显示会变化；修改了视图中的数据后，datat 中的数据也会变化。

`v-bind` 可以使用在任何 HTML 标签当中。`v-model` 只能使用在表单类元素上。例如：input 标签、select 标签、textarea 标签。

+ 因为表单类的元素才能给用户提供交互输入的界面。元素的值才会发生改变，才有双向绑定的意义。

+ 如果使用在非表单元素上会报错：

  ```html
   <a v-model:href="url">百度</a>
  ```


`v-model:value="表达式"`  的简写方式：`v-model="表达式"`

```html
消息1：<input type="text" v-model:value="msg"><br>
消息2：<input type="text" v-model="msg"><br>
```

#### 2.3.5、v-text

可以将指令的内容拿出来填充到标签体当中，和 JS 的 innerText 一样，这种填充是以覆盖的形式进行的，先清空标签体当中原有的内容，填充新的内容，如果内容是一段HTML代码，也会当成普通字符串，不会被解析：

```vue
<h1 v-text="msg">test</h1>
```

#### 2.3.6、v-html

和 v-text 一样，也是填充标签体内容，也是采用覆盖的形式进行，只不过 v-html 会将内容当做一段 HTML 代码解析并执行，和 js 中的 innerHtml 效果一样：

```vue
<h1 v-html="<h1>欢迎大家学习Vue！</h1>"></h1>
```

#### 2.3.7、v-cloak

v-cloak 是一个用于解决闪现问题的特殊指令，使用 v-cloak 可以确保 Vue.js 将模板渲染完成后再显示元素：

```vue
<!--这一段div是模板语句-->
<div id="app">
    <h1 v-cloak>{{msg}}</h1>
</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Vue的其它指令'
        }
    })
</script>
```

模板语句是在页面加载 Vue.js 后，执行了创建 Vue 实例代码后，才开始编译的，如果在这个期间， Vue.js 加载的很慢，那么这个模板语句就会一直显示 `{{msg}}` 在页面上，直到加载完成。当 Vue 编译完后，会将 v-cloak 属性删掉。

v-cloak 通常与 CSS 配合使用，可以防止未解析的 {{}} 表达式在页面加载时闪现：

```vue
<style>
    [v-cloak] {
        display: none;
    }
</style>

<div id="app">
    <h1 v-cloak>{{msg}}</h1>
</div>
```

#### 2.3.8、v-pre

v-pre 可以提高编译速度，带有该指令的标签不会被编译，可以在没有 Vue 语法规则的标签中使用：

```vue
<h1 v-pre>欢迎学习Vue框架！</h1>
<h1 v-pre>{{msg}}</h1>
```

+ 这个胡子语法不会被编译

## 3、MVVM思想

+ M：Model（模型/数据）
+ V：View（视图）
+ VM：ViewModel（视图模型）：VM 是 MVVM 中的核心部分。（它起到一个核心的非常重要的作用。）

MVVM 是目前前端开发领域当中非常流行的开发思想。(一种架构模式。)。目前前端的大部分主流框架都实现了这个 MVVM 思想，例如 Vue，React 等。

在Vue中，M 就是数据（data），V 就是模板（template），VM 就是Vue实例：

```html
<!-- View V-->
<div id="app">
    姓名：<input type="text" v-model="name">
</div>

<script>
    // ViewModel  VM
    new Vue({
        el : '#app',
        // Model  M
        data : {
            name : 'zhangsan'
        }
    })
</script>
```

因此，一般会用 vm 表示 Vue 实例：

```js
// ViewModel  VM
const vm = new Vue({
    el : '#app',
    // Model  M
    data : {
        name : 'zhangsan'
    }
})
```

## 4、认识vm

在 Vue 中，MVVM 分层中的 vm 就是 Vue 实例。通过 Vue 实例都可以访问哪些属性？

Vue 实例中的属性很多，有的以 `$` 开始，有的以 `_` 开始。

+ 所有以 `$` 开始的属性，可以看做是公开的属性，这些属性是供程序员使用的。
+ 所有以 `_` 开始的属性，可以看做是私有的属性，这些属性是 Vue 框架底层使用的。一般我们程序员很少使用。

在 data 中定义的 msg 属性，也可以直接使用 vm 访问：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg: "hello"
    }
});
console.log(vm.msg);
```

## 5、事件绑定

### 5.1、v-on:事件名="表达式"

使用 Vue 来完成事件绑定，需要借助一个指令：`v-on:事件名="表达式"`，例如：

+ `v-on:click="表达式"` 表示当发生鼠标单击事件之后，执行表达式。
+ `v-on:keydown="表达式"` 表示当发生键盘按下事件之后，执行表达式。

这个表达式应该写事件绑定的函数，而不能写例如 `alert(1)` 这样的js代码，应该写函数调用的表达式：

```vue
<button v-on:click="sayHello()">hello</button>
```

绑定的回调函数，如果函数调用时不需要传递任何参数，小括号()可以省略：

```vue
<button v-on:click="sayHello">hello</button>
```

`v-on:` 可以简写为 `@`：

+ `v-on:click` 简写为 `@click`
+ `v-on:keydown` 简写为 `@keydown`
+ `v-on:mouseover` 简写为 `@mouseover`

### 5.2、methods

在Vue当中，所有事件所关联的回调函数，需要在Vue实例的配置项methods中进行定义：

```js
const vm = new Vue({
    methods: {
        // 回调函数
        // sayHello : function(){
        //     alert('hello')
        // }
        // : function 可以省略
        sayHello() {
            alert('hello2')
        },
    }
})
```

+ methods 是一个对象：{}，在这个 methods 对象中可以定义多个回调函数
+ methods对象中的方法可以通过vm去访问
+ methods对象中的方法没有做数据代理

在methods中定义的回调函数，如果要操作data中的数据，不能直接使用，必须通过 `this.` 或 `vm.` 来操作：

```js
const vm = new Vue({
    methods: {
        data: {
            counter: 1
        },
        add() {
            this.counter++;
            vm.counter++;
        }
    }
})
```

但如果是箭头函数的话，就不能使用this关键字，不能这样写：

```js
add : () => {
	this.counter++;
},
```

这是因为：箭头函数中没有 this，箭头函数中的 this 是从父级作用域中继承过来的。那么对于当前程序来说，父级作用域就是全局作用域 window。

### 5.3、事件对象占位符

当事件绑定的回调函数的写法是省略了小括号的形式：

```vue
<button v-on:click="sayHello">hello</button>
```

Vue在调用这个回调函数的时候，会自动给回调函数传递一个对象，这个对象是：当前发生的事件对象。那么就可以在这个回调函数中使用这个对象：

```js
const vm = new Vue({
    methods: {
        sayHello(event) {
            console.log(e);
            console.log(event.target)  // 事件发生的地方
            console.log(event.target.innerText)  // 事件发生的控件上的文本
        },
    }
})
```

注意：只有省略了小括号后，调回调函数的时候，才会传把当前的事件以对象的形式传过去 。

当事件绑定的回调函数有参数时，或者说没有省略小括号时，可以使用 \$event 占位符，将当前事件以对象的形式传过去。

```vue
<button v-on:click="sayHello($event)">hello</button
```

有多个参数时，也可以使用占位符：

```vue
<button v-on:click="sayHello($event, 'zhangsan')">hello</button
```

占位符的位置可以在参数列表中随意。

### 5.4、事件修饰符

Vue 当中提供的事件修饰符：

+ `.stop` ： 停止事件冒泡，等同于 `event.stopPropagation()`
+ `.prevent ` ： 等同于 `event.preventDefault()`  阻止事件的默认行为。
+ `.capture` ：添加事件监听器时使用事件捕获模式。
+ `.self` ：这个事件如果是“我自己元素”上发生的事件，这个事件不是别人给我传递过来的事件，则执行对应的程序。
+ `.once` ： 事件只发生一次
+ `.passive` ：`passive` 翻译为顺从/不抵抗。无需等待，直接继续（立即）执行事件的默认行为。
  + `.passive` 和 `.prevent` 修饰符是对立的。不可以共存。（如果一起用，就会报错。）
  + `.prevent`：阻止事件的默认行为。
  + `.passive`：解除阻止。

#### 5.4.1、prevent

`.prevent` 阻止超链接的默认跳转行为，只会执行点击事件 yi()：

```vue
<a href="https://www.baidu.com" @click.prevent="yi">百度</a>
```

#### 5.4.2、stop

`.stop` 阻止事件冒泡，这样就只会执行到 yi() 函数，不会执行 er() 函数：

```vue
<div @click="san">
    <div @click="er">
        <button @click.stop="yi">冒泡事件</button>
    </div>
</div>
```

#### 5.4.3、capture

`.capture` 添加事件监听器时使用事件捕获模式，先执行的是 san() 函数，再执行 er() 函数，最后执行 yi() 函数：

```vue
<div @click.capture="san">
    <div @click.capture="er">
        <button @click.capture="yi">添加事件监听器的时候采用事件捕获模式</button>
    </div>
</div>
```

+ 没有添加.capture修饰符的话，就默认是冒泡的方式：

  ```vue
  <div @click.capture="san">
      <!-- 这里没有添加.capture修饰符，以下这个元素，以及这个元素的子元素，都会默认采用冒泡模式。 -->
      <div @click="er">
          <button @click="yi">添加事件监听器的时候采用事件捕获模式</button>
      </div>
  </div>
  ```

#### 5.4.4、self

`.self` 限制只执行发生在自己身上的事件，这个事件如果是“我自己元素”上发生的事件，这个事件不是别人给我传递过来的事件，则执行对应的程序。

```vue
<div @click="san">
    <div @click.self="er">
        <button @click="yi">self修饰符</button>
    </div>
</div>
```

+ 点击按钮后，按钮的 yi() 会执行，然后冒泡到第二层的 div 上，但是该事件不是第二层 div 的本身的事件，所以不会执行 er() 函数，但是事件会继续向上冒，san() 函数会被执行。

#### 5.4.5、once

`.once` 只执行一次事件，不管触发几次：

```vue
<button @click.once="yi">事件只发生一次</button>
```

#### 5.4.6、passive

`.passive` 直接执行事件的默认行为。默认情况下会先执行事件的回调函数，然后执行默认行为，当回调函数中有一个很耗时的操作时，默认行为就会一直等，使用`.passive`修饰符就可以立即执行默认事件：

```vue
<div id="app">
    <div class="divList" @wheel.passive="testPassive">
        <div class="item">div1</div>
        <div class="item">div2</div>
        <div class="item">div3</div>
    </div>
</div>

<script>
    const vm = new Vue({
        el: "#app",
        methods: {
            testPassive(event) {
                for (let i = 0; i < 100000; i++) {
                    console.log("test passive");
                }
            },
        },
    });
</script>
```

+ @wheel是滚动条滚动事件，没有使用`.passive`的话就会等输出完后滚动
+ `.passive` 不能和 `.prevent` 和 `event.prevent()` 一起使用，会报错

#### 5.4.7、混合使用

在 Vue 当中，事件修饰符是可以多个联合使用的。

```html
<div @click="san">
    <div @click="er">
        <button @click.self.stop="yi">self修饰符</button>
    </div>
</div>
```

写在前面的修饰符先执行：

+ `@click.self.stop`：先 .self，再 .stop
+ `@click.stop.self`：先 .stop，再 .self

### 5.5、按键修饰符

9 个比较常用的按键修饰符，这些按键修饰符的使用方法都差不多：

+ `.enter`
+ `.tab `（必须配合keydown事件使用。）
  + tab 键无法触发 keyup 事件，keyup 会切换光标。
  + 只能触发 keydown 事件。因为按住不松手的话就会一直触发 keydown 事件
+ `.delete` (捕获“删除”和“退格”键)
+ `.esc`
+ `.space`
+ `.up`
+ `.down`
+ `.left`
+ `.right`

例如，`.enter` 监听回车键，以下代码只要触发了回车键的keyup事件，就会执行getInfo回调函数：

```vue
<input type="text" @keyup.enter="getInfo"><br>

<script>
    const vm = new Vue({
        el: '#app',
        methods: {
            getInfo(event) {
                console.log(event.target.value)
            }
        }
    })
</script>
```

+ 事件对象中有按下的键的值 keyCode
+ 事件对象中的 target 就是事件发生在哪的元素
+ `.enter` 可以替换为回车键对应的键值 `.13`

#### 5.5.1、每个键的修饰符

可以通过事件对象获取键的真实名字：`event.key`，将这个真实名字以 kebab-case 风格进行命名，就是按键修饰符。

比如 PageDown 是真实名字。经过命名之后：page-down 就是按键的修饰符。

```html
<input type="text" @keyup.page-down="getInfo"><br>
```

#### 5.5.2、自定义按键修饰符

通过 Vue 的全局配置对象 config 来进行按键修饰符的自定义。

语法规则：

```js
Vue.config.keyCodes.按键修饰符的名字 = 键值
```

比如自定义一个回车的按键修饰符：

```js
Vue.config.keyCodes.huiche = 13
```

+ 自定义按键名必须是小写

#### 5.5.3、系统修饰键

4 个比较特殊的键

+ ctrl
+ alt
+ shift
+ meta（win键）

对于 keydown 事件来说：只要按下系统修饰键，keydown 事件就会触发。

对于 keyup 事件来说：需要按下系统修饰键，并且加上按下组合键，然后松开组合键之后，keyup 事件才能触发。

#### 5.5.4、限制组合键

```html
<input type="text" @keyup.ctrl.i="getInfo"><br>
```

这种方式限制了只能按下 ctrl+i 才会触发事件

## 6、计算属性

使用 Vue 的原有属性，经过一系列的运算/计算，最终得到了一个全新的属性，叫做计算属性。

+ Vue 的原有属性: data 对象当中的属性可以叫做 Vue 的原有属性。
+ 全新的属性: 表示生成了一个新的属性，和 data 中的属性无关了，新的属性也有自己的属性名和属性值。

### 6.1、定义

计算属性是写在Vue实例中的computed配置项中的：

```js
const vm = new Vue({
    computed : {
        // 这是一个计算属性
        计算属性1 : {
            // setter 和 getter方法。
            // 当读取计算属性1的值的时候，getter方法被自动调用。
            get(){	return 值; },
            // 当修改计算属性1的值的时候，setter方法被自动调用。
            set(val){}
        },
        // 这是另一个计算属性
        计算属性2 : {},
    }
})
```

+ get() 返回的就是该计算属性的值
+ set() 设置的就是该计算属性的值
+ get() 的调用时机包括两个
  + 第一个时机：第一次访问这个属性的时候。
  + 第二个时机：该计算属性所关联的 Vue 原有属性的值发生变化时，getter 方法会被重新调用一次。

### 6.2、读取

在页面中使用计算属性和使用 data 中的属性是一样的，可以使用插值语法 `{{计算属性名}}`。同时，如果多个地方都使用了计算属性的话，计算属性的 getter 方法只会被执行一次（缓存），而不是像使用 methods 那样，使用一次就调用一次。

```vue
 <div id="app">
     <!-- 有缓存机制，computed 中的方法就调用了一次 -->
     {{hehe}} <br>
     {{hehe}} <br>
     <!-- 没有缓存机制，method 中的方法调用了多次 -->
     {{hello()}} <br>
     {{hello()}} <br>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        methods : {
            hello(){
                console.log('hello方法执行了')
                return 'hello'
            }
        },
        computed : {
            hehe : {
                get(){
                    console.log('getter方法调用了')
                    return 'haha'
                },
                set(val){
                    console.log('setter方法调用了')
                }
            },
        }
    })
</script>
```

也可以使用 `vm.` 和 `this.` 来访问计算属性，但是使用 `this.` 时，不能是箭头函数，因为箭头函数中的 this 不是 Vue 实例 vm，是 window。

### 6.3、修改

当修改计算属性的时候，set 方法被自动调用。修改计算属性时不能直接修改计算属性，应该修改该计算属性基于的原始属性（data中的数据）：

```js
const vm = new Vue({
    el : '#app',
    data: {
        info: ""
    },
    computed : {
        reversedInfo : { 
            get(){
                return this.info
            },
            set(val){
                console.log('setter方法被调用了。')
                this.info = val
            }
        } 
    }
})
```

原理：计算属性的值变还是不变，取决于计算属性关联的 Vue 原始属性的值。

### 6.4、简写

计算属性一般只用来做展示，所以他的 set 方法很少用。在**不用 set 方法的情况下**，有一个简写方式：

```js
reversedInfo(){ 
    return this.info
}
```

注意：这不是一个方法，这是一个计算属性，所以使用计算属性的是还是这样使用：

```html
{{reversedInfo}}
```

而不是这样：

```html
{{reversedInfo()}}
```

## 7、侦听/监视属性的变化

侦听属性的变化其实就是监视某个属性的变化。当被监视的属性一旦发生改变时，执行某段代码。

监视属性变化时需要使用 watch 配置项。

在 watch 配置项里面写要监听的属性，可以监视 Vue 的原有属性，也可以监视计算属性。

### 7.1、监听原有属性

在监听的属性中，必须有个固定的方法 handler，且名字必须叫 handler。

+ 当被监视的属性发生变化的时候，handler 就会自动调用一次。
+ handler 方法上有两个参数：第一个参数 newValue，第二个参数是 oldValue（名字可以随便取）
  + newValue 是属性值改变之后的新值。
  + oldValue 是属性值改变之前的旧值。
+ hanlder中也可以使用this，表示当前vue实例，但是不能在箭头函数中使用

```js
const vm = new Vue({
    el : '#app',
    data : {
        number : 0,
    },
    watch : {
        // 要监听的属性
        number : {
            handler(newValue, oldValue){
                console.log(newValue, oldValue)
            }
        },
    }
})
```

### 7.2、监听计算属性

和监听原有属性一样，只要这个计算属性变化了（尽管这个计算属性没有在页面中使用），那么就会执行回调函数：

```js
const vm = new Vue({
    el : '#app',
    data : {
        number : 0,
    },
    computed : {
        hehe(){
            return 'haha' + this.number
        }
    },
    watch : {
        // 要监听的属性
        hehe : {
            handler(a , b){
                console.log(a, b)
            }
        } 
    }
})
```

### 7.3、immediate属性

如果想在页面打开之后就调用一次 handler 的话，有个immediate属性：

```js
watch : {
    // 要监听的属性
    number : {
        immediate : true,
        handler(newValue, oldValue){
            console.log(newValue, oldValue)
        }
    },
}
```

immediate 为 true 表示初始化的时候，调用一次 handler 方法。

### 7.4、深度监视

#### 7.4.1、a.b

假设要监视的是一个对象的属性时，可以使用 `a.b` 的方式监视：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : '侦听属性的变化',
        number : 0,
        a : {
            b : 0
        }
    },
    watch : {
        'a.b' : {  
            handler(newValue, oldValue){
                console.log('@')
            } 
        }
    }
})
```

+ 不能直接监视 b 属性，因为 data 中没有 b 属性
+ 不能只监视 a 属性，因为监视 a 只有 a 发生了改变才会被监视到，a 中保存的是一个对象的内存地址，只有新建一个对象赋给 a 后，a 的值才算改变
+ 使用 a.b 时需要添加引号括起来，因为对象的 key 其实本来就是有引号的，只不过一般可以省略，但是当 key 中包含特殊字符时，就不能省略了

#### 7.4.2、deep

当你需要监视一个具有多级结构的属性，并且监视所有的属性，需要启用深度监视。使用 deep 属性开启深度监视：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : '侦听属性的变化',
        number : 0,
        a : {
            b : 0,
            c : 0,
            d : {
                e : {
                    f : 0
                }
            }
        }
    },
    watch: {
        a : {
            // 启用深度监视，默认是不开启深度监视的。
            deep : true,  
            handler(newValue, oldValue){
                console.log('@')
            } 
        },
    }
})
```

### 7.5、后期添加监视

Vue 实例创建完后，想要对 Vue 实例中的属性进行监视。语法：`vm.$watch('被监视的属性名', {})`

```js
vm.$watch('number', {
    immediate : true,
    deep : true,
    handler(newValue, oldValue){
        console.log(newValue, oldValue)
    }
})
```

### 7.6、监视的简写

当只有 handler 回调函数的时候，可以使用简写形式：

```js
watch: {
    number(newValue, oldValue){
        console.log(newValue, oldValue)
    },
}
```

后期添加监视也可以简写：

```js
vm.$watch('number', function(newValue, oldValue){
    console.log(newValue, oldValue)
})
```

### 7.7、computed和watch的选择

在大部分情况下，计算属性和监视是可以互换的。

computed 和 watch 如果都能够完成某个功能，优先选择 computed。

如果在程序当中采用了异步的方式，只能使用 watch。

## 8、动态绑定样式

使用 `v-bind` 指令绑定元素的 class 和 style 属性，只需要通过表达式计算出字符串结果即可：

```vue
<div v-bind:class="" v-bind:style=""></div>
<div :class="" :style=""></div>
```

在将 `v-bind` 用于 `class` 和 `style` 时，Vue.js 做了专门的增强。表达式结果的类型除了字符串之外，还可以是对象或数组。

#### 8.1、class绑定

字符串：

```vue
<div class="static" :class="c1">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Class绑定之字符串形式',
            c1 : 'small'
        },
    })
</script>
```

数组：

```vue
<!--直接使用数组-->
<div class="static" :class="['active','text-danger']">{{msg}}</div>
<!--数组中使用变量-->
<div class="static" :class="[c1, c2]">{{msg}}</div>
<!--使用数组变量-->
<div class="static" :class="classArray">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Class绑定之数组形式',
            c1 : 'active',
            c2 : 'text-danger',
            classArray : ['active', 'text-danger']
        }
    })
</script>
```

对象：

```vue
<!--使用对象变量-->
<div class="static" :class="classObj">{{msg}}</div>
<!--直接创建对象，但是很少用-->
<div class="static" :class="{active:true,'text-danger':false}">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        classObj : {
            // 该对象中属性的名字必须和样式名一致。
            active : false,
            'text-danger' : true
        }
    })
</script>
```

+ 对象中的属性为 true 的会被渲染，为 false 的不会被渲染。

#### 8.2、style绑定

用的不多。

字符串：

```vue
<div class="static" :style="myStyle">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Style绑定',
            myStyle : 'background-color: gray;',
        }
    })
</script>
```

数组：

```vue
<div class="static" :style="styleArray">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Style绑定',
            styleArray : [
                {backgroundColor: 'green'},
                {color : 'red'}
            ]
        }
    })
</script>
```

对象：

```vue
<div class="static" :style="styleObj1">{{msg}}</div>
<!-- backgroundColor 是属性名， gray 是属性值，一定要有单引号-->
<div class="static" :style="{backgroundColor: 'gray'}">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Style绑定',
            styleObj1 : {
                backgroundColor: 'green'
            },
        }
    })
</script>
```

+ 细节：使用对象形式这种写法时，样式的属性名如果带有 `-` 的话，要去掉减号，改成大驼峰写法：background-color => backgroundColor
+ 属性值要是一个字符串，要使用引号括起来。

## 9、条件渲染

### 9.1、v-if

v-if 指令的值：true / false

+ true: 表示该元素会被渲染到页面上。
+ false: 表示该元素不会被渲染到页面上。（注意：不是修改了CSS样式，是这个元素压根没有加载）

```vue
<div v-if="false">{{msg}}</div>
```

### 9.2、v-else

用于和v-if配对，v-if 和 v-else 之间不能断开，也就是说中间不能有其他的元素：

```vue
<img :src="imgPath1" v-if="counter % 2 === 1">
<img :src="imgPath2" v-else>
```

### 9.3、v-else-if

用在v-if、v-else的中间，v-if v-else-if v-else 三者在使用的时候，中间不能断开：

```vue
天气：
<span v-if="temprature <= 10">寒冷</span>
<span v-else-if="temprature <= 25">凉爽</span>
<span v-else>炎热</span>
```

### 9.4、v-show

v-show 指令是通过修改元素的 CSS 样式的 display 属性来达到显示和隐藏的。当 v-show 的值是 true 的时候元素会显示，为 false 的时候元素会被隐藏。

```vue
<div v-show="false">你可以看到我吗？</div>
```

v-if 和 v-show 应该如何选择？

​      1. 如果一个元素在页面上被频繁的隐藏和显示，建议使用 v-show，因为此时使用 v-if 开销比较大。

​      2. v-if 的优点：页面加载速度快，提高了页面的渲染效率。

### 9.5、template

template 标签/元素只是起到占位的作用，不会真正的出现在页面上，也不会影响页面的结构。

```vue
<template v-if="counter === 10">
    <input type="text">
    <input type="checkbox">
    <input type="radio">            
</template>
```

当v-if成立时，只会渲染出三个input，template标签不会被渲染。

## 10、列表渲染

### 10.1、v-for

`v-for` 用来重复渲染同一种元素：

```vue
v-for="(变量名,index) in/of 数组"
```

使用in或of是一样的效果。

遍历数组：

```vue
<ul>
    <li v-for="name,idx of names">
        {{name}}-{{idx}}
    </li>
</ul>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            names : ['jack','lucy','james'],
        }
    })
</script>
```

遍历对象的属性：第一个参数是属性的值，第二个参数是属性的名字

```vue
<ul>
    <li v-for="(value, propertyName) of user">
        {{propertyName}},{{value}}
    </li>
</ul>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            user : {
                id : '111',
                name : '张三',
                gender : '男'
            },
        }
    })
</script>
```

遍历字符串：第一个参数是字符串中的每个字符，第二个参数是下标（从0开始）

```vue
<ul>
    <li v-for="(c,index) of str">
        {{index}},{{c}}
    </li>
</ul>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            str : '魔法披风',
        }
    })
</script>
```

遍历指定的次数：前面的是数字，后面的是下标

```vue
<ul>
    <li v-for="(num,index) of counter">
        {{index}}, {{num}}
    </li>
</ul>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            counter : 10
        }
    })
</script>
```

+ 就是遍历 counter 中的每个数字。

### 10.2、key属性

v-for 指令所在的标签中，还有一个非常重要的属性，`key`：

```vue
<tr v-for="(hero,index) in heros"  :key="hero.id">
</tr>
```

如果没有指定 :key 属性，会自动拿 index 作为 key。这个 key 是这个 dom 元素的身份证号/唯一标识。

尽量不要使用index作key值，可以使用每个对象的id作key值，保证不会变化。有数组下标作key值的话，数组中头插法添加新元素会导致index变化，产生错乱。

key属性主要用于虚拟dom和真实dom之间的比较。

## 11、表单数据的收集

表单中的元素使用v-model来绑定属性。

### 11.1、.number

一个默认的输入框，type为number类型，会限制输入的数据只能是数字，但是实际上得到的是一个数字字符串，使用 `.number` 修饰符可以得到一个数字，而不是字符串：

```vue
<input type="number" v-model.number="user.age">
```

如果输入框的 type 不是 number 的话，比如是 text 的话，也可以使用 `.number` 修饰符，也会将字符串转为数字，如果输入的内容不是纯数字，会只保留数字（只限于以数字开头，如果不是以数字开头的话，则不会转为数字，而是直接保存字符串）：

```vue
<input type="text" v-model.number="user.age">
```

### 11.2、.trim

使用 `.trim` 修饰符可以去除前后空白：

```vue
<input type="text" v-model.trim="user.username">
```

### 11.3、.lazy

懒惰修饰符，当失去焦点后才会更新属性里的值。即数据不会立即同步到 Vue 实例的数据属性，而是等待特定事件触发后再同步。

默认情况下，v-model 会在每次输入事件（通常是 input 事件）时立即更新数据，但使用 lazy 修饰符后，它会等待 change 事件而不是 input 事件。

比如，在用户填写简介的时候，可以打开开发者工具查看，用户输入一个字符，Vue 实例中的属性就会实时更新一次，这是很耗资源的，可以使用 `.lazy` 修饰符，让文本域失去焦点后，才将用户输入的字符更新的 Vue 实例中

```vue
<textarea cols="50" rows="15" v-model.lazy="user.introduce"></textarea>
```

### 11.4、radio收集数据

单选框元素需要手动添加上value属性，否则使用v-model绑定的值就是空：

```vue
男<input type="radio" name="gender" value="1" v-model="user.gender">
女<input type="radio" name="gender" value="0" v-model="user.gender">
```

### 11.5、checkbox收集数据

checkbox 和 radio 一样，不能由用户输入值，如果没有指定 value 的话，使用 v-model 绑定 value 取到的值是这个标签的 checked 属性的值，所以也要手动指定 checkbox 的值：

```vue
旅游<input type="checkbox" v-model="user.interest" value="travel">
运动<input type="checkbox" v-model="user.interest" value="sport">
唱歌<input type="checkbox" v-model="user.interest" value="sing">
```

且复选框对应的数据应该是一个数组变量：

```vue
<script>
    const vm = new Vue({
        el: '#app',
        data: {
            user: {
                interest: [],
            },
        },
    })
</script>
```

+ 如果只是一个字符串的话，那么一个复选框的状态就会影响到其他复选框

### 11.6、默认值

在vue实例中就定义好一个默认值，使用v-model绑定就可以将默认值显示出来：

```js
data : {
    user : {
        // 让数据有默认值，通过双向绑定就可以设置页面的默认选中
        username : '',
        password : '',
        age : '',
        gender : '1',
        interest : ['travel'],
        grade : 'ss',
        introduce : '',
        accept : ''
    },
    msg : '表单数据的收集'
},
```

### 11.6、提交表单

如果表单中有一个按钮，点击按钮会就会默认提交表单，而一般采用ajax提交表单，所以需要阻止这样的默认提交事件，可以通过阻止按钮的默认点击事件和表单的默认提交事件：

```vue
<!--阻止按钮的默认点击事件-->
<button @click.prevent="send">注册</button>

<!--阻止表单的默认提交事件-->
<form @submit.prevent="send">
    <button>注册</button>
</form>
```

## 12、过滤器

过滤器 filters 适用于简单的逻辑处理，例如：对一些数据进行格式化显示。他的功能完全可以使用 methods，computed 来实现。过滤器可以进行全局配置，也可以进行局部配置：

+ 全局配置：在构建任何 Vue 实例之前使用 `Vue.filter(‘过滤器名称’, callback) `进行配置。
+ 局部配置：在构建 Vue 实例的配置项中使用 `filters` 进行局部配置。

### 12.1、局部配置

过滤器可以用在两个地方：插值语法和 v-bind 指令中。

过滤器的用法：通过管道使用

```vue
<!--使用在插值语法中-->
<h2>商品价格：{{price | filterA}}</h2>

<!--使用在v-bind命令中-->
<input type="text" :value="price | filterA">
```

+ `|` 是管道符号，将 price 这个值通过管道传给 filterA 方法，filterA 方法的参数就是这个传过来的值

定义过滤器，在 Vue 实例中定义一个 filters 配置项，里面定义方法：：

```vue
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '过滤器',
            price : 50.6
        },
       	filters : {
            filterA(val){
                if(val === null || val === undefined || val === ''){
                    return '-'
                }
                return val
            },
        }
    })
</script>
```

+ 过滤器都要有一个返回值，这个返回值就是过滤器的结果

过滤器可以串联：将 price 传给 filterA 过滤器，然后将 filterA 的返回结果传给 filterB 过滤器，最终将 filterB 过滤器的值渲染出来

```vue
<h2>商品价格：{{price | filterA | filterB}}</h2>
```

过滤器可以接收多个参数：

```vue
<h2>商品价格：{{price | filterA | filterB(3)}}</h2>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '过滤器',
            price : 50.6
        },
       	filters : {
            filterA(val){
                if(val === null || val === undefined || val === ''){
                    return '-'
                }
                return val
            },
            filterB(val, number){
                return val.toFixed(number)
            }
        }
    })
</script>
```

+ 过滤器的第一个参数不用手写，永远接收的都是前一个过滤器的返回值。
+ toFixed() 是 JavaScript 中用于格式化数字的方法。它可用于将浮点数或整数转换为一个指定小数位数的字符串，以便显示或输出。

### 12.2、全局配置

以上用到的都是局部过滤器，局部过滤器在另一个容器中无法使用。还有全局过滤器，全局过滤器在每个容器中都可以使用：

```js
Vue.filter('过滤器名称', 回调函数)
```

比如：

```js
Vue.filter('filterA', function(val){
    if(val === null || val === undefined || val === ''){
        return '-'
    }
    return val
})
```

## 13、自定义指令

### 13.1、局部指令

#### 13.1.1、函数式

自定义指令需要在Vue实例的 directives 配置项中：

```js
const vm = new Vue({
    el: '#app',
    data: {
        msg : '自定义指令',
    },
    directives: {
        // 指令1
        // 指令2……
        '指令' : function(element, binding){
            console.log('@')
        },
    }
})
```

关于自定义指令的名字：

+ `v- `不需要写
+ Vue 官方建议指令的名字要全部小写。如果是多个单词的话，请使用 `-` 进行衔接。

这个回调函数的执行时机包括两个:

+ 标签和指令第一次绑定的时候。
+ 模板被重新解析的时候（ Data 发生改变的时候）。

这个回调函数有两个参数：

+ 第一个参数是真实的 dom 元素。 
+ 第二个参数是标签与指令之间的绑定关系的对象。这个对象的 value 就是绑定的值

#### 13.1.2、对象式

一般自定义指令使用对象式：

```js
const vm = new Vue({
    el: '#app',
    data: {
        msg : '自定义指令',
    },
    directives: {
        'bind-blue' : {
            // 元素与指令初次绑定的时候，自动调用bind
            bind(element, binding){
                element.value = binding.value
            },
            // 元素被插入到页面之后，这个函数自动被调用。
            inserted(element, binding){
                element.parentNode.style.backgroundColor = 'blue'
            },
            // 当模板重新解析的时候，这个函数会被自动调用。
            update(element, binding){
                element.value = binding.value
            }
        } 
    }
})
```

+ 这个指令对象中三个方法的名字不能随便写。
+ 这个指令中的三个函数都会被自动调用，注意：在特定的时间节点调用特定的函数，这种被调用的函数称为钩子函数。

### 13.2、全局指令

以上定义的指令都是局部指令，不能在另一个容器中使用。

定义全局指令，要在创建所有 Vue 实例之前定义：

```js
// 函数式
Vue.directive('text-danger', function(element, binding){
    console.log(this)
    element.innerText = binding.value
    element.style.color = 'red'
})

// 对象式
Vue.directive('bind-blue', {
    bind(element, binding){
        element.value = binding.value
        console.log(this)
    },
    inserted(element, binding){
        element.parentNode.style.backgroundColor = 'skyblue'
        console.log(this)
    },
    update(element, binding){
        element.value = binding.value
        console.log(this)
    }
})
```

对于自定义指令来说，函数体当中的this是window，而不是vue实例。

## 14、响应式和数据劫持

修改 data 后，页面自动改变/刷新，这就是响应式。响应式的实现用到了数据劫持。

数据劫持就是属性的set方法（数据代理式属性的get方法）。修改属性值的时候，会先走到 set 方法这来，set 方法就像半路劫持一样，所以称为数据劫持。数据劫持主要做两个事：

+ 修改内存中该对象的属性值
+ 重新渲染页面

### 14.1、后期添加响应式

Vue会给data中所有的属性，以及属性中的属性，都会添加响应式。但是后期添加的属性，不会有响应式：

```js
// 这个不会有响应式
vm.$data.a.email = 'jack@126.com'
```

如果你想给后期追加的属性添加响应式处理的话，调用以下两个方法都可以：

+ Vue.set() 、 
+ vm.$set()

这两方法的语法格式、效果都是一样的：

```js
Vue.set(目标对象, 属性名, 属性值)
```

所以以上代码这样写：

```js
Vue.set(vm.$data.a, 'email', 'jack@126.com')
// 以下写法也可以，省略掉 $data
Vue.set(vm.a, 'email', 'jack@123.com')
```

避免在运行时向 Vue 实例或其根 $data 添加响应式，不能直接给 vm / vm.\$data 追加响应式属性。只能在声明时提前定义好。以下代码会报错：

```js
Vue.set(vm, 'x', '1')
Vue.set(vm.$data, 'x', '1')
```

### 14.2、数组的响应式处理

数组本身是有响应式处理的，但是数组中的元素，通过下标去访问是没有响应式处理的：

```vue
<div id="app">
    <h1>{{msg}}</h1>
    <ul>
        <li v-for="user in users">
            {{user}}
        </li>
    </ul>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '数组的响应式处理',
            users : ['jack', 'lucy', 'james'],
        }
    })
</script>
```

+ 执行users[0] = "zhangsan"，是不会有响应式的，页面不会改变

如果数组中每个元素是一个对象，这每个对象中的属性都是有响应式处理的：

```vue
<div id="app">
    <h1>{{msg}}</h1>
    <ul>
        <li v-for="vip in vips" :key="vip.id">
            {{vip.name}}
        </li>
    </ul>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '数组的响应式处理',
            vips : [
                {id:'111', name:'zhangsan'},
                {id:'222', name:'lisi'}
            ]
        }
    })
</script>
```

+ 执行vips[0].name="wangwu"，是会有响应式的，页面会改变

如果想通过下标修改数组中的元素时也有响应式的话，可以使用：

+ `vm.$set(数组对象, 下标, 值)`
+ `Vue.set(数组对象, 下标, 值)`

或者通过以下的 7 个方法来给数组添加响应式处理

+ push()
+ pop()      
+ reverse()
+ splice()
+ sunshift()
+ sort()

## 15、生命周期

Vue 的生命周期指的是：vm 对象从创建到最终销毁的整个过程。

### 15.1、钩子函数

在特定时间点自动调用的函数叫做钩子函数。

Vue 的生命周期可以被划分为 4 个阶段：

+ 初始阶段：生成虚拟 dom
+ 挂载阶段：把虚拟 dom 放到页面中，生成了真实 dom，页面渲染了
+ 更新阶段：data 发生了变化，页面会重新渲染
+ 销毁阶段：销毁 Vue 实例

每个阶段会调用两个钩子函数。两个钩子函数名的特点：beforeXxx()、xxxed()

+ 初始阶段
  + beforeCreate() 创建前
  + created() 创建后
+ 挂载阶段
  + beforeMount() 挂载前
  + mounted() 挂载后
+ 更新阶段
  + beforeUpdate() 更新前
  + updated() 更新后
+ 销毁阶段
  + beforeDestroy() 销毁前
  + destroyed() 销毁后

这8个钩子函数是直接写在 Vue 构造函数的 options 对象当中：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : 'Vue生命周期',
    },
    // 1.创建阶段
    beforeCreate() {
        // 创建前
        console.log('beforeCreate')
    },
    created() {
        // 创建后
        console.log('created')
    },
    // 2.挂载阶段
    beforeMount() {
        // 挂载前
        console.log('beforeMount')
    },
    mounted() {
        // 挂载后
        console.log('mounted')
    },
    // 3.更新阶段
    beforeUpdate() {
        // 更新前
        console.log('beforeUpdate')
    },
    updated() {
        // 更新后
        console.log('updated')
    },
    // 4.销毁阶段
    beforeDestroy() {
        // 销毁前
        console.log('beforeDestroy')
    },
    destroyed() {
        // 销毁后
        console.log('destroyed')
    },
})
```

### 15.2、初始阶段

初始阶段中的 beforeCreate 的 create 指的是“数据代理&数据监测”的创建，而不是 Vue 实例的创建。

那在 beforeCreate 钩子函数中，此时数据代理还没有创建，所以此时是访问不了 data 中的数据的，包括 methods 也是无法访问的。创建后表示数据代理和数据监测创建完毕，可以访问 data 中的数据了，可以访问 methods 了。

在声明周期中，created 钩子函数过后，有两个连续判断

+ el 有，template 也有，最终编译 template 模板语句。
  + 此时 el 指定的挂载位置就是个占位符，会用 template 的内容覆盖掉 el 指定位置的内容
+ el 有，template 没有，最终编译 el 模板语句。
+ el 没有的时候，需要手动调用 vm.$mount(el) 进行手动挂载，然后流程才能继续。此时如果 template 有，最终编译 template 模板语句。
  + 没有 el 指定挂载位置，就需要使用 `vm.$mount(#app)` 这样手动挂载
+ el 没有的时候，需要手动调用 vm.$mount(el) 进行手动挂载，然后流程才能继续。此时如果没有 template，最终编译 el 模板语句。

结论：

+ 流程要想继续：el 必须存在。
+ el 和 template 同时存在，优先选择 template。如果没有 template，才会选择 el。

### 15.3、挂载阶段

这个阶段将生成的虚拟 dom 变成真实的 dom，并且放在页面上。

如果在 beforeMount() 运行期间操作了 dom 元素，页面上是不会生效的，因为会被真实的 dom 覆盖掉；在 mounted() 运行期间操作了 dom 元素，页面上是会生效的。

### 15.4、更新阶段

只有当 data 中的数据变化了，才会进入更新阶段。

beforeUpdate() 此时是更新前，该更新指的是页面的更新，在内存中的数据已经改变了，但是还没有更新到页面上。beforeUpdate() 后，新旧 dom 通过 diff 算法进行比对，页面会发生变化。

updated() 此时页面已经更新完毕了。

### 15.5、销毁阶段

要进入销毁阶段，必须手动调用 vm.$destroy() 方法。

这个销毁的意思是：将 Vue 实例上的监视器、子组件、自定义事件监听器等都解绑了。而不是将 vm 从内存空间中释放了。所以这个销毁也可以叫做解绑。

注意：如果使用的是 Vue 版本较高的话，销毁时移除的不只是 自定义事件监听器，还会将普通的事件监听器也移除了；如果版本较低，就只移除 自定义事件监听器。

## 16、组件化开发

组件：实现应用中局部功能的代码和资源的集合。凡是采用组件方式开发的应用都可以称为组件化应用。

模块：一个大的 js 文件按照模块化拆分规则进行拆分，生成多个 js 文件，每一个 js 文件叫做模块。凡是采用模块方式开发的应用都可以称为模块化应用。

任何一个组件中都可以包含这些资源：HTML CSS JS 图片 声音 视频等。从这个角度也可以说明组件是可以包括模块的。

在 Vue 中根组件就是 vm。因此每一个组件也是一个 Vue 实例。

### 16.1、原始使用

组件的使用分为三步：

+ 第一步：创建组件

  ```js
  const myComponent = Vue.extend({
      template : `
              <ul>
                  <li v-for="(user,index) of users" :key="user.id">
                      {{index}},{{user.name}}
                  </li>
              </ul>
              `,
      data(){
          return {
              users : [
                  {id:'001',name:'jack'},
                  {id:'002',name:'lucy'},
                  {id:'003',name:'james'}
              ]
          }
      }
  })
  ```

  Vue.extend 可以省略。

  区别有哪些？

  + 创建 Vue 组件的时候，配置项中不能使用 el 配置项。（但是需要使用 template 配置项来配置模板语句。）
  + 配置项中的 data 不能使用直接对象的形式，必须使用 function。这样保证多个地方使用这个组件的对象时，一个地方修改了属性值不会影响其他地方的这个属性值

+ 第二步：注册组件 

  局部注册：在配置项当中使用 components，

  ```js
  const vm = new Vue({
      el : '#app',
      data : {
          msg : '第一个组件'
      },
      components : {
          // userlist是组件的名字。myComponent只是一个变量名。
          userlist : myComponent,
      }
  })
  ```

  + 这里如果组件的名字和变量名相同的话，可以这么写，比如创建的组件的名字就是userlist：

    ```js
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '第一个组件'
        },
        components : {
            userlist,
        }
    })
    ```

  全局注册：全局注册的组件可以使用在多个 Vue 实例中

  ```js
  Vue.component('userlist', myComponent)
  ```

+ 第三步：使用组件

  ```vue
  <userlist></userlist>
  ```

### 16.2、单标签

使用组件可以写成单标签形式：

```vue
<userlist/>
```

但是写了多个的话，页面只会显示出一个，因为在 Vue 当中是可以使用自闭合标签的，但是前提必须在脚手架环境中使用：

```vue
<userlist/>
<userlist/>
<userlist/>
```

### 16.3、省略Vue.extend

在创建组件的时候 Vue.extend() 可以省略，但是底层实际上还是会调用的，在注册组件的时候会调用：

```js
const myComponent = {
    template : `
            <ul>
                <li v-for="(user,index) of users" :key="user.id">
                    {{index}},{{user.name}}
                </li>
            </ul>
            `,
    data(){
        return {
            users : [
                {id:'001',name:'jack'},
                {id:'002',name:'lucy'},
                {id:'003',name:'james'}
            ]
        }
    }
}
```

### 16.4、组件的名字

第一种：全部小写

```js
Vue.component('helloworld', {
    name : 'Xxxxx',
    template : `<h1>测试组件的名字%%%%%</h1>`
})
```

第二种：首字母大写，后面都是小写

```js
Vue.component('Helloworld', {
    name : 'Xxxxx',
    template : `<h1>测试组件的名字%%%%%</h1>`
})
```

第三种：kebab-case命名法（串式命名法。例如：user-login）

```js
Vue.component('hello-world', {
    name : 'Xxxxx',
    template : `<h1>测试组件的名字%%%%%</h1>`
})
```

第四种：CamelCase命名法（驼峰式命名法。例如：UserLogin），但是这种方式只允许在脚手架环境中使用。

```js
Vue.component('HelloWorld', {
    name : 'Xxxxx',
    template : `<h1>测试组件的名字%%%%%</h1>`
})
```

+ 没有脚手架的话，还可以使用 hello-world 来调用

在创建组件的时候，通过配置项配置一个 name，这个 name 不是组件的名字，是设置 Vue 开发者工具中显示的组件的名字。

### 16.5、组件的嵌套

组件的嵌套就是创建两个组件，在一个组件中注册、使用另一个组件：

```vue
<div id="root">
    <app></app>
</div>
<script>
    // 创建X组件
    const x = {
        template : `
                <div>
                    <h2>X组件</h2>
    			</div>
            `,
    }
    // 创建app组件
    const app = {
        template : `
                <div>
                    <h1>App组件</h1>
                    <x></x>
    			</div>
            `,
        components: {
            x
        }
    }
    // vm
    const vm = new Vue({
        el : '#root',
        // 注册app组件
        components : {
            app
        }
    })
</script>
```

另外注册子组件时注意：子组件要注册在父组件之前，否则页面渲染到了父组件时找不到子组件；嵌套的子组件只能使用在父组件的 template 模板语句中

### 16.6、vm与vc

#### 16.6.1、this

vc是vue组件，VueComponent；vm是vue实例，VueModel。

vm 与 vc 的关系可以这样说：

+ vm 有的 vc 不一定有
+ vc 有的 vm 一定有
+ vc 是 vm 的子

在创建vm时，new Vue 中的this就是vm；在创建vc时，Vue.extend中的this不是vc，而是一个全新的 VueComponent 构造函数：

```js
const user = Vue.extend({
    template : `
            <div>
                <h1>user组件</h1>
    		</div>
            `,
})
```

这个user就是一个构造函数，使用user时，就会自动创建user对象：

```vue
<user></user>
```

#### 16.6.2、原型属性

关于 `prototype ` 和  `__proto__`：

+ prototype ：每个函数对象（包括构造函数）都有一个 prototype 属性，它是一个对象。

  prototype 属性用于定义对象的方法和属性，这些方法和属性可以被该函数构造的实例继承。

  当你创建一个自定义构造函数，该构造函数的 prototype 属性上的属性和方法将被新创建的实例继承。

+ `__proto__` ：`__proto__` 是每个对象都具有的属性，它指向对象的原型。

  通过 `__proto__ ` 属性，你可以访问和修改对象的原型链，它允许对象在运行时动态继承属性和方法。

  `__proto__` 属性通常不应该被直接访问，因为它是非标准的属性。

+ prototype 是用函数对象调用，显式的原型属性（建议程序员使用的）

+ `__proto__` 是用对象调用，隐式的原型属性（不建议程序员使用的）

获取原型对象：

```js
function Vip(){}

// 函数对象调用，获取原型对象
let x = Vip.prototype
// 对象调用，获取原型对象
let a = new Vip()
let y = a.__proto__

// 原型对象只有一个，其实原型对象都是共享的
console.log(x === y) // true
```

可以给原型对象扩展属性，然后通过实例可以访问到这个扩展的属性：

```js
// 给原型对象扩展属性
Vip.prototype.counter = 1000

// 通过Vip实例对象来访问这个属性
console.log(a.counter)  // 1000
// 本质上就是：
console.log(a.__proto__counter)
```

访问原理：首先去 a 实例上找 counter 属性，如果 a 实例上没有 counter 属性的话，会沿着 `__proto__` 这个原型对象去找。

那么给Vue的原型对象扩展一个属性，也可以通过vc来访问到。因为vc的原型对象就是Vue，如果Vue上面没有该属性就会去Vue的原型对象上找。这样设计是为了代码复用，在 Vue 的原型对象中有很多属性和方法，在 vc 中就不用重新定义了。

底层实现原理：

```js
VueComponent.prototype.__proto__ = Vue.prototype
```

### 16.7、单文件组件

在实际开发中，一个组件对应一个单独的文件，并且每个文件的扩展名都是 `.vue` ，这是 Vue 框架规定的，只有 Vue 框架能够认识，浏览器无法直接打开运行。

#### 16.7.1、使用

单文件组件的文件名命名规范和组件名的命名规范相同：

+ 全部小写：userlist
+ 首字母大写，后面全部小写：Userlist
+ kebab-case 命名法：user-list
+ CamelCase 命名法：UserList

.vue 文件的内容包括三块：

```vue
<template></template>

<script></script>

<style></style>
```

+ 结构：`<template>HTML代码</template>`
+ 交互：`<script>JS代码</script>`
+ 样式：`<style>CSS代码</style>`

现在创建一个X1组件，需要创建一个X1.vue文件：

```vue
<template>
	<div>
    	<h3>X1组件</h3>
    </div>
</template>

<script>
    // 导出X组件
    // const X1 = {
    //     
    // }
    // export X1;
    
    // 默认导出
    export default {
        
    }
</script>

<style></style>
```

+ 定义完组件后，需要将组件导出去，这样其他组件才能使用这个组件，使用 export 导出 X1 组件，X1 就是一个对象，所以可以直接使用默认导出
+ 这个导出的对象，就是之前创建的vc对象

要想在组件中使用其他组件，需要先将其他组件导入进来，然后注册、使用：

```vue
<template>
    <div>
        <h2>X组件</h2>
        <!-- 使用组件 -->
        <X1></X1>
    </div>
</template>

<script>
    import X1 from './X1.vue'
    export default {
        // 注册组件
        components : {X1}
    }
</script>
```

+ 导入时，import 后的名字可以随意写，使用的时候也是用这个名字，导入的文件名去掉 `.vue` 扩展名也可以
+ 导入之后，就要注册组件，注册组件时所用的名字，就应该和导入时定义的名字一样
+ 注册后就要使用组件，在 template 中的 html 代码中使用

#### 16.7.2、main.js

一般项目中会将创建Vue实例vm（根组件）的代码写在一个单独的js文件中，main.js，这是整个项目的入口文件，在这里创建vm，并且挂载vm，注册App组件：

```js
import App from './App.vue'

new Vue({
    el : '#root',
    // 使用组件
    template : `<App></App>`,
    // 注册App组件
    components : {App}
})
```

#### 16.7.3、index.html

将Vue实例挂载的位置、安装Vue.js的代码放在一个index.html文件中：

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>单文件组件</title>
</head>
<body>
    <div id="root"></div>
    <script src="../js/vue.js"></script>
    <script src="./main.js"></script>
</body>
</html>
```

此时运行这个index.html文件，会报错，因为浏览器不支持 ES6 的模块化开发，需要 Vue 的脚手架 Vue CLI，脚手架会将 vue 文件转换成浏览器能看懂的 html、css、js，并且脚手架还会将这些代码自动放在服务器上，启动脚手架后，服务器就启动了，就可以访问了。

### 16.8、props

组件实现了复用，但是组件的数据也被复用了。现要求每个组件都有自己的数据。这就需要使用 props 了，让数据变成动态的。

在父组件中找到使用的子组件，在这个子组件上使用属性传递数据，也可以使用v-bind命令绑定属性来传递动态数据：

```vue
<template>
    <div>
        <h1>{{msg}}</h1>
        <!-- 在App这个父组件当中，找到子组件Car，然后给Car这个子组件传数据：通过属性的形式传数据 -->
        <Car brand="宝马520" color="黑色" price="10"></Car>
        <hr>
        <Car brand="比亚迪汉" color="红色" price="20"></Car>
        <Car :brand="brand" :color="color" :price="price"></Car>
    </div>
</template>
```

然后在子组件中使用 props 来接收这个数据，使用 props 接收数据就不需要使用 data 配置项了，且 props 有好几种方式。

第一种方式：简单的接收方式，直接采用数组接收

```vue
<script>
export default {
    name: 'Car',
    props: ['brand', 'color', 'price']
}
</script>
```

第二种：添加类型限制

```vue
<script>
    export default {
        name: 'Car',
        props : {
            brand : String,
            color : String,
            price : Number
        }
    }
</script>
```

+ 这里的price限制是一个Number类型，那么父组件中传值就要使用v-bind来传，否则会是一个字符串类型的值：

  ```vue
  <Car brand="比亚迪汉" color="红色" :price="20"></Car>
  ```

第三种：添加类型限制，并且还可以添加默认值，还可以添加必要性

```vue
<script>
    export default {
        name: 'Car',
        props : {
            brand : {
                type : String,
                required : true
            },
            color : {
                type : String,
                default : '红色'
            },
            price : {
                type : Number,
                required : true
            }
        }
    }
</script>
```

不要修改 prop 中的数据，避免直接更改 prop，因为每当父组件重新渲染时，该值都会被覆盖。

### 16.9、从父组件中获取子组件

在要获取的子组件上使用 `ref` 打标记：

```html
<Car brand="宝马520" color="黑色" :price="10" ref="car1"></Car>
<hr>
<Car brand="比亚迪汉" color="红色" :price="20" ref="car2"></Car>
```

通过vc对象可以拿到打过标记的子组件：

```vue
<script>
    import Car from './components/Car.vue'
    export default {
        name: 'App',
        data() {
            return {
                msg: '汽车信息'
            }
        },
        methods: {
            printCarInfo() {
                // 获取子组件
                console.log(this.$refs.car1)
                console.log(this.$refs.car2)
                // 获取子组件的属性
                console.log(this.$refs.car1.brand)
                console.log(this.$refs.car1.color)
                console.log(this.$refs.car1.price)
            }
        },
        components: { Car }
    }
</script>
```

也可以拿到不是组件的元素，方法一样的：

```vue
<h1 ref="hh">{{msg}}</h1>
```

### 16.10、mixins（混入）

mixins用来实现代码复用，可以将多个组件中相同的代码片段提取出来，放在一个方法中，需要时候调用即可。新建一个 mixin.js 文件，该文件和 main.js 平级，然后将公共部分的代码放到这个 mixins 中的一个对象中，然后将这个对象暴露出去：

```js
export const mix1 = {
    methods: {
        printInfo(){
           console.log(this.name, ',' , this.age) 
        }
    }
}
```

然后在需要的位置导入，比如 User.vue：

```vue
<template>
	<div>
        <h1>{{msg}}</h1>
        <h3>姓名：{{name}}</h3>
        <h3>年龄：{{age}}</h3>
        <button @click="printInfo">打印用户信息</button>
    </div>
</template>

<script>
    import {mix1} from '../mixin.js'

    export default {
        name : 'User',
        data() {
            return {
                msg : '用户信息',
                name : '张三',
                age : 20
            }
        },
        mixins : [mix1]
    }
</script>
```

混入不会破坏原有的东西，假如 User.vue 有个 a 方法，在混入中也定义了一个 a 方法，混入中的 a 方法不会覆盖掉 User 中的 a 方法。

混入对生命周期的八个钩子函数有特殊处理

+ 不会有覆盖的问题
+ 先执行 mixins 中的钩子函数，再执行自己的

现在想要混入所有的组件，可以使用全局混入。在 main.js 中：

```js
import { mix1, mix2, mix3 } from './mixin.js'

Vue.mixin(mix1)
Vue.mixin(mix2)
Vue.mixin(mix3)
```

这样所有的组件都混入 mix1、mix2、mix3

### 16.11、plugins（插件）

 给 Vue 做功能增强的。

定义插件：插件一般都放到一个 plugins.js 文件中

```js
const p1 = {
    install(Vue, a, b, c, d){
        console.log('这个插件正在显示一个可爱的封面....')
    }
}
```

每一个插件都是一个对象，每一个插件对象中必须有一个 install 方法，这个 install 方法会被自动调用。

install 方法上的参数：包括两部分

+ 第一部分：Vue 构造函数( main.js 中的 Vue 构造函数)
+ 第二部分：可以接收用户在使用这个插件时传过来的数据，参数个数无限制。

定义完插件后，要暴露插件：

```js
export const p1 = {
    install(Vue, a, b, c, d){
        console.log('这个插件正在显示一个可爱的封面....')
    }
}
```

要使用插件，先导入插件，在 main.js 中：

```js
import {p1} from './plugins.js'
```

然后使用插件，插件的使用通常放在创建 Vue 实例之前：

```js
Vue.use(p1, 1,2,3,4)
```

### 16.12、scoped（局部样式）

默认情况下，在 vue 组件中定义的样式最终会汇总到一块，如果样式名一致，会导致冲突，冲突发生后，以后来加载的组件样式为准。

所以可以通过 scoped 来设置当前的样式是一个局部的：

```vue
<style scoped>
    .s {
        background-color:bisque
    } 
</style>
```

一般子组件中，样式上都会加一个属性 scoped，避免冲突。

如果想定义全局的样式，可以在 App.vue 跟组件中定义，根组件的 style 一般不加 scoped。

### 16.13、组件的自定义事件

#### 16.13.1、内置事件

click、keydown、keyup，这些事件都是内置事件。关于内置事件的实现步骤

+ 第一步：提供事件源
+ 第二步：给事件源绑定事件
  + `v-on:事件名` 或者简写为 `@事件名`
+ 第三步：编写回调函数，将回调函数和事件进行绑定
+ 第四步：等待事件的触发，只要事件触发，则执行回调函数。

#### 16.13.2、自定义事件

##### 16.13.2.1、组件标签上绑定事件

流程差不多

+ 第一步：提供事件源（这个事件源是一个组件）
+ 第二步：给组件绑定事件
  + `v-on:事件名` 或者简写为 `@事件名`
+ 第三步：编写回调函数，将回调函数和事件进行绑定
+ 第四步：等待事件的触发，只要事件触发，则执行回调函数。

对于组件自定义事件来说，要想让事件发生，需要去执行一段代码。这段代码负责去触发这个事件，让这个事件发生。事件绑定在 A 组件上，则触发这个事件的代码要在 A 组件当中编写。

通过事件的方式，可以实现子组件向父组件传递数据的功能。

给组件绑定一个事件：

```vue
<!-- 给User组件绑定一个自定义的事件，该组件使用在App组件中 -->
<User v-on:event1="doSome"></User>
```

那么要在组件内部编写代码触发事件，触发指定事件使用 vc 上的 $emit 方法，传过去一个事件名：

```vue
<template>
    <div>
        <!--点击这个按钮就会触发event1事件-->
        <button @click="triggerEvent1">触发event1事件</button>
    </div>
</template>

<script>
    export default {
        name : 'User',
        methods: {
            triggerEvent1(){
                // 编写触发event1事件的代码
                // this是当前的组件实例：vc
                this.$emit('event1')
            },
        },
    }
</script>
```

在使用 $emit 触发事件的时候，还可以给事件绑定的回调函数传数据过去：

```vue
<script>
    export default {
        name: 'User',
        data() {
            return {
                name: '张三',
                age: 20,
                gender: '男'
            }
        },
        methods: {
            triggerEvent1(){
                // 触发事件的同时，可以给事件绑定的回调函数传数据
                this.$emit('event1', this.name, this.age, this.gender)
            },
        },

    }
</script>
```

那么 event1 事件绑定的函数需要接收这些数据：

```js
/* doSome(name, age, gender){
    console.log(name, age, gender)
} */
// ES6的语法，...params这个params可以看做是一个数组。以数组的形式接收多个参数。
doSome(name, ...params){
    console.log(name, params)
},
```

自定义事件也可以使用事件的修饰符：

```vue
 <User v-on:event1.once="doSome"></User>
```

##### 16.13.2.2、通过代码绑定事件

先创建一个组件（事件源）

```vue
<User ref="user"></User>
```

+ 需要通过 ref 拿到这个组件

接下来需要等这个组件挂载完毕后，才能给他绑定事件，所以用到一个钩子函数 mounted，在父组件 App 的 mounted 中绑定事件：

```js
mounted() {
    // 给ref="user"的组件绑定event1事件，并且给event1事件绑定一个回调函数：doSome
    this.$refs.user.$on('event1', this.doSome)
},
```

+ 而触发事件的代码还是之前的代码。

+ 还有种写法，保证绑定事件只触发一次：

  ```js
  this.$refs.user.$once('event1', this.doSome)
  ```

绑定事件时，this.doSome 可以被替代为function doSome()这样的普通函数，也可以使用箭头函数：

+ 普通函数中的this就是前面绑定事件的对象 this.$refs.user
+ 箭头函数中的this是mounted的this，也就是App组件实例
+ this.doSome这种写法中的this是App组件实例

##### 16.13.2.3、解绑自定义事件

哪个组件绑定的，就找哪个组件解绑，无论是触发事件还是解绑事件都是通过 `this.` 来调用对应的方法，所以每个组件之间不会有影响：

```js
// 仅仅解绑this指向的这个组件实例上的event1事件。
this.$off('event1')
```

如果解绑多个事件，可以使用数组：

```js
this.$off(['event1', 'event2'])
```

如果想解绑所有的事件：

```js
this.$off()
```

### 16.14、全局事件总线

可以实现所有组件之间的通信。

#### 16.14.1、原理

绑定事件使用 `$on`，触发事件使用 `$emit`，而绑定和触发事件的对象其实是同一个vc，说明vc上有`$on` 和 `$emit` 两个方法。

+ 在App组件中通过User组件绑定事件：

  ```js
  this.$refs.user.$on('event1', this.doSome)
  ```

+ 在User组件中也是通过User组件触发事件：

  ```js
  this.$emit('event1')
  ```

可以在所有组件外创建一个 vc 对象，是一个全局的 vc 对象，是一个所有组件共享的 vc 对象。这个 vc 对象上也有 `$on` 和 `$emit` 两个方法，此时，想 A1 组件给 B1 组件传递数据的话，那么可以让 A1 和 B1 拿到这个共享的 vc 组件，由 A1 去调用触发事件的代码 `$emit`，由 B1 去调用绑定事件的代码 `$on` 。

那么这个共享的 vc 对象就被称为全局事件总线。

#### 16.14.2、实现

创建一个vc对象作为全局事件总线对象，将这个对象扩展为vue原型对象的属性，这样所有实例都可以访问到他。

`$on` 和 `$emit` 两个方法在 vc 上有，在 vm 上也有，所以不需要单独创建一个共享的 vc 对象，直接使用 vm 对象，给vm对象扩展一个全局事件总线对象即可，全局事件总线有个通用的名字：`$bus`：

```js
new Vue({
   el: '#app',
   render: h => h(App),
   beforeCreate() {
      Vue.prototype.$bus = this
   }
})
```

绑定事件：

```js
// 获取全局事件总线，绑定事件
this.$bus.$on('eventx', this.hello);
```

触发事件：

```js
// 触发事件
this.$bus.$emit("eventx", this.name);
```

注意：在全局事件总线上绑定了很多组件的事件，当某个组件被销毁的时候，总线上对应的事件也应该被销毁，所以要在组件的 beforeDestroy 钩子中使用 `$off` 解绑对应的事件。

### 16.15、组件间通信方式

父向子传：通过 props 属性

子向父传：使用自定义事件

其他情况：全局事件总线

### 16.16、消息的订阅与发布

这是一种机制，使用这种机制也可以完成任意组件之间数据的传递，能够完成和全局事件总线一样的功能。

假设 A 组件是订阅方，B 组件是发布方，订阅放负责接收数据，发布方负责发送数据。

那么 A 组件中有个订阅的方法：

```js
订阅("消息的名字", function(a, b) {
    // 这个回调函数会在发布方发布消息后自动调用
})
```

那么 B 组件中有个发布的方法：

```js
发布("消息的名字", 消息的内容)
```

+ 这两个参数就会被传递到订阅方法中的回调函数的参数列表中，a 就是消息的名字，b 就是消息的内容

想要使用这个机制，需要安装第三方库 pubsub-js。

在终端中项目目录下：

```
npm i pubsub-js
```

装成功了后，就有一个对象可以使用了，这个对象就是 pubsub。

现在有三个组件 App、A、B，A、B 在 App 中注册并使用了，要实现 A、B 间的数据传递。在 A 组件中订阅，在 B 组件中发布。

在 A 组件中，等 A 组件挂载之后就订阅消息，要订阅消息，就需要用到 pubsub 对象，需要先引入这个对象，然后调用相关方法：

```vue
<script>
import pubsub from "pubsub-js";  // 引入pubsub对象

export default {
    name: "A",
    mounted() {  // 挂载后就开始订阅
        pubsub.subscribe('2024消息', function (messageName, message) {
            console.log("消息的名字：",messageName);
            console.log("消息的内容：",message);
        })
    }
}
</script>
```

+ messageName：消息的名字
+ message：具体的消息（数据）

在 B 组件中，通过一个按钮点击来发布消息，发布消息也需要 pubsub 对象：

```vue
<template>
    <div>
        <button @click="publish">发布</button>
    </div>
</template>

<script>
import pubsub from 'pubsub-js';

export default {
    name: "B",
    methods: {
        publish() {
            pubsub.publish("2024消息", "这是具体的消息");
        }
    }
}
</script>
```

+ 发布方法的第一个参数是消息的名字，要和订阅方法的消息名字一致

跟全局事件总线一样，A 组件订阅了消息，当 A 组件销毁的时候，一定要记得取消订阅。取消订阅不是根据名字来取消，而是通过 id，这个 id 是订阅消息时返回的 id：

```js
export default {
    name: "A",
    mounted() {
        this.pid = pubsub.subscribe('2024消息', function (messageName, message) {
            console.log("消息的名字：",messageName);
            console.log("消息的内容：",message);
        })
    },
    beforeDestroy() {
        pubsub.unsubscribe(this.pid);
    }
}
```

订阅中的回调函数尽量写箭头函数，因为写成普通函数的话，这个函数中的 this 是一个 undefined，写成箭头函数的话就能保证 this 是组件实例。

全局数据总线和消息订阅机制，优先使用全局数据总线。

## 17、Vue与Ajax

### 17.1、ajax发送异步请求的方式

1、原生方式，使用浏览器内置的 JS 对象 XMLHttpRequest

```js
(1)const xhr = new XMLHttpRequest()
(2)xhr.onreadystatechange = function(){}
(3)xhr.open()
(4)xhr.send()
```

2、原生方式，使用浏览器内置的 JS 函数 fetch

```js
fetch(‘url’, {method : ‘GET’}).then().then()
```

3、第三方库方式，JS 库 jQuery（对 XMLHttpRequest 进行的封装）

```js
(1)$.get()
(2)$.post()
```

4、第三方库方式，基于 Promise 的 HTTP 库：axios （对 XMLHttpRequest 进行的封装）

```js
axios.get().then()
```

axios 是Vue官方推荐使用的。

### 17.2、ajax跨域

在 a 页面中想获取 b 页面中的资源，如果 a 页面和 b 页面所处的协议、域名、端口不同（只要有一个不同），所进行的访问行动都是跨域的。

被允许的跨域行为：

+ 直接在浏览器地址栏上输入地址进行访问
+ 超链接
+ `<img src="”其它网站的图片是允许的”>"`
+ `<link href="其它网站的css文件是允许的">`
+ `<script src="其它网站的js文件是允许的">`

不被允许的跨域行为：

+ AJAX 请求是不允许的
+ Cookie、localStorage、IndexedDB 等存储性内容是不允许的
+ DOM 节点是不允许的

AJAX 请求无法跨域访问的原因：同源策略，同源是指"协议+域名+端口"三者相同，即便两个不同的域名指向同一个 ip 地址，也非同源。AJAX 请求不允许跨域并不是请求发不出去，请求能发出去，服务端能收到请求并正常返回结果，只是结果被浏览器拦截了。

解决ajax跨域的方案：

+ CORS方案（工作中常用的），这种方案主要是后端的一种解决方案，被访问的资源设置响应头，告诉浏览器我这个资源是允许跨域访问的：

  ```java
  response.setHeader("Access-Control-Allow-Origin", "http://localhost:8080");
  ```

+ jsonp 方案（面试常问的），采用的是`<script src="">`不受同源策略的限制来实现的，但只能解决GET请求。

+ 代理服务器方案（工作中常用的），Vue 脚手架自带的 8080 服务器也可以作为代理服务器，需要通过配置 vue.config.js 来启用这个代理

同源策略是浏览器需要遵循的标准，而如果是服务器向服务器请求就无需遵循同源策略的。

### 17.3、Vue脚手架内置服务器

#### 17.3.1、简单开启

在 vue.config.js 中添加如下配置：

```json
devServer: {
    proxy: 'http://localhost:8000' 
}
```

+ 含义：Vue 脚手架内置的 8080 服务器负责代理访问 8000 服务器

+ 注意：这个地址就写到端口号位置即可，后面具体的路径不需要写。

发送请求：

```js
 axios.get('http://localhost:8080/vue/bugs').then()
```

原理：当发送 AJAX 请求的时候，会优先从自己的服务器（http://localhost:8080）当中找 /vue/bugs 资源，如果找不到，就会找代理，然后去 http://localhost:8000 找 /vue/bugs 资源。

当前按钮这个页面就是在 8080 服务器上，又去访问 8080 服务器上的资源，所以 http://localhost:8080 可以省略：

```js
 axios.get('/vue/bugs').then()
```

这种简单配置不支持配置多个代理。

#### 17.3.2、高级开启

支持配置多个代理。官网上的配置模板：

```json
devServer: {
    proxy: {
        '/api': {
            target: '<url>',
            ws: true,
            changeOrigin: true
        },
        '/foo': {
            target: '<other_url>'
        }
    }
}
```

在 vue.config.js 中修改配置为：

```json
devServer: {
    proxy: {
        // 凡是请求路径以 /api 开始的，都走这个代理
        '/api': {
            target: 'http://localhost:8000',
            ws: true,  // 开启对websocket的支持（websocket是一种实时推送技术），默认不写就是true
            changeOrigin: true  // 默认是true，表示改变起源（让对方服务器不知道我们的真正起源）
        },
    }
}
```

然后发送 ajax 请求的地方也要修改以下路径：

```js
axios.get('/api/vue/bugs').then()
```

路径是由 /api 开头的，就会走 http://localhost:8000 这个代理，最终会将路径拼成：http://localhost:8000/api/vue/bugs，可以将api这个前缀去除，使用配置 pathRewrite，这样最终访问的路径是 http://localhost:8000/vue/bugs：

```js
devServer: {
    proxy: {
        '/api': {
            target: 'http://localhost:8000',
            pathRewrite: {'^/api' : ''},
            ws: true,
            changeOrigin: true
        },
    }
}
```

+ pathRewrite: {'^/api' : ''} 会将路径中的 /api 替换成 '' (空串)，这个 '^/api' 是一个正则表达式，^ 表示字符串的开始

## 18、Vuex

### 18.1、概述

Vuex 是一个插件，这个插件就是 Vue 的开发团队开发的。vuex 是实现数据集中式状态管理的插件。数据由 vuex 统一管理。其它组件都去使用 vuex 中的数据。只要有其中一个组件去修改了这个共享的数据，其它组件会同步更新。

全局事件总线和 vuex 插件的区别：

+ 全局事件总线关注点：组件和组件之间数据如何传递，一个绑定 \$on，一个触发 \$emit。数据实际上还是在局部的组件当中，并没有真正的让数据共享。只是数据传来传去
+ vuex 插件的关注点：共享数据本身就在 vuex 上。其中任何一个组件去操作这个数据，其它组件都会同步更新。是真正意义的数据共享

安装 Vuex：

+ vue2 安装 vuex3 版本：

  ```
  npm i vuex@3
  ```

+ vue3 安装 vuex4 版本:

  ```
  npm i vuex@4
  ```

### 18.2、使用准备

一般会将vuex单独放一个文件夹中，创建目录vuex，下面创建一个store.js文件，在 store.js 文件中创建核心 store 对象，并暴露：

```js
import Vue from "vue";
import Vuex from 'vuex';

Vue.use(Vuex);

const actions = {};
const mutations = {};
const state = {};

export default new Vuex.Store({ actions, mutations, state })
```

Vuex 是一个插件，所以要使用插件必须先引入它，然后通过 Vue.use 来使用，再通过 Vuex.Store 创建一个 store 对象，该构造函数需要传递一个配置项，里面起码有三个核心的配置项对象：

+ actions：它是一个负责执行某个行为的对象，在里面定义多个回调函数action，用来处理业务逻辑，以及调用更新数据的mutation
+ mutations：它是一个负责更新的对象，里面定义多个回调函数mutation，用来更新数据
+ state：它是一个状态对象，等同于 Vue 中的 data，只不过不叫数据，叫状态。state 中的数据都是做了响应式处理的。 

在 main.js 文件中关联 store，这一步很重要，完成这一步之后，所有的 vm 和 vc 对象上会多一个 $store 属性：

```js
import Vue from 'vue'
import App from './App.vue'
import store from './vuex/store'

new Vue({
   el: '#app',
   store: store,
   render: h => h(App),
})
```

+ 使用一个新的配置项 store，加上这个配置项之后，vm 以及所有的 vc 对象上都会多一个属性：\$store，以后通过 vm.\$store 或者 vc.\$store 来获取 store 对象。

### 18.3、一般用法

创建store对象，暴露出去：

```js
import Vuex from 'vuex';
import Vue from 'vue';

Vue.use(Vuex);  // 这一句必须在创建store实例前

const actions = {
    add(context, value) {
        value++;
        context.commit("ADD", value);
    }
};
const mutations = {
    ADD(state, value) {
        state.num = value;
    }
};
const state = {
    num: 0,
};

export default new Vuex.Store({actions, mutations, state})
```

actions中可以创建多个action，每一个action都是一个回调函数，该函数中不直接修改state中的状态，而是处理逻辑，最后调用mutations中的函数修改state。action的调用使用 `dispatch(名字，数据)`

+ context 参数：vuex 的上下文，可以看作是 store 的压缩版
+ value 参数：传过来的数据

mutations中可以创建多个mutation，每一个mutation也是一个回调函数，作用是直接更新state，mutations 中的方法名一般使用大写。mutation的调用使用 `commit(名字，数据)` 

+ state 参数：状态对象，这是一个引用，指向真正的state
+ value 参数：上一环节传过来的数据

然后在main.js中绑定：

```js
import Vue from 'vue'
import App from './App.vue'
import store from "./store/store";

new Vue({
  render: h => h(App),
  store: store,
}).$mount('#app')
```

在组件中使用：

```vue
<template>
    <div>
        <h1>{{$store.state.num}}</h1>
        <button @click="add">+1</button>
    </div>
</template>

<script>
export default {
    methods: {
        add() {
            // 调用actions中的action
            this.$store.dispatch('add', this.$store.state.num);
            // 也可以直接调用mutations中的mutation
            // this.#store.commit('ADD', this.$store.state.num);
        }
    }
}
</script>
```

如果在actions中有多个action，要在action中调用其他的action的话，不能直接调用，需要使用 `context.dispatch`：

```js
const actions = {
    addOne(context, value) {
        value++;
        context.commit('ADD_ONE', value);
        context.dispatch('other', value);
    },
    other(context, value) {
        console.log('other');
    }
};
```

在mutation中调用其他的mutation需要使用 `this.commit`，但是一般不会这么使用。

### 18.4、getters

vuex 插件中还有一个配置项 getters，

```js
const getters = {
    // 有很多个 getter
}
export default new Vuex.Store({actions, mutations, state, getters})
```

+ 每一个 getter 都可以看作是一个计算属性。
+ 每一个 getter 方法都会自动接收一个 state 对象

创建：

```js
const getters = {
    reversedName(state) {
        return state.name.split('').reverse().join('');
    }
}
```

使用：

```vue
<h3>反转后的用户名：{{ $store.getters.reversedName }}</h3>
```

### 18.5、mapState

mapState 对象是 vuex 插件提供的内置的对象（负责 state 对象映射工作的一个对象）。用来生成计算属性代码的。

需要先引入：

```js
import { mapState } from 'vuex';
```

然后使用在组件的计算属性中，可以使用对象形式，也可以使用数组形式：

```js
computed: {
    // 数组形式
    ...mapState(['users', 'vips', 'name']
	// 对象形式
	// ...mapState({ users: 'users', vips: 'vips', name: 'name' })
},
```

+ 对象形式中的key就是计算属性的名，value就是计算属性的值，就是 `this.$store.state.value` 
+ 注意，这个数组形式的写法，必须要是计算属性名和 state 中的数据名一致时，才能这样写
+ `...`是扩展运算符，解构

以上代码其实生成了以下代码：

```js
computed: {
    users() {
        return this.$store.state.users;
    },
    vips() {
        return this.$store.state.vips;
    },
    name() {
        return this.$store.state.name;
    }
},
```

那么访问就可以直接使用计算属性：

```vue
<h3>当前用户数量：{{ users.length }}</h3>
<h3>当前会员数量：{{ vips.length }}</h3>
<h3>用户名：{{ name }}</h3>
```

注意：mapState和mapGetters生成的代码是这样的：

```js
name() {
    return this.$store.state.name;
}
```

是简写的计算属性方式，没有setter方法，所以双向绑定的属性，不要用 mapState 代替

### 18.6、mapGetters

mapGetters 的使用方法和 mapState 是一样的，也要先引入：

```js
import {mapGetters} from 'vuex';
```

也是在组件的 computed 中使用：

```js
computed: {
    ...mapState(['users', 'vips', 'name']),
    ...mapGetters(['reversedName'])
},
```

然后模板中就可以直接使用 reversedName 变量，而可以不用 $store.getters.reversedName 了。

### 18.7、mapMutations和mapActions

mapMutations和mapActions用来优化methods的。

先引入：

```js
import {mapMutations, mapActions} from 'vuex';
```

使用在methods中：

```js
methods: {
    // 对象形式
    ...mapActions({ saveUser: 'saveUser' }),
    ...mapMutations({ saveVip: 'SAVE_VIP' }),
    
    // 数组形式
    ...mapActions(['saveUser']),
    ...mapMutations(['SAVE_VIP']),
}
```

+ 数组形式必须要是方法名和 action 中的数组名一致

以上的代码就生成了以下的代码：

```js
methods: {
    saveUser() {
        this.$store.dispatch('saveUser', { id: Date.now(), username: this.username });
        this.$store.commit('SAVE_VIP', { id: Date.now(), username: this.username });
        
        this.$store.dispatch('saveUser', { id: Date.now(), username: this.username });
        this.$store.commit('SAVE_VIP', { id: Date.now(), username: this.username });
    }
}
```

那么调用方法传递参数就在模板中调用的时候传：

```vue
<button @click="saveVip(vipname)">保存会员</button>
<button @click="SAVE_VIP(vipname)">保存会员</button>
```

### 18.8、vuex的模块化

#### 18.8.1、多模块

将所有模块共享的数据以及方法放在一个store.js中不好维护，所以按模块划分，store.js中不再需要state、actions、mutations、getters这四个配置，每个模块有自己的js文件，有自己的这四个配置，在store.js中只需要将模块引入进来即可：

```js
import Vue, { computed } from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

import aModel from './a';
import bModel from './b';
import cModel from "./c";

export default new Vuex.Store({
    /*
    modules: {
        // 模块名 ：模块对象
        aModel: aModel,
        bModel: bModel,
    },
    */
    modules: { aModel, bModel, cModel },
});
```

每个模块的写法，比如a模块，就是a.js：

```js
export default {
    actions: {
        doA1() {
            console.log("doA1 action.....");
        },
    },
    mutations: {
        doA2() {
            console.log("doA2 mutation.....");
        },
    },
    state: {
        a: 1,
    },
    getters: {
        computedA() {
            return 1;
        },
    },
};
```

那么原先访问state中数据的代码 `this.$store.state.a` 就需要改成具体的模块：

```js
this.$store.state.aModel.a
```

而调用action、mutation、getter的写法不变：

```js
this.$store.dispatch("doA1");
this.$store.commit("doA2");
this.$store.getters.computedA;
```

#### 18.8.2、命名空间

如果有多个模块，多个模块中有相同名字的action，在调用action的时候，就会将所有模块中相同的action都执行，所以这个时候需要在模块中开启命名空间：

```js
const a = {
    // 开启命名空间
    namespaced: true,
    actions: {
        doA1() {
            console.log("doA1 action.....");
        },
    },
    mutations: {
        doA2() {
            console.log("doA2 mutation.....");
        },
    },
    state: {
        a: 1,
    },
    getters: {
        computedA() {
            return 1;
        },
    },
};
```

开启命名空间后，会自动用引入模块时，给定的模块名字作命名空间的名字，调用action、mutation、getter的代码就需要指定命名空间，这样就不会执行所有模块中的全部同名方法：

```js
this.$store.dispatch("aModel/doA1");
this.$store.commit("aModel/doA2");
this.$store.getters['aModel/computedA']
```

+ bModel/computedB 这是一个属性名，但是不能通过 `.` 来访问，因为有一个斜杠

指定了命名空间后，mapState、mapGettera、mapMutations、mapActions的使用也要加上命名空间：

```js
export default {
    name: "A",
    computed: {
        ...mapState('aModel', ['a']),
        ...mapGetters('aModel', ['computedA']),
    },
    methods: {
        ...mapActions('aModel', ['doA1']),
        ...mapMutations('aModel', ['doA2']),
    },
};
```

## 19、路由

路由：route，路由器：router。

路由是为单页面应用而生。一个路由就是一个对应关系，是一个键值对，key是路径，value是组件。路由器管理着所有路由。

路由的工作原理：当地址栏上的地址发生了改变，路由器监视到了这个改变，根据新的路径匹配路由，然后显示对应的组件。

有了路由后，可以将组件分为路由组件和普通组件，普通组件就是没有路由的组件。一般会新建一个pages文件夹，将路由组件放在该文件夹下，普通组件就放在components下。

### 19.1、创建

1. 安装插件
2. 创建路由器
3. 使用并配置路由器

vue-router是一个插件，要使用路由器，需要先安装这个插件，

+ vue2 要安装 vue-router3

  ```
  npm i vue-router@3
  ```

+ vu3 要安装 vue-router4

  ```
  npm i vue-router@4
  ```

创建路由器对象，一般会在router目录下新建一个index.js文件：

```js
// 导入VueRouter插件
import VueRouter from "vue-router";
// 导入组件
// @表示指向的是 src 目录，表示路径从src下开始
import HeBei from "@/components/HeBei.vue";
import HeNan from "@/components/HeNan.vue";

// 创建路由器对象，在路由器对象中配置路由
const router = new VueRouter({
    // 在这里配置路由信息
    routes: [
        {
            // 如果路径是 /hebei，就会切换到HeBei组件
            path: '/hebei',
            component: HeBei
        },
        {
            path: '/henan',
            component: HeNan
        }
    ]
});

// 导出路由器对象
export default router;
```

+ routes 是一个数组，数组中的每一个对象就是一个路由
+ path：表示路径，必须以 `/` 开始，可以看成路由的 key
+ component：表示组件，可以看成路由的 value

只要路径检测到的是以某个路由的 path ，就会切换到对应的路由。

然后要在 main.js 中导入并使用这个插件，使用了插件之后，Vue 实例中就可以多出一个配置项 router，用来接受一个路由器对象，再把创建的路由器对象配置上去：

```js
// 导入
import VueRouter from 'vue-router'
// 如果一个文件是index.js，那么可以不写index.js
// import router from './router/index.js'
import router from "./router";

// 使用
Vue.use(VueRouter)

new Vue({
   el: '#app',
    // 配置
   router: router,
   render: h => h(App),
})
```

### 19.2、使用

要在组件中使用路由，需要使用 vue-router 插件提供的标签 router-link，这个标签会被编译为 a 标签：

```vue
<ul>
    <<li><router-link to="/hebei" active-class="selected">河北省</router-link></li>
	<li><router-link to="/henan" active-class="selected">河南省</router-link></li>
</ul>
```

+ active-class="selected"：实现被点击的元素class变为selected。
+ 这个 active-class 属性是 Vue.js框架中的，`router-link` 组件使用 `active-class` 属性来定义当路由链接匹配当前路由时应当添加到该链接元素上的 CSS 类。

然后点击链接后，要将对应的组件展示出来，需要告诉路由器将组件展示在哪，需要用到一个标签 router-view ，翻译为路由视图，其实就是一个占位符的作用：

```vue
<div>
    <div>
        <h1>省份</h1>
        <ul>
            <<li><router-link to="/hebei" active-class="selected">河北省</router-link></li>
        	<li><router-link to="/henan" active-class="selected">河南省</router-link></li>
        </ul>
	</div>
	<router-view></router-view>
</div>
```

router-view标签是跟路由的路径有关的，如果想要在父组件中使用了router-view，还要在子组件中使用的话，就要对应好路由 关系，然后可以直接使用。

### 19.3、多级路由

在原先的路由中使用children属性，children 是一个数组，表示多个子路由。数组中一个对象就是一个子路由，子路由中的 path 不要以 `/` 开始，系统会自动添加 `/`：

```js
routes: [
    {
        path: "/hebei",
        component: HeBei,
        children: [
            {
                path: "shijiazhuang",
                component: ShiJiaZhuang,
            },
            {
                path: "tangshan",
                component: TangShan,
            },
        ],
    },
],
```

使用多级路由时，就要将路径写完整：

```vue
<li><router-link to="/hebei/shijiazhuang" active-class="selected">石家庄</router-link></li>
<li><router-link to="/hebei/tangshan" active-class="selected">唐山</router-link></li>
```

### 19.4、query传参

通过传参可以让同一个组件显示出不同的数据。

可以在路由的路径上给组件传参，这种传参方式实际上是将参数传递到了路由对象的 query 属性上：

```vue
<li>
    <router-link to="/hebei/city?a1=长安区&a2=裕华区&a3=新华区" active-class="selected">石家庄</router-link>
</li>
<li>
    <router-link to="/hebei/city?a1=邯山区&a2=复兴区&a3=丛台区" active-class="selected">邯郸</router-link>
</li>
```

所有的路由组件都有一个属性 $route，这个 \$route 可以取到组件对应的路由对象，所以就可以通过 this.\$route.query.a1 来拿到“长安区”这个值，所以在组件中就可以通过遍历这个 query 的方式来渲染：

```vue
<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <li v-for="(a, index) in $route.query" :key="index">
                {{ a }}
            </li>
        </ul>
    </div>
</template>
```

而传参那里一般不会直接用字符串，而是使用变量，可以使用 v-bind 绑定 to 属性，这样 to= 后面就是表达式，表达式中可以使用字符串拼接的技术：

```vue
<li>
    <router-link :to="`/hebei/city?a1=${sjz[0]}&a2=${sjz[1]}&a3=${sjz[2]}`" active-class="selected"
                 >石家庄</router-link
        >
</li>
<li>
    <router-link :to="`/hebei/city?a1=${hd[0]}&a2=${hd[1]}&a3=${hd[2]}`" active-class="selected"
                 >邯郸</router-link
        >
</li>

<script>
export default {
    name: "HeBei",
    data() {
        return {
            sjz: ["长安区3", "裕华区2", "新华区2"],
            hd: ["邯山区3", "复兴区2", "丛台区2"],
        };
    },
};
</script>
```

也可以使用对象的方式传参，常用：

```vue
<li>
    <router-link
                 active-class="selected"
                 :to="{
                      path: '/hebei/city',
                      query: {
                          a1: sjz[0],
                          a2: sjz[1],
                          a3: sjz[2],
                          },
                      }"
                 >石家庄</router-link
        >
</li>
<li>
    <router-link
                 active-class="selected"
                 :to="{
                      path: '/hebei/city',
                      query: {
                          a1: hd[0],
                          a2: hd[1],
                          a3: hd[2],
                          },
                      }"
                 >邯郸</router-link
        >
</li>
```

这里要注意的是，以上代码中的两个路由的路径是一样的，并且都有active-class="selected"，那么当其中一个被点击后，另外一个的class也会变成selected，这是因为路径一样，所以将路径改为不一样即可，同时在路由器中将两个路由路径对应的组件改成同一个即可。

### 19.5、路由命名

可以给路由命名，这样就可以不使用路由的路径，而是直接使用名称，更加方便：

```js
{
    path: "/hebei",
    component: HeBei,
    children: [
        {
            name: "shi",  // 给路由命名
            path: "sjz",
            component: City,
        },
        {
            name: "han",  // 给路由命名
            path: "hd",
            component: City,
        },
    ],
},
```

但是使用路由的名称时，一定是一个变量，不能是一个字符串，也就是说必须用 v-bind 绑定to属性，这要to后面的才能写一个变量：

```vue
<li>
    <router-link
                 active-class="selected"
                 :to="{
                      name: 'shi',
                      //path: '/hebei/sjz',
                      query: {
                          a1: sjz[0],
                          a2: sjz[1],
                          a3: sjz[2],
                          },
                      }"
                 >石家庄</router-link
        >
</li>
```

不能直接在 `:to` 后面写路由的名字，必须要是一个对象，里面有name属性：

```vue
<router-link :to="{ name: 'shi'}">
```

### 19.6、params传参

params 方式传参是将参数直接跟在路径后面：

```vue
<li>
    <router-link active-class="selected" to="/hebei/sjz/裕华区/新华区/长安区">石家庄</router-link>
    <!--拼接字符串的方式：-->
    <router-link active-class="selected" :to="`/hebei/sjz/${sjz[0]}/${sjz[1]}/${sjz[2]}`">石家庄</router-link>
</li>
<li>
    <router-link active-class="selected" to="/hebei/hd/邯山区/复兴区/丛台区">邯郸</router-link>
</li>
```

如果是以对象的方式传参的话，属性名是params，并且只能使用路由的名字，不能使用路径；或者想使用名字而不是用路径的话，也只能使用对象的形式传参，因为路由的名称本身不包含参数：

```vue
<li>
    <router-link
                 active-class="selected"
                 :to="{
                      // 强调：如果使用的是params方式传参，这里只能使用name，不能使用path
                      //path : '/hebei/sjz',
                      name: 'shi',
                      params: {
                          a1: sjz[0],
                          a2: sjz[1],
                          a3: sjz[2],
                          },
                      }"
                 >石家庄</router-link
        >
</li>
```

并且，路由的路径中还需要使用 `:` 来配置参数，路径中使用 `:` 的表示是参数，`:` 后面的是参数的名字：

```js
{
    path: "/hebei",
    component: HeBei,
    children: [
        {
            name: "shi",
            path: "sjz/:a1/:a2/:a3",
            component: City,
        },
        {
            name: "han",
            path: "hd/:a1/:a2/:a3",
            component: City,
        },
    ],
},
```

使用这些数据的方法和query传参一样：

```vue
<ul>
    <li v-for="(a, index) in $route.params" :key="index">
        {{ a }}
    </li>
</ul>
```

### 19.6、props配置

以下写法支持params传参和query传参，用法一样的。

路由中有一个属性 props，用来配置一些数据，从而简化 `this.$router.params.xxx` 或 `this.$router.query.xxx` 的写法：

```js
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props($route) {  // 这个参数名随意，这个参数是当前路由对象
        return {
            a1: $route.params.a1,
            a2: $route.params.a2,
            a3: $route.params.a3,
        };
    }
},
```

+ 还有一种写法是对象式写法：

  ```js
  {
      name: "shi",
      path: "sjz/:a1/:a2/:a3",
      component: City,
      props: {
          x: "张三",
          y: "李四",
      },
  },
  ```

  但是，这种写法只能写静态数据，无法写动态的数据，无法接收传过来的数据，无法使用` x: this.$router.params.a1`。

+ 还有一种极简写法，这种写法只对params传参有效，直接将props属性赋值true，这会将 parmas 对象直接转换成 props 对象，内部直接转换，不需要我们负责：

  ```js
  {
      name: "shi",
      path: "sjz/:a1/:a2/:a3",
      component: City,
      props: true,
  },
  ```

  但这种写法，组件在使用props接收的时候，必须要写清楚每个属性名，不能直接写params接收整个对象。

当访问这个路径的时候，路由器会经过这个路由，可以访问到这个 props 对象，最后跳转到 City 这个组件上，那么在 City 组件中就可以接收这个 props 里面的数据。也是通过 props 来接收：

```vue
<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <li>{{ a1 }}</li>
            <li>{{ a2 }}</li>
            <li>{{ a3 }}</li>
        </ul>
    </div>
</template>

<script>
export default {
    name: "City",
    props: ["a1", "a2", "a3"],
};
</script>
```

也可以直接将params整个参数传给组件：

```js
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props($route) {  // 这个参数名随意
        return {
            params: $route.params,
        };
    }
},
```

让组件自己去渲染：

```vue
<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <li v-for="val,name in params" :key="name">
                {{ val }}
            </li>
        </ul>
    </div>
</template>

<script>
export default {
    name: "City",
    props: ["params"],
};
</script>
```

### 19.7、浏览器前进后退

浏览器的历史记录是存放在栈这种数据结构里面的。历史记录在存放到栈中的时候有两种不同的模式：push 和 replace。

+ push：以追加的方式入栈
+ replace：以替换栈顶元素的方式入栈

浏览器默认的模式是 push 模式。在浏览器上前进和后退是不会删除栈内的数据的，只是会将栈顶指针向上或向下移动：

```vue
<router-link active-class="selected" to="/hebei/hd/邯山区/复兴区/丛台区">邯郸</router-link>
```

开启replace模式，添加要给replace属性：

```vue
<router-link :replace="true" active-class="selected" to="/hebei/hd/邯山区/复兴区/丛台区">邯郸</router-link>
```

### 19.8、编程式路由导航

之前，在进行路由组件切换的时候，使用的是 router-link，router-link 最后会被编译为 a 超链接，所以目前本质上是通过超链接来完成路由组件的切换。这个叫声明式的路由导航。

通过编程的方式完成路由组件的切换叫做编程式路由导航。（其实就是调用现有的 API 来切换路由组件）

要获取到路由器对象 this.\$router，这个对象中有两个方法 push 和 replace，因为这里会切换路由，切换路由就会有两种方式将路由放入浏览器的栈中，这里的两种方法就是对应着两种方式。在使用编程式路由导航时，push 或 replace 方法会返回一个 Promise 对象，Promise 对象期望你能通过参数的方式给它两个回调函数，一个是成功的回调，一个是失败的回调。如果你没有给这两个回调函数，则会出现错误。在 push 或 replace 方法的参数位置上给两个回调函数，两个函数里面啥也不给，当发生错误的时候就不会执行任何事：：

```js
// 获取路由器对象
this.$router.push(
    {
        name: "shi",
        params: {
            a1: this.sjz[0],
            a2: this.sjz[1],
            a3: this.sjz[2],
        },
    },
    () => { },
    () => { }
);
```

+ 路由器对象是 this.\$router，路由对象是 this.\$route，

+ this.\$router 对象是整个项目的路由器对象，路由器对象一般一个项目只需要一个。

+ push 方法里面写的参数就是 rouer-link 上 `:to` 后的对象。或者写字符串链接也可以：

  ```js
  this.$router.push("/hebei/hd/邯山区/复兴区/丛台区");
  ```

this.\$router 中不止有 push 和 replace 两种 API，还有前进、后退、前进几步、后退几步的 API：

```js
// 前进
this.$router.forward();
// 后退
this.$router.back();
// 前进2步
this.$router.go(2);
// 后退2步
this.$router.go(-2);
```

### 19.9、路由组件的销毁

默认的情况下，只要进行了路由的切换，原先的那个组件就一定会被销毁。比如，选择的组件中有几个复选框被选中，切换路由组件后，又切换回来，发现原先的复选框选中状态没有了，这就是原先的组件被销毁了。

要保留组件，在切换的时候不被销毁，需要在组件显示的地方添加属性，可以将这个 router-view 标签加在一个 keep-alive 标签中，这样这个 router-view 上所有的组件切换都不会被杀死：

```vue
<keep-alive>
    <router-view></router-view>
</keep-alive>
```

也可以指定某个组件在切换的时候不被销毁，在 keep-alive 上使用 include 属性指定组件的名称：

```vue
<keep-alive include="HeBei">
    <router-view></router-view>
</keep-alive>
```

+ 这个组件的名字就是组件导出时指定的 name
+ include="HeBei" 表示切换组件时，HeBei 这个组件不被销毁

也可以指定多个组件名称，需要使用数组：

```vue
<keep-alive :include="['HeBei', 'HeNan']">
    <router-view></router-view>
</keep-alive>
```

### 19.10、路由组件的钩子

对于路由组件来书，除了普通组件的 8 个，还有两个：

+ activated：在路由组件被激活的时候执行
+ deactivated：在路由组件被切走的时候被执行

### 19.11、路由meta属性

如果想给路由添加自定义属性，需要借助路由对象的 meta（路由元）属性：

```js
{
    path: "/hebei",
    component: HeBei,
    children: [
        {
            name: "shi",
            path: "sjz/:a1/:a2/:a3",
            component: City,
            props: true,
            meta: { isAuth: true },
        },
        {
            name: "han",
            path: "hd/:a1/:a2/:a3",
            component: City,
            props: true,
            meta: { isAuth: true },
        },
    ],
},
```

+ 要想给路由对象自定义属性，必须把自定义属性写在 meta 对象中。
+ 自定义的属性不写在 meta 中的话，通过路由对象是访问不到的。

访问自定义属性时：

```js
路由对象.meta.isAuth
```

### 19.12、路由守卫

保护路由安全的一种机制。一般会将鉴权代码写在路由守卫上，不同的守卫就相当于在不同的时机、不同的位置添加代码。

#### 19.12.1、全局前置守卫

全局前置守卫的的代码是配置在路由器对象中的，所以要在创建路由器之后、暴露路由器之前编写：

```js
// 创建路由器对象
const router = new VueRouter({});

// 配置路由守卫
router.beforeEach(callback)

// 导出路由器对象
export default router;
```

这个callback是一个回调函数，在初始化的时候调用一次，在以后每一次切换任意路由组件之前调用一次，这个 callback 可以是普通函数，也可以是箭头函数，他有三个参数：

```js
router.beforeEach((to, from, next) => {
    let loginame = "zs";
    if (to.meta.isAuth && loginame != "admin") alert("你没有权限访问");
    else next();
});
```

+ from：from 是一个路由对象，表示从哪个路由来
+ to：to 也是一个路由对象，表示到哪个路由去
+ next：next 是一个函数，调用这个函数过后，表示放行，可以继续往下走，不执行这个next函数，无法看见路由组件的显示

#### 19.12.2、全局后置守卫

全局后置守卫的代码也写在创建路由器对象之后，暴露路由器对象之前，它的回调函数和前置守卫一样的，只是没有next方法，会在初始化的时候调用一次，在以后每次切换完任意一个路由组件之后被调用：

```js
router.afterEach((to, from) => {	

})
```

#### 19.12.3、局部path守卫

局部路由守卫之 path 守卫的代码 beforeEnter 写在路由对象中，拥有三个同全局前置守卫的参数，在进入这个组件之前调用：

```js
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props: true,
    meta: { isAuth: true, title: "石家庄" },
    // 局部路由
    beforeEnter(to, from, next) {
        let loginame = "zs";
        if (loginame != "admin") alert("你没有权限！");
        else next();
    },
},
```

局部path守卫只有beforeEnter，没有afterEnter。

#### 19.12.4、局部component守卫

路由组件守卫，component 守卫的代码是写在组件中的，普通组件不会触发，只有路由组件（在路由中配置过的组件）才会触发：

```js
export default {
    name: "City",
    props: ["a1", "a2", "a3"],
    beforeRouteEnter(to, from, next) {
        
    },
    beforeRouteLeave(to, from, next) {
        
    },
};
```

+ beforeRouteEnter 的执行时机是：进入路由组件之前。
+ beforeRouteLeave 的执行时机是：离开路由组件之前。
+ beforeRouteEnter 中的 to 和 beforeRouteLeave 中的 from 是同一个对象
+ beforeRouteUpdate 在同一路由的参数更新时会被调用。

### 19.13、路由的两种路径模式

+ hash 模式：http://localhost:8080/#/hebei/sjz/长安区3/裕华区2/新华区2
+ history 模式：http://localhost:8080/hebei/sjz/长安区3/裕华区2/新华区2

路径中如果带有 `#` 字符，那么这个路径就是 hash 模式，默认就是 hash 模式。路径中 `#` 后面的部分称为 hash，这个 hash 不会作为路径的一部分发送给服务器。

路径中如果没有这个 `#` 就是 history 模式，在 router/index.js 中创建 router 对象的时候添加一个配置项可以设置为history模式，不设置就是hash模式：

```js
const router = new VueRouter({
    mode: "history",  // history 模式
    routes: []
})
```

在hash模式下，当前路径为：http://localhost:8080/#/hebei/sjz/长安区3/裕华区2/新华区2，刷新页面时，提交给服务器的路径只是：http://localhost:8080/。

而在history模式下，当前路径为：http://localhost:8080/hebei/sjz/长安区3/裕华区2/新华区2，刷新页面时，提交给服务器的路径是：http://localhost:8080/hebei/sjz/长安区3/裕华区2/新华区2，所以这个时候就会出现404错误。

# Vue3

## 1、vue3工程

创建vue3工程，使用vue-cli脚手架，该脚手架使用webpack打包工具打包：

```cmd
vue creat project_name
```

使用creat-vue脚手架，该脚手架使用vite打包工具打包，比webpack更快：

```
npm init vue@latest

然后要进入项目主目录执行：
npm install

运行项目的命令是：启动的端口也不是8080了
npm run dev
```

Vue3工程的main.js中，不再引入 Vue 了，引入了一个 createApp 函数，这个函数可以创建 app 对象，app对象就相当于vm实例：

```js
// 在Vue3当中，不再引入Vue了，引入了一个createApp函数，这个函数可以创建app对象。
import { createApp } from 'vue'
// 引入了一个根组件App
import App from './App.vue'

// 这行代码表示创建了一个app对象并将app挂载到指定位置，这个app对象类似于Vue2当中的vm。
// app和vm的区别是：app更加轻量级。(app上的属性更少一些)
createApp(App).mount('#app')
```

并且Vue3的`<template>`标签中可以有多个标签了，而不是只能一个根标签。

而使用create-vue脚手架构建的Vue3项目，以 index.html 作为入口，不再用 main.js 作为入口了。在 index.html 中引入了 main.js，且对于 vite 构建工具来说，配置文件是：vite.config.js（对应webpack的vue.config.js），这是vite.config.js文件配置的说明：https://cn.vitejs.dev/config/。

## 2、proxy代理

ES6新特性：window.Proxy对象，Proxy是Vue3响应式的核心。

通过 Proxy 可以创建一个代理对象，通过代理对象去完成目标对象的任务，同时还可以额外新增一些程序：

```js
let proxyObj = new Proxy(targetObj, {
    // 当你读取的时候，get执行。
    get(target, propertyName){
        return target[propertyName]
    },
    // 当你修改某个属性的时候，或者新增某个属性的时候，set执行。
    set(target, propertyName, value){
        target[propertyName] = value
    },
    // 当你删除某个属性的时候，deleteProperty就会执行
    deleteProperty(target, propertyName){
        // 要将删除的结果返回
        return delete target[propertyName]
    }
})
```

+ target 就是目标对象，
+ propertyName 就是访问的属性名，
+ value就是要赋值的值

vue3 当中在使用 Proxy 对象完成响应式处理的时候，和我们写的代码有些不同，Vue3 框架底层实际上使用了 ES6 的 Reflect 对象来完成对象属性的访问。

### 2.1、判断是否是响应式数据

提供了四个函数来判断某个数据是否具有响应式：

+ isRef：检查某个值是否为 ref。
+ isReactive：检查一个对象是否是由 reactive() 或 shallowReactive() 创建的代理。
+ isProxy：检查一个对象是否是由 reactive()、readonly()、shallowReactive() 或 shallowReadonly() 创建的代理。
+ isReadonly：检查传入的值是否为只读对象。

## 3、setup

setup 是一个函数，vue3 中新增的配置项。原先组件中所用到的 data、methods、computed、watch、生命周期钩子....等，都要配置到 setup 中。如果将这些还是配置到了 setup 外的话，表示还是使用了 vue2 的规则（可以用，不建议用）。

在 setup 函数体中定义的变量就相当于之前的 data 中的数据，在 setup 函数体中定义的方法就相当于之前的 methods 中的方法，setup 中定义的方法可以直接使用 setup 中定义的变量，但是想在模板中使用，都需要封装成一个对象返回才能用：

```vue
<template>
<h2>姓名：{{ name }}</h2>
<h2>年龄：{{ age }}</h2>
<button @click="sayHi">SAY HI</button>
</template>

<script>
    export default {
        name: "App",
        setup() {
            let name = "zhansan";
            let age = 50;
            // 在 setup 函数体中定义函数一定不能少了 function 关键字
            function sayHi() {
                alert(name,age);
            }

            return {
                name,
                age,
                sayHi,
            };
        },
    };
</script>
```

setup中没有this。

setup 函数的返回值：

+ 返回一个对象，该对象的属性、方法等均可以在模板语法中使用

+ 返回一个渲染函数，从而执行渲染函数，渲染页面

  ```js
  // 先导入一个渲染函数
  import { h } from "vue";
  
  export default {
      name: "App",
      setup() {
          // 返回的渲染函数会将 template 模板全部覆盖。
          // 渲染函数第一个参数是标签名，第二个参数是标签内容
          return function () {
              return h("h1", "hhhhhhhhh");
          };
      },
  };
  ```

但是setup中定义的数据，没有响应式。

### 3.1、语法糖

关于 setup 的语法糖：

```vue
<script setup>

</script>
```

这样就不需要写 setup 函数了，他会自动将 script 中的一级数据全部导出去，另外注册组件也只需要导入即可：

```vue
<template>
  <h2>计数器：{{counter}}</h2>
  <button @click="add">计数器加1</button>
  <hr>
  <User></User>
</template>

<script setup>
  import {ref} from 'vue'
  import User from './components/User.vue'

  // data
  let counter = ref(0)

  // methods
  function add(){
    counter.value++
  }

  // watch

  // computed

  // ....
</script>
```

## 4、ref函数

vue3 要做响应式，需要使用到 ref 函数，ref 是 vue3 内置的一个函数。

ref 函数一般用于做基本数据类型的响应式。

### 4.1、数据响应式

要先引入 ref 函数，然后使用 ref 函数创建数据，ref 对这个数据进行包裹，然后返回了一个全新的对象RefImpl对象 ：

```js
import { ref } from "vue";

export default {
    name: "App",
    setup() {
        let name = ref("张三");
        let age = ref("520");
        console.log(name);
    },
};
```

RefImpl是 reference implement，引用的实现的实例对象，或者就叫引用对象。RedImpl 对象的 value 属性是有响应式的，有对应的 set 和 get，底层使用了 Object.defineProperty 完成了响应式。当读取 RefImpl 对象的 value 属性时：get 执行；当修改 RefImpl 对象的 value 属性时：set 执行。在插值语法中，访问 RefImpl 对象时，不需要写 .value，只需要写 name 就可以了，会自动调用 value：

```vue
<template>
    <h2>姓名：{{ name }}</h2>
    <h2>年龄：{{ age }}</h2>
    <button @click="modify">modify</button>
</template>

<script>
import { ref } from "vue";

export default {
    name: "App",
    setup() {
        let name = ref("张三");
        let age = ref("520");

        function modify() {
            name.value = "李四";
            age.value = 50;
            console.log(111);
        }

        return {
            name,
            age,
            modify,
        };
    },
};
</script>
```

### 4.2、对象响应式

对象也默认没有响应式处理。使用 ref 包裹对象，此时该对象的value属性就是一个Proxy对象，那么就可以通过这个 Proxy 去访问目标对象中的属性，就有了响应式处理：

```vue
<template>
    <h2>姓名：{{ user.name }}</h2>
    <h2>年龄：{{ user.age }}</h2>
    <button @click="modify">modify</button>
</template>

<script>
import { ref } from "vue";

export default {
    name: "App",
    setup() {
        let user = ref({
            name: "zs",
            age: 12,
        });

        function modify() {
            user.value.name = "lisi";
            user.value.age = 22;
            console.log(111);
        }

        return {
            user,
            modify,
        };
    },
};
</script>
```

如果 ref 包裹的是一个基本数据类型，那么响应式就是 Object.defineProperty 实现的；

如果 ref 包裹的是一个对象，那么响应式就是 Object.defineProperty + Proxy 实现的。

+ 如果是这样修改的话，则只使用了 Object.defineProperty 机制，因为这只是改了 Proxy 对象，没有修改Proxy对象的属性，所以只走了 Object.defineProperty，修改 Proxy 中的属性式才会走 Proxy 机制。：

  ```js
  function modify() {
      user.value = {
          name : 'lisi',
          age : 23
      }
  }
  ```


Proxy 实现的响应式，对象中的对象，都有响应式处理，底层是递归处理了。

### 4.3、shallowRef

浅层次响应式，shallowRef只给基本数据类型添加响应式。如果是对象，则不会支持响应式。

对于基本数据类型来说，shallowRef 和 ref 没有区别：

```js
import { ref, shallowRef } from 'vue';
export default {
    name: "App",
    setup() {
        // let counter = ref(1);
        let counter = shallowRef(1);

        return {
            counter,
        };
    },
};
```

对于对象来说，使用 ref 是有响应式的，底层会创建 Proxy 对象；使用 shallowRef 是没有响应式的（具体来说是对象中的属性没有响应式，如果直接更换对象的话还是有响应式的），底层也不会创建 Proxy 对象，而是创建一个Object对象：

```js
let data = shallowRef({
    counter: 0,
});
```

有的时候，这个对象中的属性可能永远都不可能修改，如果要改，也是更换对象。显然这个时候可以使用 shallowRef，进行优化。更换对象这一步还是有响应式的。

## 5、reactive函数

### 5.1、对象响应式

对对象做响应式处理，一般用 reactive 函数。

因为 ref 对对象做的响应式处理是通过 Object.defineProperty + Proxy 的，麻烦；而用 reactive 函数包裹起来的对象，直接就是一个 Proxy。而 Proxy 对象中的对象都是做了响应式处理的，是递归的。

向用 reactive 包裹的对象中添加、删除属性，或通过下标操作数组都会有响应式处理，因为他是 Proxy 对象。

reactive 函数不能用于基本数据类型，专门用于对象类型的。使用 ref 包裹对象，底层也是会调用 reactive 函数的。

先引入reactive，再使用：

```js
import { reactive } from "vue";

export default {
    name: "App",
    setup() {
        let user = reactive({
            name: "zs",
            age: 12,
        });

        console.log(user);

        function modify() {
            user.name = "lisi";
            user.age = 22;
            console.log(111);
        }

        return {
            user,
            modify,
        };
    },
};
```

注意：使用reactive包裹的对象，只能修改其属性，不能直接修改对象，因为该对象是一个Proxy对象，具有响应式，如果直接修改对象的话，就变成了普通对象，不是响应式的了：

```js
let user = reactive({
    name: "zs",
    age: 12,
});
let student = {
    name: 'lisi',
    age: 12
};

user = student;  // 直接修改了对象，user将不再具有响应式
```

也不能直接赋值一个reactive包裹的对象，这样仍然不会有响应式：

```js
setup(props) {
    let article = reactive({});
    onMounted(() => {
        $.ajax({
            url: "/detail/" + props.articleId,
            type: "get",
            success(resp) {
                // 重新赋值一个reactive包裹的对象
                article = reactive(resp);
            },
        });
    });

    return {
        article,
    };
},
```

这个操作相当于给 `article` 重新赋值为一个新的响应式对象，但是 `setup` 函数返回的 `article` 的引用已经固定。Vue 组件模板依赖的是 `setup` 函数中最初返回的 `article` 引用。如果你直接替换掉 `article`，模板不会感知到这个变化，因此响应性会失效。

所以可以使用 `Object.assign` 来更新用reactive包裹的对象的属性，或者是手动修改对象的每一个属性：

```js
Object.assign(article, resp); 
```

### 5.2、shallowReactive

浅层次响应式，对象的第一层支持响应式，第二层就不再支持了。

使用 reactive 包裹一个对象时，该对象中的所有属性都是有响应式的，是递归式的；但是使用 shallowReactive 包裹一个对象时，只会给第一层做响应式：

```js
import { reactive, shallowReactive } from 'vue'
export default {
    name : 'App',
    setup(){
        let data = shallowReactive({
            counter2 : 1000,
            a : {
                b : {
                    c : {
                        counter : 1
                    }
                }
            }
        })

        return {data}
    }
}
```

以上代码中，只会有 counter2 有响应式。

## 6、props

props配置还是用来父组件向子组件传递数据，但是Vue3中的setup函数中没有this，所以使用props接受的数据时，需要将props当作setup函数的参数，通过这个参数来访问props接收的值，而在模板中，访问props接受的值还是一样直接使用变量名即可：

```js
export default {
    name: "User",
    props: ["name", "age", "sex"],
    setup(props) {
        console.log(props);
        console.log(props.name);
        console.log(props.age);
        console.log(props.sex);
    },
};
```

这份参数props也是一个Proxy对象，也具有响应式，且 props 在 setup 中不需要 return，可以直接使用（return 了也是一样的）。

这个props参数就是该组件中定义的props属性，如果没有定义props属性，不能使用该参数。

## 7、组合式API

组合式API：往 setup 函数体中配置的 data、methods、computed、watch 等这些东西，就叫做组合式 API，composition API：

```js
export default {
    name: "User",
    setup(props) {
        // 在这里配置就是组合式API
        // 如ref、reactive都属于组合式API
    },
};
```

## 8、选项式API

选项式 API：Vue2就是这样的写法，在 setup 外的对象体中配置的 data、methods、computed、watch 等这些东西，就叫做选项式 API，options API：

```js
export default {
    name: "User",
    // 在这里配置都属于选项式API
    setup(props) {
    },
};
```

### 8.1、选项式API和组合式API的区别

选项式 API 的关注点在一个一个选项上，就是一个一个的配置项上，data、computed、methods、watch 等都是一个配置项。关注点不在单独的一个功能上，比如 data 配置项中就可能放所有功能需要的数据：

```js
export default {
    name: "App",
    data() {
        return {
            // 功能1的data
            // 功能2的data
            //……
        };
    },
    methods: {
        // 功能1的method
        // 功能2的method
        //……
    },
    computed: {
        // 功能1的computed
        // 功能2的computed
        // ……
    },
    watch: {
        // 功能1的watch
        // 功能2的watch
        // ……
    },
};
```

假设以后要修改功能 1 ，那么就要对应修改 data、methods、computed、watch 中的功能 1 的代码，维护成本较高。所以说选项式 API 关注点不在功能上，在于配置项上。

组合式 API + hook(自定义钩子，后面有笔记) 的关注点在功能上，一个 hook 是一个独立的功能，一个 hook 中有自己的 data、methods、computed、watch。将一个功能写成一个 js 文件，写成一个钩子函数，想使用功能 1 的时候，直接调用，想修改功能 1，也不会牵扯到其他的功能函数。

## 9、生命周期

Vue3中的生命周期和Vue2中的差不多，但是将Vue2 中的 destroyed 和 beforeDestroy 两个钩子变成了 unmounted 和 beforeUnmount，并且在 beforeCreate 之前，就执行了 setup 函数。

在Vue3中，钩子函数的写法有两种：组合式和选项式，一般使用组合式。

选项式：

```js
export default {
    name : 'User',
    setup(){
        console.log('setup...')
    },
    // 选项式API
    beforeCreate(){
        console.log('beforeCreate')
    },
    created(){
        console.log('created')
    },
    beforeMount(){
        console.log('beforeMount')
    },
    mounted(){
        console.log('mounted')
    },
    beforeUpdate(){
        console.log('beforeUpdate')
    },
    updated(){
        console.log('updated')
    },
    beforeUnmount(){
        console.log('beforeUnmount')
    },
    unmounted(){
        console.log('unmounted')
    } 
}
```

组合式：组合式 API 的钩子函数的名称不一样了，且需要导入进来；如果是使用组合式 API 的话，生命周期钩子函数就少了两个：created、beforeCreated，因为用 setup 函数代替了这两个钩子。所以如果实在想写 created、beforeCreated 这两钩子，就用选项式 API 的方式写：

```js
import {ref, onBeforeMount, onMounted, onBeforeUpdate, onUpdated, onBeforeUnmount, onUnmounted} from 'vue'

export default {
    name : 'User',
    setup(){
        console.log('setup...')
        // 采用组合式API：生命周期钩子函数
        onBeforeMount(() => {
            console.log('onBeforeMount')    
        })

        onMounted(() => {
            console.log('onMounted')
        })

        onBeforeUpdate(() => {
            console.log('onBeforeUpdate')
        })

        onUpdated(() => {
            console.log('onUpdated')
        })

        onBeforeUnmount(() => {
            console.log('onBeforeUnmount')
        })

        onUnmounted(() => {
            console.log('onUnmounted')
        })
    },
    
    // 选项式API
    beforeCreate(){
        console.log('beforeCreate')
    },
    created(){
        console.log('created')
    },
}
```

## 10、自定义事件

自定义事件是为了组件之间的通信

+ 绑定事件方：接收数据
+ 触发事件方：发送数据

绑定事件，和Vue2中的绑定事件一样：

```vue
<template>
    <User @event1="fun1"></User>
</template>

<script>
import User from "./components/User.vue";

export default {
    name: "App",
    components: {
        User,
    },
    setup() {
        function fun1(name, age) {
            alert(name + ", " + age);
        }
        return { fun1 };
    },
};
</script>
```

那么触发事件的时候，还是使用emit来触发，因为setup中没有this，所以只能用setup函数的第二个参数context来触发事件，context 参数是组件的上下文：

```vue
<template>
    <button @click="triggerEvent">触发事件</button>
</template>

<script>
export default {
    name: "User",
    setup(props, context) {
        function triggerEvent() {
            context.emit("event1", "张三", 50);
        }

        return {
            triggerEvent,
        };
    },
};
</script>
```

## 11、全局事件总线

需要借助第三方库mitt，安装这个库：

```cmd
npm i mitt
```

通常会在src目录下新建一个utils目录，utils中新建一个event-bus.js文件：

```js
import mitt from "mitt";

export default mitt();
```

mitt 函数会返回一个 emitter 对象，所以这个 event-bus.js 就相当于导出了一个 emitter 对象，可以将这个 emitter 对象当作一个全局事件总线对象，有需要即可导入使用。

使用全局事件总线对象来绑定事件，绑定回调函数的时候，该回调函数只能接收一个参数：

```vue
<template>
    <User></User>
</template>

<script>
import { onMounted } from "vue";
import emitter from "./utils/event-bus.js";
import User from "./components/User.vue";

export default {
    name: "App",
    components: {
        User,
    },
    setup() {
        onMounted(() => {
            emitter.on("event1", user => {
                alert(user.name + ", " + user.age);
            });
        });
    },
};
</script>
```

使用全局事件总线对象来触发事件：

```vue
<template>
    <button @click="triggerEvent">触发事件</button>
</template>

<script>
import emitter from "../utils/event-bus.js";

export default {
    name: "User",
    setup(props, context) {
        function triggerEvent() {
            emitter.emit("event1", { name: "张三", age: 50 });
        }

        return {
            triggerEvent,
        };
    },
};
</script>
```

清除所有的事件：

```js
emitter.all.clear();
```

清除指定的事件：

```js
emitter.off('event1');
```

## 12、计算属性

计算属性最重要的特征是：只要计算属性关联的数据发生变化，计算属性的回调函数就会执行。所以计算属性关联的数据必须是具有响应式的。

在Vue3中，使用组合式API的计算属性，使用computed函数，函数中传递一个要关联的数据，这个数据是响应式的，最后返回一个对象，这个被返回的对象就是计算属性，也是一个具有响应式的对象：

```js
export default {
    name: "App",
    setup() {
        let data = reactive({
            name: "",
        });

        let reversedName = computed({
            get() {
                return data.name.split("").reverse().join("");
            },
            set(val) {
                console.log(666);
                data.name = val.split('').reverse().join('');
            },
        });

        return {
            data,
            reversedName,
        };
    },
};
```

计算属性如果没有set方法还可以简写：

```vue
<template>
    反转前：<input type="text" v-model="data.name" />
    <br />
    反转后：<input type="text" v-model="reversedName" />
</template>

<script>
import { computed, reactive } from "vue";

export default {
    name: "App",
    setup() {
        let data = reactive({
            name: "",
        });

        let reversedName = computed(() => {
            return data.name.split("").reverse().join("");
        });

        return {
            data,
            reversedName,
        };
    },
};
</script>
```

如果使用选项式API的方式使用computed的话，就和Vue2一样。

## 13、监视

监视的属性也一定要是具有响应式的属性，所以要用 ref 函数或 reactive 函数包裹。

使用组合式API，需要先导入watch，使用watch()函数，第一个参数是要被监视的数据，第二个参数是监视的数据发生变化要执行的函数，第三个参数是配置项,第三个参数不是必须的：

```js
watch(
    counter,
    (newVal, oldVal) => {
        console.log(newVal, oldVal);
    },
    { immediate: true, deep: true }
);
```

### 13.1、监视ref数据

ref 包裹数据生成的是 RefImpl 对象，底层采用了 Object.defineProperty 和 Proxy，这个 RefImpl 对象有一个 Value 属性，这个 Value 属性就是一个 Proxy 对象。

监视一个基本类型数据：

```js
import { ref, watch } from "vue";

export default {
    name: "App",
    setup() {
        let counter = ref(0);
        // 这里必须监视的直接是counter，因为他是具有响应式的，counter.value是没有的
        watch(counter, (newVal, oldVal) => {
            console.log(newVal, oldVal);
        });
        return { counter };
    },
};
```

如果想要监视多个数据，那就调用多次 watch：

```js
watch(
    counter,
    (newVal, oldVal) => {
        console.log(newVal, oldVal);
    },
    { immediate: true, deep: true }
);
watch(
    counter2,
    (newVal, oldVal) => {
        console.log(newVal, oldVal);
    },
    { immediate: true, deep: true }
);
```

如果在监视多个数据时，需要处理的逻辑是一样的，就可以使用数组的形式一次性监视多个属性，不需要写多次 watch：

```js
watch([counter, counter2], (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

而这样的话，参数newVal和oldVal也变成了数组形式，对应着被监视的数组新值和旧值。

ref 包裹一个对象时：

```js
let data = ref({
    counter: 1
});
watch(data.value, (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

这个是可以的，data 的 value 是一个 Proxy 对象，所以可以直接监视的，但是依旧拿不到 oldVal，且默认开启深度监视不能关闭。

但是如果只监视 data 对象的话：

```js
let data = ref({
    counter: 1
});
watch(data, (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

会先发现现在监视不到 counter 的变化了，这说明 RefImpl 对象默认没有开启深度监视，且它是支持 deep 配置的。

### 13.2、监视reactive数据

reactive 包裹生成的是 Proxy 对象。

对于 reactive 获取的代理对象来说，默认就是开启深度侦听的，并且这种深度侦听是无法取消的，配置 deep:false 也不行；而且对于 reactive 获取的代理对象，在进行侦听的时候，只能获取 newVal，oldVal 获取不到：

```js
import { reactive, ref, watch } from "vue";

export default {
    name: "App",
    setup() {
        let data = reactive({
            counter: 0,
            a: {
                b: {
                    c: {
                        d: {
                            counter2: 0,
                        },
                    },
                },
            },
        });

        watch(data, (newVal, oldVal) => {
            console.log(newVal, oldVal);
        });

        return {
            data,
        };
    },
};
```

如果不想有深度监视的效果，不想监视所有的属性，那么watch的第一个参数只需要写希望被监视的数据，但是要保证这个数据是具有响应式的，如果是对象内的基本数据类型，那么可以使用函数的方式：

```js
watch(
    () => data.counter,  // 要监听的属性
    (newVal, oldVal) => {  // 监听执行的函数
        console.log(newVal, oldVal);
    }
);

watch(
    data.a.b,  // 要监听的属性，b是一个对象，是有响应式的，因为reactive是递归的
    (newVal, oldVal) => {  // 监听执行的函数
        console.log(newVal, oldVal);
    }
);
```

如果想要同时监视 多个数据的话，使用数组形式，数组中的数据还是要保证都是具有响应式的：

```js
watch([() => data.counter, () => data.a.b.c.d.counter2], (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

第一个参数使用函数返回的形式的话，可以使用 deep 配置来关闭默认的深度监视：

```js
watch(
    () => data.a.b,
    (newVal, oldVal) => {
        console.log(newVal, oldVal);
    },
    { deep: false }
);
```

总结：

+ 只要监视的是对象，都拿不到 oldVal，只能拿到 newVal；监视的是基本数据类型，可以拿到 oldVal。
+ 要想监视基本数据类型，只能使用函数返回的形式写，因为要求是个响应式对象。
+ 使用函数返回的形式返回一个对象，监视该对象可以关闭默认的深度监视。

### 13.3、watchEffect

这也是一个用来监视的组合式API，这个 watchEffect 函数中直接跟一个回调函数即可，他会在初始的时候和监视的数据发生变化时自动调用。它会会监听它的回调函数中使用过的所有属性：

```js
import { reactive, watchEffect } from "vue";

export default {
    name: "App",
    setup() {
        let data = reactive({
            counter1: 0,
            counter2: 100,
            counter3: 1000,
        });

        // 监视data.counter1, data.counter3这两个属性
        watchEffect(() => {
            console.log(data.counter1, data.counter3);
        });

        return {
            data,
        };
    },
};
```

## 14、自定义钩子

hook 函数，hook 翻译为 钩子，用的时候把他勾出来使用。和 Vue2 的混入 mixin 差不多，都是为了代码的复用。

一般会将钩子放在一个目录中，所以在 src 下新建一个目录 hooks，在 hooks 下新建一个文件，文件名一般就为功能名，比如定义一个求和的钩子，sum.js：

```js
import { reactive } from "vue";
export default function () {
    let data = reactive({
        num1: 0,
        num2: 0,
        res: 0,
    });

    function sum() {
        data.res = data.num1 + data.num2;
    }

    return {
        data,
        sum,
    };
}
```

使用钩子：

```js
// 导入钩子
import sum from "./hooks/sum";

export default {
    name: "App",
    setup() {
        // 使用钩子
        let res = sum();
        // 返回对象
        return {
            ...res,
        };
        
        // 或直接返回
        // return sum();
    },
};
```

## 15、深只读与浅只读

其它组件传递过来的数据，如果不希望你修改，你最好加上只读，以防以后不小心改了人家的数据。

深只读：readonly，具有响应式的对象中的所有的属性，包括子对象中的子对象中的属性，所有的值都是不能修改的。

浅只读：shallowReadonly，具有响应式的对象中的第一层属性是只读的，其他层属性是可修改的。

需要引入这两个函数：

```js
import { readonly, shallowReadonly } from "vue";
```

使用这两个函数，参数必须是有响应式的数据：

```js
import { reactive, readonly, shallowReadonly } from "vue";

export default {
    name: "App",
    setup() {
        let data = {
            counter1: 0,
            a: {
                b: {
                    c: {
                        counter2: 100,
                    },
                },
            },
        };

        // 深只读
        data = readonly(data)
        
        // 浅只读
        // data = shallowReadonly(data)

        return { data };
    },
};
```

## 16、toRef和toRefs

以下代码中，模板语法中，引用变量的代码太长、太冗余：

```vue
<template>
    <h2>计数器：{{ data.counter1 }}</h2>
    <button @click="data.counter1++">点我加1</button>
    <hr />
    <h2>计数器：{{ data.counter2 }}</h2>
    <button @click="data.counter2++">点我加1</button>
    <hr />
    <h2>计数器：{{ data.a.b.counter3 }}</h2>
    <button @click="data.a.b.counter3++">点我加1</button>
</template>

<script>
import { reactive } from "vue";
export default {
    name: "App",
    setup() {
        let data = reactive({
            counter1: 1,
            counter2: 100,
            a: {
                b: {
                    counter3: 1000,
                },
            },
        });

        return { data };
    },
};
</script>
```

所以可以使用 toRef 或 toRefs 将具体的数据给到某个变量上，比如将 data.a.b.counter3 给到一个新的变量 cnt3 上，然后就可以直接使用cnt3来访问数据。

### 16.1、toRef

通过 toRef 将目标对象中的属性转换成一个 ObejctRefImpl 对象，该对象是一个引用对象，具有相应式，然后将该对象赋值给一个变量再 return 出去，在模板语法中就可以使用这个变量，当访问或修改这个变量时，就会执行 ObjectRefImpl 对象中的 get 和 set 方法，从而修改到目标对象的属性。

所以可以使用 toRef ：`toRef(对象, '该对象中的属性名')`，将一个对象中的某个属性 转化成一个具有响应式的对象，这样在模板中使用时就只需要写新的对象名即可：

```vue
<template>
    <h2>计数器：{{ counter1 }}</h2>
    <button @click="counter1++">点我加1</button>
    <hr />
    <h2>计数器：{{ counter2 }}</h2>
    <button @click="counter2++">点我加1</button>
    <hr />
    <h2>计数器：{{ counter3 }}</h2>
    <button @click="counter3++">点我加1</button>
</template>

<script>
import { reactive, toRef } from "vue";
export default {
    name: "App",
    setup() {
        let data = reactive({
            counter1: 1,
            counter2: 100,
            a: {
                b: {
                    counter3: 1000,
                },
            },
        });

        return {
            counter1: toRef(data, "counter1"),
            counter2: toRef(data, "counter2"),
            counter3: toRef(data.a.b, "counter3"),
        };
    },
};
</script>
```

### 16.2、toRefs

toRefs 可以将一个对象的一级属性的书写省略掉，但是要注意使用扩展运算符将 toRefs 生成的对象中的属性解析出来：

```vue
<template>
    <h2>{{ data }}</h2>
    <h2></h2>
    <h2>计数器：{{ counter1 }}</h2>
    <button @click="counter1++">点我加1</button>
    <hr />
    <h2>计数器：{{ counter2 }}</h2>
    <button @click="counter2++">点我加1</button>
    <hr />
    <h2>计数器：{{ a.b.counter3 }}</h2>
    <button @click="a.b.counter3++">点我加1</button>
</template>

<script>
import { reactive, toRefs } from "vue";
export default {
    name: "App",
    setup() {
        let data = reactive({
            counter1: 1,
            counter2: 100,
            a: {
                b: {
                    counter3: 1000,
                },
            },
        });

        return {
            ...toRefs(data),
        };
    },
};
</script>
```

## 17、toRaw和markRow

toRaw：转换为原始，将响应式对象转换为普通对象。只适用于 reactive 生成的响应式对象。

markRaw：标记为原始，标记某个对象，让这个对象永远都不具备响应式。比如在集成一些第三方库的时候，比如有一个巨大的只读列表，不让其具备响应式是一种性能优化。

用法：

```js
let 原始对象 = toRaw(具有响应式的对象)
data.x = markRaw({
    counter2: 100,
});
```

## 18、Fragment组件

Vue3 新增的组件。fragment 翻译为：碎片。片段。

在 Vue2 中每个组件必须有一个根标签。这样性能方面稍微有点问题，如果每一个组件必须有根标签，组件嵌套组件的时候，有很多无用的根标签。

在 Vue3 中每个组件不需要有根标签。实际上内部实现的时候，最终将所有组件嵌套好之后，最外层会添加一个 Fragment，用这个 fragment 当做根标签。这是一种性能优化策略。

## 19、Teleport组件

teleport 翻译为：远距离传送。用于设置组件的显示位置，teleport标签中的元素，会被显示到teleport标签指定的位置，teleport 的 to 后可以使用选择器来指定元素：

```vue
<teleport to='body'>
    <!-- 遮罩层，一会整个遮罩层要瞬移到body下面 -->
    <div v-show="isShow" class="cover">
        <!-- 模态窗口 -->
        <div class="s">
            我是一个窗口.....
            <button @click="isShow = false">关闭</button>
        </div>
    </div>
</teleport>
```

+ 这个div会被显示到body标签的下面

## 20、provide和inject

Vue3 提供了两个函数专门来完成祖宗组件给后代组件传递数据，用来完成组件之间数据的传递，组件之间的通信：

+ provide
+ inject

在祖宗组件中使用 provide 提供数据，在后代组件中使用 inject 完成数据的注入。

provide 语法：

```js
provide('名字', 数据)
```

inject 语法：

```js
inject('名字')
```

祖宗组件中的写法：

```vue
<script>
    import {provide, ref} from 'vue'
    import ErZi from './ErZi.vue'
    export default {
        name : 'YeYe',
        components : {ErZi},
        setup(){
            let counter = ref(1)
            
            // 在祖宗组件中使用provide提供数据
            provide('c', counter)

            return {counter}
        }
    }
</script>
```

后代组件中的写法：

```vue
<script>
    import {ref, inject} from 'vue'
    export default {
        name : 'SunZi',
        setup(){
            // data
            let isShow = ref(false)
            // 注入inject
            let counter = inject('c')
            // 返回一个对象
            return {isShow, counter}
        }
    }
</script>
```

## 21、延迟显示

实现：在一个文本框中输入数据，一秒后再显示这个数据。

### 21.1、watch实现

```vue
<template>
  <input type="text" v-model="name">
  <br><br>
  {{newName}}
</template>

<script>
  import {ref, watch} from 'vue'
  export default {
    name : 'App',
    setup(){
      // data
      let name = ref('')
      let newName = ref(name.value)
      // 侦听属性
      watch(name, (newValue, oldValue) => {
        setTimeout(() => {
          newName.value = newValue
        }, 300)
      })
      // 返回一个对象
      return {name, newName}
    }
  }
</script>
```

### 21.2、自定义ref实现

官方教程：https://cn.vuejs.org/api/reactivity-advanced.html#customref

ref 是一个函数，像这种函数是可以程序员自定义的，自定义的 ref 也具有响应式。

自定义 ref 也是调用 Vue 提供的 API 接口来自定义，只需要照着模板写

```vue
<script>
import { ref, customRef } from "vue";
export default {
    name: "App",
    setup() {
        // 使用Vue3内置的ref
        //let name = ref('test')

        // 创建一个防抖 ref
        // 以下这个代码就是真正的属于自己定义的ref了。
        // ref是一个函数，那么我们自定义的ref同样是一个函数。
        function useDebouncedRef(value) {
            let t;
            // 自定义的ref这个函数体当中的代码不能随便写，必须符合ref规范。
            // 通过调用customRef函数来获取一个自定义的ref对象。
            // 调用customRef函数的时候必须给该函数传递一个回调：这个回调可以叫做factory
            // 对于这个回调函数来说，有两个非常重要的参数：track是追踪。trigger是触发。
            const x = customRef((track, trigger) => {
                // 对于这个factory回调来说，必须返回一个对象，并且对象中要有get
                return {
                    // 模板语句中只要使用到该数据，get会自动调用。
                    get() {
                        console.log("get执行了");
                        // 告诉Vue去追踪这个value的变化
                        track();
                        return value;
                    },
                    // 当模板语句中修改该数据的时候，set会自动调用。
                    set(newValue) {
                        console.log("set执行了", newValue);
                        clearTimeout(t);
                        t = setTimeout(() => {
                            value = newValue;
                            // 触发(通知去调用get方法)
                            trigger();
                        }, 1000);
                    },
                };
            });

            // 返回自定义的ref对象实例。
            return x;
        }

        // 使用自定义的ref同样具备响应式。
        let name = useDebouncedRef("test");

        // 返回一个对象
        return { name };
    },
};
</script>
```



