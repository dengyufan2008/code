#include <algorithm>
#include <fstream>
#include <vector>
#define PII pair<int, int>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 5e4 + 1, kMaxM = 513;
int n, m, h, w, a[kMaxN], ans[kMaxN];

class Seg {
  struct V {
    int c, l, r;
  } v[kMaxN * 18 * 18];
  int k, c[kMaxM], s[kMaxM][kMaxM];
  bool g[kMaxM][kMaxM];
  vector<int> d[kMaxM];

  void Insert(int &p, int l, int r, int x) {
    !p && (p = ++k);
    if (l == r) {
      v[p].c = 1;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Insert(v[p].l, l, mid, x);
    } else {
      Insert(v[p].r, mid + 1, r, x);
    }
    v[p].c = v[v[p].l].c + v[v[p].r].c;
  }

  int Size(int p, int l, int r, int x) {
    if (!p) {
      return 0;
    } else if (l >= x) {
      return v[p].c;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      return Size(v[p].l, l, mid, x) + v[v[p].r].c;
    } else {
      return Size(v[p].r, mid + 1, r, x);
    }
  }

  void Merge(int &p, int q, int l, int r) {
    if (!p || !q) {
      p |= q;
      return;
    }
    int mid = l + r >> 1;
    Merge(v[p].l, v[q].l, l, mid);
    Merge(v[p].r, v[q].r, mid + 1, r);
    v[p].c = v[v[p].l].c + v[v[p].r].c;
  }

  PII Split(int p, int l, int r, int x) {
    if (!p) {
      return {0, 0};
    } else if (l == r) {
      return l >= x ? PII{0, p} : PII{p, 0};
    }
    int mid = l + r >> 1;
    if (mid < x) {
      PII o = Split(v[p].r, mid + 1, r, x);
      v[p].r = o.first, v[p].c = v[v[p].l].c + v[v[p].r].c;
      k++, v[k].c = v[o.second].c, v[k].r = o.second;
      return {p, k};
    } else {
      PII o = Split(v[p].l, l, mid, x);
      v[p].l = o.second, v[p].c = v[v[p].l].c + v[v[p].r].c;
      k++, v[k].c = v[o.first].c, v[k].l = o.first;
      return {k, p};
    }
  }

  void Print(int p, int l, int r, int w) {
    if (!p) {
      return;
    } else if (l == r) {
      ans[l] = w;
      return;
    }
    int mid = l + r >> 1;
    Print(v[p].l, l, mid, w);
    Print(v[p].r, mid + 1, r, w);
  }

 public:
  void Insert(int b, int k, int x) {
    c[b]++, Insert(s[b][k], 1, n, x);
    if (!g[b][k]) {
      g[b][k] = 1, d[b].push_back(k);
    }
  }

  int Size(int b) { return c[b]; }

  int Size(int b, int x) {
    int ans = 0;
    for (int i : d[b]) {
      ans += Size(s[b][i], 1, n, x);
    }
    return ans;
  }

  /// @brief (k) \in [0, k) or (k) = k and (x) >= x: += b, else: = b
  void Move(int k, int x = -1) {
    static int _s[kMaxM][kMaxM];
    static bool _g[kMaxM][kMaxM];
    static vector<int> _d[kMaxM];
    for (int i = 0; i < k; i++) {
      for (int j : d[i]) {
        _s[i + j][j] = s[i][j];
        _g[i + j][j] = 1, _d[i + j].push_back(j);
      }
    }
    if (x == -1) {
      k--;
    } else {
      for (int i : d[k]) {
        PII o = Split(s[k][i], 1, n, x);
        _s[k + i][i] = o.second;
        _g[k + i][i] = 1, _d[k + i].push_back(i);
        Merge(_s[i][i], o.first, 1, n);
        if (!_g[i][i]) {
          _g[i][i] = 1, _d[i].push_back(i);
        }
      }
    }
    for (int i = k + 1; i < kMaxM; i++) {
      for (int j : d[i]) {
        Merge(_s[j][j], s[i][j], 1, n);
        if (!_g[j][j]) {
          _g[j][j] = 1, _d[j].push_back(j);
        }
      }
    }
    for (int i = 0; i < kMaxM; i++) {
      for (int j : d[i]) {
        s[i][j] = g[i][j] = 0;
      }
      d[i].swap(_d[i]), _d[i].clear();
      for (int j : d[i]) {
        s[i][j] = _s[i][j], _s[i][j] = 0;
        g[i][j] = _g[i][j], _g[i][j] = 0;
      }
      c[i] = 0;
      for (int j : d[i]) {
        c[i] += v[s[i][j]].c;
      }
    }
  }

  void Print() {
    for (int i = 0; i < kMaxM; i++) {
      for (int j : d[i]) {
        Print(s[i][j], 1, n, i);
      }
    }
  }
} seg;

void Solve() {
  if (m + a[n] < kMaxM) {
    seg.Insert(m + a[n], a[n], n), h = w = -1;
  } else {
    h = n, w = m + a[n];
  }
  for (int i = n - 1, j; i >= 1; i--) {
    int x = n - i >> 1, c = 0, s = 0;
    for (j = 0; c < x; j++) {
      if (c + seg.Size(j) <= x) {
        s += seg.Size(j) * j, c += seg.Size(j);
      } else {
        s += (x - c) * j;
        break;
      }
    }
    if (s <= m) {
      if (c == x) {
        seg.Move(j);
      } else {
        int l = 1, r = n;
        while (l <= r) {
          int mid = l + r >> 1;
          if (seg.Size(j, mid) <= x - c) {
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        seg.Move(j, l);
      }
      if (w != -1) {
        seg.Insert(a[h], a[h], h);
      }
      if (m - s + a[i] < kMaxM) {
        seg.Insert(m - s + a[i], a[i], i), h = w = -1;
      } else {
        h = i, w = m - s + a[i];
      }
    } else {
      seg.Insert(0, a[i], i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  Solve(), w != -1 && (ans[h] = w), seg.Print();
  for (int i = 1; i <= n; i++) {
    ans[i] = ans[i] == 0 ? -1 : ans[i] - a[i];
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}
