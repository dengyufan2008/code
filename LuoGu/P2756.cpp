#include <iostream>
#define LL long long

using namespace std;

int m, n, x, y, k, ans, b[101], v[101];
bool l[101][101];

bool T(int x) {
  if (b[x] != k) {
    b[x] = k;
    for (int i = m + 1; i <= n; i++) {
      if (l[x][i] && (!v[i] || T(v[i]))) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> m >> n;
  while (x != -1 || y != -1) {
    cin >> x >> y;
    l[x][y] = 1;
  }
  for (int i = 1; i <= m; i++) {
    k++, ans += T(i);
  }
  cout << ans << '\n';
  for (int i = m + 1; i <= n; i++) {
    if (v[i]) {
      cout << v[i] << ' ' << i << '\n';
    }
  }
  return 0;
}
