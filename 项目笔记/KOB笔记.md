# KOB

大体思路与结构：

![image-20240909183146117](https://gitee.com/LowProfile666/image-bed/raw/master/img/202409091831383.png)

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

这里的两个 @RequestMapping() 其实没有区别，写成两个的话就会自动拼接起来，和以下代码效果一样：

```java
@Controller
public class IndexController {
    @RequestMapping("/pk/index/")
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

## 3、配置MySQL

到目前为止，整个项目的模型：

![image-20231125154056835](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251540919.png)

### 3.1 MySQL 常用操作

mysql 服务的关闭与启动（默认开机自动启动，如果想手动操作，可以参考如下命令）

+ 关闭：`net stop mysql80`
+ 启动：`net start mysql80`

mysql 的常用操作

+ 连接用户名为root，密码为123456的数据库服务：`mysql -uroot -p123456`
+ `show databases;`：列出所有数据库
+ `create database kob;`：创建数据库
+ `drop database kob;`：删除数据库
+ `use kob;`：使用数据库kob
+ `show tables;`：列出当前数据库的所有表
+ `create table user(id int, username varchar(100))`：创建名称为user的表，表中包含id和username两个属性。
+ `drop table user;`：删除表
+ `insert into user values(1, 'zsm');`：在表中插入数据
+ `select * from user;`：查询表中所有数据
+ `delete from user where id = 2;`：删除某行数据

### 3.2 IDEA 操作 MySQL

使用 IDEA 可以图形化操作 MySQL 数据库：

![image-20231125155654286](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251556423.png)

然后配置要连接的数据库，在架构里选择默认架构，如果提示需要下载缺少的驱动文件则点击下载：

![image-20231125155857157](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251558233.png)

点击确定后就可以看到数据库，以及其中的东西：

![image-20231125160055622](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251600761.png)

### 3.3 加入依赖

在 SpringBoot 中想要操作数据库需要加入一些依赖：

打开 [Maven仓库地址](https://mvnrepository.com/)，在这里面搜索一下依赖，复制它们的 Maven 信息，并在 pom.xml 文件中添加：

+ Spring Boot Starter JDBC（2.7.1）
+ Project Lombok：帮忙简化代码（1.18.24）
+ MySQL Connector/J（8.0.29）
+ mybatis-plus-boot-starter：帮我们默认写好了很多 SQL 语句（3.5.2）
+ mybatis-plus-generator：帮忙自动生成函数（3.5.3）

以下的先不装：

+ spring-boot-starter-security
+ jjwt-api
+ jjwt-impl
+ jjwt-jackson

比如：搜索 Spring Boot Starter JDBC，然后点击最新的版本，进入到这个页面，复制这里的 Maven 代码，然后添加到 pom.xml 的 dependencies 中：

![image-20231125160801387](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251608502.png)

![image-20231125160922173](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251609275.png)

依赖都装好了后，点击右边侧边栏的 Maven，点击刷新按钮，让他重新加载，加载好了后，可以在依赖项中看到所安装的依赖。

如果安装依赖的时候报错，可以尝试清除缓存并重启：文件-->清除缓存-->清除并重启

### 3.4 SpringBoot 配置

依赖安装好后，需要配置一下。SpringBoot 也要用用户名和密码才能访问数据库。

在 application.properties 中添加数据库配置：

![image-20231125162453994](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251624074.png)

```
spring.datasource.username=root  # 连接数据库的用户名
spring.datasource.password=123  # 连接数据库的密码
spring.datasource.url=jdbc:mysql://localhost:3306/kob?serverTimezone=Asia/Shanghai&useUnicode=true&characterEncoding=utf-8  # 数据库连接字，serverTimezone 表示服务的时区
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
```

然后启动项目，报错：

```
[main] ERROR org.springframework.boot.SpringApplication - Application run failed
java.lang.NoClassDefFoundError: com/baomidou/mybatisplus/core/toolkit/StringUtils
```

由于这些依赖我都是装的最新版，于是我将所有依赖都换成视频中的版本，除了 MySQL Connector/J 用的最新的版本，因为它已经没有 8.0.29 版了。然后重新运行，成功：

![image-20231125165924276](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251659360.png)

但是页面错误。因为这个路径没有内容，所以会报错，输入有内容的路径时，就不会报错了：

![image-20231125165959804](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251659883.png)

为了方便可以直接把登录页面配置到这个页面来，在 controller/pk 包下，IndexController 中：

```java
@Controller
public class IndexController {
    @RequestMapping("/")
    public String index(){
        return "pk/index.html";  // 这里要写的是在 templates 里面，index 目录的路径
    }
}
```

## 4、 实现注册登录模块

在 controller 下新建几个软件包 ，分别对应几个页面：

![image-20231125170957067](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251709127.png)

在 user 下建一个 UserController。

### 4.1 SpringBoot 层的概念

SpringBoot 中的常用模块

+ pojo层：将数据库中的表对应成 Java 中的 Class
+ mapper层（也叫Dao层）：将 pojo 层的 class 中的操作，映射成 sql 语句
+ service层：写具体的业务逻辑，组合使用 mapper 中的操作
+ controller层：负责请求转发，接受页面过来的参数，传给 Service 处理，接到返回值，再传给页面

### 4.2 实现 pojo 层

在 backend 下新建一个包 pojo，在包下新建一个 User.java，用来将数据库中的 user 表翻译成类：

```java
@Data
@NoArgsConstructor
@AllArgsContructor
public class User {
    private Integer id;
    private String username;
    private String password;
}
```

上面的三个注解，就是使用的 lombox 依赖中的，会自动帮我们生成无参和有参构造函数以及一些常用基本函数。点击运行后，可以在 target 中看到生成的代码，找到 pojo 中的 User，可以看到帮我们生成了哪些代码：

![image-20231125173953045](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251739184.png)

### 4.3 实现 mapper 层

在 backend 下创建一个包 mapper，包里创建一个 UserMapper 文件：

```java
@Mapper
public interface UserMapper extends BaseMapper<User> {
}
```

安装的依赖 mybaits-plus 帮我们实现了很多东西，要想使用，就需要继承过来。

### 4.4 测试如何操作数据库

#### 查询操作

在 controller/user 下的 UserController 里，要加一个注解 `@RestController` ，在这里实现一些数据库的操作：

```java
@RestController
public class UserController {

    @Autowired  // 如果用到数据库的mapper，一定要加这个注解
    UserMapper userMapper;


    @GetMapping("/user/all/")
    // 返回所有的用户
    public List<User> getAll() {
        return userMapper.selectList(null);
    }
}
```

mapper 里的接口都是在 mybaits-plus 里定义好的，可以查询官网的文档：[Mybatis-Plus官网](https://baomidou.com/)。

这时就可以访问：

![image-20231125175531040](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251755089.png)

根据 id 来查询用户：

```java
// 根据 ID 返回用户
@GetMapping("/user/{userId}/")  // {} 中间的是参数
public User getUser(@PathVariable int userId) { // 这个注解用于将URL中的路径参数绑定到方法的参数上
    return userMapper.selectById(userId);
}
```

![image-20231125175913631](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251759681.png)

实现复杂的查询：

实现复杂的查询需要封装一个条件构造器 QueryWrappr，里面有很多的 API 可以用。比如以上的代码可以改为：

```java
@GetMapping("/user/{userId}/")  // {} 中间的是参数
public User getUser(@PathVariable int userId) { // 这个注解用于将URL中的路径参数绑定到方法的参数上
    QueryWrapper<User> queryWrapper = new QueryWrapper<>();
    queryWrapper.eq("id", userId);
    return userMapper.selectOne(queryWrapper);
}
```

效果是一样的。

如果想查询一个区间内的用户，查询用户id大于等于 1 且小于等于 3 的用户：

```java
@GetMapping("/user/{userId}/")  // {} 中间的是参数
public List<User> getUser(@PathVariable int userId) { // 这个注解用于将URL中的路径参数绑定到方法的参数上
    QueryWrapper<User> queryWrapper = new QueryWrapper<>();
    queryWrapper.ge("id", 1).le("id", 3);
    // ge：大于等于，gt：大于，le：小于等于，lt：小于
    // g是greater，l是lesser
    return userMapper.selectList(queryWrapper);
}
```

+ ge：大于等于，gt：大于
+ le：小于等于，lt：小于
+ g是greater，l是lesser

效果：

![image-20231125181038940](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251810998.png)

#### 插入操作

插入操作一般使用 Post（安全，长度不受限制），这里演示使用 Get。

```java
@GetMapping("/user/add/{userId}/{username}/{password}/")  // {userId}其实就是将当前位置的值当作userId
public String addUser(@PathVariable int userId,
                      @PathVariable String username,
                      @PathVariable String password) {
    User user = new User(userId, username, password);
    userMapper.insert(user);
    return "Add User Successfully";
}
```

测试：

![image-20231125181837138](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251818194.png)

此时数据库中就会多出一条数据。

#### 删除操作

```java
@GetMapping("/user/delete/{userId}/")
public String deleteUser(@PathVariable int userId) {
    userMapper.deleteById(userId);
    return "Delete User Successfully";
}
```

结果：

![image-20231125182223628](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251822684.png)

### 4.5 权限判断模块

先安装 spring-boot-starter-security 依赖，选择了视频中的版本：2.7.1，然后点击 Maven，点击重新加载。然后重启一下服务，发现会弹出一个登录的页面，此时访问其他所有页面都访问不了了：

![image-20231125183037805](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251830896.png)

这个页面是 spring-boot-starter-security 自己写的，不止这一个页面，还有 logout 等其他页面。

它默认有一个用户 user，密码每次会随机生成，在控制台中寻找：

![image-20231125183312026](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251833102.png)

使用这个密码就可以登录，就可以访问所有页面了。

#### 修改 Spring Security

让 Spring Security 对接数据库。

+ 实现 `service.impl.UserDetailsServiceImpl` 类，继承自 `UserDetailsService` 接口，用来接入数据库信息

+ 实现 `config.SecurityConfig` 类，用来实现用户密码的加密存储

在 backend 下创建一个包 service，包下创建一个包 impl，impl 包下创建一个类 UserDetailsServiceImpl，这个类实现了 UserDetailsService 接口：

```java
@Service
public class UserDetailsServiceImpl implements UserDetailsService {
    // 需要使用数据库的操作
    @Autowired
    private UserMapper userMapper;

    // 根据 username 返回对应 user 的详情信息
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        QueryWrapper<User> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("username", username);
        User user = userMapper.selectOne(queryWrapper);
        if (user == null)
            throw new RuntimeException("用户不存在");

        return new UserDetailsImpl(user);
    }
}
```

当用户存在的话，会返回一个 UserDetailsImpl ，这是自己需要实现的一个接口，在 impl 包下创建一个 utils 包，在 utils 包下写一个 UserDetailsImpl 类，实现了 UserDetails 接口：

```java
package com.kob.backend.service.impl.utils;

import com.kob.backend.pojo.User;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;

import java.util.Collection;

/**
 * Author : ZSM
 * Time :  2023/11/25
 */
public class UserDetailsImpl implements UserDetails {
    private User user;

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return null;
    }

    @Override
    public String getPassword() {
        return user.getPassword();
    }

    @Override
    public String getUsername() {
        return user.getUsername();
    }


    @Override
    public boolean isAccountNonExpired() {
        return true;
    }

    // 账户是否被锁定
    @Override
    public boolean isAccountNonLocked() {
        return true;
    }

    // 授权是否过期
    @Override
    public boolean isCredentialsNonExpired() {
        return true;
    }

    // 用户是否被启用
    @Override
    public boolean isEnabled() {
        return true;
    }
}
```

现在启动项目，使用数据库的用户信息来进行登录测试，会发现控制台报错：

```java
java.lang.IllegalArgumentException: There is no PasswordEncoder mapped for the id "null"
```

这个错误的意思是我们需要提供一个 PasswordEncoder。如果我们就想使用明文的方式存储密码的话，在数据库中的密码的值前面加一个 `{noop}` 就可以了，像这样：

![image-20231125190437897](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251904951.png)

这时候数据库读到这个数据时，就知道这个密码没有使用加密，就可以直接进行判断，而不需要 PasswordEncoder 了。这样再去使用这个账户登录就可以了。

#### 密码加密

实现一个 config 类就可以了。

在 backend/config 包下，创建一个 SecurityConfig 类，用来实现用户密码的加密存储：

```java
@Configuration
@EnableWebSecurity
public class SecurityConfig {

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
}
```

这个 BCryptPasswordEncoder 类有几个 API：

+ `encode()`：将明文转成密文
+ `matches()`：判断一个明文和一个密文是否匹配

可以在 test 中试一下：

```java
@SpringBootTest
class BackendApplicationTests {
	@Test
	void contextLoads() {
		PasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
		System.out.println(passwordEncoder.encode("123"));
		System.out.println(passwordEncoder.matches("123", "$2a$10$PIOupAaMEWIo4C6PmV6U8e.E/cBMWYlTu2ZvqzXlx0xOb5j7JW462"));
	}
}
```

可以将所有密码的密文输出出来，然后复制，修改到数据库中，再在前台使用明文密码登录，也可以登录成功的：

![image-20231125192244037](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251922097.png)

登录时使用 123 为密码可以登录成功，因为数据库中的密文可以和 123 匹配。

#### 使用密文存储

在添加用户时，可以直接存储密文。在 UserController 中：

```java
@GetMapping("/user/add/{userId}/{username}/{password}/")  // {userId}其实就是将当前位置的值当作userId
public String addUser(@PathVariable int userId,
                      @PathVariable String username,
                      @PathVariable String password) {
    PasswordEncoder passwordEncoder = new BCryptPasswordEncoder();  
    String encodedPassword = passwordEncoder.encode(password);  // 得到密文
    User user = new User(userId, username, encodedPassword);
    userMapper.insert(user);
    return "Add User Successfully";
}
```

登录前台后，访问以下页面：

![image-20231125192724188](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251927244.png)

再查看数据库中的数据：

![image-20231125192757133](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251927189.png)

### 4.6  JWT 验证

上面的登录验证使用的是传统的 session 验证模式：

![image-20231125194857951](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251948031.png)

JWT 模式：

![image-20231125195643738](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311251956836.png)

用户会在自己的 token 存在浏览器里，每次想服务器发送请求的时候都会带上这个 token；服务器收到一个请求，会先验证这个 token 是否合法，合法就会根据 token 里的信息（包括 userId）从数据库中查找用户，并把用户信息提取到上下文当中，然后再访问授权的方法。

实现步骤

+ 实现`utils.JwtUtil`类，为jwt工具类，用来创建、解析jwt token
+ 实现`config.filter.JwtAuthenticationTokenFilter`类，用来验证jwt token，如果验证成功，则将User信息注入上下文中
+ 配置`config.SecurityConfig`类，放行登录、注册等接口

先添加三个依赖：

+ jjwt-api（0.11.5）
+ jjwt-impl（0.11.5）
+ jjwt-jackson（0.11.5）

然后点击 maven，点击重新加载。

#### JwtUtil 类

在 backend 下新建一个包 utils，在 utils 下实现 JwtUtil 类，为 jwt 工具类，用来创建、解析 jwt token，作用：

+ 将一个字符串，加上密钥，加上有效期，变成一个加密后的字符串。
+ 解析一个令牌，取出当中的 userID

```java
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import org.springframework.stereotype.Component;

import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
import java.util.Date;
import java.util.UUID;

@Component
public class JwtUtil {
    public static final long JWT_TTL = 60 * 60 * 1000L * 24 * 14;  // 有效期14天
    public static final String JWT_KEY = "SDFGjhdsfalshdfHFdsjkdsfds121232131afasdfac";

    public static String getUUID() {
        return UUID.randomUUID().toString().replaceAll("-", "");
    }

    public static String createJWT(String subject) {
        JwtBuilder builder = getJwtBuilder(subject, null, getUUID());
        return builder.compact();
    }

    private static JwtBuilder getJwtBuilder(String subject, Long ttlMillis, String uuid) {
        SignatureAlgorithm signatureAlgorithm = SignatureAlgorithm.HS256;
        SecretKey secretKey = generalKey();
        long nowMillis = System.currentTimeMillis();
        Date now = new Date(nowMillis);
        if (ttlMillis == null) {
            ttlMillis = JwtUtil.JWT_TTL;
        }

        long expMillis = nowMillis + ttlMillis;
        Date expDate = new Date(expMillis);
        return Jwts.builder()
                .setId(uuid)
                .setSubject(subject)
                .setIssuer("sg")
                .setIssuedAt(now)
                .signWith(signatureAlgorithm, secretKey)
                .setExpiration(expDate);
    }

    public static SecretKey generalKey() {
        byte[] encodeKey = Base64.getDecoder().decode(JwtUtil.JWT_KEY);
        return new SecretKeySpec(encodeKey, 0, encodeKey.length, "HmacSHA256");
    }

    public static Claims parseJWT(String jwt) throws Exception {
        SecretKey secretKey = generalKey();
        return Jwts.parserBuilder()
                .setSigningKey(secretKey)
                .build()
                .parseClaimsJws(jwt)
                .getBody();
    }
}
```

#### JwtAuthenticationTokenFilter 类

在 config 包下新建一个 filter 包，在 filter 包内实现 JwtAuthenticationTokenFilter 类，用来验证 jwt token，如果验证成功，则将 User 信息注入上下文中：

`````java
import com.kob.backend.mapper.UserMapper;
import com.kob.backend.pojo.User;
import com.kob.backend.service.impl.utils.UserDetailsImpl;
import com.kob.backend.utils.JwtUtil;
import io.jsonwebtoken.Claims;
import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.filter.OncePerRequestFilter;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Component
public class JwtAuthenticationTokenFilter extends OncePerRequestFilter {
    @Autowired
    private UserMapper userMapper;

    @Override
    protected void doFilterInternal(HttpServletRequest request, @NotNull HttpServletResponse response, @NotNull FilterChain filterChain) throws ServletException, IOException {
        String token = request.getHeader("Authorization");

        if (!StringUtils.hasText(token) || !token.startsWith("Bearer ")) {
            filterChain.doFilter(request, response);
            return;
        }

        token = token.substring(7);

        String userid;
        try {
            Claims claims = JwtUtil.parseJWT(token);
            userid = claims.getSubject();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        User user = userMapper.selectById(Integer.parseInt(userid));

        if (user == null) {
            throw new RuntimeException("用户名未登录");
        }

        UserDetailsImpl loginUser = new UserDetailsImpl(user);
        UsernamePasswordAuthenticationToken authenticationToken =
                new UsernamePasswordAuthenticationToken(loginUser, null, null);

        SecurityContextHolder.getContext().setAuthentication(authenticationToken);

        filterChain.doFilter(request, response);
    }
}
`````

#### SecurityConfig 配置

修改 config 包下的 SecurityConfig 文件：

```java
import com.kob.backend.config.filter.JwtAuthenticationTokenFilter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpMethod;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private JwtAuthenticationTokenFilter jwtAuthenticationTokenFilter;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    @Override
    public AuthenticationManager authenticationManagerBean() throws Exception {
        return super.authenticationManagerBean();
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http.csrf().disable()
                .sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS)
                .and()
                .authorizeRequests()
                .antMatchers("/user/account/token/", "/user/account/register/").permitAll()  // 这两个链接是公开的
                .antMatchers(HttpMethod.OPTIONS).permitAll()
                .anyRequest().authenticated();

        http.addFilterBefore(jwtAuthenticationTokenFilter, UsernamePasswordAuthenticationFilter.class);
    }
}
```

### 4.7 创建后端API

先修改一下数据库中的 user 表

+ 将用户 id 改为自增的，主键
+ 创建一个新的列用来存储用户头像（数据库中存头像一般是链接）

然后数据库发生了变化，需要将 pojo 层的内容也改一下：

```java
@Data
@NoArgsConstructor
@AllArgsConstructor
public class User {
    @TableId(type = IdType.AUTO)  // 设置 id 自增
    private Integer id;
    private String username;
    private String password;
    private String photo;
}
```

写 API 只需要改三个地方：

+ controller：用来调 service 里的接口
+ service：在service里面写一个接口
+ impl：在 service/impl 下写一个接口的实现

在 service 下创建一个包 user，用来存放和 user 有关的，在 user 下再创建一个包 account，用来放和 account 有关的 API，在 account 包里创建三个接口：LoginService、InfoService、RegisterService。习惯让所有的 API 都返回一个 Map。

InfoService：

```java
public interface InfoService {
    Map<String, String> getInfo();
}
```

LoginService：

```java
public interface LoginService {
    Map<String, String> getToken(String username, String password);
}
```

RegisterService：

```java
public interface RegisterService {
    /**
     *
     * @param username 用户名
     * @param password 密码
     * @param confirmedPassword 确认密码
     * @return json信息
     */
    Map<String, String> register(String username, String password, String confirmedPassword);
}
```

接下来实现接口。在 service/impl 下建一个包 user，在 user 下建一个包 account，在 account 下写实现类，实现一个 service 要加一个注解 `@Service`：

#### 获取token

根据用户的用户名和密码，来获取一个 jwt-token，

LoginServiceImpl：

```java
@Service
public class LoginServiceImpl implements LoginService {

    @Autowired
    private AuthenticationManager authenticationManager;  // 用到验证用户登录
    @Override
    public Map<String, String> getToken(String username, String password) {
        // 将用户名和密码封装一下，因为在数据库中已密文的形式存密码
        // 这个类里面存的就不会是明文了，而是加密后的密码
        UsernamePasswordAuthenticationToken authenticationToken =
                new UsernamePasswordAuthenticationToken(username, password);

        // 验证是不是可以登录
        // 登录失败的话，会自动处理
        Authentication authenticate = authenticationManager.authenticate(authenticationToken);

        // 取出用户
        UserDetailsImpl loginUser = (UserDetailsImpl) authenticate.getPrincipal();
        User user = loginUser.getUser();

        // 将用户的userId封装成一个jwt-token
        String jwt = JwtUtil.createJWT(user.getId().toString());

        // 定义结果
        // 这里的 key 最好与前端对应
        Map<String, String> map = new HashMap<>();
        map.put("message", "success");
        map.put("token", jwt);

        return map;
    }
}
```

实现类定义成功后，需要实现对应的 controller 。在 controller/user 包下新建一个包 account，在 account 下定义一个类 LoginController：

```java
@RestController
public class LoginController {
    @Autowired  // 注入刚刚创建的接口
    private LoginService loginService;

    // 这里的路径记得在SecurityConfig里的configure方法里将它公开化：所有人都可以访问
    // 需要从post请求中将参数拿出来，可以将这次参数放在一个Map里，需要使用注解 @RequestParam
    @PostMapping("/user/account/token")  // 登录一般使用post，安全一些
    public Map<String, String> getToken(@RequestParam Map<String, String> map) {
        String username = map.get("username");
        String password = map.get("password");
        return loginService.getToken(username, password);
    }
}
```

此时调试一下，访问 http://localhost:3000/user/account/token/ 会发现一个 405 错误，因为默认是 get 请求，而上面代码定义的 post 请求，

+ @PostMapping：只能用 post 请求
+ @GetMapping：只能用 get 请求
+ @RequestMapping：都可以用

所以可以使用 postman 工具来调试，也可以在前台直接调试。

在前端调试，使用 Ajax 调试，在 App.vue 中：

```js
import $ from "jquery"

export default {
  // 这里是注册
  components: {
    NavBar
  },
  setup() {
    $.ajax({
      url: "http://localhost:3000/user/account/token/",
      type: "post",
      data: {
        username: "zsm",
        password: "123"
      },
      success(resp) {
        console.log(resp);
      },
      error(resp) {
        console.log(resp);
      }
    })
  }
}
```

这样一刷新前端首页就会向后端发送请求，然后可以在控制台中看到结果：

![image-20231126082633952](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311260826078.png)

这个返回的信息就是在后端 LoginServiceImpl 中写的：

![image-20231126082744232](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311260827288.png)

#### 获取信息

如果获取 token 成功，则会向服务器发送一个请求，获取当前用户的信息。

在 service/impl/user/account 下新建一个类 InfoServiceImpl：

```java
@Service  // 不写这个注解 controller 就无法注入服务
public class InfoServiceImpl implements InfoService {

    @Override
    public Map<String, String> getInfo() {
        // 如果授权成功，需要从上下文当中将用户信息提取出来
        // 如何转换：
        UsernamePasswordAuthenticationToken authentication =
                (UsernamePasswordAuthenticationToken) SecurityContextHolder.getContext().getAuthentication();

        UserDetailsImpl loginUser = (UserDetailsImpl) authentication.getPrincipal();

        User user = loginUser.getUser();

        Map<String, String> map = new HashMap<>();

        map.put("message", "success");
        map.put("id", user.getId().toString());
        map.put("username", user.getUsername());
        map.put("photo", user.getPhoto());

        return map;
    }
}
```

然后实现 controller/user/account 下新建一个类 InfoController：

```java
@RestController
public class InfoController {
    @Autowired
    private InfoService infoService;

    @GetMapping("/user/account/info/")  // 获取信息一般使用 get，修改、添加、删除一般使用 post
    public Map<String, String> getInfo() {
        return infoService.getInfo();  // 因为 InfoServiceImpl 上使用了注解 @Service，所以它会找到 InfoServiceImpl
    }
}
```

然后在前端测试：

```js
$.ajax({
    url: "http://localhost:3000/user/account/info/",
    type: "get",
    headers: {
        // 授权，这个会传在后端的 filter 里面去，格式也是 filter 定义的，以 "Bearer " 开头，后面的跟 token
        Authorization: "Bearer " + "eyJhbGciOiJIUzI1NiJ9.eyJqdGkiOiI2ODUzNTgzNmMyNzY0M2UxODVlNjBkYWUwY2I3YWFiYiIsInN1YiI6IjEiLCJpc3MiOiJzZyIsImlhdCI6MTcwMDk1OTk0MywiZXhwIjoxNzAyMTY5NTQzfQ.0CeVtQ64eqXtU7sPmkKOfxFfoAmKORWSoXVawzcdHPo"

        // Authntication: ""  // 认证
    },
    success(resp) {
        console.log(resp);
    },
    error(resp) {
        console.log(resp);
    }
});
```

成功：

![image-20231126085607664](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311260856757.png)

#### 注册账号

先在 Service/impl/user/account 下创建一个实现类 RegisterServiceImpl：

```java
@Service
public class RegisterServiceImpl implements RegisterService {
    @Autowired
    private UserMapper userMapper;
    @Autowired
    private PasswordEncoder passwordEncoder;

    @Override
    public Map<String, String> register(String username, String password, String confirmedPassword) {
        Map<String, String> map = new HashMap<>();

        // 判断用户名和密码是否合法
        // 去除用户名的前后空白字符后，判断是否为空
        if (username.isEmpty() || username.trim().isEmpty()) {
            map.put("message", "用户名不能为空");
            return map;
        }
        if (password.isEmpty() || confirmedPassword.isEmpty()) {
            map.put("message", "密码不能为空");
            return map;
        }

        // 判断长度大小，长度根据数据库中的数据类型长度定
        if (username.length() > 100) {
            map.put("message", "用户名长度不能大于100");
            return map;
        }
        if (password.length() > 100) {
            map.put("message", "密码长度不能大于100");
            return map;
        }

        // 两次密码要一样
        if (!password.equals(confirmedPassword)) {
            map.put("message", "两次密码不一致");
            return map;
        }

        // 判断用户名是否重复，需要使用数据库查询
        QueryWrapper<User> queryWrapper = new QueryWrapper<User>();
        queryWrapper.eq("username", username);
        List<User> list = userMapper.selectList(queryWrapper);
        if (!list.isEmpty()) {
            map.put("message", "用户名已存在");
            return map;
        }

        // 将用户名和密码存入数据库
        // 需要将密码加密
        String encodedPassword = passwordEncoder.encode(password);

        // 默认头像
        String photo = "https://cdn.acwing.com/media/user/profile/photo/307620_md_6513a93905.jpeg";

        User user = new User(null, username, encodedPassword, photo);  // id是默认自增的不用穿

        userMapper.insert(user);

        map.put("message", "success");
        return map;
    }
}
```

然后定义 controller，在 controller/user/account 下新建一个类 RegisterController：

```java
@RestController
public class RegisterController {

    @Autowired
    private RegisterService registerService;

    @PostMapping("/user/account/register/")  // 公开访问的页面一定记得要在 SecurityConfig 中放行
    public Map<String, String> register(@RequestParam Map<String, String> map) {
        String username = map.get("username");
        String password = map.get("password");
        String confirmedPassword = map.get("confirmedPassword");
        return registerService.register(username, password, confirmedPassword);
    }
}
```

记得重启一下，然后前端调试：

```js
$.ajax({
    url: "http://localhost:3000/user/account/register/",
    type: "post",
    data: {
        username: "lisi",
        password: "lisi",
        confirmedPassword: "lisi"
    },
    success(resp) {
        console.log(resp);
    },
    error(resp) {
        console.log(resp);
    }
});
```

### 4.8 前端登录注册页面

在 src/views/user 下创建一个目录 account，在 account 下创建两个文件：UserAccountLoginView.vue、UserAccountRegisterView.vue，文件名根据路径来取的。

然后将这两个页面加入 router 中，在 router/index.js 中添加：

```js
import UserAccountLoginView from "../views/user/account/UserAccountLoginView"
import UserAccountRegisterView from "../views/user/account/UserAccountRegisterView"

const routes = [
    //...
    {
       path: "/user/account/login/",
       name: "user_account_login",  // 路径名字
       component: UserAccountLoginView
    },
    {
       path: "/user/account/register/",
       name: "user_account_register",  // 路径名字
       component: UserAccountRegisterView
    },
    //...
]
```

#### 登录页面

在 bootstrap 上抄一个，搜索 grid system 和 form 和 buttons。

+ grid system 用来布局的。grid 将整个平面分为 12 格，我们用中间 3 格区域。
+ form 用来展示登录表单。
+ buttons 用来设置按钮样式 

使 grid 内容居中使用：`justify-content-md-center`

UserAccountLoginView.vue：

```vue
<template>
    <ContentField>
        <div class="row justify-content-md-center">
            <div class="col-3">
                <form>
                    <div class="mb-3">
                        <label for="username" class="form-label">用户名</label>
                        <input type="text" class="form-control" id="username" placeholder="请输入用户名">
                    </div>
                    <div class="mb-3">
                        <label for="password" class="form-label">密码</label>
                        <input type="password" class="form-control" id="password" placeholder="请输入密码">
                    </div>
                    <button type="submit" class="btn btn-primary">登录</button>
                </form>
            </div>
        </div>
    </ContentField>
</template>

<script>
import ContentField from "../../../components/ContentField.vue"

export default {
    components: {
        ContentField
    }
}
</script>
<style scoped >
button {
    width: 100%;
}
</style>
```

#### 全局信息

比如在每个页面都需要存当前登录的用户是谁，所以我们需要把用户的信息存到全局，就需要用到 vue 的 vuex。

将用户信息存在 src 下的 store 下，在 store 下新建一个文件 user.js ：

```js
import $ from "jquery"

export default {
    state: {
        id: "",
        username: "",
        photo: "",
        token: "",
        is_login: false,
    },
    getters: {
    },
    mutations: {  // 一般用来修改数据
        updateStae(state, user) {
            state.id = user.id;
            state.username = user.username;
            state.photo = user.photo;
            state.is_login = user.is_login;
        },
        updateToken(state, token) {
            state.token = token;
        }
    },
    actions: {
        login(context, data) {
            $.ajax({
                url: "http://localhost:3000/user/account/token/",
                type: "post",
                data: {
                    username: data.username,
                    password: data.password
                },
                success(resp) {
                    if (resp.message === "success") {
                        context.commit("updateToken", resp.token);  // 调用mutations中的函数使用commit
                        data.success(resp);  // 这里的函数是 UserAccountLoginView 里调用该login方法是传过来的对象中的函数
                    } else {
                        data.error(resp);  // 这里的函数是 UserAccountLoginView 里调用该login方法是传过来的对象中的函数
                    }
                    
                },
                error(resp) {
                    data.error(resp);
                }
            });
        }
    },
    modules: {
    }
}
```

然后将这个 user.js 加入到全局的 module 里面，在 store/index.js 中：

```js
import { createStore } from 'vuex'
import ModuleUser from "./user"

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
    user: ModuleUser,
  }
})
```

然后在前端页面中实现一下，在 UserAccountLoginView 中修改，且将页面的数据来源绑定成动态的：

```js
<template>
    <ContentField>
        <div class="row justify-content-md-center">
            <div class="col-3">
                <form @submit.prevent="login">
                    <div class="mb-3">
                        <label for="username" class="form-label">用户名</label>
                        <input v-model="username" type="text" class="form-control" id="username" placeholder="请输入用户名">
                    </div>
                    <div class="mb-3">
                        <label for="password" class="form-label">密码</label>
                        <input v-model="password" type="password" class="form-control" id="password" placeholder="请输入密码">
                    </div>
                    <div class="error_message">{{message}}</div>
                    <button type="submit" class="btn btn-primary">登录</button>
                </form>
            </div>
        </div>
    </ContentField>
</template>

<script>
import ContentField from "../../../components/ContentField.vue"
import { useStore } from "vuex";
import { ref } from "vue";

export default {
    components: {
        ContentField
    },
    setup() {
        const store = useStore();
        const username = ref('');
        const password = ref('');
        const message = ref('');

        const login = () => {
            message.value = '';
            store.dispatch("login", {  // 调用 action 中的函数使用 dispatch
                username: username.value,
                password: password.value,
                success(resp) {
                    console.log(resp);
                },
                error() {
                    message.value = "用户名或密码错误"
                }
            })
        };

        return {
            username,
            password,
            message,
            login
        }
    }
}
</script>
<style scoped >
button {
    width: 100%;
}

div.error_message {
    color: red;
}
</style>
```

此时登录页面就可以根据用户名和密码拿到 token 了。

#### 登录跳转

如果用户名和密码正确的话，就让页面跳转到主页面。

先引入 router，然后使用 router 的 push 方法，在 UserAccountLoginView 中：

```js
import router from "../../../router/index"

setup() {
    // ...
    const login = () => {
        // ...
        store.dispatch("login", {
            // ...
            success(resp) {
                router.push({ name: "home" });  // 跳转到 home 页面，这个名字是在 router/index.js 中定义的
            },
            // ...
        })
    }
};
```

此时就可以实现登陆成功直接跳转到主页。

#### 获取信息

登录成功后，希望动态的显示用户的信息。所以登陆成功后，还需要向后端发送一个请求，来获取当前登录用户的信息，所以在 store/user.js 中再写一个辅助函数：

```js
getInfo(context, data) {
    $.ajax({
        url: "http://localhost:3000/user/account/info/",
        type: "get",
        headers: {
            Authorization: "Bearer " + context.state.token,
        },
        success(resp) {  // 成功就更新用户
            if (resp.message === "success") {
                context.commit("updateStae", {
                    ...resp,  // 将resp的内容解析出来,放在当前对象里
                    is_login: true,
                });
                data.success(resp);
            } else {
                data.error(resp);
            }
        },
        error(resp) {
            data.error(resp);
        }

    });
},
```

然后在 UserAccountLoginView 中，调用上面的函数：

```js
setup() {
    // ...
    const login = () => {
        // ...
        store.dispatch("login", {
            // ...
            success() {
                store.dispatch("getInfo", {
                    success() {
                        router.push({ name: "home" });  // 跳转到 home 页面，这个名字是在 router/index.js 中定义的
                        console.log(store.state.user);
                    }
                })
            },
            // ...
        })
    }
};
```

此时就可以拿到登录用户的信息，保存在 store.state.user 中。

#### 显示信息

将获取到的信息显示到右上角的位置，

+ 如果没有登录，则显示注册和登录两个按钮，
+ 已登录则显示用户名

在导航栏组件 NavBar.vue 中，使用 v-if 和 router-link 将右上角的下拉菜单部分改为：

```vue
<ul class="navbar-nav" v-if="$store.state.user.is_login">
    <li class="nav-item dropdown">
        <a class="nav-link dropdown-toggle" href="#" role="button" data-bs-toggle="dropdown"
           aria-expanded="false">
            {{ $store.state.user.username }}
        </a>
        <ul class="dropdown-menu">
            <li>
                <!-- <a class="dropdown-item" href="/user/bots/">我的Bots</a> -->
                <router-link class="dropdown-item" :to="{ name: 'user_bots_index' }">
                    我的Bots
                </router-link>
            </li>
            <li>
                <hr class="dropdown-divider">
            </li>
            <li><a class="dropdown-item" href="#">退出</a></li>
        </ul>
    </li>
</ul>
<ul class="navbar-nav" v-else>
    <li class="nav-item">
        <router-link class="nav-link" :to="{ name: 'user_account_login' }" role="button">
            登录
        </router-link>
    </li>
    <li class="nav-item">
        <router-link class="nav-link" :to="{ name: 'user_account_register' }" role="button">
            注册
        </router-link>
    </li>
</ul>
```

此时右上角的信息就会根据登录状态来显示，且如果没有登录会显示登录和注册的按钮，点击可跳转。

### 4.9 登出

目前这整个认证机制，token 是完全存在本地的，用户将 token 删除，就表示退出登录了。不需要向后端发送请求，直接在前端就可以删除。

在 store/user.js 中的 mutations 中写一个辅助函数：

```js
logout(state) {
    state.id = "";
    state.username = "";
    state.photo = "";
    state.token = "";
    state.is_login = false;
}
```

然后在 actions 中调用 logout：

```js
logout(context) {
    context.commit("logout");
},
```

然后在 NavBar 组件里面加一个事件：

```js
import { useStore } from 'vuex';

setup() {
    // ...
    const store = useStore();
    const logout = () => store.dispatch("logout");

    return {
        route_name,
        logout
    }
}
```

并且修改退出链接的代码：

```vue
 <li><a class="dropdown-item" href="#" @click="logout">退出</a></li>
```

这样的话，当我们点击“退出”的时候，会调用 NavBar.vue 中 setup 里面定义的 logout 函数，这个函数里面会调用 user.js 里面 actions 里定义的 logout 函数，这个函数又会调用 mutations 里面定义的 logout 函数。

这样就实现了退出的功能。

此时的系统的 token 保存在本地，一刷新页面就没有了，登录状态就没有了。

### 4.10 前端页面授权

当未登录时，所有页面都会重定向到登录页面。

为了方便判断哪些页面是需要授权的，可以直接在 route 中保存一个信息：

```js
const routes = [
    {
        path: "/",
        name: "home",
        redirect: "/pk/",
        meta: {  // 存放额外信息的域
            requestAuth: true,  // 是否需要授权
        }
    },
    //...
]
```

在 router 下的 index.js 里，使用 beforeEach 函数：

```js
import { useStore } from 'vuex'  // 需要读取登录状态

// router 在起作用之前执行的函数
// 当每次通过 router 进入某个页面之前会被调用
// to：跳转到的页面
// form：从哪个页面跳过去
// next：将页面要不要执行下一步操作
router.beforeEach((to, from, next) => {
  // 如果没有登录，且访问页面需要登录
  if (to.meta.requestAuth && !useStore().state.user.is_login) {
    next({ name: "user_account_login" });  // 导航到登录页面
  } else {
    next();  // 直接下一步
  }
})
```

### 4.11 注册页面

将登录页面复制过来改一改：

```vue
<template>
    <ContentField>
        <div class="row justify-content-md-center">
                <div class="col-3">
                    <form @submit.prevent="register">
                        <div class="mb-3">
                            <label for="username" class="form-label">用户名</label>
                            <input v-model="username" type="text" class="form-control" id="username" placeholder="请输入用户名">
                        </div>
                        <div class="mb-3">
                            <label for="password" class="form-label">密码</label>
                            <input v-model="password" type="password" class="form-control" id="password" placeholder="请输入密码">
                        </div>
                        <div class="mb-3">
                                <label for="confirmedPassword" class="form-label">确认密码</label>
                                <input v-model="confirmedPassword" type="password" class="form-control" id="confirmedPassword" placeholder="请再次输入密码">
                            </div>
                        <div class="error_message">{{ message }}</div>
                        <button type="submit" class="btn btn-primary">注册</button>
                    </form>
                </div>
            </div>
    </ContentField>
</template>

<script>
import ContentField from "../../../components/ContentField.vue"
import { ref } from 'vue'
import router from "../../../router/index"
import $ from "jquery"

export default {
    components: {
        ContentField
    },

    setup() {
        let username = ref('');
        let password = ref('');
        let confirmedPassword = ref('');
        let message = ref('');

        const register = () => {
            $.ajax({
                url: "http://localhost:3000/user/account/register/",
                type: "post",
                data: {  // 参数，看后端需要什么
                    username: username.value,
                    password: password.value,
                    confirmedPassword: confirmedPassword.value,
                },
                success(resp) {  // 注册成功就直接返回登录页面
                    if (resp.message === "success")
                        router.push({ name: "user_account_login" });
                    else  // 注册失败返回显示错误信息
                        message.value = resp.message;
                },
                error(resp) {
                    console.log(resp);
                }
            });
        };

        return {
            username,
            password,
            confirmedPassword,
            message,
            register
        }
    }
}
</script>
<style scoped >
button {
    width: 100%;
}

div.error_message {
    color: red;
}
</style>
```

注册的 ajax 为什么不放在 user.js 中？

是因为当我们有可能会修改我们 state 的值的时候，才会放在 user.js 中。

### 4.12 登录状态持久化

当前登录后的 token 其实存在内存中，一刷新页面内存就清空了。所以登录状态持久化就是将 token 存在本地浏览器的一小块内存控件里。这个空间是存在 localStorage 中，所以可以将 token 存在 localStorage 中。

在 user.js 中，登录的时候，保存token：

```js
actions: {
    login(context, data) {
        $.ajax({
            // ...
            success(resp) {
                if (resp.message === "success") {
                    localStorage.setItem("jwt_token", resp.token);  // localStorage是一个字典
                    //...
                }
            }
            // ...
        })
    }
}              
```

退出登录的时候，删除掉 token：

```js
actions: {
    logout(context) {
        localStorage.removeItem("jwt_token");
        context.commit("logout");
    },
}   
```

这时登录后，按 F12 查看 Application 中的 Storage/Local storage 中就会有当前登录用户的 token 信息：

![image-20231126171555449](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311261715550.png)

但此时刷新页面后，依旧会取消我们的登录状态，原因是当我们刷新页面时，它不会自动地将我们的 token 从 localstorage 中取出来，所以需要我们手动判断一下。

每次当用户重定向到了登录页面时，就判断有没有本地的 token

+ 有：取出来，验证是否过期
  + 没有过期：直接登录，不需要输入用户密码

在 UserAccountLoginView 中：

```js
setup() {
    // ...
    const jwt_token = localStorage.getItem("jwt_token");
    if (jwt_token) {
        store.commit("updateToken", jwt_token);  // 更新 token
        // 验证token是否合法
        // 从云端获取用户信息
        store.dispatch("getInfo", {
            success() {  // 如果成功，用户直接跳转到首页
                router.push({ name: "home" });
            },
            error() {

            }
        })
    }
}
```

流程：刷新过后，是未登录状态，会跳转到登录页面，然后会从本地拿到 token ，如果 token 存在，则将 token 更新到内存当中，然后再从云端请求一下用户的信息，如果可以请求到信息，表示 token 是有效的，是可以登录的，所以就跳转到首页。

> 也可以把从 localStorage 取用户信息的过程放在 router/index.js 的 beforeEach 函数中，在每次跳转路由前就不用再去请求登录页面，这样就可以每次刷新时对应的 url 也不会发生变化。
>
> ```js
> router.beforeEach((to, from, next) => {
> 
>   let flag = 1;
>   const jwt_token = localStorage.getItem("jwt_token");
> 
>   if (jwt_token) {
>     store.commit("updateToken", jwt_token);
>     store.dispatch("getInfo", {
>       success() {
>       },
>       error() {
>         alert("token无效，请重新登录！");
>         router.push({ name: 'userLogin' });
>       }
>     })
>   } else {
>     flag = 2;
>   }
> 
>   if (to.meta.requestAuth && !store.state.user.is_login) {
>     if (flag === 1) {
>       next();
>     } else {
>       alert("请先进行登录！");
>       next({name: "userLogin"});
>     }
>   } else {
>     next();
>   }
> })
> ```
>
> 

但是这里刷新的时候，虽然跳过了登录的页面，但是登录页面和导航栏在刷新的时候会一闪而过，不好看，优化：

可以先让登录页面和导航栏默认不显示，等我们判断结束之后，再选择将他展示出来，使用一个全局变量来设置默认不显示，在 user.js 中：

```js
state: {
    // ...
    pulling_info: true,  // 表示当前是不是正在获取信息当中
},
mutations: {  // 一般用来修改数据
    //...
    updatePullingInfo(state, pulling_info) {
        state.pulling_info = pulling_info;
    }
},
```

如果在获取信息的话，就不展示我们的登录页面：

```js
<ContentField v-if="!$store.state.user.pulling_info">  <!--正在拉取信息的话不展示-->
    // ...
</ContentField>
// ...
setup() {
    // ...
    const jwt_token = localStorage.getItem("jwt_token");
    if (jwt_token) {
        store.commit("updateToken", jwt_token);  // 更新 token
        // 验证token是否合法
        // 从云端获取用户信息
        store.dispatch("getInfo", {
            success() {  // 如果成功，用户直接跳转到首页
                router.push({ name: "home" });
                store.commit("updatePullingInfo", false);
            },
            error() {
                store.commit("updatePullingInfo", false);
            }
        })
    } else {  // 本地没有 token
       	store.commit("updatePullingInfo", false);
    }
    // ...
}
```

然后在 NavBar.vue 中：

```vue
<ul class="navbar-nav" v-else-if="!$store.state.user.pulling_info">
    <li class="nav-item">
        <router-link class="nav-link" :to="{ name: 'user_account_login' }" role="button">
            登录
        </router-link>
    </li>
    <li class="nav-item">
        <router-link class="nav-link" :to="{ name: 'user_account_register' }" role="button">
            注册
        </router-link>
    </li>
</ul>
```

这样就可以了。

## 5、个人中心页面

### 5.1 创建数据表

先创建数据库表 bot，表中包含的列：

+ id: int：非空、自动增加、唯一、主键
+ user_id: int：非空
  注意：在pojo中需要定义成userId，在queryWrapper中的名称仍然为user_id
+ title: varchar(100)
+ description: varchar(300)
+ content：varchar(10000)：bot 的代码
+ rating: int：默认值为1500
+ createtime: datetime
  pojo中定义日期格式的注解：@JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
+ modifytime: datetime
  pojo中定义日期格式的注解：@JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")

```mysql
CREATE TABLE `kob`.`bot`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `title` varchar(100) NULL,
  `description` varchar(300) NULL,
  `content` varchar(10000) NULL,
  `rating` int NULL DEFAULT 1500,
  `createtime` datetime NULL,
  `modifytime` datetime NULL,
  PRIMARY KEY (`id`)
);
```

创建了数据表就要创建一个 pojo 来对应。

在 pojo 目录下新建一个类 Bot：

```java
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Bot {
    @TableId(type = IdType.AUTO)
    private Integer id;
    private Integer userId;  // 在数据库中以下划线分隔命名的，在这里中用驼峰
    private String title;
    private String description;
    private String content;
    private Integer rating;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date createtime;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date modifytime;
}
```

然后创建 Mapper：

在 mapper 目录下新建一个接口 BotMapper：

```java
@Mapper
public interface BotMapper extends BaseMapper<Bot> {
}
```

### 5.2 实现 API

实现 bot 的增删改查的API。

在 service/user 包下新建一个包 bot，在 bot 包下新建四个接口：AddService、RemoveService、UpdateService、GetListService：

AddService：

```java
public interface AddService {
    Map<String, String> add(Map<String, String> data);
}
```

RemoveService：

```java
public interface RemoveService {
    Map<String, String> remove(Map<String, String> data);
}
```

UpdateService：

```java
public interface UpdateService {
    Map<String, String> update(Map<String, String> data);
}
```

GetListService：

```java
public interface GetListService {
    List<Bot> getList();  // 返回自己的bot信息，自己的userid存在pojo中，不需要传递参数
}
```

接口创建好后，需要实现。在 service/impl/user 包下创建一个包 bot，在 bot 包下创建四个对应的实现类；在 controller/user 包下创建一个包 bot，在这个 bot 包下创建对应的 controller。

#### 添加

AddServiceImpl：

```java
@Service
public class AddServiceImpl implements AddService {

    @Autowired
    private BotMapper botMapper;

    @Override
    public Map<String, String> add(Map<String, String> data) {
        // 需要知道当前插入人是谁，需要取出当前 user：
        UsernamePasswordAuthenticationToken authenticationToken =
                (UsernamePasswordAuthenticationToken) SecurityContextHolder.getContext().getAuthentication();
        UserDetailsImpl loginUser = (UserDetailsImpl) authenticationToken.getPrincipal();
        User user = loginUser.getUser();

        // 将要插入的信息取出来
        String title = data.get("title");
        String description = data.get("description");
        String content = data.get("content");

        // 判断数据合法性
        Map<String, String> map = new HashMap<>();

        if (title == null || title.isEmpty()) {
            map.put("message", "标题不能为空");
            return map;
        }

        if (title.length() > 100) {
            map.put("message", "标题长度不能大于100");
            return map;
        }

        if (description == null || description.isEmpty()) {
            description = "这个用户很懒，什么也没留下~";
        }

        if (description.length() > 300) {
            map.put("message", "Bot描述的长度不能大于300");
            return map;
        }

        if (content == null || content.isEmpty()) {
            map.put("message", "代码不能为空");
            return map;
        }

        if (content.length() > 10000) {
            map.put("message", "代码长度不能超过10000");
            return map;
        }

        Date now = new Date();
        Bot bot = new Bot(null, user.getId(), title, description, content, 1500, now, now);

        botMapper.insert(bot);
        map.put("message", "success");

        return map;
    }
}
```

AddController：

```java
@RestController
public class AddController {
    @Autowired
    private AddService addService;

    @PostMapping("/user/bot/add/")
    public Map<String, String> add(@RequestParam Map<String, String> data) {
        return addService.add(data);
    }
}
```

测试，在前台 views/user/bots 下的 UserBoxIndexView.vue 中：

```vue
<template>
    <ContentField>
        我的Bots
    </ContentField>
</template>

<script>
import ContentField from "../../../components/ContentField.vue"
import $ from 'jquery'
import { useStore } from "vuex";  // 需要读取token

export default {
    components: {
        ContentField
    },
    setup() {
        const store = useStore();
        $.ajax({
            url: "http://localhost:3000/user/bot/add/",
            type: "post",
            data: {
                title: "Bot的标题",
                description: "Bot的描述",
                content: "Bot的代码",
            },
            headers: {  // 访问要授权的页面需要加header
                Authorization: "Bearer " + store.state.user.token,
            },
            success(resp) {
                console.log(resp);
            },
            error(resp) {
                console.log(resp);
            }
        });
    }
}
</script>
<style scoped></style>
```

#### 删除

RemoveServiceImpl：

 ```java
 @Service
 public class RemoveServiceImpl implements RemoveService {
     @Autowired
     private BotMapper botMapper;
     @Autowired
     private QueryWrapper<Bot> queryWrapper;
     @Override
     public Map<String, String> remove(Map<String, String> data) {
         // 先找到用户，因为用户只能删除自己的bot
         UsernamePasswordAuthenticationToken authenticationToken =
                 (UsernamePasswordAuthenticationToken) SecurityContextHolder.getContext().getAuthentication();
         UserDetailsImpl loginUser = (UserDetailsImpl) authenticationToken.getPrincipal();
         User user = loginUser.getUser();
 
         int bot_id = Integer.parseInt(data.get("bot_id"));
         Bot bot = botMapper.selectById(bot_id);
         Map<String, String> map = new HashMap<>();
 
         if (bot == null) {
             map.put("message", "bot不存在或已被删除");
             return map;
         }
 
         if (!bot.getUserId().equals(user.getId())) {
             map.put("message", "没有权限删除该bot");
             return map;
         }
 
         botMapper.deleteById(bot_id);
         
         map.put("message", "success");
         return map;
     }
 }
 ```

RemoveController：

```java
@RestController
public class RemoveController {
    @Autowired
    private RemoveService removeService;
    
    @PostMapping("/user/bot/remove/")
    public Map<String, String> remove(@RequestParam Map<String, String> data) {
        return removeService.remove(data);
    }
}
```

测试，在前台 views/user/bots 下的 UserBoxIndexView.vue 中：

```js
$.ajax({
    url: "http://localhost:3000/user/bot/remove/",
    type: "post",
    data: {
        bot_id: 1,
    },
    headers: {  // 访问要授权的页面需要加header
        Authorization: "Bearer " + store.state.user.token,
    },
    success(resp) {
        console.log(resp);
    },
    error(resp) {
        console.log(resp);
    }
});
```

#### 更新

UpdateServiceImpl：

```java
@Service
public class UpdateServiceImpl implements UpdateService {
    @Autowired
    private BotMapper botMapper;
    @Override
    public Map<String, String> update(Map<String, String> data) {
        UsernamePasswordAuthenticationToken authenticationToken =
                (UsernamePasswordAuthenticationToken) SecurityContextHolder.getContext().getAuthentication();
        UserDetailsImpl loginUser = (UserDetailsImpl) authenticationToken.getPrincipal();
        User user = loginUser.getUser();

        Map<String, String> map = new HashMap<>();

        int bot_id = Integer.parseInt(data.get("bot_id"));  // 要修改的bot的id
        String title = data.get("title");
        String content = data.get("content");
        String description = data.get("description");

        Bot bot = botMapper.selectById(bot_id);

        if (title.isEmpty()) {
            map.put("message", "标题不能为空");
            return map;
        }

        if (title.length() > 100) {
            map.put("message", "标题长度不能大于100");
            return map;
        }

        if (description == null || description.isEmpty()) {
            description = "这个用户很懒，什么也没留下~";
        }

        if (description.length() > 300) {
            map.put("message", "Bot描述的长度不能大于300");
            return map;
        }

        if (content == null || content.isEmpty()) {
            map.put("message", "代码不能为空");
            return map;
        }

        if (content.length() > 10000) {
            map.put("message", "代码长度不能超过10000");
            return map;
        }

        if (bot == null) {
            map.put("message", "bot不存在或已被删除");
            return map;
        }

        if (!bot.getUserId().equals(user.getId())) {
            map.put("message", "没有权限修改该bot");
            return map;
        }

        Date now = new Date();
        // Bot bot2 = new Bot(bot_id,user.getId(),title,description,content,bot.getRating(),bot.getCreatetime(),now);
        Bot bot2 = new Bot(bot_id,user.getId(),title,description,content,null,null,now);  // 使用null也不会更改原有的数据

        botMapper.updateById(bot2);

        map.put("message", "success");

        return map;
    }
}
```

UpdateController：

```java
@RestController
public class UpdateController {
    @Autowired
    private UpdateService updateService;
    @PostMapping("/user/bot/update/")
    public Map<String, String> update(@RequestParam Map<String, String> data) {
        return updateService.update(data);
    }
}
```

测试，在前台 views/user/bots 下的 UserBoxIndexView.vue 中：

```js
$.ajax({
    url: "http://localhost:3000/user/bot/update/",
    type: "post",
    data: {
        bot_id: 2,
        title: "22222",
        description: "22222",
        content: "22222",
    },
    headers: {  // 访问要授权的页面需要加header
        Authorization: "Bearer " + store.state.user.token,
    },
    success(resp) {
        console.log(resp);
    },
    error(resp) {
        console.log(resp);
    }
});
```

#### 查询

GetListServiceImpl：

```java
@Service
public class GetListServiceImpl implements GetListService {
    @Autowired
    private BotMapper botMapper;
    @Override
    public List<Bot> getList() {
        UsernamePasswordAuthenticationToken authenticationToken =
                (UsernamePasswordAuthenticationToken) SecurityContextHolder.getContext().getAuthentication();
        UserDetailsImpl loginUser = (UserDetailsImpl) authenticationToken.getPrincipal();
        User user = loginUser.getUser();

        QueryWrapper<Bot>  queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("user_id", user.getId());
        return botMapper.selectList(queryWrapper);
    }
}
```

GetListController：

```java
@RestController
public class GetListController {
    @Autowired
    private GetListService getListService;
    @GetMapping("/user/bot/getlist/")
    public List<Bot> getList() {
        return getListService.getList();
    }
}
```

测试，在前台 views/user/bots 下的 UserBoxIndexView.vue 中：

```js
$.ajax({
    url: "http://localhost:3000/user/bot/get/",
    type: "get",
    headers: {  // 访问要授权的页面需要加header
        Authorization: "Bearer " + store.state.user.token,
    },
    success(resp) {
        console.log(resp);
    },
    error(resp) {
        console.log(resp);
    }
});
```

### 5.3 实现前端

在 src/views/user/bots 下的 UserBotsIndexView.vue 中实现。

可以使用 bootstrap 中的 grid，grid 将一行分为 12 个部分，我们可以自己规定一个元素占多少格。

```vue
<template>
    <div class="container"> <!--container会根据窗口自动调整大小-->
        <div class="row">
            <div class="col-3">
                <div class="card" style="margin-top: 20px;">
                    <div class="card-body">
                        <img :src="$store.state.user.photo" alt="" style="width: 100%;">
                    </div>
                </div>

            </div>
            <div class="col-9">
                <div class="card" style="margin-top: 20px;">
                    <div class="card-header">
                        <span style="font-size: 130%;">我的Bot</span>
                        <button type="button" class="btn btn-dark float-end">创建Bot</button> <!--float-end是向右对齐的类-->
                    </div>
                    <div class="card-body">
                        <table class="table table-hover">
                            <thead>
                                <tr>
                                    <th>名称</th>
                                    <th>创建时间</th>
                                    <th>操作</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr v-for="bot in bots" :key="bot.id">
                                    <td>{{ bot.title }}</td>
                                    <td>{{ bot.createtime }}</td>
                                    <td>
                                        <button type="button" class="btn btn-secondary" style="margin-right: 10px;">修改</button>
                                        <button type="button" class="btn btn-danger">删除</button>
                                    </td>
                                </tr>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>

    </div>
</template>

<script>

import { ref } from 'vue'
import $ from 'jquery'
import { useStore } from 'vuex'

export default {
    setup() {
        const store = useStore();
        let bots = ref([]);
        const refresh_bots = () => {
            $.ajax({
                url: "http://127.0.0.1:3000/user/bot/getlist/",
                type: "get",
                headers: {
                    Authorization: "Bearer " + store.state.user.token,
                },
                success(resp) {
                    bots.value = resp;
                },
                error() {

                },
            });
        }

        refresh_bots();

        return {
            bots
        }
    }
}
</script>
<style scoped></style>
```

效果：

![image-20231127144305563](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311271443913.png)

### 5.4 创建功能

点击创建按钮，弹出一个浮窗，在浮窗里创建。在 bootstrap 中搜索 modal。浮窗里需要表单，在 bootstrap 中搜索 form。

还是在 UserBotsIndexView.vue 中添加代码：

```vue
<template>
    <div class="container"> <!--container会根据窗口自动调整大小-->
        <!--...-->
            <div class="col-9">
                <div class="card" style="margin-top: 20px;">
                    <div class="card-header">
                        <span style="font-size: 130%;">我的Bot</span>
                        <button type="button" class="btn btn-dark float-end" data-bs-toggle="modal"
                            data-bs-target="#add-bot-btn">
                            创建Bot
                        </button> 
                        <!-- data-bs-toggle="modal" data-bs-target="#exampleModal" 这一句在哪就是点哪打开浮窗 -->
                        <!-- Modal -->
                        <div class="modal fade" id="add-bot-btn" tabindex="-1" aria-labelledby="exampleModalLabel"
                            aria-hidden="true">
                            <div class="modal-dialog modal-xl">
                                <div class="modal-content">
                                    <div class="modal-header">
                                        <h1 class="modal-title fs-5" id="exampleModalLabel">创建 Bot</h1>
                                        <button type="button" class="btn-close" data-bs-dismiss="modal"
                                            aria-label="Close"></button>
                                    </div>
                                    <div class="modal-body">
                                        <div class="mb-3">
                                            <label for="add-bot-title" class="form-label">名称</label>
                                            <input v-model="botadd.title" type="text" class="form-control"
                                                id="add-bot-title" placeholder="请输入Bot名称">
                                        </div>
                                        <div class="mb-3">
                                            <label for="add-bot-description" class="form-label">简介</label>
                                            <textarea v-model="botadd.description" class="form-control"
                                                id="add-bot-description" rows="3" placeholder="请输入Bot简介"></textarea>
                                        </div>
                                        <div class="mb-3">
                                            <label for="add-bot-code" class="form-label">代码</label>
                                            <textarea v-model="botadd.content" class="form-control" id="add-bot-code"
                                                rows="7" placeholder="请编写Bot代码"></textarea>
                                        </div>
                                    </div>
                                    <div class="modal-footer">
                                        <div class="message">{{ botadd.message }}</div>
                                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">取消</button>
                                        <button type="button" class="btn btn-primary" @click="addbot">创建</button>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="card-body">
                        <table class="table table-hover">
                            <thead>
                                <tr>
                                    <th>名称</th>
                                    <th>创建时间</th>
                                    <th>操作</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr v-for="bot in bots" :key="bot.id">
                                    <td>{{ bot.title }}</td>
                                    <td>{{ bot.createtime }}</td>
                                    <td>
                                        <button type="button" class="btn btn-secondary"
                                            style="margin-right: 10px;">修改</button>
                                        <button type="button" class="btn btn-danger">删除</button>
                                    </td>
                                </tr>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import { ref, reactive } from 'vue'  // ref 绑定一个变量，reactive 绑定一个对象
import $ from 'jquery'
import { useStore } from 'vuex'
import { Modal } from 'bootstrap/dist/js/bootstrap'  // 手动关闭浮窗，路径要写完全

export default {
    setup() {
        const store = useStore();
        let bots = ref([]);

        const botadd = reactive({
            title: "",
            description: "",
            content: "",
            message: "",
        });

        const refresh_bots = () => {
            $.ajax({
                url: "http://127.0.0.1:3000/user/bot/getlist/",
                type: "get",
                headers: {
                    Authorization: "Bearer " + store.state.user.token,
                },
                success(resp) {
                    bots.value = resp;
                },
                error() {
                },
            });
        }

        const addbot = () => {
            botadd.message = "";
            $.ajax({
                url: "http://127.0.0.1:3000/user/bot/add/",
                type: "post",
                data: {
                    title: botadd.title,
                    description: botadd.description,
                    content: botadd.content,
                },
                headers: {
                    Authorization: "Bearer " + store.state.user.token,
                },
                success(resp) {
                    if (resp.message === "success") {
                        botadd.title = "";
                        botadd.content = "";
                        botadd.description = "";
                        Modal.getInstance("#add-bot-btn").hide();  // 关闭浮窗
                        refresh_bots();
                    }
                    else
                        botadd.message = resp.message;
                },
                error() {
                }
            });
        }

        refresh_bots();

        return {
            bots,
            botadd,
            addbot,
        }
    }
}
</script>
<style scoped>
div.message {
    color: red;
}
</style>
```

如果创建时间不对，需要更改时区，在 pojo 层中修改：

```java
@JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "Asia/Shanghai")
private Date createtime;
@JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "Asia/Shanghai")
private Date modifytime;
```

### 5.5 删除功能

```js
const removebot = (bot) => {
    $.ajax({
        url: "http://127.0.0.1:3000/user/bot/remove/",
        type: "post",
        data: {
            bot_id: bot.id,
        },
        headers: {
            Authorization: "Bearer " + store.state.user.token,
        },
        success(resp) {
            if (resp.message === "success")
                refresh_bots();
        }
    });
}
//...
return {
    //...
    removebot,
}
```

在删除按钮上绑定这个事件：

```vue
<button type="button" class="btn btn-danger" @click="removebot(bot)">删除</button>
```

### 5.6 修改功能

要给修改按钮添加一个浮窗，浮窗的 id 随着当前 bot 的 id 有关：

```vue
<button type="button" class="btn btn-secondary" style="margin-right: 10px;"
        data-bs-toggle="modal" :data-bs-target="'#update-bot-modal-' + bot.id">
    修改
</button>
<!-- Modal -->
<div class="modal fade" :id="'update-bot-modal-' + bot.id" tabindex="-1"
     aria-labelledby="exampleModalLabel" aria-hidden="true">
    <div class="modal-dialog modal-xl">
        <div class="modal-content">
            <div class="modal-header">
                <h1 class="modal-title fs-5">修改 Bot</h1>
                <button type="button" class="btn-close" data-bs-dismiss="modal"
                        aria-label="Close"></button>
            </div>
            <div class="modal-body">
                <div class="mb-3">
                    <label for="update-bot-title" class="form-label">名称</label>
                    <input v-model="bot.title" type="text" class="form-control"
                           id="update-bot-title" placeholder="请输入Bot名称">
                </div>
                <div class="mb-3">
                    <label for="update-bot-description"
                           class="form-label">简介</label>
                    <textarea v-model="bot.description" class="form-control"
                              id="update-bot-description" rows="3"
                              placeholder="请输入Bot简介"></textarea>
                </div>
                <div class="mb-3">
                    <label for="update-bot-code" class="form-label">代码</label>
                    <textarea v-model="bot.content" class="form-control"
                              id="update-bot-code" rows="7"
                              placeholder="请编写Bot代码"></textarea>
                </div>
            </div>
            <div class="modal-footer">
                <div class="message">{{ bot.message }}</div>
                <button type="button" class="btn btn-secondary"
                        data-bs-dismiss="modal">取消</button>
                <button type="button" class="btn btn-primary"
                        @click="updatebot(bot)">修改</button>
            </div>
        </div>
    </div>
</div>
```

实现修改函数：

```js
const updatebot = (bot) => {
    $.ajax({
        url: "http://127.0.0.1:3000/user/bot/update/",
        type: "post",
        data: {
            bot_id: bot.id,
            title: bot.title,
            description: bot.description,
            content: bot.content,
        },
        headers: {
            Authorization: "Bearer " + store.state.user.token,
        },
        success(resp) {
            if (resp.message === "success") {
                Modal.getInstance('#update-bot-modal-' + bot.id).hide();  // 关闭浮窗
                refresh_bots();
            }
        }
    });
}
return {
     //...
     updatebot,
}
```

### 5.7 安装编辑器

在 vue 控制台中安装一个依赖 ：vue3-ace-editor 和 ace-builds。安装之后需要集成一下：

在 `<script>` 中导入：

```js
// 加了这个【import "ace-builds/webpack-resolver";】可能会报错
//（若报错 则需要安装node.js的一个包 就是主题）
// 命令：npm install --save-dev file-loader
import "ace-builds/webpack-resolver";
import 'ace-builds/src-noconflict/mode-json';
import 'ace-builds/src-noconflict/theme-chrome';
import 'ace-builds/src-noconflict/ext-language_tools';
```

在 `setup()` 中：

```js
const aceConfig = reactive({
    theme: 'textmate', //主题
    readOnly: false, //是否只读
    options: {
        enableBasicAutocompletion: true,
        enableSnippets: true,
        enableLiveAutocompletion: true,
        tabSize: 2,
        showPrintMargin: false,
        fontSize: 16
    }
});
```

在创建按钮的浮窗中修改 textarea 为：

```vue
<VAceEditor v-model:value="botadd.content" @init="editorInit"
            lang="java" :theme="aceConfig.theme" style="height: 300px"
            :options="aceConfig.options" class="ace-editor" />
```

在修改按钮的浮窗中修改 textarea 为：

```vue
<VAceEditor v-model:value="bot.content" @init="editorInit"
            lang="java" :theme="aceConfig.theme" style="height: 300px"
            :options="aceConfig.options" class="ace-editor" />
```

## 6、微服务：匹配系统

匹配玩家之间 PK。匹配过程：

![image-20231127170104804](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311271701978.png)

在客户端，打开界面、点击匹配后，向服务器发送一个请求，服务器收到请求后会将请求发送到匹配系统，匹配系统将匹配结果返回给服务器，服务器再将匹配信息返回给玩家。

同时，现在的地图是在用户本地生成的，而当两个玩家pk时，地图应该是在服务器端生成一张一模一样的地图，还有蛇的移动、判定等都应该放在服务器端完成。服务器判定完后，将结果返回给前端，前端不做业务逻辑，只画动画。

### 6.1 集成 WebSocket

在 pom.xml 文件中添加依赖：

+ spring-boot-starter-websocket（2.7.2）
+ fastjson（2.0.11）

添加完依赖要刷新下 Maven。

添加 config.WebSocketConfig 配置类：在 config 包下新建类 WebSocketConfig：

```java
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.server.standard.ServerEndpointExporter;

@Configuration
public class WebSocketConfig {

    @Bean
    public ServerEndpointExporter serverEndpointExporter() {

        return new ServerEndpointExporter();
    }
}
```

添加 consumer.WebSocketServer 类，在 backend 下新建一个包 consumer，在 consumer 包下新建一个类 WebSocketServer：

```java
import org.springframework.stereotype.Component;

import javax.websocket.*;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;

@Component
@ServerEndpoint("/websocket/{token}")  // 这是映射的链接，注意不要以'/'结尾
public class WebSocketServer {
    @OnOpen
    public void onOpen(Session session, @PathParam("token") String token) {
        // 建立连接
    }

    @OnClose
    public void onClose() {
        // 关闭链接
    }

    @OnMessage
    public void onMessage(String message, Session session) {
        // 从Client接收消息
    }

    @OnError
    public void onError(Session session, Throwable error) {
        error.printStackTrace();
    }
}
```

配置 config.SecurityConfig，创建的链接默认都会被屏蔽掉，只有在 SecurityConfig 中指定放行的链接才能访问：

```java
@Override
public void configure(WebSecurity web) throws Exception {
    web.ignoring().antMatchers("/websocket/**");
}
```

#### 测试连接

PkIndexView.vue：

```vue
<template>
    <PlayGround>
    </PlayGround>
</template>

<script>
import { useStore } from "vuex";
import PlayGround from "../../components/PlayGround.vue"
// 当当前的组件被加载出来后再建立连接，需要这两个函数
import { onMounted, onUnmounted } from "vue";

export default {
    components: {
        PlayGround
    },
    setup() {
        const store = useStore();
        const socketUrl = `ws://localhost:3000/websocket/${store.state.user.id}`;  // 这里使用的是飘号`，不是单引号

        let socket = null;
        onMounted(() => {  // 挂载的时候需要创建连接
            socket = new WebSocket(socketUrl);  // 创建连接,WebSocket是js自带的类

            socket.onopen = () => {  // 当链接创建成功时
                console.log("connected");
                // 成功创建了链接，要将这个链接存到全局变量里面
                store.commit("updateSocket", socket);
            };

            socket.onmessage = msg => {  // 当接收到信息的时候
                const data = JSON.parse(msg.data);  // sping发过来的是json格式
                console.log(data);
            }

            socket.onclose = () => {  // 当关闭连接时
                console.log("disconnected");
            }
        }); 

        onUnmounted(() => {  // 当当前页面被关闭时
            socket.onclose();  // 如果不断开链接的话，每次切换页面都会新建一个链接，然后刷新一下就会断开所有的链接
        });
    }
}
</script>

<style scoped></style>
```

还要在 store 文件夹下新建一个 pk.js :

```js
// 存和pk有关的全局变量
export default {
    state: {
        status: "matching",  // 当前的状态，matching表示匹配界面，playing表示对战界面
        socket: null,  // 前端和后端建立的连接
        opponent_username: "",  // 竞争对手的名字
        opponent_photo: "",  // 竞争对手头像
    },
    getters: {
    },
    mutations: {
        updateSocket(state, socket) {
            state.socket = socket;
        },
        updateOpponent(state, opponent) {
            state.opponent_username = opponent.username;
            state.opponent_photo = opponent.photo;
        },
        updateStatus(state, status) {
            state.status = status;
        }
    },
    actions: {
    },
    modules: {
    }
}
```

后端中这样写：

```java
@Component
@ServerEndpoint("/websocket/{token}")  // 这是映射的链接，注意不要以'/'结尾
public class WebSocketServer {
    // 存下所有的链接信息，ConcurrentHashMap 是一个线程安全的哈希表
    // 这个是要对所有实例可见的，要加static，不加static的话，每个实例都会有一份
    private static ConcurrentHashMap<Integer, WebSocketServer> users = new ConcurrentHashMap<>();
    private User user;  // 存每个链接对应的用户是谁
    private Session session = null;  // websocket里的一个包，从后端向前端发送信息需要用到的 API
    // 注入数据库服务
    private static UserMapper userMapper;
    @Autowired
    public void setUserMapper(UserMapper userMapper) {
        WebSocketServer.userMapper = userMapper;
    }
    @OnOpen
    public void onOpen(Session session, @PathParam("token") String token) {
        this.session = session;
        System.out.println("connection");
        // 假设token是用户id
        Integer userId = Integer.parseInt(token);
        // 通过id查出用户
        this.user = userMapper.selectById(userId);
        users.put(userId, this);
    }

    @OnClose
    public void onClose() {
        // 关闭链接
        System.out.println("disconnection");
        // 需要将user从users里删掉
        if (this.user != null) {
            users.remove(this.user.getId());
        }
    }
 
    // 从后端往前端发送信息
    public void sendMessage(String message) {
        // 异步操作，加个锁
        synchronized (this.session) {
            try {
                this.session.getBasicRemote().sendText(message);  // 这个api可以从后端向当前的链接发送信息，链接是由session获得的
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
```

此时进入 pk 页面，就建立连接了，后端就可以拿到当前的用户信息。

#### jwt验证

将以上连接时的用户 id 换成 token，使用 jwt 验证。

可以将验证 token 这一模块单独地写一个类出来，在 consumer 包下新建一个 utils 包，在 utils 包下新建一个 JwtAuthentication 类：

```java
public class JwtAuthentication {
    public static Integer getUserId(String token) {
        Integer userId = -1;
        try {
            Claims claims = JwtUtil.parseJWT(token);
            userId = Integer.parseInt(claims.getSubject());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return userId;
    }
}
```

这一块代码是 config/filter  下的 JwtAuthenticationTokenFilter 中的验证代码。

然后在 WebSocketServer 中修改 onOpen 方法：

```java
@OnOpen
public void onOpen(Session session, @PathParam("token") String token) throws IOException {
    this.session = session;
    System.out.println("connection");
    // 拿到用户id
    Integer userId = JwtAuthentication.getUserId(token);
    // 通过id查出用户
    this.user = userMapper.selectById(userId);

    if (this.user != null)
        users.put(userId, this);
    else
        this.session.close();
}
```

接下来就是实现匹配界面，以及实现匹配界面和pk界面的切换，切换由全局变量中的 status 决定，已经定义好了。

### 6.2 实现匹配界面

匹配页面的布局：

![image-20231128160032585](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311281600677.png)

在 components 下新建一个 MatchGround.vue 文件：

```vue
<template>
    <div class="matchground">

    </div>
</template>

<script>

export default {

}
</script>

<style scoped>
div.matchground {
    /* 百分之60的浏览器宽度，百分之70的高度*/
    width: 60vw;
    height: 70vh;
    /* background-color: lightblue; */
    /* 设置居中，且离上方有40px距离*/
    margin: 40px auto;
    background-color: lightblue;  /*调试用*/
}
</style>
```

然后要将匹配界面引入到主界面：

```vue
<template>
    <PlayGround v-if="$store.state.pk.status === 'playing'" />  <!--当状态为playing时才显示-->
    <MatchGround v-else/>
</template>
<script>
//...
import MatchGround from "../../components/MatchGround.vue"
    export default {
        components: {
            PlayGround,
            MatchGround
        },
    }
    //...
</script>
```

此时，将 store/pk.js 中的 status 设为 matching 就可以看到匹配界面：

![image-20231128155820105](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311281558455.png)

然后再修改下 MatchGround.vue：

```vue
<template>
    <div class="matchground">
        <div class="row">
            <div class="col-6">
                <div class="user-photo">
                    <img :src="$store.state.user.photo" alt="">
                </div>
                <div class="user-username">
                    {{ $store.state.user.username }}
                </div>
            </div>
            <div class="col-6">
                <div class="user-photo">
                        <img :src="$store.state.pk.opponent_photo" alt="">
                    </div>
                    <div class="user-username">
                        {{ $store.state.pk.opponent_username }}
                    </div>
            </div>
        </div>
        <div class="col-12" style="text-align: center; padding-top: 10vh;">
            <button @click="click_match_btn" type="button" class="btn btn-outline-warning btn-lg">
                {{ match_btn_info }}
    		</button>
        </div>
    </div>
</template>

<script>
import { ref } from 'vue';

export default {
    setup() {
        let match_btn_info = ref("开始匹配");

        const click_match_btn = () => {
            if (match_btn_info.value === "开始匹配")
                match_btn_info.value = "取消"
            else
                match_btn_info.value = "开始匹配"
        }

        return {
            match_btn_info,
            click_match_btn,
        }
    }
}
</script>

<style scoped>
div.matchground {
    /* 百分之60的浏览器宽度，百分之70的高度*/
    width: 60vw;
    height: 70vh;
    /* background-color: lightblue; */
    /* 设置居中，且离上方有40px距离*/
    margin: 40px auto;
    background-color: rgb(50,50,50,0.5);
}
/* 头像居中 */
div.user-photo {
    text-align: center;  
    padding-top: 10vh;
}
/* 头像变圆变小 */
div.user-photo > img{
    border-radius: 50%;
    width: 20vh;
}
/* 名字居中变大加粗 */
div.user-username {
    text-align: center;
    font-size: 24px;
    font-weight: 600;
    color: white;
    padding-top: 2vh;
}
</style>
```

可以 Pk 主页 PkIndexView 中的 onMounted 函数中指定一个对手的头像和名字：

```js
store.commit("updateOpponent", {
    username: "我的对手",
    photo: "https://cdn.acwing.com/media/article/image/2022/08/09/1_1db2488f17-anonymous.png"
})
```

此时前端页面的效果就是：

![image-20231128164231623](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311281642060.png)

### 6.3 实现业务逻辑

#### 匹配

当点击开始匹配时，向后端发送一个请求，服务器会将请求放在匹配池中，当匹配池满 2 个后，就返回：

![image-20231128164625465](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311281646567.png)

如何区分事件（匹配和取消匹配）：因为传输的数据是 json，所以可以在 json 中添加一个域用来区分：

```js
setup() {
    const store = useStore();

    let match_btn_info = ref("开始匹配");

    const click_match_btn = () => {
        if (match_btn_info.value === "开始匹配") {
            match_btn_info.value = "取消";
            // socket有一个api：send，可以像后端发送信息
            // stringify表示将一个json封装成字符串
            store.state.pk.socket.send(JSON.stringify({
                event: "start-matching",  // 后端用来区分事件
            }));
        }
        else {
            match_btn_info.value = "开始匹配"
            store.state.pk.socket.send(JSON.stringify({
                event: "stop-matching",
            }));
        }
    }
}
```

然后在后端程序 WebSocketServer 中：

```java
@OnMessage
public void onMessage(String message, Session session) {  // 把message当作路由
    // 从Client接收消息
    System.out.println("receive message");

    JSONObject data = JSONObject.parseObject(message);  // 解析字符串成json
    String event = data.getString("event");  // 取出区分域

    if ("start-matching".equals(event)) {
        startMatching();  // 开始匹配
    } else {
        stopMatching();  // 停止匹配
    }
}
public void startMatching() {
    System.out.println("start matching");
    // 开始匹配时，将用户加入匹配池
    matchPool.add(this.user);

    // 当匹配池用户多余两个时，任意匹配
    while (matchPool.size() >= 2) {
        Iterator<User> it = matchPool.iterator();
        User a = it.next(), b = it.next();
        matchPool.remove(a);
        matchPool.remove(b);

        // 匹配成功后。要将信息返回前端
        JSONObject respA = new JSONObject();
        respA.put("event", "start-matching");
        respA.put("opponent_username", b.getUsername());
        respA.put("opponent_photo", b.getPhoto());
        // 获取a的连接，然后给前端发送信息
        users.get(a.getId()).sendMessage(respA.toJSONString());

        JSONObject respB = new JSONObject();
        respB.put("event", "start-matching");
        respB.put("opponent_username", a.getUsername());
        respB.put("opponent_photo", a.getPhoto());
        // 获取a的连接，然后给前端发送信息
        users.get(b.getId()).sendMessage(respB.toJSONString());
    }
}

public void stopMatching() {
    System.out.println("stop matching");
    // 取消匹配时，将用户移除匹配池
    matchPool.remove(this.user);
}
```

然后后端返回给前端的信息也需要接受判断，在 PjIndexView 中：

```js
socket.onmessage = msg => {  // 当接收到信息的时候
    const data = JSON.parse(msg.data);  // sping发过来的是json格式
    if (data.event.value === "start-matching") {  // 匹配成功
        // 更新对手信息
        store.commit("updateOpponent", {
            username: data.opponent_username,
            photo: data.opponent_photo, 
        })
    }
}
```

然后使用两个浏览器来登录两个账号进行测试，因为一个浏览器不能登录两个账号。此时可以匹配成功：

![image-20231128200145331](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311282001749.png)

然后匹配成功后应该跳转 pk 页面，只需要将 pk 的 status 的值改为 playing 即可，同时设置个延迟，2 秒后跳转：

```js
setTimeout(() => {
    store.commit("updateStatus", "playing");
}, 2000);
```

然后设置点击其他页面后就自动取消 pk，当再回到 pk 页面时就是匹配界面，就是在当这个页面被卸载的时候将 pk 的 status 改为 matching：

```js
onUnmounted(() => {  // 当当前页面被关闭时
    socket.onclose();  // 如果不断开链接的话，每次切换页面都会新建一个链接，然后刷新一下就会断开所有的链接
    store.commit("updateStatus", "matching");
});
```

现在就只有同步的问题。每个人的地图都是在本地生成的，所以两方的地图不一样。我们需要同一生成地图，就需要将生成地图的逻辑放在云端。

#### 同步地图

在后端 consumer 包下 utils 包下新建一个类 Game，用来管理整个游戏的流程：

```java
public class Game {
    final private Integer rows;  // 地图行数
    final private Integer cols;  // 地图列数
    final private Integer inner_walls_count;  // 障碍物数
    final private int[][] g;  // 地图
    final private static int[] dx = {-1,0,1,0}, dy={0,1,0,-1};

    public Game(Integer rows, Integer cols, Integer inner_walls_count) {
        this.rows = rows;
        this.cols = cols;
        this.inner_walls_count = inner_walls_count;
        this.g = new int[rows][cols];
    }

    // 返回地图
    public int[][] getG() {
        return g;
    }

    // 画地图
    public void createMap() {
        for (int i = 0; i < 1000; i++) {
            if (draw())
                break;
        }
    }
    private boolean draw() {  // 0表示空地，1表示墙
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.cols; j++) {
                g[i][j] = 0;
            }
        }

        for (int r = 0; r < this.rows; r++) {
            g[r][0] = g[r][this.cols - 1] = 1;
        }

        for (int c = 0; c < this.cols; c++) {
            g[0][c] = g[this.rows - 1][c] = 1;
        }

        Random random = new Random();
        for (int i = 0; i < this.inner_walls_count / 2; i++) {
            int r, c;
            do {
                r = random.nextInt(this.rows);
                c = random.nextInt(this.cols);

                if (g[r][c] == 1 || g[this.rows - 1 - r][this.cols - 1 - c] == 1) continue;

                if (r == this.rows - 2 && c == 1 || r == 1 && c == this.cols - 2) continue;
                // Add symmetry
                g[r][c] = g[this.rows - 1 - r][this.cols - 1 - c] = 1;
                break;
            } while (true);
        }

        return checkConnectivity(this.rows - 2, 1, 1, this.cols - 2);
    }
    private boolean checkConnectivity(int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return true;
        g[sx][sy] = 1;

        for (int i = 0; i < 4; i++) {
            int x = sx + dx[i];
            int y = sy + dy[i];

            // 如果没有撞墙，且能连接到终点就返回 true
            if (g[x][y] == 0 && this.checkConnectivity(x, y, tx, ty)) {
                g[x][y] = 0;
                return true;
            }
        }

        g[sx][sy] = 0;
        return false;
    }
}
```

然后在 WebSocketServer 中要将地图创建出来，并且返回给前端：

```java
public void startMatching() {
 //...
    Game game = new Game(13,14,20);
    game.createMap();
    while (matchPool.size() >= 2) {
     //...
        respA.put("gamemap", game.getG());
     //...
        respB.put("gamemap", game.getG());
    }
}
```

然后在前端要接收到地图，将地图存到一个全局变量中，在 pk.js 中：

```js
export default {
    state: {
        //...
        gamemap: null,
    },
    getters: {
    },
    mutations: {
        //...
        updateGamemap(state, gamemap) {
            state.gamemap = gamemap;
        }
    },
    actions: {
    },
    modules: {
    }
}
```

然后在匹配成功后，更新地图，在 PkIndexView 中：

```js
store.commit("updateGamemap", data.gamemap);
```

在 GameMap.vue 中：

```js
import { useStore } from "vuex";

onMounted(() => {
    new GameMap(canvas.value.getContext('2d'), parent.value, useStore()); 
});
```

然后修改 GameMap.js ：

```js
//...
import { Snake } from "./Snake";

export class GameMap extends AcGameObject {
    constructor(ctx, parent, store) {  
//...
        this.store = store;
//...
    }

    create_walls() {
        // 画出障碍物
        const g = this.store.state.pk.gamemap;
        for (let r = 0; r < this.rows; r++) {
            for (let c = 0; c < this.cols; c++) {
                if (g[r][c])
                    this.walls.push(new Wall(r, c, this));
            }
        }
        return true;
    }
//...
    start() {
        this.create_walls();
        this.add_listening_events();
    }
//...
}
```

这样地图就同步好了。

