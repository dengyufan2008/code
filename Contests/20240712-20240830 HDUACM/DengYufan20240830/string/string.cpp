#include <fstream>
#define LL long long

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 10001, kMod = 998244353;
int a, b;
LL ans, f[kMaxN], fact[kMaxN], _fact[kMaxN];
string s, t;

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
  cin >> s >> t;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '1') {
      t[i] == '1' ? a++ : b++;
    }
  }
  ans = f[0] = 1;  // F = (\sum_{i=0}^a \frac{x^i}{(i+1)!})^b
  for (int i = 0; i < a; i++) {
    for (int j = 0; j <= i; j++) {
      f[i + 1] = (f[i + 1] + f[i - j] * _fact[j + 2] % kMod * (b * j + b + j - i)) % kMod;
    }
    f[i + 1] = f[i + 1] * fact[i] % kMod * _fact[i + 1] % kMod;
    ans = (ans + f[i + 1]) % kMod;
  }
  ans = ans * fact[a + b] % kMod * fact[a] % kMod * fact[b] % kMod;
  cout << ans << '\n';
  return 0;
}
