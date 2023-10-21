import Vue from 'vue'
import App from './App.vue'

Vue.config.productionTip = false

// 导入vue-router插件
import VueRouter from 'vue-router'

// 导入路由器对象
//import router from './router/index.js'
import router from './router'

// 使用vue-router插件
Vue.use(VueRouter)

new Vue({
  el : '#app',
  // 一旦使用了vue-router插件，那么new Vue的时候就可以直接传递一个配置项：router
  // router配置项用来接收一个路由器对象。
  router : router,
  render : h => h(App)
})
