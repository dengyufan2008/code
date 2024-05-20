#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("pantheon.in");
ofstream cout("pantheon.out");

int n, m, t, p;
class Mod {
 private:
  uint64_t p, m;

 public:
  Mod(uint64_t kMod) : p(kMod) {
    m = ((__int128_t)1 << 64) / p;
  }

  uint64_t operator()(uint64_t x) const {  // needs to be positive
    return x - ((__int128_t(x) * m) >> 64) * p;
  }
} mod(1);

namespace Sub2 {
const int kMaxN = 201;
LL ans, c[kMaxN << 1][kMaxN], f[2][kMaxN][kMaxN];

int main() {
  c[0][0] = 1;
  for (int i = 1; i <= n + m - 2; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= n; j++) {
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
      c[i][j] >= p && (c[i][j] -= p);
    }
  }
  t++, f[0][0][0] = 1;
  for (int i = 1; i <= t; i++) {
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= m; k++) {
        f[i & 1][j][k] = 0;
        if (j) {
          f[i & 1][j][k] += f[i & 1 ^ 1][j - 1][k];
          f[i & 1][j][k] >= p && (f[i & 1][j][k] -= p);
        }
        if (k) {
          f[i & 1][j][k] += f[i & 1 ^ 1][j][k - 1];
          f[i & 1][j][k] >= p && (f[i & 1][j][k] -= p);
        }
        for (int _j = 0; _j < j; _j++) {
          for (int _k = 0; _k < k; _k++) {
            int x = j - _j, y = k - _k;
            int w1 = mod(c[x + y - 2][x - 1] * c[x + y - 2][y - 1]);
            int w2 = mod(c[x + y - 2][x] * c[x + y - 2][y]);
            f[i & 1][j][k] += mod(f[i & 1 ^ 1][_j][_k] * (w1 - w2 + p) * 2);
            f[i & 1][j][k] >= p && (f[i & 1][j][k] -= p);
          }
        }
      }
    }
  }
  cout << f[t & 1][n][m] << '\n';
  return 0;
}
}

namespace Sub6 {
const int kMaxN = 4e6 + 1;
int k, prime[kMaxN], c[kMaxN];
bool b[kMaxN];
LL w;
vector<int> l[kMaxN];

LL Pow(LL x, int y) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = mod(ans * x);
    }
    x = mod(x * x);
  }
  return ans;
}

LL C(int x, int y) {
  if (y < 0 || y > x) {
    return 0;
  }
  int z = x - y;
  y > z ? swap(y, z) : void();
  for (int i = 2; i <= y; i++) {
    for (int j : l[i]) {
      c[j]--;
    }
  }
  for (int i = z + 1; i <= x; i++) {
    for (int j : l[i]) {
      c[j]++;
    }
  }
  LL w = 1;
  for (int i = 1; i <= k; i++) {
    w = mod(w * Pow(prime[i], c[i])), c[i] = 0;
  }
  return w;
}

int main() {
  b[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      prime[++k] = i;
    }
    for (int j = 1; j <= k; j++) {
      int w = i * prime[j];
      if (w < kMaxN) {
        b[w] = 1;
        if (!(i % prime[j])) {
          break;
        }
      } else {
        break;
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    l[prime[i]].push_back(i);
  }
  for (int i = 2; i < kMaxN; i++) {
    if (b[i]) {
      for (int j = 1; j <= k; j++) {
        if (!(i % prime[j])) {
          l[i] = l[i / prime[j]];
          l[i].push_back(j);
          break;
        }
      }
    }
  }
  w = C(n + m - 2, n - 1);
  w = mod(w * w) - mod(C(n + m - 2, n) * C(n + m - 2, m)) + p;
  w >= p && (w -= p);
  cout << w << '\n';
  return 0;
}
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t >> p, mod = Mod(p);
  if (!t) {
    return Sub6::main();
  } else if (n <= 200 && m <= 200) {
    return Sub2::main();
  } else {
    return Sub6::main();
  }
  return 0;
}
