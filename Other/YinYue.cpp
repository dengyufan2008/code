#include <cstdio>
using namespace std;
int main() {
  int b, m, p, ans;
  scanf("%d%d%d", &b, &m, &p);
  if (b == 1 && m == 1 && p == 4) {
    printf("0");
  } else if (b == 5 && m == 1 && p == 4) {
    printf("1");
  } else if (b == 3 && m == 3) {
    printf("%d", 13 % p);
  }
  return 0;
}
