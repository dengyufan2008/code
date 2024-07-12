#include <algorithm>
#include <iostream>

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS++) : *iS++)
template <class T>
inline void Read(T &x) {
  x = 0;
  int f = 0;
  char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc()) {
  }
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc()) {
  }
  x = (f == 1 ? ~x + 1 : x);
}
template <class T, class... Args>
inline void Read(T &x, Args &...args) { Read(x), Read(args...); }
template <class T>
inline void Readch(T &x) {
  char ch = gc();
  for (; !isalpha(ch); ch = gc()) {
  }
  x = ch;
}
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template <class T>
inline void Write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter++ = '-', x = ~x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10) {
  }
  for (; l; --l, *iter++ = c[l] + '0') {
  }
  *iter++ = ch;
  flush();
}
template <class T, class... Args>
inline void Write(T x, Args... args) { Write(x, ' '), Write(args...); }
}
using namespace IO;
using namespace std;

const int kMaxN = 3e5 + 1, kMaxV = 1e6 + 1, kMaxM = 26;
struct Q {
  int l, r, x, o;
} q[kMaxV];
int n, m, a[kMaxN], b[kMaxN];
double t[kMaxN], d[kMaxM][kMaxN], ans[kMaxV];

int main() {
  freopen("frac.in", "r", stdin);
  freopen("frac.out", "w", stdout);
  Read(n, m);
  for (int i = 1; i <= n; i++) {
    Read(a[i]);
  }
  for (int i = 1; i <= n; i++) {
    Read(b[i]);
  }
  for (int o = 1; o <= m; o++) {
    Read(q[o].l, q[o].r, q[o].x);
    q[o].o = o;
  }
  sort(q + 1, q + m + 1, [](Q i, Q j) { return i.x < j.x; });
  for (int i = 0, x = 1, o = 1; o <= m; i++, x *= 2) {
    if (q[o].x > x * 3 / 4 && q[o].x <= x * 3 / 2) {
      for (int k = 1; k <= n; k++) {
        double w = 1.0 / (double)(b[k] + x);
        d[0][k] = (double)a[k] * w;
        t[k] = (double)x * w;
      }
      for (int j = 1; j < kMaxM; j++) {
        for (int k = 1; k <= n; k++) {
          d[j][k] = d[j - 1][k] * t[k];
        }
      }
      for (int j = 0; j < kMaxM; j++) {
        for (int k = 1; k <= n; k++) {
          d[j][k] += d[j][k - 1];
        }
      }
      for (; o <= m && q[o].x > x * 3 / 4 && q[o].x <= x * 3 / 2; o++) {
        int delta = q[o].x - x;
        double s = 1, w = -(double)delta / (double)x;
        for (int j = 0; j < kMaxM; j++) {
          ans[q[o].o] += s * (d[j][q[o].r] - d[j][q[o].l - 1]);
          s *= w;
        }
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    printf("%.10f\n", ans[i]);
  }
  return 0;
}
