#include <fstream>
#define LL long long

using namespace std;

ifstream cin("q.in");
ofstream cout("q.out");

// const int kMaxN = 301, kMod = 1e9 + 7;
const int kMaxN = 5, kMod = 1e9 + 7;
int n, m, p, a[kMaxN];
LL ans, f[kMaxN][kMaxN], g[kMaxN][kMaxN], h[kMaxN][kMaxN];
LL fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  y = (y + kMod - 1) % (kMod - 1);
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Add(LL &x, LL y) { x = (x + y) % kMod; }

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
  for (int i = 1, x; i <= n; i++) {
    cin >> x, a[x]++;
  }
  f[0][0] = 1;
  for (int i = 1; i <= m; i++) {
    LL w = Pow(i, i - 1);
    for (int j = 0; j + i <= n; j++) {
      for (int k = 0; k < n; k++) {
        Add(f[j + i][k + 1], f[j][k] * w);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = f[i][j] * Pow(i, j - 2) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      Add(g[i][1], j & 1 ? f[i][j] : kMod - f[i][j]);
    }
    g[i][1] = g[i][1] * i % kMod;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j + i <= n; j++) {
      for (int k = 1; k < n; k++) {
        Add(g[j + i][k + 1], g[j][k] * g[i][1]);
      }
    }
  }
  h[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i]) {
      for (int j = 1; j <= a[i]; j++) {
        for (int k = 0; k <= n - j; k++) {
          Add(h[i][k + j], h[p][k] * g[a[i]][j]);
        }
        g[a[i]][j];
      }
      p = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    h[p][i] = h[p][i] * Pow(n, i - 2) % kMod;
    Add(ans, h[p][i]);
  }
  cout << ans << '\n';
  return 0;
}
