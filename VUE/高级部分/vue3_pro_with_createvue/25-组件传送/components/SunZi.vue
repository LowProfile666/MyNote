<template>
    <div class="s4">
        <h2>我是孙子组件</h2>
        <button @click="isShow = true">弹窗</button>
        
        <teleport to='body'>
            <!-- 遮罩层，一会整个遮罩层要瞬移到body下面 -->
            <div v-show="isShow" class="cover">
                <!-- 模态窗口 -->
                <div class="s">
                    我是一个窗口.....
                    <button @click="isShow = false">关闭</button>
                </div>
            </div>
        </teleport>
        

    </div>
</template>

<script>
    import {ref} from 'vue'
    export default {
        name : 'SunZi',
        setup(){
            // data
            let isShow = ref(false)
            // 返回一个对象
            return {isShow}
        }
    }
</script>

<style lang="css" scoped>
    .s4 {
        width: 200px;
        height: 200px;
        background-color: darkmagenta;
    }
    .s {
        width: 250px;
        height: 250px;
        background-color: cadetblue;
    }
    .cover {
        position: absolute;
        top: 0; bottom: 0; left: 0; right: 0;
        /* opacity: 90%; */
        background-color: darkgrey;
    }
</style>