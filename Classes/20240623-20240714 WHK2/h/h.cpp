#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

// const int kMaxN = 601, kMod = 1e9 + 7;
const int kMaxN = 5, kMod = 1e9 + 7;
int n, m, k, a[kMaxN], b[kMaxN], inva[kMaxN], invb[kMaxN], la[kMaxN], lb[kMaxN];
LL ans, f[kMaxN][kMaxN], g[kMaxN][kMaxN], h[kMaxN + 1][kMaxN], pw[kMaxN];

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
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] < 0) {
      b[++m] = a[i], i--, n--;
    }
  }
  sort(a + 1, a + n + 1, greater<int>());
  sort(b + 1, b + m + 1), f[0][0] = g[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    f[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      f[i][j] = (f[i - 1][j - 1] * a[i] + f[i - 1][j]) % kMod;
    }
  }
  for (int i = 1; i <= m; i++) {
    g[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      g[i][j] = (g[i - 1][j - 1] * (b[i] + kMod) + g[i - 1][j]) % kMod;
    }
  }
  for (int x = k - 1, y = 1; x >= 0; x -= 2, y += 2) {
    ans = (ans + f[n][x] * g[m][y]) % kMod;
  }
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j <= i; j++) {
      f[i][j] = (f[i][j] - f[i - 1][j] + kMod) % kMod;
    }
  }
  for (int i = m; i >= 1; i--) {
    for (int j = 0; j <= i; j++) {
      g[i][j] = (g[i][j] - g[i - 1][j] + kMod) % kMod;
    }
  }
  for (int i = 1, j = 1, o = 1; i <= n || j <= m;) {
    if (i <= n && (j > m || a[i] + b[j] >= 0)) {
      la[i++] = o++;
    } else {
      lb[j++] = o++;
    }
  }
  for (int i = 1; i <= n; i++) {
    inva[i] = Pow(a[i]);
  }
  for (int i = 1; i <= m; i++) {
    invb[i] = Pow(b[i] + kMod);
  }
  if (k & 1) {
    h[m + 1][0] = 1;
    for (int i = m; i >= 1; i--) {
      h[i][0] = 1;
      for (int j = 1; j <= m - i + 1; j++) {
        h[i][j] = (h[i + 1][j - 1] * (b[i] + kMod) + h[i + 1][j]) % kMod;
      }
    }
    for (int i = 1; i <= m; i++) {
      for (int j = 0; j <= m - i + 1; j++) {
        h[i][j] = (h[i][j] - h[i + 1][j] + kMod) % kMod;
      }
    }
    for (int i = 1; i <= m; i++) {
      ans = (ans + h[i][k] * (pw[i - 1] - 1)) % kMod;
    }
  }
  for (int x = k, y = 0; x >= 0; x -= 2, y += 2) {
    for (int i = x; i <= n; i++) {
      for (int j = y; j <= m; j++) {
        ans = (ans + f[i][x] * g[j][y] % kMod * pw[n - i] % kMod * pw[m - j]) % kMod;
      }
    }
  }
  for (int x = k - 1, y = 1; x >= 0; x -= 2, y += 2) {
    for (int i = x; i < n; i++) {
      for (int j = y; j < m; j++) {
        for (int p = i + 1; p <= n; p++) {
          for (int q = j + 1; q <= m; q++) {
            if (1LL * a[i] * a[p] >= 1LL * b[j] * b[q]) {
              ans = (ans + f[i][x] * g[j][y] % kMod * invb[j] % kMod * a[p] % kMod * pw[n - i] % kMod * pw[m - j]) % kMod;
            } else {
              ans = (ans + f[i][x] * g[j][y] % kMod * inva[i] % kMod * (b[q] + kMod) % kMod * pw[n - i] % kMod * pw[m - j]) % kMod;
            }
            if (ans < 0) {
              ans++, ans--;
            }
          }
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
