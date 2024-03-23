#include <algorithm>
#include <iostream>
#include <vector>
#define RF(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

using namespace std;
using LL = long long;
using Pii = pair<int, int>;
using Pll = pair<LL, LL>;

const int kN = 3001;

int n, v, a[kN], b[kN * 2], f[kN * 2], ans;

int main() {
  RF("kanzenkankaku");
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> v;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int l = 1; l <= n; ++l) {
    for (int r = l; r <= n; ++r) {
      copy_n(a + 1, n, b + 1);
      sort(b + l, b + r + 1);
      for (int i = n; i >= 1; --i) {
        b[i * 2] = b[i], b[i * 2 + 1] = 0;
      }
      b[1] = 0;
      fill_n(f + 1, n * 2 + 1, 0);
      for (int i = 1, m = 0, p = 0; i <= n * 2 + 1; ++i) {
        f[i] = (i < p ? min(f[m] + m - i, f[m * 2 - i]) : 1);
        for (; b[i + f[i]] == b[i - f[i]]; ++f[i]) {
        }
        if (f[i] + i > p) {
          p = f[i] + i, m = i;
        }
        ans = max(ans, f[i] - 1);
      }
    }
  }
  cout << ans;
  return 0;
}