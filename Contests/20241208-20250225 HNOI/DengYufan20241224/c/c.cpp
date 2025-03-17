#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 71;
int n, m, p;
LL f[kMaxN][kMaxN][kMaxN][2], g[kMaxN][kMaxN][kMaxN], c[kMaxN][kMaxN];
// f_{i, s, t, 0/1}: 原本有 s 个点, 加了 i 层点后有 t 个点, 第一层转移不受限制, 第一层的第一个点连的边是否包含了 1
// g: f 最后一维的和

void Update(LL &x, LL y) { x = (x + y) % p; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  for (int i = 0; i <= m; i++) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
    }
  }
  for (int i = 1; i <= n; i++) {
    g[i][0][0] = 1;
    for (int s = 1; s <= m; s++) {
      for (int t = s; t <= m; t++) {
        //   连 0
        //     不转
        Update(f[i][s][t][0], g[i][s - 1][t - 1]);
        //     转 1 或 01
        for (int j = 1; j < i; j++) {
          for (int r = s; r <= t; r++) {
            Update(f[i][s][t][0], g[j][s - 1][r - 1] * f[i - j][r][t][1]);
          }
        }
        //   连 1
        Update(f[i][s][t][1], g[i][s - 1][t - 1]);
        if (s < t) {
          // 连 01
          //   不转
          Update(f[i][s][t][1], g[i][s - 1][t - 2]);
          //   转 1 或 01
          for (int j = 1; j < i; j++) {
            for (int r = s + 1; r <= t; r++) {
              Update(f[i][s][t][1], g[j][s - 1][r - 2] * f[i - j][r][t][1]);
            }
          }
        }
        //   统计 g
        Update(g[i][s][t], f[i][s][t][0] + f[i][s][t][1]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      LL ans = 0;
      for (int k = 1; k <= j; k++) {
        Update(ans, g[i][1][k] * c[j - 1][k - 1]);
      }
      cout << ans << " \n"[j == m];
    }
  }
  return 0;
}
