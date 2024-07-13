#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, ans, a[100001], b[100001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
    ans += (a[i] + b[i]) * (b[i] - a[i] + 1) / 2;
  }
  cout << ans << endl;
  return 0;
}
