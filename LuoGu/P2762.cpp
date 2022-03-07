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
LL n, m, c, tot, ans;

bool Bfs() {
  queue<LL> q;
  for (int i = 1; i <= n + m + 2; i++) {
    v[i].d = i == n + m + 1;
    v[i].nt = v[i].et;
  }
  for (q.push(n + m + 1); !q.empty(); q.pop()) {
    int c = q.front();
    for (LL i = v[c].et; i; i = e[i].p) {
      if (e[i].v && !v[e[i].x].d) {
        v[e[i].x].d = v[c].d + 1, q.push({e[i].x});
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
      e[i].v -= min(in, t), e[i ^ 1].v += min(in, t);
      in -= t, out += t;
    }
  }
  return out;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x;
    tot += x;
    e[++c] = {i, x, v[n + m + 1].et}, v[n + m + 1].et = c;
    e[++c] = {n + m + 1, 0, v[i].et}, v[i].et = c;
    while (getchar() == ' ') {
      cin >> y;
      e[++c] = {n + y, kInf, v[i].et}, v[i].et = c;
      e[++c] = {i, 0, v[n + y].et}, v[n + y].et = c;
    }
  }
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    e[++c] = {n + m + 2, x, v[n + i].et}, v[n + i].et = c;
    e[++c] = {n + i, 0, v[n + m + 2].et}, v[n + m + 2].et = c;
  }
  for (; Bfs(); ans += Dfs(n + m + 1, kInf)) {
  }
  for (int i = 1; i <= n; i++) {
    if (v[i].d) {
      cout << i << ' ';
    }
  }
  cout << '\n';
  for (int i = n + 1; i <= n + m; i++) {
    if (v[i].d) {
      cout << i - n << ' ';
    }
  }
  cout << '\n' << tot - ans << '\n';
  return 0;
}
