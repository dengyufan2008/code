#include <fstream>
#include <iomanip>

using namespace std;

ifstream cin("course.in");
ofstream cout("course.out");

const int kMaxN = 2001, kMaxM = 301, kInf = 1e9;
int n, m, t, c, d[kMaxM][kMaxM];
double ans, p[kMaxN], f[kMaxN][kMaxN][2];
pair<int, int> a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> t >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i].second;
  }
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  for (int i = 1; i <= t; i++) {
    for (int j = 1; j <= t; j++) {
      d[i][j] = (i != j) * kInf;
    }
  }
  for (int i = 1, x, y, z; i <= c; i++) {
    cin >> x >> y >> z;
    d[x][y] = min(d[x][y], z), d[y][x] = min(d[y][x], z);
  }
  for (int i = 1; i <= t; i++) {
    for (int j = 1; j <= t; j++) {
      for (int k = 1; k <= t; k++) {
        d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
      }
    }
  }
  fill(&f[0][0][1], &f[kMaxN][0][0], kInf);
  for (int i = 1; i <= n; i++) {
    int d00 = (i > 1) * d[a[i - 1].first][a[i].first], d01 = (i > 1) * d[a[i - 1].first][a[i].second],
        d10 = (i > 1) * d[a[i - 1].second][a[i].first], d11 = (i > 1) * d[a[i - 1].second][a[i].second];
    for (int j = 0; j <= min(m, i); j++) {
      f[i][j][0] = min(f[i - 1][j][0] + d00, f[i - 1][j][1] + d00 * (1.0 - p[i - 1]) + d10 * p[i - 1]);
      if (j) {
        f[i][j][1] = min(f[i - 1][j - 1][0] + d00 * (1.0 - p[i]) + d01 * p[i], f[i - 1][j - 1][1] + d00 * (1.0 - p[i - 1]) * (1.0 - p[i]) + d01 * (1.0 - p[i - 1]) * p[i] + d10 * p[i - 1] * (1 - p[i]) + d11 * p[i - 1] * p[i]);
      }
    }
  }
  ans = kInf;
  for (int j = 0; j <= min(m, n); j++) {
    ans = min(ans, min(f[n][j][0], f[n][j][1]));
  }
  cout << fixed << setprecision(2) << ans;
  return 0;
}
