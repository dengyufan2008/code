#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const LL kMaxN = 1e5 + 1, kM = 3, kBase = 2333, kMod = 1e9 + 7, kInf = 1e18;
struct E {
  LL mn, mx;
};
struct V {
  int d, s, f, l, r;
  int p[kM + 2], q[kM + 2];
  vector<int> e;
} v[kMaxN];
int n, m, k, a[kMaxN], w[kMaxN];
bool b[kMaxN];  // 0:上点 1:下点
LL base, ans;

E Merge(E x, E y) { return {min(x.mn, y.mn), max(x.mx, y.mx)}; }

class Seg {
  struct V {
    E e0, e1;
    LL t0, t1;
  } v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p].t0 = v[p].t1 = 0;
    if (l == r) {
      v[p].e0.mn = v[p].e0.mx = w[a[l]];
      v[p].e1 = {kInf, -kInf};
      b[l] ? swap(v[p].e0, v[p].e1) : void();
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    v[p].e0 = Merge(v[p << 1].e0, v[p << 1 | 1].e0);
    v[p].e1 = Merge(v[p << 1].e1, v[p << 1 | 1].e1);
  }

  void Tag0(int p, LL t) { v[p].e0.mn += t, v[p].e0.mx += t, v[p].t0 += t; }
  void Tag1(int p, LL t) { v[p].e1.mn += t, v[p].e1.mx += t, v[p].t1 += t; }

  void Pushdown(int p) {
    Tag0(p << 1, v[p].t0), Tag0(p << 1 | 1, v[p].t0), v[p].t0 = 0;
    Tag1(p << 1, v[p].t1), Tag1(p << 1 | 1, v[p].t1), v[p].t1 = 0;
  }

  void Add(int p, int l, int r, int _l, int _r, int w, bool b) {
    if (l >= _l && r <= _r) {
      return Tag1(p, w), b ? void() : Tag0(p, w);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w, b);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w, b);
    }
    v[p].e0 = Merge(v[p << 1].e0, v[p << 1 | 1].e0);
    v[p].e1 = Merge(v[p << 1].e1, v[p << 1 | 1].e1);
  }

  E Ask(int p, int l, int r, int _l, int _r, bool b) {
    if (l >= _l && r <= _r) {
      return b ? v[p].e1 : Merge(v[p].e0, v[p].e1);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    E ans = {kInf, -kInf};
    if (mid >= _l) {
      ans = Merge(ans, Ask(p << 1, l, mid, _l, _r, b));
    }
    if (mid < _r) {
      ans = Merge(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r, b));
    }
    return ans;
  }

  int FindGreater(int p, int l, int r, LL s) {
    if (v[p].e1.mx < s) {
      return n + 1;
    } else if (l == r) {
      return l;
    }
    Pushdown(p);
    int mid = l + r >> 1, ans = FindGreater(p << 1, l, mid, s);
    if (ans == n + 1) {
      ans = FindGreater(p << 1 | 1, mid + 1, r, s);
    }
    return ans;
  }

  int FindGreater(int p, int l, int r, int _l, int _r, LL s) {
    if (l >= _l && r <= _r) {
      return FindGreater(p, l, r, s);
    }
    Pushdown(p);
    int mid = l + r >> 1, ans = n + 1;
    if (mid >= _l) {
      ans = FindGreater(p << 1, l, mid, _l, _r, s);
    }
    if (mid < _r && ans == n + 1) {
      ans = FindGreater(p << 1 | 1, mid + 1, r, _l, _r, s);
    }
    return ans;
  }

  int FindLess(int p, int l, int r, LL s) {
    if (v[p].e1.mn > s) {
      return n + 1;
    } else if (l == r) {
      return l;
    }
    Pushdown(p);
    int mid = l + r >> 1, ans = FindLess(p << 1, l, mid, s);
    if (ans == n + 1) {
      ans = FindLess(p << 1 | 1, mid + 1, r, s);
    }
    return ans;
  }

  int FindLess(int p, int l, int r, int _l, int _r, LL s) {
    if (l >= _l && r <= _r) {
      return FindLess(p, l, r, s);
    }
    Pushdown(p);
    int mid = l + r >> 1, ans = n + 1;
    if (mid >= _l) {
      ans = FindLess(p << 1, l, mid, _l, _r, s);
    }
    if (mid < _r && ans == n + 1) {
      ans = FindLess(p << 1 | 1, mid + 1, r, _l, _r, s);
    }
    return ans;
  }

 public:
  void Init() { Init(1, 1, n); }
  // 是否是局部的
  void Add(int l, int r, int w, bool b) { Add(1, 1, n, l, r, w, b); }
  // 是否是局部的
  E Ask(int l, int r, bool b) { return Ask(1, 1, n, l, r, b); }

  // 局部的; 0:是否先<再> 1:是否先>再<
  bool Check(int l, int r, bool o, LL s) {
    if (!o) {
      int p = FindGreater(1, 1, n, l, r, s);
      return p > r || Ask(p, r, 1).mn > s;
    } else {
      int p = FindLess(1, 1, n, l, r, s);
      return p > r || Ask(p, r, 1).mx < s;
    }
  }
} seg;

void Init(int f, int x) {
  static vector<int> _e;
  for (int i : v[x].e) {
    if (i != f) {
      _e.push_back(i);
    }
  }
  v[x].e.swap(_e), _e.clear();

  v[x].d = v[f].d + 1, v[x].s = 1, v[x].f = f;
  for (int &i : v[x].e) {
    Init(x, i), v[x].s += v[i].s;
    if (v[v[x].e[0]].s < v[i].s) {
      swap(v[x].e[0], i);
    }
  }
}

void CalcL(int x, int l) {
  v[x].l = l;
  if (v[x].e.empty()) {
    return;
  }
  CalcL(v[x].e[0], l);
  for (int i : v[x].e) {
    if (i != v[x].e[0]) {
      CalcL(i, i);
    }
  }
}

void CalcR(int x, int d) {
  if (d--) {
    for (int i : v[x].e) {
      CalcR(i, d);
    }
  } else {
    v[x].r = ++k, a[k] = x;
  }
}

void CalcR(int x) {
  CalcR(x, kM);
  for (int i : v[x].e) {
    CalcR(i);
  }
}

void CalcR() {
  static queue<int> q;
  for (q.push(1); !q.empty(); q.pop()) {
    int x = q.front();
    v[x].r = ++k, a[k] = x;
    if (v[x].d < kM) {
      for (int i : v[x].e) {
        q.push(i);
      }
    }
  }
  CalcR(1);
  for (int i = 1; i <= n; i++) {
    b[v[i].r] = v[i].d - v[v[i].l].d >= kM;
  }
}

void CalcP(int x) {
  for (int i : v[x].e) {
    CalcP(i);
  }
  v[x].p[0] = v[x].q[0] = v[x].r;
  for (int i = 1; i <= kM + 1; i++) {
    v[x].p[i] = n + 1, v[x].q[i] = 0;
    for (int j : v[x].e) {
      v[x].p[i] = min(v[x].p[i], v[j].p[i - 1]);
      v[x].q[i] = max(v[x].q[i], v[j].q[i - 1]);
    }
  }
  for (int i : v[x].e) {
    v[x].p[kM + 1] = min(v[x].p[kM + 1], v[i].p[kM + 1]);
    v[x].q[kM + 1] = max(v[x].q[kM + 1], v[i].q[kM + 1]);
  }
}

void AddChain(int x, int y, int w) {
  for (; v[x].l != v[y].l; x = v[v[x].l].f) {
    v[v[x].l].d < v[v[y].l].d ? swap(x, y) : void();
    int z = v[x].l;
    for (int i = 0; i < kM && z != x; i++) {
      seg.Add(v[z].r, v[z].r, w, 0);
      z = v[z].e[0];
    }
    seg.Add(v[z].r, v[x].r, w, z != x);
  }
  v[x].d > v[y].d ? swap(x, y) : void();
  for (int i = 0; i < kM && x != y; i++) {
    seg.Add(v[x].r, v[x].r, w, 0);
    x = v[x].e[0];
  }
  seg.Add(v[x].r, v[y].r, w, x != y);
}

void AddSub(int x, int w) {
  for (int i = 0; i <= kM + 1; i++) {
    if (v[x].p[i] <= v[x].q[i]) {
      seg.Add(v[x].p[i], v[x].q[i], w, 0);
    }
  }
}

void AddRound(int x, int d, int w) {
  int y = v[x].f;
  for (int i = 0; i <= d; i++) {
    seg.Add(v[x].p[i], v[x].q[i], w, 0);
  }
  for (int i = 1; i <= d && y; i++) {
    seg.Add(v[y].r, v[y].r, w, 0);
    for (int j = 1; j <= d - i; j++) {
      if (v[y].p[j] < v[x].p[j - 1]) {
        seg.Add(v[y].p[j], v[x].p[j - 1] - 1, w, 0);
      }
      if (v[x].q[j - 1] < v[y].q[j]) {
        seg.Add(v[x].q[j - 1] + 1, v[y].q[j], w, 0);
      }
    }
    x = y, y = v[y].f;
  }
}

// y 向 x 走一步
int Find(int x, int y) {
  int ans = 0;
  for (; v[v[x].l].d > v[v[y].l].d; x = v[v[x].l].f) {
    ans = v[x].l;
  }
  if (v[x].l == v[y].l) {
    if (v[x].d == v[y].d) {
      return ans;
    } else if (v[x].d > v[y].d) {
      return v[y].e[0];
    }
  }
  return v[y].f;
}

E AskHeavy(int x, int y) {
  E ans = {kInf, -kInf};
  for (int i = 0; i < kM && x != y; i++) {
    ans = Merge(ans, seg.Ask(v[x].r, v[x].r, 0));
    x = v[x].e[0];
  }
  return Merge(ans, seg.Ask(v[x].r, v[y].r, x != y));
}

E AskChain(int x, int y) {
  E ans = {kInf, -kInf};
  for (; v[x].l != v[y].l; x = v[v[x].l].f) {
    v[v[x].l].d < v[v[y].l].d ? swap(x, y) : void();
    ans = Merge(ans, AskHeavy(v[x].l, x));
  }
  v[x].d > v[y].d ? swap(x, y) : void();
  return Merge(ans, AskHeavy(x, y));
}

// 0:是否先<再> 1:是否先>再<
bool CheckHeavy(int x, int y, bool o, LL s) {
  bool u = 0;
  for (int i = 0; i < kM && x != y; i++) {
    LL w = seg.Ask(v[x].r, v[x].r, 0).mn;
    if (o ^ (w > s)) {  // 不符合前缀的限制
      u = 1;
    } else if (u) {  // 符合
      return 0;
    }
    x = v[x].e[0];
  }
  if (u) {
    E e = seg.Ask(v[x].r, v[y].r, x != y);
    return o && e.mx < s || !o && e.mn > s;
  }
  return x == y || seg.Check(v[x].r, v[y].r, o, s);
}

bool Check(int x, int y, LL s) {  // 是否先 < s 再 > s
  static vector<pair<E, E>> e, _e;
  e.clear(), _e.clear();
  for (; v[x].l != v[y].l;) {
    if (v[v[x].l].d > v[v[y].l].d) {
      e.push_back({AskHeavy(v[x].l, x), {v[x].r, v[v[x].l].r}});
      x = v[v[x].l].f;
    } else {
      _e.push_back({AskHeavy(v[y].l, y), {v[v[y].l].r, v[y].r}});
      y = v[v[y].l].f;
    }
  }
  if (v[x].d <= v[y].d) {
    e.push_back({AskHeavy(x, y), {v[x].r, v[y].r}});
  } else {
    e.push_back({AskHeavy(y, x), {v[x].r, v[y].r}});
  }
  reverse(_e.begin(), _e.end()), e.insert(e.end(), _e.begin(), _e.end());

  int p = -1;
  for (int i = 0; i < e.size(); i++) {
    if (e[i].first.mn < s && e[i].first.mx > s) {
      if (p == -1) {
        p = i;
      } else {
        return 0;
      }
    }
  }
  int l = 0, r = e.size() - 1;
  for (; l < e.size() && e[l].first.mx < s; l++) {
  }
  for (; r >= 0 && e[r].first.mn > s; r--) {
  }
  if (!(p == -1 && l > r || p != -1 && l == p && r == p)) {
    return 0;
  } else if (p == -1) {
    return 1;
  }
  l = e[p].second.mn, r = e[p].second.mx;
  if (l <= r) {
    return CheckHeavy(a[l], a[r], 0, s);
  } else {
    return CheckHeavy(a[r], a[l], 1, s);
  }
}

int Ask(int x, int y, int w) {
  if (x == y) {
    return 0;
  }
  LL s = seg.Ask(v[w].r, v[w].r, 0).mn;
  int w1 = Find(x, w), w2 = Find(y, w);
  E e1 = w1 ? AskChain(x, w1) : E{kInf, -kInf};
  E e2 = w2 ? AskChain(y, w2) : E{kInf, -kInf};
  if (min(e1.mn, e2.mn) > s || max(e1.mx, e2.mx) < s) {
    return 1;
  } else if (max(e1.mn, e2.mn) > s || min(e1.mx, e2.mx) < s) {
    return 2;
  }
  LL s1 = seg.Ask(v[w1].r, v[w1].r, 0).mn;
  LL s2 = seg.Ask(v[w2].r, v[w2].r, 0).mn;
  if ((s1 < s) != (s2 < s)) {
    return 3;
  }
  if (s1 < s) {
    if (Check(w1, x, s) && Check(w2, y, s)) {
      return 2;
    }
  } else {
    if (Check(x, w1, s) && Check(y, w2, s)) {
      return 2;
    }
  }
  return 3;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> base;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Init(0, 1), CalcL(1, 1), CalcR(), CalcP(1), seg.Init(), base = 1;
  for (int i = 1, o, x, y, w; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      cin >> w;
      AddChain(x, y, w);
    } else if (o == 2) {
      AddSub(x, y);
    } else if (o == 3) {
      cin >> w;
      if (y <= kM) {
        AddRound(x, y, w);
      } else {
        cout << "shit\n";
      }
    } else {
      cin >> w;
      base = base * kBase % kMod;
      ans = (ans + Ask(x, y, w) * base) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
