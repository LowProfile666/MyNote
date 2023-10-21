<template>
  <div class="s1">
    <h2>我是App组件</h2>
    <YeYe></YeYe>
  </div>
</template>

<script>
  import YeYe from './components/YeYe.vue'
  export default {
    name : 'App',
    components : {YeYe}
  }
</script>

<style lang="css" scoped>
  .s1 {
    width: 500px;
    height: 500px;
    background-color: aquamarine;
  }
</style>