#include <iostream>
#define LL long long

using namespace std;

LL n, w, s, ans = -1145141919810, a[5001], f[2][5001];  //前i个原料,锅里还剩j个

int main() {
  cin >> n >> w >> s;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= n; i++) {
    fill(&f[1][0], &f[1][5000] + 1, -1145141919810);
    for (LL j = 1; j <= min(i, w); j++) {
      for (LL k = j - 1; k < j + min(i - j, s); k++) {
        f[1][j] = max(f[1][j], f[0][k] + a[i] * j);
      }
    }
    copy(&f[1][0], &f[1][5000] + 1, &f[0][0]);
  }
  for (LL i = 0; i <= w; i++) {
    ans = max(ans, f[1][i]);
  }
  cout << ans << endl;
  return 0;
}
