#include <bits/stdc++.h>
using namespace std;
long long hf(int n, int k) {
  if (n < k || k == 0) {
    return 0;
  }
  if (k == 1 || k == n) {
    return 1;
  }
  return hf(n - 1, k - 1) + k * hf(n - 1, k);
}
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  printf("%lld", hf(n, k));
  exit(0);
}
