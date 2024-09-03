#include <iostream>
#include <vector>

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *is = ibuf + iL, *it = ibuf + iL;
#define Getchar() ((is == it) ? (it = (is = ibuf) + fread(ibuf, 1, iL, stdin), is == it ? EOF : *is++) : *is++)
template <class T>
inline void Read(T &x) {
  x = 0;
  int f = 0;
  char ch = Getchar();
  for (; !isdigit(ch); f |= ch == '-', ch = Getchar()) {
  }
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = Getchar()) {
  }
  x = (f == 1 ? ~x + 1 : x);
}
template <class T, class... Args>
inline void Read(T &x, Args &...args) { Read(x), Read(args...); }
template <class T>
inline void Readch(T &x) {
  char ch = Getchar();
  for (; !isalpha(ch); ch = Getchar()) {
  }
  x = ch;
}
char out[iL], *iter = out;
#define Flush() fwrite(out, 1, iter - out, stdout), iter = out
template <class T>
inline void Write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter++ = '-', x = ~x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10) {
  }
  for (; l; --l, *iter++ = c[l] + '0') {
  }
  *iter++ = ch;
  Flush();
}
template <class T, class... Args>
inline void Write(T x, Args... args) { Write(x, ' '), Write(args...); }
}  // namespace IO
using namespace IO;
using namespace std;

const int kMaxN = 1e6 + 1, kMaxL = 20;
struct E {
  int x, y;
} e[kMaxN];
struct V {
  int f, r, o;
  vector<int> e;
} v[kMaxN];
int t, n, k, a[kMaxN], ans[kMaxN];

struct LCA {
  int d[kMaxL][kMaxN], lg[kMaxN];

  void CalcLg() {
    for (int i = 2; i < kMaxN; i++) {
      lg[i] = lg[i >> 1] + 1;
    }
  }

  void Init() {
    for (int i = 1; i <= n; i++) {
      d[0][v[i].r] = v[v[i].f].r;
    }
    for (int i = 1; i < kMaxL; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = d[i - 1][j];
        if (j + (1 << i - 1) <= n) {
          d[i][j] = min(d[i][j], d[i - 1][j + (1 << i - 1)]);
        }
      }
    }
  }

  int Ask(int x, int y) {
    x = v[x].r, y = v[y].r;
    x > y ? swap(x, y) : void();
    int l = lg[y - x];
    int r = min(d[l][x + 1], d[l][y - (1 << l) + 1]);
    return a[r];
  }
} lca;

struct Set {
  int f[kMaxN];

  void Init() {
    for (int i = 1; i <= n; i++) {
      f[i] = i;
    }
  }

  int GetRoot(int x) {
    return f[x] == x ? x : f[x] = GetRoot(f[x]);
  }

  void Merge(int x, int y) {
    x = GetRoot(x), y = GetRoot(y);
    x != y && (f[x] = y);
  }
} set;

void T(int f, int x) {
  v[x].f = f, v[x].r = ++k, a[k] = x;
  for (auto i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
}

int main() {
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  lca.CalcLg(), Read(t);
  while (t--) {
    k = 0;
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    Read(n);
    for (int i = 1, x, y; i < n; i++) {
      Read(x, y), e[i] = {x, y};
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    T(0, 1), lca.Init(), set.Init();
    for (int i = 1; i < n; i++) {
      if (v[e[i].x].r < v[e[i].y].r) {
        v[e[i].y].o = i;
      } else {
        v[e[i].x].o = i;
      }
    }
    for (int i = n / 2; i >= 1; i--) {
      int mn = i, mx = i;
      for (int j = i + i; j <= n; j += i) {
        if (v[j].r < v[mn].r) {
          mn = j;
        }
        if (v[j].r > v[mx].r) {
          mx = j;
        }
      }
      int x = lca.Ask(mn, mx);
      for (int j = i; j <= n; j += i) {
        for (int y = set.GetRoot(j); v[y].r > v[x].r; y = set.GetRoot(v[y].f)) {
          ans[v[y].o] = i, set.Merge(y, v[y].f);
        }
      }
    }
    for (int i = 1; i < n; i++) {
      Write(ans[i], " \n"[i == n - 1]);
    }
  }
  return 0;
}
