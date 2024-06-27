#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 301;
int n, m, p, f[kMaxN], g[kMaxN][2], c[2][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  f[0] = g[0][0] = g[0][1] = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      c[j & 1][0] = c[j & 1][j] = 1;
      for (int k = 1; k < j; k++) {
        c[j & 1][k] = (c[j & 1 ^ 1][k - 1] + c[j & 1 ^ 1][k]) % p;
      }
      g[j][0] = g[j][1] = 0;
      for (int k = 1; k <= j; k++) {
        int w = 1LL * f[k] * c[j & 1][k] % p;
        g[j][0] = (g[j][0] + 1LL * g[j - k][1] * w) % p;
        g[j][1] = (g[j][1] + g[j - k][0]) % p;
      }
    }
    f[0] = 1;
    for (int j = 1; j <= n; j++) {
      f[j] = (g[j][0] + g[j][1]) % p;
    }
  }
  cout << f[n] << '\n';
  return 0;
}
