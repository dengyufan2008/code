#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int x, y;
  double v;
  bool operator<(const E &e) const {
    return v < e.v;
  }
} e[500001];
int n, k, m, c, d[1001][2], f[1001];

int GetRoot(int x) {
  return x == f[x] ? x : f[x] = GetRoot(f[x]);
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> d[i][0] >> d[i][1];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      e[++m] = {i, j, sqrt((d[i][0] - d[j][0]) * (d[i][0] - d[j][0]) + (d[i][1] - d[j][1]) * (d[i][1] - d[j][1]))};
    }
  }
  sort(e + 1, e + m + 1);
  for (int i = 1; i <= n; i++) {
    f[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int x = GetRoot(e[i].x), y = GetRoot(e[i].y);
    if (x != y) {
      c++;
      f[x] = y;
      if (c > n - k) {
        cout << fixed << setprecision(2) << e[i].v << endl;
        break;
      }
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
