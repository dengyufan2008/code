#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, d;
} v[2100001];
int n, m, q, k, a[100001], b[100001], s[100001], f[100001];
char ch;

int GetRoot(int x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

void Insert(int &p, int l, int r, int x) {
  v[p ? p : p = ++k].d++;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) {
    Insert(v[p].l, l, mid, x);
  } else {
    Insert(v[p].r, mid + 1, r, x);
  }
}

void Merge(int &p, int q, int l, int r) {
  if (!p || !q) {
    p = p ? p : q;
    return;
  } else if (l == r) {
    v[p].d += v[q].d;
    return;
  }
  int mid = l + r >> 1;
  Merge(v[p].l, v[q].l, l, mid);
  Merge(v[p].r, v[q].r, mid + 1, r);
  v[p].d = v[v[p].l].d + v[v[p].r].d;
}

int Ask(int p, int l, int r, int x) {
  if (!p) {
    return -1;
  } else if (l == r) {
    return b[l];
  }
  int mid = l + r >> 1;
  if (x <= v[v[p].l].d) {
    return Ask(v[p].l, l, mid, x);
  } else {
    return Ask(v[p].r, mid + 1, r, x - v[v[p].l].d);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[a[i]] = i, f[i] = i, Insert(s[i] = ++k, 1, n, a[i]);
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    if (GetRoot(x) != GetRoot(y)) {
      Merge(s[GetRoot(x)], s[GetRoot(y)], 1, n);
      f[GetRoot(y)] = GetRoot(x);
    }
  }
  cin >> q;
  for (int i = 1, x, y; i <= q; i++) {
    cin >> ch >> x >> y;
    if (ch == 'Q') {
      cout << Ask(s[GetRoot(x)], 1, n, y) << '\n';
    } else if (GetRoot(x) != GetRoot(y)) {
      Merge(s[GetRoot(x)], s[GetRoot(y)], 1, n);
      f[GetRoot(y)] = GetRoot(x);
    }
  }
  return 0;
}
