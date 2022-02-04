#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL d, a, t = 1;
} v[400001];
LL n, m, p;

void Pushdown(LL s, LL l, LL r) {
  LL mid = (l + r) / 2;
  v[s << 1].d = (v[s].t * v[s << 1].d + (mid - l + 1) * v[s].a % p) % p;
  v[s << 1 | 1].d = (v[s].t * v[s << 1 | 1].d + (r - mid) * v[s].a % p) % p;
  v[s << 1].t = v[s << 1].t * v[s].t % p;
  v[s << 1 | 1].t = v[s << 1 | 1].t * v[s].t % p;
  v[s << 1].a = (v[s << 1].a * v[s].t + v[s].a) % p;
  v[s << 1 | 1].a = (v[s << 1 | 1].a * v[s].t + v[s].a) % p;
  v[s].t = 1, v[s].a = 0;
}

void Time(LL s, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    v[s].d = v[s].d * k % p, v[s].t = v[s].t * k % p, v[s].a = v[s].a * k % p;
    return;
  }
  Pushdown(s, l, r);
  LL mid = (l + r) / 2;
  if (mid >= _l) {
    Time(s * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Time(s * 2 + 1, mid + 1, r, _l, _r, k);
  }
  v[s].d = (v[s * 2].d + v[s * 2 + 1].d) % p;
}

void Add(LL s, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    v[s].d = (v[s].d + (r - l + 1) * k) % p, v[s].a = (v[s].a + k) % p;
    return;
  }
  Pushdown(s, l, r);
  LL mid = (l + r) / 2;
  if (mid >= _l) {
    Add(s * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(s * 2 + 1, mid + 1, r, _l, _r, k);
  }
  v[s].d = (v[s * 2].d + v[s * 2 + 1].d) % p;
}

LL Ask(LL s, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return v[s].d;
  }
  Pushdown(s, l, r);
  LL mid = (l + r) / 2, ans = 0;
  if (mid >= _l) {
    ans = (ans + Ask(s * 2, l, mid, _l, _r)) % p;
  }
  if (mid < _r) {
    ans = (ans + Ask(s * 2 + 1, mid + 1, r, _l, _r)) % p;
  }
  return ans;
}

int main() {
  cin >> n >> m >> p;
  for (LL i = 1, x; i <= n; i++) {
    cin >> x;
    Add(1, 1, n, i, i, x % p);
  }
  for (LL i = 1, c, x, y, k; i <= m; i++) {
    cin >> c;
    if (c == 1) {
      cin >> x >> y >> k;
      Time(1, 1, n, x, y, k % p);
    } else if (c == 2) {
      cin >> x >> y >> k;
      Add(1, 1, n, x, y, k % p);
    } else {
      cin >> x >> y;
      cout << Ask(1, 1, n, x, y) << '\n';
    }
  }
  return 0;
}
