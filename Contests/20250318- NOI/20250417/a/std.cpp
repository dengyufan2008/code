#include <fstream>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.ans");

const int kMaxN = 301;
int n, m, k, ans, a[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 1, x, y; i <= k; i++) {
    cin >> x >> y, a[x][y] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int d = 1; d <= min(n - i, m - j); d++) {
        int w = a[i + d - 1][j + d - 1] - a[i][j + d - 1] - a[i + d - 1][j] + a[i][j];
        if (!w) {
          ans += d * d;
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
