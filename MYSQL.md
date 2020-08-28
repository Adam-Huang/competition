# References





# 基础

## 安装

```shell
rpm -qa | grep -i mysql # 先找到之前的安装软件
rpm -o mysql-libs-xxxx --nodops # 卸载
# 将windows下载的上传到linux上
# 解压
# 安装第三方的依赖库 
```

## [P2](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=2>) **远程访问授权** Linux 防火墙查看与关闭

```shell
service iptables status
service iptables stop
```



**`SQLyog`**

> [MySQL最佳客户端工具 -- SQLyog 13.1.1.0 安装与注册](https://www.cnblogs.com/tangbohu2008/p/11017235.html)

`error` 错误号码1130, Host is not allowed to connect to this Mysql server.

> ```mysql
> mysql> select host, user from user where user='root'; # 该表法
> mysql> update user set host = '%' where user = 'root';
> mysql> select host, user from user where user='root';
> mysql> FLUSH PRIVILEGES;
> ```
>
> 但是本地就登录不了了，参考解决[未成功](<https://www.cnblogs.com/chunguang-yao/p/10666403.html>)

## [P3 - 索引](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=3>)

索引就是数据结构，目的是高效的获取数据。

[P4 - 索引的优势与劣势](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=4>)

[P5 - 索引的结构](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=5>)

索引是MySQL的存储引擎层中实现的，MySQL目前提供了以下4种索引：

B树、HASH索引、R-Tree索引（空间索引）、Full-Text（全文索引）。

[P6 - B 树](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=6>)

[P7- B+树](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=7>)

[P8-索引的分类](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=8>)

- 单值索引： 一个索引只包含单个列，一个表可以有多个单列索引
- 唯一索引： 索引列的值必须唯一，但允许有空值 
- 复合索引：一个索引包含多个列

### [P9 - 索引的语法](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=9>)

```mysql
mysql> CREATE DATABASE demo DEFAULT CHARSET=utf8mb4; # 创建数据库
mysql> SHOW DATABASES; # 查看数据库

mysql> use demo;

CREATE TABLE `city`(
`city_id` INT(11) NOT NULL AUTO_INCREMENT,
`city_name` VARCHAR(50) NOT NULL,
`country_id` INT(11) NOT NULL,
PRIMARY KEY (`city_id`)
)ENGINE=INNOBASE DEFAULT CHARSET=utf8; # 创建一个表

CREATE TABLE `country`(
`country_id` INT(11) NOT NULL AUTO_INCREMENT,
`country_name` VARCHAR(50) NOT NULL,
PRIMARY KEY (`country_id`)
)ENGINE=INNOBASE DEFAULT CHARSET=utf8; # 再创建一个表

mysql> desc city; # 查看表结构 和 show columns from city; 一样
+------------+-------------+------+-----+---------+----------------+
| Field      | Type        | Null | Key | Default | Extra          |
+------------+-------------+------+-----+---------+----------------+
| city_id    | int(11)     | NO   | PRI | NULL    | auto_increment |
| city_name  | varchar(50) | NO   |     | NULL    |                |
| country_id | int(11)     | NO   |     | NULL    |                |
+------------+-------------+------+-----+---------+----------------+
3 rows in set (0.00 sec)

# 插入数据
INSERT INTO `city` (`city_id`,`city_name`,`country_id`) VALUE(1,'西安',1);
INSERT INTO `city` (`city_id`,`city_name`,`country_id`) VALUE(2,'NewYork',2);
INSERT INTO `city` (`city_id`,`city_name`,`country_id`) VALUE(3,'上海',1);
INSERT INTO `city` (`city_id`,`city_name`,`country_id`) VALUE(4,'北京',1);

INSERT INTO `country` (`country_id`,`country_name`) VALUE(1,'China');
INSERT INTO `country` (`country_id`,`country_name`) VALUE(2,'America');
INSERT INTO `country` (`country_id`,`country_name`) VALUE(3,'Japan');
INSERT INTO `country` (`country_id`,`country_name`) VALUE(4,'UK');
```

**创建索引**

```shell
# 语法 CREATE [索引类型: UNIQUE（唯一索引）|FULLTEXT（全文索引）|SPATIAL] INDEX index_name ON 对哪些表的哪些字段进行索引
```

`city_id`已经是索引了，mysql里默认为主键创建主键索引

```mysql
mysql> create index idx_city_name on city(city_name); 
mysql> show index from city\G; # 查看索引\G可不加
*************************** 1. row ***************************
        Table: city
   Non_unique: 0
     Key_name: PRIMARY
 Seq_in_index: 1
  Column_name: city_id
    Collation: A
  Cardinality: 0
     Sub_part: NULL
       Packed: NULL
         Null: 
   Index_type: BTREE
      Comment: 
Index_comment: 
      Visible: YES
   Expression: NULL
*************************** 2. row ***************************
        Table: city
   Non_unique: 1
     Key_name: idx_city_name
 Seq_in_index: 1
  Column_name: city_name
    Collation: A
  Cardinality: 4
     Sub_part: NULL
       Packed: NULL
         Null: 
   Index_type: BTREE # 默认都是BTREE
      Comment: 
Index_comment: 
      Visible: YES
   Expression: NULL
2 rows in set (0.00 sec)

ERROR: 
No query specified
```

**删除索引**

```mysql
mysql> drop index idx_city_name on city;
```

**`ALTER`** 创建和修改索引

```mysql
alter table tb_name add primary key(column_list);
# 添加一个主键，意味着索引值必须是位置的，且不能为NULL
alter table tb_name add unique index_name(column_list);
# 创建索引值必须是唯一的 除NULL之外，NULL可能会出现很多次
alter table tb_name add index index_name(column_list);
# 添加普通索引，索引值可出现多次
alter table tb_name add fulltext index_name(column_list);
# 全文索引。

mysql> show index from city\G;
*************************** 1. row ***************************
        Table: city
   Non_unique: 0
     Key_name: PRIMARY
 Seq_in_index: 1
  Column_name: city_id
    Collation: A
  Cardinality: 0
     Sub_part: NULL
       Packed: NULL
         Null: 
   Index_type: BTREE
      Comment: 
Index_comment: 
      Visible: YES
   Expression: NULL
*************************** 2. row ***************************
        Table: city
   Non_unique: 0 # 这里变成0就是唯一了 -。-
     Key_name: idx_city_name
 Seq_in_index: 1
  Column_name: city_name
    Collation: A
  Cardinality: 4
     Sub_part: NULL
       Packed: NULL
         Null: 
   Index_type: BTREE
      Comment: 
Index_comment: 
      Visible: YES
   Expression: NULL
2 rows in set (0.00 sec)

ERROR: 
No query specified
```

[P10 - 索引的创建原则](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=10>)

针对什么样的表？查询次数多、数据量比较大、应当从where子句的条件种提取。

索引需要维护，不是越多越好。

```mysql
# 创建组合索引， 顾名思义就是指多级索引
create index <'id_name_emial_status'> on tb_seller(NAME, email, STATUS);
```

## [P11 - 视图](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=11>)

虚拟存在的表，就是一条`SELECT`语句，主要用来简化我们的查询操作。特点：简单、安全、数据独立。

[P12 - 创建与修改](<https://www.bilibili.com/video/BV1UQ4y1P7Xr?p=12>)

```mysql
create [or replace] [ALGORITHM = {undefied | merge | template}]
VIEW view_name [(column_list)]
AS select_statement
[WITH [CASCADED | LOCAL] CHECK OPTION] # 创建语法

mysql> select * from city c, country t where c.country_id = t.country_id; 
                       #  | -> 别名<- |
+---------+-----------+------------+------------+--------------+
| city_id | city_name | country_id | country_id | country_name |
+---------+-----------+------------+------------+--------------+
|       1 | 西安      |          1 |          1 | China        |
|       2 | NewYork   |          2 |          2 | America      |
|       3 | 上海      |          1 |          1 | China        |
|       4 | 北京      |          1 |          1 | China        |
+---------+-----------+------------+------------+--------------+
4 rows in set (0.00 sec)
# 这和单独展示有什么区别呢？以下是单独展示结果。
mysql> select * from city;
+---------+-----------+------------+
| city_id | city_name | country_id |
+---------+-----------+------------+
|       1 | 西安      |          1 |
|       2 | NewYork   |          2 |
|       3 | 上海      |          1 |
|       4 | 北京      |          1 |
+---------+-----------+------------+
4 rows in set (0.00 sec)

mysql> select * from country;
+------------+--------------+
| country_id | country_name |
+------------+--------------+
|          1 | China        |
|          2 | America      |
|          3 | Japan        |
|          4 | UK           |
+------------+--------------+
4 rows in set (0.00 sec)  #  就是关联展示了。

# 创建视图
mysql> create view view_city_country as select c.* , t.country_name from city c, country t where c.country_id = t.country_id;

mysql> select * from view_city_country; # 可以看到，视图就像一个虚拟的表。
+---------+-----------+------------+--------------+
| city_id | city_name | country_id | country_name |
+---------+-----------+------------+--------------+
|       1 | 西安      |          1 | China        |
|       2 | NewYork   |          2 | America      |
|       3 | 上海      |          1 | China        |
|       4 | 北京      |          1 | China        |
+---------+-----------+------------+--------------+
4 rows in set (0.00 sec) 

mysql> update view_city_country set city_name = '西安市' where city_id = 1; # 还可以直接修改
```

修改

```mysql
ALTER [ALGORITHM = {undefied | merge | template}]
VIEW view_name [(column_list)]
AS select_statement
[WITH [CASCADED | LOCAL] CHECK OPTION]
```

