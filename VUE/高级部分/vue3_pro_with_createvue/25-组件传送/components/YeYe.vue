<template>
    <div class="s2">
        <h2>我是爷爷组件</h2>
        <ErZi></ErZi>
    </div>
</template>

<script>
    import ErZi from './ErZi.vue'
    export default {
        name : 'YeYe',
        components : {ErZi}
    }
</script>

<style lang="css" scoped>
    .s2 {
        width: 400px;
        height: 400px;
        background-color: bisque;
    }
</style>