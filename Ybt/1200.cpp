#include <bits/stdc++.h>
using namespace std;
long long num;
void fj(int a, int start) {
  if (a == 1) {
    num++;
    return;
  }
  for (int i = start; i <= a; i++) {
    if (a % i == 0) {
      fj(a / i, i);
    }
  }
}
int main() {
  int a, n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a);
    num = 0;
    fj(a, 2);
    printf("%lld\n", num);
  }
  exit(0);
}
