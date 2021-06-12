#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, d, p, c[1001], ans[2001];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> d;
  for (int i = 1; i <= m; i++) {
    cin >> c[i];
    if (c[i] > d) {
      cout << "NO" << endl;
    }
  }
  for (int i = 1; i <= m && p <= n; i++) {
    p += d;
    fill(&ans[p], &ans[p + c[i] - 1] + 1, i);
    p += c[i] - 1;
  }
  if (p > n) {
    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
