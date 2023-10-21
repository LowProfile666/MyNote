<template>
    <div>
        <h1>B组件</h1>
        <button @click="doB1">doB1 BUTTON</button>
        <button @click="doB2">doB2 BUTTON</button>
        <h3>state : {{b}}</h3>
        <h3>getters : {{computedB}}</h3>
        <button @click="displayBugs">显示bug列表信息</button>
        <ul>
            <li v-for="bug in bugList" :key="bug.id">
                {{bug.desc}}
            </li>
        </ul>
    </div>
</template>

<script>
    import {mapState, mapGetters, mapActions, mapMutations} from 'vuex'
    export default {
        name : 'B',
        computed : {
            ...mapState('bModule',['b', 'bugList']),
            ...mapGetters('bModule',['computedB'])
        },
        methods: {
            ...mapActions('bModule',['doB1', 'displayBugs']),
            ...mapMutations('bModule',['doB2'])
        },
    }
</script>