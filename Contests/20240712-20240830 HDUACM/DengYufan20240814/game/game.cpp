#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("game.in");
ofstream cout("game.out");

const int kMaxN = 1001, kMaxM = 64, kMaxL = 30, kMod = 998244353;
int n, m, a[kMaxN];
LL f[4], g[4], h[4];
bool e[4][4];
vector<pair<int, int>> v[kMaxN];
struct H {
  LL f[kMaxM][kMaxM];
  bool o;  // 0:matrix 1:vector

  void operator+=(H &h) {
    for (int i = 0; i < kMaxM; i++) {
      for (int j = 0; j < kMaxM; j++) {
        f[i][j] = (f[i][j] + h.f[i][j]) % kMod;
      }
    }
  }

  void operator*=(H &h) {
    int t = o ? 1 : kMaxM;
    LL ans[kMaxM][kMaxM] = {};
    for (int i = 0; i < t; i++) {
      for (int j = 0; j < kMaxM; j++) {
        for (int k = 0; k < kMaxM; k++) {
          ans[i][j] = (ans[i][j] + f[i][k] * h.f[k][j]) % kMod;
        }
      }
    }
    for (int i = 0; i < t; i++) {
      for (int j = 0; j < kMaxM; j++) {
        f[i][j] = ans[i][j];
      }
    }
  }
} w[4], pw[kMaxL], ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cin >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z, v[x].push_back({y, z});
  }
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      cin >> e[i][j];
    }
  }
  for (int s = 0; s < kMaxM; s++) {
    w[0].f[s][s] = 1;
  }
  for (int i = 1; i <= 3; i++) {
    for (int s = 0; s < kMaxM; s++) {
      for (int j = 0; j <= 3; j++) {
        if (!e[i][1] || (s >> 4 & 3 ^ j)) {
          if (!e[i][2] || (s >> 2 & 3 ^ j)) {
            if (!e[i][3] || (s & 3 ^ j)) {
              w[i].f[s][s >> 2 | j << 4] = 1;
              break;
            }
          }
        }
      }
    }
  }
  pw[0] += w[1], pw[0] += w[2], pw[0] += w[3];
  for (int i = 1; i < kMaxL; i++) {
    pw[i] = pw[i - 1], pw[i] *= pw[i - 1];
  }
  f[0] = 1;
  for (int i = 1, p; i <= n; i++) {
    sort(v[i].begin(), v[i].end()), v[i].push_back({a[i] + 1, 0});
    p = 0, ans.o = 1, ans.f[0][kMaxM - 1] = 1;
    fill(&ans.f[0][0], &ans.f[0][kMaxM - 1], 0);
    for (auto j : v[i]) {
      int o = j.first - p - 1;
      if (o >= 1) {
        for (int k = 0; k < kMaxL; k++) {
          if (o >> k & 1) {
            ans *= pw[k];
          }
        }
      }
      ans *= w[j.second], p = j.first;
    }
    g[0] = g[1] = g[2] = g[3] = 0;
    for (int s = 0; s < kMaxM; s++) {
      g[s >> 4] = (g[s >> 4] + ans.f[0][s]) % kMod;
    }
    h[0] = h[1] = h[2] = h[3] = 0;
    for (int j = 0; j <= 3; j++) {
      for (int k = 0; k <= 3; k++) {
        h[j ^ k] = (h[j ^ k] + f[j] * g[k]) % kMod;
      }
    }
    f[0] = h[0], f[1] = h[1], f[2] = h[2], f[3] = h[3];
  }
  cout << f[0] << '\n';
  return 0;
}
