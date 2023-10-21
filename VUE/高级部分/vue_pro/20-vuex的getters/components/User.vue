<template>
    <div>
        <h1>用户列表</h1>
        <input type="text" v-model="username">
        <button @click="saveUser">保存用户</button>
        <ul>
            <li v-for="user in $store.state.users" :key="user.id">
                用户名：{{user.name}}
            </li>
        </ul>
        <h3>当前用户数量：{{$store.state.users.length}}</h3>
        <h3>当前会员数量：{{$store.state.vips.length}}</h3>
        <h3>用户名：{{$store.state.username}}</h3>
        <h3>反转之后的用户名：{{$store.getters.reversedName}}</h3>
    </div>
</template>

<script>
	export default {
		name : 'User',
        data() {
            return {
                username : '',
            }
        },
        methods: {
            saveUser(){
                // dispatch
                //this.$store.dispatch('saveUser', {id:Date.now(),name:this.username})
                // 如果action中的逻辑非常简单，可以不经过action，直接通过commit走mutation
                this.$store.commit('SAVE_USER', {id:Date.now(),name:this.username})
            }
        },
	}
</script>