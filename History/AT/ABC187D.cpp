#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, tot, tmp, ans, a[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> tmp;
    tot += a[i], a[i] = a[i] * 2 + tmp;
  }
  sort(a + 1, a + n + 1);
  for (int i = n; i >= 1 && tot >= 0; i--) {
    tot -= a[i];
    ans++;
  }
  cout << ans << endl;
  return 0;
}
