#include <bits/stdc++.h>
#define LL long long

using namespace std;

int t, n, ans, x[200001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    ans = n;
    fill(&x[1], &x[2 * n] + 1, 0);
    for (int i = 1, tmp; i <= n; i++) {
      cin >> tmp;
      x[tmp]++;
    }
    for (int i = 1; i <= n * 2; i++) {
      if (x[i] == 2) {
        x[i]--, x[i + 1]++;
      } else if (x[i] > 2) {
        x[i]--, x[i + 1]++;
        ans -= x[i] - 1;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
