#include <fstream>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 101, kMaxM = 501;
int t, n, m, p;
LL f[kMaxN][kMaxM][kMaxM], g[kMaxN][kMaxM][kMaxM], h[kMaxN][kMaxM];

void Update(LL &x, LL y) { x = (x + y) % p; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> p;
    for (int i = 0; i <= m; i++) {
      h[2][i] = (i + 1) * (i + 2) / 2;
      for (int j = 0; j <= m; j++) {
        f[2][i][j] = g[2][i][j] = max(min(j, i - j + 1), 0) * 2;
      }
      for (int j = m - 1; j >= 0; j--) {
        Update(f[2][i][j], f[2][i][j + 1]);
      }
      for (int j = 1; j <= m; j++) {
        Update(g[2][i][j], g[2][i][j - 1]);
      }
    }
    for (int i = 3; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        h[i][j] = 0;
        for (int k = 0; k <= m; k++) {
          f[i][j][k] = g[i][j][k] = 0;
        }
      }
      for (int j = 0; j <= m; j++) {
        for (int k = 0; j + k <= m; k++) {
          Update(h[i][j + k], h[i - 1][j] * h[i - 1][k]);
        }
      }
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k < j && j + k <= m; k++) {
          Update(g[i][j + k][j], g[i - 1][j][m] * h[i - 1][k] * 2);
        }
      }
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k < j && j + k <= m; k++) {
          Update(f[i][j + k][j], f[i - 1][j][k + 1] * h[i - 1][k] * 2);
        }
      }
      for (int j = 0; j <= m; j++) {
        for (int k = 1; k < j && j + k <= m; k++) {
          Update(f[i][j + k][j], g[i - 1][j][k - 1] * g[i - 1][k][m] * 2);
        }
      }
      for (int j = 1; j <= m; j++) {
        Update(h[i][j], h[i][j - 1]);
        for (int k = 0; k <= m; k++) {
          Update(f[i][j][k], f[i][j - 1][k]);
          Update(g[i][j][k], g[i][j - 1][k]);
        }
      }
      for (int j = 0; j <= m; j++) {
        for (int k = m - 1; k >= 0; k--) {
          Update(f[i][j][k], f[i][j][k + 1]);
        }
        for (int k = 1; k <= m; k++) {
          Update(g[i][j][k], g[i][j][k - 1]);
        }
      }
    }
    cout << f[n][m][0] << '\n';
  }
  return 0;
}
