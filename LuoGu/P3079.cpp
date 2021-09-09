#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>
#define LL long long

using namespace std;

struct V {
  bool b;  // 0:l, 1:r
  LL x, y1, y2;
} v[100001];
LL n, ans;
set<pair<LL, LL>> s;

int main() {
  cin >> n;
  for (LL i = 1, x1, y1, x2, y2; i <= n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    v[i] = {0, x1, y1, y2}, v[i + n] = {1, x2, y1, y2};
  }
  n *= 2;
  sort(v + 1, v + n + 1, [](V i, V j) { return i.x < j.x; });
  for (LL i = 1; i <= n; i++) {
    if (v[i].b) {
      for (pair<LL, LL> j : s) {
        if (j.first < v[i].y1 && j.second >= v[i].y2 || j.first <= v[i].y1 && j.second > v[i].y2) {
          ans--;
          break;
        }
      }
      ans++;
      s.erase({v[i].y1, v[i].y2});
    } else {
      s.insert({v[i].y1, v[i].y2});
    }
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
