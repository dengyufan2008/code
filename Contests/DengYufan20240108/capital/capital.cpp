#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("capital.in");
ofstream cout("capital.out");

const int kMaxN = 2e5 + 1, kMaxM = 5e5 + 1, kMaxL = 18;
struct V {
  int d, l, w, s, p[kMaxL];
  vector<int> g, f;
  vector<pair<int, int>> e;
} v[kMaxN << 1];
int n, m, q, k, _n, s, _s, a[kMaxM];
vector<int> l;

void S(int x) {
  static int r = 0;
  v[x].d = v[x].l = ++r;
  l.push_back(x);
  for (int i : v[x].g) {
    if (v[i].d) {
      v[x].l = min(v[x].l, v[i].d);
    } else {
      S(i);
      v[x].l = min(v[x].l, v[i].l);
      if (v[i].l == v[x].d) {
        v[++_n].f.push_back(x), v[x].f.push_back(_n);
        for (; l.back() != i; l.pop_back()) {
          v[_n].f.push_back(l.back());
          v[l.back()].f.push_back(_n);
        }
        v[_n].f.push_back(i), v[i].f.push_back(_n);
        l.pop_back();
      }
    }
  }
}

void T(int f, int x) {
  static int r = 0;
  v[x].d = v[f].d + 1, v[x].l = ++r, v[x].p[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].p[i] = v[v[x].p[i - 1]].p[i - 1];
  }
  for (int i : v[x].f) {
    if (i != f) {
      T(x, i);
    }
  }
}

int Lca(int x, int y) {
  if (v[x].d < v[y].d) {
    swap(x, y);
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].p[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].p[i] != v[y].p[i]) {
      x = v[x].p[i], y = v[y].p[i];
    }
  }
  return x == y ? x : v[x].p[0];
}

void AddEdge(int x, int y) {
  v[x].e.push_back({y, v[y].d - v[x].d});
  v[y].e.push_back({x, v[y].d - v[x].d});
}

void Build() {
  for (int j = 1; j <= k; j++) {
    if (a[j] != 1 && a[j] != a[j - 1]) {
      int lca = Lca(l.back(), a[j]);
      if (lca != l.back()) {
        for (; l.size() > 1 && v[l[l.size() - 2]].l > v[lca].l; l.pop_back()) {
          AddEdge(l[l.size() - 2], l.back());
        }
        AddEdge(lca, l.back()), l.pop_back();
        if (v[lca].l > v[l.back()].l) {
          l.push_back(lca);
        }
      }
      l.push_back(a[j]);
    }
  }
  for (; l.size() > 1; l.pop_back()) {
    AddEdge(l[l.size() - 2], l.back());
  }
}

void R(int f, int x, bool b) {
  int mx = 0;
  v[x].s = v[x].w;
  for (auto i : v[x].e) {
    if (i.first != f) {
      R(x, i.first, b), v[x].s += v[i.first].s;
      mx = max(mx, v[i.first].s);
    }
  }
  if (b && max(mx, k - v[x].s) * 2 <= k) {
    s = x;
  }
}

LL Calc(int f, int x) {
  LL ans = 0;
  for (auto i : v[x].e) {
    if (i.first != f) {
      int w = i.second / 2 + (x > n && i.first <= n);
      ans += Calc(x, i.first) + 1LL * w * v[i.first].s;
    }
  }
  return ans;
}

void Clear(int f, int x) {
  v[x].s = v[x].w = 0;
  for (auto i : v[x].e) {
    if (i.first != f) {
      Clear(x, i.first);
    }
  }
  v[x].e.clear();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].g.push_back(y), v[y].g.push_back(x);
  }
  _n = n, S(1), T(0, 1);
  for (int i = 1; i <= q; i++) {
    cin >> k;
    for (int j = 1; j <= k; j++) {
      cin >> a[j];
      v[a[j]].w++;
    }
    sort(a + 1, a + k + 1, [](int i, int j) { return v[i].l < v[j].l; });
    Build(), R(0, 1, 1), R(0, s, 0), _s = 0;
    if (s > n) {
      for (auto j : v[s].e) {
        if (!_s || v[_s].s < v[j.first].s) {
          _s = j.first;
        }
      }
      // if (Lca(_s, s) == _s) {
      //   cout << v[s].p[0] << '\n';
      // } else {
      //   for (int i = kMaxL - 1; i >= 0; i--) {
      //     if (v[_s].d - (1 << i) > v[s].d) {
      //       _s = v[_s].p[i];
      //     }
      //   }
      //   cout << _s << '\n';
      // }
    } else {
      // cout << s << '\n';
    }
    cout << 1LL * (n - 1) * k - Calc(0, s) + v[_s].s << '\n';
    Clear(0, 1);
  }
  return 0;
}
