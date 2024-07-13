#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct L {
  LL x, y1, y2, k;
  bool operator<(const L &l) const {
    return x < l.x;
  }
} l[200001];
LL n, ans, raw[200001];
pair<LL, LL> d[1600001];

void Update(LL p, LL l, LL r) {
  d[p].second = d[p].first > 0 ? raw[r] - raw[l] : d[p * 2].second + d[p * 2 + 1].second;
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (raw[l] >= _l && raw[r] <= _r) {
    d[p].first += k;
    Update(p, l, r);
    return;
  }
  LL mid = (l + r) / 2;
  if (raw[mid] > _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (raw[mid] < _r) {
    Add(p * 2 + 1, mid, r, _l, _r, k);
  }
  Update(p, l, r);
}

int main() {
  cin >> n;
  for (LL i = 1, x1, y1, x2, y2; i <= n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    l[i * 2 - 1] = {x1, y1, y2, 1}, l[i * 2] = {x2, y1, y2, -1};
    raw[i * 2 - 1] = y1, raw[i * 2] = y2;
  }
  sort(l + 1, l + n * 2 + 1);
  sort(raw + 1, raw + n * 2 + 1);
  unique(raw + 1, raw + n * 2 + 1);
  for (LL i = 2; i <= n * 2; i++) {
    Add(1, 1, n * 2, l[i - 1].y1, l[i - 1].y2, l[i - 1].k);
    ans += (l[i].x - l[i - 1].x) * d[1].second;
  }
  cout << ans;
  return 0;
}
