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
}  // namespace IO
using namespace IO;
using namespace std;

const int kMaxN = 1e4 + 1, kInf = 1e9;
struct V {
  int mn, t, l, r;
} v[kMaxN * 150];
int n, m, h, k, c, a[kMaxN], b[kMaxN], w[kMaxN], t[kMaxN], s[kMaxN * 4];

void Build2(int &p, int l, int r, int x, bool o) {
  !p && (p = ++k);
  if (l == r) {
    v[p].mn = w[b[l]] / t[b[l]] + o * w[b[l]] % t[b[l]];
    return;
  }
  int mid = l + r >> 1;
  mid >= a[x] ? Build2(v[p].l, l, mid, x, o) : Build2(v[p].r, mid + 1, r, x, o);
  v[p].mn = min(v[v[p].l].mn, v[v[p].r].mn);
}

void Build1(int p, int l, int r, int k) {
  if (l == r) {
    t[l] = k, Build2(s[p], 1, n, l, 1);
    return;
  }
  int mid = l + r >> 1;
  Build1(p << 1, l, mid, k + 1), Build1(p << 1 | 1, mid + 1, r, k + 1);
  for (int i = l; i <= r; i++) {
    Build2(s[p], 1, n, i, 0);
  }
}

void Pushdown(int p) {
  if (v[p].t) {
    if (v[p].l) {
      v[v[p].l].mn += v[p].t, v[v[p].l].t += v[p].t;
    }
    if (v[p].r) {
      v[v[p].r].mn += v[p].t, v[v[p].r].t += v[p].t;
    }
    v[p].t = 0;
  }
}

int Ask(int p, int l, int r, int x) {
  if (!p) {
    return 0;
  } else if (l == r) {
    return v[p].mn;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  return mid >= a[x] ? Ask(v[p].l, l, mid, x) : Ask(v[p].r, mid + 1, r, x);
}

void ReCalc2(int p, int l, int r, int x, bool o) {
  if (!p || v[p].mn == kInf) {
    return;
  } else if (l == r) {
    v[p].mn = w[b[l]] >= 0 ? w[b[l]] / t[b[l]] + o * w[b[l]] % t[b[l]] : kInf;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= a[x]) {
    ReCalc2(v[p].l, l, mid, x, o);
  } else {
    ReCalc2(v[p].r, mid + 1, r, x, o);
  }
  v[p].mn = min(v[v[p].l].mn, v[v[p].r].mn);
}

void ReCalc1(int p, int l, int r, int x, int k) {
  k += Ask(s[p], 1, n, x);
  if (l == r) {
    k < 0 && c--, w[x] = k, ReCalc2(s[p], 1, n, x, 1);
    return;
  }
  int mid = l + r >> 1;
  mid >= x ? ReCalc1(p << 1, l, mid, x, k) : ReCalc1(p << 1 | 1, mid + 1, r, x, k);
  ReCalc2(s[p], 1, n, x, 0);
}

void ReBuild(int p, int l, int r) {
  if (!p || v[p].mn == kInf) {
    return;
  } else if (l == r) {
    ReCalc1(1, 1, n, b[l], 0);
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (v[v[p].l].mn < 0) {
    ReBuild(v[p].l, l, mid);
  }
  if (v[v[p].r].mn < 0) {
    ReBuild(v[p].r, mid + 1, r);
  }
  v[p].mn = min(v[v[p].l].mn, v[v[p].r].mn);
}

void Decrease2(int p, int l, int r, int _l, int _r, int k) {
  if (!p || v[p].mn == kInf) {
    return;
  } else if (l >= _l && r <= _r) {
    v[p].mn -= k, v[p].t -= k;
    if (v[p].mn < 0) {
      ReBuild(p, l, r);
    }
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Decrease2(v[p].l, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Decrease2(v[p].r, mid + 1, r, _l, _r, k);
  }
  v[p].mn = min(v[v[p].l].mn, v[v[p].r].mn);
}

void Decrease1(int p, int l, int r, int _l, int _r, int __l, int __r, int k) {
  if (l >= _l && r <= _r) {
    Decrease2(s[p], 1, n, __l, __r, k);
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Decrease1(p << 1, l, mid, _l, _r, __l, __r, k);
  }
  if (mid < _r) {
    Decrease1(p << 1 | 1, mid + 1, r, _l, _r, __l, __r, k);
  }
}

int main() {
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
  Read(n, m);
  for (int i = 1; i <= n; i++) {
    Read(a[i], w[i]);
    b[a[i]] = i;
  }
  c = n, v[0].mn = kInf, Build1(1, 1, n, 1);
  for (int i = 1, x1, y1, x2, y2, z, p = 0; i <= m; i++) {
    Read(x1, y1, x2, y2, z);
    x1 ^= p, y1 ^= p, x2 ^= p, y2 ^= p, z ^= p;
    Decrease1(1, 1, n, x1, x2, y1, y2, z);
    Write(p = c);
  }
  return 0;
}
