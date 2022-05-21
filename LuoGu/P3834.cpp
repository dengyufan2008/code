#include <algorithm>
#include <cmath>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int d[201], num[201];
} v[19];
int n, q, a[201];

void Build(int l, int r, int d) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1, num = mid - l + 1, _l = l, _r = mid + 1;
  for (int i = l; i <= r; i++) {
    num -= v[d].d[i] < a[mid];
  }
  for (int i = l; i <= r; i++) {
    if (v[d].d[i] < a[mid] || v[d].d[i] == a[mid] && num-- > 0) {
      v[d + 1].d[_l++] = v[d].d[i];
      v[d].num[i] = (i != l) * v[d].num[i - 1] + 1;
    } else {
      v[d + 1].d[_r++] = v[d].d[i];
      v[d].num[i] = (i != l) * v[d].num[i - 1];
    }
  }
  Build(l, mid, d + 1), Build(mid + 1, r, d + 1);
}

int Ask(int l, int r, int d, int _l, int _r, int k) {
  if (l == r) {
    return v[d].d[l];
  }
  int mid = l + r >> 1, num = v[d].num[_r] - (_l != l) * v[d].num[_l - 1];
  if (k <= num) {
    return Ask(l, mid, d + 1, _l, _l + num - 1, k);
  } else {
    return Ask(mid + 1, r, d + 1, _r - num, _r, k - num);
  }
}

int main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    v[1].d[i] = a[i];
  }
  sort(a + 1, a + n + 1);
  Build(1, n, 1);
  for (int i = 1, l, r, k; i <= q; i++) {
    cin >> l >> r >> k;
    cout << Ask(1, n, 1, l, r, k) << '\n';
  }
  return 0;
}
