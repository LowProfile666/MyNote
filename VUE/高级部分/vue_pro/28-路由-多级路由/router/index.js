import VueRouter from "vue-router"
import HeBei from '../pages/HeBei'
import HeNan from '../pages/HeNan'
import ShiJiaZhuang from '../pages/ShiJiaZhuang'
import HanDan from '../pages/HanDan'

const router = new VueRouter({
    routes : [
        {
            path : '/hebei',
            component : HeBei,
            // 子路由们
            children : [
                // 这是其中的一个子路由
                {
                    // 注意：对于子路由来说，这个path不要以 / 开始，这个 / 系统会自动添加。
                    path : 'shijiazhuang',
                    component : ShiJiaZhuang
                },
                {
                    path : 'handan',
                    component : HanDan
                }
            ]
        },
        {
            path : '/henan',
            component : HeNan
        }
    ]
})
export default router