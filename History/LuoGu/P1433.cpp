#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

int n;
double ans = 10000000.000001, f[15][1 << 15];
pair<double, double> a[16];

double M(int x, int y) {
  return sqrt((a[x].first - a[y].first) * (a[x].first - a[y].first) + (a[x].second - a[y].second) * (a[x].second - a[y].second));
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  fill(&f[0][0], &f[15][0], 10000000.000001);
  for (int i = 0; i < n; i++) {
    f[i][1 << i] = 0;
  }
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (j != k && (i & (1 << j)) && (i & (1 << k))) {
          f[j][i] = min(f[j][i], f[k][i - (1 << j)] + M(j, k));
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    ans = min(ans, f[i][(1 << n) - 1] + M(15, i));
  }
  cout << fixed << setprecision(2) << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
