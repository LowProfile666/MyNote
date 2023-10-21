
// 导入vue-router插件
import VueRouter from "vue-router"

// 导入组件
import HeBei from '../components/HeBei'
import HeNan from '../components/HeNan'

// 创建路由器对象（在路由器对象中配置路由。）
const router = new VueRouter({
    // 在这里配置所有的路由规则。
    routes : [
        // 这就是一个路由
        {
            // 只要路径监测到的是 /hebei，就切换到HeBei组件.
            // 这个可以看做就是路由的key
            path : '/hebei',
            // 这个可以看做就是路由的value，路由的value是一个组件。
            component : HeBei
        },
        {
            // 注意：这个路径要以 / 开始。
            path : '/henan',
            component : HeNan
        }
    ]
})

// 暴露路由器对象(导出路由器对象)
export default router