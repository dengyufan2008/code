#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, k, m, a[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i <<= 1) {
    if (i & n) {
      a[++m] = i;
    }
  }
  if (k > n || m > k) {
    cout << "NO";
    return 0;
  }
  cout << "YES\n";
  for (int i = 1; m < k;) {
    while (a[i] == 1) {
      i++;
    }
    a[i] /= 2;
    a[++m] = a[i];
  }
  for (int i = 1; i <= m; i++) {
    cout << a[i] << " ";
  }
  return 0;
}
