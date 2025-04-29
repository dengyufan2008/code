#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 2.5e5 + 1, kMaxM = kMaxN << 1, kInf = 1e18;
struct E {
  int a, b;
} e[kMaxN];
struct V {
  int c, d;
} v[kMaxN];
struct G {
  int o, x, y, z;
} g[kMaxN];
int n, m, q, k, t, w[kMaxM];
LL inite[kMaxM];
bool initv[kMaxM];

class Seg {
  struct V {
    LL s;          // 区间内 a 的和
    vector<LL> f;  // 只考虑区间内的元素, 选取 i 个 c, 认为 k=i 的最小代价
    vector<LL> w;  // 区间内前 i 小的 c 的和
  } v[kMaxM << 2];

  void Divide(vector<LL> &ans, vector<LL> &f, vector<LL> &g, int l, int r, int x, int y) {
    if (l > r || x == y) {
      for (int i = l; i <= r; i++) {
        ans[i] = f[x] + g[i - x];
      }
      return;
    }
    int mid = l + r >> 1, p = -1;
    for (int i = max(x, mid - (int)g.size() + 1); i <= min(y, mid); i++) {
      if (p == -1 || f[i] + g[mid - i] < f[p] + g[mid - p]) {
        p = i;
      }
    }
    ans[mid] = f[p] + g[mid - p];
    Divide(ans, f, g, l, mid - 1, x, p);
    Divide(ans, f, g, mid + 1, r, p, y);
  }

  void Pushup(int p) {
    int len = min((int)v[p << 1].w.size() + (int)v[p << 1 | 1].w.size() - 1, k + 1);
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
    v[p].w.assign(len, 0);
    for (int i = 1, j = 1, k = 1; i < v[p].w.size(); i++) {
      if (j < v[p << 1].w.size() && (k == v[p << 1 | 1].w.size() || v[p << 1].w[j] - v[p << 1].w[j - 1] <= v[p << 1 | 1].w[k] - v[p << 1 | 1].w[k - 1])) {
        v[p].w[i] = v[p].w[i - 1] + v[p << 1].w[j] - v[p << 1].w[j - 1];
        j++;
      } else {
        v[p].w[i] = v[p].w[i - 1] + v[p << 1 | 1].w[k] - v[p << 1 | 1].w[k - 1];
        k++;
      }
    }
    v[p].f.assign(len, kInf), v[p].f[0] = 0;
    if (v[p << 1].f.size() > 1) {
      Divide(v[p].f, v[p << 1].f, v[p << 1 | 1].w, 1, len - 1, 1, v[p << 1].f.size() - 1);
    }
    for (int i = 1; i < v[p].f.size(); i++) {
      v[p].f[i] += v[p << 1 | 1].s;
    }
    for (int i = 1; i < v[p << 1 | 1].f.size(); i++) {
      v[p].f[i] = min(v[p].f[i], v[p << 1 | 1].f[i]);
    }
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p].s = inite[l];
      if (initv[l]) {
        v[p].f.assign(2, 0), v[p].f[1] = v[p].s + w[l];
        v[p].w.assign(2, 0), v[p].w[1] = w[l];
      } else {
        v[p].f.assign(1, 0);
        v[p].w.assign(1, 0);
      }
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    Pushup(p);
  }

  void AddE(int p, int l, int r, int x, int w) {
    if (l == r) {
      v[p].s += w;
      for (int i = 1; i < v[p].f.size(); i++) {
        v[p].f[i] += w;
      }
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      AddE(p << 1, l, mid, x, w);
    } else {
      AddE(p << 1 | 1, mid + 1, r, x, w);
    }
    Pushup(p);
  }

  void ChangeV(int p, int l, int r, int x, bool o) {
    if (l == r) {
      if (o) {
        v[p].f.resize(2), v[p].f[1] = v[p].s + w[l];
        v[p].w.resize(2), v[p].w[1] = w[l];
      } else {
        v[p].f.resize(1);
        v[p].w.resize(1);
      }
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      ChangeV(p << 1, l, mid, x, o);
    } else {
      ChangeV(p << 1 | 1, mid + 1, r, x, o);
    }
    Pushup(p);
  }

 public:
  void Init() { Init(1, 0, t); }
  void AddE(int x, int w) { AddE(1, 0, t, x, w); }
  void ChangeV(int x, bool o) { ChangeV(1, 0, t, x, o); }

  LL Ask() {
    LL ans = v[1].s;
    if (v[1].f.size() > k) {
      ans = min(ans, v[1].f[k]);
    }
    return ans;
  }
} seg;

void Init() {
  static int d[kMaxM], l[kMaxM], ans[kMaxM];
  for (int i = 1; i <= m; i++) {
    d[i] = v[i].d;
  }
  t = m;
  for (int i = 1; i <= q; i++) {
    if (g[i].o == 2) {
      d[++t] = g[i].z;
    }
  }
  for (int i = 1; i <= t; i++) {
    l[i] = i;
  }
  sort(l + 1, l + t + 1, [](int i, int j) {
    return d[i] < d[j];
  });
  for (int i = 1; i <= t; i++) {
    ans[l[i]] = i;
  }
  for (int i = 1; i <= m; i++) {
    v[i].d = ans[i], w[v[i].d] = v[i].c;
  }
  t = m;
  for (int i = 1; i <= q; i++) {
    if (g[i].o == 2) {
      g[i].z = ans[++t], w[g[i].z] = g[i].y;
    }
  }
  sort(d + 1, d + t + 1);
  for (int i = 1; i <= n; i++) {
    e[i].b = lower_bound(d + 1, d + t + 1, e[i].b) - d - 1;
  }
  for (int i = 1; i <= q; i++) {
    if (g[i].o == 1) {
      g[i].z = lower_bound(d + 1, d + t + 1, g[i].z) - d - 1;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q >> k;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b;
  }
  for (int i = 1; i <= m; i++) {
    cin >> v[i].c >> v[i].d;
  }
  for (int i = 1; i <= q; i++) {
    cin >> g[i].o >> g[i].x >> g[i].y >> g[i].z;
  }
  Init();
  for (int i = 1; i <= n; i++) {
    inite[e[i].b] += e[i].a;
  }
  for (int i = 1; i <= m; i++) {
    initv[v[i].d] = 1;
  }
  seg.Init();
  for (int i = 1; i <= q; i++) {
    int o = g[i].o, x = g[i].x, y = g[i].y, z = g[i].z;
    if (o == 1) {
      seg.AddE(e[x].b, -e[x].a);
      e[x] = {y, z};
      seg.AddE(e[x].b, e[x].a);
    } else {
      seg.ChangeV(v[x].d, 0);
      v[x] = {y, z};
      seg.ChangeV(v[x].d, 1);
    }
    cout << seg.Ask() << '\n';
  }
  return 0;
}
