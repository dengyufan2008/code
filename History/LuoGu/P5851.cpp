#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, m, f[301][301][301], g[301][301];

int main() {
  cin >> n >> m;
  for (int i = 1, w, l, r; i <= m; i++) {
    cin >> w >> l >> r;
    for (int j = l; j <= r; j++) {
      f[j][l][r] = w;
    }
  }
  for (int k = 1; k <= n; k++) {
    for (int i = k; i >= 1; i--) {
      for (int j = k; j <= n; j++) {
        if (i != 1) {
          f[k][i - 1][j] = max(f[k][i - 1][j], f[k][i][j]);
        }
        if (j != n) {
          f[k][i][j + 1] = max(f[k][i][j + 1], f[k][i][j]);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      for (int l = j; l < k; l++) {
        g[j][k] = max(g[j][k], g[j][l] + g[l + 1][k]);
      }
      for (int l = j; l <= k; l++) {
        g[j][k] = max(g[j][k], (l != j) * g[j][l - 1] + (l != k) * g[l + 1][k] + f[l][j][k]);
      }
    }
  }
  cout << g[1][n] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
