#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[101], s;

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    if(a[1] != a[2] && a[1] != a[3]) {
      cout << 1 << endl;
      continue;
    }
    for(int i = 2; i <= n; i++) {
      if(a[1] != a[i]) {
        cout << i << endl;
        break;
      }
    }
  }
  return 0;
}
