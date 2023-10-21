<template>
    <div>
        <h1>{{msg}}</h1>
        <!-- 在App这个父组件当中，找到子组件Car，然后给Car这个子组件传数据：通过属性的形式传数据 -->
        <Car brand="宝马520" color="黑色" :price="10"></Car>
        <hr>
        <Car brand="比亚迪汉" color="红色" :price="20"></Car>
    </div>
</template>

<script>
    import Car from './components/Car.vue'
    export default {
        name : 'App',
        data() {
            return {
                msg : '汽车信息'
            }
        },
        components : {Car}
    }
</script>
