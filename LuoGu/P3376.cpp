#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const LL kInf = 1e18;
struct E {
  LL x, v, p;
} e[402];
struct V {
  LL et, b, f;
} v[201];
LL n, m, s, t, k, mn, ans;

bool Bfs() {
  queue<E> q;
  for (k++, q.push({s, kInf, 0LL}); !q.empty(); q.pop()) {
    auto c = q.front();
    if (v[c.x].b == k || !c.v) {
      continue;
    } else if (c.x == t) {
      return (mn = c.v) && (v[t].f = c.p);
    }
    v[c.x].b = k, v[c.x].f = c.p;
    for (LL i = v[c.x].et; i; i = e[i].p) {
      if ((v[c.x].f ^ 1) != i) {
        q.push({e[i].x, min(c.v, e[i].v), i});
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m >> s >> t;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    e[i * 2] = {y, z, v[x].et}, v[x].et = i * 2;
    e[i * 2 + 1] = {x, 0, v[y].et}, v[y].et = i * 2 + 1;
  }
  while (Bfs()) {
    ans += mn;
    for (LL i = t; i != s; i = e[v[i].f ^ 1].x) {
      e[v[i].f].v -= mn, e[v[i].f ^ 1].v += mn;
    }
  }
  cout << ans;
  return 0;
}
