#include <fstream>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 22;
int w, n, m, x, y, ans, d[1 << kMaxN];

bool C(int n, int s) {
  for (int i = 0; i + x < n; i++) {
    if (s >> i & s >> i + x & 1) {
      return 0;
    }
  }
  for (int i = 0; i + y < n; i++) {
    if (s >> i & s >> i + y & 1) {
      return 0;
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> w >> x >> y, n = x + y >> 1, m = x + y - n;
  if (w % (n + m) < n) {
    for (int s = 0; s < 1 << m; s++) {
      if (C(m, s)) {
        d[s] = __builtin_popcount(s);
      }
    }
    for (int i = 0; i < m; i++) {
      for (int s = 1 << i; s < 1 << m; s = s + 1 | 1 << i) {
        d[s] = max(d[s], d[s ^ 1 << i]);
      }
    }
    for (int s = 0; s < 1 << n; s++) {
      if (C(n, s)) {
        int t = 0;
        for (int i = 0; i < n; i++) {
          if (s >> i & 1) {
            if (i - x < 0 && i - x + m >= 0) {
              t |= 1 << i - x + m;
            }
            if (i - y < 0 && i - y + m >= 0) {
              t |= 1 << i - y + m;
            }
            if (i + x >= n && i + x - n < m) {
              t |= 1 << i + x - n;
            }
            if (i + y >= n && i + y - n < m) {
              t |= 1 << i + y - n;
            }
          }
        }
        t ^= (1 << m) - 1;
        ans = max(ans, w / (n + m) * (__builtin_popcount(s) + d[t]) +
                           __builtin_popcount(s & (1 << w % (n + m)) - 1));
      }
    }
  } else {
    for (int s = 0; s < 1 << n; s++) {
      if (C(n, s)) {
        d[s] = __builtin_popcount(s);
      }
    }
    for (int i = 0; i < n; i++) {
      for (int s = 1 << i; s < 1 << n; s = s + 1 | 1 << i) {
        d[s] = max(d[s], d[s ^ 1 << i]);
      }
    }
    for (int s = 0; s < 1 << m; s++) {
      if (C(m, s)) {
        int t = 0;
        for (int i = 0; i < m; i++) {
          if (s >> i & 1) {
            if (i - x < 0 && i - x + n >= 0) {
              t |= 1 << i - x + n;
            }
            if (i - y < 0 && i - y + n >= 0) {
              t |= 1 << i - y + n;
            }
            if (i + x >= m && i + x - m < n) {
              t |= 1 << i + x - m;
            }
            if (i + y >= m && i + y - m < n) {
              t |= 1 << i + y - m;
            }
          }
        }
        t ^= (1 << n) - 1;
        ans = max(ans, w / (n + m) * (d[t] + __builtin_popcount(s)) + d[t] +
                           __builtin_popcount(s & (1 << w % (n + m) - n) - 1));
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
