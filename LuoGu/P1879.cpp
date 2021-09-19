#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int m, n, ans, a[12][12], d[2][1 << 12];

int M(int x, int y) {
  return ((x - 1) * n + y) & 1;
}

int main() {
  cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  d[1][0] = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      fill(&d[!M(i, j)][0], &d[!M(i, j)][1 << 12], 0);
      for (int k = 0; k < (1 << 12); k++) {
        d[!M(i, j)][k >> 1] += d[M(i, j)][k];
        if (a[i][j] && !(k & 1) && (j == 1 || !(k & (1 << n - 1)))) {
          d[!M(i, j)][(k >> 1) + (1 << n - 1)] += d[M(i, j)][k];
        }
      }
    }
  }
  for (int i = 0; i < (1 << 12); i++) {
    ans += d[M(m, n)][i];
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
