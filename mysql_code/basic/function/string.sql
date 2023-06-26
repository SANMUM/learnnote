-- concat 
select concat('Hello',' MySQL');
-- lower
select lower('Hello');

-- upper
select upper('Hello');

--lpad
select lpad('01',5,'-');

--rpad
select rpad('01',5,'-');

--trim

select trim(' Hello MySQL ');

-- substring (起始位置为1)
select substring('Hello Mysql',1,5);


-- 1. 由于业务需求变更，企业员工的公号，统一为5位数，目前不足5位数的全部在前面补0.
update emp set workno = lpad(workno,5,'0');