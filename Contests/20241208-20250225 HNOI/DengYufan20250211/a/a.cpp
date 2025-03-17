#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 14, kInf = 1e9;
struct V {
  int f[1 << kMaxN];
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m;
vector<int> l[kMaxN];

void Update(int &x, int y) { x = min(x, y); }

void Dp() {
  for (int u = 1; u < n; u++) {
    for (int s : l[u]) {
      for (int i = 0; i < n; i++) {
        if (s >> i & 1) {
          for (auto e : v[i].e) {
            if (s >> e.first & 1) {
              int _s = s ^ 1 << i ^ 1 << e.first;
              Update(v[i].f[s], v[i].f[s ^ 1 << e.first] + e.second);
              for (int t = _s; t; t = t - 1 & _s) {
                t |= 1 << e.first;
                Update(v[i].f[s], max(v[i].f[s ^ t], v[e.first].f[t]) + e.second);
                t ^= 1 << e.first;
              }
            }
          }
        }
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z, x--, y--;
    v[x].e.push_back({y, z});
  }
  for (int s = 1; s < 1 << n; s++) {
    l[__builtin_popcount(s) - 1].push_back(s);
  }
  for (int i = 0; i < n; i++) {
    fill(&v[i].f[0], &v[i].f[1 << n], kInf);
    v[i].f[1 << i] = 0;
  }
  Dp();
  if (v[0].f[(1 << n) - 1] == kInf) {
    cout << -1 << '\n';
  } else {
    cout << v[0].f[(1 << n) - 1] << '\n';
  }
  return 0;
}
