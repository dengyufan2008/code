#include <fstream>

using namespace std;

ifstream cin("hctam.in");
ofstream cout("hctam.out");

const int kMaxN = 12;
int n, m, p, ans, f[2][kMaxN + 1][1 << kMaxN], r[kMaxN + 1][kMaxN + 1][1 << kMaxN];

void Update(int &x, int y) { x = (x + y) % p; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      for (int s = 0; s < (1 << n); s++) {
        int &t = r[i][j][s] = s;
        for (int o = j + 1; o < i; o++) {
          if ((s >> o - 1 & 1 ^ 1) && (s >> o & 1)) {
            t ^= 1 << o;
          }
        }
        for (int o = i + 1; o < j; o++) {
          if ((s >> o - 1 & 1) && (s >> o & 1 ^ 1)) {
            t ^= 1 << o - 1;
          }
        }
      }
    }
  }
  fill(&f[1][0][0], &f[1][n + 1][0], 1);
  for (int o = 1; o < m; o++) {
    fill(&f[o & 1 ^ 1][0][0], &f[o & 1 ^ 1][n + 1][0], 0);
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        for (int s = 0; s < (1 << n); s++) {
          Update(f[o & 1 ^ 1][j][r[i][j][s]], f[o & 1][i][s]);
        }
      }
    }
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < n; j++) {
        for (int s = 0; s < (1 << n); s++) {
          if (s >> j & 1) {
            Update(f[o & 1 ^ 1][i][s ^ 1 << j], f[o & 1 ^ 1][i][s]);
          }
        }
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int s = 0; s < (1 << n); s++) {
      Update(ans, f[m & 1][i][s]);
    }
  }
  cout << ans;
  return 0;
}
