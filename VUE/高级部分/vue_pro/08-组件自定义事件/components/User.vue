<template>
    <div>
        <button @click="triggerEvent1">触发event1事件</button>
        <button @click="triggerEvent2">触发event2事件</button>
        <button @click="unbinding">解绑事件</button>
        <button @click="goodbye">再见</button>
    </div>
</template>

<script>
    export default {
        name : 'User',
        data() {
            return {
                name : '张三',
                age : 20,
                gender : '男'
            }
        },
        methods: {
            triggerEvent1(){
                // 编写触发event1事件的代码
                // this是当前的组件实例：vc
                // 触发事件的同时，可以给事件绑定的回调函数传数据
                this.$emit('event1', this.name, this.age, this.gender)
            },
            triggerEvent2(){
                this.$emit('event2')
            },
            goodbye(){
                this.$destroy()
            },
            // 解绑事件
            unbinding(){
                // 仅仅解绑this指向的这个组件实例上的event1事件。
                //this.$off('event1')
                //this.$off(['event1', 'event2'])
                this.$off()
            }
        },
    }
</script>