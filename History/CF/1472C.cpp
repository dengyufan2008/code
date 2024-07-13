#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, ans, a[200001], f[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    ans = 0, f[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
      f[i] = a[i];
      if (a[i] <= (n - i)) {
        f[i] += f[i + a[i]];
      }
    }
    for (int i = 1; i <= n; i++) {
      ans = max(ans, f[i]);
    }
    cout << ans << endl;
  }
  return 0;
}
