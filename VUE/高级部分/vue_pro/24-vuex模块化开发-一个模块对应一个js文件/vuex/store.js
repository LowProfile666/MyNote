import Vue from 'vue'

import Vuex from 'vuex'

Vue.use(Vuex)

import aModule from './a'
import bModule from './b'
import cModule from './c'

export default new Vuex.Store({
    modules : {aModule, bModule, cModule}
})