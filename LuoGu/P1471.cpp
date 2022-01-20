#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int k, c, s;  // k:lazytag c:sigma(1,n,a[i]) s:square distance
} v[400001];
int n, m;

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    v[p].k += k, v[p].c += (r - l + 1) * k;
    return;
  }
  Pushdown(p, l, r);
  int mid = (l + r) / 2;
  if (mid >= _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  v[p].c = v[p * 2].c + v[p * 2 + 1].c, v[p].s = Calc(p, l, r);
}

int Find1(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p].c;
  }
  Pushdown(p, l, r);
  int mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ans += Find1(p * 2, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Find1(p * 2 + 1, mid + 1, r, _l, _r);
  }
  return ans;
}

int Find2(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p].s;
  }
  Pushdown(p, l, r);
  int mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ;
  }
  if (mid < _r) {
    ;
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    Add(1, 1, n, i, i, x);
  }
  for (int i = 1, o, x, y, k; i <= m; i++) {
    cin >> o >> x >> y;
    if (o == 1) {
      cin >> k;
      Add(1, 1, n, x, y, k);
    } else if (o == 2) {
      cout << fixed << setprecision(4) << Find1(1, 1, n, x, y) / (y - x + 1) << '\n';
    } else {
      cout << fixed << setprecision(4) << Find2(1, 1, n, x, y) << '\n';
    }
  }
  return 0;
}
