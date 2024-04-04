#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2001, kMod = 998244353;
struct T {
  LL p, e;
  T() : p(0), e(0) {}
  T(LL _p, LL _e) : p(_p), e(_e) {}
  T operator+(T v) {
    return {(p + v.p) % kMod, (e + v.e) % kMod};
  }
  T operator*(T v) {
    return {p * v.p % kMod, (e * v.p + p * v.e) % kMod};
  }
} ans, f[kMaxN][kMaxN * 2], g[kMaxN][kMaxN * 2], h[kMaxN][kMaxN * 2], t[kMaxN][kMaxN * 2];
int n, m;
LL k, a[kMaxN * 2], pw[kMaxN * 2];

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
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
    k = (k + a[i]) % kMod;
  }
  k = Pow(k);
  for (int i = 1; i <= m; i++) {
    a[i] = a[i] * k % kMod;
  }
  m += n, pw[0] = 1;
  for (int i = 1; i <= m; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
    f[1][i] = g[1][i] = T(a[i], 0);
    h[1][i] = t[1][i] = T(1, 0);
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= m; j++) {
      f[i - 1][j] = f[i - 1][j] + f[i - 1][j - 1];
    }
    t[i - 1][m] = T(a[m], 0) * t[i - 1][m];
    for (int j = m - 1; j >= 1; j--) {
      t[i - 1][j] = T(a[j], 0) * t[i - 1][j] + t[i - 1][j + 1];
    }
    for (int j = 1; j <= m; j++) {
      g[i][j] = T(a[j], 0) + g[i][j - 1] * g[i - 1][j - 1] * T(1, pw[j - 1]);
      h[i][j] = t[i - 1][j + 1] + f[i - 1][j - 1];
      f[i][j] = g[i][j] * h[i][j];
    }
    for (int j = m - 1; j >= 1; j--) {
      t[i][j] = h[i][j] + g[i - 1][j] * T(1, pw[j]) * t[i][j + 1];
    }
  }
  for (int i = 1; i <= m; i++) {
    ans = ans + f[n][i];
  }
  cout << ans.e << '\n';
  return 0;
}
