#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const LL kMaxN = 1e6 + 1, kMod = 998244353;
LL t, n, k;
LL ans, f[kMaxN], fact[kMaxN << 1] = {1}, _fact[kMaxN << 1];

LL Pow(LL x, LL y = kMod - 2) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL C(LL x, LL y) { return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod; }

LL F(LL x) { return (C(x << 1, x) - C(x << 1, x - 1) + kMod) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> n >> k;
  for (int i = 1; i < kMaxN << 1; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[(kMaxN << 1) - 1] = Pow(fact[(kMaxN << 1) - 1]);
  for (int i = (kMaxN << 1) - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  if (t == 1) {
    cout << F(n) * Pow(k % kMod, n) % kMod;
  } else {
    k %= kMod, f[0] = 1;
    for (int i = 0; i < n; i++) {
      f[i + 1] = ((k * 8 - 4 + kMod) % kMod * i % kMod + (-k * 4 % kMod + 2 + kMod) % kMod) % kMod * Pow(i + 1) % kMod * f[i] % kMod;
    }
    for (int i = 1; i <= n; i++) {
      f[i] = f[i] * k % kMod;
    }
    for (int i = 0; i <= n; i++) {
      ans = (ans + f[i] * Pow(k * k % kMod * 4 % kMod, n - i) % kMod) % kMod;
    }
    cout << ans;
  }
  return 0;
}
