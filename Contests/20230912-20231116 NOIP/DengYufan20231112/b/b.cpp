#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 1e6 + 2;
LL b[kMaxN];
struct Seg {
  struct V {
    LL d, s, t;
  } v[kMaxN << 2];

  void Init(LL p, LL l, LL r) {
    v[p].t = 0;
    if (l == r) {
      v[p].d = v[p].s = b[l];
      return;
    }
    LL mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    v[p].d = max(v[p << 1].d, v[p << 1 | 1].d);
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  }

  void Pushdown(LL p, LL l, LL r) {
    LL mid = l + r >> 1;
    if (v[p].t) {
      v[p << 1].d = v[p << 1].t = v[p].t, v[p << 1].s = v[p].t * (mid - l + 1);
      v[p << 1 | 1].d = v[p << 1 | 1].t = v[p].t, v[p << 1 | 1].s = v[p].t * (r - mid);
      v[p].t = 0;
    }
  }

  void Change(LL p, LL l, LL r, LL _l, LL _r, LL k) {
    if (l >= _l && r <= _r) {
      v[p].d = v[p].t = k, v[p].s = k * (r - l + 1);
      return;
    }
    Pushdown(p, l, r);
    LL mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, k);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, k);
    }
    v[p].d = max(v[p << 1].d, v[p << 1 | 1].d);
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  }

  LL Find(LL p, LL l, LL r, LL _l, LL _r, LL k, bool o) {  // 0:Left 1:Right
    if (l == r) {
      return l;
    }
    Pushdown(p, l, r);
    LL mid = l + r >> 1;
    if (v[p << 1].d >= k && v[p << 1 | 1].d < k) {
      return Find(p << 1, l, mid, _l, _r, k, o);
    } else if (v[p << 1].d < k && v[p << 1 | 1].d >= k) {
      return Find(p << 1 | 1, mid + 1, r, _l, _r, k, o);
    } else if (v[p << 1].d < k && v[p << 1 | 1].d < k) {
      return o ? l - 1 : r + 1;
    } else if (o) {
      return Find(p << 1 | 1, mid + 1, r, _l, _r, k, o);
    } else {
      return Find(p << 1, l, mid, _l, _r, k, o);
    }
  }

  LL Max(LL p, LL l, LL r, LL _l, LL _r) {
    if (l >= _l && r <= _r) {
      return v[p].d;
    }
    Pushdown(p, l, r);
    LL mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans = max(ans, Max(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = max(ans, Max(p << 1 | 1, mid + 1, r, _l, _r));
    }
    return ans;
  }

  LL Sum(LL p, LL l, LL r, LL _l, LL _r) {
    if (l >= _l && r <= _r) {
      return v[p].s;
    }
    Pushdown(p, l, r);
    LL mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans += Sum(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Sum(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }
} seg[2];
LL t, n, m, mx;
LL s, a[kMaxN];

LL Read() {
  LL x = 0, c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

int main() {
  // freopen("b.in", "r", stdin);
  // freopen("b.out", "w", stdout);
  t = Read();
  while (t--) {
    n = Read(), s = mx = 0;
    for (LL i = 1; i <= n; i++) {
      a[i] = Read(), s += a[i], b[i] = max(b[i - 1], a[i]);
      if (a[mx] < a[i]) {
        mx = i;
      }
    }
    seg[0].Init(1, 1, n), b[n + 1] = 0;
    for (LL i = n, x = 0; i >= 1; i--) {
      b[i] = max(b[i + 1], a[i]);
    }
    seg[1].Init(1, 1, n);
    m = Read();
    for (LL i = 1, x, y; i <= m; i++) {
      x = Read(), y = Read();
      s += y, a[x] += y;
      if (a[mx] < a[x]) {
        mx = x;
      }
      if (x == 1 || seg[0].Max(1, 1, n, 1, x - 1) < a[x]) {
        LL t = x < n ? seg[0].Find(1, 1, n, x + 1, n, a[x], 0) : n + 1;
        if (x < t) {
          seg[0].Change(1, 1, n, x, t - 1, a[x]);
        }
      }
      if (x == n || seg[1].Max(1, 1, n, x + 1, n) < a[x]) {
        LL t = x > 1 ? seg[1].Find(1, 1, n, 1, x - 1, a[x], 1) : 0;
        if (t < x) {
          seg[1].Change(1, 1, n, t + 1, x, a[x]);
        }
      }
      LL ans = seg[0].Sum(1, 1, n, 1, mx) - s;
      if (mx < n) {
        ans += seg[1].Sum(1, 1, n, mx + 1, n);
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
