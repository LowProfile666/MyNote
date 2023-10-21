// 引入Vue，因为下面使用Vuex插件的时候需要Vue
import Vue from 'vue'

// 引入vuex插件
import Vuex from 'vuex'

// 使用插件
Vue.use(Vuex)

// 创建三个vuex插件的核心对象：actions对象、mutations对象、state对象
const actions = {
    // N多个action
    // 每一个action都是一个callback（回调函数）
    // 在action这种回调函数中编写复杂的业务逻辑
    // 有个原则：action是专门用来处理业务逻辑，或者说发送AJAX请求的。
    //plusOne : function(){}
    // 简写
    // context参数：context是vuex的上下文(context可以看做是store对象的缩小版)
    // value参数：传过来的数据
    plusOne(context, value){ 
        // 处理业务
        value = value + 1
        // 调用其它的action这个回调函数
        //context.dispatch('otherAction', value)
        // 业务逻辑处理完成之后，继续向下一个环节走，就轮到了数据的更新。
        // 提交上下文环境（所有的事儿都做完了，该最后一步了，更新数据了，怎么办？提交）
        context.commit('PLUS_ONE', value)
    },

    // 这里可能还会有其它的action
    // ...
    /* otherAction(context, value){        
        console.log(6666)
    } */
}
const mutations = {
    // N多个mutation
    // 每一个mutation都是一个callback（回调函数）
    // 每一个mutation这个回调函数的作用就是：更新state
    // 只要state一更新，因为是响应式的，所以页面就重新渲染了。
    // state参数：状态对象
    // value参数：上一环节传过来的数据
    PLUS_ONE(state, value){
        state.num += value
    }
}

// 等同于Vue当中的data（只不过这里我们不叫做数据，叫做状态）
// 状态对象（数据对象），已经做了响应式处理的。
const state = {
    num : 0
}

// 简写形式
export default new Vuex.Store({actions,mutations,state})


/* // 创建store对象（这个store对象是vuex插件中的老大，最核心的对象，这个对象store是用来管理actions对象、mutations对象、state对象。）
const store = new Vuex.Store({
    // 它是一个负责执行某个行为的对象
    actions : actions,
    // 它是一个负责更新的对象
    mutations : mutations,
    // 它是一个状态对象
    state : state
})

// 导出store对象（暴露之后，别人想用可以使用import进行引入）
export default store */