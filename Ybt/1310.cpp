#include <cstdio>
#include <iostream>
using namespace std;
int n, cx[10001], ans = 0, i, j;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &cx[i]);
  }
  for (i = n - 1; i >= 1; i--) {
    for (j = 1; j <= i; j++) {
      if (cx[j] > cx[j + 1]) {
        swap(cx[j], cx[j + 1]);
        ans++;
      }
    }
  }
  printf("%d", ans);
  return 0;
}
