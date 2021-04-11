#include <cstdio>
using namespace std;
int main() {
  int n, k, p1, p2, p3;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &k);
    p1 = 1;
    p2 = 2;
    if (k == 1) {
      printf("1\n");
      continue;
    }
    if (k == 2) {
      printf("2\n");
      continue;
    }
    for (int j = 3; j <= k; j++) {
      p3 = (p1 + 2 * p2) % 32767;
      p1 = p2;
      p2 = p3;
    }
    printf("%d\n", p3);
  }
  return 0;
}
