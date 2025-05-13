#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3001, kMaxL = 17;
int n, f[kMaxL][kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  fill(&f[0][0][0], &f[1][0][0], -1), f[0][0][1] = 0;
  for (int ans = 1; ans < kMaxL; ans++) {
    for (int i = 0; i <= n; i++) {
      for (int j = 1, p = 2; j <= n - i; j++) {
        if (f[ans - 1][i][j] >= 0) {
          int l = (1 << ans - 1) - j;
          f[ans][i][j] = f[ans - 1][i][j] + l;
        } else if (j > 1 && f[ans - 1][i][1] >= j - 1) {
          for (p--; p < j && f[ans - 1][i][p] >= j - p; p++) {
          }
          f[ans][i][j] = f[ans - 1][p - 1][j - p + 1];
        } else if (1 << ans - 1 > j) {
          int l = (1 << ans - 1) - j;
          f[ans][i][j] = f[ans - 1][max(i - l, 0)][j];
        } else {
          f[ans][i][j] = -1;
        }
      }
    }
  }
  for (int i = 0, ans = kMaxL - 1; i < n; i++) {
    for (; ans >= 0 && f[ans][i][n - i] >= 0; ans--) {
    }
    cout << ans + 1 << " \n"[i + 1 == n];
  }
  return 0;
}
