#include <fstream>
#define LL long long

using namespace std;

ifstream cin("dfs.in");
ofstream cout("dfs.out");

const int kMaxN = 36, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
int n, m, c, lg[1 << (kMaxN >> 1)];
LL ans, e[kMaxN];
LL f[1 << (kMaxN >> 1)][kMaxN][2][2];  // 是否有过最小值 是否链长至少为 1
LL g[1 << (kMaxN >> 1)][kMaxN][2];     // 开头是奇数还是偶数
LL wf[1 << (kMaxN >> 1)], wg[1 << (kMaxN >> 1)];

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> c, n += n & 1;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, e[x - 1] |= 1LL << y - 1, e[y - 1] |= 1LL << x - 1;
  }
  for (int i = 0; i < n >> 1; i++) {
    lg[1 << i] = i;
  }
  for (int i = 0; i < n; i++) {
    f[1 << (i >> 1)][i][1][0] = kInv2;
  }
  for (int s = 1; s < 1 << (n >> 1); s++) {
    int x = lg[s & -s];
    for (int i = 0; i < n; i++) {
      if (f[s][i][0][0] || f[s][i][0][1] || f[s][i][1][0] || f[s][i][1][1]) {
        LL f0 = f[s][i][0][0] + f[s][i][0][1], f1 = f[s][i][1][0] + f[s][i][1][1];
        for (int j = 0; j < x << 1; j++) {
          if ((s >> (j >> 1) & 1 ^ 1) && (e[i] >> j & 1)) {
            Update(f[s | 1 << (j >> 1)][j ^ 1][1][1], (f0 + f1) * c);
          }
        }
        for (int j = x + 1 << 1; j < n; j++) {
          if ((s >> (j >> 1) & 1 ^ 1) && (e[i] >> j & 1)) {
            Update(f[s | 1 << (j >> 1)][j ^ 1][0][1], f0 * c);
            Update(f[s | 1 << (j >> 1)][j ^ 1][1][1], f1 * c);
          }
        }
        for (int j = 0; j < x << 1; j++) {
          if (s >> (j >> 1) & 1 ^ 1) {
            Update(f[s | 1 << (j >> 1)][j][1][0], f[s][i][1][1] * kInv2);
          }
        }
        for (int j = x + 1 << 1; j < n; j++) {
          if (s >> (j >> 1) & 1 ^ 1) {
            Update(f[s | 1 << (j >> 1)][j][0][0], f[s][i][1][1] * kInv2);
          }
        }
      }
    }
  }
  for (int s = 0; s < 1 << (n >> 1); s++) {
    for (int i = 0; i < n; i++) {
      Update(wf[s], f[s][i][1][1]);
    }
  }
  for (int i = 0; i < n; i++) {
    g[1 << (i >> 1)][i ^ 1][i & 1] = kInv2;
  }
  for (int s = 1; s < 1 << (n >> 1); s++) {
    int x = lg[s & -s];
    for (int i = 0; i < n; i++) {
      for (int o = 0; o < 2; o++) {
        if (g[s][i][o]) {
          g[s][i][o] = g[s][i][o] * c % kMod;
          for (int j = x + 1 << 1; j < n; j++) {
            if ((s >> (j >> 1) & 1 ^ 1) && (e[i] >> j & 1)) {
              Update(g[s | 1 << (j >> 1)][j ^ 1][o], g[s][i][o]);
            }
          }
          if (e[i] >> (x << 1 | o) & 1) {
            Update(wg[s], g[s][i][o]);
            for (int j = 0; j < x << 1; j++) {
              if (s >> (j >> 1) & 1 ^ 1) {
                Update(g[s | 1 << (j >> 1)][j ^ 1][j & 1], g[s][i][o] * kInv2);
              }
            }
          }
        }
      }
    }
  }
  wf[0] = wg[0] = 1;
  for (int i = 0; i < n >> 1; i++) {
    for (int s = 0; s < 1 << (n >> 1); s++) {
      if (s >> i & 1) {
        Update(wg[s], wg[s ^ 1 << i]);
      }
    }
  }
  for (int s = 0; s < 1 << (n >> 1); s++) {
    Update(ans, wf[s] * wg[~(-1 << (n >> 1)) ^ s]);
  }
  cout << ans << '\n';
  return 0;
}
