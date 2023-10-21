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
