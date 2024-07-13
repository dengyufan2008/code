#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL x, y, v;
} v[1001];
LL n, s, tot, f[1001][1001][2];

int main() {
  cin >> n >> s;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].x;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].y;
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].v;
  }
  sort(v + 1, v + 1 + n, [](V i, V j) { return i.x < j.x; });
  for (LL i = 1; i <= n; i++) {
    v[i].v += v[i - 1].v;
    tot += v[i].y;
  }
  for (LL i = 1; i <= n; i++) {
    f[i][i][0] = f[i][i][1] = -v[n].v * abs(v[i].x - s);
  }
  for (LL i = 2; i <= n; i++) {
    for (LL j = 1, k; (k = j + i - 1) <= n; j++) {
      f[j][k][0] = max(f[j + 1][k][0] - (v[n].v - v[k].v + v[j].v) * (v[j + 1].x - v[j].x), f[j + 1][k][1] - (v[n].v - v[k].v + v[j].v) * (v[k].x - v[j].x));
      f[j][k][1] = max(f[j][k - 1][1] - (v[n].v - v[k - 1].v + v[j - 1].v) * (v[k].x - v[k - 1].x), f[j][k - 1][0] - (v[n].v - v[k - 1].v + v[j - 1].v) * (v[k].x - v[j].x));
    }
  }
  cout << fixed << setprecision(3) << (max(f[1][n][0], f[1][n][1]) + tot) / 1000.0 << endl;
  // cout << "Runtime:" << clock() / 1000.0 << "s" << endl;
  return 0;
}
