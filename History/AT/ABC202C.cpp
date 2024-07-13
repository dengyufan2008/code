#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, ans, a[100001], b[100001], c[100001], _a[100001], _c[100001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    _a[a[i]]++;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (LL i = 1; i <= n; i++) {
    cin >> c[i];
    _c[c[i]]++;
  }
  for (LL i = 1; i <= n; i++) {
    ans += _a[b[i]] * _c[i];
  }
  cout << ans;
  return 0;
}
