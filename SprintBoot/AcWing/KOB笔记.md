# KOB

前后端不分离：html 代码是根据请求的数据在服务器端生成的。client 访问 server，server 直接向 client 发送一个 html 字符串。

前后端分离：返回的 html 代码是在用户端浏览器用 js 代码完成的。打开一个网站，第一步是将网站的静态文件从某个地方先传过来，然后 client 再向 server 发送数据，server 会将一些数据返回给 client，前端接收到数据后，再动态的渲染页面。



## 1、项目创建

IDEA 创建项目：

+ https://start.spring.io/加载慢的话，可以换成：https://start.aliyun.com

![image-20231120082444192](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311200824239.png)

![image-20231120082530496](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311200825544.png)

整个SpringBoot的入口：

![image-20231120082634874](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311200826951.png)

在第一次打开的时候会提醒配置 jdk ，需要注意 JDK 的版本，重新创建了一个项目，并且重新下载了 1.8 版本的 JDK，如果用的是jdk8，那么springboot的版本要小于3。

然后点击配置 maven 。

最后成功界面：

![image-20231120142913364](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201429471.png)

手动导入 gradle 项目：

下载下来 gradle 项目，在 gradle 设置里，选择分发：本地安装，选择下载的 gradle 项目的根目录即可。

idea 会自动配置，配置完后，出现以下界面，就成功了：

![image-20231120081148720](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311200811836.png)

这时访问 localhost:8080 是这样的界面：

![image-20231120081251758](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311200812795.png)

### 前后端不分离的写法

spring后端主要用来实现函数的，每一个链接都对应一个函数，负责给用户返回一个页面。

函数可以写在任何地方，只要加个 controller 的注解就可以了。一般新建一个包，取名 controller，用来存所有的后端函数。

本项目分为四个模块，第一个模块是 PK 模块，所以可以在 controller 里新建一个包 pk，在这里写关于 pk 模块的 controller。

在 pk 包下新建一个类，叫 IndexController ，如果想要把这个函数变成一个链接的真正的函数，要在类上加一个注解 `@Controller` 。

pk 模块下的所有链接都在 pk 包下，所以可以在 IndexController 上加一个父目录：`@RequestMapping("/pk/")`。

如果我们想要返回一个页面的话，我们需要先创建一个页面出来，在 resources 里面的 template 里面创建一个目录 pk，然后在 pk 目录里创建一个 html 文件 index。

![image-20231120145806378](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201458421.png)

然后让 IndexController 返回 index 页面：

```java
@Controller
@RequestMapping("/pk/")
public class IndexController {
    @RequestMapping("index/")
    public String index(){
        return "pk/index.html";  // 这里要写的是在 templates 里面，pk目录下的 index 页面路径
    }
}
```

然后通过  http://127.0.0.1:8080/pk/index/ 这个链接就能访问到 index 页面了。

观察上面的链接：

+ pk：对应 IndexController 类上的注解
+ index：对应 index 方法上的注解
+ pk/index/：就是访问 index 这个方法

显示图片：

图片一般存在 static 目录下，在 static 目录下新建一个 img 目录，在里面放图片。然后在 index 页面里添加这张图片，就可以了。

![image-20231120150246276](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201502315.png)

图片路径这样写的话不对：

```java
<img src="/static/img/img.png">
```

### 创建后端

在 controller.pk 下新建一个类，这个类上的注解就不用 @controller 了，而是用 `@RestController`，同时也要使用映射 `@RequestMapping("/pk/")`，在其下的方法上也使用映射 `@RequestMapping("getinfo/")`，

![image-20231120151047645](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201510689.png)

点击 application.properties 文件，如果里面是空的，表示是使用的 Spring 默认的网站；如果不是空白的，且 server.port = 8080 的话，最好是将 8080 改了，因为 vue 默认也是使用 8080，这样的话前端后端的项目就会冲突。所以可以将 8080 改成 3000：

```java
server.port=3000
```

然后访问的时候用 http://127.0.0.1:3000。

### 创建前端

安装 vue。

在控制台里输入 vue ui 可以打开 vue 的图形化界面管理。在图形页面中，找到当前项目的目录，新建一个 web 项目，

![image-20231120153208279](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201532317.png)

然后下一步选择 vue3，创建。然后安装上两个插件：

![image-20231120153406453](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201534525.png)

然后安装两个依赖：jquery、bootstrap：

![image-20231120153640396](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201536468.png)

然后点击任务，点击运行，在输出里面可以看到一个网址：

![image-20231120154008641](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201540718.png)

然后以同样的方式再创建一个项目 acapp，插件只需要装 vuex 就可以了。

目前的结构：

![image-20231120154525217](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201545242.png)

### 运行web

运行 web 项目后，点击输出中的链接，就可以运行。

#### 去除地址栏的#号

发现地址栏中会多出一个 `#` 号，去除这个 # 号：

+ 在 router 目录下，index.js 里，有一段代码：
  ```vue
  const router = createRouter({
    history: createWebHashHistory(),
    routes
  })
  ```

  去掉这段代码的 createWebHashHistory 的 Hash 即可。

  可能第一句也有这样的代码需要去掉：

  ```vue
  import { createRouter, createWebHashHistory } from 'vue-router'
  ```

#### 删除无用的文件

views 目录下的 AboutView 与 HomeView 无用，删掉。

components 目录下的 HelloWorld 无用，删掉。

router 目录下的 index.js 中删掉相关代码：

```vue
import { createRouter, createWebHistory } from 'vue-router'

const routes = [

]

const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router
```

然后将 App.vue 文件中的代码删掉，只留下模板：

```vue
<template>
  <div>hello</div>
  <router-view />
</template>

<style></style>
```

#### 前后端通信

假设后端返回的是一个键值对数据：

```java
@RequestMapping("getbotinfo/")
public Map<String,String> getBotInfo() {
    Map<String, String> map = new HashMap<>();
    map.put("name", "Jack");
    map.put("rating", "1500");
    return map;
}
```

修改前端页面：

```vue
<template>
  <div>Bot昵称：{{ bot_name }}</div>
  <div>Bot战力：{{ bot_rating }}</div>
  <router-view />
</template>

<script>
import $ from 'jquery';
import { ref } from "vue";

export default {
  name: "App",
  // setup 是整个函数的入口
  setup: () => {
    let bot_name = ref("");
    let bot_rating = ref("");

    $.ajax({
      url: "http://127.0.0.1:3000/pk/getbotinfo/",
      type: "get",
      success: resp => {
        console.log(resp);
      }
    });

    return {
      bot_name,
      bot_rating
    }
  }
}
</script>

<style></style>
```

然后这时候按 f12 在控制台中可以看到报错信息：

![image-20231120161035563](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201610593.png)

这是跨域问题。跨域：当前网站地址是 localhost:8080，调用的地址是 localhost:3000，两个域名不一样，就出现了跨域问题。

##### 解决跨域问题

在后端添加配置类：CorsConfig。

在后端项目的根包下，创建一个 config 包，包里新建一个类 CorsConfig：

```java
package com.kob.backend.config;

import org.springframework.context.annotation.Configuration;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Configuration
public class CorsConfig implements Filter {
    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) throws IOException, ServletException {
        HttpServletResponse response = (HttpServletResponse) res;
        HttpServletRequest request = (HttpServletRequest) req;

        String origin = request.getHeader("Origin");
        if(origin!=null) {
            response.setHeader("Access-Control-Allow-Origin", origin);
        }

        String headers = request.getHeader("Access-Control-Request-Headers");
        if(headers!=null) {
            response.setHeader("Access-Control-Allow-Headers", headers);
            response.setHeader("Access-Control-Expose-Headers", headers);
        }

        response.setHeader("Access-Control-Allow-Methods", "*");
        response.setHeader("Access-Control-Max-Age", "3600");
        response.setHeader("Access-Control-Allow-Credentials", "true");

        chain.doFilter(request, response);
    }

    @Override
    public void init(FilterConfig filterConfig) {

    }

    @Override
    public void destroy() {
    }
}
```

然后将项目重启。这个时候再去刷新一下前台页面就没问题了：

![image-20231120161542308](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201615340.png)

然后在 App.vue 中修改代码：

```vue
<template>
  <div>Bot昵称：{{ bot_name }}</div>
  <div>Bot战力：{{ bot_rating }}</div>
  <router-view />
</template>

<script>
import $ from 'jquery';
import { ref } from "vue";

export default {
  name: "App",
  // setup 是整个函数的入口
  setup: () => {
    let bot_name = ref("");
    let bot_rating = ref("");

    $.ajax({
      url: "http://127.0.0.1:3000/pk/getbotinfo/",
      type: "get",
      success: resp => {
          // 赋值，显示在页面上
        bot_name.value = resp.name;
        bot_rating.value = resp.rating;
      }
    });

    return {
      bot_name,
      bot_rating
    }
  }
}
</script>

<style></style>
```

这样就可以显示了：

![image-20231120161753248](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201617280.png)

#### 添加背景图片

将背景图片下载到后端项目的 web\src\assets 下，然后在 App.vue 中修改 <style> 块的代码，添加一个背景样式即可：

```css
<style>
    body {
        background-image: url("@/assets/background.png");
        background-size: cover;
    }
</style>
```

新版本的 VUE 会把 `@` 符号定义为当前项目的 src 目录。

## 2、创建菜单与游戏界面

分析页面：

+ 每个页面都有一个导航栏区域 nav
+ 然后是内容区域 content

nav 区基本上每个页面都不变的，所以可把这一部分提出来，专门做成一个组件，可以复用。

### 2.1 创建 nav 组件

在 components 目录下，创建一个 NavBar.vue 文件。每一个 vue 组件都有三个部分

+ html：写在 `<template>` 标签中
+ JavaScript：写在 `<script>` 标签中
+ css：写在 `<style>` 标签中，一般会加上一个 scoped：`<style scoped>` ，这是为了让这个样式不会影响到该组件外其他的部分。

使用 Bootstrap：[bootstrap地址](https://v5.bootcss.com/)。让程序员很轻松地做到美工的工作。

在 bootstrap 中搜索 navbar，然后选择想要的样式复制过来就好，比如这个样式：

![image-20231123144313556](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231443611.png)

```vue
<nav class="navbar navbar-expand-lg bg-body-tertiary">
  <div class="container-fluid">
    <a class="navbar-brand" href="#">Navbar w/ text</a>
    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarText">
      <ul class="navbar-nav me-auto mb-2 mb-lg-0">
        <li class="nav-item">
          <a class="nav-link active" aria-current="page" href="#">Home</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">Features</a>
        </li>
        <li class="nav-item">
          <a class="nav-link" href="#">Pricing</a>
        </li>
      </ul>
      <span class="navbar-text">
        Navbar text with an inline element
      </span>
    </div>
  </div>
</nav>
```

也可以让他变成黑色主题：

```vue
<nav class="navbar navbar-expand-lg bg-body-tertiary " data-bs-theme="dark">
```

将以上代码粘贴到 NavBar.vue 里的 `<template>` 中，然后将这个组件先导入一下：

```vue
<template>
  <!-- 这里是使用 -->
  <NavBar />  
  <router-view />
</template>

<script>
// 这里是导入
import NavBar from './components/NavBar.vue'

export default {
  // 这里是注册
  components: {
    NavBar
  }
}
</script>
```

然后现在的界面就是：

![image-20231123144846777](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231448885.png)

此时是因为样式还没有导进来。要先将 bootstrap 的依赖导入进来，因为最开始我们就已经安装了 bootstrap 的依赖，所以现在只需要导入即可：

```vue
import "bootstrap/dist/css/bootstrap.min.css"
import "bootstrap/dist/js/bootstrap"
```

此时页面上会报错：

![image-20231123145232236](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231452290.png)

将图中的名字复制下来，然后在 VUE 控制台中选择安装依赖，搜索这个名字的依赖，将这个依赖安装就可以了。这就是安装后的导航栏样式：

![image-20231123145550204](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231455259.png)

可以对样式进行一些修改：

```vue
<template>
    <nav class="navbar navbar-expand-lg bg-body-tertiary">
        <!-- <div class="container-fluid"> 这个是宽的导航栏 -->
        <div class="container"> <!-- 这个是窄的导航栏-->
            <a class="navbar-brand" href="#">King Of Bots</a> <!-- 标题-->
            <div class="collapse navbar-collapse" id="navbarText">
                <ul class="navbar-nav me-auto mb-2 mb-lg-0">
                    <li class="nav-item">
                        <a class="nav-link" aria-current="page" href="#">对战</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="#">对局列表</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="#">排行榜</a>
                    </li>
                </ul>
                <ul class="navbar-nav">
                    <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" href="#" role="button" data-bs-toggle="dropdown"
                            aria-expanded="false">
                            zhangshimao
                        </a>
                        <ul class="dropdown-menu">
                            <li><a class="dropdown-item" href="#">我的Bots</a></li>
                            <li>
                                <hr class="dropdown-divider">
                            </li>
                            <li><a class="dropdown-item" href="#">退出</a></li>
                        </ul>
                    </li>
                </ul>
            </div>
        </div>
    </nav>
</template>

<style scoped></style>

<script>
</script>
```

样式都可以从 bootstrap 里找样式复制下来使用，现在的效果是：

![image-20231123151453966](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231514035.png)

### 2.2 跳转不同的页面

先要实现不同的页面。每个页面也是单写一个组件。一共有五个页面：

+ 对战页面：Pk
+ 对战列表：Record
+ 排行榜：RankList
+ 我的 Bots：UserBots
+ 报错 404 页面：

页面一般放在 views 文件夹下。因为每个页面可能会包括很多个组件，所以推荐在 views 下建文件夹，给每个页面模块都建一个文件夹，然后在每个文件夹中都建一个主页面：

![image-20231123152413367](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231524402.png)

然后给每个页面先建好框架：

```vue
<template>
    <div>404 Not Found</div>
</template>

<script>
</script>

<style scoped></style>
```

然后要让页面和地址产生关联，比如输入 http://localhost:8080/pk/ 时，显示 pk 的首页。

在主页 App.vue 中，包含两个部分：

```vue
<template>
  <NavBar />
  <router-view />
</template>
```

一个是导航栏，一个是 `router-view`，这个 `router-view` 会自动跟着网址来变化，它的变化方式是在 router 文件下的 index.js 中定义的。所以在 router/index.js 中定义：

```vue
import { createRouter, createWebHistory } from 'vue-router'
// 先导入页面
import PkIndexView from "../views/pk/PkIndexView"
import RanklistIndexView from "../views/ranklist/RanklistIndexView"
import RecordIndexView from "../views/record/RecordIndexView"
import UserBotsIndexView from "../views/user/bots/UserBotsIndexView"
import NotFound from "../views/error/NotFound"

// 下面的路径都是从上往下匹配的
const routes = [
  // 再定义路径
  // 定义路径是写一个对象
  // 这里的路径是相对路径，是域名后面的路径
  {
    path: "/pk/",
    name: "pk_index",  // 路径名字
    component: PkIndexView
  },
  {
    path: "/ranklist/",
    name: "ranklist_index",  // 路径名字
    component: RanklistIndexView
  },
  {
    path: "/record/",
    name: "record_index",  // 路径名字
    component: RecordIndexView
  },
  {
    path: "/user/bots/",
    name: "pkuser_bots_index",  // 路径名字
    component: UserBotsIndexView
  },
  {
    path: "/404/",
    name: "404",  // 路径名字
    component: NotFound
  },

]

const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router
```

此时在网站中输入对应的路径就会进入到对应的页面：

![image-20231123194315884](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311231943959.png)

设置只输入网址时，重定向到对战页面：

```vue
{
    path: "/",
    name: "home",
    redirect: "/pk/"
},
```

设置输入不对的网址时，重定向到 404 页面：

```vue
{
    path: "/:catch(.*)",
    redirect: "/404/"
}
```

那要实现通过导航跳到不同页面，将对应的超链接地址 href 改了就行：

```vue
<ul class="navbar-nav me-auto mb-2 mb-lg-0">
    <li class="nav-item">
        <a class="nav-link" aria-current="page" href="/pk/">对战</a>
    </li>
    <li class="nav-item">
        <a class="nav-link" href="/record/">对局列表</a>
    </li>
    <li class="nav-item">
        <a class="nav-link" href="/ranklist/">排行榜</a>
    </li>
</ul>
```

### 2.3 点完页面不刷新

使用 `<router-link>` 标签代替 `<a>` 标签即可：

```vue
<!-- <a class="navbar-brand" href="/">King Of Bots</a> 标题 -->
<router-link class="navbar-brand" :to="{name: 'home'}">King Of Bots</router-link>
```

将 href 换成 `:to=""` 的形式，其中的 name 是路径的名称。

### 2.4 让每个页面都有一个范围

使用 bootstrap 中的 card，card 可以框出一部分的范围。 

```vue
<div class="container">
    <div class="card">
        <div class="card-body">
            对战
        </div>
    </div>
</div>
```

这三个类的作用就是实现以下效果：

![image-20231123200549865](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311232005919.png)

如果不加 container 类的话，这个白色框会撑满宽度。container 是一个自定义大小的容器。

因为每一个页面都应该有这样的一个框，所以可以把这个框单定义一个组件，在 components 下新建一个 ContentField.vue ：

```vue
<template>
    <div class="container content-field">
            <div class="card">
                <div class="card-body">
                    <slot></slot>
                </div>
            </div>
        </div>
</template>

<script>
</script>

<style scoped>
div.content-field{
    margin-top: 20px;
}
</style>
```

框中的内容根据页面不同显示不同，所以使用一个 `<slot>` 标签来渲染。同时还给这个框设置了一个样式，让他没有紧贴导航栏。

然后在每个页面中使用这个组件：

```vue
<template>
    <ContentField>
        对战
    </ContentField>
</template>

<script>
import ContentField from "../../components/ContentField.vue"

export default {
    components: {
        ContentField
    }
}
</script>

<style scoped></style>
```

`<ContentField>` 中的内容就会被渲染到上面的 `<slot>` 中。需要注意的是，在 user/bots/UesrBotsIndexView.vue 中使用时，需要注意组件的路径：`"../../../components/ContentField.vue"`。

现在效果：

![image-20231123202458852](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311232024908.png)

### 2.5 导航栏的高亮

当处于当前页面时，导航栏上的对应标题应该高亮。

高亮的设置就是 `active` 属性的作用，要谁高亮就在谁上设置一个 active。

```vue
<script>
// router 的一个 API
import { useRoute } from 'vue-router';
// 需要使用实时计算的函数来实时获得当前 route 的内容
import { computed } from 'vue';

export default {
    setup() {
        const route = useRoute();
        let route_name = computed(() => route.name);
        return {
            route_name
        }
    }
}
</script>
```

然后在链接上使用三元运算符指定类别：

```vue
<router-link :class="route_name == 'pk_index' ? 'nav-link active' : 'nav-link'"  aria-current="page" :to="{ name: 'pk_index' }">对战</router-link>
```

或者可以使用下面这种方法：

使用 `class="nav-link" ` 和 `active-class="active"` 就可以：

```vue
<router-link class="nav-link" active-class="active" aria-current="page" :to="{ name: 'pk_index' }">
    对战
</router-link>
```

### 2.6 游戏对象的基类

所有的游戏对象都会有动的效果，我们可以把这个动的效果抽离出来，形成一个基类，让所有的游戏对象都继承自这个基类。

在 assets 目录下新建两个文件夹：images 和 scripts，用来存放图片和脚本，顺便将背景图片移动到 images 下，注意要修改一下 App.vue 里的背景图片的路径。

在 scripts 下，建一个 AcGameObject.js 文件，为了每一秒中都能让所有游戏对象刷新一遍，我们需要先把所有游戏对象都存下来。

```js
const AC_GAME_OBJECTS = [];

export class AcGameObject {
    constructor() {
        AC_GAME_OBJECTS.push(this);
    }
}
```

实现每秒钟刷新游戏多次：浏览器有一个函数：`requestAntimationFrame(函数)`，一般浏览器默认是每秒钟刷新 60 次，`requestAntimationFrame` 会在下一次浏览器渲染之前执行一遍，使用递归就可以让他一直调用刷新：

```js
const step = () => {
    requestAnimationFrame(step);
}

requestAnimationFrame(step);
```

然后每个游戏对象需要具备以下几个函数：

```js
start() {  // 只执行一次

}

update() {  // 每一帧执行一次，除了第一帧

}

on_destory() {  // 删除之前执行

}

distory() {  // 将当前对象从对象数组中删除   
    this.on_destory();

    for (let i in AC_GAME_OBJECTS) {
        const obj = AC_GAME_OBJECTS[i];
        if (obj === this) {
            AC_GAME_OBJECTS.splice(i);
            break;
        }
    }
}
```

在 js 的 for 里面，用 in 是遍历下标，用 of 是遍历值。

需要开一个变量来记录这个对象有没有执行过；一般在计算物体移动的时候，会用到一个速度的概念，一秒钟移动几个像素或者几个距离。速度就是一段时间间隔，帧与帧之间执行的时间不一定是一样的，所以我们在算距离的时候，要让速度乘上时间间隔，所以还需要实现一个 API：

```js
constructor() {
    AC_GAME_OBJECTS.push(this);
    this.timedelta = 0;  // 这一帧的执行时刻与上一帧的执行时刻的时间间隔
    this.has_called_start = false;  // 记录有没有被执行过
}

let last_timestamp;  // 上一次执行的时刻
const step = timestamp => {  // 传入的时当前的执行时刻
    for (let obj of AC_GAME_OBJECTS) {
        if (!obj.has_called_start) {  // 没有被执行过
            obj.has_called_start = true;
            obj.start();
        }
        else {  // 执行过了
            obj.timedelta = timestamp - last_timestamp;
            obj.update();
        }
    }
    last_timestamp = timestamp;

    requestAnimationFrame(step);
}
```

这样所有的游戏对象都会第一帧执行一次 start 函数，之后的每一帧都会执行 update 函数。

### 2.7 实现pk页面

将地图画到当前的页面来，可以将背景框删除掉，也就是将 `<ContectFiled>` 删掉即可。

先将游戏区域引入 pk 页面：

```vue
<template>
    <PlayGround>
    </PlayGround>
</template>

<script>
import PlayGround from "../../components/PlayGround.vue"

export default {
    components: {
        PlayGround
    }
}
</script>
```



### 2.8 实现地图

实现一个 13 × 13 的地图。

+ 周围是一圈墙，中间地图区域会随机生成障碍物
+ 左下角和右上角各一条蛇
+ 地图以左上到右下的对角线对称
+ 生成的障碍物必须合法，保证蛇能从左下角走到右上角
+ 每次刷新都会得到一个新的地图

在 assets 下的 scripts 下新建一个 GameMap.js ：

```js
// 先引入基类
// 有时候需要用到 {}，有时候不需要，区别：
//  如果是 export class 的话，就需要用 {}
//  如果是 export default 的话，就不需要用 {}
import { AcGameObject } from "./AcGameObject";

export class GameMap extends AcGameObject {
    constructor(ctx, parent) {  // ctx 是画布，parent 是画布的父元素，用来动态修改画布
        super();

        this.ctx = ctx;
        this.parent = parent;

        // 游戏的地图会动态的变化，比如缩小或放大游戏屏幕时，
        // 如果动态变化的话，游戏里面的对象应该成比例变化
        // 那么游戏里面的绝对距离就不重要
        // 所以我们在写的时候使用相对距离，
        // 先存一下地图每个格子的绝对距离，后面使用坐标就用相对距离
        this.L = 0;  // 地图一个格子的长度
        
        this.rows = 13;  // 行数
        this.cols = 13;  // 列数
    }

    start() {

    }

    update() {
        this.render();  // 每一帧渲染一次
    }

    // 渲染函数
    render() {

    }
}
```

### 2.9 创建游戏区域

新建一个游戏区域，在 components 下新建一个 PlayGround.vue 文件：

```vue
<template>
<div class="palyground"></div>
</template>

<script>
</script>

<style scoped>
div.palyground {
    /* 百分之60的浏览器宽度，百分之70的高度*/
    width: 60vw;
    height: 70vh;
    background-color: lightblue;
    /* 设置居中，且离上方有40px距离*/
    margin: 40px auto;
}
</style>
```

设置宽高和背景色暂时为了方便调试。

![image-20231124094759255](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311240947528.png)

这时的区域就可以随着浏览器窗口的大小自动变化。

然后新建一些组件，用于放在游戏区域内的，比如计分板等。

在 components 下新建一个 GameMap.vue 文件：

```vue
<template>
    <div class="gamemap">
        <!-- 游戏是画在 <canvas> 里的 -->
        <canvas></canvas>
    </div>
</template>

<script>
</script>

<style scoped>
div.gamemap {
    /* 宽高和父元素等长 */
    width: 100%;
    height: 100%;
    /* 设置居中 */
    display: flex;
    /* 水平居中 */
    justify-content: center;
    /* 垂直居中 */
    align-items: center;
}
</style>
```

然后将他引入到游戏区域：

```vue
<template>
    <div class="palyground">
        <GameMap />
    </div>
</template>

<script>
import GameMap from "./GameMap.vue"

export default {
    components: {
        GameMap
    }
}
</script>
```

地图是正方形区域，要使正方形区域的边长最大，所以地图的边长要动态的求：

```js
update_size() {  // 计算地图的大小
    this.L = Math.min(this.parent.clientWidth / this.cols, this.parent.clientHeight / this.rows);
    this.ctx.canvas.width = this.L * this.cols;
    this.ctx.canvas.height = this.L * this.rows;
}

update() {
    this.update_size();
    this.render();  // 每一帧渲染一次
}
```

渲染一下看看效果：

```js
render() {
    this.ctx.fillStyle = "green";
    // 前两个值为起始坐标，后两个为宽高
    this.ctx.fillRect(0, 0, this.ctx.canvas.width, this.ctx.canvas.height);
}
```

关于 canvas 的用法可以参考 MDN 里的教程。

当前效果：

![image-20231124102816609](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241028873.png)

### 2.10 画地图

地图样式：

![image-20231124102944531](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241029604.png)

是深浅格子交替出现形成的，可以根据横纵标之和的奇偶来决定格子颜色，奇数就画一个深色的格子，偶数画一个浅色的格子：

```js
render() {
    // even表偶数，odd表奇数
    const color_even = "#aad752", color_odd = "#a2d048";
    // 画格子
    for (let r = 0; r < this.rows; r++) {
        for (let c = 0; c < this.cols; c++) {
            if ((r + c) % 2 == 0)
                this.ctx.fillStyle = color_even;
            else
                this.ctx.fillStyle = color_odd;
            this.ctx.fillRect(c * this.L, r * this.L, this.L, this.L);
        }
    }
}
```

效果：

![image-20231124104117251](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241041517.png)

### 2.11 放置障碍物

新建一个对象 Wall.js，表示墙：

```js
import { AcGameObject } from "./AcGameObject";

export class Wall extends AcGameObject {
    // 第r行，第c列
    constructor(r, c, gamemap) {
        super();

        this.r = r;
        this.c = c;
        this.gamemap = gamemap;
        this.color = "#b47226";  // 墙的颜色
    }

    update() {
        this.render();  // 每一次都要渲染
    }

    render() {
        const L = this.gamemap.L;
        const ctx = this.gamemap.ctx;

        ctx.fillStyle = this.color;
        // 横坐标、纵坐标、边长
        ctx.fillRect(this.c * L, this.r * L, L, L);
    }
}
```

画墙：墙可以画在 GameMap.js 里：

```js
// 引入 Wall
import { Wall } from "./Wall";

// 定义墙
constructor(ctx, parent) {  
    // ...
    this.walls = [];  // 墙
}

// 创建画墙的函数
create_walls() {
    new Wall(0, 0, this);
}

start() {
    this.create_walls();
}
```

此时的效果就是：

![image-20231124105248180](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241052464.png)

修改 create_wall 函数就可以：

```js
create_walls() {
    // 使用一个bool数组
    const g = [];
    for (let r = 0; r < this.rows; r++) {
        g[r] = [];
        for (let c = 0; c < this.cols; c++) {
            g[r][c] = false;
        }
    }

    // 给四周加上障碍物
    for (let r = 0; r < this.rows; r++) {
        g[r][0] = g[r][this.cols - 1] = true;
    }

    for (let c = 0; c < this.cols; c++) {
        g[0][c] = g[this.rows - 1][c] = true;
    }

    // 画出障碍物
    for (let r = 0; r < this.rows; r++) {
        for (let c = 0; c < this.cols; c++) {
            if (g[r][c])
                this.walls.push(new Wall(r, c, this));
        }
    }
}
```

这时的效果：

![image-20231124105947573](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241059842.png)

为什么墙的颜色会覆盖掉地图的颜色：

+ 在 AcGameOject 中，每次创建一个就 push 一个
+ 先创建了地图，后创建了墙
+ 所以墙会把地图覆盖掉

这时发现墙之间有一些白色的细线，是因为渲染时出了问题，是因为在 update_size 中计算地图大小时，得到的是一个浮点数，而画的时候使用的是整数，所以会有误差，改成这样即可：

```js
this.L = parseInt(Math.min(this.parent.clientWidth / this.cols, this.parent.clientHeight / this.rows)); 
```

接下来就是随机放置一些障碍物：

```js
this.inner_walls_count = 20;  // 内置障碍物的个数

// 创建随机障碍物
// 因为关于主对角线对称，所以只需要随机一半即可
for (let i = 0; i < this.inner_walls_count / 2; i++) {
    for (let j = 0; ; j++) {
        let r = parseInt(Math.random() * this.rows);  // 取到 【0，this.rows）的数
        let c = parseInt(Math.random() * this.cols);
        
        if (g[r][c] || g[c][r]) continue;  // 已有障碍物
        // 防止墙放在了左下角和右上角的位置
        if (r == this.rows - 2 && c == 1 || r == 1 && c == this.cols - 2) continue; 
        
        g[r][c] = g[c][r] = true;
        break;
    }
}
```

效果如图：

![image-20231124112310617](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241123880.png)

保证左下角和右上角的点是连通的，如果不连通的话就重新生成：

将 create_walls 函数返回一个布尔值，写一个检查是否连通的函数 check_connectivity ，如果不连通，则直接返回 false，连通则画出墙并返回 true。那么在 create_walls 的调用处使用循环来调用，确保一定可以生成满足要求的障碍物：

```js
check_connectivity() {
  // ...
}

create_walls() {
    // ...
    // 如果墙让两个点不连通
    if (!this.check_connectivity()) return false;
    // ...
    return true;
}

start() {
    for (let i = 0; i < 1000; i++)  // 尽量不写死循环
        if (this.create_walls())
            break;
}
```

使用 Flod-fill 算法来实现 check_connectivity 函数：

```js
// 当前地图、起点坐标、终点坐标
check_connectivity(g, sx, sy, tx, ty) {
    if (sx == tx && sy == ty) return true;
    g[sx][sy] = true;

    // 上右下左四个方向
    let dx = [-1, 0, 1, 0], dy = [0, 1, 0, -1];
    for (let i = 0; i < 4; i++) {
        let x = sx + dx[i];
        let y = sy + dy[i];

        // 如果没有撞墙，且能连接到终点就返回 true
        if (!g[x][y] && this.check_connectivity(g, x, y, tx, ty))
            return true;
    }
    return false;
}

create_walls() {
    // ...
    const copy_g = JSON.parse(JSON.stringify(g));
    // 如果墙让两个点不连通
    if (!this.check_connectivity(copy_g, this.rows - 2, 1, 1, this.cols - 2)) return false;
    // ...
    return true;
}
```

### 2.12 更改网站图标

将图片保存到 public 下，名字为 favicon.ico 即可。

PK界面最终效果：

![image-20231124164124011](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311241641371.png)

### 2.13 防止两蛇碰头

因为目前棋盘大小是 13 × 13 的，左下角的蛇的起始位置和右上角的蛇的起始位置的奇偶性相同，就意味着有可能下一步两蛇头会走到同一个格子里面，所以可以将棋盘的边长变成 13 × 14，这样右上角的蛇头的起始位置的奇偶性和左下角的蛇头相反，就不会走到同一个格子里去。

但是这样设计过后地图就不能轴对称了，因为它是一个长方形了现在，但是可以做中心对称：

![image-20231124202017812](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311242020906.png)

需要在 GameMap.js 中的创建障碍物的函数 create_walls 中将代码改成中心对称的代码：

```js
if (g[r][c] || g[this.rows - 1 - r][this.cols - 1 - c]) continue;  // 已有障碍物

// 防止墙放在了左下角和右上角的位置
if (r == this.rows - 2 && c == 1 || r == 1 && c == this.cols - 2) continue;

g[r][c] = g[this.rows - 1 - r][this.cols - 1 - c] = true;  // 中心对称
```

### 2.14 添加蛇

添加两条蛇，一条在左下角，一条在右上角。初始的时候，两条蛇都是一个点，在同一的时间两条蛇都会变长，比如：在前 10 步内，每一步边长一格，10 步后，每三步变长一格。

蛇是以一堆格子构成，也就是格子的序列，所以先定义一个格子类：

```js
export class Cell {
    constructor(r, c) {
        this.r = r;
        this.c = c;
        this.x = c + 0.5;  // 坐标转换
        this.y = r + 0.5;
    }
}
```

格子是方的，但是蛇是圆的，所以蛇身体的坐标应该就行一下转换

![image-20231124203250347](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311242032424.png)

为了方便，把蛇也定义为一个对象 Sanke.js：

```js
import { AcGameObject } from "./AcGameObject";
import { Cell } from "./Cell";

export class Snake extends AcGameObject {
    constructor(info, gamemap) {
        super();

        this.id = info.id;
        this.color = info.color;
        this.gamemap = gamemap;
        this.cells = [new Cell(info.r, info.c)];  // 存放蛇，cell[0] 是蛇头
    }

    start() {

    }

    update() {
        this.render();
    }

    render() {

    }
}
```

然后在 GameMap.js 中创建蛇：

```js
this.snakes = [
    new Snake({ id: 0, color: "#4876EC", r: this.rows - 2, c: 1 }, this),
    new Snake({ id: 1, color: "#F94848", r: 1, c: this.cols - 2 }, this),
];
```

此时可以将蛇画出来看一下，方便调试：

```js
 render() {
     const L = this.gamemap.L;
     const ctx = this.gamemap.ctx;

     ctx.fillStyle = this.color;
     for (const cell of this.cells) {
         ctx.beginPath();  // 画圆
         ctx.arc(cell.x * L, cell.y * L, L / 2, 0, Math.PI * 2);  // 画圆弧，参数：圆弧的终点的坐标、圆的半径、起始角度、终止角度
         ctx.fill();
     }
 }
```

此时效果：

![image-20231125101847220](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251018543.png)

### 2.15 蛇动起来

算一下每一帧蛇的位置即可。

```js
this.speed = 5;  // 蛇的速度，一秒移动五个格子

update_move() {
    this.cells[0].x += this.speed * this.timedelta / 1000;  // 向右移动
}

update() {
    this.update_move();  // 每秒刷新位置
    this.render();
}
```

这样就可以实现蛇的移动。

当蛇有很多结时，采用每次移动创建一个新的头且只将尾向前移动的方法，这样每次只会移动两个节点，且画面保持连续感。

何时移动？当两条蛇都有下一步的指令时，就向指令移动。

需要先定义下蛇的指令和状态：

```js
this.direction = -1;  // -1表示没有指令，0、1、2、3 表示上右下左
this.status = "idle";  // idle 表示静止，move 表示移动中，die 表示死亡
```

然后需要判断一个”裁判“来判断蛇的状态，将”裁判“放在一个公共的位置来判断两条蛇下一步能不能走（需要满足：两条蛇都处于静止，且都有下一步操作，才能走），写在 GameMap.js 中：

```js
check_ready() {  // 检查两条蛇是否都准备好了下一回合
    for (const snake of this.snakes) {
        if (snake.status !== "idle") return false;
        if (snake.direction === -1) return false;
    }
    return true;
}
```

准备好下一步后，每条蛇需要更新一下状态：

首先需要知道下一步的方向，先在 Snake.js 中定义下一步的目标位置以及方向的偏移量，还有回合数：

```js
this.next_cell = null;  // 下一步的目标位置
this.dr = [-1, 0, 1, 0];  // 四个方向的偏移量
this.dc = [0, 1, 0, -1];
this.step = 0;  // 回合数
```

然后更新状态的函数：

```js
next_step() {  // 将蛇的状态改为下一步
    const d = this.direction;  // 取出当前的位置
    this.next_cell = new Cell(this.cells[0].r + this.dr[d], this.cells[0].c + this.dc[d]);  // 求出下一个位置
    this.direction = -1;  // 清空方向
    this.status = "move";  // 状态变化
    this.step++;  // 回合数加一
}
```

再在 GameMap.js 中定义让两条蛇进入下一回合的函数：

```js
next_step() {  // 让两条蛇进入下一步
    for (const snake of this.snakes) {
        snake.next_step();
    }
}

update() {
    this.update_size();
    if (this.check_ready()) {
        this.next_step();
    }
    this.render();  // 每一帧渲染一次
}
```

### 2.16 获取用户的操作

用键盘的 wasd 来控制第一条蛇，上下左右方向键来控制第二条蛇。

为了让我们的 canvas 获取用户的操作，需要给 canvas 加一个属性 `tabindex="0"`，在 GameMap.vue 中：

```vue
<canvas ref="canvas" tabindex="0"></canvas>
```

为了方便以后可以从后端获取到输入的数据，在 Snake.js 中写一个统一的接口来设置方向：

```js
set_direction(d) {
    this.direction = d;
}
```

然后在 GameMap.js 中给 canvas 绑定一个获取用户输入的事件即可：

```js
add_listening_events() {
    // 首先要聚焦
    this.ctx.canvas.focus();
    
    const [s0, s1] = this.snakes;
    this.ctx.canvas.addEventListener("keydown", e => {
        switch (e.key) {
            case 'w': s0.set_direction(0); break;
            case 'd': s0.set_direction(1); break;
            case 's': s0.set_direction(2); break;
            case 'a': s0.set_direction(3); break;
            case 'ArrowUp': s1.set_direction(0); break;
            case 'ArrowRight': s1.set_direction(1); break;
            case 'ArrowDown': s1.set_direction(2); break;
            case 'ArrowLeft': s1.set_direction(3); break;
        }
    });
}

start() {
    for (let i = 0; i < 1000; i++)
        if (this.create_walls())
            break;
    this.add_listening_events();
}
```

### 2.17 根据操作控制蛇移动

蛇的移动是在头部加一个新的球，在 Snake.js 中的 next_step 函数里添加以下代码，将每个球都复制一个：

```js
const k = this.cells.length;
for (let i = k; i > 0; i--) {
    this.cells[i] = JSON.parse(JSON.stringify(this.cells[i - 1]));
}
```

然后先在 Snake.js 中实现 update_move 函数：

```js
update_move() {
    // this.cells[0].x += this.speed * this.timedelta / 1000;

    const dx = this.next_cell.x - this.cells[0].x;
    const dy = this.next_cell.y - this.cells[0].y;
    const distance = Math.sqrt(dx * dx + dy * dy);

    if (distance < this.eps) {
        this.cells[0] = this.next_cell;  // 添加一个新蛇头
        this.next_cell = null;
        this.status = "idle";  // 走完了，停下来
    } else {
        const move_distance = this.speed * this.timedelta / 1000;  // 两帧之间走的距离
        this.cells[0].x += move_distance * dx / distance;
        this.cells[0].y += move_distance * dy / distance;
    }
}

update() {  // 每一帧执行一次
    if (this.status === "move")
        this.update_move();  // 每秒刷新位置
    this.render();
}
```

然后先在的效果就是：

![image-20231125125354669](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251253024.png)

但这只是蛇头在移动。还需要控制蛇尾动。

先判断一下当前要不要动蛇尾：

```js
check_tail_increasing() {  // 检测当前回合，蛇的长度是否增加
    if (this.step <= 10) return true;  // 前十步每一步增加一格
    if (this.step % 3 === 1) return true;  // 十步后每三步增加一格
    return false;
}
```

如果蛇尾要变长的话，蛇尾不动就可以了；如果蛇尾不变长的话，蛇尾跟着蛇头动就可以了。

```js
update_move() {
    // this.cells[0].x += this.speed * this.timedelta / 1000;

    const dx = this.next_cell.x - this.cells[0].x;
    const dy = this.next_cell.y - this.cells[0].y;
    const distance = Math.sqrt(dx * dx + dy * dy);

    if (distance < this.eps) {  // 走到目标点
        this.cells[0] = this.next_cell;  // 添加一个新蛇头
        this.next_cell = null;
        this.status = "idle";  // 走完了，停下来

        if (!this.check_tail_increasing()) {  // 蛇不变长
            this.cells.pop();  // 去掉蛇尾
        }
    } else {
        const move_distance = this.speed * this.timedelta / 1000;  // 两帧之间走的距离
        this.cells[0].x += move_distance * dx / distance;
        this.cells[0].y += move_distance * dy / distance;

        if (!this.check_tail_increasing()) {
            const k = this.cells.length;
            const tail = this.cells[k - 1], tail_target = this.cells[k - 2];
            const tail_dx = tail_target.x - tail.x;
            const tail_dy = tail_target.y - tail.y;
            tail.x += move_distance * tail_dx / distance;
            tail.y += move_distance * tail_dy / distance;
        }
    }
}
```

此时效果：

![image-20231125130813573](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251308879.png)

### 2.18 美化蛇

将相邻的两个节点之间填充一个矩形，将中间的缝隙盖住：

![image-20231125130903989](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251309035.png)

修改 render 函数：

```js
render() {
    const L = this.gamemap.L;
    const ctx = this.gamemap.ctx;

    ctx.fillStyle = this.color;
    for (const cell of this.cells) {
        ctx.beginPath();  // 画圆
        ctx.arc(cell.x * L, cell.y * L, L / 2, 0, Math.PI * 2);  // 画圆弧，参数：圆弧的终点的坐标、圆的半径、起始角度、终止角度
        ctx.fill();
    }


    // 填充蛇身体间的空隙
    for (let i = 1; i < this.cells.length; i++) {
        const a = this.cells[i - 1], b = this.cells[i];
        // 如果两点重合就不用了
        if (Math.abs(a.x - b.x) < this.eps && Math.abs(a.y - b.y) < this.eps)
            continue;
        if (Math.abs(a.x - b.x) < this.eps) {  // 竖方向
            ctx.fillRect((a.x - 0.5) * L, Math.min(a.y, b.y) * L, L, Math.abs(a.y - b.y) * L);
        } else {  // 横方向
            ctx.fillRect(Math.min(a.x, b.x) * L, (a.y - 0.5) * L, Math.abs(a.x - b.x) * L, L);
        }
    }
}
```

关于坐标的计算参考：



![image-20231125131732532](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251317602.png)

现在效果：

![image-20231125131929404](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251319712.png)

但是这个蛇身体太粗了，调整一下：蛇的宽度是 L，将它变为百分之80 L。同时，填充的矩形的坐标也要缩：

```js
render() {
    const L = this.gamemap.L;
    const ctx = this.gamemap.ctx;

    ctx.fillStyle = this.color;
    for (const cell of this.cells) {
        ctx.beginPath();  // 画圆
        ctx.arc(cell.x * L, cell.y * L, L / 2 * 0.8, 0, Math.PI * 2);  // 画圆弧，参数：圆弧的终点的坐标、圆的半径、起始角度、终止角度
        ctx.fill();
    }


    // 填充蛇身体间的空隙
    for (let i = 1; i < this.cells.length; i++) {
        const a = this.cells[i - 1], b = this.cells[i];
        // 如果两点重合就不用了
        if (Math.abs(a.x - b.x) < this.eps && Math.abs(a.y - b.y) < this.eps)
            continue;
        if (Math.abs(a.x - b.x) < this.eps) {  // 竖方向
            ctx.fillRect((a.x - 0.4) * L, Math.min(a.y, b.y) * L, L * 0.8, Math.abs(a.y - b.y) * L);
        } else {  // 横方向
            ctx.fillRect(Math.min(a.x, b.x) * L, (a.y - 0.4) * L, Math.abs(a.x - b.x) * L, L * 0.8);
        }
    }
}
```

这样就可以了：

![image-20231125144359931](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251444244.png)

### 2.19 检测撞墙功能

检测蛇有没有撞墙等，就是判断下一个位置是否合法。

在 GameMap.js 里实现检测逻辑：

```js
check_valid(cell) {  // 检测目标位置是否合法：没有撞到两条蛇的身体和障碍物
    // 判断有没有撞到墙
    for (const wall of this.walls)
        if (wall.r === cell.r && wall.c === cell.c)
            return false;
    // 判断有没有撞到身体
    // 特判：头追尾时，蛇尾有可能会缩，如果缩的话，合法；不缩，不合法
    for (const snake of this.snakes) {
        const k = snake.cells.length;
        if (!snake.check_tail_increasing())  // 蛇尾会前进时，不判断
            k--;
        for (let i = 0; i < k; i++)
            if (snake.cells[i].r === cell.r && snake.cells[i].c === cell.c)
                return false;
    }
    return true;
}
```

这个函数需要在蛇走下一步的时候调用，且会改变蛇的状态：

```js
next_step() {  // 将蛇的状态改为下一步
    const d = this.direction;  // 取出当前的位置
    this.next_cell = new Cell(this.cells[0].r + this.dr[d], this.cells[0].c + this.dc[d]);  // 求出下一个位置
    this.direction = -1;  // 清空方向
    this.status = "move";  // 状态变化
    this.step++;  // 回合数加一

    const k = this.cells.length;
    for (let i = k; i > 0; i--) {
        this.cells[i] = JSON.parse(JSON.stringify(this.cells[i - 1]));
    }

    if (!this.gamemap.check_valid(this.next_cell))  // 下一步操作撞了，蛇当场去世
        this.status = "die";
}
```

然后为了方便看到蛇去世，在 render 函数中可以判断是否是死亡状态，是则将颜色改为白色：

```js
if (this.status === "die")  // 死亡时的颜色
    ctx.fillStyle = "white";
```

现在效果：

![image-20231125150036459](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251500774.png)

### 2.20 给蛇加眼睛

加两个眼睛其实就是画两个小圆。

需要存一下蛇头的方向，因为眼睛始终是在蛇头朝向的方向那一端，所以在 Snake.js 中定义下：

```js
// 左下角的蛇初始朝上，右上角的蛇初始朝下
this.eye_direction = 0;  // 蛇头方向，也就是蛇眼方向
if (this.id === 1) this.eye_direction = 2;  
```

每次在走下一步的时候，就要在 next_step 函数里更改一下蛇头的方向：

```js
this.eye_direction = d;  // 更改蛇头方向
```

然后看不同方向上，两个眼睛的偏移量：

![image-20231125151036099](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251510163.png)

```js
this.eye_dx = [  // 蛇眼的不同方向的 x 的偏移量
    [-1, 1],
    [1, 1],
    [1, -1],
    [-1, -1]
];
this.eye_dy = [  // 蛇眼的不同方向的 y 的偏移量
    [-1, -1],
    [-1, 1],
    [1, 1],
    [-1, 1]
];
```

然后在 render 中用黑色渲染出眼睛：

```js
ctx.fillStyle = "black";
for (let i = 0; i < 2; i++) {

    const eye_x = (this.cells[0].x + this.eye_dx[this.eye_direction][i] * 0.15) * L;
    const eye_y = (this.cells[0].y + this.eye_dy[this.eye_direction][i] * 0.15) * L;
    ctx.beginPath();
    ctx.arc(eye_x, eye_y, L * 0.05, 0, Math.PI * 2);
    ctx.fill();
}
```

最终效果：

![image-20231125152716862](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251527207.png)

