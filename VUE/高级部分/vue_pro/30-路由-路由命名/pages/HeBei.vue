<template>
    <div class="s1">
        <div>
            <h2>市</h2>
            <ul>
                <li>
                    <router-link active-class="selected" :to="{
                        // 注意：如果使用name的话，要求必须使用对象形式。不能使用字符串形式。
                        name : 'shi',
                        //path : '/hebei/sjz',
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
                        name : 'han',
                        //path : '/hebei/hd',
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
                sjz : ['长安区', '裕华区', '新华区'],
                hd : ['邯山区', '复兴区', '丛台区']
            }
        },
    }
</script>