#include <ctime>
#include <iostream>
#include <iomanip>
#define LL long long

using namespace std;

struct V {
  LL x, h, v;
} v[1001];
LL n, x, p, c, d[1001][1001], f[1001][1001][2];

int main() {
  cin >> n >> x;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].x;
    if (v[i].x <= x) {
      p = i;
    }
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].h;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].v;
  }
  for (LL i = 1; i <= n; i++) {
    c += v[i].h;
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = i; j <= n; j++) {
      d[i][j] = d[i][j - 1] + v[j].v;
    }
  }
  fill(&f[0][0][0], &f[1000][1000][1] + 1, -1000000000);
  if (v[p].x == x) {
    f[p][p][0] = f[p][p][1] = c;
  } else {
    f[p][p][0] = f[p][p][1] = c - (x - v[p].x) * d[1][n];
    f[p + 1][p + 1][0] = f[p + 1][p + 1][1] = c - (v[p + 1].x - x) * d[1][n];
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
