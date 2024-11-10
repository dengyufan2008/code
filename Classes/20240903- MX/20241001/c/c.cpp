#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 401, kMod = 998244353;
int n, m, s, b[kMaxN];
LL a[kMaxN], pw[kMaxN][kMaxN], fact[kMaxN], _fact[kMaxN];
LL ans, f[kMaxN][kMaxN];

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
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i], s += a[i], m += b[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= s; j++) {
      pw[i][j] = Pow(a[i], j);
    }
  }
  f[0][0] = -1;
  for (int i = 1; i <= n; i++) {
    for (int j = s; j >= a[i]; j--) {
      for (int k = 0; k <= m; k++) {
        for (int l = 0; l <= min(b[i] - 1, k); l++) {
          f[j][k] = (f[j][k] - f[j - a[i]][k - l] * pw[i][l] % kMod * _fact[l]) % kMod;
        }
      }
    }
  }
  for (int i = 1; i <= s; i++) {
    for (int j = 0; j <= m; j++) {
      ans = (ans + f[i][j] * fact[j] % kMod * Pow(i, kMod - j - 2)) % kMod;
    }
  }
  ans = (ans * s % kMod + kMod) % kMod;
  cout << ans << '\n';
  return 0;
}
