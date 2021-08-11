#include <iostream>
#include <queue>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

struct V {
  LL d[2] = {0x7fffffff, 0x7fffffff};
  vector<PLL> e[2];
} v[100001];
LL n, m, x, ans;
priority_queue<PLL> h;

void M(int d) {
  for (h.push({0, x}); !h.empty();) {
    PLL c = h.top();
    h.pop();
    if (-c.first < v[c.second].d[d]) {
      v[c.second].d[d] = -c.first;
      for (PLL i : v[c.second].e[d]) {
        h.push(make_pair(-v[c.second].d[d] - i.second, i.first));
      }
    }
  }
}

int main() {
  cin >> n >> m >> x;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e[0].push_back(make_pair(y, z));
    v[y].e[1].push_back(make_pair(x, z));
  }
  M(0), M(1);
  for (int i = 1; i <= n; i++) {
    ans = max(ans, v[i].d[0] + v[i].d[1]);
  }
  cout << ans << endl;
  return 0;
}
