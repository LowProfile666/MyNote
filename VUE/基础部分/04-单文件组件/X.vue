<template>
    <div>
        <h2>X组件</h2>
        <!-- 使用组件 -->
        <X1></X1>
    </div>
</template>

<script>
    import X1 from './X1.vue'
    export default {
        // 注册组件
        components : {X1}
    }
</script>