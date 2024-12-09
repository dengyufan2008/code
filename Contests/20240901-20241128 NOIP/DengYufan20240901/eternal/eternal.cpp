#include <iostream>

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

const int kMaxN = 1e6 + 1, kMaxL = 20, kInf = 1e9;
struct W {
  int l, r, s;
} e[kMaxN];
struct V {
  int s, c = -1;
} v[kMaxN << 2];
int n, m, k, t, a[kMaxN], b[kMaxN], d[kMaxL][kMaxN], lg[kMaxN], ans[kMaxN];

int Max(int l, int r) {
  int o = lg[r - l + 1];
  int x = d[o][l], y = d[o][r - (1 << o) + 1];
  return a[x] < a[y] ? y : x;
}

void Pushdown(int p) {
  if (v[p].c != -1) {
    v[p << 1].c = v[p << 1 | 1].c = v[p].c, v[p].c = -1;
  }
}

void Build(int p, int l, int r) {
  if (l == r) {
    v[p].s = b[l], v[p].c = 1, e[1].s |= b[l];
    return;
  }
  int mid = l + r >> 1;
  Build(p << 1, l, mid);
  Build(p << 1 | 1, mid + 1, r);
  v[p].s = v[p << 1].s | v[p << 1 | 1].s;
}

int Tag(int p, int l, int r, int _l, int _r, int t) {
  if (l >= _l && r <= _r) {
    return v[p].c = t, v[p].s;
  }
  Pushdown(p);
  int mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    ans |= Tag(p << 1, l, mid, _l, _r, t);
  }
  if (mid < _r) {
    ans |= Tag(p << 1 | 1, mid + 1, r, _l, _r, t);
  }
  return ans;
}

int Or(int p, int l, int r, int x, int s) {
  if (l == r) {
    v[p].s |= s, e[v[p].c].s |= s;
    return v[p].c;
  }
  Pushdown(p);
  int mid = l + r >> 1, ans;
  if (mid >= x) {
    ans = Or(p << 1, l, mid, x, s);
  } else {
    ans = Or(p << 1 | 1, mid + 1, r, x, s);
  }
  v[p].s = v[p << 1].s | v[p << 1 | 1].s;
  return ans;
}

void Contribute(int p) {
  int l = e[p].l, r = e[p].r;
  if (l && r && e[p].s >= k) {
    int x = Max(l, r);
    for (int i = r - l + 1; i >= 1; i -= i & -i) {
      ans[i] = min(ans[i], a[x]);
    }
    Tag(1, 1, n, x, x, 0);
    if (l < x && r > x) {
      t++;
      e[p] = {l, x - 1, Tag(1, 1, n, l, x - 1, p)};
      e[t] = {x + 1, r, Tag(1, 1, n, x + 1, r, t)};
      Contribute(p), Contribute(t);
    } else if (e[p].l < x) {
      e[p] = {l, x - 1, Tag(1, 1, n, l, x - 1, p)};
      Contribute(p);
    } else if (e[p].r > x) {
      e[p] = {x + 1, r, Tag(1, 1, n, x + 1, r, p)};
      Contribute(p);
    } else {
      e[p] = e[0];
    }
  }
}

void Or(int x, int s) { Contribute(Or(1, 1, n, x, s)); }

int main() {
  freopen("eternal.in", "r", stdin);
  freopen("eternal.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 2; i < kMaxN; i++) {
    lg[i] = lg[i >> 1] + 1;
  }
  Read(n, m, k);
  for (int i = 1; i <= n; i++) {
    Read(a[i]), d[0][i] = i, ans[i] = kInf;
  }
  for (int i = 1; i < kMaxL; i++) {
    for (int j = 1; j <= n; j++) {
      d[i][j] = d[i - 1][j];
      if (j + (1 << i - 1) <= n) {
        if (a[d[i][j]] < a[d[i - 1][j + (1 << i - 1)]]) {
          d[i][j] = d[i - 1][j + (1 << i - 1)];
        }
      }
    }
  }
  t = 1, e[1] = {1, n, 0};
  Tag(1, 1, n, 1, n, 1);
  for (int i = 1, x; i <= n; i++) {
    Read(x), Or(i, x);
  }
  for (int i = 1, o, x, y; i <= m; i++) {
    Read(o, x);
    if (o == 1) {
      Read(y), Or(x, y);
    } else {
      int w = kInf;
      for (int j = x; j <= n; j += j & -j) {
        w = min(w, ans[j]);
      }
      Write(w == kInf ? -1 : w);
    }
  }
  return 0;
}
