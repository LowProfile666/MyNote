import {reactive} from 'vue'

export default function(){
    // data
    let data = reactive({
        num1 : 0,
        num2 : 0,
        result : 0
    })
    // methods
    function sum(){
        data.result = data.num1 + data.num2
    }
    // 返回一个对象
    return {data, sum}
}