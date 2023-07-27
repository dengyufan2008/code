#include <algorithm>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>
#define max(x, y) ((x) < (y) ? (y) : (x))

using namespace std;

const int kMaxN = 1e6 + 1;
struct E {
  int x, y, w;
} e[kMaxN];
struct EV {
  int p, d, w;
} ev[kMaxN << 1];
struct V {
  int et, w, f, s, ms, ans;
  bool b;
  // vector<pair<int, int>> e;
} v[kMaxN];
int t, n, r, s, a[kMaxN], l[kMaxN], d[2][kMaxN << 2];

inline void Add(int p, int l, int r, int x, int k, bool b) {
  if (l == r) {
    d[0][p] += k;
    if (b) {
      d[1][p] -= k;
    }
    return;
  }
  int mid(l + r >> 1);
  mid >= x ? Add(p << 1, l, mid, x, k, b) : Add(p << 1 | 1, mid + 1, r, x, k, b);
  d[0][p] = max(d[0][p << 1], d[0][p << 1 | 1]), d[1][p] = max(d[1][p << 1], d[1][p << 1 | 1]);
}

inline int Ask(int p, int l, int r, int k) {
  if (l == r) {
    return d[0][p] >= k || d[1][p] >= k ? a[l] : 0;
  }
  int mid(l + r >> 1);
  if (d[0][p << 1 | 1] >= k || d[1][p << 1 | 1] >= k) {
    return Ask(p << 1 | 1, mid + 1, r, k);
  } else if (d[0][p << 1] >= k || d[1][p << 1] >= k) {
    return Ask(p << 1, l, mid, k);
  }
  return 0;
}

inline void CalcF(int f, int x) {
  v[x].f = f, Add(1, 1, n, v[x].w, 1, 0);
  for (int i(v[x].et); i; i = ev[i].p) {
    if (ev[i].d != f) {
      CalcF(x, ev[i].d);
    }
  }
}

inline void CalcR(int f, int x) {
  v[x].s = 1, v[x].ms = 0;
  for (int i(v[x].et); i; i = ev[i].p) {
    if (ev[i].d != f && !v[ev[i].d].b) {
      CalcR(x, ev[i].d);
      v[x].s += v[ev[i].d].s, v[x].ms = max(v[x].ms, v[ev[i].d].s);
    }
  }
  if (v[x].ms <= s / 2 && s - v[x].s <= s / 2) {
    r = x;
  }
}

inline void Record(int f, int x, int k) {
  Add(1, 1, n, v[x].w, k, 1);
  for (int i(v[x].et); i; i = ev[i].p) {
    if (ev[i].d != f && !v[ev[i].d].b) {
      Record(x, ev[i].d, k);
    }
  }
}

inline void Divide(int x) {
  for (int i(v[x].et); i; i = ev[i].p) {
    if (!v[ev[i].d].b) {
      Record(x, ev[i].d, -1);
      if (v[ev[i].d].f == x) {
        v[ev[i].d].ans = Ask(1, 1, n, ev[i].w);
      } else {
        v[x].ans = Ask(1, 1, n, ev[i].w);
      }
      Record(x, ev[i].d, 1);
    }
  }
  v[x].b = 1;
  for (int i(v[x].et); i; i = ev[i].p) {
    if (!v[ev[i].d].b) {
      s = v[ev[i].d].s, CalcR(x, ev[i].d), CalcR(x, r), Divide(r);
    }
  }
}

inline void Read(int &x) {
  int c = getchar();
  x = 0;
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
}

int main() {
  // freopen("shit.in", "r", stdin);
  // freopen("shit.out", "w", stdout);

  int size(512 << 20);  // 512M
  __asm__("movq %0, %%rsp\n" ::"r"((char *)malloc(size) + size));

  // cin.tie(0), cout.tie(0);
  // ios::sync_with_stdio(0);
  Read(t);
  // cin >> t;
  while (t--) {
    Read(n);
    // cin >> n;
    for (int i(1); i <= n; ++i) {
      Read(a[i]);
      // cin >> a[i];
    }
    for (int i(1); i <= n; ++i) {
      l[i] = i;
    }
    for (int i(1); i <= n; ++i) {
      v[i].b = 0;
    }
    for (int i(1); i <= n; ++i) {
      // v[i].e.clear();
      v[i].et = 0;
    }
    sort(l + 1, l + n + 1, [](int i, int j) { return a[i] < a[j]; });
    for (int i(1); i <= n; ++i) {
      v[l[i]].w = v[l[i - 1]].w + (a[l[i]] != a[l[i - 1]]);
    }
    sort(a + 1, a + n + 1), unique(a + 1, a + n + 1);
    for (int i(1); i < n; ++i) {
      Read(e[i].x), Read(e[i].y), Read(e[i].w);
      // cin >> e[i].x >> e[i].y >> e[i].w;
      // v[e[i].x].e.push_back((pair<int, int>){e[i].y, e[i].w});
      // v[e[i].y].e.push_back((pair<int, int>){e[i].x, e[i].w});
      ev[i << 1] = {v[e[i].x].et, e[i].y, e[i].w}, v[e[i].x].et = i << 1;
      ev[i << 1 | 1] = {v[e[i].y].et, e[i].x, e[i].w}, v[e[i].y].et = i << 1 | 1;
    }
    CalcF(0, 1), s = n, CalcR(0, 1), CalcR(0, r), Divide(r), Add(1, 1, n, v[n].w, -1, 0);
    for (int i(1); i < n; ++i) {
      Add(1, 1, n, v[i].w, -1, 0);
      if (v[e[i].x].f == e[i].y) {
        // Print(v[e[i].x].ans), putchar(10);
        printf("%d\n", v[e[i].x].ans);
        // cout << v[e[i].x].ans << '\n';
      } else {
        // Print(v[e[i].y].ans), putchar(10);
        printf("%d\n", v[e[i].y].ans);
        // cout << v[e[i].y].ans << '\n';
      }
    }
  }

  // cerr << clock();

  exit(0);
}
