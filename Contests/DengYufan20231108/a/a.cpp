#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const LL kMaxN = 1e6 + 1, kMod = 998244353;
LL n, m, ans, fact[kMaxN], _fact[kMaxN];

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

LL C(int x, int y) { return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod; }

int main() {
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m;
  if (n - 1 <= m) {
    for (int i = 1; i < n; i++) {
      cout << i + 1 << ' ' << i << " \n"[i == m];
    }
    for (int i = n; i <= m; i++) {
      cout << 2 << ' ' << 1 << " \n"[i == m];
    }
    for (int i = 0; i < n; i++) {
      ans = (ans + (i & 1 ? -1 : 1) * Pow((n * (n - 1) / 2 - i) % kMod, m) * C(n - 1, i) % kMod + kMod) % kMod;
    }
    cout << ans << '\n';
  } else {
    for (int i = 1; i < m; i++) {
      cout << i + 1 << ' ' << i << ' ';
    }
    if (m) {
      cout << n << ' ' << m;
    }
    cout << '\n' << fact[m] << '\n';
  }
  return 0;
}
