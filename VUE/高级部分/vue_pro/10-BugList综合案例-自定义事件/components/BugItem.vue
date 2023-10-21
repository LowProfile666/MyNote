<template>
    <tr>
        <td><input type="checkbox" :checked="bug.resolved" @change="modifyResolved(bug.id)"></td>
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
            enterEdit(bug){
                if(bug.hasOwnProperty('editState')){
                    bug.editState = true
                }else{
                    this.$set(bug, 'editState', true)
                }
                this.$nextTick(function(){
                    this.$refs.inputDesc.focus()  
                })
            },
            updateDesc(bug, e){
                let newDesc = e.target.value.trim()
                if(!newDesc) return
                this.updateDescCallback(bug.id, newDesc)
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