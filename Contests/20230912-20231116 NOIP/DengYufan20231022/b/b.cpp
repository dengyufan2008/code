#include <algorithm>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxM = 25;
int n, m, a[kMaxM], l[kMaxM], lg[1 << kMaxM];
LL ans = 1e18, d[1 << kMaxM];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int o = 0; o < n; o++) {
    for (int i = 0; i < m; i++) {
      cin >> a[i];
      l[i] = i;
    }
    sort(l, l + m, [](int i, int j) { return a[i] < a[j]; });
    for (int i = 0, j = 0; i < m; i++) {
      d[(~(-1 << m)) ^ j] += a[l[i]];
      j ^= 1 << l[i];
      d[(~(-1 << m)) ^ j] -= a[l[i]];
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = ~(-1 << m); j >= 0; j--) {
      if (!(j >> i & 1)) {
        d[j] += d[j ^ (1 << i)];
      }
    }
  }
  for (int i = 0; i < m; i++) {
    cin >> a[i];
    lg[1 << i] = i;
  }
  for (int i = 1; i < 1 << m; i++) {
    for (int j = i; j; j ^= j & -j) {
      d[i] += a[lg[j & -j]];
    }
    ans = min(ans, d[i]);
  }
  cout << ans;
  return 0;
}
