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
    ans = 0;
    for (int i = 1; i <= n; i++) {
      fill(&f[1], &f[n] + 1, 0);
      for (int j = i; j <= n;) {
        f[j + a[j]] = max(f[j] + a[j], f[j + a[j]]);
      }
      ans = max(ans, f[n]);
    }
    cout << ans << endl;
  }
  return 0;
}
