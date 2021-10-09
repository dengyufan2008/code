#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL x, h, v;
  bool operator<(const V &c) const { return x < c.x; }
} v[1002];
LL n, x, p, c, d[1002][1002], f[1002][1002][2];

int main() {
  cin >> n >> x;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].x;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].h;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].v;
  }

  v[++n].x = x;
  sort(v + 1, v + n + 1);
  for (LL i = 1; i <= n; i++) {
    c += v[i].h;
    for (LL j = i; j <= n; j++) {
      d[i][j] = d[i][j - 1] + v[j].v;
    }
  }

  fill(&f[0][0][0], &f[1000][1000][1] + 1, -1145141919810);
  for (LL i = 1; i <= n; i++) {
    if (v[i].x == x) {
      f[i][i][0] = f[i][i][1] = c;
    }
  }
  for (LL i = 2; i <= n; i++) {
    for (LL j = 1, k; (k = j + i - 1) <= n; j++) {
      f[j][k][0] = max(f[j + 1][k][0] - (v[j + 1].x - v[j].x) * (d[1][n] - d[j + 1][k]), f[j + 1][k][1] - (v[k].x - v[j].x) * (d[1][n] - d[j + 1][k]));
      f[j][k][1] = max(f[j][k - 1][0] - (v[k].x - v[j].x) * (d[1][n] - d[j][k - 1]), f[j][k - 1][1] - (v[k].x - v[k - 1].x) * (d[1][n] - d[j][k - 1]));
    }
  }
  cout << fixed << setprecision(3) << max(f[1][n][0], f[1][n][1]) / 1000.0 << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
