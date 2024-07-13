#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ans, a[101], b[1001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 2, num = 0; i <= 1000; i++, num = 0) {
    for (int j = 1; j <= n; j++) {
      b[i] += !(a[j] % i);
    }
  }
  for (int i = 2; i <= 1000; i++) {
    if (b[ans] < b[i]) {
      ans = i;
    }
  }
  cout << ans << endl;
  return 0;
}
