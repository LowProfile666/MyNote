drop table if exists t_ajax;
create table t_ajax(
    id int primary key auto_increment,
    content varchar(255)
);
insert into t_ajax(content) values('javascript');
insert into t_ajax(content) values('javaweb');
insert into t_ajax(content) values('java');
insert into t_ajax(content) values('java123');
insert into t_ajax(content) values('mysql');
insert into t_ajax(content) values('myweb');
insert into t_ajax(content) values('myapp');
insert into t_ajax(content) values('jdk');
commit;
select * from t_ajax;