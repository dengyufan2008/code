#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("leaf.in");
ofstream cout("leaf.out");

const LL kMaxN = 3e5 + 1, kMaxL = 19, kInf = 1e18;
struct V {
  int r, s, l, fa[kMaxL];
  int f, g, h;
  LL d;
  vector<pair<int, int>> e;
} v[kMaxN];
struct Q {
  int x, y, z, o;
} q[kMaxN];
int n, m, k, s, ans[kMaxN];
vector<int> f[kMaxN], g[kMaxN];

class H {
  int d[kMaxN];

 public:
  void Add(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      d[i] += y;
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans += d[i];
    }
    return ans;
  }
} h1, h2;

int Lca(int x, int y) {
  v[x].l < v[y].l ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].l - (1 << i) >= v[y].l) {
      x = v[x].fa[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].fa[i] != v[y].fa[i]) {
      x = v[x].fa[i], y = v[y].fa[i];
    }
  }
  return x == y ? x : v[x].fa[0];
}

void Init(int f, int x) {
  static vector<pair<int, int>> e;
  for (auto i : v[x].e) {
    if (i.first != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();

  v[x].r = ++k, v[x].s = 1;
  v[x].l = v[f].l + 1, v[x].fa[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].fa[i] = v[v[x].fa[i - 1]].fa[i - 1];
  }
  for (auto i : v[x].e) {
    v[i.first].d = v[x].d + i.second;
    Init(x, i.first);
    v[x].s += v[i.first].s;
  }
}

void CalcF(int x) {
  if (v[x].e.empty()) {
    v[x].f = x;
    return;
  }
  LL dis1 = kInf;
  for (auto i : v[x].e) {
    CalcF(i.first);
    LL dis = v[v[i.first].f].d - v[x].d;
    if (dis < dis1 || dis == dis1 && v[i.first].f < v[x].f) {
      dis1 = dis, v[x].f = v[i.first].f;
    }
  }
}

void CalcG(int x, LL dis0) {
  if (dis0 < v[v[x].f].d - v[x].d || dis0 == v[v[x].f].d - v[x].d && v[x].g < v[x].f) {
    v[x].h = v[x].g;
  } else {
    v[x].h = v[x].f;
  }
  if (v[x].e.empty()) {
    return;
  }
  LL mn1 = v[x].g, dis1 = dis0, mn2 = 0, dis2 = kInf;
  for (auto i : v[x].e) {
    LL dis = v[v[i.first].f].d - v[x].d;
    if (dis < dis1 || dis == dis1 && v[i.first].f < mn1) {
      mn2 = mn1, dis2 = dis1;
      mn1 = v[i.first].f, dis1 = dis;
    } else if (dis < dis2 || dis == dis2 && v[i.first].f < mn2) {
      mn2 = v[i.first].f, dis2 = dis;
    }
  }
  for (auto i : v[x].e) {
    if (mn1 == v[i.first].f) {
      v[i.first].g = mn2;
      CalcG(i.first, dis2 + i.second);
    } else {
      v[i.first].g = mn1;
      CalcG(i.first, dis1 + i.second);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  cin >> m;
  if (n <= 2) {
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      cout << 1 << '\n';
    }
    return 0;
  }
  for (s = 1; v[s].e.size() == 1; s++) {
  }
  Init(0, s), CalcF(s), CalcG(s, kInf);
  for (int i = 1; i <= m; i++) {
    cin >> q[i].x >> q[i].y, q[i].z = Lca(q[i].x, q[i].y), q[i].o = i;
  }
  for (int i = 1; i <= n; i++) {
    f[v[i].f].push_back(i), g[v[i].g].push_back(i);
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) {
    return i.x < j.x;
  });
  for (int i = 1, j = 1; i <= n; i++) {
    for (int k : f[i]) {
      h1.Add(v[k].r, 1), h1.Add(v[k].r + v[k].s, -1);
    }
    for (int k : g[i]) {
      h2.Add(v[k].r, 1), h2.Add(v[k].r + v[k].s, -1);
    }
    for (; j <= m && q[j].x == i; j++) {
      ans[q[j].o] = h1.Ask(v[q[j].x].r) - h1.Ask(v[q[j].z].r) +
                    h2.Ask(v[q[j].y].r) - h2.Ask(v[q[j].z].r) +
                    (v[q[j].y].h == q[j].x);
    }
    for (int k : f[i]) {
      h1.Add(v[k].r, -1), h1.Add(v[k].r + v[k].s, 1);
    }
    for (int k : g[i]) {
      h2.Add(v[k].r, -1), h2.Add(v[k].r + v[k].s, 1);
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
