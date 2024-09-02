// by wls
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, k;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    if (n == k || (k == 1 && (n & 1))) {
      cout << "A";
    } else
      cout << "B";
  }
  return 0;
}
