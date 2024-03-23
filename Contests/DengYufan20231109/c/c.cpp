#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 12;
const double kEps = 1e-6;
int t, n;
double c, ans, a[kMaxN][kMaxN], d[kMaxN][kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> a[i][j];
      }
    }
    ans = 0;
    for (int s = 0; s < (1 << n); s++) {
      fill(&d[0][0], &d[kMaxN][0], 0);
      for (int i = 0; i < n; i++) {
        if (!(s >> i & 1)) {
          d[i][n] = 1;
          for (int j = 0; j < n; j++) {
            if (i != j && !(s >> j & 1)) {
              d[i][j] = a[i][j];
            }
          }
        }
      }
      for (int i = 0; i < n; i++) {
        if (!(s >> i & 1)) {
          d[n][i] = 1;
        }
      }
      d[n][n + 1] = 1;
      for (int i = 0; i <= n; i++) {
        if (fabs(d[i][i]) < kEps) {
          for (int j = i + 1; j <= n; j++) {
            if (fabs(d[j][i]) > kEps) {
              swap(d[i], d[j]);
              break;
            }
          }
        }
        if (fabs(d[i][i]) > kEps) {
          for (int j = n + 1; j >= i; j--) {
            d[i][j] /= d[i][i];
          }
          for (int j = i + 1; j <= n; j++) {
            if (fabs(d[j][i]) > kEps) {
              for (int k = n + 1; k >= i; k--) {
                d[j][k] -= d[j][i] * d[i][k];
              }
            }
          }
        }
      }
      for (int i = n; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
          if (fabs(d[j][i]) > kEps) {
            for (int k = n + 1; k >= i; k--) {
              d[j][k] -= d[j][i] * d[i][k];
            }
          }
        }
      }
      c = 0;
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          c += a[i][j] * d[i][n + 1] * d[j][n + 1];
        }
      }
      for (int i = 0; i < n; i++) {
        if (d[i][n + 1] < -kEps && !(s >> i & 1)) {
          c = -1e9;
        }
      }
      ans = max(ans, c);
    }
    cout << fixed << setprecision(10) << ans << '\n';
  }
  return 0;
}
