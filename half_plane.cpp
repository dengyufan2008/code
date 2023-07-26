#include <algorithm>
#include <iomanip>
#include <iostream>
#define PDD pair<double, double>
#define VEC pair<PDD, PDD>

using namespace std;

const int kMaxN = 501;
const double kEps = 1e-6, kInf = 1145141919.810;
int n, m = 4, h, t;
double ans;
PDD a[kMaxN];
VEC v[kMaxN] = {{}, {{-kInf, -kInf}, {kInf, -kInf}}, {{kInf, -kInf}, {kInf, kInf}}, {{kInf, kInf}, {-kInf, kInf}}, {{-kInf, kInf}, {-kInf, -kInf}}};
pair<PDD, VEC> q[kMaxN];

PDD operator+(PDD x, PDD y) { return {x.first + y.first, x.second + y.second}; }
PDD operator-(PDD x, PDD y) { return {x.first - y.first, x.second - y.second}; }
double operator*(PDD x, PDD y) { return x.first * y.second - x.second * y.first; }
double operator*(VEC x, PDD y) { return (x.second - x.first) * (y - x.first); }
double operator*(VEC x, VEC y) { return (x.second - x.first) * (y.second - y.first); }
double operator-(VEC x) { return abs((x.second - x.first).second) > kEps ? (x.second - x.first).second : (x.second - x.first).first; }  // +:一二象限 -:三四象限
PDD operator+(VEC x, VEC y) {
  double s1 = (x.second - x.first) * (y.second - x.first), s2 = s1 + (y.first - x.first) * (x.second - x.first);
  return {y.second.first + (y.first - y.second).first * s1 / s2, y.second.second + (y.first - y.second).second * s1 / s2};
}

int main() {
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    for (int j = 1; j <= x; j++) {
      cin >> a[j].first >> a[j].second;
    }
    for (int j = 2; j <= x; j++) {
      v[m + j - 1] = {a[j - 1], a[j]};
    }
    m += x, v[m] = {a[x], a[1]};
  }
  sort(v + 1, v + m + 1, [](VEC x, VEC y) {
    if (-x * -y < kEps) {
      return -x > -y;
    } else if (abs(x * y) > kEps) {
      return x * y > kEps;
    }
    return (x.second - x.first) * (y.second - x.first) < -kEps;
  });
  h = t = 1, q[1] = {{-kInf, v[1].first.second}, v[1]};
  for (int i = 2; i <= m; i++) {
    if (abs(v[i] * v[i - 1]) > kEps) {
      for (; h < t && v[i] * q[t].first < -kEps; t--) {
      }
      t++, q[t] = {q[t - 1].second + v[i], v[i]};
      for (; h + 1 < t && q[t].second * q[h + 1].first < kEps; h++) {
      }
    }
  }
  for (; h + 1 < t && q[h].second * q[t].first < kEps; t--) {
  }
  if (h + 1 >= t) {
    cout << "0.000";
    return 0;
  }
  q[h].first = q[h].second + q[t].second;
  for (int i = h; i <= t; i++) {
    if (abs(abs(q[i].first.first) - kInf) < kEps || abs(abs(q[i].first.second) - kInf) < kEps) {
      cout << "Inf";
      return 0;
    }
  }
  for (int i = h; i < t; i++) {
    ans += q[i].first * q[i + 1].first;
  }
  cout << fixed << setprecision(3) << (ans + q[t].first * q[h].first) / 2;
  return 0;
}
