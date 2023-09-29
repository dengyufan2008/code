#include <fstream>
#define LL long long

using namespace std;

ifstream cin("walk.in");
ofstream cout("walk.out");

LL t, p, m, n, a[61][12][12], b[61][12][12], c[61][12][12], d[61][69][69], ans0[12][12], ans1[12][12], ans2[12][12], ans3[69][69], o[69][69];

void Init() {
  for (LL i(1); i < 3; i++) {
    for (LL j(1); j < 3; j++) {
      ans0[i][j] = 0;
    }
  }
  ans0[1][1] = 1;
  for (LL i(1); i <= m; i++) {
    for (LL j(1); j <= m; j++) {
      ans1[i][j] = i == j;
    }
  }
  for (LL i(1); i < 7; i++) {
    for (LL j(1); j < 7; j++) {
      ans2[i][j] = i == j;
    }
  }
  for (LL i(1); i < 69; i++) {
    for (LL j(1); j < 69; j++) {
      ans3[i][j] = i == j;
    }
  }
}

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

void Mul1(LL x[12][12], LL y[12][12]) {
  for (LL i = 1; i <= 11; i++) {
    for (LL j = 1; j <= 11; j++) {
      o[i][j] = 0;
      for (LL k = 1; k <= 11; k++) {
        o[i][j] = (o[i][j] + x[i][k] * y[k][j]) % p;
      }
    }
  }
  for (LL i = 1; i <= 11; i++) {
    for (LL j = 1; j <= 11; j++) {
      x[i][j] = o[i][j];
    }
  }
}

void Mul2(LL x[69][69], LL y[69][69], LL f) {
  for (LL i = 1; i <= m; i++) {
    for (LL j = i; j <= m; j++) {
      for (LL _i = 1; _i <= 6; _i++) {
        for (LL _j = 1; _j <= 6; _j++) {
          o[(i - 1) * 6 + _i][(j - 1) * 6 + _j] = f ? b[f][i][j] * c[f][_i][_j] % p : ans1[i][j] * ans2[_i][_j] % p;
        }
      }
    }
  }
  for (LL i = 1; i <= m * 6 + 2; i++) {
    for (LL j = m * 6 + 1; j <= m * 6 + 2; j++) {
      o[i][j] = 0;
      for (LL k = 1; k <= m * 6 + 2; k++) {
        o[i][j] = (o[i][j] + x[i][k] * y[k][j] % p) % p;
      }
    }
  }
  for (LL i = 1; i <= m * 6 + 2; i++) {
    for (LL j = 1; j <= m * 6 + 2; j++) {
      x[i][j] = o[i][j];
    }
  }
}

void SpawnMatrix() {
  m++, a[0][1][1] = a[0][2][1] = 8, a[0][1][2] = 1;
  for (LL i = 1; i <= m; i++) {
    b[0][1][i] = b[0][i][i] = 1;
    for (LL j = 2; j < i; j++) {
      b[0][j][i] = (b[0][j][i - 1] + b[0][j - 1][i - 1]) % p;
    }
  }
  c[0][1][3] = c[0][2][2] = c[0][2][6] = c[0][3][1] = c[0][3][4] = c[0][3][6] = c[0][4][1] = c[0][4][2] = c[0][4][6] = c[0][5][5] = c[0][5][6] = c[0][6][2] = c[0][6][5] = c[0][6][6] = 1;
  c[0][2][4] = c[0][3][3] = c[0][4][3] = c[0][4][4] = c[0][5][1] = c[0][5][3] = c[0][5][4] = c[0][6][1] = c[0][6][3] = c[0][6][4] = 2;
  for (LL i = 1; i <= m; i++) {
    for (LL j = i; j <= m; j++) {
      for (LL _i = 1; _i <= 6; _i++) {
        for (LL _j = 1; _j <= 6; _j++) {
          d[0][(i - 1) * 6 + _i][(j - 1) * 6 + _j] = b[0][i][j] * c[0][_i][_j] % p;
        }
      }
    }
  }
  d[0][m * 6 + 1][m * 6 + 1] = d[0][m * 6 + 2][m * 6 + 1] = 8, d[0][m * 6 + 1][m * 6 + 2] = 1;
  for (LL i = 1; i < m; i++) {
    d[0][(i - 1) * 6 + 1][m * 6 + 1] = (d[0][(i - 1) * 6 + 1][m * 6 + 1] + ((m + i & 1) ? 2 : -2) * b[0][i][m]) % p;
    for (LL _i = 1; _i <= 6; _i++) {
      for (LL j = m * 6 - 4; j <= m * 6; j++) {
        d[0][(i - 1) * 6 + _i][m * 6 + 1] = (d[0][(i - 1) * 6 + _i][m * 6 + 1] + d[0][(i - 1) * 6 + _i][j]) % p;
      }
    }
  }
  for (LL i(1); i < 61; i++) {
    copy(&a[i - 1][0][0], &a[i][0][0], &a[i][0][0]), Mul1(a[i], a[i - 1]);
  }
  for (LL i(1); i < 61; i++) {
    copy(&b[i - 1][0][0], &b[i][0][0], &b[i][0][0]), Mul1(b[i], b[i - 1]);
  }
  for (LL i(1); i < 61; i++) {
    copy(&c[i - 1][0][0], &c[i][0][0], &c[i][0][0]), Mul1(c[i], c[i - 1]);
  }
  for (LL i(1); i < 61; i++) {
    copy(&d[i - 1][0][0], &d[i][0][0], &d[i][0][0]), Mul2(d[i], d[i - 1], i);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> p >> m;
  SpawnMatrix();
  while (t--) {
    Init();
    cin >> n;
    for (LL i(0); i < 61; i++) {
      if (1LL << i & n) {
        Mul1(ans0, a[i]), Mul1(ans1, b[i]), Mul1(ans2, c[i]), Mul2(ans3, d[i], 0);
      }
    }
    cout << ans3[6][m * 6 + 1] * Pow(ans0[1][1], p - 2) % p << '\n';
  }
  return 0;
}
