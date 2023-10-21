<template>
    <button @click="triggerEvent1">触发event1事件</button>
</template>

<script>
    export default {
        name : 'User',

        // context代表组件上下文对象。
        // context是setup当中的第二个参数。
        setup(props, context){
            // data
            // methods
            function triggerEvent1(){
                // 触发事件event1，传递数据。
                context.emit('event1', '张三', 50)
            }
            // 返回一个对象
            return {triggerEvent1}
        }
    }
</script>