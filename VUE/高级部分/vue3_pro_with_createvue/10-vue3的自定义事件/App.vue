<template>
  <!-- 给User组件绑定自定义事件。 -->
  <User @event1="showInfo"></User>
</template>

<script>
  import User from './components/User.vue'
  export default {
    name : 'App',
    components : {User},
    setup(){
      // data
      // methods
      function showInfo(name, age){
        alert(`姓名：${name}，年龄：${age}岁`)
      }
      // 返回一个对象
      return {showInfo}
    }
  }
</script>