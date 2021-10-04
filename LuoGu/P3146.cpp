#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, f[251][251][2];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> f[i][i][0];
    f[i][i][1] = f[i][i][0];
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      f[j][k][0] = max(f[j][k - 1][0] + (f[max(j - i, 1)][j - 1][1] == f[j][k - 1][0]), f[j + 1][min(j + i, n)][0] + (f[j + 1][min(j + 1, n)][0] == f[max(j - i, 1)][j - 1][1]));
      f[j][k][1] = f[j + 1][k][1] + (f[k + 1][min(k + i, n)][0] == f[j + 1][k][1]);
    }
  }
  cout << max(f[1][n][0], f[1][n][1]) << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
