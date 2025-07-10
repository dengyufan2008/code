#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 8e4 + 1, kMaxL = 17;
struct E {
  int x, y, l, r;
} e[kMaxN];
struct Q {
  int x, y, l, r;
} q[kMaxN];
int n, m, k;

namespace Sub1 {
const int kMaxN = 3001;
class Uni {
  int f[kMaxN];

  int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

 public:
  Uni() {
    for (int i = 1; i < kMaxN; i++) {
      f[i] = i;
    }
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    if (x != y) {
      f[x] = y;
    }
  }

  int Same(int x, int y) {
    return GetRoot(x) == GetRoot(y);
  }
};

Uni uni[kMaxN];

int main() {
  for (int i = 1; i <= m; i++) {
    for (int j = e[i].l; j <= e[i].r; j++) {
      uni[j].Merge(e[i].x, e[i].y);
    }
  }
  for (int i = 1; i <= k; i++) {
    int ans = 0;
    for (int j = q[i].l; j <= q[i].r; j++) {
      ans += uni[j].Same(q[i].x, q[i].y);
    }
    cout << ans << '\n';
  }
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
int mx[kMaxL][kMaxN], mn[kMaxL][kMaxN];

int main() {
  for (int i = 1; i <= m; i++) {
    mx[0][i] = e[i].l, mn[0][i] = e[i].r;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= m; j++) {
      mx[i][j] = mx[i - 1][j];
      mn[i][j] = mn[i - 1][j];
      if (j + (1 << i - 1) <= m) {
        mx[i][j] = max(mx[i][j], mx[i - 1][j + (1 << i - 1)]);
        mn[i][j] = min(mn[i][j], mn[i - 1][j + (1 << i - 1)]);
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    if (q[i].x > q[i].y) {
      swap(q[i].x, q[i].y);
    }
    int o = __lg(q[i].y - q[i].x);
    int l = max(q[i].l, max(mx[o][q[i].x], mx[o][q[i].y - (1 << o)]));
    int r = min(q[i].r, min(mn[o][q[i].x], mn[o][q[i].y - (1 << o)]));
    cout << max(r - l + 1, 0) << '\n';
  }
  return 0;
}
}  // namespace Sub2

namespace Sub3 {
struct V {
  int d, f[kMaxL], mx[kMaxL];
  vector<pair<int, int>> e;
} v[kMaxN];
int f[kMaxN];

int GetRoot(int x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

void Init(int f, int x) {
  v[x].d = v[f].d + 1;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
    v[x].mx[i] = max(v[x].mx[i - 1], v[v[x].f[i - 1]].mx[i - 1]);
  }
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].f[0] = x;
      v[i.first].mx[0] = i.second;
      Init(x, i.first);
    }
  }
}

int Ask(int x, int y) {
  int ans = 1;
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      ans = max(ans, v[x].mx[i]);
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      ans = max(ans, max(v[x].mx[i], v[y].mx[i]));
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? ans : max(ans, max(v[x].mx[0], v[y].mx[0]));
}

int main() {
  for (int i = 1; i <= n; i++) {
    f[i] = i;
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return i.l < j.l;
  });
  for (int i = 1; i <= m; i++) {
    int x = GetRoot(e[i].x), y = GetRoot(e[i].y);
    if (x != y) {
      f[x] = y;
      v[e[i].x].e.push_back({e[i].y, e[i].l});
      v[e[i].y].e.push_back({e[i].x, e[i].l});
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].d) {
      Init(0, i);
    }
  }
  for (int i = 1; i <= m; i++) {
    if (GetRoot(q[i].x) != GetRoot(q[i].y)) {
      cout << 0 << '\n';
    } else {
      int l = max(Ask(q[i].x, q[i].y), q[i].l);
      cout << max(q[i].r - l + 1, 0) << '\n';
    }
  }
  return 0;
}
}  // namespace Sub3

namespace Sub4 {
int o[kMaxN], ans[kMaxN];
vector<pair<int, int>> v[kMaxN << 2];

class Uni {
  int f[kMaxN], s[kMaxN];
  vector<pair<int, int>> l;

  int GetRoot(int x) { return f[x] == x ? x : GetRoot(f[x]); }

 public:
  Uni() {
    for (int i = 1; i < kMaxN; i++) {
      f[i] = i, s[i] = 1;
    }
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    if (x == y) {
      l.push_back({0, 0});
    } else {
      s[x] > s[y] ? swap(x, y) : void();
      f[x] = y, s[y] += s[x], l.push_back({x, y});
    }
  }

  void Undo() {
    if (l.back().first) {
      f[l.back().first] = l.back().first;
      s[l.back().second] -= s[l.back().first];
    }
    l.pop_back();
  }

  bool Ask(int x, int y) {
    return GetRoot(x) == GetRoot(y);
  }
} uni;

void Add(int p, int l, int r, int _l, int _r, pair<int, int> x) {
  if (l >= _l && r <= _r) {
    v[p].push_back(x);
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, x);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, x);
  }
}

void Calc(int p, int l, int r) {
  for (auto i : v[p]) {
    uni.Merge(i.first, i.second);
  }
  if (l == r) {
    ans[o[l]] = uni.Ask(q[o[l]].x, q[o[l]].y);
  } else {
    int mid = l + r >> 1;
    Calc(p << 1, l, mid), Calc(p << 1 | 1, mid + 1, r);
  }
  for (auto i : v[p]) {
    uni.Undo();
  }
}

int main() {
  static int w[kMaxN];
  for (int i = 1; i <= k; i++) {
    o[i] = i;
  }
  sort(o + 1, o + k + 1, [](int i, int j) {
    return q[i].l < q[j].l;
  });
  for (int i = 1; i <= k; i++) {
    w[i] = q[o[i]].l;
  }
  for (int i = 1; i <= m; i++) {
    e[i].l = lower_bound(w + 1, w + k + 1, e[i].l) - w;
    e[i].r = upper_bound(w + 1, w + k + 1, e[i].r) - w - 1;
    if (e[i].l <= e[i].r) {
      Add(1, 1, k, e[i].l, e[i].r, {e[i].x, e[i].y});
    }
  }
  Calc(1, 1, k);
  for (int i = 1; i <= k; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
}  // namespace Sub4

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  bool sub1 = 1, sub2 = 1, sub3 = 1, sub4 = 1;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y >> e[i].l >> e[i].r;
    sub1 &= e[i].r <= 3000;
    sub2 &= e[i].x == i && e[i].y == i + 1;
    sub3 &= e[i].r == 1000000000;
  }
  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> q[i].x >> q[i].y >> q[i].l >> q[i].r;
    sub1 &= q[i].r <= 3000;
    sub4 &= q[i].l == q[i].r;
  }
  sub1 &= n <= 3000 && m <= 3000 && k <= 3000;
  sub2 &= n - 1 == m;
  if (sub1) {
    return Sub1::main();
  } else if (sub2) {
    return Sub2::main();
  } else if (sub3) {
    return Sub3::main();
  } else if (sub4) {
    return Sub4::main();
  }
  return 0;
}
