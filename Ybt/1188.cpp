#include <cstdio>
using namespace std;
int main() {
  int n, a, f1, f2, f3;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a);
    f1 = f2 = f3 = 1;
    for (int j = 3; j <= a; j++) {
      f3 = (f1 + f2) % 1000;
      f1 = f2;
      f2 = f3;
    }
    printf("%d\n", f3);
  }
  return 0;
}
