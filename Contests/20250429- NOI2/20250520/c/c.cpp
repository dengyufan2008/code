#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
struct V {
  int w[2];
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m;
bool u;

class Solve {
  struct V {
    int d, l, t, f[kMaxL];
    vector<pair<int, int>> e;
  } v[kMaxN];
  int c;
  pair<int, int> a[kMaxN];

  void CalcF(int f, int x) {
    static vector<pair<int, int>> e;
    for (auto i : v[x].e) {
      if (i.first != f) {
        e.push_back(i);
      }
    }
    v[x].e.swap(e), e.clear();
    v[x].f[0] = f;
    for (int i = 1; i < kMaxL; i++) {
      v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
    }
    for (auto i : v[x].e) {
      v[i.first].d = v[x].d + i.second;
      CalcF(x, i.first);
    }
  }

  void CalcL(int x) {
    if (v[x].e.empty()) {
      return;
    }
    for (auto &i : v[x].e) {
      CalcL(i.first);
      if (v[i.first].l + i.second > v[x].l) {
        v[x].l = v[i.first].l + i.second;
        swap(i, v[x].e[0]);
      }
    }
    for (auto i : v[x].e) {
      if (i != v[x].e[0]) {
        a[++c] = {i.first, v[i.first].l + i.second};
      }
    }
  }

  int Find(int x, int t) {
    for (int i = kMaxL - 1; i >= 0; i--) {
      if (v[v[x].f[i]].t > t) {
        x = v[x].f[i];
      }
    }
    return v[x].f[0];
  }

 public:
  void AddEdge(int x, int y, int z) {
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }

  void Init(int s) {
    CalcF(0, s), CalcL(s), a[++c] = {s, v[s].l};
    sort(a + 1, a + c + 1, [](pair<int, int> i, pair<int, int> j) {
      return i.second > j.second;
    });
    for (int i = 1; i <= c; i++) {
      a[i].second += a[i - 1].second;
      for (int j = a[i].first;; j = v[j].e[0].first) {
        v[j].t = i;
        if (v[j].e.empty()) {
          break;
        }
      }
    }
  }

  int Ask(int x, int t) {
    if (v[x].t <= t) {
      return a[min(t, c)].second;
    }
    int p = Find(x, t - 1), q = Find(x, t);
    int ans1 = a[t - 1].second + v[x].l + v[x].d - v[p].d;
    int ans2 = a[t].second - v[q].l + v[x].l + v[x].d - v[q].d;
    return max(ans1, ans2);
  }
} solve1, solve2;

void CalcW(int f, int x, bool o) {
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].w[o] = v[x].w[o] + i.second;
      CalcW(x, i.first, o);
    }
  }
}

void Init() {
  int x = 1, y = 1;
  v[1].w[1] = 0, CalcW(0, 1, 1);
  for (int i = 2; i <= n; i++) {
    v[x].w[1] < v[i].w[1] && (x = i);
  }
  v[x].w[0] = 0, CalcW(0, x, 0);
  for (int i = 2; i <= n; i++) {
    v[y].w[0] < v[i].w[0] && (y = i);
  }
  v[y].w[1] = 0, CalcW(0, y, 1);
  solve1.Init(x), solve2.Init(y);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> u;
  if (n == 1) {
    for (int i = 1; i <= m; i++) {
      cout << 0 << '\n';
    }
    return 0;
  }
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
    solve1.AddEdge(x, y, z), solve2.AddEdge(x, y, z);
  }
  Init();
  for (int i = 1, x, t, p = 0; i <= m; i++) {
    cin >> x >> t;
    if (u) {
      x = (x - 1 + p) % n + 1, t = (t - 1 + p) % n + 1;
    }
    t = t * 2 - 1;
    if (v[x].w[0] > v[x].w[1]) {
      p = solve1.Ask(x, t);
    } else {
      p = solve2.Ask(x, t);
    }
    cout << p << '\n';
  }
  return 0;
}
