#include <fstream>
#define LL long long
#define Clear(f, m) fill((f), (f) + (m), 0)
#define Copy(f, g, m) copy((g), (g) + (m), (f))

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 12e5 + 1, kMaxL = 21, kMod = 998244353, kG = 3;
int k;
LL ans[kMaxN], t[kMaxN * 2], u[kMaxN * 2], uf[kMaxN * 8], ug[kMaxN * 8];
LL *hf[kMaxN], *hg[kMaxN];
LL *hw0[kMaxL * kMaxL], *hw1[kMaxL * kMaxL], **hhw0[kMaxL], **hhw1[kMaxL];
LL uw0[kMaxN * 2], uw1[kMaxN * 2];

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

const LL kInvG = Pow(kG);

void CalcUW() {
  LL **shit0, *shit1;

  shit0 = hw0, shit1 = uw0;
  for (int o = 0; o < kMaxL; o++) {
    int m = 1 << o;
    hhw0[o] = shit0, shit0 += o;
    for (int i = 1, _i = 0; i < m; i <<= 1, _i++) {
      LL g = Pow(kG, (kMod - 1) / (i + i));
      LL w = 1;
      hhw0[o][_i] = shit1, shit1 += i;
      for (int j = 0; j < i; j++) {
        hhw0[o][_i][j] = w;
        w = w * g % kMod;
      }
    }
  }

  shit0 = hw1, shit1 = uw1;
  for (int o = 0; o < kMaxL; o++) {
    int m = 1 << o;
    hhw1[o] = shit0, shit0 += o;
    for (int i = 1, _i = 0; i < m; i <<= 1, _i++) {
      LL g = Pow(kInvG, (kMod - 1) / (i + i));
      LL w = 1;
      hhw1[o][_i] = shit1, shit1 += i;
      for (int j = 0; j < i; j++) {
        hhw1[o][_i][j] = w;
        w = w * g % kMod;
      }
    }
  }
}

void Ntt(LL *f, int m, bool b) {
  static int r[kMaxN];
  for (int i = 0; i < m; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? m >> 1 : 0);
  }
  for (int i = 0; i < m; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  int o = 31 - __builtin_clz(m);
  LL ***hhw = b ? hhw1 : hhw0;
  for (int i = 1, _i = 0; i < m; i <<= 1, _i++) {
    for (int j = 0; j < m; j += i + i) {
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i] * hhw[o][_i][k - j];
        f[k] = (f0 + f1) % kMod;
        f[k + i] = (f0 - f1) % kMod;
      }
    }
  }
  if (b) {
    LL invm = Pow(m);
    for (int i = 0; i < m; i++) {
      f[i] = f[i] * invm % kMod;
    }
  }
}

void Inv(LL *f, int _m) {
  static LL g[kMaxN], tf[kMaxN], tg[kMaxN];
  int m = 1;
  for (; m < _m; m <<= 1) {
  }
  m <<= 1;
  Clear(g, m), Clear(tf, m), Clear(tg, m);
  g[0] = Pow(f[0]);
  for (int i = 2; i < m; i <<= 1) {
    Copy(tf, f, i), Copy(tg, g, i);
    Ntt(tf, i + i, 0), Ntt(tg, i + i, 0);
    for (int j = 0; j < i + i; j++) {
      tg[j] = tg[j] * tg[j] % kMod * tf[j] % kMod;
    }
    Ntt(tg, i + i, 1), Clear(tg + i, i);
    for (int j = 0; j < i; j++) {
      g[j] = (g[j] * 2 - tg[j]) % kMod;
    }
  }
  Copy(f, g, _m);
}

void Init(LL *&u, LL **f, int p, int l, int r, bool o) {
  static LL tf[kMaxN], tg[kMaxN];
  f[p] = u, u += (r - l + 1) * 2 + 1;
  if (l == r) {
    if (o) {
      f[p][0] = 1, f[p][1] = -(6 * l + 3);
      f[p][2] = (9LL * l * l + 9 * l + 2) % kMod;
    } else {
      f[p][0] = 1, f[p][1] = -(4 * l + 1);
      f[p][2] = (4LL * l * l + 2 * l) % kMod;
    }
    return;
  }
  int mid = l + r >> 1;
  Init(u, f, p << 1, l, mid, o);
  Init(u, f, p << 1 | 1, mid + 1, r, o);
  int m = 1;
  for (; m < (r - l + 1) * 2 + 1; m <<= 1) {
  }
  Clear(tf, m), Clear(tg, m);
  Copy(tf, f[p << 1], (mid - l + 1) * 2 + 1);
  Copy(tg, f[p << 1 | 1], (r - mid) * 2 + 1);
  Ntt(tf, m, 0), Ntt(tg, m, 0);
  for (int i = 0; i < m; i++) {
    tf[i] = tf[i] * tg[i] % kMod;
  }
  Ntt(tf, m, 1);
  Copy(f[p], tf, (r - l + 1) * 2 + 1);
}

void Solve(LL *f, LL *t, int p, int n, int l, int r) {
  static LL tg[kMaxN];
  if (l == r) {
    if (n == 0) {
      ans[l] = f[0];
    } else if (n == 1) {
      ans[l] = (-(4 * l + 1) * f[0] + f[1]) % kMod;
    } else {
      ans[l] = ((4LL * l * l + 2 * l) % kMod * f[0] - (4 * l + 1) * f[1] + f[2]) % kMod;
    }
    return;
  }
  int mid = l + r >> 1, m = 1;
  LL *_f = f + n + 1;
  for (; m < n + (mid - l + 1) * 2 + 1; m <<= 1) {
  }
  Clear(t, m);
  Copy(t, f, n + 1), Ntt(t, m, 0);

  Clear(tg, m);
  Copy(tg, hg[p << 1 | 1], (r - mid) * 2 + 1);
  Ntt(tg, m, 0);
  for (int i = 0; i < m; i++) {
    tg[i] = tg[i] * t[i] % kMod;
  }
  Ntt(tg, m, 1);
  if (n <= (mid - l + 1) * 2) {
    Copy(_f, tg, n + 1);
    Solve(_f, t + m, p << 1, n, l, mid);
  } else {
    Copy(_f, tg + n - (mid - l + 1) * 2, (mid - l + 1) * 2 + 1);
    Solve(_f, t + m, p << 1, (mid - l + 1) * 2, l, mid);
  }

  Clear(tg, m);
  Copy(tg, hf[p << 1], (mid - l + 1) * 2 + 1);
  Ntt(tg, m, 0);
  for (int i = 0; i < m; i++) {
    tg[i] = tg[i] * t[i] % kMod;
  }
  Ntt(tg, m, 1);
  if (n <= (r - mid) * 2) {
    Copy(_f, tg, n + 1);
    Solve(_f, t + m, p << 1 | 1, n, mid + 1, r);
  } else {
    Copy(_f, tg + n - (r - mid) * 2, (r - mid) * 2 + 1);
    Solve(_f, t + m, p << 1 | 1, (r - mid) * 2, mid + 1, r);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  static int n, o;
  static LL *shit, f[kMaxN];
  cin >> n >> k >> o, CalcUW();
  Init(shit = uf, hf, 1, 0, k - 1, 0);
  Init(shit = ug, hg, 1, 0, k - 1, 1);
  Copy(f, hg[1], k * 2 + 1), Inv(f, max(n + 1, k * 2 + 1));
  if (n <= k * 2) {
    Copy(u, f, n + 1);
    Solve(u, t, 1, n, 0, k - 1);
  } else {
    Copy(u, f + n - k * 2, k * 2 + 1);
    Solve(u, t, 1, k * 2, 0, k - 1);
  }
  if (o) {
    for (int i = 0; i < k; i++) {
      cout << (ans[i] + kMod) % kMod << '\n';
    }
  } else {
    cout << (ans[k - 1] + kMod) % kMod << '\n';
  }
  return 0;
}
