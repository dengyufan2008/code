#include <fstream>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 8e3 + 3, kMaxM = 201, kMod = 998244353;
int n, m, o, r[kMaxN << 2];
LL ans, f[kMaxN << 2], g[kMaxN << 2];
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

void Ntt(LL f[kMaxN << 2], bool o) {
  for (int i = 0; i < m; i++) {
    i < r[i] ? swap(f[i], f[r[i]]) : void();
  }
  for (int i = 1; i < m; i <<= 1) {
    LL g = Pow(3, (kMod - 1) / (i + i) * (o ? i + i - 1 : 1));
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
    LL _m = Pow(m);
    for (int i = 0; i < m; i++) {
      f[i] = f[i] * _m % kMod;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> o;
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  for (m = 1; m <= n; m <<= 1) {
  }
  m <<= 1, f[0] = 1;
  for (int i = 0; i < m; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? m >> 1 : 0);
  }
  for (int i = 1; i <= o; i++) {
    static LL h[kMaxN] = {};
    for (int j = 0; j <= n; j++) {
      g[j] = _fact[j + 2], h[j] = f[j] * j % kMod;
      f[j] = f[j] * _fact[j] % kMod;
    }
    Ntt(f, 0), Ntt(g, 0);
    for (int j = 0; j < m; j++) {
      f[j] = f[j] * g[j] % kMod;
    }
    Ntt(f, 1);
    for (int j = 0; j <= n; j++) {
      f[j] = (f[j] * fact[j + 2] - h[j] + kMod) % kMod;
    }
    for (int j = n + 1; j < m; j++) {
      f[j] = g[j] = 0;
    }
  }
  for (int j = 0; j <= n; j++) {
    ans = (ans + f[j] * C(n, j)) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
