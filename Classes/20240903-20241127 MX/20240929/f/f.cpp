#include <fstream>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int n, m;
LL ans, f[kMaxN], fact[kMaxN], _fact[kMaxN];

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
  f[0] = f[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    f[i] = (f[i - 1] + f[i - 2] * (i - 1)) % kMod;
  }
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    if (x == 0) {
      i--, n--;
    } else if (x == 1) {
      m++;
    }
  }
  for (int i = 0; i < n - m; i++) {
    LL w1 = C(n - m, i) * fact[i] % kMod;
    LL w2 = fact[n - m - i - 1] * C(n - i - 1, m) % kMod * m % kMod;
    ans = (ans + w1 * w2) % kMod;
  }
  ans = (ans + fact[n - m]) * f[m] % kMod;
  // cout << ans << '\n';
  cout << fact[n] * _fact[m] % kMod * f[m] % kMod << '\n';
  return 0;
}
