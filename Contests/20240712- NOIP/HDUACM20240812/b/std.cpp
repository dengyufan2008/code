#include <bits/stdc++.h>
using namespace std;
#define rint register int
#define ll long long
#define rll register long long
const int N = 1 << 18;
const int p = 998244353;
inline int Add(rint x, rint y) {
  x += y;
  return x >= p ? x - p : x;
}
inline int Del(rint x, rint y) {
  x -= y;
  return x >= 0 ? x : x + p;
}
inline ll Mul(rll x, rint y) {
  x *= y;
  return x >= p ? x % p : x;
}
ll fpow(rll a, rll b) {
  rll res = 1;
  for (; b; b >>= 1, a = Mul(a, a))
    if (b & 1) res = Mul(res, a);
  return res;
}
int r[N], w[N], t, pd;
void ntt(rint n, vector<int> &a, rint typ) {
  a.resize(n);
  if (pd != n) {
    for (rint i = 0; i < n; i++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    pd = n;
  }
  for (rint i = 0; i < n; i++)
    if (i < r[i]) swap(a[i], a[r[i]]);
  for (rint mid = 1; mid < n; mid <<= 1)
    for (rint i = 0, R = mid << 1; i < n; i += R)
      for (rint j = 0; j < mid; j++)
        t = Mul(w[mid + j], a[i + j + mid]), a[i + j + mid] = Del(a[i + j], t), a[i + j] = Add(a[i + j], t);
  if (typ == 1) return;
  rint inv = fpow(n, p - 2);
  reverse(a.begin() + 1, a.end());
  for (rint i = 0; i < n; i++) a[i] = Mul(a[i], inv);
}
void dfs_inv(vector<int> &f, vector<int> g, rint n) {
  g.resize(n);
  if (n == 1) {
    f.resize(1);
    f[0] = fpow(g[0], p - 2);
    return;
  }
  dfs_inv(f, g, n + 1 >> 1);
  rint Max = 1;
  while (Max < n + n) Max <<= 1;
  ntt(Max, f, 1);
  ntt(Max, g, 1);
  for (rint i = 0; i < Max; i++)
    f[i] = Mul(f[i], Del(2, Mul(f[i], g[i])));
  ntt(Max, f, -1);
  f.resize(n);
}
struct Eval {
  vector<int> vec[N], tmp, res;
  vector<int> Mult(vector<int> f, vector<int> g) {
    rint Max = f.size();
    for (rint i = 0; i < Max; i++) f[i] = Mul(f[i], g[i]);
    ntt(Max, f, 1);
    return f;
  }
  void dfs1(rint x, rint l, rint r) {
    if (l == r) {
      vec[x].resize(2);
      vec[x][0] = 1;
      vec[x][1] = p - tmp[l];
      return;
    }
    rint mid = l + r >> 1;
    dfs1(x << 1, l, mid);
    dfs1(x << 1 | 1, mid + 1, r);
    rint Max = 1;
    while (Max < r - l + 2) Max <<= 1;
    ntt(Max, vec[x << 1], 1);
    ntt(Max, vec[x << 1 | 1], 1);
    vec[x].resize(Max);
    for (rint i = 0; i < Max; i++) vec[x][i] = Mul(vec[x << 1][i], vec[x << 1 | 1][i]);
    ntt(Max, vec[x], -1);
  }
  void dfs2(rint x, rint l, rint r, vector<int> v) {
    v.resize(r - l + 2);
    if (l == r) {
      res[l] = v[0];
      return;
    }
    rint Max = 1, mid = l + r >> 1;
    while (Max < r - l + 2) Max <<= 1;
    ntt(Max, v, -1);
    dfs2(x << 1, l, mid, Mult(v, vec[x << 1 | 1]));
    dfs2(x << 1 | 1, mid + 1, r, Mult(v, vec[x << 1]));
  }
  vector<int> query(vector<int> f, vector<int> g) {
    rint n = f.size(), m = g.size();
    tmp = g;
    dfs1(1, 0, m - 1);
    dfs_inv(vec[1], vec[1], n);
    rint Max = 1;
    while (Max < n + n) Max <<= 1;
    res.resize(m);
    ntt(Max, f, -1);
    ntt(Max, vec[1], 1);
    dfs2(1, 0, m - 1, Mult(f, vec[1]));
    return res;
  }
} T;
vector<int> dfs(rint l, rint r, rll a, rll b) {
  if (l == r) {
    vector<int> f(2);
    f[0] = (a * l + b) % p;
    f[1] = 1;
    return f;
  }
  rint mid = l + r >> 1;
  vector<int> f = dfs(l, mid, a, b), g = dfs(mid + 1, r, a, b);
  rint Max = 1;
  while (Max < r - l + 2) Max <<= 1;
  ntt(Max, f, 1);
  ntt(Max, g, 1);
  for (rint i = 0; i < Max; i++) f[i] = Mul(f[i], g[i]);
  ntt(Max, f, -1);
  f.resize(r - l + 2);
  return f;
}
ll n, m;
ll get_mul(ll a, ll b) {
  ll sqr = sqrt(n);
  vector<int> f = dfs(1, sqr, a, b);
  vector<int> g;
  for (int i = 0; i < sqr; i++)
    g.push_back(a * i % p * sqr % p);
  vector<int> vec = T.query(f, g);
  ll res = 1;
  for (int i = sqr * sqr + 1; i <= n; i++)
    res = res * (a * i % p + b) % p;
  for (int x : vec) res = res * x % p;
  return res;
}
int main() {
  freopen("b.in", "r", stdin);
  freopen("b.ans", "w", stdout);
  w[N / 2] = 1;
  w[N / 2 + 1] = t = fpow(3, (p - 1) / N);
  for (rint i = N / 2 + 2; i < N; i++) w[i] = Mul(w[i - 1], t);
  for (rint i = N / 2 - 1; i; i--) w[i] = w[i << 1];
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld", &n, &m);
    ll res = (n * m + 1) % p;
    res = res * fpow(m, n) % p;
    res = res * get_mul(1, 0) % p;
    res = res * fpow(get_mul(m, 1), p - 2) % p;
    printf("%lld\n", res);
  }
  return 0;
}
