#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL b, p, k, tmp, ans = 1;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> b >> p >> k;
  tmp = b % k;
  for (LL i = 1; i <= p; i <<= 1) {
    if (p & i) {
      ans = ans * tmp % k;
    }
    tmp = tmp * tmp % k;
  }
  cout << b << "^" << p << " mod " << k << "=" << ans << endl;
  return 0;
}
