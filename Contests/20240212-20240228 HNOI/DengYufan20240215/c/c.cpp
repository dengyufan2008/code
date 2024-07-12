#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#define LL long long

using namespace std;

const LL kMaxN = 1e5 + 1, kMaxV = 1e13;
struct A {
  int l, r;
  LL w;
};
struct B {
  int l, r;
  LL k, b;
  bool operator<(const B &b) const {
    return r < b.r;
  }
};
int n, m;
LL w[kMaxN], ans[kMaxN];
vector<A> a;
vector<B> s, t;
class H1 {
  struct V {
    int d, l, r;
  } v[kMaxN << 5];
  int n, s;

  void Change(int &p, LL l, LL r, LL x, int k) {
    !p && (p = ++n);
    if (l == r) {
      v[p].d = k;
      return;
    }
    LL mid = l + r >> 1;
    if (mid >= x) {
      Change(v[p].l, l, mid, x, k);
    } else {
      Change(v[p].r, mid + 1, r, x, k);
    }
    v[p].d = max(v[v[p].l].d, v[v[p].r].d);
  }

  int Ask(int p, LL l, LL r, LL _l, LL _r) {
    if (!p) {
      return 0;
    } else if (l >= _l && r <= _r) {
      return v[p].d;
    }
    LL mid = l + r >> 1;
    int ans = 0;
    if (mid >= _l) {
      ans = max(ans, Ask(v[p].l, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = max(ans, Ask(v[p].r, mid + 1, r, _l, _r));
    }
    return ans;
  }

 public:
  void Change(LL x, int k) { Change(s, 1, kMaxV, x, k); }
  int Ask(LL l, LL r) { return Ask(s, 1, kMaxV, l, r); }
} h1;
class H2 {
  int v[kMaxN << 2];
  multiset<B> s[kMaxN << 2];

  void Change(int p, int l, int r, B t, bool b) {
    if (l == r) {
      b ? s[l].insert(t) : s[l].erase(--s[l].end());
      v[p] = s[l].empty() ? 0 : (--s[l].end())->r;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= t.l) {
      Change(p << 1, l, mid, t, b);
    } else {
      Change(p << 1 | 1, mid + 1, r, t, b);
    }
    v[p] = max(v[p << 1], v[p << 1 | 1]);
  }

  B Ask(int p, int l, int r, int x) {
    if (l == r) {
      return s[l].empty() ? (B){} : *--s[l].end();
    }
    int mid = l + r >> 1;
    if (v[p] == v[p << 1]) {
      return Ask(p << 1, l, mid, x);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
  }

  B Ask(int p, int l, int r, int _l, int _r, int x) {
    if (l >= _l && r <= _r) {
      return Ask(p, l, r, x);
    }
    int mid = l + r >> 1;
    B ans = {};
    if (mid >= _l) {
      ans = max(ans, Ask(p << 1, l, mid, _l, _r, x));
    }
    if (mid < _r) {
      ans = max(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r, x));
    }
    v[p] = max(v[p << 1], v[p << 1 | 1]);
    return ans;
  }

 public:
  void Insert(B t) { Change(1, 1, n, t, 1); }

  B Ask(int x) {
    B ans = Ask(1, 1, n, 1, x, x);
    if (ans.r >= x) {
      Change(1, 1, n, ans, 0);
    }
    return ans;
  }
} h2;
class H3 {
  struct S {
    int l, r;
    mutable int t;
    mutable LL w;
    bool operator<(const S &s) const {
      return l < s.l;
    }
  };
  set<S> s;

  auto Split(int x) {
    auto p = --s.upper_bound({x});
    int l = p->l, r = p->r, t = p->t;
    LL w = p->w;
    if (r == x) {
      return p;
    }
    s.erase(p), s.insert({x + 1, r, t, w});
    return s.insert({l, x, t, w}).first;
  }

 public:
  H3() { s.insert({1, kMaxN - 1, 1, kMaxV}); }

  void CheckMin(int l, int r, int t, LL w) {
    auto q = Split(r), p = Split(l - 1), o = q;
    bool b = 0;
    for (auto i = q; i != p; i--) {
      if (i->w > w) {
        o = i, b = 1;
        if (max(i->l + m, i->t) < t) {
          h2.Insert({max(i->l + m, i->t), t - 1, i->w, i->w * (1 - i->l)});
        }
      } else {
        break;
      }
    }
    if (b) {
      l = o->l, s.erase(o, ++q), s.insert({l, r, t, w});
    }
  }
} h3;
class H4 {
  struct V {
    LL k, b;
  } v[kMaxN << 2];
  int l, r;

  void Clear(int p, int l, int r) {
    v[p].k = v[p].b = 0;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Clear(p << 1, l, mid);
    Clear(p << 1 | 1, mid + 1, r);
  }

  LL F(LL k, LL b, LL x) { return k * x + b; }

  void Add(int p, int l, int r, LL k, LL b) {
    if (l == r) {
      if (F(v[p].k, v[p].b, l) < F(k, b, l)) {
        v[p] = {k, b};
      }
      return;
    }
    int mid = l + r >> 1;
    if (F(v[p].k, v[p].b, mid) < F(k, b, mid)) {
      swap(v[p].k, k), swap(v[p].b, b);
    }
    if (F(v[p].k, v[p].b, l) < F(k, b, l)) {
      Add(p << 1, l, mid, k, b);
    }
    if (F(v[p].k, v[p].b, r) < F(k, b, r)) {
      Add(p << 1 | 1, mid + 1, r, k, b);
    }
  }

  LL Ask(int p, int l, int r, int x) {
    LL ans = F(v[p].k, v[p].b, x);
    if (l != r) {
      int mid = l + r >> 1;
      if (mid >= x) {
        ans = max(ans, Ask(p << 1, l, mid, x));
      } else {
        ans = max(ans, Ask(p << 1 | 1, mid + 1, r, x));
      }
    }
    return ans;
  }

 public:
  void Clear(int _l, int _r) { l = _l, r = _r, Clear(1, l, r); }
  void Add(LL k, LL b) { Add(1, l, r, k, b); }
  LL Ask(int x) { return Ask(1, l, r, x); }
} h4;

void Divide(int l, int r) {
  if (l > r) {
    return;
  }
  int mid = l + r >> 1;
  s.clear(), t.clear();
  for (B i = h2.Ask(mid); i.r >= mid; i = h2.Ask(mid)) {
    s.push_back({i.l, mid, i.k, i.b});
    if (i.r > mid) {
      t.push_back({mid + 1, i.r, i.k, i.b});
    }
  }
  if (l <= mid) {
    sort(s.begin(), s.end(), [](B i, B j) { return i.l < j.l; });
    h4.Clear(l, mid);
    for (int i = l, j = 0; i <= mid; i++) {
      for (; j < s.size() && s[j].l == i; j++) {
        h4.Add(s[j].k, s[j].b);
      }
      ans[i] = max(ans[i], h4.Ask(i));
    }
  }
  if (mid < r) {
    sort(t.begin(), t.end(), [](B i, B j) { return i.r > j.r; });
    h4.Clear(mid + 1, r);
    for (int i = r, j = 0; i > mid; i--) {
      for (; j < t.size() && t[j].r == i; j++) {
        h4.Add(t[j].k, t[j].b);
      }
      ans[i] = max(ans[i], h4.Ask(i));
    }
  }
  Divide(l, mid - 1);
  Divide(mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }
  m--;
  for (int i = 1; i <= n; i++) {
    int j = h1.Ask(1, w[i]);
    for (; j;) {
      a.push_back({j, i, w[i] - w[j]});
      if (w[i] > w[j]) {
        j = h1.Ask(w[j] + w[i] + 1 >> 1, w[i]);
      } else {
        break;
      }
    }
    j = h1.Ask(w[i], kMaxV);
    for (; j;) {
      a.push_back({j, i, w[j] - w[i]});
      if (w[j] > w[i]) {
        j = h1.Ask(w[i], w[i] + w[j] >> 1);
      } else {
        break;
      }
    }
    h1.Change(w[i], i);
  }
  for (A i : a) {
    h3.CheckMin(1, i.l, i.r, i.w);
  }
  h3.CheckMin(1, n, n + 1, 0);
  Divide(1, n);
  for (int i = m + 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
