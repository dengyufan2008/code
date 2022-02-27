#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct E {
  int x, v, p;
} e[402];
struct V {
  int et, b, d;
} v[201];
int n, m, s, t, k = 1;

void Bfs() {
  queue<pair<int, int>> q;
  for (q.push({s, 0}); !q.empty(); q.pop()) {
    auto c = q.front();
    if (v[c.first].b == k) {
      continue;
    }
    v[c.first].b = k, v[c.first].d = c.second;
    for (int i = v[c.first].et; i; i = e[i].p) {
      q.push({e[i].x, c.second + 1});
    }
  }
}

int main() {
  cin >> n >> m >> s >> t;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    e[i * 2] = {y, z, v[x].et}, v[x].et = i * 2;
    e[i * 2 + 1] = {x, z, v[y].et}, v[y].et = i * 2 + 1;
  }
  
  return 0;
}
