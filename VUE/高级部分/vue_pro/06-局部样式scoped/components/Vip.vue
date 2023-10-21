<template>
    <div class="s">
        <h1>{{msg}}</h1>
        <h3>姓名：{{name}}</h3>
        <h3>年龄：{{age}}</h3>
    </div>
</template>

<script>
    export default {
        name : 'Vip',
        data() {
            return {
                msg : '会员信息',
                name : '李四2',
                age : 21
            }
        }
    }
</script>

<style scoped>
   .s {
    background-color:bisque
   } 
</style>