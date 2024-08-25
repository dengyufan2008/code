#include <fstream>
#define LL long long

using namespace std;

ifstream cin("super.in");
ofstream cout("super.out");

const int kMaxN = 2e5 + 1, kMod = 998244353;
int n, a[kMaxN], c[kMaxN];
LL ans, fact[kMaxN], _fact[kMaxN];
bool b[kMaxN];

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
  ans = 1, cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] < 0 || a[i] > i || a[i] < a[i - 1]) {
      ans = 0;
    }
  }
  if (a[n] < n) {
    ans = 0;
  }
  for (int i = n; i >= 1; i--) {
    if (a[i - 1] != a[i]) {
      b[a[i - 1]] = 1;
    } else {
      c[a[i] + 1]++;
    }
  }
  for (int i = n - 1, j = 0; i >= 0; i--) {
    j += !b[i], ans = ans * fact[j] % kMod;
    if (j >= c[i]) {
      ans = ans * _fact[j - c[i]] % kMod, j -= c[i];
    } else {
      ans = 0;
    }
  }
  cout << ans << '\n';
  return 0;
}
