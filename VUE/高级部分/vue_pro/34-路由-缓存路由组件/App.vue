<template>
    <div>
        <MyHeader></MyHeader>
        <div>    
            <h1>省</h1>
            <button @click="forward">前进</button>
            <button @click="back">后退</button>
            <button @click="forwardTwo">前进2步</button>
            <button @click="backTwo">后退2步</button>
            <ul>
                <li><router-link to="/hebei" active-class="selected">河北省</router-link></li>
                <li><router-link to="/henan" active-class="selected">河南省</router-link></li>
            </ul>
        </div>
        <!-- 这个标签，如果你这样编写的话，表示这个标签中所有的路由组件在切换的时候不会销毁。 -->
        <!-- <keep-alive>
            <router-view></router-view>
        </keep-alive> -->

        <!-- 注意：include="HeBei"表示在进行路由组件切换的时候，HeBei组件不被销毁。保留状态。 -->
        <!-- <keep-alive include="HeBei">
            <router-view></router-view>
        </keep-alive> -->

        <!-- include也支持数组形式 -->
        <keep-alive :include="['HeBei', 'HeNan']">
            <router-view></router-view>
        </keep-alive>
        
    </div>
</template>

<script>
    import MyHeader from './components/MyHeader'
    export default {
        name :'App',
        components : {MyHeader},
        methods: {
            forward(){
                this.$router.forward()
            },
            back(){
                this.$router.back()
            },
            forwardTwo(){
                this.$router.go(2)
            },
            backTwo(){
                this.$router.go(-2)
            }
        },
    }
</script>

<style lang="css">
    .s1 {
        margin-left: 100px;
    }
    .s2 {
        margin-left: 100px;
    }
    .selected {
        background-color: aqua;
    }
</style>