<template>
    <div>
        <input type="text" v-model="$store.state.uname">
        <br>
        <h3>用户名：{{uname}}</h3>
        <h3>反转之后的用户名：{{reversedName}}</h3>
    </div>
</template>

<script>
    import {mapState, mapGetters} from 'vuex'
    export default {
        name : 'Name',
        computed : {
            ...mapState(['uname']),
            ...mapGetters(['reversedName'])
        }
    }
</script>