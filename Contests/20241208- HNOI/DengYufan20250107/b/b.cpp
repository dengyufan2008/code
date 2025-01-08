#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5e5 + 1, kMaxM = 19, kMaxL = 30, kMod = 998244353, kG = 3;
int n, m;
LL inv[kMaxN], fact[kMaxN], _fact[kMaxN], mul[kMaxN];  // n 的 i 次下降幂
LL a[kMaxN];  // 使用 i 个 1 的贡献

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

LL Cn(int x) {
  return mul[x] * _fact[x] % kMod;
}

namespace CalcA {
LL f[kMaxN], g[kMaxL][kMaxL], c[kMaxL], s[kMaxL];

void Solve() {
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= i; j++) {
      g[i][j] = ((g[i - 1][j - 1] + g[i - 1][j] << 1) + C(i - 1, j - 1)) % kMod;
    }
  }
  for (int i = kMaxL - 1, u = 0; i >= 0; i--) {
    if (n >> i & 1) {
      for (int j = 0; j <= i; j++) {
        c[u + j] = (c[u + j] + C(i, j)) % kMod;
        s[u + j] = (s[u + j] + C(i, j) * (n >> i + 1 << i + 1) + g[i][j]) % kMod;
      }
      u++;
    }
  }
  for (int i = 0; i < kMaxL; i++) {
    LL t = (c[i] * n - s[i] + kMod) % kMod;
    f[0] = 1, f[1] = (n - (1 << i + 1) % kMod + kMod) % kMod;
    for (int j = 2; j <= m; j++) {
      f[j] = f[1] * f[j - 1] + (j - (n + 2) % kMod + kMod) * f[j - 2];
      f[j] = (f[j] % kMod + kMod) * inv[j] % kMod;
    }
    for (int j = 0; j <= m; j++) {
      a[j] = (a[j] + (Cn(j) - f[j] + kMod) * inv[2] % kMod * t) % kMod;
    }
  }
}
}  // namespace CalcA

namespace CalcAns {
int r[kMaxN << 2];
LL c[kMaxN << 2], w[kMaxN << 2], ct[kMaxN << 2], wt[kMaxN << 2];

void Ntt(LL *f, bool o, int m) {
  for (int i = 0; i < m; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < m; i <<= 1) {
    LL g = Pow(kG, (kMod - 1) / (i + i) * (o ? i + i - 1 : 1));
    for (int j = 0; j < m; j += i + i) {
      LL w = 1;
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i] * w % kMod;
        f[k] = (f0 + f1) % kMod;
        f[k + i] = (f0 - f1 + kMod) % kMod;
        w = w * g % kMod;
      }
    }
  }
  if (o) {
    LL inv = Pow(m);
    for (int i = 0; i < m; i++) {
      f[i] = f[i] * inv % kMod;
    }
  }
}

void Solve() {
  c[0] = 1;
  for (int i = kMaxM - 1; i >= 0; i--) {
    for (int j = m >> i; j >= 0; j--) {
      if (j & 1) {
        c[j] = w[j] = 0;
      } else {
        c[j] = c[j >> 1], w[j] = w[j >> 1];
      }
      ct[j] = Cn(j), wt[j] = a[j] * (1 << i) % kMod;
    }
    int _m = 1;
    for (; _m <= m >> i; _m <<= 1) {
    }
    _m <<= 1;
    for (int j = 0; j < _m; j++) {
      r[j] = (r[j >> 1] >> 1) | (j & 1 ? _m >> 1 : 0);
    }
    Ntt(c, 0, _m), Ntt(ct, 0, _m);
    Ntt(w, 0, _m), Ntt(wt, 0, _m);
    for (int j = 0; j < _m; j++) {
      w[j] = (w[j] * ct[j] + c[j] * wt[j]) % kMod;
      c[j] = c[j] * ct[j] % kMod;
    }
    Ntt(c, 1, _m), Ntt(w, 1, _m);
    fill(&c[(m >> i) + 1], &c[_m], 0), fill(&ct[0], &ct[_m], 0);
    fill(&w[(m >> i) + 1], &w[_m], 0), fill(&wt[0], &wt[_m], 0);
  }
  for (int i = 1; i <= m; i++) {
    cout << w[i] << '\n';
  }
}
}  // namespace CalcAns

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  inv[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    inv[i] = kMod - kMod / i * inv[kMod % i] % kMod;
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  mul[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    mul[i] = mul[i - 1] * (n - i + 1) % kMod;
  }
  CalcA::Solve(), CalcAns::Solve();
  return 0;
}
