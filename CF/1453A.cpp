#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, m, ans, a[101], b[101];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
      cin >> b[i];
    }
    ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (a[i] == b[j]) {
          ans++;
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
