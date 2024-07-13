#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[301];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1, j = n; i < j; i++, j--) {
      cout << a[i] << " " << a[j] << " ";
    }
    if (n & 1) {
      cout << a[n / 2 + 1];
    }
    cout << endl;
  }
  return 0;
}
