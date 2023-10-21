// 引入Vue，因为下面使用Vuex插件的时候需要Vue
import Vue from 'vue'

// 引入vuex插件
import Vuex from 'vuex'

// 使用插件
Vue.use(Vuex)

// 创建三个vuex插件的核心对象：actions对象、mutations对象、state对象
const actions = {}
const mutations = {}
const state = {}

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