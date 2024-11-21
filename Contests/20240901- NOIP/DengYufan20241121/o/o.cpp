#include <fstream>
#define LL long long

using namespace std;

ifstream cin("o.in");
ofstream cout("o.out");

const int kMaxN = 1e6 + 1, kMaxL = 20, kMod = 1e9 + 7;
int n, m, q;
LL ans, d[kMaxN], fact[kMaxN], _fact[kMaxN];

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
  cin >> n >> m >> q;
  for (int i = 0; i < kMaxL; i++) {
    LL s = 0;
    for (int j = 1; j <= m; j++) {
      s = (s + C(j - 1, (1 << i) - 2) * C(m - j, n - (1 << i) + 1)) % kMod;
      d[j] = (d[j] + s) % kMod;
    }
  }
  for (int i = 0; i <= m; i++) {
    d[i] = (d[i] + C(m, n)) * 2 % kMod;
  }
  for (int i = 1, x; i <= q; i++) {
    cin >> x, ans ^= d[x] * i;
  }
  cout << ans << '\n';
  return 0;
}
