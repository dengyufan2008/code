#include <bits/stdc++.h>
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)
#define ll long long
#define N 400005
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int inf = 1e9;
int rt, n, q, tp, l[N], id[N], r[N], son[N][2], fa[N];
int op(int x) { return (son[fa[x]][1] == x); }
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid (l + r >> 1)
struct SGT {
  int tg[N << 1];
  pii mn[N << 1];
  void pd(int p) {
    if (tg[p] == 0) return;
    mn[ls].fi += tg[p], tg[ls] += tg[p];
    mn[rs].fi += tg[p], tg[rs] += tg[p], tg[p] = 0;
  }
  void pp(int p) { mn[p] = min(mn[ls], mn[rs]); }
  void bd(int p, int l, int r) {
    tg[p] = 0;
    mn[p].fi = 0;
    if (l == r) {
      mn[p].se = l;
      return;
    }
    bd(ls, l, mid), bd(rs, mid + 1, r), pp(p);
  }
  void add(int p, int l, int r, int a, int b, int q) {
    if (a <= l && r <= b) {
      tg[p] += q, mn[p].fi += q;
      return;
    }
    pd(p);
    if (a <= mid) add(ls, l, mid, a, b, q);
    if (b > mid) add(rs, mid + 1, r, a, b, q);
    pp(p);
  }
  pii qry(int p, int l, int r, int a, int b) {
    if (a <= l && r <= b) return mn[p];
    pii ret;
    ret.fi = 1e9, ret.se = 0;
    pd(p);
    if (a <= mid) ret = min(ret, qry(ls, l, mid, a, b));
    if (b > mid) ret = min(ret, qry(rs, mid + 1, r, a, b));
    return ret;
  }
} dp;
struct BIT {
  ll val[N];
  void add(int p, ll x) {
    for (int i = p; i <= n + 5; i += (i & -i)) val[i] += x;
  }
  ll qry(int p) {
    ll ret = 0;
    for (int i = p; i; i &= (i - 1)) ret += val[i];
    return ret;
  }
} T[2][2], T1[2][2], T2[2][2];
void add(int x, int o = 1) {
  if (l[x] == r[x]) return;
  dp.add(1, 0, n, l[x], r[x] - 1, o);
  if (!op(x)) {
    T[0][1].add(r[x] + 1, 1ll * o * (r[x] - l[x])), T[0][0].add(r[x] + 1, 1ll * o * (r[x] - l[x]) * (1 - r[x]));
    T1[0][0].add(l[x] + 1, 1ll * o * (l[x] + 1) * (1 - r[x])), T1[0][0].add(r[x] + 1, -1ll * o * (l[x] + 1) * (1 - r[x]));
    T1[1][0].add(l[x] + 1, -1ll * o * (1 - r[x])), T1[1][0].add(r[x] + 1, 1ll * o * (1 - r[x]));
    T1[0][1].add(l[x] + 1, 1ll * o * (l[x] + 1)), T1[0][1].add(r[x] + 1, -1ll * o * (l[x] + 1));
    T1[1][1].add(l[x] + 1, -1ll * o), T1[1][1].add(r[x] + 1, 1ll * o);
  } else {
    T[1][1].add(l[x] + 1, 1ll * o * (l[x] - r[x])), T[1][0].add(l[x] + 1, 1ll * o * (r[x] - l[x]) * (l[x] + 1));
    T2[0][0].add(l[x] + 1, 1ll * o * (1 - r[x]) * (1 + l[x])), T2[0][0].add(r[x] + 1, -1ll * o * (1 - r[x]) * (1 + l[x]));
    T2[1][0].add(l[x] + 1, -1ll * o * (1 - r[x])), T2[1][0].add(r[x] + 1, 1ll * o * (1 - r[x]));
    T2[0][1].add(l[x] + 1, 1ll * o * (1 + l[x])), T2[0][1].add(r[x] + 1, -1ll * o * (1 + l[x]));
    T2[1][1].add(l[x] + 1, -1ll * o), T2[1][1].add(r[x] + 1, 1ll * o);
  }
}
void rotate(int x) {
  if (x == rt) return;
  int y = fa[x], z = fa[y], o = op(x), o1 = op(y);
  if (!z)
    rt = x;
  else
    son[z][o1] = x;
  int a = son[x][o], b = son[x][o ^ 1], c = son[y][o ^ 1];
  add(a, -1), add(b, -1), add(c, -1), add(x, -1);
  fa[y] = x, fa[b] = y, fa[x] = z, son[y][o] = b, son[x][o ^ 1] = y, l[x] = min(l[x], l[y]), r[x] = max(r[x], r[y]);
  if (!o)
    l[y] = l[b];
  else
    r[y] = r[b];
  add(a), add(b), add(c), add(y);
}
ll query(int tl, int tr) {
  ll ret = 0;
  ret += T[0][0].qry(tr + 1) - T[0][0].qry(tl - 1) + 1ll * tr * (T[0][1].qry(tr + 1) - T[0][1].qry(tl - 1));
  ret += T[1][0].qry(tr + 1) - T[1][0].qry(tl - 1) + 1ll * tl * (T[1][1].qry(tr + 1) - T[1][1].qry(tl - 1));
  int z = dp.qry(1, 0, n, tl - 1, tr).se;
  ret += T1[0][0].qry(tl - 1) + 1ll * tl * T1[1][0].qry(tl - 1) + 1ll * tr * T1[0][1].qry(tl - 1) + 1ll * tl * tr * T1[1][1].qry(tl - 1);
  ret -= T1[0][0].qry(z + 1) + 1ll * tl * T1[1][0].qry(z + 1) + 1ll * tr * T1[0][1].qry(z + 1) + 1ll * tl * tr * T1[1][1].qry(z + 1);
  ret += T2[0][0].qry(tr + 1) + 1ll * tl * T2[1][0].qry(tr + 1) + 1ll * tr * T2[0][1].qry(tr + 1) + 1ll * tl * tr * T2[1][1].qry(tr + 1);
  ret -= T2[0][0].qry(z + 1) + 1ll * tl * T2[1][0].qry(z + 1) + 1ll * tr * T2[0][1].qry(z + 1) + 1ll * tl * tr * T2[1][1].qry(z + 1);
  return ret;
}
int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.ans", "w", stdout);
  cin >> n >> q;
  for (int i = 1; i <= 2 * n - 1; ++i) {
    scanf("%d%d%d%d", &l[i], &r[i], &son[i][0], &son[i][1]);
    if (son[i][0]) fa[son[i][0]] = i;
    if (son[i][1]) fa[son[i][1]] = i;
  }
  for (int i = 1; i <= 2 * n - 1; ++i)
    if (l[i] < r[i]) id[r[son[i][0]]] = i;
  for (int i = 1; i <= 2 * n - 1; ++i)
    if (!fa[i]) rt = i;
  l[n << 1] = r[n << 1] = 0;
  l[n << 1 | 1] = 0, r[n << 1 | 1] = n, son[n << 1 | 1][0] = (n << 1), son[n << 1 | 1][1] = rt, id[0] = (n << 1 | 1), fa[n << 1] = fa[rt] = (n << 1 | 1);
  l[n + 1 << 1] = r[n + 1 << 1] = n + 1;
  l[n + 1 << 1 | 1] = 0, r[n + 1 << 1 | 1] = n + 1, son[n + 1 << 1 | 1][0] = (n << 1 | 1), son[n + 1 << 1 | 1][1] = (n + 1 << 1), id[n] = (n + 1 << 1 | 1), fa[n + 1 << 1] = fa[n << 1 | 1] = (n + 1 << 1 | 1);
  rt = (n + 1 << 1 | 1), dp.bd(1, 0, n);
  for (int i = 1; i < rt; ++i)
    if (l[i] < r[i]) add(i);
  int lst = 0;
  while (q--) {
    int op;
    scanf("%d", &op);
    if (op & 1) {
      int x;
      scanf("%d", &x);
      if (l[x] == 1 && r[x] == n) continue;
      rotate(x);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", query(l, r));
    }
  }
  return 0;
}
