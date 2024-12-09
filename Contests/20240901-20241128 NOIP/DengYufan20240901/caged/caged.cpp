#include <fstream>
#define LL long long

using namespace std;

ifstream cin("caged.in");
ofstream cout("caged.out");

const int kMaxN = 1001, kMaxV = 301, kMod = 998244353;
int n, v;
LL f[kMaxV][kMaxN];
LL fact[kMaxN], _fact[kMaxN], inv[kMaxN];

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

LL Calc(int x) {
  f[0][0] = 1;
  for (int i = 1; i <= v; i++) {
    f[i][0] = 1;
    for (int j = 1; j + (v - i) * x <= n; j++) {
      f[i][j] = f[i][j - 1];
      if (j > x) {
        f[i][j] = (f[i][j] - f[i - 1][j - x - 1] * _fact[x]) % kMod;
      }
      f[i][j] = (f[i][j] + kMod) * i % kMod * inv[j] % kMod;
    }
  }
  return f[v][n] * fact[n] % kMod;
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
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = kMod - inv[kMod % i] * (kMod / i) % kMod;
  }
  cin >> v >> n;
  LL ans = Pow(v, n) * n % kMod;
  for (int i = 1; i < n; i++) {
    ans = (ans - Calc(i) + kMod) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
