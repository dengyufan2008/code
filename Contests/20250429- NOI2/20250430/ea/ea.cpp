#include <fstream>
#define LL long long

using namespace std;

ifstream cin("ea.in");
ofstream cout("ea.out");

const int kMod = 998244353;
int n;
bool u;

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

namespace Sub1 {
const int kMaxN = 5001;
LL ans, f[kMaxN][kMaxN], g[kMaxN][kMaxN];

int main() {
  for (int i = 0; i <= n; i++) {
    f[0][i] = f[1][i] = f[i][0] = f[i][1] = 1;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= n; j++) {
      f[i][j] = (f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + f[i - 2][j - 2]) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      ans ^= (f[i][j] + kMod) % kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
}  // namespace Sub1

namespace Sub0 {
const int kMaxN = 1 << 21;
struct Vector {
  LL w[2];
};
struct Matrix {
  LL w[2][2];
};
int m, r[kMaxN];
LL f[kMaxN];
LL fact[kMaxN], _fact[kMaxN];

const Vector kBase = {1, 1};
const Matrix kI = {1, 0, 0, 1};

const Vector operator*(const Vector &a, const Matrix &b) {
  return {(a.w[0] * b.w[0][0] + a.w[1] * b.w[1][0]) % kMod,
          (a.w[0] * b.w[0][1] + a.w[1] * b.w[1][1]) % kMod};
}

const Matrix operator*(const Matrix &a, const Matrix &b) {
  return {(a.w[0][0] * b.w[0][0] + a.w[0][1] * b.w[1][0]) % kMod,
          (a.w[0][0] * b.w[0][1] + a.w[0][1] * b.w[1][1]) % kMod,
          (a.w[1][0] * b.w[0][0] + a.w[1][1] * b.w[1][0]) % kMod,
          (a.w[1][0] * b.w[0][1] + a.w[1][1] * b.w[1][1]) % kMod};
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Init() {
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  for (m = 1; m <= n + (n & 1); m <<= 1) {
  }
  m <<= 1;
  for (int i = 0; i < m; i++) {
    r[i] = (r[i >> 1] >> 1) | (i & 1 ? m >> 1 : 0);
  }
}

void Ntt(LL *f, bool o) {
  for (int i = 0; i < m; i++) {
    if (i < r[i]) {
      swap(f[i], f[r[i]]);
    }
  }
  for (int i = 1; i < m; i <<= 1) {
    LL g = Pow(3, (kMod - 1) / (i + i) * (o ? i + i - 1 : 1));
    for (int j = 0; j < m; j += i + i) {
      LL w = 1;
      for (int k = j; k < j + i; k++) {
        LL f0 = f[k], f1 = f[k + i] * w % kMod;
        f[k] = (f0 + f1) % kMod;
        f[k + i] = (f0 - f1) % kMod;
        w = w * g % kMod;
      }
    }
  }
  if (o) {
    LL inv = Pow(m);
    for (int i = 0; i < m; i++) {
      f[i] = f[i] * inv % kMod;
    }
  }
}

void CalcF() {
  LL omega = Pow(3, (kMod - 1) / m);
  for (int i = 0; i < m; i++) {
    static LL g = 1;
    Vector ans = kBase;
    Matrix x = {g * g % kMod, g * g % kMod, 1 - g, (1 - g + g * g) % kMod};
    for (int j = 1; j <= n >> 1; j <<= 1) {
      if (j & n >> 1) {
        ans = ans * x;
      }
      x = x * x;
    }
    f[i] = ans.w[n & 1], g = g * omega % kMod;
  }
}

void RestoreF() {
  static LL g[kMaxN];
  for (int i = 0; i < m >> 1; i++) {
    g[i] = C(i + (n >> 1), i);
  }
  Ntt(g, 0);
  for (int i = 0; i < m; i++) {
    f[i] = f[i] * g[i] % kMod;
  }
  Ntt(f, 1);
}

int main() {
  Init(), CalcF(), RestoreF();
  for (int i = 1; i <= n + (n & 1); i++) {
    cout << (f[i] + kMod) % kMod << " \n"[i == n + (n & 1)];
  }
  return 0;
}
}  // namespace Sub0

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> u;
  if (u) {
    return Sub1::main();
  } else {
    return Sub0::main();
  }
}
