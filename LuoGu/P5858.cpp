#include <iostream>
#define LL long long

using namespace std;

LL n, w, s, ans = -1145141919810, a[5001], f[5001][5001];  //前i个原料,锅里还剩j个

int main() {
  cin >> n >> w >> s;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  fill(&f[1][0], &f[5000][5000] + 1, -1145141919810);
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= min(i, w); j++) {
      for (LL k = j - 1; k < j + min(i - j, s); k++) {
        f[i][j] = max(f[i][j], f[i - 1][k] + a[i] * j);
      }
    }
  }
  for (LL i = 0; i <= w; i++) {
    ans = max(ans, f[n][i]);
  }
  cout << ans << endl;
  return 0;
}
