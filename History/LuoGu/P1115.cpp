#include <iostream>
#define LL long long

using namespace std;

LL n, ans = -1145141919810, a[200001], f[201];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= n; i++) {
    f[i] = max(f[i - 1], 0LL) + a[i];
    ans = max(ans, f[i]);
  }
  cout << ans << endl;
  return 0;
}
