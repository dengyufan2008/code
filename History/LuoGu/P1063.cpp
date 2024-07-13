#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, ans, a[201], f[201][201];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }
  n *= 2;
  for (LL i = 2; i <= n; i++) {
    for (LL j = 1, k; (k = j + i - 1) <= n; j++) {
      for (LL l = j; l < k; l++) {
        f[j][k] = max(f[j][k], f[j][l] + f[l + 1][k] + a[j] * a[l + 1] * a[k == n ? 1 : k + 1]);
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    ans = max(ans, f[i][i + n / 2 - 1]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
