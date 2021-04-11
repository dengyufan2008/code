#include <cstdio>
using namespace std;
int main() {
  int zy, xc, qm, ans;
  scanf("%d%d%d", &zy, &xc, &qm);
  ans = zy * 2 / 10 + xc * 3 / 10 + qm * 5 / 10;
  printf("%d", ans);
  return 0;
}
