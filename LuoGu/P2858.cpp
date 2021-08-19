#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, a[2001], f[2001][2001];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    f[i][i] = a[i] * n;
  }
  for (LL i = 2; i <= n; i++) {
    for (LL j = 1, k; (k = j + i - 1) <= n; j++) {
      f[j][k] = max(f[j + 1][k] + a[j] * (n - i + 1), f[j][k - 1] + a[k] * (n - i + 1));
    }
  }
  cout << f[1][n] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
