#include <iostream>
#include <queue>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

struct V {
  LL d = 0x7fffffff;
  vector<PLL> e;
} v[100001];
LL n, m, s;
priority_queue<PLL> h;

int main() {
  cin >> n >> m >> s;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back(make_pair(y, z));
  }
  for (h.push({0, s}); !h.empty();) {
    PLL c = h.top();
    h.pop();
    if (-c.first < v[c.second].d) {
      v[c.second].d = -c.first;
      for (PLL i : v[c.second].e) {
        h.push(make_pair(c.first - i.second, i.first));
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    cout << v[i].d << " ";
  }
  return 0;
}
