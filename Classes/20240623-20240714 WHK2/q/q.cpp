#include <fstream>
#define LL long long

using namespace std;

ifstream cin("q.in");
ofstream cout("q.out");

const int kMaxN = 301, kMod = 1e9 + 7;
int n, m, p, a[kMaxN];
LL fact[kMaxN], _fact[kMaxN];
LL f[kMaxN][kMaxN];  // i 个点实线连成 j 棵树使得每棵树不超过 m 且最后用虚线连成 1 棵树的方案数
LL g[kMaxN][kMaxN];  // g_{i, 1} 为容斥后 i 个点连成 1 棵树的方案数 \ 
                        容斥的效果为若干 g_{i, 1} 分别以 i 个标号再次连成 1 棵树的方案数恰好为 f_{i, 1} \
                        g_{i, j} 为 i 个点 j 个 g_{x, 1} 的并集的方案数 (即 Exp) \
                        且为了之后统计答案每个 g_{x, 1} 带 x 的权
LL h[kMaxN][kMaxN];  // 考虑了颜色 i, 形成了 j 个 g_{x, 1} 的并集的方案数, 同样带权
LL ans;              // 将 h_{?, i} 的 i 个 g_{x, 1} 连成 1 棵树, 统计答案

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

LL C(int x, int y) { return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod; }

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
  for (int i = 1; i <= m; i++) {
    f[i][1] = Pow(i, i - 1);
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= i; j++) {
      for (int k = 1; k <= m && i + k <= n; k++) {
        Add(f[i + k][j + 1], f[i][j] * C(i + k - 1, i) % kMod * f[k][1]);
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
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= i; j++) {
      for (int k = 1; i + k <= n; k++) {
        Add(g[i + k][j + 1], g[i][j] * C(i + k - 1, i) % kMod * g[k][1]);
      }
    }
  }
  h[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i]) {
      for (int j = 0; j <= n; j++) {
        for (int k = 1; k <= a[i] && j + k <= n; k++) {
          Add(h[i][j + k], h[p][j] * g[a[i]][k]);
        }
      }
      p = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    Add(ans, h[p][i] * Pow(n, i - 2));
  }
  cout << ans << '\n';
  return 0;
}
