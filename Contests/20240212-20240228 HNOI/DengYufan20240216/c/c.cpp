#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int kMaxN = 1e5;
struct Q {
  int o, l, r, x, y;
} q[kMaxN];
int n, m, k, a[kMaxN], b[kMaxN << 1 | 1];
bool d[kMaxN << 1 | 1];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i], b[i] = a[i];
  }
  k = n;
  for (int i = 0; i < m; i++) {
    cin >> q[i].o >> q[i].l >> q[i].r >> q[i].x;
    q[i].l--, q[i].r--;
    if (q[i].o == 1) {
      cin >> q[i].y, b[k++] = q[i].y;
    }
  }
  b[k++] = ~(1 << 31), sort(b, b + k), k = unique(b, b + k) - b;
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(b, b + k, a[i]) - b;
  }
  for (int i = 0; i < m; i++) {
    if (q[i].o == 1) {
      int x = lower_bound(b, b + k, q[i].x) - b;
      q[i].y = lower_bound(b, b + k, q[i].y) - b;
      x >= k || b[x] != q[i].x ? q[i].o = 0 : q[i].x = x;
    }
  }
  for (int i = 0; i < m; i++) {
    int l = q[i].l, r = q[i].r, x = q[i].x, y = q[i].y;
    if (q[i].o == 1) {
      for (int j = l; j <= r; j++) {
        if (a[j] == x) {
          a[j] = y;
        }
      }
    } else if (q[i].o == 2) {
      for (int j = l; j <= r; j++) {
        d[a[j]] = 1;
      }
      int p = upper_bound(b, b + k, x) - b - 1;
      for (int j = 0; j <= p; j++) {
        x += d[j];
      }
      for (p++; b[p] <= x; p++) {
        x += d[p];
      }
      cout << x << '\n', memset(d, 0, k);
    }
  }
  return 0;
}
