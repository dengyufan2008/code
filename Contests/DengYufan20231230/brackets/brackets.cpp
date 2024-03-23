#include <fstream>
#define LL long long

using namespace std;

ifstream cin("brackets.in");
ofstream cout("brackets.out");

const int kMaxN = 1e7 + 1, kMod = 1e9 + 7;
int n, m;
LL ans, fac[kMaxN], _fac[kMaxN];
string s;

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

LL C(LL x, LL y) {
  if (y < 0) {
    return 0;
  }
  return fac[x] * _fac[y] % kMod * _fac[x - y] % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fac[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fac[i] = fac[i - 1] * i % kMod;
  }
  _fac[kMaxN - 1] = Pow(fac[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fac[i - 1] = _fac[i] * i % kMod;
  }
  cin >> n >> s;
  m = n >> 1, ans = 1;
  for (int i = 0, j = 0, k = 0; i < n; i++) {
    j++;
    if (s[i] == ')') {
      ans = (ans + C(n - j - k, m - j) - C(n - j - k, m - j - 1) + kMod) % kMod;
      j--, k++;
    }
  }
  cout << ans << '\n';
  return 0;
}
