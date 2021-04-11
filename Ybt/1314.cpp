#include <cstdio>
using namespace std;
int main() {
  long long a[21][21];
  int n, m, c1, c2, ma[9][2];
  scanf("%d%d%d%d", &n, &m, &c1, &c2);
  for (int i = 1; i <= 20; i++) {
    for (int j = 1; j <= 20; j++) {
      a[i][j] = 1;
    }
  }
  a[c1 + 2][c2 + 1] = a[c1 + 1][c2 + 2] = a[c1 - 1][c2 + 2] =
      a[c1 - 2][c2 + 1] = a[c1 - 2][c2 - 1] = a[c1 - 1][c2 - 2] =
          a[c1 + 1][c2 - 2] = a[c1 + 2][c2 - 1] = a[c1][c2] = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= m; j++) {
      if (a[i][j]) {
        a[i][j] = a[i - 1][j] + a[i][j - 1];
      }
    }
  }
  printf("%lld", a[n][m]);
  return 0;
}
