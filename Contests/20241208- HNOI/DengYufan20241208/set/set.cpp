#include <fstream>
#define LL long long

using namespace std;

ifstream cin("set.in");
ofstream cout("set.out");

const int kMaxN = 501;
int n, p;
LL ans, w[kMaxN << 1][kMaxN << 1];
LL f[kMaxN][kMaxN << 1];
LL g[kMaxN][kMaxN << 1];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p;
  f[n][0] = 1;
  for (int i = 1; i <= n + 1; i++) {
    for (int j = n; j >= 0; j--) {
      for (int k = 0; k <= n << 1; k++) {
        int l = max(k, i + j - 1), m = n - i + j;
        if (j >= 1) {
          w[m][l] += g[j][k],
              w[m][l] >= p && (w[m][l] -= p);

          f[j - 1][l] += g[j][k],
              f[j - 1][l] >= p && (f[j - 1][l] -= p);

          g[j - 1][k] += g[j][k] << 1,
              g[j - 1][k] >= p && (g[j - 1][k] -= p),
              g[j - 1][k] >= p && (g[j - 1][k] -= p);

          g[j][k] = 0;
        }
        if (i <= n) {
          g[j][k] += f[j][k],
              g[j][k] >= p && (g[j][k] -= p);

          f[j][k] <<= 1,
              f[j][k] >= p && (f[j][k] -= p);
        }
      }
    }
  }
  for (int i = 0; i <= n << 1; i++) {
    static LL pw = 1;
    LL s = 0;
    for (int j = 0; j <= n << 1; j++) {
      s = (s + w[i][j] * j) % p;
    }
    ans = (ans + s * pw) % p;
    pw = pw * 2 % p;
  }
  cout << ans << '\n';
  return 0;
}
