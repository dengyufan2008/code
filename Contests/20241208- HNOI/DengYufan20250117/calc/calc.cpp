#include <fstream>
#define LL long long

using namespace std;

ifstream cin("calc.in");
ofstream cout("calc.out");

const int kMaxN = 101, kMaxM = kMaxN * kMaxN, kMod = 998244353;
int n, m, s;
LL ans, d[kMaxN][kMaxN], f[kMaxM], g[kMaxM];
LL fact[kMaxM], _fact[kMaxM];

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

LL C(LL x, int y) {
  if (y < 0 || y > x) {
    return 0;
  }
  LL ans = _fact[y];
  for (int i = 0; i < y; i++) {
    ans = ans * (x - i) % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kMaxN; i++) {
    d[i][0] = !i;
    for (int j = 1; j <= i; j++) {
      d[i][j] = (d[i - 1][j - 1] * (i - j + 1) + d[i - 1][j] * j) % kMod;
    }
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m, f[0] = 1;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    for (int j = 0; j <= s; j++) {
      for (int k = 0; k <= x; k++) {
        g[j + k] = (g[j + k] + f[j] * d[x][k]) % kMod;
      }
    }
    s += x;
    for (int j = 0; j <= s; j++) {
      f[j] = g[j], g[j] = 0;
    }
  }
  for (int i = 0; i <= s; i++) {
    ans = (ans + f[i] * C(m - i + s + n - 1, s + n - 1)) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
