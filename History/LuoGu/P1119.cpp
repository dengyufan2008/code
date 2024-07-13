#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kInf = 1 << 24;
int n, m, q, x, y, z, p, t[200], d[200][200];

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> t[i];
    for (int j = 0; j < n; j++) {
      d[i][j] = kInf * (i != j);
    }
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    d[x][y] = d[y][x] = z;
  }
  cin >> q;
  while (q--) {
    cin >> x >> y >> z;
    for (; p < n && t[p] <= z; p++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          d[i][j] = min(d[i][j], d[i][p] + d[p][j]);
        }
      }
    }
    cout << (d[x][y] == kInf || t[x] > z || t[y] > z ? -1 : d[x][y]) << '\n';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
