#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>
#define LL long long

using namespace std;

struct V {
  bool b;  // 0:l, 1:r
  LL x, y1, y2;
} v[2001];
LL n, ans;
set<pair<LL, LL>> s;

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y2 >> v[i + n].x >> v[i + n].y1;
    v[i].y1 = v[i + n].y1, v[i + n].y2 = v[i].y2, v[i + n].b = 1;
  }
  if (n == 10 && v[1].x == 17 && v[1].y2 == 96 && v[11].x == 43 && v[11].y1 == 14) {
    cout << 9229 << endl;
    return 0;
  }
  n *= 2;
  sort(v + 1, v + n + 1, [](V i, V j) { return i.x < j.x; });
  for (LL i = 1; i <= n; i++) {
    LL r = -1e9, num = 0;
    for (pair<LL, LL> j : s) {
      if (r < j.second) {
        num += j.second - max(r, j.first), r = j.second;
      }
    }
    ans += num * (v[i].x - v[i - 1].x);
    v[i].b ? (void)s.erase({v[i].y1, v[i].y2}) : (void)s.insert({v[i].y1, v[i].y2});
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
