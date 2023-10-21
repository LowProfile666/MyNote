<template>
  <h2>姓名：{{userRefImpl.name}}</h2>
  <h2>年龄：{{userRefImpl.age}}</h2>
  <h2>计数器：{{counterRefImpl}}</h2>
  <h2>城市：{{userRefImpl.addr.city}}</h2>
  <h2>街道：{{userRefImpl.addr.street}}</h2>
  <button @click="modifyUser">修改用户信息</button>
</template>

<script>
  import {ref} from 'vue'
  export default {
    name : 'App',

    setup() {
      // data
      // 如果ref包裹的是一个基本数据类型，响应式是如何实现的？Object.defineProperty
      let counterRefImpl = ref(100)
      console.log(counterRefImpl)

      // 如果ref包裹的是一个对象，响应式是如何实现的？Object.defineProperty + Proxy 实现的。
      // Proxy实现的响应式，对象中的对象，对象中的对象，都有响应式处理。（底层是递归处理了。）
      let userRefImpl = ref({
        name : 'jack',
        age : 20,
        addr : {
          city : '北京',
          street : '大兴区凉水河二街'
        }
      })
      console.log(userRefImpl)

      // methods
      function modifyUser(){
        // 这种修改是有响应式处理的。
        counterRefImpl.value = 200

        // 对于userRefImpl对象来说，应该怎么改，才能有响应式呢？
        // 如果你采用这种value直接赋值的方式，表示这种响应式是基于Object.defineProperty的。
        /* userRefImpl.value = {
          name : '张三',
          age : 50
        } */

        // userRefImpl.value 是一个代理对象Proxy: userProxy对象。
        userRefImpl.value.name = '李四'
        userRefImpl.value.age = 90

        // 修改地址信息
        userRefImpl.value.addr.city = '邯郸'
        userRefImpl.value.addr.street = '太极二路'

      }
      // 返回对象
      return {userRefImpl, counterRefImpl, modifyUser}
    }

    /* setup() {
      // data
      // 如果这里是一个对象的话，默认也是没有响应式处理的。
      let user = {
        name : 'jack',
        age : 20
      }
      // methods
      function modifyUser(){
        user.name = 'lucy'
        user.age = 30
      }
      // 返回对象
      return {user, modifyUser}
    } */
  }
</script>