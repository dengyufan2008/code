#include <iostream>
#include <vector>
#define PDD pair<double, double>

using namespace std;

const double kInf = 114514191981.0;
int n;
pair<PDD, PDD> l[50001];
vector<PDD> a, _a;

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
    if (Cross(x, y, a[i]) <= 0) {
      _a.push_back(a[i]);
    }
    if (Cross(x, y, a[i]) * Cross(x, y, a[i - 1]) <= 0) {
      _a.push_back(P(x, y, a[i], a[i - 1]));
    }
  }
  _a.push_back(_a[0]), a = _a;
}

int main() {
  a.push_back({kInf, kInf}), a.push_back({-kInf, kInf}), a.push_back({-kInf, -kInf}), a.push_back({kInf, -kInf}), a.push_back(a[0]);
  cin >> n;
  for (int i = 1, a, b; i <= n; i++) {
    cin >> a >> b;
    l[i] = {{-1, -a + b}, {1, a + b}};
  }
  for (int i = 1; i <= n; i++) {
    M(l[i].first, l[i].second);
  }
  for (int i = 1; i < a.size(); i++) {
    cout << a[i].first << ' ' << a[i].second << '\n';
  }
  return 0;
}
