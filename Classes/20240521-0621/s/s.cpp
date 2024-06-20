// O(n \sqrt n)
#include <fstream>
#include <set>
#include <vector>
#define LL long long
#define PLL pair<LL, LL>
#define LLL __int128_t

using namespace std;

ifstream cin("s.in");
ofstream cout("s.out");

const int kMaxN = 2e5 + 1;
struct T {
  int l, r;
  mutable int w;
  bool operator<(const T &t) const {
    return ~l && ~t.l ? l < t.l : w > t.w;
  }
};
int n, m, a[kMaxN], h[kMaxN];
LL s[kMaxN], f[kMaxN];
vector<T> o[kMaxN];

PLL operator-(PLL x, PLL y) {
  return {x.first - y.first, x.second - y.second};
}

class E {
  set<T> s;

  auto Split(int x) {  // (, x] return (x, ]
    if (s.empty() || (--s.end())->r <= x) {
      return s.end();
    }
    auto p = s.lower_bound({x + 1, -1, -1});
    if (p != s.end() && p->l == x + 1) {
      return p;
    }
    T t = *--p;
    s.erase(p), s.insert({t.l, x, t.w});
    return s.insert({x + 1, t.r, t.w}).first;
  }

 public:
  void Calc() {
    int w = 0, c[kMaxN] = {};
    for (int i = n; i >= 1; i--) {
      c[a[i]]++;
      for (; w <= n && c[w]; w++) {
      }
      s.insert({i, i, w});
    }
    for (int i = n; i >= 1; i--) {
      T t = *--s.end();
      s.erase(--s.end());
      if (t.l < t.r) {
        s.insert({t.l, t.r - 1, t.w});
      }
      auto p = Split(h[i]);
      if (p != s.end() && p->w > a[i]) {
        auto q = s.lower_bound({-1, -1, a[i]});
        for (auto j = p; j != q; j++) {
          o[i].push_back(*j);
        }
        int l = p->l, r = (--q)->r;
        s.erase(p, ++q), s.insert({l, r, a[i]});
      }
      o[i].push_back({i, i, t.w});
    }
  }
} e;

class V {
  struct P {
    int h[512], t[512];
    PLL d[kMaxN];
  } p[2];
  int n, w1[kMaxN], w2[512];

  void Pushdown(int x) {
    if (w2[x] <= 0) {
      fill(&w1[x << 9], &w1[min(x << 9 | 511, n)] + 1, w2[x]);
      w2[x] = 1;
    }
  }

  LLL Cross(PLL o, PLL x, PLL y) {
    x.first -= o.first, x.second -= o.second;
    y.first -= o.first, y.second -= o.second;
    return (LLL)x.first * y.second - (LLL)y.first * x.second;
  }

  void Pushup(int x) {
    int l = x << 9, r = min(l | 511, n);
    int &j = p[1].t[x] = l - 1;
    for (int i = l; i <= r; i++) {
      PLL d = {w1[i], f[i] + s[i] * w1[i]};
      for (; j > l && Cross(p[1].d[j - 1], p[1].d[j], d) >= 0; j--) {
        if (d.first == p[1].d[j].first) {
          d.second = max(d.second, p[1].d[j].second);
        }
      }
      p[1].d[++j] = d;
    }
    p[1].h[x] = p[1].t[x];
  }

 public:
  void Init() {
    n = p[0].h[0] = p[0].t[0] = 0;
    p[0].d[0] = {0, 0};
    fill(&w2[0], &w2[512], 1);
  }

  void Cover(int l, int r, int w) {
    int x = l >> 9, y = r >> 9;
    if (x == y) {
      Pushdown(x);
      fill(&w1[l], &w1[r] + 1, w);
      Pushup(x);
      return;
    }
    int _l = x << 9 | 511, _r = y << 9;
    Pushdown(x), Pushdown(y);
    fill(&w1[l], &w1[_l] + 1, w);
    fill(&w1[_r], &w1[r] + 1, w);
    Pushup(x), Pushup(y);
    for (int i = x + 1; i < y; i++) {
      int _i = i << 9, &j = p[0].h[i];
      w2[i] = p[1].d[_i].first = w;
      p[1].h[i] = p[1].t[i] = _i;
      for (; j > _i; j--) {
        PLL d = p[0].d[j] - p[0].d[j - 1];
        if (w * d.first + d.second >= 0) {
          break;
        }
      }
      p[1].d[_i].second = w * p[0].d[j].first + p[0].d[j].second;
    }
  }

  void Ask() {  // [n - m + 1, n]
    int _n = n + 1;
    int l = max(n - m + 1, 0), r = n;
    int x = l >> 9, y = r >> 9;
    if (x == y) {
      Pushdown(x), Pushup(x);
      for (int i = l; i <= r; i++) {
        f[_n] = max(f[_n], f[i] - w1[i] * (s[_n] - s[i]));
      }
      return;
    }
    int _l = x << 9 | 511, _r = y << 9;
    Pushdown(x), Pushup(x);
    Pushdown(y), Pushup(y);
    for (int i = l; i <= _l; i++) {
      f[_n] = max(f[_n], f[i] - w1[i] * (s[_n] - s[i]));
    }
    for (int i = _r; i <= r; i++) {
      f[_n] = max(f[_n], f[i] - w1[i] * (s[_n] - s[i]));
    }
    for (int i = x + 1; i < y; i++) {
      int _i = i << 9, &j = p[1].h[i];
      for (; j > _i; j--) {
        PLL d = p[1].d[j] - p[1].d[j - 1];
        if (d.second - s[_n] * d.first >= 0) {
          break;
        }
      }
      f[_n] = max(f[_n], p[1].d[j].second - s[_n] * p[1].d[j].first);
    }
  }

  void AddPoint() {
    int m = ++n >> 9, _m = m << 9, &i = p[0].t[m];
    PLL d = {s[n], f[n]};
    !(n & 511) && (i = _m - 1);
    for (; i > _m && Cross(p[0].d[i - 1], p[0].d[i], d) >= 0; i--) {
    }
    p[0].d[++i] = d, p[0].h[m] = i;
  }
} v;

void Input() {
  int d[kMaxN] = {};
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], h[i] = d[a[i]], d[a[i]] = i;
  }
}

void Compress() {
  vector<T> _o;
  for (int i = 1; i <= n; i++) {
    for (T j : o[i]) {
      if (_o.empty() || _o.back().r + 1 < j.l || _o.back().w > j.w) {
        _o.push_back(j);
      } else {
        _o.back().r = j.r;
      }
    }
    o[i] = _o, _o.clear();
  }
}

void CalcF() {
  v.Init();
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i];
    for (T j : o[i]) {
      v.Cover(j.l - 1, j.r - 1, -j.w);
    }
    v.Ask(), v.AddPoint();
  }
  cout << f[n] << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), e.Calc(), Compress(), CalcF();
  return 0;
}
