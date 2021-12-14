#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL l, r, d, a, t = 1;  // Data, AddMark, TimeMark
} v[400001];
LL n, m, p, a[100001];

void Build(LL s, LL l, LL r) {
  v[s].l = l, v[s].r = r;
  if (l == r) {
    v[s].d = a[l] % p;
    return;
  }
  LL mid = (l + r) >> 1;
  Build(s << 1, l, mid), Build(s << 1 | 1, mid + 1, r);
  v[s].d = (v[s << 1].d + v[s << 1 | 1].d) % p;
}

void SpreadTime(LL s) {
  if (v[s].t > 1) {
    v[s << 1].d = v[s << 1].d * v[s].t % p;
    v[s << 1 | 1].d = v[s << 1 | 1].d * v[s].t % p;
    v[s << 1].a = v[s << 1].a * v[s].t % p, v[s << 1].t = v[s << 1].t * v[s].t % p;
    v[s << 1 | 1].a = (v[s << 1 | 1].a * v[s].t) % p, v[s << 1 | 1].t = (v[s << 1 | 1].t * v[s].t) % p;
    v[s].t = 1;
  }
}

void SpreadAdd(LL s) {
  if (v[s].a > 0) {
    v[s << 1].a = (v[s << 1].a + v[s].a) % p;
    v[s << 1 | 1].a = (v[s << 1 | 1].a + v[s].a) % p;
    v[s << 1].d = (v[s << 1].d + (v[s << 1].r - v[s << 1].l + 1) * v[s].a) % p;
    v[s << 1 | 1].d = (v[s << 1 | 1].d + (v[s << 1 | 1].r - v[s << 1 | 1].l + 1) * v[s].a) % p;
    v[s].a = 0;
  }
}

void Time(LL s, LL l, LL r, LL x) {
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d = (v[s].d * x) % p, v[s].a = (v[s].a * x) % p, v[s].t = (v[s].t * x) % p;
    return;
  }
  SpreadTime(s);
  LL mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Time(s << 1, l, r, x);
  }
  if (mid < r) {
    Time(s << 1 | 1, l, r, x);
  }
  v[s].d = (v[s << 1].d + v[s << 1 | 1].d) % p;
}

void Add(LL s, LL l, LL r, LL x) {
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d = (v[s].d + (v[s].r - v[s].l + 1) * x) % p, v[s].a = (v[s].a + x) % p;
    return;
  }
  SpreadAdd(s);
  LL mid = (v[s].l + v[s].r) >> 1;
  if (mid >= l) {
    Add(s << 1, l, r, x);
  }
  if (mid < r) {
    Add(s << 1 | 1, l, r, x);
  }
  v[s].d = (v[s << 1].d + v[s << 1 | 1].d) % p;
}

LL Ask(LL s, LL l, LL r) {
  if (v[s].l >= l && v[s].r <= r) {
    return v[s].d;
  }
  SpreadTime(s), SpreadAdd(s);
  LL mid = (v[s].l + v[s].r) >> 1, ans = 0;
  if (mid >= l) {
    ans = (ans + Ask(s << 1, l, r)) % p;
  }
  if (mid < r) {
    ans = (ans + Ask(s << 1 | 1, l, r)) % p;
  }
  return ans;
}

int main() {
  cin >> n >> m >> p;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n);
  for (LL i = 1, c, x, y, k; i <= m; i++) {
    cin >> c;
    if (c == 1) {
      cin >> x >> y >> k;
      Time(1, x, y, k);
    } else if (c == 2) {
      cin >> x >> y >> k;
      Add(1, x, y, k);
    } else {
      cin >> x >> y;
      cout << Ask(1, x, y) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
