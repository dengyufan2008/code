#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, x[100001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> x[i];
    }
    ans = n;
    for (int i = 1; i <= n; i++) {
      if (x[i] == x[i - 1]) {
        x[i]++;
      }
      if (x[i] < x[i - 1]) {
        ans--;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
