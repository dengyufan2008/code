// #include <ctime>
#include <iostream>
#include <queue>
#define LL long long

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS++) : *iS++)
template <class T>
inline void read(T &x) {
  x = 0;
  LL f = 0;
  char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc()) {
  }
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc()) {
  }
  x = (f == 1 ? ~x + 1 : x);
}
template <class T, class... Args>
inline void read(T &x, Args &...args) { read(x), read(args...); }
template <class T>
inline void readch(T &x) {
  char ch = gc();
  for (; !isalpha(ch); ch = gc()) {
  }
  x = ch;
}
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template <class T>
inline void write(T x, char ch = '\n') {
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
inline void write(T x, Args... args) { write(x, ' '), write(args...); }
}  // namespace IO

using namespace std;
using namespace IO;

const LL kMaxN = 5e5 + 2;
LL o, n, m, k, a, b, c, t, ans, s[kMaxN], d[kMaxN];
priority_queue<pair<LL, LL>> q;

int main() {
  freopen("lunae.in", "r", stdin);
  freopen("lunae.out", "w", stdout);
  read(o), read(o);
  while (o--) {
    read(n, m, k, a, b, c, t);
    for (LL i = 1; i <= m; i++) {
      read(s[i]);
    }
    s[m + 1] = n + 1, ans = 0;
    while (!q.empty()) {
      q.pop();
    }
    for (LL i = 1; i <= m; i++) {
      if (t - (s[i] - 1) * b >= 0) {
        d[i] = s[i] + (t - (s[i] - 1) * b) / a + 1;
        ans += min(d[i], s[i + 1]) - s[i];
        if (t - (s[i] - 1) * b - (d[i] - s[i]) * c >= 0 && d[i] < s[i + 1]) {
          q.push({min((t - (s[i] - 1) * b - (d[i] - s[i]) * c) / a + 1, s[i + 1] - d[i]), i});
        }
      }
    }
    for (LL p = 1; p <= k - m && !q.empty(); p++) {
      LL i = q.top().second;
      ans += q.top().first, q.pop();
      if (t - (s[i] - 1) * b - (d[i] - s[i]) * c >= 0) {
        d[i] = d[i] + (t - (s[i] - 1) * b - (d[i] - s[i]) * c) / a + 1;
        if (t - (s[i] - 1) * b - (d[i] - s[i]) * c >= 0 && d[i] < s[i + 1]) {
          q.push({min((t - (s[i] - 1) * b - (d[i] - s[i]) * c) / a + 1, s[i + 1] - d[i]), i});
        }
      }
    }
    write(ans);
  }
  // write(clock());
  return 0;
}
