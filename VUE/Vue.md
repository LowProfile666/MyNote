> Vue 是一个基于 JavaScript（JS）实现的框架

# Vue 初体验

Vue 读音类似 View（视图），Vue 是一个视图框架，用于展示。

## 下载与安装 Vue2

Vue 框架就是一个 js 文件，从 [Vue2官网](https://v2.cn.vuejs.org/) 下载 vue.js 文件：

![image-20240419194034669](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404191940744.png)

在 Vue2 的主页中，注意 学习 中的 教程 和 API 两个菜单，学习 Vue 需要用到。

点击主页中的 起步，会跳转到 教程 界面中去，点击 安装 菜单：

![image-20240419194156224](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404191941298.png)

+ Vue Devtools：一个浏览器插件，开发者工具，更方便调试 Vue 程序
+ 开发版本：vue.js，体积更大
+ 生产版本：vue.min.js，体积更小

下载好了之后，安装 Vue 就是通过 `<script>` 标签将 vue.js 文件引入即可：

```html
<script src="../js/vue.js"></script>
```

+ 当使用 script 进行 Vue 安装之后，上下文中就注册了一个全局变量：Vue（相当于引入 jQuery 后多了一个 `$` 全局变量）

运行这个引入了 vue.js 的 html 页面后，这个 Vue 全局变量可以在浏览器中控制台中查看：

![image-20240419194542180](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404191945210.png)

## 第一个vue程序

```html
<div id="app"></div>
<script>
    var myVue = new Vue({
        template: '<h1>hello world</h1>'
    });
    myVue.$mount('#app');
</script>
```

运行结果：

![image-20240419194735706](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404191947731.png)

代码解释：

第一步：**创建Vue实例**

**1、为什么要new Vue()，直接调用Vue()函数不行吗？**

不行，因为直接调用 Vue() 函数，不创建实例的话，会出现以下错误：

```html
vue.js:5129 [Vue warn]: Vue is a constructor and should be called with the `new` keyword
```

![image-20240419194941349](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404191949383.png)

可以看出，Vue 这个全局变量是一个构造方法，需要一个参数 options。

**2、关于Vue构造函数的参数：options？**

Vue 框架要求这个 options 参数必须是一个纯粹的 JS 对象：`{}`，在 `{}` 对象中可以编写大量的 `key:value` 对。

一个 `key:value` 对就是一个配置项。

通过 options 这个参数来给 Vue 实例指定多个配置项。

**3、关于template配置项？**

 template 翻译为：模板。template 配置项用来指定**模板语句**，模板语句是一个字符串形式的。

**4、什么是模板语句？**

Vue 的模板语句是 Vue 框架自己搞的一套语法规则。Vue 框架自己制定了一些具有特殊含义的特殊符号。

模板语句可以是一个纯粹的 HTML 代码，也可以是 Vue 中的特殊规则。也可以是 HTML 代码 + Vue 的特殊规则。

运行时，template 后面的模板语句会被 Vue 框架的编译器进行编译，转换成浏览器能够识别的 HTML 代码。

第二步：**挂载**

**1、Vue实例都有一个$mount()方法，这个方法的作用是什么？**

将 Vue 实例挂载到指定位置。`myVue.$mount('#app')` 就是将 myVue 这个实例挂载到 id 为 app 的元素上。这里的 `#app` 是一个 id 选择器，和 css 中的选择器一样的写法，也可以使用以下写法：

```js
myVue.$mount(document.getElementById('app'));
```

**2、为什么要挂载？**

Vue 实例创建出来时，是在内存中漂泊，如果想展示该 Vue 实例，需要将实例挂载到页面中的某个位置，才能显示出该实例。

这就是指定一个挂载位置：

```html
<div id="app"></div>
```

然后挂载：

```js
myVue.$mount('#app');
```

## 模板语句的数据来源

模板语句的数据来源是另一个配置项 `data`，专业叫法：Vue 实例的数据对象（data实际上是给整个Vue实例提供数据来源的。）

```html
<div id="app"></div>
<script>
    var myVue = new Vue({
        template: '<h1>姓名：{{name}}，年龄：{{age}}</h1>',
        data: {
            name: "zsm",
            age: 18
        }
    });
    myVue.$mount('#app');
</script>
```

**1、data选项的类型是什么？**

data 配置项的值是一个 `Obejct` （对象）或者 `function`（函数）。

如果 data 是对象的话，对象必须是纯粹的对象 (含有零个或多个的 key/value 对)。

**2、data数据如何插入到模板语句当中？**

template 指定的模板语句是可以动态显示数据的，就是将 data 中的值通过特定的语法写在 template 中，然后显示在页面上。

`{{}}` 这是 Vue 框架自己搞的一套语法，别的框架看不懂的，浏览器也是不能够识别的。这种语法在 Vue 框架中被称为：模板语法中的**插值语法**。（有的人把他叫做胡子语法。）

**3、怎么使用插值语法？**

`{{ }}` 中间写的是 data 中对象的 key。

细节：`{{` 和 `}}` 中间不能有空格或其他字符，例如不能这样：`{  {name}}、{{name}  }、{aaa{name}da}`

**4、data的值**

data 配置项的值的类型不是固定的，可以是任意的合法的 js 的类型：

```js
new Vue({
    // 这里换行可以使用 + 号连接字符串，也可以直接使用飘号 ``
    template : `<h1>最近非常火爆的电视剧{{name}}，它的上映日期是{{releaseTime}}。主角是{{lead.name}}，年龄是{{lead.age}}岁。
                其他演员包括：{{actors[0].name}}({{actors[0].age}}岁)，{{actors[1].name}}({{actors[1].age}}岁)。{{a.b.c.d.e.name}}
                </h1>`,
    data : {
        name : '狂飙!!!',
        releaseTime : '2023年1月2日',
        lead : {
            name : '高启强',
            age : 41
        },
        actors : [
            {
                name : '安欣',
                age : 41
            },
            {
                name : '高启兰',
                age : 29
            }
        ],
        a : {
            b : {
                c : {
                    d : {
                        e : {
                            name : '呵呵'
                        }
                    }
                }
            }
        }
    }
}).$mount('#app')
```

以上程序执行原理：Vue 编译器对 template 进行编译，遇到胡子 `{{}}` 时从 data 中取数据，然后将取到的数据插到对应的位置。生成一段 HTML 代码，最终将 HTML 渲染到挂载位置，呈现。

**当 data 发生改变时，template 模板会被重新编译，重新渲染。**

## template详解

**1、template中只能有一个根节点**

template 后面指定的是模板语句，但是模板语句中只能有一个根节点。比如，下面的写法会报错：

```js
var myVue = new Vue({
    template: '<h1>hello world</h1><h1>zzzzssm</h1>'
});
myVue.$mount('#app');
```

![image-20240419201540534](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404192015582.png)

所以可以将模板语句这样写：

```js
var myVue = new Vue({
    template: '<div><h1>hello world</h1><h1>zzzzssm</h1></div>'
});
myVue.$mount('#app');
```

**2、只要data中的数据发生变化，模板语句一定会重新编译**

**3、如果使用template配置项的话，指定挂载位置的元素会被替换**

假如指定的挂载位置是：

```html
<div id="app">1234</div>
```

那么挂载后，该 `div` 中的内容都会被替换掉，该 `div` 的作用就是起一个占位符的作用。

**4、template可以直接写在html中**

目前我们可以不使用 template 来编写模板语句。这些模板语句可以直接写到 html 标签中。Vue 框架能够找到并编译，然后渲染。

比如：

```html
<div id="app">
    <div>
        <h1>{{msg}}</h1>
        <h1>{{name}}</h1>
    </div>
</div>
```

这样就不需要使用 template 配置项了，只要提供了 data 数据即可，Vue 框架能够找到并编译，然后渲染。

如果像这样直接将模板语句编写到 HTML 标签中，指定的挂载位置就不会被替换了。

**5、使用el自动挂载**

使用 `el` 配置项，可以达到 `$mount()` 同样的效果。就是告诉 Vue 实例去接管哪个容器：

```js
new Vue({
    data : {
        msg : 'Hello Vue!!!!!!!',
        name : 'ssss!!!!!!'
    },
    el : '#app'
    //el : document.getElementById('app')
})
```

`el : '#app'` 就表示让 Vue 实例去接管 id 为 app 的容器，将实例挂载到这个元素上。

el 其实是 element 的缩写，被翻译为元素。

## 解决控制台上的提示信息

![image-20240419202911013](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404192029067.png)

第一条提示：

```
下载 Vue Devtools 扩展以获得更好的开发体验：
https://github.com/vuejs/vue-devtools
```

+ 安装了 Vue Devtools 插件后就不会有该提示了

第二条提示：生产提示信息

```
您正在开发模式下运行 Vue。
确保在部署生产时打开生产模式。
```

+ 因为该 html 文件引入的是开发模式的 vue.js，如果是生产环境下，建议引入 vue.min.js。

+ 引入了 vue.min.js 后，vue 框架就会认为进入了生产环境，就不会再有该提示。

+ 手动去掉该提示：

  + 打开 Vue2 的官方 API 文档，找到 “全局配置”，`Vue.config` 对象

    ![image-20240419203534608](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404192035708.png)

  + 修改 Vue.config 对象中的 productionTip 属性为 false，即可关闭该提示信息：

    ![image-20240419203649837](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404192036898.png)

    ```js
    Vue.config.productionTip = false
    ```

  + 该方法可能不会起效，可能和浏览器等有关。那么如何彻底解决？在 vue.js 源码中搜索到 productionTip 这个属性，将值改为 false。

## Vue开发者工具

安装了 Vue Devtools 后，在浏览器的开发者工具中就会有一个 vue 面板：

![image-20240420083637855](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200836906.png)

+ 左侧第一栏：显示 app
+ 第二栏：显示 app 下的组件，每个 app 下可有多个组件，root 是根组件
+ 第三栏：显示组件下的数据，可以更改，改了后，页面会重新渲染

小问题：data 中的数据如果全部以中文字符开头，可能会出现 vue devtools 工具不能正常显示的问题：

```js
data : {
    msg : '的Hello Vue!!!!!!!',
    name : '顶顶顶顶顶!!!!!!'
},
```

![image-20240420084114800](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200841862.png)

这样的情况下，跟组件选择不了，如果 data 中有一个数据不是以中文开头的就可以：

![image-20240420084211817](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200842878.png)

## Vue实例和容器

Vue实例 和 容器 的关系是：一夫一妻制。

一个 Vue 实例只能接管一个容器；一个容器只能被一个 Vue 实例接管。

比如，一个 Vue 实例接管相同类名的两个容器：

```html
<!-- 准备容器 -->
<div class="app">
    <h1>{{msg}}</h1>
</div>

<div class="app">	
    <h1>{{msg}}</h1>
</div>
<script>
    new Vue({
        el : '.app',
        data : {
            msg : 'Hello Vue!'
        }
    })
</script>
```

![image-20240420084710422](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200847744.png)

可以看到，这个 Vue 实例只接管了第一个类名为 app 的容器。一旦接管到容器之后，即使后面有相同的容器，Vue 也是不管的。

再比如：一个容器被两个 Vue 实例接管：

```html
<!-- 准备容器 -->
<div id="app2">
    <h1>{{name}}</h1>
</div>
<script>
    new Vue({
        el : '#app2',
        data : {
            name : 'zhangsan'
        }
    })
    new Vue({
        el : '#app2',
        data : {
            name : 'jackson'
        }
    })
</script>
```

![image-20240420085250544](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200852614.png)

+ 此时页面上显示的是第一个 Vue 实例的数据，但是开发者工具中却只有第二个 Vue 实例，说明第一个 Vue 实例被覆盖掉了，但是数据已经渲染了（猜的）

---

# Vue 核心技术

## 模板语法

### 插值语法

模板语法中的插值语法 `{{ }}`。

在 `{{ }}` 可以写四种东西。

**1、在data中声明的变量、函数等**

可以将在 data 中声明的键值对看成是一个变量，key 是变量名，value 是变量值：

```html
<!-- 准备容器 -->
<div id="app">
    <!-- 在data中声明的 -->
    <!-- 这里就可以看做在使用msg变量。 -->
    <h1>{{msg}}</h1>
    <h1>{{sayHello()}}</h1>
</div>

<script>
new Vue({
    el : '#app',
    data : {
        msg : 'abcdef',  // 把msg叫做变量。（这行代码就可以看做是变量的声明。）
        sayHello : function(){
            console.log('hello vue!');
        }
    }
})
</script>
```

注意：不在 data 中定义的变量或函数无法使用，比如这个 i ：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <h1>{{sayHello()}}</h1>
    <h1>{{i}}</h1>
</div>

<script>
    var i = 1;
    new Vue({
        el : '#app',
        data : {
            msg : 'abcdef',  
            sayHello : function(){
                console.log('hello vue!');
            }
        }
    })
</script>
```

会报错：

![image-20240420090307583](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200903655.png)

**2、常量**

该常量指固定不变的字面量、字面值。比如 `var i = 10;` 中等号左边的是变量，右边的是常量。

```html
<h1>{{100}}</h1>
<h1>{{'hello vue!'}}</h1>
<h1>{{3.14}}</h1>
```

以上写法是可以的：

![image-20240420090720441](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200907519.png)

但是这个常量不能是代码中通过 `const` 关键字定义的常量：

```html
<h1>{{a}}</h1>

<script>
	const a = 'aaa';
</script>
```

![image-20240420090815810](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200908881.png)

**3、合法的javascript表达式**

```html
<h1>{{1 + 1}}</h1>
<h1>{{'hello' + 'vue'}}</h1>
<h1>{{msg + 1}}</h1>
<h1>{{'msg' + 1}}</h1>
<h1>{{gender ? '男' : '女'}}</h1>
<h1>{{number + 1}}</h1>
<h1>{{'number' + 1}}</h1>
<h1>{{msg.split('').reverse().join('')}}</h1>

<script>
	new Vue({
        el : '#app',
        data : {
            number : 1,
            gender : true,
            msg : 'abcdef',  
            sayHello : function(){
                console.log('hello vue!');
            }
        }
    })
</script>
```

注意：在 `{{ }}` 中写 js 语句是不会生效的，比如：

```html
<h1>{{ var a = 1 }}</h1>
<h1>{{ if (ok) { return message } }}</h1>
```

**4、白名单变量**

模板表达式都被放在沙盒中，只能访问[全局变量的一个白名单](https://github.com/vuejs/vue/blob/v2.6.10/src/core/instance/proxy.js#L9)，如 `Math` 和 `Date` 等。链接跳转到的地方是：

![image-20240420091643201](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200916278.png)

说明以下这些都是白名单中的内容：

```html
'Infinity,undefined,NaN,isFinite,isNaN,'
'parseFloat,parseInt,decodeURI,decodeURIComponent,encodeURI,encodeURIComponent,'
'Math,Number,Date,Array,Object,Boolean,String,RegExp,Map,Set,JSON,Intl,'
'require'
```

那么就可以直接使用：

```html
<h1>{{Date}}</h1>
<h1>{{Date.now()}}</h1>
<h1>{{Math}}</h1>
<h1>{{Math.ceil(3.14)}}</h1>
```

![image-20240420091832326](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200918416.png)

### 指令语法

**1、什么是指令？有什么作用？**

指令的职责是，当表达式的值改变时，将其产生的连带影响，响应式地作用于 DOM。

**2、Vue 框架中的所有指令的名字都以 “v-” 开始**

比如 `v-if` 。

**3、指令写在哪里呢？**

插值 `{{ }}` 是写在标签体当中的，指令 `v-` 是写在标签上的，以属性的形式存在：

```html
<span 指令是写在这里的>{{这里是插值语法的位置}}</span>
```

注意：虽然指令是写在标签的属性位置上，但是这个指令浏览器是无法直接看懂的。是需要先让 Vue 框架进行编译的，编译之后的内容浏览器是可以看懂的。

**4、指令语法**

指令的一个完整的语法格式：

```html
<HTML标签 v-指令名:参数="javascript表达式"></HTML标签>
```

+ `v-指令名:参数="javascript表达式"` 这一串就是一个完整的指令写法
+ 参数是属于指令的参数，参数不是必须的，有的指令不需要参数
+ 表达式：之前在插值语法中 `{{这里可以写什么}}`，那么指令中的表达式就可以写什么。实际上是一样的。但是需要注意的是：**在指令中的表达式位置不能外层再添加一个 `{{ }}`**

不是所有的指令都有参数和表达式。

+ 有的指令，不需要参数，也不需要表达式，例如：`v-once`
+ 有的指令，不需要参数，但是需要表达式，例如：`v-if="表达式"`
+ 有的指令，既需要参数，又需要表达式，例如：`v-bind:参数="表达式"`

#### v-once

作用：只渲染元素一次。随后的重新渲染，元素及其所有的子节点将被视为静态内容并跳过。这可以用于优化更新性能。

```html
<h1>{{msg}}</h1>
<h1 v-once>{{msg}}</h1>
```

当 data 中的 msg 发生了改变后，以上两个 `h1` 标签只会更新第一个，因为第二个使用了 `v-once` 指令，只会熏染一次，相当于变成了一个静态的元素，只有重新刷新页面才会重新渲染。

#### v-if="表达式"

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

#### v-bind

**1、这个指令是干啥的？**

它是一个负责动态绑定的指令，它可以让HTML标签的某个属性的值产生动态的效果。

**2、语法格式**

```html
<HTML标签 v-bind:参数="表达式"></HTML标签>
```

**3、v-bind指令的编译原理？**

编译前：

```html
<HTML标签 v-bind:参数="表达式"></HTML标签>
```

编译后：将参数名转换为标签的属性名，表达式的执行结果转换为属性的值

```	html
<HTML标签 参数="表达式的执行结果"></HTML标签>
```

比如：

```html
<div id="app">
    <img v-bind:src="path" >
</div>

<script>
	new Vue({
        el: "#app",
        data: {
            path: "pppppp"
        }
    })
</script>
```

此时这个图片标签的 src 属性就是 data 中定义的 path 变量，是一个变量的值了，不再是一个写死的路径。

而在页面上，这个元素是被转换成这样的：

![image-20240420095152765](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404200951859.png)

如果是这样写：

```html
<img v-bind:src="'path'" >
```

那么这个 'path' 就是一个常量，最终的 html 标签是这样：

![image-20240420100205021](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201002116.png)

注意两项：

+ 第一：在编译的时候 v-bind 后面的“参数名”会被编译为 HTML 标签的“属性名”
  + 这个参数名可以随便写，但是还是需要写成该HTML标签支持的属性名。这样才会有意义
+ 第二：表达式会关联 data，当 data 发生改变之后，表达式的执行结果就会发生变化。
+ 所以，连带的就会产生动态效果。

**4、简写方式**

v-bind 因为很常用，所以 Vue 框架对该指令提供了一种简写方式，比如：

```html
<img :src="imgPath">
```

**5、应用示例**

动态绑定文本输入框的值：

```html
<div id="app">
    <!-- 这是一个普通的文本框 -->
    <input type="text" name="username" value="zhangsan"> <br>
    <!-- 以下文本框可以让value这个数据变成动态的：这个就是典型的动态数据绑定。 -->
    <input type="text" name="username" :value="username"> <br>
</div>

<script>
	new Vue({
        el : '#app',
        data : {    
            username : 'jackson',
        }
    })
</script>
```

动态绑定超链接的地址：

```html
<div id="app">
   <!-- 使用v-bind也可以让超链接的地址动态 -->
    <a href="https://www.baidu.com">走起</a> <br>
    <a :href="url">走起2</a> <br>
</div>

<script>
	new Vue({
        el : '#app',
        data : {    
            url : 'https://www.baidu.com',
        }
    })
</script>
```

不能有这种写法：

```html
<div id="app">
    <a href="{{url}}">走起</a> <br>
</div>
```

会报错：

![image-20240420104817148](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201049670.png)

属性内部插值这种语法已经被移除了。（可能Vue在以前的版本中是支持这种写法的，但是现在不允许了。）

请使用v-bind或冒号速记来代替。

请使用 `<div :id="val">` 来代替 `<div id="{{ val }}">`。

**5、什么时候使用插值语法？什么时候使用指令？**

凡是标签体当中的内容要想动态，需要使用插值语法。

只要想让HTML标签的属性动态，需要使用指令语法。

#### v-model

`v-model` 和 `v-bind` 差不多，可以完成数据的绑定。

**1、v-bind和v-model的区别和联系**

`v-bind` 是单向数据绑定。data \=\=\=> 视图；`v-model` 是双向数据绑定。data <\=\=\=> 视图

```html
<div id="app">
    v-bind指令：<input type="text" v-bind:value="name1"><br>
    v-model指令：<input type="text" v-model:value="name2"><br>
</div>

<script>
    new Vue({
        el : '#app',
        data : {
            name1 : 'zhangsan',
            name2 : 'wangwu',
        }
    })
</script>
```

![image-20240420110105548](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201101672.png)

+ 单向数据绑定：修改了 data 后，视图中的显示会变化。
+ 双向数据绑定：修改了 data 后，视图中的显示会变化；修改了视图中的数据后，datat 中的数据也会变化。
+ 比如，将 data 中的 name1 和 name2 都修改了的话，页面上输入框的值也会发生变化；但是将第一个文本框中的数据修改后，data 中的 name1 不会发生变化；将第二个输入框中的数据修改后，data 中的 name2 也会被修改。

`v-bind` 可以使用在任何 HTML 标签当中。`v-model` 只能使用在表单类元素上。例如：input 标签、select 标签、textarea 标签。

+ 因为表单类的元素才能给用户提供交互输入的界面。元素的值才会发生改变，才有双向绑定的意义。

+ 如果使用在非表单元素上会报错：

  ```html
   <a v-model:href="url">百度</a>
  ```

  ![image-20240420110745524](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201107666.png)

`v-model` 指令通常也是用在 value 属性上面的。

`v-bind` 和 `v-model` 都有简写方式：

+ `v-bind:参数="表达式" `  简写为   ` :参数="表达式"`
+ `v-model:value="表达式"`  简写为   `v-model="表达式"`

```html
消息1：<input type="text" :value="msg"><br>
消息2：<input type="text" v-model="msg"><br>
```

## MVVM分层思想

![MVVM分层思想-Vue框架的实现](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201114655.png)

**1、MVVM是什么？**

M：Model（模型/数据）

V：View（视图）

VM：ViewModel（视图模型）：VM 是 MVVM 中的核心部分。（它起到一个核心的非常重要的作用。）

MVVM 是目前前端开发领域当中非常流行的开发思想。(一种架构模式。)。目前前端的大部分主流框架都实现了这个 MVVM 思想，例如 Vue，React 等。

**2、Vue框架遵循MVVM吗？**

虽然没有完全遵循 MVVM 模型，但是 Vue 的设计也受到了它的启发。Vue 框架基本上也是符合 MVVM 思想的。

**3、MVVM模型当中倡导了Model和View进行了分离，为什么要分离？**

假如 Model 和 View 不分离，使用最原始的原生的 javascript 代码写项目：如果数据发生任意的改动，接下来我们需要编写大篇幅的操作 DOM 元素的 JS 代码。

将 Model 和 View 分离之后，出现了一个 VM 核心，这个 VM 把所有的脏活累活给做了，也就是说，当 Model 发生改变之后，VM 自动去更新 View。当 View 发生改动之后，VM 自动去更新 Model。我们再也不需要编写操作DOM 的 JS 代码了。开发效率提高了很多。

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

![image-20240420112204459](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201122583.png)

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

## vscode生成代码片段

像上面创建一个 Vue 实例的代码片段一般是固定的，没必要每次都去手写，可以使用 vscode 自动生成。

在 vscode 左下角，点开齿轮图标，选择用户代码片段（User Snippets），

![image-20240420112733580](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201127698.png)

会弹出搜索框，直接搜索 JavaScript，

![image-20240420112757454](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201127565.png)

回车，会打开一个 json 文件：

![image-20240420112837498](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201128625.png)

在这个文件当中就可以配置代码片段，比如默认中的一个例子：

```json
"Print to console": {
    "prefix": "log",
    "body": [
        "console.log('$1');",
        "$2"
    ],
    "description": "Log output to console"
},
```

+ "Print to console"：这是提示信息
+ "prefix"：前缀，或者说简写。只要敲完这个简写指定的字符 log，就会出现 "Print to console" 这个提示信息，回车之后就会生成 "body" 中指定的代码模板。
+ "body"：配置代码片段。
  + body 中的部分是一个数组，数组之间的元素使用逗号隔开。一般情况下，一个元素就是一行代码
  + body 中的 `$1` 和 `$2` 是用来做光标定位的，`$1` 表示生成这个代码片段后，输入光标会被定位在哪里；`$2` 是当光标在 `$1` 位置时，按下 tab 键后，光标所在的位置。
+ "description"：描述信息，可以删除不要。

所以此时在 vscode 中输入 log：

![image-20240420113332773](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201133893.png)

所以可以给生成 Vue 实例的代码片段配置一下：

```json
"create vue instance": {
    "prefix": "cvm",
    "body": [
        "const vm = new Vue({",
        "    el: '$1',",
        "    data: {",
        "		$2",
        "    }",
        "})"
    ]
},
```

此时输入 cvm：

![image-20240420113918731](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201139856.png)

还可以安装一个插件：JavaScript (ES6) code snippets，自带了很多的常用代码片段

![image-20240420114024075](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201140208.png)

比如生成箭头函数：anfn

![image-20240420114112276](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404201141394.png)

## 认识vm

在 Vue 中，MVVM 分层中的 vm 就是 Vue 实例。通过 Vue 实例都可以访问哪些属性？

Vue 实例中的属性很多，有的以 `$` 开始，有的以 `_` 开始。

+ 所有以 `$` 开始的属性，可以看做是公开的属性，这些属性是供程序员使用的。
+ 所有以 `_` 开始的属性，可以看做是私有的属性，这些属性是 Vue 框架底层使用的。一般我们程序员很少使用。

在代码中创建一个 Vue 实例，然后在浏览器的控制台中输出：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg: "hello"
    }
})
```

![image-20240421084846607](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210849137.png)

这些都是 Vue 实例 vm 中的属性，都可以通过 `vm.` 访问到。通过 vm 也可以访问 Vue 实例对象的原型对象 Prototype 上的属性 。

还有在 data 中定义的 msg 属性，也可以直接使用 vm 访问：

```js
console.log(vm.msg);
```

**有个疑问**：在上图中可以看到 vm 中有个 msg 属性，但是 msg 属性是 data 对象里面的，为什么 vm 中会有？而且在图中显示的是`msg:(...)` ，只有点击了这三个点才能看到 msg 的值，为什么 msg 属性可以通过 vm 来访问呢？

这是因为 Vue 框架底层使用了数据代理机制。要想搞明白数据代理机制，必须有一个基础知识点要学会：Object.defineProperty()。

## Object.defineProperty()

这个方法是 ES5 新增的。

这个方法的作用是：**给对象新增属性，或者设置对象原有的属性。**

使用格式：

```js
Object.defineProperty(给哪个对象新增属性, '新增的这个属性名叫啥', {给新增的属性设置相关的配置项key:value对})
```

第三个参数是属性相关的配置项，配置项都有哪些？每个配置项的作用是啥？

+ value 配置项：给属性指定值
+ writable 配置项：设置该属性的值是否可以被修改。true 表示可以修改。false 表示不能修改。
+ getter方法 配置项：不需要我们手动调用的。当读取属性值的时候，getter 方法被自动调用。
  + getter 方法的返回值非常重要，这个返回值就代表这个属性它的值。
+ setter方法 配置项：不需要我们手动调用的。当修改属性值的时候，setter 方法被自动调用。
  + setter 方法上是有一个参数的，这个参数可以接收传过来的值。
+ **注意：当配置项当中有 setter 和 getter 的时候，value 和 writable 配置项都不能存在。**

比如现在有个对象 phone，给他新增一个 color 属性：

```js
// 这是一个普通的对象
let phone = {}

// 给上面的phone对象新增一个color属性
Object.defineProperty(phone, 'color', {
    value: '太空灰'
}
```

然后可以访问到这个 color 属性：

![image-20240421090515399](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210905462.png)

此时在控制台中修改 color 属性的值，发现不会修改成功：

![image-20240421090604457](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210906517.png)

因为还有一个配置项 writable 设置该属性是否可以被修改，设为 true 时就说明可以被修改：

```js
// 这是一个普通的对象
let phone = {}

// 给上面的phone对象新增一个color属性
Object.defineProperty(phone, 'color', {
    value: '太空灰',
    writable: true,
}
```

![image-20240421090805978](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210908042.png)

还有 getter 和 setter 方法配置项，这两个方法自动调用，不需要手动调用

+ 在读取属性值时调用 getter
+ 在修改属性值时调用 setter

getter setter 和 value writable 同时存在，也就是不能这么写：

```js
Object.defineProperty(phone, 'color', {
    value : '太空灰',
    writable : true,
    // getter方法配置项
    get: function () {
       
    },
    // setter方法配置项
    set: function () {
       
    }
})
```

会报错：

![image-20240421091131590](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210911654.png)

将 value 和 writable 注释掉后，就可以了：

```js
Object.defineProperty(phone, 'color', {
    get: function () {
        console.log('getter方法执行了@@@');
    },
    set: function () {
        console.log('setter方法执行了@@@');
    }
})
```

此时访问和修改 phone.color：

![image-20240421091753612](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210917682.png)

set 方法应该是有参数的，可以测试一下：

```js
Object.defineProperty(phone, 'color', {
    get: function () {
        console.log('getter方法执行了@@@');
    },
    set: function (a, b, c, d) {
        console.log('setter方法执行了@@@', a, b, c, d);
    }
})
```

![image-20240421091903603](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210919670.png)

显然，给属性赋值的时候，值就是第一个参数。所以 setter 方法的参数一般叫做 val：

```js
Object.defineProperty(phone, 'color', {
    get: function () {
        
    },
    set: function (val) {
        
    }
})
```

但是此时访问属性的时候，拿到的值是 undefined，这是因为 get 方法并没有返回值，所以需要给 get 方法设置返回值，返回该属性的值。

注意，不能这样写，这样会产生递归：

```js
Object.defineProperty(phone, 'color', {
    get: function () {
        console.log('getter方法执行了@@@');
        return this.color;
    },
    set: function (val) {
        console.log('setter方法执行了@@@', val);
        this.color = a;
    }
})
```

此时当访问 phone.color 时，会调用 get 方法，get 方法中的 this.color 又会访问 get 方法，最终就会一直递归：

![image-20240421092423013](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210924108.png)

修改 phone.color 时也会递归，也是一直调用 get 方法。

为了避免这种情况，需要使用一个临时变量：

```js
let temp;
Object.defineProperty(phone, 'color', {
    get: function () {
        console.log('getter方法执行了@@@');
        return temp;
    },
    set: function (val) {
        console.log('setter方法执行了@@@', val);
        temp = val;
    }
})
```

![image-20240421092824186](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210928273.png)

## 数据代理机制

### 原理

**1、什么是数据代理机制？**

通过访问 代理对象的属性 来间接访问 目标对象的属性。

数据代理机制的实现需要依靠：Object.defineProperty() 方法。

此时我有两个对象：

```js
// 目标对象
let target = {
    name : 'zhangsan'
}

// 代理对象
let proxy = {}
```

如果要实现数据代理机制的话，也就是说我要使用代理对象 proxy 的属性去访问目标对象 target 的 name 属性的话，就需要给 proxy 新增一个 name 属性。

+ 注意：代理对象新增的这个属性的名字 和 目标对象的属性名要一致。
+ 因为：为了达到这种效果：访问代理对象的属性时，就像在访问目标对象的属性

```js
Object.defineProperty(proxy, 'name', {
    get : function(){
        // 间接访问目标对象的属性
        return target.name;
    },
    set : function(val){
        target.name = val;
    }
})
```

此时，访问和修改 proxy 对象的 name 属性时，都是操作的 target 对象的 name 属性：

![image-20240421093642485](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210936565.png)

那么此时，就能理解为什么 Vue 实例 vm 中会有 msg 属性，就相当于：

```js
let target = {
    msg : 'hello world'
}

const vm = new Vue({
    el : '#app',
    data : target
})
```

就是 Vue 实例会做一个数据代理，访问 vm.msg 时会间接的去访问目标对象 data 的 msg，这就达到了一个效果：感觉 data 中的属性设置到了 vm 上。

此时在浏览器控制台中输出 proxy，可以看到他有个属性 name，name 后面是 (...)，这种形式就一定是数据代理机制：

![image-20240421094446487](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404210944569.png)

当点击 name 后的三点后，他才会去动态的调用 get 方法，get 方法才会执行。

**2、在对象中的函数/方法 :function 是可以省略的。**

这是 ES6 的新特性。在对象中的函数可以直接这样写：

```js
Object.defineProperty(proxy, 'name', {
    // get : function(){
    //     // 间接访问目标对象的属性
    //     return target.name
    // },
    // set : function(val){
    //     target.name = val
    // }

    get(){
        return target.name
    },
    set(val){
        target.name = val
    }
})
```

### 属性名的要求

Vue 实例中的属性很多，有的以 `$` 开始，有的以 `_` 开始。

+ 所有以 `$` 开始的属性，可以看做是公开的属性，这些属性是供程序员使用的。
+ 所有以 `_` 开始的属性，可以看做是私有的属性，这些属性是 Vue 框架底层使用的。一般我们程序员很少使用。

**1、Vue实例不会给以_和$开始的属性名做数据代理。**

如果允许给 `_` 或 `$` 开始的属性名做数据代理的话，vm 这个 Vue 实例上可能会出现 _xxx 或 $xxx 属性，而这个属性名可能会和 Vue 框架自身的属性名冲突。

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : 'Hello Vue!',
        _name : 'zhangsan',
        $age : 20
    }
})
```

在以上代码中，data 对象中有 3 个属性，其中 `_name` 和 `$age` 是以下划线和美元符号开头，`msg` 是普通写法，那么在控制台中访问一下：

![image-20240421103612908](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211036001.png)

发现通过 vm 只能访问到 msg 属性了，其他两个访问不到。能访问到 msg 说明 Vue 做了数据代理的；访问不到 `_name` 和 `$age` 说明没有给这两个属性做数据代理。

因为如果给以 `_` 或 `$` 开头的属性做了数据代理，那么程序员可能会起一个根 Vue 实例中原有的属性冲突的属性名，这样的话就会影响到原来 Vue 实例中的值。

**2、在Vue当中，给data对象的属性名命名的时候，不能以_或$开始。**

程序不会报错，但是不能使用 Vue 实例访问到该属性，就相当于没有意义。

### 手写数据代理

这是一个普通的 Vue 程序：

```html
<!-- 容器 -->
<div id="app">
	<h1>{{msg}}</h1>
</div>

<!-- Vue代码 -->
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Hello Vue!',
            name : 'jackson',
            age : 30
        }
    })
</script>
```

手写数据代理机制的最终效果就是，能够通过 vm 访问这个 data 中的 msg。

新建一个 js 文件：myvue.js，然后在项目中安装自己的 js：

```html
<script src="../js/myvue.js"></script> 
```

首先，在创建 Vue 实例的时候，需要一个 Vue 类，所以先创建一个 Vue 类和它的构造函数：

```js
class Vue {
    constructor(options) {
        Object.keys(options.data).forEach((propertyName, index) => {
            console.log(propertyName, index);
        })
    }
}
```

+ options：是一个简单的纯粹的JS对象：{}，作为构造函数的参数，
+ options 对象中有一个 data 配置项，也是一个对象，获取 data 对象的所有属性，分别给每个属性做数据代理
+ Object.keys(options.data)：获取 options.data 中所有的属性名

那么创建 Vue 实例时这样创建：

```js
const vm = new Vue({
    data : {
        msg : 'Hello Vue!',
        name : 'jackson',
        age : 30
    }
})
```

+ 上面的 options 就是这一部分：

  ```js
  {
      data : {
          msg : 'Hello Vue!',
          name : 'jackson',
          age : 30
      }
  }
  ```

此时查看页面控制台：

![image-20240421105635275](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211056373.png)

拿到所有的属性名了后，就可以使用 Object.defineProperty() 来做数据代理：

```js
class Vue {
    constructor(options) {
        Object.keys(options.data).forEach((propertyName, index) => {
            Object.defineProperty(this, propertyName, {
                get() {
                    return options.data[propertyName];
                },
                set(val) {
                    options.data[propertyName] = val;
                }
            })
        })
    }
}
```

+ options.data 就是目标对象

此时就可以访问了：

![image-20240421110310510](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211103618.png)

那么当属性名以 `_` 和 `$` 开头时，不做数据代理，此时就需要做一个判断：

```js
class Vue {
    constructor(options) {
        Object.keys(options.data).forEach((propertyName, index) => {
            let c = propertyName.charAt(0);
            if (c != '_' && c != '$') {
                Object.defineProperty(this, propertyName, {
                    get() {
                        return options.data[propertyName];
                    },
                    set(val) {
                        options.data[propertyName] = val;
                    }
                })
            }      
        })
    }
}
```

此时当我们的 data 中有美元符号和下划线开头的属性时，就不会做数据代理：

```js
const vm = new Vue({
    data : {
        msg : 'Hello Vue!',
        _name : 'jackson',
        $age : 30
    }
})
```

![image-20240421110734027](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211107135.png)

### 解读Vue框架源代码

主要研究 Vue 中的数据代理实现部分。

当前有个页面：

```html
<!-- 容器 -->
<div id="app">
    <h1>姓名：{{name}}</h1>
    <h1>年龄：{{age}}岁</h1>
</div>

<!-- vue代码 -->
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            name : 'jackson',
            age : 35
        }
    })
</script>
```

在浏览器的开发者工具中，点击“源代码”，找到 vue.js，或者也可以直接在 vscode 中查看源代码：

![image-20240421111149537](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211111654.png)

从 Vue 的构造函数中入手，直接在源代码中搜索 `Vue(` ，定位到：

![image-20240421111442326](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211114460.png)

在 5774 行打了一个断点，这一行表示正常情况下会执行的代码，然后刷新，程序回到这个断点这里停下来：

![image-20240421111607500](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211116642.png)

此时点击调试工具中的 Step into，就会进入到 `_init` 函数：

![image-20240421111710260](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211117377.png)

+ 这个 options 就是创建 Vue 实例时传过来的对象

然后在 4701 行打个断点，使用调试工具中的 Resume 达到这个断点：

![image-20240421112125928](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211121102.png)

+ 4701 这一行的代码主要作用是合并 options 到 $options 属性中
+ 并且此时可以看到 vm 中的属性还很少，说明在创建 Vue 实例 vm 的过程中，会不断的给 vm 添加属性

接着在 4714 行打上断点，走到这个断点上来：

![image-20240421112327863](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211123007.png)

这个 initState 是初始化阶段，进入这个函数看看：

![image-20240421112450060](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211124202.png)

这里面最重要的是 initData 函数，初始化数据，数据代理就是在这里面进行的，进入这个 initData 函数：

![image-20240421112704499](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211127630.png)

+ 4391 行：

  ```js
  var data = vm.$options.data;
  ```

  这里 $options 包含了我们创建 Vue 实例时传过来的对象，这个 data 就是我们传过来的对象中的 data。

  注意：这是获取 data。程序执行到这里的时候 vm 上还没有 _data 属性。

+ 4392 行：

  ```js
  data = vm._data = isFunction(data) ? getData(data, vm) : data || {};
  ```

  观察这行代码，他是在判断 data 是否是一个函数，

  + 如果 data 是函数，则调用 getData(data, vm) 来获取 data。
  + 如果 data 不是函数，则直接将 data 返回，给 data 变量。并且同时将 data 赋值给 vm._data 属性了。

  + 这说明创建 Vue 实例的时候，data 不仅可以是一个对象，还可以是一个函数。

  程序执行完这个代码之后，vm 对象上多了一个 _data 这样的属性。

  ![image-20240421113109250](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211131385.png)

  **1、程序执行到这里，为什么要给 vm 扩展一个 _data 属性呢？**

  `_data`属性，以"_"开始，足以说明，这个属性是人家 Vue 框架底层需要访问的。

  **2、Vue框架底层它使用vm._data这个属性干啥呢？**

  `vm._data` 就是创建 Vue 实例时传过去的参数对象：

  ![image-20240421114016429](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211140553.png)

  `vm._data` 这个属性直接指向了底层真实的 data 对象。通过 `_data` 访问的 name 和 age 是不会走数据代理机制的。也就是说，通过 `vm._data` 方式获取 name 和 age 的时候，是不会走 getter 和 setter 方法的。

  注意：对于 Vue 实例 vm 来说，不仅有 _data 这个属性，还有一个 $data 这个属性。

  + _data 是框架内部使用的，可以看做私有的。
  + $data 这是 Vue 框架对外公开的一个属性，是给我们程序员使用。
  + 如果我们程序员不想走代理的方式读取 data，想直接读取 data 当中的数据，可以通过 _data 和 $data 属性来访问,建议使用\$data 这个属性。

+ 4399 行：获取 data 所有的属性名

+ 4404 行：遍历每个属性名

+ 4414 行：

  ```js
  else if (!isReserved(key)) {
  ```

  进入这个 isReserved() 函数中：

  ```js
  function isReserved(str) {
      var c = (str + '').charCodeAt(0);
      return c === 0x24 || c === 0x5f;
  }
  ```

  这个函数是用来判断字符串是否以 _ 和 $ 开始的。

  + true 表示以 _ 或 $ 开始的。
  + false 表示不是以 _ 或 $ 开始的。

+ 4415 行：

  ```js
  proxy(vm, "_data", key);
  ```

  + 这个 key 是当前循环的属性名

  通过这行代码直接进入代理机制（数据代理）。

  ```js
  var sharedPropertyDefinition = {
      enumerable: true,
      configurable: true,
      get: noop,
      set: noop
  };
  function proxy(target, sourceKey, key) {
      sharedPropertyDefinition.get = function proxyGetter() {
          return this[sourceKey][key];
      };
      sharedPropertyDefinition.set = function proxySetter(val) {
          this[sourceKey][key] = val;
      };
      Object.defineProperty(target, key, sharedPropertyDefinition);
  }
  ```

  这行代码走过之后，vm 中就有一个数据代理的属性了。

总结：

+ 创建 Vue 实例时，data 对象中的属性会被做数据代理（属性名不以 _ 和 $ 开头）；
+ Vue 实例中有属性 `_data` 和 `$data`，这两个对象完全一样的，都是创建 Vue 实例时传过去的 data 对象；
+ 通过  `_data` 和 `$data` 可以访问到 data 对象中的属性，且不会走数据代理，程序员一般使用 `$data` 对象

### 关于配置项：enumerable、configurable

该配置项在这里出现过：

![image-20240421143440897](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211434036.png)

enumerable：

+ true：表示该属性是可以遍历的。（可枚举的，可迭代的。）
+ false：表示该属性是不可遍历的。

```js
let phone = {
    name: '苹果X'
}

// 给phone对象新增一个color属性
Object.defineProperty(phone, 'color', {
    value: '奶奶灰',
    enumerable: true,
})
```

此时，在控制台中可以遍历 phone 的属性：

![image-20240421143826409](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211438539.png)

当 enumerable 为 false 的时候，就是不可遍历的：

![image-20240421143911207](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211439338.png)

configurable：

+ true：表示该属性是可以被删除的。

  ![image-20240421144049234](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211440365.png)

+ false：表示该属性是不可以被删除的。

  ![image-20240421144120483](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211441615.png)

## data可以是个函数

在创建 Vue 实例时，一般给 data 配置项设置的是一个对象，

```js
const vm = new Vue({
    el: '#app',
    data : {
        msg : 'Hello Vue!'
    }
})
```

但是也可以是函数：

```js
const vm = new Vue({
    el: '#app',
    data : function() {
        
    }
})
```

此时控制台会报错：

![image-20240421143002350](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211430493.png)

说明 data 如果是函数的话，必须使用 return 语句返回 {} 对象。

```js
const vm = new Vue({
    el: '#app',
    // data : function(){
    //     return {
    //         msg : 'Hello Vue!'
    //     }
    // }

    // 在对象当中，函数的 :function 可以省略
    data() {
        return {
            msg: 'Hello Zhangsan!'
        }
    }
})
```

**什么时候使用对象？什么时候使用函数？**等学到组件就知道了。

## Vue的事件绑定

### 如何bang'ding

使用 javascript 原生代码如何完成事件绑定：

```html
<button onclick="alert('hello')">hello</button>
```

使用 Vue 来完成事件绑定，需要借助一个指令：`v-on`。

+ 复习，指令的语法格式：

  ```html
  <标签 v-指令名:参数名="表达式">{{插值语法}}</标签>
  ```

`v-on` 的语法格式：`v-on:事件名="表达式"`，例如：

+ `v-on:click="表达式"` 表示当发生鼠标单击事件之后，执行表达式。
+ `v-on:keydown="表达式"` 表示当发生键盘按下事件之后，执行表达式。

**1、在Vue当中，所有事件所关联的回调函数，需要在Vue实例的配置项methods中进行定义。**

使用 Vue 的指令绑定事件，不能像原生 js 那样：

```html
<button v-on:click="alert('hello')">hello</button>
```

当点击按钮后，控制台会报错：

![image-20240421153259740](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211535701.png)

所以在 Vue 当中，所有事件所关联的回调函数，需要在 Vue 实例的配置项 methods 中进行定义。

methods 是一个对象：{}，在这个 methods 对象中可以定义多个回调函数：

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

然后这样使用：

```html
<button v-on:click="sayHello()">hello</button>
```

点击时就会触发这个函数。

**2、简写**

```html
<button @click="sayHello()">hello</button>
```

v-on 指令也有简写形式：

+ `v-on:click` 简写为 `@click`
+ `v-on:keydown` 简写为 `@keydown`
+ `v-on:mouseover` 简写为 `@mouseover`

**3、绑定的回调函数，如果函数调用时不需要传递任何参数，小括号()可以省略。**

```html
<button v-on:click="sayHello">hello</button>
```

**4、Vue在调用回调函数的时候，会自动给回调函数传递一个对象，这个对象是：当前发生的事件对象。**

在 sayHello 方法上加一个参数：

```html
<button v-on:click="sayHello">hello</button>

<script>
    const vm = new Vue({
        methods: {
            sayHello(event) {
                console.log(e);
            },
        }
    })
</script>
```

这时点击该按钮后，查看控制台，会输出一个事件：

![image-20240421154826922](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211548083.png)

拿到了该事件对象后，可以进行一些操作：

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

注意：当省略了小括号后，调回调函数的时候，才会传一个对象过去，会把当前的事件以对象的形式传过去 ，也就是说，如果要使用 event 对象的话，调用该函数时就不能加上小括号，否则会拿不到这个 event 事件：

```html
<button v-on:click="sayHello()">hello</button>
```

此时控制台的输出是 undefined。

**5、在绑定回调函数的时候，可以在回调函数的参数上使用 \$event 占位符，Vue框架看到这个 $event 占位符之后，会自动将当前事件以对象的形式传过去。**

```html
<button v-on:click="sayHello($event, 'zsm')">hello</button>
```

这个 $event 就是占位符。Vue 会将事件对象传到 \$event 占位符所在的位置。

```js
const vm = new Vue({
    methods: {
        sayHello(event, name) {
            console.log(event, name);
        },
    }
})
```

![image-20240421155745391](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404211557538.png)

占位符的位置可以在参数列表中随意。

### 事件中回调函数的this

 在这个回调函数中，使用 this 的话，这个 this 代表的是谁。

实现一个功能，显示一个数字和一个按钮，点击按钮一次，数字就加一。

直接绑定事件为表达式：

```html
 <!-- 容器 -->
<div id="app">
    <h1>计数器：{{counter}}</h1>
    <button @click="counter++">点击我加1</button>
</div>
<!-- vue代码 -->
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            counter : 0
        }
    });
</script>
```

绑定事件为函数：

```html
 <!-- 容器 -->
<div id="app">
    <h1>计数器：{{counter}}</h1>
    <button @click="add">点击我加1</button>
    <button @click="add2">点击我加1（箭头函数）</button>
</div>
<!-- vue代码 -->
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            counter : 0
        },
        methods : {
            add(){
                
            },
        }
    });
</script>
```

那么如何在 add 方法中访问 counter 变量呢？先研究一下 Vue 实例 vm 和 add 方法中的 this 的关系：

```js
add(){
	console.log(vm === this);
},
```

结果是 true，说明 add 方法中的 this 就是 Vue 实例。所以想要访问 counter 变量，就可以使用数据代理的方式，使用 this 或 vm 直接访问：

```js
add(){
	this.coutner++;
    // vm.counter++;
},
```

+ 不能直接这样写：

  ```js
  add(){
  	counter++;
  },
  ```

  这会报错，因为 counter 是 data 对象中的，在 add 方法中访问不到。

**如何回调函数是箭头函数呢？**

```js
add : () => {
	this.counter++;
},
```

这样写了后，点击按钮，计数器 counter 并没有变化，这说明箭头函数中的 this 和普通函数中的 this 不一样。

输出一下箭头函数中的 this：

![image-20240422142417903](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404221424081.png)

这是因为：==箭头函数中没有 this，箭头函数中的 this 是从父级作用域中继承过来的==。那么对于当前程序来说，父级作用域就是全局作用域 window。

### methods的实现原理

**1、methods对象中的方法可以通过vm去访问吗？**

可以。

在 methods 中定义一个函数，在浏览器控制台中使用 vm 去访问试一下：

```js
methods : {
    sayHi(){
        alert('hi...')
    }
}
```

![image-20240422142751411](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404221427584.png)

**2、methods对象中的方法有没有做数据代理呢？**

没有。

直接输出 vm 可以看到：

![image-20240422142958682](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404221429863.png)

只有 data 中的数据才做了数据代理，methods 中的方法不会做数据代理。

**为什么methods中的方法可以给vm用？**

打开之前手写的 myvue.js：

```js
class Vue {
    constructor(options) {
        Object.keys(options.data).forEach((propertyName, index) => {
            let c = propertyName.charAt(0);
            if (c != '_' && c != '$') {
                Object.defineProperty(this, propertyName, {
                    get() {
                        return options.data[propertyName];
                    },
                    set(val) {
                        options.data[propertyName] = val;
                    }
                })
            }      
        })
    }
}
```

这只是对数据代理的实现原理的模仿，模仿的是 data。那么还可以模仿下 methods 的原理：

```js
// 获取并遍历所有的方法名
Object.keys(options.methods).forEach((methodName, index) => {
    // 给当前的Vue实例扩展一个方法
    this[methodName] = options.methods[methodName];
});
```



![image-20240422143819724](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404221438901.png)

### 事件修饰符

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

**1、阻止默认行为**

比如，现在有一个超链接，链接到一个网址，想点击链接后执行一个 js 回调函数。正常情况下，点击后，执行了回调函数后，会执行超链接的默认行为，跳转到目标网站中，而现在要阻止这个默认行为。

```html
<div id="app">
    <h1>{{msg}}</h1>
    <a href="https://www.baidu.com" @click="yi">百度</a>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '事件修饰符'
        },
        methods : {
            yi(){
                alert(1)
            },
        }
    })
</script>
```

以上代码点击链接后，会弹出一个提示框，关闭提示框后，就会跳转到百度的页面，就是会执行超链接的默认行为。那么要阻止这个行为。

使用 js 代码，手动调用事件对象的 preventDefault() 方法，可以阻止事件的默认行为。：

```js
yi(event){
    event.preventDefault();
    alert(1)
},
```

在 Vue 当中，这种事件的默认行为可以不采用手动调用 DOM 的方式来完成，可以使用事件修饰符 `:prevent`:

```html
<a href="https://www.baidu.com" @click.prevent="yi">百度</a>
```

**2、停止事件冒泡**

事件冒泡的意思就是，最内层的事件发生后，会向上传递，一直到根节点的事件发生：

```html
<div @click="san">
    <div @click="er">
        <button @click="yi">冒泡事件</button>
    </div>
</div>
```

点击按钮后，会触发按钮的点击事件，函数 yi() 执行，然后向上冒泡，第二层的 div 的点击函数 er() 也会被执行，再向上冒泡，第一层 div 的点击函数 san()  也会被执行，最后还有往外冒……

使用 `.stop` 修饰符，表示该事件不会向上冒泡：

```html
<div @click="san">
    <div @click="er">
        <button @click.stop="yi">冒泡事件</button>
    </div>
</div>
```

这样，点击按钮后，就只会执行到 yi() 函数，不会执行 er() 函数。

**3、添加事件监听器时使用事件捕获模式**

先给谁添加事件监听器，谁就先执行。

添加事件监听器包括两种不同的方式：

+ 一种是从内到外添加。（事件冒泡模式，默认）
+ 一种是从外到内添加。（事件捕获模式）

```html
<div @click.capture="san">
    <div @click.capture="er">
        <button @click.capture="yi">添加事件监听器的时候采用事件捕获模式</button>
    </div>
</div>
```

此时点击按钮，先执行的是 san() 函数，再执行 er() 函数，最后执行 yi() 函数。

```html
<div @click.capture="san">
    <!-- 这里没有添加.capture修饰符，以下这个元素，以及这个元素的子元素，都会默认采用冒泡模式。 -->
    <div @click="er">
        <button @click="yi">添加事件监听器的时候采用事件捕获模式</button>
    </div>
</div>
```

此时第一层的 div 添加事件监听器是事件捕获模式，第二层 div 和按钮是冒泡模式，所以这时候点击按钮，会先执行 san() 函数，在执行 yi() 函数，最后执行 er() 函数。

**4、.self修饰符**

`.self` ：这个事件如果是“我自己元素”上发生的事件，这个事件不是别人给我传递过来的事件，则执行对应的程序。

```html
<div @click="san">
    <div @click="er">
        <button @click.self="yi">self修饰符</button>
    </div>
</div>
```

此时，点击按钮后，会触发该按钮本身上有的点击事件 yi()，然后想上冒泡，触发 er() 和 san()。

将 `.self` 换个位置：

```html
<div @click="san">
    <div @click.self="er">
        <button @click="yi">self修饰符</button>
    </div>
</div>
```

此时，点击按钮后，按钮的 yi() 会执行，然后冒泡到第二层的 div 上，但是该事件不是第二层 div 的本身的事件，所以不会执行 er() 函数，但是事件会继续向上冒，san() 函数会被执行。

**5、事件只发生一次**

```html
<button @click="yi">事件只发生一次</button>
```

此时这个按钮，点击几次，执行几次。

```html
<button @click.once="yi">事件只发生一次</button>
```

此时这个按钮，第一次点击会执行 yi() 函数，以后点击都不会执行。

**6、.passive修饰符**

无需等待，直接继续（立即）执行事件的默认行为。

准备几个元素：

```html
<style>
    .divList{
        width: 300px;
        height: 200px;
        background-color: aquamarine;
        overflow: auto;
    }
    .item{
        width: 300px;
        height: 200px;
    }
</style>

<div class="divList">
    <div class="item">div1</div>
    <div class="item">div2</div>
    <div class="item">div3</div>
</div>
```

此时的效果是这样的：

![image-20240422152907352](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404221529553.png)

当鼠标在该区域滚动的时候，会触发默认的 wheel 事件，这个 wheel 事件就是滚动条滚动。那么给 最外层的 div 绑定一个 wheel 事件：

```html
<div class="divList" @wheel.passive="testPassive">
    <div class="item">div1</div>
    <div class="item">div2</div>
    <div class="item">div3</div>
</div>

<script>
    const vm = new Vue({
        el : '#app',
        methods : {
            testPassive(){
                console.log('test passive')
            }
        }
    })
</script>
```

此时每滚动一次鼠标的中轮，就会输出一句 test passive。此时将该默认事件阻止：

```js
testPassive(){
    console.log('test passive');
    event.preventDefault()
}
```

现在每滚动一次，滚动条不会再滚动了，但是输出还会输出。

此时使用 `.passive` 修饰符来解除阻止默认行为的操作：

```html
<div class="divList" @wheel.passive="testPassive">
    <div class="item">div1</div>
    <div class="item">div2</div>
    <div class="item">div3</div>
</div>
```

此时默认行为滚动条滚动已经解除了，但是滚动一次就会报错：

![image-20240422153529628](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404221535828.png)

所以 `.passive` 和 `.prevent` 修饰符是对立的。不可以共存。（如果一起用，就会报错。）

那么 `.passive` 用在什么时候？将 testPassive 方法改变一下：

```js
testPassive(event){
    for(let i = 0; i < 100000; i++){
        console.log('test passive')
    }
}
```

然后先不使用修饰符：

```html
<div class="divList" @wheel="testPassive">
    <div class="item">div1</div>
    <div class="item">div2</div>
    <div class="item">div3</div>
</div>
```

此时，滚动一次滑轮，就会执行一次 100000 次的循环，然后才会执行默认行为，滚动条才会滚动。

使用了修饰符后：

```html
<div class="divList" @wheel.passive="testPassive">
    <div class="item">div1</div>
    <div class="item">div2</div>
    <div class="item">div3</div>
</div>
```

滚动滑轮，滚动条正常滚动，而这个 100000 次的循环也在正常运行。

**7、联合使用事件修饰符**

在 Vue 当中，事件修饰符是可以多个联合使用的。

```html
<div @click="san">
    <div @click="er">
        <button @click.self.stop="yi">self修饰符</button>
    </div>
</div>
```

但是需要注意：

+ `@click.self.stop`：先 .self，再 .stop
+ `@click.stop.self`：先 .stop，再 .self

### 按键修饰符

9 个比较常用的按键修饰符：

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

这些按键修饰符的使用方法都差不多。

**0、按回车后获取输入的值**

比如，现有一个文本框，绑定一个按键触发事件，当输入回车后，控制台打印出输入的内容：

```html
<input type="text" @keyup="getInfo"><br>

<script>
    const vm = new Vue({
        el: '#app',
        methods: {
            getInfo(event) {
                if(event.keyCode === 13){
                	console.log(event.target.value)
                }
            }
        }
    })
</script>
```

+ 事件对象中有按下的键的值 keyCode
+ 事件对象中的 target 就是事件发生在哪的元素

此时输入内容后按下回车就会在控制台中输出输入的内容。

那么此时不想写 if 语句判断是不是回车键，就可以使用按键修饰符 `.enter`：

```html
<input type="text" @keyup.enter="getInfo"><br>
```

此时，只要发生 keyup 事件，并且是由 enter 键触发的事件，就会执行 getInfo() 函数。

这个修饰符也可以写键值：

```html
<input type="text" @keyup.13="getInfo"><br>
```

**1、怎么获取某个键的按键修饰符？**

第一步：通过 `event.key` 获取这个键的真实名字。

第二步：将这个真实名字以 kebab-case 风格进行命名。

比如 PageDown 是真实名字。经过命名之后：page-down 就是按键的修饰符。
```html
<input type="text" @keyup.page-down="getInfo"><br>
```

**2、按键修饰符是可以自定义的？**

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

**3、系统修饰键**

4 个比较特殊的键。

+ ctrl
+ alt
+ shift
+ meta（win键）

对于 keydown 事件来说：只要按下系统修饰键，keydown 事件就会触发。

对于 keyup 事件来说：需要按下系统修饰键，并且加上按下组合键，然后松开组合键之后，keyup 事件才能触发。

**4、限制组合键**

```html
<input type="text" @keyup.ctrl.i="getInfo"><br>
```

这种方式限制了只能按下 ctrl+i 才会触发事件

## 计算属性



