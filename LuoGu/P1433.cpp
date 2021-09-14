#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

int n;
double ans = 10000000.000001, f[15][15][1 << 15];
pair<double, double> a[16];

bool C(int x, int y, int z, int k) {
  int c = 0;
  for (int i = 0; i < n; i++) {
    c += ((1 << i) & k) > 0;
  }
  return c == x && y != z && ((1 << y) & k) && (((1 << z) & k) || x == 1);
}

double M(int x, int y) {
  return sqrt(double(a[x].first - a[y].first) * double(a[x].first - a[y].first) + double(a[x].second - a[y].second) * double(a[x].second - a[y].second));
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  fill(&f[0][0][0], &f[1][0][0], 0.000001);
  fill(&f[1][0][0], &f[15][0][0], 10000000.000001);
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < (1 << n); l++) {
          if (C(i, j, k, l)) {
            f[i][j][l] = min(f[i][j][l], f[i - 1][k][l - (1 << j)] + M(k, j));
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans = min(ans, f[n - 1][i][(1 << n) - (1 << j) - 1] + M(15, j));
    }
  }
  cout << fixed << setprecision(2) << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
