#include <fstream>
#include <map>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 1e5 + 2;
int t, n, k, q, p[kMaxN][2], f[kMaxN], v[kMaxN << 2];
LL m, a[kMaxN];
pair<int, int> d[kMaxN];
map<LL, int> s;

void Init(int p, int l, int r) {
  v[p] = n + 1;
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
}

void Change(int p, int l, int r, int x, int y) {
  if (l == r) {
    v[p] = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, y);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, y);
  }
  v[p] = min(v[p << 1], v[p << 1 | 1]);
}

int Min(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return v[p];
  }
  int mid = l + r >> 1, ans = n + 1;
  if (mid >= _l) {
    ans = min(ans, Min(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = min(ans, Min(p << 1 | 1, mid + 1, r, _l, _r));
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    k = 0, s.clear();
    cin >> n >> m >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], s[a[i]] = 0;
    }
    for (auto &i : s) {
      i.second = ++k;
    }
    for (int i = 1; i <= n; i++) {
      d[i].first = s.lower_bound(a[i] - m)->second;
      d[i].second = (--s.upper_bound(a[i] + m))->second;
      a[i] = s[a[i]];
    }
    Init(1, 1, k);
    for (int i = n; i >= 1; i--) {
      p[i][0] = Min(1, 1, k, d[i].first, a[i]);
      if (a[i] < d[i].second) {
        p[i][1] = Min(1, 1, k, a[i] + 1, d[i].second);
      } else {
        p[i][1] = n + 1;
      }
      Change(1, 1, k, a[i], i);
    }
    cin >> q;
    for (int i = 1, x, y, ans; i <= q; i++) {
      cin >> x >> y, ans = 0;
      for (int j = x; j <= y; j++) {
        f[j] = 1;
      }
      for (int j = x, jj; j <= y; j++) {
        ans = max(ans, f[j]);
        jj = p[j][0], f[jj] = max(f[jj], f[j] + 1);
        jj = p[j][1], f[jj] = max(f[jj], f[j] + 1);
      }
      cout << y - x + 1 - ans << '\n';
    }
  }
  return 0;
}
