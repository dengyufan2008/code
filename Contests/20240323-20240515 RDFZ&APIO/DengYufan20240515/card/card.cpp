#include <fstream>
#define LL long long

using namespace std;

ifstream cin("card.in");
ofstream cout("card.out");

const int kMaxN = 1001, kMaxM = 12, kMod = 998244353;
struct F {
  LL p, e;
  F operator+(F x) {
    return {(p + x.p) % kMod, (e + x.e) % kMod};
  }
  F operator*(F x) {
    return {p * x.p % kMod, (p * x.e + e * x.p) % kMod};
  }
} f[kMaxN][1 << kMaxM];
int n, m, a[1 << kMaxM], b[1 << kMaxM];
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

LL _C(int x, int y) {
  return _fact[x] * fact[y] % kMod * fact[x - y] % kMod;
}

void Add(F &x, F y) { x = x + y; }

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
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a[1 << i];
  }
  for (int i = 0; i < m; i++) {
    cin >> b[1 << i];
  }
  for (int s = 0; s < 1 << m; s++) {
    if ((s & -s) != s) {
      a[s] = a[s ^ (s & -s)] + a[s & -s];
      b[s] = b[s ^ (s & -s)] + b[s & -s];
    }
  }
  for (int i = 0, s = 0; i < m; i++) {
    if (!b[1 << i]) {
      s |= 1 << i;
    }
    if (i == m - 1) {
      f[0][s] = {1, 0};
    }
  }
  for (int s = 0; s < 1 << m; s++) {
    for (int i = 0; i + a[s] < n; i++) {
      LL e = (n - b[s] - i) * Pow(n - a[s] - i) % kMod;
      Add(f[i + 1][s], f[i][s] * (F){1, e});
      for (int j = 0; j < m; j++) {
        int t = 1 << j;
        if (!(s & t) && (i + 1 >= b[t])) {
          LL w = C(i, b[t] - 1) * _C(n - a[s], a[t]) % kMod;
          w = w * C(n - a[s] - i - 1, a[t] - b[t]) % kMod;
          Add(f[i + 1 - b[t]][s | t], f[i][s] * (F){w, w * e % kMod});
        }
      }
    }
  }
  cout << f[0][~(-1 << m)].e << '\n';
  return 0;
}
