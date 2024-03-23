#include <cmath>
#include <fstream>
#include <iomanip>
#define Point pair<double, double>
#define Line pair<Point, Point>

using namespace std;

ifstream cin("antiak.in");
ofstream cout("antiak.out");

const int kMaxN = 20;
const double kEps = 1e-6, kInf = 1e18;
struct V {
  double x, y, r;
} v[kMaxN];
int n;
Point s, t;
double r, w, ans;

double Dis(Point x, Point y) {
  return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

Point T(Point o, Point x, Point y) {
  double k1 = (x.second - y.second) / (x.first - y.first), b1 = x.second - k1 * x.first;
  double k2 = -1.0 / k1, b2 = o.second - k2 * o.first;
  double p = (b1 - b2) / (k2 - k1), q = k1 * p + b1;
  return {p, q};
}

bool P(Point x, Point y) {
  // if (abs(x.first - y.first) < kEps && abs(s.first - t.first) < kEps) {
  //   if (max(x.second, y.second) < min(s.second, t.second) || max(s.second, t.second) < min(x.second, y.second)) {
  //     return min(min(Dis(x, s), Dis(x, t)), min(Dis(y, s), Dis(y, t))) < r + kEps;
  //   } else {
  //     return abs(x.first - s.first) < r + kEps;
  //   }
  // } else if (abs(x.second - y.second) < kEps && abs(s.second - t.second) < kEps) {
  //   if (max(x.first, y.first) < min(s.first, t.first) || max(s.first, t.first) < min(x.first, y.first)) {
  //     return min(min(Dis(x, s), Dis(x, t)), min(Dis(y, s), Dis(y, t))) < r + kEps;
  //   } else {
  //     return abs(x.second - s.second) < r + kEps;
  //   }
  // }
  double ans = kInf;
  Point z = T(x, s, t);
  if (z > min(s, t) && z < max(s, t)) {
    ans = min(ans, Dis(x, z));
  }
  z = T(y, s, t);
  if (z > min(s, t) && z < max(s, t)) {
    ans = min(ans, Dis(y, z));
  }
  z = T(s, x, y);
  if (z > min(x, y) && z < max(x, y)) {
    ans = min(ans, Dis(s, z));
  }
  z = T(t, x, y);
  if (z > min(x, y) && z < max(x, y)) {
    ans = min(ans, Dis(t, z));
  }
  return ans < r + kEps;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s.first >> s.second >> r >> t.first >> t.second >> w >> n;
  for (int i = 0; i < n; i++) {
    cin >> v[i].x >> v[i].y >> v[i].r;
  }
  // if (abs(w - 1e18) < kEps && n == 1 && (P({v[0].x, v[0].y}, {v[0].x + v[0].r, v[0].y}) || P({v[0].x, v[0].y}, {v[0].x, v[0].y + v[0].r}) || P({v[0].x + v[0].r, v[0].y + v[0].r}, {v[0].x + v[0].r, v[0].y}) || P({v[0].x + v[0].r, v[0].y + v[0].r}, {v[0].x, v[0].y + v[0].r}))) {
  //   ;
  // } else {
    ans = Dis(s, t);
  // }
  cout << fixed << setprecision(2) << ans;
  return 0;
}
