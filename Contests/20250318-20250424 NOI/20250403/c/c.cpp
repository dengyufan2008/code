#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5 + 2, kMaxL = 18;
int t, n, m;
vector<pair<int, int>> v[kMaxN];

class A {
  int nt[kMaxL][kMaxN];  // 左端点大于 i 的最小的右端点
  vector<pair<int, int>> a;

 public:
  void Clear() { a.clear(); }
  void Insert(int x, int y) { a.push_back({x, y}); }

  void Init() {
    sort(a.begin(), a.end(), [](pair<int, int> i, pair<int, int> j) {
      return i.first > j.first;
    });
    nt[0][m + 1] = m + 1;
    for (int i = m, j = 0, k = m + 1; i >= 0; i--) {
      for (; j < a.size() && a[j].first > i; j++) {
        k = min(k, a[j].second);
      }
      nt[0][i] = k;
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 0; j <= m + 1; j++) {
        nt[i][j] = nt[i - 1][nt[i - 1][j]];
      }
    }
  }

  int Next(int x) { return nt[0][x]; }

  // 0 \le l \le r \le m
  pair<int, int> Ask(int l, int r) {
    int ans = 0;
    for (int i = kMaxL - 1; i >= 0; i--) {
      if (nt[i][l] <= r) {
        l = nt[i][l], ans |= 1 << i;
      }
    }
    return {ans, l};
  }
} a1, a2;

void Input() {
  static int d[kMaxN], p[kMaxN], l[kMaxN], w[kMaxN];
  cin >> n;
  for (int i = 1, o, x, y; i <= n; i++) {
    cin >> o >> x >> y;
    if (o == 3) {
      cin >> w[i];
    } else {
      w[i] = o - 2;
    }
    d[i * 2 - 1] = x, d[i * 2] = y + 1;
    l[i * 2 - 1] = i * 2 - 1, l[i * 2] = i * 2;
  }
  sort(l + 1, l + n * 2 + 1, [](int i, int j) {
    return d[i] < d[j];
  });
  for (int i = 1; i <= n * 2; i++) {
    p[l[i]] = p[l[i - 1]] + (d[l[i - 1]] < d[l[i]]);
  }
  m = 0;
  for (int i = 1; i <= n; i++) {
    if (w[i] == -1) {
      a1.Insert(p[i * 2 - 1], p[i * 2] - 1);
    } else if (w[i] == 0) {
      a2.Insert(p[i * 2 - 1], p[i * 2] - 1);
    } else {
      v[p[i * 2] - 1].push_back({p[i * 2 - 1], w[i]});
    }
    m = max(m, max(p[i * 2 - 1], p[i * 2] - 1));
  }
}

LL Dp() {
  struct H {
    LL w;
    int p;
    bool operator<(const H &h) const {
      return w < h.w || w == h.w && p > h.p;
    }
  };
  static H f[kMaxN], g[kMaxN];
  for (int i = 0; i <= m; i++) {
    if (i) {
      f[i] = max(f[i], f[i - 1]);
      g[i] = max(g[i], g[i - 1]);
    }

    H h = {0, 0};
    for (auto j : v[i]) {
      h = max(h, H{max(f[j.first - 1].w, g[j.first - 1].w) + j.second, i});
    }
    f[i] = max(f[i], h), g[i] = max(g[i], h);
    v[i].clear();

    static int nt;

    nt = a1.Next(i);
    if (nt <= m) {
      auto w = a2.Ask(f[i].p, nt);
      f[nt] = max(f[nt], H{f[i].w + w.first + 1, w.second});
    }

    nt = a1.Next(g[i].p);
    if (nt <= m && i < nt) {
      auto w = a2.Ask(i, nt);
      f[nt] = max(f[nt], H{g[i].w + w.first + 1, w.second});
    }

    nt = a2.Next(i);
    if (nt <= m) {
      auto w = a1.Ask(g[i].p, nt);
      g[nt] = max(g[nt], H{g[i].w + w.first + 1, w.second});
    }

    nt = a2.Next(f[i].p);
    if (nt <= m && i < nt) {
      auto w = a1.Ask(i, nt);
      g[nt] = max(g[nt], H{f[i].w + w.first + 1, w.second});
    }
  }
  LL ans = 0;
  for (int i = 1; i <= m; i++) {
    ans = max(ans, max(f[i].w, g[i].w));
    f[i] = g[i] = {0, 0};
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    a1.Clear(), a2.Clear();
    Input();
    a1.Init(), a2.Init();
    cout << Dp() << '\n';
  }
  return 0;
}
