#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxM = 2e6 + 1, kMod = 1e9 + 7;
int t, n, a[kMaxN], b[kMaxN];
LL ans, f[kMaxN][2], fact[kMaxM], _fact[kMaxM];

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
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  f[0][0] = f[0][1] = 1, cin >> t;
  while (t--) {
    ans = 1, cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; i++) {
      f[i][0] = (f[i - 1][0] * C(a[i] + b[i], a[i]) + f[i - 1][1] * C(a[i] + b[i], a[i] + 1)) % kMod;
      f[i][1] = (f[i - 1][1] * C(a[i] + b[i], b[i]) + f[i - 1][0] * C(a[i] + b[i], b[i] + 1)) % kMod;
      ans = (ans + f[i - 1][0] * (C(a[i] + b[i] + 1, a[i]) - 1) + f[i - 1][1] * (C(a[i] + b[i] + 1, b[i]) - 1)) % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
