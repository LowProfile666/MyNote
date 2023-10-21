<template>
  <button @click="isDisplay = !isDisplay">显示或隐藏</button>
  <User v-if="isDisplay"></User>
</template>

<script>
  import {ref} from 'vue'
  import User from './components/User.vue'
  export default {
    name : 'App',
    components : {User},
    setup(){
      //console.log('setup：安装组合式API')
      // data
      let isDisplay = ref(true)
      // 返回对象
      return {isDisplay}
    },
    /* beforeCreate(){
      console.log('beforeCreate')
      console.log('正在初始化选项式API')
    },
    created(){
      console.log('选项式API初始化完成')
      console.log('created')
    } */
  }
</script>