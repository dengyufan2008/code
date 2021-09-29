#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, m, ans, f[2][1048576];
bool b, a[101][11];
char ch;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> ch;
      a[i][j] = ch == 'P';
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b ^= 1;
      fill(&f[b][0], &f[b][1048576], 0);
      for (int k = 0; k < 1048576; k++) {
        bool u1 = (1 << m) & k, u2 = 1 & k, l1 = (1 << 2 * m - 1) & k, l2 = (1 << 2 * m - 2) & k;
        f[b][k >> 1] = max(f[b][k >> 1], f[b ^ 1][k]);
        if (!u1 && !u2 && !l1 && !l2 && a[i][j]) {
          f[b][(k >> 1) + (1 << m * 2 - 1)] = max(f[b][(k >> 1) + (1 << m * 2 - 1)], f[b ^ 1][k] + 1);
        }
      }
    }
  }
  for (int i = 0; i < (1 << m * 2); i++) {
    ans = max(ans, f[b][i]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
