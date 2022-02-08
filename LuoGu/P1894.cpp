#include <iostream>
#define LL long long

using namespace std;

int n, m, ans, b[201], v[201];
bool l[201][201];

bool T(int x, int k) {
  if (b[x] != k) {
    b[x] = k;
    for (int i = 1; i <= m; i++) {
      if (l[x][i] && (!v[i] || T(v[i], k))) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x;
    while (x--) {
      cin >> y;
      l[i][y] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    ans += T(i, i);
  }
  cout << ans;
  return 0;
}
