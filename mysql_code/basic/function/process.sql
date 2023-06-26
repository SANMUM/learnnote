-- 流程函数
-- if 
select if(true,'ok','error');

--ifnull
select ifnull(null,'default');
select ifnull('ok','default');
select ifnull('','default');

-- case when then else end
-- 查询emp表的员工姓名和地址（上海、北京----->一线城市，其他---->二线城市）
select name,
(case workaddress when '北京' then '一线城市' when '上海' then '一线城市' else '二线城市' end) as 工作地址
from emp;

/*
统计班级各个学员的成绩，展示规则如下：
>= 85，展示优秀
>= 60,展示及格
否则,展示不及格
*/ 
create table score(
id int comment 'ID',
name varchar(20) comment '姓名',
math int comment '数学',
english int comment '英语',
chinese int comment '语文'
) comment '学员成绩表';
insert into score(id, name, math, english, chinese) VALUES  (1, 'Tom', 67, 88, 95), (2, 'Rose' , 23, 66, 90),(3, 'Jack', 56, 98, 76);


select 
id,
name,
( case when math>= 85 then '优秀' when math >= 60 then '及格' else '不及格' end ) as '数学',
( case when english>= 85 then '优秀' when english >= 60 then '及格' else '不及格' end ) as '英文',
( case when chinese>= 85 then '优秀' when chinese >= 60 then '及格' else '不及格' end ) as '语文'
from score;