#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, a[51];

bool P(int i, int j) {
  return (double)max(i, j) / (double)min(i, j) > 2.0;
}

int main() {
  cin >> t;
  while (t--) {
    ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1, tmp; i < n; i++) {
      tmp = min(a[i], a[i + 1]);
      while (P(tmp, max(a[i], a[i + 1]))) {
        tmp *= 2;
        ans++;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
