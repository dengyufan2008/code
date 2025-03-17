// 也是 O(n \log^2 n) 的, 但是被卡常了
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const LL kMaxN = 2e5 + 1, kMaxL = 72;
struct V {
  int d, f, s[2];
  LL w;
} v[kMaxN];
struct H {
  int x;
  LL y;
} h[kMaxN];
int n, m, k0, k1;
LL a[kMaxN];
vector<LL> g[2];
unordered_multiset<LL> s;

class Seg {
  struct E {
    int mx, t;
  } e[kMaxN * 150];

  void Add(int p, int l, int r, int _l, int _r, int w) {
    if (l >= _l && r <= _r) {
      e[p].mx += w, e[p].t += w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= _l) {
      Add(p << 1, l, mid, _l, _r, w);
    }
    if (mid < _r) {
      Add(p << 1 | 1, mid + 1, r, _l, _r, w);
    }
    e[p].mx = max(e[p << 1].mx, e[p << 1 | 1].mx) + e[p].t;
  }

 public:
  void Add(int k, int x, int y, int w) { Add(1, 1, k, x, y, w); }
  bool Ask() { return e[1].mx <= 1; }
} seg[2];

void CalcD(int x) {
  v[x].d = v[v[x].f].d + 1;
  if (x > n) {
    CalcD(v[x].s[0]), CalcD(v[x].s[1]);
  }
}

void Mark(LL x, LL y, int w) {
  if (x == y) {
    if (w == 1) {
      if (!s.count(x)) {
        g[1].push_back(x);
      }
      s.insert(x);
    } else if (w == -1) {
      s.erase(s.find(x));
      if (!s.count(x)) {
        g[1].push_back(x);
      }
    }
  } else {
    x > y ? swap(x, y) : void();
    g[0].push_back(x), g[0].push_back(y - 1);
    if (x + 1 <= y - 1) {
      g[1].push_back(x + 1), g[1].push_back(y - 1);
    }
  }
}

void Add(LL x, LL y, int w) {
  if (x == y) {
    if (w == 1) {
      if (!s.count(x)) {
        seg[1].Add(k1, g[1].back(), g[1].back(), 1);
        g[1].pop_back();
      }
      s.insert(x);
    } else if (w == -1) {
      s.erase(s.find(x));
      if (!s.count(x)) {
        seg[1].Add(k1, g[1].back(), g[1].back(), -1);
        g[1].pop_back();
      }
    }
  } else {
    x > y ? swap(x, y) : void();
    int shit1 = g[0].back();
    g[0].pop_back();
    int shit2 = g[0].back();
    g[0].pop_back();
    seg[0].Add(k0, shit1, shit2, w);
    if (x + 1 <= y - 1) {
      int shit1 = g[1].back();
      g[1].pop_back();
      int shit2 = g[1].back();
      g[1].pop_back();
      seg[1].Add(k1, shit1, shit2, w);
    }
  }
}

void CalcW1(int x) {
  if (x > n) {
    CalcW1(v[x].s[0]), CalcW1(v[x].s[1]);
    v[x].w = v[v[x].s[0]].w + v[v[x].s[1]].w;
    Mark(v[v[x].s[0]].w, v[v[x].s[1]].w, 1);
  }
}

void CalcW2(int x) {
  if (x > n) {
    CalcW2(v[x].s[0]), CalcW2(v[x].s[1]);
    v[x].w = v[v[x].s[0]].w + v[v[x].s[1]].w;
    Add(v[v[x].s[0]].w, v[v[x].s[1]].w, 1);
  }
}

void Proceed(vector<LL> &g, int &k) {
  static vector<int> o;
  static vector<LL> ans;
  o.resize(1), ans.resize(g.size());
  for (int i = 1; i < g.size(); i++) {
    o.push_back(i);
  }
  sort(o.begin(), o.end(), [&](int i, int j) {
    return g[i] < g[j];
  });
  for (int i = 1; i < g.size(); i++) {
    ans[o[i]] = ans[o[i - 1]] + (g[o[i]] > g[o[i - 1]]);
  }
  k = ans[o.back()], g.swap(ans);
  reverse(g.begin(), g.end()), g.pop_back();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  g[0].resize(1), g[1].resize(1);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], v[i].w = a[i];
  }
  for (int i = n + 1; i < n << 1; i++) {
    cin >> v[i].s[0] >> v[i].s[1];
    v[v[i].s[0]].f = v[v[i].s[1]].f = i;
  }
  if (n <= 2) {
    for (int i = 1; i <= m; i++) {
      cout << "YES\n";
    }
    return 0;
  }
  CalcD((n << 1) - 1);
  for (int i = 1; i < n << 1; i++) {
    if (v[i].d > kMaxL) {
      for (int j = 1; j <= m; j++) {
        cout << "NO\n";
      }
      return 0;
    }
  }
  CalcW1((n << 1) - 1);
  for (int i = 1; i < m; i++) {
    cin >> h[i].x >> h[i].y;
    for (int j = v[h[i].x].f; j; j = v[j].f) {
      Mark(v[v[j].s[0]].w, v[v[j].s[1]].w, -1);
    }
    v[h[i].x].w = h[i].y;
    for (int j = v[h[i].x].f; j; j = v[j].f) {
      v[j].w = v[v[j].s[0]].w + v[v[j].s[1]].w;
      Mark(v[v[j].s[0]].w, v[v[j].s[1]].w, 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    v[i].w = a[i];
  }
  Proceed(g[0], k0), Proceed(g[1], k1), s.clear();
  CalcW2((n << 1) - 1);
  cout << (seg[0].Ask() && seg[1].Ask() ? "YES\n" : "NO\n");
  for (int i = 1; i < m; i++) {
    for (int j = v[h[i].x].f; j; j = v[j].f) {
      Add(v[v[j].s[0]].w, v[v[j].s[1]].w, -1);
    }
    v[h[i].x].w = h[i].y;
    for (int j = v[h[i].x].f; j; j = v[j].f) {
      v[j].w = v[v[j].s[0]].w + v[v[j].s[1]].w;
      Add(v[v[j].s[0]].w, v[v[j].s[1]].w, 1);
    }
    cout << (seg[0].Ask() && seg[1].Ask() ? "YES\n" : "NO\n");
  }
  return 0;
}
