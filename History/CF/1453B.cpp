#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, tot, ans, a[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    tot = 0;
    for (int i = 2; i <= n; i++) {
      tot += abs(a[i] - a[i - 1]);
    }
    ans = tot;
    for (int i = 2; i < n; i++) {
      ans = min(ans, tot - abs(a[i] - a[i - 1]) - abs(a[i + 1] - a[i]) + abs(a[i + 1] - a[i - 1]));
    }
    ans = min(ans, min(tot - abs(a[2] - a[1]), tot - abs(a[n] - a[n - 1])));
    cout << ans << endl;
  }
  return 0;
}
