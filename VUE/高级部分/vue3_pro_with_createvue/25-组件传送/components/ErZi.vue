<template>
    <div class="s3">
        <h2>我是儿子组件</h2>
        <SunZi></SunZi>
    </div>
</template>

<script>
    import SunZi from './SunZi.vue'
    export default {
        name : 'ErZi',
        components : {SunZi}
    }
</script>

<style lang="css" scoped>
    .s3 {
        width: 300px;
        height: 300px;
        background-color:chartreuse;
    }
</style>