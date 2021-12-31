#include <cmath>
#include <iomanip>
#include <iostream>
#define PDD pair<double, double>

using namespace std;

int n;
double ans = 1e9;
PDD p[1003];

double Cross(PDD o, PDD i, PDD j) {
  return (i.first - o.first) * (j.second - o.second) - (i.second - o.second) * (j.first - o.first);
}

double Dis(PDD i, PDD j) {
  return sqrt((i.first - j.first) * (i.first - j.first) + (i.second - j.second) * (i.second - j.second));
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first >> p[i].second;
  }
  p[++n] = p[1], p[++n] = p[2];
  for (int i = 2; i <= n - 1; i++) {
    ans = min(ans, abs(Cross(p[i], p[i - 1], p[i + 1])) / Dis(p[i - 1], p[i + 1]));
  }
  cout << fixed << setprecision(10) << ans / 2.0;
  return 0;
}
