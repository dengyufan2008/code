#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, ans, d[100001][21];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> d[i][0];
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      d[j][i] = max(d[j][i - 1], d[j + (1 << (i - 1))][i - 1]);
    }
  }
  for (int i = 1, l, r; i <= m; i++) {
    cin >> l >> r;
    ans = 0;
    for (int j = 20; j >= 0; j--) {
      if (l + (1 << j) - 1 <= r) {
        ans = max(ans, d[l][j]);
        l += 1 << j;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
