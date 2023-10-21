<template>
    <div>
        <h1>A组件</h1>
        <button @click="doA1">doA1 BUTTON</button>
        <button @click="doA2">doA2 BUTTON</button>
        <h3>state : {{a}}</h3>
        <h3>getters : {{computedA}}</h3>
    </div>
</template>

<script>
    import {mapState, mapGetters, mapActions, mapMutations} from 'vuex'
    export default {
        name : 'A',
        computed : {
            ...mapState('aModule',['a']),
            ...mapGetters('aModule',['computedA'])
        },
        methods: {
            ...mapActions('aModule',['doA1']),
            ...mapMutations('aModule',['doA2'])
        },
    }
</script>