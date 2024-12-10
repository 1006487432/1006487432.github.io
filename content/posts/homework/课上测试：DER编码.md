---
title: 课上测试：DER编码
subtitle:
date: 2024-12-10T11:02:56+08:00
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

# 完成下面任务（9分）

在 Ubuntu 或 openEuler 中完成任务（推荐openEuler）

1. 使用抽象语法记法（ASN.1）来定义学生数据结构：
    StudentInfo ::= SEQUENCE {
    studentID INTEGER,
    name IA5String,
    score INTEGER
    }

## 对上面数据结构使用你的信息进行填充，studentID是 8 位学号；name 是姓名首字母；score：60-100 数字，填充完使用 echo 命令得到“你的八位学号.der”文件，给出编码过程和echo命令具体内容（5 分）

studentID  20221415 INTEGER

name  cjs IA5String

score  100 INTEGER

分别进行der编码

### studentID

20221415 16进制为1348de7

T:为0x02

V:0x01 0x34 0x8d 0xe7

L:0x04

der编码为02 04 01 34 8d e7

验证无误

~~~ shell
$ echo -ne "\x02\x04\x01\x34\x8d\xe7" > stuid.der
$ openssl asn1parse -in stuid.der -inform der
    0:d=0  hl=2 l=   4 prim: INTEGER           :01348DE7
~~~

### name

T:0x16

L:0x03

V:0x63 0x6a 0x73

der编码为16 03 63 6a 73

验证无误

~~~ shell 
$ echo -ne "\x16\x03\x63\x6a\x73" > name.der
$ openssl asn1parse -in name.der -inform der
    0:d=0  hl=2 l=   3 prim: IA5STRING         :cjs
~~~

### score

100 16进制为64

T:为0x02

V:0x64

L:0x01

der编码为02 01 64

验证无误

~~~ shell
$ echo -ne "\x02\x01\x64" > score.der
$ openssl asn1parse -in score.der -inform der
    0:d=0  hl=2 l=   1 prim: INTEGER           :64
~~~

### 合并为：

stuid长度为6、name长度为5、score长度为3，长度共为14，16进制为e

T：0x30

L：0x0e

V: 上面连接起来

综上，der编码为300e020401348de71603636a73020164

~~~ shell
$ echo -ne "\x30\x0e\x02\x04\x01\x34\x8d\xe7\x16\x03\x63\x6a\x73\x02\x01\x64" > 20221415.der
~~~

## 使用 od 命令查看“你的八位学号.der”文件的内容，提交运行结果（2分）

~~~ shell
$ od -tx1 20221415.der
0000000 30 0e 02 04 01 34 8d e7 16 03 63 6a 73 02 01 64
0000020
~~~

结果无误

## 使用 OpenSSL asn1parse 命令解析“你的八位学号.der”文件，提交运行结果（2分）

~~~ shell
$ openssl asn1parse -in 20221415.der -inform der
    0:d=0  hl=2 l=  14 cons: SEQUENCE
    2:d=1  hl=2 l=   4 prim: INTEGER           :01348DE7
    8:d=1  hl=2 l=   3 prim: IA5STRING         :cjs
   13:d=1  hl=2 l=   1 prim: INTEGER           :64
~~~

结果无误

## 提交要求 (1')

1. 记录实践过程和 AI 问答过程，尽量不要截图，给出文本内容
2. (选做)推荐所有作业托管到 gitee或 github 上
3. (必做)提交作业 markdown文档，命名为“学号-姓名-作业题目.md”
4. (必做)提交作业 markdown文档转成的 PDF 文件，命名为“学号-姓名-作业题目.pdf”