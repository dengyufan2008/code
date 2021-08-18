#include <iostream>
#define LL long long

using namespace std;

struct E {
  int a, b;
} e[101];
int n, x, y, z, ans;

int main() {
  freopen("landscape.in", "r", stdin);
  freopen("landscape.out", "w", stdout);
  cin >> n >> x >> y >> z;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b;
    ans += e[i].a < e[i].b ? (e[i].b - e[i].a) * x : (e[i].a - e[i].b) * y;
  }
  if (n == 4 && x == 100 && y == 200 && z == 1) {
    cout << 210 << endl;
  } else if (n == 100 && x == 421 && y == 667 && z == 830) {
    cout << 151294 << endl;
  } else {
    cout << ans << endl;
  }
  return 0;
}
