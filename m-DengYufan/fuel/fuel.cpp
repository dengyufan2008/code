#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

LL n, ans, a[500001], f[2][500001];

int main() {
  freopen("fuel.in", "r", stdin);
  freopen("fuel.out", "w", stdout);
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= i; j++) {
      f[i & 1][j] = max(f[!(i & 1)][j - 1] + (a[i] == j), f[!(i & 1)][j]);
    }
  }
  for (LL i = 1; i <= n; i++) {
    ans = max(ans, f[n & 1][i]);
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
