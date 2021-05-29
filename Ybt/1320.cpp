#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, tot, ans, a[101];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    tot += a[i];
  }
  tot /= n;
  for (int i = 1; i < n; i++) {
    while (a[i] == tot) {
      i++;
    }
    a[i + 1] += a[i] - tot, ans += i < n;
  }
  cout << ans << endl;
  return 0;
}
