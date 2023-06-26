-- 分组查询
--  根据性别分组 , 统计男性员工 和 女性员工的数量
select gender,count(*) from table emp group by gender; 
--  根据性别分组 , 统计男性员工 和 女性员工的平均年龄
select gender, avg(*) from emp group by gender;
--  查询年龄小于45的员工 , 并根据工作地址分组 , 获取员工数量大于等于3的工作地址
-- select * from emp where age<45 group by workaddress having count(*)>= 3;
select workaddress, count(*) from emp where age<45 group by workaddress having count(*)>= 3;
select workaddress,count(*) from emp where age<45 group by workaddress;
--  查询年龄小于45的员工 , 并根据工作地址分组 , 获取员工数量大于等于3的工作地址

--排序查询
--根据年龄对公司的员工进行升序排序
-- select * from emp order by age asc;
select * from emp order by age desc;
--根据入职时间, 对员工进行降序排序
select * from emp order by entrydate desc;
--根据年龄对公司的员工进行升序排序 , 年龄相同 , 再按照入职时间进行降序排序
select * from emp order by age asc,entrydate desc;

--分页查询
--查询第1页员工数量，每页展示10条记录
select * from emp limit 0,10;
--查询第2页员工数据，每页展示10条记录 ----------> (页码-1)*页展示记录数
select * from emp limit 10, 10;

--DQL练习题
-- 查询年龄为20,21,22,23岁的员工信息。
select * from emp where age in (20,21,22,23) and gender='女性';
-- 查询性别为 男 ，并且年龄在 20-40 岁(含)以内的姓名为三个字的员工。
select * from emp  where gender='男' and age between 20 and 40  and name LIKE '___';
-- 统计员工表中, 年龄小于60岁的 , 男性员工和女性员工的人数。
select gender,count(*) from emp where age<60 group by gender;
-- 查询所有年龄小于等于35岁员工的姓名和年龄，并对查询结果按年龄升序排序，如果年龄相同按入职时间降序排序。
select name,age from emp where age <= 35 order by age asc,entrydate desc;
-- 查询性别为男，且年龄在20-40岁（含）以内的前5个员工信息，对查询的结果按照年龄升序排序，年龄相同按入职时间升序排序
select * from emp where age between 20 and 40 order by age asc, entrydate desc  limit 5;

--小结
-- 查询年龄大于15的员工姓名、年龄，并根据年龄进行升序排序。
select name,age from emp where age>15 order by age;
select name,age from emp e where e.age>15 order by age;