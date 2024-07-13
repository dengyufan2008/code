#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, c, num, x, a[2001], b[1000001], ans[2001];
bool flag;

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
      cin >> a[i];
    }
    flag = false;
    sort(a + 1, a + n + n + 1);
    for (int i = 1; i < 2 * n && !flag; i++) {
      fill(&b[1], &b[1000000] + 1, 0);
      for (int j = 1; j <= 2 * n; j++) {
        b[a[j]]++;
      }
      c = 2 * n, num = 0, x = a[2 * n] + a[i];
      for (int j = 1; j <= n; j++) {
        while (c > 1 && !b[a[c]]) {
          c--;
        }
        ans[++num] = a[c], ans[++num] = x - a[c];
        b[a[c]]--, b[x - a[c]]--;
        if (b[a[c]] < 0 || b[x - a[c]] < 0) {
          break;
        }
        x = max(a[c], x - a[c]);
        flag = j == n;
      }
      if (flag) {
        cout << "YES" << endl
             << ans[1] + ans[2] << endl;
        for (int i = 1; i <= 2 * n; i += 2) {
          cout << ans[i] << " " << ans[i + 1] << endl;
        }
      }
    }
    if (!flag) {
      cout << "NO" << endl;
    }
  }
  return 0;
}
