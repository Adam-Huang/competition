# Practice

## [基础概念](<https://ly525.github.io/luban-h5/zh/getting-started/quick-start.html#%E5%9F%BA%E7%A1%80%E6%A6%82%E5%BF%B5>)

>- `Node.js`  服务器端的JavaScript 运行环境，你可以理解为和Python、Java等一样，它也是一门后端语言
>
>- `npm(or yarn)` Node.js 的包版本工具
>
>> 1. 类似于 Python 的pip，或 Centos 的yum，或 Ubuntu 的 apt-get
>> 2. 你在python 中安装requrest 库，通常是通过 `pip install requests` 来安装
>> 3. 在 Node.js 中，也是一样的，只是把 `pip` 换成 `pip` or `yarn` 即可： `npm install requests`  or `yarn add requests`
>
>- `nvm` ：Node.js 版本工具
>
>> 1. 使用 nvm可以快速安装 Node 的某个版本，比如通过 `node -v` 查看你的Node 当前版本。
>> 2. 假如这个版本(假设当前版本为 v.8.0.0)不符合要求，你可以通过 `nvm install v10.15.3` 来安装 `v10.15.3`

- 前端：Vue.js



- 后端：Strapi



- 存储：[Sqlite](#sqlite)

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
> mysql -uroot -p # 用这个就可以了 e:123*
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

> SQLite 是一个软件库，实现了自给自足的、无服务器的、零配置的、事务性的 SQL 数据库引擎。SQLite 是在世界上最广泛部署的 SQL 数据库引擎。SQLite 源代码不受版权限制。





# MongoDB





# Redis



# Memcached











