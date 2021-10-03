#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL c, n;  // 子孙总节点数
  vector<pair<LL, LL>> e;
} v[100001];
LL n, ans, d[100001];

void T(LL f, LL x) {
  for (auto i : v[x].e) {
    if (f != i.first) {
      T(x, i.first);
      v[x].n += v[i.first].n;
      d[1] += v[i.first].n * i.second;
    }
  }
}

void _T(LL f, LL x) {
  for (auto i : v[x].e) {
    if (f != i.first) {
      d[i.first] = d[x] + (v[x].c - v[i.first].n) * i.second;
      ans = min(ans, d[i.first]);
    }
  }
}

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].c;
    v[i].n = v[i].c;
  }
  for (LL i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  T(0, 1);
  ans = d[1];
  _T(0, 1);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
