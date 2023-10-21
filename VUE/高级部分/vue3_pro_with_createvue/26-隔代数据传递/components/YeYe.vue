<template>
    <div class="s2">
        <h2>我是爷爷组件（{{counter}}）</h2>
        <ErZi></ErZi>
    </div>
</template>

<script>
    import {provide, ref} from 'vue'
    import ErZi from './ErZi.vue'
    export default {
        name : 'YeYe',
        components : {ErZi},
        setup(){
            let counter = ref(1)
            
            // 在祖宗组件中使用provide提供数据
            provide('c', counter)

            return {counter}
        }
    }
</script>

<style lang="css" scoped>
    .s2 {
        width: 400px;
        height: 400px;
        background-color: bisque;
    }
</style>