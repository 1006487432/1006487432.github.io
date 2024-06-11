---
title: Go-gin教程与实战(1)
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

## Gin框架介绍

```
Gin 是一个用 Go (Golang) 编写的 HTTP Web 框架。 它具有类似 Martini 的 API，但性能比 Martini 快 40 倍。如果你需要极好的性能，使用 Gin 吧。
```

### Gin框架安装

- 要求：Go 1.13及以上版本
- 安装

1. 下载并安装gin：

   go get -u github.com/gin-gonic/gin

2. 在项目中引入gin：

```go
import "github.com/gin-gonic/gin"
```

有时候需要使用诸如http.StatusOK之类的常量，则需要引入`net/http`包：

```go
import "net/http"
```

## Gin框架的简单使用

```go
package main

import "github.com/gin-gonic/gin"

func main(){
    router := gin.Default()
	router.GET("/ping", func(context *gin.Context) {
		context.JSON(200, gin.H{"message": "pong",})
	})
    router.Run(":8080") // 监听并在 0.0.0.0:8080 上启动服务
}
```

上述代码运行后访问https://localhost:8080/ping可以看到一个json格式的数据,{“message”:“pong”}说明代码运行成功了。

首先使用gin.Default()函数生成一个路由引擎，这个路由引擎会默认使用两个全局中间件gin.Logger()和gin.Recovery()，生成的类型为*gin.Engine的变量router是Gin框架的基础。

```go
gin.Logger()//Logger 中间件将日志写入 gin.DefaultWriter
gin.Recovery()//Recovery 中间件会 recover 任何 panic。如果有 panic 的话，会写入 500
```

如果想生成一个没有默认中间件的路由引擎则使用函数gin.New()

```go
router := gin.New()
```

然后注册路由，上述代码为匿名函数的写法，以下展示注册路由和自定义函数的写法：

```go
---
router.GET("/path/to",	func(context *gin.Context)){函数内容})	//Get方法
router.POST("/path/to", func(context *gin.Context)){函数内容})	//post方法
---
自定义路由的方法
func helloword(context *gin.Context){
    	context.JSON(200, gin.H{"message": "hello world",})
}
router.GET("/path/to", helloword)
router.POST("/path/to", helloword)
--- 
```

当需要注册的路由太多时，可以采用注册路由组的方法：

```go
test := router.Group("/video")
	{
		test.GET("/1", func(c *gin.Context) {//访问/video/1以此类推
			c.JSON(http.StatusOK, gin.H{"msg": "访问路由组成功"})
		})
		test.GET("/2", func(c *gin.Context) {
			c.JSON(http.StatusOK, gin.H{"msg": "访问路由组成功"})
		})
		test.GET("/3", func(c *gin.Context) {
			c.JSON(http.StatusOK, gin.H{"msg": "访问路由组成功"})
		})
		test.GET("/4", func(c *gin.Context) {
			c.JSON(http.StatusOK, gin.H{"msg": "访问路由组成功"})
		})
	}
```

### 从URL获得参数

从url获得参数有GET和POST两种方法，具体区别见[http请求中get和post方法的区别 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/275695831)，下面用代码展示两种方法的使用:

- 通过上下文对象c *gin.Context的方法获得值

```go
//GET方法：
//URL /path?id=1234&name=Manu&value= 
//GET方法使用Query获得值，Query(key string) (value string)
       c.Query("id") == "1234"
       c.Query("name") == "Manu"
       c.Query("value") == ""
       c.Query("wtf") == ""
//也可以使用DefaultQuery(key string, defaultValue string) string  如果值为空则返回defaultValue的值
//QueryArray(key string) (values []string)
//QueryMap(key string) (dicts map[string]string)
---
//POST方法
	name := c.PostForm("name")
	price := c.DefaultPostForm("price", "100")
//c.PostForm(key string)(value string)
//同样有GET类似的方法，参数和返回值一样
```

- 可以通过参数绑定获取参数
  - 参数绑定利用反射机制，自动提取querystring，form表单，json，xml等参数到结构体中，可以极大提升开发效率。

```go
type Teacher struct {
	Name   string `form:"Name" json:"Name" binding:"required"`
	Email  string `form:"Email" json:"Email" binding:"required"`
	Wechat string `form:"Wechat" json:"Wechat" binding:"required"`
	id     int    `form:"id" json:"id" binding:"-"`
}
//在变量后面加上 `form:"Name" json:"Name" binding:"required"`， form为表单， json为json格式的数据，binding和参数验证有关，当值为required为需要验证不能传空值，为-时不需要验证；相较于form，会优先选择json格式，json:“”中的值必须与前端参数的name一致
func test(context *gin.Context){
  	 var information Teacher
   	 err := context.ShouldBind(&information) //根据req的content type 自动推断如何绑定,form/json/xml等格式
	if  err != nil {
		context.JSON(400, gin.H{"error": err.Error()})
		return
	}
    //这样就将获取的参数存储到了infomation变量里，通过访问结构体变量即可访问数据
}
```

## 参考资料:

[文档 | Gin Web Framework (gin-gonic.com)](https://gin-gonic.com/zh-cn/docs/)

[http请求中get和post方法的区别 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/275695831)
