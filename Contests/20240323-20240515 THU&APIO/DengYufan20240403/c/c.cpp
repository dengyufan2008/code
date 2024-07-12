#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 301;
int s, q, f[kMaxN][kMaxN][kMaxN][2];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> q;
  for (int i = 1; i < kMaxN; i++) {
    for (int j = 0; j < kMaxN; j++) {
      for (int k = 1; k < kMaxN; k++) {
        int l = 0, r = kMaxN - 1;
        while (l <= r) {
          int mid = l + r >> 1;
          if (i <= k - s * j || k - s * j > 0 && f[i - k + s * j][j][k][0] < mid || j && f[i][j - 1][k][0] < mid) {
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        f[i][j][k][1] = l;
        l = 0, r = kMaxN - 1;
        while (l <= r) {
          int mid = l + r >> 1;
          if (k <= i - s * mid || i - s * mid > 0 && f[i][j][k - i + s * mid][1] > mid || mid && f[i][j][k][1] >= mid) {
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }
        f[i][j][k][0] = r;
      }
    }
  }
  for (int o = 1, i, j, k, l; o <= q; o++) {
    cin >> i >> j >> k >> l;
    cout << (f[i][j][k][0] >= l ? "YES\n" : "NO\n");
  }
  return 0;
}
