#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("guilty.in");
ofstream cout("guilty.out");

const int kMaxN = 2501, kB = 192, kC = kMaxN / kB, kMod = 1e9 + 7;
int n, m, a[kMaxN], c[kMaxN];
LL fans[kC + 1][kMaxN];  // 钦定每个盒子最多只能放 B 个, 留下最大的 i 个不放, 放了 j 个
LL gans[kC + 1][kMaxN];  // 钦定每个盒子至少放 B+1 个, 放了 i 个盒子, 放了 j 个
LL fact[kMaxN], _fact[kMaxN];

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

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void Mul(LL *f, LL *g, int l) {
  static LL t[kMaxN];
  for (int i = 0; i <= l; i++) {
    for (int j = 0; i + j <= n; j++) {
      Update(t[i + j], f[j] * g[i]);
    }
  }
  for (int i = 0; i <= n; i++) {
    f[i] = t[i], t[i] = 0;
  }
}

void CalcF() {
  static LL f[kMaxN];
  f[0] = 1, fill(&f[1], &f[kMaxN], 0);
  for (int i = 1; i <= kB; i++) {  // a_i 互不相同, 故只需到 kB
    if (a[i] > kB) {
      break;
    }
    Mul(f, _fact, a[i]);
  }
  if (c[kB + 1] > kC) {
    static LL g[kMaxN];
    int w = c[kB + 1] - kC;
    copy(&_fact[0], &_fact[kB] + 1, &g[0]);
    fill(&g[kB + 1], &g[kMaxN], 0);
    for (int i = 1; i <= w; i <<= 1) {
      if (i & w) {
        Mul(f, g, n);
      }
      Mul(g, g, n);
    }
  }
  for (int i = min(kC, c[kB + 1]); i >= 0; i--) {
    copy(&f[0], &f[n] + 1, &fans[i][0]);
    Mul(f, _fact, kB);
  }
}

void CalcG() {
  static LL f[kC + 1][kMaxN], g[kC + 1][kMaxN];
  f[0][0] = 1, fill(&f[0][1], &f[kC][0], 0);
  for (int i = n; i > kB; i--) {
    for (int j = 0; i * j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        if (!f[j][k]) {
          continue;
        }
        LL w = 1;
        for (int l = 0; j + l <= c[i] && k + i * l <= n; l++) {
          Update(g[j + l][k + i * l], f[j][k] * C(c[i] - j, l) % kMod * w);
          w = w * _fact[i] % kMod;
        }
      }
    }
    for (int j = 0; i * j <= n; j++) {
      for (int k = 0; k <= n; k++) {
        f[j][k] = g[j][k], g[j][k] = 0;
      }
    }
  }
  copy(&f[0][0], &f[kC][0], &gans[0][0]);
}

void CalcAns() {
  LL ans = 0;
  for (int i = 0; i <= kC; i++) {
    for (int j = 0; j <= n; j++) {
      Update(ans, fans[i][j] * gans[i][n - j]);
    }
  }
  ans = ans * fact[n] % kMod;
  cout << (ans + kMod) % kMod << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i], a[i] = min(a[i], n), c[a[i]]++;
  }
  for (int i = n - 1; i >= 1; i--) {
    c[i] += c[i + 1];
  }
  sort(a + 1, a + m + 1);
  CalcF(), CalcG(), CalcAns();
  return 0;
}
