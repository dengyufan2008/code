#include <iostream>
#define LL long long

using namespace std;

const LL kMaxN = 1e5 + 1;
struct V {
  LL v, d, l, r;
} v[kMaxN << 5];
LL n, m, k, t, h[kMaxN];
char c;

void Copy(LL &p) {
  v[++k] = v[p], p = k;
}

void Add(LL &p, LL l, LL r, LL _l, LL _r, LL x, bool b) {
  if (b || !p) {
    Copy(p);
  }
  if (l >= _l && r <= _r) {
    v[p].v += x * (r - l + 1), v[p].d += x;
    return;
  }
  LL mid = l + r >> 1;
  if (mid >= _l) {
    Add(v[p].l, l, mid, _l, _r, x, b);
  }
  if (mid < _r) {
    Add(v[p].r, mid + 1, r, _l, _r, x, b);
  }
  v[p].v = v[v[p].l].v + v[v[p].r].v;
}

LL Ask(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    return k + v[p].v;
  }
  LL mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans += Ask(v[p].l, l, mid, _l, _r, k + v[p].d * (min(mid, _r) - max(l, _l) + 1));
  }
  if (mid < _r) {
    ans += Ask(v[p].r, mid + 1, r, _l, _r, k + v[p].d * (min(r, _r) - max(mid + 1, _l) + 1));
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (LL i = 1, x; i <= n; i++) {
    cin >> x;
    Add(h[0], 1, n, i, i, x, 0);
  }
  for (LL i = 1, l, r, x; i <= m; i++) {
    cin >> c;
    if (c == 'C') {
      cin >> l >> r >> x;
      t++, Add(h[t] = h[t - 1], 1, n, l, r, x, 1);
    } else if (c == 'Q') {
      cin >> l >> r;
      cout << Ask(h[t], 1, n, l, r, 0) << '\n';
    } else if (c == 'H') {
      cin >> l >> r >> x;
      cout << Ask(h[x], 1, n, l, r, 0) << '\n';
    } else {
      cin >> x;
      t = x;
    }
  }
  return 0;
}
