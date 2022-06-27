#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL l, r, d;
} v[6400001];
LL n, m, k, a[200001], b[200001], l[200001], h[200001];

void Copy(LL &p) {
  v[++k] = v[p];
  p = k;
}

void Insert(LL &p, LL l, LL r, LL x) {
  Copy(p), v[p].d++;
  if (l >= r) {
    return;
  }
  LL mid = l + r >> 1;
  if (x <= mid) {
    Insert(v[p].l, l, mid, x);
  } else {
    Insert(v[p].r, mid + 1, r, x);
  }
}

LL Ask(LL p, LL q, LL l, LL r, LL x) {
  if (l >= r) {
    return l;
  }
  LL mid = l + r >> 1;
  if (x <= v[v[q].l].d - v[v[p].l].d) {
    return Ask(v[p].l, v[q].l, l, mid, x);
  } else {
    return Ask(v[p].r, v[q].r, mid + 1, r, x - (v[v[q].l].d - v[v[p].l].d));
  }
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](LL i, LL j) { return a[i] < a[j]; });
  for (LL i = 1; i <= n; i++) {
    b[l[i]] = a[l[i]] == a[l[i - 1]] ? b[l[i - 1]] : i;
  }
  for (LL i = 1; i <= n; i++) {
    Insert(h[i] = h[i - 1], 1, n, b[i]);
  }
  for (LL i = 1, x, y, k; i <= m; i++) {
    cin >> x >> y >> k;
    cout << a[l[Ask(h[x - 1], h[y], 1, n, k)]] << '\n';
  }
  return 0;
}
