#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3e5 + 1;
struct E {
  int l, r, w;
} e[kMaxN];
struct V {
  LL f[2];
  int t[2];
  bool ans;
} v[kMaxN << 2];
int n, m;
LL ans, a[kMaxN];

void Tag(int p, int t, bool o) { v[p].f[o] += t, v[p].t[o] += t; }

void Pushdown(int p) {
  for (int o : {0, 1}) {
    if (v[p].t[o]) {
      Tag(p << 1, v[p].t[o], o);
      Tag(p << 1 | 1, v[p].t[o], o);
      v[p].t[o] = 0;
    }
  }
}

void Merge(V &x, V &y, V &z) {
  z.f[0] = min(x.f[0], y.f[0]);
  z.f[1] = max(x.f[1], y.f[1]);
  z.ans = x.ans || y.ans || x.f[0] < y.f[1];
}

void Init(int p, int l, int r) {
  if (l == r) {
    v[p].f[0] = v[p].f[1] = -a[l];
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
  Merge(v[p << 1], v[p << 1 | 1], v[p]);
}

void Add(int p, int l, int r, int x, int y, bool o) {
  if (l >= x) {
    return Tag(p, y, o);
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(p << 1, l, mid, x, y, o);
  }
  Add(p << 1 | 1, mid + 1, r, x, y, o);
  Merge(v[p << 1], v[p << 1 | 1], v[p]);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i] += a[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    cin >> e[i].l >> e[i].r >> e[i].w;
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return i.w > j.w;
  });
  Init(1, 0, n);
  for (int i = 1; i <= m; i++) {
    Add(1, 0, n, e[i].l, 1, 0);
    Add(1, 0, n, e[i].r, 1, 1);
    if (v[1].ans) {
      Add(1, 0, n, e[i].l, -1, 0);
      Add(1, 0, n, e[i].r, -1, 1);
    } else {
      ans += e[i].w;
    }
  }
  cout << ans << '\n';
  return 0;
}
