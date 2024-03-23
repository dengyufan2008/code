#include <iostream>
#include <set>

using namespace std;

const int kMaxN = 2e5 + 2;
struct V {
  int mn, t, mx, lmx, rmx, ans;
} v[kMaxN << 2];
int n, m, a[kMaxN];
set<int> s[kMaxN];

void Pushdown(int p) {
  if (v[p].t) {
    v[p << 1].mn += v[p].t, v[p << 1].t += v[p].t;
    v[p << 1 | 1].mn += v[p].t, v[p << 1 | 1].t += v[p].t;
    v[p].t = 0;
  }
}

void Pushup(int p) {
  v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
  v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
  v[p].lmx = v[p << 1].lmx;
  v[p].rmx = v[p << 1 | 1].rmx;
  if (v[p << 1].mn < v[p << 1 | 1].mn) {
    v[p].rmx = max(v[p << 1].rmx, v[p << 1 | 1].mx);
    v[p].ans = v[p << 1].ans;
  } else if (v[p << 1].mn > v[p << 1 | 1].mn) {
    v[p].lmx = max(v[p << 1].mx, v[p << 1 | 1].lmx);
    v[p].ans = v[p << 1 | 1].ans;
  } else {
    v[p].ans = v[p << 1].ans + v[p << 1 | 1].ans;
    v[p].ans += max(v[p << 1].rmx, v[p << 1 | 1].lmx);
  }
}

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    v[p].mn += k, v[p].t += k;
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
  Pushup(p);
}

void Change(int p, int l, int r, int x, int k) {
  if (l == r) {
    v[p].mx = v[p].lmx = k;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, k);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, k);
  }
  Pushup(p);
}

void Add(int x, int k) {
  if (s[x].size() > 1) {
    Add(1, 0, n + 1, *s[x].begin(), *--s[x].end() - 1, k);
  }
}

void Change(int x, bool b) {
  if (!s[x].empty()) {
    Change(1, 0, n + 1, *s[x].begin(), b ? s[x].size() : 0);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s[a[i]].insert(i);
  }
  for (int i = 1; i < kMaxN; i++) {
    Add(i, 1), Change(i, 1);
  }
  cout << n - v[1].ans << '\n';
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    for (int o = 0; o < 2; o++) {
      Add(a[x], -1), Change(a[x], 0);
      o ? s[a[x]].insert(x), 0 : s[a[x]].erase(x);
      Add(a[x], 1), Change(a[x], 1);
      a[x] = y;
    }
    cout << n - v[1].ans << '\n';
  }
  return 0;
}
