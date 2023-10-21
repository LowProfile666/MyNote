<template>
    <div>
        <button @click="getBugs">获取bug列表信息</button>
        <button @click="getUsers">获取user列表信息</button>
    </div>
</template>

<script>
    import axios from 'axios'
    export default {
        name : 'Bugs',
        methods: {
            getUsers(){
                axios.get('/abc/vue/users').then(
                    response => {
                        console.log('服务器响应回来的数据：', response.data)
                    },
                    error => {
                        console.log('错误信息：', error.message)
                    }
                )
            },
            getBugs(){
                // 发送AJAX请求，访问：http://localhost:8000/vue/bugs
                // 使用axios库发送AJAX请求
                // 原理：发送AJAX请求的时候，会优先从自己的服务器当中找/vue/bugs资源
                // 如果找不到，就会找代理，然后去http://localhost:8000找/vue/bugs资源。
                //axios.get('http://localhost:8080/vue/bugs').then(
                // 当前按钮这个页面就是在8080服务器上，又去访问8080服务器上的资源，所以http://localhost:8080可以省略。
                /* axios.get('/vue/bugs').then(
                    response => {
                        console.log('服务器响应回来的数据：', response.data)
                    },
                    error => {
                        console.log('错误信息：', error.message)
                    }
                ) */

                axios.get('/api/vue/bugs').then(
                    response => {
                        console.log('服务器响应回来的数据：', response.data)
                    },
                    error => {
                        console.log('错误信息：', error.message)
                    }
                )
            }
        },
    }
</script>