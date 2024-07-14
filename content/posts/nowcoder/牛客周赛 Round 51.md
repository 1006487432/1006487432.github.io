---
title: 牛客周赛Round51
subtitle:
date: 2024-07-14T21:11:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round51
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

## A.小红的同余

签到题

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long m;
    cin >> m;
    cout << (m + 1) / 2;
    return 0;
}
~~~

## B.小红的三倍数

字符串输入。3的倍数特点数位之和是3的倍数，把每一位全部加起来模3就行。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        string s;
        cin >> s;
        for(auto j : s){
            ans = (ans + j - '0') % 3;
        }
    }
    if(ans % 3 == 0)    cout << "YES";
    else cout << "NO";
    return 0;
}

~~~

## C.小红充电

小于t的时候直接快充。大于t的时候要么直接充，要么先玩到t再快充。注意输出精度

~~~ c++
#include<bits/stdc++.h>
using namespace std;

int main(){
    double x, y, t, a, b, c;
    cin >> x >> y >> t >> a >> b >> c;
    double ans = 0;
    if(x <= t){
        ans = (100.0 - x) / c;
    }else{
        ans = (100.0 - x) / b;
        ans = min(ans,((x - t) / y) + ((100 - t) / c));
    }
    printf("%.7lf", ans);
    return 0;
}
~~~

## D.小红的 gcd

注意b是int范围，字符串输入a，然后对b取模（第一步辗转相除），然后套gcd公式就行。

~~~ C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b){
    return b ? gcd(b, a % b):a;
}
int main(){
    string a;
    cin >> a;
    ll b;
    cin >> b;
    ll to = 0;
    for(auto i : a){
        to = (to * 10 + (i - '0')) % b;
    }
    cout << gcd(b, to);
    return 0;
}
~~~

## E.小红走矩阵

直接bfs

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[550][550];
ll st[550][550];
int dx[] = {-1, 1, 0 ,0};
int dy[] = {0, 0, -1, 1};

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            cin >> a[i][j];
        }
    st[1][1] = a[1][1];
    queue<pair<int,int>> que;
    que.push({1, 1});
    while(que.size()){
        auto [x, y] = que.front();
        que.pop();
        for(int i = 0; i < 4; i++){
            int xx = x + dx[i], yy = y + dy[i];
            if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
                int val = max(st[x][y], a[xx][yy]);
                if(st[xx][yy] && st[xx][yy] <= val){
                    continue;
                }else{
                    st[xx][yy] = val;
                    que.push({xx, yy});
                }
            }
        }
    }
    cout << st[n][n];
    return 0;
}	
~~~

## F.小红的数组

假设没有绝对值，求连续子段和的极值可以使用线段树。而考虑绝对值的话，答案显然是连续子段和的最大或最小的绝对值较大者。

线段树求连续子段和的最大值（最小值把max改为min即可）。

需要维护的信息：

- 区间和
- 区间从左端点开始的最大/小连续子段和
- 区间从右端点开始的最大/小连续子段和
- 区间最大/小的连续子段和

更新信息（画图便于理解）：

- 区间和直接对左右区间求和
- 左：max/min(左区间的左，左区间+右区间的左)
- 右：max/min(右区间的右，右区间+左区间的右)
- 最：max/min(max/min(左区间的最，右区间的最), 左区间的右+右区间的左)；最值显然要么来自左区间，要么来自右区间，要么是合并之后产生的（即左的右+右的左）

~~~ c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int M=500010;
ll a[M];
struct node{
    ll s,ls,rs,ms;
    node(){};
    node(ll x){this->s = x, this->ls = x, this->rs = x, this->ms = x;};
    node(ll s, ll ls, ll rs, ll ms){this->s = s, this->ls = ls, this->rs = rs, this->ms = ms;};
    node operator +(const node& b){
        return node(this->s + b.s, max(this->ls, this->s + b.ls), max(b.rs, this->rs + b.s), max(max(this->ms, b.ms),this->rs + b.ls));
    };
    node operator -(const node& b){
        return node(this->s + b.s, min(this->ls, this->s + b.ls), min(b.rs, this->rs + b.s), min(min(this->ms, b.ms),this->rs + b.ls));
    };//重载运算符便于信息合并编码
}tree[M<<2], tree2[M<<2];

void build(ll p, ll pl, ll pr) {
    if (pl == pr) {
        tree[p] = node(a[pl]);
        return;
    }
    ll mid=(pl+pr)>>1;
    build(p << 1, pl, mid);
    build(p << 1 | 1, mid + 1, pr);
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
} 
void build2(ll p, ll pl, ll pr) {
    if (pl == pr) {
        tree2[p] = node(a[pl]);
        return;
    }
    ll mid=(pl+pr)>>1;
    build2(p << 1, pl, mid);
    build2(p << 1 | 1, mid + 1, pr);
    tree2[p] = tree2[p << 1] - tree2[p << 1 | 1];
}
node askans(int x,int y, int p, int pl,int pr) {
    if (x <= pl && pr <= y) return tree[p];   //完全包含
    int mid=(pr + pl)>>1;
    node f1,f2,T;
    T.s=0;
    if (y <= mid)   //全部都在左儿子
        T = askans(x, y, p << 1, pl, mid);
    if (x > mid)     //全部都在右儿子
        T = askans(x, y, p << 1 | 1, mid + 1, pr);
    if (x <= mid && y > mid) {     //询问区间被拆成两部分
        f1 = askans(x, y, p << 1, pl, mid);
        f2 = askans(x, y, p << 1 | 1, mid + 1, pr);
        T = f1 + f2;
    }
    return T;
}
node askans2(int x,int y, int p, int pl,int pr) {
    if (x <= pl && pr <= y) return tree2[p];   //完全包含
    int mid = (pr + pl) >> 1;
    node f1,f2,T;
    T.s=0;
    if (y <= mid)   //全部都在左儿子
        T = askans2(x, y, p << 1, pl, mid);
    if (x > mid)     //全部都在右儿子
        T = askans2(x, y, p << 1 | 1, mid + 1, pr);
    if (x <= mid&&y>mid) {     //询问区间被拆成两部分
        f1 = askans2(x, y, p << 1, pl, mid);
        f2 = askans2(x, y, p << 1 | 1, mid + 1, pr);
        T = f1 - f2;
    }
    return T;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    build2(1, 1, n);    
    ll q;
    cin >> q;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        if(l > r) swap(l, r);
        node ans = askans(l, r, 1, 1, n);
        node ans2 = askans2(l, r, 1, 1, n);
        cout << max(ans.ms, abs(ans2.ms)) << '\n';                
    }
    return 0;
}


~~~

