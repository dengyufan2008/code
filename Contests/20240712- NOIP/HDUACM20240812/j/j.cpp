// by wls
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, B = 31, M = (1ll << B) - 1;
bool _st;
int n, q, a[N];
struct node {
  int ls, rs, sum;
  int xt, lb, rb;
} t[N * 100];
int tot = 0;
void push_up(int p) {
  t[p].sum = t[t[p].ls].sum + t[t[p].rs].sum;
  t[p].lb = t[t[p].ls].lb | t[t[p].rs].lb, t[p].rb = t[t[p].ls].rb | t[t[p].rs].rb;
}
void setxor(int p, int x, int dep) {
  if (x >> dep & 1) swap(t[p].ls, t[p].rs);
  int lb = t[p].lb, rb = t[p].rb;
  t[p].xt ^= x, t[p].lb = (lb & (x ^ M)) | (rb & x), t[p].rb = (rb & (x ^ M)) | (lb & x);
}
void push_down(int p, int dep) {
  if (!t[p].xt) return;
  setxor(t[p].ls, t[p].xt, dep - 1), setxor(t[p].rs, t[p].xt, dep - 1);
  t[p].xt = 0;
}
void insert(int &p, int x, int dep) {
  if (!p) p = ++tot;
  if (dep < 0) {
    t[p].lb = x ^ M, t[p].rb = x, t[p].sum = 1;
    return;
  }
  push_down(p, dep);
  if (x >> dep & 1)
    insert(t[p].rs, x, dep - 1);
  else
    insert(t[p].ls, x, dep - 1);
  push_up(p);
}
void split(int &p, int &q, int l, int r, int x, int y, int dep) {
  if (!p) return;
  if (x <= l && r <= y) return q = p, p = 0, void();
  push_down(p, dep), q = ++tot;
  int mid = (l + r) >> 1;
  if (x <= mid) split(t[p].ls, t[q].ls, l, mid, x, y, dep - 1);
  if (mid < y) split(t[p].rs, t[q].rs, mid + 1, r, x, y, dep - 1);
  push_up(p), push_up(q);
}
void merge(int &p, int q, int dep) {
  if (!p || !q) return p += q, void();
  if (dep < 0) return;
  push_down(p, dep), push_down(q, dep);
  merge(t[p].ls, t[q].ls, dep - 1), merge(t[p].rs, t[q].rs, dep - 1);
  push_up(p);
}
void setor(int &p, int x, int dep) {
  if (!p || dep < 0) return;
  if (!(x & t[p].lb & t[p].rb)) {
    setxor(p, x & t[p].lb, dep);
    return;
  }
  push_down(p, dep);
  if (x >> dep & 1) {
    setxor(t[p].ls, 1 << dep, dep - 1);
    merge(t[p].rs, t[p].ls, dep - 1);
    t[p].ls = 0;
  }
  setor(t[p].ls, x, dep - 1), setor(t[p].rs, x, dep - 1);
  push_up(p);
}
void setand(int &p, int x, int dep) {
  int y = x ^ M;
  setxor(p, M, dep), setor(p, y, dep), setxor(p, M, dep);
}
int query(int p, int x) {
  int dp = B - 1, res = 0;
  while (dp >= 0) {
    push_down(p, dp);
    if (t[p].ls && (x >> dp & 1)) {
      p = t[p].ls, res |= (1 << dp);
    } else if (t[p].rs && (x >> dp & 1 ^ 1)) {
      p = t[p].rs, res |= (1 << dp);
    } else if (t[p].ls) {
      p = t[p].ls;
    } else if (t[p].rs) {
      p = t[p].rs;
    } else {
      assert(0);
    }
    --dp;
  }
  return res;
}
int rt;
bool _ed;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], insert(rt, a[i], B - 1);
    for (int i = 1, op, l, r, x, tp; i <= q; i++) {
      cin >> op >> x;
      if (op == 1)
        insert(rt, x, B - 1);
      else if (op == 2)
        setor(rt, x, B - 1);
      else if (op == 3)
        setand(rt, x, B - 1);
      else if (op == 4)
        setxor(rt, x, B - 1);
      else if (op == 5)
        cout << query(rt, x) << '\n';
    }
    for (int i = 0; i <= tot; i++) t[i] = node();
    tot = rt = 0;
  }
  return 0;
}
