#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, a[31], f[31][31];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  fill(&f[0][0], &f[30][30] + 1, 1);
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      for (int l = j; l <= k; l++) {
        f[j][k] = max(f[j][k], f[j][l - 1] * f[l + 1][k] + a[l]);
      }
    }
  }
  cout << f[1][n] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
