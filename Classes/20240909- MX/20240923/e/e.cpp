#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#define PDD pair<double, double>

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 5e5 + 1, kL = 30;
const double kPi = acos(-1), kTheta = 2.0 * kPi / kL;
const double kSinT = sin(kTheta), kCosT = cos(kTheta);
int n, l[kMaxN];
double k, ans;
PDD a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second, l[i] = i;
  }
  a[0] = {1, 0};
  for (int o = 0; o < kL; o++) {
    sort(l + 1, l + n + 1, [](int i, int j) {
      return a[i] < a[j];
    });
    k += abs(a[0].first);
    for (int i = 1; i < n; i++) {
      ans += (a[l[i + 1]].first - a[l[i]].first) * i * (n - i);
    }
    for (int i = 0; i <= n; i++) {
      PDD x = a[i];
      a[i].first = x.first * kCosT - x.second * kSinT;
      a[i].second = x.first * kSinT + x.second * kCosT;
    }
  }
  cout << fixed << setprecision(10) << ans / k << '\n';
  return 0;
}
