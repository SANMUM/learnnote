-- 创建视图
create or replace view stu_v_1 as select id,name from student where id <= 10;
-- select id,name from student where id <= 10;

-- 查询视图
show create view stu_v_1;
select * from  stu_v_1;

-- 修改视图
create or replace view stu_v_1 as select id,name,no from student where id <= 10;
alter view stu_v_1 as select id,name from student where id<=10;

-- 删除视图
drop view if exists  stu_v_1;

-- ---------------
create or replace view stu_v_1 as select id,name from student where id <= 20 with cascaded check option ;

select * from stu_v_1;
insert into stu_v_1 values (6,'Tom');
-- insert into stu_v_1 values (30,'Tom2');




-- ----------------
-- 检测选项 cascade
create or replace view stu_v_1 as select id,name from student where id <= 20;

insert into stu_v_1 values(5,'Tom');
insert into stu_v_1 values (25,'Tom2');

create or replace view stu_v_2 as select id,name from stu_v_1 where id >= 10 with cascaded check option ;
-- failed
insert into stu_v_2 values(7,'Tom');
insert into stu_v_2 values(26,'Tom');
-- succeed
insert into stu_v_2 values(15,'Tom');

create or replace view stu_v_3 as select id,name from stu_v_2 where id <= 15;

-- succeed
insert into stu_v_3 values(11,'Tom');

insert into stu_v_3 values(17,'Tom');
-- failed
insert into stu_v_3 values(28,'Tom');

-- 检查选项local


create or replace view stu_v_4 as select id,name from student where id <= 15 with local check option;

insert into stu_v_4 values(5,'Tom');
insert into stu_v_4 values (16,'Tom2');

create or replace view stu_v_5 as select id,name from stu_v_4 where id >= 10 with local check option ;
-- succeed
insert into stu_v_5 values(13,'Tom');
insert into stu_v_5 values(17,'Tom');
-- failed
insert into stu_v_5 values(18,'Tom');

create or replace view stu_v_6 as select id,name from stu_v_5 where id < 20;
-- succeed
insert into stu_v_6 values(14,'Tom');


-- 创建视图，使用聚合函数
create view stu_v_count as select count(*) from student;
insert into stu_v_count values(10);

-- 案例
-- 1. 为了保证数据库表的安全性，开发人员在操作tb_user表时，只能看到的用户的基本字段，屏蔽手机号和邮箱两个字段。
create view tb_user_view as select id,name,profession,age,gender,status,createtime from tb_user;
select * from tb_user_view;

--  查询每个学生所选修的课程（三张表联查），这个功能在很多的业务中都有使用到，为了简化操作，定义一个视图。
select s.name,s.no,c.name from student s,student_course sc,course c where s.id = sc.studentid and  sc.courseid= c.id;
create view  tb_stu_course_view as select s.name student_name,s.no student_no,c.name course_name from student s,student_course sc,course c where s.id = sc.studentid and  sc.courseid= c.id;

select * from tb_stu_course_view;