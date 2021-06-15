#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, k, a[3000001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (LL i = 1; i * i <= n; i++) {
    if (!(n % i)) {
      a[++k] = i;
      if (i * i != n) {
        a[++k] = n / i;
      }
    }
  }
  sort(a + 1, a + k + 1);
  for (LL i = 1; i <= k; i++) {
    cout << a[i] << endl;
  }
  return 0;
}
