#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL l, r, d;
} v[2000001];
LL n, m, a[500001];

void Build(LL s, LL l, LL r) {
  v[s].l = l, v[s].r = r;
  if (l == r) {
    v[s].d = a[l];
    return;
  }
  LL mid = (l + r) >> 1;
  Build(s << 1, l, mid), Build(s << 1 | 1, mid + 1, r);
  v[s].d = v[s << 1].d + v[s << 1 | 1].d;
}

void Change(LL s, LL x, LL y) {
  if (v[s].l == v[s].r) {
    v[s].d += y;
    return;
  }
  LL mid = (v[s].l + v[s].r) >> 1;
  Change(s << 1 | (x > mid), x, y);
  v[s].d = v[s << 1].d + v[s << 1 | 1].d;
}

LL Ask(LL s, LL l, LL r) {
  if (v[s].l >= l && v[s].r <= r) {
    return v[s].d;
  }
  LL mid = (v[s].l + v[s].r) >> 1, ans = 0;
  if (l <= mid) {
    ans += Ask(s << 1, l, r);
  }
  if (r > mid) {
    ans += Ask(s << 1 | 1, l, r);
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n);
  for (LL i = 1, p, x, y; i <= m; i++) {
    cin >> p >> x >> y;
    if (p == 1) {
      Change(1, x, y);
    } else {
      cout << Ask(1, x, y) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
