#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, h, ans, a[5002], f[5002], g[5002];  //a:原数组; f:经过次数; g:前向差分

int main() {
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
    }
    ans = 0;
    fill(&f[1], &f[n + 1] + 1, 0);
    fill(&g[1], &g[n + 1] + 1, 0);
    for (LL i = 1; i <= n; i++) {
      f[i] += (g[i] += g[i - 1]);
      if (f[i] < a[i] - 1) {
        ans += a[i] - f[i] - 1;
      } else {
        f[i + 1] += f[i] - a[i] + 1;
      }
      g[i + 2]++, g[min(a[i] + i, n) + 1]--;
    }
    cout << ans << endl;
  }
  return 0;
}
