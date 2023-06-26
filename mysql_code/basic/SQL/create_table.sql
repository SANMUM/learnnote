create table emp(
    id int comment "编号",
    workno varchar(10) comment "工号",
    name varchar(10) comment '姓名', 
    gender varchar(1) comment '性别',
    age tinyint unsigned comment '年龄',
    idcard char(18) comment '身份证号',
    workaddress varchar(50) comment '工作地址',
    entrydate date comment '入职时间'
) comment '员工表';

--插入 
insert into employee(id,workno,name,gender,age,idcard,entrydate) values(1,'1','itheima','男', 10, '123456200506307896','2020-01-01');
-- insert into employee(id,workno,name,gender,age,idcard,entrydate) values(2,'2','itheima2','男', -1, '123456200506307896','2020-01-01');

insert into employee values(2,'2','张无忌','男', 18, '123456200506307898','205-01-01');
insert into employee values(3,'3','韦一笑','男', 38, '123456200506307899','2005-02-03'), values(4,'4','赵敏','女', 18, '123456200506307799','2005-03-03');

-- 更新
update employee set name = 'itheiman' where id = 1;
update employee set name = '小昭', gender = '女' where id = 1;

-- 删除
delete from employee where gender = '女';

insert into emp (id, workno, name, gender, age, idcard,workaddress, entrydate)
values
(1,'1','柳岩','女',20,'123456789012345678','北京','2000-01-01'),
(2,'2','张无忌','男',18,'123456789012345670', '北京','2005-09-01'),
(2,'3','韦一笑','男',38,'123456789712345670','上海', '2005-08-01'),
(4,'4','赵敏','女',18,'123456757123845670','北京','2009-12-01'),
(5,'5','小昭','女',16, '123456769012345678','上海','2007-07-01'),
(6,'6','杨道','男',28,'12345678931234567X','北京','2006-01-01'),
(7,'7', '范瑶','男',40,'123456789212345670','北京', '2005-05-01'),
(8,'8','黛绮丝','女',38,'123456157123645670','天津','2015-05-01'),
(9,'9','范凉凉','女',45,'123156789012345678','北京','2010-04-01'),
(10,'10','陈友谅','男',53, '123456789012345670','上海','2011-01-01'),
(11,'11', '张士诚','男',55,'123567897123465670','江苏' ,'2015-05-01'),
(12,'12','常遇春','男',32,'123446757152345670','北京','2004-02-01'),
(13,'13','张三丰','男',88, '123656789012345678','江苏','2020-11-01'),
(14,'14', '灭绝','女',65,'123456719012345670', '西安', '2019-05-01'),
(15,'15','胡青牛','男',70,'12345674971234567X','西安','2018-04-01'),
(16,'16','周芷若','女',18,null, '北京', '2012-06-01');