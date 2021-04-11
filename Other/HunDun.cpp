#include <bits/stdc++.h>
using namespace std;
int main() {
  double u, f;
  printf("Please input u(0<u<1):");
  cin >> u;
  printf("Please input f(f>0):");
  cin >> f;
  printf("%lf", u);
  for (int i = 2;; i++) {
    u = u * (1 - u) * f;
    printf("->%lf", u);
    if (i % 10 == 0) {
      printf("\n");
    }
  }
  exit(0);
}
