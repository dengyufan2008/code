#include <fstream>
#define LL long long

using namespace std;

ifstream cin("mo.in");
ofstream cout("mo.out");

const int kMaxN = 1e7 + 1, kMod = 998244353;
int n, s, v, l, r;
LL ans, fact[kMaxN], _fact[kMaxN];

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
  cin >> n >> s >> v >> l >> r;
  if (v == 1) {
    if (s >= l && s <= r) {
      cout << C(n - 1, s - 1) << '\n';
    } else {
      cout << 0 << '\n';
    }
    return 0;
  }
  for (int i = s - r; i <= s - l; i++) {
    ans = (ans + C(v - 2, i - 1) * C(n - v, s - i - 1)) % kMod;
  }
  for (int i = l - s; i <= r - s; i++) {
    ans = (ans + C(v - 2, i - 1) * C(n - v, n - s - i)) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
