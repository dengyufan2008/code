#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#define ULL unsigned long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
struct V {
  int p, s, r, d, f[kMaxL];
  vector<int> e;
} v[kMaxN];
int t, n, m, u, p[kMaxN];
ULL a[kMaxN], s[kMaxN];
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

class D {
  struct V {
    int l, r, s;
  } v[kMaxN * 48];
  int k, s[kMaxN];

  void Change(int &p, int l, int r, int x, int y) {
    !p && (v[++k] = v[0], p = k);
    if (l == r) {
      v[p].s = y;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(v[p].l, l, mid, x, y);
    } else {
      Change(v[p].r, mid + 1, r, x, y);
    }
    v[p].s = v[v[p].l].s + v[v[p].r].s;
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (!p) {
      return 0;
    } else if (l >= _l && r <= _r) {
      return v[p].s;
    }
    int mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans += Ask(v[p].l, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(v[p].r, mid + 1, r, _l, _r);
    }
    return ans;
  }

  int FindVal(int p, int l, int r) {
    if (!v[p].s) {
      return 0;
    } else if (l == r) {
      return l;
    }
    int mid = l + r >> 1, ans = 0;
    ans ^= FindVal(v[p].l, l, mid);
    ans ^= FindVal(v[p].r, mid + 1, r);
    return ans;
  }

  int FindRange(int p, int l, int r, int _l, int _r) {
    if (!v[p].s) {
      return 0;
    } else if (l >= _l && r <= _r) {
      return FindVal(p, l, r);
    }
    int mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans ^= FindRange(v[p].l, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans ^= FindRange(v[p].r, mid + 1, r, _l, _r);
    }
    return ans;
  }

 public:
  void Clear() { k = 0, fill(&s[1], &s[n] + 1, 0); }
  void Insert(int o, int x) { Change(s[o], 1, n, x, 1); }
  void Erase(int o, int x) { Change(s[o], 1, n, x, 0); }
  int Ask(int o, int l, int r) { return Ask(s[o], 1, n, l, r); }
  int Find(int o, int l, int r) { return FindRange(s[o], 1, n, l, r); }
} d;

class L {
  struct E {
    int x;
    bool operator<(const E &e) const {
      return ::v[x].d < ::v[e.x].d;
    }
  };
  struct V {
    E mx, mn;
  } v[kMaxN * 4];

  void Change(int p, int l, int r, int x, int y) {
    if (l == r) {
      v[p].mx = v[p].mn = {y};
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, y);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, y);
    }
    v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
  }

  V Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      V x = Ask(p << 1, l, mid, _l, _r);
      V y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
      return {max(x.mx, y.mx), min(x.mn, y.mn)};
    } else if (mid >= _l) {
      return Ask(p << 1, l, mid, _l, _r);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
  }

 public:
  void Change(int x, int y) { Change(1, 1, n, x, y); }
  pair<int, int> Ask(int l, int r) {
    V ans = Ask(1, 1, n, l, r);
    return {ans.mx.x, ans.mn.x};
  }
} l;

class H {
  ULL v[kMaxN];

  void Xor(int x, ULL w) {
    for (int i = x; i <= n; i += i & -i) {
      v[i] ^= w;
    }
  }

 public:
  void Clear() { fill(&v[1], &v[n] + 1, 0); }
  void Xor(int l, int r, ULL w) { Xor(l, w), Xor(r + 1, w); }
  ULL Ask(int x) {
    ULL ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans ^= v[i];
    }
    return ans;
  }
} h;

void T(int f, int x) {
  v[x].s = 1, v[x].r = ++u;
  v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s += v[i].s;
    }
  }
}

int F(int x, int d) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= d) {
      x = v[x].f[i];
    }
  }
  return x;
}

void Swap(int x, int y) {
  if (v[x].d != v[y].d) {
    d.Erase(v[x].d, v[x].p), d.Erase(v[y].d, v[y].p);
    d.Insert(v[x].d, v[y].p), d.Insert(v[y].d, v[x].p);
  }
  l.Change(v[x].p, y), l.Change(v[y].p, x);
  h.Xor(v[x].r, v[x].r + v[x].s - 1, a[v[x].p] ^ a[v[y].p]);
  h.Xor(v[y].r, v[y].r + v[y].s - 1, a[v[x].p] ^ a[v[y].p]);
  swap(v[x].p, v[y].p), swap(p[v[x].p], p[v[y].p]);
}

bool Exist(int x, int y) {
  pair<int, int> z = l.Ask(x, y);
  ULL w = h.Ask(v[z.first].r) ^ h.Ask(v[v[z.second].f[0]].r);
  w ^= s[x - 1] ^ s[y];
  if (!w) {
    return 1;
  }
  int l = v[z.second].d + 1, r = v[z.first].d;
  while (l <= r) {
    int mid = l + r >> 1;
    if (d.Ask(mid, x, y) == 2) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (d.Ask(r, x, y) != 2) {
    return 0;
  }
  w ^= h.Ask(v[z.second].r);
  w ^= h.Ask(v[p[d.Find(r, x, y) ^ v[F(z.first, r)].p]].r);
  return !w;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    u = 0, d.Clear(), h.Clear();
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].p, p[v[i].p] = i;
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    T(0, 1);
    for (int i = 1; i <= n; i++) {
      a[i] = Rand(), s[i] = s[i - 1] ^ a[i];
    }
    for (int i = 1; i <= n; i++) {
      d.Insert(v[i].d, v[i].p), l.Change(v[i].p, i);
      h.Xor(v[i].r, v[i].r + v[i].s - 1, a[v[i].p]);
    }
    cin >> m;
    for (int i = 1, o, x, y; i <= m; i++) {
      cin >> o >> x >> y;
      if (o == 1) {
        Swap(x, y);
      } else {
        cout << (Exist(x, y) ? "Yes\n" : "No\n");
      }
    }
  }
  return 0;
}
