#include <iostream>
#define LL long long

using namespace std;

LL n, m, a[501], d[501][501], f[501][501];

int main() {
  cin >> n >> m;
  for (LL i = 2; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  fill(&f[0][0], &f[500][500] + 1, 0x7fffffff);
  f[0][0] = 0;
  for (LL i = 1; i <= n; i++) {
    for (LL j = i; j <= n; j++) {
      LL p = (i + j) >> 1;
      for (LL k = i; k <= j; k++) {
        d[i][j] += abs(a[k] - a[p]);
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      if (j > i) {
        f[i][j] = 0;
      } else {
        for (LL k = j - 1; k <= i; k++) {
          f[i][j] = min(f[i][j], f[k][j - 1] + d[k + 1][i]);
        }
      }
    }
  }
  cout << f[n][m] << endl;
  return 0;
}
