<template>
    <div class="s1">
        <div>
            <h2>市</h2>
            <ul>
                <li><router-link to="/hebei/shijiazhuang" active-class="selected">石家庄</router-link></li>
                <li><router-link to="/hebei/handan" active-class="selected">邯郸</router-link></li>
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
        name :'HeBei'
    }
</script>