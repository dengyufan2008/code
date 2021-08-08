#include <iostream>
#define LL long long

using namespace std;

LL t, n, m, ans, p[101][101], f[10001];  //f[k]:剩k元,第二天把纪念品卖完以后的钱

int main() {
  cin >> t >> n >> m;
  for (LL i = 1; i <= t; i++) {
    for (LL j = 1; j <= n; j++) {
      cin >> p[i][j];
    }
  }
  ans = m;
  for (LL i = 1; i < t; i++) {
    fill(&f[0], &f[10000] + 1, -1145141919810);
    f[ans] = ans;
    for (LL j = 1; j <= n; j++) {
      for (LL k = ans; k >= p[i][j]; k--) {
        f[k - p[i][j]] = max(f[k - p[i][j]], f[k] + p[i + 1][j] - p[i][j]);
      }
    }
    for (LL j = 0, tmp = ans; j <= tmp; j++) {
      ans = max(j ? ans : -1145141919810, f[j]);
    }
  }
  cout << ans << endl;
  return 0;
}
