#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("o.in");
ofstream cout("o.out");

const LL kMaxN = 2e5 + 1, kMaxM = 1e6 + 1, kMaxL = 18, kInf = 1e18;
struct E {
  int p, d, w;
} e[kMaxN << 2];
struct V {
  int et, s, f, r;
  LL w;
  bool b;
} v[kMaxN];
struct Q {
  int l, r, d;
} q[kMaxM];
int n, m, s, r, lg[kMaxN];
LL ans[kMaxM];
vector<pair<int, LL>> l, t;
vector<LL> w;
class Seg {
  LL v[kMaxN];

 public:
  Seg() { fill(&v[1], &v[kMaxN], kInf); };

  void CheckMin(int x, LL y) {
    for (int i = x; i <= n; i += i & -i) {
      v[i] = min(v[i], y);
    }
  }

  LL Ask(int x) {
    LL ans = kInf;
    for (int i = x; i >= 1; i -= i & -i) {
      ans = min(ans, v[i]);
    }
    return ans;
  }
} seg;
class Lca {
  int r[kMaxL][kMaxN], a[kMaxN];

  void Init(int f, int x) {
    static int k = 0;
    v[x].f = f, v[x].r = ++k, r[0][k] = v[f].r, a[k] = x;
    for (int i = v[x].et; i; i = e[i].p) {
      if (e[i].d != f) {
        v[e[i].d].w = v[x].w + e[i].w;
        Init(x, e[i].d);
      }
    }
  }

 public:
  void Init() {
    Init(0, 1);
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        r[i][j] = r[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          r[i][j] = min(r[i][j], r[i - 1][j + (1 << i - 1)]);
        }
      }
    }
    for (int i = 2; i < kMaxN; i++) {
      lg[i] = lg[i >> 1] + 1;
    }
  }

  int Ask(int x, int y) {
    x = v[x].r, y = v[y].r;
    x > y ? swap(x, y) : void();
    int l = lg[y - x];
    return a[min(r[l][x + 1], r[l][y - (1 << l) + 1])];
  }

  LL Dis(int x, int y) {
    return v[x].w + v[y].w - v[Ask(x, y)].w * 2;
  }
} lca;

void CalcR(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f && !v[e[i].d].b) {
      CalcR(x, e[i].d);
      v[x].s += v[e[i].d].s;
      mx = max(mx, v[e[i].d].s);
    }
  }
  if (max(mx, s - v[x].s) * 2 <= s) {
    r = x;
  }
}

void CalcD(int f, int x, LL d) {
  l.push_back({x, d});
  for (int i = v[x].et; i; i = e[i].p) {
    if (e[i].d != f && !v[e[i].d].b) {
      CalcD(x, e[i].d, d + e[i].w);
    }
  }
}

void Divide() {
  v[r].b = 1, l.clear(), CalcD(0, r, 0), sort(l.begin(), l.end());
  for (int o : {1, -1}) {
    t.clear();
    for (int i = ~o ? 0 : l.size() - 1; ~o ? i < l.size() : i >= 0; i += o) {
      for (; !t.empty() && t.back().second > l[i].second; t.pop_back()) {
      }
      if (!t.empty()) {
        LL x = t.back().first, y = l[i].first;
        w.push_back(min(x, y) << 31 | max(x, y));
      }
      t.push_back(l[i]);
    }
  }
  int _s = s, _r = r;
  for (int i = v[r].et; i; i = e[i].p) {
    if (!v[e[i].d].b) {
      s = v[e[i].d].s * 2 <= _s ? v[e[i].d].s : _s - v[_r].s;
      CalcR(0, e[i].d), Divide();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    e[i << 1] = {v[x].et, y, z}, v[x].et = i << 1;
    e[i << 1 | 1] = {v[y].et, x, z}, v[y].et = i << 1 | 1;
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r, q[i].d = i;
  }
  s = n, CalcR(0, 1), Divide();
  sort(w.begin(), w.end());
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.l < j.l || i.l == j.l && i.r < j.r;
  });
  lca.Init();
  for (int i = n, j = w.size() - 1, k = m; i >= 1; i--) {
    for (; j >= 0 && (w[j] >> 31) == i; j--) {
      seg.CheckMin(w[j] & ~(-1 << 31), lca.Dis(w[j] >> 31, w[j] & ~(-1 << 31)));
    }
    for (; k >= 1 && q[k].l == i; k--) {
      ans[q[k].d] = seg.Ask(q[k].r);
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << (ans[i] == kInf ? -1 : ans[i]) << '\n';
  }
  return 0;
}
