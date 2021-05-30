#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, ans, a[100001], d[100001][21];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    d[i][0] = a[i];
  }
  for (int i = 1; (1 << i) <= n; i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      d[j][i] = max(d[j][i - 1], d[j + (1 << (i - 1))][i - 1]);
    }
  }
  
  return 0;
}
