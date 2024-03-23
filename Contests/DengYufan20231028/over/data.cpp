#include <bits/stdc++.h>
using namespace std;
int n = 10, m = 10;
mt19937 rnd(chrono::steady_clock().now().time_since_epoch().count());
signed main() {
  freopen("data.in", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cout << n << ' ' << m << '\n';
  for (int i = 2; i <= n; i++) {
    cout << i << ' ' << rnd() % (i - 1) + 1 << '\n';
  }
  for (int i = 1; i <= n; i++) cout << rnd() % n + 1 << ' ';
  cout << '\n';
  while (m--) {
    int op = rnd() % 2 + 1, u = rnd() % n + 1, v = rnd() % n + 1, l = rnd() % n + 1, r = rnd() % n + 1, x = rnd() % n + 1, k = rnd() % 2;
    if (op == 1)
      cout << op << ' ' << u << ' ' << v << '\n';
    else
      cout << op << ' ' << u << ' ' << v << ' ' << l << ' ' << r << ' ' << k << '\n';
  }
  return 0;
}
