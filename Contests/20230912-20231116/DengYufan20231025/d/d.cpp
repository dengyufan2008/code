#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 1002, kMod = 1e9 + 7;
int t, n, m;
LL ans, fact[kMaxN] = {1}, _fact[kMaxN], inv[kMaxN], f[kMaxN][kMaxN];

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
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  for (int i = 0; i < kMaxN; i++) {
    inv[i] = Pow(i);
  }
  cin >> t;
  while (t--) {
    ans = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        f[i][j] = 0;
      }
    }
    cin >> n >> m;
    for (int i = 1, p = 0; i <= n; i++) {
      for (int j = m - n / i; j <= m; j++) {
        f[m - j][0] = 1;
        for (int k = 1; k <= n - (m - j) * i; k++) {
          f[m - j][k] = f[m - j][k - 1] * j % kMod;
          if (k >= i + 1) {
            f[m - j][k] = (f[m - j][k] - _fact[i] * j % kMod * f[m - j + 1][k - 1 - i] % kMod + kMod) % kMod;
          }
          f[m - j][k] = f[m - j][k] * inv[k] % kMod;
        }
      }
      ans = (ans + (f[0][n] - p + kMod) % kMod * i % kMod * fact[n] % kMod) % kMod;
      p = f[0][n];
    }
    cout << ans << '\n';
  }
  return 0;
}
