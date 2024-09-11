#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e6 + 1, kMod = 998244353;
int t, n, k;
LL ans, f[kMaxN], fact[kMaxN], _fact[kMaxN];

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
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> t;
  while (t--) {
    cin >> n >> k, k = Pow(2, k), f[n] = 1;  // A(k - i, n - i)
    for (int i = n - 1; i >= 0; i--) {
      f[i] = f[i + 1] * (k - i) % kMod;
    }
    for (int i = 0; i <= n; i++) {
      f[i] = f[i] * C(n, i) % kMod;
      ans = i & 1 ? (ans - f[i] + kMod) % kMod : (ans + f[i]) % kMod;
    }
    for (int i = 1; i <= n; i++) {
      ans = ans * (k - i) % kMod;
    }
    cout << ans << '\n', ans = 0;
  }
  return 0;
}
