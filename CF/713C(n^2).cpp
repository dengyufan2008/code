#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const LL kInf = 1e18;
LL n, ans = kInf, a[3001], b[3001] = {-kInf}, l[3001], d[3001] = {kInf}, f[3001][3001];

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> b[i];
    b[i] -= i, l[i] = i;
  }
  sort(l + 1, l + n + 1, [](LL i, LL j) { return b[i] < b[j]; });
  for (LL i = 1; i <= n; i++) {
    a[l[i]] = a[l[i - 1]] + (b[l[i]] != b[l[i - 1]]);
  }
  fill(&f[0][0], &f[3001][0], kInf);
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= n; j++) {
      f[i][j] = d[j] + abs(b[i] - b[l[j]]);
    }
    for (LL j = 1; j <= n; j++) {
      d[j] = min(d[j - 1], f[i][j]);
    }
  }
  for (LL i = 1; i <= n; i++) {
    ans = min(ans, f[n][i]);
  }
  cout << ans;
  return 0;
}
