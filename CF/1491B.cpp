#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, u, v, a[101];
bool need, nextto;

int main() {
  cin.tie(0), cout.tie(0);
  cin >> t;
  for (LL i = 1; i <= t; i++) {
    need = true, nextto = false;
    cin >> n >> u >> v;
    for (LL j = 1; j <= n; j++) {
      cin >> a[j];
      if (j == 1) {
        continue;
      }
      if (a[j] == a[j - 1] + 1 || a[j] == a[j - 1] - 1) {
        nextto = true;
      } else if (a[j] != a[j - 1]) {
        need = false;
      }
    }
    if (!need) {
      cout << 0 << "\n";
    } else {
      if (!nextto) {
        cout << min(v * 2, u + v) << "\n";
      } else {
        cout << min(u, v) << "\n";
      }
    }
  }
  return 0;
}
