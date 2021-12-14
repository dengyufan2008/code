#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL l, r, d, c = 1 << 31, s;
} v[4000001];
LL n, q, a[1000001];

void Build(LL s, LL l, LL r) {
  v[s].l = l, v[s].r = r;
  if (l == r) {
    v[s].d = a[l];
    return;
  }
  LL mid = (l + r) >> 1;
  Build(s << 1, l, mid), Build(s << 1 | 1, mid + 1, r);
  v[s].d = max(v[s << 1].d, v[s << 1 | 1].d);
}

void Spread(LL s) {
  if (v[s].c > 1 << 31) {
    v[s << 1].d = v[s << 1 | 1].d = v[s].c;
    v[s << 1].s = v[s << 1 | 1].s = 0;
  }
  v[s << 1].d += (v[s << 1].r - v[s << 1].l + 1) * v[s].s;
  v[s << 1 | 1].d += (v[s << 1 | 1].r - v[s << 1 | 1].l + 1) * v[s].s;
  v[s << 1].s += v[s].s, v[s << 1 | 1].s += v[s].s;
  v[s].c = 1 << 31, v[s].s = 0;
}

void Change(LL s, LL l, LL r, LL x) {
  v[s].s = 0;  // MARK
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d = v[s].c = x;
    return;
  }
  LL mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Change(s << 1, l, r, x);
  }
  if (mid < r) {
    Change(s << 1 | 1, l, r, x);
  }
  v[s].d = max(v[s << 1].d, v[s << 1 | 1].d);
}

void Add(LL s, LL l, LL r, LL x) {
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d += (v[s].r - v[s].l + 1) * x, v[s].s += x;
    return;
  }
  LL mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Add(s << 1, l, r, x);
  }
  if (mid < r) {
    Add(s << 1 | 1, l, r, x);
  }
  v[s].d = max(v[s << 1].d, v[s << 1 | 1].d);
}

LL Ask(LL s, LL l, LL r) {
  if (v[s].l >= l && v[s].r <= r) {
    return v[s].d;
  }
  Spread(s);
  LL mid = (v[s].l + v[s].r) >> 1, ans = 1 << 31;
  if (mid >= l) {
    ans = max(ans, Ask(s << 1, l, r));
  }
  if (mid < r) {
    ans = max(ans, Ask(s << 1 | 1, l, r));
  }
  return ans;
}

int main() {
  cin >> n >> q;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n);
  for (LL i = 1, p, l, r, x; i <= q; i++) {
    cin >> p;
    if (p == 1) {
      cin >> l >> r >> x;
      Change(1, l, r, x);
    } else if (p == 2) {
      cin >> l >> r >> x;
      Add(1, l, r, x);
    } else {
      cin >> l >> r;
      cout << Ask(1, l, r) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
