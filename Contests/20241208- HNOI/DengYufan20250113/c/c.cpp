#include <iostream>
#include <vector>
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

const int kMaxN = 2e6 + 1, kMod = 998244353, kInv = 61689804;
struct E {
  int d, w, inv;
};
struct V {
  int l;
  LL s, t, _t, *f;
  vector<E> e;
} v[kMaxN];
int n, m;
LL *h, u[kMaxN * 5];
vector<int> r;

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void T(int f, int x) {
  static vector<E> e;
  for (E i : v[x].e) {
    if (i.d != f && i.w) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (E &i : v[x].e) {
    T(x, i.d);
    if (v[x].l < v[i.d].l) {
      v[x].l = v[i.d].l;
      swap(v[x].e[0], i);
    }
  }
  v[x].l++;
}

void Init() {
  struct A {
    int x, y, w;
  };
  static A a[kMaxN];
  static int zero[kMaxN], _zero[kMaxN];
  static LL fact[kMaxN], _fact[kMaxN];
  Read(n, a[0].x, m), m <<= 1, h = u;
  for (int i = 1, x, y, z; i < n; i++) {
    Read(x, y, z), z = 1LL * z * kInv % kMod;
    a[i] = {x, y, (1 - z + kMod) % kMod};
  }
  zero[0] = 0, fact[0] = 1;
  for (int i = 1; i < n; i++) {
    if (a[i].w) {
      zero[i] = zero[i - 1];
      fact[i] = fact[i - 1] * a[i].w % kMod;
    } else {
      zero[i] = zero[i - 1] + 1;
      fact[i] = fact[i - 1];
    }
  }
  _zero[n - 1] = zero[n - 1], _fact[n - 1] = Pow(fact[n - 1]);
  for (int i = n - 1; i >= 1; i--) {
    if (a[i].w) {
      _zero[i - 1] = _zero[i];
      _fact[i - 1] = _fact[i] * a[i].w % kMod;
    } else {
      _zero[i - 1] = _zero[i] - 1;
      _fact[i - 1] = _fact[i];
    }
  }
  for (int i = 1; i < n; i++) {
    if (a[i].w) {
      int w = fact[i - 1] * _fact[i] % kMod;
      v[a[i].x].e.push_back({a[i].y, a[i].w, w});
      v[a[i].y].e.push_back({a[i].x, a[i].w, w});
    } else {
      v[a[i].x].e.push_back({a[i].y, 0, 0});
      v[a[i].y].e.push_back({a[i].x, 0, 0});
    }
  }
  if (m < a[0].x) {
    for (int i = 1; i <= n; i++) {
      if (!v[i].l) {
        r.push_back(i), T(0, i);
      }
    }
    for (int i = 1; i <= n; i++) {
      v[i].l--;
    }
  }
}

void Long(int x) {
  int y = v[x].e[0].d;
  v[x].s = v[y].s;
  v[x].t = v[y].t * v[x].e[0].w % kMod;
  v[x]._t = v[y]._t * v[x].e[0].inv % kMod;
  v[x].f[0] = v[y].s * (1 - v[x].e[0].w) % kMod * v[x]._t % kMod;
  if (m < v[x].l && v[x].f[m + 1]) {
    v[x].s = (v[x].s - v[x].f[m + 1] * v[x].t) % kMod;
    v[x].f[m + 1] = 0;
  }
}

void Short(int x, E e) {
  static LL s[kMaxN], t[kMaxN];
  int y = e.d;
  for (int i = 0; i <= v[y].l && i <= m; i++) {
    v[y].f[i] = v[y].f[i] * v[y].t % kMod;
  }
  v[y].t = v[y]._t = 1, t[0] = v[y].f[0];
  for (int i = 1; i <= v[y].l && i <= m; i++) {
    t[i] = (t[i - 1] + v[y].f[i]) % kMod;
  }
  if (v[y].l + 1 << 1 > m) {
    for (int i = 0; i <= v[x].l && i <= m; i++) {
      v[x].f[i] = v[x].f[i] * v[x].t % kMod;
    }
    v[x].t = v[x]._t = 1, s[0] = v[x].f[0];
    for (int i = 1; i <= v[x].l && i <= m; i++) {
      s[i] = (s[i - 1] + v[x].f[i]) % kMod;
    }
    v[x].s = 0;
    for (int i = 0; i <= v[x].l && i <= m; i++) {
      LL w = v[x].f[i] * v[y].s % kMod * (1 - e.w);
      if (i && i < m) {
        w += v[x].f[i] * t[min(i - 1, m - i - 1)] % kMod * e.w;
      }
      if (i && i - 1 <= v[y].l) {
        w += v[y].f[i - 1] * s[min(i - 1, m - i)] % kMod * e.w;
      }
      v[x].s = (v[x].s + w) % kMod, v[x].f[i] = w % kMod;
    }
  } else {
    s[0] = v[x].f[0] * v[x].t % kMod;
    for (int i = 1; i <= v[y].l; i++) {
      s[i] = (s[i - 1] + v[x].f[i] * v[x].t) % kMod;
    }
    for (int i = 0; i <= v[y].l + 1; i++) {
      LL w = v[x].f[i] * v[x].t % kMod * v[y].s % kMod * (1 - e.w);
      if (i && i < m) {
        w += v[x].f[i] * v[x].t % kMod * t[min(i - 1, m - i - 1)] % kMod * e.w;
      }
      if (i) {
        w += v[y].f[i - 1] * v[y].t % kMod * s[min(i - 1, m - i)] % kMod * e.w;
      }
      v[x].s = (v[x].s + w - v[x].f[i] * v[x].t) % kMod;
      v[x].f[i] = w % kMod * v[x]._t % kMod;
    }
    for (int i = m - v[y].l; i <= v[x].l && i <= m; i++) {
      LL w = v[x].f[i] * v[x].t % kMod * v[y].s % kMod * (1 - e.w);
      if (i && i < m) {
        w += v[x].f[i] * v[x].t % kMod * t[min(i - 1, m - i - 1)] % kMod * e.w;
      }
      v[x].s = (v[x].s + w - v[x].f[i] * v[x].t) % kMod;
      v[x].f[i] = w % kMod * v[x]._t % kMod;
    }
  }
}

void Dp(int x) {
  if (v[x].e.empty()) {
    v[x].s = v[x].t = v[x]._t = v[x].f[0] = 1;
    return;
  }
  v[v[x].e[0].d].f = v[x].f + 1;
  Dp(v[x].e[0].d), Long(x);
  for (E i : v[x].e) {
    if (i.d != v[x].e[0].d) {
      v[i.d].f = h, h += v[i.d].l + 1;
      Dp(i.d), Short(x, i);
    }
  }
}

void Calc() {
  LL ans = 1;
  for (int i : r) {
    v[i].f = h, h += v[i].l + 1, Dp(i);
    ans = ans * v[i].s % kMod;
  }
  Write((ans + kMod) % kMod);
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  Init(), Calc();
  return 0;
}
