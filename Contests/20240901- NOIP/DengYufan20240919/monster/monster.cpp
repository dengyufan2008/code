#include <iostream>
#include <queue>
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
using namespace IO;
using namespace std;

const int kMaxN = 1e6 + 1, kInf = 1e9;
struct V {
  int w, d;
  vector<int> e;
} v[kMaxN];
int t, n, m, k;
queue<int> q;
priority_queue<pair<int, int>> h;

void Input() {
  int a, b;
  for (int i = 1; i <= n; i++) {
    v[i].e.clear();
  }
  Read(n, m, a, b);
  for (int i = 1, x, y; i <= m; i++) {
    Read(x, y), v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    Read(v[i].w);
  }
  for (int i = 2; i <= n; i++) {
    v[i].w += b;
  }
  k = a - b;
}

void Solve1() {
  while (!q.empty()) {
    q.pop();
  }
  for (int i = 1; i <= n; i++) {
    v[i].d = kInf;
  }
  for (v[1].d = 0, q.push(1); !q.empty(); q.pop()) {
    int x = q.front();
    if (x == n) {
      Write(v[n].d);
      return;
    }
    for (int i : v[x].e) {
      if (v[i].d > v[x].d + 1 && v[i].w < v[1].w + 1LL * v[x].d * k) {
        v[i].d = v[x].d + 1, q.push(i);
      }
    }
  }
  Write(-1);
}

bool C(int s) {
  if (v[n].w >= v[1].w + 1LL * (s - 1) * k) {
    return 0;
  }
  while (!q.empty()) {
    q.pop();
  }
  for (int i = 1; i <= n; i++) {
    v[i].d = kInf;
  }
  for (v[n].d = 0, q.push(n); !q.empty(); q.pop()) {
    int x = q.front();
    if (v[x].d > s) {
      return 0;
    } else if (x == 1) {
      return 1;
    }
    for (int i : v[x].e) {
      if (v[i].d > v[x].d + 1 && (i == 1 || v[i].w < v[1].w + 1LL * (s - v[x].d - 2) * k)) {
        v[i].d = v[x].d + 1, q.push(i);
      }
    }
  }
  return 0;
}

void Solve2() {
  int s = 0;
  while (!h.empty()) {
    h.pop();
  }
  for (int i = 1; i <= n; i++) {
    v[i].d = 0;
  }
  for (int i : v[1].e) {
    v[i].d = 1, h.push({-v[i].w, i});
  }
  for (v[1].d = 1; !h.empty();) {
    int x = h.top().second;
    h.pop();
    if (v[1].w + 1LL * s * k <= v[x].w) {
      break;
    }
    s++;
    for (int i : v[x].e) {
      if (!v[i].d) {
        v[i].d = 1, h.push({-v[i].w, i});
      }
    }
  }
  int l = 0, r = ++s;
  while (l <= r) {
    int mid = l + r >> 1;
    if (C(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  Write(l > s ? -1 : l);
}

int main() {
  freopen("monster.in", "r", stdin);
  freopen("monster.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Read(t);
  while (t--) {
    Input(), k <= 0 ? Solve1() : Solve2();
  }
  return 0;
}
