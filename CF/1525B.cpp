#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, a[51], l[51];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      l[i] = i;
    }
    sort(l + 1, l + n + 1, [](int i, int j) {
      return a[i] < a[j];
    });
    ans = 0;
    for (int i = 1; i <= n; i++) {
      if (l[i - 1] == i - 1 && l[i] != i) {
        ans++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
