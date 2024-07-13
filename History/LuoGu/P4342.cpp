#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, ans = -114514, a[101], f[2][101][101];
char ch[101];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> ch[i] >> a[i];
    ch[i + n] = ch[i], a[i + n] = a[i];
  }
  fill(&f[0][0][0], &f[0][100][100] + 1, 114514);
  fill(&f[1][0][0], &f[1][100][100] + 1, -114514);
  for (int i = 1; i <= n * 2; i++) {
    f[0][i][i] = f[1][i][i] = a[i];
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n * 2; j++) {
      for (int l = j; l < k; l++) {
        f[0][j][k] = min(f[0][j][k], ch[l + 1] == 't' ? f[0][j][l] + f[0][l + 1][k] : min(min(f[0][j][l] * f[0][l + 1][k],  f[1][j][l] * f[1][l + 1][k]), min(f[0][j][l] * f[1][l + 1][k], f[1][j][l] * f[0][l + 1][k])));
        f[1][j][k] = max(f[1][j][k], ch[l + 1] == 't' ? f[1][j][l] + f[1][l + 1][k] : max(f[1][j][l] * f[1][l + 1][k], f[0][j][l] * f[0][l + 1][k]));
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = max(ans, f[1][i][i + n - 1]);
  }
  cout << ans << endl;
  for (int i = 1; i <= n; i++) {
    if (f[1][i][i + n - 1] == ans) {
      cout << i << " ";
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
