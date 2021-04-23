#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, d, l, r, mid, ans;

bool C(int x) {
  for (int i = 1, p = 0; i <= sqrt(x); i++) {
    if (!(x % i)) {
      if (i - p > d) {
        return false;
      }
      p = i;
    }
  }
  return true;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> d;
    l = 6, r = 1e9;
    while (l <= r) {
      mid = (l + r) >> 1;
      if (C(mid)) {
        ans = min(ans, mid);
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
