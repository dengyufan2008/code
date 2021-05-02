#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[2];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    a[0] = a[1] = 0;
    cin >> n;
    for (int i = 1, tmp; i <= n; i++) {
      cin >> tmp;
      a[tmp]++;
    }
    if (a[0] >= (n + 1) / 2) {
      cout << (n + 1) / 2 << endl;
      for (int i = 1; i <= (n + 1) / 2; i++) {
        cout << 0 << " ";
      }
    } else {
      cout << a[1] - (a[1] & 1) << endl;
      for (int i = 1; i <= a[1] - (a[1] & 1); i++) {
        cout << 1 << " ";
      }
    }
    cout << endl;
  }
  return 0;
}
