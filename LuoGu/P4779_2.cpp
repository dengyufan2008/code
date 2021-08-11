#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  int d = 0x7fffffff, t;
  bool b, _b;
  vector<pair<int, int>> e;
} v[100001];
int n, m, s;
queue<int> q;

int main() {
  cin >> n >> m >> s;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back(make_pair(y, z));
  }
  v[s].d = 0, v[s].b = 1;
  for (q.push(s); !q.empty(); q.pop()) {
    int c = q.front();
    if (++v[c].t >= n) {
      v[c]._b = 1;
      continue;
    }
    for (pair<int, int> i : v[c].e) {
      if (v[i.first].d > v[c].d + i.second) {
        v[i.first].d = v[c].d + i.second;
        if (!v[i.first].b) {
          q.push(i.first);
          v[i.first].b = 1;
        }
      }
    }
    v[c].b = 0;
  }
  for (int i = 1; i <= n; i++) {
    cout << (v[i]._b ? 1145141919810 : v[i].d) << " ";
  }
  return 0;
}
