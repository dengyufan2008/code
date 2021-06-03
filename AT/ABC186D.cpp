#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, ans, a[200001], d[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    d[i] = a[i] + d[i - 1];
    ans += a[i] * (i - 1) - d[i - 1];
  }
  cout << ans << endl;
  return 0;
}
