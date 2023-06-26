create table emp(
    id int comment "编号",
    workno varchar(10) comment "工号",
    name varchar(10) comment '姓名', 
    gender varchar(1) comment '性别',
    age tinyint unsigned comment '年龄',
    idcard char(18) comment '身份证号',
    workaddress varchar(50) comment '工作地址',
    entrydate date comment '入职时间'
) comment '员工表';
-- 查询年龄等于88的员工
select * from emp where age = 88; 
-- 查询年龄小于 20 的员工信息
select * from  emp where age < 20;
-- 查询年龄小于等于 20 的员工信息
select * from  emp where age <= 20;
-- 查询没有身份证号的员工信息
select * from emp where idcard is null;
-- 查询有身份证号的员工信息
select * from emp where idcard is not null;
-- 查询年龄不等于 88 的员工信息
select * from emp where age != 88;
select * from emp where age <> 88;
-- 查询年龄在15岁(包含) 到 20岁(包含)之间的员工信息
select * from emp where age between 15 and 20;
select * from emp where age >= 15 && age <= 20;
select * from emp where age >= 15 and age <= 20;
-- 查询性别为 女 且年龄小于 25岁的员工信息
select * from emp where gender='女' and age < 25;
-- 查询年龄等于18 或 20 或 40 的员工信息
select * from emp where age = 18 or age = 20 or age = 40 ;
select * from emp where age in  (18, 20, 40) ;
-- 查询姓名为两个字的员工信息 _ %
select * from emp where name LIKE '__';
-- 查询身份证号最后一位是X的员工信息
select * from  emp where idcard LIKE '%X';