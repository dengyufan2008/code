#include <bits/stdc++.h>

#include "number.h"
using namespace std;

int T, m;
int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
  scanf("%d", &T);
  for (int tc = 0; tc < T; tc++) {
    scanf("%d", &m);
    int n = 1 << m;
    vector<int> a(n), b(n);
    for (int i = 1; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; i++) {
      scanf("%d", &b[i]);
    }
    printf("%lld\n", solve(m, a, b));
  }
  return 0;
}
