#include <fstream>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 501, kMaxM = 11, kMod = 1e9 + 7;
int n, m, v;
LL ans, f[kMaxM][kMaxN];
LL fact[kMaxN], _fact[kMaxN], pw[kMaxM][kMaxN * kMaxN];

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
  for (int i = 0; i < kMaxM; i++) {
    pw[i][0] = 1;
    for (int j = 1; j < kMaxN * kMaxN; j++) {
      pw[i][j] = pw[i][j - 1] * i % kMod;
    }
  }
  cin >> n >> m >> v;
  n > m ? swap(n, m) : void(), f[0][0] = 1;
  for (int i = 1; i <= v; i++) {
    for (int j = 0; j <= n; j++) {
      for (int k = 0; j + k <= n; k++) {
        LL w = pw[i - 1][k * (n + m - (j << 1) - k - 1)];
        w = w * C(n - j, k) % kMod * C(m - j, k) % kMod * fact[k] % kMod;
        f[i][j + k] = (f[i][j + k] + f[i - 1][j] * w) % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    LL w = f[v][i] * pw[v][(n - i) * (m - i)] % kMod;
    if (i & 1) {
      ans = (ans + w) % kMod;
    } else {
      ans = (ans - w + kMod) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
