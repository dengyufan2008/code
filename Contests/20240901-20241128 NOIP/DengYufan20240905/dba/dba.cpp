#include <fstream>
#define LL long long

using namespace std;

ifstream cin("dba.in");
ofstream cout("dba.out");

const int kMaxN = 2001, kMaxM = kMaxN * kMaxN * 2, kMod = 1e9 + 7;
int m, l, a[kMaxN];
LL ans, fact[kMaxM], _fact[kMaxM];

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

LL Calc(int p, int k) {
  LL ans = 0;
  for (int i = 0; i <= p; i++) {
    LL w = C(p, i) * C(k - m * i + p, p) % kMod;
    if (i & 1) {
      ans = (ans - w + kMod) % kMod;
    } else {
      ans = (ans + w) % kMod;
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxM - 1] = Pow(fact[kMaxM - 1]);
  for (int i = kMaxM - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> m >> l;
  for (int i = l - 1; i >= 0; i--) {
    cin >> a[i];
  }
  for (int i = 1; i < l; i++) {
    a[i] += a[i - 1];
  }
  for (int i = 0, p = 0; i < l; p = a[i], i++) {
    ans = (ans + Calc(i, a[i]) - Calc(i, p) + kMod) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
