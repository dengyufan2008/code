#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 501, kInf = 1e18;
struct V {
  int w, s, c, d;
  vector<int> e;
  vector<pair<int, LL>> f[kMaxN];  // 断了 j 条边 (j + 1 个连通块)
} v[kMaxN];
int t, n, r, w;
vector<pair<int, LL>> g[kMaxN];

void S(int f, int x) {
  v[x].d = v[f].d + 1;
  v[x].d > v[r].d && (r = x);
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i);
    }
  }
}

void T(int f, int x) {
  v[x].s = v[x].w;
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s += v[i].s;
    }
  }
  v[x].c = 1, v[x].f[0].clear(), v[x].f[0].push_back({v[x].w, 0});
  for (int i : v[x].e) {
    if (i != f) {
      for (int j = 0; j < v[x].c; j++) {
        for (int k = 0; k < v[i].c; k++) {
          for (auto l : v[x].f[j]) {
            LL ans = kInf;
            for (auto r : v[i].f[k]) {
              g[j + k].push_back({l.first + r.first, l.second + r.second});  // 连
              ans = min(ans, 1LL * r.first * r.first + r.second);
            }
            g[j + k + 1].push_back({l.first, l.second + ans});  // 断
          }
        }
      }
      v[x].c += v[i].c;
      for (int j = 0; j < v[x].c; j++) {
        v[x].f[j].swap(g[j]), g[j].clear();
        sort(v[x].f[j].begin(), v[x].f[j].end());
        for (auto l : v[x].f[j]) {
          if (g[j].empty()) {
            g[j].push_back(l);
          } else if (1LL * g[j].back().first * g[j].back().first + g[j].back().second >
                     1LL * l.first * l.first + l.second) {
            g[j].push_back(l);
          }
        }
        v[x].f[j].swap(g[j]), g[j].clear();
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].w, v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    S(0, r = 1), T(0, r);
    for (int i = 0; i < n; i++) {
      LL ans = kInf;
      for (auto l : v[r].f[i]) {
        ans = min(ans, 1LL * l.first * l.first + l.second);
      }
      cout << ans << " \n"[i == n - 1];
    }
  }
  return 0;
}
