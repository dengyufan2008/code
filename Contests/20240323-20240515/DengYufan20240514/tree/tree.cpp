#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const int kMaxN = 1e5 + 1, kMaxL = 11, kMod = 998244353;
struct W {
  LL k, b;
  W operator*(W x) {
    return {k * x.k % kMod, (b * x.k + x.b) % kMod};
  }
};
struct V {
  int f, s, l, d, r, t, w;
  bool b;
  pair<int, int> p[kMaxL];
  vector<int> e;
} v[kMaxN];
int n, m, k, a[kMaxN];
queue<int> q;
class Seg {
  pair<W, W> v[kMaxN << 2];
  bool b[kMaxN];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p].first.b = v[p].second.b = ::v[a[l]].w;
      b[l] = ::v[a[l]].b;
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p].first.k = v[p].second.k = 1;
  }

  void Pushdown(int p) {
    if (v[p].second.k != 1 || v[p].second.b != 0) {
      v[p << 1].second = v[p << 1].second * v[p].second;
      v[p << 1 | 1].second = v[p << 1 | 1].second * v[p].second;
      v[p].second = {1, 0};
    }
    if (v[p].first.k != 1 || v[p].first.b != 0) {
      v[p << 1].first = v[p << 1].first * v[p].first;
      v[p << 1 | 1].first = v[p << 1 | 1].first * v[p].first;
      v[p].first = {1, 0};
    }
  }

  void Change(int p, int l, int r, int _l, int _r, W w, bool o) {
    if (l >= _l && r <= _r) {
      if (o) {
        v[p].first = v[p].first * w;
      }
      v[p].second = v[p].second * w;
      return;
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Change(p << 1, l, mid, _l, _r, w, o);
    }
    if (mid < _r) {
      Change(p << 1 | 1, mid + 1, r, _l, _r, w, o);
    }
  }

  int Ask(int p, int l, int r, int x) {
    if (l == r) {
      if (b[x]) {
        return v[p].second.b;
      } else {
        return v[p].first.b;
      }
    }
    Pushdown(p);
    int mid = l + r >> 1;
    if (mid >= x) {
      return Ask(p << 1, l, mid, x);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, x);
    }
  }

 public:
  void Init() { Init(1, 1, n); }

  void Change(int l, int r, int k, int b, bool o) {
    if (l >= 1 && r <= n && l <= r) {
      Change(1, 1, n, l, r, {k, b}, o);
    }
  }

  int Ask(int x) { return Ask(1, 1, n, x); }
} seg;

void S(int f, int x) {
  v[x].f = f, v[x].s = 1, v[x].d = v[f].d + 1;
  for (int &i : v[x].e) {
    if (i != f) {
      S(x, i), v[x].s += v[i].s;
      if (v[x].e[0] == f || v[v[x].e[0]].s < v[i].s) {
        swap(v[x].e[0], i);
      }
    }
  }
}

void R(int s, int x, int l) {
  if (l == kMaxL - 1) {
    v[x].r = ++k, a[k] = x;
  } else {
    for (int i : v[x].e) {
      if (i != v[x].f) {
        R(s, i, l + 1);
      }
    }
  }
  v[s].p[l].first = min(v[s].p[l].first, v[x].r);
  v[s].p[l].second = max(v[s].p[l].second, v[x].r);
}

void T(int x, int l) {
  for (int i = 0; i < kMaxL; i++) {
    v[x].p[i] = {n, 0};
  }
  v[x].l = l, v[x].b = v[x].d - v[l].d >= kMaxL - 1;
  R(x, x, 0), v[x].t = v[x].r;
  if (!v[x].e.empty() && v[x].e[0] != v[x].f) {
    T(v[x].e[0], l);
    v[x].t = max(v[x].t, v[v[x].e[0]].t);
  }
  for (int i : v[x].e) {
    if (i != v[x].f && i != v[x].e[0]) {
      T(i, i);
      v[x].t = max(v[x].t, v[i].t);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  S(0, 1);
  for (kMaxL > 1 ? q.push(1) : void(); !q.empty(); q.pop()) {
    int x = q.front();
    v[x].r = ++k, a[k] = x;
    for (int i : v[x].e) {
      if (i != v[x].f && v[i].d < kMaxL) {
        q.push(i);
      }
    }
  }
  T(1, 1);
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  seg.Init();
  for (int u = 1, o, x, y, k, b; u <= m; u++) {
    cin >> o >> x;
    if (o == 1) {
      cout << seg.Ask(v[x].r) << '\n';
    } else if (o == 2) {
      pair<int, int> p[kMaxL];
      cin >> y >> k >> b;
      seg.Change(v[x].p[0].first, v[x].p[0].second, k, b, 1);
      for (int i = 1; i <= y; i++) {
        seg.Change(v[x].p[i].first, v[x].p[i].second, k, b, 1);
        p[i] = v[x].p[i - 1];
      }
      for (int i = 1; i <= y; i++) {
        x = v[x].f;
        seg.Change(v[x].p[0].first, v[x].p[0].second, k, b, 1);
        for (int j = 1; i + j <= y; j++) {
          if (p[j] != make_pair(n, 0)) {
            seg.Change(v[x].p[j].first, p[j].first - 1, k, b, 1);
            seg.Change(p[j].second + 1, v[x].p[j].second, k, b, 1);
          } else {
            seg.Change(v[x].p[j].first, v[x].p[j].second, k, b, 1);
          }
          p[j] = v[x].p[j - 1];
        }
      }
    } else if (o == 3) {
      cin >> k >> b;
      for (int i = 0; i < kMaxL; i++) {
        seg.Change(v[x].p[i].first, v[x].p[i].second, k, b, 1);
      }
      if (v[x].p[kMaxL - 1] != make_pair(n, 0)) {
        seg.Change(v[x].p[kMaxL - 1].second + 1, v[x].t, k, b, 1);
      }
    } else {
      int p;
      cin >> y >> k >> b;
      for (; v[x].l != v[y].l; x = v[v[x].l].f) {
        v[v[x].l].d < v[v[y].l].d ? swap(x, y) : void();
        p = v[x].l;
        for (int i = 1; i < kMaxL && p != x; i++) {
          seg.Change(v[p].r, v[p].r, k, b, 1);
          p = v[p].e[0];
        }
        seg.Change(v[p].r, v[x].r, k, b, p == x);
      }
      v[x].d > v[y].d ? swap(x, y) : void();
      p = x;
      for (int i = 1; i < kMaxL && p != y; i++) {
        seg.Change(v[p].r, v[p].r, k, b, 1);
        p = v[p].e[0];
      }
      seg.Change(v[p].r, v[y].r, k, b, p == y);
    }
  }
  return 0;
}
