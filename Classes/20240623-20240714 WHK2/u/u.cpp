#include <fstream>

using namespace std;

ifstream cin("u.in");
ofstream cout("u.out");

int t, n, x, y, a, b, h;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> y >> n >> x >> h, y %= x;
    if (y == 0) {
      cout << "YES\n";
      continue;
    } else if (y * 2 < x && n < x / y) {
      cout << (h >= y ? "YES\n" : "NO\n");
      continue;
    }
    a = 1, b = 0;
    for (;;) {
      int w = x / y;
      if (n >= w * a) {
        x -= w * y, b += w * a, n -= w * a;
        swap(x, y), swap(a, b);
      } else {
        w = n / a, x -= w * y, b += w * a;
        cout << (h >= x ? "YES\n" : "NO\n");
        break;
      }
    }
  }
  return 0;
}
