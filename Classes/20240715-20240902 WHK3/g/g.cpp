#include <iostream>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxL = 100, kMod = 1e9 + 7;
vector<LL> w[kMaxL];  // W_i(x) = \sum_{j=0}^{x-1} j^i

LLL Read() {
  LLL x = 0;
  int c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

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

void Init() {
  static LL t, f[kMaxL + 2], g[kMaxL + 2];
  for (int i = 0; i < kMaxL; i++) {
    f[0] = 1;
    for (int j = 1; j <= i + 2; j++) {
      f[j] = 0;
    }
    for (int j = 0; j <= i + 1; j++) {
      g[0] = f[0] * -j % kMod;
      for (int k = 1; k <= i + 2; k++) {
        g[k] = (f[k - 1] - f[k] * j) % kMod;
      }
      for (int k = 0; k <= i + 2; k++) {
        f[k] = g[k];
      }
    }
    g[i + 2] = t = 0, w[i].clear(), w[i].resize(i + 2);
    for (int j = 0; j <= i + 1; j++) {
      for (int k = i + 1; k >= 0; k--) {
        g[k] = (f[k + 1] + g[k + 1] * j) % kMod;
      }
      LL s = 1;
      for (int k = 0; k <= i + 1; k++) {
        if (j != k) {
          s = s * (j - k) % kMod;
        }
      }
      s = t * Pow(s) % kMod;
      for (int k = 0; k <= i + 1; k++) {
        w[i][k] = (w[i][k] + g[k] * s) % kMod;
      }
      s = 1;
      for (int k = 1; k <= i; k++) {
        s = s * j % kMod;
      }
      t = (t + s) % kMod;
    }
  }
}

LL Solve(LLL n) {
  static vector<LL> f, g;
  f.clear(), f.push_back(1);
  for (n >>= 1; n; n >>= 1) {
    LL s = 0;
    g.clear(), g.resize(f.size() + 1);
    for (int i = 0; i < f.size(); i++) {
      LL o1 = 1, o2 = 1;
      for (int j = 0; j < w[i].size(); j++) {
        s = (s + f[i] * w[i][j] % kMod * o1) % kMod;
        g[j] = (g[j] + f[i] * w[i][j] % kMod * o2) % kMod;
        o1 = o1 * ((n + 1) % kMod) % kMod;
        o2 = o2 * 2 % kMod;
      }
    }
    f.clear(), f.resize(g.size());
    for (int i = 0; i < g.size(); i++) {
      f[i] = -g[i];
    }
    f[0] = (f[0] + s) % kMod;
  }
  return (f[0] + kMod) % kMod;
}

int main() {
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), cout << Solve(Read()) << '\n';
  return 0;
}
