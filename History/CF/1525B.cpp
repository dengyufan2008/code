#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[51];
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    flag = true;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      flag = flag && a[i] == i;
    }
    if (flag) {
      cout << 0 << endl;
    } else if (a[1] == 1 || a[n] == n) {
      cout << 1 << endl;
    } else if (a[1] == n && a[n] == 1) {
      cout << 3 << endl;
    } else {
      cout << 2 << endl;
    }
  }
  return 0;
}
