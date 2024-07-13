/*
ID: dengyuf1
TASK: nocows
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

const int kMod = 9901;
int n, k, f[201][101];  //f[i][j]:i个点层数最多为j的方案数

int main() {
  freopen("nocows.in", "r", stdin);
  freopen("nocows.out", "w", stdout);
  cin >> n >> k;
  fill(&f[1][1], &f[1][100] + 1, 1);
  for (int i = 1; i <= k; i++) {
    for (int j = 3; j <= n; j += 2) {
      for (int l = 1; l < j; l += 2) {
        f[j][i] = (f[j][i] + f[l][i - 1] * f[j - l - 1][i - 1]) % kMod;
      }
    }
  }
  cout << (f[n][k] - f[n][k - 1] + kMod) % kMod << endl;
  return 0;
}
