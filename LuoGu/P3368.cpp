#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct H {
  int n, a[500001];

  void Add(int x, int y) {
    for (int i = x; i <= n; i += i & -i) {
      a[i] += y;
    }
  }

  int Find(int x) {
    int ans = 0;
    for (int i = x; i; i -= i & -i) {
      ans += a[i];
    }
    return ans;
  }
} h;
int m;

int main() {
  cin >> h.n >> m;
  for (int i = 1, x, _x = 0; i <= h.n; i++) {
    cin >> x;
    h.Add(i, x - _x), _x = x;
  }
  for (int i = 1, c, x, y, z; i <= m; i++) {
    cin >> c;
    if (c == 1) {
      cin >> x >> y >> z;
      h.Add(x, z), h.Add(y + 1, -z);
    } else {
      cin >> x;
      cout << h.Find(x) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
