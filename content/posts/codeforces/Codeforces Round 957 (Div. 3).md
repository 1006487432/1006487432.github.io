---
title: Codeforces Round 957 (Div. 3)
subtitle:
date: 2024-07-06T22:21:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: Codeforces Round 957 (Div. 3)
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

## A - Only Pluses
枚举

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    for(int i = 0; i <= 5; i++){
        for(int j = 0; j + i <= 5; j++){
            for(int k = 0; i + j + k <= 5; k++){
                ans = max(ans, (a + i) * (b + j) * (c + k));
            }
        }
    }
    cout << ans << '\n';
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
## B - Angry Monk
非最大值x，进行x-1次操作全拆成1再进行x次操作全部加上。

不唯一的最大值x，同理。	

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    ll n, k;
    cin >> n >> k;
    ll mx = 0;
    ll ans = 0;
    map<ll, int> mp;
    vector<ll> a(k + 1, 0);
    for(int i = 1; i <= k; i++){
        cin >> a[i];
        mx = max(a[i], mx);
        mp[a[i]]++;
    }
    for(int i = 1; i <= k; i++){
        if(a[i] != mx){
            if(a[i] == 1) ans++;
            else ans += 2 * a[i] - 1;
        }else{
            if(mp[a[i]] == 1) continue;
            else{
                if(a[i] == 1)   ans++;
                else{
                    ans += 2 * a[i] - 1;
                }
                mp[a[i]]--;
            }
        }
    }
    cout << ans << '\n';
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
## C - Gorilla and Permutation
观察一个序列里面f和g的范围很容易得出结论
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = n; i > m; i--)
        cout << i << ' ';
    for(int i = 1; i <= m; i++)
        cout << i << ' ';
    cout << '\n';
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
}       }
~~~
## D - Test of Love

直接模拟就行。每次从一个木头跳到另一个木头，如果可以就直接跳，如果距离不够，就先跳m距离再看跳之后的位置到下一个木头有没有鳄鱼，没有就统计游泳的长度。同理处理最后一个木头到右岸。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[100010], b[100010];
const int maxn = 5e6+9;
ll  t[maxn];
int n, m;
int lowbit(int x){
    return x & -x;
}
void update(int now){
    while(now<=m){
        t[now] ++;
        now += lowbit(now);
    }
}

ll query(int now){
    ll an = 0;
    while(now){
        an += t[now];
        now -= lowbit(now);
    }
    return an;
}
void solve(){
    cin >> n;
    map<int, int> mp;
    vector<int> aa, bb;
    for(int i = 1; i <= n; i++) cin >> a[i], mp[a[i]]++, aa.push_back(a[i]);
    for(int i = 1; i <= n; i++) cin >> b[i], mp[b[i]]--, bb.push_back(b[i]);
    for(auto [k, v] : mp){
        if(v != 0) {
            cout<< "NO" << '\n';
            return;
        }
    }
    sort(aa.begin(),aa.end());
    sort(bb.begin(), bb.end());
    aa.erase( unique( aa.begin(),aa.end() ) ,aa.end());
    bb.erase( unique( bb.begin(),bb.end() ) ,bb.end());
    m = aa.size();
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(aa.begin(),aa.end(), a[i]) - aa.begin()+1;
        ans += query(m)-query(a[i]);
        update(a[i]);
    }
    int ans2 = 0;
    m = bb.size();
    for(int i = 0; i <= n; i++) t[i] = 0;
    for(int i = 1; i <= n; i++) {
        b[i] = lower_bound(bb.begin(),bb.end(), b[i]) - bb.begin()+1;
        ans2 += query(m)-query(b[i]);
        update(b[i]);
    }
    for(int i = 0; i <= n; i++) t[i] = 0;
    if(ans % 2 != ans2 % 2){
        cout << "NO" << '\n';
    }else{
        cout << "YES" << '\n';
    }
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

## E - Novice's Mistake

注意到n*a-b的范围最大是99999，也就是最大是五位数。那么对于一个确定的a，b只可能有五种取值可能是答案。

$len(n)*a-5<=len(n)*a-b < len(n)*a$

预处理n*a的前五位数存下来，然后枚举每一个a和对应的五个b，根据长度匹配，统计答案。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n;
    cin >> n;
    auto len = [&](int n){
        int tmp = 0;
        while(n){
            tmp++;
            n /= 10;
        }
        return tmp;
    };
    map<int, int> mp;
    int n_len = len(n);
    if(n_len == 1){
        int tmp = 0;
        for(int i = 1; i <= 5; i++){
            tmp = tmp * 10 + n;
            mp[i] = tmp;
        }
    }else if(n_len == 2){
        mp[1] = n / 10;
        mp[2] = n;
        mp[4] = n * 101;
        mp[3] = n * 10 + n / 10;
        mp[5] = n * 1010 + n / 10;
    }else{
        mp[1] = n / 100;
        mp[2] = n / 10;
        mp[3] = n;
        mp[4] = n * 10 + n /100;
        mp[5] = n * 100 + n / 10;
    }
    vector<pair<int,int>> ans;
    for(int a = 1; a <= 10000; a++){
        int all = n_len * a;
        for(int b = all - 5; b < all; b++){
            if(b < 1)   continue;
            if(mp[all - b] == n * a - b)    ans.push_back({a, b});
        }
    }
    cout << ans.size() << '\n';
    for(auto [a, b] : ans){
        cout << a << ' ' << b << '\n';
    }
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

			## F - Valuable Cards

开一个set存x的因子。

假设已经有一个set，对于新遍历到的元素y，如果y不为x的因子就直接不管，如果是，先find x/y存不存在，存在就清空set，答案+1，把y加入新的set；不存在，就遍历set，把y*set中所有为x的因子加入set。

从左到右遍历一遍数组，就得到答案。（答案初始为1，set初始插入1便于编码）

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n, x;
    cin >> n >> x;
    set<int> has;
    int cnt = 0;
    has.insert(1);
    for(int i = 1; i <= n; i++){
        int tmp;
        cin >> tmp;
        if(tmp > x || tmp == 1 || x % tmp != 0) continue;
        else{
            if(has.find(x / tmp) == has.end()){
                vector<int> temp;
                for(auto j : has){
                    if(x % (tmp * j) == 0){
                        temp.push_back(tmp *j);
                    }
                }
                for(auto j : temp)  has.insert(j);
            }else{
                cnt++;
                has.clear();
                has.insert(1);
                has.insert(tmp);
            }
        }
    }
    cout << cnt + 1 << '\n';
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

