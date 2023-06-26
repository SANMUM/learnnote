-- 存储过程基本语法
-- 创建
create procedure p1()
begin
    select count(*) from student;
end;

-- 调用
call p1();

-- 查看
select * from information_schema.ROUTINES WHERE ROUTINE_SCHEMA = 'itheima';
show create procedure p1;
-- 删除
drop procedure if exists p1;

-- 变量：系统变量
-- 查看系统变量
show session variables ;
show session variables like 'auto%';
show global variables like 'auto%';

select @@autocommit;
select @@session.autocommit;
select @@global.autocommit;

-- 设置系统变量
set session autocommit = 0;
insert into course(id,name) VALUES (5,'oracle');
commit ;
set session autocommit = 1;

-- 用户变量
set @myname = 'itcast';
set @myage := 10;
set @mygender := '男',@myhobby := 'java';

select @mycolor := 'red';

select count(*) into @mycount from tb_user;
-- 使用
select @myname,@myage,@mygender,@myhobby;
select @mycolor,@mycount;

-- 局部变量
# create procedure p2()
# begin
#     declare stu_count int default 0;
#     select count(*) into stu_count from student;
#     select stu_count;
# end;
#
# call p2();

# if
# 根据定义的分数score变量，判定当前分数对应的分数等级。
# score >= 85分，等级为优秀。
# score >= 60分 且 score < 85分，等级为及格。
# score < 60分，等级为不及格。

create procedure p3()
begin
    declare score int default 58;
    declare result varchar(10);
    if score >= 85 then
    set result := '优秀';
    elseif score >= 60 then
    set result := '及格';
    else
    set result := '不及格';
    end if;
    select result;
end;
call p3();

-- in/out/inout参数
-- 根据传入（in）的分数score变量，判定当前分数对应的分数等级,并返回(out)。
-- score >= 85分，等级为优秀。
-- score >= 60分 且 score < 85分，等级为及格。
-- score < 60分，等级为不及格。

create procedure p4(in score int,out result varchar(10))
begin
    if score >= 85 then
        set result := '优秀';
    elseif score >= 60 then
        set result := '及格';
    else
        set result := '不及格';
    end if;
end;
call p4(68,@result);
select @result;

-- 将传入的200分制的分数，进行换算，换成百分制，然后返回分数 ----> inout
create procedure p5(inout score double)
begin
    set score := score * 0.5;
end;

set @score = 78;
call p5(@score);
select@score;


-- case
-- 根据传入的月份，判定月份所属的季节（要求采用case结构）。
-- 1-3月份，为第一季度
-- 4-6月份，为第二季度
-- 7-9月份，为第三季度
-- 10-12月份，为第四季度
create procedure p6(in month int)
begin
declare result varchar(10);
case
when month >= 1 and month <= 3 then
set result := '第一季度';
when month >= 4 and month <= 6 then
set result := '第二季度';
when month >= 7 and month <= 9 then
set result := '第三季度';
when month >= 10 and month <= 12 then
set result := '第四季度';
else
set result := '非法参数';
end case ;
select concat('您输入的月份为: ',month, ', 所属的季度为: ',result);
end;

call p6(16);

-- while
-- 计算从1累加到n的值，n为传入的参数值。
-- A. 定义局部变量, 记录累加之后的值;
-- B. 每循环一次, 就会对n进行减1 , 如果n减到0, 则退出循环
create procedure p7(in n int)
begin
    declare total int default 0;
    while n>0 do
        set total := total + n;
        set n := n - 1;
    end while;
    select total;
end;
call p7(100);

-- repeat
-- 计算从1累加到n的值，n为传入的参数值。
-- A. 定义局部变量, 记录累加之后的值;
-- B. 每循环一次, 就会对n进行减1 , 如果n减到0, 则退出循环
create procedure p8(in n int)
begin
    declare total int default 0;
    repeat
        set total := total + n;
        set n := n - 1;
        until n <= 0
    end repeat;
    select total;
end;
call p8(10);
call p8(100);

-- loop
-- 计算从1累加到n的值，n为传入的参数值。
-- A. 定义局部变量, 记录累加之后的值;
-- B. 每循环一次, 就会对n进行减1 , 如果n减到0, 则退出循环 ---> leave xx;
create procedure p9(in n int)
begin
    declare total int default 0;
    sum:loop
        if n<= 0 then
            leave sum;
        end if;
        set total := total + n;
        set  n:= n-1;
    end loop sum;
    select  total;
end;

call p9(100)


-- 计算从1到n之间的偶数累加的值，n为传入的参数值。
-- A. 定义局部变量, 记录累加之后的值;
-- B. 每循环一次, 就会对n进行-1 , 如果n减到0, 则退出循环 ----> leave xx
-- C. 如果当次累加的数据是奇数, 则直接进入下一次循环. --------> iterate xx

create procedure p10(in n int)
begin
    declare total int default 0;
    sum:loop
        if n<= 0 then
            leave sum;
        end if;

        if n%2 = 1 then
            set  n:= n-1;
            iterate sum;
        end if;
        set total := total + n;
        set  n:= n-1;
    end loop sum;
    select  total;
end;

call p10(100);

-- 游标
-- 根据传入的参数uage，来查询用户表tb_user中，所有的用户年龄小于等于uage的用户姓名
-- （name）和专业（profession），并将用户的姓名和专业插入到所创建的一张新表
-- (id,name,profession)中。

-- 逻辑
-- A. 声明游标, 存储查询结果集
-- B. 准备: 创建表结构
-- C. 开启游标
-- D. 获取游标中的记录
-- E. 插入数据到新表中
-- F. 关闭游标

create procedure p11(in uage int)
begin
    declare uname varchar(100);
    declare upro varchar(100);
    declare u_cursor cursor for select name,profession from tb_user where age <= uage;
    declare exit handler for SQLSTATE '02000' close u_cursor;

    drop table if exists tb_user_pro;
    create table if not exists tb_user_pro(
        id int primary key auto_increment,
        name varchar(100),
        profession varchar(100)
    );
    open u_cursor;
    while true do
        fetch u_cursor into uname,upro;
        insert into tb_user_pro values (null,uname,upro);
    end while;
    close u_cursor;
end;

call p11(40)


create procedure p12(in uage int)
begin
    declare uname varchar(100);
    declare upro varchar(100);
    declare u_cursor cursor for select name,profession from tb_user where age <= uage;
    declare exit handler for  not found close u_cursor;

    drop table if exists tb_user_pro;
    create table if not exists tb_user_pro(
        id int primary key auto_increment,
        name varchar(100),
        profession varchar(100)
    );
    open u_cursor;
    while true do
        fetch u_cursor into uname,upro;
        insert into tb_user_pro values (null,uname,upro);
    end while;
    close u_cursor;
end;

call p12(30)


-- 存储函数
-- 从1到n的值累加
create function fun1(n int)
    returns int deterministic
begin
    declare total int default 0;
    while n>0 do
        set total := total + n;
        set n := n - 1;
    end while;

    return total;
end;
select fun1(100);


-- 触发器
-- 通过触发器记录 tb_user 表的数据变更日志，将变更日志插入到日志表user_logs中, 包含增加, 修改 , 删除 ;
-- 准备工作 : 日志表 user_logs
create table user_logs(
    id int(11) not null auto_increment,
    operation varchar(20) not null comment '操作类型, insert/update/delete',
    operate_time datetime not null comment '操作时间',
    operate_id int(11) not null comment '操作的ID',
    operate_params varchar(500) comment '操作参数',
    primary key(`id`)
)engine=innodb default charset=utf8;

-- 插入数据触发器
create trigger tb_user_insert_trigger
    after insert on tb_user for each row
    begin
        insert into user_logs(id, operation, operate_time, operate_id, operate_params) VALUES
    (null, 'insert', now(), new.id, concat('插入的数据内容为:
id=',new.id,',name=',new.name, ', phone=', NEW.phone, ', email=', NEW.email, ',
profession=', NEW.profession));
    end;

-- 查看
show triggers ;
-- 删除触发器
drop trigger tb_user_insert_trigger;

-- 插入数据到tb_user
insert into tb_user(id, name, phone, email, profession, age, gender, status,
createtime) VALUES (26,'三皇子','18809091212','erhuangzi@163.com','软件工
程',23,'1','1',now());

-- 修改触发器
create trigger tb_user_update_trigger
    after update on tb_user for each row
begin
    insert into user_logs(id, operation, operate_time, operate_id, operate_params)
    VALUES
    (null, 'update', now(), new.id,
    concat('更新之前的数据: id=',old.id,',name=',old.name, ', phone=',
    old.phone, ', email=', old.email, ', profession=', old.profession,
    ' | 更新之后的数据: id=',new.id,',name=',new.name, ', phone=',
    NEW.phone, ', email=', NEW.email, ', profession=', NEW.profession));
end;

-- 查看
show triggers ;
-- 更新
update tb_user set profession = '会计' where id = 23;
update tb_user set profession = '会计' where id <= 5;

-- 删除触发器
create trigger tb_user_delete_trigger
    after delete on tb_user for each row
begin
    insert into user_logs(id, operation, operate_time, operate_id, operate_params)
    VALUES
    (null, 'delete', now(), old.id,
    concat('删除之前的数据: id=',old.id,',name=',old.name, ', phone=',
    old.phone, ', email=', old.email, ', profession=', old.profession));
end;

-- 查看
show triggers ;
delete from tb_user where id=26;