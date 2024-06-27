#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 5e5 + 1, kMod = 998244353;
int n, m;
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
  cin >> n >> m, n > m ? swap(n, m) : void();
  for (int i = n; i >= 0; i--) {
    static LL _n = Pow(n + 1, m - n), _m = 1;
    LL w = _n * _m % kMod * _fact[i] % kMod;
    w = w * fact[n] % kMod * fact[m] % kMod;
    w = w * _fact[n - i] % kMod * _fact[m - i] % kMod;
    _n = _n * (n + 1) % kMod, _m = _m * (m + 1) % kMod;
    if (i & 1) {
      ans = (ans - w) % kMod;
    } else {
      ans = (ans + w) % kMod;
    }
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
