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

## 第⼀阶段发起⽅的验证

### 使⽤⼯具解析发起⽅加密私钥⽂件“left_enc.key”，得到发起⽅加密公私钥对内容

~~~
-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqBHM9VAYItBG0wawIBAQQgLrRk3CWTe+WZOFSf
TMYwbOocLs3MSRpOO0/AvSmvH5mhRANCAAR9vqVFQ0WBcr07aI5QnC31RYas4AtY
7JQUmflKUKWMZ11vmtr/CJ6BN6djQ6zS81yjCopcz4G3zc5SZqAWueNk
-----END PRIVATE KEY-----
~~~

#### 私钥

~~~
2eb464dc25937be59938549f4cc6306cea1c2ecdcc491a4e3b4fc0bd29af1f99
~~~

#### 公钥

~~~
7dbea54543458172bd3b688e509c2df54586ace00b58ec941499f94a50a58c675d6f9adaff089e8137a76343acd2f35ca30a8a5ccf81b7cdce5266a016b9e364
~~~

### 导出SKi密文

~~~
307902210083e6ecef3fb62d7d4683132d920a298dd88efc8342256fb751987a5c37300cd30220398674a09fc955c21d9218a5016994738d9eddb2939b133e8ed2273aa3a215d30420cf1f2e14abe2de8c81fc9f2fbf028648570af88dcdaa98659a4c3eb1f96975100410ac34d8306c55b50003a96045184deb81

参考“GM/T 0009-2023 SM2密码算法使⽤规范”的加密数据的定义，实际的加密值是 X||Y||Hash||C 。
SKi密⽂包，按TLV分割：

3079 T
022100 L
83e6ecef3fb62d7d4683132d920a298dd88efc8342256fb751987a5c37300cd3 X
0220
398674a09fc955c21d9218a5016994738d9eddb2939b133e8ed2273aa3a215d3 Y
0420
cf1f2e14abe2de8c81fc9f2fbf028648570af88dcdaa98659a4c3eb1f9697510 Hash
0410
ac34d8306c55b50003a96045184deb81 C
~~~

#### SKi密⽂ X||Y||Hash||C 为：

~~~
83e6ecef3fb62d7d4683132d920a298dd88efc8342256fb751987a5c37300cd3398674a09fc955c21d9218a5016994738d9eddb2939b133e8ed2273aa3a215d3cf1f2e14abe2de8c81fc9f2fbf028648570af88dcdaa98659a4c3eb1f9697510ac34d8306c55b50003a96045184deb81
~~~

#### SKi的明文为

~~~
e6b74813213bfe4759c20225ade2678e
~~~

### 在Wireshark中通过导出获取Ni密⽂

~~~
a73cb7e86cc9b2020ecb43baa4e96cf8fb83d3a176a3e11b618206b32b958c69
~~~

#### 使⽤⼯具解密Ni密⽂:SM4算法，CBC模式密钥为Ski，iv为 00000000000000000000000000000000

Ni

~~~
450be90d637a4c714d129d13e15642370000000000000000000000000000000f
后⾯的 0000000000000000000000000000000f 为填充数据，Ni明⽂为 450be90d637a4c714d129d13e1564237
~~~

### 在Wireshark中通过导出获取IDi密⽂,注意Wireshark对IDi的解析有错误，IDi数据看截图，IDi为identification payload去掉前3项后的所有数据

IDi密文

~~~
eff5aaaddbce5efb2d9daca6f1de48c88096f24ada20e090aa45dc2e46a90517140fe404e0fa5c362423b9559a7dccb08d95ed049d05bf40fbe654ba7d0fae70a583343b9cb2a417d66032ca9a786ff901f6987c86bf733851bf8a46ea92a3ef
~~~

#### 使⽤⼯具解密的到IDi明⽂：SM4算法，CBC模式， 密钥SKi iv：fb83d3a176a3e11b618206b32b958c69（Ni密⽂的最后⼀个分组）

IDi明文

~~~
09000000304a310b3009060355040613024141310b3009060355040813024242310b3009060355040a13024343310b3009060355040b13024444311430120603550403130b636c69656e74207369676e0000000000000000000000000000000f
~~~

### 在Wireshark中通过导出获取发起⽅加密证书 CERT_enc_i ，注意Wireshark对加密证书 **CERT_enc_i** 的解析有错误， **CERT_enc_i** 数据看截图，CERT_enc_i 为 **Certifcate Encoding || Certificate Date**

~~~
05308201ed30820192a00302010202145b2ebfa257b547c1b04ebce83ad65e6c595addaa300a06082a811ccf550183753045310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c024444310f300d06035504030c067375622063613020170d3233303232323032333031345a180f32313233303132393032333031345a3049310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c0244443113301106035504030c0a636c69656e7420656e633059301306072a8648ce3d020106082a811ccf5501822d034200042920dde9348041de867e49a5caa1936d3241f9b79cb5dcc5c6d59b31f8d88467b05b38505b101f7dbf242bcba73daf394cf0879d3f0e8ec08739f1db00fa770ca35a305830090603551d1304023000300b0603551d0f040403020338301d0603551d0e041604147cf13c4f768f4733a2ffe2e259346b90cfb474a8301f0603551d23041830168014ac61eb22806259083e96c8d17fce745c02af3c99300a06082a811ccf550183750349003046022100e2131845079c82d4a4b09b4990b21bc4e281899b83b226c9916d5c5fee12139f022100e7d3e711561a7a0be92392ed9f94f63ca2aa899d9039611f4472488bf14565ea
~~~

### 得到签名原⽂ SKi||Ni||IDi||CERT_enc_i :

~~~
e6b74813213bfe4759c20225ade2678e450be90d637a4c714d129d13e156423709000000304a310b3009060355040613024141310b3009060355040813024242310b3009060355040a13024343310b3009060355040b13024444311430120603550403130b636c69656e74207369676e05308201ed30820192a00302010202145b2ebfa257b547c1b04ebce83ad65e6c595addaa300a06082a811ccf550183753045310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c024444310f300d06035504030c067375622063613020170d3233303232323032333031345a180f32313233303132393032333031345a3049310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c0244443113301106035504030c0a636c69656e7420656e633059301306072a8648ce3d020106082a811ccf5501822d034200042920dde9348041de867e49a5caa1936d3241f9b79cb5dcc5c6d59b31f8d88467b05b38505b101f7dbf242bcba73daf394cf0879d3f0e8ec08739f1db00fa770ca35a305830090603551d1304023000300b0603551d0f040403020338301d0603551d0e041604147cf13c4f768f4733a2ffe2e259346b90cfb474a8301f0603551d23041830168014ac61eb22806259083e96c8d17fce745c02af3c99300a06082a811ccf550183750349003046022100e2131845079c82d4a4b09b4990b21bc4e281899b83b226c9916d5c5fee12139f022100e7d3e711561a7a0be92392ed9f94f63ca2aa899d9039611f4472488bf14565ea
~~~

### 在Wireshark中通过导出获取签名值

~~~
30450221008fd24caa07d506eb6b88ebd5852839e127e875738747a8d2c356150e4b95c6f2022014a9f5aea118004276fbd8437b0f6e5db84d138b058236f7d6656f3dedefd740

30 T
45 L
02 T
21 L
00 填充
8fd24caa07d506eb6b88ebd5852839e127e875738747a8d2c356150e4b95c6f2 r
02 T
20 L
14a9f5aea118004276fbd8437b0f6e5db84d138b058236f7d6656f3dedefd740 s
~~~

签名值 r||s :

~~~
8fd24caa07d506eb6b88ebd5852839e127e875738747a8d2c356150e4b95c6f214a9f5aea118004276fbd8437b0f6e5db84d138b058236f7d6656f3dedefd740
~~~

### 在Wireshark中通过导出获取发起⽅签名公钥

签名公钥：

~~~
04
2d617e74d5586dde23d2490fbd468e30f11d012d50a8f392cd1849b10b167e9a0661f7e3a2a00ee7ec4718ed937b4ab2c50aa0d341d15e4095743b3850af6d3c
~~~

验签成功

## 第⼀阶段响应⽅的验证

~~~
-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqBHM9VAYItBG0wawIBAQQguz0M4/6qUhgHAxuG
WI2NPtNciIwmYAN4AUDoBEka1tehRANCAAQpIN3pNIBB3oZ+SaXKoZNtMkH5t5y1
3MXG1Zsx+NiEZ7BbOFBbEB99vyQry6c9rzlM8IedPw6OwIc58dsA+ncM
-----END PRIVATE KEY-----
~~~
私钥
~~~
bb3d0ce3feaa521807031b86588d8d3ed35c888c266003780140e804491ad6d7
~~~
公钥
~~~
2920dde9348041de867e49a5caa1936d3241f9b79cb5dcc5c6d59b31f8d88467b05b38505b101f7dbf242bcba73daf394cf0879d3f0e8ec08739f1db00fa770c
~~~

### 导出SKr密文

~~~
3079022100e2fee5b1439937014b7ad1a585f4a62910787a7c885884c1370cd9fb8dadd12c02201c2f5ab9ba02bc9d9c21cf18afaa6b64f0b0a733bd730508d6567f9faac722aa042000376aa46646d90577b5ab0170f97043356acef83504b8a4b9ae159a0e834fc3041001734e922fa8c88ad6814c59264e9f21

3079
022100
e2fee5b1439937014b7ad1a585f4a62910787a7c885884c1370cd9fb8dadd12c
0220
1c2f5ab9ba02bc9d9c21cf18afaa6b64f0b0a733bd730508d6567f9faac722aa
0420
00376aa46646d90577b5ab0170f97043356acef83504b8a4b9ae159a0e834fc3
0410
01734e922fa8c88ad6814c59264e9f21

e2fee5b1439937014b7ad1a585f4a62910787a7c885884c1370cd9fb8dadd12c1c2f5ab9ba02bc9d9c21cf18afaa6b64f0b0a733bd730508d6567f9faac722aa00376aa46646d90577b5ab0170f97043356acef83504b8a4b9ae159a0e834fc301734e922fa8c88ad6814c59264e9f21
~~~

#### 解密得到SKr明文

~~~
93754381265febcf025a6c0d53abf6d3
~~~

### 在Wireshark中通过导出获取Nr密⽂

~~~
a469aa4b7374d33262e76b20ed2f65e6ccbd5799630f7f8e68320b2f121e0a26
~~~

#### 使⽤⼯具解密Nr密⽂:SM4算法，CBC模式密钥为Skr，iv为 00000000000000000000000000000000

~~~
098664cd2c46bfbc8c5f5dcb856e64810000000000000000000000000000000f
后⾯的 0000000000000000000000000000000f 为填充数据，Nr明⽂为 098664cd2c46bfbc8c5f5dcb856e6481
~~~

### 在Wireshark中通过导出获取IDr密⽂,注意Wireshark对IDr的解析有错误，IDr数据看截图，IDr为identification payload去掉前3项后的所有数据

~~~
071d406ee84d676c2837ba45490b650b27f664aa7a732aef599c69d06b25fd9be2e7f4f11d5306aa2ced370b6958a6b4a9c91b3ddb2fb6f61673d897fdf12f73796643992e7cc9d996cac9ddaa571b2ec85a68150fad375d6e94b62c28dfcd8d
~~~

#### 使⽤⼯具解密的到IDr明⽂：SM4算法，CBC模式， 密钥SKr iv：ccbd5799630f7f8e68320b2f121e0a26（Nr密⽂的最后⼀个分组）

~~~
09000000304a310b3009060355040613024141310b3009060355040813024242310b3009060355040a13024343310b3009060355040b13024444311430120603550403130b736572766572207369676e0000000000000000000000000000000f
~~~

### 在Wireshark中通过导出获取发起⽅加密证书 CERT_enc_r ，注意Wireshark对加密证书 **CERT_enc_r** 的解析有错误， **CERT_enc_r** 数据看截图，**CERT_enc_r** 为 **Certifcate Encoding || Certificate Date**

~~~
05308201eb30820192a003020102021468d892e963aca045620e799d6fc31d937433e57c300a06082a811ccf550183753045310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c024444310f300d06035504030c067375622063613020170d3233303232323032333031345a180f32313233303132393032333031345a3049310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c0244443113301106035504030c0a73657276657220656e633059301306072a8648ce3d020106082a811ccf5501822d034200047dbea54543458172bd3b688e509c2df54586ace00b58ec941499f94a50a58c675d6f9adaff089e8137a76343acd2f35ca30a8a5ccf81b7cdce5266a016b9e364a35a305830090603551d1304023000300b0603551d0f040403020338301d0603551d0e0416041467a5add59476e05a9c5e56b8860ff13b28eeec54301f0603551d23041830168014ac61eb22806259083e96c8d17fce745c02af3c99300a06082a811ccf550183750347003044022047593579c4adec8db7df98c4aae1661c1139a5ef1293f22a3aa412d09becd6e602206e57301d177946956fd39cb5ac603902cd17c7517ed8941ecc985ea7db6958c8
~~~

### 得到签名原⽂ SKr||Nr||IDr||CERT_enc_r :

~~~
93754381265febcf025a6c0d53abf6d3098664cd2c46bfbc8c5f5dcb856e648109000000304a310b3009060355040613024141310b3009060355040813024242310b3009060355040a13024343310b3009060355040b13024444311430120603550403130b736572766572207369676e05308201eb30820192a003020102021468d892e963aca045620e799d6fc31d937433e57c300a06082a811ccf550183753045310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c024444310f300d06035504030c067375622063613020170d3233303232323032333031345a180f32313233303132393032333031345a3049310b3009060355040613024141310b300906035504080c024242310b3009060355040a0c024343310b3009060355040b0c0244443113301106035504030c0a73657276657220656e633059301306072a8648ce3d020106082a811ccf5501822d034200047dbea54543458172bd3b688e509c2df54586ace00b58ec941499f94a50a58c675d6f9adaff089e8137a76343acd2f35ca30a8a5ccf81b7cdce5266a016b9e364a35a305830090603551d1304023000300b0603551d0f040403020338301d0603551d0e0416041467a5add59476e05a9c5e56b8860ff13b28eeec54301f0603551d23041830168014ac61eb22806259083e96c8d17fce745c02af3c99300a06082a811ccf550183750347003044022047593579c4adec8db7df98c4aae1661c1139a5ef1293f22a3aa412d09becd6e602206e57301d177946956fd39cb5ac603902cd17c7517ed8941ecc985ea7db6958c8
~~~

### 在Wireshark中通过导出获取签名值

~~~
3046022100c8ac036fbce28ff4e7f5366c704e405b23753b8ca95a4319b8657ea1fb46534e022100f14eeb8858614a62409af9aa1037e2b4b42b155e931b359cd792189ca90e09d4

30
46
022100
c8ac036fbce28ff4e7f5366c704e405b23753b8ca95a4319b8657ea1fb46534e
022100
f14eeb8858614a62409af9aa1037e2b4b42b155e931b359cd792189ca90e09d4
~~~

~~~
c8ac036fbce28ff4e7f5366c704e405b23753b8ca95a4319b8657ea1fb46534ef14eeb8858614a62409af9aa1037e2b4b42b155e931b359cd792189ca90e09d4
~~~

### 在Wireshark中通过导出获取响应⽅签名公钥

~~~
04
05bffaeec406c8f3f580a6e39c528476c0df2b61065d4a74f476af0fb66890f896acc4b21d8b036d13f17bd4d38234908bedb77f8e3eae870654fc6fa8048d0c
~~~

验签成功

## 第⼀阶段密钥计算

### 基于 sm3 算法计算HASH(Ni||Nr)

#### Ni||Nr:

~~~
450be90d637a4c714d129d13e1564237098664cd2c46bfbc8c5f5dcb856e6481
~~~

#### HASH(Ni||Nr)

~~~
83fddf2b5dc8bd853c343ee68f780cfaf2e37fdde3998da2c76a4b368816e972
~~~

### 在Wireshark中通过导出获取 CKY-I||CKY-R

#### CKY-I||CKY-R:

~~~
a89a4662a4d1cad049a2eb29cf6d65db
~~~

### 使⽤⼯具计算 SKEYID = PRF(HASH(Ni||Nr), CKY-I|CKY-R)

SM3-HMAC:Key为Hash(Ni||Nr), 数据为CKY-I|CKY-R(a89a4662a4d1cad049a2eb29cf6d65db)

~~~
af75db413c0babf64d866f08b53432ce027c59a975a30b284b31236c0689113e
~~~

### 使⽤⼯具计算 SKEYID_d = PRF(SKEYID, CKY-I|CKY-R|0)

SM3-HMAC:Key为SKEYID, 数据为CKY-I|CKY-R|0(a89a4662a4d1cad049a2eb29cf6d65db00)

#### SKEYID_d

~~~
d07385874bd72fa3ec6d42714e643a94de6644d24f2f50239892f8ef478293e7
~~~

### 使⽤⼯具计算SKEYID_a = PRF(SKEYID, SKEYID_d|CKY-I|CKY-R|1)

SM3-HMAC:Key为SKEYID, 数据为SKEYID_d|CKY-I|CKY-R|1

(d07385874bd72fa3ec6d42714e643a94de6644d24f2f50239892f8ef478293e7a89a4662a4d1cad049a2eb29cf6d65db01)

~~~
51b531818c073c1b72ca8e9a883e6b19755604445abedf57df176d575f4320fe
~~~

### 使⽤⼯具计算SKEYID_e = PRF(SKEYID, SKEYID_a|CKY-I|CKY-R|2)

SM3-HMAC:Key为SKEYID, 数据为SKEYID_a|CKY-I|CKY-R|2

(51b531818c073c1b72ca8e9a883e6b19755604445abedf57df176d575f4320fea89a4662a4d1cad049a2eb29cf6d65db02)

~~~
f60661271d29c5093894dacdacf5378c13aeea3d52b2be0ce06ad87edbc9f7d1

分成两段
f60661271d29c5093894dacdacf5378c SKEYID_e
13aeea3d52b2be0ce06ad87edbc9f7d1
~~~

### 使⽤⼯具计算hash(SKi||SKr)

IV=HASH(Ski_b|Skr_b)

SKi||SKr

~~~
e6b74813213bfe4759c20225ade2678e93754381265febcf025a6c0d53abf6d3
~~~

SM3结果

~~~
de788aa1e41303baf97136e86f82f2fc05fd904df03879c49c1e1a9a868b0e1a
~~~

IV=hash(SKi||SKr)

~~~
de788aa1e41303baf97136e86f82f2fc IV 05fd904df03879c49c1e1a9a868b0e1a
~~~

### HAHSi密⽂及解密

加密前的消息应进⾏填充，使其⻓度等于对称密码算法分组⻓度的整数倍。所有的填充字节的值都是0。报头中的消息⻓度应包括填充字节的⻓度，因为这反映了密⽂的⻓度。为了鉴别交换，发起⽅产⽣HASHi, 响应⽅产⽣HASHr, 计算公式如下：

~~~
HASHi=PRF(SKEYID,CKY-I|CKY-R|SAi_b|IDi_b)
HASHr=PRF(SKEYID,CKY-R|CKY-I|SAr_b|IDr_b)
~~~

#### 在Wireshark中通过导出获取HAHSi密⽂

~~~
c60c2e7689fa1519256ec690bbfb7d6380a52de3d51ce8fb1ac5923a84ceac86
b958be5fa74277fc91b3bfd3d1cbf7e0 HASHr IV
~~~

#### 使⽤⼯具解密的HASHi包:SM4算法，密钥：SKEYID_e，CBC 模式，IV=HASH(Ski_b|Skr_b)

~~~
密文：c60c2e7689fa1519256ec690bbfb7d6380a52de3d51ce8fb1ac5923a84ceac86b958be5fa74277fc91b3bfd3d1cbf7e0
密钥：f60661271d29c5093894dacdacf5378c13aeea3d52b2be0ce06ad87edbc9f7d1
IV：de788aa1e41303baf97136e86f82f2fc05fd904df03879c49c1e1a9a868b0e1a
~~~

~~~
00
00
00
24
5855a82383911acace237a72d2c6427aa18d552fc4d80d13288104a7f9da2f3c
000000000000000000000000
~~~

### 验证HASHi=PRF(SKEYID,CKY-I|CKY-R|SAi_b|IDi_b)

#### 在Wireshark中通过导出获取SAi

~~~
0d000034 去掉前三项
0000000100000001000000280001000100000020010100008001007f800200148003000a80140002800b0001800c3de0
~~~

#### CKY-I||CKY-R||SAi||IDi

~~~
a89a4662a4d1cad049a2eb29cf6d65db0000000100000001000000280001000100000020010100008001007f800200148003000a80140002800b0001800c3de009000000304a310b3009060355040613024141310b3009060355040813024242310b3009060355040a13024343310b3009060355040b13024444311430120603550403130b636c69656e74207369676e
~~~

#### HASHi=PRF(SKEYID,CKY-I|CKY-R|SAi_b|IDi_b)

~~~
5855a82383911acace237a72d2c6427aa18d552fc4d80d13288104a7f9da2f3c
~~~

### HASHr密⽂及解密

#### 在Wireshark中通过导出获取HASHr密⽂

~~~
dd55ad19832211a7909550c3472615c55feddb949b5ee01f9cfe6d9e228e3a1dd92048953a172891b194012f8db5f7b0
~~~

#### 解密的HASHr：SM4算法，密钥：SKEYID_e，CBC模式，IV=HASHi密⽂最后⼀包

~~~
密文：dd55ad19832211a7909550c3472615c55feddb949b5ee01f9cfe6d9e228e3a1dd92048953a172891b194012f8db5f7b0
Key：f60661271d29c5093894dacdacf5378c13aeea3d52b2be0ce06ad87edbc9f7d1
IV：b958be5fa74277fc91b3bfd3d1cbf7e0
~~~

~~~
00000024
4146700c999eb6b4ce92891881b8ec69c013bf83062b885372f2dfddfafe4ea6
000000000000000000000000
~~~

### 验证HASHr=PRF(SKEYID,CKY-R|CKY-I|SAr_b|IDr_b)

#### 在Wireshark中通过导出获取SAr

~~~
06000034 去掉前三项
0000000100000001000000280001000100000020010100008001007f800200148003000a80140002800b0001800c3de0
~~~

#### CKY-R||CKY-I||SAr||IDr

~~~
49a2eb29cf6d65dba89a4662a4d1cad00000000100000001000000280001000100000020010100008001007f800200148003000a80140002800b0001800c3de009000000304a310b3009060355040613024141310b3009060355040813024242310b3009060355040a13024343310b3009060355040b13024444311430120603550403130b736572766572207369676e
~~~

~~~
4146700c999eb6b4ce92891881b8ec69c013bf83062b885372f2dfddfafe4ea6
~~~

结果一致

## 第⼆阶段

### IV=HASH(第⼀阶段的最后⼀组密⽂||MsgID)

HASHr的最后一组密文



~~~
dd55ad19832211a7909550c3472615c55feddb949b5ee01f9cfe6d9e228e3a1dd92048953a172891b194012f8db5f7b0
最后一组为
d92048953a172891b194012f8db5f7b0
~~~

#### MsgID

~~~
cc2d2221
~~~

#### 密文||MsgID

~~~
d92048953a172891b194012f8db5f7b0cc2d2221
~~~

#### SM3得到

~~~
56e6dfc945499ae8aca47a6ca9cf2ada005ac24e502d2ad621591efd5d57bdbe

56e6dfc945499ae8aca47a6ca9cf2ada IV
005ac24e502d2ad621591efd5d57bdbe
~~~

### 在Wireshark中通过导出获取第⼀个包密⽂

~~~
0480348d01d6635a2c2a912fbdb677f0e718ca239c1758319069d74efc0601c4bdb814f8d5575add1acc7075723263a65270547f464345b292753cd5c759fde4c94048f5ced4b161679c75a3cb0fec2d80c292df8b6a567b916cb0cdb57d30097f841630cfb8081cc8b65b0be54dcd45acef18456a1dbb1b764b4a4164b4ffab0b364556de52ec116c1014112986fd82
359b204f92800504072e2994af771b88 第⼆包IV
~~~

### 第⼀个包解密:SM4算法，CBC模式，密钥SKEYID_e, IV=HASH(第⼀阶段的最后⼀组密⽂||MsgID)：56e6dfc945499ae8aca47a6ca9cf2ada

~~~
010000240c52abf2bee8337f08694ee22b97e4571ef491ef5c88eda04a5f4c3fc82c03d90a00003c00000001000000010000003000030401c515ecd500000024017f000080050014800400018001000180021734800100020002000400086470050000144fdbbce1785046b21f1eb00afbec31c40500001004000000ac101d00ffffff000000001004000000ac101c00ffffff00000000000000000000000000
~~~

第⼀个包明⽂：

~~~
hash包
01 next payload ：SA
00 保留
0024 ⻓度
0c52abf2bee8337f08694ee22b97e4571ef491ef5c88eda04a5f4c3fc82c03d9
SA包
0a nounce包
00
003c
00000001
00000001
建议包
00
00
0030
00
03 协议类型 ESP
04 SPI⻓度
01 ⼦载荷变换数
c515ecd5 变⻓的SPI
变换载荷
00
00
0024
01变换号
7f 变换ID ：127（现在129） SM4
0000
属性载荷
80050014 SM3-HMAC鉴别（20）
80040001 隧道模式封装
80010001 ⽣存类型：秒
80021734 ⽣存期：5940秒=99分钟
80010000002000400086470
nounce包
05 下⼀载荷：ID
00
0014
4fdbbce1785046b21f1eb00afbec31c4
IDi包
05
00
0010
04000000ac101d00ffffff00
IDr包
00
00
0010
04000000ac101c00ffffff00
000000000000000000000000填充
~~~

### 在Wireshark中通过导出获取第⼆个包密⽂

~~~
49813dfd83a4c3c3bf2950290904fc4237c90e5e45e4991a60336a91ee6848de0ca5964fbb5af6f0aa607ebcc8188e9774a8ac79f1f93b1a72140625c3588eea7e1e4b137783c948e9bd7a060f8d36821b5198c7e3eb41a5ad4e3f30acf978f80930e47a79e3ddae43fb9d1463c6dbcb45ad9d37ead1eb54fbcf39058a9e9c39f7a9c43c6c1aecc5a1a58522abd59609
20f20261bf78e32847d2f84e7f4cbdb2 第三包IV
~~~

### 第⼆个包解密:SM4算法，CBC模式，密钥SKEYID_e, IV：359b204f92800504072e2994af771b88

~~~
01000024d90aad574e561b98e0fd9136cc217e7e4c8300cf8c3829aa2c650e8de73e7c210a00003c00000001000000010000003000030401c713ad0600000024017f00008005001480040001800100018002173480010002000200040008647005000014106bcaa925dc5b6d994efc88369d60590500001004000000ac101d00ffffff000000001004000000ac101c00ffffff00000000000000000000000000
~~~

### 在Wireshark中通过导出获取第三个包密⽂

~~~
6017ca492079d1910a3cfbc30aaa2d66c6a003b902799af271b6d87d36555031b2d9d152de3a711963072efa0d2d8012
~~~

### 第三个包解密:SM4算法，CBC模式，密钥SKEYID_e, IV：20f20261bf78e32847d2f84e7f4cbdb2

~~~
00
00
0024
c6125d6cc79a13a4fa8f0806e7fed72ec4280f5a64b5a0a67789bd8e698036c9
000000000000000000000000 填充
~~~

## 验证

### 第⼀阶段发起⽅的验证



~~~
私钥
-----BEGIN SM2 PARAMETERS-----
BggqgRzPVQGCLQ==
-----END SM2 PARAMETERS-----
-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqBHM9VAYItBG0wawIBAQQgLrRk3CWTe+WZOFSf
TMYwbOocLs3MSRpOO0/AvSmvH5mhRANCAAR9vqVFQ0WBcr07aI5QnC31RYas4AtY
7JQUmflKUKWMZ11vmtr/CJ6BN6djQ6zS81yjCopcz4G3zc5SZqAWueNk
-----END PRIVATE KEY-----
公钥
3059301306072A8648CE3D020106082A811CCF5501822D034200047dbea54543458172bd3b688e509c2df54586ace00b58ec941499f94a50a58c675d6f9adaff089e8137a76343acd2f35ca30a8a5ccf81b7cdce5266a016b9e364

-----BEGIN PUBLIC KEY-----
MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAEfb6lRUNFgXK9O2iOUJwt9UWGrOALWOyUFJn5SlCljGddb5ra/wiegTenY0Os0vNcowqKXM+Bt83OUmagFrnjZA==
-----END PUBLIC KEY-----
~~~
#### 计算SKI

~~~ shell
$ echo -e -n "\x30\x79\x02\x21\x00\x83\xe6\xec\xef\x3f\xb6\x2d\x7d\x46\x83\x13\x2d\x92\x0a\x29\x8d\xd8\x8e\xfc\x83\x42\x25\x6f\xb7\x51\x98\x7a\x5c\x37\x30\x0c\xd3\x02\x20\x39\x86\x74\xa0\x9f\xc9\x55\xc2\x1d\x92\x18\xa5\x01\x69\x94\x73\x8d\x9e\xdd\xb2\x93\x9b\x13\x3e\x8e\xd2\x27\x3a\xa3\xa2\x15\xd3\x04\x20\xcf\x1f\x2e\x14\xab\xe2\xde\x8c\x81\xfc\x9f\x2f\xbf\x02\x86\x48\x57\x0a\xf8\x8d\xcd\xaa\x98\x65\x9a\x4c\x3e\xb1\xf9\x69\x75\x10\x04\x10\xac\x34\xd8\x30\x6c\x55\xb5\x00\x03\xa9\x60\x45\x18\x4d\xeb\x81" > Ski_enc.bin
~~~

~~~shell
$ openssl pkeyutl -decrypt -inkey left_pri.pem -in Ski_enc.bin -out ski_dec.txt
$ od -tx1 ski_dec.txt
0000000 e6 b7 48 13 21 3b fe 47 59 c2 02 25 ad e2 67 8e
0000020
~~~

#### 计算Ni

~~~ shell
$ echo -ne "\xa7\x3c\xb7\xe8\x6c\xc9\xb2\x02\x0e\xcb\x43\xba\xa4\xe9\x6c\xf8\xfb\x83\xd3\xa1\x76\xa3\xe1\x1b\x61\x82\x06\xb3\x2b\x95\x8c\x69" > ni_enc.bin
$ echo -n -e "\xe6\xb7\x48\x13\x21\x3b\xfe\x47\x59\xc2\x02\x25\xad\xe2\x67\x8e" > Nikey.bin
$ echo -n -e "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" > Niiv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 Nikey.bin) -iv $(xxd -p -c 32 Niiv.bin) -in ni_enc.bin -out ni_dec.bin
$ od -tc -tx1 ni_dec.bin
0000000   E  \v 351  \r   c   z   L   q   M 022 235 023 341   V   B   7
         45  0b  e9  0d  63  7a  4c  71  4d  12  9d  13  e1  56  42  37
0000020  \0
         00
0000021

Ni明⽂为 450be90d637a4c714d129d13e1564237
~~~

#### 计算IDi

~~~ shell
$ echo -ne "\xef\xf5\xaa\xad\xdb\xce\x5e\xfb\x2d\x9d\xac\xa6\xf1\xde\x48\xc8\x80\x96\xf2\x4a\xda\x20\xe0\x90\xaa\x45\xdc\x2e\x46\xa9\x05\x17\x14\x0f\xe4\x04\xe0\xfa\x5c\x36\x24\x23\xb9\x55\x9a\x7d\xcc\xb0\x8d\x95\xed\x04\x9d\x05\xbf\x40\xfb\xe6\x54\xba\x7d\x0f\xae\x70\xa5\x83\x34\x3b\x9c\xb2\xa4\x17\xd6\x60\x32\xca\x9a\x78\x6f\xf9\x01\xf6\x98\x7c\x86\xbf\x73\x38\x51\xbf\x8a\x46\xea\x92\xa3\xef" > idi.bin
$ echo -ne "\xfb\x83\xd3\xa1\x76\xa3\xe1\x1b\x61\x82\x06\xb3\x2b\x95\x8c\x69" > idi_iv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 Nikey.bin) -iv $(xxd -p -c 32 idi_iv.bin) -in idi.bin
-out idi_dec.bin
$ od -tx1 idi_dec.bin
0000000 09 00 00 00 30 4a 31 0b 30 09 06 03 55 04 06 13
0000020 02 41 41 31 0b 30 09 06 03 55 04 08 13 02 42 42
0000040 31 0b 30 09 06 03 55 04 0a 13 02 43 43 31 0b 30
0000060 09 06 03 55 04 0b 13 02 44 44 31 14 30 12 06 03
0000100 55 04 03 13 0b 63 6c 69 65 6e 74 20 73 69 67 6e
0000120 00
0000121
~~~

#### 验证签名

~~~ shell
$ echo -n -e "\xe6\xb7\x48\x13\x21\x3b\xfe\x47\x59\xc2\x02\x25\xad\xe2\x67\x8e\x45\x0b\xe9\x0d\x63\x7a\x4c\x71\x4d\x12\x9d\x13\xe1\x56\x42\x37\x09\x00\x00\x00\x30\x4a\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x13\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x13\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x13\x02\x44\x44\x31\x14\x30\x12\x06\x03\x55\x04\x03\x13\x0b\x63\x6c\x69\x65\x6e\x74\x20\x73\x69\x67\x6e\x05\x30\x82\x01\xed\x30\x82\x01\x92\xa0\x03\x02\x01\x02\x02\x14\x5b\x2e\xbf\xa2\x57\xb5\x47\xc1\xb0\x4e\xbc\xe8\x3a\xd6\x5e\x6c\x59\x5a\xdd\xaa\x30\x0a\x06\x08\x2a\x81\x1c\xcf\x55\x01\x83\x75\x30\x45\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x0c\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x0c\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x0c\x02\x44\x44\x31\x0f\x30\x0d\x06\x03\x55\x04\x03\x0c\x06\x73\x75\x62\x20\x63\x61\x30\x20\x17\x0d\x32\x33\x30\x32\x32\x32\x30\x32\x33\x30\x31\x34\x5a\x18\x0f\x32\x31\x32\x33\x30\x31\x32\x39\x30\x32\x33\x30\x31\x34\x5a\x30\x49\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x0c\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x0c\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x0c\x02\x44\x44\x31\x13\x30\x11\x06\x03\x55\x04\x03\x0c\x0a\x63\x6c\x69\x65\x6e\x74\x20\x65\x6e\x63\x30\x59\x30\x13\x06\x07\x2a\x86\x48\xce\x3d\x02\x01\x06\x08\x2a\x81\x1c\xcf\x55\x01\x82\x2d\x03\x42\x00\x04\x29\x20\xdd\xe9\x34\x80\x41\xde\x86\x7e\x49\xa5\xca\xa1\x93\x6d\x32\x41\xf9\xb7\x9c\xb5\xdc\xc5\xc6\xd5\x9b\x31\xf8\xd8\x84\x67\xb0\x5b\x38\x50\x5b\x10\x1f\x7d\xbf\x24\x2b\xcb\xa7\x3d\xaf\x39\x4c\xf0\x87\x9d\x3f\x0e\x8e\xc0\x87\x39\xf1\xdb\x00\xfa\x77\x0c\xa3\x5a\x30\x58\x30\x09\x06\x03\x55\x1d\x13\x04\x02\x30\x00\x30\x0b\x06\x03\x55\x1d\x0f\x04\x04\x03\x02\x03\x38\x30\x1d\x06\x03\x55\x1d\x0e\x04\x16\x04\x14\x7c\xf1\x3c\x4f\x76\x8f\x47\x33\xa2\xff\xe2\xe2\x59\x34\x6b\x90\xcf\xb4\x74\xa8\x30\x1f\x06\x03\x55\x1d\x23\x04\x18\x30\x16\x80\x14\xac\x61\xeb\x22\x80\x62\x59\x08\x3e\x96\xc8\xd1\x7f\xce\x74\x5c\x02\xaf\x3c\x99\x30\x0a\x06\x08\x2a\x81\x1c\xcf\x55\x01\x83\x75\x03\x49\x00\x30\x46\x02\x21\x00\xe2\x13\x18\x45\x07\x9c\x82\xd4\xa4\xb0\x9b\x49\x90\xb2\x1b\xc4\xe2\x81\x89\x9b\x83\xb2\x26\xc9\x91\x6d\x5c\x5f\xee\x12\x13\x9f\x02\x21\x00\xe7\xd3\xe7\x11\x56\x1a\x7a\x0b\xe9\x23\x92\xed\x9f\x94\xf6\x3c\xa2\xaa\x89\x9d\x90\x39\x61\x1f\x44\x72\x48\x8b\xf1\x45\x65\xea" > text.bin
$ echo -n -e "\x30\x45\x02\x21\x00\x8f\xd2\x4c\xaa\x07\xd5\x06\xeb\x6b\x88\xeb\xd5\x85\x28\x39\xe1\x27\xe8\x75\x73\x87\x47\xa8\xd2\xc3\x56\x15\x0e\x4b\x95\xc6\xf2\x02\x20\x14\xa9\xf5\xae\xa1\x18\x00\x42\x76\xfb\xd8\x43\x7b\x0f\x6e\x5d\xb8\x4d\x13\x8b\x05\x82\x36\xf7\xd6\x65\x6f\x3d\xed\xef\xd7\x40" > sign.bin
$ cat left_sign_pub.pem
-----BEGIN PUBLIC KEY-----
MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAELWF+dNVYbd4j0kkPvUaOMPEdAS1Q
qPOSzRhJsQsWfpoGYffjoqAO5+xHGO2Te0qyxQqg00HRXkCVdDs4UK9tPA==
-----END PUBLIC KEY-----
$ gmssl sm2verify -pubkey left_sign_pub.pem -sig sign.bin -in text.bin
verify : success
~~~

### 第⼀阶段响应⽅的验证

#### 密钥

~~~shell
$ cat right_pri.pem
-----BEGIN SM2 PARAMETERS-----
BggqgRzPVQGCLQ==
-----END SM2 PARAMETERS-----
-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqBHM9VAYItBG0wawIBAQQguz0M4/6qUhgHAxuG
WI2NPtNciIwmYAN4AUDoBEka1tehRANCAAQpIN3pNIBB3oZ+SaXKoZNtMkH5t5y1
3MXG1Zsx+NiEZ7BbOFBbEB99vyQry6c9rzlM8IedPw6OwIc58dsA+ncM
-----END PRIVATE KEY-----
$ cat right_pub.pem
-----BEGIN PUBLIC KEY-----
MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAEKSDd6TSAQd6GfkmlyqGTbTJB+bec
tdzFxtWbMfjYhGewWzhQWxAffb8kK8unPa85TPCHnT8OjsCHOfHbAPp3DA==
-----END PUBLIC KEY-----
~~~

#### 计算SKr

~~~ shell
$ echo -ne "\x30\x79\x02\x21\x00\xe2\xfe\xe5\xb1\x43\x99\x37\x01\x4b\x7a\xd1\xa5\x85\xf4\xa6\x29\x10\x78\x7a\x7c\x88\x58\x84\xc1\x37\x0c\xd9\xfb\x8d\xad\xd1\x2c\x02\x20\x1c\x2f\x5a\xb9\xba\x02\xbc\x9d\x9c\x21\xcf\x18\xaf\xaa\x6b\x64\xf0\xb0\xa7\x33\xbd\x73\x05\x08\xd6\x56\x7f\x9f\xaa\xc7\x22\xaa\x04\x20\x00\x37\x6a\xa4\x66\x46\xd9\x05\x77\xb5\xab\x01\x70\xf9\x70\x43\x35\x6a\xce\xf8\x35\x04\xb8\xa4\xb9\xae\x15\x9a\x0e\x83\x4f\xc3\x04\x10\x01\x73\x4e\x92\x2f\xa8\xc8\x8a\xd6\x81\x4c\x59\x26\x4e\x9f\x21" > skr_enc.bin
$ openssl pkeyutl -decrypt -inkey right_pri.pem -in skr_enc.bin -out skr_dec.txt
$ od -tc -tx1 skr_dec.txt
0000000 223   u   C 201   &   _ 353 317 002   Z   l  \r   S 253 366 323
         93  75  43  81  26  5f  eb  cf  02  5a  6c  0d  53  ab  f6  d3
0000020
~~~

#### 计算Nr

~~~ shell
$ echo -ne "\xa4\x69\xaa\x4b\x73\x74\xd3\x32\x62\xe7\x6b\x20\xed\x2f\x65\xe6\xcc\xbd\x57\x99\x63\x0f\x7f\x8e\x68\x32\x0b\x2f\x12\x1e\x0a\x26" > nr_enc.bin
$ echo -ne "\x93\x75\x43\x81\x26\x5f\xeb\xcf\x02\x5a\x6c\x0d\x53\xab\xf6\xd3" > nr_key.bin
$ echo -ne "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" > nr_iv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 nr_key.bin) -iv $(xxd -p -c 32 nr_iv.bin) -in nr_enc.bin -out nr_dec.bin
$ od -tc -tx1 nr_dec.bin
0000000  \t 206   d 315   ,   F 277 274 214   _   ] 313 205   n   d 201
         09  86  64  cd  2c  46  bf  bc  8c  5f  5d  cb  85  6e  64  81
0000020  \0
         00
0000021
~~~

#### 计算IDr

~~~ SHELL
$ echo -ne "\x07\x1d\x40\x6e\xe8\x4d\x67\x6c\x28\x37\xba\x45\x49\x0b\x65\x0b\x27\xf6\x64\xaa\x7a\x73\x2a\xef\x59\x9c\x69\xd0\x6b\x25\xfd\x9b\xe2\xe7\xf4\xf1\x1d\x53\x06\xaa\x2c\xed\x37\x0b\x69\x58\xa6\xb4\xa9\xc9\x1b\x3d\xdb\x2f\xb6\xf6\x16\x73\xd8\x97\xfd\xf1\x2f\x73\x79\x66\x43\x99\x2e\x7c\xc9\xd9\x96\xca\xc9\xdd\xaa\x57\x1b\x2e\xc8\x5a\x68\x15\x0f\xad\x37\x5d\x6e\x94\xb6\x2c\x28\xdf\xcd\x8d" > idr.bin
$ echo -ne "\xcc\xbd\x57\x99\x63\x0f\x7f\x8e\x68\x32\x0b\x2f\x12\x1e\x0a\x26" > idr_iv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 nr_key.bin) -iv $(xxd -p -c 32 idr_iv.bin) -in idr.bin -out idr_dec.bin
$ od -tx1 idr_dec.bin
0000000 09 00 00 00 30 4a 31 0b 30 09 06 03 55 04 06 13
0000020 02 41 41 31 0b 30 09 06 03 55 04 08 13 02 42 42
0000040 31 0b 30 09 06 03 55 04 0a 13 02 43 43 31 0b 30
0000060 09 06 03 55 04 0b 13 02 44 44 31 14 30 12 06 03
0000100 55 04 03 13 0b 73 65 72 76 65 72 20 73 69 67 6e
0000120 00
0000121
~~~

#### 签名验证

~~~shell
$ echo -n -e "\x93\x75\x43\x81\x26\x5f\xeb\xcf\x02\x5a\x6c\x0d\x53\xab\xf6\xd3\x09\x86\x64\xcd\x2c\x46\xbf\xbc\x8c\x5f\x5d\xcb\x85\x6e\x64\x81\x09\x00\x00\x00\x30\x4a\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x13\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x13\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x13\x02\x44\x44\x31\x14\x30\x12\x06\x03\x55\x04\x03\x13\x0b\x73\x65\x72\x76\x65\x72\x20\x73\x69\x67\x6e\x05\x30\x82\x01\xeb\x30\x82\x01\x92\xa0\x03\x02\x01\x02\x02\x14\x68\xd8\x92\xe9\x63\xac\xa0\x45\x62\x0e\x79\x9d\x6f\xc3\x1d\x93\x74\x33\xe5\x7c\x30\x0a\x06\x08\x2a\x81\x1c\xcf\x55\x01\x83\x75\x30\x45\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x0c\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x0c\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x0c\x02\x44\x44\x31\x0f\x30\x0d\x06\x03\x55\x04\x03\x0c\x06\x73\x75\x62\x20\x63\x61\x30\x20\x17\x0d\x32\x33\x30\x32\x32\x32\x30\x32\x33\x30\x31\x34\x5a\x18\x0f\x32\x31\x32\x33\x30\x31\x32\x39\x30\x32\x33\x30\x31\x34\x5a\x30\x49\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x0c\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x0c\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x0c\x02\x44\x44\x31\x13\x30\x11\x06\x03\x55\x04\x03\x0c\x0a\x73\x65\x72\x76\x65\x72\x20\x65\x6e\x63\x30\x59\x30\x13\x06\x07\x2a\x86\x48\xce\x3d\x02\x01\x06\x08\x2a\x81\x1c\xcf\x55\x01\x82\x2d\x03\x42\x00\x04\x7d\xbe\xa5\x45\x43\x45\x81\x72\xbd\x3b\x68\x8e\x50\x9c\x2d\xf5\x45\x86\xac\xe0\x0b\x58\xec\x94\x14\x99\xf9\x4a\x50\xa5\x8c\x67\x5d\x6f\x9a\xda\xff\x08\x9e\x81\x37\xa7\x63\x43\xac\xd2\xf3\x5c\xa3\x0a\x8a\x5c\xcf\x81\xb7\xcd\xce\x52\x66\xa0\x16\xb9\xe3\x64\xa3\x5a\x30\x58\x30\x09\x06\x03\x55\x1d\x13\x04\x02\x30\x00\x30\x0b\x06\x03\x55\x1d\x0f\x04\x04\x03\x02\x03\x38\x30\x1d\x06\x03\x55\x1d\x0e\x04\x16\x04\x14\x67\xa5\xad\xd5\x94\x76\xe0\x5a\x9c\x5e\x56\xb8\x86\x0f\xf1\x3b\x28\xee\xec\x54\x30\x1f\x06\x03\x55\x1d\x23\x04\x18\x30\x16\x80\x14\xac\x61\xeb\x22\x80\x62\x59\x08\x3e\x96\xc8\xd1\x7f\xce\x74\x5c\x02\xaf\x3c\x99\x30\x0a\x06\x08\x2a\x81\x1c\xcf\x55\x01\x83\x75\x03\x47\x00\x30\x44\x02\x20\x47\x59\x35\x79\xc4\xad\xec\x8d\xb7\xdf\x98\xc4\xaa\xe1\x66\x1c\x11\x39\xa5\xef\x12\x93\xf2\x2a\x3a\xa4\x12\xd0\x9b\xec\xd6\xe6\x02\x20\x6e\x57\x30\x1d\x17\x79\x46\x95\x6f\xd3\x9c\xb5\xac\x60\x39\x02\xcd\x17\xc7\x51\x7e\xd8\x94\x1e\xcc\x98\x5e\xa7\xdb\x69\x58\xc8" > text2.bin
$ echo -n -e "\x30\x46\x02\x21\x00\xc8\xac\x03\x6f\xbc\xe2\x8f\xf4\xe7\xf5\x36\x6c\x70\x4e\x40\x5b\x23\x75\x3b\x8c\xa9\x5a\x43\x19\xb8\x65\x7e\xa1\xfb\x46\x53\x4e\x02\x21\x00\xf1\x4e\xeb\x88\x58\x61\x4a\x62\x40\x9a\xf9\xaa\x10\x37\xe2\xb4\xb4\x2b\x15\x5e\x93\x1b\x35\x9c\xd7\x92\x18\x9c\xa9\x0e\x09\xd4" > sign2.bin
$ cat right_sign_pub.pem
-----BEGIN PUBLIC KEY-----
MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAEBb/67sQGyPP1gKbjnFKEdsDfK2EG
XUp09HavD7ZokPiWrMSyHYsDbRPxe9TTgjSQi+23f44+rocGVPxvqASNDA==
-----END PUBLIC KEY-----
$ gmssl sm2verify -pubkey right_sign_pub.pem -sig sign2.bin -in text2.bin
verify : success
~~~

### 第一阶段密钥验证

#### 计算HASH(Ni||Nr)

~~~ shell
echo -n -e "\x45\x0b\xe9\x0d\x63\x7a\x4c\x71\x4d\x12\x9d\x13\xe1\x56\x42\x37\x09\x86\x64\xcd\x2c\x46\xbf\xbc\x8c\x5f\x5d\xcb\x85\x6e\x64\x81" | gmssl sm3
83fddf2b5dc8bd853c343ee68f780cfaf2e37fdde3998da2c76a4b368816e972
~~~

#### 计算SKEYID=PRF(HASH(Ni||Nr),CKY-I|CKY-R)

~~~ python
import hmac
key = b"\x83\xfd\xdf\x2b\x5d\xc8\xbd\x85\x3c\x34\x3e\xe6\x8f\x78\x0c\xfa\xf2\xe3\x7f\xdd\xe3\x99\x8d\xa2\xc7\x6a\x4b\x36\x88\x16\xe9\x72"
data = b"\xa8\x9a\x46\x62\xa4\xd1\xca\xd0\x49\xa2\xeb\x29\xcf\x6d\x65\xdb"
hmac_value = hmac.new(key, data, digestmod="sm3").hexdigest()
print(hmac_value)
~~~

计算得到SKEYID值为

~~~
af75db413c0babf64d866f08b53432ce027c59a975a30b284b31236c0689113e
~~~

#### 计算 SKEYID_d = PRF(SKEYID, CKY-I|CKY-R|0)

~~~ python
import hmac
key = b"\xaf\x75\xdb\x41\x3c\x0b\xab\xf6\x4d\x86\x6f\x08\xb5\x34\x32\xce\x02\x7c\x59\xa9\x75\xa3\x0b\x28\x4b\x31\x23\x6c\x06\x89\x11\x3e"
data = b"\xa8\x9a\x46\x62\xa4\xd1\xca\xd0\x49\xa2\xeb\x29\xcf\x6d\x65\xdb\x00"
hmac_value = hmac.new(key, data, digestmod="sm3").hexdigest()
print(hmac_value)
~~~

~~~
d07385874bd72fa3ec6d42714e643a94de6644d24f2f50239892f8ef478293e7
~~~

#### 计算SKEYID_a = PRF(SKEYID, SKEYID_d|CKY-I|CKY-R|1)

~~~ python
import hmac
key = b"\xaf\x75\xdb\x41\x3c\x0b\xab\xf6\x4d\x86\x6f\x08\xb5\x34\x32\xce\x02\x7c\x59\xa9\x75\xa3\x0b\x28\x4b\x31\x23\x6c\x06\x89\x11\x3e"
data = b"\xd0\x73\x85\x87\x4b\xd7\x2f\xa3\xec\x6d\x42\x71\x4e\x64\x3a\x94\xde\x66\x44\xd2\x4f\x2f\x50\x23\x98\x92\xf8\xef\x47\x82\x93\xe7\xa8\x9a\x46\x62\xa4\xd1\xca\xd0\x49\xa2\xeb\x29\xcf\x6d\x65\xdb\x01"
hmac_value = hmac.new(key, data, digestmod="sm3").hexdigest()
print(hmac_value)
~~~

~~~
51b531818c073c1b72ca8e9a883e6b19755604445abedf57df176d575f4320fe
~~~

#### 计算SKEYID_e = PRF(SKEYID, SKEYID_a|CKY-I|CKY-R|2)

~~~ python
import hmac
key = b"\xaf\x75\xdb\x41\x3c\x0b\xab\xf6\x4d\x86\x6f\x08\xb5\x34\x32\xce\x02\x7c\x59\xa9\x75\xa3\x0b\x28\x4b\x31\x23\x6c\x06\x89\x11\x3e"
data = b"\x51\xb5\x31\x81\x8c\x07\x3c\x1b\x72\xca\x8e\x9a\x88\x3e\x6b\x19\x75\x56\x04\x44\x5a\xbe\xdf\x57\xdf\x17\x6d\x57\x5f\x43\x20\xfe\xa8\x9a\x46\x62\xa4\xd1\xca\xd0\x49\xa2\xeb\x29\xcf\x6d\x65\xdb\x02"
hmac_value = hmac.new(key, data, digestmod="sm3").hexdigest()
print(hmac_value)
~~~

~~~
f60661271d29c5093894dacdacf5378c13aeea3d52b2be0ce06ad87edbc9f7d1
~~~

#### 计算hash(SKi||SKr)

~~~ shell
echo -n -e "\xe6\xb7\x48\x13\x21\x3b\xfe\x47\x59\xc2\x02\x25\xad\xe2\x67\x8e\x93\x75\x43\x81\x26\x5f\xeb\xcf\x02\x5a\x6c\x0d\x53\xab\xf6\xd3" | gmssl sm3
de788aa1e41303baf97136e86f82f2fc05fd904df03879c49c1e1a9a868b0e1a
~~~

#### HAHSi密⽂及解密

~~~ shell
$ echo -ne "\xc6\x0c\x2e\x76\x89\xfa\x15\x19\x25\x6e\xc6\x90\xbb\xfb\x7d\x63\x80\xa5\x2d\xe3\xd5\x1c\xe8\xfb\x1a\xc5\x92\x3a\x84\xce\xac\x86\xb9\x58\xbe\x5f\xa7\x42\x77\xfc\x91\xb3\xbf\xd3\xd1\xcb\xf7\xe0\x67\xc2\xc4\xbf\xa4\xd6\x54\xb0\xea\x42\x33\xe7\x9e\xe9\xc6\x2b" > hahsi_enc.bin
$ echo -ne "\xf6\x06\x61\x27\x1d\x29\xc5\x09\x38\x94\xda\xcd\xac\xf5\x37\x8c" > hahsi_key.bin
$ echo -ne "\xde\x78\x8a\xa1\xe4\x13\x03\xba\xf9\x71\x36\xe8\x6f\x82\xf2\xfc" > hahsi_iv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 hahsi_key.bin) -iv $(xxd -p -c 32 hahsi_iv.bin) -in hahsi_enc.bin -out hahsi_dec.bin
$ od -tx1 hahsi_dec.bin
0000000 00 00 00 24 58 55 a8 23 83 91 1a ca ce 23 7a 72
0000020 d2 c6 42 7a a1 8d 55 2f c4 d8 0d 13 28 81 04 a7
0000040 f9 da 2f 3c 00 00 00 00 00 00 00 00 00 00 00 00
0000060
~~~

#### 计算HASHi=PRF(SKEYID,CKY-I|CKY-R|SAi_b|IDi_b)

~~~ python
import hmac
key = b"\xaf\x75\xdb\x41\x3c\x0b\xab\xf6\x4d\x86\x6f\x08\xb5\x34\x32\xce\x02\x7c\x59\xa9\x75\xa3\x0b\x28\x4b\x31\x23\x6c\x06\x89\x11\x3e"
data = b"\xa8\x9a\x46\x62\xa4\xd1\xca\xd0\x49\xa2\xeb\x29\xcf\x6d\x65\xdb\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x28\x00\x01\x00\x01\x00\x00\x00\x20\x01\x01\x00\x00\x80\x01\x00\x7f\x80\x02\x00\x14\x80\x03\x00\x0a\x80\x14\x00\x02\x80\x0b\x00\x01\x80\x0c\x3d\xe0\x09\x00\x00\x00\x30\x4a\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x13\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x13\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x13\x02\x44\x44\x31\x14\x30\x12\x06\x03\x55\x04\x03\x13\x0b\x63\x6c\x69\x65\x6e\x74\x20\x73\x69\x67\x6e"
hmac_value = hmac.new(key, data, digestmod="sm3").hexdigest()
print(hmac_value)
~~~

~~~ shell
5855a82383911acace237a72d2c6427aa18d552fc4d80d13288104a7f9da2f3c
~~~

#### HASHr密⽂及解密

~~~ shell
$ echo -n -e "\xdd\x55\xad\x19\x83\x22\x11\xa7\x90\x95\x50\xc3\x47\x26\x15\xc5\x5f\xed\xdb\x94\x9b\x5e\xe0\x1f\x9c\xfe\x6d\x9e\x22\x8e\x3a\x1d\xd9\x20\x48\x95\x3a\x17\x28\x91\xb1\x94\x01\x2f\x8d\xb5\xf7\xb0\x00\x84\xab\xbb\xce\x85\x8d\x22\xd3\x9b\x41\x74\x8e\x00\xd5\xfe" > hashr_enc.bin
$ echo -n -e "\xf6\x06\x61\x27\x1d\x29\xc5\x09\x38\x94\xda\xcd\xac\xf5\x37\x8c" > hashr_key.bin
$ echo -n -e "\xb9\x58\xbe\x5f\xa7\x42\x77\xfc\x91\xb3\xbf\xd3\xd1\xcb\xf7\xe0" > hashr_iv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 hashr_key.bin) -iv $(xxd -p -c 32 hashr_iv.bin) -in hashr_enc.bin -out hashr_dec.bin
$ od -tx1 hashr_dec.bin
$ od -tx1 hashr_dec.bin
0000000 00 00 00 24 41 46 70 0c 99 9e b6 b4 ce 92 89 18
0000020 81 b8 ec 69 c0 13 bf 83 06 2b 88 53 72 f2 df dd
0000040 fa fe 4e a6 00 00 00 00 00 00 00 00 00 00 00 00
0000060
~~~

#### HASHr=PRF(SKEYID,CKY-R|CKY-I|SAr_b|IDr_b)

~~~ python
import hmac
key = b"\xaf\x75\xdb\x41\x3c\x0b\xab\xf6\x4d\x86\x6f\x08\xb5\x34\x32\xce\x02\x7c\x59\xa9\x75\xa3\x0b\x28\x4b\x31\x23\x6c\x06\x89\x11\x3e"
data = b"\x49\xa2\xeb\x29\xcf\x6d\x65\xdb\xa8\x9a\x46\x62\xa4\xd1\xca\xd0\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x28\x00\x01\x00\x01\x00\x00\x00\x20\x01\x01\x00\x00\x80\x01\x00\x7f\x80\x02\x00\x14\x80\x03\x00\x0a\x80\x14\x00\x02\x80\x0b\x00\x01\x80\x0c\x3d\xe0\x09\x00\x00\x00\x30\x4a\x31\x0b\x30\x09\x06\x03\x55\x04\x06\x13\x02\x41\x41\x31\x0b\x30\x09\x06\x03\x55\x04\x08\x13\x02\x42\x42\x31\x0b\x30\x09\x06\x03\x55\x04\x0a\x13\x02\x43\x43\x31\x0b\x30\x09\x06\x03\x55\x04\x0b\x13\x02\x44\x44\x31\x14\x30\x12\x06\x03\x55\x04\x03\x13\x0b\x73\x65\x72\x76\x65\x72\x20\x73\x69\x67\x6e"
hmac_value = hmac.new(key, data, digestmod="sm3").hexdigest()
print(hmac_value)
~~~

~~~ shell
4146700c999eb6b4ce92891881b8ec69c013bf83062b885372f2dfddfafe4ea6
~~~

### 第二阶段密钥验证

计算iv

~~~ shell
echo -e -n "\xd9\x20\x48\x95\x3a\x17\x28\x91\xb1\x94\x01\x2f\x8d\xb5\xf7\xb0\xcc\x2d\x22\x21" | gmssl sm3
56e6dfc945499ae8aca47a6ca9cf2ada005ac24e502d2ad621591efd5d57bdbe
~~~

~~~ shell
$ echo -n -e "\x04\x80\x34\x8d\x01\xd6\x63\x5a\x2c\x2a\x91\x2f\xbd\xb6\x77\xf0\xe7\x18\xca\x23\x9c\x17\x58\x31\x90\x69\xd7\x4e\xfc\x06\x01\xc4\xbd\xb8\x14\xf8\xd5\x57\x5a\xdd\x1a\xcc\x70\x75\x72\x32\x63\xa6\x52\x70\x54\x7f\x46\x43\x45\xb2\x92\x75\x3c\xd5\xc7\x59\xfd\xe4\xc9\x40\x48\xf5\xce\xd4\xb1\x61\x67\x9c\x75\xa3\xcb\x0f\xec\x2d\x80\xc2\x92\xdf\x8b\x6a\x56\x7b\x91\x6c\xb0\xcd\xb5\x7d\x30\x09\x7f\x84\x16\x30\xcf\xb8\x08\x1c\xc8\xb6\x5b\x0b\xe5\x4d\xcd\x45\xac\xef\x18\x45\x6a\x1d\xbb\x1b\x76\x4b\x4a\x41\x64\xb4\xff\xab\x0b\x36\x45\x56\xde\x52\xec\x11\x6c\x10\x14\x11\x29\x86\xfd\x82\x35\x9b\x20\x4f\x92\x80\x05\x04\x07\x2e\x29\x94\xaf\x77\x1b\x88\x49\x27\x54\x59\x0f\x6d\x0b\x25\xb2\xdc\x26\xca\x2c\xef\x83\xb2" > FirstPri.bin
$ echo -n -e "\xf6\x06\x61\x27\x1d\x29\xc5\x09\x38\x94\xda\xcd\xac\xf5\x37\x8c" > Firstkey.bin
$ echo -n -e "\x56\xe6\xdf\xc9\x45\x49\x9a\xe8\xac\xa4\x7a\x6c\xa9\xcf\x2a\xda" > Firstiv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 Firstkey.bin) -iv $(xxd -p -c 32 Firstiv.bin) -in FirstPri.bin -out Firstdec.bin
$ od -tx1 Firstdec.bin
0000000 01 00 00 24 0c 52 ab f2 be e8 33 7f 08 69 4e e2
0000020 2b 97 e4 57 1e f4 91 ef 5c 88 ed a0 4a 5f 4c 3f
0000040 c8 2c 03 d9 0a 00 00 3c 00 00 00 01 00 00 00 01
0000060 00 00 00 30 00 03 04 01 c5 15 ec d5 00 00 00 24
0000100 01 7f 00 00 80 05 00 14 80 04 00 01 80 01 00 01
0000120 80 02 17 34 80 01 00 02 00 02 00 04 00 08 64 70
0000140 05 00 00 14 4f db bc e1 78 50 46 b2 1f 1e b0 0a
0000160 fb ec 31 c4 05 00 00 10 04 00 00 00 ac 10 1d 00
0000200 ff ff ff 00 00 00 00 10 04 00 00 00 ac 10 1c 00
0000220 ff ff ff 00 00 00 00 00 00 00 00 00 00 00 00 00
0000240
~~~

~~~ shell
$ echo -n -e "\x49\x81\x3d\xfd\x83\xa4\xc3\xc3\xbf\x29\x50\x29\x09\x04\xfc\x42\x37\xc9\x0e\x5e\x45\xe4\x99\x1a\x60\x33\x6a\x91\xee\x68\x48\xde\x0c\xa5\x96\x4f\xbb\x5a\xf6\xf0\xaa\x60\x7e\xbc\xc8\x18\x8e\x97\x74\xa8\xac\x79\xf1\xf9\x3b\x1a\x72\x14\x06\x25\xc3\x58\x8e\xea\x7e\x1e\x4b\x13\x77\x83\xc9\x48\xe9\xbd\x7a\x06\x0f\x8d\x36\x82\x1b\x51\x98\xc7\xe3\xeb\x41\xa5\xad\x4e\x3f\x30\xac\xf9\x78\xf8\x09\x30\xe4\x7a\x79\xe3\xdd\xae\x43\xfb\x9d\x14\x63\xc6\xdb\xcb\x45\xad\x9d\x37\xea\xd1\xeb\x54\xfb\xcf\x39\x05\x8a\x9e\x9c\x39\xf7\xa9\xc4\x3c\x6c\x1a\xec\xc5\xa1\xa5\x85\x22\xab\xd5\x96\x09\x20\xf2\x02\x61\xbf\x78\xe3\x28\x47\xd2\xf8\x4e\x7f\x4c\xbd\xb2\x9a\x5e\x19\xc9\x06\x46\x2a\x6a\x12\xe3\x82\xfd\xdb\x47\x4c\x38" > SecondPri.bin
$ echo -n -e "\xf6\x06\x61\x27\x1d\x29\xc5\x09\x38\x94\xda\xcd\xac\xf5\x37\x8c" > Secondkey.bin
$ echo -n -e "\x35\x9b\x20\x4f\x92\x80\x05\x04\x07\x2e\x29\x94\xaf\x77\x1b\x88" > Secondiv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 Secondkey.bin) -iv $(xxd -p -c 32 Secondiv.bin) -in SecondPri.bin -out Seconddec.bin
$ od -tx1 Seconddec.bin
0000000 01 00 00 24 d9 0a ad 57 4e 56 1b 98 e0 fd 91 36
0000020 cc 21 7e 7e 4c 83 00 cf 8c 38 29 aa 2c 65 0e 8d
0000040 e7 3e 7c 21 0a 00 00 3c 00 00 00 01 00 00 00 01
0000060 00 00 00 30 00 03 04 01 c7 13 ad 06 00 00 00 24
0000100 01 7f 00 00 80 05 00 14 80 04 00 01 80 01 00 01
0000120 80 02 17 34 80 01 00 02 00 02 00 04 00 08 64 70
0000140 05 00 00 14 10 6b ca a9 25 dc 5b 6d 99 4e fc 88
0000160 36 9d 60 59 05 00 00 10 04 00 00 00 ac 10 1d 00
0000200 ff ff ff 00 00 00 00 10 04 00 00 00 ac 10 1c 00
0000220 ff ff ff 00 00 00 00 00 00 00 00 00 00 00 00 00
0000240
~~~

~~~ shell
$ echo -n -e "\x60\x17\xca\x49\x20\x79\xd1\x91\x0a\x3c\xfb\xc3\x0a\xaa\x2d\x66\xc6\xa0\x03\xb9\x02\x79\x9a\xf2\x71\xb6\xd8\x7d\x36\x55\x50\x31\xb2\xd9\xd1\x52\xde\x3a\x71\x19\x63\x07\x2e\xfa\x0d\x2d\x80\x12\x75\x79\xef\x62\x53\x32\xf1\xc9\xd4\x3c\xcc\x7e\xbb\x0a\xdd\xf5" > ThirdPri.bin
$ echo -n -e "\xf6\x06\x61\x27\x1d\x29\xc5\x09\x38\x94\xda\xcd\xac\xf5\x37\x8c" > Thirdkey.bin
$ echo -n -e "\x20\xf2\x02\x61\xbf\x78\xe3\x28\x47\xd2\xf8\x4e\x7f\x4c\xbd\xb2" > Thirdiv.bin
$ gmssl sm4_cbc -decrypt -key $(xxd -p -c 32 Thirdkey.bin) -iv $(xxd -p -c 32 Thirdiv.bin) -in ThirdPri.bin -out Thirddec.bin
$ od -tx1 Thirddec.bin
0000000 00 00 00 24 c6 12 5d 6c c7 9a 13 a4 fa 8f 08 06
0000020 e7 fe d7 2e c4 28 0f 5a 64 b5 a0 a6 77 89 bd 8e
0000040 69 80 36 c9 00 00 00 00 00 00 00 00 00 00 00 00
0000060
~~~

