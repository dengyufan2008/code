#include <fstream>
#define LL long long

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 1 << 21, kMaxM = 1e7 + 1, kMod = 998244353;
int n, m, t, r[kMaxN];
LL a[kMaxN], b[kMaxN], f[kMaxM], inv[kMaxM];

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

void Ntt(LL f[kMaxN], bool o) {
  const static int kInv = Pow(kMaxN);
  for (int i = 0; i < kMaxN; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < kMaxN; i <<= 1) {
    LL g = Pow(3, (kMod - 1) / (i + i) * (o ? i + i - 1 : 1));
    for (int j = 0; j < kMaxN; j += i + i) {
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
    for (int i = 0; i < kMaxN; i++) {
      f[i] = f[i] * kInv % kMod;
    }
  }
}

void CalcPair() {
  LL w = 0;
  cin >> n >> t;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, a[x - 1]++, m = max(m, x);
  }
  for (int i = 0; i < m; i++) {
    b[i] = a[m - i - 1];
    w = (w + 1LL * b[i] * (b[i] - 1) / 2) % kMod;
  }
  for (int i = 1; i < kMaxN; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? kMaxN >> 1 : 0);
  }
  Ntt(a, 0), Ntt(b, 0);
  for (int i = 0; i < kMaxN; i++) {
    a[i] = a[i] * b[i] % kMod;
  }
  Ntt(a, 1);
  for (int i = 0, j = m - 1; i < j; i++, j--) {
    swap(a[i], a[j]);
  }
  a[0] = w;
}

void CalcAns() {
  if (n == 2) {
    cout << a[0] << '\n';
    return;
  }
  inv[1] = 1;
  for (int i = 2; i <= t; i++) {
    inv[i] = kMod - 1LL * kMod / i * inv[kMod % i] % kMod;
  }
  LL p = 2LL * (n - 2) * Pow(1LL * n * (n - 1) % kMod) % kMod;
  LL _p = Pow(p), q = (1 + (kMod - p) * 2) % kMod, ans = 0;
  f[t] = Pow(p, t), f[t - 1] = Pow(p, t - 1) * t % kMod * q % kMod;
  for (int i = t - 1; i >= 1; i--) {
    f[i - 1] = f[i + 1] * (t + i + 1) % kMod * p + f[i] * i % kMod * q;
    f[i - 1] = f[i - 1] % kMod * _p % kMod * inv[t - i + 1] % kMod;
  }
  for (int i = 0; i < m; i++) {
    ans = (ans + a[i] * f[i]) % kMod;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  CalcPair(), CalcAns();
  return 0;
}
