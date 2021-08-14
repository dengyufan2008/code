#include <iostream>
#define LL long long

using namespace std;

const LL kInf = 0x7fffffffffffff;
LL n, m, ans = kInf, a[101][101], f[101][101];

int main() {
  for (int i = 1; i <= 100; i++) {
    for (int j = 1; j <= 100; j++) {
      f[i][j] = kInf * (i != j);
    }
  }
  cin >> n >> m;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    f[x][y] = f[y][x] = a[x][y] = a[y][x] = z;
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j < i; j++) {
      for (LL k = j + 1; k < i; k++) {
        ans = min(ans, f[i][j] + a[i][k] + a[j][k]);
      }
    }
    for (LL j = 1; j <= n; j++) {
      for (LL k = 1; k <= n; k++) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }
  if (ans == kInf) {
    cout << "No solution." << endl;
  } else {
    cout << ans << endl;
  }
  return 0;
}
