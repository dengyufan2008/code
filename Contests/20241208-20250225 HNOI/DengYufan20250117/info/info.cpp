#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("info.in");
ofstream cout("info.out");

const int kMaxN = 1e5 + 1, kMaxL = 18, kMod = 998244353;
struct V {
  int r, s, d, f[kMaxL];
  LL t, w[kMaxL];
  bool b;
  vector<pair<int, int>> e, i, g;
} v[kMaxN];
int n, m;

void S(int x) {
  static int k = 0;
  v[x].r = ++k, v[x].s = 1;
  for (auto i : v[x].e) {
    if (!v[i.first].b) {
      v[i.first].b = 1;
      v[i.first].d = v[x].d + 1;
      v[i.first].f[0] = x;
      v[i.first].w[0] = i.second;
      S(i.first);
      v[x].s += v[i.first].s;
    } else {
      v[i.first].i.push_back({x, i.second});
    }
  }
}

bool In(int x, int y) {
  return v[x].r <= v[y].r && v[x].r + v[x].s > v[y].r;
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

void AddEdge(int x, int y) {
  int z = y;
  LL w = 1;
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[z].d - (1 << i) >= v[x].d) {
      w = w * v[z].w[i] % kMod;
      z = v[z].f[i];
    }
  }
  v[x].g.push_back({y, w});
}

void Dp(int x) {
  LL t = (1 - v[x].t + kMod) % kMod;
  for (auto i : v[x].g) {
    Dp(i.first);
    t = t * (1 - v[i.first].t * i.second % kMod + kMod) % kMod;
  }
  v[x].t = (1 - t + kMod) % kMod;
}

void Clear(int x) {
  v[x].t = 0;
  for (auto i : v[x].g) {
    Clear(i.first);
  }
  v[x].g.clear();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
  }
  v[1].b = 1, S(1), v[0].w[0] = v[1].w[0] = 1;
  for (int i = 1; i < kMaxL; i++) {
    v[0].w[i] = 1;
    for (int j = 1; j <= n; j++) {
      v[j].f[i] = v[v[j].f[i - 1]].f[i - 1];
      v[j].w[i] = v[j].w[i - 1] * v[v[j].f[i - 1]].w[i - 1] % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    static vector<pair<int, int>> e;
    for (auto j : v[i].i) {
      if (!In(i, j.first)) {
        e.push_back(j);
      }
    }
    v[i].i.swap(e), e.clear();
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].i.empty()) {
      cout << v[i].w[kMaxL - 1] << '\n';
      continue;
    }
    v[i].i.push_back({v[i].f[0], v[i].w[0]});
    sort(v[i].i.begin(), v[i].i.end(), [](pair<int, int> x, pair<int, int> y) {
      return v[x.first].r < v[y.first].r;
    });
    static vector<int> l = {1};
    for (int j = v[i].i[0].first == 1; j < v[i].i.size(); j++) {
      int x = v[i].i[j].first, p, q;
      if ((q = Lca(l.back(), x)) != l.back()) {
        for (; (p = Lca(l[l.size() - 2], x)) != l[l.size() - 2]; l.pop_back(), q = p) {
          AddEdge(l[l.size() - 2], l.back());
        }
        AddEdge(q, l.back()), l.pop_back();
        if (q != p) {
          l.push_back(q);
        }
      }
      l.push_back(x);
    }
    for (; l.size() > 1; l.pop_back()) {
      AddEdge(l[l.size() - 2], l.back());
    }
    for (auto j : v[i].i) {
      v[j.first].t = j.second;
    }
    Dp(1), cout << v[1].t << '\n', Clear(1);
  }
  return 0;
}
