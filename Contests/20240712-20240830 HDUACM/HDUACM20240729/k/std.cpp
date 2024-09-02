#include <iostream>
using namespace std;
typedef unsigned int U;
typedef unsigned long long ull;
const int N = 1005, M = 2005, TOT = N * M * 11, BASE = 998244353, P = 1000000007;
ull weight[N];
U SX = 335634763, SY = 873658265, SZ = 192849106, SW = 746126501;
inline ull xorshift128() {
  U t = SX ^ (SX << 11);
  SX = SY;
  SY = SZ;
  SZ = SW;
  return SW = SW ^ (SW >> 19) ^ t ^ (t >> 8);
}
inline ull myrand() { return (xorshift128() << 32) ^ xorshift128(); }
int Case, inv[N], n, m, i, j, res, f[N][N], tot, l[TOT], r[TOT], val[TOT];
ull sum[TOT];
struct E {
  int x, y, z;
} e[M];
struct Frac {
  int u1, u2, d;
  Frac() {}
  Frac(int _u1, int _u2, int _d) { u1 = _u1, u2 = _u2, d = _d; }
};
int ins(int x, int a, int b, int c) {
  int y = ++tot;
  val[y] = val[x] + 1;
  sum[y] = sum[x] + weight[c];
  if (a == b) return y;
  int mid = (a + b) >> 1;
  if (c <= mid)
    l[y] = ins(l[x], a, mid, c), r[y] = r[x];
  else
    l[y] = l[x], r[y] = ins(r[x], mid + 1, b, c);
  return y;
}
inline bool smaller(int x, int y) {
  if (y < 0) return 1;
  if (sum[x] == sum[y]) return 0;
  int a = 1, b = n, mid;
  while (a < b) {
    mid = (a + b) >> 1;
    if (sum[r[x]] == sum[r[y]]) {
      b = mid;
      x = l[x];
      y = l[y];
    } else {
      a = mid + 1;
      x = r[x];
      y = r[y];
    }
  }
  return val[x] < val[y];
}
inline int compare(const Frac& A, const Frac& B) {
  if (A.u1 < 0 && B.u1 < 0) return 0;
  if (A.u1 < 0) return 1;
  if (B.u1 < 0) return -1;
  int a = 1, b = n, mid;
  int A1 = A.u1, A2 = A.u2, B1 = B.u1, B2 = B.u2, AD = A.d, BD = B.d;
  if ((sum[A1] - sum[A2]) * BD == (sum[B1] - sum[B2]) * AD) return 0;
  //(A1-A2)/AD<(B1-B2)/BD
  //(A1-A2)*BD<(B1-B2)*AD
  while (a < b) {
    mid = (a + b) >> 1;
    if ((sum[r[A1]] - sum[r[A2]]) * BD == (sum[r[B1]] - sum[r[B2]]) * AD) {
      b = mid;
      A1 = l[A1];
      A2 = l[A2];
      B1 = l[B1];
      B2 = l[B2];
    } else {
      a = mid + 1;
      A1 = r[A1];
      A2 = r[A2];
      B1 = r[B1];
      B2 = r[B2];
    }
  }
  int cross = (val[A1] - val[A2]) * BD - (val[B1] - val[B2]) * AD;
  if (!cross) return 0;
  return cross < 0 ? -1 : 1;
}
void cal(int x, int y, int a, int b) {
  if (a == b) {
    res = (1LL * res * BASE + val[x] - val[y]) % P;
    return;
  }
  int mid = (a + b) >> 1;
  cal(r[x], r[y], mid + 1, b);
  cal(l[x], l[y], a, mid);
}
int main() {
  freopen("k.in", "r", stdin);
  freopen("k.ans", "w", stdout);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> Case;
  for (inv[0] = inv[1] = 1, i = 2; i < N; i++) inv[i] = 1LL * (P - P / i) * inv[P % i] % P;
  while (Case--) {
    cin >> n >> m;
    for (i = 1; i <= m; i++) cin >> e[i].x >> e[i].y >> e[i].z;
    for (i = 1; i <= n; i++) weight[i] = myrand();
    for (i = 0; i <= n + 1; i++)
      for (j = 1; j <= n; j++) f[i][j] = -1;
    for (j = 1; j <= n; j++) f[0][j] = 0;
    for (i = 0; i <= n; i++)
      for (j = 1; j <= m; j++) {
        int x = e[j].x, y = e[j].y, z = e[j].z;
        int root = f[i][x];
        if (root < 0) continue;
        int now = ins(root, 1, n, z + 1);
        if (smaller(now, f[i + 1][y])) f[i + 1][y] = now;
      }
    Frac ans = Frac(-1, -1, 1);
    for (i = 1; i <= n; i++) {
      int fin = f[n + 1][i];
      if (fin < 0) continue;
      Frac me = Frac(0, 0, 1);
      for (j = 0; j <= n; j++) {
        int now = f[j][i];
        if (now < 0) continue;
        Frac tmp(fin, now, n + 1 - j);
        if (compare(tmp, me) > 0) me = tmp;
      }
      if (compare(me, ans) < 0) ans = me;
    }
    if (ans.u1 < 0)
      cout << "-1\n";
    else {
      res = 0;
      cal(ans.u1, ans.u2, 1, n);
      res = 1LL * res * inv[ans.d] % P;
      cout << res << "\n";
    }
    for (i = 1; i <= tot; i++) l[i] = r[i] = val[i] = sum[i] = 0;
    tot = 0;
  }
}
