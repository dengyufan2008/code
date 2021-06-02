#include <bits/stdc++.h>
#define LL long long

using namespace std;

int h, w, mn = 101, ans, a[101][101];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      cin >> a[i][j];
      mn = min(mn, a[i][j]);
    }
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      ans += a[i][j] - mn;
    }
  }
  cout << ans << endl;
  return 0;
}
