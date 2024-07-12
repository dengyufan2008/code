#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 2e5 + 1;
const LL kInf = 1e18;
struct V {
  int x, y, z;
} v[kMaxN];
int n, l[kMaxN];
pair<LL, LL> d[kMaxN << 2];

void Init(int p, int l, int r) {
  d[p].first = kInf;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
}

void Pushdown(int p) {
  if (d[p].second) {
    d[p << 1].first += d[p].second, d[p << 1].second += d[p].second;
    d[p << 1 | 1].first += d[p].second, d[p << 1 | 1].second += d[p].second;
    d[p].second = 0;
  }
}

void Add(int p, int l, int r, int _l, int _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].first += k, d[p].second += k;
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
  d[p].first = min(d[p << 1].first, d[p << 1 | 1].first);
}

void Change(int p, int l, int r, int x, LL k) {
  if (l == r) {
    d[p].first = min(d[p].first, k);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  mid >= x ? Change(p << 1, l, mid, x, k) : Change(p << 1 | 1, mid + 1, r, x, k);
  d[p].first = min(d[p << 1].first, d[p << 1 | 1].first);
}

LL Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return d[p].first;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  LL ans = kInf;
  if (mid >= _l) {
    ans = min(ans, Ask(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = min(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y;
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return v[i].y < v[j].y; });
  for (int i = 1; i <= n; i++) {
    v[l[i]].z = v[l[i - 1]].z + 1;
  }
  sort(v + 1, v + n + 1, [](V i, V j) { return i.x < j.x; });
  Init(1, 0, n), Change(1, 0, n, 0, 0);
  for (int i = 1; i <= n; i++) {
    LL t = Ask(1, 0, n, 0, v[i].z);
    Add(1, 0, n, 0, v[i].z, v[i].y);
    Change(1, 0, n, v[i].z, t + v[i].x);
    if (v[i].z < n) {
      Add(1, 0, n, v[i].z + 1, n, v[i].x);
    }
  }
  cout << Ask(1, 0, n, 0, n);
  return 0;
}
