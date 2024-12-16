#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 2e5 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int n, m, d, _n, _m, v, s;
LL _v, ans;

int Gcd(int x, int y) {
  return y ? Gcd(y, x % y) : x;
}

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

LL Calc(int x) {
  return Pow((Pow(x - 1, _n) * Pow(v - x + 1, _m) + Pow(x - 1, _m) * Pow(v - x + 1, _n)) % kMod, d);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> v >> s;
  d = Gcd(n, m), _n = n / d, _m = m / d;
  _v = ans = Pow(v, n + m);
  for (int i = 2; i <= v; i++) {
    if (i <= s) {
      ans = (ans + (_v + Calc(i)) * kInv2) % kMod;
    } else {
      ans = (ans + (_v - Calc(i) + kMod) * kInv2) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
