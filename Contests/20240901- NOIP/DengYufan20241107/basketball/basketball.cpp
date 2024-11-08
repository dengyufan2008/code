#include <fstream>
#define LL long long

using namespace std;

ifstream cin("basketball.in");
ofstream cout("basketball.out");

const LL kMaxN = 201, kMaxM = 10, kInf = 1e18;
int n, m, t, a[kMaxN], b[kMaxN], w[kMaxM * 2];
LL f[kMaxN][kMaxN], g[kMaxN][kMaxN][kMaxM], h[kMaxN][kMaxN][kMaxM];

void Update(LL &x, LL y) { x = max(x, y); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = m; i <= m * 2 - 2; i++) {
    cin >> w[i];
  }
  for (int i = 1; i <= n; i++) {
    f[i][i] = w[m] - (m - b[i]) * t;
    for (int j = 1; j < m; j++) {
      g[i][i][j] = h[i][i][j] = -kInf;
    }
    g[i][i][b[i]] = h[i][i][b[i]] = 0;
  }
  for (int i = 2; i <= n; i++) {
    for (int l = 1, r; (r = l + i - 1) <= n; l++) {
      f[l][r] = -kInf;
      for (int k = 1; k < m; k++) {
        g[l][r][k] = h[l][r][k] = -kInf;
      }
      for (int j = l; j < r; j++) {
        if (l == 1 || r == n || a[l - 1] != a[j + 1] || a[j] != a[r + 1]) {
          Update(f[l][r], f[l][j] + f[j + 1][r]);
        }
      }
      if (a[l] == a[r]) {
        for (int j = l; j < r; j++) {
          for (int k1 = 1; k1 < m; k1++) {
            for (int k2 = 1; k2 < m; k2++) {
              if (k1 + k2 < m) {
                Update(f[l][r], g[l][j][k1] + h[j + 1][r][k2] + w[m] - (m - k1 - k2) * t);
              } else {
                Update(f[l][r], g[l][j][k1] + h[j + 1][r][k2] + w[k1 + k2]);
              }
            }
          }
        }
      }
      Update(g[l][r][b[l]], f[l + 1][r]);
      Update(h[l][r][b[r]], f[l][r - 1]);
      for (int j = l + 1; j < r; j++) {
        for (int k = 1; k < m; k++) {
          if (a[l] == a[j + 1] && k + b[l] < m) {
            Update(g[l][r][k + b[l]], f[l + 1][j] + g[j + 1][r][k]);
          }
          if (a[r] == a[j - 1] && k + b[r] < m) {
            Update(h[l][r][k + b[r]], h[l][j - 1][k] + f[j][r - 1]);
          }
        }
      }
    }
  }
  cout << f[1][n] << '\n';
  return 0;
}
