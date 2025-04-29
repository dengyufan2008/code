#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 5002;
struct E {
  int xl, xr, yl, yr;
};
int n, m, a[kMaxN][kMaxN];
vector<E> e;

class Seg {
  struct V {
    int w, p;
  } v[kMaxN << 2];
  int t, f[kMaxN][kMaxN];

  int GetRoot(int *f, int x) {
    return f[x] == x ? x : f[x] = GetRoot(f, f[x]);
  }

  void Init(int p, int l, int r) {
    if (l == r) {
      v[p] = {f[l][t], l};
      return;
    }
    int mid = l + r >> 1;
    Init(p << 1, l, mid);
    Init(p << 1 | 1, mid + 1, r);
    v[p] = v[p << 1].w >= v[p << 1 | 1].w ? v[p << 1] : v[p << 1 | 1];
  }

  V Ask(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return v[p];
    }
    int mid = l + r >> 1;
    if (mid >= _l && mid < _r) {
      V x = Ask(p << 1, l, mid, _l, _r);
      V y = Ask(p << 1 | 1, mid + 1, r, _l, _r);
      return x.w >= y.w ? x : y;
    } else if (mid >= _l) {
      return Ask(p << 1, l, mid, _l, _r);
    } else {
      return Ask(p << 1 | 1, mid + 1, r, _l, _r);
    }
  }

  void Change(int p, int l, int r, int x, int w) {
    if (l == r) {
      v[p].w = w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(p << 1, l, mid, x, w);
    } else {
      Change(p << 1 | 1, mid + 1, r, x, w);
    }
    v[p] = v[p << 1].w >= v[p << 1 | 1].w ? v[p << 1] : v[p << 1 | 1];
  }

 public:
  void Forward() {
    t++;
    for (int i = 1; i <= m; i++) {
      if (a[t][i]) {
        f[i][t] = t;
      } else {
        f[i][t] = GetRoot(f[i], t - 1);
      }
    }
    Init(1, 1, m);
  }

  V Ask(int l, int r) { return Ask(1, 1, m, l, r); }

  void Merge(int x) {
    int y = GetRoot(f[x], t);
    f[x][y] = GetRoot(f[x], y - 1);
    Change(1, 1, m, x, f[x][y]);
  }
} seg;

void CalcE() {
  static int s[kMaxN], d[kMaxN], pr[kMaxN], nt[kMaxN];
  static vector<int> v;
  static vector<pair<int, int>> g[kMaxN];
  for (int j = 0; j <= m + 1; j++) {
    d[j] = n + 1, g[j].push_back({n + 1, m + 1});
  }
  for (int i = n; i >= 1; i--) {
    for (int j = m, p = m + 1; j >= 0; j--) {
      for (; !g[j].empty() && g[j].back().second <= p; g[j].pop_back()) {
      }
      g[j].push_back({i, p});
      a[i][j] && (p = j, d[j] = i);
    }
    for (int j = 1; j <= m; j++) {
      s[j] = s[j - 1] + a[i - 1][j];
    }
    v.clear();
    for (int j = 1; j <= m; j++) {
      for (; !v.empty() && d[v.back()] <= d[j]; v.pop_back()) {
      }
      pr[j] = v.empty() ? 0 : v.back();
      v.push_back(j);
    }
    v.clear();
    for (int j = m; j >= 1; j--) {
      for (; !v.empty() && d[v.back()] < d[j]; v.pop_back()) {
      }
      nt[j] = v.empty() ? m + 1 : v.back();
      v.push_back(j);
    }
    for (int j = 1; j <= m; j++) {
      if (d[j] < min(d[pr[j]], d[nt[j]]) && (i == 1 || s[pr[j]] == s[nt[j] - 1])) {
        int l = 0, r = g[pr[j]].size() - 1;
        while (l <= r) {
          int mid = l + r >> 1;
          auto &_g = g[pr[j]][mid];
          if (_g.first > d[j] && _g.second >= nt[j]) {
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }
        if (r >= 0) {
          auto &_g = g[pr[j]][r];
          if (_g.first <= min(d[pr[j]], d[nt[j]])) {
            e.push_back({i, _g.first - 1, pr[j] + 1, nt[j] - 1});
          }
        }
      }
    }
  }
}

void Sort() {
  // for (int i = 1; i < e.size(); i++) {  // CHICK
  //   if (e[i - 1].xl < e[i].xl) {
  //     cout << "shit\n";
  //   }
  // }
  static vector<E> _e, v[kMaxN];
  for (E i : e) {
    v[i.yr - i.yl + 1].push_back(i);
  }
  for (int i = 1; i <= m; i++) {
    for (E j : v[i]) {
      _e.push_back(j);
    }
    v[i].clear();
  }
  e.swap(_e), _e.clear();
  for (E i : e) {
    v[i.xr].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    for (E j : v[i]) {
      _e.push_back(j);
    }
    v[i].clear();
  }
  e.swap(_e), _e.clear();
}

void CalcAns() {
  long long ans = 0;
  static vector<E> _e;
  for (E i : e) {  // 小卡常
    if (i.xl == i.xr || i.yl == i.yr) {
      int s = (i.xr - i.xl + 1) * (i.yr - i.yl + 1);
      for (int j = i.xl; j <= i.xr; j++) {
        for (int k = i.yl; k <= i.yr; k++) {
          if (a[j][k]) {
            a[j][k] = 0, ans += s;
          }
        }
      }
    } else {
      _e.push_back(i);
    }
  }
  e.swap(_e), _e.clear(), Sort();
  for (int i = 1, j = 0; i <= n; i++) {
    seg.Forward();
    for (; j < e.size() && e[j].xr == i; j++) {
      int s = (e[j].xr - e[j].xl + 1) * (e[j].yr - e[j].yl + 1);
      while (1) {
        auto x = seg.Ask(e[j].yl, e[j].yr);
        if (x.w < e[j].xl) {
          break;
        }
        seg.Merge(x.p), ans += s;
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      static char c;
      cin >> c, a[i][j] = c == '0';
    }
  }
  CalcE(), CalcAns();
  return 0;
}
