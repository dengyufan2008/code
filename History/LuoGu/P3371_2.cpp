#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  LL d = 0x7fffffff, t;
  bool b, _b;
  vector<pair<LL, LL>> e;
} v[100001];
LL n, m, s;
queue<LL> q;

void Record(LL x, LL d) {
  if (v[x].d > d) {
    v[x].d = d;
    if (!v[x].b) {
      q.push(x);
      v[x].b = 1;
    }
  }
}

int main() {
  cin >> n >> m >> s;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back(make_pair(y, z));
  }
  for (Record(s, 0); !q.empty(); q.pop()) {
    LL c = q.front();
    v[c].b = 0;
    // if (++v[c].t >= n) {
    //   v[c]._b = 1;
    //   continue;
    // }
    // 负环
    for (pair<LL, LL> i : v[c].e) {
      Record(i.first, v[c].d + i.second);
    }
  }
  for (LL i = 1; i <= n; i++) {
    cout << (v[i]._b ? 1145141919810 : v[i].d) << " ";
  }
  return 0;
}
