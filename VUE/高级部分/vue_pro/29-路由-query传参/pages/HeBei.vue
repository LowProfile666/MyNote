<template>
    <div class="s1">
        <div>
            <h2>市</h2>
            <ul>
                <!-- <li><router-link to="/hebei/city?a1=长安区&a2=裕华区&a3=新华区" active-class="selected">石家庄</router-link></li>
                <li><router-link to="/hebei/city?a1=邯山区&a2=复兴区&a3=丛台区" active-class="selected">邯郸</router-link></li> -->

                <!-- 采用query方式传参，这里使用的是字符串拼接方式 -->
                <!-- <li><router-link :to="`/hebei/city?a1=${sjz[0]}&a2=${sjz[1]}&a3=${sjz[2]}`" active-class="selected">石家庄</router-link></li>
                <li><router-link :to="`/hebei/city?a1=${hd[0]}&a2=${hd[1]}&a3=${hd[2]}`" active-class="selected">邯郸</router-link></li> -->

                <!-- 采用query方式传参，这里还可以使用对象形式 -->
                <li>
                    <router-link active-class="selected" :to="{
                        path : '/hebei/city',
                        query : {
                            a1 : sjz[0],
                            a2 : sjz[1],
                            a3 : sjz[2],
                        }
                    }">
                        石家庄
                    </router-link>
                </li>

                <li>
                    <router-link active-class="selected" :to="{
                        path : '/hebei/city',
                        query : {
                            a1 : hd[0],
                            a2 : hd[1],
                            a3 : hd[2],
                        }
                    }">
                        邯郸
                    </router-link>
                </li>

                <li>唐山</li>
                <li>保定</li>
            </ul>
        </div>
        <!-- 区组件 -->
        <router-view></router-view>
    </div>
</template>

<script>
    export default {
        name :'HeBei',
        data() {
            return {
                sjz : ['长安区3', '裕华区2', '新华区2'],
                hd : ['邯山区3', '复兴区2', '丛台区2']
            }
        },
    }
</script>