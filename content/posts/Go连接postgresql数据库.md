---
title: Go连接pgsql数据库
subtitle:
date: 2024-06-11T13:21:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords:
license:
comment: false
weight: 0
tags:
  - Go
categories:
  - 工程
hiddenFromHomePage: false
hiddenFromSearch: false
hiddenFromRss: false
hiddenFromRelated: false
summary:
resources:
  - name: featured-image
    src: featured-image.jpg
  - name: featured-image-preview
    src: featured-image-preview.jpg
toc: true
math: false
lightgallery: false
password:
message:
repost:
  enable: true
  url:

# See details front matter: https://fixit.lruihao.cn/documentation/content-management/introduction/#front-matter
---

<!--more-->

# Go语言连接postgresql数据库并实现基础操作教程

## 安装依赖包

```go
 go get -u github.com/lib/pq
参考资料:
https://godoc.org/github.com/lib/pq
https://www.runoob.com/postgresql/postgresql-tutorial.html
```

## 基础操作

### 连接数据库

```go
import (
	"database/sql"
	"fmt"
	_ "github.com/lib/pq"
)
func Database_connect() *sql.DB {
	localDB, err := sql.Open("postgres", "host=localhost port=5432 user=postgres password=123456 dbname=test sslmode=disable")
	if err != nil {
		fmt.Println("Wrong args.Connected failed.")
		panic(err)
	}
	err = localDB.Ping()	//ping一下验证是否连通
	if err != nil {
		fmt.Println("Wrong args.Connected failed.")
		panic(err)
	}
	localDB.SetMaxOpenConns(20) //设置数据库连接池最大连接数
	localDB.SetMaxIdleConns(10) //设置最大空闲连接数
	fmt.Println("Local sql Successfully connected!")
	return localDB
}
```

sql.Open()函数第一个参数为驱动的名字即"postgres"，第二个参数是数据库信息，分别是ip、端口、数据库用户名、密码、数据库的名字、sslmode 参数用于指定数据库连接时使用的 SSL 加密模式。函数返回一个连接池的指针，只有在需要的时候才会和数据库之间产生连接。

### 查找

```go
rows， err  := db.Query("select * from test where name = $1",  myname)	//("select 参数，参数(*表示全部参数) from 表的名字 where 参数 = $1 and 参数=$2(限制条件)", 变量名, 变量名)
if err != nil{
    panic(err)//检查错误，panic会直接报错并停止程序，也可以用其他方式打印出报错，但不停止程序
}
生成的rows是一个结果集，需要用Next()方法遍历结果集
for rows.Next(){
    var 变量1 数据类型
    ...
    err = rows.Scan(&变量1, &...)//存储数据到创建的变量中
    if err != nil{
        //检查错误
    }
    //这样就将数据库里一行的数据存储下来，遍历完数据集，便得到所有符合要求的数据
}
err := db.QueryRow("select * from test where name = $1", myname).Scan(&参数 ....)//查询数据库中的一行并存储到变量中

var count int
err := db.QueryRow("select count(*) from test where name = $1", myname).Scan(&count)//查询数据库中名字为myname变量值的数据行数，有时候需要提前检查是否存在数据，可以用count的方法检查
//可以用postgresql语法中的关键字、函数来辅助查询如max、min、DISTINCT等等
```

### 增加and更新

```go
_, err = db.Exec("insert into test (name, password) values ($1, $2)", myname, mypassword)//向test表中添加一行，其中name和password列的值为myname和mypassword
if err != nil{
    //检查错误
}
_, err = db.Exec("update test set password = $1 where name = $2", newpassword, myname)//更新test表中name为myname的行，令password等于newpassword
if err != nil{
    //检查错误
}
```

### 删除

```go
_, err = db.Exec("delete from test where name = $1", myname)//删除test表中name为myname的行
_, err = db.Exec("drop table test")//删除test表
_, err = db.Exec("alter table table_name drop column column_name;")//删除table_name表中名为column_name的列
```

### 创建表

```go
_, err = db.Exec("create table if not exists test(name text, password text)")//创建test表如果不存在的话，有两个列分别是name和password
_, err = db.Exec("alter table table_name add column_name datatype;")//向table_name表添加数据类型为datatype的列名为column_name
```

### 模糊查找

```go
rows, err := db.Query("select * from tesst where name ilike $1",  myname)	//	使用like模糊查找，ilike表示不分大小写
当myname = chen%时表示查找所有name前缀中有chen的行
当myname = %chen%时表示查找所有name中包含chen的行，如mychen, mychenmy
```
