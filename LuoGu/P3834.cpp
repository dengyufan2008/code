#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int a[201], l[201];
} v[19];
int n, m;

void Build(int l, int r, int d) {
  if (l == r) {
    return;
  }
  int mid = l + r >> 1, num = mid - l + 1, _l = l, _r = mid + 1;
  for (int i = l; i <= r; i++) {
    num -= v[d].a[i] < v[0].a[mid];
  }
  for (int i = l; i <= r; i++) {
    if (v[d].a[i] < v[0].a[mid] || v[d].a[i] == v[0].a[mid] && num-- > 0) {
      v[d + 1].a[_l++] = v[d].a[i];
      v[d].l[i] = v[d].l[i - 1] + 1;
    } else {
      v[d + 1].a[_r++] = v[d].a[i];
      v[d].l[i] = v[d].l[i - 1];
    }
  }
  Build(l, mid, d + 1), Build(mid + 1, r, d + 1);
}

int Ask(int l, int r, int d, int _l, int _r, int k) {
  if (_l == _r) {
    return v[d].a[_l];
  }
  int mid = l + r >> 1, num = v[d].l[_r] - v[d].l[_l - 1];
  if (k <= num) {
    return Ask(l, mid, d + 1, l + v[d].l[_l] - v[d].l[l - 1], l + v[d].l[_r - 1] - v[d].l[l - 1], k);
  } else {
    return Ask(mid + 1, r, d + 1, mid + _l - v[d].l[_l - 1], mid + _r - v[d].l[_r - 1], k - num);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[0].a[i];
    v[1].a[i] = v[0].a[i];
  }
  sort(v[0].a + 1, v[0].a + n + 1);
  Build(1, n, 1);
  for (int i = 1, l, r, k; i <= m; i++) {
    cin >> l >> r >> k;
    cout << Ask(1, n, 1, l, r, k) << '\n';
  }
  return 0;
}
/*
5 1
3 1 2 4 5 
4 5 1
*/