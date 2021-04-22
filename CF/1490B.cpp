#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, mx, ans, c[3];

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    c[0] = c[1] = c[2] = mx = ans = 0;
    for (LL i = 0, tmp; i < n; i++) {
      cin >> tmp;
      c[tmp % 3]++;
    }
    for (LL i = 1; i <= 2; i++) {
      if (c[mx] < c[i]) {
        mx = i;
      }
    }
    for (LL i = 0; i <= 2; i++) {
      ans += abs(c[(i + mx) % 3] - n / 3);
      if (c[(i + mx) % 3] >= n / 3) {
        c[(i + mx + 1) % 3] += c[(i + mx) % 3] - n / 3;
      } else {
        c[(i + mx + 2) % 3] -= c[(i + mx) % 3] - n / 3;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
