---
title: DP练习记录
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

## DP

### 洛谷P1541

[P1095 [NOIP2007 普及组\] 守望者的逃离 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P1095)

[P1541 [NOIP2010 提高组\] 乌龟棋 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P1541)

首先考虑状态，在出第i张牌时，值只和dp[i - 1]有关，但有四种情况，同时需要知道当前能获取的价值（走到了哪里）。如果能记录下先前都出了什么牌以及获得的总价值，就能解决这个问题。由于有四类牌，设一个四维数组dp[a][b][c][d],表示出了a张1，b张2，c张3，d张4，dp[0][0][0][0]=val[0],那么当前获取的价值就是val[1 + a + b * 2 + c * 3 + d * 4];

对于状态转移：当出一张1时，显然有dp[a][b][c][d] = max（dp[a][b][c][d]， dp[a - 1][b][c][d] + val[1 + a + b * 2 + c * 3 + d * 4]）,以此类推当出其他牌时同理。

那么四重循环枚举每类牌的个数即可（每类牌不超过40)

```c++
#include <bits/stdc++.h>
#define fi first;
#define se second;

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

// 1.integer overflow (1e5 * 1e5) (2e9 + 2e9)
// 2.runtime error
// 3.boundary condition
int f[400];
int g[5];
int dp[41][41][41][41];
int ans = 0;
int n, m;
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> f[i];
  for (int i = 0; i < m; i++) {
    int tmp;
    cin >> tmp;
    g[tmp]++;
  }
  dp[0][0][0][0] = f[1];
  for (int a = 0; a <= g[1]; a++)
    for (int b = 0; b <= g[2]; b++)
      for (int c = 0; c <= g[3]; c++)
        for (int d = 0; d <= g[4]; d++) {
          int r = a + 2 * b + 3 * c + 4 * d + 1;
          if (a != 0)
            dp[a][b][c][d] = max(dp[a][b][c][d], dp[a - 1][b][c][d] + f[r]);
          if (b != 0)
            dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b - 1][c][d] + f[r]);
          if (c != 0)
            dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c - 1][d] + f[r]);
          if (d != 0)
            dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d - 1] + f[r]);
        }
  cout << dp[g[1]][g[2]][g[3]][g[4]];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
```

[P1868 饥饿的奶牛 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P1868)

以区间为单位进行考虑的话，每个区间只有取和不取两种状态。将所有区间按右端点排序后，用dp[i]表示从最左端到第i个区间右端点内可以取的价值的最大值，dp[i] = max(i.r - i.l + 1 + dp[j], dp[i - 1])

当考虑第i个区间时，只需要将它的贡献与往前数第一个不相交的区间的dp[j]加起来与dp[i - 1]做比较即可。先预处理将所有区间的右端点存储，再用二分查找优化一下找不相交区间即可。

```c++
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#define fi first;
#define se second;

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
vector<int> t;
//1.integer overflow (1e5 * 1e5) (2e9 + 2e9)
//2.runtime error
//3.boundary condition
const int N = 150010;
struct tmp{
	int l, r;
}g[N];
int dp[N];
bool cmp(struct tmp a, struct tmp b){
	if(a.r == b.r)
		return a.l < b.l;
	return a.r < b.r;
}
void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> g[i].l >> g[i].r;
	}
	sort(g + 1, g + 1 + n, cmp);
	t.push_back(0);
	for(int i = 1; i <= n; i++)
		t.push_back(g[i].r);
	dp[0] = 0;
	for(int i = 1; i <= n; i++){
		int val = g[i].r - g[i].l + 1;
		int pos = lower_bound(t.begin(), t.end(), g[i].l) - t.begin();
		pos--;
		dp[i] = val + dp[pos];
		dp[i] = max(dp[i], dp[i - 1]);
	}
	// for(int i = 1; i <= n; i++)
	// 	cout << dp[i] << ' ';
	// cout << '\n';
	cout << dp[n];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    t = 1;
    while(t--){
    	solve();
    }
    return 0;
}
```

[P2679 [NOIP2015 提高组\] 子串 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P2679)

字符串匹配类型的DP

xxxxxxxxxx class Solution {public:   vector<vector> rangeAddQueries(int n, vector<vector>& queries) {     vector<vector> tmp(n+1 , vector(n+1,0));     int m = queries.size();     for(int i = 0; i < m; i++)    {       tmp[queries[i][0]][queries[i][1]]++;       tmp[queries[i][0]][queries[i][3]+1]–;       tmp[queries[i][2]+1][queries[i][1]]–;       tmp[queries[i][2]+1][queries[i][3]+1]++;    }//对差分数组进行操作     vector<vector> ans(n , vector(n , 0));     ans[0][0] = tmp[0][0];     for(int i = 0; i < n; ++i)       for(int j = 1; j < n; ++j) tmp[i][j] += tmp[i][j-1];     for(int i = 1; i < n; ++i)       for(int j = 0; j < n; ++j) tmp[i][j] += tmp[i-1][j];     for(int i = 0; i < n; ++i)       for(int j = 0; j < n; ++j) ans[i][j] = tmp[i][j];     //由于下标从0开始，所以分布求前缀和要方便一点     //这种写法不存在重复加的地方，第一个for求一维前缀和，第二个for加上前面行的和。     return ans;  }};  c++

本题是dp[i][j][k][0\1]表示A字符串前i个、中选了k个子串匹配到B字符串前j个的方案数，因为要求不相交的子串需要知道某个字符有没有被选中，所以用第四维表示第i个字符有没有被选中。

状态转移：

显然第i个字符如果被选中那么只有2种可能：1.作为前面被选中的子串的末尾、2.作为新子串的开头

如果第i个字符被选中，那么显然A[i] = B[j] 或者A[i] != B[j] (这时方案为0)；

所以当A[i] == B[j] 时有第一类转移方程

不选:dp[i][j][k][0] = dp[i - 1][j][k][1] + dp[i - 1][j][k][0]

选:dp[i][j][k][1] = dp[i - 1][j - 1][k][1] + dp[i - 1][j - 1][k - 1][0] + dp[i - 1][j - 1][k - 1][1]

第二类当A[i] != B[j]时只需要继承即可：

dp[i][j][k][0] = dp[i - 1][j][k][0] + dp[i - 1][j][k][1]

dp[i][j][k][1] = 0

最后答案即为dp[n][m][k][0] + dp[n][m][k][1]即从A串中前n个字符中选出k个与B串前m个字符相匹配

```c++
#include <bits/stdc++.h>
#include <cstdio>
#define fi first;
#define se second;

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int mod = 1000000007;

// 1.integer overflow (1e5 * 1e5) (2e9 + 2e9)
// 2.runtime error
// 3.boundary condition
int dp[2][210][210][2];
void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  char a[1010], b[1010];
  scanf("%s%s", a + 1, b + 1);
  dp[0][0][0][0] = dp[1][0][0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int p = 1; p <= k; p++) {
        if (a[i] == b[j]) {
          dp[i % 2][j][p][0] =
              (dp[(i - 1) % 2][j][p][0] + dp[(i - 1) % 2][j][p][1]) % mod;
          dp[i % 2][j][p][1] = ((dp[(i - 1) % 2][j - 1][p - 1][0] +
                                 dp[(i - 1) % 2][j - 1][p - 1][1]) %
                                    mod +
                                dp[(i - 1) % 2][j - 1][p][1]) %
                               mod;

        } else {
          dp[i % 2][j][p][0] =
              (dp[(i - 1) % 2][j][p][0] + dp[(i - 1) % 2][j][p][1]) % mod;
          dp[i % 2][j][p][1] = 0;
        }
      }
  int tmp = (dp[n % 2][m][k][0] + dp[n % 2][m][k][1]) % mod;
  printf("%d\n", tmp);
}
int main() {
  int t;
  t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
```

[P2946 [USACO09MAR\] Cow Frisbee Team S - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P2946)

```c++
#include<bits/stdc++.h>
const int p=1e8;//定义常数
const int N=2000+10;
const int F=1000+10;
using namespace std;

int n,f,r[N],s[N][F];
long long h[N][F];

int main()
{
	int i,j;
	cin>>n>>f;
	for(i=1;i<=n;i++)
	{
	  cin>>r[i];
	  r[i]%=f;//提前取模
	}
	for(i=1;i<=n;i++) h[i][r[i]]=1;//初始化
	for(i=1;i<=n;i++)
	  for(j=0;j<f;j++)//余数范围：0到f-1
	    h[i][j]=((h[i][j]+h[i-1][j])%p+h[i-1][(j-r[i]+f)%f])%p;//每加一次就%p
	cout<<h[n][0]<<endl;
	return 0;
}
```

[P5662 [CSP-J2019\] 纪念品 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P5662)

```c++
#include <bits/stdc++.h>
#define fi first;
#define se second;
#define vector<int> vi;

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
//1.integer overflow (1e5 * 1e5) (2e9 + 2e9)
//2.runtime error
//3.boundary condition
const int MAXN = 105;
int dp[10005], price[MAXN][MAXN];

void solve(){
    int t, n, m;
    int ans;
    cin >> t >> n >> m;
    for(int i = 1; i <= t; i++)
        for(int j = 1; j <= n; j++)
            cin >> price[i][j];
    ans = m;
    for(int i = 1; i < t; i++){
        dp[ans] = ans;
        for(int j = 1; j <= n; j++){
            for(int k = ans; k >= price[i][j]; k--) {
                dp[k - price[i][j]] = max(dp[k - price[i][j]], dp[k] + price[i + 1][j] - price[i][j]);
            }
        }
        int ma = 0;
        for (int j = 0; j <= ans; ++j) {
            ma = max(ma, dp[j]);
        }
        ans = ma;
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    t = 1;
    while(t--){
    	solve();
    }
    return 0;
}
```

xxxxxxxxxx typedef long long ll;ll fpow(ll a, ll b, ll p)//求快速幂{    ll res = 1;    while (b)    {        if (b & 1)  res = res * a % p;        a = a * a % p;        b >>= 1;    }    return res;}ll bsgs(ll a, ll b, ll p)//bsgs{    a %= p, b %= p;    if (a == 0) return b == 0 ? 1 : -1;    if (b == 1) return 0;    ll m = ceil(sqrt(p)), t = fpow(a, m, p);    unordered_map<ll, ll> mp;    mp[b] = 0;    ll tmp = t;    for (int i = 1, e = b; i < m; i++)    {        e = e * a % p;        mp[e] = i;    }    for (int i = 1; i <= m; i++)    {        if (mp.find(t) != mp.end())        {            return (i * m - mp[t] + p) % p;        }        t = t * tmp % p;    }    return -1;}ll gcd(ll a, ll b)//欧几里得{    return b ? gcd(b, a % b) : a;}ll exgcd(ll a, ll b, ll& x, ll& y)//扩欧求逆元{    if (b == 0)    {        x = 1, y = 0;        return a;    }    ll d = exgcd(b, a % b, y, x);    y -= a / b * x;    return d;}ll inv(ll a, ll b)求逆元{    ll x, y;    exgcd(a, b, x, y);    return (x % b + b) % b;}ll exbsgs(ll a, ll b, ll p)//扩展bsgs{    if (b == 1 || p == 1)return 0;         ll g = gcd(a, p), k = 0, na = 1;    while (g > 1)    {        if (b % g != 0)return -1;            k++; b /= g; p /= g; na = na * (a / g) % p;        if (na == b)return k;           g = gcd(a, p);    }    ll f = bsgs(a, b * inv(na, p) % p, p);    if (f == -1)return -1;    return f + k;}cpp

```c++
#include <bits/stdc++.h>
#define fi first;
#define se second;
#define vector<int> vi;

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
//1.integer overflow (1e5 * 1e5) (2e9 + 2e9)
//2.runtime error
//3.boundary condition
struct girl{
    int rmb, rp, time;
}f[110];
int dp1[110][110], dp2[110][110];
void solve(){
    int n, m, r;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> f[i].rmb >> f[i].rp >> f[i].time;
    cin >> m >> r;
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= f[i].rmb; j--)
            for(int k = r; k >= f[i].rp; k--){
                if(dp1[j][k] == dp1[j - f[i].rmb][k - f[i].rp] + 1){
                    dp2[j][k] = min(dp2[j][k], dp2[j - f[i].rmb][k - f[i].rp] + f[i].time);
                }else if(dp1[j][k] < dp1[j - f[i].rmb][k - f[i].rp] + 1){
                    dp1[j][k] = dp1[j - f[i].rmb][k - f[i].rp] + 1;
                    dp2[j][k] = dp2[j - f[i].rmb][k - f[i].rp] + f[i].time;
                }
            }
    }
    int ans = 1e9;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= r; j++)
            if(dp1[i][j] == dp1[m][r])
                ans = min(ans, dp2[i][j]);
    cout << ans << '\n';
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    t = 1;
    while(t--){
    	solve();
    }
    return 0;
}
```

## **字符串**

给出两个字符串，比较由两个字符串重复构成的无限长字符串的字典序。

若字符串A+B < B + A, **则**A < B 反之同理

```c++
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int main(){
    string a, b;
    while(cin >> a >> b){
        string c = a + b;
        string d = b + a;
        if(c > d)
            puts(">");
        else if(c < d)
            puts("<");
        else 
            puts("=");
    }
    return 0;
}
```
