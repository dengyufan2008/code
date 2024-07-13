#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, x, num, ans = -1, v, p;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> x;
  x *= 100;
  for (int i = 1; i <= n; i++) {
    cin >> v >> p;
    num += v * p;
    if (num > x) {
      ans = i;
      break;
    }
  }
  cout << ans << endl;
  return 0;
}
