<template>
</template>

<script>
  import {isRef, ref, isReactive, isProxy, isReadonly, reactive, readonly} from 'vue'
  export default {
    name : 'App',
    setup(){
      // 判断某个数据是否是 ref 的。
      let counter = ref(1)
      console.log(isRef(counter))
      // 判断某个对象是否通过 reactive()或者shallowReactive()获取的代理
      let data = reactive({
        counter : 1
      })
      console.log(isReactive(data))
      // 判断某个对象是否为代理对象
      console.log(isProxy(data))
      // 判断某个对象是否为只读对象
      data = readonly(data)
      console.log(isReadonly(data))
      // 只读的如果采用isProxy判断的话，如果是只读的，isProxy的结果也是true
      console.log(isProxy(data))
    }
  }
</script>