// not be done
#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 1e5 + 1, kMod = 998244353;
int t, n, m, k, a[kMaxN];
LL fact[kMaxN], _fact[kMaxN];
LL ans, f[kMaxN << 2], g[kMaxN << 2];

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
    ans = 0, fill(&f[0], &f[k], 0), fill(&g[0], &g[k], 0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (k = 1; k < m; k <<= 1) {
    }
    k <<= 1;
    for (int i = 1; i <= m; i++) {
      g[i] = _fact[i];
      f[i] = C(m, i) * fact[m - i] % kMod * Pow(i) % kMod;
      if (i & 1) {
        f[i] = kMod - f[i];
      }
    }
    Ntt(f, 0), Ntt(g, 0);
    for (int i = 0; i < k; i++) {
      f[i] = f[i] * g[i] % kMod;
    }
    Ntt(f, 1);
    ;
    // for (int i = 1; i <= m; i++) {
    //   LL v = 0;
    //   for (int j = i; j <= m; j++) {
    //     LL w = C(m - i, j - i);
    //     for (int k = 1; k <= n; k++) {
    //       w = w * C(m - j, a[k]) % kMod;
    //     }
    //     if (j & 1) {
    //       v = (v - w + kMod) % kMod;
    //     } else {
    //       v = (v + w) % kMod;
    //     }
    //   }
    //   v = v * C(m, i) % kMod * Pow(i) % kMod;
    //   if (i & 1) {
    //     ans = (ans - v + kMod) % kMod;
    //   } else {
    //     ans = (ans + v) % kMod;
    //   }
    // }
    ans = ans * m % kMod;
    for (int i = 1; i <= n; i++) {
      ans = ans * Pow(C(m, a[i])) % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}
