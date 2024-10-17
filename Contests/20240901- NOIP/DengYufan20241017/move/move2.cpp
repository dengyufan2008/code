// slow
#include <fstream>

using namespace std;

ifstream cin("move.in");
ofstream cout("move.ans");

const int kMaxN = 1e6 + 2, kInf = 1e9;
int t, n, k, f[kMaxN][2], r[kMaxN][2], p[kMaxN][2];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  for (int u = 1; u <= t; u++) {
    for (int i = 1; i < kMaxN; i++) {
      r[i][0] = r[i][1] = p[i][0] = p[i][1] = 0;
      f[i][0] = f[i][1] = -kInf;
    }
    cin >> n >> k;
    for (int i = 1, x, y, z; i <= n; i++) {
      cin >> x >> y >> z, z--;
      r[y][z] = 1, p[x][z] += y;
      if (y + 1 < kMaxN) {
        p[y + 1][z] -= y;
      }
    }
    for (int i = 1; i < kMaxN; i++) {
      r[i][0] += r[i - 1][0], r[i][1] += r[i - 1][1];
      p[i][0] += p[i - 1][0], p[i][1] += p[i - 1][1];
    }
    f[1][0] = f[k][1] = 0;
    for (int i = 1; i < kMaxN; i++) {
      f[i + 1][0] = max(f[i + 1][0], f[i][0] + (p[i][0] == i));
      f[i + 1][1] = max(f[i + 1][1], f[i][1] + (p[i][1] == i));
      if (i + k < kMaxN) {
        if (p[i][0]) {
          if (p[i][0] < i + k + k) {
            f[i + k][1] = max(f[i + k][1], f[i][0] + 1);
          } else {
            f[i + k][1] = max(f[i + k][1], f[i][0]);
            f[p[i][0] - k + 1][1] = max(f[p[i][0] - k + 1][1],
                                        f[i][0] + 1 + r[p[i][0] - k][1] - r[i + k - 1][1]);
          }
        }
        if (p[i][1]) {
          if (p[i][1] < i + k + k) {
            f[i + k][0] = max(f[i + k][0], f[i][1] + 1);
          } else {
            f[i + k][0] = max(f[i + k][0], f[i][1]);
            f[p[i][1] - k + 1][0] = max(f[p[i][1] - k + 1][0],
                                        f[i][1] + 1 + r[p[i][1] - k][0] - r[i + k - 1][0]);
          }
        }
      }
    }
    cout << max(f[kMaxN - 1][0], f[kMaxN - 1][1]) << '\n';
  }
  return 0;
}
