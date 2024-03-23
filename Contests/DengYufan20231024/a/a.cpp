#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kMod = 998244353;
struct V {
  int f[4];
  vector<int> e;
} v[kMaxN];
int n, m, c, f;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    v[i].f[0] = 1;
  }
  for (int o = 1; o <= 3; o++) {
    int s = 0;
    for (int i = 1; i <= n; i++) {
      s = (s + v[i].f[o - 1]) % kMod;
    }
    for (int i = 1; i <= n; i++) {
      v[i].f[o] = (s - v[i].f[o - 1] + kMod) % kMod;
      for (int j : v[i].e) {
        v[i].f[o] = (v[i].f[o] - v[j].f[o - 1] + kMod) % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    c = (c + v[i].f[3]) % kMod;
    f = (f + 1LL * (n - 1 - v[i].e.size()) * (n - 1 - v[i].e.size()) % kMod * v[i].f[2] % kMod) % kMod;
  }
  cout << 1LL * c * c % kMod * f % kMod;
  return 0;
}
