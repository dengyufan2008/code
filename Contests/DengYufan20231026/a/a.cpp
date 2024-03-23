#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e6 + 1;
int n, m, a[kMaxN], d[kMaxN << 2];

void Build(int p, int l, int r) {
  if (l == r) {
    d[p] = a[l];
    return;
  }
  int mid = l + r >> 1;
  Build(p << 1, l, mid), Build(p << 1 | 1, mid + 1, r);
  d[p] = max(d[p << 1], d[p << 1 | 1]);
}

int Ask(int p, int l, int r) {
  if (l == r) {
    return l;
  }
  int mid = l + r >> 1;
  if (d[p << 1] >= d[p << 1 | 1]) {
    return Ask(p << 1, l, mid);
  } else {
    return Ask(p << 1 | 1, mid + 1, r);
  }
}

void Change(int p, int l, int r, int x, int k, bool b) {
  if (l == r) {
    d[p] = b ? k : max(d[p], k);
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, k, b);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, k, b);
  }
  d[p] = max(d[p << 1], d[p << 1 | 1]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Build(1, 1, n);
  for (int i = 1, x; i <= n; i++) {
    x = Ask(1, 1, n);
    if (x > 1 && a[x - 1] > 0) {
      Change(1, 1, n, x - 1, a[x] - m, 0);
      a[x - 1] = max(a[x - 1], a[x] - m);
    }
    if (x < n && a[x + 1] > 0) {
      Change(1, 1, n, x + 1, a[x] - m, 0);
      a[x + 1] = max(a[x + 1], a[x] - m);
    }
    Change(1, 1, n, x, 0, 1), a[x] = -a[x];
  }
  for (int i = 1; i <= n; i++) {
    cout << -a[i] << ' ';
  }
  return 0;
}
