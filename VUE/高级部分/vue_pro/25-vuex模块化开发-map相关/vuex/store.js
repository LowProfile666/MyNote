import Vue from 'vue'

import Vuex from 'vuex'

Vue.use(Vuex)

import aModule from './a'
import bModule from './b'

export default new Vuex.Store({
    modules : {aModule, bModule}
})