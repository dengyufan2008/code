#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("test.in");
ofstream cout("test.out");

const int kMaxN = 15, kMod = 1e9 + 7;
int n, e[kMaxN], c[1 << kMaxN];
LL f[1 << kMaxN], g[1 << kMaxN];
LL pw[kMaxN * kMaxN];

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

void CalcSCC(LL *f) {  // 计算 s 的点导出子图的强连通边集数量
  static LL g[1 << kMaxN];
  static vector<int> l;
  for (int s = 1; s < 1 << n; s++) {
    g[s] = 0;
    for (int _s = s & s - 1, t = _s; t; t = t - 1 & _s) {
      g[s] = (g[s] + g[t] * f[s ^ t]) % kMod;
    }
    g[s] = (kMod - g[s]) % kMod;
    f[s] = (pw[c[s] << 1] + g[s]) % kMod;
    l.clear();
    for (int t = s; t; t = t - 1 & s) {
      l.push_back(t);
    }
    for (; !l.empty(); l.pop_back()) {
      int t = l.back();
      f[s] = (f[s] + g[s ^ t] * pw[c[s] - c[s ^ t] + c[t]]) % kMod;
    }
    g[s] = (g[s] - f[s] + kMod) % kMod;
  }
}

// void CalcTo(LL *f) {  // 计算 s 内的点能到达 u \ s 的点, 但 u \ s 内的点不能到达 s 内的点的边集数量
//   static LL g[1 << kMaxN];
//   for (int u = 1; u < 1 << n; u++) {
//     for (int s = u; s < 1 << n; s = s + 1 | u) {
//       int _s = s ^ u;
//       g[s] = 0;
//       for (int _t = _s; _t; _t = _t - 1 & _s) {
//         int t = u | (_s ^ _t);
//         g[s] = (g[s] + g[t] * pw[c[s ^ t] - c[u ^ t] + c[_s]]) % kMod;
//       }
//       g[s] = (pw[c[s] - c[u] + c[_s]] - g[s] + kMod) % kMod;
//     }
//     f[u] = g[(1 << n) - 1];
//   }
// }

void CalcTo(LL *f) {  // 将上面的代码视为从小集合走向大集合的带权方案数, 直接反向即可
  f[(1 << n) - 1] = 1;
  for (int s = (1 << n) - 2; s >= 0; s--) {
    f[s] = 0;
    for (int t = s + 1 | s; t < 1 << n; t = t + 1 | s) {
      f[s] = (f[s] + f[t] * pw[c[s ^ t]]) % kMod;
    }
    f[s] = (kMod - f[s]) % kMod;
  }
  for (int s = 0; s < 1 << n; s++) {
    f[s] = f[s] * pw[c[s]] % kMod;
  }
  for (int i = 0; i < n; i++) {
    for (int s = 1 << i; s < 1 << n; s = s + 1 | 1 << i) {
      f[s ^ 1 << i] = (f[s ^ 1 << i] + f[s]) % kMod;
    }
  }
  for (int s = 0; s < 1 << n; s++) {
    f[s] = f[s] * pw[c[(1 << n) - 1 ^ s]] % kMod * Pow(pw[c[s]]) % kMod;
  }
  f[0] = 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN * kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  int m, t;
  cin >> t >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      e[i] = 0;
    }
    for (int i = 0, x, y, z; i < m; i++) {
      cin >> x >> y >> z, x--, y--;
      e[x] |= 1 << y, e[y] |= 1 << x;
    }
    for (int s = 1; s < 1 << n; s++) {
      int x = 31 - __builtin_clz(s & -s);
      c[s] = c[s & s - 1] + __builtin_popcount(e[x] & s);
    }
    CalcSCC(f), CalcTo(g);
    LL ans = 0;
    for (int s = 1; s < 1 << n; s++) {
      ans = (ans + f[s] * g[s]) % kMod;
    }
    cout << (ans % kMod + kMod) * Pow(2, kMod - 1 - m - m) % kMod << '\n';
  }
  return 0;
}
