<template>
    <div>
        <!-- 
            1.关于内置事件的实现步骤。
                第一步：提供事件源（以下这个按钮就是一个事件源）
                第二步：给事件源绑定事件
                    v-on:事件名  或者  @事件名
                第三步：编写回调函数，将回调函数和事件进行绑定
                第四步：等待事件的触发，只要事件触发，则执行回调函数。
            2.关于组件的自定义事件，实现步骤：
                第一步：提供事件源（这个事件源是一个组件）
                第二步：给组件绑定事件
                    v-on:事件名  或者  @事件名
                第三步：编写回调函数，将回调函数和事件进行绑定
                第四步：等待事件的触发，只要事件触发，则执行回调函数。
                    对于组件自定义事件来说，要想让事件发生，需要去执行一段代码。
                    这段代码负责去触发这个事件，让这个事件发生。
                    这段代码在哪里写？
                        事件绑定在A组件上，则触发这个事件的代码要在A组件当中编写。
            3.总结：到目前为止，父子组件之间如何通信
                父---子：
                    props
                子---父：
                    第一种方式：在父中定义一个方法，将方法传递给子，然后在子中调用父传过来的方法，这样给父传数据。（这种方式以后很少使用）
                    第二种方式：使用组件的自定义事件的方式，也可以完成子向父传数据。
                        App组件是父组件
                        User组件是子组件
                        子组件向父组件传数据（User给App组件传数据）：
                            在父组件当中绑定事件。
                            在子组件当中触发事件。
                        父绑定，子触发。（这句话记住）
            4. 对于事件的once修饰符来说，组件的自定义事件也是可以使用的。
         -->
        <button @click.once="hello">内置事件的实现步骤</button>

        <!-- 给User组件绑定一个自定义的事件 -->
        <!-- <User v-on:event1.once="doSome"></User> -->
        <User v-on:event1="doSome" @event2="doOther"></User>

        <!-- 简写形式 -->
        <!-- <User @event1.once="doSome"></User> -->
        <User @event1="doSome" @event2="doOther"></User>

        <!-- 准备一个组件 -->
        <User ref="user"></User>

    </div>
</template>

<script>
    import User from './components/User.vue'
    export default {
        name : 'App',
        mounted() {
            // 给ref="user"的组件绑定event1事件，并且给event1事件绑定一个回调函数：doSome
            this.$refs.user.$on('event1', this.doSome)

            // 如果回调函数是普通函数：函数体当中的this是User组件实例。不是App组件实例。
            /* this.$refs.user.$on('event1', function(){
                console.log(this)
            }) */

            // 如果回调函数是箭头函数：那么函数体当中的this就是App组件实例。
            /* this.$refs.user.$on('event1', () => {
                console.log(this)
            }) */

            this.$refs.user.$on('event2', this.doOther)
            // 保证事件只触发一次。
            //this.$refs.user.$once('event1', this.doSome)
        },
        methods: {
            hello(){
                console.log('hello vue!')
            },
            /* doSome(name, age, gender){
                console.log(name, age, gender)
            } */
            // ES6的语法，...params这个params可以看做是一个数组。以数组的形式接收多个参数。
            doSome(name, ...params){
                console.log(name, params)
            },
            doOther(){
                console.log('do other!')
            }
        },
        components : {User}
    }
</script>
