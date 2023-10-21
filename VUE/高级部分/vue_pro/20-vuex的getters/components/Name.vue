<template>
    <div>
        <input type="text" v-model="$store.state.username">
        <br>
        <h3>用户名：{{$store.state.username}}</h3>
        <h3>反转之后的用户名：{{$store.getters.reversedName}}</h3>
    </div>
</template>

<script>
    export default {
        name : 'Name'
    }
</script>