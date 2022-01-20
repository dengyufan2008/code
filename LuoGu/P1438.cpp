#include <iostream>
#define LL long long

using namespace std;

LL n, m, a[100001];
pair<LL, LL> d[400001];

void Pushdown(LL p, LL l, LL r) {
  LL mid = (l + r) / 2;
  if (d[p].second) {
    d[p * 2].second += d[p].second;
    d[p * 2 + 1].second += d[p].second;
    d[p * 2].first += (mid - l + 1) * d[p].second;
    d[p * 2 + 1].first += (r - mid) * d[p].second;
    d[p].second = 0;
  }
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].first += (r - l + 1) * k, d[p].second += k;
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
  d[p].first = d[p * 2].first + d[p * 2 + 1].first;
}

LL Find(LL p, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return d[p].first;
  }
  Pushdown(p, l, r);
  LL mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ans += Find(p * 2, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Find(p * 2 + 1, mid + 1, r, _l, _r);
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = n; i; i--) {
    a[i] = a[i] - a[i - 1];
  }
  for (LL i = 1; i <= n; i++) {
    Add(1, 1, n, i, i, a[i]);
  }
  for (LL i = 1, o, l, r, k, d; i <= m; i++) {
    cin >> o;
    if (o == 1) {
      cin >> l >> r >> k >> d;
      Add(1, 1, n, l, l, k);
      Add(1, 1, n, l + 1, r, d);
      Add(1, 1, n, r + 1, r + 1, -k - (r - l) * d);
    } else {
      cin >> d;
      cout << Find(1, 1, n, 1, d) << '\n';
    }
  }
  return 0;
}
