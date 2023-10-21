<template>
  <h2>计数器1：{{data.counter1}}</h2>
  <button @click="data.counter1++">计数器加1</button>
  <hr>
  <h2>计数器2：{{data.a.b.counter2}}</h2>
  <button @click="data.a.b.counter2++">计数器加1</button>
</template>

<script>
  import { reactive, readonly, shallowReadonly } from 'vue'
  export default {
    name : 'App',
    setup(){
      // data
      let data = reactive({
        counter1 : 1,
        a : {
          b : {
            counter2 : 100
          }
        }
      })
      // 深只读（具有响应式的对象中所有的属性，包括子对象中的子对象中的属性，它的所有值都是只读的不可修改的。）
      //data = readonly(data)

      // 浅只读（具有响应式的对象的第一层属性值是只读的）
      data = shallowReadonly(data)

      // 返回一个对象
      return {data}
    }
  }
</script>