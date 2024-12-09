#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("mex.in");
ofstream cout("mex.out");

const int kMaxN = 1e6 + 1, kNull = -114514;
int n, m, ans[kMaxN];
vector<int> p[kMaxN];
vector<pair<int, int>> q[kMaxN];
struct Seg0 {
  int v[kMaxN << 2];

  void Init(int p, int l, int r) {
    v[p] = r - l + 1;
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  }

  void Decrease(int p, int l, int r, int x) {
    if (l == r) {
      v[p] = 0;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Decrease(p << 1, l, mid, x);
    } else {
      Decrease(p << 1 | 1, mid + 1, r, x);
    }
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans += Ask(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      ans += Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
    return ans;
  }
} seg0;
struct Seg1 {
  struct V {
    int lmin, lmax, rmin, rmax, wmax, t;
  } v[kMaxN << 2];

  void Pushdown(int p) {
    if (v[p].t) {
      v[p << 1].wmax += v[p].t, v[p << 1].t += v[p].t;
      v[p << 1 | 1].wmax += v[p].t, v[p << 1 | 1].t += v[p].t;
      v[p].t = 0;
    }
  }

  V Calc(V x, V y) {
    return {min(x.lmin, y.lmin), max(x.lmax, y.lmax),
            min(x.rmin, y.rmin), max(x.rmax, y.rmax), max(x.wmax, y.wmax), 0};
  }

  void Init(int p, int l, int r) {
    v[p] = {n + 1, 0, n + 1, 0, -1, 0};
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  }

  void Change(int p, int l, int r, int x, bool o) {
    if (l == r) {
      if (o) {
        v[p] = {l, l, q[l].back().first, q[l].back().first,
                seg0.Ask(1, 1, n, l, q[l].back().first), 0};
      } else {
        v[p] = {n + 1, 0, n + 1, 0, -1, 0};
      }
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, o);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, o);
    }
    v[p] = Calc(v[p << 1], v[p << 1 | 1]);
  }

  void Decrease(int p, int l, int r, int x) {
    if (v[p].lmin > x || v[p].rmax < x) {
      return;
    } else if (v[p].lmax <= x && v[p].rmin >= x) {
      v[p].wmax--, v[p].t--;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    Decrease(p << 1, l, mid, x), Decrease(p << 1 | 1, mid + 1, r, x);
    v[p] = Calc(v[p << 1], v[p << 1 | 1]);
  }

  int Ask(int p, int l, int r, int x) {
    if (l == r) {
      return l;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (v[p << 1].wmax >= x) {
      return Ask(p << 1, l, mid, x);
    } else if (v[p << 1 | 1].wmax >= x) {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
    return kNull;
  }

  int Pre(int p, int l, int r, int x) {
    if (l == r) {
      return v[p].rmax;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (v[p << 1 | 1].lmin < x) {
      return Pre(p << 1 | 1, mid + 1, r, x);
    } else if (v[p << 1].lmin < x) {
      return Pre(p << 1, l, mid, x);
    }
    return 0;
  }

  int Suf(int p, int l, int r, int x) {
    if (l == r) {
      return v[p].lmin;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (v[p << 1].lmax > x) {
      return Suf(p << 1, l, mid, x);
    } else if (v[p << 1 | 1].lmax > x) {
      return Suf(p << 1 | 1, mid + 1, r, x);
    }
    return n + 1;
  }
} seg1;
struct Seg2 {
  int v[kMaxN << 2];

  int Calc(int x, int y) {
    if (q[y].empty()) {
      return x;
    } else if (q[x].empty()) {
      return y;
    }
    int _x = q[x].back().first, _y = q[y].back().first;
    return _x > _y || _x == _y && x < y ? x : y;
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = l;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    v[p] = Calc(v[p << 1], v[p << 1 | 1]);
  }

  void Change(int p, int l, int r, int x) {
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x);
    } else {
      Change(p << 1 | 1, mid + 1, r, x);
    }
    v[p] = Calc(v[p << 1], v[p << 1 | 1]);
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans = Calc(Ask(p << 1, l, mid, _l, _r), ans);
    }
    if (mid < _r) {
      ans = Calc(Ask(p << 1 | 1, mid + 1, r, _l, _r), ans);
    }
    return ans;
  }
} seg2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    p[min(x, n)].push_back(i);
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    q[x].push_back({y, i});
  }
  for (int i = 1; i <= n; i++) {
    sort(q[i].begin(), q[i].end());
  }
  seg1.Init(1, 1, n), seg2.Init(1, 1, n), seg0.Init(1, 1, n);
  for (int i = 1, j = 0; i <= n; i++) {
    if (!q[i].empty() && q[i].back().first > j) {
      j = q[i].back().first;
      seg1.Change(1, 1, n, i, 1);
    }
  }
  for (int i = n; i >= 0; i--) {
    for (int j : p[i]) {
      seg0.Decrease(1, 1, n, j), seg1.Decrease(1, 1, n, j);
    }
    for (int j = seg1.Ask(1, 1, n, i); j != kNull; j = seg1.Ask(1, 1, n, i)) {
      ans[q[j].back().second] = i, q[j].pop_back();
      seg1.Change(1, 1, n, j, 0), seg2.Change(1, 1, n, j);
      int rmin = seg1.Pre(1, 1, n, j), lmax = seg1.Suf(1, 1, n, j);
      for (; j < lmax;) {
        lmax = seg2.Ask(1, 1, n, j, lmax - 1);
        if (!q[lmax].empty() && q[lmax].back().first > rmin) {
          seg1.Change(1, 1, n, lmax, 1);
        } else {
          break;
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
