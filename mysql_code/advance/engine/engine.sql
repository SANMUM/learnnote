-- 查询建表语句
-- select * from course; 默认存储引擎： InnoDB
show create table course;

-- 查询当前数据库支持的存储引擎
show engines;

-- 创建表my_myisam，并指定MyISAM存储引擎
create table  my_myiasm(
    id int,
    name varchar(10)
) engine = MyISAM;