#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, a[201], f[101][101];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[i][i] = a[i + n] = a[i];
  }
  n *= 2;
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      for (int l = j; l < k; l++) {
        f[i][j] = max(f[i][j], f[i][l] + f[l + 1][j] + a[i] * a[l] * a[k + 1 > n ? 1 : k + 1]);
      }
    }
  }
  cout << f[1][n] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
