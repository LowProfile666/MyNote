# KOB

前后端不分离：html 代码是根据请求的数据在服务器端生成的。client 访问 server，server 直接向 client 发送一个 html 字符串。

前后端分离：返回的 html 代码是在用户端浏览器用 js 代码完成的。打开一个网站，第一步是将网站的静态文件从某个地方先传过来，然后 client 再向 server 发送数据，server 会将一些数据返回给 client，前端接收到数据后，再动态的渲染页面。



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

## 前后端不分离的写法

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

## 创建后端

在 controller.pk 下新建一个类，这个类上的注解就不用 @controller 了，而是用 `@RestController`，同时也要使用映射 `@RequestMapping("/pk/")`，在其下的方法上也使用映射 `@RequestMapping("getinfo/")`，

![image-20231120151047645](https://gitee.com/LowProfile666/image-bed/raw/master/img/202311201510689.png)

点击 application.properties 文件，如果里面是空的，表示是使用的 Spring 默认的网站；如果不是空白的，且 server.port = 8080 的话，最好是将 8080 改了，因为 vue 默认也是使用 8080，这样的话前端后端的项目就会冲突。所以可以将 8080 改成 3000：

```java
server.port=3000
```

然后访问的时候用 http://127.0.0.1:3000。

## 创建前端

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

## 运行web

运行 web 项目后，点击输出中的链接，就可以运行。

### 去除地址栏的#号

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

### 删除无用的文件

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

### 前后端通信

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

#### 解决跨域问题

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

### 添加背景图片

将背景图片下载到后端项目的 web\src\assets 下，然后在 App.vue 中修改 <style> 块的代码，添加一个背景样式即可：

```css
<style>
    body {
        background-image: url("@/assets/background.png");
        background-size: cover;
    }
</style>
```

