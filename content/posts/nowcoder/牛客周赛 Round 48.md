---
title: 牛客周赛Round48
subtitle:
date: 2024-07-07T21:11:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round48
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

## A.小红的整数自增

签到题

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    int sum = a + b + c;
    ans = max(3 * a, max(3 * b, 3 * c));
    cout << ans - sum;
    return 0;
}
~~~

## B.小红的伪回文子串（easy）

暴力即可

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int check(string tmp){
    int temp = 0;
    int len = tmp.size();
    for(int i = 0, j = len - 1; i < j; i++, j--)
        if(tmp[i] != tmp[j])    temp++;
    return temp;
}
int main(){
    string s;
    cin >> s;
    int ans = 0;
    int len = s.size();
    for(int i = 2; i <= len; i++){
        for(int j = 0; j < len - i + 1; j++){
            string t = s.substr(j, i);
            ans += check(t);
        }
    }
    cout << ans;
    return 0;
}
~~~

## C.小红的01串取反

从一端开始拟合最后看最后一个元素相不相同。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    vector<int> ans;
    for(int i = 0; i < n - 1; i++){
        if(a[i] != b[i]){
            a[i] = b[i];
            a[i + 1] = a[i + 1] == '1'?'0':'1';
            ans.push_back(i);
       }
    }
    if(a[n - 1] != b[n - 1]){
        cout << -1;
        return 0;
    }
    cout << ans.size() << '\n';    
    for(auto i : ans)
        cout << i + 1 << ' ' << i + 2 << '\n';
    return 0;
}
~~~

## D.小红的乘2除2

特判一下n=2的情况。

然后暴力跑出来第一次操作每个数/2后的陡峭值减少值(称为贡献）。

然后考虑操作2，对第i位进行操作2，则有四种情况：

1.第一次操作不发生在第i位和与之相邻的位置

2.第一次操作发生在第i位

3.第一次操作发生在第i+1位

4.第一次操作发生在第i-1位

对于后三种操作，这两次操作的总贡献是 第一次操作的贡献+ 第二次操作的贡献（让相应位置的数/2后计算）

对于第一种操作，总贡献是 第一次操作中其他位置的最大贡献（这三位之外的最值） + 第二次操作的贡献

那么再处理其他位置的最大贡献就可以了。当最大值的个数超过3的时候，直接全部都是最大值就行。

小于三的时候对相邻位和自己的第一次贡献中存在最大值的位置单独计算一遍其他位置的最大贡献就行，最多跑九遍。	

最后初始陡峭值减去总贡献的最大值就是答案。

~~~ C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100010];
ll tag[100010];
ll n;
ll mxx[100010];    
ll check(int i){
    ll tmp = a[i] * 2;
    ll t1 = abs(a[i] - a[i - 1]) + abs(a[i] - a[i + 1]);
    ll t2 = abs(tmp - a[i - 1]) + abs(tmp - a[i + 1]);
    ll ret = t1 - t2;
    ll mx = mxx[i];

    ret = ret + mx;
    for(ll j = -1; j <= 1; j++){
        ll a_1 = a[i - 1], a0 = a[i], a1 = a[i + 1];
        if(j == -1)    a_1 /= 2;
        if(j == 0) a0 /= 2;
        if(j == 1) a1 /= 2;
        tmp = a0 * 2;
        t1 = abs(a0 - a_1) + abs(a0 - a1);
        t2 = abs(tmp - a_1) + abs(tmp - a1);
        ret = max(ret,t1 - t2 + tag[i + j]);
    }
    return ret;
}
ll check2(ll i){
    ll tmp = a[i] * 2;
    ll t1 = abs(a[i] - a[i + 1]);
    ll t2 = abs(tmp - a[i + 1]);
    ll ret = t1 - t2;
    ll mx = mxx[i];
    ret = ret + mx;
    for(ll j = 0; j <= 1; j++){
        ll a0 = a[i], a1 = a[i + 1];
        if(j == 0) a0 /= 2;
        if(j == 1) a1 /= 2;
        tmp = a0 * 2;
        t1 = abs(a0 - a1);
        t2 = abs(tmp - a1);
        ret = max(ret,t1 - t2 + tag[i + j]);
    }
    return ret;
}
ll check3(ll i){
    ll tmp = a[i] * 2;
    ll t1 = abs(a[i] - a[i - 1]);
    ll t2 = abs(tmp - a[i - 1]);
    ll ret = t1 - t2;
    ll mx = mxx[i];    

    ret = ret + mx;
    for(ll j = -1; j <= 0; j++){
        ll a_1 = a[i - 1], a0 = a[i];
        if(j == -1)    a_1 /= 2;
        if(j == 0) a0 /= 2;
        tmp = a0 * 2;
        t1 = abs(a0 - a_1);
        t2 = abs(tmp - a_1);
        ret = max(ret,t1 - t2 + tag[i + j]);
    }
    return ret;
}
int main(){
    cin >> n;
    for(ll i = 1; i <= n; i++)    cin >> a[i];
    if(n == 2){
        ll ans = 1e18;
        for(ll i = 1; i <= 2; i++)
            for(ll j = 1; j <= 2; j++){
                ll a1 = a[1], a2 = a[2];
                if(i == 1) a1 /= 2;
                else a2 /= 2;
                if(j == 1) a1 *= 2;
                else a2 *= 2;
                ans = min(ans, abs(a1 - a2));
            }
        cout << ans;
        return 0;
    }
    ll ans = 0;
    for(ll i = 1; i < n; i++)    ans += abs(a[i] - a[i + 1]);
    tag[1] = abs(a[1] - a[2]) - abs(a[1] / 2 - a[2]);
    tag[n] = abs(a[n] - a[n - 1]) - abs(a[n] / 2 - a[n]);
    ll mx = 0;
    for(ll i = 2; i < n; i++){
        ll t1 = abs(a[i] - a[i - 1]) + abs(a[i] - a[i + 1]);
        ll t2 = abs(a[i] / 2 - a[i - 1]) + abs(a[i] / 2 - a[i + 1]);
        tag[i] = t1 - t2;
        mx = max(mx, tag[i]);
    }
    ll cnt = 0;
    for(ll i = 1; i <= n; i++)if(tag[i] == mx) cnt++;
    if(cnt > 3){
        for(ll i = 1; i <= n; i++) mxx[i] = mx;
    }else{
        for(ll i = 1; i <= n; i++){
            if(tag[i] == mx || tag[i - 1] == mx || tag[i + 1] == mx){
                for(ll j = 1; j <= n; j++){
                    if(abs(i - j) <= 1)    continue;
                    mxx[i] = max(mxx[i], tag[j]);
                }
            }else mxx[i] = mx;
        }
    }
    ll op1 = -1e18;
    for(ll i = 2; i < n; i++){
        op1 = max(op1, check(i));
        //cout << check(i) << '\n';
    }
    op1 = max(op1, check2(1));
    op1 = max(op1, check3(n));
    ans -= op1;
    cout << ans;
    return 0;
}
~~~

​	
