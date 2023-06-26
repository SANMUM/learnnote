-- select * from tb_sku where id = 1\G;
-- 最左前缀法则
select * from tb_user;

show index from tb_user;

select * from tb_user where profession='软件工程' and age=31 and status='0';
explain select * from tb_user where profession='软件工程' and age=31 and status='0';

select * from tb_user where profession='软件工程' and age=31;
-- 有效
explain select * from tb_user where profession='软件工程' and age=31;
-- 有效
explain select * from tb_user where profession='软件工程';
-- 失效，无最左列
explain select * from tb_user where age=31 and status='0';


-- 范围查询 尽量用>=
explain select * from tb_user where profession = '软件工程' and age > 30 and status= '0';
explain select * from tb_user where profession = '软件工程' and age >= 30 and status= '0';

-- 索引列运算
select * from tb_user where phone='17799990015';
explain select * from tb_user where phone='17799990015';
-- 失效
select * from tb_user where substring(phone,10,2)='15';

-- 字符串不加单引号
-- 失效
explain select * from tb_user where phone=17799990015;

explain select * from  tb_user where profession = '软件工程' and age = 31 and status='0';

-- 头部失效，尾部有效
select * from tb_user where profession like  '软件%';
-- 失效
select * from tb_user where profession like  '%软件';
select * from tb_user where profession like  '%软件%';

-- or连接的条件
-- 失效
explain  select * from  tb_user where  id = 10 or age = 23;
explain select * from tb_user where  phone='17799990015' or age = 23;

-- 数据分布影响
select * from tb_user;
explain select * from tb_user where  phone>='17799990000';

explain select * from tb_user where profession is null;
explain select * from tb_user where profession is not null;

-- SQL提示
show index from tb_user;
select * from tb_user where profession='软件工程';
-- 设置单列索引
create index idx_user_pro on tb_user(profession);
-- 选择用联合索引还是单列索引，默认联合索引
explain select * from tb_user where profession='软件工程';

-- use index
explain select * from tb_user use index(idx_user_pro) where profession='软件工程';

-- ignore index
explain select * from tb_user ignore index(idx_user_pro) where profession='软件工程';
explain select * from tb_user ignore index(index_user_pro_age_sta) where profession='软件工程';

-- force index
explain select * from tb_user force index(idx_user_pro) where profession='软件工程';


drop index idx_user_pro on tb_user;
-- 覆盖索引

select * from tb_user where profession = '软件工程' and age = 31 and status='0';
explain select id,profession,age,status from tb_user where profession = '软件工程' and age = 31 and status='0';

explain select id,profession,age,status,name from tb_user where profession = '软件工程' and age = 31 and status='0';

-- 前缀索引
select count(distinct email) from tb_user;
select count(distinct email)/count(*) from tb_user;
select count(distinct substring(email,1,4))/count(*) from tb_user;

show index from tb_user;

create index idx_email_5 on tb_user(email(5));

select * from tb_user where email = 'daqiao666@sina.com';
explain select * from tb_user where email = 'daqiao666@sina.com';