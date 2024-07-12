#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 5e5 + 1;
struct V {
  int l, r;
} v[kMaxN], w[kMaxN];
int n, m, k, a[kMaxN], d[kMaxN];
LL ans;
pair<LL, LL> t[kMaxN << 2];

int FindR(int x) {
  int l = 1, r = k;
  while (l <= r) {
    int mid = l + r >> 1;
    if (w[mid].r >= x) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

int FindL(int x) {
  int l = 1, r = k;
  while (l <= r) {
    int mid = l + r >> 1;
    if (w[mid].l <= x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r;
}

void Pushdown(int p) {
  if (t[p].second) {
    t[p << 1].first += t[p].second, t[p << 1].second += t[p].second;
    t[p << 1 | 1].first += t[p].second, t[p << 1 | 1].second += t[p].second;
    t[p].second = 0;
  }
}

LL M(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    t[p].second++;
    return t[p].first++;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  LL ans = 0;
  if (mid >= _l) {
    ans = max(ans, M(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = max(ans, M(p << 1 | 1, mid + 1, r, _l, _r));
  }
  t[p].first = max(t[p << 1].first, t[p << 1 | 1].first);
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    d[i] = i;
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> v[i].l >> v[i].r;
  }
  sort(v + 1, v + m + 1, [](V i, V j) { return i.l < j.l || i.l == j.l && i.r < j.r; });
  for (int i = 1, j, p = 0; i <= m; i = j + 1) {
    for (j = i; j <= m && v[i].l == v[j].l; j++) {
    }
    if (v[--j].r > p) {
      w[++k] = v[j], p = v[j].r;
    }
  }
  sort(d + 1, d + n + 1, [](int i, int j) { return a[i] > a[j]; });
  for (int i = 1; i <= n; i++) {
    int l = FindR(d[i]), r = FindL(d[i]);
    if (l <= r) {
      ans = max(ans, (LL)a[d[i]] * M(1, 1, k, l, r));
    }
  }
  cout << ans;
  return 0;
}
