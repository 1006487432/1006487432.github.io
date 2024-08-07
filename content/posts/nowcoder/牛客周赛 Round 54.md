---
title: 牛客周赛Round54
subtitle:
date: 2024-08-06T21:00:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round54
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

## A.清楚姐姐的糖葫芦

签到题

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    string s;
    cin >> s;
    int ans = 0;
    for(auto i : s)    if(i == 'o')    ans++;
    cout << ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    t = 1;
    while(t--){
        solve();
    }
    return 0;
}
~~~

## B.清楚姐姐买竹鼠

注意可能有多买更便宜的情况

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    ll a, b, x;
    cin >> a >> b >> x;
    if(3LL * a <= b){
        cout << x * a;
    }else{
        ll ans = (x + 2LL) / 3LL * b;
        ans = min(ans, (x / 3LL) * b + (x % 3LL) * a);
        cout << ans;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    t = 1;
    while(t--){
        solve();
    }
    return 0;
}
~~~

## C.竹鼠饲养物语

模拟

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    map<ll, ll> mp;
    for(int i = 1; i <= n; i++)    cin >> a[i], mp[a[i]]++;
    ll ans = 0;
    ll d = 1e9 + 10;
    ll last = 0;
    for(auto [k, v] : mp){
        if(last == k - 1){
            d = min(d, v);
            ans += d;
            last = k;
        }else{
            break;
        }
    }
    cout << ans;
    return 0;
}
~~~

## D.清楚姐姐跳格子

BFS

~~~ C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    vector<long long> st(n + 1, -1);
    for(int i = 1; i <= n; i++)    cin >> a[i];
    queue<int> que;
    int cnt = 0;
    st[1] = 0;
    que.push(1);
    while(!que.empty()){
        auto fr = que.front();
        que.pop();
        for(int i = 1; i * i <= a[fr] && i <= n; i++){
            if(a[fr] % i == 0){
                ll d1 = fr + i, d2 = fr - i;
                if(d1 <= n && st[d1] == -1)    st[d1] = st[fr] + 1, que.push(d1);
                if(d2 >= 1 && st[d2] == -1)    st[d2] = st[fr] + 1, que.push(d2);
                d1 = fr + (a[fr] / i), d2 = fr - (a[fr] / i);
                if(d1 <= n && st[d1] == -1)    st[d1] = st[fr] + 1, que.push(d1);
                if(d2 >= 1 && st[d2] == -1)    st[d2] = st[fr] + 1, que.push(d2);
            }
        }
    }
    cout << st[n];
    return 0;
}
~~~

## E.清楚姐姐的布告规划

dp[i]表示覆盖到第i位需要的布告数量。

dp[i] = min(dp[i], dp[i - a[j]] + 1)， a[j]是这个布告的长度，i的范围是i±（a[j]-1）

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)    cin >> a[i];
    vector<int> dp(n + 1, 1e5);
    dp[0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = max(i, a[i]); j <= min(n, i + a[i] - 1); j++){
            dp[j] = min(dp[j], dp[j - a[i]] + 1);
        }
    }
    if(dp[n] == 1e5)    cout << -1 << '\n';
    else cout << dp[n] << '\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
~~~
