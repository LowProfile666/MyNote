建表：

articles：

```mysql
create table articles
(
    id          int auto_increment comment '文章id'
        primary key,
    title       varchar(30)                        not null comment '文章标题',
    summary     varchar(255)                       not null comment '文章摘要',
    content     text                               not null comment '文章内容',
    type        varchar(20)                        not null comment '文章分类',
    creat_time  datetime default CURRENT_TIMESTAMP not null comment '文章创建时间',
    update_time datetime default CURRENT_TIMESTAMP not null comment '文章最新修改时间',
    delete_flag int      default 0                 not null comment '文章是否被删除标记，0为否，1为是'
);
```

user：

```mysql
create table users
(
    id       char(36)    not null comment '用户主键'
        primary key,
    username varchar(10) not null comment '用户名',
    password varchar(20) not null comment '用户密码'
);
```



vue3中安装了bootstrap依赖后，引入bootstrap的js文件时，会报错：

```
 error  in ./node_modules/bootstrap/dist/js/bootstrap.min.js

Module not found: Error: Can't resolve '@popperjs/core' in 'D:\MyCode\e-blog2.0\ui\node_modules\bootstrap\dist\js'

ERROR in ./node_modules/bootstrap/dist/js/bootstrap.min.js 15:82-107
Module not found: Error: Can't resolve '@popperjs/core' in 'D:\MyCode\e-blog2.0\ui\node_modules\bootstrap\dist\js'
 @ ./src/main.js 6:0-44

webpack compiled with 1 error
```

需要安装@popperjs/core这个依赖。



当使用同一个组件渲染不同的路由路径时，默认情况下组件不会重新挂载。如果想要重新挂载，可以在组件上使用key属性，这样每次路径变化时 Vue 会认为是一个全新的组件实例，从而重新挂载组件：

```vue
<template>
    <router-view :key="$route.fullPath"></router-view>
</template>
```

