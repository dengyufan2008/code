#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, c, d[51][51], f[51][51][2];
pair<int, int> a[51];

int main() {
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      d[i][j] = d[i][j - 1] + a[j].second;
    }
  }
  fill(&f[0][0][0], &f[50][50][1] + 1, 1000000000);
  f[c][c][0] = f[c][c][1] = 0;
  for (int i = 2; i <= n; i++) {
    for (int j = 1, k; (k = j + i - 1) <= n; j++) {
      f[j][k][0] = min(f[j][k][0], min(f[j + 1][k][0] + (a[j + 1].first - a[j].first) * (d[1][n] - d[j + 1][k]), f[j + 1][k][1] + (a[k].first - a[j].first) * (d[1][n] - d[j + 1][k])));
      f[j][k][1] = min(f[j][k][1], min(f[j][k - 1][0] + (a[k].first - a[j].first) * (d[1][n] - d[j][k - 1]), f[j][k - 1][1] + (a[k].first - a[k - 1].first) * (d[1][n] - d[j][k - 1])));
    }
  }
  cout << min(f[1][n][0], f[1][n][1]) << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
