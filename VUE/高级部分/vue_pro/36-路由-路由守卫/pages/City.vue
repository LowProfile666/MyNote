<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <li>{{a1}}</li>
            <li>{{a2}}</li>
            <li>{{a3}}</li>
        </ul>
    </div>
</template>

<script>
    export default {
        name :'City',
        props : ['a1', 'a2', 'a3'],

        //1.代码写在哪里？局部路由守卫之component守卫，代码是写在component当中的（写到组件当中的Xxx.vue）
        //2.beforeRouteEnter执行时机：进入路由组件之前执行。
        //3.普通组件不会触发，必须是路由组件才会触发。
        beforeRouteEnter(to, from, next){
            console.log(`进入路由组件之前：${to.meta.title}`)
            next()
        },

        // beforeRouteLeave执行时机：离开路由组件之前执行。
        beforeRouteLeave(to, from, next){
            console.log(`离开路由组件之前：${from.meta.title}`)
            next()
        }

    }
</script>