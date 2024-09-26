#include <algorithm>
#include <fstream>
#include <map>
#define LL long long

using namespace std;

ifstream cin("rectangle.in");
ofstream cout("rectangle.out");

const int kMaxN = 2e5 + 1;
struct A {
  int l, r, d, u, c;
} a[kMaxN];
struct E {
  int l, r, x, d;
  bool o;
} e[kMaxN * 2];
int n, m;
LL ans;
map<int, int> q1, q2;
class H {
  int n, l[kMaxN * 2], r[kMaxN * 2];

 public:
  void Clear() {
    n = 0;
    fill(&l[1], &l[m] + 1, 0);
    fill(&r[1], &r[m] + 1, 0);
  }

  void Change(int x, int y, int k) {
    n += k;
    for (int i = x; i <= m; i += i & -i) {
      l[i] += k;
    }
    for (int i = y; i <= m; i += i & -i) {
      r[i] += k;
    }
  }

  int Ask(int x, int y) {
    int ans = 0;
    for (int i = y; i >= 1; i -= i & -i) {
      ans += l[i];
    }
    for (int i = x; i >= 1; i -= i & -i) {
      ans -= r[i];
    }
    return ans;
  }
} h;
class T {
  struct V {
    LL w[3];
    int t;

    void operator+=(int k) {
      w[2] += w[0] * k * (k - 1) / 2;
      w[2] += w[1] * k;
      w[1] += w[0] * k;
      t += k;
    }

    V operator+(V &v) {
      return {w[0] + v.w[0], w[1] + v.w[1], w[2] + v.w[2], 0};
    }
  } v[kMaxN << 3];

  void Pushdown(int p) {
    if (v[p].t) {
      v[p << 1] += v[p].t;
      v[p << 1 | 1] += v[p].t;
      v[p].t = 0;
    }
  }

 public:
  void Init(int p, int l, int r) {
    v[p] = {r - l + 1};
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
  }

  void Add(int p, int l, int r, int _l, int _r, int k) {
    if (l >= _l && r <= _r) {
      return v[p] += k;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, k);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, k);
    }
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  LL Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].w[2];
    }
    Pushdown(p);
    int mid = l + r >> 1;
    LL ans = 0;
    if (mid >= _l) {
      ans += Ask(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }
} t1, t2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].l >> a[i].r >> a[i].d >> a[i].u;
    q1[a[i].l] = q1[a[i].r] = q2[a[i].d] = q2[a[i].u] = 0;
  }
  for (auto &i : q1) {
    i.second = ++m;
  }
  m = 0, ans = -1LL * n * (n - 1) * (n - 2) / 6;
  for (auto &i : q2) {
    i.second = ++m;
  }
  for (int i = 1; i <= n; i++) {
    a[i].l = q1[a[i].l], a[i].r = q1[a[i].r];
    a[i].d = q2[a[i].d], a[i].u = q2[a[i].u];
    e[i * 2 - 1] = {a[i].d, a[i].u, a[i].l, i, 1};
    e[i * 2] = {a[i].d, a[i].u, a[i].r, i, 0};
  }
  sort(e + 1, e + m + 1, [](E i, E j) {
    return i.x < j.x;
  });
  for (int i = 1; i <= m; i++) {
    if (e[i].o) {
      h.Change(e[i].l, e[i].r, 1);
      a[e[i].d].c -= h.Ask(e[i].l, e[i].r);
    } else {
      a[e[i].d].c += h.Ask(e[i].l, e[i].r);
    }
  }
  h.Clear();
  for (int i = 1; i <= m; i++) {
    if (e[i].o) {
      a[e[i].d].c += h.Ask(e[i].l, e[i].r);
      h.Change(e[i].l, e[i].r, 1);
    } else {
      h.Change(e[i].l, e[i].r, -1);
    }
  }
  for (int i = 1; i <= n; i++) {
    ans += 1LL * a[i].c * (a[i].c - 1) / 2;
    ans += 1LL * (n - a[i].c - 1) * (n - a[i].c - 2) / 2;
  }
  ans /= 2, t1.Init(1, 1, m), t2.Init(1, 1, m);
  for (int i = 1; i <= m; i++) {
    if (e[i].o) {
      ans -= t1.Ask(1, 1, m, e[i].l, e[i].r);
      ans += t2.Ask(1, 1, m, e[i].l, e[i].r - 1);
      t1.Add(1, 1, m, e[i].l, e[i].r, 1);
      t2.Add(1, 1, m, e[i].l, e[i].r - 1, 1);
    } else {
      t1.Add(1, 1, m, e[i].l, e[i].r, -1);
      t2.Add(1, 1, m, e[i].l, e[i].r - 1, -1);
    }
  }
  cout << ans << '\n';
  return 0;
}
