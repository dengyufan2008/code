#include <iostream>
#define LL long long

using namespace std;

LL n, a[100001], t, l, r, ans;

int main() {
  cin >> n >> t;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] = (a[i] + a[i - 1]) % 1000000007;
  }
  for (LL i = 1; i <= t; i++) {
    cin >> l >> r;
    ans = (a[r] - a[l - 1]) % 1000000007;
    if (ans < 0) {
      ans = ans + 1000000007;
    }
    cout << ans << endl;
  }
  return 0;
}
