<template>
  <h2>计数器：{{counter}}</h2>
  <h2>计数器2：{{counter2}}</h2>
  <button @click="counter++">计数器加1</button>
  <br><br>
  <button @click="counter2++">计数器2加1</button>
</template>

<script>
  import {watch, ref} from 'vue'
  export default {
    name : 'App',

    //vue3当中如何进行属性的监视/侦听
    //组合式API： watch
    setup(){
      // data
      let counter = ref(1)
      let counter2 = ref(100)
      // watch
      // 被监视的数据需要具有响应式。
     /*  watch(counter, (newValue, oldValue) => {
        console.log('计数器', newValue, oldValue)
      }, {immediate : true, deep : true})

      watch(counter2, (newValue, oldValue) => {
         console.log('计数器2', newValue, oldValue)
      }, {immediate : true}) */

      // 采用数组的方式，一次性监视多个属性。
      watch([counter, counter2], (newValue, oldValue) => {
        console.log(newValue, oldValue)
      })

      // 返回一个对象
      return {counter, counter2}
    }

    /* data() {
      return {
        counter : 1
      }
    },
    watch : {
      // 简写形式
      // 监视的是counter属性。
      // 注意：被监视的属性必须是具有响应式的，才能监视。
      // counter(newValue, oldValue){
      //   console.log(newValue, oldValue)
      // }

      // 完整写法
      counter : {
        immediate : true, //开始的时候，立即执行一次handler
        deep : true, //启用深度监视
        handler(newValue, oldValue){
          console.log(newValue, oldValue)
        }
      }
    } */
  }
</script>