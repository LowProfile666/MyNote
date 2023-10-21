<template>
    <div>
        <input type="text" v-model="$store.state.uname">
        <br>
        <h3>用户名：{{uname}}</h3>
        <h3>反转之后的用户名：{{reversedName}}</h3>
    </div>
</template>

<script>
    import {mapState, mapGetters} from 'vuex'
    export default {
        name : 'Name',
        computed : {
            ...mapState(['uname']),

            // 实际上生成的代码是？以上代码生成的以下代码是简写形式的计算属性。(这里只有get方法，没有set方法。)
            /* uname(){
                return this.$store.state.uname
            }, */

            /* uname : {
                get(){
                    return this.$store.state.uname
                },
                set(value){
                    this.$store.state.uname = value
                }
            }, */

            ...mapGetters(['reversedName'])
        }
    }
</script>