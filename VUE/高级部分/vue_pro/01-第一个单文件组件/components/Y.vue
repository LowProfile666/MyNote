<template>
    <div>
        <h2>Y组件</h2>
        <!-- 使用组件 -->
        <Y1></Y1>
    </div>
</template>

<script>
    // 导入组件Y1（Y1可以使用其它名字。）
    import Y1 from './Y1.vue'
    export default {
        // 注册组件
        components : {Y1}
    }
</script>