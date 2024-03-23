#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const int kMaxN = 5001, kMaxM = 1e5 + 2, kMod = 998244353;
int t, n, m, k, a[kMaxM], s[kMaxM];
LL p, _p, x, w, ans, f[kMaxN][kMaxN], g[kMaxN][kMaxN];
LL sf[kMaxN], sg[kMaxN], inv[kMaxN], _inv[kMaxN];

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
  cin >> n >> m >> p >> t;
  p = p * Pow(1000000) % kMod, _p = (1 - p + kMod) % kMod, inv[0] = 1;
  for (int i = 0; i <= m; i++) {
    for (int j = 1; j <= i; j++) {
      sf[j] = (sf[j - 1] + f[i - j][j]) % kMod;
      sg[j] = (sg[j - 1] + g[i - j][j]) % kMod;
    }
    for (int j = i + 1; j <= n; j++) {
      sf[j] = sf[j - 1], sg[j] = sg[j - 1];
    }
    for (int j = 1; j <= n; j++) {
      inv[j] = inv[j - 1] * (j - _p * sg[j] % kMod + kMod) % kMod;
    }
    _inv[n] = Pow(inv[n]);
    for (int j = n; j >= 1; j--) {
      _inv[j - 1] = _inv[j] * (j - _p * sg[j] % kMod + kMod) % kMod;
    }
    for (int j = 1; j <= n; j++) {
      f[i][j] = (_p * sf[j] + j) % kMod * inv[j - 1] % kMod * _inv[j] % kMod;
      g[i][j] = p * j % kMod * inv[j - 1] % kMod * _inv[j] % kMod;
    }
  }
  x = (_p * sf[n] + n) % kMod * Pow(_p * (n - sg[n] + kMod) % kMod) % kMod;
  while (t--) {
    cin >> k;
    for (int i = 1; i <= k; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + k + 1), s[k + 1] = 0;
    for (int i = k; i >= 1; i--) {
      s[i] = s[i + 1] + a[i];
    }
    w = 1, ans = 0;
    if (s[1] <= m) {
      for (int i = 1; i <= k; i++) {
        ans = (ans + w * f[m - s[i]][a[i]]) % kMod;
        w = w * g[m - s[i]][a[i]] % kMod;
      }
      ans = (ans + w * x) % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
