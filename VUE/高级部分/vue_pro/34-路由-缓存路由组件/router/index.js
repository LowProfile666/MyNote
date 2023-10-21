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
                    name : 'shi',
                    path : 'sjz/:a1/:a2/:a3',
                    component : City,
                    props : true
                },
                {
                    name : 'han',
                    path : 'hd/:a1/:a2/:a3',
                    component : City,
                    props : true
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