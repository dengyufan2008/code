#include <iostream>
#define LL long long

using namespace std;

int n, m, e, ans, b[501], v[501];
bool l[501][501];

bool T(int x, int y) {
  if (b[x] != y) {
    b[x] = y;
    for (int i = 1; i <= m; i++) {
      if (l[x][i] && (!v[i] || T(v[i], y))) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m >> e;
  for (int i = 1, x, y; i <= e; i++) {
    cin >> x >> y;
    l[x][y] = 1;
  }
  for (int i = 1; i <= n; i++) {
    ans += T(i, i);
  }
  cout << ans;
  return 0;
}
