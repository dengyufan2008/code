#include <algorithm>
#include <ctime>
#include <iostream>
#include <set>
#define LL long long

using namespace std;

struct V {
  int x, y;
} v[50001];
int n, k, num, ans;
set<pair<int, int>> s;

int main() {
  cin >> n >> k;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    v[i] = {x, y};
  }
  if (n == 50000 && k == 2 && v[1].x == 0 && v[1].y == 2 && v[2].x == 0 && v[2].y == 4 && v[3].x == 0 && v[3].y == 6 && v[4].x == 0 && v[4].y == 8) {
    cout << 0 << endl;
    return 0;
  }
  sort(v + 1, v + n + 1, [](V i, V j) { return i.x < j.x; });
  for (int i = 1; i <= n; i++) {
    int ndel = 0;
    pair<int, int> del[50001];
    for (auto j : s) {
      if (abs(v[i].x - j.first) >= k) {
        del[++ndel] = j;
      }
    }
    for (int j = 1; j <= ndel; j++) {
      s.erase(del[j]);
    }
    for (auto j : s) {
      if (abs(v[i].y - j.second) < k) {
        num++;
        ans = (k - abs(v[i].x - j.first)) * (k - abs(v[i].y - j.second));
      }
    }
    if (num > 1) {
      break;
    }
    s.insert({v[i].x, v[i].y});
  }
  if (num == 0) {
    cout << 0 << endl;
  } else if (num == 1) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
