#include <bits/stdc++.h>
using ll = long long;
const int MAXN = 1e5 + 9;
const ll INF = 4e18;

int t, n, m, a[MAXN], q;
// prefix of a[i]-1
struct BIT {
  ll c[MAXN];
  int lowbit(int x) { return x & -x; }
  void clear() {
    for (int i = 0; i <= n; ++i) c[i] = 0;
  }
  void modify(int p, ll d) {
    for (int i = p; i <= n; i += lowbit(i)) c[i] += d;
  }
  ll query(int p) {
    ll res = 0;
    for (int i = p; i > 0; i -= lowbit(i)) res += c[i];
    return res;
  }
  ll query(int l, int r) { return query(r) - query(l - 1); }
} pre;
// min{pre[l]...pre[r]}
struct SegTree {
  ll d[MAXN << 2], tg[MAXN << 2];
  void pushDown(int s, int t, int p) {
    d[p << 1] += tg[p], tg[p << 1] += tg[p];
    d[p << 1 | 1] += tg[p], tg[p << 1 | 1] += tg[p];
    tg[p] = 0;
  }
  void build(int s = 1, int t = n, int p = 1) {
    if (t < s) return;
    if (s == t) {
      d[p] = pre.query(s), tg[p] = 0;
      return;
    }
    int mid = (s + t) / 2;
    build(s, mid, p << 1), build(mid + 1, t, p << 1 | 1);
    d[p] = std::min(d[p << 1], d[p << 1 | 1]), tg[p] = 0;
  }
  void modify(int l, int r, ll c, int s = 1, int t = n, int p = 1) {
    if (t < l || r < s || t < s) return;
    if (l <= s && t <= r) {
      d[p] += c, tg[p] += c;
      return;
    }
    pushDown(s, t, p);
    int mid = (s + t) / 2;
    modify(l, r, c, s, mid, p << 1), modify(l, r, c, mid + 1, t, p << 1 | 1);
    d[p] = std::min(d[p << 1], d[p << 1 | 1]);
  }
  ll query(int l, int r, int s = 1, int t = n, int p = 1) {
    if (t < l || r < s || t < s) return INF;
    if (l <= s && t <= r) return d[p];
    pushDown(s, t, p);
    int mid = (s + t) / 2;
    return std::min(query(l, r, s, mid, p << 1), query(l, r, mid + 1, t, p << 1 | 1));
  }
} draw;
int main() {
  freopen("l.in", "r", stdin);
  freopen("l.ans", "w", stdout);
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), cnt += a[i] > 0;
    pre.clear();
    for (int i = 1; i <= n; ++i) pre.modify(i, a[i] - 1);
    draw.build();

    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      if (pre.query(x, x) > -1 && y == 0)
        cnt--;
      else if (pre.query(x, x) == -1 && y > 0)
        cnt++;

      draw.modify(x, n, y - 1 - pre.query(x, x));
      pre.modify(x, y - 1 - pre.query(x, x));

      printf("%d\n", pre.query(1, n) <= -m || cnt <= 1 ? -1 : std::max(1ll, draw.query(1, n) / -m + 1));
    }
  }

  return 0;
}
