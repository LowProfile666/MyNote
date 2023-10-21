<template>
  数字1：<input type="number" v-model="data.num1">
  <br><br>
  数字2：<input type="number" v-model="data.num2">
  <br><br>
  求和结果：{{data.result}}
  <br><br>
  <button @click="sum">求和</button>
</template>

<script>
  // 导入钩子函数
  import sum from './hooks/sum.js'
  export default {
    name : 'App',
    setup(){
      // 调用钩子函数
      //let result = sum()
      // 返回一个对象
      //return result

      return sum()
    }
  }
</script>