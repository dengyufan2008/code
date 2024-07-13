#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, k, ans, a[101], b[101], c[17], d[17];
bool bl[101];

void S(int x) {
  if (x > k) {
    int num = 0;
    for (int i = 1; i <= m; i++) {
      num += bl[a[i]] && bl[b[i]];
    }
    ans = max(ans, num);
    return;
  }
  bool tmp = bl[c[x]], _tmp = bl[d[x]];
  bl[c[x]] = true;
  S(x + 1);
  bl[c[x]] = tmp, bl[d[x]] = true;
  S(x + 1);
  bl[d[x]] = _tmp;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i];
  }
  cin >> k;
  for (int i = 1; i <= k; i++) {
    cin >> c[i] >> d[i];
  }
  S(1);
  cout << ans << endl;
  return 0;
}
