#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, r, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> r;
      ans += (r != 2);
    }
    cout << ans << endl;
  }
  return 0;
}
