#include <fstream>
#define LL long long

using namespace std;

ifstream cin("timeline.in");
ofstream cout("timeline.out");

const int kMaxN = 16, kMaxM = 1 << kMaxN - 1, kMod = 1e9 + 7;
int n, m, k, e[kMaxM];
LL ans, f[kMaxM], g[kMaxM][kMaxN + 1], h[kMaxM][kMaxN + 1];
LL fact[kMaxN << 1], _fact[kMaxN << 1];

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

int PopCount(int s) {
  int c = 0;
  for (; s; s >>= 1) {
    c += s & 1;
  }
  return c;
}

void Mul(LL f[kMaxN + 1]) {
  static LL g[kMaxN + 1];
  for (int i = 0; i <= n + 1; i++) {
    g[i] = 0;
    for (int j = n; j >= 0; j--) {
      g[i] = (g[i] * i + f[j]) % kMod;
    }
  }
  copy(&g[0], &g[n + 1] + 1, &f[0]);
}

void ReMul(LL f[kMaxN + 1]) {
  static LL g[kMaxN + 2], h[kMaxN + 1];
  g[0] = 1, fill(&g[1], &g[n + 2] + 1, 0);
  for (int i = 0; i <= n + 1; i++) {
    for (int j = i + 1; j >= 1; j--) {
      g[j] = (g[j - 1] - g[j] * i % kMod + kMod) % kMod;
    }
    g[0] = (kMod - g[0] * i % kMod) % kMod;
  }
  fill(&h[0], &h[n + 1] + 1, 0);
  for (int i = 0; i <= n + 1; i++) {
    LL w = g[n + 2], s = 1;
    for (int j = 0; j <= n + 1; j++) {
      if (i != j) {
        s = s * (i - j + kMod) % kMod;
      }
    }
    s = Pow(s) * f[i] % kMod;
    for (int j = n + 1; j >= 0; j--) {
      h[j] = (h[j] + w * s) % kMod;
      w = (w * i + g[j]) % kMod;
    }
  }
  copy(&h[0], &h[n + 1] + 1, &f[0]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN << 1; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[(kMaxN << 1) - 1] = Pow(fact[(kMaxN << 1) - 1]);
  for (int i = (kMaxN << 1) - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m >> k;
  for (int i = 0, x, y; i < m; i++) {
    cin >> x >> y;
    e[1 << x - 1] |= 1 << y - 1;
  }
  for (int s = 0; s < 1 << n; s++) {
    int t = s & -s;
    e[s] = e[s ^ t] | e[t];
  }
  f[0] = 1;
  for (int s = 1; s < 1 << n; s++) {
    for (int i = 0; i < n; i++) {
      int t = s ^ 1 << i;
      if (s > t && !(e[1 << i] & t)) {
        f[s] = (f[s] + f[t]) % kMod;
      }
    }
  }
  g[0][0] = -1;
  for (int s = 1; s < 1 << n; s++) {
    int _s = s ^ s & -s;
    for (int _t = _s;; _t = _t - 1 & _s) {
      int t = _t | s & -s;
      for (int i = 1; i <= n; i++) {
        if (!(e[s ^ t] & t) && !(e[t] & (s ^ t))) {
          g[s][i] = (g[s][i] - g[s ^ t][i - 1] * f[t] % kMod + kMod) % kMod;
        }
      }
      if (!_t) {
        break;
      }
    }
  }
  for (int s = 0; s < 1 << n; s++) {
    Mul(g[s]);
  }
  fill(&h[0][0], &h[0][n + 1] + 1, 1);
  for (int s = 0; s < 1 << n; s++) {
    for (int t = s; t; t = t - 1 & s) {
      if (!(e[s ^ t] & t)) {
        for (int i = 0; i <= n + 1; i++) {
          h[s][i] = (h[s][i] + h[s ^ t][i] * g[t][i]) % kMod;
        }
      }
    }
  }
  ReMul(h[~(-1 << n)]);
  for (int i = 1; i <= n && i <= k + 1; i++) {
    ans = (ans + h[~(-1 << n)][i] * _fact[k - i + 1]) % kMod;
  }
  cout << ans * fact[k + 1] % kMod * fact[k] % kMod * _fact[n + k] % kMod << '\n';
  return 0;
}
