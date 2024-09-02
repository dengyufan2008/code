// by lsl
// in fact we can maintain a_i - a_{i-1} instead
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int a[N];
struct node {
  int tp, lv, rv, is, l;
};
// -1 GG
// 1 '/'
// 2 '\'
// 3 '/\'
node operator+(node a, node b) {
  if (a.tp == 4) return b;
  node c;
  c.lv = a.lv, c.rv = b.rv;
  c.is = 0;
  c.l = a.l + b.l;
  if (a.is && b.is && a.rv == b.lv) {
    c.is = 1;
    c.tp = -1;
    return c;
  }
  if (a.tp == -1 || b.tp == -1 || (a.tp == 3 && b.tp == 3)) {
    c.tp = -1;
    return c;
  }
  if ((a.tp == 2 && b.tp == 3)) {
    c.tp = -1;
    return c;
  }
  if (a.tp == 3 && b.tp == 1) {
    if (b.l == 1 && a.rv > b.lv)
      c.tp = 3;
    else
      c.tp = -1;
    return c;
  }
  if (a.tp == 1 && b.tp == 1) {
    if (a.rv < b.lv)
      c.tp = 1;
    else if (b.l == 1 && a.rv > b.lv) {
      if (a.l == 1)
        c.tp = 2;
      else
        c.tp = 3;
    } else
      c.tp = -1;
    return c;
  }
  if (a.tp == 2 && b.tp == 2) {
    if (a.rv > b.lv)
      c.tp = 2;
    else
      c.tp = -1;
    return c;
  }
  if (a.tp == 1 && b.tp == 3) {
    if (a.rv < b.lv)
      c.tp = 3;
    else
      c.tp = -1;
    return c;
  }
  if (a.tp == 3 && b.tp == 2) {
    if (a.rv > b.lv)
      c.tp = 3;
    else
      c.tp = -1;
    return c;
  }
  if (a.tp == 1 && b.tp == 2) {
    if (a.l == 1) {
      if (a.rv > b.lv)
        c.tp = 2;
      else if (a.rv != b.lv)
        c.tp = 3;
      else
        c.tp = -1;
      return c;
    }
    if (a.rv != b.lv)
      c.tp = 3;
    else
      c.tp = -1;
    return c;
  }
  if (a.tp == 2 && b.tp == 1) {
    if (b.l == 1 && a.rv > b.lv)
      c.tp = 2;
    else
      c.tp = -1;
    return c;
  }
}
node operator+(node a, int x) { return (node){a.tp, a.lv + x, a.rv + x, a.is, a.l}; }
struct segtree {
  node t[N << 2];
  int lz[N << 2];
#define mid (l + r >> 1)
#define ls (k << 1)
#define rs (k << 1 | 1)
  void pushup(int k) { t[k] = t[ls] + t[rs]; }
  void ch(int k, int z) { t[k] = t[k] + z, lz[k] += z; }
  void pushdown(int k) {
    if (!lz[k]) return;
    ch(ls, lz[k]), ch(rs, lz[k]);
    lz[k] = 0;
  }
  void build(int k, int l, int r) {
    if (l == r) {
      t[k] = (node){1, a[l], a[l], 1, 1};
      return;
    }
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(k);
  }
  void upd(int k, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) {
      ch(k, z);
      return;
    }
    pushdown(k);
    if (mid >= x) upd(ls, l, mid, x, y, z);
    if (y > mid) upd(rs, mid + 1, r, x, y, z);
    pushup(k);
  }
  node qry(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return t[k];
    pushdown(k);
    node ans = (node){4, 0, 0, 0, 0};
    if (mid >= x) ans = ans + qry(ls, l, mid, x, y);
    if (y > mid) ans = ans + qry(rs, mid + 1, r, x, y);
    return ans;
  }
} T;
int n, q;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  T.build(1, 1, n);
  cin >> q;
  while (q--) {
    int op, l, r, x;
    cin >> op >> l >> r;
    if (op == 1) {
      cin >> x;
      T.upd(1, 1, n, l, r, x);
    } else {
      node ans = T.qry(1, 1, n, l, r);
      if ((op == 3 || op == 4) && l == r) {
        cout << 1 << '\n';
        continue;
      }
      if ((op == 2 && ans.is) || (op - 2 == ans.tp))
        cout << 1 << '\n';
      else
        cout << 0 << '\n';
    }
  }
  return 0;
}
