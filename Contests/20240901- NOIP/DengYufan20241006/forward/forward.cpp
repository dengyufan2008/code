#include <fstream>
#define LL unsigned long long

using namespace std;

ifstream cin("forward.in");
ofstream cout("forward.out");

const int kMaxN = 401, kMaxL = 30, kMod = 998244353;
int n, m, q, s, t, d[kMaxN];
bool e[kMaxN][kMaxN];
LL f[kMaxN], g[kMaxN], pw[kMaxL][kMaxN][kMaxN];

void Mul(LL a[kMaxN][kMaxN], LL b[kMaxN][kMaxN]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = 0;
      for (int k = 1; k <= n; k += 16) {
        a[i][j] = (a[i][j] + b[i][k] * b[k][j] + b[i][k + 1] * b[k + 1][j] +
                   b[i][k + 2] * b[k + 2][j] + b[i][k + 3] * b[k + 3][j] +
                   b[i][k + 4] * b[k + 4][j] + b[i][k + 5] * b[k + 5][j] +
                   b[i][k + 6] * b[k + 6][j] + b[i][k + 7] * b[k + 7][j] +
                   b[i][k + 8] * b[k + 8][j] + b[i][k + 9] * b[k + 9][j] +
                   b[i][k + 10] * b[k + 10][j] + b[i][k + 11] * b[k + 11][j] +
                   b[i][k + 12] * b[k + 12][j] + b[i][k + 13] * b[k + 13][j] +
                   b[i][k + 14] * b[k + 14][j] + b[i][k + 15] * b[k + 15][j]) %
                  kMod;
      }
    }
  }
}

void Mul(LL a[kMaxN], LL b[kMaxN][kMaxN]) {
  static LL c[kMaxN];
  for (int i = 1; i <= n; i++) {
    c[i] = 0;
    for (int j = 1; j <= n; j += 16) {
      c[i] = (c[i] + a[j] * b[j][i] + a[j + 1] * b[j + 1][i] +
              a[j + 2] * b[j + 2][i] + a[j + 3] * b[j + 3][i] +
              a[j + 4] * b[j + 4][i] + a[j + 5] * b[j + 5][i] +
              a[j + 6] * b[j + 6][i] + a[j + 7] * b[j + 7][i] +
              a[j + 8] * b[j + 8][i] + a[j + 9] * b[j + 9][i] +
              a[j + 10] * b[j + 10][i] + a[j + 11] * b[j + 11][i] +
              a[j + 12] * b[j + 12][i] + a[j + 13] * b[j + 13][i] +
              a[j + 14] * b[j + 14][i] + a[j + 15] * b[j + 15][i]) %
             kMod;
    }
  }
  copy(&c[1], &c[n] + 1, &a[1]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q >> s >> t;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, d[x]++, d[y]++, e[x][y] = e[y][x] = 1;
  }
  for (int i = 1; i <= n; i++) {
    f[i] = e[s][i];
    for (int j = 1; j <= n; j++) {
      f[n + i] += e[s][j] && e[j][i];
    }
  }
  f[n + s] = 0;
  for (int i = 1; i <= n; i++) {
    pw[0][n + i][i] = 1;
    pw[0][i][n + i] = (1 - d[i] + kMod) % kMod;
    for (int j = 1; j <= n; j++) {
      pw[0][n + i][n + j] = e[i][j];
    }
  }
  n <<= 1;
  for (int i = 1; i < kMaxL; i++) {
    Mul(pw[i], pw[i - 1]);
  }
  for (int i = 1, x; i <= q; i++) {
    cin >> x;
    if (x == 1) {
      cout << e[s][t] << '\n';
    } else {
      x -= 2, copy(&f[1], &f[n] + 1, &g[1]);
      for (int j = 0; j < kMaxL; j++) {
        if (x >> j & 1) {
          Mul(g, pw[j]);
        }
      }
      cout << g[(n >> 1) + t] << '\n';
    }
  }
  return 0;
}
