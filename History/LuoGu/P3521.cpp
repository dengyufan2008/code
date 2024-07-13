#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL l, r, d;
} v[4400001];
LL n, m, x, a, b, ans;

void Insert(LL p, LL l, LL r, LL x) {
  v[p].d++;
  if (l == r) {
    return;
  }
  LL mid = l + r >> 1;
  if (x <= mid) {
    Insert(v[p].l = ++m, l, mid, x);
  } else {
    Insert(v[p].r = ++m, mid + 1, r, x);
  }
}

void Merge(LL &p, LL q, LL l, LL r) {
  if (!p || !q) {
    p = p ? p : q;
    return;
  } else if (l == r) {
    v[p].d += v[q].d;
    return;
  }
  LL mid = l + r >> 1;
  a += v[v[p].l].d * v[v[q].r].d;
  b += v[v[p].r].d * v[v[q].l].d;
  Merge(v[p].l, v[q].l, l, mid);
  Merge(v[p].r, v[q].r, mid + 1, r);
  v[p].d = v[v[p].l].d + v[v[p].r].d;
}

LL S() {
  cin >> x;
  if (x) {
    LL y = m + 1;
    Insert(++m, 1, n, x);
    return y;
  } else {
    LL l = S(), r = S();
    a = b = 0;
    Merge(l, r, 1, n);
    ans += min(a, b);
    return l;
  }
}

int main() {
  cin >> n;
  S();
  cout << ans;
  return 0;
}
