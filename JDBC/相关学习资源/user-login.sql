drop table if exists t_user;

/*==============================================================*/
/* Table: t_user                                                */
/*==============================================================*/
create table t_user
(
   id                   bigint auto_increment,
   loginName            varchar(255),
   loginPwd             varchar(255),
   realName             varchar(255),
   primary key (id)
);

insert into t_user(loginName,loginPwd,realName) values('zhangsan','123','张三');
insert into t_user(loginName,loginPwd,realName) values('jack','123','杰克');
commit;
select * from t_user;