#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, d, sum, s, t = 1, w[2001], ans[2001];
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> d;
  for (int i = 1; i <= m; i++) {
    cin >> w[i];
    sum += w[i];
  }
  while (s <= n) {
    s = s + d + sum - 1 <= n ? s + d : n - sum + 1;
    if (s > n) {
      break;
    }
    if (t <= m) {
      for (int i = s; i < s + w[t]; i++) {
        ans[i] = t;
      }
      s += w[t] - 1;
      sum -= w[t++];
    } else {
      flag = true;
      break;
    }
  }
  if (flag) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
  }
  return 0;
}
