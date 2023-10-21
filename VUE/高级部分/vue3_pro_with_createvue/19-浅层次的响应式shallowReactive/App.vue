<template>
  <h2>计数器：{{data.a.b.c.counter}}</h2>
  <button @click="data.a.b.c.counter++">点我加1</button>
  <hr>
  <h2>计数器：{{data.counter2}}</h2>
  <button @click="data.counter2++">点我加1</button>
</template>

<script>
  import { reactive, shallowReactive } from 'vue'
  export default {
    name : 'App',
    setup(){
      // data
      let data = shallowReactive({
        counter2 : 1000,
        a : {
          b : {
            c : {
              counter : 1
            }
          }
        }
      })

      // 返回一个对象
      return {data}
    }
  }
</script>