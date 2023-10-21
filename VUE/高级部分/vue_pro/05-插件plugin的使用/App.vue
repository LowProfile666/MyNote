<template>
    <div>
        <User></User>
        <Vip></Vip>
    </div>
</template>

<script>
    import User from './components/User.vue'
    import Vip from './components/Vip.vue'
    export default {
        name : 'App',
        components : {User, Vip}
    }
</script>
