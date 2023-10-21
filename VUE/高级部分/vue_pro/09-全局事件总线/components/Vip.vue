<template>
    <div>
        <button @click="triggerEvent">触发事件，发送数据给爷爷</button>
    </div>
</template>

<script>
    export default {
        name : 'Vip',
        data() {
            return {
                name : 'jackson'
            }
        },
        methods: {
            triggerEvent(){
                // 获取共享的vc对象
                this.$bus.$emit('eventx', this.name)
            }
        },
    }
</script>