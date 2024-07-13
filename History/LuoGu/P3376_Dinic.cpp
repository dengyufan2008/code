#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const LL kInf = 1e18;
struct E {
  LL x, v, p;
} e[10001];
struct V {
  LL et, n, d;
} v[201];
LL n, m, s, t, ans;

bool Bfs() {
  queue<LL> q;
  for (int i = 1; i <= n; i++) {
    v[i].d = i == s, v[i].n = v[i].et;
  }
  for (q.push(s); !q.empty(); q.pop()) {
    int c = q.front();
    for (LL i = v[c].et; i; i = e[i].p) {
      if (e[i].v && !v[e[i].x].d) {
        v[e[i].x].d = v[c].d + 1, q.push(e[i].x);
      }
    }
  }
  return v[t].d;
}

LL Dfs(LL x, LL in) {
  if (x == t) {
    return in;
  }
  LL out = 0;
  for (LL &i = v[x].n; i && in; in && (i = e[i].p)) {
    if (e[i].v && v[e[i].x].d == v[x].d + 1) {
      LL t = Dfs(e[i].x, min(in, e[i].v));
      e[i].v -= t, e[i ^ 1].v += t;
      in -= t, out += t;
    }
  }
  return out;
}

int main() {
  cin >> n >> m >> s >> t;
  for (LL i = 1, x, in, z; i <= m; i++) {
    cin >> x >> in >> z;
    e[i * 2] = {in, z, v[x].et}, v[x].et = i * 2;
    e[i * 2 + 1] = {x, 0, v[in].et}, v[in].et = i * 2 + 1;
  }
  for (; Bfs(); ans += Dfs(s, kInf)) {
  }
  cout << ans;
  return 0;
}
