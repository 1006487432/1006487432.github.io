---
title: IPsec协议认证
subtitle:
date: 2024-11-10T11:02:56+08:00
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

# IPsec协议认证

第⼀阶段发起⽅的验证

发起⽅加密私钥prv_i：

发起⽅加密公钥pub_i:



在Wireshark中打开“left.pcapng”包，⽤ isakmp 协议过滤⼀下数据包

导出SKi密⽂



所以SKi密⽂ X||Y||Hash||C 为：



使⽤⼯具，⽤prv_i解密SKi密⽂得到SKi的明⽂为：

在Wireshark中通过导出获取Ni密⽂

使⽤⼯具解密Ni密⽂:SM4算法，CBC模式密钥为Ski，iv为 00000000000000000000000000000000



在Wireshark中通过导出获取IDi密⽂,注意Wireshark对IDi的解析有错误，IDi数据看截图，IDi为identification payload去掉前3项后的所有数据



使⽤⼯具解密的到IDi明⽂：SM4算法，CBC模式， 密钥SKi iv：fb83d3a176a3e11b618206b32b958c69（Ni密⽂的最后⼀个分组）



在Wireshark中通过导出获取发起⽅加密证书 CERT_enc_i ，注意Wireshark对加密证书 **CERT_enc_i** 的解析有错误， **CERT_enc_i** 数据看截图，CERT_enc_i 为 **Certifcate Encoding || Certificate Date**

