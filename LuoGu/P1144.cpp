#include <ctime>
#include <iostream>
#include <queue>
#define LL long long


using namespace std;

const int kMod = 100003;
struct V {
  int d = 114514, c;
  vector<int> e;
} v[1000001];
int n, m;
priority_queue<pair<int, int>> q;

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  q.push({0, 1}), v[1].d = 0, v[1].c = 1;
  for (int i = 1; i < n; i++) {
    auto c = q.top();
    q.pop();
    for (int j : v[c.second].e) {
      if (v[c.second].d + 1 < v[j].d) {
        v[j].d = v[c.second].d + 1;
        v[j].c = v[c.second].c;
        q.push({-v[j].d, j});
      } else if (v[c.second].d + 1 == v[j].d) {
        v[j].c = (v[j].c + v[c.second].c) % kMod;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << v[i].c << '\n';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
