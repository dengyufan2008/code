#include <fstream>
#define LL long long

using namespace std;

ifstream cin("calc.in");
ofstream cout("calc.out");

const int kMaxN = 22, kMod = 998244353;
int n, m;
LL f[kMaxN], g[kMaxN], h[kMaxN], inv[kMaxN], c[kMaxN][kMaxN];

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
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = kMod - kMod / i * inv[kMod % i] % kMod;
  }
  for (int i = 0; i < kMaxN; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % kMod;
    }
  }
  cin >> n >> m, f[0] = 1;
  for (int i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    LL w = Pow(r - l);
    for (int j = 0; j <= m; j++) {
      g[j] = (Pow(r, j + 1) - Pow(l, j + 1) + kMod) * inv[j + 1] % kMod * w % kMod;
    }
    for (int j = 0; j <= m; j++) {
      for (int k = 0; j + k <= m; k++) {
        h[j + k] = (h[j + k] + f[j] * g[k] % kMod * c[j + k][j]) % kMod;
      }
    }
    for (int j = 0; j <= m; j++) {
      f[j] = h[j], h[j] = 0;
    }
  }
  for (int i = 0; i <= m; i++) {
    g[i] = i & 1 ? kMod - inv[i + 1] : inv[i + 1];
  }
  for (int i = 0; i <= m; i++) {
    for (int j = 0; i + j <= m; j++) {
      h[i + j] = (h[i + j] + f[i] * g[j] % kMod * c[i + j][i]) % kMod;
    }
  }
  cout << h[m] << '\n';
  return 0;
}
