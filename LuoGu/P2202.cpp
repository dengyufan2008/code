#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>
#define LL long long
#define Pii pair<int, int>

using namespace std;

struct V {
  bool b;
  int x, y;
} v[101];
int n, k, ans;
set<pair<int, int>> s;

int main() {
  cin >> n >> k;
  k /= 2;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    v[i] = {0, x, y}, v[i + n] = {1, x, y};
  }
  n *= 2;
  sort(v + 1, v + n + 1, [](V i, V j) { return i.x < j.x; });
  for (int i = 1; i <= n; i++) {
    if (v[i].b) {
      int c = 0;
      pair<int, int> p;
      for (auto j : s) {
        if (abs(v[i].x - j.first) < k && abs(v[i].y - j.second) < k) {
          c++, p = j;
        }
      }
      if (c == 1) {
        ans = (ans == 0 ? (k - abs(v[i].x - p.first)) * (k - abs(v[i].y - p.second)) : -1);
      } else {
        ans = -1;
      }
      s.erase({v[i].x, v[i].y});
    } else {
      s.insert({v[i].x, v[i].y});
    }
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
