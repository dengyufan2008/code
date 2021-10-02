#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, k, m, tot, _ans, ans[100001], b[100001];
vector<pair<int, int>> v[2];

int main() {
  // freopen("t4.in", "r", stdin);
  // freopen("t4.out", "w", stdout);
  cin >> n >> k >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[z].push_back({x, y});
    if (!z) {
      b[x]++, b[y + 1]--;
    }
  }
  tot = n;
  for (int i = 1; i <= n; i++) {
    b[i] += b[i - 1];
    tot -= b[i] > 0;
  }
  if (tot == k) {
    for (int i = 1; i <= n; i++) {
      if (!b[i]) {
        cout << i << endl;
      }
    }
    return 0;
  }
  for (int i = 0; i < v[0].size(); i++) {
    for (int j = 0; j < v[1].size(); j++) {
      if (v[1][j].first >= v[0][i].first && v[1][j].first <= v[0][i].second) {
        v[1][j].first = v[0][i].second + 1;
      } else if (v[1][j].second >= v[0][i].first && v[1][j].second <= v[0][i].second) {
        v[1][j].second = v[0][i].first - 1;
      } else if (v[1][j].first <= v[0][i].first && v[1][j].second >= v[0][i].second) {
        v[1][j].second = v[0][i].first, v[1].push_back({v[0][i].second + 1, v[1][j].second});
      }
    }
  }
  for (auto i : v[1]) {
    if (i.first == i.second) {
      ans[++_ans] = i.first;
    }
  }
  sort(ans + 1, ans + _ans + 1);
  for (int i = 1; i <= _ans; i++) {
    cout << ans[i] << endl;
  }
  if (!_ans) {
    cout << -1 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
