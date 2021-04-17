#include <bits/stdc++.h>
using namespace std;
long long int ans[31] = {};
long long int my_floor(long long int n) {
  if (n == 1) {
    return 1;
  }
  if (n == 2) {
    return 2;
  }
  return ans[n] =
             ((ans[n - 1] == 0 ? my_floor(n - 1) : ans[n - 1]) +
              (ans[n - 2] == 0 ? my_floor(n - 2) : ans[n - 2]));
}
int main() {
  long long int n;
  ans[1] = 1;
  ans[2] = 2;
  for (int i = 1; scanf("%lld", &n) == 1; i++) {
    printf("%lld\n", my_floor(n));
  }
  return 0;
}
