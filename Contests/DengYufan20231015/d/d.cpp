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
using namespace IO;
using namespace std;

template <int kMaxN, int kMod = 998244353, int kG = 3>  // 当你 RE 的时候, 不妨想想自己的数组开大没有
class Poly {
 public:
#define LL long long
#define ULL unsigned long long
#define Clear(f, n) std::fill((f), (f) + (n) + 1, 0)
#define Copy(f, g, n) std::copy((g), (g) + (n) + 1, (f))

  LL Pow(LL a, LL t = kMod - 2) {
    LL ans = 1;
    while (t) {
      if (t & 1) {
        ans = ans * a % kMod;
      }
      a = a * a % kMod, t >>= 1;
    }
    return ans;
  }

  const int kInvG = Pow(kG);
  int tf, tr[kMaxN << 1];

  void CalcTr(int n) {
    if (tf == n) {
      return;
    }
    tf = n;
    for (int i = 0; i < n; i++) {
      tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    }
  }

  void NTT(int *g, bool op, int n) {  // 1 -> 0
    static ULL f[kMaxN << 1], w[kMaxN] = {1};
    CalcTr(n);
    for (int i = 0; i < n; i++) {
      f[i] = (((LL)kMod << 5) + g[tr[i]]) % kMod;
    }
    for (int l = 1; l < n; l <<= 1) {
      ULL tG = Pow(op ? kG : kInvG, (kMod - 1) / (l + l));
      for (int i = 1; i < l; i++) {
        w[i] = w[i - 1] * tG % kMod;
      }
      for (int k = 0; k < n; k += l + l) {
        for (int p = 0; p < l; p++) {
          int t = 1LL * w[p] * f[k | l | p] % kMod;
          f[k | l | p] = (f[k | p] + kMod - t) % kMod;
          f[k | p] = (f[k | p] + t) % kMod;
        }
      }
    }
    if (!op) {
      ULL invn = Pow(n);
      for (int i = 0; i < n; ++i) {
        g[i] = f[i] % kMod * invn % kMod;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        g[i] = f[i] % kMod;
      }
    }
  }

  void NTT2(int *g, int *gg, bool op, int n) {  // 1 -> 0
    static ULL f[kMaxN << 1], ff[kMaxN << 1], w[kMaxN] = {1};
    CalcTr(n);
    for (int i = 0; i < n; i++) {
      f[i] = (((LL)kMod << 5) + g[tr[i]]) % kMod;
      ff[i] = (((LL)kMod << 5) + gg[tr[i]]) % kMod;
    }
    for (int l = 1; l < n; l <<= 1) {
      ULL tG = Pow(op ? kG : kInvG, (kMod - 1) / (l + l));
      for (int i = 1; i < l; i++) {
        w[i] = w[i - 1] * tG % kMod;
      }
      for (int k = 0; k < n; k += l + l) {
        for (int p = 0; p < l; p++) {
          int t = 1LL * w[p] * f[k | l | p] % kMod;
          f[k | l | p] = (f[k | p] + kMod - t) % kMod;
          f[k | p] = (f[k | p] + t) % kMod;
          t = 1LL * w[p] * ff[k | l | p] % kMod;
          ff[k | l | p] = (ff[k | p] + kMod - t) % kMod;
          ff[k | p] = (ff[k | p] + t) % kMod;
        }
      }
    }
    if (!op) {
      ULL invn = Pow(n);
      for (int i = 0; i < n; ++i) {
        g[i] = f[i] % kMod * invn % kMod;
        gg[i] = ff[i] % kMod * invn % kMod;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        g[i] = f[i];
        gg[i] = ff[i];
      }
    }
  }

  void Dot(int *f, int *g, int n) {
    for (int i = 0; i < n; ++i) {
      f[i] = 1LL * f[i] * g[i] % kMod;
    }
  }

  int tmp[kMaxN << 1];

#define sav tmp

  void Cross(int *f, int *g, int len, int lim) {
    int n = 1;
    while (n < len + len) {
      n <<= 1;
    }
    Copy(sav, g, n), Clear(sav + len, n - len);
    NTT(f, 1, n), NTT(sav, 1, n), Dot(f, sav, n), NTT(f, 0, n);
    Clear(f + lim, n - lim), Clear(sav, n);
  }

  void InvP(int *f, int m) {
    int n;
    for (n = 1; n < m; n <<= 1) {
    }
    static int w[kMaxN << 1], r[kMaxN << 1];
    w[0] = Pow(f[0]);
    for (int len = 2; len <= n; len <<= 1) {
      for (int i = 0; i < (len >> 1); i++) {
        r[i] = w[i];
      }
      Copy(sav, f, len);
      NTT(sav, 1, len), NTT(r, 1, len), Dot(r, sav, len), NTT(r, 0, len);
      Clear(r, len >> 1), Copy(sav, w, len);
      NTT(sav, 1, len), NTT(r, 1, len), Dot(r, sav, len), NTT(r, 0, len);
      for (int i = len >> 1; i < len; i++) {
        w[i] = (w[i] * 2ll - r[i] + kMod) % kMod;
      }
    }
    Copy(f, w, m), Clear(sav, n), Clear(w, n), Clear(r, n);
  }

  void Derivative(int *f, int m) {
    for (int i = 1; i < m; i++) {
      f[i - 1] = 1LL * f[i] * i % kMod;
    }
    f[m - 1] = 0;
  }

  int inf, inv[kMaxN];

  void CalcInv(int m) {
    if (inf == m) {
      return;
    }
    inf = m, inv[1] = 1;
    for (int i = 2; i < kMaxN; i++) {
      inv[i] = 1LL * inv[kMod % i] * (kMod - kMod / i) % kMod;
    }
  }

  void Intergral(int *f, int m) {
    CalcInv(m);
    for (int i = m; i; i--) {
      f[i] = 1LL * f[i - 1] * inv[i] % kMod;
    }
    f[0] = 0;
  }

  void LnP(int *f, int m) {
    static int g[kMaxN << 1];
    Copy(g, f, m);
    InvP(g, m), Derivative(f, m), Cross(f, g, m, m), Intergral(f, m - 1);
    Clear(g, m);
  }

  void ExP(int *f, int m) {
    static int s[kMaxN << 1], s2[kMaxN << 1];
    int n = 1;
    for (; n < m; n <<= 1) {
    }
    s2[0] = 1;
    for (int len = 2; len <= n; len <<= 1) {
      Copy(s, s2, len >> 1);
      LnP(s, len);
      for (int i = 0; i < len; i++) {
        s[i] = (f[i] - s[i] + kMod) % kMod;
      }
      s[0] = (s[0] + 1) % kMod;
      Cross(s2, s, len, len);
    }
    Copy(f, s2, m), Clear(s, n), Clear(s2, n);
  }

  void PowP(int *f, int m, int k) {
    LnP(f, m);
    for (int i = 0; i < m; i++) {
      f[i] = 1LL * f[i] * k % kMod;
    }
    ExP(f, m);
  }
};

const int kMaxN = 5.5e5 + 1, kMod = 998244353;
int n, m, k, t, q, f[kMaxN], g[kMaxN];
unsigned ans;
Poly<kMaxN> poly;

int Calc(int x1, int y1, int x2, int y2) {
  int a = x2 - x1 + y2 - y1 + t >> 1, b = x2 - x1 + y1 - y2 + t >> 1;
  return 1LL * f[(a % m + m) % m] * f[(b % m + m) % m] % kMod;
}

int main() {
  // freopen("d.in", "r", stdin);
  // freopen("d.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Read(n, t, q);
  m = n + 2 << 1, f[0] = 1, g[0] = g[1] = 1;
  for (k = 1; k < m << 1; k <<= 1) {
  }
  for (int i = 1; i <= t; i <<= 1) {
    if (i & t) {
      poly.NTT2(f, g, 1, k);
      for (int i = 0; i < k; i++) {
        f[i] = 1LL * f[i] * g[i] % kMod;
      }
      for (int i = 0; i < k; i++) {
        g[i] = 1LL * g[i] * g[i] % kMod;
      }
      poly.NTT2(f, g, 0, k);
      for (int i = m; i < k; i++) {
        f[i % m] = (f[i % m] + f[i]) % kMod, f[i] = 0;
      }
      for (int i = m; i < k; i++) {
        g[i % m] = (g[i % m] + g[i]) % kMod, g[i] = 0;
      }
    } else {
      poly.NTT(g, 1, k);
      for (int i = 0; i < k; i++) {
        g[i] = 1LL * g[i] * g[i] % kMod;
      }
      poly.NTT(g, 0, k);
      for (int i = m; i < k; i++) {
        g[i % m] = (g[i % m] + g[i]) % kMod, g[i] = 0;
      }
    }
  }
  for (int i = 1, x1, y1, x2, y2; i <= q; i++) {
    Read(x1, y1, x2, y2);
    if ((x1 ^ y1 ^ x2 ^ y2 ^ t) & 1) {
      Write(0);
      continue;
    }
    x1++, y1++, x2++, y2++, ans = 0;
    for (int ox : {1, -1}) {
      for (int oy : {1, -1}) {
        ans = (ans + ox * oy * (Calc(x1, y1, ox * x2, oy * y2) + Calc(x1, y1, ox * x2 + m, oy * y2)) % kMod + kMod) % kMod;
      }
    }
    Write(ans);
  }
  return 0;
}
