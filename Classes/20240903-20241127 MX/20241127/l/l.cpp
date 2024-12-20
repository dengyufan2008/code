#include <fstream>
#define LL long long

using namespace std;

ifstream cin("l.in");
ofstream cout("l.out");

const int kMaxN = 2e5 + 1, kMod = 998244353;
LL n, m, q, _n, _m, inv_n, inv_m, ans;

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
  cin >> n >> m >> q;
  _n = n * (n + 1) / 2 % kMod, _m = m * 2 + 1;
  inv_n = Pow(_n), inv_m = Pow(_m);
  for (int j = 1; j <= n; j++) {
    LL p = j * (n - j + 1) % kMod * inv_n % kMod;
    ans = (ans + _m * (Pow(1 - m * inv_m % kMod * p % kMod, q) - 1) + m * q % kMod * p) % kMod;
  }
  ans = ans * (m - 1) % kMod * Pow(m * 2) % kMod * inv_m % kMod;
  cout << (ans + kMod) * Pow(_n * _m % kMod, q) % kMod << '\n';
  return 0;
}
