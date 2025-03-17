#include <fstream>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const int kMaxN = 2e5 + 1;
struct V {
  int l, r, mid, f, s[2];
} v[kMaxN << 1];
int n, m, a[kMaxN];

class Seg {
  struct V {
    pair<int, int> mn;
    int t;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].t = 0;
    if (l == r) {
      v[p].mn = {a[l], l};
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
  }

  void Add(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      v[p].mn.first += w, v[p].t += w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
    v[p].mn.first += v[p].t;
  }

  pair<int, int> Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].mn;
    }
    int mid = l + r >> 1;
    pair<int, int> ans = {n, 0};
    if (mid >= _l) {
      ans = min(ans, Ask(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = min(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
    }
    ans.first += v[p].t;
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  void Add(int l, int r, int w) { Add(1, 1, n, l, r, w); }
  int Ask(int l, int r) { return Ask(1, 1, n, l, r).second; }
} seg;

class Bit1 {  // 内部
  struct V {
    LL a, b, c;  // aL + bR + c
    void operator+=(V x) {
      a += x.a, b += x.b, c += x.c;
    }
    V operator-(V x) {
      return {a - x.a, b - x.b, c - x.c};
    }
  } vl[kMaxN], vr[kMaxN];  // 以 l/r 为索引

  void Add(V *v, int x, V y) {
    for (int i = x; i <= n; i += i & -i) {
      v[i] += y;
    }
  }

  V Ask(V *v, int x) {
    V ans = {};
    for (int i = x; i >= 1; i -= i & -i) {
      ans += v[i];
    }
    return ans;
  }

 public:
  void Add(int l, int mid, int r, int w, bool o) {
    if (o) {  // 右儿子
      V v = {0, (mid - l + 1) * w, 1LL * (mid - l + 1) * (-r + 1) * w};
      Add(vl, mid + 1, v), Add(vr, r, v);
    } else {  // 左儿子
      V v = {-(r - mid) * w, 0, 1LL * (l + 1) * (r - mid) * w};
      Add(vl, l, v), Add(vr, mid, v);
    }
  }

  V Ask(int l, int r, bool o) {
    if (l > r) {
      return {};
    } else if (o) {  // vr
      return Ask(vr, r) - Ask(vr, l - 1);
    } else {  // vl
      return Ask(vl, r) - Ask(vl, l - 1);
    }
  }
} bit1;

class Bit2 {  // 修正
  struct V {
    LL o, l, r, lr;  // 一个区间的贡献为 1, l, r, l*r
    void operator+=(V x) {
      o += x.o, l += x.l, r += x.r, lr += x.lr;
    }
    V operator-(V x) {
      return {o - x.o, l - x.l, r - x.r, lr - x.lr};
    }
  } vl[kMaxN], vr[kMaxN], vmid[kMaxN];  // 以 l/r/mid 为索引

  void Add(V *v, int x, V y) {
    for (int i = x; i <= n; i += i & -i) {
      v[i] += y;
    }
  }

  V Ask(V *v, int x) {
    V ans = {};
    for (int i = x; i >= 1; i -= i & -i) {
      ans += v[i];
    }
    return ans;
  }

 public:
  void Add(int l, int mid, int r, int w) {
    V v = {w, l * w, r * w, 1LL * l * r * w};
    Add(vl, l, v), Add(vr, r, v), Add(vmid, mid, v);
  }

  V Ask(int l, int r, int o) {
    if (l > r) {
      return {};
    } else if (o == 0) {
      return Ask(vl, r) - Ask(vl, l - 1);
    } else if (o == 1) {
      return Ask(vr, r) - Ask(vr, l - 1);
    } else {
      return Ask(vmid, r) - Ask(vmid, l - 1);
    }
  }
} bit2;

void Init(int x) {
  if (v[x].l == v[x].r) {
    return;
  }
  v[x].mid = v[v[x].s[0]].r;
  a[v[x].mid] = a[v[v[x].f].mid] + 1;
  v[v[x].s[0]].f = v[v[x].s[1]].f = x;
  Init(v[x].s[0]), Init(v[x].s[1]);
  bit1.Add(v[x].l, v[x].mid, v[x].r, 1, 0);
  bit1.Add(v[x].l, v[x].mid, v[x].r, 1, 1);
  bit2.Add(v[x].l, v[x].mid, v[x].r, 1);
}

void Add(int x, int w) {
  if (x) {
    if (v[x].l < v[x].r) {
      bit2.Add(v[x].l, v[x].mid, v[x].r, w);
    }
    if (v[x].f) {
      bool o = v[v[x].f].s[1] == x;
      x = v[x].f;
      bit1.Add(v[x].l, v[x].mid, v[x].r, w, o);
    }
  }
}

void Rotate(int x) {
  if (!v[x].f) {
    return;
  }
  bool o = v[v[x].f].s[1] == x;
  int y = x;
  x = v[x].f, Add(x, -1), Add(y, -1);
  Add(v[x].s[!o], -1), Add(v[y].s[0], -1), Add(v[y].s[1], -1);

  v[x].s[o] = v[y].s[!o], v[y].s[!o] = x;
  v[v[x].s[o]].f = x, v[y].f = v[x].f, v[x].f = y;
  v[v[y].f].s[v[v[y].f].s[1] == x] = y;

  v[y].l = v[x].l, v[y].r = v[x].r;
  if (o) {  // x 是 y 的左儿子
    v[x].l = v[y].l, v[x].r = v[y].mid;
    seg.Add(v[x].l, v[x].mid, 1), seg.Add(v[y].mid, v[y].r - 1, -1);
  } else {  // x 是 y 的右儿子
    v[x].l = v[y].mid + 1, v[x].r = v[y].r;
    seg.Add(v[x].mid, v[x].r - 1, 1), seg.Add(v[y].l, v[y].mid, -1);
  }

  Add(y, 1), Add(x, 1);
  Add(v[y].s[o], 1), Add(v[x].s[0], 1), Add(v[x].s[1], 1);
}

LL Ask(int l, int r) {
  if (l == r) {
    return 1;
  } else if (l == 1 && r == n) {
    auto e = bit1.Ask(1, n, 0);
    return e.a * l + e.b * r + e.c + 1;
  }
  int t = seg.Ask(l, r - 1), x = a[t];
  if (v[x].l == l && v[x].r == r) {
    if (v[v[x].f].s[1] == x) {  // 右儿子
      auto e = bit1.Ask(l, r, 0);
      return e.a * l + e.b * r + e.c - (l - v[v[x].f].l - 1);
    } else {  // 左儿子
      auto e = bit1.Ask(l, r, 1);
      return e.a * l + e.b * r + e.c - (v[v[x].f].r - r - 1);
    }
  }
  if (v[x].l == l) {
    t = l - 1;
  } else if (v[x].r == r) {
    t = r;
  }
  LL ans = 0;
  auto e = bit1.Ask(l, t, 0);
  e += bit1.Ask(t + 1, r, 1);
  ans += e.a * l + e.b * r + e.c;
  auto el = bit2.Ask(l - 1, t - 1, 2) - bit2.Ask(l, t, 0);
  auto er = bit2.Ask(t + 1, r, 2) - bit2.Ask(t + 1, r, 1);
  el += er;
  ans -= el.lr - el.l * (r + 1) - el.r * (l - 1) + el.o * (l - 1) * (r + 1);
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i < n << 1; i++) {
    cin >> v[i].l >> v[i].r >> v[i].s[0] >> v[i].s[1];
    if (v[i].l == 1 && v[i].r == n) {
      v[0].s[1] = i;
    }
  }
  Init(v[0].s[1]), seg.Init();
  for (int i = 1; i < n << 1; i++) {
    a[v[i].mid] = i;
  }
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      Rotate(x);
    } else {
      cin >> y;
      cout << Ask(x, y) << '\n';
    }
  }
  return 0;
}
