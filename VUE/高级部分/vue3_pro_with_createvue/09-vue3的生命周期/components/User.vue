<template>
    <h1>User组件</h1>
    <h2>计数器：{{counter}}</h2>
    <button @click="counter++">计数</button>
</template>

<script>
    import {ref, onBeforeMount, onMounted, onBeforeUpdate, onUpdated, onBeforeUnmount, onUnmounted} from 'vue'
    export default {
        name : 'User',
        setup(){
            console.log('setup...')
            // 采用组合式API：生命周期钩子函数
            onBeforeMount(() => {
                console.log('onBeforeMount')    
            })

            onMounted(() => {
                console.log('onMounted')
            })

            onBeforeUpdate(() => {
                console.log('onBeforeUpdate')
            })

            onUpdated(() => {
                console.log('onUpdated')
            })

            onBeforeUnmount(() => {
                console.log('onBeforeUnmount')
            })

            onUnmounted(() => {
                console.log('onUnmounted')
            })

            // data
            let counter = ref(0)
            // 返回一个对象
            return {counter}
        },

        // 选项式API
        beforeCreate(){
            console.log('beforeCreate')
        },
        created(){
            console.log('created')
        },

        // 在Vue3当中，生命周期钩子函数有两种写法：
        // 第一种写法：选项式API（以下这种方式就是选项式API）
        // 第二种写法：组合式API
        /* beforeCreate(){
            console.log('beforeCreate')
        },
        created(){
            console.log('created')
        },
        beforeMount(){
            console.log('beforeMount')
        },
        mounted(){
            console.log('mounted')
        },
        beforeUpdate(){
            console.log('beforeUpdate')
        },
        updated(){
            console.log('updated')
        },
        beforeUnmount(){
            console.log('beforeUnmount')
        },
        unmounted(){
            console.log('unmounted')
        } */
    }
</script>