#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, v;
} v[32000001];
int n, m, k, a[1000001], h[1000001];

int Read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') {
      f = -1;
    }
    c = getchar();
  }
  while (c > '/' && c < ':') {
    x = (x << 3) + (x << 1) + (c - '0');
    c = getchar();
  }
  return f * x;
}

void Copy(int &p) {
  v[++k] = v[p];
  p = k;
}

void Build(int &p, int l, int r) {
  p = ++k;
  if (l == r) {
    v[p].v = a[l];
    return;
  }
  int mid = l + r >> 1;
  Build(v[p].l, l, mid), Build(v[p].r, mid + 1, r);
}

void Change(int &p, int l, int r, int x, int y) {
  Copy(p);
  if (l == r) {
    v[p].v = y;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) {
    Change(v[p].l, l, mid, x, y);
  } else {
    Change(v[p].r, mid + 1, r, x, y);
  }
}

int Ask(int &p, int l, int r, int x) {
  if (l == r) {
    return v[p].v;
  }
  int mid = l + r >> 1;
  if (x <= mid) {
    return Ask(v[p].l, l, mid, x);
  } else {
    return Ask(v[p].r, mid + 1, r, x);
  }
}

int main() {
  n = Read(), m = Read();
  for (int i = 1; i <= n; i++) {
    a[i] = Read();
  }
  Build(h[0], 1, n);
  for (int i = 1, o, x, y, z; i <= m; i++) {
    x = Read(), o = Read(), y = Read();
    if (o == 1) {
      z = Read();
      Change(h[i] = h[x], 1, n, y, z);
    } else {
      cout << Ask(h[i] = h[x], 1, n, y) << '\n';
    }
  }
  return 0;
}
