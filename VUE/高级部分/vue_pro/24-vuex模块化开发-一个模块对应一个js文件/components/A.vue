<template>
    <div>
        <h1>A组件</h1>
        <button @click="doA1">doA1 BUTTON</button>
        <button @click="doA2">doA2 BUTTON</button>
        <h3>state : {{$store.state.aModule.a}}</h3>
        <h3>getters : {{$store.getters['aModule/computedA']}}</h3>
    </div>
</template>

<script>
    export default {
        name : 'A',
        mounted() {
            console.log(this.$store)
        },
        methods: {
            doA1(){
                this.$store.dispatch('aModule/doA1')
            },
            doA2(){
                this.$store.commit('aModule/doA2')
            }
        },
    }
</script>