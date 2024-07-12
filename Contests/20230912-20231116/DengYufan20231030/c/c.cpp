#include <iostream>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 1e5 + 2, kMaxM = 21, kMod = 1e9 + 7;
int n, k, ans, a[kMaxN], f[kMaxN][kMaxM], fact[kMaxN] = {1}, _fact[kMaxN], p[kMaxN][kMaxM], _p[kMaxN][kMaxM];

int Pow(int x, int y = kMod - 2) {
  int ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = 1LL * ans * x % kMod;
    }
    x = 1LL * x * x % kMod;
  }
  return ans;
}

int C(int x, int y) { return 1LL * fact[x] * _fact[y] % kMod * _fact[x - y] % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = 1LL * fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = 1LL * _fact[i] * i % kMod;
  }
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j < kMaxM; j++) {
      p[i][j] = Pow(i, j), _p[i][j] = Pow(p[i][j]);
    }
  }
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  f[n + 1][k] = 1;
  for (int i = n + 1; i > 1; i--) {
    for (int j = 1; j <= k; j++) {
      f[i - 1][j] = (f[i - 1][j] + 1LL * f[i][j] * p[i - 2][j] % kMod * _p[i - 1][j] % kMod) % kMod;
      for (int l = 1; l <= j; l++) {
        int t = 1LL * f[i][j] * C(j, l) % kMod * p[i - 2][j - l] % kMod * _p[i - 1][j] % kMod;
        f[i - 1][j - l + 1] = (f[i - 1][j - l + 1] + t) % kMod;
        if (j == l) {
          ans = (ans + 1LL * t * a[i - 1] % kMod) % kMod;
        }
      }
    }
  }
  cout << 1LL * ans * p[n][k] % kMod;
  return 0;
}
