<template>
  <User name="张三" age="30" :sex="sex"></User>
</template>

<script>
  import {ref} from 'vue'
  import User from './components/User.vue'
  export default {
    // 直接在大括号当中进行的配置，叫做：选项式API（options api）
    name : 'App',
    components : {User},
    setup(){
      // 在setup函数体当中进行的配置，使用的API叫做组合式API。(ref、reactive这些都属于组合式API。)
      // data
      let sex = ref('男')
      // 返回对象
      return {sex}
    }
  }
</script>