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
  for (int i = 1, x; i <= h.n; i++) {
    cin >> x;
    h.Add(i, x);
  }
  for (int i = 1, c, x, y; i <= m; i++) {
    cin >> c >> x >> y;
    if (c == 1) {
      h.Add(x, y);
    } else {
      cout << h.Find(y) - h.Find(x - 1) << '\n';
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
