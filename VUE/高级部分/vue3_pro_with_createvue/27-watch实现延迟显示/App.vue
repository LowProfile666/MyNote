<template>
  <input type="text" v-model="name">
  <br><br>
  {{newName}}
</template>

<script>
  import {ref, watch} from 'vue'
  export default {
    name : 'App',
    setup(){
      // data
      let name = ref('')
      let newName = ref(name.value)
      // 侦听属性
      watch(name, (newValue, oldValue) => {
        setTimeout(() => {
          newName.value = newValue
        }, 300)
      })
      // 返回一个对象
      return {name, newName}
    }
  }
</script>