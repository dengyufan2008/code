#include <iostream>
#define LL long long

using namespace std;

LL n, a[3002], d[3002], f[3002][3002];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    d[i] = d[i - 1] + a[i];
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      f[j][j + i - 1] = d[j + i - 1] - d[j - 1] - min(f[j + 1][j + i - 1], f[j][j + i - 2]);
    }
  }
  cout << f[1][n] * 2 - d[n] << endl;
  return 0;
}
