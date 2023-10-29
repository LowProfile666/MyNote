# VUE2

在使用开发版 Vue 框架时，浏览器会有一个警告：

![image-20231021111745625](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310211117683.png)

意思是我正在使用开发板的Vue，上线的时候记得改为生产版的 Vue。

消除这样的警告：

```vue
Vue.config.productionTip = false
// Vue.config是Vue的全局配置对象。
// productionTip属性可以设置是否生成生产提示信息。
// 默认值：true。如果是false则表示阻止生成提示信息。
```

Vue.js devtools

图标亮度：如果当前页面有Vue框架就是亮的，否则暗的。

Vue.js devtools 的界面：

![image-20231021113804093](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310211138144.png)

左边第一个是 app 页面，中间是组件页面，右边是组件相关的数据

VScode快速生成代码片段

左下角的齿轮 --》User Snippets（用户代码片段）--》输入 javascript --》打开了 javascript.json --》里面有段注释代码：

```

"Print to console": {  // 提示信息
    "prefix": "log",  // 简写
    "body": [  // 配置代码片段
        "console.log('$1');",  // $1 和 $2 是用来定位光标的，
        "$2"
    ],
    "description": "Log output to console"
}
```

将以上代码放开以后，在写JavaScript代码的时候，写下 log 这个简写就会有提示：

![image-20231021161325034](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310211613080.png)

直接回车就会生成 body 中的内容：

![image-20231021161400842](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310211614850.png)

而代码中的 \$1 和 \$2 的作用是定位光标，第一次生成时光标定位在 $1，如果你没有输入任何信息，按 tab 键后会跳到 \$2 的位置。

那么在这个文件中添加以下代码即可快速生成片段：

```
"create vue instance": {
    "prefix": "vm",
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

Vscode有个这样的插件：JavaScript (ES6) code snippets


# Vue 脚手架
先确保 npm 能用，需要安装 Node.js。
Vue 脚手架（Vue CLI：Command Line Interface）是 Vue 官方提供的开发平台，可以将我们的 .vue 的代码进行编译生成 html、css、js 代码，并将这些代码自动发布到它的自带的服务器上。

初始的vue项目：

![image-20231029211707105](https://gitee.com/LowProfile666/image-bed/raw/master/img/202310292118853.png)

`index.html`：在index.html中，没有看到引入vue.js文件，也没有看到引入main.js文件。Vue脚手架会自动找到main.js文件，不需要手动引入，所以main.js文件的文件不要随便改，位置也不要随便动。

```html
<!DOCTYPE html>
<html lang="">
  <head>
    <meta charset="utf-8">
    <!-- 让IE浏览器启用最高渲染标准。IE8是不支持Vue的 -->
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <!-- 开启移动端虚拟窗口（理想视口） -->
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <!-- 设置页签图标（浏览器左上角） -->
    <link rel="icon" href="<%= BASE_URL %>favicon.ico">
    <!-- 设置标题 -->
    <title><%= htmlWebpackPlugin.options.title %></title>
  </head>
  <body>
    <!-- 当浏览器不支持JS语言的时候，显示如下的提示信息 -->
    <noscript>
      <strong>We're sorry but <%= htmlWebpackPlugin.options.title %> doesn't work properly without JavaScript enabled. Please enable it to continue.</strong>
    </noscript>
    <!-- 容器 -->
    <div id="app"></div>
    <!-- built files will be auto injected -->
  </body>
</html>
```

`main.js`

```js
// 等同于引入vue.js文件
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

`App.vue`

```vue
<template>
  <div id="app">
    <img alt="Vue logo" src="./assets/logo.png">
    <HelloWorld msg="Welcome to Your Vue.js App"/>
  </div>
</template>

<script>
import HelloWorld from './components/HelloWorld.vue'

export default {
  name: 'App',
  components: {
    HelloWorld
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

