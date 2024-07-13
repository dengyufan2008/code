#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL l, w, u;
} e[1001];
LL n, x, ans, f[1001][1001];

int main() {
  cin >> n >> x;
  for (LL i = 1; i <= n; i++) {
    cin >> e[i].l >> e[i].w >> e[i].u;
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j <= x; j++) {
      f[i + 1][j] = max(f[i + 1][j], f[i][j] + e[i + 1].l);
      if (j + e[i + 1].u <= x) {
        f[i + 1][j + e[i + 1].u] = max(f[i + 1][j + e[i + 1].u], f[i][j] + e[i + 1].w);
      }
    }
  }
  for (LL i = 0; i <= x; i++) {
    ans = max(ans, f[n][i]);
  }
  cout << ans * 5 << endl;
  return 0;
}
