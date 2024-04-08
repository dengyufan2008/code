#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 8e5 + 1, kMod = 998244353;
int t, n, m, k, a[kMaxN], b[kMaxN], c[kMaxN];
LL ans, f[kMaxN], g[kMaxN], h[kMaxN], fact[kMaxN], _fact[kMaxN];

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

void Init() {
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> t;
  for (int i = 1, x; i <= t; i++) {
    cin >> x >> a[i] >> b[i];
    n += a[i], m += b[i];
  }
}

void Ntt(LL *f, bool b) {
  static int r[kMaxN] = {};
  for (int i = 1; i < k; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? k >> 1 : 0);
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < k; i <<= 1) {
    LL g = Pow(3, (kMod - 1) / (i + i) * (b ? i + i - 1 : 1));
    for (int j = 0; j < k; j += i + i) {
      LL w = 1;
      for (int l = j; l < j + i; l++) {
        LL f0 = f[l], f1 = f[l + i] * w % kMod;
        f[l] = (f0 + f1) % kMod;
        f[l + i] = (f0 - f1 + kMod) % kMod;
        w = w * g % kMod;
      }
    }
  }
  if (b) {
    LL _k = Pow(k);
    for (int i = 0; i < k; i++) {
      f[i] = f[i] * _k % kMod;
    }
  }
}

void Calc() {
  fill(&c[0], &c[n] + 1, 0), fill(&f[0], &f[n] + 1, 1);
  for (int i = 1; i <= t; i++) {
    c[a[i]]++;
  }
  for (int i = 0; i <= n; i++) {
    if (c[i]) {
      for (int j = 0; j <= n; j++) {
        f[j] = f[j] * Pow(C(j, i), c[i]) % kMod;
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    f[i] = f[i] * _fact[i] % kMod;
    h[i] = _fact[i], i & 1 && (h[i] = (kMod - h[i]) % kMod);
  }
  for (k = 1; k <= n << 1; k <<= 1) {
  }
  Ntt(f, 0), Ntt(h, 0);
  for (int i = 0; i < k; i++) {
    f[i] = f[i] * h[i] % kMod;
  }
  Ntt(f, 1), fill(&f[n] + 1, &f[kMaxN], 0), fill(&h[1], &h[kMaxN], 0);
  swap(n, m), swap(a, b), swap(f, g);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc(), Calc();
  for (k = 1; k <= n + m; k <<= 1) {
  }
  Ntt(f, 0), Ntt(g, 0);
  for (int i = 0; i < k; i++) {
    f[i] = f[i] * g[i] % kMod;
  }
  Ntt(f, 1), fill(&f[n + m + 1], &f[kMaxN], 0);
  for (int i = 0; i <= n + m; i++) {
    LL w = f[i] * fact[i] % kMod;
    if (i & 1) {
      ans = (ans - w + kMod) % kMod;
    } else {
      ans = (ans + w) % kMod;
    }
  }
  if (n + m & 1) {
    ans = (kMod - ans) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
