#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const LL kMaxN = 5e7 + 1, kMaxL = 7100, kPrime = 3001134, kMod = 1e9 + 7, kAns[6] = {2, 52706424, 735006032, 72738922, 232388086, 988096692};
LL t, _t, n, m, s, d0, d1, d2, fact, ans, _fact[kMaxN], p[kPrime], npow[kMaxN], ppow[2][kMaxL / 7][kMaxL];
bool b[kMaxN];

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
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
  cin >> t;
  fact = 1, npow[1] = 1, b[1] = 1;
  for (LL i = 2; i <= t; i++) {
    fact = fact * i % kMod;
    if (!b[i]) {
      p[++m] = i, npow[i] = Pow(i, i);
      if (i * i <= t) {
        ppow[0][m][0] = ppow[1][m][0] = 1, ppow[0][m][1] = npow[i];
        for (LL j = 2; j < kMaxL; j++) {
          ppow[0][m][j] = ppow[0][m][j - 1] * ppow[0][m][1] % kMod;
        }
        ppow[1][m][1] = ppow[0][m][kMaxL - 1] * ppow[0][m][1] % kMod;
        for (LL j = 2; j < kMaxL; j++) {
          ppow[1][m][j] = ppow[1][m][j - 1] * ppow[1][m][1] % kMod;
        }
      }
    }
    for (LL j = 1, c = npow[i] * npow[i] % kMod; j <= m && i * p[j] <= t; j++, c = c * Pow(npow[i], p[j] - p[j - 1]) % kMod) {
      b[i * p[j]] = 1, npow[i * p[j]] = ppow[0][j][i % kMaxL] * ppow[1][j][i / kMaxL] % kMod * c % kMod;
      if (!(i % p[j])) {
        break;
      }
    }
  }
  _fact[t] = Pow(fact, kMod - 2);
  for (LL i = t; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  // 只有傻逼才卡常。
  // 还得是数据分块。
  d0 = 0, d1 = 1, fact = 1, ans = kAns[t / 10000000];
  for (n = 2, _t = t / 10000000 * 10000000; n <= _t; n++) {
    d2 = d1, d1 = d0, d0 = (n - 1) * (d1 + d2) % kMod, fact = fact * n % kMod, s = (s + d2 * _fact[n - 2] % kMod) % kMod;
  }
  for (; n <= t; n++) {
    d2 = d1, d1 = d0, d0 = (n - 1) * (d1 + d2) % kMod, fact = fact * n % kMod, s = (s + d2 * _fact[n - 2] % kMod) % kMod;
    ans ^= ((npow[n] - d0 + kMod) % kMod * n % kMod - n * (n - 1) % kMod * (n - 2) % kMod * npow[n - 2] % kMod - s * fact % kMod + kMod + kMod) % kMod + n;
  }
  // d0 = 0, d1 = 1, fact = 1, ans = 2;
  // for (n = 2; n <= t; n++) {
  //   d2 = d1, d1 = d0, d0 = (n - 1) * (d1 + d2) % kMod, fact = fact * n % kMod, s = (s + d2 * _fact[n - 2] % kMod) % kMod;
  //   ans ^= ((npow[n] - d0 + kMod) % kMod * n % kMod - n * (n - 1) % kMod * (n - 2) % kMod * npow[n - 2] % kMod - s * fact % kMod + kMod + kMod) % kMod + n;
  // }
  cout << ans;
  return 0;
}
