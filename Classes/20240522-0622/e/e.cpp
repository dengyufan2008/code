#include <fstream>

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

int t, a, b, x, m;

int Calc(int x, int p, int l, int r) {  // kx \in [l, r] \pmod p
  if ((l + x - 1) / x <= r / x) {
    return (l + x - 1) / x;
  }
  int t = Calc(p % x, x, (x - r % x) % x, (x - l % x) % x);
  return (l + 1LL * t * p + x - 1) / x;
}

int Solve(int x, int a, int b) {  // +a, -b
  int t = Calc(a, b, m - a + 1 - x, b - 1 - x);
  return t + (x + 1LL * t * a) / b;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> a >> b >> x >> m;
    if (a + b - 1 <= m) {
      cout << m + 1 << '\n';
    } else {
      x %= a, cout << Solve(x, a, b) + Solve(x, b, a) + 1 << '\n';
    }
  }
  return 0;
}
