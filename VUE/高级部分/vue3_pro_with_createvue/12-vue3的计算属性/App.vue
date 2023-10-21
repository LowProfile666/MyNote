<template>
  姓名：<input type="text" v-model="data.name">
  <br>
  反转之后的姓名：<input type="text" v-model="reversedName">
</template>

<script>
  import { computed, reactive } from 'vue'
  export default {
    name : 'App',

    // vue3的计算属性，computed是一个组合式的API。
    setup(){

      // data
      let data = reactive({
        name : ''
      })

      // computed简写
      /* let reversedName = computed(() => {
        // 这种写法是一种简写形式，如果你只需要使用计算属性的get方法的话。
        return data.name.split('').reverse().join('')
      }) */

      // computed完整写法
      let reversedName = computed({
        get(){
          // 读取计算属性的值的时候执行。
          return data.name.split('').reverse().join('')
        },
        set(val){
          // 当修改计算属性的值的时候执行。
          data.name = val.split('').reverse().join('')
        }
      })

      // 返回一个对象
      return {data, reversedName}
    }


    /* data() {
      return {
        name : ''
      }
    },
    computed : {
      // 完整写法
      reversedName : {
        get(){
          return this.name.split('').reverse().join('')
        },
        set(value){
          
        }
      }
      // 简写形式
      reversedName(){
        return this.name.split('').reverse().join('')
      }
    } */
  }
</script>
