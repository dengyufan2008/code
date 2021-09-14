#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

int n;
double ans = 10000000.000001, f[16][15][1 << 15];
pair<double, double> a[15];

bool C(int x, int y) {
  int c = 0;
  for (int i = 0; i < n; i++) {
    c += ((1 << i) & y) > 0;
  }
  return c == x;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  fill(&f[0][0][0], &f[1][0][0], 0.000001);
  fill(&f[1][0][0], &f[15][0][0], 10000000.000001);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < (1 << n); k++) {
        for (int l = 0; l < n; l++) {
          if (j != l && C(i, k) && ((1 << j) & k) && ((1 << l) & k)) {
            f[i][j][k] = min(f[i][j][k], f[i - 1][l][k - (1 << j)] + sqrt((a[j].first - a[l].first) * (a[j].first - a[l].first) + (a[j].second - a[l].second) * (a[j].second - a[l].second)));
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    ans = min(ans, f[n][i][(1 << n) - 1]);
  }
  cout << fixed << setprecision(2) << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
