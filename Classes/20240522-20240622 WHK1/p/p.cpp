#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("p.in");
ofstream cout("p.out");

const int kMaxN = 1e6 + 1;
int t, p, n, a[4], d[4][4];
LL fact[kMaxN], _fact[kMaxN];

void Add(LL &x, LL y) { x = (x + y) % p; }

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

class P {
 public:
  LL r, i;

  P() : r(0), i(0) {}
  P(LL _r, LL _i) : r(_r), i(_i) {}

  P operator+(P x) {
    return {(r + x.r) % p, (i + x.i) % p};
  }

  P operator<<(LL x) {
    if (x & 1) {
      return x & 2 ? P(i, -r) : P(-i, r);
    } else {
      return x & 2 ? P(-r, -i) : P(r, i);
    }
  }

  P operator*(LL x) {
    return {r * x % p, i * x % p};
  }

  P operator*(P x) {
    return {(r * x.r - i * x.i) % p, (r * x.i + i * x.r) % p};
  }

  P operator^(LL y) {
    P x = *this, ans(1, 0);
    for (LL i = 1; i <= y; i <<= 1) {
      if (i & y) {
        ans = ans * x;
      }
      x = x * x;
    }
    return ans;
  }
} ans;

void CalcAns(bool o) {
  LL b[4] = {};
  P w(1, 0);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      b[j] += d[i][j];
    }
  }
  if (!o && b[0] <= 0 && b[1] <= 1 && b[2] <= 0 && b[3] <= 1) {
    return;
  }
  for (int i = 0; i < 4; i++) {
    w.r = w.r * fact[a[i]] % p;
    for (int j = 0; j < 4; j++) {
      w.r = w.r * _fact[d[i][j]] % p;
    }
  }
  int q = (d[1][3] + d[3][1]) + 3 * (d[1][1] + d[3][3]) & 3;
  q = q + 2 * (d[1][2] + d[2][1] + d[2][3] + d[3][2]) & 3;
  w = w << q;
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 4; j++) {
      P p(1, 0);
      if (i + j & 1) {
        p.i += i + j & 2 ? -1 : 1;
      } else {
        p.r += i + j & 2 ? -1 : 1;
      }
      w = w * (p ^ b[i] * b[j]);
    }
  }
  for (int i = 0; i < 4; i++) {
    P p(1, 0);
    p.r += i & 1 ? -1 : 1;
    w = w * (p ^ b[i] * (b[i] - 1) / 2);
  }
  ans = ans + w;
}

void S(int x, int b0, int b1, int b2, int b3, bool o) {
  if (x == 4) {
    CalcAns(o);
    return;
  }
  for (int &i = d[x][0] = 0; i <= b0 && i <= a[x]; i++) {
    for (int &j = d[x][1] = 0; j <= b1 && i + j <= a[x]; j++) {
      for (int &k = d[x][2] = 0; k <= b2 && i + j + k <= a[x]; k++) {
        int &l = d[x][3] = a[x] - i - j - k;
        l <= b3 ? S(x + 1, b0 - i, b1 - j, b2 - k, b3 - l, o) : void();
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> p;
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1], p - 2);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % p;
  }
  while (t--) {
    cin >> n >> a[0] >> a[1] >> a[2] >> a[3];
    ans = P(), S(0, 0, 1, n, 1, 1), S(0, n, 1, 0, 1, 0);
    int q = p - 1 - 1LL * n * (n + 3) / 2 % (p - 1);
    cout << (ans.r + p) * Pow(2, q) % p << '\n';
  }
  return 0;
}
