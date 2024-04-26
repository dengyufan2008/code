#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("o.in");
ofstream cout("o.out");

const LL kMaxN = 2e5 + 1, kMaxM = 1e6 + 1, kMaxL = 18, kInf = 1e18;
struct V {
  int s, d, f[kMaxL];
  LL w;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxN];
struct Q {
  int l, r, d;
} q[kMaxM];
int n, m, s, r;
LL ans[kMaxM];
vector<pair<int, LL>> l, t;
vector<pair<int, int>> w;
class Seg {
  LL v[kMaxN];

 public:
  Seg() { fill(&v[0], &v[kMaxN], kInf); };

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

void CalcR(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      CalcR(x, i.first);
      v[x].s += v[i.first].s;
      mx = max(mx, v[i.first].s);
    }
  }
  if (max(mx, s - v[x].s) * 2 <= s) {
    r = x;
  }
}

void CalcD(int f, int x, LL d) {
  l.push_back({x, d});
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      CalcD(x, i.first, d + i.second);
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
        int x = t.back().first, y = l[i].first;
        w.push_back({min(x, y), max(x, y)});
      }
      t.push_back(l[i]);
    }
  }
  int _s = s;
  for (auto i : v[r].e) {
    if (!v[i.first].b) {
      s = v[i.first].s * 2 <= _s ? v[i.first].s : _s - v[r].s;
      CalcR(0, i.first), Divide();
    }
  }
}

void CalcF(int f, int x) {
  v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].w = v[x].w + i.second;
      CalcF(x, i.first);
    }
  }
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
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

LL Dis(int x, int y) {
  return v[x].w + v[y].w - v[Lca(x, y)].w * 2;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
    v[y].e.push_back({x, z});
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
  CalcF(0, 1);
  for (int i = n, j = w.size() - 1, k = m; i >= 1; i--) {
    for (; j >= 0 && w[j].first == i; j--) {
      seg.CheckMin(w[j].second, Dis(w[j].first, w[j].second));
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
