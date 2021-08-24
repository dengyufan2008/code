#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, c, ans = 0x7fffffff, h[100001], f[100001][101];

int main() {
  // freopen("telewire.in", "r", stdin);
  // freopen("telewire.out", "w", stdout);
  cin >> n >> c;
  for (LL i = 1; i <= n; i++) {
    cin >> h[i];
  }
  fill(&f[1][0], &f[100000][100] + 1, 0x7fffffff);
  for (LL i = 1; i <= n; i++) {
    for (LL j = h[i]; j <= 100; j++) {
      for (LL k = h[i - 1]; k <= 100; k++) {
        f[i][j] = min(f[i][j], f[i - 1][k] + c * abs(j - k) + (j - h[i]) * (j - h[i]));
      }
    }
  }
  for (LL i = 1; i <= 100; i++) {
    ans = min(ans, f[n][i]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
