<template>
    <div>
        <User></User>
        <Vip></Vip>
    </div>
</template>

<script>
    import Vip from './components/Vip.vue'
    import User from './components/User.vue'
    export default {
        name : 'App',
        components : {User, Vip}
    }
</script>

<style>
    /* 一般在App根组件当中样式不会添加scoped，因为根组件的样式还是希望采用全局的方式处理。 */
</style>