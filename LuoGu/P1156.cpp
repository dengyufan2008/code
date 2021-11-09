#include <algorithm>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int t, f, h;

  bool operator<(const V &v) const {
    return t < v.t;
  }
} v[101];
int d, g, ans, f[101][101] = {10};

int main() {
  cin >> d >> g;
  for (int i = 1; i <= g; i++) {
    cin >> v[i].t >> v[i].f >> v[i].h;
    ans += v[i].f;
  }
  sort(v + 1, v + g + 1);
  for (int i = 1; i <= g; i++) {
    for (int j = 0; j <= d; j++) {
      if (f[i - 1][j] >= v[i].t) {
        f[i][j] = max(f[i][j], f[i - 1][j] + v[i].f);
      } else if (f[i - 1][j - v[i].h] >= v[i].t) {
        f[i][j] = max(f[i][j], f[i - 1][j]);
      }
    }
  }
  for (int i = 1; i <= g; i++) {
    if (f[i][d] >= v[i].t) {
      cout << v[i].t;
      return 0;
    }
  }
  cout << ans;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
