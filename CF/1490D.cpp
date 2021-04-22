#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, a[101], d[101];

void C(int l, int r) {
  if (l == r) {
    d[l]++;
    return;
  } else if (l > r) {
    return;
  }
  int mx = 0;
  for (int i = l; i <= r; i++) {
    d[i]++;
    if (a[mx] <= a[i]) {
      mx = i;
    }
  }
  C(l, mx - 1), C(mx + 1, r);
}

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    fill(&d[1], &d[n] + 1, 0);
    C(1, n);
    for (int i = 1; i <= n; i++) {
      cout << --d[i] << " ";
    }
    cout << "\n";
  }
  return 0;
}
