---
title: 牛客周赛Round52
subtitle:
date: 2024-08-06T21:00:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round52
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

## A.两数之和

签到题

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int z;
    cin >> z;
    if(z == 1 || z == 2)    cout << "NO";
    else cout << "YES"<<'\n'<<1 << ' ' << z - 1;
    return 0;
}
~~~

## B.小红装匣子

可以发现1*2的物块怎么放都无所谓，而1 * 3的物块只能放偶数个，先放完后者再放前者贪心。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t;
    cin >> t;
    while(t--){
        ll a, b, n;
        cin >> a >> b >> n;
        if(2 * a + 3 * b < 2 * n)    cout << "NO" << '\n';
        else{
            ll d = min(n / 3, b / 2);
            n -= d * 3;
            if(n > a)    cout << "NO" << '\n';
            else    cout << "YES" << '\n';
        }
    }
    return 0;
}
~~~

## C.小红的数字对对碰

可以发现只有以下几种情况可以减少数组长度：

负负、负正、负零、零零、零正

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100010];
unordered_map<ll, ll> mp;
int main(){
    int n;
    cin >> n;
    int cnt0 = 0, cnt1 = 0, cnt_1 = 0;
    for(int i = 1; i <= n; i++)    cin >> a[i], mp[a[i]]++;
    for(int i = 1; i <= n; i++){
        if(a[i] == 0)    cnt0++;
        else if(a[i] > 0)    cnt1++;
        else cnt_1++;
    }
    int p1 = 0, p_1 = 0;
    for(auto [k, v] : mp){
        if(v > 1){
            if(k > 0)    p1 += v / 2;
            else p_1 += v / 2;
        }
    }
    if(cnt1 == cnt_1){
        cout << cnt0 % 2;
    }else if(cnt1 > cnt_1){
        cnt0 %= 2;
        if(cnt0 && cnt_1)    cnt_1--, cnt0--;
        cnt1 -= cnt_1;
        if(cnt1 > 1){
            int d = min(cnt1 / 2, p1);
            cnt1 -= d * 2;
        }
        cout << cnt1 + cnt0;
    }else{
        cnt_1 -= cnt1;
        int d = min(cnt_1, cnt0);
        cnt_1 -= d;
        cnt0 -= d;
        if(cnt_1 > 1){    
            cnt_1 %= 2;
        }
        cout << cnt_1 + (cnt0 % 2);
    }
    return 0;
}
~~~

## D.小红的最大字典序

保证相对顺序插入，所以可以把所有串的第一位放进去后再放第二位以此类推。使用堆维护字典序最大，每次把串的第一位放进去

~~~ C++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    string s;
    priority_queue<string, vector<string>, less<>> que;
    for(int i = 0; i < n; i++){
        cin >> s;
        que.push(s);
    }
    while(!que.empty()){
        s = que.top();
        que.pop();
        cout << s[0];
        s.erase(0, 1);
        if(s != "")    que.push(s);
    }
    return 0;
}
~~~

## E.小红的图上加边

并查集维护连通块的最大元素值，然后从小加到大。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll fa[100010], w[100010];
int find(int x){
    if(fa[x] != x){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}
void add(int a, int b){
    int faa = find(a), fbb = find(b);
    if(faa == fbb)    return;
    fa[faa] = fbb;
    w[fbb] = max(w[fbb], w[faa]);
}
int main(){
    ll ans = 0;
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)    fa[i] = i;
    for(int i = 1; i <= n; i++)    cin >> w[i];
    for(int i = 1; i <= n; i++){
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    priority_queue<ll, vector<ll>, greater<ll>> que;
    for(int i = 1; i <= n; i++){
        if(find(i) == i){
            que.push(w[find(i)]);
        }
    }
    while(que.size() > 1){
        ll a1 = que.top();
        que.pop();
        ll a2 = que.top();
        que.pop();
        a1 = max(a1, a2);
        ans += a1;
        que.push(a1);
    }
    cout << ans;
    return 0;
}
~~~

## F.小红的括号串

(和)的数量相同就满足条件。

当数量相同时，假设不是匹配的括号串，失配的）有x个，那么在这x个）之后一定有x个（适配，此外去掉这个2x个括号的括号串都是匹配的。所以通过循环移位，可以让这x个括号对匹配上。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 1000000007
#define N 200000

int i,j,k,n,m,t,d;
ll jc[N+50],inv[N+50],res;

ll su(ll a,ll b){a+=b;return (a>=M)?a-M:a;}
ll ksm(ll a,ll p){ll res=1;while(p){if(p&1){res=res*a%M;}a=a*a%M;p>>=1;}return res;}
ll c(ll n,ll m){if(n<m||n<0||m<0){return 0;}return jc[n]*inv[m]%M*inv[n-m]%M;}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	jc[0]=inv[0]=1;
	for(i=1;i<=N;i++)jc[i]=jc[i-1]*i%M;
	inv[N]=ksm(jc[N],M-2);
	for(i=N-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%M;
	string s;
	cin>>n>>s;
	if(n&1){
		cout<<0; return 0;
	}
	for(auto c:s){
		if(c=='(')i++;
		else if(c==')') j++;
	}
	cout<<c(n-i-j,n/2-i);
    return 0;
}
~~~

