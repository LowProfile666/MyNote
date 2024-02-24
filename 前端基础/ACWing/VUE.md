[Vue官网](https://vuejs.org/)

# 1、配置环境

## 终端

Linux和Mac上可以用自带的终端。
Windows上推荐用powershell或者cmd。Git Bash有些指令不兼容。

## 安装Nodejs

[安装地址](https://nodejs.org/en/)

## 安装@vue/cli

打开Git Bash，执行：

```bash
npm i -g @vue/cli
```

如果执行后面的操作有bug，可能是最新版有问题，可以尝试安装早期版本，比如：`npm i -g @vue/cli@4`

## 启动vue自带的图形化项目管理界面

```bash
vue ui
```

常见问题1：Windows上运行vue，提示无法加载文件，表示用户权限不足。
解决方案：用管理员身份打开终端，输入`set-ExecutionPolicy RemoteSigned`，然后输入y

## 创建项目

使用 Vue 的图形界面管理页面，左上角点击下拉选择，Vue项目管理器

![image-20240216194300056](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402161943137.png)

然后来到项目管理页面，点击新建项目

![image-20240216194440337](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402161944416.png)

输入项目名，基本设置：

![image-20240216195102596](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402161951671.png)

预设选择 Vue3

![image-20240216195129435](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402161951509.png)

项目创建成功后，就会在指定的目录下新建一个项目文件夹。并且 Vue 的图形界面会跳到下面的页面：

![image-20240216195722529](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402161957609.png)

+ 插件页面是显示所有安装的插件
+ 依赖页面是所有安装的包，比如 bootstrap
+ 任务页面可以用来调试

安装一个 router 和 vuex 插件

+ router：路由
+ vuex：类似于 React 中的 Redux

安装一个 bootstrap 的依赖。

## 项目结构

![image-20240216223534851](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402162236255.png)

views：用来放页面文件的

routers：写路由

components：存各种组件

main.js：整个程序的入口

# 2、基本概念

## .vue 文件

.vue 文件是 Vue 自己定义的类型文件，每个页面都是一个 .vue 文件，每个 .vue 文件都会由三部分组成：HTML 部分、CSS 部分、JS 部分，这个 CSS 部分可以加一个属性 scoped，这样不同组件之间的样式不会相互影响。

```vue
<template></template>
<script></script>
<style scoped></style>
```

每个 vue 组件都会导出一个对象：

```vue
<script>
    export default {
        name: 'HomeView',
        components: {

        }
    }
</script>
```

+ components：表示在 template 区域会用到哪些其他的组件，把需要用到的组件放在这个属性里面

## script部分

export default对象的属性：

+ name：组件的名称

+ components：存储<template>中用到的所有组件

+ props：存储父组件传递给子组件的数据

+ watch()：当某个数据发生变化时触发

+ computed：动态计算某个数据

  ```js
  import { computed } from 'vue'
  ```

+ setup(props, context)：初始化变量、函数
  + ref定义变量，根据给定的值创建一个响应式的数据对象，可以用.value属性重新赋值，可以接收普通变量类型
  
    + ref定义的变量，改变值要.value,而且在template中不用写.value
  
  + reactive定义对象，响应式的数据对象，不可重新赋值，只能用来接收对象，效率比 ref 高一些
  
    ```js
    import { reactive } from 'vue'
    ```
  
  + props存储父组件传递过来的数据
  
  + context.emit()：触发父组件绑定的函数

## template部分

+ <slot></slot>：存放父组件传过来的children。
+ v-on:click或@click属性：绑定事件
+ v-if、v-else、v-else-if属性：判断
+ v-for属性：循环，:key循环的每个元素需要有唯一的key
+ v-bind:或:：绑定属性

## style部分

`<style>` 标签添加scope属性后，不同组件间的css不会相互影响。

## 第三方组件

+ view-router包：实现路由功能。
+ vuex：存储全局状态，全局唯一。
  + state: 存储所有数据，可以用modules属性划分成若干模块
  + getters：根据state中的值计算新的值
  + mutations：所有对state的修改操作都需要定义在这里，不支持异步，可以通过$store.commit()触发
  + actions：定义对state的复杂修改操作，支持异步，可以通过$store.dispatch()触发。注意不能直接修改state，只能通过mutations修改state。
  + modules：定义state的子模块

# 实现网站

整个网站可以分为两部分，第一部分是上面的导航栏 navbar，第二部分是导航栏下面的内容部分 content。

+ 不同的页面导航栏都是一样的，不一样的是内容部分

需要实现的页面：

+ 首页
+ 好友列表
+ 好友动态
+ 登录
+ 注册
+ 404

先删除新建项目中的无用代码文件。

## 导航栏组件

在 components 下新建一个 .vue 文件，用作导航栏组件：

```vue
<template>
    <nav class="navbar navbar-expand-lg bg-body-tertiary">
      <div class="container">
        <a class="navbar-brand" href="#">Myspace</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav me-auto mb-2 mb-lg-0">
            <li class="nav-item">
              <a class="nav-link active" aria-current="page" href="#">首页</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">好友列表</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="#">用户动态</a>
            </li>
          </ul>
          <ul class="navbar-nav mb-2 mb-lg-0">
                <li class="nav-item">
                  <a class="nav-link" href="#">登录</a>
                </li>
                <li class="nav-item">
                  <a class="nav-link" href="#">注册</a>
                </li>
              </ul>
        </div>
      </div>
    </nav>
</template>

<script>
export default {
    name: "NavBar",
}
</script>

<style scoped></style>
```

使用了 bootstrap，需要在 main.js 中引入 bootstrap 的文件：

```js
import 'bootstrap/dist/css/bootstrap.css';
import 'bootstrap/dist/js/bootstrap.js'
```

如果出现以下报错：

![image-20240216225908035](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402162259080.png)

那么需要在 vue 图形界面管理中安装一下 @popperjs/core 依赖。

然后在根组件 App.vue 中使用 NavBar：

```vue
<template>
  <NavBar />
  <router-view/>
</template>

<script>
import NavBar from './components/NavBar.vue';

export default {
  name: "App",
  components: {
      NavBar
    }
  }
</script>

<style>

</style>
```

+ 在 template 中使用了 NavBar 组件，那么 export 中就必须要在 components 中添加 NavBar。

当前效果：

![image-20240216231122703](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402162311742.png)

接下来是写页面，一共要写六个页面，先定义六个组件，如果一个页面过于庞大的话还可以继续拆分组件。

## 首页

首页就在自带的 HomeView.vue 中修改代码，使用 bootstrap 的卡片样式和 container 样式：

```vue
<template>
  <div class="home">
    <div class="container">
      <div class="card">
        <div class="card-body">
          首页
        </div>
    </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'HomeView',
  components: {

  }
}
</script>

<style scoped>
  .container {
    margin-top : 20px;
  }
</style>
```

+ 这里的样式如果不写 scoped 的话，会发现这个上边距会影响到导航栏的上边距

## 好友列表页面

在 views 下新建一个 userListView.vue 文件

```vue
<template>
    <div class="user-list">
        <div class="container">
            <div class="card">
                <div class="card-body">
                    好友列表
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: 'UserListView',
    components: {

    }
}
</script>

<style scoped>
.container {
    margin-top: 20px;
}
</style>
```

会发现，这两个页面的内容区域其实是一样的代码，像这种几个页面一样的部分可以抽出来作为一个单独的组件定义，这样方便维护修改。

## 定义内容组件

在 components 下定义一个 Content.vue 文件，用来表示公用的内容区域组件：

```vue
<template>
<div class="home">
    <div class="container">
        <div class="card">
            <div class="card-body">

            </div>
        </div>
    </div>
</div>
</template>

<script>
export default {
    name: 'PageContent',
}
</script>

<style scoped>
.container {
    margin-top: 20px;
}
</style>
```

+ 这里 export 的时候，name 取 Content 的话会报错：

  ```vue
  [eslint] 
  D:\MyCode\VUE3\myspace\src\components\Content.vue
    15:11  error  Component name "Content" should always be multi-word  vue/multi-word-component-names
  ```

  所以换了驼峰命名法取名

然后修改首页、好友列表页面的代码：

HomeView.vue

```vue
<template>
<PageContent>
  首页
</PageContent>
</template>

<script>
import PageContent from '@/components/Content.vue';

export default {
  name: 'HomeView',
  components: {
    PageContent,
  }
}
</script>

<style scoped></style>
```

然后就是如何将 “首页” 这两个字使用到 PageContent 组件中。有一个标签 `<slot></slot>` ，它会将使用组件时，所有的子元素全部渲染出来，所以 PageContent 组件的模板：

```vue
<template>
<div class="home">
    <div class="container">
        <div class="card">
            <div class="card-body">
                <slot></slot>
            </div>
        </div>
    </div>
</div>
</template>
```

然后将好友列表的页面也修改：

```vue
<template>
<PageContent>
    好友列表
</PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';

export default {
    name: 'UserList',
    components: {
        PageContent
    }
}
</script>

<style scoped>
</style>
```

## 用户动态页面

UserProfileView.vue

```vue
<template>
    <PageContent>
        用户动态
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';

export default {
    name: 'UserProfile',
    components: {
        PageContent
    }
}
</script>

<style scoped></style>

```

需要实现三个模块：个人信息、历史帖子、发帖

![image-20240217090443154](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402170905775.png)

将这三个模块，拆分为三个组件来写。

以上布局可以使用 bootstrap 的 grid 来实现。比如，左边部分占 3 份，右边部分占 9 份。

所在在 UserProfileView.vue 中：

```vue
<template>
    <PageContent>
        <div class="row">
            <div class="col-3">用户信息</div>
            <div class="col-9">帖子列表</div>
        </div>
    </PageContent>
</template> 
```

+ PageContent 组件中有了 container，所以直接写在 PageContent 中即可。

当前效果：

![image-20240217092927319](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402170929425.png)

### 个人信息组件

这一模块也分为左右两部分，左边是头像，右边是一些数据内容，所以也可使用 grid 实现。

UserProfileInfo.vue

```vue
<template>
<div class="card">
    <div class="card-body">
        <div class="row">
        <div class="col-3">
            <img class="img-fluid" src="https://cdn.acwing.com/media/user/profile/photo/307620_lg_6513a93905.jpeg" alt="">
        </div>
        <div class="col-9">
            <div class="username">Shimao Zhang</div>
            <div class="fans">粉丝：123</div>
            <button class="btn btn-secondary btn-sm">+关注</button>
        </div>
    </div>
    </div>
</div>
</template>

<style scoped>
.username {
    font-weight: bold;
}
.fans {
    font-size: 12px;
    color: grey;
}
button {
    padding: 2px 4px;
    font-size: 11px;
}
</style>

<script>
export default {
    name: "UserProfileInfo",
}
</script>
```

+ `img-fluid` 是 bootstrap 的响应式图片样式，自动调整图片的样式

然后在页面中使用该组件：

```vue
<template>
    <PageContent>
        <div class="row">
            <div class="col-3">
                <UserProfileInfo />
            </div>
            <div class="col-9">帖子列表</div>
        </div>
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';
import UserProfileInfo from '@/components/UserProfileInfo.vue';

export default {
    name: 'UserProfileView',
    components: {
        PageContent,
        UserProfileInfo,
    }
}
</script>

<style scoped></style>
```

当前效果：

![image-20240217092747402](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402170927521.png)

### 数据的交互

当前用户状态的访问地址是：http://localhost:8080/userProfile，应该有一些参数，比如用户的 id，这样来展示不同的用户。还有发帖的组件和帖子列表的组件之间也会存在数据交互。所以把这三个模板需要交互的数据存到最顶层的组件里面，也就是当前 UserProfileView 。

怎么存储数据？

在 export default 的对象中定义一个 setup 函数：

```js
export default {
    //...
    setup: () => {}
}
```

在一个对象里面，如果一个属性是函数，可以直接这样写：

```js
export default {
    //...
    setup() {
        
    }
}
```

在 setup 函数中定义数据：

```js
import { reactive } from 'vue';

export default {
    name: 'UserProfileView',
    components: {
        PageContent,
        UserProfileInfo,
    },
    setup() {
        const user = reactive({
            id: 1,
            username: "zsm",
            firstname: "Shimao",
            lastname: "Zhang",
            followers: 0,
            is_followd: false,
        })
        return {
            // user: user,  // 名字一样，可以简写
            user,
        }
    }
}
```

+ 在 setup 函数中定义的数据，需要用到其他地方的数据就需要 return 出去

这样这个 user 对象就可以在其他组件中使用了。

在 Vue 中，父组件向子组件传递数据是通过 props 属性的，子组件向父组件传递信息是通过事件触发的。

在 UserProfileView 中向 UserProfileInfo 组件传数据 user：

```vue
<div class="col-3">
    <UserProfileInfo :user="user"/>
</div>
```

+ `:` 是 `v-bind:` 的缩写，用来绑定数据，`"user"` 双引号中的是一个表达式。

UserProfileInfo 组件要接收传过来的数据的话，要在 export default 中声明一个 props 属性：

```js
export default {
    name: "UserProfileInfo",
    props: {
        user: {
            type: Object,
            required: true,
        },
    }
}
```

然后就可以在 UserProfileInfo 组件中使用这个 user 属性：

```vue
<div class="col-9">
    <div class="username">{{user.username}}</div>
    <div class="fans">粉丝：{{ user.followers }}</div>
    <button class="btn btn-secondary btn-sm">+关注</button>
</div>
```

+ 对象的属性使用要在 `{{ }}` 之间

如果希望显示的数值是通过动态计算出来的，vue 中也有一个特殊的类型 computed，它可以动态的计算某个属性。

比如将 username 改为 lastname + firstname：

```js
import { computed } from 'vue';

export default {
    name: "UserProfileInfo",
    props: {
        user: {
            type: Object,
            required: true,
        },
    },
    setup(props) {
        const fullname = computed(() => props.user.lastname + ' ' + props.user.firstname);
        return {
            fullname,
        }
    }
}
```

+ setup 函数是用来定义数据的，所以需要使用 setup 函数
+ setup 函数中没有 this，所以要把 props 传过来

然后直接使用 fullname：

```vue
<div class="col-9">
    <div class="username">{{ fullname }}</div>
    <div class="fans">粉丝：{{ user.followers }}</div>
    <button class="btn btn-secondary btn-sm">+关注</button>
</div>
```

当前效果：

![](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171013295.png)

### 关注按钮

实现关注按钮的功能：未关注时，点击关注；已关注时，点击取消关注。使用 `v-if` 属性。

在 UserProfileInfo 组件中：

```vue
<div class="col-9">
    <div class="username">{{ fullname }}</div>
    <div class="fans">粉丝：{{ user.followers }}</div>
    <button v-if="!user.is_followed" class="btn btn-secondary btn-sm">+关注</button>
    <button v-else class="btn btn-secondary btn-sm">取消关注</button>
</div>
```

+ 如果 `v-if` 后的表达式为 true 的话，则会渲染当前按钮
+ 否则，会渲染 `v-else` 所在的按钮

此时，当 user.is_followed 为 true 时：

![image-20240217102107604](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171021757.png)

然后实现点击按钮后，加关注或取消关注。点击按钮后，需要触发事件，修改 user.is_followed 的值

在 UserProfileInfo 组件的 setup 中定义两个函数 follow 和 unfollow，

```js
setup(props) {
    const fullname = computed(() => props.user.lastname + ' ' + props.user.firstname);

    const follow = () => {
        console.log("follow");
    }

    const unfollow = () => {
        console.log("unfollow");
    }

    return {
        fullname,
        follow,
        unfollow
    }
}
```

+ 当前组件需要使用到的数据、函数等，都在 setup 中定义，并通过 return 返回出来。

给按钮绑定事件，使用 `v-on:click` ，可以绑定一个事件，缩写为：`@click`

```vue
<div class="col-9">
    <div class="username">{{ fullname }}</div>
    <div class="fans">粉丝：{{ user.followers }}</div>
    <button @click="follow" v-if="!user.is_followed" class="btn btn-secondary btn-sm">+关注</button>
    <button @click="unfollow" v-else class="btn btn-secondary btn-sm">取消关注</button>
</div>
```

接下来就是修改 user 的状态，但是 user 是定义在父组件 UserProfileView 中的，所以涉及到子组件向父组件传递信息，是通过绑定事件触发的。

在 UserProfileView 中，setup 中添加两个函数 follow 和 unfollow，然后给 UserProfileInfo 组件上绑定这两个函数：

```vue
<template>
    <PageContent>
        <div class="row">
            <div class="col-3">
                <UserProfileInfo @follow="follow" @unfollow="unfollow" :user="user"/>
            </div>
            <div class="col-9">
                <UserProfilePosts />
            </div>
        </div>
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';
import UserProfileInfo from '@/components/UserProfileInfo.vue';
import UserProfilePosts from '@/components/UserProfilePosts.vue';
import { reactive } from 'vue';

export default {
    name: 'UserProfileView',
    components: {
        PageContent,
        UserProfileInfo,
        UserProfilePosts,
    },
    setup() {
        const user = reactive({
            id: 1,
            username: "zsm",
            firstname: "Shimao",
            lastname: "Zhang",
            followers: 0,
            is_followed: true,
        })
        const follow = () => {
            if (user.is_followed) return;
            user.is_followed = true;
            user.followers++;
        }
        const unfollow = () => {
            if (!user.is_followed) return;
            user.is_followed = false;
            user.followers--;
        }
        return {
            user: user,
            follow,
            unfollow,
        }
    }
}
</script>

<style scoped></style>
```

+ 在子组件 UserProfileInfo 上绑定了 follow 和 unfollow 两个事件，子组件可以调用到这两个事件，事件名称可以随意

所以我们如果想修改父组件 UserProfileView 中的 user 的值，那么只能通过触发父组件的这两个函数。那么怎么触发这两个函数？

使用 `context.emit()` 可以触发父元素绑定的函数。

在 UserProfileInfo 组件的  follow 和 unfollow 中，通过 `context.emit()` 来触发父组件的函数，这个 `context` 是一个 setup 中的参数：

```js
setup(props, context) {
    const fullname = computed(() => props.user.lastname + ' ' + props.user.firstname);

    const follow = () => {
        context.emit("follow");
    }

    const unfollow = () => {
        context.emit("unfollow");
    }

    return {
        fullname,
        follow,
        unfollow
    }
}
```

+ `context.emit()` 中的字符串是父组件中绑定事件的名称

这样，当点击 UserProfileInfo 组件的关注按钮时，会触发 UserProfileInfo 组件的 follow 或 unfollow 函数，通过这两个函数又会触发到父组件 UserProfileView 中的 follow 或 unfollow 函数，就可以修改 user 的值。

### 历史帖子组件

UserProfilePosts.vue

```vue
<template>
    <div class="card">
        <div class="card-body"></div>
    </div>
</template>

<style scoped></style>

<script>
export default {
    name: "UserProfilePosts",
}
</script>
```

在 UserProfileView 中使用：

```vue
<template>
    <PageContent>
        <div class="row">
            <div class="col-3">
                <UserProfileInfo :user="user"/>
            </div>
            <div class="col-9">
                <UserProfilePosts />
            </div>
        </div>
    </PageContent>
</template>
<script>
import PageContent from '../components/Content.vue';
import UserProfileInfo from '@/components/UserProfileInfo.vue';
import UserProfilePosts from '@/components/UserProfilePosts.vue';
import { reactive } from 'vue';

export default {
    name: 'UserProfileView',
    components: {
        PageContent,
        UserProfileInfo,
        UserProfilePosts,
    },
    setup() {
        const user = reactive({
            id: 1,
            username: "zsm",
            firstname: "Shimao",
            lastname: "Zhang",
            followers: 0,
            is_followd: false,
        })
        return {
            user: user,
        }
    }
}
</script>
```

当前效果：

![image-20240217101334227](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171013393.png)

在父组件 UserProfileView 中定义帖子列表的数据：

```js
setup() {
   //...
    const posts = reactive({
        count: 3,
        posts: [
            { id: 1, userId: 1, content: "今天很开心" },
            { id: 2, userId: 1, content: "昨天很开心" },
            { id: 3, userId: 1, content: "明天很开心" },
        ]
    });
    return {
        user: user,
        follow,
        unfollow,
        posts,
    }
}
```

然后将数据传给子组件 UserProfilePosts ：

```vue
<div class="col-9">
    <UserProfilePosts :posts="posts"/>
</div>
```

然后在 UserProfilePosts 中使用：

```vue
<template>
    <div class="card">
        <div class="card-body">
            {{ posts }}
        </div>
    </div>
</template>

<style scoped></style>

<script>
export default {
    name: "UserProfilePosts",
    props: {
        posts: {
            type: Object,  // 传过来的类型
            required: true,  // 必须传过来
        }
    },

}
</script>
```

当前效果：

![image-20240217105022859](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171050038.png)

显然需要使用循环将传过来的数据进行渲染。使用 `v-for` 进行循环：

```vue
<template>
    <div class="card">
        <div class="card-body">
            <div v-for="post in posts.posts" :key="post.id">
                <div class="card" >
                    <div class="card-body">
                        {{ post.content }}
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>
```

+ `<div v-for="post in posts.posts" :key="post.id">`：`v-for` 后面的内容和普通 for 循环的语法差不多，`posts.posts` 才是需要遍历的数组，`posts` 是一个对象

+ 只要是循环操作，都需要绑定上一个 key，这个 key 不能相同。

+ `v-for` 所在 `div` 的本身以及其内部就是循环体，将数组中的每个元素构建成一个 `<div><div class="card"><div class="card-body"></div></div></div>` ，所以可以直接将 class=card 写在 v-for 所在的 `div` 上，这样会少掉一个 `div`。

  ```vue
  <div  class="card" v-for="post in posts.posts" :key="post.id">
      <!-- <div class="card" > -->
      <div class="card-body">
          {{ post.content }}
      </div>
      <!-- </div> -->
  </div>
  ```

循环中也可以使用下标：

```vue
<div  class="card" v-for="(post,index) in posts.posts" :key="post.id">
</div>
```

+ 这个 index 就是对应 post 的下标

添点样式：

```vue
<template>
    <div class="card">
        <div class="card-body">
            <div  class="card single-post" v-for="post in posts.posts" :key="post.id">
                <!-- <div class="card" > -->
                    <div class="card-body">
                        {{ post.content }}
                    </div>
                <!-- </div> -->
            </div>
        </div>
    </div>
</template>

<script>
export default {
    name: "UserProfilePosts",
    props: {
        posts: {
            type: Object,  // 传过来的类型
            required: true,  // 必须传过来
        }
    },

}
</script>

<style scoped>
.single-post {
    margin-bottom: 10px;
}
</style>
```

当前效果：

![image-20240217110559193](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171105388.png)

### 发帖组件

UserProfileWrite.vue

```vue
<template>
    <div class="card eidt-field">
        <div class="card-body">
            <label for="textarea" class="form-label">编辑帖子</label>
            <textarea class="form-control" id="textarea" rows="3"></textarea>
            <button type="button" class="btn btn-primary btn-sm">发布</button>
        </div>
    </div>
</template>

<script>
export default {
    name: "UserProfileWrite",

}
</script>

<style scoped>
.eidt-field {
    margin-top: 10px;
}
button {
    margin-top: 10px ; 
}
</style>
```

在 UserProfileView 中使用：

```vue
<div class="col-3">
    <UserProfileInfo @follow="follow" @unfollow="unfollow" :user="user"/>
    <UserProfileWrite />
</div>

<script>
import UserProfileWrite from '@/components/UserProfileWrite.vue';
    
export default {
    name: 'UserProfileView',
    components: {
        PageContent,
        UserProfileInfo,
        UserProfilePosts,
        UserProfileWrite,
    },
    //..
}
</script>
```

当前效果：

![image-20240217112549815](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171125021.png)

接下来需要获取到文本框中的值。使用 `v-model` 属性。

```vue
<template>
    <div class="card eidt-field">
        <div class="card-body">
            <label for="textarea" class="form-label">编辑帖子</label>
            <textarea v-model="content" class="form-control" id="textarea" rows="3"></textarea>
            <button type="button" class="btn btn-primary btn-sm">发布</button>
        </div>
    </div>
</template>

<script>
import { ref } from 'vue';

export default {
    name: "UserProfileWrite",
    setup() {
        let content = ref('');
        return {
            content
        }
    }
}
</script>

<style scoped>
.eidt-field {
    margin-top: 10px;
}
button {
    margin-top: 10px ; 
}
</style>
```

+ 在 setup 中定义一个变量 content，通过 `v-model` 将 textarea 的值和 content 绑定起来，这样 textarea 中的值就是 content 了。

然后给按钮绑定事件：

```js
<button @click="post_post" type="button" class="btn btn-primary btn-sm">发布</button>

import { ref } from 'vue';
export default {
    name: "UserProfileWrite",
    setup(props, context) {
        let content = ref('');
        const post_post = () => {
            context.emit("post_post", content.value);
            content.value = "";
        }
        return {
            content,
            post_post,
        }
    }
}
```

+ content 中的内容需要使用 value 属性来访问。

帖子的内容应该是存在父组件的数据里面的，所以又需要子组件向父组件传递信息，使用触发函数，先在父组件中实现函数：

```js
<div class="col-3">
    <UserProfileInfo @follow="follow" @unfollow="unfollow" :user="user"/>
    <UserProfileWrite  @post_post="post_post"/>
</div>

setup() {
    //。。。
    const post_post = (content) => {
        posts.count++;  // 帖子数量加1
        posts.posts.unshift({
            id: posts.count,
            userId: 1,
            content: content
        });
    }
    return {
        user: user,
        follow,
        unfollow,
        posts,
        post_post,
    }
}
```

+ 数组的 `unshift` 方法是在数组第一个位置添加一个元素，`push` 是在最后一个位置添加元素

流程：当点击发布按钮后，触发 UserProfileWrite 组件中的 post_post 事件，在这个事件中，会触发父组件 UserProfileView 中的 post_post 函数，并将当前文本框的值当作参数传过去，然后就会触发 UserProfileView 中的 post_post 事件，向数组中添加数据，然后因为 posts 对象是通过 reactive 创建的，所以当 posts 中的值发生改变的时候，就会将引入了该对象的组件重新渲染一遍。



## 注册页面

RegisterView.vue

```vue
<template>
    <PageContent>
        注册
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';

export default {
    name: 'Register',
    components: {
        PageContent
    }
}
</script>

<style scoped></style>

```



## 登录页面

LoginView.vue

```vue
<template>
    <PageContent>
        登录
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';

export default {
    name: 'Login',
    components: {
        PageContent
    }
}
</script>

<style scoped></style>

```



## 404页面

NotFoundView.vue

```vue
<template>
    <PageContent>
        404 Not Found!
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';

export default {
    name: 'NotFound',
    components: {
        PageContent
    }
}
</script>

<style scoped></style>

```



## 路由

要将每个页面来根据地址显示。

在 router/index.js 中：

```js
import { createRouter, createWebHashHistory } from 'vue-router'
// 先引入每个页面
import HomeView from '../views/HomeView.vue'
import UserListView from '../views/UserListView.vue'
import UserProfileView from '../views/UserProfileView.vue'
import LoginView from '../views/LoginView.vue'
import RegisterView from '../views/RegisterView.vue'
import NotFoundView from '../views/NotFoundView.vue'

const routes = [
    // 再给每个页面配置路由
  {
    path: '/',
    name: 'home',
    component: HomeView
  },
  {
    path: '/userList',
    name: 'userList',
    component: UserListView
  },
  {
    path: '/userProfile',
    name: 'userProfile',
    component: UserProfileView
  },
  {
    path: '/login',
    name: 'login',
    component: LoginView
  },
  {
    path: '/register',
    name: 'register',
    component: RegisterView
  },
  {
    path: '/404',
    name: '404',
    component: NotFoundView
  },
]
  
const router = createRouter({
  history: createWebHashHistory(),
  routes
})

export default router
```

+ 如果不想要地址栏中的 # 号，可以删除该文件中 createWebHashHistory 中的 Hash，使用 createWebHistory
+ name：以后跳转使用 name 跳转

## 页面跳转

修改 NavBar 组件上的链接地址：

```vue
<template>
    <nav class="navbar navbar-expand-lg bg-body-tertiary">
      <div class="container">
        <a class="navbar-brand" href="/">Myspace</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav me-auto mb-2 mb-lg-0">
            <li class="nav-item">
              <a class="nav-link active" aria-current="page" href="/">首页</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="/userList">好友列表</a>
            </li>
            <li class="nav-item">
              <a class="nav-link" href="/userProfile">用户动态</a>
            </li>
          </ul>
          <ul class="navbar-nav mb-2 mb-lg-0">
                <li class="nav-item">
                  <a class="nav-link" href="/login">登录</a>
                </li>
                <li class="nav-item">
                  <a class="nav-link" href="/register">注册</a>
                </li>
              </ul>
        </div>
      </div>
    </nav>
</template>
```

这样可以实现页面跳转，但是这样的话，每次跳转都会刷新整个页面，都会像服务器端重新请求一次数据。想实现前端渲染的话，就要使用 `<router-link>` 标签，和 React 中的 `Link` 标签类似。

```vue
<template>
    <nav class="navbar navbar-expand-lg bg-body-tertiary">
      <div class="container">
        <router-link class="navbar-brand" :to="{name: 'home'}">Myspace</router-link>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav me-auto mb-2 mb-lg-0">
            <li class="nav-item">
              <router-link class="nav-link active" aria-current="page" :to="{name: 'home'}">首页</router-link>
            </li>
            <li class="nav-item">
              <router-link class="nav-link" :to="{name: 'userList'}">好友列表</router-link>
            </li>
            <li class="nav-item">
              <router-link class="nav-link" :to="{name: 'userProfile'}">用户动态</router-link>
            </li>
          </ul>
          <ul class="navbar-nav mb-2 mb-lg-0">
                <li class="nav-item">
                  <router-link class="nav-link" :to="{name: 'login'}">登录</router-link>
                </li>
                <li class="nav-item">
                  <router-link class="nav-link" :to="{name: 'register'}">注册</router-link>
                </li>
              </ul>
        </div>
      </div>
    </nav>
</template>
```

+ router-link 标签绑定了一个属性，`:to`，在 vue 中用 `:` 来绑定属性。
+ `:to` 属性赋值了一个对象，对象中指定了一个 name，这个 name 需要和路由中指定的 name 一样

先在就是前端渲染了。

## 好友列表页面

从云端获取十个好友的信息，并显示在页面上。

获取用户列表接口：

+ 地址：https://app165.acapp.acwing.com.cn/myspace/userlist/
+ 方法：GET
+ 是否验证jwt：否
+ 输入参数：无
+ 返回结果：返回10个用户的信息

连接后端接口，可以使用 ajax，也可以使用 axios，这里使用 ajax。先安装 jQuery 包：

```bash
npm i jquery
```

在 UserListView 中：

```vue
<template>
<PageContent>
    <div class="card single-user" v-for="user in users" :key="user.id">
        <div class="card-body">
            <div class="row">
                <div class="col-1">
                    <img :src="user.photo" alt="" class="img-fluid"/>
                    <!-- 用 : 属性的话就会将字符串变为一个值 -->
                </div>
                <div class="col-11">
                    <div class="username">{{ user.username }}</div>
                    <div class="followers">粉丝数：{{ user.followerCount }}</div>
                </div>
            </div>
        </div>
    </div>
</PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';
import $ from 'jquery'
import { ref } from 'vue'

export default {
    name: 'UserListView',
    components: {
        PageContent
    },
    setup() {
        let users = ref([]);  // 定义用户数组
        $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/userlist/",
            type: 'get',
            success(resp) {
                users.value = resp;  // 这里一定要用 .value来赋值
            }
        })
        return {
            users,
        };
    }
}
</script>

<style scoped>
    
.username {
    height: 50%;
    font-weight: bold;
}
.followers{
    font-size: 12px;
    color: gray;
    height: 50%;
}
.single-user {
    margin-bottom: 10px;
    cursor: pointer;
}
.single-user:hover {
    box-shadow: 2px 2px 10px lightgrey;
    transition: 500ms;
}
</style>
```

当前效果：

![image-20240217151903772](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171521252.png)



## 链接加上参数

目前的用户动态页面 http://localhost:8080/userProfile 是一个固定的页面，但应该是根据网址中的用户 id 来决定显示哪个用户的动态页面，所以需要添加一个用户的 id 在网址上，比如：http://localhost:8080/userProfile/1，此时发现这个网址会显示一个空白页面，而不是 404 页面，所以要配置下路由：

```j
const routes = [
  {
    path: '/',
    name: 'home',
    component: HomeView
  },
  {
    path: '/userList/',
    name: 'userList',
    component: UserListView
  },
  {
    path: '/userProfile/',
    name: 'userProfile',
    component: UserProfileView
  },
  {
    path: '/login/',
    name: 'login',
    component: LoginView
  },
  {
    path: '/register/',
    name: 'register',
    component: RegisterView
  },
  {
    path: '/404/',
    name: '404',
    component: NotFoundView
  },
  // 这个正则表达式会匹配任意内容，当前面的所有路由都不匹配的时候就会匹配下一个
  {
    path: "/:catchAll(.*)",  // catchAll是关键字，这个正则表达式就是匹配任意字符
    redirect: '/404/'
  }
]
```

+ 严格一些，给所有路径的末尾都加上 `/` 。

然后给链接添加参数，实现通过不同的参数访问不同的用户：

```js
{
    path: '/userProfile/:userId/',  // ：表示有一个参数，这个参数的名字叫userId
    name: 'userProfile',
    component: UserProfileView
},
```

路由修改了后，记得将导航栏中跳转到用户动态的链接也改了，否则会报错：

```js
<router-link class="nav-link" :to="{name: 'userProfile', params: {userId: 1}}">用户动态</router-link>
```

然后进入 UserProfileView 中，可以使用 useRoute 这个函数获取参数：

```js
setup() {
    const route = useRoute();
    const userId = route.params.userId
    console.log(route.params.userId);
}
```

## 登录页面

先实现下登录页面。

```vue
<template>
    <PageContent>
        <form>
            <div class="mb-3">
                <label for="username" class="form-label">用户名</label>
                <input type="text" class="form-control" id="username" aria-describedby="emailHelp">
            </div>
            <div class="mb-3">
                <label for="password" class="form-label">密码</label>
                <input type="password" class="form-control" id="password">
            </div>
            <button type="submit" class="btn btn-primary">登录</button>
        </form>
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';

export default {
    name: 'LoginView',
    components: {
        PageContent
    }
}
</script>

<style scoped></style>
```

想登录的话，需要动态获取用户名和密码，使用 `v-model` 将这两个属性双向绑定在两个输入框上：

同时再定义一个 `div` 用来显示密码错误提示信息：

```vue
//...
<div class="mb-3">
    <label for="username" class="form-label">用户名</label>
    <input v-model="username" type="text" class="form-control" id="username" aria-describedby="emailHelp">
</div>
<div class="mb-3">
    <label for="password" class="form-label">密码</label>
    <input v-model="password" type="password" class="form-control" id="password">
</div>
<!-- 显示密码错误信息： -->
<div class="error-message">{{error_message}}</div>  

//...
import { ref } from 'vue';

export default {
    name: 'LoginView',
    components: {
        PageContent
    },
    setup() {
        let username = ref('');
        let password = ref('');
        let error_message = ref('');

        return {
            username,
            password,
            error_message,
        }
    }
}

//...
<style scoped>
button {
    width: 100%;
}
.error-message {
    color: red;
}
</style>
```

写一个登录事件：

```vue
<template>
//。。
<form @submit.prevent="login">
  //。。
</form>
//。。
</template>

<script>
export default {
    //。。
    setup() {
        let username = ref('');
        let password = ref('');
        let error_message = ref('');

        let login = () => {
            console.log(username.value, password.value)
        }
        return {
            username,
            password,
            error_message,
            login,
        }
    }
}
</script>
```

+ 访问 ref 变量的值时，需要通过 value 属性。
+ 绑定表单的事件的时候，表单有自己的默认事件，如果使用 `@submit="login"` 这种方式绑定的话，最后执行了 login 函数后还会执行一遍表单自身的默认事件，为了消除这个默认的事件，使用 `@submit.prevent="login"`。

## store

很多的页面都需要访问用户的信息，所以用户的信息应该存在全局信息里面。vue 中提供一种维护全局变量的机制叫 vuex，所以可以将登录的信息存在 vuex 种。

vuex 依赖已经装过了，打开项目文件夹下的 store/index.js ，：

```js
import { createStore } from 'vuex'

export default createStore({
  state: {
  },
  getters: {
  },
  mutations: {
  },
  actions: {
  },
  modules: {
  }
})
```

+ state 存储数据的

+ getters：当需要获取一些数据的时候，又不能直接获取，需要经过一些计算的时候，可以在 getters 中实现，只能读取，不能修改

+ actions：定义对 state 的各种操作，但是不能直接修改 state，对 state 直接修改的各种操作必须定义在 mutations 中。一个完整复杂的修改放在 actons 中，直接修改放在 mutations 中。

+ modules：是对 state 的分割，每个 modules 中的对象是维护的 state 中的对象，每个对象都有完整的 state、getters等

  假如有另外一个 js 文件：

  ```js
  const ModuleUser({
      state: {
          user: {
              id:"",
              username: "",
              password: "",
              firstName: "",
              lastName: "",
        }
    },
      getters: {
          fullName() {
              return lastName + " " + firstName;
        }
    },
      mutations: {},
      actions: {},
      modules: {}
  })
  export default ModulwUser;
  ```

  那么在 index.js 中引入这个 ModuleUser：

  ```js
  import { createStore } from 'vuex'
  
  export default createStore({
    state: {
    },
    getters: {
    },
    mutations: {
    },
    actions: {
    },
    modules: {
        user: ModulerUser,
    }
  })
  ```

  如果想访问 ModuleUser 中的属性的话：

  ```js
  store.state.user.username;
  ```

## 实现登录

登录接口：

获取Json Web Token（JWT）

+ 地址：https://app165.acapp.acwing.com.cn/api/token/
+ 方法：POST
+ 是否验证jwt：否
+ 输入参数：
  + username: 用户名
  + password: 密码
+ 返回结果：
  + access: 访问令牌，有效期5分钟
  + refresh: 刷新令牌，有效期14天

在 store/user.js 中写上登录的 API

```js
const ModuleUser = {
  state: {
    id: "",
    username: "",
    photo: "",
    followers: 0,
  },
  getters: {
    
  },
  mutations: {
    
  },
  actions: {
    // context里传的是api
    // data是自己传过来的
    login(context, data) {
      $.ajax({
        url: "https://app165.acapp.acwing.com.cn/api/token/",
        type: "post",
        data: {
          username: data.username,
          password: data.password,
        },
        success(resp) {
          console.log(resp)
        }
      })
    }
  },
  modules: {
    
  }
}
export default ModuleUser;
```

然后在 LoginView 中的 login 函数中调用：

```js
export default {
    name: 'LoginView',
    components: {
        PageContent
    },
    setup() {
        let username = ref('');
        let password = ref('');
        let error_message = ref('');
        let store = useStore();

        let login = () => {
            store.dispatch("login", {
                username: username.value,
                password: password.value,
                success() {
                    console.log("success");
                },
                error() {
                    console.log("fail")
                }
            })
        }
        return {
            username,
            password,
            error_message,
            login,
        }
    }
}
```

+ 要使用 store 的话要使用 `useStore()` 。

现在登录试一下：

![image-20240217174205040](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171742192.png)

显然已经获取到了登录需要的 JWT，接下来就是获取到用户的信息。

将上面输出的对象的 access 复制出来，使用在线 base64 解码可以看到里面包含的信息，[解码地址](https://jwt.io/)：

![image-20240217182742535](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171827691.png)



## 获取用户信息

获取某个用户的信息接口：

+ 地址：https://app165.acapp.acwing.com.cn/myspace/getinfo/
+ 方法：GET
+ 是否验证jwt：是
+ 输入参数：
  + user_id：用户的ID
+ 返回结果：该用户的信息

在获取用户信息的时候，显然要传一个参数过去，这个参数是用户 id，这个用户 id 在我们拿到的 jwt 令牌中，所以我们需要先将拿到的 access 码解码，解码就需要安装一个包：

```bash
npm i jwt-decode
```

然后通过解码拿到 userid，再通过这个接口将 userid 传过去，拿到用户信息：

```js
import $ from 'jquery'
import { jwtDecode } from 'jwt-decode';

const ModuleUser = {
  state: {
    id: "",
    username: "",
    photo: "",
    followers: 0,
  },
  getters: {
    
  },
  mutations: {
    
  },
  actions: {
    // context里传的是api
    // data是自己传过来的
    login(context, data) {
      $.ajax({
        url: "https://app165.acapp.acwing.com.cn/api/token/",
        type: "post",
        data: {
          username: data.username,
          password: data.password,
        },
        success(resp) {
          const { access } = resp;
          const access_obj = jwtDecode(access);//解码
          $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/getinfo/",
            type: "get",
            data: {
              user_id: access_obj.user_id,
            },
            headers: {  // jwt 验证
              "Authorization": "Bearer " + access,  // 后端要求的格式
            },
            success(resp) {
              console.log(resp)
            }
          })
        }
      })
    }
  },
  modules: {
    
  }
}
export default ModuleUser;
```

查看输出，已经拿到了用户的信息：

![image-20240217184258211](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171842318.png)

接下来要将这些信息更新到 state 中，在 action 中是不能更新的，要在 mutations 中更新：

```js
import $ from 'jquery'
import { jwtDecode } from 'jwt-decode';

const ModuleUser = {
  state: {
    id: "",
    username: "",
    photo: "",
    followers: 0,
    access: "",
    refresh: "",
    is_login: false,
  },
  getters: {
    
  },
  mutations: {
    updateUser(state, user) {
      state.id = user.id;
      state.username = user.username;
      state.photo = user.photo;
      state.followers = user.followerCount;
      state.access = user.access;
      state.refresh = user.refresh;
      state.is_login = user.is_login;
    }
  },
  actions: {
    // context里传的是api，这是vue传的
    // data是自己传过来的数据
    login(context, data) {
      $.ajax({
        url: "https://app165.acapp.acwing.com.cn/api/token/",
        type: "post",
        data: {
          username: data.username,
          password: data.password,
        },
        success(resp) {
          const { access, refresh } = resp;
          const access_obj = jwtDecode(access);
          $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/getinfo/",
            type: "get",
            data: {
              user_id: access_obj.user_id,
            },
            headers: {  // jwt 验证
              "Authorization": "Bearer " + access,  // 后端要求的格式
            },
            success(resp) {
              // 使用 context.commit() 调用mutations 中的方法
              // 第一个参数是要调方法的名称
              // 第二个参数是要传的参数
              context.commit("updateUser", {
                ...resp,
                access: access,
                refresh: refresh,
                is_login: true,
              });
              // 调用一下回调函数
              data.success();
            }
          })
        },
        error() {
          data.error();
        }
      })
    }
  },
  modules: {
    
  }
}
export default ModuleUser;
```

现在是 access 每五分钟过期，所以要定期的刷新 access，每当我们访问的时候，发现 access 过期了，就先去获取 access 再重新访问。这里使用每4.5分钟获取一次的方式。

## 刷新JWT令牌

刷新JWT令牌接口

+ 地址：https://app165.acapp.acwing.com.cn/api/token/refresh/
+ 方法：POST
+ 是否验证jwt：否
+ 输入参数：
  + refresh: 刷新令牌
+ 返回结果：
  + access: 访问令牌，有效期5分钟

在 store/user.js 中 actions 中的 login 方法中的 success 中：

```js
// 定时刷新令牌
setInterval(() => {
    $.ajax({
        url: 'https://app165.acapp.acwing.com.cn/api/token/refresh/',
        type: 'post',
        data: {
            refresh: refresh,
        },
        success(resp) {
            console.log(resp);
        }
    })
}, 4.5 * 60 * 1000);
```

+ 每4分半刷新一次

然后需要更新 state 中的值，同样是要在 mutations 中添加一个函数，并在上面的函数中调用：

```js
import $ from 'jquery'
import { jwtDecode } from 'jwt-decode';

const ModuleUser = {
  state: {
    id: "",
    username: "",
    photo: "",
    followers: 0,
    access: "",
    refresh: "",
    is_login: false,
    
  },
  getters: {
    
  },
  mutations: {
    updateUser(state, user) {
      state.id = user.id;
      state.username = user.username;
      state.photo = user.photo;
      state.followers = user.followerCount;
      state.access = user.access;
      state.refresh = user.refresh;
      state.is_login = user.is_login;
    },
    updateAccess(state, access) {
      state.access = access;
    },
  },
  actions: {
    // context里传的是api
    // data是自己传过来的
    login(context, data) {
      $.ajax({
        url: "https://app165.acapp.acwing.com.cn/api/token/",
        type: "post",
        data: {
          username: data.username,
          password: data.password,
        },
        success(resp) {
          const { access, refresh } = resp;
          const access_obj = jwtDecode(access);

          // 定时刷新令牌
          setInterval(() => {
            $.ajax({
              url: 'https://app165.acapp.acwing.com.cn/api/token/refresh/',
              type: 'post',
              data: {
                refresh: refresh,
              },
              success(resp) {
                context.commit("updateAccess", resp.access)
              }
            })
          }, 4.5 * 60 * 1000);

          $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/getinfo/",
            type: "get",
            data: {
              user_id: access_obj.user_id,
            },
            headers: {  // jwt 验证
              "Authorization": "Bearer " + access,  // 后端要求的格式
            },
            success(resp) {
              // 使用 context.commit() 调用mutations 中的方法
              // 第一个参数是要调方法的名称
              // 第二个参数是要传的参数
              context.commit("updateUser", {
                ...resp,
                access: access,
                refresh: refresh,
                is_login: true,
              });
              // 调用以下回调函数
              data.success();
            }
          })
        },
        error() {
          data.error();
        }
      })
    }
  },
  modules: {
    
  }
}
export default ModuleUser;
```

## 登录后跳转

在登录页面 LoginView 中

```js
import PageContent from '../components/Content.vue';
import { ref } from 'vue';
import { useStore } from 'vuex';
import router from '@/router';

export default {
    name: 'LoginView',
    components: {
        PageContent
    },
    setup() {
        let username = ref('');
        let password = ref('');
        let error_message = ref('');
        let store = useStore();

        let login = () => {
            store.dispatch("login", {
                username: username.value,
                password: password.value,
                success() {
                    router.push({ name: "userList" }); 
                },
                error() {
                    error_message.value = '用户名或密码错误'
                }
            })
        }
        return {
            username,
            password,
            error_message,
            login,
        }
    }
}
```

+ 使用 router 进行跳转，router.push 将要跳转的地址写入，等同于点击 `<router-link :to="..."> `

## 展示用户名

登录成功后，在右上角显示用户名。

当前，用户的所有信息都存在了 store 里，存在全局里，所以在 navbar 里判断一下是否登录，登录了就显示用户名，未登录就显示登录和注册按钮。

怎么访问全局 store 里面的数据呢？使用 `$store`：

```vue
<ul class="navbar-nav mb-2 mb-lg-0" v-if="!$store.state.user.is_login">
    <li class="nav-item">
        <router-link class="nav-link" :to="{name: 'login'}">登录</router-link>
    </li>
    <li class="nav-item">
        <router-link class="nav-link" :to="{name: 'register'}">注册</router-link>
    </li>
</ul>
<ul class="navbar-nav mb-2 mb-lg-0" v-else>
    <li class="nav-item">
        <router-link 
                     class="nav-link" 
                     :to="{ name: 'userProfile', params:{userId: $store.state.user.id} }">
            {{$store.state.user.username}}
        </router-link>
    </li>
    <li class="nav-item">
        <router-link class="nav-link" :to="{ name: 'login' }">退出</router-link>
    </li>
</ul>
```

现在登录后的效果：

![image-20240217194543982](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402171945138.png)

## 实现退出

登录的本质就是获取了 jwt，那么退出就直接把 jwt 删除即可。所以直接写个事件通过 store 修改用户的全局信息：

```vue
<script>
import { useStore } from 'vuex';

export default {
  name: "NavBar",
  setup() {
    const store = useStore();
    let logout = () => {
      store.commit('logout');
    }
    return {
      logout,
    }
  }
}
</script>
```

+ 调用 mutations 中的函数使用 commit
+ 调用 actions 中的函数使用 dispatch

因为要修改 store 里 state 的值，所以还是要将修改的接口写在 actions 中，直接修改写在 mutations 中，但是这个逻辑很简单，所以直接在 mutations 中写即可，不用在 actions 中写。在 user.js 中的 mutations 中：

```js
logout(state) {
    state.id = "";
    state.username = "";
    state.photo = "";
    state.followers = 0
    state.access = "";
    state.refresh = "";
    state.is_login = false;
}
```

## 修改用户动态页面

这个页面应该默认只有登录后的用户才能点开，未登录用户点开这个页面就跳转到登录页面。

可以将导航栏中的跳转该页面的链接删掉，因为这个页面的打开方式应该是通过地址栏上的参数来确定打开的是哪个用户的页面。

删除之后，就需要实现点击好友列表中的用户就会跳转到用户动态的页面。所以在 UserListView 中，写一个打开用户动态页面的函数，然后给每个用户的卡片上绑定触发事件：

```vue
<template>
<PageContent>
    <div class="card single-user" v-for="user in users" :key="user.id" @click="open_userprofile(user.id)">
        <div class="card-body">
            <div class="row">
                <div class="col-1">
                    <img :src="user.photo" alt="" class="img-fluid"/>
                    <!-- 用 : 属性的话后面的字符串就不会是普通的字符串 -->
                </div>
                <div class="col-11">
                    <div class="username">{{ user.username }}</div>
                    <div class="followers">粉丝数：{{ user.followerCount }}</div>
                </div>
            </div>
        </div>
    </div>
</PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';
import $ from 'jquery'
import { ref } from 'vue'
import router from '@/router';
import { useStore } from 'vuex';

export default {
    name: 'UserListView',
    components: {
        PageContent
    },
    setup() {
        const store = useStore();
        let open_userprofile = userId => {
            if (store.state.user.is_login) {
                router.push({
                    name: "userProfile",
                    params: {
                        userId: userId
                    }
                })
            }
            else {
                router.push({name: 'login'})
            }
        }
        let users = ref([]);  // 定义用户数组
        $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/userlist/",
            type: 'get',
            success(resp) {
                users.value = resp;  // 这里一定要用 .value来赋值
            }
        })
        return {
            users,
            open_userprofile,
        };
    }
}
</script>
```

+ 打开一个界面还是使用 router

接下来就是修改用户动态的这个页面的数据，从云端上获取，目前是写死的数据。

需要动态拉取两个信息：用户信息、用户发布的帖子

### 获取用户信息

获取某个用户的信息接口

+ 地址：https://app165.acapp.acwing.com.cn/myspace/getinfo/
+ 方法：GET
+ 是否验证jwt：是
+ 输入参数：
  + user_id：用户的ID
+ 返回结果：该用户的信息

修改UserProfileView 页面：

```vue
<template>
    <PageContent>
        <div class="row">
            <div class="col-3">
                <UserProfileInfo @follow="follow" @unfollow="unfollow" :user="user"/>
                <UserProfileWrite  @post_post="post_post"/>
            </div>
            
            <div class="col-9">
                <UserProfilePosts :posts="posts"/>
            </div>
        </div>
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';
import UserProfileInfo from '@/components/UserProfileInfo.vue';
import UserProfilePosts from '@/components/UserProfilePosts.vue';
import UserProfileWrite from '@/components/UserProfileWrite.vue';
import { reactive } from 'vue';
import { useRoute } from 'vue-router';
import $ from 'jquery';
import { useStore } from 'vuex';

export default {
    name: 'UserProfileView',
    components: {
        PageContent,
        UserProfileInfo,
        UserProfilePosts,
        UserProfileWrite,
    },
    setup() {
        const posts = reactive({});
        const user = reactive({});
        const route = useRoute();
        const userId = route.params.userId
        const store = useStore();

        $.ajax({
            url: 'https://app165.acapp.acwing.com.cn/myspace/getinfo/',
            type: 'get',
            headers: {  
                "Authorization": "Bearer " + store.state.user.access,  
            },
            data: {
                user_id: userId,
            },
            success(resp) {
                user.id = resp.id,
                user.username = resp.username;
                user.photo = resp.photo;
                user.followers = resp.followerCount;
                user.is_followed = resp.is_followed;
            }
        })

        const follow = () => {
            if (user.is_followed) return;
            user.is_followed = true;
            user.followers++;
        }
        const unfollow = () => {
            if (!user.is_followed) return;
            user.is_followed = false;
            user.followers--;
        }
        
        const post_post = (content) => {
            posts.count++;  // 帖子数量加1
            posts.posts.unshift({
                id: posts.count,
                userId: 1,
                content: content
            });
        }
        return {
            user: user,
            follow,
            unfollow,
            posts,
            post_post,
        }
    }
}
</script>

<style scoped></style>
```

然后将 UserProfileInfo 组件中的头像属性修改：

```vue
<img class="img-fluid" :src="user.photo" alt="">
```

### 获取帖子信息

获取某个用户的所有帖子接口

+ 地址：https://app165.acapp.acwing.com.cn/myspace/post/
+ 方法：GET
+ 是否验证jwt：是
+ 输入参数：
  + user_id：用户的ID
+ 返回结果：该用户的所有帖子

在 Use人ProfileView 页面中的 setup 中：

```js
$.ajax({
    url: 'https://app165.acapp.acwing.com.cn/myspace/post/',
    type: 'get',
    data: {
        user_id: userId,
    },
    headers: {
        "Authorization": "Bearer " + store.state.user.access,
    },
    success(resp) {
        posts.posts = resp;
        posts.count = resp.length;
    }
})
```

### 添加帖子

只能在自己的动态页面里添加帖子。

使用动态计算的属性，判断当前页面是否属于当前的用户，是则显示编辑页面，在 UserProfileView 页面中，修改一下三处：

```js
<UserProfileWrite v-if="is_me" @post_post="post_post"/>

import { computed } from 'vue';

const is_me = computed(() => userId == store.state.user.id);

return {
//..
    is_me,
}
```

此时还有一个bug，当我们进入了别人的动态页面后，点击右上角我们的名字，并没有跳转到我们的动态页面，这是因为 router 此时将我们的页面的地址 http://localhost:8080/userProfile/65/ 当成了当前动态页面的地址，因为在路由中，这两个地址的 name 都是 userProfile，而 router 默认是根据这个 name 来判断两个路径的，所以要在 App.vue 中修改：

```vue
<template>
  <NavBar />
  <router-view :key="$route.fullPath"/>
</template>
```

+ 绑定一个 key 属性，这样 router 会用完整路径来比较

### 动态修改帖子

创建一个帖子接口

+ 地址：https://app165.acapp.acwing.com.cn/myspace/post/
+ 方法：POST
+ 是否验证jwt：是
+ 输入参数：
  + content：帖子的内容
+ 返回结果：result: success

删除一个帖子接口

+ 地址：https://app165.acapp.acwing.com.cn/myspace/post/
+ 方法：DELETE
+ 是否验证jwt：是
+ 输入参数：
  + post_id：被删除帖子的ID
+ 返回结果：result: success

在 UserProfileWrite 组件中：

```vue
<template>
//。。
</template>

<script>
import { ref } from 'vue';
import $ from 'jquery'
import { useStore } from 'vuex';

export default {
    name: "UserProfileWrite",
    setup(props, context) {
        let content = ref('');
        const store = useStore();

        const post_post = () => {
            $.ajax({
                url: "https://app165.acapp.acwing.com.cn/myspace/post/",
                type: 'post',
                data: {
                    content: content.value,
                },
                headers: {
                    "Authorization": "Bearer " + store.state.user.access,
                },
                success(resp) {
                    console.log(resp)
                    if (resp.result === "success") {
                        context.emit("post_post", content.value);
                        content.value = "";
                    }
                }
            })
        }
        return {
            content,
            post_post,
        }
    }
}
</script>

<style scoped>
.eidt-field {
    margin-top: 10px;
}
button {
    margin-top: 10px ; 
}
</style>
```

当前，每次一刷新页面，登录状态就会没有。如果希望刷新能保持登录状态的话，可以将我们的 access 存在 localStorage 里面

### 删除帖子

在我们自己的动态页面中，应该可以删除帖子。

在 UserProfilePosts 组件中添加删除按钮，为删除按钮绑定删除事件，同时还要判断当前页面是不是自己的页面，是的话就渲染删除按钮：

```vue
<template>
    <div class="card">
        <div class="card-body">
            <div  class="card single-post" v-for="post in posts.posts" :key="post.id">
                    <div class="card-body">
                        {{ post.content }}
                        <button 
                                v-if="is_me"   
                                @click="delete_post(post.id)" 
                                type="button" class="btn btn-danger btn-sm">删除</button>
                    </div>
            </div>
        </div>
    </div>
</template>

<script>
import { computed } from 'vue';
import { useStore } from 'vuex';
import $ from 'jquery'

export default {
    name: "UserProfilePosts",
    props: {
        posts: {
            type: Object,  // 传过来的类型
            required: true,  // 必须传过来
        },
        user: {
            type: Object,  // 传过来的类型
            required: true,  // 必须传过来
        }
    },
    setup(props,context) {
        const store = useStore();

        let is_me = computed(() => store.state.user.id === props.user.id);

        const delete_post = (post_id) => {
            $.ajax({
                url: 'https://app165.acapp.acwing.com.cn/myspace/post/',
                type: 'delete',
                headers: {
                    "Authorization": "Bearer " + store.state.user.access,
                },
                data: {
                    post_id: post_id,
                },
                success(resp) {
                    if (resp.result == 'success') {
                        context.emit('delete_post', post_id);
                    }
                }
            })
        }
        return {
            is_me,
            delete_post,
        }
    }
}
```

这只是将后端数据库的帖子删除了，前端显示的帖子还没有删除，在 UserProfileView 页面中定义删除事件，同时绑定在 UserProfilePosts 组件中：

```vue
<UserProfilePosts :user="user" :posts="posts" @delete_post="delete_post"/>

const delete_post = (post_id) => {
	posts.posts = posts.posts.filter(p => p.id !== post_id);
	posts.count = posts.posts.length;
}
```

## 增删改查的API类型

增：增加，POST

删：删除，DELETE

改：修改，PUT

查：查找，GET

## 注册功能

注册页面和登录页面类似，复制过来。

注册账号接口

+ 地址：https://app165.acapp.acwing.com.cn/myspace/user/
+ 方法：POST
+ 是否验证jwt：否
+ 输入参数：
  + username: 用户名
  + password：密码
  + password_confirm：确认密码
+ 返回结果：
  + result: success
  + result: 用户名和密码不能为空
  + result: 两个密码不一致
  + result: 用户名已存在

加一条确认密码：

```vue
<template>
    <PageContent>
        <div class="row justify-content-md-center">
            <div class="col-3">
                <form @submit.prevent="register">
                    <div class="mb-3">
                        <label for="username" class="form-label">用户名</label>
                        <input v-model="username" type="text" class="form-control" id="username"
                            aria-describedby="emailHelp">
                    </div>
                    <div class="mb-3">
                        <label for="password" class="form-label">密码</label>
                        <input v-model="password" type="password" class="form-control" id="password">
                    </div>
                    <div class="mb-3">
                            <label for="confirm-password" class="form-label">确认密码</label>
                            <input v-model="confirm_password" type="password" class="form-control" id="confirm-password">
                        </div>
                    <!-- 显示注册信息： -->
                    <div class="error-message">{{ error_message }}</div>
                    <button type="submit" class="btn btn-primary ">注册</button>
                </form>
            </div>
        </div>
    </PageContent>
</template>

<script>
import PageContent from '../components/Content.vue';
import { ref } from 'vue';
import $ from 'jquery'

export default {
    name: 'LoginView',
    components: {
        PageContent
    },
    setup() {
        let username = ref('');
        let password = ref('');
        let confirm_password = ref('');
        let error_message = ref('');

        let register = () => {
            $.ajax({
                url: 'https://app165.acapp.acwing.com.cn/myspace/user/',
                type: 'post',
                data: {
                    username: username.value,
                    password: password.value,
                    password_confirm: confirm_password.value,
                },
                success(resp) {
                    error_message.value = resp.result;
                }
            })
        }
        return {
            username,
            password,
            confirm_password,
            error_message,
            register
        }
    }
}
</script>
```

注册成功后，直接进行登录：直接将 loginView 中的登录逻辑复制过来：

```js
import { useStore } from 'vuex';
import router from '@/router';

setup() {
    let username = ref('');
    let password = ref('');
    let confirm_password = ref('');
    let error_message = ref('');
    const store = useStore();

    let register = () => {
        $.ajax({
            url: 'https://app165.acapp.acwing.com.cn/myspace/user/',
            type: 'post',
            data: {
                username: username.value,
                password: password.value,
                password_confirm: confirm_password.value,
            },
            success(resp) {
                if (resp.result === 'success') {
                    store.dispatch("login", {
                        username: username.value,
                        password: password.value,
                        success() {
                            router.push({ name: "userList" });
                        },
                        error() {
                            error_message.value = '系统错误！'
                        }
                    })
                } else {
                    error_message.value = resp.result;
                }
            }
        })
    }
    return {
        username,
        password,
        confirm_password,
        error_message,
        register
    }
}
```

## 关注功能

点击关注后，数据库中的粉丝会增加。

更改关注状态

+ 如果未关注，则关注；如果已关注，则取消关注。

+ 地址：https://app165.acapp.acwing.com.cn/myspace/follow/
+ 方法：POST
+ 是否验证jwt：是
+ 输入参数：
  + target_id: 被关注的用户ID
+ 返回结果：result: success

在 UserProfileInfo 组件中的 follow 和 unfollow 函数中更新数据库的状态：

```vue
<script>
import $ from 'jquery';
import { useStore } from 'vuex';

export default {
    name: "UserProfileInfo",
    props: {
        user: {
            type: Object,
            required: true,
        },
    },
    setup(props, context) {
        const store = useStore();

        const follow = () => {
            $.ajax({
                url: 'https://app165.acapp.acwing.com.cn/myspace/follow/',
                type: 'post',
                 headers: {  
                     "Authorization": "Bearer " + store.state.user.access,  // 后端要求的格式
                },
                data: {
                    target_id: props.user.id,
                },
                success(resp) {
                    if (resp.result === 'success')
                        context.emit("follow");
                }
            })
        }

        const unfollow = () => {
            $.ajax({
                url: 'https://app165.acapp.acwing.com.cn/myspace/follow/',
                type: 'post',
                headers: {
                    "Authorization": "Bearer " + store.state.user.access,  // 后端要求的格式
                },
                data: {
                    target_id: props.user.id,
                },
                success(resp) {
                    if (resp.result === 'success')
                        context.emit("unfollow");
                }
            })
        }

        return {
            follow,
            unfollow
        }
    }
}
</script>
```

# 部署项目

将项目部署在云服务器上。

使用 Vue 的图形界面管理器，点击任务，点击 Build，点击运行，就会将当前项目打包，打包完了之后，就会在项目目录下多一个 dist 文件夹，这个文件夹中就是我们需要部署的东西：

![image-20240218011526073](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402180116965.png)

然后运行这个 index.html ，使用开发者工具查看元素：

![image-20240218011647199](https://gitee.com/LowProfile666/image-bed/raw/master/img/202402180116496.png)

+ chunk\*\*\*.js 是我们项目用到所有的第三方的 js 的打包
+ app\*\*\*.js 是我们自己的代码的打包
+ chunk\*\*\*.css 是我们项目用到所有的第三方的 css 的打包
+ app\*\*\*.css 是我们自己的代码的打包

这就是静态页面，想怎么部署就怎么部署。

先打包，再将包传到自己的服务器上，

