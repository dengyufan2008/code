/*
ID: dengyuf1
TASK: subset
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

LL n, f[41][1001] = {1};

int main() {
  freopen("subset.in", "r", stdin);
  freopen("subset.out", "w", stdout);
  cin >> n;
  if (((n + 1) * n / 2) & 1) {
    cout << 0 << endl;
    return 0;
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < (n + 1) * n / 4; j++) {
      f[i + 1][j] += f[i][j], f[i + 1][j + i + 1] += f[i][j];
    }
  }
  cout << f[n][(n + 1) * n / 4] << endl;
  return 0;
}
