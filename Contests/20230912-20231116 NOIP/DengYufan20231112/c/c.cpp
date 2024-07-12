#include <iostream>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 5001, kInf = 1e9;
int t, n, m, ans, sumb[kMaxN], sumq[kMaxN], f[kMaxN][kMaxN], g[kMaxN][kMaxN];
string a, b;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> a >> b;
    a = '~' + a, b = '~' + b;
    sumb[0] = sumq[0] = 0, ans = kInf;
    fill(&f[0][0], &f[m][kMaxN], 0);
    fill(&g[0][0], &g[m - 1][kMaxN], kInf);
    fill(&g[m][0], &g[m][kMaxN], 0);
    for (int i = 1; i <= n; i++) {
      sumb[0] += a[i] == 'B';
      sumq[0] += a[i] == 'Q';
    }
    for (int i = 1; i <= m; i++) {
      sumb[i] = sumb[i - 1] + (b[i] == 'B');
      sumq[i] = sumq[i - 1] + (b[i] == 'Q');
    }
    f[0][sumb[0]] = 1;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j <= sumb[i]; j++) {
        if (f[i][j]) {
          int t = sumq[i] - i + (sumb[i] - j << 1);
          if (j) {
            int _i = min(i + 2, m);
            f[_i][j - 1 + sumb[_i] - sumb[i]] = 1;
          }
          if (t) {
            int _i = i + 1;
            f[_i][j + sumb[_i] - sumb[i]] = 1;
          }
        }
      }
    }
    for (int i = m - 1; i >= 0; i--) {
      for (int j = 0; j <= sumb[i]; j++) {
        if (j) {
          g[i][j] = min(g[i][j], max(g[min(i + 2, m)][j - 1 + sumb[i + 1] - sumb[i]] - sumq[i + 1] + sumq[i], 0));
        }
        g[i][j] = min(g[i][j], max(g[i + 1][j + sumb[i + 1] - sumb[i]] + 1 - sumq[i + 1] + sumq[i], 1));
      }
    }
    for (int i = 0; i <= m; i++) {
      for (int j = 0; j <= sumb[i]; j++) {
        int t = sumq[i] - i + (sumb[i] - j << 1);
        if (f[i][j] && g[i][j] <= t) {
          ans = min(ans, n + sumb[i] - j);
        }
      }
    }
    if (ans == kInf) {
      cout << "IMPOSSIBLE\n";
    } else {
      cout << ans << '\n';
    }
  }
  return 0;
}
