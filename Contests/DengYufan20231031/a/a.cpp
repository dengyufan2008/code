#include <algorithm>
#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kMod = 998244353;
int n, ans, a[5][kMaxN], d[4];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int o = 0; o < 5; o++) {
    for (int i = 1; i <= n; i++) {
      cin >> a[o][i];
    }
    sort(a[o] + 1, a[o] + n + 1);
  }
  for (int o = 0; o < 5; o++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 0, k = 0; j < 5; j++) {
        if (j < o) {
          d[k++] = lower_bound(a[j] + 1, a[j] + n + 1, a[o][i]) - a[j] - 1;
        } else if (j > o) {
          d[k++] = upper_bound(a[j] + 1, a[j] + n + 1, a[o][i]) - a[j] - 1;
        }
      }
      for (int j : {3, 5, 6, 9, 10, 12}) {
        int s = 1;
        for (int k = 0; k < 4; k++) {
          int w = d[k];
          if (j >> k & 1) {
            w = n - w;
          }
          s = 1LL * s * w % kMod;
        }
        ans = (ans + 1LL * s * a[o][i] % kMod) % kMod;
      }
    }
  }
  cout << ans;
  return 0;
}
