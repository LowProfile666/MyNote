// 定义一个Vue类
class Vue {
    // 定义构造函数
    // options是一个简单的纯粹的JS对象：{}
    // options对象中有一个data配置项
    constructor(options){
        // 获取所有的属性名
        Object.keys(options.data).forEach((propertyName, index) => {
            //console.log(typeof propertyName, propertyName, index)
            let firstChar = propertyName.charAt(0)
            if(firstChar != '_' && firstChar != '$'){
                Object.defineProperty(this, propertyName, {
                    get(){
                        return options.data[propertyName]
                    },
                    set(val){
                        options.data[propertyName] = val
                    }
                })
            }
        })
        // 获取所有的方法名
        Object.keys(options.methods).forEach((methodName, index) => {
            // 给当前的Vue实例扩展一个方法
            this[methodName] = options.methods[methodName]
        })
    }
}