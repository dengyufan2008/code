#include <fstream>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 701, kMod = 998244353;
int n, m, a[kMaxN], b[kMaxN], c[kMaxN];
LL f[2][kMaxN][kMaxN];  // (x, z1, i)
LL g[2][kMaxN][kMaxN];  // (y, z2, j)
LL s[kMaxN][kMaxN];     // (z1, i)
LL t[kMaxN][kMaxN];     // (z2, j)
LL r[kMaxN][kMaxN];     // (z2, i)
LL ans[kMaxN];
LL fact[kMaxN], _fact[kMaxN];

void Update(LL &x, LL y) { x = (x + y) % kMod; }

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
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  f[1][1][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j; k < n; k++) {
        f[i & 1 ^ 1][j][k] = 0;
      }
    }
    for (int j = i; j < n; j++) {
      for (int k = j; k < n; k++) {
        Update(s[j][k], f[i & 1][j][k] * a[i + 1]);
        Update(f[i & 1][j][k + 1], f[i & 1][j][k] * j);
        Update(f[i & 1][j + 1][k + 1], f[i & 1][j][k] * (k - j));
        Update(f[i & 1 ^ 1][j + 1][k + 1], f[i & 1][j][k]);
      }
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      s[i][j] = s[i][j] * _fact[j] % kMod;
    }
  }
  g[1][1][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < n; j++) {
      for (int k = max(i + 1, j); k < n; k++) {
        g[i & 1 ^ 1][j][k] = 0;
      }
    }
    for (int j = 1; j < n; j++) {
      for (int k = max(i, j); k < n; k++) {
        Update(t[j][k], g[i & 1][j][k] * b[i + 1]);
        Update(g[i & 1][j][k + 1], g[i & 1][j][k] * (j - 1));
        Update(g[i & 1][j + 1][k + 1], g[i & 1][j][k] * (k - j + 1));
        Update(g[i & 1 ^ 1][j][k + 1], g[i & 1][j][k]);
      }
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      t[i][j] = t[i][j] * _fact[j] % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    Update(r[i][0], 1LL * c[i] * a[1]);  // s[0][0] = a[1]
    for (int j = 1; j <= i; j++) {
      for (int k = j; k < n; k++) {
        Update(r[i - j][k], c[i] * s[j][k]);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    Update(ans[i + 1], r[1][i] * b[1]);  // t[1][0] = b[1]
    for (int j = 1; j < n; j++) {
      for (int k = j; i + k < n; k++) {
        Update(ans[i + k + 1], r[j][i] * t[j][k]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] * fact[i - 1] % kMod << " \n"[i == n];
  }
  return 0;
}
