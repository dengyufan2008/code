#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, x[1001], y[1001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> x[i] >> y[i];
    }
    if (n % 2) {
      cout << 1 << endl;
    } else {
      sort(x + 1, x + n + 1), sort(y + 1, y + n + 1);
      cout << (x[n / 2 + 1] - x[n / 2] + 1) * (y[n / 2 + 1] - y[n / 2] + 1) << endl;
    }
  }
  return 0;
}
