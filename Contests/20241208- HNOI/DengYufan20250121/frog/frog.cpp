#include <fstream>
#define LL long long

using namespace std;

ifstream cin("frog.in");
ofstream cout("frog.out");

const int kMaxN = 1e7 + 1, kMod = 998244353;
int n;
LL p, _p, ans, t[kMaxN];
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

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Init() {
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  LL a, b;
  cin >> n >> a >> b;
  p = a * Pow(b) % kMod, _p = (1 - p + kMod) % kMod;
}

void Calc() {
  static LL _t[kMaxN], pre[kMaxN];
  t[1] = p, _t[1] = 1;
  for (int i = 2; i < n; i++) {
    t[i] = _t[i - 1] * p % kMod;
    _t[i] = (_t[i - 1] - _p * t[i - 1]) % kMod;
  }
  pre[0] = 1;
  for (int i = 1; i < n; i++) {
    pre[i] = pre[i - 1] * _t[i] % kMod;
  }
  t[n] = 1;
  for (int i = n - 1; i >= 1; i--) {
    static LL _pre = Pow(pre[n - 1]);
    pre[i - 1] = pre[i - 1] * _pre % kMod;
    _pre = _pre * _t[i] % kMod, _t[i] = pre[i - 1];
    t[i] = t[i] * _t[i] % kMod * t[i + 1] % kMod;
  }
  for (int i = 1; i < n; i++) {
    static LL w = 1;
    t[i] = t[i] * w % kMod;
    w = w * p % kMod;
  }
  for (int i = n - 1; i >= 1; i--) {
    static LL w = 1;
    t[i] = t[i] * w % kMod;
    w = w * _p % kMod;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc();
  for (int i = 1; i < n; i++) {
    ans = (ans + C(n - 2, i - 1) * t[i]) % kMod;
  }
  cout << (ans + kMod) % kMod << '\n';
  return 0;
}
