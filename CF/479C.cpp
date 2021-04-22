#include <bits/stdc++.h>

using namespace std;

int n, k, a[200001];

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  a[n + 1] = 0;
  sort(a + 1, a + 1 + n);
  if(a[k] == a[k + 1]) {
    cout << -1;
  } else {
    cout << a[k] + 1;
  }
  return 0;
}
