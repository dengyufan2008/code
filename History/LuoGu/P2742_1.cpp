#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long
#define Pdd pair<double, double>

using namespace std;

int n, p = 1, d[100001] = {0, 1};
double ans;
Pdd c = {10000000, 10000000}, a[100001];

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
    c = min(c, a[i]);
  }
  sort(a + 1, a + n + 1, [](Pdd i, Pdd j) {
    return Cross(c, i, j) > 0 || Cross(c, i, j) == 0 && Dis(c, i) < Dis(c, j);
  });
  for (int i = 2; i <= n; i++) {
    for (; p > 1 && Cross(a[d[p - 1]], a[d[p]], a[i]) < 0; p--) {
    }
    d[++p] = i;
  }
  ans = Dis(a[d[1]], a[d[p]]);
  for (int i = 1; i < p; i++) {
    ans += Dis(a[d[i]], a[d[i + 1]]);
  }
  cout << fixed << setprecision(2) << ans;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
