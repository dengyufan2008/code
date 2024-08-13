#include <fstream>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

int t, a, b, c, s, ans;

bool Calc(int x) {
  int _c = 0;
  for (int _a = a, _b = b, w = 1; _a || _b;) {
    _c += (_a + _b) % x * w;
    _a /= x, _b /= x, w *= x;
  }
  return c == _c;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> a >> b >> c;
    s = a + b - c, ans = 0;
    if (s) {
      for (int i = 1, j; i * i <= s; i++) {
        if (!(s % i)) {
          j = s / i;
          ans += i > 1 && Calc(i);
          ans += j > 1 && i < j && Calc(j);
        }
      }
      cout << ans << '\n';
    } else {
      cout << -1 << '\n';
    }
  }
  return 0;
}
