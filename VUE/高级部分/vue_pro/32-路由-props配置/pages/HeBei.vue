<template>
    <div class="s1">
        <div>
            <h2>市</h2>
            <ul>
                <li>
                    <router-link active-class="selected" :to="{
                        name : 'shi',
                        params : {
                            a1 : sjz[0],
                            a2 : sjz[1],
                            a3 : sjz[2],
                        }
                    }">石家庄</router-link>
                </li>

                <li>
                    <router-link active-class="selected" :to="{
                        name : 'han',
                        params : {
                            a1 : hd[0],
                            a2 : hd[1],
                            a3 : hd[2],
                        }
                    }">邯郸</router-link>
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
                sjz : ['长安区2', '裕华区1', '新华区1'],
                hd : ['邯山区1', '复兴区1', '丛台区1']
            }
        },
    }
</script>