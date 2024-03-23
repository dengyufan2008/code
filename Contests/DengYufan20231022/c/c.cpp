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

const int kMaxN = 2002, kMaxM = 5e5 + 1, kMod = 1e9 + 7;
struct V {
  int l[kMaxN], r[kMaxN], d[kMaxN];

  void Clear(int n, int x) {
    r[0] = 1, l[n + 1] = n;
    for (int i = 1; i <= n; i++) {
      l[i] = i - 1, r[i] = i + 1, d[i] = x;
    }
  }

  int GetLeft(int x) {
    return l[r[x]] == x ? x : l[x] = GetLeft(l[x]);
  }

  int GetRight(int x, int y, int k) {
    if (x > y) {
      return x;
    }
    l[r[x]] = l[x], d[x] = k;
    return r[x] = GetRight(r[x], y, k);
  }

  void Change(int x, int y, int k) {
    GetLeft(x), r[l[x]] = GetRight(r[l[x]], y, k);
  }
} v1[kMaxN], v2[kMaxN];
struct H {
  struct A {
    int d, w, b;
  } a[kMaxN];
  int h, t, c[kMaxN];

  void Clear(int n) {
    h = 1, t = 0;
    for (int i = 0; i <= n; i++) {
      c[i] = 0;
    }
  }

  void Insert(int d, int w, int b) {
    for (; h <= t && a[t].d < d; t--) {
      c[a[t].d] = (c[a[t].d] - a[t].w + kMod) % kMod;
    }
    a[++t] = {d, w, b}, c[d] = (c[d] + w) % kMod;
  }

  int Top(int b) {
    for (; h <= t && a[h].b < b; h++) {
      c[a[h].d] = (c[a[h].d] - a[h].w + kMod) % kMod;
    }
    return h <= t ? a[h].d : 0;
  }

  int Count(int d) {
    return c[d];
  }
} r, c[kMaxN];
struct A {
  int x1, y1, x2, y2;
} a[kMaxM];
int o, n, m, q, ans1, ans2, l1[kMaxM], l2[kMaxM],
    s[kMaxN][kMaxN], t[kMaxN][kMaxN], f[kMaxN][kMaxN], g[kMaxN][kMaxN];

void Input() {
  Read(n, m, q);
  for (int i = 1; i <= q; i++) {
    Read(a[i].x1, a[i].y1, a[i].x2, a[i].y2);
  }
}

void Sort() {
  int c1[kMaxN] = {}, c2[kMaxN] = {};
  for (int i = 1; i <= q; i++) {
    c1[a[i].y1]++, c2[a[i].x1]++;
  }
  for (int i = 1; i <= m; i++) {
    c1[i] += c1[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    c2[i] += c2[i - 1];
  }
  for (int i = q; i >= 1; i--) {
    l1[c1[a[i].y1]--] = i, l2[c2[a[i].x1]--] = i;
  }
}

void CalcST() {
  for (int i = 1; i <= m; i++) {
    v1[i].Clear(n, i);
  }
  for (int i = 1; i <= n; i++) {
    v2[i].Clear(m, i);
  }
  for (int i = 1; i <= q; i++) {
    v1[a[l1[i]].y2].Change(a[l1[i]].x1 + 1, a[l1[i]].x2, a[l1[i]].y1);
    v2[a[l2[i]].x2].Change(a[l2[i]].y1 + 1, a[l2[i]].y2, a[l2[i]].x1);
  }
  for (int i = 1; i <= n; i++) {
    s[i][m] = v1[m].d[i];
    for (int j = m - 1; j >= 1; j--) {
      s[i][j] = min(v1[j].d[i], s[i][j + 1]);
    }
  }
  for (int i = 1; i <= m; i++) {
    t[n][i] = v2[n].d[i];
    for (int j = n - 1; j >= 1; j--) {
      t[j][i] = min(v2[j].d[i], t[j + 1][i]);
    }
  }
}

void CalcFG() {
  for (int j = 0; j < m; j++) {
    c[j].Clear(min(n, m));
  }
  for (int i = 1; i <= n; i++) {
    r.Clear(min(n, m));
    for (int j = 1; j <= m; j++) {
      c[j - 1].Insert(f[i - 1][j - 1], g[i - 1][j - 1], i - 1);
      f[i][j] = max(r.Top(s[i][j]), c[j - 1].Top(t[i][j])) + 1;
      g[i][j] = (r.Count(f[i][j] - 1) + c[j - 1].Count(f[i][j] - 1)) % kMod;
      if (f[i][j] == 1) {
        g[i][j] = 1;
      }
      r.Insert(f[i - 1][j - 1], g[i - 1][j - 1], j - 1);
    }
  }
  ans1 = ans2 = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (f[i][j] > ans1) {
        ans1 = f[i][j], ans2 = g[i][j];
      } else if (f[i][j] == ans1) {
        ans2 = (ans2 + g[i][j]) % kMod;
      }
    }
  }
  Write(ans1, ans2);
}

int main() {
  Read(o);
  while (o--) {
    Input(), Sort(), CalcST(), CalcFG();
  }
  return 0;
}
