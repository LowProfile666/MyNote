<template>
    <div class="footer"  v-show="bugList.length">
        <button class="small red button" @click="clearResolved">清除已解决</button>
        <span>当前BUG总量{{bugList.length}}个，已解决{{resolvedCount}}个</span>
    </div>
</template>

<script>
    export default {
        name : 'BugFooter',
        props : ['bugList'],
        methods: {
            clearResolved(){
                this.$emit('clearResolvedCallback')
            }
        },
        computed : {
            resolvedCount(){
                return this.bugList.reduce((a, b) => a + (b.resolved ? 1 : 0), 0)
            }
        }
    }
</script>

<style scoped>
/* footer */
.footer{
	margin-top: 10px;
}
.footer span{
	font-size: 12px;
}
</style>