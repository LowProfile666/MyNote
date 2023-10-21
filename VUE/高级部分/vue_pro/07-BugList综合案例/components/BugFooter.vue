<template>
    <div class="footer"  v-show="bugList.length">
        <button class="small red button" @click="clearResolved">清除已解决</button>
        <span>当前BUG总量{{bugList.length}}个，已解决{{resolvedCount}}个</span>
    </div>
</template>

<script>
    export default {
        name : 'BugFooter',
        props : ['bugList', 'clearResolvedCallback'],
        methods: {
            clearResolved(){
                this.clearResolvedCallback()
            }
        },
        computed : {
            resolvedCount(){
                // 采用普通的计数器的方式
                /* let count = 0
                this.bugList.forEach((bug) => {
                    if(bug.resolved) count++
                })
                return count */
                // 使用ES6数组的reduce方法进行对数组条件统计。
                // this.bugList.reduce(回调函数, 统计起点)
                // 统计起点从0开始。
                // 回调函数有两个参数：a , b
                // 回调函数的调用次数和数组中元素总数有关系。数组中有三个元素，则这个回调函数被调用三次。
                // a是什么？a是上一次回调函数调用之后的返回值。
                // b是什么？当前被统计的对象。(bug对象)
                /* const count = this.bugList.reduce((a, b) => {
                    return a + (b.resolved ? 1 : 0)
                }, 0)
                return count */

                // 简写
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