<template>
    <div>
    </div>
</template>

<script>
    import pubsub from 'pubsub-js'
    export default {
        name : 'A',
        mounted() {
            // A组件挂载完毕之后，订阅消息
            /* this.pid = pubsub.subscribe('2023年第5期英语周报', function(messageName, message){
                // messageName就是消息的名字
                // message就是具体的消息（数据）
                console.log('消息的名字是：', messageName)
                console.log('消息的具体内容是：', message)
                console.log(this)
            }) */

            this.pid = pubsub.subscribe('2023年第5期英语周报', (messageName, message) => {
                // messageName就是消息的名字
                // message就是具体的消息（数据）
                console.log('消息的名字是：', messageName)
                console.log('消息的具体内容是：', message)
                console.log(this)
            })
        },
        beforeDestroy() {
            // 当前组件实例销毁的之前，要取消之前订阅的所有消息。
            pubsub.unsubscribe(this.pid)
        },
    }
</script>