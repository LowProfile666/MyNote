<template>
    <div>
        <h1>用户列表</h1>
        <input type="text" v-model="username">
        <button @click="saveUser(username)">保存用户</button>
        <ul>
            <li v-for="user in users" :key="user.id">
                用户名：{{user.name}}
            </li>
        </ul>
        <h3>当前用户数量：{{users.length}}</h3>
        <h3>当前会员数量：{{vips.length}}</h3>
        <h3>用户名：{{uname}}</h3>
        <h3>反转之后的用户名：{{reversedName}}</h3>
    </div>
</template>

<script>
    import {mapState, mapGetters, mapActions} from 'vuex'
	export default {
		name : 'User',
        data() {
            return {
                username : '',
            }
        },
        computed : {
            ...mapState(['users', 'vips', 'uname']),
            ...mapGetters(['reversedName'])
        },
        methods: {
            /* saveUser(){
                // 下一个环节走的是action
                this.$store.dispatch('saveUser', this.username)
            }, */

            // 对象形式
            //...mapActions({saveUser : 'saveUser'})

            // 数组形式
            ...mapActions(['saveUser'])
        },
	}
</script>