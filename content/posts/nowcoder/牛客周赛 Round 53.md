---
title: 牛客周赛Round53
subtitle:
date: 2024-08-06T21:00:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: 牛客周赛Round53
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

当掷n次时，小红有三种情况平局、赢、输，同时赢的概率等于输的概率。小红投第n+1次后，赢仍然赢，输最多是平局，平局有一半几率赢。设n次赢的概率是x，平局是y，有2x+y=1

第n+1次后赢得概率是x+y*0.5。联立得y=1-2x，则x+0.5y=0.5

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll fact[200010];
int main(){
    int n;
    cin >> n;
    printf("%.06f", 0.5);
    return 0;
}
~~~

## B.小红的字符串

要么顺着走，要么逆着走

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    string s;
    cin >> s;
    int cnt = 0;
    for(int i = 0, j = s.size() - 1; i < j; i++, j--){
        if(s[i] == s[j]) continue;
        cnt += min(abs(s[j] - s[i]), 26 - abs(s[j] - s[i]));
    }
    cout << cnt;    
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

## C.小红的 01 消除

可以发现操作1和3都没有用，直接统计能进行多少次操作2和y去min就行

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int x, y, z;
    cin >> x >> y >> z;
    int cnt = 1;
    int lhave = 0;
    int ans = 0;
    for(int i = 1; i < s.size(); i++){
        if(s[i] != s[i - 1]){
            if(s[i] == '1'){
                lhave += cnt;
            }else{
                ans += min(cnt, lhave);
                lhave -= min(cnt, lhave);
            }
            cnt = 1;
        }else{
            cnt++;
        }
    }
    if(s[s.size() - 1] == '1'){
        ans += min(cnt, lhave);
    }
    cout << min(ans, y);
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

## D.小红组比赛

一眼分组dp，注意相差最小值可以超过target，则dp数组开得范围应该是100*50（n * ai)

~~~ C++
#include<bits/stdc++.h>
using namespace std;
int dp[101][5010];
int a[110][25];
int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }
    int target;
    cin >> target;
    for(int i = 0; i <= n; i++){
        for(int j = 1; j <= 5000; j++){
            dp[i][j] = -1;
        }
    }
    for(int i = 1; i <= n; i++){
        dp[i][0] = 0;
        for(int j = 1; j <= m; j++){
            for(int k = 5000; k >= a[i][j]; k--){
                if(dp[i - 1][k - a[i][j]] != -1){
                    dp[i][k] = max(dp[i - 1][k - a[i][j]] + 1, dp[i][k]);
                }
            }
        }
        for(int j = 1; j <= 5000; j++)
            if(dp[i][j] != i)    dp[i][j] = -1;
    }
    int ans = 1e9;
    for(int i = 5000; i >= 0; i--){
        if(dp[n][i] == n){
            ans = min(ans, abs(i - target));
        }
    }
    cout << ans;
    return 0;
}
~~~

## E.折半丢弃

答案具有单调性，若MEX可以为X，则一定可以是更小的，若不能为X，那么更大的一定不能。

二分答案。接下来就是怎么check。

在check的时候，如果从低位开始考虑会面临第x位没有，但有多个数折半之后可以变成x。不妨倒过来想，因为要检查MEX能不能是mid+1，说明从0到mid之间的数全都存在，对于每个数的折半都是固定的路线，先把所有大于mid的折半到mid以内，然后再从mid开始看存不存在值，若存在就把剩下的继续折半继承下去。若出现不存在的则说明MEX不是能是mid+1。若全部存在则可以。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for(int i = 1; i <= n; i++)    cin >> a[i];
    int l = 0, r = n - 1;
    auto check = [&](int x){
        vector<int> vis(x + 1, 0);
        for(int i = 1; i <= n; i++){
            int t = a[i];
            while(t > x)    t /= 2;
            vis[t]++;
        }
        for(int i = x; i >= 0; i--){
            if(vis[i] == 0){
                return false;
            }
            vis[i / 2] += vis[i] - 1;
        }
        return true;
    };
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << l << '\n';
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

## F.小红走矩阵

五种状态，每种记录到达x，位置替换和不替换的最小步数。最后取最小值

~~~ c++
#include<bits/stdc++.h>
using namespace std;
char a[1010][1010];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int st[2][1010][1010];
int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    int ans = 1e9;
    for(int i = 0; i < 5; i++){
        queue<array<int, 3> > que;//x y val
        memset(st, 0, sizeof st);
        que.push({1, 1, 0});
        while(!que.empty()){
            auto [x, y, v] = que.front();
            que.pop();
            for(int j = 0; j < 4; j++){
                if(i == j)    continue;
                int xx = x + dx[j], yy = y + dy[j];
                if(xx >= 1 && xx <= n && yy >= 1 && yy <= m){
                    if(v == 0){//can replace
                        if(a[xx][yy] == 'X'){
                            if(st[1][xx][yy])    continue;
                            if(i == 4)    continue;
                            st[1][xx][yy] = st[0][x][y] + 1;
                            que.push({xx, yy, 1});
                        }else{
                            if(st[0][xx][yy])    continue;
                            st[0][xx][yy] = st[0][x][y] + 1;
                            que.push({xx, yy, 0});
                        }
                    }else{
                        if(a[xx][yy] == 'X' || st[1][xx][yy])    continue;
                        st[1][xx][yy] = st[1][x][y] + 1;
                        que.push({xx, yy, 1});
                    }
                }
            }
        }
        if(st[0][n][m] == 0 && st[1][n][m] == 0)    continue;
        if(st[0][n][m] && st[1][n][m])
            ans = min(ans, min(st[0][n][m], st[1][n][m]));
        if(st[0][n][m])
            ans = min(ans, st[0][n][m]);
        if(st[1][n][m])
            ans = min(ans, st[1][n][m]);
    }
    if(ans == 1e9)    cout << -1;
    else cout << ans;
    return 0;
}
~~~



## F.游游的删点直径

换根DP。

可以发现f(u)的值要么是在u的子树中，要么是以父亲为根的子树中。

在u的子树中，则有两种，一种是指向u的路径，一种是经过u的子节点的路径即一个v形。

在转移时，v要得到以父亲u为根的子树中最长的路径，要么是原先不经过u的路径且排除掉的经过v路径的最大值，要么是u连接的路径（指向u的最大和次大相连得到）。两者取最大值即可。

前者则有子节点提供经过子节点的最长路径即可（dmx）。

~~~ c++
#include<bits/stdc++.h>
using namespace std;
vector<int> g[100010];
int d1[100010], d2[100010], dmx[100010], ans[100010];
void dfs1(int fa, int pos){
    for(auto to : g[pos]){
        if(fa == to)    continue;
        dfs1(pos, to);
        if(d1[to] + 1 > d1[pos]){
            d2[pos] = d1[pos];//指向pos的次长路径
            d1[pos] = d1[to] + 1;//指向pos的最长路径
        }else if(d1[to] + 1 > d2[pos]){
            d2[pos] = d1[to] + 1;
        }
        dmx[pos] = max(dmx[pos], dmx[to]);
    }
    dmx[pos] = max(dmx[pos], d1[pos] + d2[pos]);//pos子树中包括pos的最长路径
}
void dfs2(int fa, int pos, int p1, int p2){
    multiset<int> s1, s2;
    s1.insert(0), s2.insert(0);
    s1.insert(p1), s2.insert(p2);//p1是父亲那边的最长路径，p2是父亲那边指向父亲的最长路径
    //s1表示不包括pos节点的路径长度
    //s2表示指向pos节点的路径长度
    for(auto to : g[pos]){
        if(to == fa)    continue;
        s1.insert(dmx[to]);
        s2.insert(d1[to] + 1);
    }
    ans[pos] = *s1.rbegin();//*s1.rbegin()表示最后一个元素，即最大的元素
    for(auto to : g[pos]){
        if(to == fa)    continue;
        s1.erase(s1.find(dmx[to]));
        s2.erase(s2.find(d1[to] + 1));
        int np1 = max(*s1.rbegin(), *s2.rbegin() + *prev(prev(s2.end())));
        //最大值要么是不包括pos的最大路径长度，要么是pos接连的最大路径长度
        //*prev(prev(s2.end()))表示倒数第二个元素，即次大的元素
        int np2 = *s2.rbegin() + 1;
        dfs2(pos, to, np1, np2);
        s1.insert(dmx[to]);
        s2.insert(d1[to] + 1);
    }
}
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n - 1; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 1);
    dfs2(1, 1, 0, 0);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
    return 0;
}
~~~

