#include <iostream>
#define LL long long

using namespace std;

const LL kMod = 1000000007;
LL n, k, a[102], f[102][100002] = {1};

int main() {
  cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 0; j <= k; j++) {
      f[i][j] = (f[i][j] + f[i - 1][j]) % kMod;
      if (j + a[i] <= k) {
        f[i][j + a[i] + 1] = (f[i][j + a[i] + 1] - f[i - 1][j] + kMod) % kMod;
      }
    }
    for (LL j = 1; j <= k; j++) {
      f[i][j] = (f[i][j] + f[i][j - 1]) % kMod;
    }
  }
  cout << f[n][k] << endl;
  return 0;
}
