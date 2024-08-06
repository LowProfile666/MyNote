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



## 2、语法

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

### 2.1、插值语法





### 2.2、指令语法



