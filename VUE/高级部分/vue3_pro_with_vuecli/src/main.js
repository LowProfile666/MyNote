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

// unmount()，这个方法可以卸载组件。
// 3秒之后卸载掉。
/* setTimeout(() => {
    app.unmount('#app')
}, 3000) */