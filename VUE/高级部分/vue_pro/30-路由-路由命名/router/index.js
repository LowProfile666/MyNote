import VueRouter from "vue-router"
import HeBei from '../pages/HeBei'
import HeNan from '../pages/HeNan'
import City from '../pages/City'

const router = new VueRouter({
    routes : [
        {
            path : '/hebei',
            component : HeBei,
            children : [
                {
                    // 给路由命名
                    name : 'shi',
                    path : 'sjz',
                    component : City
                },
                {
                    // 给路由命名
                    name : 'han',
                    path : 'hd',
                    component : City
                },
            ]
        },
        {
            path : '/henan',
            component : HeNan
        }
    ]
})
export default router