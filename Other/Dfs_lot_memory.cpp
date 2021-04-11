#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, a[0];

void Print(int a[]) {
  for (int i = 0; i < n; i++) {
    printf("%5d", a[i]);
  }
  printf("\n");
}

void Dfs(int a[], int len) {
  if (len == n) {
    Print(a);
    return;
  }
  bool b[n + 1] = {};
  for (int i = 0; i < len; i++) {
    b[a[i]] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      int c[len + 1];
      copy(a, a + len, c);
      c[len] = i;
      Dfs(c, len + 1);
    }
  }
}

int main() {
  scanf("%d", &n);
  Dfs(a, 0);
  return 0;
}
