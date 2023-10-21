import Vue from 'vue'

import Vuex from 'vuex'

Vue.use(Vuex)

// 怎么拆分模块？vuex建议，一个功能最好对应一个模块。
// 这里业务非常简单，我就把整个系统拆分为两个模块：a模块和b模块。(a业务和b业务)
// a模块
const a = {
    // 开启命名空间
    namespaced : true,
    actions : {
        doA1(){
            console.log('doA1 action...')
        }
    },
    mutations : {
        doA2(){
            console.log('doA2 mutation...')
        }
    },
    state : {
        a : 1
    },
    getters : {
        computedA(){
            return 1
        }
    }
}

// b模块
const b = {
    // 开启命名空间
    namespaced : true,
    actions : {
        doB1(){
            console.log('doB1 action...')
        }
    },
    mutations : {
        doB2(){
            console.log('doB2 mutation...')
        }
    },
    state : {
        b : 1
    },
    getters : {
        computedB(){
            return 1
        }
    }
}

const c = {
    // 开启命名空间
    namespaced : true,
    actions : {
        doA1(){
            console.log('c模块的doA1执行了。')
        }
    }
}

export default new Vuex.Store({
    modules : {
        // aModule是a模块的名字
        aModule : a,
        // bModule是b模块的名字
        bModule : b,
        cModule : c
    }
})