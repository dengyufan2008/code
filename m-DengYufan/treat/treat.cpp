#include <iostream>
#define LL long long

using namespace std;

LL n, ans, v[2002], f[2002][2002];

int main() {
  freopen("treat.in", "r", stdin);
  freopen("treat.out", "w", stdout);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i];
  }
  for (LL l = 1; l <= n; l++) {
    for (LL r = n; r >= l - 1; r--) {
      f[l][r] = max(f[l - 1][r] + v[l - 1] * (n - r + l - 1), f[l][r + 1] + v[r + 1] * (n - r + l - 1));
    }
  }
  for (LL i = 1; i <= n; i++) {
    ans = max(ans, f[i][i - 1]);
  }
  cout << ans << endl;
  return 0;
}
