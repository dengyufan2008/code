#include <fstream>
#define LL long long

using namespace std;

ifstream cin("dream.in");
ofstream cout("dream.out");

const int kMaxN = 5e5 + 1, kMod = 998244353;
int o, n, m, k, x, y;
LL s[kMaxN], f[kMaxN], g[kMaxN];

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
  cin >> o >> n >> m;
  for (int i = 1; i <= m; i++) {
    s[i] = (s[i - 1] + Pow(i, n)) % kMod;
  }
  for (int i = 1; i <= m; i++) {  // lcm | i
    for (int j = i; j <= m; j += i) {
      f[j] = (f[j] + i) % kMod;
    }
    f[i] = Pow(f[i], n);
  }
  for (int i = 1; i <= m; i++) {  // lcm = i
    for (int j = i + i; j <= m; j += i) {
      f[j] = (f[j] - f[i] + kMod) % kMod;
    }
  }
  for (int i = 1; i <= m; i++) {  // lcm = i, gcd = 1
    for (int j = i + i; j <= m; j += i) {
      f[j] = (f[j] - Pow(j / i, n) * f[i] % kMod + kMod) % kMod;
    }
  }
  for (int i = 1; i <= m; i++) {  // lcm <= i, gcd = 1
    f[i] = (f[i] + f[i - 1]) % kMod;
  }
  for (int i = 1; i <= m; i++) {  // i | gcd
    g[i] = Pow(1LL * (m / i) * (m / i + 1) / 2 * i % kMod, n);
  }
  for (int i = m; i >= 1; i--) {  // gcd = i
    for (int j = i + i; j <= m; j += i) {
      g[i] = (g[i] - g[j] + kMod) % kMod;
    }
  }
  for (int i = 1; i <= m; i++) {  // gcd <= i
    g[i] = (g[i] + g[i - 1]) % kMod;
  }
  while (o--) {
    cin >> x >> y;
    LL ans = g[y];                                       // gcd <= y
    for (int i = 1, j; i <= min(x - 1, y); i = j + 1) {  // (-) lcm < x, gcd <= y
      j = min((x - 1) / ((x - 1) / i), min(x - 1, y));
      ans = (ans - (s[j] - s[i - 1]) * f[(x - 1) / i] % kMod + kMod) % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
