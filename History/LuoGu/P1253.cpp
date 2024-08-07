#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const LL kInf = -1LL << 61;
struct V {
  LL l, r, d, c = kInf, s;
} v[4000001];
LL n, q, a[1000001];

LL Read() {
  LL f = 1, x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch > '/' && ch < ':') {
    x = (x << 3) + (x << 1) + (ch - '0');
    ch = getchar();
  }
  return f * x;
}

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
  if (v[s].c != kInf) {
    v[s << 1].c = v[s << 1 | 1].c = v[s << 1].d = v[s << 1 | 1].d = v[s].c;
    v[s << 1].s = v[s << 1 | 1].s = 0;
    v[s].c = kInf;
  }
  v[s << 1].d += v[s].s, v[s << 1 | 1].d += v[s].s;
  v[s << 1].s += v[s].s, v[s << 1 | 1].s += v[s].s;
  v[s].s = 0;
}

void Change(LL s, LL l, LL r, LL x) {
  if (v[s].l >= l && v[s].r <= r) {
    v[s].d = v[s].c = x, v[s].s = 0;  // MARK
    return;
  }
  Spread(s);
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
    v[s].d += x, v[s].s += x;
    return;
  }
  Spread(s);
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
  LL mid = (v[s].l + v[s].r) >> 1, ans = kInf;
  if (mid >= l) {
    ans = max(ans, Ask(s << 1, l, r));
  }
  if (mid < r) {
    ans = max(ans, Ask(s << 1 | 1, l, r));
  }
  return ans;
}

int main() {
  n = Read(), q = Read();
  for (LL i = 1; i <= n; i++) {
    a[i] = Read();
  }
  Build(1, 1, n);
  for (LL i = 1, p, l, r, x; i <= q; i++) {
    p = Read();
    if (p == 1) {
      l = Read(), r = Read(), x = Read();
      Change(1, l, r, x);
    } else if (p == 2) {
      l = Read(), r = Read(), x = Read();
      Add(1, l, r, x);
    } else {
      l = Read(), r = Read();
      cout << Ask(1, l, r) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
