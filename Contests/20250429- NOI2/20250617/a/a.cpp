#include <algorithm>
#include <iostream>
#define LL long long

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
using IO::Read;
using IO::Write;
using namespace std;

const int kMaxN = 2e5 + 1, kMaxL = 18;
int n, m, a[kMaxN], b[kMaxN], d[kMaxL][kMaxN];

class Seg {
  struct V {
    int l, r, c;
    LL s;
  } v[kMaxN * 20];
  int k, s[kMaxN], w[kMaxN];

  void Change(int &p, int l, int r, int x, int w) {
    v[++k] = v[p], p = k;
    if (l == r) {
      v[p].c = 1, v[p].s = w;
      return;
    }
    int mid = l + r >> 1;
    if (mid >= x) {
      Change(v[p].l, l, mid, x, w);
    } else {
      Change(v[p].r, mid + 1, r, x, w);
    }
    v[p].c = v[v[p].l].c + v[v[p].r].c;
    v[p].s = v[v[p].l].s + v[v[p].r].s;
  }

  pair<int, LL> Find(int p, int q, int l, int r, int c, LL s) {
    if (l == r) {
      return {c + v[q].c - v[p].c, s + v[q].s - v[p].s};
    }
    int mid = l + r >> 1;
    int _c = c + v[v[q].l].c - v[v[p].l].c;
    LL _s = s + v[v[q].l].s - v[v[p].l].s;
    if (1LL * _c * w[mid + 1] <= _s) {
      return Find(v[p].r, v[q].r, mid + 1, r, _c, _s);
    } else {
      return Find(v[p].l, v[q].l, l, mid, c, s);
    }
  }

 public:
  void Init(int *_w) {
    static int o[kMaxN], l[kMaxN];
    for (int i = 1; i <= n; i++) {
      l[i] = i;
    }
    sort(l + 1, l + n + 1, [&](int i, int j) {
      return _w[i] < _w[j];
    });
    for (int i = 1; i <= n; i++) {
      o[l[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
      w[i] = _w[l[i]];
      Change(s[i] = s[i - 1], 1, n, o[i], _w[i]);
    }
  }

  pair<int, LL> Find(int t1, int t2) {
    return Find(s[t1], s[t2], 1, n, t1 - t2 >> 1, 0);
  }
} seg1, seg2;

int Min(int l, int r) {
  int o = __lg(r - l + 1);
  return min(d[o][l], d[o][r - (1 << o) + 1]);
}

int main() {
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  Read(n, m);
  for (int i = 1; i <= n; i++) {
    Read(a[i]);
  }
  for (int i = 1; i <= n; i++) {
    Read(b[i]);
  }
  for (int i = 1; i <= n; i++) {
    d[0][i] = a[i] + b[i];
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      d[i][j] = d[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        d[i][j] = min(d[i][j], d[i - 1][j + (1 << i - 1)]);
      }
    }
  }
  seg1.Init(a), seg2.Init(b);
  for (int i = 1, x, y; i <= m; i++) {
    static pair<int, LL> f1, f2;
    Read(x, y), x++, y++;
    f1 = seg1.Find(x - 1, y), f2 = seg2.Find(x - 1, y);
    f1.second /= f1.first, f2.second /= f2.first;
    cout << min((LL)Min(x, y), min(f1.second, f2.second)) << '\n';
  }
  return 0;
}
