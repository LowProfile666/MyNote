<template>
  <h2>计数器1：{{data.counter1}}</h2>
  <h2>计数器2：{{data.a.b.c.d.counter2}}</h2>
  <button @click="data.counter1++">1号计数器加1</button>
  <button @click="data.a.b.c.d.counter2++">2号计数器加1</button>
</template>

<script>
  import {watch, reactive} from 'vue'
  export default {
    name : 'App',
    setup(){
      // data
      let data = reactive({
        counter1 : 1,
        a : {
          b : {
            c : {
              d : {
                counter2 : 100
              }
            }
          }
        }
      })
      // watch
      // 对于reactive函数获取的代理对象，在进行侦听的时候，只能获取到newValue，oldValue无法获取。
      // 对于reactive函数获取的代理对象来说，默认就是开启深度侦听的。
      // 这种深度侦听是无法取消的，配置 deep:false 无效。
      /* watch(data, (newValue, oldValue) => {
        console.log(newValue, oldValue) 
      }, {deep : false}) */

      // 怎么办？我不想每一个属性都侦听，我只想指定某个属性侦听。
      // 只想侦听data中的counter1这个属性。
      // 注意点：第一个需要侦听的数据，必须是一个函数。
      /* watch(()=>data.counter1, (newValue, oldValue) => {
        console.log(newValue, oldValue) 
      }) */

      // 如果是这样的，deep设置无效。
      /* watch(data.a.b, (newValue, oldValue) => {
        console.log(newValue, oldValue)
      }, {deep : false}) */

      // 如果是这样的，deep设置是有效的。(oldValue拿不到)
      watch(()=>data.a.b, (newValue, oldValue) => {
        console.log(newValue, oldValue)
      }, {deep : false})

      /* watch(()=>data.a.b.c.d.counter2, (newValue, oldValue) => {
        console.log(newValue, oldValue)
      }) */

      /* watch([()=>data.counter1,()=>data.a.b.c.d.counter2], (newValue, oldValue) => {
        console.log(newValue, oldValue) 
      }) */


      // 返回一个对象
      return {data}
    }
  }
</script>