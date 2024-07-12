#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const LL kMaxN = 3002, kMod = 998244353;
int n, a[kMaxN];
LL fact[kMaxN] = {1}, _fact[kMaxN], f[kMaxN][kMaxN], g[kMaxN][kMaxN];

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

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    a[x]++, fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[n] = Pow(fact[n]);
  for (int i = n; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  for (int i = 1; i <= n; i++) {
    g[i][0] = 1;
    for (int j = 1; j * i <= n; j++) {
      g[i][j] = g[i][j - 1] * C(j * i, i) % kMod * Pow(j) % kMod;
    }
  }
  f[n + 1][0] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j <= n; j++) {
      for (int k = max((a[i] - j + i - 1) / i, 0); k * i + j <= n; k++) {
        f[i][j] = (f[i][j] + f[i + 1][k * i + j - a[i]] * C(k * i + j, k * i) % kMod * g[i][k] % kMod) % kMod;
      }
    }
  }
  cout << f[1][0];
  return 0;
}
