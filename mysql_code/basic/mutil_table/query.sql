-- 创建dept表，并插入数据
create table dept(
id int auto_increment comment 'ID' primary key,
name varchar(50) not null comment '部门名称'
)comment '部门表';
INSERT INTO dept (id, name) VALUES (1, '研发部'), (2, '市场部'),(3, '财务部'), (4,
'销售部'), (5, '总经办'), (6, '人事部');
-- 创建emp表，并插入数据
create table emp(
id int auto_increment comment 'ID' primary key,
name varchar(50) not null comment '姓名',
age int comment '年龄',
job varchar(20) comment '职位',
salary int comment '薪资',
entrydate date comment '入职时间',
managerid int comment '直属领导ID',
dept_id int comment '部门ID'
)comment '员工表';
-- 添加外键
alter table emp add constraint fk_emp_dept_id foreign key (dept_id) references
dept(id);
INSERT INTO emp (id, name, age, job,salary, entrydate, managerid, dept_id)
VALUES
(1, '金庸', 66, '总裁',20000, '2000-01-01', null,5),
(2, '张无忌', 20, '项目经理',12500, '2005-12-05', 1,1),
(3, '杨逍', 33, '开发', 8400,'2000-11-03', 2,1),
(4, '韦一笑', 48, '开发',11000, '2002-02-05', 2,1),
(5, '常遇春', 43, '开发',10500, '2004-09-07', 3,1),
(6, '小昭', 19, '程序员鼓励师',6600, '2004-10-12', 2,1),
(7, '灭绝', 60, '财务总监',8500, '2002-09-12', 1,3),
(8, '周芷若', 19, '会计',48000, '2006-06-02', 7,3),
(9, '丁敏君', 23, '出纳',5250, '2009-05-13', 7,3),
(10, '赵敏', 20, '市场部总监',12500, '2004-10-12', 1,2),
(11, '鹿杖客', 56, '职员',3750, '2006-10-03', 10,2),
(12, '鹤笔翁', 19, '职员',3750, '2007-05-09', 10,2),
(13, '方东白', 19, '职员',5500, '2009-02-12', 10,2),
(14, '张三丰', 88, '销售总监',14000, '2004-10-12', 1,4),
(15, '俞莲舟', 38, '销售',4600, '2004-10-12', 14,4),
(16, '宋远桥', 40, '销售',4600, '2004-10-12', 14,4),
(17, '陈友谅', 42, null,2000, '2011-10-12', 1,null);


--- 多表查询

select * from emp,dept where emp.dept_id = dept.id;

--- 查询每一个员工的姓名 , 及关联的部门的名称 (隐式内连接实现)
-- 表结构: emp , dept
-- 连接条件: emp.dept_id = dept.id
select emp.name, dept.name from emp,dept where emp.dept_id = dept.id

--- 查询每一个员工的姓名 , 及关联的部门的名称 (显式内连接实现)
-- 表结构: emp , dept
-- 连接条件: emp.dept_id = dept.id

select * from emp e inner join dept d on e.dept_id = d.id;


---查询emp表的所有数据, 和对应的部门信息
-- 由于需求中提到，要查询emp的所有数据，所以是不能内连接查询的，需要考虑使用外连接查询。
-- 表结构: emp, dept
-- 连接条件: emp.dept_id = dept.id
select e.* ,d.name from emp e left outer join dept d on e.dept_id = d.id;

-- 查询dept表的所有数据, 和对应的员工信息(右外连接)
select d.*,e.* from emp e right outer join dept d on e.dept_id = d.id;


-- 子连接查询
-- 查询员工 及其 所属领导的名字
-- 表结构: emp
select a.name, b.name from emp a,emp b where a.managerid = b.managerid

-- 查询所有员工 emp 及其领导的名字 emp , 如果员工没有领导, 也需要查询出来
-- 表结构: emp a , emp b
select a.name '员工', b.name '领导' from emp a left join emp b on a.managerid = b.id;

-- 将薪资低于 5000 的员工 , 和 年龄大于 50 岁的员工全部查询出来.
select * from emp where salary < 5000
union all
select * from emp where age > 50;

-- 去重
select * from emp where salary < 5000;

union 
select * from emp where age > 50


-- 标量子查询
-- 查询 "销售部" 的所有员工信息
-- a. 查询销售部的部门id
select id from dept where name = '销售部';
-- b. 根据销售部门ID，查询员工信息
select * from emp where dept_id = 4;
select * from emp where dept_id = (select id from dept where name = '销售部');

-- c查询在房东白入职之后的员工信息
-- a. 查询房东白入职日期
select entrydate from emp where name = '房东白';
-- b. 查询指定日期之后入职的员工信息
select * from emp entrydate > '2009-02-12';
select * from emp entrydate > (select entrydate from emp where name = '房东白');

-- 列子查询

-- 查询 "销售部" 和 "市场部" 的所有员工信息

-- a. 查询销售部和市场部的部门ID
select * from dept where name = '销售部' or name = '市场部';
-- b. 查询员工信息，根据部门ID
select * from emp where dept_id in (select * from dept where name = '销售部' or name = '市场部');
--查询比 财务部 所有人工资都高的员工信息
-- a. 查询所有财务部员工工资
select id from dept where name = '财务';
select salary from emp where dept_id = (select id from dept where name = '财务');
-- b. 比财务部所有人工资都高的员工信息
select * from salary > all (select salary from emp where dept_id = (select id from dept where name = '财务'));

-- 查询比研发部其中任意一人工资高的员工信息
-- a. 查询研发部所有人工资
select salary from emp where dept_id = (select id from dept where name = '研发部');
-- b. 比研发部其中任意一人工资都高的员工信息
salary * from emp where salary > some (select salary from emp where dept_id = (select id from dept where name = '研发部'));

-- 行子查询
-- 1. 查询与张无忌的薪资及直属领导相同的员工信息
-- a. 查询张无忌的薪资及直属领导
select salary,managerid from emp where name = '张无忌';
-- b. 查询与张无忌的薪资及直属领导相同的员工信息
select * from emp from (salary,managerid) =  (select salary,managerid from emp where name = '张无忌');

-- 表子查询
-- 查询鹿杖客，宋远桥的职位和薪资都相同的员工信息
-- a. 查询鹿杖客，宋远桥的薪资和职位
select job,salary from emp where name = '鹿杖客' or name = '宋远桥';
-- b. 查询与鹿杖客，宋远桥的职位和薪资相同的员工信息
select * from emp where (job,salary) in (select job,salary from emp where name = '鹿杖客' or name = '宋远桥');


-- 查询入职日期是2006-01-01之后的员工信息
-- a. 入职日期是2006-01-01之后的员工信息
select * from emp where entrydate > '2006-01-01';
-- b. 查询这部分员工对应的部门信息
select * from (select * from emp where entrydate > '2006-01-01') e left join dept d on e.dept_id = d.id;