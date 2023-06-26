-- 查询数据库系统状态信息
SHOW GLOBAL STATUS LIKE 'Com_______';
select * from tb_user;

-- 查看慢查询日志是否开启
show variables like 'slow_query_log';
-- 开启慢查询日志
set global slow_query_log=ON;
-- 设置慢查询时间
set long_query_time=2;
-- 查看慢查询时间
select @@long_query_time;
show variables like 'slow_%';

-- 查看是否支持profile操作
select @@have_profiling;

-- 查看profiling是否开启
select @@profiling;

-- 开启 profiling
set profiling=1;
-- 查看最近操作的耗时
show profiles ;
-- 查询指定id的具体消耗详情
show profile for query 22;
-- 查看cpu的耗时情况
show profile CPU for query 22;

-- 查询
select * from tb_user where id=1;
explain select * from tb_user where id=1;

-- explain --1
select * from  student;
select * from course;
select * from  student_course;

select s.*,c.* from student s,course c,student_course sc where s.id = sc.studentid and c.id = sc.courseid;

explain select s.*,c.* from student s,course c,student_course sc where s.id = sc.studentid and c.id = sc.courseid;

-- explain --2
-- 查询了选修了MYSQL课程的学生；（子查询）
select id from course c where c.name='MySQL';
select studentid from student_course sc where sc.courseid = 3;
select * from student s where s.id in (1,2);

explain select * from student s where s.id in (select studentid from student_course sc where sc.courseid = (select id from course c where c.name='MySQL'));