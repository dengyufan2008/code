#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const LL kMaxN = 5e5 + 1, kMaxL = 19, kMod = 1e9 + 7, kInf = 1e18;
struct P {
  int x, y;
  LL dis;
} p[kMaxN];
int n, m;
vector<int> s[kMaxN];

int Read() {
  int x = 0, c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
  return x;
}

struct T {
  struct V {
    int r;
    LL l;
    vector<pair<int, int>> e;
  } v[kMaxN];
  int k, a[kMaxN], d[kMaxL][kMaxN], lg[kMaxN];

  void S(int f, int x) {
    v[x].r = ++k, a[k] = x, d[0][k] = v[f].r;
    for (auto i : v[x].e) {
      if (i.first != f) {
        v[i.first].l = v[x].l + i.second;
        S(x, i.first);
      }
    }
  }

  void Init() {
    for (int i = 2; i < kMaxN; i++) {
      lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1, x, y, z; i < n; i++) {
      x = Read(), y = Read(), z = Read();
      v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
    }
    S(0, 1);
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = d[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          d[i][j] = min(d[i][j], d[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  int Lca(int x, int y) {
    if (x == y) {
      return x;
    }
    x = v[x].r, y = v[y].r;
    x > y ? swap(x, y) : void();
    int l = lg[y - x];
    return a[min(d[l][x + 1], d[l][y - (1 << l) + 1])];
  }

  LL Dis(int x, int y) {
    if (!x || !y) {
      return -kInf;
    }
    return v[x].l + v[y].l - v[Lca(x, y)].l * 2;
  }
} t;

struct W {
  int x, y;
  LL dis;

  W operator+(W w) {
    W ans = dis > w.dis ? *this : w;
    for (int i : {x, y}) {
      for (int j : {w.x, w.y}) {
        LL nwdis = t.Dis(i, j);
        if (ans.dis < nwdis) {
          ans = {i, j, nwdis};
        }
      }
    }
    return ans;
  }
};

struct Seg {
  W v[kMaxN << 2];

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = {l, r, 0};
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  void Change(int p, int l, int r, int x, bool o) {
    if (l == r) {
      v[p] = o ? (W){l, r, 0} : (W){0, 0, -kInf};
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, o);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, o);
    }
    v[p] = v[p << 1] + v[p << 1 | 1];
  }

  void Init() { Init(1, 1, n); }
  void Change(int x, bool o) { Change(1, 1, n, x, o); }
  W Ask() { return v[1]; }
} seg;

struct F {
  int f[kMaxN], s[kMaxN];

  void Init() {
    for (int i = 1; i <= n; i++) {
      f[i] = i, s[i] = 1;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    s[x] > s[y] ? swap(x, y) : void();
    f[x] = y, s[y] += s[x];
  }
} f;

struct G {
  struct E {
    int x, y;
    LL w;
  } e[kMaxN];
  int m;
  F f;

  void AddEdge(int x, int y, LL w) { e[++m] = {x, y, w}; }

  LL Calc() {
    LL ans = 0;
    sort(e + 1, e + m + 1, [](E i, E j) {
      return i.w > j.w;
    });
    f.Init();
    for (int i = 1; i <= m; i++) {
      int x = f.GetRoot(e[i].x), y = f.GetRoot(e[i].y);
      e[i].w %= kMod, ans = ans + (f.s[x] * f.s[y] % kMod * e[i].w) % kMod;
      f.Merge(x, y);
    }
    return ans * 2 % kMod;
  }
} g;

int main() {
  freopen("travel.in", "r", stdin);
  freopen("travel.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  n = m = Read(), t.Init(), seg.Init(), f.Init();
  for (int i = 1; i <= n; i++) {
    s[i].push_back(i);
  }
  while (m > 1) {
    W w = seg.Ask();
    for (int i = 1; i <= m; i++) {
      bool o = 0;
      p[i] = {0, 0, 0};
      for (int j : s[i]) {
        if (j == w.x || j == w.y) {
          o = 1;
          break;
        }
      }
      if (o) {
        for (int j : s[i]) {
          seg.Change(j, 0);
        }
        w = seg.Ask();
      }
      for (int j : s[i]) {
        LL dis1 = t.Dis(j, w.x), dis2 = t.Dis(j, w.y);
        if (dis1 < dis2) {
          swap(dis1, dis2), swap(w.x, w.y);
        }
        if (p[i].dis < dis1) {
          p[i] = {j, w.x, dis1};
        }
      }
      if (o) {
        for (int j : s[i]) {
          seg.Change(j, 1);
        }
        w = seg.Ask();
      }
    }
    for (int i = 1; i <= m; i++) {
      int x = f.GetRoot(p[i].x), y = f.GetRoot(p[i].y);
      if (x != y) {
        f.s[x] > f.s[y] ? swap(x, y) : void();
        s[y].insert(s[y].end(), s[x].begin(), s[x].end()), s[x].clear();
        f.Merge(x, y), g.AddEdge(p[i].x, p[i].y, p[i].dis);
      }
    }
    int _m = 0;
    for (int i = 1; i <= m; i++) {
      if (!s[i].empty()) {
        s[++_m].swap(s[i]);
      }
    }
    m = _m;
  }
  cout << g.Calc() << '\n';
  return 0;
}
