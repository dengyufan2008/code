#include <fstream>
#include <map>

using namespace std;

ifstream cin("sus.in");
ofstream cout("sus.out");

const int kMaxN = 2e5 + 1, kMaxL = 18;
struct V {
  int mx, t;
} v[kMaxN << 3];
int n, m, k, p[kMaxL][kMaxN];
pair<int, int> a[kMaxN];
map<int, int> s;

void Tag(int p, int x) {
  v[p].mx += x, v[p].t += x;
}

void Pushdown(int p) {
  if (v[p].t) {
    Tag(p << 1, v[p].t);
    Tag(p << 1 | 1, v[p].t);
    v[p].t = 0;
  }
}

void Add(int p, int l, int r, int _l, int _r, int x) {
  if (l >= _l && r <= _r) {
    return Tag(p, x);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
  v[p].mx = max(v[p << 1].mx, v[p << 1 | 1].mx);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    s[a[i].first] = s[a[i].second] = 0;
  }
  for (auto &i : s) {
    i.second = ++k;
  }
  for (int i = 1; i <= n; i++) {
    a[i].first = s[a[i].first];
    a[i].second = s[a[i].second];
  }
  for (int i = 1, j = 1; i <= n; i++) {
    Add(1, 1, k, a[i].first, a[i].second, 1);
    for (; v[1].mx > 1; j++) {
      Add(1, 1, k, a[j].first, a[j].second, -1);
    }
    p[0][i] = j - 1;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      p[i][j] = p[i - 1][p[i - 1][j]];
    }
  }
  cin >> m;
  for (int i = 1, l, r; i <= m; i++) {
    int ans = 1;
    cin >> l >> r;
    for (int j = kMaxL - 1; j >= 0; j--) {
      if (p[j][r] >= l) {
        r = p[j][r], ans += 1 << j;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
