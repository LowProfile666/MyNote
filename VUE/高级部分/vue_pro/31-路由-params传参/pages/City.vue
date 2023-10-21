<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <!-- <li>{{$route.params.a1}}</li>
            <li>{{$route.params.a2}}</li>
            <li>{{$route.params.a3}}</li> -->

            <li v-for="area, propertyName in $route.params" :key="propertyName">
                {{area}}
            </li>
        </ul>
    </div>
</template>

<script>
    export default {
        name :'City',
        mounted() {
            console.log(this.$route)
            console.log(this.$route.params)
        },
    }
</script>