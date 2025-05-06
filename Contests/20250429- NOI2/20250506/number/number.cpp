#include <fstream>
#define LL long long

using namespace std;

ifstream cin("number.in");
ofstream cout("number.out");

const int kMaxN = 5e3 + 10, kMod = 998244353;
int t, r, p, n, k;
LL fact[kMaxN], _fact[kMaxN];

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

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

LL Sum(int k, int n) {  // \sum_{i=1}^n i^k
  static LL s[kMaxN], pre[kMaxN], suf[kMaxN];
  for (int i = 1; i <= k + 2; i++) {
    s[i] = (s[i - 1] + Pow(i, k)) % kMod;
  }
  pre[0] = 1;
  for (int i = 1; i <= k + 2; i++) {
    pre[i] = pre[i - 1] * (n - i) % kMod;
  }
  suf[k + 3] = 1;
  for (int i = k + 2; i >= 1; i--) {
    suf[i] = suf[i + 1] * (n - i) % kMod;
  }
  LL ans = 0;
  for (int i = 1; i <= k + 2; i++) {
    LL w1 = s[i] * _fact[i - 1] % kMod * _fact[k + 2 - i] % kMod;
    LL w2 = pre[i - 1] * suf[i + 1] % kMod;
    if (k + 2 - i & 1) {
      ans = (ans - w1 * w2) % kMod;
    } else {
      ans = (ans + w1 * w2) % kMod;
    }
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
  cin >> t;
  while (t--) {
    cin >> r >> p >> n >> k;
    r = Gcd(r, p - 1);
    LL w1 = p + p - 2 - (p - 2) % r;
    LL w2 = Pow(r, k + 1) * (p - 2 - (p - 2) / r) % kMod;
    LL ans = (Sum(k, n) * w1 + Sum(k, n / r) * w2) % kMod;
    cout << (ans + kMod) % kMod << '\n';
  }
  return 0;
}
