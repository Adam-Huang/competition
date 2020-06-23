# SQL

Structured Query Language

> 虽然 SQL 是一门 ANSI（American National Standards Institute 美国国家标准化组织）标准的计算机语言，但是仍然存在着多种不同版本的 SQL 语言。
>
> 然而，为了与 ANSI 标准相兼容，它们必须以相似的方式共同地来支持一些主要的命令（比如 SELECT、UPDATE、DELETE、INSERT、WHERE 等等）。

## 在您的网站中使用 SQL

> 要创建一个显示数据库中数据的网站，您需要：
>
> - RDBMS 数据库程序（比如 MS Access、SQL Server、MySQL）
> - 使用服务器端脚本语言，比如 PHP 或 ASP
> - 使用 SQL 来获取您想要的数据
> - 使用 HTML / CSS

**RDBMS** Relational Database Management System





# MySQL

## MySQL 安装

检测系统是否自带安装 MySQL: 

```shell
rpm -qa | grep mysql
```

如果你系统有安装，那可以选择进行卸载:

```shell
rpm -e mysql　　# 普通删除模式
rpm -e --nodeps mysql　　# 强力删除模式，如果使用上面命令删除时，提示有依赖的其它文件，则用该命令可以对其进行强力删除
```

`error1:ERROR 1045 (28000): Access denied for user 'root'@'localhost' (using password: NO/YES)`

> [解决mysql：ERROR 1045 (28000): Access denied for user 'root'@'localhost' (using password: NO/YES)](https://www.cnblogs.com/winton-nfs/p/12956811.html)
>
> ```shell
> mysql -uroot -p # 用这个就可以了
> ```

## MySQL 管理
```shell
ps -ef | grep mysqld # 检查MySQL服务器是否启动

root@host# cd /usr/bin
./mysqld_safe &      # 启动mysql服务器:

root@host# cd /usr/bin
./mysqladmin -u root -p shutdown
Enter password: ****** # 关闭目前运行的 MySQL 服务器
```

### MySQL 用户设置

没有`Password`这个`field list`

```shell
root@host# mysql -u root -p
Enter password:*******
mysql> use mysql;
mysql> INSERT INTO user()
mysql> FLUSH PRIVILEGES; # 创建完毕

mysql> SELECT host, user, password FROM user WHERE user = 'guest'; # 查看添加结果
```

另外一种添加用户的方法为通过SQL的 GRANT 命令

```shell
mysql> GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP
```



# PostgreSQL





# SQLite





# MongoDB





# Redis



# Memcached











