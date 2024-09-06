#include <fstream>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 401, kMaxV = 801, kMod = 998244353;
int n;
LL ans, f[kMaxV][kMaxV + kMaxN], g[kMaxV][kMaxV + kMaxN];
bool a[kMaxN][kMaxV];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    for (int j = 1, y; j <= x; j++) {
      cin >> y, a[i][y] = 1;
    }
  }
  for (int i = 0; i < kMaxV; i++) {
    f[i][1] = a[1][i];
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < kMaxV; j++) {
      for (int k = 1; k < kMaxV + kMaxN; k++) {
        f[j][k] = (f[j][k] + f[j - 1][k - 1]) % kMod;
        g[j][k] = (g[j][k] + g[j - 1][k - 1]) % kMod;
      }
    }
    for (int j = 0; j < kMaxV; j++) {
      if (!a[i][j]) {
        for (int k = 0; k < kMaxV + kMaxN; k++) {
          f[j][k] = g[j][k] = 0;
        }
      }
    }
    for (int j = 0; j < kMaxV; j++) {
      for (int k = 0; k < i; k++) {
        f[j][i] = (f[j][i] + f[j][k]) % kMod;
        g[j][i] = (g[j][i] + g[j][k]) % kMod;
        f[j][k] = g[j][k] = 0;
      }
      for (int k = n + i; k < kMaxV + kMaxN; k++) {
        f[j][n + i - 1] = (f[j][n + i - 1] + f[j][k]) % kMod;
        g[j][n + i - 1] = (g[j][n + i - 1] + g[j][k]) % kMod;
        g[j][n + i - 1] = (g[j][n + i - 1] + f[j][k] * (k - n - i + 1)) % kMod;
        f[j][k] = g[j][k] = 0;
      }
    }
  }
  for (int i = 0; i < kMaxV; i++) {
    for (int j = 0; j < kMaxV + kMaxN; j++) {
      ans = (ans + g[i][j]) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
