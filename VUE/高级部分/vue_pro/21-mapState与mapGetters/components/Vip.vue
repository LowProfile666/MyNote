<template>
    <div>
        <h1>会员列表</h1>
        <input type="text" v-model="vipname">
        <button @click="saveVip">保存会员</button>
        <ul>
            <li v-for="vip in vips" :key="vip.id">
                会员名：{{vip.name}}
            </li>
        </ul>
        <h3>当前用户数量：{{users.length}}</h3>
        <h3>当前会员数量：{{vips.length}}</h3>
        <h3>用户名：{{uname}}</h3>
        <h3>反转之后的用户名：{{reversedName}}</h3>
    </div>
</template>

<script>
    import {mapState, mapGetters} from 'vuex'
	export default {
		name : 'Vip',
        data() {
            return {
                vipname : ''
            }
        },
        computed : {
            ...mapState(['vips','users','uname']),
            ...mapGetters(['reversedName'])
        },
        methods: {
            saveVip(){
                // dispatch
                //this.$store.dispatch('saveVip', {id:Date.now(), name:this.vipname})
                this.$store.commit('SAVE_VIP', {id:Date.now(),name:this.vipname})
            }
        },
	}
</script>