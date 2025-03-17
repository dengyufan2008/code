// 20240221 c
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxN = 2e5 + 1, kMaxM = 5e5 + 1, kInf = 1e9;
struct A {
  LL w;
  int p;
  explicit A(LL _w = 0, int _p = 0) : w(_w), p(_p) {}
};
struct B {
  int o;
  LL a, b;
};
struct C {
  LL k, b;
  explicit C(LL _k = 0, LL _b = 0) : k(_k), b(_b) {}
  bool operator<(const C &c) const {
    return k * c.b < b * c.k || k * c.b == b * c.k && k < c.k;
  }
};
struct D {
  int d, o, y;
  LL a, b;
};
struct V {
  int s, c;
  A f[3];
  LL d, w, g, t;
  bool b;
  vector<pair<int, int>> e;
  vector<D> q;
} v[kMaxN];
struct Q {
  int x, y, d, o1, o2;
  LL a, b;
  explicit Q(int _x = 0, int _y = 0, int _d = 0,
             int _o1 = 0, int _o2 = 0, LL _a = 0, LL _b = 0)
      : x(_x), y(_y), d(_d), o1(_o1), o2(_o2), a(_a), b(_b) {}
} q[kMaxM];
int n, m, k, s, o;
LL ans[kMaxM];
vector<int> p[kMaxN];
multimap<C, int> g;
class H {
  int u;
  C a[kMaxM << 1], v[kMaxM << 3];
  vector<B> t[kMaxN];

  LL F(C x, int o) { return x.k * a[o].k + x.b * a[o].b; }
  bool Less(C x, C y, int o) { return F(x, o) < F(y, o); }

  void Add(int p, int l, int r, C x) {
    int mid = l + r >> 1;
    if (Less(v[p], x, mid)) {
      t[u].push_back({p, v[p].k, v[p].b});
      swap(v[p], x);
    }
    if (l != r) {
      if (Less(v[p], x, l)) {
        Add(p << 1, l, mid, x);
      }
      if (Less(v[p], x, r)) {
        Add(p << 1 | 1, mid + 1, r, x);
      }
    }
  }

  LL Ask(int p, int l, int r, int o) {
    LL ans = F(v[p], o);
    if (l != r) {
      int mid = l + r >> 1;
      if (mid >= o) {
        ans = max(ans, Ask(p << 1, l, mid, o));
      } else {
        ans = max(ans, Ask(p << 1 | 1, mid + 1, r, o));
      }
    }
    return ans;
  }

 public:
  H() { fill(&v[1], &v[kMaxM << 3], C(-kInf, -kInf)); }
  void Set(int x, LL k, LL b) { a[x] = C(k, b); }
  void Add(LL k, LL b) { u++, Add(1, 1, m * 2, C(k, b)); }
  LL Ask(int o) { return Ask(1, 1, m * 2, o); }

  void Undo() {
    for (B i : t[u]) {
      v[i.o] = C(i.a, i.b);
    }
    t[u].clear(), u--;
  }
} h;

bool Update(A f[3], A w) {
  for (int i = 0; i < 3; i++) {
    if (f[i].w <= w.w) {
      for (int j = 2; j > i; j--) {
        f[j] = f[j - 1];
      }
      return f[i] = w, 1;
    }
  }
  return 0;
}

void CalcF1(int f, int x) {
  for (auto i : v[x].e) {
    if (i.first != f) {
      CalcF1(x, i.first);
      Update(v[x].f, A(v[i.first].f[0].w + i.second, i.first));
    }
  }
}

void CalcF2(int f, int x, LL w) {
  Update(v[x].f, A(w, f));
  if (v[x].e.empty()) {
    return;
  }
  LL pre[v[x].e.size()] = {}, suf[v[x].e.size()] = {};
  pre[0] = v[v[x].e.front().first].f[0].w + v[x].e.front().second;
  v[x].e.front().first == f && (pre[0] = 0);
  suf[v[x].e.size() - 1] = v[v[x].e.back().first].f[0].w + v[x].e.back().second;
  v[x].e.back().first == f && (suf[v[x].e.size() - 1] = 0);
  for (int i = 1; i < v[x].e.size(); i++) {
    pre[i] = pre[i - 1];
    if (v[x].e[i].first != f) {
      pre[i] = max(pre[i], v[v[x].e[i].first].f[0].w + v[x].e[i].second);
    }
  }
  for (int i = v[x].e.size() - 2; i >= 0; i--) {
    suf[i] = suf[i + 1];
    if (v[x].e[i].first != f) {
      suf[i] = max(suf[i], v[v[x].e[i].first].f[0].w + v[x].e[i].second);
    }
  }
  for (int i = 0; i < v[x].e.size(); i++) {
    if (v[x].e[i].first != f) {
      LL _pre = i ? pre[i - 1] : 0;
      LL _suf = i < v[x].e.size() - 1 ? suf[i + 1] : 0;
      CalcF2(x, v[x].e[i].first, max(w, max(_pre, _suf)) + v[x].e[i].second);
    }
  }
}

LL MaxDis(int x, int ban1 = -1, int ban2 = -1) {
  for (int i = 0; i < 3; i++) {
    if (v[x].f[i].p != ban1 && v[x].f[i].p != ban2) {
      return v[x].f[i].w;
    }
  }
  return -kInf;
}

void CalcR(int f, int x) {
  int mx = 0;
  v[x].s = 1;
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      CalcR(x, i.first);
      v[x].s += v[i.first].s;
      mx = max(mx, v[i.first].s);
    }
  }
  if (!s && max(mx, k - v[x].s) * 2 <= k) {
    s = x;
  }
}

void Calc(int f, int x) {
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      v[i.first].c = v[x].c;
      v[i.first].d = MaxDis(x, i.first, f);
      v[i.first].w = v[x].w + i.second;
      v[i.first].g = max(v[x].g, v[i.first].d + v[x].w);
      v[i.first].t = max(v[x].t, v[i.first].d - v[x].w);
      Calc(x, i.first);
    }
  }
  v[x].t = max(v[x].t + v[x].w, MaxDis(x, f));
}

void Ans(int f, int x) {
  for (auto i : v[x].q) {
    ans[i.d] = max(ans[i.d], h.Ask(i.o) + i.a * v[x].w + i.b * v[i.y].w);
    ans[i.d] = max(ans[i.d], i.a * MaxDis(x, f) + i.b * (v[x].g + v[i.y].w));
  }
  v[x].q.clear();
  for (auto i : v[x].e) {
    if (i.first != f && !v[i.first].b) {
      h.Add(v[i.first].d - v[x].w, v[x].g);
      Ans(x, i.first);
      h.Undo();
    }
  }
}

void Divide(int l, int r) {
  if (l > r) {
    return;
  }
  v[s].b = 1, v[s].c = v[s].d = v[s].w = v[s].t = v[s].g = 0;
  for (auto i : v[s].e) {
    if (!v[i.first].b) {
      v[i.first].c = i.first;
      v[i.first].d = 0;
      v[i.first].w = i.second;
      v[i.first].g = 0;
      v[i.first].t = -i.second;
      Calc(s, i.first);
    }
  }
  for (int i = l; i <= r; i++) {
    if (v[q[i].x].c != v[q[i].y].c) {
      v[q[i].x].q.push_back({q[i].d, q[i].o1, q[i].y, q[i].a, q[i].b});
      v[q[i].y].q.push_back({q[i].d, q[i].o2, q[i].x, q[i].b, q[i].a});
      LL x = q[i].a * v[q[i].x].t;
      LL y = q[i].b * v[q[i].y].t;
      LL z = MaxDis(s, v[q[i].x].c, v[q[i].y].c);
      ans[q[i].d] = max(ans[q[i].d], x + y);
      if (v[q[i].x].c) {
        ans[q[i].d] = max(ans[q[i].d], x + q[i].b * (z + v[q[i].y].w));
      }
      if (v[q[i].y].c) {
        ans[q[i].d] = max(ans[q[i].d], y + q[i].a * (z + v[q[i].x].w));
      }
    } else {
      p[v[q[i].x].c].push_back(i);
    }
  }
  for (auto i : v[s].e) {
    if (!v[i.first].b) {
      Ans(s, i.first);
    }
  }
  int _l = 0, _k = k, _s = s;
  Q _q[r - l + 1];
  for (auto i : v[s].e) {
    if (!v[i.first].b) {
      for (int j : p[i.first]) {
        _q[_l++] = q[j];
      }
      v[i.first].c = p[i.first].size();
      p[i.first].clear();
    }
  }
  for (int i = l; i <= r; i++) {
    q[i] = _q[i - l];
  }
  for (auto i : v[_s].e) {
    if (!v[i.first].b) {
      r = l + v[i.first].c - 1, s = 0;
      k = v[i.first].s > v[_s].s ? _k - v[_s].s : v[i.first].s;
      CalcR(_s, i.first), Divide(l, r);
      l = r + 1;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k;
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].x >> q[i].y >> q[i].a >> q[i].b;
    q[i].d = i, g.insert({C(q[i].a, q[i].b), 0}), g.insert({C(q[i].b, q[i].a), 0});
  }
  for (auto &i : g) {
    i.second = ++o, h.Set(o, i.first.k, i.first.b);
  }
  for (int i = 1; i <= m; i++) {
    q[i].o1 = g.find(C(q[i].a, q[i].b))->second;
    q[i].o2 = g.find(C(q[i].b, q[i].a))->second;
  }
  CalcF1(0, 1), CalcF2(0, 1, 0);
  k = n, s = 0, CalcR(0, 1), Divide(1, m);
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
