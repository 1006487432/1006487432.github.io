---
title: 牛客周赛Round49
subtitle:
date: 2024-07-06T14:21:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round49
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

## 嘤嘤不想做计几喵
签到
~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a, b;
    cin >> a >> b;
    cout << (a - b) - b * 10;
    return 0;
}
~~~
## 嘤嘤不想打怪兽喵
签到
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll h;
    cin >> h;
    ll ans = 0;
    ll cnt = 1;
    while(h){
        ans += cnt;
        cnt <<= 1;
        h >>= 1;
    }
    cout << ans;
    return 0;
}
~~~
## 嘤嘤不想买东西喵
线性DP
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100010], b[100010];
int main(){
    ll n, x;
    cin >> n >> x;
    for(int i = 1; i <= n; i++)    cin >> a[i];
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        b[i] = max(b[i - 1] + a[i] - x, a[i] - x);
        ans = max(ans, b[i]);
    }
    cout << ans;
    return 0;
}
~~~
## 嘤嘤不想求异或喵
异或和的性质
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
long long sumXor(long long x) {
        if (x % 4 == 0) {
            return x;
        }
        if (x % 4 == 1) {
            return 1;
        }
        if (x % 4 == 2) {
            return x + 1;
        }
        return 0;
}

int main(){
    ll t;
    cin >> t;
    while(t--){
        ll l, r;
        cin >> l >> r;
        cout << (sumXor(l - 1) ^ sumXor(r)) << '\n';
    }
    return 0;
}
~~~
## 嘤嘤不想解方程喵
将y代入式子得到一个二次方程，判断是否有解即可。

注意会爆long long

~~~ c++
#include<bits/stdc++.h>
using namespace std;
//0 1 2
typedef long long ll;
ll a1, b1, c1, a2, b2, c2;
int main(){
    ll t;
    cin >> t;
    while(t--){
        cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
        __int128 a = a1 * b2;
        __int128 b = b1 * b2 + a2;
        __int128 c = c1*b2+c2;
        if(a == 0){
            if(b == 0){
                if(c == 0){
                    cout << "INF" << endl;
                }else{
                    cout << "0" << endl;
                }
            }else{
                cout << "1" << endl;
            }
        }else{
            __int128 deta = b * b - 4 * a * c;
            if(deta > 0)    cout << "2" << endl;
            else if(deta == 0)    cou    t << "1" << endl;
            else cout << "0" << endl;
        }
    }
    return 0;
}
~~~