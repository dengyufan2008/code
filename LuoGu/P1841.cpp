#include <ctime>
#include <iostream>
#include <set>
#define LL long long

using namespace std;

int n, m, a[201][201], d[201][201];
set<int> s;

int main() {
  cin >> n >> m;
  fill(&a[0][0], &a[200][200] + 1, 100000);
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    a[x][y] = a[y][x] = z;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        if (j != k) {
          if (a[j][i] + a[i][k] < a[j][k]) {
            a[j][k] = a[j][i] + a[i][k];
            d[j][k] = i;
          } else if (a[j][i] + a[i][k] == a[j][k]) {
            d[j][k] = 0;
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (d[i][j]) {
        s.insert(d[i][j]);
      }
    }
  }
  if (s.empty()) {
    cout << "No important cities.";
  }
  for (auto i : s) {
    cout << i << ' ';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
