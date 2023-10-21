<template>
    <div>
        <div>    
            <h1>省份</h1>
            <ul>
                <!-- 如果使用的是路由方式，就不能使用超链接a标签了，需要使用vue-router插件提供的一个标签 -->
                <!-- router-link 将来会被自动编译为a标签。 -->
                <li><router-link to="/hebei" active-class="selected">河北省</router-link></li>
                <li><router-link to="/henan" active-class="selected">河南省</router-link></li>
            </ul>
        </div>
        <!-- 这个位置将来是要显示对应的组件的，具体怎么写，一会再说?????? -->
        <!-- 路由视图，其实就是起到一个占位的作用。 -->
        <router-view></router-view>
    </div>
</template>

<script>
    export default {
        name :'App'
    }
</script>

<style lang="css">
    .s1 {
        margin-left: 100px;
    }
    .selected {
        background-color: aqua;
    }
</style>