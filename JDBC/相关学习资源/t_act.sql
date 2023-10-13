drop table if exists t_act;                                     
create table t_act(                                             
    actno int,                                                  
    balance double(7,2)
);                                                              
insert into t_act(actno,balance) values(111,20000);             
insert into t_act(actno,balance) values(222,0);                 
commit;                                                         
select * from t_act;                                            