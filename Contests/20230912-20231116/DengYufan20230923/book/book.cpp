#include <fstream>
#include <vector>

using namespace std;

ifstream cin("book.in");
ofstream cout("book.out");

const int kMaxN = 72, kMaxV = 232, kInf = 1e9;
int t, n, m, a[kMaxN], f[kMaxN][kMaxN][kMaxV];

int main() {
  for (int i = 0; i < kMaxN; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = i != j; k < kMaxV; k++) {
        f[i][j][k] = kInf;
      }
    }
  }
  cin >> t >> t;
  while (t--) {
    m = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      f[i][i][a[i] / 2] = kInf;
      cin >> a[i];
      m = max(m, a[i] * 3 >> 1);
      f[i][i][a[i] / 2] = a[i];
    }
    for (int i = 2; i <= n; i++) {
      for (int j = 1, k; (k = j + i - 1) <= n; j++) {
        fill(&f[j][k][0], &f[j][k][m] + 1, kInf);
        for (int l = j; l <= k; l++) {
          for (int x = 0; x <= m; x++) {
            for (int y = 0; y <= m; y++) {
              int z = (max(x, a[l]) >> 1) + y;
              if (z <= m) {
                f[j][k][z] = min(f[j][k][z], f[j][l - 1][x] + f[l + 1][k][y] + max(a[l] - x, 0));
              }
            }
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      int ans = kInf;
      for (int j = 0; j <= m; j++) {
        ans = min(ans, f[1][i][j]);
      }
      cout << ans << ' ';
    }
    cout << '\n';
  }
  return 0;
}
