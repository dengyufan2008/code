#include <iostream>
#define LL long long

using namespace std;

LL n, d[100001][3], f[100001][3];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> d[i][0] >> d[i][1] >> d[i][2];
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j <= 2; j++) {
      f[i + 1][(j + 1) % 3] = max(f[i + 1][(j + 1) % 3], f[i][j] + d[i + 1][(j + 1) % 3]);
      f[i + 1][(j + 2) % 3] = max(f[i + 1][(j + 2) % 3], f[i][j] + d[i + 1][(j + 2) % 3]);
    }
  }
  cout << max(max(f[n][0], f[n][1]), f[n][2]) << endl;
  return 0;
}
