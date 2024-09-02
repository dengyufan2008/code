#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 401, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int t, n;
LL a[kMaxN], b[kMaxN], d[kMaxN][2], w[kMaxN];
LL ans, f[kMaxN][kMaxN], g[kMaxN][kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  d[0][0] = 1, cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, x, y; i <= n; i++) {
      cin >> x >> y;
      a[i] = x * Pow(y) % kMod;
      b[i] = (1 - a[i] + kMod) % kMod;
    }
    for (int i = 1; i < n; i++) {
      f[i][i + 1] = g[i][i + 1] = a[i] * b[i + 1] % kMod;
    }
    for (int i = 4; i <= n; i += 2) {
      for (int j = 1, k; (k = j + i - 1) <= n; j++) {
        f[j][k] = g[j][k] = a[j] * b[k] % kMod * g[j + 1][k - 1] % kMod;
        for (int l = j + 1; l < k; l += 2) {
          g[j][k] = (g[j][k] + f[j][l] * g[l + 1][k]) % kMod;
        }
      }
    }
    for (int i = 0; i <= n; i += 2) {
      for (int j = 1; j <= n; j++) {
        d[j][0] = d[j - 1][0] * b[j] % kMod;
        for (int k = j - 1; k >= 1 && k > j - i; k -= 2) {
          d[j][0] = (d[j][0] + d[k - 1][0] * f[k][j]) % kMod;
        }
        d[j][1] = (d[j - 1][0] + d[j - 1][1]) * a[j] % kMod;
        for (int k = j - 1; k >= 1 && k > j - i; k -= 2) {
          d[j][1] = (d[j][1] + d[k - 1][1] * f[k][j]) % kMod;
        }
      }
      w[i] = (d[n][0] + d[n][1]) % kMod;
    }
    for (int i = 2; i <= n; i += 2) {
      ans = (ans + (w[i] - w[i - 2] + kMod) * (i / 2 - kInv2 + kMod)) % kMod;
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
