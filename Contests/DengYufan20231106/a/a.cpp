#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

LL t, n, m, x, y, l, r;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> x >> y;
    m = 1;
    for (int i = 2; i * i <= n; i++) {
      int c = 0;
      while (!(n % i)) {
        n /= i, c++;
      }
      if (c & 1) {
        m *= i;
      }
    }
    if (n > 1) {
      m *= n;
    }
    x = (x + m - 1) / m, y = y / m;
    l = 1, r = 1e6;
    while (l <= r) {
      LL mid = l + r >> 1;
      if (mid * mid < x) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << (l * l <= y ? l * l * m : -1) << '\n';
  }
  return 0;
}
