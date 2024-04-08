#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.ans");

const int kMaxN = 1e4 + 1, kMod = 998244353;
int t, n, m, a[kMaxN], b[kMaxN];
LL ans, f[kMaxN], g[kMaxN], fact[kMaxN], _fact[kMaxN];

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
  for (int i = 1, x; i <= t; i++) {
    cin >> x >> a[i] >> b[i];
    n += a[i], m += b[i];
  }
  for (int i = 0; i <= n; i++) {
    f[i] = 1;
    for (int j = 1; j <= t; j++) {
      f[i] = f[i] * C(i, a[j]) % kMod;
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      f[i] = (f[i] - f[j] * C(i, j) % kMod + kMod) % kMod;
    }
  }
  for (int i = 0; i <= m; i++) {
    g[i] = 1;
    for (int j = 1; j <= t; j++) {
      g[i] = g[i] * C(i, b[j]) % kMod;
    }
  }
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j < i; j++) {
      g[i] = (g[i] - g[j] * C(i, j) % kMod + kMod) % kMod;
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      LL w = f[i] * g[j] % kMod * C(i + j, i) % kMod;
      if (i + j & 1) {
        ans = (ans - w + kMod) % kMod;
      } else {
        ans = (ans + w) % kMod;
      }
    }
  }
  if (n + m & 1) {
    ans = (kMod - ans) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
