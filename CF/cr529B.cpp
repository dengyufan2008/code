#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, mx1, mx2, mn1 = 1e5 + 1, mn2 = 1e5 + 1;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1, tmp; i <= n; i++) {
    cin >> tmp;
    if(tmp > mx1) {
      mx2 = mx1;
      mx1 = tmp;
    } else {
      mx2 = max(mx2, tmp);
    }
    if(tmp < mn1) {
      mn2 = mn1;
      mn1 = tmp;
    } else {
      mn2 = min(mn2, tmp);
    }
  }
  cout << min(mx1 - mn2, mx2 - mn1);
  return 0;
}
