-- curdate
select curdate();
-- curtime
select curtime();
-- now
select now();

-- YEAR, MONTH, DAY
select YEAR(now());
select MONTH(now());
select DAY(now()); 

-- date_add

select date_add(now(),INTERVAL 70 MONTH);

-- datediff
select datediff('2021-12-01','2021-11-01');

-- 查询所有员工的入职天数，并且根据入职天数倒序排序

select name,datediff(curdate(), entrydate) as 'entrydays' from emp order by entrydays desc; 
