---
title: Codeforces Round #956 (Div. 2)
subtitle:
date: 2024-07-06T22:21:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: Codeforces Round #956 (Div. 2)
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

## A - Array Divisibility
暴力处理了一下，但是看结果发现直接输出1到n就行了好像。
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1, 1);
    for(int i = n / 2 + 1; i <= n; i++)
        a[i] = i;
    for(int i = n / 2; i >= 1; i--){
        int sum = 0;
        for(int j = i + i; j <= n; j+=i){   
            sum += a[j];
        }
        if(sum % i == 0)    a[i] = i;
        else a[i] = i - (sum % i);
    }
    for(int i = 1; i <= n; i++) cout << a[i] << ' ';
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
}
~~~
## B - Corner Twist
注意到这个操作每次对某一行/某一列都是+1、+2,在模3的意义下就是某一行、一列的和不变。因此只需要检查两个矩阵是不是每一行、每一列对应的和模3下是不是相同的就行。
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> r(n + 1, 0);
    vector<int> c(m + 1, 0);
    for(int i = 1; i <= n; i++){
        string s;
        cin >> s;
        for(int j = 0; j <m; j++){
            r[i] += s[j] - '0';
            c[j + 1] += s[j] - '0';
        }

    }
    int temp = 0;
    for(int i = 1; i <= n; i++){
        string s;
        cin >> s;
        for(int j = 0; j <m; j++){
            r[i] -= s[j] - '0';
            c[j + 1] -= s[j] - '0';
        }
    }
    int flag = 1;
    for(int i = 1; i <= n; i++)
        if(r[i] % 3 != 0)   flag = 0;
    for(int i =1 ; i <= m; i++)
        if(c[i] % 3 != 0)   flag = 0;
    if(flag) cout << "YES" << '\n';
    else cout << "NO" << '\n';
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
## C - Have Your Cake and Eat It Too
​	暴力枚举六种排列方式，每次从左到右找到满足条件的最小右边界，检查是否存在满足题意的分配方式。	
~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[200010], b[200010], c[200010];
ll tot = 0;
ll n;
int flag = 0;
int st[3];
int la, ra, lb, rb, lc, rc;
void dfs(int front, int r, int cnt){
    if(r > n)   return;
    for(int i = 0; i < 3 && flag == 0; i++){
        ll nr = r;
        if(st[i])   continue;
        if(cnt == 3){
            if(i == 0){
                if(a[n] - a[front - 1]  < tot)   return;
                la = front , ra = n;
            }else if(i == 1){
                if(b[n] - b[front - 1] < tot) return;
                lb = front , rb = n;
            }else{
                if(c[n] - c[front - 1] < tot) return;
                lc = front, rc = n;
            }	
            flag = 1;
            return;
        }
        st[i] = 1;
        if(i == 0){
            while(nr <= n && a[nr] - a[front - 1] < tot) nr++;
            la = front, ra = nr;
            dfs(nr + 1, nr + 1, cnt + 1);
        }else if(i == 1){
            while(nr <= n && b[nr] - b[front - 1] < tot) nr++;
            lb = front, rb = nr;
            dfs(nr + 1, nr + 1, cnt + 1);
        }else{
            while(nr <= n && c[nr] - c[front - 1] < tot) nr++;
            lc = front, rc = nr;
            dfs(nr + 1, nr + 1, cnt + 1);
        }
        if(flag == 1)   return;
        st[i] = 0;
    }
}
void solve(){
    cin >> n;
    st[0] = st[1] = st[2] = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
    for(int i = 1; i <= n; i++) cin >> b[i], b[i] += b[i - 1];
    for(int i = 1; i <= n; i++) cin >> c[i], c[i] += c[i - 1];
    tot = (a[n] + 2) / 3;
    flag = 0;
    dfs(1, 1, 1);
    if(!flag){
        cout << -1 << '\n';
        return;
    }
    cout << la << ' ' << ra << ' ' << lb << ' ' << rb << ' ' << lc << ' ' << rc;
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
}
~~~
## D - Swap Dilemma

注意到这个操作可以相邻元素之间进行交换，且两个数组都必须进行交换。要让A、B数组都变成相同的数组，那么可以让他们都变成有序数组，而相邻元素之间交换变成有序数组的最小次数为逆序对的个数。那么只需要两个数组逆序对的个数奇偶性相同就可以变成一样的数组。（奇偶性相同说明差值为偶数，交换次数少的数组偶数次交换可以不变）

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


