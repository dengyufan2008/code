#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 5001, kMod = 998244353;
int n, m, a[kMaxN];
LL fact[kMaxN], _fact[kMaxN], s1[kMaxN][kMaxN], s2[kMaxN][kMaxN];
LL f[kMaxN][kMaxN], g[kMaxN], h[kMaxN];

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
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], m += a[i];
  }
  sort(a + 1, a + n + 1), fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[n] = Pow(fact[n]);
  for (int i = n; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  s1[0][0] = s2[0][0] = f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      s1[i][j] = s1[i - 1][j] * (i - 1);
      s2[i][j] = s2[i - 1][j] * j;
      f[i][j] = f[i - 1][j] * (m + i - j);
    }
    s1[i][0] %= kMod, s2[i][0] %= kMod, f[i][0] %= kMod;
    for (int j = 1; j <= i; j++) {
      s1[i][j] = (s1[i][j] + s1[i - 1][j - 1]) % kMod;
      s2[i][j] = (s2[i][j] + s2[i - 1][j - 1]) % kMod;
      f[i][j] = (f[i][j] + f[i - 1][j - 1] * (a[i] + 1)) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {  // 至少 i 个环
    for (int j = i; j <= n; j++) {
      g[i] = (g[i] + f[n][j] * s1[j][i]) % kMod;
    }
  }
  for (int i = n; i >= 1; i--) {  // 恰好 i 个环
    for (int j = i + 1; j <= n; j++) {
      g[i] = (g[i] - g[j] * C(j, i) % kMod + kMod) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {  // 恰好 i 个集合
    for (int j = i; j <= n; j++) {
      h[i] = (h[i] + g[j] * s2[j][i]) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {  // 恰好 i 个有序的集合
    h[i] = h[i] * fact[i] % kMod;
  }
  for (int i = n; i >= 1; i--) {  // 恰好 i 个有序的内部无 0 的集合
    for (int j = i + 1; j <= n; j++) {
      h[i] = (h[i] - h[j] * C(j - 1, j - i) % kMod + kMod) % kMod;
    }
  }
  for (int i = 1, j = 1; i <= n; i = j) {  // 相同 a_i 不区分
    for (; j <= n && a[i] == a[j]; j++) {
    }
    for (int k = 1; k <= n; k++) {
      h[k] = h[k] * _fact[j - i] % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << h[i] << '\n';
  }
  return 0;
}
