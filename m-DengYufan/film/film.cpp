#include <cmath>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, l, r, mid, ans;
double x, y;

int main() {
  freopen("film.in", "r", stdin);
  freopen("film.out", "w", stdout);
  while (cin >> x >> y >> n) {
    l = 0, r = 1e9, ans = 1e9;
    x = min(x + 0.049999999999, 10.0) * (double)n, y += 0.0000001;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (round((x + mid) / (double)(n + mid) * 10.0) / 10.0 <= y) {
        r = mid - 1;
        ans = min(ans, mid);
      } else {
        l = mid + 1;
      }
    }
    cout << ans << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
