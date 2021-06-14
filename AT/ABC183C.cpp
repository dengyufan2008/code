#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, k, ans, t[9][9];
bool b[9];

void S(LL s, LL m, LL d) {
  if (d == n - 1) {
    ans += m + t[s][1] == k;
    return;
  }
  b[s] = true;
  for (LL i = 2; i <= n; i++) {
    if (!b[i]) {
      S(i, m + t[s][i], d + 1);
    }
  }
  b[s] = false;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      cin >> t[i][j];
    }
  }
  S(1, 0, 0);
  cout << ans << endl;
  return 0;
}
