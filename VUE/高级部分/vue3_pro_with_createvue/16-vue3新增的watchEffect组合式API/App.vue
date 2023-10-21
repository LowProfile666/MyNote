<template>
  <h2>计数器：{{data.counter1}}</h2>
  <button @click="data.counter1++">点我加1</button><hr>
  <h2>计数器：{{data.counter2}}</h2>
  <button @click="data.counter2++">点我加1</button><hr>
  <h2>计数器：{{data.counter3}}</h2>
  <button @click="data.counter3++">点我加1</button>
</template>
<script>
  import { reactive, watchEffect } from 'vue'
  export default {
    name : 'App',
    setup(){
      let data = reactive({
        counter1 : 1,
        counter2 : 100,
        counter3 : 1000
      })
      // 使用watchEffect这个组合式的API。
      // 作用：也是用来监视的。
      // watchEffect函数中直接跟一个回调函数即可。
      // 这个回调函数什么时候执行？一开始就先执行一次。然后函数体当中使用到了某个数据。
      // 这个使用到的数据只要发生变化，watchEffect中的回调函数一定会执行一次。
      watchEffect(() => {
        // 我这个回调函数当中使用到了data.counter1和data.counter3
        // 这个回调函数的执行实际是：只要counter1发生变化，或者counter3发生变化，这个回调函数都会执行。
        const a = data.counter1
        const b = data.counter3
        console.log(a, b)
      })
      // 返回一个对象
      return {data}
    }
  }
</script>