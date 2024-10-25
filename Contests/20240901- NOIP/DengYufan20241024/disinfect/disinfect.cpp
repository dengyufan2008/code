#include <algorithm>
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

const int kMaxN = 5001, kMaxM = 501;
struct V {
  int xl, xr, yl, yr;
  int z;
} e[kMaxM], v[kMaxM];
int n, m, s, c, ans, o[kMaxM], d[kMaxM], a[kMaxN][kMaxN];

int main() {
  freopen("disinfect.in", "r", stdin);
  freopen("disinfect.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Read(n, m, s);
  for (int i = 1; i < kMaxM; i++) {
    e[i].xl = n, e[i].xr = 0, e[i].yl = m, e[i].yr = 0, o[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      Read(a[i][j]);
      e[a[i][j]].xl = min(e[a[i][j]].xl, i);
      e[a[i][j]].xr = max(e[a[i][j]].xr, i);
      e[a[i][j]].yl = min(e[a[i][j]].yl, j);
      e[a[i][j]].yr = max(e[a[i][j]].yr, j);
    }
  }
  for (int i = 1; i < kMaxM; i++) {
    e[i].yr ? v[++c] = e[i] : e[i];
  }
  sort(v + 1, v + c + 1, [](V i, V j) { return i.yr < j.yr; });
  sort(o + 1, o + c + 1, [](int i, int j) { return v[i].yl < v[j].yl; });
  for (int i = 1; i <= c; i++) {
    v[o[i]].z = v[o[i - 1]].z + (v[o[i]].yl > v[o[i - 1]].yl);
  }
  for (int i = 1; i <= c; i++) {
    o[v[i].z] = v[i].yl;
  }
  for (int i = 1; i <= c; i++) {
    for (int j = i; j <= c; j++) {
      int xl = min(v[i].xl, v[j].xl), xr = max(v[i].xr, v[j].xr);
      if (s >= xr - xl + 1) {
        int l = s / (xr - xl + 1);
        for (int k = 1, p = 1; k <= c; k++) {
          if (v[k].xl >= xl && v[k].xr <= xr && l >= v[k].yr - v[k].yl + 1) {
            for (; o[p] < v[k].yr - l + 1; p++) {
            }
            d[p]++, (v[k].z < c) && d[v[k].z + 1]--;
          }
        }
        for (int k = 1; k <= c; k++) {
          d[k] += d[k - 1], ans = max(ans, d[k]);
        }
        for (int k = 1; k <= c; k++) {
          d[k] = 0;
        }
      }
    }
  }
  cout << c - ans << '\n';
  return 0;
}
