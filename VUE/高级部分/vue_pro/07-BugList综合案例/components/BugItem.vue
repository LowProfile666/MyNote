<template>
    <tr>
        <!-- <td><input type="checkbox" :checked="bug.resolved" @click="modifyResolved"></td> -->
        <td><input type="checkbox" :checked="bug.resolved" @change="modifyResolved(bug.id)"></td>
        <!-- <td><input type="checkbox" v-model="bug.resolved"></td> -->
        <td>
            <span v-show="!bug.editState" class="desc" @click="enterEdit(bug)">{{ bug.desc }}</span>
            <input ref="inputDesc" v-show="bug.editState" type="text" :value="bug.desc" @blur="updateDesc(bug, $event)">
        </td>
        <td><button class="small red button" @click="deleteById(bug.id)">删除</button></td>
    </tr>
</template>

<script>
    export default {
        name : 'BugItem',
        props : ['bug', 'modifyResolvedCallback', 'deleteByIdCallback', 'updateDescCallback'],
        methods : {
            modifyResolved(bugId){
                this.modifyResolvedCallback(bugId)
            },
            deleteById(bugId){
                this.deleteByIdCallback(bugId)
            },
            // 进入编辑状态
            enterEdit(bug){
                if(bug.hasOwnProperty('editState')){
                    bug.editState = true
                }else{
                    // 这里的代码只会第一次的时候执行。
                    this.$set(bug, 'editState', true)
                }
                // 获取文本框，并且让文本框获得焦点
                // 第一种方案：
                /* setTimeout(() => {    
                    this.$refs.inputDesc.focus()    
                }) */
                // 第二种方案：使用Vue提供好的API就行了。
                // 非常重要：nextTick方法会绑定一个回调函数，这个回调函数在什么时候执行？在下一次DOM全部渲染完毕后被调用。
                this.$nextTick(function(){
                    this.$refs.inputDesc.focus()  
                })
            },
            updateDesc(bug, e){
                // 获取最新的描述信息
                let newDesc = e.target.value.trim()
                if(!newDesc) return
                // 更新描述信息
                this.updateDescCallback(bug.id, newDesc)
                // 隐藏文本框
                bug.editState = false
            }
        }
    }

</script>

<style scoped>
/* item */
table tbody tr:nth-child(odd){
	background-color: #eee;
}
table tbody tr:hover{
	background-color: #ccc;
}
table tbody tr td:first-child{
	color: #f40;
}
td{
	border: 1px solid #999;
	text-align: center;
	padding: 5px 0;
}
.desc {
    cursor: pointer;
}
</style>