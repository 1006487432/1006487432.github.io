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

#### 共享素数
gcd

n1和n2存在相同的素数q，通过gcd求出q，然后得到p1、p2

~~~ python
from Crypto.Util.number import *
from gmpy2 import *
from gmpy2 import gmpy2

# flag = b'NSSCTF{******}'
#
# p1 = getPrime(512)
# q = getPrime(512)
# p2 = getPrime(512)
#
# n1 = p1*q
# n2 = p2*q
#
# e = 65537
#
# m = bytes_to_long(flag)
# c1 = pow(m, e, n1)
# c2 = pow(m, e, n2)
#
# print(f'n1 = {n1}')
# print(f'n2 = {n2}')
# print(f'e = {e}')
# print(f'c1 = {c1}')
# print(f'c2 = {c2}')

n1 = 143348646254804947818644803938588739009782265465565896704788366218178523508874903492905378927641178487821742289009401873633609987818871281146199303052141439575438691652893995423962176259643151111739185844059243400387734688275416379337335777994990138009973618431459431410429980866760075387393812720247541406893
n2 = 138110854441015362783564250048191029327770295545362614687087481715680856350219966472039006526758450117969049316234863489558254565946242898336924686721846675826468588471046162610143748100096038583426519355288325214365299329095841907207926280081868726568947436076663762493891291276498567791697978693639037765169
e = 65537
c1 = 54957154834913405861345262613986460384513988240935244315981524013378872930144117440787175357956479768211180412158274730449811947349624843965933828130932856052315165316154486515277625404352272475136003785605985702495858150662789554694910771308456687676791434476722168247882078861234982509648037033827107552029
c2 = 122221335585005390437769701090707585780333874638519916373585594040154234166935881089609641995190534396533473702495240511296379249872039728112248708182969185010334637138777948970821974238214641235158623707766980447918480715835847907220219601467702961667091318910582445444058108454023108157805147341928089334736

q = gcd(n1, n2)
p1 = n1 // q
p2 = n2 // q
d1 = gmpy2.invert(e, (p1 - 1) * (q - 1))
d2 = gmpy2.invert(e, (p2 - 1) * (q - 1))
print(long_to_bytes(pow(c1, d1,n1)))

~~~

#### 欧拉定理

$$
n=p_1^{k_1}p_2^{k_2}...p_r^{k_r}\\
\varphi(n)=\prod_{i=1}^{r}p_i^{k_i - 1}(p_i - 1)
$$

#### 小明文攻击

~~~ python
import gmpy2
from Crypto.Util.number import *
from gmpy2 import *

# flag = b'NSSCTF{******}'
#
# p = getPrime(512)
# q = getPrime(512)
#
# e = 65537
# while True:
#     r = 2*getPrime(100)*e+1
#     if isPrime(r):
#         break
#
# n = p*q*r
#
# m = bytes_to_long(flag)
#
# c = pow(m, e, n)
#
# print(f'p = {p}')
# print(f'q = {q}')
# print(f'r = {r}')
# print(f'e = {e}')
# print(f'c = {c}')


p = 7478755670255767435237487693415479182290330775502792675052667363676831056436638619069277770540533350723045234676443621124912287506103439704868369839725279
q = 9232828888049557325429111621080998490274442347556398052322580869768941301413255711626092627273543579067597113958627672298942570149816938335701615759283713
r = 102909133680612532601801231903654039
e = 65537
c = 142893174944324070830219394465469685943669308818639857030565389839224452373848570577201378981080333784852764502832587008270072323948511579823852437852643609820245476634896477031076952735298279618952398460203032125853063235638358942643559551563899381032067185778629120272032518475352761100115057449043142848203976076694124978394099839339406197
n=p*q
phi = (p-1)*(q-1)
d = inverse(e, phi)
print(long_to_bytes(pow(c, d, p * q)))
~~~

本题不存在逆元，phi = (p - 1) *(q - 1) * 2 * r * e

phi是e的倍数，e对phi不存在逆元

当明文m较小时，若满足
$$
m\mod pq≡ m \mod n
$$
即m比p*q小，则可以自己计算n=p * q计算明文

总结：
满足以下情况时，可以不使用题中给的n=pqr计算公式，自己重新计算n，再进一步计算公私钥：
1.明文m比较简短
flag = b’NSSCTF{****** }’ + b’1’*100 不行
flag = b’NSSCTF{******}’ 可以
2.分析发现使用给定的n无法计算d，原因可能是d = inverse(e, phi)中e、phi不互素



#### [CryptoCTF 2021]DoRSA

两个模数

~~~ python
#!/usr/bin/env python3

from Crypto.Util.number import *
from math import gcd
from flag import FLAG

def keygen(nbit, dbit):
	assert 2*dbit < nbit
	while True:
		u, v = getRandomNBitInteger(dbit), getRandomNBitInteger(nbit // 2 - dbit)
		p = u * v + 1
		if isPrime(p):
			while True:
				x, y = getRandomNBitInteger(dbit), getRandomNBitInteger(nbit // 2 - dbit)
				q = u * y + 1
				r = x * y + 1
				if isPrime(q) and isPrime(r):
					while True:
						e = getRandomNBitInteger(dbit)
						if gcd(e, u * v * x * y) == 1:
							phi = (p - 1) * (r - 1)
							d = inverse(e, phi)
							k = (e * d - 1) // phi
							s = k * v + 1
							if isPrime(s):
								n_1, n_2 = p * r, q * s
								return (e, n_1, n_2)

def encrypt(msg, pubkey):
	e, n = pubkey
	return pow(msg, e, n)

nbit, dbit = 1024, 256

e, n_1, n_2 = keygen(nbit, dbit)

FLAG = int(FLAG.encode("utf-8").hex(), 16)

c_1 = encrypt(FLAG, (e, n_1))
c_2 = encrypt(FLAG, (e, n_2))

print('e =', e)
print('n_1 =', n_1)
print('n_2 =', n_2)

print('enc_1 =', c_1)
print('enc_2 =', c_2)


~~~

~~~ python
from Crypto.Util.number import *
from sage.all import *
from gmpy2 import iroot

e = 93546309251892226642049894791252717018125687269405277037147228107955818581561
n_1 = 36029694445217181240393229507657783589129565545215936055029374536597763899498239088343814109348783168014524786101104703066635008905663623795923908443470553241615761261684865762093341375627893251064284854550683090289244326428531870185742069661263695374185944997371146406463061296320874619629222702687248540071
n_2 = 29134539279166202870481433991757912690660276008269248696385264141132377632327390980628416297352239920763325399042209616477793917805265376055304289306413455729727703925501462290572634062308443398552450358737592917313872419229567573520052505381346160569747085965505651160232449527272950276802013654376796886259
enc_1 = 4813040476692112428960203236505134262932847510883271236506625270058300562795805807782456070685691385308836073520689109428865518252680199235110968732898751775587988437458034082901889466177544997152415874520654011643506344411457385571604433702808353149867689652828145581610443408094349456455069225005453663702
enc_2 = 2343495138227787186038297737188675404905958193034177306901338927852369293111504476511643406288086128052687530514221084370875813121224208277081997620232397406702129186720714924945365815390097094777447898550641598266559194167236350546060073098778187884380074317656022294673766005856076112637129916520217379601

f = continued_fraction(ZZ(n_2)/n_1)
for i in range(len(f)):
    k, x = f[:-1-i].value().numerator(), f[:-1-i].value().denominator()
    if len(bin(x))==258:
        break

phi = crt([0, ZZ(-1/Zmod(e)(k))], [x, e])
pq = (n_1 - phi + 1) % (x*e)
while pq**2 < 4*n_1:
    pq += x*e

p = (pq + iroot(pq**2 - 4*n_1, 2)[0])//2
q = n_1//p
print(long_to_bytes(pow(enc_1, inverse(e, (p-1)*(q-1)), n_1)))

#CCTF{__Lattice-Based_atT4cK_on_RSA_V4R1aN75!!!}
~~~



#### 素数分解

##### 网站

[factordb.com](https://factordb.com/) 256位p、q

##### 工具

Yafu 128位p、q