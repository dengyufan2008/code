#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

int n, i;
double ans = 10000000.000001, f[15][15][1 << 15];
pair<double, double> a[16];

bool C(int x, int y, int z, int k) {
  return y != z && ((1 << y) & k) && (((1 << z) & k) || x == 1);
}

double M(int x, int y) {
  return sqrt(double(a[x].first - a[y].first) * double(a[x].first - a[y].first) + double(a[x].second - a[y].second) * double(a[x].second - a[y].second));
}

void S(int d, int c, int s) {
  if (c == n) {
    return;
  } else if (!s) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (C(i, j, k, d)) {
          f[i][j][d] = min(f[i][j][d], f[i - 1][k][d - (1 << j)] + M(k, j));
        }
      }
    }
    return;
  }
  S(d, c + 1, s);
  S(d + (1 << c), c + 1, s - 1);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  fill(&f[0][0][0], &f[1][0][0], 0.000001);
  fill(&f[1][0][0], &f[15][0][0], 10000000.000001);
  for (i = 1; i < n; i++) {
    S(0, 0, i);
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
