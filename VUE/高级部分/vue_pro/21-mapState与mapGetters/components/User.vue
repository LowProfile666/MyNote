<template>
    <div>
        <h1>用户列表</h1>
        <input type="text" v-model="username">
        <button @click="saveUser">保存用户</button>
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
    // vuex插件提供的内置的mapState对象（负责state对象映射工作的一个对象）
    import {mapState, mapGetters} from 'vuex'
	export default {
		name : 'User',
        data() {
            return {
                username : '',
            }
        },
        /* mounted() {
            const x = mapState({users:'users', vips:'vips', uname:'uname'})
            console.log(x)
        }, */
        computed : {
            // 我们手动编写的
            /* users(){
                return this.$store.state.users
            },
            vips(){
                return this.$store.state.vips
            },
            uname(){
                return this.$store.state.uname
            } */

            // vuex可以借助mapState帮我们自动生成以上的代码
            // 对象形式
            //...mapState({users:'users', vips:'vips', uname:'uname'})
            // 数组形式（这种方式表示计算属性的名字和state中的属性名一致。）
            ...mapState(['users', 'vips', 'uname']),

            // 数组形式
            ...mapGetters(['reversedName'])
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