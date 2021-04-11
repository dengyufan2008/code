#include <cstdio>
using namespace std;
int main() {
  long long x, y, z, cc[101] = {0}, r[101] = {0};
  scanf("%lld%lld%lld", &x, &y, &z);
  for (long long i = 1; i <= x; i++) {
    cc[i] = 1;
    r[i] = 0;
  }
  for (long long i = x + 1; i <= z + 1; i++) {
    r[i] = cc[i - x] * y;
    cc[i] = cc[i - 1] + r[i - 2];
  }
  printf("%lld", cc[z + 1]);
  return 0;
}
