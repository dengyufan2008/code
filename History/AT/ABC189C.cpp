#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans, a[10001], d[10001][10001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    d[i][i] = a[i];
    for (int j = i + 1; j <= n; j++) {
      d[i][j] = min(d[i][j - 1], a[j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      ans = max(ans, d[i][j] * (j - i + 1));
    }
  }
  cout << ans << endl;
  return 0;
}
