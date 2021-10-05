#include <algorithm>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, k, a[1000001], d[1000001];

int main() {
  freopen("ski.in", "r", stdin);
  freopen("ski.out", "w", stdout);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  fill(&d[0], &d[1000001], -1LL << 63);
  sort(a + 1, a + n + 1, [](LL i, LL j) { return i > j; });
  for (LL i = 1; i <= n; i++) {
    LL l = 1, r = k, mid, ans = -1;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (d[mid] > a[i]) {
        ans = max(ans, mid);
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    d[ans == -1 ? ++k : ans] = a[i];
  }
  cout << k - 1 << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
