#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, k;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    if (n == 2) {
      cout << -1 << endl;
      continue;
    }
    k = 0;
    for (int i = 1; i <= n * n; i += 2) {
      cout << i << " ";
      if (++k == n) {
        cout << endl;
        k = 0;
      }
    }
    for (int i = 2; i <= n * n; i += 2) {
      cout << i << " ";
      if (++k == n) {
        cout << endl;
        k = 0;
      }
    }
  }
  return 0;
}
