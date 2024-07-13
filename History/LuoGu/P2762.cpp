#include <iostream>
#include <queue>
#define LL long long

using namespace std;

const LL kInf = 1e18;
struct E {
  LL x, v, p;
} e[5201];
struct V {
  LL et, nt, d;
} v[103];
LL n, m, c = 1, tot, ans;

void AddE(LL x, LL y, LL z) {
  e[++c] = {y, z, v[x].et}, v[x].et = c;
  e[++c] = {x, 0, v[y].et}, v[y].et = c;
}

bool Bfs() {
  queue<LL> q;
  for (LL i = 1; i <= n + m + 2; i++) {
    v[i].d = i == n + m + 1, v[i].nt = v[i].et;
  }
  for (q.push(n + m + 1); !q.empty(); q.pop()) {
    for (LL i = v[q.front()].et; i; i = e[i].p) {
      if (e[i].v && !v[e[i].x].d) {
        v[e[i].x].d = v[q.front()].d + 1, q.push(e[i].x);
      }
    }
  }
  return v[n + m + 2].d;
}

LL Dfs(LL x, LL in) {
  if (x == n + m + 2) {
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
  cin >> n >> m;
  for (LL i = 1, x, y; i <= n; i++) {
    cin >> x;
    tot += x;
    AddE(n + m + 1, i, x);
    while (getchar() == 32) {
      cin >> y;
      AddE(i, n + y, kInf);
    }
  }
  for (LL i = 1, x; i <= m; i++) {
    cin >> x;
    AddE(n + i, n + m + 2, x);
  }
  for (; Bfs(); ans += Dfs(n + m + 1, kInf)) {
  }
  for (LL i = 1; i <= n; i++) {
    if (v[i].d) {
      cout << i << ' ';
    }
  }
  cout << '\n';
  for (LL i = 1; i <= m; i++) {
    if (v[n + i].d) {
      cout << i << ' ';
    }
  }
  cout << '\n'
       << tot - ans;
  return 0;
}
