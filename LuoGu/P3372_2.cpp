#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 1e5 + 1;
LL n, m;
pair<LL, LL> d[kMaxN << 2];

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  d[p].first += k * (min(r, _r) - max(l, _l) + 1);  // 这一句与普通线段树不同
  if (l >= _l && r <= _r) {
    d[p].second += k;  // 这一句与普通线段树不同
    return;
  }
  LL mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  // 这一句与普通线段树不同
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    return d[p].first + k * (r - l + 1);  // 这一句与普通线段树不同
  }
  LL mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans += Ask(p << 1, l, mid, _l, _r, k + d[p].second);  // 这一句与普通线段树不同
  }
  if (mid < _r) {
    ans += Ask(p << 1 | 1, mid + 1, r, _l, _r, k + d[p].second);  // 这一句与普通线段树不同
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (LL i = 1, x; i <= n; i++) {
    cin >> x;
    Add(1, 1, n, i, i, x);
  }
  for (LL i = 1, o, l, r, x; i <= m; i++) {
    cin >> o >> l >> r;
    if (o == 1) {
      cin >> x;
      Add(1, 1, n, l, r, x);
    } else {
      cout << Ask(1, 1, n, l, r, 0) << '\n';
    }
  }
  return 0;
}
