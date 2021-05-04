/*
ID: dengyuf1
TASK: skidesign
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, ans = 1e18, a[1001];

int main() {
  freopen("skidesign.in", "r", stdin);
  freopen("skidesign.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (LL i = a[1], num = 0; i <= a[n]; i++, num = 0) {
    for (int j = 1; j <= n; j++) {
      if (a[j] - i > 17) {
        num += (a[j] - i - 17) * (a[j] - i - 17);
      } else if (a[j] < i) {
        num += (a[j] - i) * (a[j] - i);
      }
    }
    ans = min(ans, num);
  }
  cout << ans << endl;
  return 0;
}
