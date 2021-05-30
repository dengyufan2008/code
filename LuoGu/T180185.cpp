#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, a[100001], d[100001][21];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 2; i <= n; i++) {
    cin >> a[i];
    d[i][0] = a[i];
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      d[j][i] = d[d[j][i - 1]][i - 1];
    }
  }
  for (int i = 1, x, k, num, ans; i <= m; i++) {
    cin >> x >> k;
    ans = x, num = 0;
    for (int j = 20; j >= 0; j--) {
      if (num + (1 << j) <= k) {
        ans = d[ans][j], num += 1 << j;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
