#include <fstream>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 2001, kMod = 1e9 + 7;
int n;
LL ans, a[kMaxN], f[kMaxN][kMaxN][3], g[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  while (cin >> n) {
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      f[1][i][0] = a[i], f[1][i][1] = i * a[i] % kMod;
      f[1][i][2] = 1LL * i * i * a[i] % kMod;
    }
    for (int i = 2; i <= n - 2; i++) {
      for (int j = 1; j <= n; j++) {
        g[j] = (g[j - 1] + f[i - 1][j][0]) % kMod;
      }
      for (int j = 1; j <= n; j++) {
        f[i][j][0] = (g[n] - g[j] + kMod + f[i - 1][j][1]) * a[j] % kMod;
        f[i][j][1] = ((g[n] - g[j] + kMod) * j % kMod + f[i - 1][j][2]) * a[j] % kMod;
        f[i][j][2] = (g[n] - g[j] + kMod) * j * j % kMod * a[j] % kMod;
      }
      for (int j = 1; j <= n; j++) {
        g[j] = (g[j - 1] + f[i - 1][j][0] * (j - 1) * (j - 1)) % kMod;
        g[j] = (g[j] + f[i - 1][j][1] * (j - 1) + f[i - 1][j][2]) % kMod;
      }
      for (int j = 1; j <= n; j++) {
        f[i][j][2] = (f[i][j][2] + g[j] * a[j]) % kMod;
      }
    }
    for (int i = 1; i <= n; i++) {
      ans = (ans + f[n - 2][i][0] * (i - 1) * (i - 1)) % kMod;
      ans = (ans + f[n - 2][i][1] * (i - 1) + f[n - 2][i][2]) % kMod;
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
