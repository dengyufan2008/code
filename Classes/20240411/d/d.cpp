#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 5001, kMod = 998244353;
int n, m, a[kMaxN];
LL f[kMaxN][kMaxN], g[kMaxN], h[kMaxN], fact[kMaxN], _fact[kMaxN];

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

LL Cat1(int x, int y) {
  ;
}

LL Cat2(int x, int y) {
  ;
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
}

void Update(LL &x, LL y) {
  x = (x + y % kMod + kMod) % kMod;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], m += a[i];
  }
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      Update(f[i][j], f[i - 1][j] * (m + i - j));
      Update(f[i][j + 1], f[i - 1][j] * (a[i] + 1));
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      Update(g[i], f[n][j] * Cat1(j, i));
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      Update(g[i], -g[j] * C(i, j));
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      Update(h[i], g[j] * Cat2(j, i));
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      Update(h[i], -h[j] * C(i, j));
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << h[i] << '\n';
  }
  return 0;
}
