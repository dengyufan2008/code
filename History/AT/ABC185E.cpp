#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, a[1001], b[1001], f[1001][1001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[i][0] = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    f[0][i] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      f[i][j] = min(min(f[i][j - 1], f[i - 1][j]) + 1, f[i - 1][j - 1] + (a[i] != b[j]));
    }
  }
  cout << f[n][m] << endl;
  return 0;
}
