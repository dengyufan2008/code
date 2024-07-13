#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, lg[100001], d[100001][21];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1, p = 0; i <= n; i++) {
    cin >> d[i][0];
    lg[i] = p += i == 1 << p + 1;
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      d[j][i] = max(d[j][i - 1], d[j + (1 << (i - 1))][i - 1]);
    }
  }
  for (int i = 1, l, r; i <= m; i++) {
    cin >> l >> r;
    cout << max(d[l][lg[r - l + 1]], d[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]) << "\n";
  }
  return 0;
}
