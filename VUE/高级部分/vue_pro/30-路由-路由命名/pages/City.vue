<template>
    <div class="s2">
        <h2>区</h2>
        <ul>
            <!-- <li>{{$route.query.a1}}</li>
            <li>{{$route.query.a2}}</li>
            <li>{{$route.query.a3}}</li> -->

            <li v-for="areaName,propertyName in $route.query" :key="propertyName">
                {{areaName}}
            </li>

        </ul>
    </div>
</template>

<script>
    export default {
        name :'City'
    }
</script>