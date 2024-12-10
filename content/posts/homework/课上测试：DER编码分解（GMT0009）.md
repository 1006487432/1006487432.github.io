---
title: 课上测试：DER编码分解（GMT0009）
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

## 使用 GmSSL 命令对“你的8 位学号+姓名的首字母”进行数字签名，并参考附件 GMT0009 分解得到签名值，提交签名值结果。（4 分）

首先使用GmSSL命令行生成密钥并输入要加密的数据

~~~ shell
$ gmssl sm2keygen -pass 1415 -out sm2.pem -pubout sm2pub.pem
$ ls
sm2.pem  sm2pub.pem
~~~

签名

~~~ shell
$ echo -ne "20221415cjs" | gmssl sm2sign -key sm2.pem -pass 1415 -out sm2.sig
$ od -tx1 sm2.sig
0000000 30 45 02 21 00 ee 6a 70 44 f3 d2 fd 5a f2 b3 bf
0000020 8c f6 a6 13 05 6a 56 5f ab 64 0f 86 23 61 18 9f
0000040 fa ab 8a 58 35 02 20 0c bc 76 ce 72 e2 d0 54 08
0000060 24 fd 35 ba 9b 7e 1f a6 5f d6 71 2e 8c 57 fb 82
0000100 83 f0 4e 66 eb 8f 4f
0000107
~~~

参考附件可知

~~~
SM2 算法签名数据格式的 ASN.1 定义为：
SM2Signature ::= SEQUENCE {
    r INTEGER, -- 签名值的第 1 部分
    s INTEGER -- 签名值的第 2 部分
}
~~~

~~~
3045022100ee6a7044f3d2fd5af2b3bf8cf6a613056a565fab640f862361189ffaab8a583502200cbc76ce72e2d0540824fd35ba9b7e1fa65fd6712e8c57fb8283f04e66eb8f4f

其中
3045 为SEQUENCE的TL
02 T 表示 INTEGER
21 l长度为2*16+1共33个字节
ee6a7044f3d2fd5af2b3bf8cf6a613056a565fab640f862361189ffaab8a5835 为r的值
02 t 表示 INTEGER
20 l 长度为32个字节
0cbc76ce72e2d0540824fd35ba9b7e1fa65fd6712e8c57fb8283f04e66eb8f4f 为s的值
~~~

分解得到签名值为r||s

~~~
ee6a7044f3d2fd5af2b3bf8cf6a613056a565fab640f862361189ffaab8a58350cbc76ce72e2d0540824fd35ba9b7e1fa65fd6712e8c57fb8283f04e66eb8f4f
~~~

## 使用 GmSSL 命令对“你的8 位学号+姓名的首字母”进行加密 ，并参考附件 GMT0009 分解得到密文数据，提交密文值。（5 分）

加密得到密文

~~~shell
$ echo -ne "20221415cjs" | gmssl sm2encrypt -pubkey sm2pub.pem -out sm2.der
$ od -tx1 sm2.der
0000000 30 75 02 21 00 87 e2 68 29 d5 5f 06 14 1f bd 8f
0000020 27 8d 79 e9 12 97 64 f0 30 87 1a 8e 54 70 83 45
0000040 07 83 52 0d d1 02 21 00 c3 f1 71 b6 21 54 20 3e
0000060 9d 30 28 82 1e e0 1d 69 a5 09 8f 4a 43 7e f1 87
0000100 7a 1c b6 3e a7 77 58 51 04 20 d7 91 3a 2f 4e 04
0000120 29 d6 86 e5 be 6c fd 1d f7 26 06 1c a6 0c 91 09
0000140 e4 a0 d6 c6 28 8f 57 48 ac 9c 04 0b 32 11 c9 61
0000160 40 aa 5e 4c 3a 24 56
0000167
~~~

~~~ 
307502210087e26829d55f06141fbd8f278d79e9129764f030871a8e547083450783520dd1022100c3f171b62154203e9d3028821ee01d69a5098f4a437ef1877a1cb63ea77758510420d7913a2f4e0429d686e5be6cfd1df726061ca60c9109e4a0d6c6288f5748ac9c040b3211c96140aa5e4c3a2456
~~~

参考附件可知

```text
SM2Cipher ::= SEQUENCE {
    xCoordinate INTEGER, -- x 分量
    yCoordinate INTEGER, -- y 分量
    hash OCTET STRING SIZE(32), -- 杂凑值
    cipherText OCTET STRING -- 密文
}
```

下面对结果进行分解

~~~
3075 SEQUENCE的TL
02 INTEGER的T
21 INTEGER的L
0087e26829d55f06141fbd8f278d79e9129764f030871a8e547083450783520dd1 X分量
02 INTEGER的T
21 INTEGER的L
00c3f171b62154203e9d3028821ee01d69a5098f4a437ef1877a1cb63ea7775851 T分量
04 OCTET STRING的T
20 OCTET STRING的L
d7913a2f4e0429d686e5be6cfd1df726061ca60c9109e4a0d6c6288f5748ac9c 32字节的杂凑值
04 OCTET STRING的T
0b OCTET STRING的L
3211c96140aa5e4c3a2456 密文
~~~

分解得到密文为：

~~~
3211c96140aa5e4c3a2456
~~~

## 提交要求 (1')

1. 记录实践过程和 AI 问答过程，尽量不要截图，给出文本内容
2. (选做)推荐所有作业托管到 gitee或 github 上
3. (必做)提交作业 markdown文档，命名为“学号-姓名-作业题目.md”
4. (必做)提交作业 markdown文档转成的 PDF 文件，命名为“学号-姓名-作业题目.pdf”