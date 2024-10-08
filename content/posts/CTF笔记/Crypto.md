---
title: Crypto
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

## RSA

#### p、q很接近的时候

~~~ python
from Crypto.Util.number import *
import gmpy2
# p = getPrime(512)
# q = gmpy2.next_prime(p)
temp=gmpy2.iroot(n,2)[0]
p=gmpy2.next_prime(temp)
q=n//p
或者
sn = isqrt(n)
q = next_prime(sn)
p = n // q
~~~

2.费马分解

当p和q比较接近时，可以使用费马分解分解p、q



~~~ python
def fermat_attack(n):
    a = isqrt(n)
    b2 = a*a - n
    b = isqrt(n)
    count = 0
    while b*b != b2:
        a = a + 1
        b2 = a*a - n
        b = isqrt(b2)
        count += 1
    p = a+b
    q = a-b
    assert n == p * q
    return p, q
~~~



#### 素数分解

##### 网站

[factordb.com](https://factordb.com/) 256位p、q

##### 工具

Yafu 128位p、q