#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL w, v;
} e[101];
LL n, w, ans, f[101][100001];

int main() {
  cin >> n >> w;
  for (LL i = 1; i <= n; i++) {
    cin >> e[i].w >> e[i].v;
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j <= w; j++) {
      f[i + 1][j] = max(f[i + 1][j], f[i][j]);
      if (j + e[i + 1].w <= w) {
        f[i + 1][j + e[i + 1].w] = max(f[i + 1][j + e[i + 1].w], f[i][j] + e[i + 1].v);
      }
    }
  }
  for (LL i = 0; i <= w; i++) {
    ans = max(ans, f[n][i]);
  }
  cout << ans << endl;
  return 0;
}
