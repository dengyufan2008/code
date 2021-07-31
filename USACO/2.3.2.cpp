/*
ID: dengyuf1
TASK: nocows
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

int n, k, f[201][101];

int main() {
  // freopen("nocows.in", "r", stdin);
  // freopen("nocows.out", "w", stdout);
  cin >> n >> k;
  f[0][0] = f[1][1] = f[3][2] = 1;
  for (int i = 4; i <= n; i++) {
    for (int j = 3; j <= k; j++) {
      for (int _i = 1; _i < i; _i++) {
        for (int _j = 1; _j < k - 1; _j++) {
          f[i][j] = (f[i][j] + f[_i][j - 1] * f[i - _i - 1][_j] * 2) % 9901;
        }
        f[i][j] = (f[i][j] + f[_i][k - 1] * f[i - _i - 1][k - 1]) % 9901;
      }
    }
  }
  cout << f[n][k] << endl;
  return 0;
}
