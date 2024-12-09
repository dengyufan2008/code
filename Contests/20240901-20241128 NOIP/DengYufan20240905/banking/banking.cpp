#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("banking.in");
ofstream cout("banking.out");

const LL kMaxN = 1e5 + 1, kMaxL = 17, kInf = 1e18;
struct V {
  int d, x, y, f[kMaxL];
  LL w, s, l, g, h;
  vector<pair<int, int>> e;
} v[kMaxN];
int t, n, r;
LL s, ans;

void CalcR(int f, int x) {
  LL mx = 0;
  v[x].s = v[x].w;
  for (auto i : v[x].e) {
    if (i.first != f) {
      CalcR(x, i.first);
      v[x].s += v[i.first].s;
      mx = max(mx, v[i.first].s);
    }
  }
  if (max(mx, s - v[x].s) * 2 <= s) {
    r = x;
  }
}

void CalcE(int f, int x) {
  v[x].d = v[f].d + 1, v[x].f[0] = f, v[x].s = v[x].w;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (auto &i : v[x].e) {
    if (i.first != f) {
      v[i.first].l = v[x].l + i.second;
      CalcE(x, i.first);
      v[x].s += v[i.first].s;
      if (v[x].e[0].first == f || v[v[x].e[0].first].s < v[i.first].s) {
        swap(v[x].e[0], i);
      }
    }
  }
}

void CalcX(int x) {
  if (v[x].e.empty()) {
    v[x].x = x;
    return;
  }
  for (auto i : v[x].e) {
    CalcX(i.first);
  }
  int y = v[v[x].e[0].first].x;
  for (; v[y].s * 2 <= v[x].s; y = v[y].f[0]) {
  }
  v[x].x = y;
}

int Find(int x, LL s) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] && v[v[x].f[i]].s * 2 <= s) {
      x = v[x].f[i];
    }
  }
  return v[x].s * 2 <= s ? v[x].f[0] : x;
}

void CalcY(int x) {
  for (auto i : v[x].e) {
    v[i.first].y = Find(v[x].y, s - v[i.first].s);
    CalcY(i.first);
  }
}

void CalcY() {
  if (v[r].e.size() == 1) {
    v[v[r].e[0].first].y = r;
    CalcY(v[r].e[0].first);
    return;
  }
  int son = v[r].e[0].first, mx = 0, son2 = 0;
  for (int i = 1; i < v[r].e.size(); i++) {
    int x = v[r].e[i].first;
    if (v[x].s > mx) {
      mx = v[x].s, son2 = x;
    }
  }
  if (mx * 2 <= s - v[son].s) {
    v[son].y = r;
  } else {
    v[son].y = Find(v[son2].x, s - v[son].s);
  }
  for (int i = 1; i < v[r].e.size(); i++) {
    int x = v[r].e[i].first;
    if (v[son].s * 2 <= s - v[x].s) {
      v[x].y = r;
    } else {
      v[x].y = Find(v[son].x, s - v[x].s);
    }
  }
  for (auto i : v[r].e) {
    CalcY(i.first);
  }
}

void CalcG(int x) {
  v[x].g = 0;
  for (auto i : v[x].e) {
    CalcG(i.first);
    v[x].g += v[i.first].g + v[i.first].s * i.second;
  }
}

void CalcH(int x) {
  for (auto i : v[x].e) {
    v[i.first].h = v[x].h + (s - v[i.first].s * 2) * i.second;
    CalcH(i.first);
  }
}

int Lca(int x, int y) {
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

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    s = 0, ans = kInf, cin >> n;
    for (int i = 1; i <= n; i++) {
      v[i].e.clear(), cin >> v[i].w, s += v[i].w;
    }
    for (int i = 1, x, y, z; i < n; i++) {
      cin >> x >> y >> z;
      v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
    }
    CalcR(0, 1), v[r].l = v[r].y = 0;
    for (int i = 0; i < kMaxL; i++) {
      v[r].f[i] = 0;
    }
    CalcE(0, r);
    for (int i = 1; i <= n; i++) {
      vector<pair<int, int>> e;
      for (auto j : v[i].e) {
        if (j.first != v[i].f[0]) {
          e.push_back(j);
        }
      }
      v[i].e.swap(e);
    }
    CalcX(r), CalcY(), CalcG(r), v[r].h = v[r].g, CalcH(r);
    for (int i = 1; i <= n; i++) {
      if (i != r) {
        int x = v[i].x, y = v[i].y, z = Lca(i, y);
        LL wi = v[x].h - (v[i].h - v[i].g) - (s - v[i].s) * (v[x].l - v[i].l);
        LL wj = v[y].h - v[i].g - v[i].s * (v[i].l + v[y].l - v[z].l * 2);
        ans = min(ans, wi + wj);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
