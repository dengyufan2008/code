#include <iostream>
#define LL long long

using namespace std;

const LL kInf = 1e9;
struct V {
  LL i, j, k;
} v[101][101][9];
LL n, m, mn, ans, a[101], d[2][9], f[101][101][9];

int main() {
  cin >> n >> m;
  for (LL t = 1; n || m; t++) {
    ans = kInf, mn = -1;
    fill(&d[0][0], &d[1][8] + 1, 0), fill(&f[0][0][1], &f[100][100][100] + 1, kInf);
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
      d[0][a[i] - 24]++;
    }
    for (LL i = 0; i < n; i++) {
      for (LL j = 0; j <= m; j++) {
        for (LL k = 0; k < 9; k++) {
          LL c = f[i][j][k] + (!i || a[i + 1] - 24 != k);
          if (c < f[i + 1][j][a[i + 1] - 24]) {
            f[i + 1][j][a[i + 1] - 24] = c;
            v[i + 1][j][a[i + 1] - 24] = {i, j, k};
          }
          if (j < m && f[i][j][k] < f[i + 1][j + 1][k]) {
            f[i + 1][j + 1][k] = f[i][j][k];
            v[i + 1][j + 1][k] = {i, j, k};
          }
        }
      }
    }
    for (LL i = 0; i < 9; i++) {
      if (mn != -1 || f[n][m][i] < f[n][m][mn]) {
        mn = i, ans = f[n][m][i];
      }
    }
    for (LL i = n, j = m, k = mn; i;) {
      V c = v[i][j][k];
      if (j == c.j) {
        d[1][k]++;
      }
      i = c.i, j = c.j, k = c.k;
    }
    for (LL i = 1; i < 9; i++) {
      ans += d[0][i] && !d[1][i];
    }
    cout << "Case " << t << ": " << ans << "\n\n";
    cin >> n >> m;
  }
  return 0;
}
