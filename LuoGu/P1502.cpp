#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct L {
  LL x, y1, y2, k;
  bool operator<(const L &l) const {
    return x < l.x;
  }
} l[20001];
LL t, n, w, h, ans, raw[20001];
pair<LL, LL> d[160001];

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (raw[l] >= _l && raw[r] <= _r) {
    d[p].first += k, d[p].second += k;
    return;
  }
  LL mid = (l + r) / 2;
  if (raw[mid] > _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (raw[mid] < _r) {
    Add(p * 2 + 1, mid, r, _l, _r, k);
  }
  d[p].first = max(d[p * 2].first, d[p * 2 + 1].first) + d[p].second;;
}

int main() {
  cin >> t;
  while (t--) {
    ans = 0, fill(&d[1], &d[160000] + 1, d[0]);
    cin >> n >> w >> h;
    for (LL i = 1, x, y, k; i <= n; i++) {
      cin >> x >> y >> k;
      l[i * 2 - 1] = {x, y, y + h, k};
      l[i * 2] = {x + w, y, y + h, -k};
      raw[i * 2 - 1] = y;
      raw[i * 2] = y + h;
    }
    sort(l + 1, l + n * 2 + 1);
    sort(raw + 1, raw + n * 2 + 1);
    unique(raw + 1, raw + n * 2 + 1);
    for (LL i = 1; i <= n * 2; i++) {
      Add(1, 1, n * 2, l[i].y1, l[i].y2, l[i].k);
      ans = max(ans, d[1].first);
    }
    cout << ans << '\n';
  }
  return 0;
}
