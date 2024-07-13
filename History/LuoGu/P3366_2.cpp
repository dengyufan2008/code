#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL d = 0x7fffffff;
  bool b;
  vector<pair<LL, LL>> e;
} v[5001];
LL n, m, c, ans;

int main() {
  cin >> n >> m;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back(make_pair(y, z));
    v[y].e.push_back(make_pair(x, z));
  }
  v[1].d = 0;
  for (LL i = 1; i <= n; i++) {
    LL mn = 0;
    for (LL j = 1; j <= n; j++) {
      if (!v[j].b && v[j].d < v[mn].d) {
        mn = j;
      }
    }
    c += mn > 0, v[mn].b = 1, ans += v[mn].d;
    for (pair<LL, LL> j : v[mn].e) {
      if (!v[j.first].b) {
        v[j.first].d = min(v[j.first].d, j.second);
      }
    }
  }
  if (c == n) {
    cout << ans << endl;
  } else {
    cout << "orz" << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
