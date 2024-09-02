#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 1e7 + 1, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int t, n, s, a[26];
char c;
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

LL Solve0() {
  for (int i = 0; i < 26; i++) {
    if (a[i] & 1) {
      return kInv2;
    }
  }
  LL ans = fact[s >> 1] * _fact[s] % kMod;
  for (int i = 0; i < 26; i++) {
    ans = ans * _fact[a[i] >> 1] % kMod * fact[a[i]] % kMod;
  }
  return (1 - ans + kMod) * kInv2 % kMod;
}

LL Solve1() {
  int t = 0;
  bool b = 0;
  for (int i = 0; i < 26; i++) {
    if (a[i] & 1) {
      if (b) {
        return kInv2;
      } else {
        b = 1, a[i]--, s--, t = a[i];
      }
    }
  }
  LL ans = (1 - Solve0() + kMod) * (t + 1) + (s - t) / 2;
  return ans % kMod * Pow(s + 1) % kMod;
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
    s = 0;
    for (int i = 0; i < 26; i++) {
      a[i] = 0;
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> c >> a[c - 'a'], s += a[c - 'a'];
    }
    cout << (s & 1 ? Solve1() : Solve0()) << '\n';
  }
  return 0;
}
