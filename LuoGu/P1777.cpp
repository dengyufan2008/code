#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1e9;
int n, m, ans, a[101], f[101][101][9];

int main() {
  cin >> n >> m;
  for (int t = 1; n || m; t++) {
    ans = kInf, fill(&f[0][0][0], &f[0][100][100] + 1, 1), fill(&f[1][0][0], &f[100][100][100] + 1, kInf);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= m; j++) {
        for (int k = 1; k < 9; k++) {
          f[i + 1][j][k] = min(f[i + 1][j][k], f[i][j][k] + (a[i + 1] != k + 24));
          if (j < m) {
            f[i + 1][j + 1][a[i + 1] - 24] = min(f[i + 1][j + 1][a[i + 1] - 24], f[i][j][k]);
          }
        }
      }
    }
    for (int i = 1; i < 9; i++) {
      ans = min(ans, f[n][m][i]);
    }
    cout << "Case " << t << ": " << ans << '\n';
    cin >> n >> m;
  }
  return 0;
}
