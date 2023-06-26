-- 数值函数
-- ceil
select ceil(1.1);
-- floor
select floor(1.9);
-- mod
select mod(3,4);
-- rand
select rand();
-- round 四舍五入
select round(2.345,2);

-- 通过数据库函数，生成一个六位数的随机验证码
select lpad(round(rand()*1000000,0),6,'0');