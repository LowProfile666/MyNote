// 等同于引入vue.js文件
import Vue from 'vue'
// 导入App组件（根组件）
import App from './App.vue'

// 导入混入
import {mix1} from './mixin.js'
import {mix2} from './mixin.js'
import {mix3} from './mixin.js'

// 导入插件
import {p1} from './plugins.js'

// 全局混入
Vue.mixin(mix1)
Vue.mixin(mix2)
Vue.mixin(mix3)

// 插件的使用通常放在创建Vue实例之前
// 插上插件。（删除就是拔下插件）
Vue.use(p1, 1,2,3,4)

// 关闭生产提示信息
Vue.config.productionTip = false

// 创建Vue实例
new Vue({
  el : '#app',
  // 您正在使用Vue的仅运行时版本，其中模板编译器不可用。
  // 目前使用的vue.js是一个缺失了模板编译器的vue.js文件。
  // 怎么解决，两种方案：
  // 第一种：使用完整版的vue.js： import Vue from 'vue/dist/vue.js'
  // 第二种：使用render函数。
  // 为什么采用缺失模板编译器的vue.js？
  // 目的：减小体积。Vue.js包括两块：Vue的核心 + 模板编译器（模板编译器可能占用vue.js文件体积的三分之一。）
  // 将来程序员使用webpack进行打包处理之后，模板编译器就没有存在的必要了。
  //template : '<h1>render函数</h1>'
  // 看不懂，一会再说。
  //render: h => h(App),
  // render函数被自动调用
  // 这个函数被调用的时候会自动传过来一个参数：createElement，createElement是一个函数。
  // createElement函数可以用来创建元素
  /* render(createElement){ 
    // 创建了一个div元素
    //return createElement('div', 'render函数')
    return createElement(App)
  } */

  render : h => h(App)
  
})
