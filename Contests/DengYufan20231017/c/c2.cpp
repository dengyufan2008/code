#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxM = 21, kMaxP = 11, kMod = 998244353, kG = 3, kInvG = 332748118;
int n, p, m, k;
template <int kMaxN, int kMod = 998244353, int kG = 3>  // 当你 RE 的时候, 不妨想想自己的数组开大没有
class Poly {
 public:
#define LL long long
#define ULL unsigned long long
#define Clear(f, n) std::fill((f), (f) + (n), 0)
#define Copy(f, g, n) std::copy((g), (g) + (n), (f))

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

  void Add(int *f, int *g, int n) {
    for (int i = 0; i < n; ++i) {
      f[i] = (f[i] + g[i]) % kMod;
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
Poly<kMaxM> poly;
class Poly2 {
 public:
  int f[kMaxP][kMaxM];
  void Mul(Poly2 g) {
    int t[kMaxM];
    Poly2 ans = {};
    for (int i = 0; i < p; i++) {
      for (int j = 0; j < p; j++) {
        Copy(t, f[i], k), poly.Cross(t, g.f[j], k, k);
        poly.Add(ans.f[(i + j) % p], t, k);
      }
    }
    for (int i = 0; i < p; i++) {
      Copy(f[i], ans.f[i], k);
    }
  }
} t, ot, ans;
class Cnt {
 public:
  int m, d[kMaxP];
  Cnt operator*(Cnt x) {
    Cnt ans = *this;
    ans.m = m * x.m % p;
    for (int i = 0; i < p; i++) {
      ans.d[i * m % p] += x.d[i];
    }
    return ans;
  }
} c, oc;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> p >> m;
  for (k = 1; k < m; k <<= 1) {
  }
  k <<= 1;
  for (int i = 0; i < p; i++) {
    ans.f[i][0] = 1;
  }
  c = {1, {}}, oc = {10, {0, 1}};
  for (int i = 1; i <= n; i <<= 1) {
    if (i & n) {
      c = c * oc;
    }
    oc = oc * oc;
  }
  for (int i = 0; i < p; i++) {
    t.f[0][0] = 1, fill(&t.f[0][1], &t.f[0][k], 0);
    for (int j = 1; j < p; j++) {
      fill(&t.f[j][0], &t.f[j][k], 0);
    }
    for (int j = 0; j <= min(m, 9); j++) {
      ot.f[j * i % p][j] = 1;
    }
     for (int j = 1; j <= c.d[i]; j <<= 1) {
      if (j & c.d[i]) {
        t.Mul(ot);
      }
      ot.Mul(ot);
    }
    ans.Mul(t);
  }
  for (int i = 0, j = 0; i <= m; i++) {
    j = (j + ans.f[0][i]) % kMod;
    cout << j << ' ';
  }
  return 0;
}
