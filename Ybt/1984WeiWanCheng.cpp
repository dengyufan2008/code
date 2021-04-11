#include <cstdio>
using namespace std;
int main() {
  int t, n, m;
  scanf("%d%d%d", &t, &n, &m);
  int p[t + 1][n + 1];
  for (int i = 1; i <= t; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &p[i][j]);
    }
  }
  printf("%d", m);
  return 0;
}
