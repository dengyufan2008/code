#include <iostream>
#define LL long long

using namespace std;

LL n, m;
pair<LL, LL> a[400001];

void Pushdown(LL p, LL l, LL r) {
  LL mid = (l + r) / 2;
  a[p * 2].first += (mid - l + 1) * a[p].second;
  a[p * 2 + 1].first += (r - mid) * a[p].second;
  a[p * 2].second += a[p].second;
  a[p * 2 + 1].second += a[p].second;
  a[p].second = 0;
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    a[p].first += (r - l + 1) * k, a[p].second += k;
    return;
  }
  Pushdown(p, l, r);
  LL mid = (l + r) / 2;
  if (mid >= _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  a[p].first = a[p * 2].first + a[p * 2 + 1].first;
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return a[p].first;
  }
  Pushdown(p, l, r);
  LL mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ans += Ask(p * 2, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Ask(p * 2 + 1, mid + 1, r, _l, _r);
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (LL i = 1, x; i <= n; i++) {
    cin >> x;
    Add(1, 1, n, i, i, x);
  }
  for (LL i = 1, c, x, y, k; i <= m; i++) {
    cin >> c;
    if (c == 1) {
      cin >> x >> y >> k;
      Add(1, 1, n, x, y, k);
    } else {
      cin >> x >> y;
      cout << Ask(1, 1, n, x, y) << '\n';
    }
  }
  return 0;
}
