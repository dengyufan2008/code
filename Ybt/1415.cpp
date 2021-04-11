#include <algorithm>
#include <cstdio>
using namespace std;
int n, q, bm[1001], cd[1001], xq[1001], again[1001] = {},
                                        ans[1001];
bool finded;
bool pd(int cd, int xq, int bm) {
  int x = 0, y = 1;
  while (cd != 0) {
    x = x + bm % 10 * y;
    y = y * 10;
    cd--;
  }
  return x == xq;
}
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &bm[i]);
  }
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &cd[i], &xq[i]);
  }
  sort(bm, bm + n);
  for (int i = 2; i <= n; i++) {
    if (bm[i - 1] == bm[i]) {
      again[i] = 1;
    }
  }
  for (int i = 1; i <= q; i++) {
    finded = false;
    for (int j = 1; j <= n; i++) {
      if (again[j]) {
        continue;
      }
      if (pd(cd[i], xq[i], bm[j])) {
        ans[i] = bm[j];
        finded = true;
        break;
      }
    }
    if (!finded) {
      ans[i] = -1;
    }
  }
  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
