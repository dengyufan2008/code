#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e7 + 1, kMod = 998244353;
int n, a, b;
LL ans, fact[kMaxN], _fact[kMaxN], fact2[kMaxN];

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
  fact2[0] = fact2[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    fact2[i] = fact2[i - 2] * i % kMod;
  }
  cin >> n >> a >> b;
  for (int i = max(a + b - n + 2 >> 1, 0); i <= min(a, b); i++) {
    int m = n - 1 - a - b + i + i;
    LL w = fact[n - 1] % kMod * _fact[a - i] % kMod;
    m && (w = w * _fact[m] % kMod * fact2[m - 1] % kMod);
    ans = (ans + C(b, i) * w) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
