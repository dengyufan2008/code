#include <fstream>

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 51, kMaxM = 6, kMod = 1e9 + 7;
const int kMove[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int t, n, m, _m, h, x, y, ans;
int f[kMaxN][kMaxN][kMaxN][kMaxM << 1][kMaxM << 1][kMaxM];
int g[kMaxN][kMaxN][kMaxN];
bool a[kMaxN][kMaxN];

void Init() {
  int x1, y1, x2, y2;
  char c;
  cin >> n >> m >> _m >> h, m -= _m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c, a[i][j] = c == '#';
      if (c == 'P') {
        x1 = i, y1 = j;
      } else if (c == 'E') {
        x2 = i, y2 = j;
      }
    }
  }
  for (int i = 0; i <= n + 1; i++) {
    a[0][i] = a[i][0] = a[n + 1][i] = a[i][n + 1] = 1;
  }
  x = x2 - x1, y = y2 - y1, f[0][x1][y1][kMaxM][kMaxM][h] = 1;
}

void Update(int &x, int y) { x += y, x >= kMod && (x -= kMod); }

void CalcF() {
  for (int i = 0; i < m; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        for (int p = -h; p <= h; p++) {
          for (int q = -h; q <= h; q++) {
            for (int l = 1; l <= h; l++) {
              int w = f[i][j][k][p + kMaxM][q + kMaxM][l];
              if (w) {
                f[i][j][k][p + kMaxM][q + kMaxM][l] = 0;
                for (int o = 0; o < 4; o++) {
                  int _j = j + kMove[o][0], _k = k + kMove[o][1];
                  if (!a[_j][_k]) {
                    if (a[_j + x + p][_k + y + q]) {
                      if (l == 1) {
                        Update(g[0][_j][_k], w);
                      } else if (i + 1 < m) {
                        int _p = p - kMove[o][0], _q = q - kMove[o][1];
                        Update(f[i + 1][_j][_k][_p + kMaxM][_q + kMaxM][l - 1], w);
                      }
                    } else if (i + 1 < m) {
                      Update(f[i + 1][_j][_k][p + kMaxM][q + kMaxM][l], w);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void CalcG() {
  for (int i = 0; i < _m; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        int w = g[i][j][k];
        if (w) {
          g[i][j][k] = 0;
          for (int o = 0; o < 4; o++) {
            int _j = j + kMove[o][0], _k = k + kMove[o][1];
            if (!a[_j][_k]) {
              Update(g[i + 1][_j][_k], w);
            }
          }
        }
      }
    }
  }
  for (int j = 1; j <= n; j++) {
    for (int k = 1; k <= n; k++) {
      Update(ans, g[_m][j][k]), g[_m][j][k] = 0;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    Init(), CalcF(), CalcG(), cout << ans << '\n', ans = 0;
  }
  return 0;
}
