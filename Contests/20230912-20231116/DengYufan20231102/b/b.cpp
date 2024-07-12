#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 2e5 + 1, kMod = 1e9 + 7;
LL n, m, f[kMaxN], fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = 1LL * ans * x % kMod;
    }
    x = 1LL * x * x % kMod;
  }
  return ans;
}

LL C(int x, int y) {
  if (x < y) {
    return 0;
  }
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; i * j <= n; j++) {
      if (j & 1) {
        f[i] = (f[i] + C(n - i * j, n - m) * C(n - m + 1, j) % kMod) % kMod;
      } else {
        f[i] = (f[i] - C(n - i * j, n - m) * C(n - m + 1, j) % kMod + kMod) % kMod;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << (f[i] - f[i + 1] + kMod) % kMod << ' ';
  }
  return 0;
}
