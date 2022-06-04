#include <iostream>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

LL n, m, f[1002][1002][2];
PLL h[1002], g[1002];

LL Dis(PLL x, PLL y) {
  return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}

int main() {
  cin >> n >> m;
  for (LL i = 1; i <= n; i++) {
    cin >> h[i].first >> h[i].second;
  }
  for (LL i = 1; i <= m; i++) {
    cin >> g[i].first >> g[i].second;
  }
  fill(&f[0][0][0], &f[1001][1001][1] + 1, 1145141919810);
  f[1][0][0] = 0;
  for (LL i = 1; i <= n; i++) {
    for (LL j = 0; j <= m; j++) {
      f[i + 1][j][0] = min(f[i][j][0] + Dis(h[i], h[i + 1]), f[i][j][1] + Dis(g[j], h[i + 1]));
      f[i][j + 1][1] = min(f[i][j][0] + Dis(h[i], g[j + 1]), f[i][j][1] + Dis(g[j], g[j + 1]));
    }
  }
  cout << f[n][m][0];
  return 0;
}
