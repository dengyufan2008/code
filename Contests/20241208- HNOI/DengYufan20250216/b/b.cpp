#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMaxL = 17;
int n, lg[kMaxN];
LL ans;
string s;

class SA {
  int a[kMaxN], r[kMaxN], h[kMaxL][kMaxN];
  string s;
  bool u;

  void CalcSA() {
    static int b[kMaxN], c[kMaxN];
    for (int i = 1; i <= n; i++) {
      a[i] = i;
    }
    sort(a + 1, a + n + 1, [&](int i, int j) {
      return s[i] < s[j];
    });
    for (int i = 1; i <= n; i++) {
      r[a[i]] = r[a[i - 1]] + (s[a[i]] != s[a[i - 1]]);
    }
    for (int g = 1; g < n; g <<= 1) {
      for (int i = 1; i <= g; i++) {
        b[i] = n - g + i;
      }
      for (int i = 1, j = g; i <= n; i++) {
        if (a[i] > g) {
          b[++j] = a[i] - g;
        }
      }
      for (int i = 1; i <= n; i++) {
        c[i] = 0;
      }
      for (int i = 1; i <= n; i++) {
        c[r[i]]++;
      }
      for (int i = 1; i <= n; i++) {
        c[i] += c[i - 1];
      }
      for (int i = n; i >= 1; i--) {
        a[c[r[b[i]]]--] = b[i];
      }
      for (int i = 1; i <= n; i++) {
        b[a[i]] = b[a[i - 1]];
        if (r[a[i]] != r[a[i - 1]]) {
          b[a[i]]++;
        } else if (min(a[i], a[i - 1]) + g <= n) {
          if (max(a[i], a[i - 1]) + g > n) {
            b[a[i]]++;
          } else if (r[a[i] + g] != r[a[i - 1] + g]) {
            b[a[i]]++;
          }
        }
      }
      for (int i = 1; i <= n; i++) {
        r[i] = b[i];
      }
    }
  }

  void CalcH() {
    int *g = h[0];
    for (int i = 1; i <= n; i++) {
      if (r[i] < n) {
        g[r[i]] = max(g[r[i - 1]] - 1, 0);
        for (int &j = g[r[i]]; s[i + j] == s[a[r[i] + 1] + j]; j++) {
        }
      }
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j + (1 << i) - 1 < n; j++) {
        h[i][j] = min(h[i - 1][j], h[i - 1][j + (1 << i - 1)]);
      }
    }
  }

 public:
  /// @param _u 0:求 lcp  1:求 lcs
  void Init(string _s, bool _u) {
    s = _s, u = _u;
    if (u) {
      reverse(s.begin(), s.end());
      s.pop_back(), s = '~' + s;
    }
    CalcSA(), CalcH();
  }

  int Ask(int x, int y) {
    if (u) {
      x = n - x + 1, y = n - y + 1;
    }
    if (x < 1 || y < 1 || x > n || y > n) {
      return 0;
    } else if (x == y) {
      return n - x + 1;
    } else {
      x = r[x], y = r[y];
      x > y ? swap(x, y) : void();
      int o = lg[y - x];
      return min(h[o][x], h[o][y - (1 << o)]);
    }
  }
} lcp, lcs;

class Seg {
  struct V {
    LL s;         // 和
    int t1;       // 加法标记
    int t2 = -1;  // 覆盖标记
  } v[kMaxN << 2];
  int n;

  void Tag1(int p, int l, int r, int t) {
    v[p].s += 1LL * (r - l + 1) * t, v[p].t1 += t;
    if (v[p].t2 != -1) {
      v[p].t2 += t;
    }
  }

  void Tag2(int p, int l, int r, int t) {
    v[p].s = 1LL * (r - l + 1) * t;
    v[p].t1 = 0, v[p].t2 = t;
  }

  void Pushdown(int p, int l, int r) {
    int mid = l + r >> 1;
    if (v[p].t1) {
      Tag1(p << 1, l, mid, v[p].t1);
      Tag1(p << 1 | 1, mid + 1, r, v[p].t1);
      v[p].t1 = 0;
    }
    if (v[p].t2 != -1) {
      Tag2(p << 1, l, mid, v[p].t2);
      Tag2(p << 1 | 1, mid + 1, r, v[p].t2);
      v[p].t2 = -1;
    }
  }

  void Clear(int p, int l, int r, int _l, int _r) {
    if (l >= _l && r <= _r) {
      return Tag2(p, l, r, 0);
    }
    Pushdown(p, l, r);
    int mid = l + r >> 1;
    if (mid >= _l) {
      Clear(p << 1, l, mid, _l, _r);
    }
    if (mid < _r) {
      Clear(p << 1 | 1, mid + 1, r, _l, _r);
    }
    v[p].s = v[p << 1].s + v[p << 1 | 1].s;
  }

 public:
  void Init(int _n) { n = _n; }
  void Add() { Tag1(1, 1, n, 1); }
  void Clear(int l, int r) { Clear(1, 1, n, l, r); }
  LL Sum() { return v[1].s; }
} seg;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  cin >> s, n = s.size(), s = '~' + s;
  lcp.Init(s, 0), lcs.Init(s, 1);
  for (int g = 2; g << 1 <= n; g++) {
    seg.Init(g), seg.Clear(1, g);
    for (int i = g; i + g <= n; i += g) {
      static vector<pair<int, int>> v;
      v.clear(), seg.Add();
      int l1 = min(lcs.Ask(i, i + g), g);
      int l2 = min(l1 + 1 + lcs.Ask(i - l1 - 1, i + g - l1 - 1), g);
      int r1 = min(lcp.Ask(i + 1, i + g + 1), min(g - 1, n - i - g));
      int r2 = i + g >= n ? 0 : min(r1 + 1 + lcp.Ask(i + r1 + 2, i + g + r1 + 2), min(g - 1, n - i - g));
      if (l1 + r2 >= g) {
        v.push_back({i + g - l1 + 1, i + r2 + 1});
      }
      if (l2 + r1 >= g) {
        v.push_back({i + g - l2 + 1, i + r1 + 1});
      }
      if (v.empty()) {
        seg.Clear(1, g);
        continue;
      }
      if (v.front() > v.back()) {
        swap(v.front(), v.back());
      }
      if (v.size() == 2 && v.front().second + 1 >= v.back().first) {
        v.front().second = v.back().second, v.pop_back();
      }
      if (v.front().first > i + 1) {
        seg.Clear(1, v.front().first - i - 1);
      }
      if (v.back().second < i + g) {
        seg.Clear(v.back().second - i + 1, g);
      }
      if (v.size() == 2) {
        seg.Clear(v.front().second - i + 1, v.back().first - i - 1);
      }
      ans += seg.Sum();
    }
  }
  cout << ans << '\n';
  return 0;
}
