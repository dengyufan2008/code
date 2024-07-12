#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("train.in");
ofstream cout("train.out");

const int kMaxN = 5e5 + 1;
struct Q {
  int l, r;
  bool b;
} e[kMaxN << 1];
struct V {
  LL s, t, ans;
} v[kMaxN << 2];
int n, m, t, k, a[kMaxN];
LL x, y, ans, s[kMaxN], f[kMaxN];
vector<int> q[kMaxN];

void Calc(int p, bool b) {
  if (v[p].t > 0) {
    v[p].ans = v[p].s;
  } else {
    v[p].ans = b ? v[p << 1].ans + v[p << 1 | 1].ans : 0;
  }
}

void Change(int p, int l, int r, int x, int k) {
  if (l == r) {
    v[p].s = k, Calc(p, 0);
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, k);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, k);
  }
  v[p].s = v[p << 1].s + v[p << 1 | 1].s, Calc(p, 1);
}

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    v[p].t += k, Calc(p, l != r);
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  v[p].s = v[p << 1].s + v[p << 1 | 1].s, Calc(p, 1);
}

LL Dp() {
  for (int i = 1; i <= m; i++) {
    e[i].b ? (void)0 : q[e[i].r].push_back(e[i].l - 1);
  }
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i], f[i] = f[i - 1];
    for (int j : q[i]) {
      f[i] = max(f[i], f[j] + s[i] - s[j]);
    }
  }
  return f[n];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    Change(1, 1, n, i, a[i]);
  }
  for (int i = 1; i <= m; i++) {
    cin >> e[i].l >> e[i].r;
    Add(1, 1, n, e[i].l, e[i].r, 1);
  }
  for (int i = 1, o; i <= t; i++) {
    cin >> o >> x;
    x ^= ans;
    if (o == 1) {
      cin >> y;
      Change(1, 1, n, x, a[x] = y ^ ans);
    } else if (o == 2) {
      e[x].b = 1;
      Add(1, 1, n, e[x].l, e[x].r, -1);
    } else {
      cin >> y;
      e[++m].l = x, e[m].r = y ^ ans;
      Add(1, 1, n, e[m].l, e[m].r, 1);
    }
    cout << (ans = i == 1 ? Dp() : v[1].ans) << '\n';
  }
  return 0;
}
