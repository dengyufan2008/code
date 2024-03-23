#include <fstream>
#define LL long long

using namespace std;

ifstream cin("merchant.in");
ofstream cout("merchant.out");

const int kMaxN = 1e6 + 1, kMod = 998244353;
int o, n, m;
LL ans, fact[kMaxN], _fact[kMaxN], d[kMaxN];

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
  if (y < 0 || y > x) {
    return 0;
  }
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

LL Calc(int x) {
  return d[n - x] - d[x - 1] - (n - x * 2 + 1) * C(n, x - 1);
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
  cin >> o >> n;
  if (o == 1) {
    cin >> m;
    cout << (n - m * 2 + 1) * (C(n, m) - C(n, m - 1) + kMod) % kMod << '\n';
  } else {
    d[0] = 1;
    for (int i = 1; i <= n; i++) {
      d[i] = (d[i - 1] + C(n, i)) % kMod;
    }
    for (int i = n / 2; i >= 0; i--) {
      ans = (ans * 233 + Calc(i)) % kMod;
      if (i < n / 2) {
        ans = (ans - Calc(i + 1)) % kMod;
      }
    }
    cout << (ans + kMod) % kMod << '\n';
  }
  return 0;
}
