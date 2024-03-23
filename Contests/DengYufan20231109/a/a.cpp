#include <cstring>
#include <ctime>
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

const int kMaxN = 1e5 + 1, kMaxM = 21, kInf = 1e9;
int n, m, q, h, c[26], p[26][kMaxN], f[kMaxM][kMaxM];
char s[kMaxN], t[kMaxN];

int Find(int x, int o) {
  int l = h, r = c[o];
  while (l <= r) {
    int mid = l + r >> 1;
    if (p[o][mid] <= x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  h = l;
  return l <= c[o] ? p[o][l] : n + 1;
}

int main() {
  scanf("%s %s", s + 1, t + 1);
  n = strlen(s + 1), m = strlen(t + 1);
  for (int i = 1; i <= n; i++) {
    int j = s[i] - 'a';
    p[j][++c[j]] = i;
  }
  fill(&f[0][1], &f[0][kMaxM], kInf);
  Read(q);
  for (int i = 1, x, y; i <= q; i++) {
    Read(x, y);
    f[0][0] = x - 1;
    for (int j = 0; j < m; j++) {
      h = 1, f[j + 1][0] = kInf;
      for (int k = 0; k <= j; k++) {
        f[j + 1][k] = min(f[j + 1][k], f[j][k]);
        if (k < m) {
          f[j + 1][k + 1] = Find(f[j][k], t[j + 1] - 'a');
        }
      }
    }
    for (int j = m; j >= 0; j--) {
      if (f[m][j] <= y) {
        Write(y - x + 1 + m - j * 2);
        break;
      }
    }
  }
  return 0;
}
