#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL t, n, k, ans, a[1000001], l[1000001], r[1000001];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    ans = 1e18, k = 0;
    fill(&l[1], &l[n] + 1, 0), fill(&r[1], &r[n] + 1, 0);
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> ch;
      if (ch == '.') {
        a[++k] = i;
      }
    }
    if (!k) {
      cout << 0 << endl;
      continue;
    }
    for (LL i = 1; i <= k; i++) {
      l[i] = a[i] - i, r[i] = n - k + i - a[i];
    }
    for (LL i = 1; i <= k; i++) {
      l[i] += l[i - 1];
    }
    for (LL i = k; i >= 1; i--) {
      r[i] += r[i + 1];
    }
    for (LL i = 0; i <= k; i++) {
      ans = min(ans, l[i] + r[i + 1]);
    }
    cout << ans << endl;
  }
  return 0;
}
