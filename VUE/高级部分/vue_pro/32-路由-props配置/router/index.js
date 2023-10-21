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
                    // 在路由当中进行的配置。
                    /* props : {
                        x : '张三',
                        y : '李四'
                    } */
                    // props含有有种函数式写法。
                    /* props($route){ // $route将来会被自动传过来，它代表了当前的路由对象。变量名随意的。
                        return {
                            a1 : $route.params.a1,
                            a2 : $route.params.a2,
                            a3 : $route.params.a3,
                            x : '李四',
                            y : '王五'
                        }
                    } */
                    // 这种方式只支持params方式的传参。不支持query方式。
                    // 将params对象直接转换成props对象，内部直接转换，不需要我们负责。
                    props : true
                },
                {
                    name : 'han',
                    path : 'hd/:a1/:a2/:a3',
                    component : City,
                    /* props(t){
                        return {
                            a1 : t.params.a1,
                            a2 : t.params.a2,
                            a3 : t.params.a3,
                            x : 'hehe',
                            y : 'haha'
                        }
                    } */
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