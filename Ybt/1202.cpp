#include <bits/stdc++.h>
using namespace std;
int ans[1000001];
int pell(int k) {
  if (k == 1) {
    return ans[k] = 1;
  }
  if (k == 2) {
    return ans[k] = 2;
  }
  if (ans[k] != -1) {
    return ans[k];
  }
  return ans[k] = (2 * pell(k - 1) + pell(k - 2)) % 32767;
}
int main() {
  for (int i = 0; i <= 1000000; i++) {
    ans[i] = -1;
  }
  for (int i = 1; i <= 1000000; i++) {
    pell(i);
  }
  int n, x;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x);
    printf("%d\n", ans[x]);
  }
  exit(0);
}
