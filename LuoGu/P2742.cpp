#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long
#define Pdd pair<double, double>

using namespace std;

int n, p, d[100001] = {0, 1};
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
    if (!p || a[p] > a[i]) {
      p = i;
    }
  }
  swap(a[1], a[p]);
  sort(a + 2, a + n + 1, [](Pdd i, Pdd j) {
    return Cross(a[1], i, j) > 0 || Cross(a[1], i, j) == 0 && Dis(a[1], i) < Dis(a[1], j);
  });
  p = 1;
  for (int i = 2; i <= n; i++) {
    while (p > 1 && Cross(a[d[p - 1]], a[d[p]], a[i]) < 0) {
      p--;
    }
    d[++p] = i;
  }
  for (int i = 1; i < p; i++) {
    ans += Dis(a[d[i]], a[d[i + 1]]);
  }
  cout << fixed << setprecision(2) << ans + Dis(a[d[p]], a[d[1]]);
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
