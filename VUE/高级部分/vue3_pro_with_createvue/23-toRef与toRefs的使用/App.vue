<template>
  <h2>{{data}}</h2>
  <h2>计数器1：{{counter1}}</h2>
  <button @click="counter1++">计数器加1</button>
  <hr>
  <h2>计数器2：{{counter2}}</h2>
  <button @click="counter2++">计数器加1</button>
  <hr>
  <h2>计数器3：{{a.b.counter3}}</h2>
  <button @click="a.b.counter3++">计数器加1</button>
</template>

<script>
  import { reactive, ref, toRef, toRefs } from 'vue'
  export default {
    name : 'App',
    setup(){
      // data
      let data = reactive({
        counter1 : 1,
        counter2 : 100,
        a : {
          b : {
            counter3 : 1000
          }
        }
      })
      // 返回一个对象
      //return {data}

      // 这样写肯定不行，因为这种方式第一次打开页面的时候，能够看到数据，但是不是响应式的。因为这个数据和data无关了。
      // 并不是具有响应式的data对象了。
      /* return {
        counter1 : data.counter1,
        counter2 : data.counter2,
        counter3 : data.a.b.counter3
      } */

      // 这种方式可以完成响应式。
      // 问题是什么？计数器加1的时候，data对象中的数据不会变。
      /* return {
        data,
        counter1 : ref(data.counter1),
        counter2 : ref(data.counter2),
        counter3 : ref(data.a.b.counter3)
      } */

      // toRef
      // toRef语法格式：toRef(对象, '该对象中的属性名')
      // toRef函数执行之后会生成一个全新的对象：ObjectRefImpl（引用对象）
      // 只要有引用对象，就有value属性，并且value属性是响应式的。(value有对应的set和get。)
      //console.log(toRef(data, 'counter1'))

      /* return {
        data,
        counter1 : toRef(data, 'counter1'),
        counter2 : toRef(data, 'counter2'),
        counter3 : toRef(data.a.b, 'counter3')
      } */

      // toRefs
      // toRefs函数用法：toRefs(data)
      console.log(toRefs(data)) // 这个生成的是一个对象

      return {
        data,
        ...toRefs(data)
      }


    }
  }
</script>