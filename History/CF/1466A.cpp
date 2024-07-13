#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, x[51], a[51];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        a[x[j] - x[i]] = t + 1;
      }
    }
    ans = 0;
    for (int i = 1; i <= 50; i++) {
      if (a[i] == t + 1) {
        ans++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
