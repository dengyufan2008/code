#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("query.in");
ofstream cout("query.out");

const int kMaxN = 5e5 + 1, kMaxL = 19;
struct Q {
  int l, r, k, o;
};
struct E {
  int l, r, w;
};
int n, m, a[kMaxN], ans[kMaxN], lg[kMaxN];
vector<Q> q;
vector<E> e;

class Tree {
  struct V {
    int d, f[kMaxL];
    vector<int> e;
  } v[kMaxN];

  void T(int f, int x) {
    v[x].d = v[f].d + 1, v[x].f[0] = f;
    for (int i = 1; i < kMaxL; i++) {
      v[x].f[i] = v[v[x].f[i - 1]].f[i - 1];
    }
    for (int i : v[x].e) {
      i != f ? T(x, i) : void();
    }
  }

 public:
  void AddEdge(int x, int y) { v[x].e.push_back(y), v[y].e.push_back(x); }
  void Init() { T(0, 1); }
  int Dep(int x) { return v[x].d; }

  int LcaDep(int x, int y) {
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
    return v[x].d - (x != y);
  }
} tree;

class Bit {
  int v[kMaxN];

 public:
  void Max(int x, int w) {
    for (int i = x; i <= n; i += i & -i) {
      v[i] = max(v[i], w);
    }
  }

  int Ask(int x) {
    int ans = 0;
    for (int i = x; i >= 1; i -= i & -i) {
      ans = max(ans, v[i]);
    }
    return ans;
  }
} bit;

class Seg {
  int v[kMaxN << 2];

  void Max(int p, int l, int r, int x, int w) {
    if (l == r) {
      v[p] = max(v[p], w);
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Max(p << 1, l, mid, x, w);
    } else {
      Max(p << 1 | 1, mid + 1, r, x, w);
    }
    v[p] = max(v[p << 1], v[p << 1 | 1]);
  }

  int Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1, ans = 0;
    if (mid >= _l) {
      ans = max(ans, Ask(p << 1, l, mid, _l, _r));
    }
    if (mid < _r) {
      ans = max(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r));
    }
    return ans;
  }

 public:
  void Max(int x, int w) { Max(1, 1, n, x, w); }
  int Ask(int l, int r) { return Ask(1, 1, n, l, r); }
} seg1, seg2;

void CalcQ() {
  static int g[kMaxL][kMaxN];
  for (int i = 1; i < n; i++) {
    a[i] = tree.LcaDep(i, i + 1);
  }
  for (int i = 1; i <= n; i++) {
    g[0][i] = tree.Dep(i);
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      g[i][j] = g[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        g[i][j] = max(g[i][j], g[i - 1][j + (1 << i - 1)]);
      }
    }
  }
  n--, cin >> m;
  for (int i = 1, l, r, k; i <= m; i++) {
    cin >> l >> r >> k;
    if (k == 1) {
      int o = lg[r - l + 1];
      ans[i] = max(g[o][l], g[o][r - (1 << o) + 1]);
    } else {
      q.push_back({l, r - 1, k - 1, i});
    }
  }
}

void CalcE() {
  static int pre[kMaxN], nxt[kMaxN];
  static vector<pair<int, int>> s;
  for (int i = 1; i <= n; i++) {
    for (; !s.empty() && s.back().first >= a[i]; s.pop_back()) {
    }
    pre[i] = s.empty() ? 0 : s.back().second;
    s.push_back({a[i], i});
  }
  s.clear();
  for (int i = n; i >= 1; i--) {
    for (; !s.empty() && s.back().first >= a[i]; s.pop_back()) {
    }
    nxt[i] = s.empty() ? n + 1 : s.back().second;
    s.push_back({a[i], i});
  }
  for (int i = 1; i <= n; i++) {
    e.push_back({pre[i] + 1, nxt[i] - 1, a[i]});
  }
}

// [L, R, k]: [l, r, w] st. r-l+1 \ge k, l \in [L, R-k+1] \lor r \in [L+k-1, R]
void CalcAns1() {
  sort(q.begin(), q.end(), [](Q i, Q j) {
    return i.k > j.k;
  });
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.r - i.l > j.r - j.l;
  });
  for (int i = 0, j = 0; i < q.size(); i++) {
    for (; j < n && e[j].r - e[j].l + 1 >= q[i].k; j++) {
      seg1.Max(e[j].l, e[j].w), seg2.Max(e[j].r, e[j].w);
    }
    ans[q[i].o] = max(ans[q[i].o], seg1.Ask(q[i].l, q[i].r - q[i].k + 1));
    ans[q[i].o] = max(ans[q[i].o], seg2.Ask(q[i].l + q[i].k - 1, q[i].r));
  }
}

// [L, R, k]: [l, r, w] st. [L, R] \subseteq [l, r]
void CalcAns2() {
  sort(q.begin(), q.end(), [](Q i, Q j) {
    return i.r > j.r;
  });
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.r > j.r;
  });
  for (int i = 0, j = 0; i < q.size(); i++) {
    for (; j < n && e[j].r >= q[i].r; j++) {
      bit.Max(e[j].l, e[j].w);
    }
    ans[q[i].o] = max(ans[q[i].o], bit.Ask(q[i].l));
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, tree.AddEdge(x, y);
  }
  tree.Init(), CalcQ(), CalcE(), CalcAns1(), CalcAns2();
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
