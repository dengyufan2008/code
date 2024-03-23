#include <fstream>
#define LL long long
#define Clear(f, n) fill((f), (f) + (n), 0)
#define Copy(f, g, n) copy((f), (f) + (n), (g))

using namespace std;

ifstream cin("seq.in");
ofstream cout("seq.out");

const int kMaxN = 4e5 + 1, kMod = 998244353, kG = 3;
int n, m, _n, _m, p, r[kMaxN];
LL w[2][kMaxN], f[kMaxN], g[kMaxN], s[kMaxN], t[kMaxN], fact[kMaxN], _fact[kMaxN];

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

const int kInvG = Pow(kG);

void Update(int n) {
  if (n != p) {
    p = n;
    for (int i = 0; i < n; i++) {
      r[i] = r[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
    }
    for (int i = 1; i < n; i <<= 1) {
      w[0][i] = w[1][i] = 1;
      w[0][i + 1] = Pow(kG, (kMod - 1) / (i + i));
      w[1][i + 1] = Pow(kInvG, (kMod - 1) / (i + i));
      for (int j = 2; j < i; j++) {
        w[0][i + j] = w[0][i + j - 1] * w[0][i + 1] % kMod;
        w[1][i + j] = w[1][i + j - 1] * w[1][i + 1] % kMod;
      }
    }
  }
}

void Ntt(int n, LL *f, bool b) {
  for (int i = 0; i < n; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += i + i) {
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i];
        f[k] = (f0 + f1 * w[b][i - j + k] % kMod) % kMod;
        f[k + i] = (f0 - f1 * w[b][i - j + k] % kMod + kMod) % kMod;
      }
    }
  }
  if (b) {
    LL _n = Pow(n);
    for (int i = 0; i < n; i++) {
      f[i] = f[i] * _n % kMod;
    }
  }
}

void Mul(int n, LL *f) {
  Clear(f + n, n);
  Update(n << 1), Ntt(n << 1, f, 0);
  for (int i = 0; i < n << 1; i++) {
    f[i] = f[i] * f[i] % kMod;
  }
  Ntt(n << 1, f, 1);
}

void Mul(int n, LL *f, LL *g) {
  Clear(f + n, n), Clear(g + n, n);
  Update(n << 1), Ntt(n << 1, f, 0), Ntt(n << 1, g, 0);
  for (int i = 0; i < n << 1; i++) {
    f[i] = f[i] * g[i] % kMod;
  }
  Ntt(n << 1, f, 1), Ntt(n << 1, g, 1);
}

void Calc(int l, int r) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1, k = 1;
  Calc(l, mid);
  for (; k < r - l + 1; k <<= 1) {
  }
  for (int i = 0; i < k; i++) {
    s[i] = i <= mid - l ? f[i + l] + 1 : 0;
    t[i] = i <= r - l ? g[i] : 0;
  }
  Mul(k, s, t);
  for (int i = mid + 1; i <= r; i++) {
    f[i] = (f[i] + s[i - l]) % kMod;
  }
  Calc(mid + 1, r);
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
  cin >> n >> m;
  for (_n = 1; _n < n; _n <<= 1) {
  }
  for (_m = 1; _m < m; _m <<= 1) {
  }
  g[0] = 1, Copy(_fact + 1, s + 1, n - 1);
  for (int i = 1; i < m; i <<= 1) {
    if (i & m - 1) {
      Mul(_n, g, s);
    }
    Mul(_n, s);
  }
  for (int i = n; i > 0; i--) {
    g[i] = g[i - 1] * fact[i - 1] % kMod * Pow(m, kMod - i) % kMod;
  }
  g[0] = 0, Calc(0, n);
  cout << f[n] << '\n';
  return 0;
}
