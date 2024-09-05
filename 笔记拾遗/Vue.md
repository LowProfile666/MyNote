# Vue3使用Vuex

安装：

```
npm install vuex
```

在store/index.js，创建store对象：

```js
import {createStore} from "vuex";

export default createStore({
    state: {
        loginUser: {}
    },
    mutations: {
        LOGIN(state, value) {
            state.loginUser = value;
        }
    },
    actions: {
        login(context, value) {
            context.commit("LOGIN", value);
        }
    },
    getters: {}
});
```

在src/main.js中引入store对象并使用：

```js
import store from "./store/index.js";

app.use(store).mount('#app')
```

在组件中使用：

```js
import {useStore} from "vuex";

const store = useStore();
store.dispatch("login", {});
let userId = store.state.loginUser.id;
```

store的数据是存在内存中的，如果刷新了页面，store中的数据就会重置。使用location.href改变地址或者手动刷新按f5，都会让store中的数据消失。而是用路由器切换路由则不会。

# Vue3使用props

在使用这样的写法时：

```vue
<script setup>
    
</script>
```

没有props属性，那么要父组件传过来的值，需要使用defineProps函数：

```js
const props = defineProps({
    id,
    name: String
})
console.log(props.id)
```

如果是路由参数，需要使用路由对象来获取：

```js
const route = useRoute();
const {id, name} = route.params;
console.log(id)
```

# Vue3使用路由

使用useRouter和useRoute获取路由器对象和路由对象：

```js
import {useRoute, useRouter} from "vue-router";

const router = useRouter();
const route = useRoute();
```

useRouter获得的路由器对象是唯一的，整个应用中所有组件获得的路由器对象都是同一个。

useRoute获得的路由对象只是当前激活路由的对象，每一次获取都是一个新的对象。

