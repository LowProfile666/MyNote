<template>
  <h2>计数器：{{counterRefImpl}}</h2>
  <button @click="counterRefImpl++">点我加1</button>
  <hr>
  <h2>计数器：{{data.a.b.c.counter}}</h2>
  <button @click="data.a.b.c.counter++">点我加1</button>
</template>

<script>
  import {watch, ref} from 'vue'
  export default {
    name : 'App',
    setup(){

      // data
      let counterRefImpl = ref(1)

      let data = ref({
        a : {
          b : {
            c : {
              counter : 1
            }
          }
        }
      })

      // 监视data
      // oldValue又是拿不到。
      // deep配置无效。
      /* watch(data.value, (newValue, oldValue) => {
        console.log(newValue, oldValue)
      }, {deep : false}) */

      // data是一个RefImpl对象。支持deep配置的。默认是没有开启深度监视的。
      watch(data, (newValue, oldValue) => {
        console.log(newValue, oldValue)
      }, {deep : true}) 

      //console.log(counterRefImpl.value)

      // watch
      // 错误的。
      //watch(counterRefImpl.value, (newValue, oldValue) => {})

      // 可以监视到。
      /* watch(()=>counterRefImpl.value, (newValue, oldValue) => {
        console.log(newValue, oldValue)
      }) */

      // 返回一个对象
      return {counterRefImpl, data}
    }
  }
</script>