---
title: 牛客周赛Round50
subtitle:
date: 2024-07-07T21:11:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round50
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

## A.小红的最小最大

签到题

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a, b, c;
    cin >> a >> b >> c;
    if(min(a,b) + c > max(a,b))    puts("YES");
    else puts("NO");
    return 0;
}
~~~

## B.小红的四则运算（easy）

特判全1的时候就行，也可以hard版的写法直接枚举操作符

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    sort(a, a + 3);
    if(a[0] == 1){
        if(a[1] == 1){
            if(a[2] == 1){
                cout << 3;
                return 0;
            }
        }
    }
    if(a[0] == 1)    cout << (a[0] + a[1]) * a[2];
    else cout << a[0] * a[1] * a[2];
    
    return 0;
}
~~~

## C.小红的四则运算（hard）

暴力枚举操作符即可，注意有两种计算顺序。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int op(int a, int b, int c){
    if(c == 0)    return a + b;
    if(c == 1)    return a - b;
    if(c == 2)    return a * b;
    return a / b;
}
int main(){
    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            int t1 = op(a, b, i);
            int t2 = op(t1, c, j);
            int t3 = op(b, c, i);
            int t4 = op(a, t3, j);
            ans = max(ans, t2);
            ans = max(ans, t4);
        }
    cout << ans;
    return 0;
}
~~~

## D.小红的因式分解

暴力枚举因子，然后计算是否满足条件即可。注意当C=0时的特判，以及因子正负情况。	

~~~ C++
#include<bits/stdc++.h>
using namespace std;
void solve(){
    int a, b, c;
    cin >> a >> b >> c;
    if(c == 0){
        cout << 1 << ' ' << 0 << ' ' << a << ' ' << b << '\n';
        return;
    }
    vector<pair<int,int>> pa, pb;
    int absc = c < 0? -c:c;
    int absa = a < 0? -a:a;
    for(int i = 1; i * i <= absa; i++){
        if(absa % i == 0){
            if(a > 0){
                pa.push_back({i, absa / i});
                pa.push_back({-1, -1 * absa / i});
            }else{
                pa.push_back({-i, absa / i});
                pa.push_back({i, -1 * absa / i});
            }
        }
    }
    for(int i = 1; i * i <= absc; i++){
        if(absc % i == 0){
            if(c > 0){
                pb.push_back({i, absc / i});
                pb.push_back({-i, -1 * absc / i});
            }else{
                pb.push_back({-i, absc / i});
                pb.push_back({i, -1 * absc / i});
            }
        }
    }
    for(auto [a1, a2]:pa)
        for(auto [b1, b2]:pb){
            if(a1 * b1 + a2 * b2 == b){
                cout << a1 << ' ' << b2 << ' ' << a2 << ' ' << b1 << '\n';
                return;
            }
            if(a1 * b2 + a2 * b1 == b){
                cout << a1 << ' ' << b1 << ' ' << a2 << ' ' << b2 << '\n';
                return;
            }
        }
    cout << "NO" << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();    
    }
    return 0;
}
//a = a1a2
//b = a1b2+a2b1
//c = b1b2	
~~~

## E.小红的树上移动

题意相当于每次等概率走到下一层的任意一个节点，走到叶子节点则停下来。求走的次数的期望。

分析题意可知这题和树的结构无关，只要知道每一层节点个数和叶子节点的数量就可以了。

在第i层，前一层没停下来的概率为p，该层有x个叶子节点，y个节点数量。停下的概率是p*（x/y),继续走的概率是p * （1-x/y），注意一下求逆元就行。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
typedef long long ll;
vector<int> g[1000010];
int dep[1000010];
int num[1000010];
int all[1000010];
void dfs(int x, int fa){
    dep[x] = dep[fa] + 1;
    all[dep[x]]++;
    int cnt = 0;
    for(auto v : g[x]){
        if(v == fa)    continue;
        cnt++;
        dfs(v, x);
    }
    if(cnt == 0)    num[dep[x]]++;
}
ll ksm(ll a, ll b){
    ll res = 1;
    while(b){
        if(b & 1)    res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll inv(ll a){
    return ksm(a, mod - 2);
}
int main(){
    ll n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    ll fenzi = 1;
    ll fenmu = 1;
    ll ans = 0;
    for(int i = 2; ; i++){
        if(!all[i])    break;
        ll nzi = fenzi * num[i] % mod;
        nzi = nzi * (i - 1) % mod;
        fenmu = fenmu * all[i] % mod;
        fenzi = fenzi * (all[i] - num[i]) % mod;
        ans = (ans + nzi * inv(fenmu) % mod) % mod;
    }    
    cout << ans;
    return 0;
}			
~~~

