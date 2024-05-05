#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

ifstream cin("party.in");
ofstream cout("party.out");

const int kMaxN = 2e5 + 1, kInf = 1e9;
struct V {
  int s, d, f, l, r;
  vector<int> e;
} v[kMaxN];
int n, w, s, a[kMaxN];
long long t;
double ans;
struct Mx {
  int p, w;
  bool operator<(Mx mx) const {
    return w < mx.w;
  }
};
class Seg {
  struct V {
    Mx d, s;
    int t, c;
  } v[kMaxN << 2];

  void TagD(int p, int t) { v[p].t += t, v[p].d.w += t; }
  void TagS(int p, int c) { v[p].c += c, v[p].s.w += c; }

  void Pushdown(int p) {
    if (v[p].t) {
      TagD(p << 1, v[p].t), TagD(p << 1 | 1, v[p].t);
      v[p].t = 0;
    }
    if (v[p].c) {
      TagS(p << 1, v[p].c), TagS(p << 1 | 1, v[p].c);
      v[p].c = 0;
    }
  }

  void Pushup(int p) {
    v[p].d = max(v[p << 1].d, v[p << 1 | 1].d);
    v[p].s = max(v[p << 1].s, v[p << 1 | 1].s);
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = {{l, ::v[l].d}, {l, -kInf}, 0, ::v[l].s};
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    Pushup(p);
  }

  void Set(int p, int l, int r, int x, bool b) {
    if (l == r) {
      v[p].s.w = b ? ::v[l].s : -kInf;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Set(p << 1, l, mid, x, b);
    } else {
      Set(p << 1 | 1, mid + 1, r, x, b);
    }
    Pushup(p);
  }

  void Add(int p, int l, int r, int _l, int _r, int t, int c) {
    if (l >= _l && r <= _r) {
      return TagD(p, t), TagS(p, c);
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, t, c);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, t, c);
    }
    Pushup(p);
  }

 public:
  void Init() { Init(1, 1, n); }
  void Set(int x, bool b) { Set(1, 1, n, x, b); }
  void AddS(int l, int r, int x) { Add(1, 1, n, l, r, 0, x); }
  void AddD(int l, int r, int x) { Add(1, 1, n, l, r, x, 0); }
  Mx MaxS() { return v[1].s; }
  Mx MaxD() {
    Mx ans = v[1].d;
    Set(v[1].d.p, 0);
    AddD(v[1].d.p, v[1].d.p, -v[1].d.w);
    return ans;
  }
} seg;

void R(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      R(x, i);
      v[x].s += v[i].s, mx = max(mx, v[i].s);
    }
  }
  if (max(mx, n - v[x].s) * 2 <= n) {
    s = x;
  }
}

void S(int f, int x) {
  v[x].f = f, v[x].s = 1, t += v[x].d;
  for (int &i : v[x].e) {
    if (i != f) {
      v[i].d = v[x].d + 1;
      S(x, i), v[x].s += v[i].s;
      if (v[x].e[0] == f || v[v[x].e[0]].s < v[i].s) {
        swap(v[x].e[0], i);
      }
    }
  }
}

void T(int f, int x, int l) {
  static int k = 0;
  v[x].l = l, v[x].r = ++k, a[k] = x;
  if (!v[x].e.empty() && v[x].e[0] != f) {
    T(x, v[x].e[0], l);
  }
  for (int i : v[x].e) {
    if (i != f && i != v[x].e[0]) {
      T(x, i, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> w;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  R(0, 1), S(0, s), T(0, s, s);
  seg.Init();
  for (int i : v[s].e) {
    seg.Set(v[i].r, 1);
  }
  for (int i = n; i >= 1; i--) {
    ans = max(ans, sqrt(i) * w - t);
    Mx x = seg.MaxD();  // Remove
    t -= x.w;
    for (int j = x.p; j; j = v[v[j].l].f) {
      seg.AddS(v[v[j].l].r, v[j].r, -1);
    }
    Mx y = seg.MaxS();
    if (y.w * 2 > i) {
      t += i - y.w * 2;
      for (int i : v[s].e) {
        seg.Set(v[i].r, 0);
      }
      s = y.p, seg.AddD(1, n, 1);
      seg.AddD(v[s].r, v[s].r + v[s].s - 1, -2);
      for (int i : v[s].e) {
        seg.Set(v[i].r, 1);
      }
    }
  }
  cout << fixed << setprecision(2) << ans << '\n';
  return 0;
}
