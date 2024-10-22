#include <fstream>
#define LL long long

using namespace std;

ifstream cin("v.in");
ofstream cout("v.out");

const int kMaxN = 13, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int n, m, e[kMaxN];
LL f[kMaxN][1 << kMaxN], g[1 << kMaxN], h[1 << kMaxN], ans[1 << kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, x--, y--;
    e[x] |= 1 << y, e[y] |= 1 << x;
  }
  g[0] = ans[0] = 1;
  for (int i = 0; i < n; i++) {
    f[i][0] = 1;
    for (int s = 0; s < 1 << i; s++) {
      for (int j = 0; j <= i; j++) {
        if (f[j][s]) {
          for (int k = 0; k < i; k++) {
            if ((~s & e[j]) >> k & 1) {
              for (int t = s | 1 << k; t < 1 << i; t = t + 1 | s | 1 << k) {
                f[k][t] = (f[k][t] + f[j][s] * ans[s ^ t]) % kMod;
              }
            }
          }
        }
      }
    }
    for (int s = 1; s < 1 << i; s++) {
      g[s] = ans[s] * __builtin_popcount(s & e[i]) % kMod;
      for (int j = 0; j < i; j++) {
        if (e[j] >> i & 1) {
          g[s] = (g[s] + f[j][s]) % kMod;
        }
        f[j][s] = 0;
      }
      g[s] = g[s] * kInv2 % kMod;
    }
    for (int s = 0, _s; s < 1 << i; s++) {
      _s = s ^ (s & -s), h[s] = g[s];
      for (int t = _s; t; t = t - 1 & _s) {
        h[s] = (h[s] + g[t ^ s] * h[t]) % kMod;
      }
      ans[s | 1 << i] = h[s];
    }
    f[i][0] = 0;
  }
  cout << ans[~(-1 << n)] << '\n';
  return 0;
}
