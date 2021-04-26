#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[3];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    a[2] = a[1] = a[0];
    cin >> n;
    for (int i = 1, tmp; i <= n; i++) {
      cin >> tmp;
      a[tmp]++;
    }
    cout << (!(a[1] % 2) && !(a[2] % 2) || a[1] >= 2 && !(a[1] % 2) && a[2] % 2 ? "YES" : "NO") << endl;
  }
  return 0;
}
