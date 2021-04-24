#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, s, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    s = n / 2050;
    if (s * 2050 != n) {
      cout << -1 << endl;
    } else {
      ans = 0;
      while (s) {
        ans += s % 10;
        s /= 10;
      }
      cout << ans << endl;
    }
  }
  return 0;
}
