#include <fstream>
#define LL long long

using namespace std;

ifstream cin("calc.in");
ofstream cout("calc.out");

const LL kMaxN = 1e7 + 1, kMod = 998244353;
LL t, n, m, fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, LL y = kMod - 2) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
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
  fact[0] = 1;
  for (LL i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (LL i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> t;
  while (t--) {
    cin >> n >> m;
    cout << fact[n * m] * _fact[n] % kMod * _fact[m] % kMod << '\n';
  }
  return 0;
}
