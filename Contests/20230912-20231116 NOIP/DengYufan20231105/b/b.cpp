#include <algorithm>
#include <iostream>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 4e5 + 1;
struct V {
  int x, y;
} v[kMaxN], _v[kMaxN], d[kMaxN << 2];
int n, m, _n;

int Find(int x, bool b) {
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    if ((b ? v[mid].x : v[mid].y + 1) <= x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l - b;
}

void Pushdown(int p) {
  if (d[p].y) {
    d[p << 1].x += d[p].y, d[p << 1].y += d[p].y;
    d[p << 1 | 1].x += d[p].y, d[p << 1 | 1].y += d[p].y;
    d[p].y = 0;
  }
}

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    d[p].x += k, d[p].y += k;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  d[p].x = max(d[p << 1].x, d[p << 1 | 1].x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y;
  }
  sort(v + 1, v + n + 1, [](V i, V j) { return i.x < j.x || i.x == j.x && i.y < j.y; });
  for (int i = 1, j = 0; i <= n; i++) {
    if (v[i].y > j) {
      _v[++_n] = v[i], j = v[i].y;
    }
  }
  n = _n, copy(&_v[1], &_v[_n] + 1, &v[1]);
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    int l = Find(x, 0), r = Find(x, 1);
    if (l <= r) {
      Add(1, 1, n, l, r, y);
    }
    cout << d[1].x << '\n';
  }
  return 0;
}
