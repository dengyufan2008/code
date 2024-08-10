#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
struct V {
  int r, s, d, f[kMaxL];
  vector<int> e;
} v1[kMaxN], v2[kMaxN];
struct Q {
  int x, y, l1, l2;
} q[kMaxN];
int t, n, m;
LL ans;
vector<pair<int, int>> w[kMaxN];
vector<int> p[kMaxN];

class Seg1 {
  struct V {
    int l, r;
    LL s, t;
  } v[kMaxN * 256];
  int h, k, s[kMaxN];

  void Add(int &p, int l, int r, int _l, int _r, int x) {
    v[++k] = v[p], p = k;
    if (l >= _l && r <= _r) {
      v[p].s += x * (r - l + 1), v[p].t += x;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(v[p].l, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Add(v[p].r, mid + 1, r, _l, _r, x);
    }
    v[p].s = v[v[p].l].s + v[v[p].r].s + v[p].t * (r - l + 1);
  }

  int Ask(int p, int l, int r, int x) {
    if (!p) {
      return 0;
    } else if (l == r) {
      return v[p].s;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      return v[p].t + Ask(v[p].l, l, mid, x);
    } else {
      return v[p].t + Ask(v[p].r, mid + 1, r, x);
    }
  }

 public:
  void Init() { k = 0; }
  void Forward() { h++, s[h] = s[h - 1]; }
  void Backward() { h--; }
  int Ask(int x) { return x >= 1 && x <= n ? Ask(s[h], 1, n, x) : 0; }

  void Add(int x, int y, int z) {
    if (x >= 1 && y <= n && x <= y) {
      Add(s[h], 1, n, x, y, z);
    }
  }
} seg1;

class Seg2 {
  struct V {
    int l, r;
    LL s, t;
  } v[kMaxN * 128];
  int h, k, s[kMaxN];

  void Add(int &p, int l, int r, int x, int y) {
    v[++k] = v[p], p = k;
    if (l == r) {
      v[p].s += y, v[p].t += y;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Add(v[p].l, l, mid, x, y);
    } else {
      Add(v[p].r, mid + 1, r, x, y);
    }
    v[p].s = v[v[p].l].s + v[v[p].r].s + v[p].t * (r - l + 1);
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (!p) {
      return 0;
    } else if (l >= _l && r <= _r) {
      return v[p].s;
    }
    int mid = l + r >> 1, ans = v[p].t * (min(r, _r) - max(l, _l) + 1);
    if (mid >= _l) {
      ans += Ask(v[p].l, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(v[p].r, mid + 1, r, _l, _r);
    }
    return ans;
  }

 public:
  void Init() { k = 0; }
  void Forward() { h++, s[h] = s[h - 1]; }
  void Backward() { h--; }
  void Add(int x, int y) { x >= 1 && x <= n ? Add(s[h], 1, n, x, y) : void(); }

  int Ask(int x, int y) {
    if (x >= 1 && y <= n && x <= y) {
      return Ask(s[h], 1, n, x, y);
    }
    return 0;
  }
} seg2;

class Seg3 {
  struct V {
    LL s, t;
  } v[kMaxN * 4];

  void Add(int p, int l, int r, int _l, int _r, int x) {
    if (l >= _l && r <= _r) {
      v[p].s += x * (r - l + 1), v[p].t += x;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
    v[p].s = v[p << 1].s + v[p << 1 | 1].s + v[p].t * (r - l + 1);
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (!p) {
      return 0;
    } else if (l >= _l && r <= _r) {
      return v[p].s;
    }
    int mid = l + r >> 1, ans = v[p].t * (min(r, _r) - max(l, _l) + 1);
    if (mid >= _l) {
      ans += Ask(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }

 public:
  void Add(int x, int y, int z) {
    if (x >= 1 && y <= n && x <= y) {
      Add(1, 1, n, x, y, z);
    }
  }

  void Add(int x, int z) { Add(x, x, z); }

  int Ask(int x, int y) {
    if (x >= 1 && y <= n && x <= y) {
      return Ask(1, 1, n, x, y);
    }
    return 0;
  }

  int Ask(int x) { return Ask(x, x); }
} seg3;

int Lca(int x, int y, V *v) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

void CalcF(int f, int x, int k, V *v) {
  v[x].r = k++, v[x].s = 1;
  v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int i : v[x].e) {
    if (i != f) {
      CalcF(x, i, k, v), v[x].s += v[i].s, k += v[i].s;
      v[i].s = v[i].r + v[i].s - 1;
    }
  }
}

void Calc1(int f, int x) {
  seg1.Forward();
  for (int i : p[x]) {
    seg1.Add(v2[q[i].l2].r, v2[q[i].l2].s, 1);
  }
  for (auto i : w[x]) {
    Q _q = q[i.first];
    int o = seg1.Ask(v2[_q.x].r) + seg1.Ask(v2[_q.y].r);
    o -= seg1.Ask(v2[_q.l2].r) + seg1.Ask(v2[v2[_q.l2].f[0]].r);
    ans += i.second * o;
  }
  for (int i : v1[x].e) {
    if (i != f) {
      Calc1(x, i);
    }
  }
  seg1.Backward();
}

void Calc2(int f, int x) {
  seg2.Forward();
  for (int i : p[x]) {
    Q _q = q[i];
    seg2.Add(v2[_q.x].r, 1), seg2.Add(v2[_q.y].r, 1);
    seg2.Add(v2[_q.l2].r, -2);
  }
  for (auto i : w[x]) {
    ans += i.second * seg2.Ask(v2[q[i.first].l2].r, v2[q[i.first].l2].s);
  }
  for (int i : v1[x].e) {
    if (i != f) {
      Calc2(x, i);
    }
  }
  seg2.Backward();
}

void Minus() {
  for (int x = 1; x <= n; x++) {
    for (int i : p[x]) {
      Q _q = q[i];
      seg3.Add(v2[_q.l2].r, v2[_q.l2].s, 1);
    }
    for (int i : p[x]) {
      Q _q = q[i];
      ans -= seg3.Ask(v2[_q.x].r) + seg3.Ask(v2[_q.y].r);
      ans += seg3.Ask(v2[_q.l2].r) + seg3.Ask(v2[v2[_q.l2].f[0]].r);
      seg3.Add(v2[_q.l2].r, v2[_q.l2].s, -1);
    }
    for (int i : p[x]) {
      Q _q = q[i];
      seg3.Add(v2[_q.x].r, 1), seg3.Add(v2[_q.y].r, 1);
      seg3.Add(v2[_q.l2].r, -2);
    }
    for (auto i : p[x]) {
      Q _q = q[i];
      ans -= seg3.Ask(v2[_q.l2].r, v2[_q.l2].s);
      seg3.Add(v2[_q.x].r, -1), seg3.Add(v2[_q.y].r, -1);
      seg3.Add(v2[_q.l2].r, 2);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    seg1.Init(), seg2.Init();
    for (int i = 1; i <= n; i++) {
      v1[i].e.clear(), v2[i].e.clear();
      w[i].clear(), p[i].clear();
    }
    cin >> n >> m;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v1[x].e.push_back(y), v1[y].e.push_back(x);
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v2[x].e.push_back(y), v2[y].e.push_back(x);
    }
    CalcF(0, 1, 1, v1), CalcF(0, 1, 1, v2);
    for (int i = 1; i <= m; i++) {
      cin >> q[i].x >> q[i].y;
      q[i].l1 = Lca(q[i].x, q[i].y, v1);
      q[i].l2 = Lca(q[i].x, q[i].y, v2);
      p[q[i].l1].push_back(i);
      w[q[i].x].push_back({i, 1});
      w[q[i].y].push_back({i, 1});
      w[q[i].l1].push_back({i, -1});
      w[v1[q[i].l1].f[0]].push_back({i, -1});
    }
    Calc1(0, 1), Calc2(0, 1), Minus();
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
