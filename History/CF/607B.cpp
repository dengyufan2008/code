#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, a[501], f[501][501];

int main() {
  cin >> n;
  fill(&f[0][0], &f[500][500] + 1, 1000000000);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[i][i] = 1;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      if (a[j] == a[k]) {
        f[j][k] = min(f[j][k], i == 2 ? 1 : f[j + 1][k - 1]);
      }
      for (int l = j; l < k; l++) {
        f[j][k] = min(f[j][k], f[j][l] + f[l + 1][k]);
      }
    }
  }
  cout << f[1][n] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
