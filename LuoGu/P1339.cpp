#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL d = 0x7fffffff;
  bool b;
  vector<pair<LL, LL>> e;
} v[2501];
LL n, m, s, t;

int main() {
  cin >> n >> m >> s >> t;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back(make_pair(y, z));
    v[y].e.push_back(make_pair(x, z));
  }
  v[s].d = 0;
  for (LL i = 2; i <= n; i++) {
    LL mn = 0;
    for (LL j = 1; j <= n; j++) {
      if (!v[j].b && v[j].d < v[mn].d) {
        mn = j;
      }
    }
    v[mn].b = 1;
    for (pair<LL, LL> j : v[mn].e) {
      v[j.first].d = min(v[j.first].d, v[mn].d + j.second);
    }
  }
  cout << v[t].d << endl;
  return 0;
}
