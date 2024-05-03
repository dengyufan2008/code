#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;
const int N = 4100;
const int M = 4100;
typedef unsigned long long ll;
const ll mod = 998244353;
struct Data  // 转移用的矩阵类
{
  int dp[3][3];
  inline int* operator[](const int& x) { return dp[x]; }
  Data() {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) dp[i][j] = -1;
  }
  friend bool operator<(Data a, Data b) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (a[i][j] != b[i][j]) return a[i][j] < b[i][j];
    return false;
  }
  friend bool operator!=(Data a, Data b) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (a[i][j] != b[i][j]) return true;
    return false;
  }
  inline void trs(Data& c, int del) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (dp[i][j] != -1)
          for (int k = 0, rem = del - i - j; k < 3 && i + j + k <= del; k++, rem--)
            c[j][k] = max(c[j][k], min(i + dp[i][j] + rem / 3, 4));
  }
  inline bool ckhu() {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (dp[i][j] >= 4) return true;
    return false;
  }
};
struct nod  // 自动机节点
{
  Data is_pair[2];
  int cnt_pair;
  friend bool operator<(nod a, nod b) {
    if (a.cnt_pair != b.cnt_pair) return a.cnt_pair < b.cnt_pair;
    if (a.is_pair[0] != b.is_pair[0]) return a.is_pair[0] < b.is_pair[0];
    if (a.is_pair[1] != b.is_pair[1]) return a.is_pair[1] < b.is_pair[1];
    return false;
  }
  inline void clear() {
    is_pair[0] = Data();
    is_pair[1] = Data();
    cnt_pair = -2333;
  }
  inline bool ckhu() {
    if (cnt_pair >= 7) {
      clear();
      return true;
    }
    if (is_pair[1].ckhu()) {
      clear();
      return true;
    }
    return false;
  }
  friend nod operator+(nod a, int b) {
    if (a.cnt_pair == -2333) return a;
    nod c;
    if (b >= 2) a.is_pair[0].trs(c.is_pair[1], b - 2);
    a.is_pair[0].trs(c.is_pair[0], b);
    a.is_pair[1].trs(c.is_pair[1], b);
    c.cnt_pair = a.cnt_pair + (b >= 2);
    c.ckhu();
    return c;
  }
};
inline nod stat() {
  nod res;
  res.clear();
  res.cnt_pair = 0;
  res.is_pair[0][0][0] = 0;
  return res;
}
map<nod, int> mrk;
int tot;
int mp[M][5];
queue<nod> q;
int ed;
inline void bfs()  // 搜索
{
  nod st = stat();
  q.push(st);
  mrk[st] = ++tot;
  while (!q.empty()) {
    st = q.front();
    q.pop();
    int nu = mrk[st];
    for (int i = 0; i <= 4; i++) {
      nod tw = st + i;
      if (mrk.count(tw))
        mp[nu][i] = mrk[tw];
      else
        mp[nu][i] = mrk[tw] = ++tot, q.push(tw);
    }
  }
  st.clear();
  ed = mrk[st];
}
ll fac[N];
ll inv[N];
ll ifac[N];
ll dp[2][440][M];
ll* p1[440];
ll* p2[440];
ll xs[N];
int sum[N];
int n;
inline void pre() {
  fac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % mod;
  inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  ifac[0] = 1;
  for (int i = 1; i < N; i++) ifac[i] = ifac[i - 1] * inv[i] % mod;
}
inline void calc()  // dp使用了滚动数组
{
  int cap = n * 4 - 13;
  for (int i = 0; i <= cap; i++) p1[i] = dp[0][i];
  for (int i = 0; i <= cap; i++) p2[i] = dp[1][i];
  p1[0][mrk[stat()]] = 1;
  for (int z = 1; z <= n; z++) {
    for (int j = 0; j <= 4 - sum[z]; j++) xs[j] = fac[4 - sum[z]] * ifac[4 - sum[z] - j] % mod * ifac[j] % mod;
    for (int i = cap; i >= 0; i--) {
      for (int j = 1; j <= tot; j++) p2[i][j] = 0;
      for (int j = 1; j <= tot; j++)
        if (p1[i][j] != 0)
          for (int tmp = 0; tmp <= 4 - sum[z] && i + tmp <= cap; tmp++)
            (p2[i + tmp][mp[j][tmp + sum[z]]] += p1[i][j] * xs[tmp]) %= mod;
    }
    for (int i = 0; i <= cap; i++) swap(p1[i], p2[i]);
  }
}
int main() {
  freopen("i.in", "r", stdin);
  freopen("i.ans", "w", stdout);
  bfs();
  pre();
  scanf("%d", &n);
  for (int i = 1, w, t; i <= 13; i++) scanf("%d%d", &w, &t), sum[w]++;
  calc();
  ll ans = 0;
  for (int p = 1, q = 4 * n - 14; p <= 4 * n - 13; p++, q--)  // 计算答案
    for (int j = 1; j <= tot; j++)
      if (j != ed) (ans += p1[p][j] * fac[p] % mod * fac[q]) %= mod;
  printf("%lld\n", ans * ifac[4 * n - 13] % mod + 1);
  return 0;  // 拜拜程序~
}