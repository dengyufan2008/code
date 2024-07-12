#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMod = 998244353;
LL n, m, k, s, t, l, inv, a[253], b[1 << 25], d[253][253];
bool o[6][6];
char ch;

LL R(LL x, LL y) {
  return x * m + y;
}

LL Pow(LL x, LL y = kMod - 2) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL PopCount(LL x) {
  LL c = 0;
  for (; x; x >>= 1) {
    c++;
  }
  return c;
}

void S(LL x, LL y) {
  if (x == 0 && y == m) {
    LL p = 0;
    for (LL i = 0; i < n; i++) {
      for (LL j = 0; j < m; j++) {
        LL k = o[i][j];
        if (i) {
          k |= p >> R(i - 1, j) & 1;
        }
        if (j) {
          k |= p >> R(i, j - 1) & 1;
        }
        p |= k << R(i, j);
      }
    }
    a[l] = p, b[p] = l, l++;
    return;
  }
  if (x > 0) {
    o[x - 1][y] = 1, S(x - 1, y), o[x - 1][y] = 0;
  }
  if (y < m) {
    o[x][y + 1] = 1, S(x, y + 1), o[x][y + 1] = 0;
  }
}

LL M(LL s) {
  for (LL i = n - 1; i >= 0; i--) {
    for (LL j = m - 1; j >= 0; j--) {
      LL k = s >> R(i, j) & 1;
      if (i < n - 1) {
        k &= s >> R(i + 1, j) & 1;
      }
      if (j < m - 1) {
        k &= s >> R(i, j + 1) & 1;
      }
      s ^= ((s >> R(i, j)) & 1) << R(i, j);
      if (k) {
        s |= k << R(i, j);
      }
    }
  }
  return s;
}

LL T(LL s, LL x, LL y, bool w) {
  for (LL i = 0; i <= x; i++) {
    for (LL j = 0; j <= y; j++) {
      s ^= ((s >> R(i, j)) & 1) << R(i, j);
      if (((t >> R(i, j)) & 1) ^ w) {
        s |= (((t >> R(i, j)) & 1) ^ w) << R(i, j);
      }
    }
  }
  return s;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      cin >> ch;
      s |= (ch == 'B') << R(i, j);
    }
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      cin >> ch;
      t |= (ch == 'B') << R(i, j);
    }
  }
  S(n, 0), inv = Pow(n * m * 2), s ^= t ^ ((1 << n * m) - 1);
  for (LL i = 1; i < l; i++) {
    d[i][i] = kMod - 1;
    for (LL j = 0; j < n; j++) {
      for (LL k = 0; k < m; k++) {
        LL p = M(T(a[i], j, k, 0));
        d[i][b[p]] = (d[i][b[p]] + inv) % kMod;
        p = M(T(a[i], j, k, 1));
        d[i][b[p]] = (d[i][b[p]] + inv) % kMod;
        d[i][l] = (d[i][l] - (j + 1) * (k + 1) * 2 * inv % kMod + kMod) % kMod;
      }
    }
  }
  d[0][0] = 1;
  for (LL i = 0; i < l; i++) {
    LL mx = i;
    for (LL j = i + 1; j < l; j++) {
      if (d[j][i] > d[mx][i]) {
        mx = j;
      }
    }
    if (mx != i) {
      for (LL j = i; j <= l; j++) {
        swap(d[i][j], d[mx][j]);
      }
    }
    inv = Pow(d[i][i]);
    for (LL j = l; j >= i; j--) {
      d[i][j] = d[i][j] * inv % kMod;
    }
    for (LL j = i + 1; j < l; j++) {
      for (LL k = l; k >= i; k--) {
        d[j][k] = (d[j][k] - d[j][i] * d[i][k] % kMod + kMod) % kMod;
      }
    }
  }
  for (LL i = l - 1; i >= 0; i--) {
    for (LL j = i - 1; j >= 0; j--) {
      d[j][l] = (d[j][l] - d[j][i] * d[i][l] % kMod + kMod) % kMod;
      d[j][i] = 0;
    }
  }
  cout << d[b[M(s)]][l];
  return 0;
}
