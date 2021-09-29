#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, m, ans, d[2][1048576] = {1};
bool b, a[101][11];
char ch;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> ch;
      a[i][j] = ch == 'P';
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      b ^= 1;
      fill(&d[b][0], &d[b][1048576], 0);
      for (int k = 0; k < 1048576; k++) {
        bool u1 = (1 << m + j) & k, u2 = (1 << j) & k, l1 = (j > 0) * (1 << m + j - 1) & k, l2 = (j > 1) * (1 << m + j - 2) & k;
        d[b][k] = d[b][k] + d[b ^ 1][k];
      }
    }
  }
  for (int i = 0; i < 1048576; i++) {
    ans += d[b][i];
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
