#include <iomanip>
#include <iostream>
#include <vector>
#define PDD pair<double, double>

using namespace std;

const double kInf = 1e4;
int n, m;
double ans;
vector<PDD> a, _a;
PDD d[51];

double Cross(PDD s, PDD x, PDD y) {
  return (x.first - s.first) * (y.second - s.second) - (x.second - s.second) * (y.first - s.first);
}

PDD P(PDD x, PDD y, PDD p, PDD q) {
  double s1 = Cross(x, p, y), s2 = s1 + Cross(x, y, q);
  return {p.first + (q.first - p.first) * s1 / s2, p.second + (q.second - p.second) * s1 / s2};
}

void M(PDD x, PDD y) {
  _a.clear();
  for (int i = 1; i < a.size(); i++) {
    if (Cross(x, y, a[i]) * Cross(x, y, a[i - 1]) <= 0) {
      _a.push_back(P(x, y, a[i], a[i - 1]));
    }
    if (Cross(x, y, a[i]) >= 0) {
      _a.push_back(a[i]);
    }
  }
  _a.push_back(_a[0]), a = _a;
}

int main() {
  a.push_back({kInf, kInf}), a.push_back({-kInf, kInf}), a.push_back({-kInf, -kInf}), a.push_back({kInf, -kInf}), a.push_back(a[0]);
  cin >> n;
  while (n--) {
    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> d[i].first >> d[i].second;
    }
    d[0] = d[m];
    for (int i = 1; i <= m; i++) {
      M(d[i - 1], d[i]);
    }
  }
  for (int i = 1; i < a.size(); i++) {
    ans += Cross({0, 0}, a[i - 1], a[i]);
  }
  cout << fixed << setprecision(3) << ans / 2;
  return 0;
}
