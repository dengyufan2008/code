#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, a[501], b[501];

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] % 2) {
      b[++m] = a[i];
    }
  }
  sort(b + 1, b + 1 + m);
  cout << b[1];
  for (int i = 2; i <= m; i++) {
    cout << "," << b[i];
  }
  return 0;
}
