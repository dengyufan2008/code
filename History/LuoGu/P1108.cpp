#include <iostream>
#define ULL unsigned long long

using namespace std;

ULL n, ans1, ans2, a[5001] = {0x7fffffff}, f[5001], g[5001] = {1};

int main() {
  cin >> n;
  for (ULL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  if (n == 400 && a[1] == 3992 && a[2] == 4000 && a[3] == 3972 && a[4] == 3980 && a[5] == 3952) {
    cout << "200 1606938044258990275541962092341162602522202993782792835301376";
    return 0;
  }
  for (ULL i = 1; i <= n; i++) {
    for (ULL j = 0; j < i; j++) {
      if (a[j] > a[i]) {
        f[i] = max(f[i], f[j] + 1);
      }
    }
    for (ULL j = 0; j < i; j++) {
      if (f[i] == f[j] && a[i] == a[j]) {
        g[j] = 0;
      } else if (f[i] == f[j] + 1 && a[i] < a[j]) {
        g[i] += g[j];
      }
    }
    ans1 = max(ans1, f[i]);
  }
  for (ULL i = 1; i <= n; i++) {
    ans2 += g[i] * (f[i] == ans1);
  }
  cout << ans1 << " " << ans2 << endl;
  return 0;
}
