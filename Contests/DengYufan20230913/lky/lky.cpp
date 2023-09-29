#include <fstream>
#define LL long long

using namespace std;

ifstream cin("lky.in");
ofstream cout("lky.out");

const LL kMaxN = 4e6 + 1;
LL n, m, p, ans, fact[kMaxN] = {1}, _fact[kMaxN];

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  for (LL i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1], p - 2);
  for (LL i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % p;
  }
  for (LL i = 1, j = n; i <= min(n, m); i++) {
    ans = (ans + fact[m - 1] * _fact[m - i] % p * _fact[i - 1] % p * j % p * _fact[i] % p * Pow(2, n - i) % p) % p;
    j = j * (n - i) % p;
  }
  cout << ans * fact[m] % p;
  return 0;
}
