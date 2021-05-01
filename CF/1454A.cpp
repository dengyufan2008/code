#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    if (n & 1) {
      cout << n << " ";
      for (int i = 1; i < n; i++) {
        cout << i << " ";
      }
      cout << endl;
    } else {
      for (int i = n; i >= 1; i--) {
        cout << i << " ";
      }
      cout << endl;
    }
  }
  return 0;
}
