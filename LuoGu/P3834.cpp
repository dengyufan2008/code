#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, v, d;
} v[1600001];
int n, m, k, a[200001], b[200001], l[200001], h[200001];

void Copy(int &p) {
  v[++k] = v[p];
  p = k;
}

void Insert(int &p, int l, int r, int x) {
  Copy(p);
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) {
    Insert(v[p].l, l, mid, x);
  } else {
    Insert(v[p].l, mid + 1, r, x);
  }
  v[p].d = v[v[p].l].d + v[v[p].r].d;
}

int Ask(int p, int q, int l, int r, int x) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1;
  if (x <= v[v[q].l].d - v[v[p].l].d) {
    return Ask(v[p].l, v[q].l, l, mid, x);
  } else {
    return Ask(v[p].r, v[q].r, mid + 1, r, x - (v[v[q].l].d - v[v[p].l].d));
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return a[i] < a[j]; });
  for (int i = 1; i <= n; i++) {
    b[l[i]] = b[l[i - 1]] + (a[l[i]] != a[l[i - 1]]);
  }
  for (int i = 1; i <= n; i++) {
    Insert(h[i] = h[i - 1], 1, n, b[i]);
  }
  for (int i = 1, x, y, k; i <= m; i++) {
    cin >> x >> y >> k;
    cout << a[l[Ask(h[x - 1], h[y], 1, n, k)]] << '\n';
  }
  return 0;
}
