#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, m, ans, f[2][1048576];
bool b;
char a[101][11];

int main() {
  cin >> n >> m;
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      fill(&f[b][0], &f[b][(1 << 2 * m)], 0);
      b ^= 1;
      for (LL k = 0; k < (1 << 2 * m); k++) {
        bool u1 = (i > 0) * ((1 << m) & k), u2 = (i > 1) * (1 & k), l1 = (j > 0) * ((1 << 2 * m - 1) & k), l2 = (j > 1) * ((1 << 2 * m - 2) & k);
        f[b ^ 1][k >> 1] = max(f[b ^ 1][k >> 1], f[b][k]);
        if (!u1 && !u2 && !l1 && !l2 && a[i][j] == 'P') {
          f[b ^ 1][(k >> 1) + (1 << m * 2 - 1)] = max(f[b ^ 1][(k >> 1) + (1 << m * 2 - 1)], f[b][k] + 1);
        }
      }
    }
  }
  for (LL i = 0; i < (1 << m * 2); i++) {
    ans = max(ans, f[b ^ 1][i]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
