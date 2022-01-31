#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1e9;
int n, m, mn, d, ans, a[101], f[2][101][512][8];

int main() {
  cin >> n >> m;
  for (int t = 1; n || m; t++) {
    mn = -1, d = 0, ans = kInf;
    fill(&f[0][0][0][0], &f[1][100][511][7] + 1, kInf), fill(&f[0][0][0][0], &f[0][0][0][7] + 1, 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      d |= 1 << (a[i] -= 25);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k < 512; k++) {
          for (int l = 0; l < 8; l++) {
            f[i & 1 ^ 1][j][k | 1 << a[i + 1]][a[i + 1]] = min(f[i & 1 ^ 1][j][k | 1 << a[i + 1]][a[i + 1]], f[i & 1][j][k][l] + (l != a[i + 1]));
            if (j < m) {
              f[i & 1 ^ 1][j + 1][k][l] = min(f[i & 1 ^ 1][j + 1][k][l], f[i & 1][j][k][l]);
            }
          }
        }
      }
    }
    for (int i = 0; i < 512; i++) {
      for (int j = 0; j < 8; j++) {
        if (mn == -1 || ans > f[n & 1][m][i][j]) {
          ans = f[n & 1][m][mn = i][j];
        }
      }
    }
    for (int i = 0; i < 8; i++) {
      ans += ((d ^ mn) & (1 << i)) > 0;
    }
    cout << "Case " << t << ": " << ans << "\n\n";
    cin >> n >> m;
  }
  return 0;
}
