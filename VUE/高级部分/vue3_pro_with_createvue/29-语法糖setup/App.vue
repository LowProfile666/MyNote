<template>
  <h2>计数器：{{counter}}</h2>
  <button @click="add">计数器加1</button>
  <hr>
  <User></User>
</template>


<script setup>

  import {ref} from 'vue'
  import User from './components/User.vue'

  // data
  let counter = ref(0)

  // methods
  function add(){
    counter.value++
  }

  // watch

  // computed

  // ....

  
  /* export default {
    name : 'App',
    setup(){

      // data
      let counter = ref(100)
      // methods
      function add(){
        counter.value++
      }
      // watch
      // computed
      // ....

      // 返回一个对象
      return {counter, add}
    }
  } */

</script>