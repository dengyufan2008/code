#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("yyl.in");
ofstream cout("yyl.out");

const int kMaxN = 3e5 + 1, kMaxL = 19;
struct V {
  int r, s, d, l, f[kMaxL];
  vector<int> e;
} v[kMaxN];
int n, m, a[kMaxN];

class Seg {
  struct V {
    LL s, t;
  } v[kMaxN << 2];
  LL w;

  void Tag(int p, int l, int r, LL x) {
    v[p].s += (r - l + 1) * x, v[p].t += x;
  }

  void Pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    Tag(p << 1, l, mid, v[p].t);
    Tag(p << 1 | 1, mid + 1, r, v[p].t);
    v[p].t = 0;
  }

  void Add(int p, int l, int r, int _l, int _r, int x) {
    if (l >= _l && r <= _r) {
      return Tag(p, l, r, x);
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, x);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, x);
    }
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  }

  int FindGeMid(int p, int l, int r, LL x) {
    if (l == r) {
      return l;
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if ((x + v[p << 1].s) * 2 >= w) {
      return FindGeMid(p << 1, l, mid, x);
    } else {
      return FindGeMid(p << 1 | 1, mid + 1, r, x + v[p << 1].s);
    }
  }

  LL Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p].s;
    }
    Pushdown(p, l, r);
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

 public:
  void Add(int l, int r, int x) {
    w += 1LL * (r - l + 1) * x, Add(1, 1, n, l, r, x);
  }

  int FindGeMid() {
    return FindGeMid(1, 1, n, 0);
  }

  bool ChkLeMid(int l, int r) {
    return Ask(1, 1, n, l, r) * 2 <= w;
  }
} seg;

int Lca(int x, int y) {
  v[x].d < v[y].d ? swap(x, y) : void();
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].d - (1 << i) >= v[y].d) {
      x = v[x].f[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (v[x].f[i] != v[y].f[i]) {
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

void Init1(int f, int x) {
  v[x].s = 1, v[x].d = v[f].d + 1, v[x].f[0] = f;
  for (int i = 1; i < kMaxL; i++) {
    v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
  }
  for (int &i : v[x].e) {
    if (i != f) {
      Init1(x, i), v[x].s += v[i].s;
      if (v[x].e[0] == f || v[i].s > v[v[x].e[0]].s) {
        swap(i, v[x].e[0]);
      }
    }
  }
}

void Init2(int f, int x, int l) {
  static int k = 0;
  v[x].l = l, v[x].r = ++k, a[k] = x;
  if (!v[x].e.empty() && v[x].e[0] != f) {
    Init2(x, v[x].e[0], l);
  }
  for (int i : v[x].e) {
    if (i != f && i != v[x].e[0]) {
      Init2(x, i, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  Init1(0, 1), Init2(0, 1, 1), cin >> m;
  for (int i = 1, o, x, y, w; i <= m; i++) {
    cin >> o;
    if (o == 1) {
      cin >> x >> w;
      seg.Add(v[x].r, v[x].r + v[x].s - 1, w);
    } else {
      cin >> x >> y >> w;
      for (; v[x].l != v[y].l; x = v[v[x].l].f[0]) {
        v[x].r < v[y].r ? swap(x, y) : void();
        seg.Add(v[v[x].l].r, v[x].r, w);
      }
      v[x].r > v[y].r ? swap(x, y) : void();
      seg.Add(v[x].r, v[y].r, w);
    }
    x = seg.FindGeMid(), x = a[x];
    for (int j = kMaxL - 1; j >= 0; j--) {
      y = v[x].f[j];
      if (y && seg.ChkLeMid(v[y].r, v[y].r + v[y].s - 1)) {
        x = y;
      }
    }
    if (seg.ChkLeMid(v[x].r, v[x].r + v[x].s - 1)) {
      cout << v[x].f[0] << '\n';
    } else {
      cout << x << '\n';
    }
  }
  return 0;
}
