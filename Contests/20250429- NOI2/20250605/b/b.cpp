#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 251, kMod = 998244353, kInv2 = kMod + 1 >> 1;
int n;

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

void Solve1() {
  static int d[kMaxN], w[kMaxN];
  int c = 0;
  for (int i = 1, x, y, z; i <= 3; i++) {
    cin >> x >> y >> z;
    d[x]++, d[y]++;
    w[x] += z, w[y] += z;
    c += z == 1;
  }
  if (d[1] == 3 || d[2] == 3 || d[3] == 3 || d[4] == 3) {
    cout << 0 << '\n';
  } else if (d[1] != 1 && d[2] != 1 && d[3] != 1 && d[4] != 1) {
    cout << 5 << '\n';
  } else if (c == 0 || c == 3) {
    cout << 11 * Pow(2) % kMod << '\n';
  } else if (c == 2) {
    if (w[1] != 2 && w[2] != 2 && w[3] != 2 && w[4] != 2) {
      cout << 61 * Pow(10) % kMod << '\n';
    } else {
      cout << 53 * Pow(10) % kMod << '\n';
    }
  } else if (c == 1) {
    if (w[1] != 4 && w[2] != 4 && w[3] != 4 && w[4] != 4) {
      cout << 115 * Pow(22) % kMod << '\n';
    } else {
      cout << 125 * Pow(22) % kMod << '\n';
    }
  }
}

void Solve2() {
  struct F {
    LL a, b;
    F() : a(0), b(0) {}
    F(LL _b) : a(0), b(_b) {}
    F(LL _a, LL _b) : a(_a), b(_b) {}
    const F operator-(const F &f) const {
      return {(a - f.a) % kMod, b - (f.b) % kMod};
    }
    const F operator*(const LL &w) const {
      return {a * w % kMod, b * w % kMod};
    }
  };
  static int d[kMaxN];
  static F f[kMaxN];  // f_i = a f_0 + b
  LL p = n - 1, q = n * (n - 1) / 2 - (n - 2);
  f[0] = F(1, 0);
  for (int i = 0; i < p; i++) {
    LL w1 = (p * q - (p - i) * (q - p + i) - i * (p - i + 1)) % kMod;
    LL w2 = i * (q - p + i - 1) % kMod;
    f[i + 1] = (f[i] * w1 - f[i - 1] * w2 - (i * q % kMod * kInv2)) * Pow((p - i) * (p - i) % kMod);
  }
  F t = (f[p] - f[p - 1]) * (q - 1) - (q * kInv2);
  f[0] = F(-t.b * Pow(t.a) % kMod);
  for (int i = 1; i < p; i++) {
    f[i] = F((f[0].b * f[i].a + f[i].b) % kMod);
  }
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    d[x]++, d[y]++;
  }
  LL ans = -f[p].b;
  for (int i = 1; i <= n; i++) {
    ans = (ans + f[d[i]].b) % kMod;
  }
  cout << (ans + kMod) % kMod << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  if (n <= 3) {
    cout << 0 << '\n';
  } else if (n == 4) {
    Solve1();
  } else {
    Solve2();
  }
  return 0;
}
