#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, l, r, mid, ans;
double x, y;

bool C(int d) {
  double c = (x + d) / (double)(n + d);
  int _c = c * 10.0 + 0.5;
  return _c <= y * 10.0;
}

int main() {
  // freopen("film.in", "r", stdin);
  // freopen("film.out", "w", stdout);
  while (cin >> x >> y >> n) {
    l = 0, r = 1e9, ans = 1e9;
    x = (x + 0.049999999999) * n;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (C(mid)) {
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
