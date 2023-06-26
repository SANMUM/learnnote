-- 创建dept表，并插入数据
create table dept(
id int auto_increment comment 'ID' primary key,
name varchar(50) not null comment '部门名称'
)comment '部门表';

-- 创建薪资等级表
create table salgrade(
grade int,
losal int,
hisal int
) comment '薪资等级表';

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

insert into salgrade values (1,0,3000);
insert into salgrade values (2,3001,5000);
insert into salgrade values (3,5001,8000);
insert into salgrade values (4,8001,10000);
insert into salgrade values (5,10001,15000);
insert into salgrade values (6,15001,20000);
insert into salgrade values (7,20001,25000);
insert into salgrade values (8,25001,30000);
-- 根据需求，完成SQL语句的编写
-- 1.  查询员工的姓名、年龄、职位、部门信息 （隐式内连接）

select e.name, e.age, e.job, d.name from emp e,dept d where e.dept_id = d.id

-- 2. 查询年龄小于30岁的员工的姓名，年龄，职位，部门信息（显示内连接）
select e.name, e.age, e.job, d.name  from emp e join dept d on e.dept_id = d.id  where e.age < 30;

-- 3. 查询拥有员工的部门ID，部门名称；
select distinct  d.id, d.name from emp e,dept d where e.dept_id = d.id;

-- 4. 查询所有年龄大于40岁的员工, 及其归属的部门名称; 如果员工没有分配部门, 也需要展示出来(外连接)
select e.*,d.name from emp e left join dept d on e.dept_id = d.id where e.age> 40;

-- 5. 查询所有员工的工资等级
-- 表emp,salgrade
-- 连接条件： emp.salary >= salgrade.losal and emp.salary <= salgrade.hisal

select e.*,s.grade from emp e,salgrade s where e.salary >= s.losal and e.salary<= s.hisal


-- 6. 查询研发部所有员工的信息及工资等级
-- 表emp,salgrade,dept
-- 连接条件：emp.salary between salgrade.losal and salgrade.hisal,emp.dept_id = dept.id
-- 查询条件：dept.name = '研发部'

select e.*,s.grade from emp e,dept d, salgrade s where (e.dept_id = d.id) and (e.salary between s.losal and s.hisal) and e.name = '研发部';

-- 7. 查询研发部的平均工资
-- 表：emp,dept
-- 连接条件： emp.dept_id = dept.id

select avg(e.salary) from emp e,dept d where e.dept_id and d.id and d.name = '研发部';

-- 8. 查询工资比灭绝高的员工信息
-- a. 查询灭绝的薪资
select salary from emp where name = '灭绝';
-- b. 查询比她工资高的员工数据；
select * from emp where salary> (select salary from emp where name = '灭绝');

-- 9. 查询比平均薪资高的员工信息
-- a. 查询员工的平均薪资
select avg(salary) from emp;
-- b. 查询比平均工资高的员工信息
select * from emp where salary > (select avg(salary) from emp);

-- 10. 查询低于本部门平均工资的员工信息
-- a. 查询指定部门平均薪资： 1；
select avg(e1.salary) from emp e1 where e1.dept_id = 1;
select avg(e1.salary) from emp e1 where e1.dept_id = 2;
-- b. 查询低于本部门平均工资的员工信息
select *, (select avg(e1.salary) from emp e1 where e1.dept_id =e2.dept_id) '平均薪资' from emp e2 where e2.salary<(select avg(e1.salary) from emp e1 where e1.dept_id =e2.dept_id)


-- 11. 查询所有部门信息，并统计部门的员工人数
select d.id, d.name ,(select count(*) from emp e where e.dept_id= d.id) '人数' from dept d;
select count(*) from emp where dept_id = 1;

-- 12. 查询所有学生的选课情况，展现出学生名称,学号，课程名称
-- 连接条件 student.id =  student_course.studentid, course.id = student_course.courseid

select s.name,s.no,c.name from student s,student_course sc,course c where s.id = sc.studentid and c.id = sc.courseid;