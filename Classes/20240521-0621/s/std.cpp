// Poly log
#include <bits/stdc++.h>
#define IL inline
#define reg register
#define N 200200
#define M 10001000
#define int long long
#define oo (1ll << 60)
IL int read() {
  reg int x = 0;
  reg char ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
  return x;
}

int n, k, pre[N], a[N], lst[N], ys[N], len;

struct Range {
  int l, r, t, w;
  IL bool operator<(const Range &a) const { return l < a.l; }
};

std::set<Range> s;

IL void cmin(reg int &x, reg int y) { x > y ? x = y : 0; }
IL void cmax(reg int &x, reg int y) { x < y ? x = y : 0; }
IL int max(reg int x, reg int y) { return x > y ? x : y; }
IL int min(reg int x, reg int y) { return x < y ? x : y; }

auto split(reg int p) {
  auto it = s.lower_bound({p, 0, 0, 0});
  if (it != s.end() && it->l == p) return it;
  Range t = *--it;
  s.erase(it);
  s.insert({t.l, p - 1, t.t, t.w});
  return s.insert({p, t.r, t.t, t.w}).first;
}

struct Node {
  int p, l, r, w;
};
std::vector<Node> vec[N];
int f[N];

struct Line {
  int k, b;
  IL int F(reg int x) { return k * ys[x] + b; }
};

namespace Seg1 {

#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l[o] + r[o] >> 1)

int l[N << 2], r[N << 2];
Line tr[N << 2];

struct Upd {
  int o;
  Line p;
} stk[M];

int top;

void build(reg int o, reg int L, reg int R) {
  l[o] = L, r[o] = R, tr[o] = {0, -oo};
  if (L < R) build(ls, L, mid), build(rs, mid + 1, R);
}

int query(reg int o, reg int x) {
  if (l[o] == r[o]) return tr[o].F(x);
  return max(tr[o].F(x), query(mid >= x ? ls : rs, x));
}

void modify(reg int o, reg Line p) {
  if (tr[o].F(mid) < p.F(mid)) stk[++top] = {o, tr[o]}, std::swap(tr[o], p);
  if (l[o] == r[o]) return;
  if (tr[o].F(l[o]) < p.F(l[o])) modify(ls, p);
  if (tr[o].F(r[o]) < p.F(r[o])) modify(rs, p);
}

IL void rollback(reg int t) {
  while (top > t) tr[stk[top].o] = stk[top].p, --top;
}

#undef ls
#undef rs
#undef mid

}  // namespace Seg1

namespace Seg2 {

#define ll __int128
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l[o] + r[o] >> 1)

int l[N << 2], r[N << 2];

struct Point {
  int x, y;
  IL Point operator+(const Point &a) const { return {x + a.x, y + a.y}; }
  IL Point operator-(const Point &a) const { return {x - a.x, y - a.y}; }
  IL ll det(const Point &a) const { return (ll)x * a.y - (ll)y * a.x; }
};

std::vector<Point> vec[N << 2];

void build(reg int o, reg int L, reg int R) {
  l[o] = L, r[o] = R;
  if (L < R) build(ls, L, mid), build(rs, mid + 1, R);
}

IL void append(reg int o, const Point &p) {
  while (vec[o].size() > 1) {
    Point t = vec[o][vec[o].size() - 2], q = vec[o].back();
    if ((p - t).det(q - t) > 0) break;
    vec[o].pop_back();
  }
  vec[o].push_back(p);
}

void insert(reg int o, reg int p, const Point &q) {
  append(o, q);
  if (l[o] == r[o]) return;
  insert(mid >= p ? ls : rs, p, q);
}

int query(reg int o, reg int k) {
  if (vec[o].empty()) return -oo;
  reg int l = 1, r = vec[o].size() - 1, Mid;
  while (l <= r) {
    Mid = l + r >> 1;
    Point p = vec[o][Mid], q = vec[o][Mid - 1];
    if (p.y - p.x * k >= q.y - q.x * k)
      l = Mid + 1;
    else
      r = Mid - 1;
  }
  return vec[o][r].y - vec[o][r].x * k;
}

int query(reg int o, reg int L, reg int R, reg int k) {
  if (L <= l[o] && r[o] <= R) return query(o, k);
  if (L > r[o] || l[o] > R) return -oo;
  return max(query(ls, L, R, k), query(rs, L, R, k));
}

#undef ll
#undef ls
#undef rs
#undef mid

}  // namespace Seg2

std::vector<Line> upd[N << 2];

void insert(reg int o, reg int L, reg int R, reg Line p, reg int l = 0, reg int r = n) {
  if (L <= l && r <= R) return upd[o].push_back(p);
  if (L > r || l > R) return;
  reg int mid = l + r >> 1;
  insert(o << 1, L, R, p, l, mid), insert(o << 1 | 1, L, R, p, mid + 1, r);
}

void dc(reg int o, reg int l, reg int r) {
  reg int t = Seg1::top;
  for (auto p : upd[o]) Seg1::modify(1, p);
  if (l == r) {
    if (l) f[l] = Seg1::query(1, pre[l]);
    Seg2::insert(1, l, {ys[pre[l]], f[l]});
    reg int pr = l;
    for (auto &[pl, ql, qr, w] : vec[l]) {
      cmax(ql, pr + 1);
      if (ql > qr) continue;

      auto slack = [&](reg int l, reg int r, reg int L, reg int R) -> void {
        insert(1, L, R, (Line){w, Seg2::query(1, l, r, w)});
      };

      reg int t = min(qr, pl + k);
      if (ql <= t) slack(pl, pr, ql, t);
      for (reg int i = max(t + 1, ql), p = i - k; i <= qr && p <= pr; ++i, ++p) slack(p, pr, i, i);
    }
  } else {
    reg int mid = l + r >> 1;
    dc(o << 1, l, mid), dc(o << 1 | 1, mid + 1, r);
  }
  Seg1::rollback(t);
}

main() {
  freopen("s.in", "r", stdin);
  freopen("s.ans", "w", stdout);
  n = read(), k = read();
  for (reg int i = 1; i <= n; ++i) a[i] = read(), ys[i + 1] = pre[i] = pre[i - 1] + a[i];
  std::sort(ys + 1, ys + 2 + n), len = std::unique(ys + 1, ys + 2 + n) - ys - 1;
  for (reg int i = 0; i <= n; ++i) pre[i] = std::lower_bound(ys + 1, ys + 1 + len, pre[i]) - ys;
  for (reg int i = 1; i <= n; ++i) {
    static int buc[N];
    lst[i] = buc[a[i]], buc[a[i]] = i;
  }
  static int cnt[N];
  for (reg int i = 1; i <= n; ++i) ++cnt[a[i]];
  reg int mex = 0;
  while (cnt[mex]) ++mex;
  for (reg int i = 1; i <= n; ++i) {
    s.insert({i, i, n + 1, mex});
    if (!--cnt[a[i]]) cmin(mex, a[i]);
  }
  for (reg int i = n, l, r, p; i; --i) {
    l = lst[i] + 1, r = i - 1;
    auto itr = split(r + 1), itl = split(l);
    p = l - 1;
    for (auto it = itl; it != itr; it = s.erase(it)) {
      if (it->w <= a[i]) break;
      p = it->r, vec[p - 1].push_back({it->l - 1, i, it->t - 1, it->w});
    }
    if (p >= l) s.insert({l, p, i, a[i]});
    vec[i - 1].push_back({i - 1, i, itr->t - 1, itr->w});
    s.erase(itr);
  }
  Seg1::build(1, 1, len), Seg2::build(1, 0, n);
  dc(1, 0, n), printf("%lld\n", f[n]);
  // for (int i = 1; i <= n; i++) {
  //   printf("%lld\n", f[i]);
  // }
}
