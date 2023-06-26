drop table if exists account;
create table account(
id int primary key AUTO_INCREMENT comment 'ID',
name varchar(10) comment '姓名',
money double(10,2) comment '余额'
) comment '账户表';
insert into account(name, money) VALUES ('张三',2000), ('李四',2000);


-- 恢复数据
select @@autocommit;
set @@autocommit = 0;
update account set money = 2000 where name = '张三' or name = '李四'；

-- 转账操作（张三向李四转钱）
-- 1. 查询张三的账余额
select * from account where name = '张三';
-- 2. 将张三的余额 -1000
update account set money = money - 1000 where name = '张三';
-- 3. 将李四的余额+1000
update account select money = money + 1000 where name = '李四';

-- 提交
commit;

-- 回滚
rollback;


-- 方式二
set @@autocommit = 1;
-- 转账操作（张三向李四转钱）
start transaction;
-- 1. 查询张三的账余额
select * from account where name = '张三';
-- 2. 将张三的余额 -1000
update account set money = money - 1000 where name = '张三';
-- 3. 将李四的余额+1000
update account select money = money + 1000 where name = '李四';

-- 提交
commit;

-- 回滚
rollback;