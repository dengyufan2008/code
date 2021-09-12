#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

int n;
double ans = 10000000.000001, f[16][16];
pair<double, double> a[16];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  fill(&f[2][0], &f[15][15] + 1, 10000000.000001);
  for (int i = 1; i <= n; i++) {
    f[1][i] = sqrt(a[i].first * a[i].first + a[i].second * a[i].second);
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        if (j != k) {
          f[i][j] = min(f[i][j], f[i - 1][k] + sqrt((a[k].first - a[j].first) * (a[k].first - a[j].first) + (a[k].second - a[j].second) * (a[k].second - a[j].second)));
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = min(ans, f[n][i]);
  }
  cout << fixed << setprecision(2) << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
