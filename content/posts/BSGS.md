---
title: BSGS
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
  - 算法
categories:
  - 算法和数据结构
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

# BSGS

2023-08-17 

 | [算法](https://blog.he-zhan.xyz/categories/算法)

 

 | 2 reads

 字数:559

**BSGS**算法(BABY-STEP GIANT-STEP)，又称大步小步法，通常用于求解**高阶线性同余方程**如：ax ≡ b (mod p)𝑎𝑥 ≡ 𝑏 (𝑚𝑜𝑑 𝑝)。根据p是否为质数，有扩展BSGS算法和BSGS算法。 BSGS通过**欧拉定理**及其拓展确定x的范围，再通过**暴力枚举**求解x。其本质是**分块思想**。

**欧拉定理**：

- 具体内容： aφ(m) ≡ 1( mod m)𝑎φ(𝑚) ≡ 1( 𝑚𝑜𝑑 𝑚) 。
- 其中 φ(m)φ(𝑚) 是 m 的**欧拉函数**，当m为质数p时，欧拉定理退化为**费马小定理**：a(p−1) ≡ 1( mod p)𝑎(𝑝−1) ≡ 1( 𝑚𝑜𝑑 𝑝)。(质数p的欧拉函数=p-1)
- 重要推论：当**a与m互质**时，有ab = ab mod φ(m)𝑎𝑏 = 𝑎𝑏 𝑚𝑜𝑑 φ(𝑚),利用这个推论，即使b比较大，也能轻松计算ab mod m𝑎𝑏 𝑚𝑜𝑑 𝑚的值
- 当a与m不互质时，采用拓展欧拉定理：若b ≥ φ(m)𝑏 ≥ φ(𝑚),则ab ≡ ab mod φ(m) + φ(m) (mod m)𝑎𝑏 ≡ 𝑎𝑏 𝑚𝑜𝑑 φ(𝑚) + φ(𝑚) (𝑚𝑜𝑑 𝑚),b < φ(m)𝑏 < φ(𝑚)时直接用快速幂计算

求解ax ≡ b (mod p)𝑎𝑥 ≡ 𝑏 (𝑚𝑜𝑑 𝑝)问题，当**P为质数**时， 由**欧拉定理的推论**可知ab = ab mod φ(p) (mod p)𝑎𝑏 = 𝑎𝑏 𝑚𝑜𝑑 φ(𝑝) (𝑚𝑜𝑑 𝑝)，ax𝑎𝑥在模P意义下的**最小循环节**为φ(p)φ(𝑝),因为p为质数所以φ(p) ＝ p−1φ(𝑝) ＝ 𝑝−1,故在[0,p][0,𝑝]之间，必能找到最小整数x。

采取暴力枚举的方法求p：

- 假设x = im - j,则有aim ≡ b∗aj ( mod p)𝑎𝑖𝑚 ≡ 𝑏∗𝑎𝑗 ( 𝑚𝑜𝑑 𝑝),其中m = ceil(sqrt(p))为根号P向上取整,这时只需要直接枚举左右两边的情况;
- 我们可以采用哈希表存储
  - 枚举右边时，当键b∗aj𝑏∗𝑎𝑗重复出现时，令对应的值等于**较大的j**；
  - 由于要求最小非负解x，则令i从1开始枚举，当aim𝑎𝑖𝑚的值在哈希表中重复出现时，说明找了到了解，并且这个解是满足条件的最小非负解，因为保证了i尽可能小，j尽可能大。 把区间分为√p𝑝块,每块长√p𝑝,根据i的值im分别对应了√p𝑝个小区间，i递增即检查每个小区间内有没有符合条件的解。i的一小步，在区间上跨越了一大步，所以叫做 BABY-STEP GIANT-STEP算法。其本质是**分块思想**。

```cpp
typedef long long ll;
ll fpow(ll a, ll b, ll p)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)	res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}
ll bsgs(ll a, ll b, ll p)
{
	a %= p, b %= p;
	if(a == 0) return b == 0 ? 1 : -1; 
	if(b == 1) return 0;
	ll m = ceil(sqrt(p)), inv = fpow(a, m, p);
	unordered_map<ll, ll> mp;
	mp[b] = 0;
	ll tmp = inv;
	for (int i = 1, e = b; i < m; i++)
	{
		e = e * a % p;
		mp[e] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		if (mp.find(inv) != mp.end())
		{
			return i * m - mp[inv];
		}
		inv = inv * tmp % p;
	}
	return -1;
}
```

当p为非质数时，使用扩展BSGS算法

```cpp
typedef long long ll;
ll fpow(ll a, ll b, ll p)//求快速幂
{
	ll res = 1;
	while (b)
	{
		if (b & 1)	res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}
ll bsgs(ll a, ll b, ll p)//bsgs
{
	a %= p, b %= p;
	if (a == 0) return b == 0 ? 1 : -1;
	if (b == 1) return 0;
	ll m = ceil(sqrt(p)), t = fpow(a, m, p);
	unordered_map<ll, ll> mp;
	mp[b] = 0;
	ll tmp = t;
	for (int i = 1, e = b; i < m; i++)
	{
		e = e * a % p;
		mp[e] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		if (mp.find(t) != mp.end())
		{
			return (i * m - mp[t] + p) % p;
		}
		t = t * tmp % p;
	}
	return -1;
}
ll gcd(ll a, ll b)//欧几里得
{
	return b ? gcd(b, a % b) : a;
}
ll exgcd(ll a, ll b, ll& x, ll& y)//扩欧求逆元
{
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
ll inv(ll a, ll b)求逆元
{
	ll x, y;
	exgcd(a, b, x, y);
	return (x % b + b) % b;
}
ll exbsgs(ll a, ll b, ll p)//扩展bsgs
{
	if (b == 1 || p == 1)return 0;     
	ll g = gcd(a, p), k = 0, na = 1;
	while (g > 1)
	{
		if (b % g != 0)return -1;    
		k++; b /= g; p /= g; na = na * (a / g) % p;
		if (na == b)return k;   
		g = gcd(a, p);
	}
	ll f = bsgs(a, b * inv(na, p) % p, p);
	if (f == -1)return -1;
	return f + k;
}
```
