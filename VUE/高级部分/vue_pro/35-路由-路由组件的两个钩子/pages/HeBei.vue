<template>
    <div class="s1">
        <div>
            <h2>市</h2>
            <ul>
                <li><input type="checkbox">
                    <router-link :replace="true" active-class="selected" :to="{
                        name : 'shi',
                        params : {
                            a1 : sjz[0],
                            a2 : sjz[1],
                            a3 : sjz[2],
                        }
                    }">石家庄</router-link>
                    <button @click="goSjz">石家庄</button>
                </li>

                <li><input type="checkbox">
                    <router-link replace active-class="selected" :to="{
                        name : 'han',
                        params : {
                            a1 : hd[0],
                            a2 : hd[1],
                            a3 : hd[2],
                        }
                    }">邯郸</router-link>
                    <button @click="goHd">邯郸</button>
                </li>

                <li><input type="checkbox">唐山</li>
                <li><input type="checkbox">保定</li>
            </ul>
        </div>
        <router-view></router-view>
    </div>
</template>

<script>
    export default {
        name :'HeBei',
        data() {
            return {
                sjz : ['长安区2', '裕华区1', '新华区1'],
                hd : ['邯山区1', '复兴区1', '丛台区1']
            }
        },
        mounted() {
            // 挂载完毕之后，创建一个定时器，每隔1秒打印一句话
            this.timer = setInterval(() => {
                console.log('我是一个定时器！')
            }, 1000)
        },
        beforeDestroy(){
            console.log('@河北省下面的市，这个组件被销毁了！')
            // 删除定时器
            //clearInterval(this.timer)
        },
        activated(){
            console.log('激活了')
        },
        deactivated(){
            console.log('失效了')
            // 删除定时器
            clearInterval(this.timer)
        },
        methods : {
            goSjz(){
                this.$router.push({
                    name : 'shi',
                    params : {
                        a1 : this.sjz[0],
                        a2 : this.sjz[1],
                        a3 : this.sjz[2],
                    }
                }, ()=>{}, ()=>{})
            },
            goHd(){
                this.$router.replace({
                    name : 'han',
                    params : {
                        a1 : this.hd[0],
                        a2 : this.hd[1],
                        a3 : this.hd[2],
                    }
                }, ()=>{}, ()=>{})
            }
        }
    }
</script>