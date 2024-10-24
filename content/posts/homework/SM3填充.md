---

title: 课上测试：SM3填充
subtitle:
date: 2024-10-25T10:11:56+08:00
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

# SM3填充

## 使用 OpenSSL 生成长度为70字节的随机数，最后添加“你的8位学号+姓名首字母”的 ASCII 码，得到HEX字符串S1，提交S1。（4 分）

~~~ shell
$ openssl rand -hex 70 > cjs.txt
$ cat cjs.txt
c2dd98fffc580d1741f29d236887404911cdd2a9f0feb4b2302e58ffa8fb89fd9e231f5c3666308d5ef5514d2d6939b0603676cdf7ded981a03249ea1d1e7f0116bcc5cfdfee
$ echo -n "20221415cjs" | od -tc -tx1
0000000   2   0   2   2   1   4   1   5   c   j   s
         32  30  32  32  31  34  31  35  63  6a  73
0000013
$ vim cjs.txt
$ cat cjs.txt
c2dd98fffc580d1741f29d236887404911cdd2a9f0feb4b2302e58ffa8fb89fd9e231f5c3666308d5ef5514d2d6939b0603676cdf7ded981a03249ea1d1e7f0116bcc5cfdfee3230323231343135636a73
~~~

S1为

c2dd98fffc580d1741f29d236887404911cdd2a9f0feb4b2302e58ffa8fb89fd9e231f5c3666308d5ef5514d2d6939b0603676cdf7ded981a03249ea1d1e7f0116bcc5cfdfee3230323231343135636a73

## 按照商用密码标准对 S1进行填充，提交填充过程和填充好的HEX 字符串S2。要包含详细填充过程。 （5 分）

S1共有162个字符，即81个字节，即648bit。

l=648，二进制表示为1010001000，为10bit

则s2末尾为54个0+1010001000

s1长为648bit，648 + 1 +k与448在模512下同余，

计算得出k的长度为311bit

则填充后的s2为:

c2dd98fffc580d1741f29d236887404911cdd2a9f0feb4b2302e58ffa8fb89fd9e231f5c3666308d5ef5514d2d6939b0603676cdf7ded981a03249ea1d1e7f0116bcc5cfdfee3230323231343135636a73Â<80>^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^@^B(

