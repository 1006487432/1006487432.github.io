---
title: Reverse
subtitle:
date: 2024-09-28T11:11:56+08:00
draft: true
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
  - 
categories:
  - homework
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

[toc]

### crunch 创建密码字典工具

Kali中已自带crunch工具，可直接在kali中使用。

命令格式：

~~~
crunch <min-len>  <max-len>  [<charset string>] [options]
~~~

参数：

~~~
min-len 最小长度字符串，即使不使用参数的值，也需要此选项

max-len 最大长度字符串，即使不使用参数的值，也需要此选项

charset string 字符集设置，默认是小写字符集
~~~

options :

~~~
-b     指定文件输出的大小，避免字典文件过大  
-c     指定文件输出的行数，即包含密码的个数
-d     限制相同元素出现的次数
-e     定义停止字符，即到该字符串就停止生成
-f     调用库文件（/etc/share/crunch/charset.lst）
-i     改变输出格式，即aaa,aab -> aaa,baa
-I     通常与-t联合使用，表明该字符为实义字符
-m     通常与-p搭配
-o     将密码保存到指定文件
-p     指定元素以组合的方式进行
-q     读取密码文件，即读取pass.txt
-r     定义重某一字符串重新开始
-s     指定一个开始的字符，即从自己定义的密码xxxx开始
-t     指定密码输出的格式
-u     禁止打印百分比（必须为最后一个选项）
-z     压缩生成的字典文件，支持gzip,bzip2,lzma,7z  

特殊字符，通常与-t配合使用

%      代表数字
^      代表特殊符号
@      代表小写字符
,      代表大写字符
~~~


