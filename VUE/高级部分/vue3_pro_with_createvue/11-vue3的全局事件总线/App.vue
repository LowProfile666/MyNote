<template>
  <User></User>
</template>

<script>
  // 导入全局事件总线对象
  import emitter from './utils/event-bus.js'
  import User from './components/User.vue'
  // 引入组合式API：生命周期钩子
  import { onMounted } from 'vue'
  export default {
    name : 'App',
    components : {User},
    setup(){
      // 生命周期钩子：mounted
      onMounted(() => {
        // 给全局事件总线绑定事件
        emitter.on('event1', showInfo)
      })

      // methods
      function showInfo(user){
        alert(`姓名：${user.name}，年龄：${user.age}岁`)
      }

      // 返回一个对象
      return {showInfo}
    }
  }
</script>