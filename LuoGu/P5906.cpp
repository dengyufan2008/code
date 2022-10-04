#include <algorithm>
#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 2e5, kInf = 1e9;
struct Q {
  LL l, r, d;
} q[kMaxN];
LL n, m, p, a[kMaxN], b[kMaxN], l[kMaxN], mn[kMaxN], _mn[kMaxN], mx[kMaxN], ans[kMaxN];

LL Read() {
  LL x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

int main() {
  n = Read();
  for (LL i = 0; i < n; i++) {
    b[i] = Read(), l[i] = i;
  }
  m = Read();
  for (LL i = 0; i < m; i++) {
    q[i].l = Read() - 1, q[i].r = Read() - 1, q[i].d = i;
  }
  p = sqrt(n);
  sort(q, q + m, [](Q i, Q j) { return i.l / p == j.l / p ? i.r < j.r : i.l < j.l; });
  sort(l, l + n, [](LL i, LL j) { return b[i] < b[j]; });
  for (LL i = 1; i < n; i++) {
    a[l[i]] = a[l[i - 1]] + (b[l[i]] != b[l[i - 1]]);
  }
  for (LL i = 0, j, k; i < m; i++) {
    if (!i || q[i].l / p != q[i - 1].l / p) {
      k = q[i].l / p * p + p;
      fill(mn, mn + kMaxN, kInf), fill(_mn, _mn + kMaxN, kInf), fill(mx, mx + kMaxN, -kInf);
    }
    for (; k <= q[i].r; k++) {
      mx[a[k]] = k;
      mn[a[k]] = min(mn[a[k]], k);
      ans[q[i].d] = max(ans[q[i].d], mx[a[k]] - mn[a[k]]);
    }
    i < m - 1 && q[i + 1].l / p == q[i].l / p && (ans[q[i + 1].d] = ans[q[i].d]);
    for (j = min(q[i].l / p * p + p - 1, q[i].r); j >= q[i].l; j--) {
      _mn[a[j]] = j;
      mx[a[j]] = max(mx[a[j]], j);
      ans[q[i].d] = max(ans[q[i].d], mx[a[j]] - _mn[a[j]]);
    }
  }
  for (LL i = 0; i < m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
