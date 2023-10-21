import Vue from 'vue'

import Vuex from 'vuex'

Vue.use(Vuex)

const actions = {
    saveUser(context, value){
        context.commit('SAVE_USER', {id:Date.now(), name:value})
    },
    /* saveVip(context, value){
        context.commit('SAVE_VIP', value)
    } */
}
const mutations = {
    SAVE_USER(state, value){
        state.users.unshift(value)
    },
    SAVE_VIP(state, value){
        state.vips.unshift({id:Date.now(), name:value})
    }
}
const state = {
    uname : '', 
    users : [
        {id:'001', name:'孙悟空'},
        {id:'002', name:'猪八戒'},
        {id:'003', name:'沙和尚'}
    ],
    vips : [
        {id:'001', name:'高启强'},
        {id:'002', name:'高启盛'},
        {id:'003', name:'张三'}
    ]
}

const getters = {
    reversedName(state){ 
        return state.uname.split('').reverse().join('')
    }
}

export default new Vuex.Store({actions, mutations, state, getters})