// #include <ctime>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxM = 1001, kMaxP = 51, kMod = 998244353;
int n, p, m, s, c1, c2, d[kMaxP];
LL f[kMaxP][kMaxM][kMaxP], g[kMaxP][kMaxM], h[kMaxM][kMaxM], t[kMaxP][kMaxM], _fact[kMaxM] = {1};

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

LL C(int v, int x) { return g[v][x] * _fact[x] % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p >> m;
  for (int i = 1, v = 1;; i++, v = v * 10 % p) {
    if (d[v]) {
      s = v;
      break;
    }
    d[v] = i;
  }
  for (int v = 1; v != s; v = v * 10 % p) {
    c1++, d[v] = 114514;
  }
  c2++;
  for (int v = s * 10 % p; v != s; v = v * 10 % p) {
    c2++;
  }
  for (int i = 1, v = 1; i <= c1 + c2; i++, v = v * 10 % p) {
    int w = d[v] == 114514 ? 1 : (n - d[v]) / c2 + 1;
    g[v][0] = 1;
    for (int j = 1; j <= m; j++) {
      g[v][j] = (w - j + 1) % kMod * g[v][j - 1] % kMod;
    }
  }
  for (int i = 1; i <= m; i++) {
    _fact[i] = _fact[i - 1] * Pow(i) % kMod;
  }
  h[0][0] = 1;
  for (int i = 1; i <= m; i++) {
    for (int k = 1; k <= m; k++) {
      for (int l = 1; l < 10 && l <= k; l++) {
        h[i][k] += h[i - 1][k - l];
      }
      h[i][k] %= kMod;
    }
  }
  for (int i = 1, v = 1; i <= c1 + c2; i++, v = v * 10 % p) {
    int w = d[v] == 114514 ? 1 : (n - d[v]) / c2 + 1;
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= j && k <= w; k++) {
        t[v][j] += h[k][j] * C(v, k) % kMod;
      }
      t[v][j] %= kMod;
    }
  }
  f[0][0][0] = 1;
  for (int i = 1, v = 1; i <= c1 + c2; i++, v = v * 10 % p) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k < p; k++) {
        for (int l = 0; l <= j; l++) {
          f[i][j][k] += f[i - 1][j - l][(k - v * l % p + p) % p] * t[v][l] % kMod;
        }
        f[i][j][k] %= kMod;
      }
    }
  }
  for (int i = 0, v = 0; i <= m; i++) {
    v = (v + f[c1 + c2][i][0]) % kMod;
    cout << v << ' ';
  }
  // cout << '\n' << clock();
  return 0;
}
