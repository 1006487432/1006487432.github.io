---


title: 课上测试：DER编码基础
subtitle:
date: 2024-10-24T17:06:56+08:00
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

# DER编码基础

## 对 BitString “101101101101”进行 DER编码，提交详细过程和结果。使用 echo 命令生成 bs.der文件，并使用 OpenSSL asn1parse命令解析，提交命令和结果（4 分）

比特串：101101101101 比特串长度为12，需要在后面补4个0

标志位:3

补位长度：4

编码结果： 03 03 0x04 0xb6 0xd0

~~~ shell
$ echo -ne "\x03\x03\x04\xb6\xd0" > bs.der
$ od -tx1 bs.der
0000000 03 03 04 b6 d0
0000005
$ openssl asn1parse -in bs.der  -inform der -i -dump
    0:d=0  hl=2 l=   3 prim: BIT STRING
      0000 - 04 b6 d0                                          ...
~~~

## 对基于SM2算法和SHA256算法的签名的OID 1.2.156.197.1.503进行 DER 编码，提交详细过程和结果，并使用 OpenSSL asn1parse命令解析，提交命令和结果。（5分）

{1 2 156 197 1 503}

第一个字节为:1*40 +2 = 42 = 2A

156的编码 1*128+28-> 81 1c

197的编码1*128+69->81 45

1的编码 0x01

503的编码128*3+119->83 77

编码结果为：

06 08 2A 81 1C 81 45 01 83 77

~~~ shell
$ echo -ne "\x06\x08\x2a\x81\x1c\x81\x45\x01\x83\x77" > oid.der
$ od -tx1 oid.der
0000000 06 08 2a 81 1c 81 45 01 83 77
0000012
$ openssl asn1parse -in oid.der  -inform der
    0:d=0  hl=2 l=   8 prim: OBJECT            :1.2.156.197.1.503
~~~

