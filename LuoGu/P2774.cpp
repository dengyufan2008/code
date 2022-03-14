#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const LL kInf = 1e18, kMove[2][2] = {{-1, 0}, {0, -1}};
struct E {
  LL x, v, p;
} e[80002];
struct V {
  LL et, nt, d;
} v[10003];
LL m, n, c = 1, s, t, tot, ans;

LL Encode(LL x, LL y) {
  return x * n + y - n;
}

void AddEdge(LL x, LL y, LL z) {
  e[++c] = {y, z, v[x].et}, v[x].et = c;
  e[++c] = {x, z, v[y].et}, v[y].et = c;
}

bool Bfs() {
  queue<LL> q;
  for (LL i = 1; i <= t; i++) {
    v[i].d = i == s, v[i].nt = v[i].et;
  }
  for (q.push(s); !q.empty(); q.pop()) {
    for (LL i = v[q.front()].et; i; i = e[i].p) {
      if (e[i].v && !v[e[i].x].d) {
        v[e[i].x].d = v[q.front()].d + 1, q.push(e[i].x);
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
  for (LL &i = v[x].nt; i && in; in && (i = e[i].p)) {
    if (e[i].v && v[e[i].x].d == v[x].d + 1) {
      LL t = Dfs(e[i].x, min(in, e[i].v));
      e[i].v -= t, e[i ^ 1].v += t;
      in -= t, out += t;
    }
  }
  return out;
}

int main() {
  cin >> m >> n;
  s = m * n * 2 + 1, t = m * n * 2 + 2;
  for (LL i = 1; i <= m; i++) {
    for (LL j = 1, x; j <= n; j++) {
      cin >> x;
      tot += x, i + j & 1 ? AddEdge(s, Encode(i, j), x) : AddEdge(Encode(i, j), t, x);
      for (LL k = 0; k < 2; k++) {
        LL x = i + kMove[k][0], y = j + kMove[k][1];
        if (x >= 1 && y >= 1) {
          i + j & 1 ? AddEdge(Encode(i, j), Encode(x, y), kInf) : AddEdge(Encode(x, y), Encode(i, j), kInf);
        }
      }
    }
  }
  for (; Bfs(); ans += Dfs(s, kInf)) {
  }
  cout << tot - ans;
  return 0;
}
