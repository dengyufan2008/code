#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long
#define LD long double

using namespace std;

LL n, m, a[101][101], f[101][101];
LD d[101];

int main() {
  cin >> n >> m;
  fill(&a[0][0], &a[100][100] + 1, 1 << 29), fill(&d[0], &d[100] + 1, 1e-8);
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    a[x][y] = a[y][x] = z, f[x][y] = f[y][x] = 1;
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      for (LL k = 1; k <= n; k++) {
        if (j != k) {
          if (a[j][k] > a[j][i] + a[i][k]) {
            f[j][k] = f[j][i] * f[i][k], a[j][k] = a[j][i] + a[i][k];
          } else if (a[j][k] == a[j][i] + a[i][k]) {
            f[j][k] += f[j][i] * f[i][k];
          }
        }
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      for (LL k = 1; k <= n; k++) {
        if (i != j && i != k && a[j][k] == a[j][i] + a[i][k]) {
          d[i] += (LD)f[j][i] * (LD)f[i][k] / (LD)f[j][k];
        }
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    cout << fixed << setprecision(3) << d[i] << '\n';
  }
  // cout << "Runtime:" << (LD)clock() / 1000.0 << "s" << endl;
  return 0;
}
