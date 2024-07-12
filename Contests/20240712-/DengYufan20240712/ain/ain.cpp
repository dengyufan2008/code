#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("ain.in");
ofstream cout("ain.out");

const int kMaxN = 5e5 + 1, kMaxM = 2e5 + 1, kMod = 1e9 + 7;
struct V {
  int l, r, d;
  vector<vector<int>> f;
} v[kMaxM];
int n, c, m, k, a[kMaxM], nt[kMaxM];
LL ans, f[kMaxN], g[kMaxN];

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
  cin >> n >> c >> m;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
  }
  nt[0] = -1;
  for (int i = 1, j; i < m; i++) {
    for (j = nt[i - 1]; j >= 0 && a[j + 1] != a[i]; j = nt[j]) {
    }
    nt[i] = a[j + 1] == a[i] ? j + 1 : -1;
  }
  for (int i = nt[m - 1], j; i >= 0; i = nt[j]) {
    if (nt[i] == -1) {
      k++, v[k].l = v[k].r = i, v[k].d = 1;
      v[k].f.resize(1), v[k].f[0].resize(1);
      break;
    }
    for (j = nt[i]; nt[j] >= 0 && i - nt[i] == j - nt[j]; j = nt[j]) {
    }
    k++, v[k].l = j, v[k].r = i, v[k].d = i - nt[i], v[k].f.resize(v[k].d);
    for (int o = 0; o < v[k].d; o++) {
      v[k].f[o].resize(1);
    }
  }
  g[0] = 1;
  for (int i = 1; i <= n; i++) {
    static LL w = Pow(c), t = 1;
    for (int j = 1; j <= k; j++) {
      LL x = v[j].f[(i - 1) % v[j].d].back();
      v[j].f[(i - 1) % v[j].d].push_back((x + f[i - 1]) % kMod);
    }
    if (i >= m) {
      f[i] = g[i - m];
      for (int j = 1; j <= k; j++) {
        // i - m + v[j].l + 1, i - m + v[j].r + 1
        int o = (i - m + v[j].l + 1) % v[j].d;
        f[i] = (f[i] - v[j].f[o][(i - m + v[j].r + 1) / v[j].d + 1] + kMod) % kMod;
        f[i] = (f[i] + v[j].f[o][(i - m + v[j].l + 1) / v[j].d]) % kMod;
      }
    }
    g[i] = (g[i - 1] * c - f[i] + kMod) % kMod;
    t = t * w % kMod, ans = (ans + f[i] * t) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
