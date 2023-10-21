<template>
  <!-- <h2>姓名：{{name}}</h2>
  <h2>年龄：{{age}}</h2>
  <button @click="modifyInfo">修改用户信息</button> -->

  <!-- 在模板语法当中访问RefImpl对象的时候，不需要手动 .value -->
  <h2>姓名：{{nameRefImpl}}</h2>
  <h2>年龄：{{ageRefImpl}}</h2>
  <button @click="modifyInfo">修改用户信息</button>
</template>

<script>
  import {ref} from 'vue'
  export default {
    name : 'App',

    // 使用ref函数实现data响应式
    setup(){
      // data
      // ref对'张三'这个数据进行包裹，然后返回了一个全新的对象：引用对象RefImpl
      // RefImpl对象中有value属性，这个value属性是具有响应式的，并且这个value底层使用了Object.defineProperty完成了响应式。
      // RefImpl对象的value属性，有对应的set和get
      // 当读取RefImpl对象的value属性时：get执行。
      // 当修改RefImpl对象的value属性时：set执行。
      let nameRefImpl = ref('张三')
      let ageRefImpl = ref(30)

      // methods
      function modifyInfo(){
        nameRefImpl.value = '李四'
        ageRefImpl.value = 100
      }

      // 返回一个对象（只有返回了，这些数据、函数才能在模板语法中使用）
      return {nameRefImpl, ageRefImpl, modifyInfo}
    }

    // 以下代码没有响应式
    /* setup(){
      // 数据data
      // 通过测试得知，如果当前的data这样写，是没有响应式的。
      let name = '张三'
      let age = 20

      // 方法methods
      function modifyInfo(){
        console.log(666)
        // 修改这个数据data时，有没有响应式
        name = '李四'
        age = 30
      }

      // 返回一个对象
      return {name, age, modifyInfo}
    } */
  }
</script>