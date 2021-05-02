#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, a[3001];

int M(int x) {
  int num = 0, ans = 1, s = 0;
  for (int i = 1; i <= x; i++) {
    num += a[i];
  }
  for (int i = x + 1; i <= n; i++) {
    s += a[i];
    if (s > num) {
      return -1;
    } else if (s == num) {
      ans++;
      s = 0;
    }
  }
  return s ? -1 : ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    ans = n + 1;
    for (int i = 1; i <= n; i++) {
      ans = min(ans, n - M(i));
    }
    cout << ans << endl;
  }
  return 0;
}
