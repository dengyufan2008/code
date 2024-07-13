#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, ans, a[200001], d[200001] = {-100000001};

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
    d[i] = max(d[i - 1], a[i]);
  }
  for (LL i = 1, j = 0; i <= n; i++) {
    ans = max(ans, j + d[i]);
    j += a[i];
  }
  cout << ans << endl;
  return 0;
}
