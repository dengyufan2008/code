#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 3e5 + 1, kMaxM = kMaxN << 1, kMaxV = 2e9;
struct A {
  int l, r, c, _c, _kc;
  int f, w, s;
  pair<int, int> p, n;
  unordered_map<int, int> e;
} a[kMaxN];
struct V {
  int l, r, w;
} v[kMaxN * 19];
int n, m, c, k, w, g[kMaxM], ans[kMaxM];
vector<pair<int, bool>> d[kMaxM];
unordered_set<int> q;

struct H {
  int mx, o;
  int mx2, o2;
  void Merge(int mx3, int o3) {
    if (o == o3) {
      mx = max(mx, mx3);
    } else if (o2 == o3) {
      mx2 = max(mx2, mx3);
      if (mx < mx2) {
        swap(mx, mx2), swap(o, o2);
      }
    } else if (mx3 > mx) {
      mx2 = mx, o2 = o, mx = mx3, o = o3;
    } else if (mx3 > mx2) {
      mx2 = mx3, o2 = o3;
    }
  }
  void Merge(H h) { Merge(h.mx, h.o), Merge(h.mx2, h.o2); }
} h[kMaxM];

void Change(int x, int mx, int o) {
  for (int i = x; i <= c; i += i & -i) {
    h[i].Merge(mx, o);
  }
}

H Ask(int x) {
  H ans = H();
  for (int i = x; i >= 1; i -= i & -i) {
    ans.Merge(h[i]);
  }
  return ans;
}

void Add(int &p, int l, int r, int x, int w) {
  static int u = 0;
  !p && (p = ++u);
  if (l == r) {
    v[p].w += w;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(v[p].l, l, mid, x, w);
  } else {
    Add(v[p].r, mid + 1, r, x, w);
  }
  v[p].w = max(v[v[p].l].w, v[v[p].r].w);
}

void Init() {
  static int p[kMaxM], b[kMaxM], o[kMaxM];
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].l >> a[i].r >> a[i].c;
    g[i * 2 - 1] = a[i].l, g[i * 2] = a[i].r;
    b[i * 2 - 1] = a[i].c, b[i * 2] = k - a[i].c;
    o[i * 2 - 1] = i * 2 - 1, o[i * 2] = i * 2;
  }
  sort(o + 1, o + n * 2 + 1, [](int i, int j) {
    return g[i] < g[j];
  });
  p[o[1]] = 1;
  for (int i = 2; i <= n * 2; i++) {
    p[o[i]] = p[o[i - 1]] + (g[o[i]] > g[o[i - 1]]);
  }
  sort(g + 1, g + n * 2 + 1);
  m = unique(g + 1, g + n * 2 + 1) - g - 1;
  for (int i = 1; i <= n; i++) {
    d[p[i * 2 - 1]].push_back({i, 1});
    d[p[i * 2]].push_back({i, 0});
  }
  sort(o + 1, o + n * 2 + 1, [](int i, int j) {
    return b[i] < b[j];
  });
  p[o[1]] = 1;
  for (int i = 2; i <= n * 2; i++) {
    p[o[i]] = p[o[i - 1]] + (b[o[i]] > b[o[i - 1]]);
  }
  c = p[o[n * 2]];
  for (int i = 1; i <= n; i++) {
    a[i]._c = p[i * 2 - 1], a[i]._kc = p[i * 2];
  }
}

void Build() {
  for (int i = 1; i <= m; i++) {
    for (auto j : d[i]) {
      j.second ? q.insert(j.first), 0 : q.erase(j.first);
    }
    if (q.size() == 2) {
      int x = *q.begin(), y = *++q.begin();
      if (a[x].l != a[y].l) {
        a[x].l > a[y].l ? swap(x, y) : void();
      } else if (a[x].r != a[y].r) {
        a[x].r < a[y].r ? swap(x, y) : void();
      } else {
        x > y ? swap(x, y) : void();
      }
      if (a[x].c + a[y].c <= k) {
        if (a[x].r < a[y].r) {
          a[x].n = {y, 0}, a[y].p = {x, 0};
        } else if (!a[y].f) {
          a[x].e[y] = a[x].e.size() + 1, a[y].f = x;
        }
      }
    }
  }
}

void Dot(int x, int z) {
  a[x].w += z;
  Change(a[x]._c, a[x].w, x);
  H h = Ask(a[x]._kc);
  w = max(w, (h.o == x ? h.mx2 : h.mx) + a[x].w);
  if (a[x].f) {
    int y = a[x].f, o = a[y].e[x];
    Add(a[y].s, 1, a[y].e.size(), o, z);
    w = max(w, v[a[y].s].w + a[y].w);
  } else {
    if (a[x].p.first) {
      w = max(w, a[a[x].p.first].w + a[x].p.second + a[x].w);
    }
    if (a[x].n.first) {
      w = max(w, a[a[x].n.first].w + a[x].n.second + a[x].w);
    }
    if (!a[x].e.empty()) {
      w = max(w, v[a[x].s].w + a[x].w);
    }
  }
}

void Edge(int x, int y, int z) {
  if (a[x].r < a[y].r) {
    a[x].n.second += z, a[y].p.second += z;
    w = max(w, a[x].w + a[y].w + a[x].n.second);
  } else {
    int o = a[x].e[y];
    Add(a[x].s, 1, a[x].e.size(), o, z);
    w = max(w, v[a[x].s].w + a[x].w);
  }
}

void CalcAns() {
  int t = ans[1] = g[1];
  for (int i = 1; i < m; i++) {
    int z = g[i + 1] - g[i];
    for (auto j : d[i]) {
      j.second ? q.insert(j.first), 0 : q.erase(j.first);
    }
    if (q.size() == 0) {
      t += z;
    } else if (q.size() == 1) {
      int x = *q.begin();
      if (a[x].c <= k) {
        Dot(x, z);
      }
    } else if (q.size() == 2) {
      int x = *q.begin(), y = *++q.begin();
      if (a[x].l != a[y].l) {
        a[x].l > a[y].l ? swap(x, y) : void();
      } else if (a[x].r != a[y].r) {
        a[x].r < a[y].r ? swap(x, y) : void();
      } else {
        x > y ? swap(x, y) : void();
      }
      if (a[x].c + a[y].c <= k) {
        Edge(x, y, z);
      }
    }
    ans[i + 1] = w + t;
  }
  ans[m + 1] = kMaxV - g[m] + ans[m];
  g[m + 1] = kMaxV, m++;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int o;
  Init(), Build(), CalcAns();
  cin >> o;
  for (int i = 1, x, y; i <= o; i++) {
    cin >> x;
    y = lower_bound(ans + 1, ans + m + 1, x) - ans;
    cout << x - ans[y] + g[y] << '\n';
  }
  return 0;
}
