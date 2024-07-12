#include <algorithm>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 2e5 + 1;
const double kInf = 1e10;
int n, a[kMaxN];
LL s, c;
double ans = kInf;
pair<double, double> d[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s += a[i];
  }
  c = s, d[n] = {(double)s / (double)n, (double)s / (double)n};
  for (int i = n - 1, l = 1, r = n; i >= 1; i--) {
    for (; r <= n && (c - a[l]) * n < s * i; c -= a[l++], c += a[++r]) {
    }
    for (; l >= 1 && (c - a[r]) * n > s * i; c += a[--l], c -= a[r--]) {
    }
    if (r <= n) {
      d[i].first = (double)(c - a[r]) / (double)i;
    } else {
      d[i].first = d[n].first;
    }
    if (l >= 1) {
      d[i].second = (double)(c - a[l]) / (double)i;
    } else {
      d[i].second = d[n].second;
    }
    if (l >= 1) {
      c -= a[l++];
    } else {
      c -= a[r--];
    }
  }
  sort(d + 1, d + n + 1);
  d[0].second = d[n + 1].first = (double)s / (double)n;
  for (int i = 1; i <= n; i++) {
    d[i].second = max(d[i].second, d[i - 1].second);
  }
  for (int i = 1; i <= n + 1; i++) {
    ans = min(ans, d[i - 1].second - d[i].first);
  }
  cout << fixed << setprecision(10) << ans;
  return 0;
}
