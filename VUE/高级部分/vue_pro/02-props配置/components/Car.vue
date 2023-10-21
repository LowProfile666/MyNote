<template>
    <div>
        <h3>品牌：{{brand}}</h3>
        <h3>价格：{{cprice}}</h3>
        <h3>颜色：{{color}}</h3>
        <button @click="add">价格加1</button>
    </div>
</template>

<script>
export default {
    name : 'Car',
    data() {
        return {
            cprice : this.price
        }
    },
    methods : {
        add(){
            this.cprice++
        }
    },
    /* data() {
        return {
            brand : '宝马520',
            price : 10,
            color : '黑色'
        }
    }, */

    // 在Car这个子组件当中使用props配置项进行数据的接收。
    // 第一种：简单的接收方式，直接采用数组接收。
    //props : ['brand','color','price']
    // 第二种：添加类型限制
    /* props : {
        brand : String,
        color : String,
        price : Number
    } */
    // 第三种：添加类型限制，并且还可以添加默认值，还可以添加必要性
    // 避免直接更改prop，因为每当父组件重新渲染时，该值都会被覆盖
    // 注意：不要修改prop中的数据。
    props : {
        brand : {
            type : String,
            required : true
        },
        color : {
            type : String,
            default : '红色'
        },
        price : {
            type : Number,
            required : true
        }
    }

}
</script>