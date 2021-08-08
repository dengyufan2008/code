#include <iostream>
#define LL long long

using namespace std;

int n, k, a[101], f[101][100001] = {1};

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= k; j++) {
      for (int k = 0; k <= a[i + 1]; k++) {
        f[i + 1][j + k] = (f[i + 1][j + k] + f[i][j]) % 1000000007;
      }
    }
  }
  cout << f[n][k] << endl;
  return 0;
}
