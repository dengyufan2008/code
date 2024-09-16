#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("sinner.in");
ofstream cout("sinner.out");

const LL kMaxN = 1e5 + 1, kMaxM = 3e5 + 1, kInf = 1e18;
int n, m, d[kMaxN];
LL ans;
vector<pair<int, int>> h[kMaxN];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

class Treap {
  struct V {
    LL w, s0, s1, t;
    int c, l, r;
  } v[kMaxN << 1];
  int k, s;

  void Update(int p) {
    v[p].s0 = v[v[p].r].s0, v[p].s1 = v[v[p].r].s1;
    if (v[v[p].r].c & 1) {
      v[p].s0 += v[v[p].l].s0, v[p].s1 += v[v[p].l].s1 + v[p].w;
    } else {
      v[p].s0 += v[v[p].l].s1 + v[p].w, v[p].s1 += v[v[p].l].s0;
    }
    v[p].c = v[v[p].l].c + v[v[p].r].c + 1;
  }

  pair<int, int> Split(int p, LL w) {
    if (!p) {
      return {0, 0};
    }
    if (v[p].w <= w) {
      auto x = Split(v[p].r, w);
      v[p].r = x.first, Update(p);
      return {p, x.second};
    } else {
      auto x = Split(v[p].l, w);
      v[p].l = x.second, Update(p);
      return {x.first, p};
    }
  }

  int Merge(int p, int q) {
    if (!p || !q) {
      return p | q;
    }
    if (v[p].t <= v[q].t) {
      v[p].r = Merge(v[p].r, q);
      return Update(p), p;
    } else {
      v[q].l = Merge(p, v[q].l);
      return Update(q), q;
    }
  }

 public:
  void Insert(LL w) {
    auto x = Split(s, w);
    v[++k] = {w, w, 0, Rand(), 1, 0, 0};
    x.first = Merge(x.first, k);
    s = Merge(x.first, x.second);
  }

  void Erase(LL w) {
    auto x = Split(s, w);
    auto y = Split(x.first, w - 1);
    y.second = Merge(v[y.second].l, v[y.second].r);
    x.first = Merge(y.first, y.second);
    s = Merge(x.first, x.second);
  }
  LL Ask() { return v[s].s0; }
} treap;
class Matrix {
  LL a[4][4];

 public:
  Matrix() {
    a[0][0] = a[0][1] = a[0][2] = a[0][3] = -kInf;
    a[1][0] = a[1][1] = a[1][2] = a[1][3] = -kInf;
    a[2][0] = a[2][1] = a[2][2] = a[2][3] = -kInf;
    a[3][0] = a[3][1] = a[3][2] = a[3][3] = -kInf;
  }

  Matrix(LL x, LL y) {
    a[0][0] = a[0][1] = a[0][3] = -kInf;
    a[1][1] = a[1][3] = -kInf;
    a[2][0] = a[2][2] = -kInf;
    a[3][0] = a[3][2] = a[3][3] = -kInf;
    a[0][2] = a[2][1] = a[2][3] = x;
    a[1][0] = a[1][2] = a[3][1] = y;
  }

  Matrix operator*(Matrix &x) {
    Matrix ans;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        ans.a[i][j] = -kInf;
        for (int k = 0; k < 4; k++) {
          ans.a[i][j] = max(ans.a[i][j], a[i][k] + x.a[k][j]);
        }
      }
    }
    return ans;
  }

  LL Max() {
    LL ans = -kInf;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        ans = max(ans, a[i][j]);
      }
    }
    return ans;
  }
};
class Seg {
  struct V {
    int l, r;
    Matrix w;
  } v[kMaxM << 2];
  int k, s[kMaxN];
  LL w[kMaxN], g[kMaxN];

  void Init(int &p, int l, int r, int x) {
    !p && (p = ++k);
    if (l == r) {
      v[p].w = Matrix(h[x][l].first, h[x][l].second);
      return;
    }
    int mid = l + r >> 1;
    Init(v[p].l, l, mid, x), Init(v[p].r, mid + 1, r, x);
    v[p].w = v[v[p].l].w * v[v[p].r].w;
  }

  Matrix Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].w;
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      Matrix x = Ask(v[p].l, l, mid, _l, _r);
      Matrix y = Ask(v[p].r, mid + 1, r, _l, _r);
      return x * y;
    } else if (mid >= _l) {
      return Ask(v[p].l, l, mid, _l, _r);
    } else {
      return Ask(v[p].r, mid + 1, r, _l, _r);
    }
  }

  void Change(int p, int l, int r, int x, pair<int, int> y) {
    if (l == r) {
      v[p].w = Matrix(y.first, y.second);
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(v[p].l, l, mid, x, y);
    } else {
      Change(v[p].r, mid + 1, r, x, y);
    }
    v[p].w = v[v[p].l].w * v[v[p].r].w;
  }

  LL Ask(int o, int l, int r) {
    return l <= r ? Ask(s[o], 1, d[o], l, r).Max() : 0LL;
  }

 public:
  void Init() {
    for (int i = 1; i <= n; i++) {
      Init(s[i], 1, d[i], i);
      int mid = d[i] >> 1;
      w[i] = Ask(i, 1, mid) - Ask(i, mid + 1, d[i]);
      ans += w[i];
      if (d[i] & 1) {
        LL _w = Ask(i, 1, mid + 1) - Ask(i, mid + 2, d[i]);
        g[i] = _w - w[i], treap.Insert(g[i]);
      }
    }
  }

  void Change(int o, int x, pair<int, int> y) {
    Change(s[o], 1, d[o], x, y);
    int mid = d[o] >> 1;
    ans -= w[o];
    w[o] = Ask(o, 1, mid) - Ask(o, mid + 1, d[o]);
    ans += w[o];
    if (d[o] & 1) {
      LL _w = Ask(o, 1, mid + 1) - Ask(o, mid + 2, d[o]);
      treap.Erase(g[o]), g[o] = _w - w[o], treap.Insert(g[o]);
    }
  }
} seg;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> d[i], h[i].resize(1);
    for (int j = 1, x, y; j <= d[i]; j++) {
      cin >> x >> y, h[i].push_back({x, y});
    }
  }
  seg.Init(), cin >> m;
  for (int i = 1, o, x, y, a, b; i <= m; i++) {
    cin >> o;
    if (o == 1) {
      cin >> x >> y >> a >> b;
      seg.Change(x, y, {a, b});
    } else {
      cout << ans + treap.Ask() << '\n';
    }
  }
  return 0;
}
