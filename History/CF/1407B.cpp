#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, p, mx, _mx, a[1001];

int Gcd(int a, int b) {
  return b ? Gcd(b, a % b) : a;
}

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    mx = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > a[mx]) {
        mx = i;
      }
    }
    cout << a[mx] << " ";
    p = a[mx], a[mx] = 0;
    for (int i = 2; i <= n; i++) {
      mx = 0, _mx = 0;
      for (int j = 1; j <= n; j++) {
        if (a[j] && Gcd(a[j], p) > _mx) {
          mx = j, _mx = Gcd(a[j], p);
        }
      }
      cout << a[mx] << " ";
      a[mx] = 0, p = _mx;
    }
    cout << endl;
  }
  return 0;
}
