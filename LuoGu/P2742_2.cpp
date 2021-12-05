#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long
#define Pdd pair<double, double>

using namespace std;

int n, p[2], d[2][100001];
double ans;
Pdd a[100001];

double Cross(Pdd k, Pdd x, Pdd y) {
  return (x.first - k.first) * (y.second - k.second) - (y.first - k.first) * (x.second - k.second);
}

double Dis(Pdd x, Pdd y) {
  return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  sort(a + 1, a + n + 1);
  d[0][p[0] = 1] = 1;
  for (int i = 2; i <= n; i++) {
    for (; p[0] > 1 && Cross(a[d[0][p[0] - 1]], a[d[0][p[0]]], a[i]) < 0; p[0]--) {
    }
    d[0][++p[0]] = i;
  }
  d[1][p[1] = 1] = n;
  for (int i = n - 1; i >= 1; i--) {
    for (; p[1] > 1 && Cross(a[d[1][p[1] - 1]], a[d[1][p[1]]], a[i]) < 0; p[1]--) {
    }
    d[1][++p[1]] = i;
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < p[i]; j++) {
      ans += Dis(a[d[i][j]], a[d[i][j + 1]]);
    }
  }
  cout << fixed << setprecision(2) << ans;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}