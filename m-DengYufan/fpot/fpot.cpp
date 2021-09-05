#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, m, p, l, r = 1e6, mid, ans = 1e7, d[2000001][21], _d[2000001][21];

inline bool C(register int x) {
  if (x >= p) {
    return 1;
  }
  for (register int i(1), j; (j = i + x) <= p; ++i) {
    int h(i), mx(0), mn(1e7);
    for (int k(20); k >= 0; --k) {
      if (h + (1 << k) - 1 <= j) {
        mx = max(mx, d[h][k]), mn = min(mn, _d[h][k]), h += 1 << k;
      }
    }
    if (mx - mn >= m) {
      return 1;
    }
  }
  return 0;
}

int main() {
  freopen("fpot.in", "r", stdin);
  freopen("fpot.out", "w", stdout);
  cin >> n >> m;
  for (register int i(0); i <= 2000000; ++i) {
    _d[i][0] = 0x7fffffff;
  }
  for (register int i(1), x, y; i <= n; ++i) {
    cin >> x >> y;
    p = max(p, y), d[x][0] = max(d[x][0], y), _d[x][0] = min(_d[x][0], y);
  }
  for (register int i(1); i <= 20; ++i) {
    for (register int j(1); j <= p; ++j) {
      d[j][i] = max(d[j][i - 1], d[j + (1 << (i - 1))][i - 1]);
      _d[j][i] = min(_d[j][i - 1], _d[j + (1 << (i - 1))][i - 1]);
    }
  }
  while (l <= r) {
    mid = (l + r) >> 1;
    if (C(mid)) {
      ans = min(ans, mid);
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << (ans == 1e7 ? -1 : ans) << '\n';
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << '\n';
  return 0;
}
