#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, q, t, mx, a[300001], d[51];  //d:最前第i个颜色牌的位置

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (!d[a[i]]) {
      d[a[i]] = i;
    }
    mx = max(mx, a[i]);
  }
  for (int i = 1; i <= q; i++) {
    cin >> t;
    cout << d[t] << " ";
    for(int j = 1; j <= mx; j++) {
      d[j] += (d[j] < d[t]);
    }
    d[t] = 1;
  }
  return 0;
}
