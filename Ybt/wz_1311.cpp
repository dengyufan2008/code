#include <bits/stdc++.h>
using namespace std;
int n, ans = 0;
int main() {
  scanf("%d", &n);
  int a[n + 1];
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n - 1; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (a[i] > a[j]) {
        ans++;
      }
    }
  }
  printf("%d", ans);
  return 0;
}
