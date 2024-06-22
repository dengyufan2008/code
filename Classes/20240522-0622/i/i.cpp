#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 41;
int n;
LL f[kMaxN][kMaxN][kMaxN], g[kMaxN][kMaxN][kMaxN];
bool b[kMaxN][kMaxN];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, n *= 2;
  for (int i = 1; i <= n; i++) {
    f[i][i][i] = 1;
    for (int j = 1; j <= n; j++) {
      cin >> ch, b[i][j] = ch == '1';
      g[i][i][j] = i < j && b[i][j];
    }
  }
  for (int o = 3; o <= n; o += 2) {
    for (int l = 1, r; (r = l + o - 1) <= n; l++) {
      for (int p = l + 1; p < r; p++) {
        for (int q = p; q < r; q++) {
          LL w = 0;
          for (int x = q + 1; x <= r; x++) {
            w += g[l][p - 1][x] * f[q + 1][r][x];
          }
          for (int z = p; z <= q; z++) {
            f[l][r][z] += f[p][q][z] * w;
          }
        }
      }
      for (int x = r + 1; x <= n; x++) {
        for (int y = l; y <= r; y++) {
          if (b[x][y]) {
            g[l][r][x] += f[l][r][y];
          }
        }
      }
    }
  }
  cout << g[1][n - 1][n] << '\n';
  return 0;
}
